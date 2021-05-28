// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Dict.c
 *	Generated 11/23/2019 09:50:49
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
#include        <Dict_internal.h>
#include        <ascii.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Dict_task_body (
        void            *pData
    )
    {
        //DICT_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DICT_DATA *     Dict_Alloc (
        void
    )
    {
        DICT_DATA       *this;
        uint32_t        cbSize = sizeof(DICT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    DICT_DATA *     Dict_New (
        void
    )
    {
        DICT_DATA       *this;
        
        this = Dict_Alloc( );
        if (this) {
            this = Dict_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                   N o d e  H a s h
    //---------------------------------------------------------------
    
    NODEHASH_DATA * Dict_getNodeHash (
        DICT_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (NODEHASH_DATA *)this;
    }

    
        
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Dict_getPriority (
        DICT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Dict_setPriority (
        DICT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Dict_getSize (
        DICT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Dict_getStr (
        DICT_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Dict_setStr (
        DICT_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
#endif
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Dict_getSuperVtbl (
        DICT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                  A d d  /  A d d U p d a t e
    //---------------------------------------------------------------
    
    ERESULT         Dict_AddA (
        DICT_DATA       *this,
        const
        char            *pNameA,
        const
        char            *pDataA
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dict_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pDataA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr = AStr_NewA(pDataA);
        if (OBJ_NIL == pStr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        eRc = NodeHash_AddA(Dict_getNodeHash(this), 0, pNameA, pStr);
        
        // Return to caller.
        obj_Release(pStr);
        pStr = OBJ_NIL;
        return eRc;
    }
    
    
    ERESULT         Dict_AddAStr (
        DICT_DATA       *this,
        const
        char            *pNameA,
        ASTR_DATA       *pData
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dict_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_AddA(Dict_getNodeHash(this), 0, pNameA, (void *)pData);

        // Return to caller.
        return eRc;
    }


    ERESULT         Dict_AddUpdate (
        DICT_DATA       *this,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dict_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (NodeHash_FindA(Dict_getNodeHash(this), 0, pNameA)) {
            eRc = NodeHash_DeleteA(Dict_getNodeHash(this), 0, pNameA);
        }
        eRc = NodeHash_AddA(Dict_getNodeHash(this), 0, pNameA, (void *)pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         Dict_AddUpdateA (
        DICT_DATA        *this,
        const
        char            *pNameA,
        const
        char            *pDataA
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dict_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = AStr_NewA(pDataA);
        if (OBJ_NIL == pStr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        if (NodeHash_FindA(Dict_getNodeHash(this), 0, pNameA)) {
            eRc = NodeHash_DeleteA(Dict_getNodeHash(this), 0, pNameA);
        }
        eRc = NodeHash_AddA(Dict_getNodeHash(this), 0, pNameA, pStr);
        
        // Return to caller.
        obj_Release(pStr);
        pStr = OBJ_NIL;
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Dict_Assign(this,pOther);
     @endcode 
     @param     this    DICT object pointer
     @param     pOther  a pointer to another DICT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Dict_Assign (
        DICT_DATA		*this,
        DICT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Dict_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Dict      *pCopy = Dict_Copy(this);
     @endcode 
     @param     this    DICT object pointer
     @return    If successful, a DICT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DICT_DATA *     Dict_Copy (
        DICT_DATA       *this
    )
    {
        DICT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Dict_New( );
        if (pOther) {
            eRc = Dict_Assign(this, pOther);
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

    void            Dict_Dealloc (
        OBJ_ID          objId
    )
    {
        DICT_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((DICT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Dict_setStr(this, OBJ_NIL);

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
    ERESULT         Dict_Disable (
        DICT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Dict_Validate(this)) {
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
    ERESULT         Dict_Enable (
        DICT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Dict_Validate(this)) {
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
    //              E x p a n d  V a r i a b l e s
    //---------------------------------------------------------------
    
    /*!
     Substitute environment variables into the current string using a BASH-like
     syntax.  Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         Dict_Expand(
        DICT_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;
        uint32_t        i = 0;
        uint32_t        iBegin;
        uint32_t        len;
        uint32_t        lenPrefix;
        uint32_t        lenSuffix;
        int32_t         chr;
        bool            fMore = true;
        //PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pData = OBJ_NIL;
        const
        char            *pEnvVar = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!Dict_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (0 == AStr_getLength(pStr)) {
            return ERESULT_SUCCESS;
        }
        
        // Expand Environment variables.
        while (fMore) {
            fMore = false;
            eRc = AStr_CharFindNextW32(pStr, &i, '%');
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            else {
                chr = AStr_CharGetW32(pStr, i+1);
                if (chr == '[') {
                    i += 2;
                    iBegin = i;
                    eRc = AStr_CharFindNextW32(pStr, &i, ']');
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_PARSE_ERROR;
                    }
                    len = i - iBegin;
                    eRc = AStr_Mid(pStr, iBegin, len, &pName);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    lenPrefix = 2;
                    lenSuffix = 1;

                    // Find the name from the Dictionary.
                do_replace:
                    pNode = NodeHash_FindA(
                                           Dict_getNodeHash(this),
                                           0,
                                           AStr_getData(pName)
                            );
                    if (OBJ_NIL == pNode) {
                        obj_Release(pName);
                        return ERESULT_DATA_NOT_FOUND;
                    }
                    obj_Release(pName);
                    pName = OBJ_NIL;
                    pData = Node_getData(pNode);
                    if((OBJ_NIL == pData)
                       || !(obj_IsKindOf(pData, OBJ_IDENT_ASTR)
                            || obj_IsKindOf(pData, OBJ_IDENT_ASTRC))) {
                        DEBUG_BREAK();
                        return ERESULT_DATA_MISSING;
                    }

                    // Substitute the name from the Dictionary.
                    eRc =   AStr_Remove(
                                pStr,
                                (iBegin - lenPrefix),
                                (len + lenPrefix + lenSuffix)
                            );
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    if (obj_IsKindOf(pData, OBJ_IDENT_ASTR)) {
                        eRc = AStr_InsertA(pStr, (iBegin - lenPrefix), AStr_getData(pData));
                    } else if (obj_IsKindOf(pData, OBJ_IDENT_ASTRC)) {
                        eRc = AStr_InsertA(pStr, (iBegin - lenPrefix), AStrC_getData(pData));
                    }
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    i = iBegin - lenPrefix + AStr_getSize(pData);
                    pEnvVar = NULL;
                    pData = OBJ_NIL;
                    pNode = OBJ_NIL;
                    fMore = true;
                }
                else {
                    //chr = AStr_CharGetW32(pStr, i+1);
                    if (ascii_isLabelFirstCharW32(chr)) {
                        ++i;
                        iBegin = i;
                        for (;;) {
                            ++i;
                            chr = AStr_CharGetW32(pStr, i);
                            if (!ascii_isLabelCharW32(chr)) {
                                break;
                            }
                        }
                        len = i - iBegin;
                        eRc = AStr_Mid(pStr, iBegin, len, &pName);
                        if (ERESULT_FAILED(eRc)) {
                            return ERESULT_OUT_OF_MEMORY;
                        }
                        lenPrefix = 1;
                        lenSuffix = 0;
                        
                        goto do_replace;

                    }
                    else
                        return ERESULT_PARSE_ERROR;
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    /*!
     Get the dictionary value for a given name.
     @param     this    object pointer
     @param     pNameA  pointer to UTF-8 Name string
     @return    if successful, pointer to data string.  Otherwise, NULL.
     */
    ASTR_DATA *     Dict_FindA (
        DICT_DATA       *this,
        const
        char            *pNameA
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pData = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pNode = NodeHash_FindA(Dict_getNodeHash(this), 0, pNameA);
        if (pNode) {
            pData = Node_getData(pNode);
            if (OBJ_NIL == pData)
                ;
            else  {
                if (obj_IsKindOf(pData, OBJ_IDENT_ASTR)) {
                    ;
                } else {
                    pData = OBJ_NIL;
                }
            }
        }

        // Return to caller.
        return pData;
    }



    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    /*!
     Get the dictionary value for a given name.
     @param     this    object pointer
     @param     pNameA  pointer to UTF-8 Name string
     @return    if successful, pointer to data string.  Otherwise, NULL.
     */
    const
    char *          Dict_GetA (
        DICT_DATA       *this,
        const
        char            *pNameA
    )
    {
        const
        char            *pStrA = NULL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pData = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif
        
        pNode = NodeHash_FindA(Dict_getNodeHash(this), 0, pNameA);
        if (pNode) {
            pData = Node_getData(pNode);
            if (OBJ_NIL == pData)
                ;
            else  if (obj_IsKindOf(pData, OBJ_IDENT_ASTR)) {
                pStrA = AStr_getData((ASTR_DATA *)pData);
            } else if (obj_IsKindOf(pData, OBJ_IDENT_ASTRC)) {
                pStrA = AStrC_getData((ASTRC_DATA *)pData);
            }
        } else {
            pStrA = getenv(pNameA);
        }
        
        // Return to caller.
        return pStrA;
    }
    
        
        
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DICT_DATA *   Dict_Init (
        DICT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(DICT_DATA);
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

        this = (OBJ_ID)NodeHash_Init((NODEHASH_DATA *)this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        (void)NodeHash_Setup((NODEHASH_DATA *)this, NODEHASH_TABLE_SIZE_XLARGE);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Dict_Vtbl);
        
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
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Dict::sizeof(DICT_DATA) = %lu\n", sizeof(DICT_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(DICT_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Dict_IsEnabled (
        DICT_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
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
        void        *pMethod = Dict_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Dict", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Dict_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        DICT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(DICT_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Dict_Class();
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
                            return Dict_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Dict_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Dict_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return Dict_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Dict_ToDebugString)
                    return "ToDebugString";
                if (pData == Dict_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     Dict_ToJSON (
        DICT_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!Dict_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Dict_ToDebugString(this,4);
     @endcode 
     @param     this    DICT object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Dict_ToDebugString (
        DICT_DATA      *this,
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
        if (!Dict_Validate(this)) {
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
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    Dict_getSize(this)
            );

        pWrkStr =   NodeHash_ToDebugString(Dict_getNodeHash(this), indent+3);
        AStr_Append(pStr, pWrkStr);
        obj_Release(pWrkStr);
        
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
    bool            Dict_Validate (
        DICT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_DICT))
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


        if (!(obj_getSize(this) >= sizeof(DICT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


