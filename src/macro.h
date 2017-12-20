// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          MACRO Console Transmit Task (macro) Header
//****************************************************************
/*
 * Program
 *				Separate macro (macro)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate macro to run things without complications
 *              of interfering with the main macro. A macro may be 
 *              called a macro on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal macro. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	08/08/2015 Generated
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
#include        <name.h>
#include        <objArray.h>
#include        <node.h>


#ifndef         MACRO_H
#define         MACRO_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct macro_data_s	MACRO_DATA;

    typedef struct macro_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } MACRO_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the macro including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    MACRO_DATA *    macro_Alloc(
        void
    );
    
    
    MACRO_DATA *    macro_NewWithName(
        NAME_DATA       *pName
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NAME_DATA *    macro_getName(
        MACRO_DATA      *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the macro macro.
     */
    bool            macro_Disable(
        MACRO_DATA		*this
    );


    /* Enable() starts the macro.
     */
    bool            macro_Enable(
        MACRO_DATA		*this
    );


    bool            macro_IsEnabled(
        MACRO_DATA		*this
    );
    
    
    MACRO_DATA *    macro_Init(
        MACRO_DATA       *this,
        NAME_DATA        *pName
    );


    MACRO_DATA *    macro_InitWithUTF8Con(
        MACRO_DATA      *this,
        const
        char            *pName
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     macro_ToDebugString(
        MACRO_DATA      *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* MACRO_H */

