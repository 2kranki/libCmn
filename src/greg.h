// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Gregorian Date (greg) Header
//****************************************************************
/*
 * Program
 *				Gregorian Date (greg)
 * Purpose
 *				This object provides support for Gregorian Dates.
 *
 * Remarks
 *	1.      N/A
 *
 * History
 *	05/14/2015 Generated
 *
 * References
 *  --      "Date Conversions", The C Users Journal, Feb 1993, page 29
 *  --      "Astronomy with Your Personal Computer", Peter Duffett-Smith,
 *          Cambridge University Press, 1988
 *  --      "Calendrical Calculations", Software-Practice, Sep 1990, page 899
 *  --      "Calendrical Calculations", Software-Practice, Apr 1993, page 383
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


#ifndef         GREG_H
#define         GREG_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct greg_data_s	GREG_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the greg including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    GREG_DATA *     greg_Alloc(
    );
    
    
    OBJ_ID          greg_Class(
    );
    
    
    bool            greg_IsLeapYear(
        uint16_t        yyyy
    );
    
    
    bool            greg_IsValid(
        uint16_t        mm,
        uint16_t        dd,
        uint16_t        yyyy
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* When Skip is set to true, all messages are skpped over
     * and purged from the queue.
     */
    bool            greg_getSkip(
        GREG_DATA       *this
    );

    bool            greg_setSkip(
        GREG_DATA       *this,
        bool            flag
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    GREG_DATA *     greg_Init(
        GREG_DATA       *this
    );


    uint32_t        greg_JulianDay(
        GREG_DATA		*this
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* GREG_H */

