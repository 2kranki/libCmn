// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SCREEN Console Transmit Task (screen) Header
//****************************************************************
/*
 * Program
 *			Separate screen (screen)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate screen to run things without complications
 *          of interfering with the main screen. A screen may be 
 *          called a screen on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/26/2018 Generated
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


#ifndef         SCREEN_H
#define         SCREEN_H



#ifdef	__cplusplus
extern "C" {
#endif
    
    
#define  SCREEN_USE_CURSES 1

    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct screen_data_s	SCREEN_DATA;    // Inherits from OBJ.

    typedef struct screen_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in screen_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SCREEN_DATA *);
    } SCREEN_VTBL;



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
     @return    pointer to screen object if successful, otherwise OBJ_NIL.
     */
    SCREEN_DATA *   screen_Alloc(
        void
    );
    
    
    OBJ_ID          screen_Class(
        void
    );
    
    
    SCREEN_DATA *   screen_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    int             screen_getNumCols(
        SCREEN_DATA     *this
    );


    int             screen_getNumRows(
        SCREEN_DATA     *this
    );

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         screen_Clear(
        SCREEN_DATA		*this
    );


    ERESULT         screen_Echo(
        SCREEN_DATA		*this,
        bool            fOn
    );

   
    int             screen_Getch(
        SCREEN_DATA     *this
    );
    
    
    SCREEN_DATA *   screen_Init(
        SCREEN_DATA     *this
    );


    ERESULT         screen_Print(
        SCREEN_DATA     *this,
        int             row,
        int             col,
        const
        char            *pFormat,
        ...
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = screen_ToDebugString(this,4);
     @endcode 
     @param     this    SCREEN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    screen_ToDebugString(
        SCREEN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SCREEN_H */

