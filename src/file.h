// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                Disk File Management  (file) Header
//****************************************************************
/*
 * Program
 *				Disk File Management (file)
 * Purpose
 *				This object is a collection of various methods that
 *              manage or deal with disk files.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/09/2015 Generated
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


#ifndef         FILE_H
#define         FILE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // FILE_DATA and FILE_VTBL are defined in "cmn.h"



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the file including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    FILE_DATA *     file_Alloc(
        void
    );
    
    
    int64_t         file_SizeA(
        const
        char            *pPath
    );
    
    
    ERESULT         file_ToArrayA(
        const
        char            *pPath,
        U8ARRAY_DATA    **ppArray
    );
    
    
    ERESULT         file_ToBufferA(
        const
        char            *pPath,
        uint8_t         **ppBuffer
    );
    
    
    ERESULT         file_TouchA(
        const
        char            *pPath
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /* If Quit is set, the file ends upon
     * completion of its next record. Set-
     * ting this does not end the file un-
     * less a record is received or we timed
     * out.
     */
    bool            file_getQuit(
        FILE_DATA       *this
    );

    bool            file_setQuit(
        FILE_DATA       *this,
        bool            flag
    );


    /* When Skip is set to true, all messages are skpped over
     * and purged from the queue.
     */
    bool            file_getSkip(
        FILE_DATA     *this
    );

    bool            file_setSkip(
        FILE_DATA       *this,
        bool            flag
    );


    void *          file_getTask(
        FILE_DATA       *this
    );


    /* TaskBody() is the primary function run by the separate file.
     * It is defaulted to running a function that waits for data
     * from the queue and processes it. By overriding this, the
     * file will perform this routine instead.
     */
    bool			file_setTaskBody(
        FILE_DATA       *this,
        void            (*function)(void *),
        void            *pData                  // Data passed as void *
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the file file.
     */
    bool            file_Disable(
        FILE_DATA		*this
    );


    /* Enable() starts the file.
     */
    bool            file_Enable(
        FILE_DATA		*this
    );


    bool            file_IsEmpty(
        FILE_DATA       *this
    );


    bool            file_IsEnabled(
        FILE_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    FILE_DATA *     file_Init(
        FILE_DATA       *this
    );


    ASTR_DATA *     file_ToDebugString(
        FILE_DATA       *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* FILE_H */

