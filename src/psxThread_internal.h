// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   psxThread_internal.h
 *	Generated 02/11/2016 10:46:17
 *
 * Notes:
 *  --	N/A
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




#ifndef PSXTHREAD_INTERNAL_H
#define	PSXTHREAD_INTERNAL_H


#include    <psxThread.h>
#include    <psxLock.h>
#include    <psxMutex.h>
#include    <psxSem.h>



#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct psxThread_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    PSXLOCK_DATA    *pWorkerVars;
    PSXLOCK_DATA    *pWorkerLock;
    PSXSEM_DATA     *pWorkerWait;
    PSXSEM_DATA     *pOwnerWait;
    PSXSEM_DATA     *pWorkerEnded;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
    pthread_t       worker;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    HANDLE          m_hThread;
    DWORD           m_ThreadID;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
    struct TN_Task  worker;
#endif
    
    // Warning - It is important that these variables must only be set by either
    //          the owner or the worker thread but not both.  The variables do not
    //          have to be protected with a lock if this is maintained.
    volatile
    sig_atomic_t    iErrno;             // Last Error
    volatile
    sig_atomic_t    fDone;              // Thread routine is done
    //                                  // (Set by worker Routine)
    volatile
    sig_atomic_t    fPause;             // Thread should go into a hold state if true
    //                                  // (RO for worker)
    volatile
    sig_atomic_t    fTerminate;         // Thread should terminate if true
    //                                  // (RO for worker)
    volatile
    sig_atomic_t    fSkip;              // Stop processing messages
    volatile
    sig_atomic_t    state;              // Current Thread State
    //                                  // (Set by worker)(RO for others)
    volatile
    sig_atomic_t    msWait;             // Thread Sleep Time between Iterations
    //                                  // (RO for worker)
    void *          (*pThreadBody)(void *);
    void            *pThreadData;
    uint32_t        (*pCalcWait)(void *); // Calculate Wait Time between Iterations.
    void            *pCalcWaitData;

    uint32_t        stackSize;
    uint8_t         *pStack;

};
#pragma pack(pop)

    extern
    const
    PSXTHREAD_VTBL  psxThread_Vtbl;



    // Internal Functions
    void            psxThread_Dealloc(
        OBJ_ID          objId
    );

    PSXTHREAD_DATA * psxThread_InitSelf(
        PSXTHREAD_DATA  *this
    );
    
#ifdef NDEBUG
#else
    bool			psxThread_Validate(
        PSXTHREAD_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PSXTHREAD_INTERNAL_H */

