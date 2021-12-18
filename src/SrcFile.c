// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SrcFile.c
 *  Generated 06/06/2020 10:44:03
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
#include        <SrcFile_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            SrcFile_task_body (
        void            *pData
    )
    {
        //SRCFILE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SRCFILE_DATA *     SrcFile_Alloc (
        void
    )
    {
        SRCFILE_DATA       *this;
        uint32_t        cbSize = sizeof(SRCFILE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SRCFILE_DATA *     SrcFile_New (
        void
    )
    {
        SRCFILE_DATA       *this;
        
        this = SrcFile_Alloc( );
        if (this) {
            this = SrcFile_Init(this);
        } 
        return this;
    }


    SRCFILE_DATA *  SrcFile_NewFromAStr(
        PATH_DATA       *pFilePath,
        ASTR_DATA       *pStr,        // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        SRCFILE_DATA    *this = OBJ_NIL;
        ERESULT         eRc;
        TOKEN_DATA      *pToken;

        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        this = SrcFile_New( );
        if (this) {
            eRc =   TextIn_SetupAStr(
                                   (TEXTIN_DATA *)this,
                                   pFilePath,
                                   pStr,
                                   fileIndex,
                                   tabSize
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }

            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = Token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            SrcFile_Preload(this);
        }

        return this;
    }


    SRCFILE_DATA *  SrcFile_NewFromFile(
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;
        SRCFILE_DATA    *this = OBJ_NIL;
        TOKEN_DATA      *pToken;

        this = SrcFile_New( );
        if (this) {
            eRc = TextIn_SetupFile((TEXTIN_DATA *)this, OBJ_NIL,
                                   pFile, fileIndex, tabSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }

            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = Token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            SrcFile_Preload(this);
        }

        return this;
    }


    SRCFILE_DATA *  SrcFile_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        ERESULT         eRc;
        SRCFILE_DATA    *this = OBJ_NIL;
        TOKEN_DATA      *pToken;
        PATH_DATA       *pWrk = OBJ_NIL;

        pWrk = Path_Copy(pFilePath);
        if (OBJ_NIL == pWrk) {
            return OBJ_NIL;
        }
        Path_Clean(pWrk);

        this = SrcFile_New( );
        if (this) {
            eRc = TextIn_SetupPath((TEXTIN_DATA *)this, pWrk, fileIndex, tabSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pWrk);
                obj_Release(this);
                return OBJ_NIL;
            }
            obj_Release(pWrk);
            pWrk = OBJ_NIL;

            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = Token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            SrcFile_Preload(this);
        }

        return this;
    }


    SRCFILE_DATA *  SrcFile_NewFromStrA(
        PATH_DATA       *pFilePath,
        const
        char            *pStrA,         // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        SRCFILE_DATA    *this = OBJ_NIL;
        ERESULT         eRc;
        TOKEN_DATA      *pToken;

        if (NULL == pStrA) {
            return OBJ_NIL;
        }

        this = SrcFile_New( );
        if (this) {
            eRc =   TextIn_SetupStrA(
                                   (TEXTIN_DATA *)this,
                                   pFilePath,
                                   pStrA,
                                   fileIndex,
                                   tabSize
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }

            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = Token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            SrcFile_Preload(this);
        }

        return this;
    }


    SRCFILE_DATA *  SrcFile_NewFromW32Str(
        PATH_DATA       *pFilePath,
        W32STR_DATA     *pStr,        // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        SRCFILE_DATA    *this = OBJ_NIL;
        ERESULT         eRc;
        TOKEN_DATA      *pToken;

        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        this = SrcFile_New( );
        if (this) {
            eRc =   TextIn_SetupW32Str(
                                   (TEXTIN_DATA *)this,
                                   pFilePath,
                                   pStr,
                                   fileIndex,
                                   tabSize
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }

            obj_setSize(&this->curchr, sizeof(TOKEN_DATA));
            pToken = Token_Init(&this->curchr);
            if (OBJ_NIL == pToken) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            SrcFile_Preload(this);
        }

        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                    F i l e  I n d e x
    //---------------------------------------------------------------

    uint16_t        SrcFile_getFileIndex (
        SRCFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return TextIn_getFileIndex((TEXTIN_DATA *)this);
    }


    bool            SrcFile_setFileIndex (
        SRCFILE_DATA    *this,
        uint16_t        value
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = TextIn_setFileIndex((TEXTIN_DATA *)this, value);

        return fRc;
    }



    //---------------------------------------------------------------
    //          L o o k  A h e a d  I n t e r f a c e
    //---------------------------------------------------------------

    LA_INTERFACE *  SrcFile_getLaInterface (
        SRCFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LA_INTERFACE *)this;
    }


    //---------------------------------------------------------------
    //                         P a t h
    //---------------------------------------------------------------

    PATH_DATA *     SrcFile_getPath (
        SRCFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return TextIn_getPath((TEXTIN_DATA *)this);
    }


    bool            SrcFile_setPath (
        SRCFILE_DATA    *this,
        PATH_DATA       *pValue
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = TextIn_setPath((TEXTIN_DATA *)this, pValue);

        return fRc;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        SrcFile_getPriority (
        SRCFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SrcFile_setPriority (
        SRCFILE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //              L o o k  A h e a d  Q u e u e
    //---------------------------------------------------------------

    uint16_t        SrcFile_getQueueSize (
        SRCFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->sizeInputs;
    }


    bool            SrcFile_setQueueSize (
        SRCFILE_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->sizeInputs = value;

        return true;
    }



    //---------------------------------------------------------------
    //                  R e m o v e  N L s
    //---------------------------------------------------------------

    bool            SrcFile_getRemoveNLs (
        SRCFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return TextIn_getRemoveNLs((TEXTIN_DATA *)this);
    }


    bool            SrcFile_setRemoveNLs (
        SRCFILE_DATA    *this,
        bool            fValue
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = TextIn_setRemoveNLs((TEXTIN_DATA *)this, fValue);

        return fRc;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        SrcFile_getSize (
        SRCFILE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------

#ifdef XYZZY
    ASTR_DATA * SrcFile_getStr (
        SRCFILE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        SrcFile_setStr (
        SRCFILE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
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
#endif
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SrcFile_getSuperVtbl (
        SRCFILE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      T a b  S i z e
    //---------------------------------------------------------------

    uint16_t        SrcFile_getTabSize (
        SRCFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return TextIn_getTabSize((TEXTIN_DATA *)this);
    }


    bool            SrcFile_setTabSize (
        SRCFILE_DATA    *this,
        uint16_t        value
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = TextIn_setTabSize((TEXTIN_DATA *)this, value);

        return fRc;
    }



    //---------------------------------------------------------------
    //                      T e x t I n
    //---------------------------------------------------------------

    TEXTIN_DATA *   SrcFile_getTextIn (
        SRCFILE_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (TEXTIN_DATA *)this;
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
        ERESULT eRc = SrcFile_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SRCFILE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SrcFile_Assign (
        SRCFILE_DATA       *this,
        SRCFILE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SrcFile_Validate(pOther)) {
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
    //                 C h e c k  P o i n t
    //---------------------------------------------------------------

    /*!
     Save the current token for a checkpoint which will allow a restart
     to begin again at this point.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   Mulitple checkpoints can be called, but only the last
                one will be recognized by SrcFile_Restart().
     */
    ERESULT         SrcFile_CheckPoint (
        SRCFILE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        idx;
        TOKEN_DATA      *pToken = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        idx = this->curInputs % this->sizeInputs;
        pToken = &this->pInputs[idx];
        memmove(&this->chkData, &pToken->data, sizeof(TOKEN_FIELDS));

        // Return to caller.
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
    int             SrcFile_Compare (
        SRCFILE_DATA    *this,
        SRCFILE_DATA    *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SrcFile_Validate(pOther)) {
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
        SrcFile      *pCopy = SrcFile_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCFILE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCFILE_DATA *     SrcFile_Copy (
        SRCFILE_DATA       *this
    )
    {
        SRCFILE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SRCFILE_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SrcFile_New( );
        if (pOther) {
            eRc = SrcFile_Assign(this, pOther);
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

    void            SrcFile_Dealloc (
        OBJ_ID          objId
    )
    {
        SRCFILE_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SRCFILE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pInputs) {
            mem_Free(this->pInputs);
            this->pInputs = OBJ_NIL;
            this->sizeInputs = 0;
            this->curInputs = 0;
        }

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
        SrcFile      *pDeepCopy = SrcFile_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SRCFILE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SRCFILE_DATA *     SrcFile_DeepyCopy (
        SRCFILE_DATA       *this
    )
    {
        SRCFILE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SrcFile_New( );
        if (pOther) {
            eRc = SrcFile_Assign(this, pOther);
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
    ERESULT         SrcFile_Disable (
        SRCFILE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
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
    ERESULT         SrcFile_Enable (
        SRCFILE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
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

    SRCFILE_DATA *   SrcFile_Init (
        SRCFILE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SRCFILE_DATA);
        //ERESULT         eRc;
        //uint16_t        i;
        
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

        this = (OBJ_ID)TextIn_Init((TEXTIN_DATA *)this);        // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SrcFile_Vtbl);
        
        this->sizeInputs = 4;
        this->pInputs = mem_Calloc(this->sizeInputs, sizeof(TOKEN_DATA));
        if (NULL == this->pInputs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SrcFile::sizeof(SRCFILE_DATA) = %lu\n", 
                sizeof(SRCFILE_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SRCFILE_DATA));
#endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------

    TOKEN_DATA *    SrcFile_InputAdvance (
        SRCFILE_DATA    *this,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        TOKEN_DATA      *pToken = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFile_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            eRc = SrcFile_InputNextChar(this);
        }

        pToken = &this->pInputs[this->curInputs];

        // Return to caller.
        return pToken;
    }


    int32_t         SrcFile_InputAdvance2 (
        SRCFILE_DATA    *this,
        uint16_t        num,
        TOKEN_DATA      **ppToken
    )
    {
        uint32_t        i;
        TOKEN_DATA      *pToken = OBJ_NIL;
        ERESULT         eRc;
        int32_t         class = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFile_Validate(this) ) {
            DEBUG_BREAK();
            return class;
        }
#endif

        // Shift inputs.
        for (i=0; i<num; ++i) {
            eRc = SrcFile_InputNextChar(this);
        }

        pToken = &this->pInputs[this->curInputs];
        if (pToken) {
            class = Token_getClass(pToken);
        }

        // Return to caller.
        if (ppToken)
            *ppToken = pToken;
        return class;
    }



    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------

    TOKEN_DATA *    SrcFile_InputLookAhead (
        SRCFILE_DATA    *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate( this )) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (num > this->sizeInputs) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        idx = (this->curInputs + num - 1) % this->sizeInputs;
        pToken = &this->pInputs[idx];

        // Return to caller.
        return pToken;
    }


    int32_t         SrcFile_InputLookAhead2 (
        SRCFILE_DATA    *this,
        uint16_t        num,
        TOKEN_DATA      **ppToken
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken = OBJ_NIL;
        int32_t         class = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate( this )) {
            DEBUG_BREAK();
            return class;
        }
        if (num > this->sizeInputs) {
            DEBUG_BREAK();
            return class;
        }
#endif

        idx = (this->curInputs + num - 1) % this->sizeInputs;
        pToken = &this->pInputs[idx];
        if (pToken) {
            class = Token_getClass(pToken);
        }

        // Return to caller.
        if (ppToken)
            *ppToken = pToken;
        return class;
    }



    //--------------------------------------------------------------
    //                  I n p u t  N e x t  C h a r
    //--------------------------------------------------------------

    ERESULT             SrcFile_InputNextChar(
        SRCFILE_DATA        *this
    )
    {
        ERESULT             eRc;
        TOKEN_DATA          *pToken;
        TOKEN_FIELDS        *pTok;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !SrcFile_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pTok = TextIn_NextToken((TEXTIN_DATA *)this);
        if (NULL == pTok) {
            return ERESULT_DATA_MISSING;
        }

        // Add the next char to the queue.
        pToken = &this->pInputs[this->curInputs];
        this->fInit = 1;
        Token_Init(pToken);
        eRc = Token_SetupFields(pToken, pTok);
        this->curInputs = (this->curInputs + 1) % this->sizeInputs;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       P r e l o a d
    //---------------------------------------------------------------
    
    ERESULT         SrcFile_Preload (
        SRCFILE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->curInputs = 0;
        for (i=0; i<this->sizeInputs; ++i) {
            eRc = SrcFile_InputNextChar(this);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
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
        void        *pMethod = SrcFile_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SrcFile", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SrcFile_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SRCFILE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SRCFILE_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SrcFile_Class();
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
                            return SrcFile_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SrcFile_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SRCFILE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return SrcFile_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return SrcFile_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SrcFile_ToDebugString;
                        }
#ifdef  SRCFILE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return SrcFile_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SrcFile_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SrcFile_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCFILE_JSON_SUPPORT
                if (pData == SrcFile_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                         R e s t a r t
    //---------------------------------------------------------------

    /*!
     Restart the token stream at the previous checkpoint.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SrcFile_Restart (
        SRCFILE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = TextIn_SeekOffset(SrcFile_getTextIn(this), this->chkData.src.offset);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }

        // Prime the inputs.
        SrcFile_Preload(this);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      S k i p  T o E O L
    //---------------------------------------------------------------

    /*!
     Advance the input the number of characters needed to get the
     current Input Char to be EOL.
     @param     this    object pointer
     @return    If successful, ERROR_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SrcFile_SkipToEOL (
        SRCFILE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TOKEN_DATA      *pToken = OBJ_NIL;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (SrcFile_getRemoveNLs(this))
            return ERESULT_INVALID_REQUEST;

        for (;;) {
            pToken = &this->pInputs[this->curInputs];
            chr = Token_getChrW32(pToken);
            if (chr == '\n')
                break;
            eRc = SrcFile_InputNextChar(this);
            if (ERESULT_FAILED(eRc))
                break;
        }

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
        ASTR_DATA      *pDesc = SrcFile_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcFile_ToDebugString (
        SRCFILE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SrcFile_Validate(this)) {
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
                    "{%p(%s) sizeInputs=%d curInputs=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    this->sizeInputs,
                    this->curInputs,
                    obj_getRetainCount(this)
            );

        {
            TOKEN_FIELDS        *pTok = &this->curchr.data;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "=> Cur: len:%d, type:%d, cls:%d, chr:%d('%c') fileIndex:%d, "
                        "lineNo:%d, colNo:%d, offset:%lld\n",
                        pTok->len,
                        pTok->type,
                        pTok->cls,
                        pTok->w32chr[0],
                        ((pTok->w32chr[0] >= ' ') && (pTok->w32chr[0] <= 0x7F) ?
                                    pTok->w32chr[0]: ' '),
                        pTok->src.fileIndex,
                        pTok->src.lineNo,
                        pTok->src.colNo,
                        pTok->src.offset
                );
        }

        for (i=0; i<this->sizeInputs; i++) {
            TOKEN_FIELDS        *pTok = &this->pInputs[i].data;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "=> %3d: len:%d, type:%d, cls:%d, chr:%d('%c') fileIndex:%d, "
                        "lineNo:%d, colNo:%d, offset:%lld\n",
                        i,
                        pTok->len,
                        pTok->type,
                        pTok->cls,
                        pTok->w32chr[0],
                        ((pTok->w32chr[0] >= ' ') && (pTok->w32chr[0] <= 0x7F) ?
                                    pTok->w32chr[0]: ' '),
                        pTok->src.fileIndex,
                        pTok->src.lineNo,
                        pTok->src.colNo,
                        pTok->src.offset
                );
        }

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
    bool            SrcFile_Validate (
        SRCFILE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SRCFILE))
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


        if (!(obj_getSize(this) >= sizeof(SRCFILE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


