// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Ansi.c
 *  Generated 02/20/2022 17:28:22
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
#include        <Ansi_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>
#include        <fcntl.h>
#include        <unistd.h>
#include        <sys/ioctl.h>






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
    void            Ansi_task_body (
        void            *pData
    )
    {
        //ANSI_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ANSI_DATA *     Ansi_Alloc (
        void
    )
    {
        ANSI_DATA       *this;
        uint32_t        cbSize = sizeof(ANSI_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ANSI_DATA *     Ansi_New (
        void
    )
    {
        ANSI_DATA       *this;
        
        this = Ansi_Alloc( );
        if (this) {
            this = Ansi_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                            C o l s
    //---------------------------------------------------------------
    
    uint16_t        Ansi_getCols (
        ANSI_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cols;
    }

    

    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   ANSI_MSGS
    bool            Ansi_setMsgs (
        ANSI_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
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
    
    uint16_t        Ansi_getPriority (
        ANSI_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Ansi_setPriority (
        ANSI_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                            R o w s
    //---------------------------------------------------------------
    
    uint16_t        Ansi_getRows (
        ANSI_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->rows;
    }

    

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Ansi_getSize (
        ANSI_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Ansi_getStr (
        ANSI_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Ansi_setStr (
        ANSI_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
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
    
    ANSI_DATA *  Ansi_getSuper (
        ANSI_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (ANSI_DATA *)this;
    }

    
    OBJ_IUNKNOWN *  Ansi_getSuperVtbl (
        ANSI_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
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
        ERESULT eRc = Ansi_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another ANSI object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Ansi_Assign (
        ANSI_DATA       *this,
        ANSI_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Ansi_Validate(pOther)) {
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
    //                          C l e a r
    //---------------------------------------------------------------

    ERESULT         Ansi_ClearLine (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[2K");
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_ClearScreen (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[2J");
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_ClearToBeginOfLine (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[1K");
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_ClearToBottom (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[0J");
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_ClearToEndOfLine (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[0K");
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_ClearToTop (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[1J");
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          C o l o r
    //---------------------------------------------------------------

    ERESULT         Ansi_ColorSet (
        ANSI_DATA       *this,
        uint16_t        oolor,
        bool            fBright
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (fBright) {
            printf("\x1b[%d1m", oolor);
        } else {
            printf("\x1b[%dm", oolor);
        }
        
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
    int             Ansi_Compare (
        ANSI_DATA     *this,
        ANSI_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Ansi_Validate(pOther)) {
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
        Ansi      *pCopy = Ansi_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ANSI object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ANSI_DATA *     Ansi_Copy (
        ANSI_DATA       *this
    )
    {
        ANSI_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef ANSI_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Ansi_New( );
        if (pOther) {
            eRc = Ansi_Assign(this, pOther);
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
    //                      C u r s o r
    //---------------------------------------------------------------

    ERESULT         Ansi_CursorDown (
        ANSI_DATA       *this,
        uint16_t        rows
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[%dB", rows);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_CursorLeft (
        ANSI_DATA       *this,
        uint16_t        cols
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[%dD", cols);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_CursorMove (
        ANSI_DATA       *this,
        uint16_t        y,                          // Row
        uint16_t        x                           // Column
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[%d;%df", y, x);;
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_CursorRight (
        ANSI_DATA       *this,
        uint16_t        cols
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[%dC", cols);
        
        // Return to caller.
        return eRc;
    }


    ERESULT         Ansi_CursorUp (
        ANSI_DATA       *this,
        uint16_t        rows
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        printf("\x1b[%dA", rows);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Ansi_Dealloc (
        OBJ_ID          objId
    )
    {
        ANSI_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ANSI_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Ansi_setStr(this, OBJ_NIL);

        tcsetattr(STDIN_FILENO, TCSANOW, &this->keyboardAttrsInitial);
        
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
        Ansi      *pDeepCopy = Ansi_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ANSI object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ANSI_DATA *     Ansi_DeepCopy (
        ANSI_DATA       *this
    )
    {
        ANSI_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Ansi_New( );
        if (pOther) {
            eRc = Ansi_Assign(this, pOther);
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
    ERESULT         Ansi_Disable (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
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
    ERESULT         Ansi_Enable (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   ANSI_MSGS
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
    //                          I n i t
    //---------------------------------------------------------------

    ANSI_DATA *   Ansi_Init (
        ANSI_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ANSI_DATA);
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

        //this = (OBJ_ID)Ansi_Init((ANSI_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Ansi_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ANSI);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Ansi_Vtbl);
#ifdef  ANSI_JSON_SUPPORT
        JsonIn_RegisterClass(Ansi_Class());
#endif
        
        tcgetattr(STDIN_FILENO, &this->keyboardAttrsInitial);
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
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Ansi::sizeof(ANSI_DATA) = %lu\n", 
                sizeof(ANSI_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(ANSI_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Ansi_IsEnabled (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
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
    //                         K e y b o a r d
    //---------------------------------------------------------------

    ERESULT         Ansi_KeyboardMode (
        ANSI_DATA       *this,
        bool            fEcho,
        bool            fRaw,
        bool            fBreak
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;
        struct termios  tio;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = tcgetattr(STDIN_FILENO, &tio);
        if (0 == iRc) {
            if (fEcho)
                tio.c_iflag |= ECHO;
            else
                tio.c_iflag &= ~ECHO;
            if (fRaw)
                tio.c_iflag |= ICANON;
            else
                tio.c_iflag &= ~ICANON;
            if (fBreak)
                tio.c_iflag |= ISIG;
            else
                tio.c_iflag &= ~ISIG;
            iRc = tcsetattr(STDIN_FILENO, TCSANOW, &tio);
            if (0 == iRc)
                ;
            else {
                eRc = ERESULT_FAILURE;
            }
        } else {
            eRc = ERESULT_FAILURE;
        }

        // Return to caller.
        return eRc;
    }

    
    int             Ansi_KeyboardGet (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        int             ch;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        ch = getchar();
        
        // Return to caller.
        return ch;
    }

    
    bool            Ansi_KeyboardHit (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        struct termios  tioNew;
        struct termios  tioOld;
        int             iRc;
        int             ch;
        int             fcntlOld;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = tcgetattr(STDIN_FILENO, &tioNew);
        if (0 == iRc)
            ;
        else {
            return ERESULT_FAILURE;
        }
        tioOld = tioNew;
        tioNew.c_lflag &= ~(ICANON | ECHO);
        iRc = tcsetattr(STDIN_FILENO, TCSANOW, &tioNew);

        fcntlOld = fcntl(STDIN_FILENO, F_GETFL, 0);
        iRc = fcntl(STDIN_FILENO, F_SETFL, fcntlOld | O_NONBLOCK);

        ch = getchar();
        
        iRc = tcsetattr(STDIN_FILENO, TCSANOW, &tioOld);
        fcntl(STDIN_FILENO, F_SETFL, fcntlOld);
        
        if (ch == EOF) {
            return false;
        }
        
        // Return to caller.
        ungetc(ch, stdin);
        return true;
    }

    
    bool            Ansi_KeyboardIsBreak (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        struct termios  tio;
        int             iRc;
        bool            fRc = false;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = tcgetattr(STDIN_FILENO, &tio);
        if (0 == iRc) {
            if (tio.c_iflag & ISIG)
                fRc = true;;
        }

        // Return to caller.
        return fRc;
    }

    
    bool            Ansi_KeyboardIsEcho (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        struct termios  tio;
        int             iRc;
        bool            fRc = false;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = tcgetattr(STDIN_FILENO, &tio);
        if (0 == iRc) {
            if (tio.c_iflag & ECHO)
                fRc = true;;
        }

        // Return to caller.
        return fRc;
    }

    
    bool            Ansi_KeyboardIsRaw (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        struct termios  tio;
        int             iRc;
        bool            fRc = false;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = tcgetattr(STDIN_FILENO, &tio);
        if (0 == iRc) {
            if (tio.c_iflag & ICANON)
                fRc = true;;
        }

        // Return to caller.
        return fRc;
    }

    
    bool            Ansi_KeyboardIsTTY (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        struct termios  tio;
        int             iRc;
        bool            fRc = false;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = tcgetattr(STDIN_FILENO, &tio);
        if (0 == iRc) {
            fRc = true;;
        }

        // Return to caller.
        return fRc;
    }

    
    bool            Ansi_KeyboardIsUTF8 (
        ANSI_DATA       *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        struct termios  tio;
        int             iRc;
        bool            fRc = false;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = tcgetattr(STDIN_FILENO, &tio);
        if (0 == iRc) {
            if (tio.c_iflag & IUTF8)
                fRc = true;;
        }

        // Return to caller.
        return fRc;
    }

    
    ERESULT         Ansi_KeyboardReset (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        tcsetattr(STDIN_FILENO, TCSANOW, &this->keyboardAttrsInitial);

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
        void        *pMethod = Ansi_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Ansi", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Ansi_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ANSI_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(ANSI_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Ansi_Class();
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
                            return Ansi_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Ansi_Enable;
                        }
                        break;

                    case 'P':
#ifdef  ANSI_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Ansi_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Ansi_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Ansi_ToDebugString;
                        }
#ifdef  ANSI_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Ansi_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Ansi_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Ansi_ToDebugString)
                    return "ToDebugString";
#ifdef  ANSI_JSON_SUPPORT
                if (pData == Ansi_ToJson)
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
        ASTR_DATA      *pDesc = Ansi_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Ansi_ToDebugString (
        ANSI_DATA      *this,
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
        if (!Ansi_Validate(this)) {
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
                    Ansi_getSize(this),
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Ansi_Validate (
        ANSI_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_ANSI))
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


        if (!(obj_getSize(this) >= sizeof(ANSI_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Ansi_WinSize (
        ANSI_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        struct winsize  ws;
        int             iRc;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ANSI_SINGLETON
        if (OBJ_NIL == this) {
            this = Ansi_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Ansi_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        iRc = ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
        if (0 == iRc) {
            this->cols = ws.ws_col;
            this->rows = ws.ws_row;
        }

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }




    
#ifdef  __cplusplus
}
#endif


