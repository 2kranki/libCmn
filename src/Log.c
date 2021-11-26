// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Log.c
 *  Generated 11/24/2021 08:34:30
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
#include        <Log_internal.h>
#include        <Appl.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






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

    void            Log_WriteMsg (
        LOG_DATA        *this,
        uint32_t        cBuffer,
        const
        void            *pBuffer
    )
    {
        ERESULT         eRc;

        if (this && this->pLog) {
            eRc = FileIO_Write(this->pLog, cBuffer, pBuffer);
        } else {
            fwrite(pBuffer, cBuffer, 1, stderr);
        }

    }





    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LOG_DATA *      Log_Alloc (
        void
    )
    {
        LOG_DATA        *this;
        uint32_t        cbSize = sizeof(LOG_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LOG_DATA *      Log_New (
        void
    )
    {
        LOG_DATA       *this;
        
        this = Log_Alloc( );
        if (this) {
            this = Log_Init(this);
        } 
        return this;
    }


    LOG_DATA *      Log_NewWithPath (
        PATH_DATA       *pPath
    )
    {
        LOG_DATA        *this;
        //ERESULT         eRc;

        this = Log_New( );
        if (this) {
            this->pLog = FileIO_NewCreate(pPath, false);
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //              A p p l i c a t i o n  I n t e r f a c e
    //---------------------------------------------------------------

    OBJ_ID          Log_getAppl (
        LOG_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pAppl;
    }


    bool            Log_setAppl (
        LOG_DATA        *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        /*** Not Owned
        obj_Retain(pValue);
        if (this->pAppl) {
            obj_Release(this->pAppl);
        }
        ***/
        this->pAppl = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                       L o g  F i l e
    //---------------------------------------------------------------

    FILEIO_DATA *   Log_getLog (
        LOG_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLog;
    }


    bool            Log_setLog (
        LOG_DATA        *this,
        FILEIO_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pLog) {
            obj_Release(this->pLog);
        }
        this->pLog = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                      M e s s a g e s
    //---------------------------------------------------------------

#ifdef   LOG_MSGS
    bool            Log_setMsgs (
        LOG_DATA    *this,
        void            (*pMsgInfo)(OBJ_ID, const char *, ...),
        void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...),
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
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
    
    uint16_t        Log_getPriority (
        LOG_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Log_setPriority (
        LOG_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
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
    
    uint32_t        Log_getSize (
        LOG_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Log_getStr (
        LOG_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Log_setStr (
        LOG_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  Log_getSuperVtbl (
        LOG_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  
    LOG_DATA *  Log_getSuper (
        LOG_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (LOG_DATA *)this;
    }

    

    //---------------------------------------------------------------
    //                       W a r n i n g s
    //---------------------------------------------------------------

    uint16_t        Log_getWarnMax (
        LOG_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->maxWarn;
    }


    bool            Log_setWarnMax (
        LOG_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->maxWarn = value;

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
        ERESULT eRc = Log_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LOG object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Log_Assign (
        LOG_DATA       *this,
        LOG_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Log_Validate(pOther)) {
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
    //                      C l o s e
    //---------------------------------------------------------------

    /*!
     Close the log file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Log_Close (
        LOG_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pLog && FileIO_IsOpen(this->pLog)) {
            eRc = FileIO_Close(this->pLog, false);
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
    int             Log_Compare (
        LOG_DATA     *this,
        LOG_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Log_Validate(pOther)) {
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
        Log      *pCopy = Log_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LOG object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LOG_DATA *     Log_Copy (
        LOG_DATA       *this
    )
    {
        LOG_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LOG_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Log_New( );
        if (pOther) {
            eRc = Log_Assign(this, pOther);
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
    //                       C r e a t e
    //---------------------------------------------------------------

    /*!
     Create a log file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Log_Create (
        LOG_DATA        *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (this->pLog) {
            FileIO_Close(this->pLog, false);
        }

        if (this->pLog) {
            eRc = FileIO_Create(this->pLog, pPath, false);
        } else {
            this->pLog = FileIO_NewCreate(pPath, false);
            if (this->pLog)
                eRc = ERESULT_SUCCESS;
            else
                eRc = ERESULT_FAILURE;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Log_Dealloc (
        OBJ_ID          objId
    )
    {
        LOG_DATA   *this = objId;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LOG_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pLog && FileIO_IsOpen(this->pLog)) {
            eRc = FileIO_Close(this->pLog, false);
        }

        Log_setAppl(this, OBJ_NIL);
        Log_setLog(this, OBJ_NIL);
        Log_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                  D e b u g  M e s s a g e s
    //---------------------------------------------------------------

    void            Log_Debug(
        LOG_DATA        *this,
        const
        char            *pFormatA,
        ...
    )
    {
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStrA = NULL;
        APPL_VTBL       *pAppl = OBJ_NIL;

        // Do initialization.
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif
        if (this->pAppl) {
            pAppl = (APPL_VTBL *)obj_getVtbl(this->pAppl);
        } else {
            Log_Fatal(this, "Missing Application Interface!\n");
        }

        if (!pAppl->pGetQuiet(this->pAppl) && pAppl->pGetDebug(this->pAppl)) {
            va_start( arg_ptr, pFormatA );
            str[0] = '\0';
            size = vsnprintf(str, sizeof(str), pFormatA, arg_ptr);
            va_end( arg_ptr );
            pStrA = str;
            if (size >= sizeof(str)) {
                ++size;
                pStrA = (char *)mem_Malloc(size);
                if( pStrA == NULL ) {
                    // return ERESULT_INSUFFICIENT_MEMORY;
                    return;
                }
                va_start( arg_ptr, pFormatA );
                size = vsnprintf(pStrA, size, pFormatA, arg_ptr);
                va_end( arg_ptr );
            }
            Log_WriteMsg(this, 8, "DEBUG - ");
            Log_WriteMsg(this, size, pStrA);
            if (!(pStrA == str)) {
                mem_Free( pStrA );
                pStrA = NULL;
            }
        }

    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Log      *pDeepCopy = Log_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LOG object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LOG_DATA *     Log_DeepCopy (
        LOG_DATA       *this
    )
    {
        LOG_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Log_New( );
        if (pOther) {
            eRc = Log_Assign(this, pOther);
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
    ERESULT         Log_Disable (
        LOG_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
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
    ERESULT         Log_Enable (
        LOG_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   LOG_MSGS
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
    //                    F a t a l  M e s s a g e s
    //---------------------------------------------------------------

    void            Log_Fatal(
        LOG_DATA        *this,
        const
        char            *pFormatA,
        ...
    )
    {
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStrA = NULL;
        APPL_VTBL       *pAppl = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (this) {
            if (!Log_Validate(this)) {
                DEBUG_BREAK();
                //return ERESULT_INVALID_OBJECT;
                return;
            }
        }
#endif
        if (this && this->pAppl) {
            pAppl = (APPL_VTBL *)obj_getVtbl(this->pAppl);
        }

        va_start( arg_ptr, pFormatA );
        str[0] = '\0';
        size = vsnprintf(str, sizeof(str), pFormatA, arg_ptr);
        va_end( arg_ptr );
        pStrA = str;
        if (size >= sizeof(str)) {
            ++size;
            pStrA = (char *)mem_Malloc(size);
            if( pStrA == NULL ) {
                // return ERESULT_INSUFFICIENT_MEMORY;
                return;
            }
            va_start( arg_ptr, pFormatA );
            size = vsnprintf( pStrA, size, pFormatA, arg_ptr );
            va_end( arg_ptr );
        }
        Log_WriteMsg(this, 8, "FATAL - ");
        Log_WriteMsg(this, size, pStrA);
        if (!(pStrA == str)) {
            mem_Free( pStrA );
            pStrA = NULL;
        }

        DEBUG_BREAK();
        if (pAppl) {
            pAppl->pExit(this->pAppl, 8);
        } else {
            exit(8);
        }
    }



    //---------------------------------------------------------------
    //           I n f o r m a t i o n a l  M e s s a g e s
    //---------------------------------------------------------------

    void            Log_Info(
        LOG_DATA        *this,
        const
        char            *pFormatA,
        ...
    )
    {
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStrA = NULL;
        APPL_VTBL       *pAppl = OBJ_NIL;

        // Do initialization.
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif
        if (this->pAppl) {
            pAppl = (APPL_VTBL *)obj_getVtbl(this->pAppl);
        } else {
            Log_Fatal(this, "Missing Application Interface!\n");
        }

        if (!((APPL_VTBL *)obj_getVtbl(this->pAppl))->pGetQuiet(this->pAppl)) {
            va_start( arg_ptr, pFormatA );
            str[0] = '\0';
            size = vsnprintf(str, sizeof(str), pFormatA, arg_ptr);
            va_end( arg_ptr );
            pStrA = str;
            if (size >= sizeof(str)) {
                ++size;
                pStrA = (char *)mem_Malloc(size);
                if( pStrA == NULL ) {
                    // return ERESULT_INSUFFICIENT_MEMORY;
                    return;
                }
                va_start( arg_ptr, pFormatA );
                size = vsnprintf(pStrA, size, pFormatA, arg_ptr);
                va_end( arg_ptr );
            }
            Log_WriteMsg(this, 7, "INFO - ");
            Log_WriteMsg(this, size, pStrA);
            if (!(pStrA == str)) {
                mem_Free( pStrA );
                pStrA = NULL;
            }
        }

    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LOG_DATA *   Log_Init (
        LOG_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LOG_DATA);
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

        //this = (OBJ_ID)Log_Init((LOG_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Log_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LOG);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Log_Vtbl);
#ifdef  LOG_JSON_SUPPORT
        JsonIn_RegisterClass(Log_Class());
#endif

        this->maxWarn = 50;
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
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Log::sizeof(LOG_DATA) = %lu\n", 
                sizeof(LOG_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LOG_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Log_IsEnabled (
        LOG_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
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
        void        *pMethod = Log_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Log", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Log_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LOG_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LOG_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Log_Class();
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
                            return Log_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Log_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LOG_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Log_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Log_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Log_ToDebugString;
                        }
#ifdef  LOG_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Log_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Log_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Log_ToDebugString)
                    return "ToDebugString";
#ifdef  LOG_JSON_SUPPORT
                if (pData == Log_ToJson)
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
        ASTR_DATA      *pDesc = Log_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Log_ToDebugString (
        LOG_DATA      *this,
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
        if (!Log_Validate(this)) {
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
                    Log_getSize(this),
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
    bool            Log_Validate (
        LOG_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LOG))
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


        if (!(obj_getSize(this) >= sizeof(LOG_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                 W a r n i n g  M e s s a g e s
    //---------------------------------------------------------------

    void            Log_Warn(
        LOG_DATA        *this,
        uint16_t        iVerbose,
        const
        char            *pFormatA,
        ...
    )
    {
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStrA = NULL;
        APPL_VTBL       *pAppl = OBJ_NIL;

        // Do initialization.
#ifdef  LOG_SINGLETON
        if (OBJ_NIL == this) {
            this = Log_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Log_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif
        if (this->pAppl) {
            pAppl = (APPL_VTBL *)obj_getVtbl(this->pAppl);
        } else {
            Log_Fatal(this, "Missing Application Interface!\n");
        }

        if (!pAppl->pGetQuiet(this->pAppl)
            && (pAppl->pGetVerbose(this->pAppl) >= iVerbose)
        ) {
            va_start( arg_ptr, pFormatA );
            str[0] = '\0';
            size = vsnprintf(str, sizeof(str), pFormatA, arg_ptr);
            va_end( arg_ptr );
            pStrA = str;
            if (size >= sizeof(str)) {
                ++size;
                pStrA = (char *)mem_Malloc(size);
                if( pStrA == NULL ) {
                    // return ERESULT_INSUFFICIENT_MEMORY;
                    return;
                }
                va_start( arg_ptr, pFormatA );
                size = vsnprintf( pStrA, size, pFormatA, arg_ptr );
                va_end( arg_ptr );
            }
            Log_WriteMsg(this, 10, "WARNING - ");
            Log_WriteMsg(this, size, pStrA);
            if (!(pStrA == str)) {
                mem_Free( pStrA );
                pStrA = NULL;
            }
        }

        this->cWarn++;
        if (this->cWarn >= this->maxWarn) {
            Log_Fatal(this, "Too many warnings!\n");
        }

    }




    
#ifdef  __cplusplus
}
#endif


