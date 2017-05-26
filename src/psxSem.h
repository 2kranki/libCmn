// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Posix Semaphore (psxSem) Header
//****************************************************************
/*
 * Program
 *			Posix Semaphore (psxSem)
 * Purpose
 *			This object creates a counting semaphore. You can
 *          think of a semaphore as an integer with a starting
 *          value and a maximum value. The integer/count is allowed
 *          to go negative.
 *
 *          When a thread waits on the semaphore (ie decrements it),
 *          if the result is negative, the thread blocks and can
 *          not continue until another thread posts (ie increments)
 *          the semaphore.
 *
 *          Semaphores are also useful when a thread wants to halt
 *          its progress waiting for a condition to become true.
 *
 * Remarks
 *	1.      See "The Little Book of Semaphores" by Allen B. Downey.
 *          It has a lot of detail about how to use semaphores.
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


#ifndef         PSXSEM_H
#define         PSXSEM_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct psxSem_data_s	PSXSEM_DATA;

    typedef struct psxSem_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } PSXSEM_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    PSXSEM_DATA *   psxSem_Alloc(
    );
    
    
    PSXSEM_DATA *   psxSem_New(
        int32_t         start,
        int32_t         max
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------
    
    ASTR_DATA *     psxSem_getName(
        PSXSEM_DATA     *this
    );
    

    bool            psxSem_setName(
        PSXSEM_DATA     *this,
        ASTR_DATA       *pValue
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    PSXSEM_DATA *   psxSem_Init(
        PSXSEM_DATA     *this,
        int32_t         start,
        int32_t         max
    );


    /*!
     Post (ie increment) the semaphore count if it is less than the
     maximum specified value. If count was increased and there are
     any threads blocked on the semaphore, release one of the threads.
     Post should only be called from normal routines (ie not within
     interrupts).
     @return:   If successful, true, otherwise false.
     */
    bool            psxSem_Post(
        PSXSEM_DATA		*this
    );
    
    
    /*!
     Post (ie increment) the semaphore count if it is less than the
     maximum specified value. If count was increased and there are
     any threads blocked on the semaphore, release one of the threads.
     iPost should only be called from interrupt routines.
     @return:   If successful, true, otherwise false.
     */
    bool            psxSem_iPost(
        PSXSEM_DATA		*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    psxSem_ToDebugString(
        PSXSEM_DATA     *this,
        int             indent
    );
    
    
    /*!
     Try to wait on (ie decrement) the semaphore count if it is greater
     than zero. If count will go negative from the decrement, do not 
     block the thread just return false.
     TryWait should only be called from normal routines (ie not within
     interrupts).
     @return:   If successful, true, otherwise false.
     */
    bool            psxSem_TryWait(
        PSXSEM_DATA		*this
    );
    
    
    /*!
     Try to wait on (ie decrement) the semaphore count if it is greater
     than zero. If count will go negative from the decrement, do not
     block the thread just return false.
     iTryWait should only be called from interrupt routines.
     @return:   If successful, true, otherwise false.
     */
    bool            psxSem_iTryWait(
        PSXSEM_DATA		*this
    );
    
    
    /*!
     Wait on (ie decrement) the semaphore count. If count goes negative
     from the decrement, block the thread until another thread issues
     a post (increment). When control is returned, the caller has
     'control' of one of the semaphore count values and should release
     that control when it is done by issuing a post (ie increment).
     Wait should only be called from normal routines (ie not within
     interrupts).
     @return:   If successful, true, otherwise false.
     */
    bool            psxSem_Wait(
        PSXSEM_DATA		*this
    );

    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* PSXSEM_H */

