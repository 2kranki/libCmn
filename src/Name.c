// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Name.c
 *	Generated 01/11/2020 10:01:40
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
#include        <Name_internal.h>
#include        <dec.h>
#include        <hex.h>
#include        <utf8.h>
#include        <stdio.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void            Name_DeleteValue (
        NAME_DATA     *this
    )
    {
        //NAME_DATA  *this = pData;

        switch (this->type) {
            case NAME_TYPE_INTEGER:          // int64_t
                // This fits within this object. So,
                // nothing to release.
                break;
            case NAME_TYPE_UTF8:             // UTF-8 NUL-terminated String
                mem_Free((void *)this->pChrs);
                this->pChrs = NULL;
                break;
            case NAME_TYPE_UTF8_CON:         // UTF-8 NUL-terminated String Constant
                // We did not own this.
                this->pChrs = NULL;
                break;
            case NAME_TYPE_ASTR:             // AStr Object
                obj_Release(this->pObj);
                this->pObj = OBJ_NIL;
                break;
            default:
                break;
        }
        this->type = NAME_TYPE_UNKNOWN;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NAME_DATA *     Name_Alloc (
        void
    )
    {
        NAME_DATA       *this;
        uint32_t        cbSize = sizeof(NAME_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NAME_DATA *     Name_New (
        void
    )
    {
        NAME_DATA       *this;
        
        this = Name_Alloc( );
        if (this) {
            this = Name_Init(this);
        } 
        return this;
    }



    NAME_DATA *     Name_NewInt(
        int64_t         value
    )
    {
        NAME_DATA       *this;

        this = Name_New( );
        if (this) {
            this->type = NAME_TYPE_INTEGER;
            this->integer = value;
        }
        return this;
    }


    NAME_DATA *     Name_NewAStr(
        ASTR_DATA       *pValue
    )
    {
        NAME_DATA       *this;

        this = Name_New();
        if (this) {
            Name_setStr(this, pValue);
        }
        return this;
    }


    NAME_DATA *     Name_NewUTF8(
        const
        char            *pValue
    )
    {
        NAME_DATA       *this;

        this = Name_New();
        if (this) {
            Name_setUTF8(this, pValue);
        }
        return this;
    }


    NAME_DATA *     Name_NewUTF8Con(
        const
        char            *pValue
    )
    {
        NAME_DATA       *this;

        this = Name_New( );
        if (this) {
            Name_setUTF8Con(this, pValue);
        }
        return this;
    }




    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          C h r s
    //---------------------------------------------------------------

    char *          Name_getChrs(
        NAME_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Name_Validate( this ) ) {
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
    //                          H a s h
    //---------------------------------------------------------------

    uint32_t        Name_getHash(
        NAME_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Name_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Name_Hash(this);
    }



    //---------------------------------------------------------------
    //                          I n t
    //---------------------------------------------------------------

    int64_t         Name_getInt(
        NAME_DATA       *this
    )
    {
        int64_t         value = 0;
        ERESULT         eRc;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Name_Validate( this ) ) {
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


    bool            Name_setInt (
        NAME_DATA       *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Name_DeleteValue(this);
        this->integer = value;
        this->type = NAME_TYPE_INTEGER;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Name_getSize (
        NAME_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     Name_getStr (
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
        if (!Name_Validate(this)) {
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
    
    
    bool            Name_setStr (
        NAME_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        if (pValue) {
            if (obj_IsKindOf(pValue, OBJ_IDENT_ASTR))
                ;
            else {
                DEBUG_BREAK();
                return false;
            }
        }
#endif

        Name_DeleteValue(this);
        if (pValue) {
            this->pObj = AStr_Copy(pValue);
            this->type = NAME_TYPE_ASTR;
        }

        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Name_getSuperVtbl (
        NAME_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                              U t f 8
    //---------------------------------------------------------------

    char *          Name_getUTF8(
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
        if( !Name_Validate(this) ) {
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


    bool            Name_setUTF8 (
        NAME_DATA       *this,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Name_DeleteValue(this);
        if (pValue) {
            this->type = NAME_TYPE_UTF8;
            this->pChrs = str_DupA(pValue);
        }

        return true;
    }


    bool            Name_setUTF8Con (
        NAME_DATA       *this,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Name_DeleteValue(this);
        if (pValue) {
            this->type = NAME_TYPE_UTF8_CON;
            this->pChrs = pValue;
        }

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
        ERESULT eRc = Name_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NAME object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Name_Assign (
        NAME_DATA		*this,
        NAME_DATA       *pOther
    )
    {
        //ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Name_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        Name_DeleteValue(pOther);

        // Create a copy of objects and areas in this object placing
        // them in other.
        switch (this->type) {

            case NAME_TYPE_INTEGER:
                pOther->integer = this->integer;
                pOther->type = NAME_TYPE_INTEGER;
                break;

            case NAME_TYPE_ASTR:
                pOther->pObj = AStr_Copy(this->pObj);
                pOther->type = NAME_TYPE_ASTR;
                break;

            case NAME_TYPE_UTF8:
                pOther->pChrs = str_DupA(this->pChrs);
                pOther->type = NAME_TYPE_UTF8;
                break;

            case NAME_TYPE_UTF8_CON:
                pOther->pChrs = this->pChrs;
                pOther->type = NAME_TYPE_UTF8_CON;
                break;

            default:
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;

        }


        // Copy other data from this object to other.

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Name_Compare (
        NAME_DATA     *this,
        NAME_DATA     *pOther
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
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Name_Validate(pOther)) {
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
                    pStr1 = Name_getUTF8(this);
                    pStr2 = Name_getUTF8(pOther);
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
                pStr1 = Name_getUTF8(this);
                pStr2 = Name_getUTF8(pOther);
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
                pStr2 = Name_getUTF8(pOther);
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
    
   
    ERESULT         Name_CompareA(
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
        if( !Name_Validate(this) ) {
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
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Name      *pCopy = Name_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NAME object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NAME_DATA *     Name_Copy (
        NAME_DATA       *this
    )
    {
        NAME_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Name_New( );
        if (pOther) {
            eRc = Name_Assign(this, pOther);
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

    void            Name_Dealloc (
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
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NAME_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Name_DeleteValue(this);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------

    NAME_DATA *     Name_DeepCopy(
        NAME_DATA       *this
    )
    {
        NAME_DATA       *pOther;
        //ERESULT         eRc;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        pOther = Name_New();
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }

        switch (this->type) {

            case NAME_TYPE_INTEGER:
                pOther->integer = this->integer;
                pOther->type = NAME_TYPE_INTEGER;
                break;

            case NAME_TYPE_ASTR:
                pOther->pObj = AStr_Copy(this->pObj);
                pOther->type = NAME_TYPE_ASTR;
                break;

            case NAME_TYPE_UTF8:
                pOther->pChrs = str_DupA(this->pChrs);
                if (NULL == pOther->pChrs) {
                    DEBUG_BREAK();
                    obj_Release(pOther);
                    return OBJ_NIL;
                }
                pOther->type = NAME_TYPE_UTF8;
                break;

            case NAME_TYPE_UTF8_CON:
                pOther->pChrs = this->pChrs;
                pOther->type = NAME_TYPE_UTF8_CON;
                break;

            default:
                DEBUG_BREAK();
                obj_Release(pOther);
                return OBJ_NIL;

        }

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
    ERESULT         Name_Disable (
        NAME_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Name_Validate(this)) {
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
    ERESULT         Name_Enable (
        NAME_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Name_Validate(this)) {
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
    //                          H a s h
    //---------------------------------------------------------------

    uint32_t        Name_Hash(
        NAME_DATA       *this
    )
    {
        char            *pStr = NULL;

#ifdef NDEBUG
#else
        if( !Name_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        if (!obj_IsFlag(this, NAME_FLAG_HASH)) {
            pStr = Name_getUTF8(this);
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

    NAME_DATA *   Name_Init (
        NAME_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NAME_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NAME);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Name_Vtbl);
        
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
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Name::sizeof(NAME_DATA) = %lu\n", sizeof(NAME_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NAME_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Name_IsEnabled (
        NAME_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
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
        void        *pMethod = Name_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Name", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Name_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NAME_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NAME_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Name_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Name_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Name_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Name_ToDebugString;
                        }
#ifdef  NAME_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Name_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Name_ToDebugString)
                    return "ToDebugString";
#ifdef  NAME_JSON_SUPPORT
                if (pData == Name_ToJson)
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
        ASTR_DATA      *pDesc = Name_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Name_ToDebugString (
        NAME_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Name_Validate(this)) {
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
                    Name_getSize(this),
                    obj_getRetainCount(this)
            );

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
    
    
    ASTR_DATA *     Name_ToString(
        NAME_DATA       *this
    )
    {
        ASTR_DATA       *pValue = OBJ_NIL;
        const
        char            *pStr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Name_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

        pStr = Name_ToUTF8(this);
        pValue = AStr_NewA(pStr);
        mem_Free((void *)pStr);
        pStr = NULL;
        return pValue;
    }


    char *          Name_ToUTF8(
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
        if( !Name_Validate( this ) ) {
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
    bool            Name_Validate (
        NAME_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NAME))
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


        if (!(obj_getSize(this) >= sizeof(NAME_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


