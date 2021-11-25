// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   PropItem.c
 *  Generated 11/22/2021 12:43:21
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
#include        <PropItem_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.

    /* The following tables were generated from:
     * "propitem_types.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the PropItem_type_entries
    // table. 0 means no enum entry.
    const
    uint16_t    PropItem_type_index[13] = {
        1, 4, 2, 3, 8, 5, 6, 7,
        9, 13, 10, 11, 12,
    };


    const
    uint32_t    cPropItem_type_index = 13;




    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } PropItem_type_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    const
    PropItem_type_entry    PropItem_type_entries[] = {
        {"PROPITEM_TYPE_ASTR", "", "ASTR", 0},
        {"PROPITEM_TYPE_FLAG16", "", "FLAG16", 2},
        {"PROPITEM_TYPE_FLAG32", "", "FLAG32", 3},
        {"PROPITEM_TYPE_FLAG8", "", "FLAG8", 1},
        {"PROPITEM_TYPE_INT16", "", "INT16", 5},
        {"PROPITEM_TYPE_INT32", "", "INT32", 6},
        {"PROPITEM_TYPE_INT64", "", "INT64", 7},
        {"PROPITEM_TYPE_INT8", "", "INT8", 4},
        {"PROPITEM_TYPE_OBJECT", "", "OBJECT", 8},
        {"PROPITEM_TYPE_UINT16", "", "UINT16", 10},
        {"PROPITEM_TYPE_UINT32", "", "UINT32", 11},
        {"PROPITEM_TYPE_UINT64", "", "UINT64", 12},
        {"PROPITEM_TYPE_UINT8", "", "UINT8", 9},
    };
    uint32_t    cPropItem_type_entries = 13;



    /* The following tables were generated from:
     * "propitem_vis.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the PropItem_vis_entries
    // table. 0 means no enum entry.
    const
    uint16_t    PropItem_vis_index[3] = {
        1, 2, 3,
    };


    const
    uint32_t    cPropItem_vis_index = 3;



    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } PropItem_vis_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    const
    PropItem_vis_entry    PropItem_vis_entries[] = {
        {"PROPITEM_VIS_NONE", "", "NONE", 0},
        {"PROPITEM_VIS_PUBLIC", "", "PUBLIC", 1},
        {"PROPITEM_VIS_READ_ONLY", "", "READ_ONLY", 2},
    };
    uint32_t    cPropItem_vis_entries = 3;




 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* The following routine was generated from:
     * "propitem_types.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum value, return its character format.
    const
    char *            PropItem_typeToEnum (
        uint32_t        value
    )
    {
        if (value >= cPropItem_type_index) {
            return "<<<Unknown Enum Value>>>";
        }
        if (PropItem_type_index[value]) {
            return PropItem_type_entries[PropItem_type_index[value] - 1].pEnum;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }

    // Given an enum value, return its name.
    const
    char *            PropItem_typeToName (
        uint32_t        value
    )
    {
        if (value >= cPropItem_type_index) {
            return NULL;
        }
        if (PropItem_type_index[value]) {
            return PropItem_type_entries[PropItem_type_index[value] - 1].pName;
        } else {
            return NULL;
        }
    }



    /* The following routine was generated from:
     * "propitem_types.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        PropItem_EnumTotype (
        char            *pDesc
    )
    {
        int            iRc;
        uint32_t        iMax = cPropItem_type_entries;
        uint32_t        i    = 0;
        uint32_t        high = 0;
        uint32_t        low  = 0;
        uint32_t        mid  = 0;

        if (iMax > 10) {
            for (i=0; i<iMax; i++) {
                iRc = strcmp(pDesc, PropItem_type_entries[i].pEnum);
                if (0 == iRc) {
                    return PropItem_type_entries[i].value + 1;
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
                iRc = strcmp(pDesc, PropItem_type_entries[i].pEnum);
                if (iRc < 0) {
                    high = mid;
                } else if (iRc == 0) {
                    return PropItem_type_entries[i].value + 1;
                } else {
                    low = mid + 1;
                }
            }
            if( high == low ) {
                i = low;
                iRc = strcmp(pDesc, PropItem_type_entries[i].pEnum);
                if (0 == iRc) {
                    return PropItem_type_entries[i].value + 1;
                }
            }
        }
        return 0;
    }



    /* The following routine was generated from:
     * "propitem_vis.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum value, return its character format.
    const
    char *            PropItem_visToEnum (
        uint32_t        value
    )
    {
        if (value >= cPropItem_vis_index) {
            return "<<<Unknown Enum Value>>>";
        }
        if (PropItem_vis_index[value]) {
            return PropItem_vis_entries[PropItem_vis_index[value] - 1].pEnum;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }

    // Given an enum value, return its name.
    const
    char *            PropItem_visToName (
        uint32_t        value
    )
    {
        if (value >= cPropItem_vis_index) {
            return NULL;
        }
        if (PropItem_vis_index[value]) {
            return PropItem_vis_entries[PropItem_vis_index[value] - 1].pName;
        } else {
            return NULL;
        }
    }



    /* The following routine was generated from:
     * "propitem_vis.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        PropItem_EnumTovis (
        char            *pDesc
    )
    {
        int            iRc;
        uint32_t        iMax = cPropItem_vis_entries;
        uint32_t        i    = 0;
        uint32_t        high = 0;
        uint32_t        low  = 0;
        uint32_t        mid  = 0;

        if (iMax > 10) {
            for (i=0; i<iMax; i++) {
                iRc = strcmp(pDesc, PropItem_vis_entries[i].pEnum);
                if (0 == iRc) {
                    return PropItem_vis_entries[i].value + 1;
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
                iRc = strcmp(pDesc, PropItem_vis_entries[i].pEnum);
                if (iRc < 0) {
                    high = mid;
                } else if (iRc == 0) {
                    return PropItem_vis_entries[i].value + 1;
                } else {
                    low = mid + 1;
                }
            }
            if( high == low ) {
                i = low;
                iRc = strcmp(pDesc, PropItem_vis_entries[i].pEnum);
                if (0 == iRc) {
                    return PropItem_vis_entries[i].value + 1;
                }
            }
        }
        return 0;
    }





    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            PropItem_task_body (
        void            *pData
    )
    {
        //PROPITEM_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PROPITEM_DATA *     PropItem_Alloc (
        void
    )
    {
        PROPITEM_DATA       *this;
        uint32_t        cbSize = sizeof(PROPITEM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PROPITEM_DATA *     PropItem_New (
        void
    )
    {
        PROPITEM_DATA       *this;
        
        this = PropItem_Alloc( );
        if (this) {
            this = PropItem_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          E x t e r n a l
    //---------------------------------------------------------------

    ASTR_DATA *     PropItem_getExternal (
        PROPITEM_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pExternal;
    }


    bool            PropItem_setExternal (
        PROPITEM_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pExternal) {
            obj_Release(this->pExternal);
        }
        this->pExternal = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTR_DATA * PropItem_getInit (
        PROPITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pInit;
    }


    bool        PropItem_setInit (
        PROPITEM_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pInit) {
            obj_Release(this->pInit);
        }
        this->pInit = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                       I n t e r n a l
    //---------------------------------------------------------------

    ASTR_DATA * PropItem_getInternal (
        PROPITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pInternal;
    }


    bool        PropItem_setInternal (
        PROPITEM_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pInternal) {
            obj_Release(this->pInternal);
        }
        this->pInternal = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         L o n g
    //---------------------------------------------------------------

    ASTR_DATA *     PropItem_getLong (
        PROPITEM_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLong;
    }


    bool            PropItem_setLong (
        PROPITEM_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pLong) {
            obj_Release(this->pLong);
        }
        this->pLong = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   PROPITEM_MSGS
    bool            PropItem_setMsgs (
        PROPITEM_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pMsgInfo = pMsgInfo;
        this->pMsgWarn = pMsgWarn;
        this->pMsgObj = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                            N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     PropItem_getName (
        PROPITEM_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool        PropItem_setName (
        PROPITEM_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        PropItem_getPriority (
        PROPITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            PropItem_setPriority (
        PROPITEM_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                            S h o r t
    //---------------------------------------------------------------

    ASTR_DATA *     PropItem_getShort (
        PROPITEM_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pShort;
    }


    bool            PropItem_setShort (
        PROPITEM_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pShort) {
            obj_Release(this->pShort);
        }
        this->pShort = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        PropItem_getSize (
        PROPITEM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  PropItem_getSuperVtbl (
        PROPITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  
    PROPITEM_DATA *  PropItem_getSuper (
        PROPITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (PROPITEM_DATA *)this;
    }

    
    //---------------------------------------------------------------
    //                 T y p e  D e f i n i t i o n
    //---------------------------------------------------------------

    ASTR_DATA *     PropItem_getTypeDef (
        PROPITEM_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pTypeDef;
    }


    bool            PropItem_setTypeDef (
        PROPITEM_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pTypeDef) {
            obj_Release(this->pTypeDef);
        }
        this->pTypeDef = pValue;

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
        ERESULT eRc = PropItem_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another PROPITEM object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         PropItem_Assign (
        PROPITEM_DATA   *this,
        PROPITEM_DATA   *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!PropItem_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
        PropItem_setExternal(pOther, OBJ_NIL);
        PropItem_setInit(pOther, OBJ_NIL);
        PropItem_setInternal(pOther, OBJ_NIL);
        PropItem_setLong(pOther, OBJ_NIL);
        PropItem_setName(pOther, OBJ_NIL);
        PropItem_setShort(pOther, OBJ_NIL);
        PropItem_setTypeDef(pOther, OBJ_NIL);

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pExternal) {
            if (obj_getVtbl(this->pExternal)->pCopy) {
                pOther->pExternal = obj_getVtbl(this->pExternal)->pCopy(this->pExternal);
            }
            else {
                obj_Retain(this->pExternal);
                pOther->pExternal = this->pExternal;
            }
        }
        if (this->pInit) {
            if (obj_getVtbl(this->pInit)->pCopy) {
                pOther->pInit = obj_getVtbl(this->pInit)->pCopy(this->pInit);
            }
            else {
                obj_Retain(this->pInit);
                pOther->pInit = this->pInit;
            }
        }
        if (this->pInternal) {
            if (obj_getVtbl(this->pInternal)->pCopy) {
                pOther->pInternal = obj_getVtbl(this->pInternal)->pCopy(this->pInternal);
            }
            else {
                obj_Retain(this->pInternal);
                pOther->pInternal = this->pInternal;
            }
        }
        if (this->pLong) {
            if (obj_getVtbl(this->pLong)->pCopy) {
                pOther->pLong = obj_getVtbl(this->pLong)->pCopy(this->pLong);
            }
            else {
                obj_Retain(this->pLong);
                pOther->pLong = this->pLong;
            }
        }
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pCopy) {
                pOther->pName = obj_getVtbl(this->pName)->pCopy(this->pName);
            }
            else {
                obj_Retain(this->pName);
                pOther->pName = this->pName;
            }
        }
        if (this->pShort) {
            if (obj_getVtbl(this->pShort)->pCopy) {
                pOther->pShort = obj_getVtbl(this->pShort)->pCopy(this->pShort);
            }
            else {
                obj_Retain(this->pShort);
                pOther->pShort = this->pShort;
            }
        }
        if (this->pTypeDef) {
            if (obj_getVtbl(this->pTypeDef)->pCopy) {
                pOther->pTypeDef = obj_getVtbl(this->pTypeDef)->pCopy(this->pTypeDef);
            }
            else {
                obj_Retain(this->pTypeDef);
                pOther->pTypeDef = this->pTypeDef;
            }
        }

        // Copy other data from this object to other.
        pOther->fObj = this->fObj;

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
    int             PropItem_Compare (
        PROPITEM_DATA     *this,
        PROPITEM_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  PROPITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = PropItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!PropItem_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc = AStr_Compare(this->pName, pOther->pName);

        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        PropItem      *pCopy = PropItem_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PROPITEM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PROPITEM_DATA *     PropItem_Copy (
        PROPITEM_DATA       *this
    )
    {
        PROPITEM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef PROPITEM_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = PropItem_New( );
        if (pOther) {
            eRc = PropItem_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            PropItem_Dealloc (
        OBJ_ID          objId
    )
    {
        PROPITEM_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((PROPITEM_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        PropItem_setExternal(this, OBJ_NIL);
        PropItem_setInit(this, OBJ_NIL);
        PropItem_setInternal(this, OBJ_NIL);
        PropItem_setLong(this, OBJ_NIL);
        PropItem_setName(this, OBJ_NIL);
        PropItem_setShort(this, OBJ_NIL);
        PropItem_setTypeDef(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        PropItem      *pDeepCopy = PropItem_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PROPITEM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PROPITEM_DATA *     PropItem_DeepCopy (
        PROPITEM_DATA       *this
    )
    {
        PROPITEM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = PropItem_New( );
        if (pOther) {
            eRc = PropItem_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         PropItem_Disable (
        PROPITEM_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PROPITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = PropItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         PropItem_Enable (
        PROPITEM_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PROPITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = PropItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   PROPITEM_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                    G e n e r a t e
    //---------------------------------------------------------------

    ASTR_DATA *     PropItem_GenCode (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        // Generate Documentation
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "//");
        AStr_AppendCharRepeatA(pStr, 62, '-');
        AStr_AppendA(pStr, "\n");
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        if (this->pShort) {
            AStr_AppendA(pStr, "//");
            spcs = 62 - (AStr_getLength(pWrk) + AStr_getLength(this->pShort) + 3);
            spcs >>= 1;
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendPrint(pStr,
                             "%s - %s\n",
                             AStr_getData(pWrk),
                             AStr_getData(this->pShort)
            );
        } else {
            AStr_AppendA(pStr, "//");
            spcs = 62 - (AStr_getLength(pWrk) + 3);
            spcs >>= 1;
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(pWrk)
            );
        }
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "//");
        AStr_AppendCharRepeatA(pStr, 62, '-');
        AStr_AppendA(pStr, "\n\n");

        // Generate Get Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(0 == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr,
                             "%s *",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - (AStr_getLength(this->pTypeDef) + 2);
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
        }
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_get%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this\n");
        AStr_AppendA(pStr, "    )\n");
        AStr_AppendA(pStr, "    {\n\n");
        AStr_AppendA(pStr, "#ifdef NDEBUG\n#else\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "if (%s_Validate(this)) {\n", pClass);
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        AStr_AppendA(pStr, "DEBUG_BREAK();\n");
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        if (this->fObj)
            AStr_AppendA(pStr, "return OBJ_NIL;\n");
        else
            AStr_AppendA(pStr, "return 0;\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendA(pStr, "}\n");
        AStr_AppendA(pStr, "#end\n\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        if (this->pInternal)
            AStr_AppendPrint(pStr, "return this->%s\n", AStr_getData(this->pInternal));
        else
            AStr_AppendPrint(pStr, "return this->%s\n", AStr_getData(this->pName));
        AStr_AppendA(pStr, "    }\n\n");

        // Generate Set Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "bool");
        spcs = 16 - 4;
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_set%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this,\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        spcs = 16 - AStr_getLength(this->pTypeDef);
        if (spcs < 1)
            spcs = 1;
        if (this->fObj
            && !(0 == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "*pValue,\n");
        } else {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "value\n");
        }
        AStr_AppendA(pStr, "    )\n");
        AStr_AppendA(pStr, "    {\n\n");
        AStr_AppendA(pStr, "#ifdef NDEBUG\n#else\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "if (%s_Validate(this)) {\n", pClass);
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        AStr_AppendA(pStr, "DEBUG_BREAK();\n");
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        AStr_AppendA(pStr, "return false;\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendA(pStr, "}\n");
        AStr_AppendA(pStr, "#end\n\n");
        if (this->fObj) {
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            AStr_AppendA(pStr, "obj_Retain(pValue);\n");
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            if (this->pInternal) {
                AStr_AppendPrint(pStr,
                                 "if (this->%s) {\n",
                                 AStr_getData(this->pInternal)
                );
                AStr_AppendCharRepeatA(pStr, 12, ' ');
                AStr_AppendPrint(pStr,
                                 "obj_Release(this->%s);\n",
                                 AStr_getData(this->pInternal)
                );
            } else {
                AStr_AppendPrint(pStr,
                                 "if (this->%s) {\n",
                                 AStr_getData(this->pName)
                );
                AStr_AppendCharRepeatA(pStr, 12, ' ');
                AStr_AppendPrint(pStr,
                                 "obj_Release(this->%s);\n",
                                 AStr_getData(this->pName)
                );
            }
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            AStr_AppendA(pStr, "}\n");
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            if (this->pInternal) {
                AStr_AppendPrint(pStr,
                                 "this->%s = pValue;\n",
                                 AStr_getData(this->pInternal)
                );
            } else {
                AStr_AppendPrint(pStr,
                                 "this->%s = pValue;\n",
                                 AStr_getData(this->pName)
                );
            }
        } else {
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            if (this->pInternal) {
                AStr_AppendPrint(pStr,
                                 "this->%s = value;\n",
                                 AStr_getData(this->pInternal)
                );
            } else {
                AStr_AppendPrint(pStr,
                                 "this->%s = value;\n",
                                 AStr_getData(this->pName)
                );
            }
        }

        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendA(pStr, "return true;\n");
        AStr_AppendA(pStr, "    }\n\n");

        // Generate WS
        AStr_AppendA(pStr, "\n");

        return pStr;
    }


    ASTR_DATA *     PropItem_GenHdrDefn (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if ((this->vis == PROPITEM_VIS_PUBLIC) || (this->vis == PROPITEM_VIS_READ_ONLY)) {
            pStr = AStr_New();
        }
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        // Generate Documentation
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        if (this->pShort) {
            AStr_AppendPrint(pStr,
                             "/*! @property %s - %s\n",
                             AStr_getData(pWrk),
                             AStr_getData(this->pShort)
            );
        } else {
            AStr_AppendPrint(pStr,
                             "/*! @property %s\n",
                             AStr_getData(pWrk)
            );
        }
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 5, ' ');
        AStr_AppendA(pStr, "*/\n");

        // Generate Get Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(0 == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr,
                             "%s *",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - (AStr_getLength(this->pTypeDef) + 2);
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
        }
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_get%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this\n");
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, ");\n\n");

        // Generate Set Method
        if (this->vis == PROPITEM_VIS_PUBLIC) {
            AStr_AppendCharRepeatA(pStr, 4, ' ');
            AStr_AppendA(pStr, "bool");
            spcs = 16 - 4;
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            if (this->pExternal) {
                pWrk = AStr_ToUpperName(this->pExternal);
            } else {
                pWrk = AStr_ToUpperName(this->pName);
            }
            AStr_AppendPrint(pStr,
                             "%s_set%s (\n",
                             pClass,
                             AStr_getData(pWrk)
            );
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            AStr_AppendPrint(pStr, "%s", pClassUC);
            spcs = 16 - (int32_t)strlen(pClassUC);
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "*this,\n");
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            spcs = 16 - AStr_getLength(this->pTypeDef);
            if (spcs < 1)
                spcs = 1;
            if (this->fObj
                && !(0 == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
                AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
                AStr_AppendCharRepeatA(pStr, spcs, ' ');
                AStr_AppendA(pStr, "*pValue,\n");
            } else {
                AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
                AStr_AppendCharRepeatA(pStr, spcs, ' ');
                AStr_AppendA(pStr, "value\n");
            }
            AStr_AppendCharRepeatA(pStr, 4, ' ');
            AStr_AppendA(pStr, ");\n\n");
        }

        // Generate WS
        AStr_AppendA(pStr, "\n");

        return pStr;
    }


    ASTR_DATA *     PropItem_GenIntDefn (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        // Generate Documentation
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        if (this->pShort) {
            AStr_AppendPrint(pStr,
                             "/*! @property %s - %s\n",
                             AStr_getData(pWrk),
                             AStr_getData(this->pShort)
            );
        } else {
            AStr_AppendPrint(pStr,
                             "/*! @property %s\n",
                             AStr_getData(pWrk)
            );
        }
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 5, ' ');
        AStr_AppendA(pStr, "*/\n");

        // Generate Get Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(0 == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr,
                             "%s *",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - (AStr_getLength(this->pTypeDef) + 2);
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
        }
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_get%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this\n");
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, ");\n\n");

        // Generate Set Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "bool");
        spcs = 16 - 4;
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_set%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this,\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        spcs = 16 - AStr_getLength(this->pTypeDef);
        if (spcs < 1)
            spcs = 1;
        if (this->fObj
            && !(0 == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "*pValue,\n");
        } else {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "value\n");
        }
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, ");\n\n");

        // Generate WS
        AStr_AppendA(pStr, "\n");

        return pStr;
    }


    ASTR_DATA *     PropItem_GenIntVar (
        PROPITEM_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(0 == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            spcs = 16 - AStr_getLength(this->pTypeDef);
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            if (this->pInternal) {
                pWrk = this->pInternal;
            } else {
                pWrk = this->pName;
            }
            AStr_AppendPrint(pStr, "*%s;\n", AStr_getData(pWrk));
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            if (this->pInternal) {
                pWrk = this->pInternal;
            } else {
                pWrk = this->pName;
            }
            AStr_AppendPrint(pStr, "%s;\n", AStr_getData(pWrk));
        }

        return pStr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PROPITEM_DATA *   PropItem_Init (
        PROPITEM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(PROPITEM_DATA);
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

        //this = (OBJ_ID)PropItem_Init((PROPITEM_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of PropItem_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PROPITEM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&PropItem_Vtbl);
#ifdef  PROPITEM_JSON_SUPPORT
        JsonIn_RegisterClass(PropItem_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "PropItem::sizeof(PROPITEM_DATA) = %lu\n", 
                sizeof(PROPITEM_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(PROPITEM_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         PropItem_IsEnabled (
        PROPITEM_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PROPITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = PropItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = PropItem_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "PropItem", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          PropItem_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PROPITEM_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PROPITEM_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)PropItem_Class();
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
                            return PropItem_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return PropItem_Enable;
                        }
                        break;

                    case 'P':
#ifdef  PROPITEM_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return PropItem_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return PropItem_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return PropItem_ToDebugString;
                        }
#ifdef  PROPITEM_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return PropItem_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return PropItem_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == PropItem_ToDebugString)
                    return "ToDebugString";
#ifdef  PROPITEM_JSON_SUPPORT
                if (pData == PropItem_ToJson)
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
        ASTR_DATA      *pDesc = PropItem_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_ToDebugString (
        PROPITEM_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PropItem_Validate(this)) {
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
                    PropItem_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            PropItem_Validate (
        PROPITEM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_PROPITEM))
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


        if (!(obj_getSize(this) >= sizeof(PROPITEM_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


