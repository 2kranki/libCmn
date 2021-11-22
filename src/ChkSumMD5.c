// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ChkSumMD5.c
 *  Generated 11/21/2021 14:37:54
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
#include        <ChkSumMD5_internal.h>
#include        <FileIO.h>
#include        <hex.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>
#include        <Value.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ChkSumMD5_task_body (
        void            *pData
    )
    {
        //CHKSUMMD5_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CHKSUMMD5_DATA *     ChkSumMD5_Alloc (
        void
    )
    {
        CHKSUMMD5_DATA       *this;
        uint32_t        cbSize = sizeof(CHKSUMMD5_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    CHKSUMMD5_DATA *     ChkSumMD5_New (
        void
    )
    {
        CHKSUMMD5_DATA       *this;
        
        this = ChkSumMD5_Alloc( );
        if (this) {
            this = ChkSumMD5_Init(this);
        } 
        return this;
    }



    CHKSUMMD5_DATA * ChkSumMD5_NewFromUtf8File(
        PATH_DATA       *pPath
    )
    {
        CHKSUMMD5_DATA  *this;
        ERESULT         eRc;

        this = ChkSumMD5_New( );
        if (this) {
            eRc = ChkSumMD5_FromUtf8File(this, pPath, OBJ_NIL);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }



    // "MD5 ("file name/path") = "16 byte hexadecimal digest(32 chars)"\n"
    ERESULT         ChkSumMD5_ParseDigest(
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

        if (0 == AStr_CompareLeftA(pInput, "MD5 ("))
            ;
        else {
            return ERESULT_PARSE_ERROR;
        }
        if (0 == AStr_CompareRightA(pInput,"\n"))
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

    uint8_t *   ChkSumMD5_getDigest(
        CHKSUMMD5_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !ChkSumMD5_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->digest;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   CHKSUMMD5_MSGS
    bool            ChkSumMD5_setMsgs (
        CHKSUMMD5_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
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
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        ChkSumMD5_getPriority (
        CHKSUMMD5_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            ChkSumMD5_setPriority (
        CHKSUMMD5_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
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
    
    uint32_t        ChkSumMD5_getSize (
        CHKSUMMD5_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                        S t r  M D 5
    //---------------------------------------------------------------
    
    ASTR_DATA *     ChkSumMD5_getStrMD5 (
        CHKSUMMD5_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStrMD5;
    }
    
    
    bool            ChkSumMD5_setStrMD5 (
        CHKSUMMD5_DATA  *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStrMD5) {
            obj_Release(this->pStrMD5);
        }
        this->pStrMD5 = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ChkSumMD5_getSuperVtbl (
        CHKSUMMD5_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  
    CHKSUMMD5_DATA *  ChkSumMD5_getSuper (
        CHKSUMMD5_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (CHKSUMMD5_DATA *)this;
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
        ERESULT eRc = ChkSumMD5_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another CHKSUMMD5 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ChkSumMD5_Assign (
        CHKSUMMD5_DATA       *this,
        CHKSUMMD5_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ChkSumMD5_Validate(pOther)) {
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             ChkSumMD5_Compare (
        CHKSUMMD5_DATA     *this,
        CHKSUMMD5_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  CHKSUMMD5_SINGLETON
        if (OBJ_NIL == this) {
            this = ChkSumMD5_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!ChkSumMD5_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ChkSumMD5      *pCopy = ChkSumMD5_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CHKSUMMD5 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CHKSUMMD5_DATA *     ChkSumMD5_Copy (
        CHKSUMMD5_DATA       *this
    )
    {
        CHKSUMMD5_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef CHKSUMMD5_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = ChkSumMD5_New( );
        if (pOther) {
            eRc = ChkSumMD5_Assign(this, pOther);
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

    void            ChkSumMD5_Dealloc (
        OBJ_ID          objId
    )
    {
        CHKSUMMD5_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CHKSUMMD5_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ChkSumMD5_setStrMD5(this, OBJ_NIL);

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
        ChkSumMD5      *pDeepCopy = ChkSumMD5_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CHKSUMMD5 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CHKSUMMD5_DATA *     ChkSumMD5_DeepCopy (
        CHKSUMMD5_DATA       *this
    )
    {
        CHKSUMMD5_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ChkSumMD5_New( );
        if (pOther) {
            eRc = ChkSumMD5_Assign(this, pOther);
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
    ERESULT         ChkSumMD5_Disable (
        CHKSUMMD5_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CHKSUMMD5_SINGLETON
        if (OBJ_NIL == this) {
            this = ChkSumMD5_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
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
    ERESULT         ChkSumMD5_Enable (
        CHKSUMMD5_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CHKSUMMD5_SINGLETON
        if (OBJ_NIL == this) {
            this = ChkSumMD5_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   CHKSUMMD5_MSGS
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
    //                          F i n a l i z e
    //---------------------------------------------------------------

    ERESULT         ChkSumMD5_Finalize(
        CHKSUMMD5_DATA  *this,
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
        if( !ChkSumMD5_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        MD5_Final(this->digest, &this->ctx);

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
            ChkSumMD5_setStrMD5(this, pMD5);
        }

        obj_Release(pMd5File);
        pMd5File = OBJ_NIL;

        // Return to caller.
    eom:
        return eRc;
    }



    //---------------------------------------------------------------
    //                     F r o m  UTF-8 File
    //---------------------------------------------------------------

    ERESULT         ChkSumMD5_FromUtf8File(
        CHKSUMMD5_DATA  *this,
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
        if( !ChkSumMD5_Validate(this) ) {
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

        pIO = FileIO_New( );
        if (OBJ_NIL == pIO) {
            DEBUG_BREAK();
            mem_Free(pBuffer);
            pBuffer = NULL;
            return ERESULT_GENERAL_FAILURE;
        }

        eRc = FileIO_Open(pIO, pPath, false);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            mem_Free(pBuffer);
            pBuffer = NULL;
            return eRc;
        }

        fileSize = FileIO_Size(pIO);

        while(fileSize) {
            eRc = FileIO_Read(pIO, cBuffer, pBuffer, &amtRead);
            if (ERESULT_FAILED(eRc)) {
                mem_Free(pBuffer);
                pBuffer = NULL;
            }

            eRc = ChkSumMD5_Update(this, pBuffer, amtRead);
            if (ERESULT_FAILED(eRc)) {
                mem_Free(pBuffer);
                pBuffer = NULL;
                fprintf(stderr, "FATAL - Buffer MD5 Check Sum Calculation Error!\n\n\n");
                exit(99);
            }

            fileSize -= amtRead;
        }

        eRc = FileIO_Close(pIO, false);
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

        eRc = ChkSumMD5_Finalize(this, pPath, &pMD5);
        if (!ERESULT_FAILED(eRc) && ppOutput) {
            *ppOutput = pMD5;
        }
        else {
            obj_Release(pMD5);
            pMD5 = OBJ_NIL;
        }

        // Return to caller.
    eom:
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CHKSUMMD5_DATA *   ChkSumMD5_Init (
        CHKSUMMD5_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CHKSUMMD5_DATA);
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

        //this = (OBJ_ID)ChkSumMD5_Init((CHKSUMMD5_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of ChkSumMD5_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CHKSUMMD5);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ChkSumMD5_Vtbl);
#ifdef  CHKSUMMD5_JSON_SUPPORT
        JsonIn_RegisterClass(ChkSumMD5_Class());
#endif

        MD5_Init(&this->ctx);
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
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "ChkSumMD5::sizeof(CHKSUMMD5_DATA) = %lu\n", 
                sizeof(CHKSUMMD5_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(CHKSUMMD5_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ChkSumMD5_IsEnabled (
        CHKSUMMD5_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CHKSUMMD5_SINGLETON
        if (OBJ_NIL == this) {
            this = ChkSumMD5_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
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
        void        *pMethod = ChkSumMD5_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ChkSumMD5", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ChkSumMD5_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CHKSUMMD5_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(CHKSUMMD5_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ChkSumMD5_Class();
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
                            return ChkSumMD5_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ChkSumMD5_Enable;
                        }
                        break;

                    case 'P':
#ifdef  CHKSUMMD5_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return ChkSumMD5_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return ChkSumMD5_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ChkSumMD5_ToDebugString;
                        }
#ifdef  CHKSUMMD5_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return ChkSumMD5_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ChkSumMD5_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ChkSumMD5_ToDebugString)
                    return "ToDebugString";
#ifdef  CHKSUMMD5_JSON_SUPPORT
                if (pData == ChkSumMD5_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s t a r t
    //---------------------------------------------------------------

    /*!
     Restart the MD5 calculation engine to process another MD5 calculation.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ChkSumMD5_Restart (
        CHKSUMMD5_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  CHKSUMMD5_SINGLETON
        if (OBJ_NIL == this) {
            this = ChkSumMD5_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ChkSumMD5_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        MD5_Init(&this->ctx);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ChkSumMD5_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ChkSumMD5_ToDebugString (
        CHKSUMMD5_DATA      *this,
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
        if (!ChkSumMD5_Validate(this)) {
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
                    ChkSumMD5_getSize(this),
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
    //                       U p d a t e
    //---------------------------------------------------------------

    ERESULT         ChkSumMD5_Update(
        CHKSUMMD5_DATA  *this,
        const
        uint8_t         *pData,
        uint32_t        len
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ChkSumMD5_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        MD5_Update(&this->ctx, pData, len);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            ChkSumMD5_Validate (
        CHKSUMMD5_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_CHKSUMMD5))
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


        if (!(obj_getSize(this) >= sizeof(CHKSUMMD5_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


