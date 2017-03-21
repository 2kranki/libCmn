// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Posix Mutex (psxMutex) Header
//****************************************************************
/*
 * Program
 *			Posix Mutex (psxMutex)
 * Purpose
 *			A Posix Mutex is an object used to serialize access to
 *          variables across threads. If all threads lock the mutex
 *          prior to accessing the variables and then unlock when
 *          they are done, only one thread will have access to the
 *          variables at a time.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal psxMutex. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
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


#ifndef         PSXMUTEX_H
#define         PSXMUTEX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct psxMutex_data_s	PSXMUTEX_DATA;

    typedef struct psxMutex_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } PSXMUTEX_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    PSXMUTEX_DATA *     psxMutex_Alloc(
    );
    
    
    PSXMUTEX_DATA *     psxMutex_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    PSXMUTEX_DATA *   psxMutex_Init(
        PSXMUTEX_DATA     *this
    );


    bool            psxMutex_IsLocked(
        PSXMUTEX_DATA		*this
    );
    
    
    bool            psxMutex_Lock(
        PSXMUTEX_DATA		*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    psxMutex_ToDebugString(
        PSXMUTEX_DATA     *this,
        int             indent
    );
    
    
    bool            psxMutex_TryLock(
        PSXMUTEX_DATA		*this
    );
    
    
    bool            psxMutex_Unlock(
        PSXMUTEX_DATA		*this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PSXMUTEX_H */

