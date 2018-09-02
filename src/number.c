// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   number.c
 *	Generated 10/22/2015 16:41:21
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
#include <number_internal.h>
#include <dec.h>
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NUMBER_DATA *     number_Alloc(
    )
    {
        NUMBER_DATA     *this;
        uint32_t        cbSize = sizeof(NUMBER_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NUMBER_DATA *   number_New(
    )
    {
        NUMBER_DATA     *this;
        
        this = number_Alloc( );
        if (this) {
            this = number_Init( this );
        } 
        return this;
    }


    NUMBER_DATA *   number_NewA(
        const
        char            *pStr
    )
    {
        NUMBER_DATA     *this;
        int64_t         i64;
        
        this = number_Alloc( );
        if (this) {
            this = number_Init(this);
            if (this) {
                i64 = dec_getInt64A(pStr);
                this->type = NUMBER_TYPE_INT64;
                this->i64 = i64;
            }
        }
        return this;
    }
    
    
    NUMBER_DATA *   number_NewInt16(
        int16_t         value
    )
    {
        NUMBER_DATA     *this;
        
        this = number_Alloc( );
        if (this) {
            this = number_InitI16(this, value);
        }
        return this;
    }
    
    
    NUMBER_DATA *   number_NewInt32(
        int32_t         value
    )
    {
        NUMBER_DATA     *this;
        
        this = number_Alloc( );
        if (this) {
            this = number_InitI32(this, value);
        }
        return this;
    }
    
    
    NUMBER_DATA *   number_NewInt64(
        int64_t         value
    )
    {
        NUMBER_DATA       *this;
        
        this = number_Alloc( );
        if (this) {
            this = number_InitI64(this, value);
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        number_getType(
        NUMBER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        return this->type;
    }

    bool            number_setType(
        NUMBER_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        this->type = value;
        
        return true;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         number_Assign(
        NUMBER_DATA     *this,
        NUMBER_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !number_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pOther->type = this->type;
        switch (this->type) {
            case NUMBER_TYPE_FLOAT:
                pOther->flt = this->flt;
                break;
                
            case NUMBER_TYPE_INT16:
                pOther->i16 = this->i16;
                break;
                
           case NUMBER_TYPE_INT32:
                pOther->i32 = this->i32;
                break;
                
            case NUMBER_TYPE_INT64:
                pOther->i64 = this->i64;
                break;
                
            case NUMBER_TYPE_UINT16:
                pOther->u16 = this->u16;
                break;
                
            case NUMBER_TYPE_UINT32:
                pOther->u32 = this->u32;
                break;
                
            case NUMBER_TYPE_UINT64:
                pOther->u64 = this->u64;
                break;
                
            default:
                pOther->i64 = this->i64;
                break;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         number_CompareA(
        NUMBER_DATA     *this,
        const
        char            *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int64_t         integer;
        
#ifdef NDEBUG
#else
        if( !number_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        integer = dec_getInt64A(pOther);
        switch (this->type) {
            case NUMBER_TYPE_INT16:          // int16_t
                i = this->i16 - (int16_t)integer;
                break;
                
            case NUMBER_TYPE_INT32:          // int32_t
                i = this->i32 - (int32_t)integer;
                break;
                
            case NUMBER_TYPE_INT64:          // int64_t
                i = (int)(this->i64 - integer);
                break;
                
                //case NUMBER_TYPE_INT128:         // int128_t
            case NUMBER_TYPE_UINT16:         // uint16_t
                i = this->u16 - (uint16_t)integer;
                break;
                
            case NUMBER_TYPE_UINT32:         // uint32_t
                i = this->u32 - (uint32_t)integer;
                break;
                
            case NUMBER_TYPE_UINT64:         // uint64_t
                i = (int)(this->u64 - integer);
                break;
                
            default:
                break;
        }
        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NUMBER_DATA *   number_Copy(
        NUMBER_DATA     *this
    )
    {
        NUMBER_DATA     *pOther;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = number_New();
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        eRc = number_Assign(this, pOther);
        if (ERESULT_HAS_FAILED(eRc)) {
            obj_Release(pOther);
            return OBJ_NIL;
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            number_Dealloc(
        OBJ_ID          objId
    )
    {
        NUMBER_DATA     *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            number_Disable(
        NUMBER_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !number_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    double          number_Float(
        NUMBER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (this->type == NUMBER_TYPE_FLOAT) {
            return this->flt;
        }
        
        return 0;
    }
    
    
    
    int16_t         number_I16(
        NUMBER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (int16_t)this->i16;
                break;
                
            case NUMBER_TYPE_INT32:
                return (int16_t)this->i32;
                break;
                
            case NUMBER_TYPE_INT64:
                return (int16_t)this->i64;
                break;
                
            case NUMBER_TYPE_UINT16:
                return (int16_t)this->u16;
                break;
                
            case NUMBER_TYPE_UINT32:
                return (int16_t)this->u32;
                break;
                
            case NUMBER_TYPE_UINT64:
                return (int16_t)this->u64;
                break;
                
        }
        
        return 0;
    }
    
    
    
    int32_t         number_I32(
        NUMBER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (int32_t)this->i16;
                break;
                
            case NUMBER_TYPE_INT32:
                return (int32_t)this->i32;
                break;
                
            case NUMBER_TYPE_INT64:
                return (int32_t)this->i64;
                break;
                
            case NUMBER_TYPE_UINT16:
                return (int32_t)this->u16;
                break;
                
            case NUMBER_TYPE_UINT32:
                return (int32_t)this->u32;
                break;
                
            case NUMBER_TYPE_UINT64:
                return (int32_t)this->u64;
                break;
                
        }
        
        return 0;
    }
    
    
    
    int64_t         number_I64(
        NUMBER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (int64_t)this->i16;
                break;
                
            case NUMBER_TYPE_INT32:
                return (int64_t)this->i32;
                break;
                
            case NUMBER_TYPE_INT64:
                return (int64_t)this->i64;
                break;
                
            case NUMBER_TYPE_UINT16:
                return (int64_t)this->u16;
                break;
                
            case NUMBER_TYPE_UINT32:
                return (int64_t)this->u32;
                break;
                
            case NUMBER_TYPE_UINT64:
                return (int64_t)this->u64;
                break;
                
        }
        
        return 0;
    }
    
    
    
    uint16_t        number_U16(
        NUMBER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (uint16_t)this->i16;
                break;
                
            case NUMBER_TYPE_INT32:
                return (uint16_t)this->i32;
                break;
                
            case NUMBER_TYPE_INT64:
                return (uint16_t)this->i64;
                break;
                
            case NUMBER_TYPE_UINT16:
                return (uint16_t)this->u16;
                break;
                
            case NUMBER_TYPE_UINT32:
                return (uint16_t)this->u32;
                break;
                
            case NUMBER_TYPE_UINT64:
                return (uint16_t)this->u64;
                break;
                
        }
        
        return 0;
    }
    
    
    
    uint32_t        number_U32(
        NUMBER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (uint32_t)this->i16;
                break;
                
            case NUMBER_TYPE_INT32:
                return (uint32_t)this->i32;
                break;
                
            case NUMBER_TYPE_INT64:
                return (uint32_t)this->i64;
                break;
                
            case NUMBER_TYPE_UINT16:
                return (uint32_t)this->u16;
                break;
                
            case NUMBER_TYPE_UINT32:
                return (uint32_t)this->u32;
                break;
                
            case NUMBER_TYPE_UINT64:
                return (uint32_t)this->u64;
                break;
                
        }
        
        return 0;
    }
    
    
    
    uint64_t        number_U64(
        NUMBER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->type) {
            case NUMBER_TYPE_INT16:
                return (uint64_t)this->i16;
                break;
                
            case NUMBER_TYPE_INT32:
                return (uint64_t)this->i32;
                break;
                
            case NUMBER_TYPE_INT64:
                return (uint64_t)this->i64;
                break;
                
            case NUMBER_TYPE_UINT16:
                return (uint64_t)this->u16;
                break;
                
            case NUMBER_TYPE_UINT32:
                return (uint64_t)this->u32;
                break;
                
            case NUMBER_TYPE_UINT64:
                return (uint64_t)this->u64;
                break;
                
        }
        
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NUMBER_DATA *   number_Init(
        NUMBER_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (NUMBER_DATA *)obj_Init( this, cbSize, OBJ_IDENT_NUMBER );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_NUMBER);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&number_Vtbl);
        
        //this->stackSize = obj_getMisc1(cbp);
        //cbp->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     
    NUMBER_DATA *   number_InitFloat(
        NUMBER_DATA     *this,
        double          flt
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = number_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NUMBER_TYPE_FLOAT;
        this->flt = flt;
        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return this;
    }
    
    
    NUMBER_DATA *   number_InitI16(
        NUMBER_DATA     *this,
        int16_t         i16
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = number_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NUMBER_TYPE_INT16;
        this->i16 = i16;
        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return this;
    }
    
    
    NUMBER_DATA *   number_InitI32(
        NUMBER_DATA     *this,
        int32_t         i32
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = number_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NUMBER_TYPE_INT32;
        this->i32 = i32;
        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return this;
    }
    
    
    NUMBER_DATA *   number_InitI64(
        NUMBER_DATA     *this,
        int64_t         i64
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = number_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        this->type = NUMBER_TYPE_INT64;
        this->i64 = i64;
        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return this;
    }
    
    
    NUMBER_DATA *   number_InitU16(
        NUMBER_DATA     *this,
        uint16_t        value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = number_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NUMBER_TYPE_UINT16;
        this->u16 = value;
        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return this;
    }
    
    
    NUMBER_DATA *   number_InitU32(
        NUMBER_DATA     *this,
        uint32_t        value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = number_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NUMBER_TYPE_UINT32;
        this->u32 = value;
        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return this;
    }
    
    
    NUMBER_DATA *   number_InitU64(
        NUMBER_DATA     *this,
        uint64_t        value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = number_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NUMBER_TYPE_UINT64;
        this->u64 = value;
        
#ifdef NDEBUG
#else
        if( !number_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          number_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NUMBER_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !number_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return number_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return number_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     number_ToDebugString(
        NUMBER_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(number) ",
                     this
            );
        AStr_AppendA(pStr, str);

        switch (this->type) {
                
            case NUMBER_TYPE_FLOAT:
                j = snprintf(
                             str,
                             sizeof(str),
                             "dbl=%e",
                             this->flt
                    );
                break;
                
            case NUMBER_TYPE_INT16:
                j = snprintf(
                             str,
                             sizeof(str),
                             "i16=%d",
                             this->i16
                             );
                break;
                
            case NUMBER_TYPE_INT32:
                j = snprintf(
                             str,
                             sizeof(str),
                             "i32=%d",
                             this->i32
                             );
                break;
                
            case NUMBER_TYPE_INT64:
                j = snprintf(
                             str,
                             sizeof(str),
                             "i64=%lld",
                             this->i64
                             );
                break;
                
            case NUMBER_TYPE_UINT16:
                j = snprintf(
                             str,
                             sizeof(str),
                             "u16=%d",
                             this->u16
                             );
                break;
                
            case NUMBER_TYPE_UINT32:
                j = snprintf(
                             str,
                             sizeof(str),
                             "u32=%d",
                             this->u32
                             );
                break;
                
            case NUMBER_TYPE_UINT64:
                j = snprintf(
                             str,
                             sizeof(str),
                             "u64=%lld",
                             this->u64
                             );
                break;
                
            default:
                strcpy(str, "unknown number type!");
                break;
        }
        AStr_AppendA(pStr, str);
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            number_Validate(
        NUMBER_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NUMBER) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NUMBER_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


