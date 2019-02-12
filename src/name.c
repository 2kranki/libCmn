// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   name.c
 *	Generated 02/07/2016 15:50:26
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
#include "name_internal.h"
#include "dec.h"
#include "hex.h"
#include "utf8.h"
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

    NAME_DATA *     name_Alloc(
    )
    {
        NAME_DATA       *this;
        uint32_t        cbSize = sizeof(NAME_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NAME_DATA *     name_New(
        void
    )
    {
        NAME_DATA       *this;
        
        this = name_Alloc( );
        if (this) {
            this = name_Init(this);
        }
        return this;
    }
    
    
    NAME_DATA *     name_NewInt(
        int64_t         value
    )
    {
        NAME_DATA       *this;
        
        this = name_Alloc( );
        if (this) {
            this = name_InitInt(this, value);
        }
        return this;
    }
    
    
    NAME_DATA *     name_NewAStr(
        ASTR_DATA       *pValue
    )
    {
        NAME_DATA       *this;
        
        this = name_Alloc( );
        if (this) {
            this = name_InitAStr(this, pValue);
        }
        return this;
    }
    
    
    NAME_DATA *     name_NewUTF8(
        const
        char            *pValue
    )
    {
        NAME_DATA       *this;
        
        this = name_Alloc( );
        if (this) {
            this = name_InitUTF8(this, pValue);
        }
        return this;
    }

    
    NAME_DATA *     name_NewUTF8Con(
        const
        char            *pValue
    )
    {
        NAME_DATA       *this;
        
        this = name_Alloc( );
        if (this) {
            this = name_InitUTF8Con(this, pValue);
        }
        return this;
    }
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    char *          name_getChrs(
        NAME_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

#ifdef XYZZY
        if (this->type == NAME_TYPE_CHAR) {
            return this->chrs;
        }
#endif
        
        return NULL;
    }
    
    
    //---------------------------------------------------------------
    //                          I n t
    //---------------------------------------------------------------
    
    int64_t         name_getInt(
        NAME_DATA       *this
    )
    {
        int64_t         value = 0;
        ERESULT         eRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        switch (this->type) {
                
            case NAME_TYPE_INTEGER:
                value = this->integer;
                eRc = ERESULT_SUCCESS;
                break;
                
            default:
                DEBUG_BREAK();
                eRc = ERESULT_INVALID_DATA;
                break;
        }
        
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        name_getHash(
        NAME_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return name_Hash(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     name_getStrA(
        NAME_DATA       *this
    )
    {
        ASTR_DATA       *pValue = OBJ_NIL;
        char            numValue[22];
        char            *pStr;
        uint32_t        len;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        switch (this->type) {
                
            case NAME_TYPE_INTEGER:
                len = 22;
                pStr = numValue;
                dec_putInt64A(this->integer, &len, &pStr);
                if (numValue[0] == ' ') {
                    pValue = AStr_NewA(&numValue[1]);
                }
                else {
                    pValue = AStr_NewA(numValue);
                }
                break;
                
            case NAME_TYPE_ASTR:
                pValue = AStr_Copy(this->pObj);
                break;
                
            case NAME_TYPE_UTF8:
            case NAME_TYPE_UTF8_CON:
                pValue = AStr_NewA(this->pChrs);
                break;
                
            default:
                DEBUG_BREAK();
                break;
        }
        
        return pValue;
    }

    
    bool            name_setStrA(
        NAME_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        if (pValue) {
            if (obj_IsKindOf(this, OBJ_IDENT_ASTR))
                ;
            else {
                DEBUG_BREAK();
                return false;
            }
        }
#endif
        
        obj_Retain(pValue);
        name_ReleaseDataIfObj(this);
        if (pValue) {
            this->type = NAME_TYPE_ASTR;
            this->pObj = pValue;
        }
        
        return true;
    }
    
    
    //---------------------------------------------------------------
    //                              U t f 8
    //---------------------------------------------------------------
    
    char *          name_getUTF8(
        NAME_DATA       *this
    )
    {
        char            *pValue = NULL;
        char            numValue[22];
        char            *pStr;
        uint32_t        len;
        //HEX_DATA        *pHex = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !name_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (this->type) {

            case NAME_TYPE_INTEGER:
                len = 22;
                pStr = numValue;
                dec_putInt64A(this->integer, &len, &pStr);
                if (numValue[0] == ' ') {
                    pValue = str_DupA(&numValue[1]);
                }
                else {
                    pValue = str_DupA(numValue);
                }
                break;
                
            case NAME_TYPE_ASTR:
                pValue = AStr_CStringA(this->pObj, NULL);
                break;
                
            case NAME_TYPE_UTF8:
            case NAME_TYPE_UTF8_CON:
                pValue = str_DupA(this->pChrs);
                break;
                
            default:
                DEBUG_BREAK();
                break;
        }
        
        return pValue;
    }
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         name_Assign(
        NAME_DATA       *this,
        NAME_DATA       *pOther
    )
    {
        
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !name_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        name_ReleaseDataIfObj(pOther);
        
        pOther->type = this->type;
        switch (this->type) {
                
            case NAME_TYPE_UNKNOWN:
                break;
                
            case NAME_TYPE_INTEGER:
                pOther->integer = this->integer;
                break;
                
            case NAME_TYPE_ASTR:
                {
                    OBJ_IUNKNOWN *pVtbl = obj_getVtbl(this->pObj);
                    if (pVtbl->pCopy) {
                        pOther->pObj = pVtbl->pCopy(this->pObj);
                    }
                    else {
                        obj_Retain(this->pObj);
                        pOther->pObj = this->pObj;
                    }
                }
                break;
                
            case NAME_TYPE_UTF8:
                pOther->pChrs = str_DupA(this->pChrs);
                break;
                
            case NAME_TYPE_UTF8_CON:
                pOther->pChrs = this->pChrs;
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
                
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         name_Compare(
        NAME_DATA       *this,
        NAME_DATA       *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        const
        char            *pStr1;
        const
        char            *pStr2;
        
#ifdef NDEBUG
#else
        if( !name_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !name_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        switch (this->type) {
                
            case NAME_TYPE_INTEGER:
                if (pOther->type == NAME_TYPE_INTEGER) {
                    i = (int)(this->integer - pOther->integer);
                }
                else {
                    pStr1 = name_getUTF8(this);
                    pStr2 = name_getUTF8(pOther);
                    i = utf8_StrCmp(pStr1, pStr2);
                    mem_Free((void *)pStr1);
                    mem_Free((void *)pStr2);
                }
                break;
                
            case NAME_TYPE_ASTR:
                if (pOther->type == NAME_TYPE_ASTR) {
                    eRc = AStr_Compare(this->pObj, pOther->pObj);
                    return eRc;
                }
                pStr1 = name_getUTF8(this);
                pStr2 = name_getUTF8(pOther);
                i = utf8_StrCmp(pStr1, pStr2);
                mem_Free((void *)pStr1);
                mem_Free((void *)pStr2);
                break;
                
            case NAME_TYPE_UTF8:
            case NAME_TYPE_UTF8_CON:
                if (pOther->type == NAME_TYPE_UTF8) {
                    i = utf8_StrCmp(this->pChrs, pOther->pChrs);
                    break;
                }
                else if (pOther->type == NAME_TYPE_UTF8_CON) {
                    i = utf8_StrCmp(this->pChrs, pOther->pChrs);
                    break;
                }
                else if (pOther->type == NAME_TYPE_ASTR) {
                    eRc = AStr_Compare(this->pObj, pOther->pObj);
                    return eRc;
                }
                pStr2 = name_getUTF8(pOther);
                i = utf8_StrCmp(this->pChrs, pStr2);
                mem_Free((void *)pStr2);
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
                
        }
        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
    
    ERESULT         name_CompareA(
        NAME_DATA       *this,
        const
        char            *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int64_t         integer;
        
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        switch (this->type) {
                
            case NAME_TYPE_INTEGER:
                integer = dec_getInt64A(pOther);
                if((this->integer - integer) < 0)
                    i = -1;
                else if((this->integer - integer) > 0)
                    i = 1;
                break;
                
            case NAME_TYPE_ASTR:
                eRc = AStr_CompareA(this->pObj, pOther);
                return eRc;
                break;
                
            case NAME_TYPE_UTF8:
            case NAME_TYPE_UTF8_CON:
                i = strcmp(this->pChrs, pOther);
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
                
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
    
    NAME_DATA *     name_Copy(
        NAME_DATA       *this
    )
    {
        NAME_DATA       *pOther;
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pOther = name_Alloc();
        pOther = name_Init( pOther );
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        eRc = name_Assign(this, pOther);
        if (ERESULT_HAS_FAILED(eRc)) {
            obj_Release(pOther);
            pOther = OBJ_NIL;
            return OBJ_NIL;
        }
        
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            name_Dealloc(
        OBJ_ID          objId
    )
    {
        NAME_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        name_ReleaseDataIfObj(this);

        obj_setVtbl(this, (OBJ_IUNKNOWN *)this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------
    
    NAME_DATA *     name_DeepCopy(
        NAME_DATA       *this
    )
    {
        NAME_DATA       *pOther;
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pOther = name_Alloc();
        pOther = name_Init( pOther );
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        pOther->type = this->type;
        switch (this->type) {
                
            case NAME_TYPE_UNKNOWN:
                break;
                
            case NAME_TYPE_INTEGER:
                pOther->integer = this->integer;
                break;
                
            case NAME_TYPE_ASTR:
                {
                    OBJ_IUNKNOWN *pVtbl = obj_getVtbl(this->pObj);
                    if (pVtbl->pDeepCopy) {
                        pOther->pObj = pVtbl->pDeepCopy(this->pObj);
                    }
                    else if (pVtbl->pCopy) {
                        pOther->pObj = pVtbl->pCopy(this->pObj);
                    }
                   else {
                        obj_Retain(this->pObj);
                        pOther->pObj = this->pObj;
                    }
                }
                break;
                
            case NAME_TYPE_UTF8:
                pOther->pChrs = str_DupA(this->pChrs);
                if (NULL == pOther->pChrs) {
                    DEBUG_BREAK();
                    obj_Release(pOther);
                    return OBJ_NIL;
                }
                break;
                
            case NAME_TYPE_UTF8_CON:
                pOther->pChrs = this->pChrs;
                break;
                
            default:
                DEBUG_BREAK();
                obj_Release(pOther);
                return OBJ_NIL;
                
        }
        
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        name_Hash(
        NAME_DATA       *this
    )
    {
        char            *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (!obj_IsFlag(this, NAME_FLAG_HASH)) {
            pStr = name_getUTF8(this);
            if (pStr) {
                this->hash = str_HashAcmA(pStr, NULL);
                mem_Free(pStr);
                pStr = NULL;
                obj_FlagOn(this, NAME_FLAG_HASH);
            }
        }
        
        return this->hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NAME_DATA *     name_Init(
        NAME_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NAME_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        //cbSize = obj_getSize(this);
        this = (NAME_DATA *)obj_Init( this, cbSize, OBJ_IDENT_NAME );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_NAME);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&name_Vtbl);
        
        obj_FlagSet(this, OBJ_FLAG_RO, true);
        if (this->type) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(sizeof(NAME_DATA));
    #endif

        return this;
    }

     
    NAME_DATA *   name_InitInt(
        NAME_DATA       *this,
        int64_t         value
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = name_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NAME_TYPE_INTEGER;
        this->integer = value;
        
        return this;
    }
    
    
    NAME_DATA *   name_InitAStr(
        NAME_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if( pValue == OBJ_NIL ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        this = name_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NAME_TYPE_ASTR;
        this->pObj = AStr_Copy(pValue);
        
        return this;
    }
    
    
    NAME_DATA *   name_InitUTF8(
        NAME_DATA       *this,
        const
        char            *pValue
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
#else
        if( pValue == OBJ_NIL ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        this = name_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NAME_TYPE_UTF8;
        this->pChrs = str_DupA(pValue);
        
        return this;
    }
    
    
    NAME_DATA *   name_InitUTF8Con(
        NAME_DATA       *this,
        const
        char            *pValue
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
#else
        if( pValue == OBJ_NIL ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        this = name_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->type = NAME_TYPE_UTF8_CON;
        this->pChrs = pValue;
        
        return this;
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
     void        *pMethod = name_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   OBJTEST object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                         for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                         character string which represents the method name without
                         the object name, "name", prefix,
                         for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                         address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                 OBJ_QUERYINFO_TYPE_INFO: info pointer,
                 OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                 OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          name_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NAME_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !name_Validate(this) ) {
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
                            return name_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return name_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //          R e l e a s e  D a t a  I f  O b j e c t
    //---------------------------------------------------------------
    
    void            name_ReleaseDataIfObj(
        NAME_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NAME_DATA);
        
        /* "this" might point to an area which is
         * an initialized token. Therefore, we need
         * to add as many checks as we can to insure
         * that we are releasing an object really
         * assigned to a token.
         */
        if ( (obj_getType(this) == OBJ_IDENT_NAME)
            && (obj_getSize(this) >= cbSize)
            && (this->pObj)
            ) {
            switch (this->type) {

                case NAME_TYPE_INTEGER:
                    // This fits within this object. So,
                    // nothing to release.
                    break;
                    
                case NAME_TYPE_ASTR:
                    obj_Release(this->pObj);
                    this->pObj = OBJ_NIL;
                    break;
                    
                case NAME_TYPE_UTF8:
                    mem_Free((void *)this->pChrs);
                    this->pChrs = NULL;
                    break;
                    
                case NAME_TYPE_UTF8_CON:
                    // We did not own this.
                    this->pChrs = NULL;
                    break;
                    
                default:
                    break;
            }
        }
        
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     name_ToDebugString(
        NAME_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        char            *pName;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        pName = name_getUTF8(this);
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(name) name=%s",
                     this,
                     pName
            );
        mem_Free((void *)pName);
        AStr_AppendA(pStr, str);

        j = snprintf( str, sizeof(str), " %p(name)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    ASTR_DATA *     name_ToString(
        NAME_DATA       *this
    )
    {
        ASTR_DATA       *pValue = OBJ_NIL;
        const
        char            *pStr;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pStr = name_ToUTF8(this);
        pValue = AStr_NewA(pStr);
        mem_Free((void *)pStr);
        pStr = NULL;
        return pValue;
    }
    

    char *          name_ToUTF8(
        NAME_DATA       *this
    )
    {
        char            *pValue = NULL;
        char            numValue[22];
        char            *pStr;
        uint32_t        len;
        //HEX_DATA        *pHex = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !name_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        switch (this->type) {
                
            case NAME_TYPE_INTEGER:
                len = 22;
                pStr = numValue;
                dec_putInt64A(this->integer, &len, &pStr);
                if (numValue[0] == ' ') {
                    pValue = str_DupA(&numValue[1]);
                }
                else {
                    pValue = str_DupA(numValue);
                }
                break;
                
            case NAME_TYPE_ASTR:
                pValue = AStr_CStringA(this->pObj, NULL);
                break;
                
            case NAME_TYPE_UTF8:
            case NAME_TYPE_UTF8_CON:
                pValue = str_DupA(this->pChrs);
                break;
                
            default:
                DEBUG_BREAK();
                break;
        }
        
        return pValue;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            name_Validate(
        NAME_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NAME) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NAME_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


