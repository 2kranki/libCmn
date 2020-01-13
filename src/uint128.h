// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          UINT128 Console Transmit Task (uint128) Header
//****************************************************************
/*
 * Program
 *			Separate uint128 (uint128)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate uint128 to run things without complications
 *          of interfering with the main uint128. A uint128 may be 
 *          called a uint128 on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal uint128. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	10/12/2015 Generated
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


#ifndef         UINT128_H
#define         UINT128_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct uint128_data_s	UINT128_DATA;

    typedef struct uint128_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fat16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FBSI_DATA *);
    } UINT128_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the uint128 including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    UINT128_DATA *     uint128_Alloc(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    
    UINT128_DATA *     uint128_New(
        uint16_t    stackSize           // Stack Size in Words
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the uint128 uint128.
     */
    bool        uint128_Disable(
        UINT128_DATA		*this
    );


    /* Enable() starts the uint128.
     */
    bool        uint128_Enable(
        UINT128_DATA		*this
    );


    bool        uint128_IsEnabled(
        UINT128_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    UINT128_DATA *   uint128_Init(
        UINT128_DATA     *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     uint128_ToDebugString(
        UINT128_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* UINT128_H */

