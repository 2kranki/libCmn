// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Consumer.c
 *  Generated 05/04/2021 09:30:56
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
#include        <Consumer_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  S e r v i c e  E x e c u t i o n
    //---------------------------------------------------------------

    void            defaultTaskExec(
        void            *pData
    )
    {
        CONSUMER_DATA  *this = pData;
        void            *pMsg;
        uint32_t        msWaitTime;
        uint32_t        msCurrent;
#ifdef XYZZY
        enum TN_RCode   tn_rc;
#endif
        bool            fRc;

#ifdef XYZZY
        msCurrent = tn_sys_time_get();
        if (cbp->calcWait) {
            msWaitTime = (*cbp->calcWait)(cbp->calcWaitData,msCurrent);
        }
        else {
            msWaitTime = TN_WAIT_INFINITE;
        }
#endif

        // Wait for next message.
#ifdef XYZZY
        tn_rc = tn_queue_receive(
                        &cbp->dque,
                        (void *)&pMsg,
                        msWaitTime
                );

        if (TN_RC_TIMEOUT == tn_rc) {
            if (cbp->timedOut) {
                (*cbp->timedOut)(cbp->timedOutData);
            }
        }
        else if (TN_RC_OK == tn_rc) {
            do {

                // Process the message if needed.
                if( cbp->fSkip ) {
                    ++cbp->numDiscard;
                }
                else {
                    if( cbp->pSrvcRtn ) {
                        fRc = (*cbp->pSrvcRtn)(cbp->pSrvcData, canmsg_getEid(pMsg), pMsg);
                        if (fRc) {
                            ++cbp->numHandled;
                        }
                        else {
                            ++cbp->numDiscard;
                        }
                    }
                    else {
                        ++cbp->numDiscard;
                    }
                }

                // Free the message.
                tn_rc = tn_fmem_release( &cbp->fmem, (void *)pMsg );
                if (tn_rc == TN_RC_OK) {
                }
                else {
                    DEBUG_BREAK();
                }

                // Try another message if already present.
                tn_rc = tn_queue_receive(
                            &cbp->dque,
                            (void *)&pMsg,
                            0
                        );

            } while (TN_RC_OK == tn_rc);
        }
#endif


    }



    //---------------------------------------------------------------
    //              S i m p l e  T a s k  B o d y
    //---------------------------------------------------------------

    void            simpleTaskBody(
        void            *pData
    )
    {
        CONSUMER_DATA  *this = pData;
        void            *pMsg;
#ifdef XYZZY
        enum TN_RCode   tn_rc;
#endif
        bool            fRc;

#ifdef XYZZY
        // Wait for next message.
        tn_rc = tn_queue_receive(
                        &cbp->dque,
                        (void *)&pMsg,
                        cbp->msWaitTime
                );

        if (TN_RC_TIMEOUT == tn_rc) {
            if( cbp->pSrvcRtn ) {
                fRc = (*cbp->pSrvcRtn)(cbp->pSrvcData, 0, NULL);
            }
        }
        else if (TN_RC_OK == tn_rc) {
            do {

                // Process the message if needed.
                if( cbp->fSkip ) {
                    ++cbp->numDiscard;
                }
                else {
                    if( cbp->pSrvcRtn ) {
                        fRc = (*cbp->pSrvcRtn)(cbp->pSrvcData, canmsg_getEid(pMsg), pMsg);
                        if (fRc) {
                            ++cbp->numHandled;
                        }
                        else {
                            ++cbp->numDiscard;
                        }
                    }
                    else {
                        ++cbp->numDiscard;
                    }
                }

                // Free the message.
                tn_rc = tn_fmem_release( &cbp->fmem, (void *)pMsg );
                if (tn_rc == TN_RC_OK) {
                }
                else {
                    DEBUG_BREAK();
                }

                // Try another message if already present.
                tn_rc = tn_queue_receive(
                                         &cbp->dque,
                                         (void *)&pMsg,
                                         0
                                         );

            } while (TN_RC_OK == tn_rc);
        }
#endif

    }



    //---------------------------------------------------------------
    //              C o n s u m e r  T a s k  B o d y
    //---------------------------------------------------------------

    static
    void            Consumer_Task(
        void            *pObject
    )
    {
        CONSUMER_DATA  *this = pObject;

        if (OBJ_NIL == this)
            return;

        if (this->pTaskBody) {
            (*this->pTaskBody)(this->pTaskObj);
        }
        else {
            psxThread_Wait(100);
        }

    }






    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    CONSUMER_DATA *     Consumer_Alloc (
        void
    )
    {
        CONSUMER_DATA       *this;
        uint32_t        cbSize = sizeof(CONSUMER_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    CONSUMER_DATA *     Consumer_New (
        void
    )
    {
        CONSUMER_DATA       *this;
        
        this = Consumer_Alloc( );
        if (this) {
            this = Consumer_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //         C a l c  W a i t  T i m e  R o u t i n e
    //---------------------------------------------------------------

    bool            Consumer_setCalcWait(
        CONSUMER_DATA   *this,
        uint32_t        (*pFunction)(void *),
        OBJ_ID          *pData
        )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Consumer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        psxThread_setCalcWait(this->pThread, pFunction, pData);

        // Return to caller.
        return( true );
    }



    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------

    OBJ_ID          Consumer_getOther (
        CONSUMER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pOther;
    }


    bool            Consumer_setOther (
        CONSUMER_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pOther) {
            obj_Release(this->pOther);
        }
        this->pOther = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Consumer_getPriority (
        CONSUMER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Consumer_setPriority (
        CONSUMER_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                     Q u e u e
    //---------------------------------------------------------------

    OBJCB_DATA *    Consumer_getQueue (
        CONSUMER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pQueue;
    }


    bool            Consumer_setQueue (
        CONSUMER_DATA   *this,
        OBJCB_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pQueue) {
            obj_Release(this->pQueue);
        }
        this->pQueue = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  S e r v i c e  R o u t i n e
    //---------------------------------------------------------------

    bool            Consumer_setService(
        CONSUMER_DATA   *this,
        int             (*pService)(OBJ_ID, OBJ_ID),
        OBJ_ID          *pServiceObj            // Service Method's Object
        )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Consumer_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pService = pService;
        this->pServiceObj = pServiceObj;

        // Return to caller.
        return( true );
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Consumer_getSize (
        CONSUMER_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Consumer_getStr (
        CONSUMER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Consumer_setStr (
        CONSUMER_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  Consumer_getSuperVtbl (
        CONSUMER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                        T h r e a d
    //---------------------------------------------------------------

    PSXTHREAD_DATA * Consumer_getThread (
        CONSUMER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pThread;
    }


    bool            Consumer_setThread (
        CONSUMER_DATA   *this,
        PSXTHREAD_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pThread) {
            obj_Release(this->pThread);
        }
        this->pThread = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         W a i t
    //---------------------------------------------------------------

    uint32_t        Consumer_getWait (
        CONSUMER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return psxThread_getWait(this->pThread);
    }


    bool            Consumer_setWait (
        CONSUMER_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return psxThread_setWait(this->pThread, value);
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
        ERESULT eRc = Consumer_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another CONSUMER object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Consumer_Assign (
        CONSUMER_DATA       *this,
        CONSUMER_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Consumer_Validate(pOther)) {
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
    int             Consumer_Compare (
        CONSUMER_DATA     *this,
        CONSUMER_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Consumer_Validate(pOther)) {
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
        Consumer      *pCopy = Consumer_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CONSUMER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CONSUMER_DATA *     Consumer_Copy (
        CONSUMER_DATA       *this
    )
    {
        CONSUMER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef CONSUMER_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Consumer_New( );
        if (pOther) {
            eRc = Consumer_Assign(this, pOther);
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

    void            Consumer_Dealloc (
        OBJ_ID          objId
    )
    {
        CONSUMER_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((CONSUMER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Consumer_setOther(this, OBJ_NIL);
        Consumer_setQueue(this, OBJ_NIL);
        Consumer_setStr(this, OBJ_NIL);
        Consumer_setThread(this, OBJ_NIL);

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
        Consumer      *pDeepCopy = Consumer_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a CONSUMER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    CONSUMER_DATA *     Consumer_DeepyCopy (
        CONSUMER_DATA       *this
    )
    {
        CONSUMER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Consumer_New( );
        if (pOther) {
            eRc = Consumer_Assign(this, pOther);
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
    ERESULT         Consumer_Disable (
        CONSUMER_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
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
    ERESULT         Consumer_Enable (
        CONSUMER_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
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

    CONSUMER_DATA *   Consumer_Init (
        CONSUMER_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(CONSUMER_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_CONSUMER);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Consumer_Vtbl);
#ifdef  CONSUMER_JSON_SUPPORT
        JsonIn_RegisterClass(Consumer_Class());
#endif
        
        // Allocate the FIFO Queue.
        this->pQueue = ObjCb_NewWithSize(16);
        if (OBJ_NIL == this->pQueue) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        // Allocate the thread and set it up.
        this->pThread = psxThread_New((void *)Consumer_Task, this, 0);
        if (OBJ_NIL == this->pQueue) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Consumer::sizeof(CONSUMER_DATA) = %lu\n", 
                sizeof(CONSUMER_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(CONSUMER_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Consumer_IsEnabled (
        CONSUMER_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
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
        void        *pMethod = Consumer_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Consumer", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Consumer_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CONSUMER_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(CONSUMER_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Consumer_Class();
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
                            return Consumer_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Consumer_Enable;
                        }
                        break;

                    case 'P':
#ifdef  CONSUMER_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Consumer_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Consumer_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Consumer_ToDebugString;
                        }
#ifdef  CONSUMER_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Consumer_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Consumer_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Consumer_ToDebugString)
                    return "ToDebugString";
#ifdef  CONSUMER_JSON_SUPPORT
                if (pData == Consumer_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e n d
    //---------------------------------------------------------------

    ERESULT         Consumer_Send (
        CONSUMER_DATA   *this,
        OBJ_ID          pObj,
        bool            fWait           // Wait for queue to have an empty slot
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObj) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (!fWait && ObjCb_IsFull(this->pQueue)) {
            return ERESULT_BUFFER_FULL;
        }

        fRc = ObjCb_Put(this->pQueue, pObj);
        if (!fRc) {
            eRc = ERESULT_FAILURE;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     S e t u p
    //---------------------------------------------------------------

    /*!
     Set up the run-timne parameters.
     @param     this        object pointer
     @param     queueSize   Consumer FIFO Queue Size
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Consumer_Setup (
        CONSUMER_DATA   *this,
        uint16_t        queueSize,
        int             (*pService)(OBJ_ID, OBJ_ID),
        void            *pServiceObj        // 1st parameter for service routine

    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Consumer_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release prior objects.
        Consumer_setQueue(this, OBJ_NIL);
        Consumer_setThread(this, OBJ_NIL);

        // Allocate the FIFO Queue.
        if (0 == queueSize)
            queueSize = 16;
        this->pQueue = ObjCb_NewWithSize(queueSize);
        if (OBJ_NIL == this->pQueue) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // Allocate the thread and set it up.
        this->pService = pService;
        this->pServiceObj = pServiceObj;
        this->pThread = psxThread_New((void *)Consumer_Task, this, 0);
        if (OBJ_NIL == this->pQueue) {
            Consumer_setQueue(this, OBJ_NIL);
            return ERESULT_OUT_OF_MEMORY;
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
        ASTR_DATA      *pDesc = Consumer_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Consumer_ToDebugString (
        CONSUMER_DATA      *this,
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
        if (!Consumer_Validate(this)) {
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
                    Consumer_getSize(this),
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
    bool            Consumer_Validate (
        CONSUMER_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_CONSUMER))
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


        if (!(obj_getSize(this) >= sizeof(CONSUMER_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


