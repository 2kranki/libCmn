// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   exec.c
 *	Generated 04/10/2018 09:21:38
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
#include        <exec_internal.h>
#include        <fileio.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            exec_task_body(
        void            *pData
    )
    {
        //EXEC_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    EXEC_DATA *     exec_Alloc(
    )
    {
        EXEC_DATA       *this;
        uint32_t        cbSize = sizeof(EXEC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    EXEC_DATA *     exec_New(
    )
    {
        EXEC_DATA       *this;
        
        this = exec_Alloc( );
        if (this) {
            this = exec_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      D i g e s t
    //---------------------------------------------------------------
    
    uint8_t *        exec_getDigest(
        EXEC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        exec_setLastError(this, ERESULT_SUCCESS);
        return this->digest;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         exec_getLastError(
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            exec_setLastError(
        EXEC_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                          M D 5
    //---------------------------------------------------------------
    
    MD5CHKSUM_DATA *    exec_getMD5(
        EXEC_DATA           *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        exec_setLastError(this, ERESULT_SUCCESS);
        return this->pMD5;
    }
    
    
    bool            exec_setMD5(
        EXEC_DATA       *this,
        MD5CHKSUM_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pMD5) {
            obj_Release(this->pMD5);
        }
        this->pMD5 = pValue;
        
        exec_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        exec_getPriority(
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        exec_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            exec_setPriority(
        EXEC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        exec_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        exec_getSize(
        EXEC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        exec_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * exec_getStr(
        EXEC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        exec_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        exec_setStr(
        EXEC_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        exec_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  exec_getSuperVtbl(
        EXEC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        exec_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = exec__Assign(this,pOther);
     @endcode 
     @param     this    EXEC object pointer
     @param     pOther  a pointer to another EXEC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         exec_Assign(
        EXEC_DATA		*this,
        EXEC_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !exec_Validate(pOther) ) {
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
        exec_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        exec_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return exec_getLastError(this);
    }
    
    
    
    ERESULT         exec_CalculateFileCheckSum(
        EXEC_DATA       *this,
        PATH_DATA       *pPath              // valid file path
    )
    {
        ERESULT         eRc;
        MD5CHKSUM_DATA    *pChkSum = OBJ_NIL;
        FILEIO_DATA     *pIO = OBJ_NIL;
        size_t          fileSize;
        uint32_t        amtRead;
        uint32_t        bufferSize = 4096;
        uint8_t         *pBuffer = NULL;
        PATH_DATA       *pMD5Path = OBJ_NIL;
        ASTR_DATA       *pMD5Str = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        TRC_OBJ(this,"exec_CreateFileCheckSum()\n");
        
        pChkSum = md5ChkSum_New( );
        if (OBJ_NIL == pChkSum) {
            fprintf(stderr, "FATAL - Could not create MD5 Check Sum Object!\n\n\n");
            exit(99);
        }
        pBuffer = mem_Malloc(bufferSize);
        if (NULL == pBuffer) {
            fprintf(stderr, "FATAL - Could allocate read buffer!\n\n\n");
            exit(99);
        }
        
        
        pIO = fileio_New( );
        if (OBJ_NIL == pChkSum) {
            fprintf(stderr, "FATAL - Could not create fileio Object!\n\n\n");
            exit(99);
        }
        
        TRC_OBJ(this, "\tpath = \"%s\"\n", path_getData(pPath));
        eRc = fileio_Open(pIO, pPath);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Could not open file for input!\n\n\n");
            exit(99);
        }
        
        fileSize = fileio_Size(pIO);
        TRC_OBJ(this, "\tFile Size == %zu\n", fileSize);
        
        while(fileSize) {
            eRc = fileio_Read(pIO, bufferSize, pBuffer, &amtRead);
            if (ERESULT_FAILED(eRc)) {
                fprintf(stderr, "FATAL - Input File Read Error!\n\n\n");
                exit(99);
            }
            
            eRc = md5ChkSum_Update(pChkSum, pBuffer, amtRead);
            if (ERESULT_FAILED(eRc)) {
                fprintf(stderr, "FATAL - Buffer MD5 Check Sum Calculation Error!\n\n\n");
                exit(99);
            }
            
            fileSize -= amtRead;
        }
        
        mem_Free(pBuffer);
        pBuffer = NULL;
        
        eRc = fileio_Close(pIO, false);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Error closing input file!\n\n\n");
            exit(99);
        }
        
        obj_Release(pIO);
        pIO = OBJ_NIL;
        
        eRc = md5ChkSum_Finalize(pChkSum, pPath, &pMD5Str);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - MD5 Check Sum Finalization Error!\n\n\n");
            exit(99);
        }
        TRC_OBJ(this, "\tMD5 String = \"%s\"\n", AStr_getData(pMD5Str));
        
        pMD5Path = path_Copy(pPath);
        if (OBJ_NIL == pMD5Path) {
            fprintf(stderr, "FATAL - Could not create copy of File Path!\n\n\n");
            exit(99);
        }
        
        eRc = path_AppendExtA(pMD5Path, "md5.txt");
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Failed to make MD5 File Path!\n\n\n");
            exit(99);
        }
        
        eRc = AStr_ToUtf8File(pMD5Str, pMD5Path);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Could not create MD5 File: %s!\n\n\n",
                    path_getData(pMD5Path)
                    );
            exit(99);
        }
        
        obj_Release(pChkSum);
        pChkSum = OBJ_NIL;
        obj_Release(pMD5Path);
        pMD5Path = OBJ_NIL;
        obj_Release(pMD5Str);
        pMD5Str = OBJ_NIL;
        return 0;
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
    ERESULT         exec_Compare(
        EXEC_DATA     *this,
        EXEC_DATA     *pOther
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
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !exec_Validate(pOther) ) {
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
        
        this->eRc = eRc;
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        exec      *pCopy = exec_Copy(this);
     @endcode 
     @param     this    EXEC object pointer
     @return    If successful, a EXEC object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the EXEC object.
     */
    EXEC_DATA *     exec_Copy(
        EXEC_DATA       *this
    )
    {
        EXEC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = exec_New( );
        if (pOther) {
            eRc = exec_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    ERESULT         exec_CreateFileCheckSumFile(
        EXEC_DATA       *this,
        PATH_DATA       *pPath              // valid file path
    )
    {
        ERESULT         eRc;
        MD5CHKSUM_DATA    *pChkSum = OBJ_NIL;
        FILEIO_DATA     *pIO = OBJ_NIL;
        size_t          fileSize;
        uint32_t        amtRead;
        uint32_t        bufferSize = 4096;
        uint8_t         *pBuffer = NULL;
        PATH_DATA       *pMD5Path = OBJ_NIL;
        ASTR_DATA       *pMD5Str = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        TRC_OBJ(this,"exec_CreateFileCheckSum()\n");
        
        pChkSum = md5ChkSum_New( );
        if (OBJ_NIL == pChkSum) {
            fprintf(stderr, "FATAL - Could not create MD5 Check Sum Object!\n\n\n");
            exit(99);
        }
        pBuffer = mem_Malloc(bufferSize);
        if (NULL == pBuffer) {
            fprintf(stderr, "FATAL - Could allocate read buffer!\n\n\n");
            exit(99);
        }
        
        
        pIO = fileio_New( );
        if (OBJ_NIL == pChkSum) {
            fprintf(stderr, "FATAL - Could not create fileio Object!\n\n\n");
            exit(99);
        }
        
        TRC_OBJ(this, "\tpath = \"%s\"\n", path_getData(pPath));
        eRc = fileio_Open(pIO, pPath);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Could not open file for input!\n\n\n");
            exit(99);
        }
        
        fileSize = fileio_Size(pIO);
        TRC_OBJ(this, "\tFile Size == %zu\n", fileSize);
        
        while(fileSize) {
            eRc = fileio_Read(pIO, bufferSize, pBuffer, &amtRead);
            if (ERESULT_FAILED(eRc)) {
                fprintf(stderr, "FATAL - Input File Read Error!\n\n\n");
                exit(99);
            }
            
            eRc = md5ChkSum_Update(pChkSum, pBuffer, amtRead);
            if (ERESULT_FAILED(eRc)) {
                fprintf(stderr, "FATAL - Buffer MD5 Check Sum Calculation Error!\n\n\n");
                exit(99);
            }
            
            fileSize -= amtRead;
        }
        
        mem_Free(pBuffer);
        pBuffer = NULL;
        
        eRc = fileio_Close(pIO, false);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Error closing input file!\n\n\n");
            exit(99);
        }
        
        obj_Release(pIO);
        pIO = OBJ_NIL;
        
        eRc = md5ChkSum_Finalize(pChkSum, pPath, &pMD5Str);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - MD5 Check Sum Finalization Error!\n\n\n");
            exit(99);
        }
        TRC_OBJ(this, "\tMD5 String = \"%s\"\n", AStr_getData(pMD5Str));

        pMD5Path = path_Copy(pPath);
        if (OBJ_NIL == pMD5Path) {
            fprintf(stderr, "FATAL - Could not create copy of File Path!\n\n\n");
            exit(99);
        }
        
        eRc = path_AppendExtA(pMD5Path, "md5.txt");
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Failed to make MD5 File Path!\n\n\n");
            exit(99);
        }
        
        eRc = AStr_ToUtf8File(pMD5Str, pMD5Path);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "FATAL - Could not create MD5 File: %s!\n\n\n",
                    path_getData(pMD5Path)
                    );
            exit(99);
        }
        
        obj_Release(pChkSum);
        pChkSum = OBJ_NIL;
        obj_Release(pMD5Path);
        pMD5Path = OBJ_NIL;
        obj_Release(pMD5Str);
        pMD5Str = OBJ_NIL;
        return 0;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            exec_Dealloc(
        OBJ_ID          objId
    )
    {
        EXEC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((EXEC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        exec_setStr(this, OBJ_NIL);

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

    ERESULT         exec_Disable(
        EXEC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        exec_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         exec_Enable(
        EXEC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        exec_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    EXEC_DATA *   exec_Init(
        EXEC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(EXEC_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_EXEC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_EXEC);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&exec_Vtbl);
        
        exec_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

        this->pMD5 = md5ChkSum_New( );
        if (OBJ_NIL == this->pMD5) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "exec::offsetof(eRc) = %lu\n", offsetof(EXEC_DATA,eRc));
        //fprintf(stderr, "exec::sizeof(EXEC_DATA) = %lu\n", sizeof(EXEC_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(EXEC_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         exec_IsEnabled(
        EXEC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            exec_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        exec_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = exec_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "exec", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          exec_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        EXEC_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)exec_Class();
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
                            return exec_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return exec_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return exec_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return exec_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == exec_ToDebugString)
                    return "ToDebugString";
                if (pData == exec_ToJSON)
                    return "ToJSON";
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
        ASTR_DATA      *pDesc = exec_ToDebugString(this,4);
     @endcode 
     @param     this    EXEC object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     exec_ToDebugString(
        EXEC_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = exec_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    exec_getSize(this)
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
        
        exec_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     exec_ToJSON(
        EXEC_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !exec_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        exec_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            exec_Validate(
        EXEC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, MAIN_IDENT_EXEC) )
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


        if( !(obj_getSize(this) >= sizeof(EXEC_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


