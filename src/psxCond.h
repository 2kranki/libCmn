// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Posix Condition Variable (psxCond) Header
//****************************************************************
/*
 * Program
 *			Posix Condition Variable (psxCond)
 * Purpose
 *			To wait for a condition to become true, a thread can make
 *          use of what is known as a condition variable. A condition 
 *          variable is an explicit queue that threads can put them-
 *          selves on when some state of execution (i.e., some condition)
 *          is not as desired (by waiting on the condition); some other 
 *          thread, when it changes said state, can then wake one (or 
 *          more) of those waiting threads and thus allow them to continue
 *          (by signaling on the condition).
 *
 *          A condition variable has two operations associated with it: 
 *          wait() and signal(). The wait() call is executed when a thread
 *          wishes to put itself to sleep; the signal() call is executed 
 *          when a thread has changed something in the program and thus 
 *          wants to wake a sleeping thread waiting on this condition.
 *
 * Remarks
 *	1.      None for now
 *
 * History
 *	07/05/2016 Generated
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


#ifndef         PSXCOND_H
#define         PSXCOND_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct psxCond_data_s	PSXCOND_DATA;    // Inherits from OBJ.

    typedef struct psxCond_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in psxCond_object.c.
        // Properties:
        // Methods:
    } PSXCOND_VTBL;



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
     @return:   pointer to psxCond object if successful, otherwise OBJ_NIL.
     */
    PSXCOND_DATA *     psxCond_Alloc(
        void
    );
    
    
    PSXCOND_DATA *     psxCond_New(
        bool            (*condRoutine)(void *),
        void            *condData
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    bool            psxCond_Broadcast(
        PSXCOND_DATA	*this
    );
    
    
    PSXCOND_DATA *  psxCond_Init(
        PSXCOND_DATA    *this,
        bool            (*condRoutine)(void *),
        void            *condData
    );


    bool            psxCond_Signal(
        PSXCOND_DATA	*this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = psxCond_ToDebugString(pObj,4);
     @endcode:
     @param:    this    psxCond object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     psxCond_ToDebugString(
        PSXCOND_DATA    *this,
        int             indent
    );
    
    
    /*!
     Wait for the condition routine to return 'true' (ie the condition).
     @param:    this    psxCond object pointer
     @return:   If successful, true is returned. Otherwise, false is returned.
     */
    bool            psxCond_Wait(
        PSXCOND_DATA    *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PSXCOND_H */

