// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          PRT Console Transmit Task (prt) Header
//****************************************************************
/*
 * Program
 *				Separate prt (prt)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate prt to run things without complications
 *              of interfering with the main prt. A prt may be 
 *              called a prt on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal prt. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/16/2015 Generated
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


#ifndef         PRT_H
#define         PRT_H



#ifdef	__cplusplus
extern "C" {
#endif
    

#define PRT_DESKJET			3
#define PRT_LASERJET		2
#define PRT_SIMPLE			1
    
    
    
    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct prt_data_s	PRT_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the prt including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    PRT_DATA *     prt_Alloc(
        void
    );
    
    
    OBJ_ID          prt_Class(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        prt_getCol(
        PRT_DATA		*this
    );

    
    void            prt_setHeader(
        PRT_DATA        *this,
        uint16_t		hdrnum,
        const
        char			*fmt,
        ...
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the prt prt.
     */
    bool            prt_Disable(
        PRT_DATA		*this
    );


    /* Enable() starts the prt.
     */
    bool            prt_Enable(
        PRT_DATA		*this
    );


    bool            prt_IsEnabled(
        PRT_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    PRT_DATA *     prt_Init(
        PRT_DATA       *this,
        int             prttyp,
        char            *lstfil
    );


    void            prt_Printf(
        PRT_DATA        *this,
        const
        char			*fmt,
        ...
    );
    
    
    void            prt_Putc(
        PRT_DATA        *this,
        char            outchr
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* PRT_H */

