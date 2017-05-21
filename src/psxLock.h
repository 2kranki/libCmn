// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          PSXLOCK Console Transmit Task (psxLock) Header
//****************************************************************
/*
 * Program
 *			Separate psxLock (psxLock)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate psxLock to run things without complications
 *          of interfering with the main psxLock. A psxLock may be 
 *          called a psxLock on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal psxLock. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	05/19/2017 Generated
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


#ifndef         PSXLOCK_H
#define         PSXLOCK_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct psxLock_data_s	PSXLOCK_DATA;    // Inherits from OBJ.

    typedef struct psxLock_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in psxLock_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PSXLOCK_DATA *);
    } PSXLOCK_VTBL;



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
     @return:   pointer to psxLock object if successful, otherwise OBJ_NIL.
     */
    PSXLOCK_DATA *  psxLock_Alloc(
    );
    
    
    PSXLOCK_DATA *  psxLock_New(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         psxLock_getLastError(
        PSXLOCK_DATA	*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    PSXLOCK_DATA *   psxLock_Init(
        PSXLOCK_DATA     *this
    );


    bool            psxLock_IsLocked(
        PSXLOCK_DATA	*this
    );
    
    
    bool            psxLock_Lock(
        PSXLOCK_DATA	*this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = psxLock_ToDebugString(this,4);
     @endcode:
     @param:    this    PSXLOCK object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     psxLock_ToDebugString(
        PSXLOCK_DATA    *this,
        int             indent
    );
    
    
    bool            psxLock_TryLock(
        PSXLOCK_DATA	*this
    );
    
    
    bool            psxLock_Unlock(
        PSXLOCK_DATA	*this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PSXLOCK_H */

