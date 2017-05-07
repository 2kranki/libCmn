// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DBF Console Transmit Task (dbf) Header
//****************************************************************
/*
 * Program
 *				Separate dbf (dbf)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate dbf to run things without complications
 *              of interfering with the main dbf. A dbf may be 
 *              called a dbf on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal dbf. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/06/2015 Generated
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


#ifndef         DBF_H
#define         DBF_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dbf_data_s	DBF_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the dbf including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    DBF_DATA *     dbf_Alloc(
        uint16_t        stackSize           // Stack Size in Words
    );
    
    
    OBJ_ID          dbf_Class(
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* If Quit is set, the dbf ends upon
     * completion of its next record. Set-
     * ting this does not end the dbf un-
     * less a record is received or we timed
     * out.
     */
    bool            dbf_getQuit(
        DBF_DATA     *this
    );

    bool            dbf_setQuit(
        DBF_DATA     *this,
        bool            flag
    );


    /* When Skip is set to true, all messages are skpped over
     * and purged from the queue.
     */
    bool            dbf_getSkip(
        DBF_DATA     *this
    );

    bool            dbf_setSkip(
        DBF_DATA     *this,
        bool            flag
    );


    void *          dbf_getTask(
        DBF_DATA     *this
    );


    /* TaskBody() is the primary function run by the separate dbf.
     * It is defaulted to running a function that waits for data
     * from the queue and processes it. By overriding this, the
     * dbf will perform this routine instead.
     */
    bool			dbf_setTaskBody(
        DBF_DATA   *this,
        void            (*function)(void *),
        void            *pData                  // Data passed as void *
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the dbf dbf.
     */
    bool            dbf_Disable(
        DBF_DATA		*this
    );


    /* Enable() starts the dbf.
     */
    bool            dbf_Enable(
        DBF_DATA		*this
    );


    bool            dbf_IsEmpty(
        DBF_DATA     *this
    );


    bool            dbf_IsEnabled(
        DBF_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    DBF_DATA *     dbf_Init(
        DBF_DATA       *this
    );


    
#ifdef	__cplusplus
}
#endif

#endif	/* DBF_H */

