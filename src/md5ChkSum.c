// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   md5ChkSum.c
 *	Generated 04/01/2018 21:11:43
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
#include <md5ChkSum_internal.h>
#include <fileio.h>
#include <hex.h>
#include <Path.h>
#include <Value.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            md5ChkSum_task_body(
        void            *pData
    )
    {
        //MD5CHKSUM_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MD5CHKSUM_DATA *     md5ChkSum_Alloc(
    )
    {
        MD5CHKSUM_DATA       *this;
        uint32_t        cbSize = sizeof(MD5CHKSUM_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MD5CHKSUM_DATA *     md5ChkSum_New(
    )
    {
        MD5CHKSUM_DATA       *this;
        
        this = md5ChkSum_Alloc( );
        if (this) {
            this = md5ChkSum_Init(this);
        } 
        return this;
    }


    
    MD5CHKSUM_DATA * md5ChkSum_NewFromUtf8File(
        PATH_DATA       *pPath
    )
    {
        MD5CHKSUM_DATA  *this;
        ERESULT         eRc;
        
        this = md5ChkSum_Alloc( );
        if (this) {
            this = md5ChkSum_Init(this);
            if (this) {
                eRc = md5ChkSum_FromUtf8File(this, pPath, OBJ_NIL);
                md5ChkSum_setLastError(this, eRc);
            }
        }
        return this;
    }

    
    
    // "MD5 ("file name/path") = "16 byte hexadecimal digest(32 chars)"\n"
    ERESULT         md5ChkSum_ParseDigest(
        ASTR_DATA       *pInput,
        PATH_DATA       **ppPath,
        VALUE_DATA      **ppDigest
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        cInput = 0;
        const
        uint32_t        cDigest = 8;
        uint8_t         digest[16];
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        VALUE_DATA      *pValue = OBJ_NIL;

#ifdef NDEBUG
#else
        if (OBJ_NIL == pInput) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((OBJ_NIL == ppPath) && (OBJ_NIL == ppDigest)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (ppPath)
            *ppPath = OBJ_NIL;
        if (ppDigest)
            *ppDigest = NULL;
        for (i=0; i<cDigest; ++i) {
            digest[i] = 0;
        }
        cInput = AStr_getLength(pInput);
        
        if (ERESULT_SUCCESS_EQUAL == AStr_CompareLeftA(pInput, "MD5 ("))
            ;
        else {
            return ERESULT_PARSE_ERROR;
        }
        if (ERESULT_SUCCESS_EQUAL == AStr_CompareRightA(pInput,"\n"))
            ;
        else {
            return ERESULT_PARSE_ERROR;
        }
        
        if (ppPath) {
            i = cInput - 33;
            eRc = AStr_CharFindPrevW32(pInput, &i, ')');
            if (ERESULT_FAILED(eRc)) {
                return ERESULT_PARSE_ERROR;
            }
            eRc = AStr_Mid(pInput, 6, (cInput - 42), &pStr);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            //fprintf(stderr, "%s\n", AStr_getData(pStr));
            pPath = Path_NewA(AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
            if (OBJ_NIL == pPath) {
                return ERESULT_PARSE_ERROR;
            }
            *ppPath = pPath;
        }

        if (ppDigest) {
            eRc = AStr_Mid(pInput, (AStr_getLength(pInput) - 32), 32, &pStr);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
            //fprintf(stderr, "\"%s\"\n", AStr_getData(pStr));
            eRc = hex_ScanData(32, AStr_getData(pStr), &pValue);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pValue);
                pValue = OBJ_NIL;
                return ERESULT_PARSE_ERROR;
            }
            *ppDigest = pValue;
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        D i g e s t
    //---------------------------------------------------------------
    
    uint8_t *   md5ChkSum_getDigest(
        MD5CHKSUM_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return this->digest;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         md5ChkSum_getLastError(
        MD5CHKSUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            md5ChkSum_setLastError(
        MD5CHKSUM_DATA  *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    ASTR_DATA *     md5ChkSum_getMD5_Str(
        MD5CHKSUM_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return this->pMD5_Str;
    }
    
    
    bool            md5ChkSum_setMD5_Str(
        MD5CHKSUM_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pMD5_Str) {
            obj_Release(this->pMD5_Str);
            //this->pMD5_Str = OBJ_NIL;
        }
        this->pMD5_Str = pValue;
        
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        md5ChkSum_getPriority(
        MD5CHKSUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            md5ChkSum_setPriority(
        MD5CHKSUM_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        md5ChkSum_getSize(
        MD5CHKSUM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  md5ChkSum_getSuperVtbl(
        MD5CHKSUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = md5ChkSum__Assign(this,pOther);
     @endcode 
     @param     this    MD5CHKSUM object pointer
     @param     pOther  a pointer to another MD5CHKSUM object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         md5ChkSum_Assign(
        MD5CHKSUM_DATA		*this,
        MD5CHKSUM_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !md5ChkSum_Validate(pOther) ) {
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
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        md5ChkSum_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return md5ChkSum_getLastError(this);
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
    ERESULT         md5ChkSum_Compare(
        MD5CHKSUM_DATA     *this,
        MD5CHKSUM_DATA     *pOther
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
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !md5ChkSum_Validate(pOther) ) {
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
        md5ChkSum      *pCopy = md5ChkSum_Copy(this);
     @endcode 
     @param     this    MD5CHKSUM object pointer
     @return    If successful, a MD5CHKSUM object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the MD5CHKSUM object.
     */
    MD5CHKSUM_DATA *     md5ChkSum_Copy(
        MD5CHKSUM_DATA       *this
    )
    {
        MD5CHKSUM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = md5ChkSum_New( );
        if (pOther) {
            eRc = md5ChkSum_Assign(this, pOther);
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
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            md5ChkSum_Dealloc(
        OBJ_ID          objId
    )
    {
        MD5CHKSUM_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MD5CHKSUM_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif
        md5ChkSum_setMD5_Str(this, OBJ_NIL);

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

    ERESULT         md5ChkSum_Disable(
        MD5CHKSUM_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         md5ChkSum_Enable(
        MD5CHKSUM_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          F i n a l i z e
    //---------------------------------------------------------------
    
    ERESULT         md5ChkSum_Finalize(
        MD5CHKSUM_DATA  *this,
        PATH_DATA       *pPath,         // (in) Optional File
        ASTR_DATA       **ppOutput      // (out) Optional MD5 String
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pMd5File = OBJ_NIL;
        ASTR_DATA       *pMD5 = OBJ_NIL;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        MD5Final(this->digest, &this->ctx);
        
        if (pPath && ppOutput) {
            eRc = Path_SplitPath(pPath, OBJ_NIL, OBJ_NIL, &pMd5File);
            if (OBJ_NIL == pMd5File) {
                goto eom;
            }
            
            pMD5 = AStr_New();
            if (pMD5) {
                AStr_AppendPrint(pMD5, "MD5 (%s) = ", Path_getData(pMd5File));
                for(i=0; i<16; ++i) {
                    AStr_AppendPrint(pMD5, "%02x", this->digest[i]);
                }
                AStr_AppendPrint(pMD5, "\n");
            }
            *ppOutput = pMD5;
            md5ChkSum_setMD5_Str(this, pMD5);
        }
        
        obj_Release(pMd5File);
        pMd5File = OBJ_NIL;
        
        // Return to caller.
    eom:
        md5ChkSum_setLastError(this, eRc);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     F r o m  UTF-8 File
    //---------------------------------------------------------------
    
    ERESULT         md5ChkSum_FromUtf8File(
        MD5CHKSUM_DATA  *this,
        PATH_DATA       *pPath,         // (in) Optional File
        ASTR_DATA       **ppOutput      // (out) Optional MD5 String
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //PATH_DATA       *pMd5File = OBJ_NIL;
        ASTR_DATA       *pMD5 = OBJ_NIL;
        //uint32_t        i;
        uint32_t        cBuffer = 4096;
        uint8_t         *pBuffer = NULL;
        FILEIO_DATA     *pIO = OBJ_NIL;
        size_t          fileSize;
        uint32_t        amtRead;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pBuffer = mem_Malloc(cBuffer);
        if (NULL == pBuffer) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        pIO = fileio_New( );
        if (OBJ_NIL == pIO) {
            DEBUG_BREAK();
            mem_Free(pBuffer);
            pBuffer = NULL;
            return ERESULT_GENERAL_FAILURE;
        }
        
        eRc = fileio_Open(pIO, pPath);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            mem_Free(pBuffer);
            pBuffer = NULL;
            return eRc;
        }
        
        fileSize = fileio_Size(pIO);
        
        while(fileSize) {
            eRc = fileio_Read(pIO, cBuffer, pBuffer, &amtRead);
            if (ERESULT_FAILED(eRc)) {
                mem_Free(pBuffer);
                pBuffer = NULL;
            }
            
            eRc = md5ChkSum_Update(this, pBuffer, amtRead);
            if (ERESULT_FAILED(eRc)) {
                mem_Free(pBuffer);
                pBuffer = NULL;
                fprintf(stderr, "FATAL - Buffer MD5 Check Sum Calculation Error!\n\n\n");
                exit(99);
            }
            
            fileSize -= amtRead;
        }
        
        eRc = fileio_Close(pIO, false);
        if (ERESULT_FAILED(eRc)) {
            mem_Free(pBuffer);
            pBuffer = NULL;
            fprintf(stderr, "FATAL - Error closing input file!\n\n\n");
            exit(99);
        }
        
        obj_Release(pIO);
        pIO = OBJ_NIL;
        
        mem_Free(pBuffer);
        pBuffer = NULL;
        
        eRc = md5ChkSum_Finalize(this, pPath, &pMD5);
        if (!ERESULT_FAILED(eRc) && ppOutput) {
            *ppOutput = pMD5;
        }
        else {
            obj_Release(pMD5);
            pMD5 = OBJ_NIL;
        }
        
        // Return to caller.
    eom:
        md5ChkSum_setLastError(this, eRc);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MD5CHKSUM_DATA *   md5ChkSum_Init(
        MD5CHKSUM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MD5CHKSUM_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MD5CHKSUM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_MD5CHKSUM);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&md5ChkSum_Vtbl);
        
        md5ChkSum_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = ObjArray_New( );

        MD5Init(&this->ctx);
        
    #ifdef NDEBUG
    #else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "md5ChkSum::offsetof(eRc) = %lu\n", offsetof(MD5CHKSUM_DATA,eRc));
        //fprintf(stderr, "md5ChkSum::sizeof(MD5CHKSUM_DATA) = %lu\n", sizeof(MD5CHKSUM_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(MD5CHKSUM_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         md5ChkSum_IsEnabled(
        MD5CHKSUM_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            md5ChkSum_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        md5ChkSum_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = md5ChkSum_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "md5ChkSum", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          md5ChkSum_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MD5CHKSUM_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)md5ChkSum_Class();
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
                            return md5ChkSum_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return md5ChkSum_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return md5ChkSum_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return md5ChkSum_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == md5ChkSum_ToDebugString)
                    return "ToDebugString";
                if (pData == md5ChkSum_ToJSON)
                    return "ToJson";
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
        ASTR_DATA      *pDesc = md5ChkSum_ToDebugString(this,4);
     @endcode 
     @param     this    MD5CHKSUM object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     md5ChkSum_ToDebugString(
        MD5CHKSUM_DATA      *this,
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
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = md5ChkSum_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s)\n",
                    this,
                    pInfo->pClassName
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
        
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     md5ChkSum_ToJSON(
        MD5CHKSUM_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
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
        
        md5ChkSum_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       U p d a t e
    //---------------------------------------------------------------
    
    ERESULT         md5ChkSum_Update(
        MD5CHKSUM_DATA  *this,
        const
        uint8_t         *pData,
        uint32_t        len
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !md5ChkSum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        MD5Update(&this->ctx, pData, len);
        
        // Return to caller.
        md5ChkSum_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            md5ChkSum_Validate(
        MD5CHKSUM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_MD5CHKSUM) )
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


        if( !(obj_getSize(this) >= sizeof(MD5CHKSUM_DATA)) ) {
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


