// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Dir.c
 *	Generated 01/31/2020 10:23:30
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
#include        <Dir_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            enumScanner(
        void            *pObj,
        DIRENTRY_DATA   *pDir
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum = (OBJENUM_DATA *)pObj;
        DIRENTRY_DATA   *pEntry;

        pEntry = DirEntry_Copy(pDir);
        if (pEntry) {
            eRc = ObjEnum_AppendObj(pEnum, pEntry);
            if (ERESULT_FAILED(eRc)) {
                return false;
            }
            obj_Release(pEntry);
            //pEntry = OBJ_NIL;
        }
        else {
            return false;
        }

        return true;
    }



#ifdef XYZZY
    static
    bool            scan_rm(
        void            *pObj,
        DIRENTRY_DATA   *pEntry
    )
    {
        //DIR_DATA        *this = pObj;
        //ERESULT         eRc;


        return true;
    }
#endif





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DIR_DATA *     Dir_Alloc (
        void
    )
    {
        DIR_DATA       *this;
        uint32_t        cbSize = sizeof(DIR_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                       I s D i r A
    //---------------------------------------------------------------

    ERESULT         Dir_IsDirA (
        const
        char            *pPath
    )
    {
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;

        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_FAILURE_FALSE;
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s E x i s t i n g A
    //---------------------------------------------------------------

    ERESULT         Dir_IsExistingA (
        const
        char            *pPath
    )
    {
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;

        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            eRc = ERESULT_SUCCESS;
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s F i l e A
    //---------------------------------------------------------------

    ERESULT         Dir_IsFileA (
        const
        char            *pPath
    )
    {
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;

        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_FAILURE_FALSE;
            }
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s L i n k A
    //---------------------------------------------------------------

    ERESULT         Dir_IsLinkA (
        const
        char            *pPath
    )
    {
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;

        if (NULL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFLNK) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_FAILURE_FALSE;
            }
        }
        else {
            eRc = ERESULT_PATH_NOT_FOUND;
        }
#endif

        // Return to caller.
        return eRc;
    }



    DIR_DATA *     Dir_New (
        void
    )
    {
        DIR_DATA       *this;
        
        this = Dir_Alloc( );
        if (this) {
            this = Dir_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Dir_getSize (
        DIR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Dir_getSuperVtbl (
        DIR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Dir_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another DIR object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Dir_Assign (
        DIR_DATA		*this,
        DIR_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Dir_Validate(pOther)) {
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
    int             Dir_Compare (
        DIR_DATA        *this,
        DIR_DATA        *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Dir_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Dir      *pCopy = Dir_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a DIR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DIR_DATA *     Dir_Copy (
        DIR_DATA       *this
    )
    {
        DIR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef DIR_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Dir_New( );
        if (pOther) {
            eRc = Dir_Assign(this, pOther);
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

    void            Dir_Dealloc (
        OBJ_ID          objId
    )
    {
        DIR_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((DIR_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
        Dir      *pDeepCopy = Dir_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a DIR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DIR_DATA *     Dir_DeepyCopy (
        DIR_DATA       *this
    )
    {
        DIR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Dir_New( );
        if (pOther) {
            eRc = Dir_Assign(this, pOther);
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
    ERESULT         Dir_Disable (
        DIR_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
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
    ERESULT         Dir_Enable (
        DIR_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
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
    //                       E n u m  D i r
    //---------------------------------------------------------------

    OBJENUM_DATA *  Dir_EnumDir (
        DIR_DATA        *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dir_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pEnum = ObjEnum_New();
        if( OBJ_NIL == pEnum ) {
            return OBJ_NIL;
        }

        eRc = Dir_ScanDir(this, pPath, &enumScanner, pEnum);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pEnum);
            pEnum = OBJ_NIL;
            return OBJ_NIL;
        }

        eRc = ObjEnum_SortAscending(pEnum);

        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DIR_DATA *   Dir_Init (
        DIR_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(DIR_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_DIR);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Dir_Vtbl);
        JsonIn_RegisterClass(DirEntry_Class());

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
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "Dir::sizeof(DIR_DATA) = %lu\n", 
                sizeof(DIR_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(DIR_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Dir_IsEnabled (
        DIR_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
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
    //                       I s D i r
    //---------------------------------------------------------------

    ERESULT         Dir_IsDir (
        DIR_DATA        *this,
        PATH_DATA       *pPath
    )
    {
        char            *pStr = NULL;
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dir_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pStr = AStr_CStringA((ASTR_DATA *)pPath, NULL);
        if (pStr) {
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
            iRc = stat(pStr, &statBuffer);
            if (0 == iRc) {
                if ((statBuffer.st_mode & S_IFMT) == S_IFDIR) {
                    eRc = ERESULT_SUCCESS;
                }
                else
                    eRc = ERESULT_FAILURE_FALSE;
            }
            else {
                eRc = ERESULT_PATH_NOT_FOUND;
            }
#endif
            mem_Free(pStr);
            pStr = NULL;
        }
        else {
            eRc = ERESULT_DATA_ERROR;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       M a k e D i r
    //---------------------------------------------------------------

    ERESULT         Dir_MakeDir (
        DIR_DATA        *this,
        PATH_DATA       *pPath,
        uint16_t        mode
    )
    {
        char            *pStr = NULL;
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dir_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = Path_IsExisting(pPath);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            return ERESULT_PATH_ALREADY_EXISTS;
        }

        pStr = AStr_CStringA((ASTR_DATA *)pPath, NULL);
        if (pStr) {
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
            iRc = mkdir(pStr, mode);
            if (0 == iRc) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_CANNOT_MAKE_DIRECTORY;
            }
#endif
            mem_Free(pStr);
            pStr = NULL;
        }
        else {
            eRc = ERESULT_DATA_ERROR;
        }

        // Return to caller.
        return eRc;
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
        void        *pMethod = Dir_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Dir", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Dir_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        DIR_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Dir_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(DIR_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Dir_Class();
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
                            return Dir_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Dir_Enable;
                        }
                        break;

#ifdef  DIR_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Dir_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Dir_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Dir_ToDebugString;
                        }
#ifdef  DIR_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Dir_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Dir_ToDebugString)
                    return "ToDebugString";
#ifdef  DIR_JSON_SUPPORT
                if (pData == Dir_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S c a n D i r
    //---------------------------------------------------------------

    ERESULT         Dir_ScanDir(
        DIR_DATA        *this,
        PATH_DATA       *pPath,
        bool            (*pScanner)(void *, DIRENTRY_DATA *),
        void            *pObject
    )
    {
        ERESULT         eRc;
        char            *pDirA;
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        struct dirent   *pDirent;
        DIR             *pDirectory;
        bool            fRc;
#endif
        ASTR_DATA       *pDrive = OBJ_NIL;
        PATH_DATA       *pDir = OBJ_NIL;
        PATH_DATA       *pFileName = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Dir_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pPath) || !(OBJ_IDENT_PATH == obj_getType(pPath)) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if( NULL == pScanner ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = Path_IsDir(pPath);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_PATH_NOT_FOUND;
        }

        eRc = Path_SplitPath(pPath, &pDrive, &pDir, OBJ_NIL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_PATH_NOT_FOUND;
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        pDirA = AStr_CStringA((ASTR_DATA *)pPath, NULL);
        if (pDirA) {
            pDirectory = opendir(pDirA);
            mem_Free(pDirA);
            pDirA = NULL;
            if (NULL == pDirectory) {
                return ERESULT_PATH_NOT_FOUND;
            }
        }
        else {
            return ERESULT_GENERAL_FAILURE;
        }

        while ((pDirent = readdir(pDirectory)) != NULL) {
            DIRENTRY_DATA   *pEntry;
            if ((pDirent->d_namlen == 1) && (0 == strcmp(".", pDirent->d_name))) {
                continue;
            }
            if ((pDirent->d_namlen == 2) && (0 == strcmp("..", pDirent->d_name))) {
                continue;
            }

            pFileName = Path_NewA(pDirent->d_name);
            if (OBJ_NIL == pFileName) {
                DEBUG_BREAK();
                closedir(pDirectory);
                return ERESULT_OUT_OF_MEMORY;
            }
            pEntry = DirEntry_NewWithData(pDrive, pDir, pFileName, pDirent->d_type);
            if( OBJ_NIL == pEntry ) {
                DEBUG_BREAK();
                closedir(pDirectory);
                return ERESULT_INVALID_PARAMETER;
            }
            obj_Release(pFileName);
            pFileName = OBJ_NIL;

            fRc = (*pScanner)(pObject, pEntry);
            obj_Release(pEntry);
            pEntry = OBJ_NIL;
            if (!fRc) {
                break;
            }
        }

        if (EOF == closedir(pDirectory)) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
            obj_Release(pDir);
            pDir = OBJ_NIL;
            return ERESULT_GENERAL_FAILURE;
        }

#endif

        // Return to caller.
        obj_Release(pDrive);
        pDrive = OBJ_NIL;
        obj_Release(pDir);
        pDir = OBJ_NIL;
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Dir_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Dir_ToDebugString (
        DIR_DATA      *this,
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
        if (!Dir_Validate(this)) {
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
                    Dir_getSize(this),
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Dir_Validate (
        DIR_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_DIR))
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


        if (!(obj_getSize(this) >= sizeof(DIR_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


