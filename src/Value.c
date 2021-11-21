// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Value.c
 *	Generated 12/31/2019 15:27:11
 *
 */

 
/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <Value_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    /* The following tables were generated from:
     * "value_type.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the Value_Type_entries
    // table. 0 means no enum entry.
    const
    uint16_t    Value_Type_index[20] = {
        19,
        1,
        4,
        5,
        10,
        7,
        8,
        9,
        18,
        15,
        16,
        17,
        11,
        12,
        13,
        14,
        2,
        3,
        6,
        0,
    };


    typedef struct {
        const
        char            *pDesc;
        uint32_t        value;
    } Value_Type_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    const
    Value_Type_entry    Value_Type_entries[] = {
        {"VALUE_TYPE_ASTR",1},
        {"VALUE_TYPE_DATA",16},
        {"VALUE_TYPE_DATA_FREE",17},
        {"VALUE_TYPE_DOUBLE",2},
        {"VALUE_TYPE_FALSE",3},
        {"VALUE_TYPE_HIGHEST",18},
        {"VALUE_TYPE_INT16",5},
        {"VALUE_TYPE_INT32",6},
        {"VALUE_TYPE_INT64",7},
        {"VALUE_TYPE_INT8",4},
        {"VALUE_TYPE_MONEY64",12},
        {"VALUE_TYPE_NULL",13},
        {"VALUE_TYPE_OBJECT",14},
        {"VALUE_TYPE_TRUE",15},
        {"VALUE_TYPE_UINT16",9},
        {"VALUE_TYPE_UINT32",10},
        {"VALUE_TYPE_UINT64",11},
        {"VALUE_TYPE_UINT8",8},
        {"VALUE_TYPE_UNKNOWN",0},
    };

    const
    uint32_t    cValue_Type_entries = 19;




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void            Value_FreeData (
        VALUE_DATA      *this
    )
    {

        switch (this->type) {

            case VALUE_TYPE_INT16:
                break;

            case VALUE_TYPE_INT32:
                break;

            case VALUE_TYPE_INT64:
                break;

            case VALUE_TYPE_UINT16:
                break;

            case VALUE_TYPE_UINT32:
                break;

            case VALUE_TYPE_UINT64:
                break;

            case VALUE_TYPE_ASTR:
            case VALUE_TYPE_FALSE:
            case VALUE_TYPE_MONEY64:
            case VALUE_TYPE_NULL:
            case VALUE_TYPE_OBJECT:
            case VALUE_TYPE_TRUE:
                if (this->value.pObject) {
                    obj_Release(this->value.pObject);
                    this->value.pObject = OBJ_NIL;
                }
                break;

            case VALUE_TYPE_DATA:
                this->value.data.pData = NULL;
                this->value.data.length = 0;
                break;

            case VALUE_TYPE_DATA_FREE:
                if (this->value.data.pData) {
                    mem_Free(this->value.data.pData);
                    this->value.data.pData = NULL;
                }
                this->value.data.length = 0;
                break;

        }
        this->type = VALUE_TYPE_UNKNOWN;

    }



    // Given an enum value, return its character format.
    const
    char *            Value_TypeToDesc(
        uint32_t        value
    )
    {
        if (value >= 20) {
            return "<<<Unknown Enum Value>>>";
        }
        if (Value_Type_index[value]) {
            return Value_Type_entries[Value_Type_index[value]-1].pDesc;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }



    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        Value_DescToType(
        char            *pDesc
    )
    {
        int             iRc;
        uint32_t        iMax = cValue_Type_entries;
        uint32_t        i    = 0;
        uint32_t        high = 0;
        uint32_t        low  = 0;
        uint32_t        mid  = 0;

        if (iMax > 10) {
            for (i=0; i<iMax; i++) {
                iRc = strcmp(pDesc, Value_Type_entries[i].pDesc);
                if (0 == iRc) {
                    return Value_Type_entries[i].value + 1;
                }
                if (iRc < 0) {
                    break;
                }
            }
        } else {
            high = iMax - 1;
            while (low < high) {
                mid = (high + low) / 2;
                i = mid + 1;
                iRc = strcmp(pDesc, Value_Type_entries[i].pDesc);
                if (iRc < 0) {
                    high = mid;
                } else if (iRc == 0) {
                    return Value_Type_entries[i].value + 1;
                } else {
                    low = mid + 1;
                }
            }
            if( high == low ) {
                i = low;
                iRc = strcmp(pDesc, Value_Type_entries[i].pDesc);
                if (0 == iRc) {
                    return Value_Type_entries[i].value + 1;
                }
            }
        }
        return 0;
    }







    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    VALUE_DATA *     Value_Alloc (
        void
    )
    {
        VALUE_DATA       *this;
        uint32_t        cbSize = sizeof(VALUE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    VALUE_DATA *     Value_New (
        void
    )
    {
        VALUE_DATA       *this;
        
        this = Value_Alloc( );
        if (this) {
            this = Value_Init(this);
        } 
        return this;
    }



    VALUE_DATA *    Value_NewAStr (
        ASTR_DATA       *pValue
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setAStr(this, pValue);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewData (
        int32_t         length,
        uint8_t         *pData
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setData(this, length, pData);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewDataCopy (
        int32_t         length,
        uint8_t         *pData
    )
    {
        VALUE_DATA      *this;
        bool            fRc;
        uint8_t         *pData2;

        this = Value_New();
        if (this) {
            pData2 = mem_Malloc(length);
            if (pData2) {
                memmove(pData2, pData, length);
                fRc = Value_setDataFree(this, length, pData2);
                if (!fRc) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            } else {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewDataFree (
        int32_t         length,
        uint8_t         *pData
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setDataFree(this, length, pData);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewDouble (
        double          value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setDouble(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewFalse (
        void
    )
    {
        VALUE_DATA      *this;

        this = Value_New();
        if (this) {
            this->type = VALUE_TYPE_FALSE;
            this->value.pObject = False_New();
            if (OBJ_NIL == this->value.pObject) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        return this;
    }


    VALUE_DATA *    Value_NewI8 (
        int8_t          value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI8(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewI16 (
        int16_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI16(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewI32 (
        int32_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI32(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewI64 (
        int64_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setI64(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewMoney64 (
        MONEY64_DATA    *pValue
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setMoney64(this, pValue);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewNull (
        void
    )
    {
        VALUE_DATA      *this;

        this = Value_New();
        if (this) {
            this->type = VALUE_TYPE_NULL;
            this->value.pObject = Null_New();
            if (OBJ_NIL == this->value.pObject) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        return this;
    }


    VALUE_DATA *    Value_NewObject (
        OBJ_DATA        *pValue
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setObject(this, pValue);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewTrue (
        void
    )
    {
        VALUE_DATA      *this;

        this = Value_New();
        if (this) {
            this->type = VALUE_TYPE_TRUE;
            this->value.pObject = True_New();
            if (OBJ_NIL == this->value.pObject) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        return this;
    }


    VALUE_DATA *    Value_NewU8 (
        uint8_t         value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU8(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewU16 (
        uint16_t        value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU16(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewU32 (
        uint32_t        value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU32(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }


    VALUE_DATA *    Value_NewU64 (
        uint64_t        value
    )
    {
        VALUE_DATA      *this;
        bool            fRc;

        this = Value_New();
        if (this) {
            fRc = Value_setU64(this, value);
            if (!fRc) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A S t r
    //---------------------------------------------------------------

    ASTR_DATA *     Value_getAStr (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->type == VALUE_TYPE_ASTR) {
            return this->value.pObject;
        }
        else {
            return OBJ_NIL;
        }
    }


    bool            Value_setAStr (
        VALUE_DATA      *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        Value_FreeData(this);
        this->value.pObject = pValue;
        this->type = VALUE_TYPE_ASTR;

        return true;
    }



    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------

    const
    uint8_t *       Value_getData (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if ((this->type == VALUE_TYPE_DATA) || (this->type == VALUE_TYPE_DATA_FREE)) {
            return this->value.data.pData;
        }
        else if (this->value.pObject && (this->type == VALUE_TYPE_ASTR)) {
            return (const uint8_t *)AStr_getData(this->value.pObject);
        }
        else {
            return NULL;
        }
    }


    uint32_t        Value_getDataLen (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if ((this->type == VALUE_TYPE_DATA) || (this->type == VALUE_TYPE_DATA_FREE)){
            return this->value.data.length;
        }
        else {
            return 0;
        }
    }


    bool            Value_setData (
        VALUE_DATA      *this,
        uint32_t        length,
        void            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.data.pData = pValue;
        this->value.data.length  = length;
        this->type = VALUE_TYPE_DATA;

        return true;
    }


    bool            Value_setDataFree (
        VALUE_DATA      *this,
        uint32_t        length,
        void            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.data.pData = mem_Malloc(length);
        if (NULL == this->value.data.pData) {
            return false;
        }
        memmove(this->value.data.pData, pValue, length);
        this->value.data.length  = length;
        this->type = VALUE_TYPE_DATA_FREE;

        return true;
    }



    //---------------------------------------------------------------
    //                          D o u b l e
    //---------------------------------------------------------------

    double          Value_getDouble (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_DOUBLE) {
            return this->value.flt;
        }
        else {
            return 0;
        }
    }


    bool            Value_setDouble (
        VALUE_DATA      *this,
        double          value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.flt = value;
        this->type = VALUE_TYPE_DOUBLE;

        return true;
    }



    //---------------------------------------------------------------
    //                          F a l s e
    //---------------------------------------------------------------

    OBJ_DATA *      Value_getFalse (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->type == VALUE_TYPE_FALSE) {
            return this->value.pObject;
        }
        else {
            return OBJ_NIL;
        }
    }


    bool            Value_setFalse (
        VALUE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.pObject = False_New();
        this->type = VALUE_TYPE_FALSE;

        return true;
    }



    //---------------------------------------------------------------
    //                        M i s c 1 6
    //---------------------------------------------------------------

    uint16_t        Value_getMisc16 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->misc16;
    }


    bool            Value_setMisc16 (
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->misc16 = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 8
    //---------------------------------------------------------------

    int8_t          Value_getI8 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_INT8) {
            return this->value.i8;
        }
        else {
            return 0;
        }
    }


    bool            Value_setI8 (
        VALUE_DATA      *this,
        int8_t          value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i8 = value;
        this->type = VALUE_TYPE_INT8;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 1 6
    //---------------------------------------------------------------

    int16_t         Value_getI16 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_INT16) {
            return this->value.i16;
        }
        else {
            return 0;
        }
    }


    bool            Value_setI16 (
        VALUE_DATA      *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i16 = value;
        this->type = VALUE_TYPE_INT16;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 3 2
    //---------------------------------------------------------------

    int32_t         Value_getI32 (
        VALUE_DATA      *this
    )
    {
        int32_t         i = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        switch (this->type) {
            case VALUE_TYPE_INT8:
                i = this->value.i8;
            case VALUE_TYPE_INT16:
                i = this->value.i16;
            case VALUE_TYPE_INT32:
                i = this->value.i32;
        }

        return i;
    }


    bool            Value_setI32 (
        VALUE_DATA      *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i32 = value;
        this->type = VALUE_TYPE_INT32;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n t 6 4
    //---------------------------------------------------------------

    int64_t         Value_getI64 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_INT64) {
            return this->value.i64;
        }
        else {
            return 0;
        }
    }


    bool            Value_setI64 (
        VALUE_DATA      *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.i64 = value;
        this->type = VALUE_TYPE_INT64;

        return true;
    }



    //---------------------------------------------------------------
    //                        M o n e y 6 4
    //---------------------------------------------------------------

    MONEY64_DATA *  Value_getMoney64 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->type == VALUE_TYPE_MONEY64) {
            return this->value.pObject;
        }
        else {
            return OBJ_NIL;
        }
    }


    bool            Value_setMoney64 (
        VALUE_DATA      *this,
        MONEY64_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        Value_FreeData(this);
        this->value.pObject = pValue;
        this->type = VALUE_TYPE_MONEY64;

        return true;
    }



    //---------------------------------------------------------------
    //                          N u l l
    //---------------------------------------------------------------

    OBJ_DATA *      Value_getNull (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->type == VALUE_TYPE_NULL) {
            return this->value.pObject;
        }
        else {
            return OBJ_NIL;
        }
    }


    bool            Value_setNull (
        VALUE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.pObject = Null_New();
        this->type = VALUE_TYPE_NULL;

        return true;
    }



    //---------------------------------------------------------------
    //                          O b j e c t
    //---------------------------------------------------------------

    OBJ_DATA *      Value_getObject (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->type == VALUE_TYPE_OBJECT) {
            return this->value.pObject;
        }
        else {
            return OBJ_NIL;
        }
    }


    bool            Value_setObject (
        VALUE_DATA      *this,
        OBJ_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        Value_FreeData(this);
        this->value.pObject = pValue;
        this->type = VALUE_TYPE_OBJECT;

        return true;
    }



    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------

    OBJ_ID          Value_getOther (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pOther;
    }


    bool            Value_setOther (
        VALUE_DATA      *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pOther) {
            obj_Release(this->pOther);
        }
        this->pOther = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Value_getSize (
        VALUE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Value_getSuperVtbl (
        VALUE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T r u e
    //---------------------------------------------------------------

    OBJ_DATA *      Value_getTrue (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->type == VALUE_TYPE_TRUE) {
            return this->value.pObject;
        }
        else {
            return OBJ_NIL;
        }
    }


    bool            Value_setTrue (
        VALUE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.pObject = True_New();
        this->type = VALUE_TYPE_TRUE;

        return true;
    }



    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    uint16_t        Value_getType (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            Value_setType (
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->type = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 8
    //---------------------------------------------------------------

    uint8_t         Value_getU8 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_UINT8) {
            return this->value.u8;
        }
        else {
            return 0;
        }
    }


    bool            Value_setU8 (
        VALUE_DATA      *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u8 = value;
        this->type = VALUE_TYPE_UINT8;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 1 6
    //---------------------------------------------------------------

    uint16_t        Value_getU16 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_UINT16) {
            return this->value.u16;
        }
        else {
            return 0;
        }
    }


    bool            Value_setU16 (
        VALUE_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u16 = value;
        this->type = VALUE_TYPE_UINT16;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 3 2
    //---------------------------------------------------------------

    uint32_t        Value_getU32 (
        VALUE_DATA      *this
    )
    {
        uint32_t        i = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        switch (this->type) {
            case VALUE_TYPE_UINT8:
                i = this->value.u8;
            case VALUE_TYPE_UINT16:
                i = this->value.u16;
            case VALUE_TYPE_UINT32:
                i = this->value.u32;
        }

        return i;
    }


    bool            Value_setU32 (
        VALUE_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u32 = value;
        this->type = VALUE_TYPE_UINT32;

        return true;
    }



    //---------------------------------------------------------------
    //                          U i n t 6 4
    //---------------------------------------------------------------

    uint64_t        Value_getU64 (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->type == VALUE_TYPE_UINT64) {
            return this->value.u64;
        }
        else {
            return 0;
        }
    }


    bool            Value_setU64 (
        VALUE_DATA      *this,
        uint64_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Value_FreeData(this);
        this->value.u64 = value;
        this->type = VALUE_TYPE_UINT64;

        return true;
    }



    //---------------------------------------------------------------
    //                          U s e r
    //---------------------------------------------------------------

    uint32_t        Value_getUser (
        VALUE_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->user;
    }


    bool            Value_setUser (
        VALUE_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->user = value;

        return true;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Value_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another VALUE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Value_Assign (
        VALUE_DATA		*this,
        VALUE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Value_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        Value_FreeData(pOther);

        // Create a copy of objects and areas in this object placing
        // them in other.
        switch (this->type) {

            case VALUE_TYPE_DOUBLE:
                pOther->value.flt = this->value.flt;
                break;

            case VALUE_TYPE_INT8:
                pOther->value.i8 = this->value.i8;
                break;

            case VALUE_TYPE_INT16:
                pOther->value.i16 = this->value.i16;
                break;

            case VALUE_TYPE_INT32:
                pOther->value.i32 = this->value.i32;
                break;

            case VALUE_TYPE_INT64:
                pOther->value.i64 = this->value.i64;
                break;

            case VALUE_TYPE_UINT8:
                pOther->value.u8 = this->value.u8;
                break;

            case VALUE_TYPE_UINT16:
                pOther->value.u16 = this->value.u16;
                break;

            case VALUE_TYPE_UINT32:
                pOther->value.u32 = this->value.u32;
                break;

            case VALUE_TYPE_UINT64:
                pOther->value.u64 = this->value.u64;
                break;

            case VALUE_TYPE_ASTR:
            case VALUE_TYPE_MONEY64:
            case VALUE_TYPE_OBJECT:
                if (this->value.pObject) {
                    if (obj_getVtbl(this->value.pObject)->pCopy) {
                        pOther->value.pObject =
                            obj_getVtbl(this->value.pObject)->pCopy(this->value.pObject);
                    }
                    else {
                        obj_Retain(this->value.pObject);
                        pOther->value.pObject = this->value.pObject;
                    }
                }
                break;

            case VALUE_TYPE_DATA:
                pOther->value.data.pData = this->value.data.pData;
                pOther->value.data.length = this->value.data.length;
                break;

            case VALUE_TYPE_DATA_FREE:
                pOther->value.data.pData = mem_Malloc(this->value.data.length);
                if (NULL == this->value.data.pData) {
                    return ERESULT_OUT_OF_MEMORY;
                }
                memmove(
                        pOther->value.data.pData,
                        this->value.data.pData,
                        this->value.data.length
                );
                pOther->value.data.length = this->value.data.length;
                break;

            default:
                break;
        }
        pOther->type = this->type;
        pOther->user = this->user;

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Value_Compare (
        VALUE_DATA     *this,
        VALUE_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Value_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        switch (this->type) {

            case VALUE_TYPE_DOUBLE:
                iRc = (int)(this->value.flt - pOther->value.flt);
                break;

            case VALUE_TYPE_INT8:
                iRc = this->value.i8 - pOther->value.i8;
                break;

            case VALUE_TYPE_INT16:
                iRc = this->value.i16 - pOther->value.i16;
                break;

            case VALUE_TYPE_INT32:
                iRc = this->value.i32 - pOther->value.i32;
                break;

            case VALUE_TYPE_INT64:
                iRc = (int)(this->value.i64 - pOther->value.i64);
                break;

            case VALUE_TYPE_UINT8:
                iRc = this->value.u8 - pOther->value.u8;
                break;

            case VALUE_TYPE_UINT16:
                iRc = this->value.u16 - pOther->value.u16;
                break;

            case VALUE_TYPE_UINT32:
                iRc = this->value.u32 - pOther->value.u32;
                break;

            case VALUE_TYPE_UINT64:
                iRc = (int)(this->value.u64 - pOther->value.u64);
                break;

            case VALUE_TYPE_ASTR:
            case VALUE_TYPE_MONEY64:
            case VALUE_TYPE_OBJECT:
                if (this->value.pObject) {
                    if (obj_getVtbl(this->value.pObject)->pCompare
                        && obj_getVtbl(pOther->value.pObject)->pCompare) {
                        iRc = obj_getVtbl(this->value.pObject)->pCompare(this, pOther);
                        return iRc;
                    }
                }
                break;

            case VALUE_TYPE_DATA:
            case VALUE_TYPE_DATA_FREE:
                iRc = this->value.data.length - pOther->value.data.length;
                if (0 == iRc) {
                    iRc =   memcmp(
                                 this->value.data.pData,
                                 pOther->value.data.pData,
                                 this->value.data.length
                            );
                }
                break;

            default:
                break;
        }

        
        if (iRc < 0) {
            iRc = -1;
        }
        if (iRc > 0) {
            iRc = 1;
        }
        
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Value      *pCopy = Value_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a VALUE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    VALUE_DATA *     Value_Copy (
        VALUE_DATA       *this
    )
    {
        VALUE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Value_New( );
        if (pOther) {
            eRc = Value_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Value_Dealloc (
        OBJ_ID          objId
    )
    {
        VALUE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((VALUE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Value_setOther(this, OBJ_NIL);
        Value_FreeData(this);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Value_Disable (
        VALUE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Value_Enable (
        VALUE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    VALUE_DATA *   Value_Init (
        VALUE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(VALUE_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_VALUE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Value_Vtbl);
#ifdef  VALUE_JSON_SUPPORT
        JsonIn_RegisterClass(Value_Class());
#endif

        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

    #ifdef NDEBUG
    #else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Value::sizeof(VALUE_DATA) = %lu\n", sizeof(VALUE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(VALUE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Value_IsEnabled (
        VALUE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     T o  M o n e y
    //---------------------------------------------------------------

    MONEY64_DATA *  Value_ToMoney64 (
        VALUE_DATA     *this
    )
    {
        int64_t         i64 = 0;
        MONEY64_DATA    *pMoney = OBJ_NIL;

#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        switch (this->type) {
            case VALUE_TYPE_DOUBLE:
                i64 = (int64_t)this->value.flt;
                break;
            case VALUE_TYPE_INT8:
                i64 = (int64_t)this->value.i8;
                break;
            case VALUE_TYPE_INT16:
                i64 = (int64_t)this->value.i16;
                break;
            case VALUE_TYPE_INT32:
                i64 = (int64_t)this->value.i32;
                break;

            case VALUE_TYPE_INT64:
                i64 = this->value.i64;
                break;

            case VALUE_TYPE_UINT8:
                i64 = (int64_t)this->value.u8;
                break;

            case VALUE_TYPE_UINT16:
                i64 = (int64_t)this->value.u16;
                break;

            case VALUE_TYPE_UINT32:
                i64 = (int64_t)this->value.u32;
                break;

            case VALUE_TYPE_UINT64:
                i64 = (int64_t)this->value.u64;
                break;

            case VALUE_TYPE_MONEY64:
                return this->value.pObject;

            case VALUE_TYPE_ASTR:
            case VALUE_TYPE_DATA:
            case VALUE_TYPE_DATA_FREE:
            case VALUE_TYPE_OBJECT:
            default:
                DEBUG_BREAK();
                return OBJ_NIL;
                break;
        }

        pMoney = Money64_New();
        if (OBJ_NIL == pMoney) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        Money64_setAmount(pMoney, i64);

        return pMoney;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Value_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Value", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Value_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        VALUE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(VALUE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Value_Class();
                break;
                
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Value_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Value_Enable;
                        }
                        break;

                    case 'P':
#ifdef  VALUE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Value_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Value_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Value_ToDebugString;
                        }
                        if (str_Compare("ToString", (char *)pStr) == 0) {
                            return Value_ToString;
                        }
#ifdef  VALUE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Value_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Value_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Value_ToDebugString)
                    return "ToDebugString";
                if (pData == Value_ToString)
                    return "ToString";
#ifdef  VALUE_JSON_SUPPORT
                if (pData == Value_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Value_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Value_ToDebugString (
        VALUE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Value_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        switch (this->type) {
            case VALUE_TYPE_ASTR:           // AStr Object
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tASTR - \"%s\"\n",
                            AStr_getData(this->value.pObject)
                    );
                break;

            case VALUE_TYPE_DOUBLE:         // 64-bit Float
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tDOUBLE - %f\n",
                            this->value.flt
                    );
                break;

            case VALUE_TYPE_INT8:           // int8_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tI8 - %d\n",
                            this->value.i8
                    );
                break;

            case VALUE_TYPE_INT16:          // int16_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tI16 - %d\n",
                            this->value.i16
                    );
                break;

            case VALUE_TYPE_INT32:          // int32_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tI32 - %d\n",
                            this->value.i32
                    );
                break;

            case VALUE_TYPE_INT64:          // int64_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tI64 - %d\n",
                            this->value.i64
                    );
                break;

            case VALUE_TYPE_UINT8:          // uint8_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tU8 - %u\n",
                            this->value.u8
                    );
                break;

            case VALUE_TYPE_UINT16:         // uint16_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tU16 - %u\n",
                            this->value.u16
                    );
                break;

            case VALUE_TYPE_UINT32:         // uint32_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tU32 - %u\n",
                            this->value.u32
                    );
                break;

            case VALUE_TYPE_UINT64:         // uint64_t
                eRc = AStr_AppendPrint(
                            pStr,
                            "\tU64 - %u\n",
                            this->value.u64
                    );
                break;

            case VALUE_TYPE_OBJECT: // Any object that supports "ToDebugString" method
                if (this->value.pObject) {
                    OBJ_DATA        *pObj = this->value.pObject;
                    if (pObj->pVtbl->pToDebugString) {
                        pWrkStr = pObj->pVtbl->pToDebugString(pObj, indent+4);
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                    }
                }
                break;

            case VALUE_TYPE_DATA:           // Any data (pointer and length) (pointer and length
                //                          // must be valid for life of object)
                break;

            case VALUE_TYPE_DATA_FREE:      // Any data (pointer and length) which will be freed
                //                          // using mem_Free() when no longer needed (pointer
                //                          // and length must be valid for life of object)
                break;

            default:
                break;
        }

#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    /*!
     Create a string that describes this object's value.
     Example:
     @code
        ASTR_DATA      *pDesc = Value_ToString(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Value_ToString (
        VALUE_DATA      *this
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Value_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        switch (this->type) {
            case VALUE_TYPE_ASTR:           // AStr Object
                pStr = this->value.pObject;
                obj_Retain(pStr);
                break;

            case VALUE_TYPE_DOUBLE:         // 64-bit Float
                pStr = AStr_NewFromPrint("%f", this->value.flt);
                break;

            case VALUE_TYPE_INT8:           // int8_t
                pStr = AStr_NewFromPrint("%d", this->value.i8);
                break;

            case VALUE_TYPE_INT16:          // int16_t
                pStr = AStr_NewFromPrint("%d", this->value.i16);
                break;

            case VALUE_TYPE_INT32:          // int32_t
                pStr = AStr_NewFromPrint("%d", this->value.i32);
                break;

            case VALUE_TYPE_INT64:          // int64_t
                pStr = AStr_NewFromPrint("%d", this->value.i64);
                break;

            case VALUE_TYPE_UINT8:          // uint8_t
                pStr = AStr_NewFromPrint("%u", this->value.u8);
                break;

            case VALUE_TYPE_UINT16:         // uint16_t
                pStr = AStr_NewFromPrint("%u", this->value.u16);
                break;

            case VALUE_TYPE_UINT32:         // uint32_t
                pStr = AStr_NewFromPrint("%u", this->value.u32);
                break;

            case VALUE_TYPE_UINT64:         // uint64_t
                pStr = AStr_NewFromPrint("%u", this->value.u64);
                break;

            case VALUE_TYPE_MONEY64:        // Money64 Object
                pStr = Money64_ToAStr((OBJ_ID)this->value.pObject);
                break;

            case VALUE_TYPE_OBJECT:         // Any object that supports "ToStr" method
                if (this->value.pObject) {
                    ASTR_DATA * (*pToStr)(OBJ_ID);
                    pToStr =    ((OBJ_DATA *)(this->value.pObject))->pVtbl->pQueryInfo(
                                             this->value.pObject,
                                             OBJ_QUERYINFO_TYPE_METHOD,
                                             "ToStr"
                                );
                    if (pToStr) {
                        pStr = pToStr(this->value.pObject);
                    }
                }
                break;

            case VALUE_TYPE_DATA:           // Any data (pointer and length) (pointer and length
                //                          // must be valid for life of object)
                break;

            case VALUE_TYPE_DATA_FREE:      // Any data (pointer and length) which will be freed
                //                          // using mem_Free() when no longer needed (pointer
                //                          // and length must be valid for life of object)
                break;

            default:
                break;
        }

        return pStr;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            Value_Validate (
        VALUE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_VALUE))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(VALUE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


