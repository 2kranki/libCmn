// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   psxThread.c
 *	Generated 02/11/2016 10:46:17
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
#include "psxThread_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    uint32_t __stdcall thread_task_body(
        void            *pData
    )
#else
    void *          thread_task_body(
        void            *pData
    )
#endif
    {
        PSXTHREAD_DATA  *this = pData;
        void            *pReturn = NULL;
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        int             iRc = 0;
#endif
       
#if defined(__MACOSX_ENV__)
        iRc = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
#endif
        this->state = PSXTHREAD_STATE_RUNNING;
        for (;;) {
            
            if( this->fPause ) {
                //psxSem_Post(this->pOwnerWait);
                psxMutex_Lock(this->pWorkerVars);
                this->state = PSXTHREAD_STATE_PAUSED;
                psxMutex_Unlock(this->pWorkerVars);
                psxSem_Wait(this->pWorkerWait);
                psxMutex_Lock(this->pWorkerVars);
                this->state = PSXTHREAD_STATE_RUNNING;
                psxMutex_Unlock(this->pWorkerVars);
            }
            
            if( this->fTerminate ) {
                this->state = PSXTHREAD_STATE_ENDING;
                break;
            }
            
            if (this->threadBody) {
                pReturn = (*this->threadBody)(this->threadData);
                if (this->fDone) {
                    this->threadBody = NULL;
                    this->threadData = OBJ_NIL;
                    this->fDone = false;
                }
            }
            else {
#if defined(__MACOSX_ENV__)
                usleep(100);            // Sleep for 100us
#endif
#if defined(__PIC32MX_TNEO_ENV__)
                tn_task_sleep(TN_WAIT_INFINITE);
#endif
            }
            
        }   // for (;;)
    
        this->state = PSXTHREAD_STATE_ENDED;
        psxSem_Post(this->pWorkerEnded);
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        return iRc;
#else
        return pReturn;
#endif
    }
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PSXTHREAD_DATA * psxThread_Alloc(
    )
    {
        PSXTHREAD_DATA  *this;
        uint32_t        cbSize = sizeof(PSXTHREAD_DATA);
        
        // Do initialization.
        
        if (sizeof(sig_atomic_t) < 4) {
            return OBJ_NIL;
        }
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    PSXTHREAD_DATA * psxThread_New(
        void            *(*startRoutine)(void *),
        void            *routineData,
        uint32_t        stackSize
    )
    {
        PSXTHREAD_DATA  *this;
        
        this = psxThread_Alloc(  );
        if (this) {
            this = psxThread_Init( this, startRoutine, routineData, stackSize );
        } 
        return( this );
    }


    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        psxThread_getErrno(
        PSXTHREAD_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->iErrno;
    }
    
    
    bool        psxThread_setErrno(
        PSXTHREAD_DATA	*this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->iErrno = value;
        
        return true;
    }


    
    bool        psxThread_getPause(
        PSXTHREAD_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->fPause;
    }
    
    
    bool        psxThread_setPause(
        PSXTHREAD_DATA	*this,
        bool        value
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->fPause = value;
        
        return true;
    }
    
    
    
    bool        psxThread_setRoutine(
        PSXTHREAD_DATA	*this,
        void            *(*startRoutine)(void *),
        void            *routineData
    )
    {
        
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->threadBody = startRoutine;
        this->threadData = routineData;
        
        return true;
    }
    
    
    
    uint32_t        psxThread_getStackSize(
        PSXTHREAD_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->stackSize;
    }



    uint32_t        psxThread_getState(
        PSXTHREAD_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->state;
    }
    
    
    
    bool        psxThread_getTerminate(
        PSXTHREAD_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->fTerminate;
    }
    
    
    bool        psxThread_setTerminate(
        PSXTHREAD_DATA	*this,
        bool        value
    )
    {
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->fTerminate = value;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          C a n c e l
    //---------------------------------------------------------------
    
    bool            psxThread_Cancel(
        PSXTHREAD_DATA  *this
    )
    {
        bool            fRc = false;
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (!((psxThread_getState(this) == PSXTHREAD_STATE_ENDED)
            || (psxThread_getState(this) == PSXTHREAD_STATE_ENDING))) {
#if defined(__MACOSX_ENV__)
            iRc = pthread_cancel(this->worker);
            if (iRc == 0) {
                fRc = true;
            }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
            tn_rc = tn_task_terminate( &this->worker );
            if (tn_rc == TN_RC_OK) {
                fRc = true;
            }
            else {
                DEBUG_BREAK();
            }
#endif
        }
        
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            psxThread_Dealloc(
        OBJ_ID          objId
    )
    {
        PSXTHREAD_DATA  *this = objId;
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->state == PSXTHREAD_STATE_UNKNOWN) {
        }
        else {
            if (this->state == PSXTHREAD_STATE_ENDED) {
            }
            else {
                psxThread_Stop(this);
                psxThread_Join(this, NULL);
            }
#if defined(__MACOSX_ENV__)
            if (this->state == PSXTHREAD_STATE_ENDED) {
            }
            else {
                // Cancel may not have an immediate effect.
                iRc = pthread_cancel(this->worker);
                if (iRc) {
                    // ESRCH(3) means that the thread has terminated prior
                    // to cancel being called.
                    DEBUG_BREAK();
                }
            }
#endif
        }
        if (this->pOwnerWait) {
            obj_Release(this->pOwnerWait);
            this->pOwnerWait = NULL;
        }
        
        if (this->pWorkerWait) {
            obj_Release(this->pWorkerWait);
            this->pWorkerWait = NULL;
        }
        
        if (this->pWorkerLock) {
            obj_Release(this->pWorkerLock);
            this->pWorkerLock = NULL;
        }
        
        if (this->pWorkerEnded) {
            obj_Release(this->pWorkerEnded);
            this->pWorkerEnded = NULL;
        }
        
        if (this->pWorkerVars) {
            obj_Release(this->pWorkerVars);
            this->pWorkerVars = NULL;
        }
        
        if (this->pStack) {
            mem_Free(this->pStack);
            this->pStack = NULL;
        }
        
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        if (this->m_hThread) {
            CloseHandle(this->m_hThread);
            this->m_hThread = NULL;
            this->m_ThreadID = 0;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tn_rc = tn_task_delete( &this->thread );
        if (tn_rc == TN_RC_OK) {
        }
        else {
            DEBUG_BREAK();
        }
#endif

        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PSXTHREAD_DATA *   psxThread_Init(
        PSXTHREAD_DATA  *this,
        void            *(*startRoutine)(void *),
        void            *routineData,
        uint32_t        stackSize       // in Words
    )
    {
        uint32_t        cbSize;
#if defined(__MACOSX_ENV__)
        //int             iRc;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (PSXTHREAD_DATA *)obj_Init( this, cbSize, OBJ_IDENT_PSXTHREAD );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_PSXTHREAD);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&psxThread_Vtbl);

        this->threadBody = startRoutine;
        this->threadData = routineData;
        this->stackSize  = stackSize;
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        this->m_hThread = NULL;
        this->m_ThreadID = 0;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        if (stackSize) {
            this->pStack = mem_Malloc(stackSize);
            if (this->pStack == NULL) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
#endif
        
        this->pWorkerVars = psxMutex_New();
        if (OBJ_NIL == this->pWorkerVars) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pWorkerEnded = psxSem_New(0, 0);
        if (OBJ_NIL == this->pWorkerEnded) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pWorkerLock = psxMutex_New();
        if (OBJ_NIL == this->pWorkerLock) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pOwnerWait = psxSem_New(0, 0);
        if (OBJ_NIL == this->pOwnerWait) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this->pWorkerWait = psxSem_New(0, 0);
        if (OBJ_NIL == this->pWorkerWait) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }


    //---------------------------------------------------------------
    //                       J o i n
    //---------------------------------------------------------------
    
    bool            psxThread_Join(
        PSXTHREAD_DATA		*this,
        void                **ppReturn
    )
    {
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (!obj_IsEnabled(this) || !(this->state == PSXTHREAD_STATE_RUNNING))
            return false;
        
#if defined(__MACOSX_ENV__)
        iRc = pthread_join(this->worker, ppReturn);
        if (0 == iRc) {
            return true;
        }
#endif
        
        // Return to caller.
        DEBUG_BREAK();
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a u s e
    //---------------------------------------------------------------
    
    bool            psxThread_Pause(
        PSXTHREAD_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->fPause) {
            return false;
        }
        this->fPause = true;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s t a r t
    //---------------------------------------------------------------
    
    bool            psxThread_Restart(
        PSXTHREAD_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->state == PSXTHREAD_STATE_PAUSED) {
            this->fPause = false;
            psxSem_Post(this->pWorkerWait);
        }

        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S l e e p
    //---------------------------------------------------------------
    
    bool        psxThread_Sleep(
        PSXTHREAD_DATA  *this,
        uint32_t        msTime              // Time in ms
    )
    {
#if defined(__MACOSX_ENV__)
        struct timespec req;
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
        int             iRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        if(msTime > 999) {
            req.tv_sec = (int)(msTime / 1000);  /* Must be Non-Negative */
            req.tv_nsec = (msTime - ((long)req.tv_sec * 1000)) * 1000000;
                                                /* Must be in range of 0 to 999999999 */
        }
        else {
            req.tv_sec = 0;                    /* Must be Non-Negative */
            req.tv_nsec = msTime * 1000000;    /* Must be in range of 0 to 999999999 */
        }   
        
        iRc = nanosleep(&req, NULL);
        if (iRc == 0) {
            return true;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_task_sleep(msTime);
        if (tnRc == TN_RC_OK) {
            return true;
        }
#endif
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S t a r t
    //---------------------------------------------------------------
    
    bool            psxThread_Start(
        PSXTHREAD_DATA	*this
    )
    {
        bool            fRc = false;
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tn_rc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Create the thread and get it running.
        this->state = PSXTHREAD_STATE_STARTING;
#if defined(__MACOSX_ENV__)
        iRc = pthread_create(&this->worker, NULL, &thread_task_body, this);
        if (iRc == 0) {
            fRc = true;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        this->m_hThread =   CreateThread(
                                    NULL,               // default security attributes
                                    0,                  // use default stack size
                                    thread_task_body,   // thread function name
                                    this,               // argument to thread function
                                    0,                  // use default creation flags
                                    &this->m_ThreadID   // returns the thread identifier
                            );
        
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        memset(&this->thread, 0, sizeof(struct TN_Task));
        tn_rc =     tn_task_create(
                                   &this->thread,
                                   thread_task_body,
                                   this->priority,
                                   (void *)this->stack,
                                   this->stackSize,
                                   this,
                                   (TN_TASK_CREATE_OPT_START)
                                   );
        if (tn_rc == TN_RC_OK) {
        }
        else {
            DEBUG_BREAK();
        }
        this->thread.name = "psxThread";
#endif
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S t o p
    //---------------------------------------------------------------
    
    bool            psxThread_Stop(
        PSXTHREAD_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxThread_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->fTerminate) {
            return false;
        }
        this->fTerminate = true;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     psxThread_ToDebugString(
        PSXTHREAD_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(psxThread) stackSize=%d ",
                     this,
                     psxThread_getStackSize(this)
            );
        AStr_AppendA(pStr, str);

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
        
        j = snprintf( str, sizeof(str), " %p(psxThread)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            psxThread_Validate(
        PSXTHREAD_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_PSXTHREAD) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(PSXTHREAD_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
#ifdef	__cplusplus
}
#endif


