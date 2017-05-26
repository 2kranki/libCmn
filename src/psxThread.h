// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              POSIX Thread Object (psxThread) Header
//****************************************************************
/*
 * Program
 *			POSIX Thread Object (psxThread)
 * Purpose
 *          This class tries to provide a Posix-like threads within
 *          a process for operating systems. Thus, it provides a
 *          standardized interface for those operating systems.
 *          It is primarily designed to manage threads which do a 
 *          small amount of work and then relinquish control in a
 *          loop.  However, it can be used for single process type
 *          threads as well.  Also, the thread's actual execution
 *          code can be changed after its creation allowing the 
 *          thread to perform a multitude of purposes.
 *
 * Remarks
 *	1.      We will call the thread created by this object, "worker"
 *          thread.
 *
 * History
 *	02/11/2016 Generated
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





#include        <cmn_defs.h>
#include        <AStr.h>


#ifndef         PSXTHREAD_H
#define         PSXTHREAD_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct psxThread_data_s	PSXTHREAD_DATA;

    typedef struct psxThread_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } PSXTHREAD_VTBL;
    
    
    typedef enum psxThread_state_e	{
        PSXTHREAD_STATE_UNKNOWN=0,
        PSXTHREAD_STATE_ENDED,
        PSXTHREAD_STATE_ENDING,
        PSXTHREAD_STATE_PAUSED,
        PSXTHREAD_STATE_RUNNING,
        PSXTHREAD_STATE_STOPPED,
        PSXTHREAD_STATE_STARTING
    } PSXTHREAD_STATE;
    
    
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return:   pointer to PSXThread object if successful, otherwise OBJ_NIL.
     */
    PSXTHREAD_DATA * psxThread_Alloc(
    );
    
    
    /*!
     Allocate and initialize a new Object.
     @return:   pointer to PSXThread object if successful, otherwise OBJ_NIL.
     */
    PSXTHREAD_DATA * psxThread_New(
        void            *(*startRoutine)(void *),
        void            *routineData,
        uint32_t        stackSize           // Stack Size in Bytes (optional)
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t    psxThread_getErrno(
        PSXTHREAD_DATA	*this
    );
    
    bool        psxThread_setErrno(
        PSXTHREAD_DATA	*this,
        uint32_t        value
    );
    
    
    bool        psxThread_getPause(
        PSXTHREAD_DATA	*this
    );
    
    bool        psxThread_setRoutine(
        PSXTHREAD_DATA	*this,
        void            *(*startRoutine)(void *),
        void            *routineData
    );
    
    
    uint32_t    psxThread_getState(
        PSXTHREAD_DATA	*this
    );

    
    bool        psxThread_getTerminate(
        PSXTHREAD_DATA	*this
    );
    
    bool        psxThread_setTerminate(
        PSXTHREAD_DATA	*this,
        bool            value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Cancel the Thread waiting for it to end.
     */
    bool        psxThread_Cancel(
        PSXTHREAD_DATA	*this
    );
    
    
    /*!
     Initialize the Thread Object and set up for execution.
     @param: this pointer to object data area to be used. Normally, this would
            point to an object that was allocated using psxThread_Alloc().
     @param: startRoutine address of the routine to be executed in the thread
     @param: stackSize the size of the initial stack to be allocated in words. 
            Currently, this is only needed for TNEO.
     @return:   pointer to PSXThread object if successful, otherwise OBJ_NIL.
     */
    PSXTHREAD_DATA * psxThread_Init(
        PSXTHREAD_DATA  *this,
        void            *(*startRoutine)(void *),
        void            *routineData,
        uint32_t        stackSize           // Stack Size in Words (optional)
    );


    /*!
     Join the worker thread (ie wait for the worker thread to end its execution).
     This is called from an external thread that wants to wait for the completion
     of the worker thread if it is running. The calling thread will be suspended
     until this thread ends. When control is returned, the worker thread will have
     ended and its return value should optionally be stored in the area provided.
     Note that this does not request the thread to end. It simply waits for it to
     end.
     @param: ppReturn optionally points to an area where the thread's void * return 
            value will be stored. It may be NULL ignoring the result value of
            this thread.
     @return: True if successful, otherwise False.
     */
    bool        psxThread_Join(
        PSXTHREAD_DATA  *this,
        void            **ppReturn
    );
    
    
    bool        psxThread_Pause(
        PSXTHREAD_DATA	*this
    );
    
    
    bool        psxThread_Resume(
        PSXTHREAD_DATA	*this
    );

    
    /*!
     Request the worker thread to stop its execution.
     @return:   True if successful, otherwise False.
     */
    bool        psxThread_Terminate(
        PSXTHREAD_DATA	*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA * psxThread_ToDebugString(
        PSXTHREAD_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PSXTHREAD_H */

