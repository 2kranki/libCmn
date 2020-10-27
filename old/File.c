// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   File.c
 *  Generated 10/27/2020 09:53:08
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
#include        <File_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            File_task_body (
        void            *pData
    )
    {
        //FILE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    FILE_DATA *     File_Alloc (
        void
    )
    {
        FILE_DATA       *this;
        uint32_t        cbSize = sizeof(FILE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------

    ERESULT         File_DeleteA(
        const
        char            *pPathA
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        bool            bRc;
#endif

        if (NULL == pPathA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPathA, &statBuffer);
        if (0 == iRc) {
            iRc = unlink(pPathA);
            if (0 == iRc) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_FILE_OPERATION_FAILED;
            }
        }
        else {
            eRc = ERESULT_FILE_NOT_FOUND;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        //TODO: DeleteFileW is more pwerful. Need to investgate using
        //      it instead
        bRc = DeleteFileA(pPathA);
        if (bRc)
            eRc = ERESULT_SUCCESS;
        else
            eRc = ERESULT_FILE_OPERATION_FAILED;
#endif

        // Return to caller.
        return eRc;
    }



    FILE_DATA *     File_New (
        void
    )
    {
        FILE_DATA       *this;
        
        this = File_Alloc( );
        if (this) {
            this = File_Init(this);
        } 
        return this;
    }



    //---------------------------------------------------------------
    //                          R e n a m e
    //---------------------------------------------------------------

    ERESULT         File_RenameA(
        const
        char            *pPathOldA,
        const
        char            *pPathNewA
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        bool            bRc;
#endif

        if ((NULL == pPathOldA) || (NULL == pPathNewA)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPathOldA, &statBuffer);
        if (0 == iRc) {
            iRc = rename(pPathOldA, pPathNewA);
            if (0 == iRc) {
                eRc = ERESULT_SUCCESS;
            }
            else {
                eRc = ERESULT_FILE_OPERATION_FAILED;
            }
        }
        else {
            eRc = ERESULT_FILE_NOT_FOUND;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        //TODO: MoveFileExW is more pwerful. Need to investgate using
        //      it instead
        bRc = MoveFileExA(pPathOldA, pPathNewA, MOVEFILE_WRITE_THROUGH);
        if (bRc)
            eRc = ERESULT_SUCCESS;
        else
            eRc = ERESULT_FILE_OPERATION_FAILED;
#endif

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       F i l e  S i z e A
    //---------------------------------------------------------------

    int64_t         File_SizeA(
        const
        char            *pPath
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
        int64_t         fileSize = -1;

        if (NULL == pPath) {
            return -1;
        }

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPath, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {
                fileSize = statBuffer.st_size;
            }
        }
#endif

        // Return to caller.
        return fileSize;
    }




    //---------------------------------------------------------------
    //                   F i l e  T o  A r r a y A
    //---------------------------------------------------------------

    ERESULT         File_ToArrayA(
        const
        char            *pPath,
        U8ARRAY_DATA    **ppArray
    )
    {
        U8ARRAY_DATA    *pArray;
        int64_t         size = 0;
        int             chr;
        FILE            *pFile;

        size = File_SizeA(pPath);
        if (-1 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pArray = u8Array_New();
        if (OBJ_NIL == pArray) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }

        pFile = fopen(pPath, "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( (chr = fgetc(pFile)) != EOF ) {
            u8Array_AppendData(pArray, (chr & 0xFF));
        }
        fclose(pFile);
        pFile = NULL;

        // Return to caller.
        if (ppArray) {
            *ppArray = pArray;
        }
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                   F i l e  T o  B u f f e r A
    //---------------------------------------------------------------

    ERESULT         File_ToBufferA(
        const
        char            *pPath,
        uint8_t         **ppBuffer
    )
    {
        //ERESULT         eRc;
        uint8_t         *pBuffer = NULL;
        int64_t         size;
        int             chr;
        FILE            *pFile;
        uint8_t         *pData;

        if (ppBuffer) {
            *ppBuffer = pBuffer;
        }
        size = File_SizeA(pPath);
        if (-1 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (0 == size) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pBuffer = mem_Malloc(size);
        if (OBJ_NIL == pBuffer) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }

        pFile = fopen(pPath, "rb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        pData = pBuffer;
        while ( (chr = fgetc(pFile)) != EOF ) {
            *pData++ = (chr & 0xFF);
        }
        fclose(pFile);
        pFile = NULL;

        // Return to caller.
        if (ppBuffer) {
            *ppBuffer = pBuffer;
        }
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o u c h A
    //---------------------------------------------------------------

    ERESULT         File_TouchA(
        const
        char            *pPathA
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        struct stat     statBuffer;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        HRESULT         hRc;
#endif
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        FILE            *pFile = NULL;

        if (NULL == pPathA) {
            return ERESULT_INVALID_PARAMETER;
        }

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        iRc = stat(pPathA, &statBuffer);
        if (0 == iRc) {
            if ((statBuffer.st_mode & S_IFMT) == S_IFREG) {  // Regular File
                iRc = utimes(pPathA, NULL);
                if (0 == iRc) {
                    eRc = ERESULT_SUCCESS;
                }
            }
        }
        else {
            if (iRc == ENOENT) {
                pFile = fopen(pPathA, "w");
                if (pFile) {
                    fclose(pFile);
                    pFile = NULL;
                    eRc = ERESULT_SUCCESS;
                }
            }
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        dwFileAttr = GetFileAttributesA(pPathA);
        hRc = E_FAIL;
        if( dwFileAttr != 0xFFFFFFFF ) {
            if( dwFileAttr & FILE_ATTRIBUTE_DIRECTORY )
                ;
            else {
                hRc = S_OK;
            }
        }
#endif

        // Return to caller.
        return eRc;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        File_getPriority (
        FILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            File_setPriority (
        FILE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
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
    
    uint32_t        File_getSize (
        FILE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * File_getStr (
        FILE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        File_setStr (
        FILE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  File_getSuperVtbl (
        FILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
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
        ERESULT eRc = File_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another FILE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         File_Assign (
        FILE_DATA       *this,
        FILE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!File_Validate(pOther)) {
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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
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
    ERESULT         File_Compare (
        FILE_DATA     *this,
        FILE_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!File_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
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
        File      *pCopy = File_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a FILE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    FILE_DATA *     File_Copy (
        FILE_DATA       *this
    )
    {
        FILE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef FILE_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = File_New( );
        if (pOther) {
            eRc = File_Assign(this, pOther);
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

    void            File_Dealloc (
        OBJ_ID          objId
    )
    {
        FILE_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((FILE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        File_setStr(this, OBJ_NIL);

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
        File      *pDeepCopy = File_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a FILE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    FILE_DATA *     File_DeepyCopy (
        FILE_DATA       *this
    )
    {
        FILE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = File_New( );
        if (pOther) {
            eRc = File_Assign(this, pOther);
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
    ERESULT         File_Disable (
        FILE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

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
    ERESULT         File_Enable (
        FILE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    FILE_DATA *   File_Init (
        FILE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(FILE_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_FILE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&File_Vtbl);
        
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
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "File::sizeof(FILE_DATA) = %lu\n", 
                sizeof(FILE_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(FILE_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         File_IsEnabled (
        FILE_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
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
        void        *pMethod = File_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "File", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          File_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        FILE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!File_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(FILE_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)File_Class();
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
                            return File_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return File_Enable;
                        }
                        break;

                    case 'P':
#ifdef  FILE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return File_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return File_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return File_ToDebugString;
                        }
#ifdef  FILE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return File_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return File_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == File_ToDebugString)
                    return "ToDebugString";
#ifdef  FILE_JSON_SUPPORT
                if (pData == File_ToJson)
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
        ASTR_DATA      *pDesc = File_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     File_ToDebugString (
        FILE_DATA      *this,
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
        if (!File_Validate(this)) {
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
                    File_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            ASTR_DATA       *pWrkStr = OBJ_NIL;
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
    bool            File_Validate (
        FILE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_FILE))
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


        if (!(obj_getSize(this) >= sizeof(FILE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


