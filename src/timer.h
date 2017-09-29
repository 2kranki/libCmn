// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                      Timer Task (timer) Header
//****************************************************************
/*
 * Program
 *			Timer Task (timer)
 * Purpose
 *			This object provides a low accuracy timer thread.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/06/2017 Generated
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


#ifndef         TIMER_H
#define         TIMER_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct timer_data_s	TIMER_DATA;    // Inherits from OBJ.

    typedef struct timer_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in timer_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TIMER_DATA *);
    } TIMER_VTBL;



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
     @return:   pointer to timer object if successful, otherwise OBJ_NIL.
     */
    TIMER_DATA *     timer_Alloc(
        void
    );
    
    
    TIMER_DATA *     timer_New(
        uint32_t        msWait,
        void            *(*timerRoutine)(void *),
        void            *routineData
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT         timer_getLastError(
        TIMER_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    TIMER_DATA *    timer_Init(
        TIMER_DATA      *this,
        uint32_t        msWait,
        void            *(*timerRoutine)(void *),
        void            *routineData
    );


    bool            timer_Pause(
        TIMER_DATA     *this
    );
    
 
    bool            timer_Resume(
        TIMER_DATA     *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = timer_ToDebugString(this,4);
     @endcode:
     @param:    this    TIMER object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     timer_ToDebugString(
        TIMER_DATA      *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

