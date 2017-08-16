// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          TRUE Console Transmit Task (True) Header
//****************************************************************
/*
 * Program
 *			Separate True (True)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate True to run things without complications
 *          of interfering with the main True. A True may be 
 *          called a True on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal True. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	11/12/2015 Generated
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


#ifndef         TRUE_H
#define         TRUE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct true_data_s	TRUE_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    TRUE_DATA *     true_Alloc(
    );
    
    
    TRUE_DATA *     true_New(
    );
    
    
    TRUE_DATA *     true_Shared(
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    TRUE_DATA *   true_Init(
        TRUE_DATA       *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    true_ToDebugString(
        TRUE_DATA       *this,
        int             indent
    );
    
    
    ASTR_DATA *     true_ToJSON(
        TRUE_DATA       *this
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TRUE_H */

