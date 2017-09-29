// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          DIR Console Transmit Task (dir) Header
//****************************************************************
/*
 * Program
 *				Separate dir (dir)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate dir to run things without complications
 *              of interfering with the main dir. A dir may be 
 *              called a dir on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal dir. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/22/2015 Generated
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
#include        <dirEntry.h>
#include        <path.h>
#include        <AStr.h>


#ifndef         DIR_H
#define         DIR_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dir_data_s	DIR_DATA;

    typedef struct dir_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } DIR_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the dir including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    DIR_DATA *      dir_Alloc(
        void
    );
    
    
    ERESULT         dir_IsDirA(
        const
        char            *pPath
    );
    
    
    ERESULT         dir_IsExistingA(
        const
        char            *pPath
    );
    
    
    ERESULT         dir_IsFileA(
        const
        char            *pPath
    );
    
    
    ERESULT         dir_IsLinkA(
        const
        char            *pPath
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    DIR_DATA *     dir_Init(
        DIR_DATA       *this
    );


    // Create a new directory if needed.
    ERESULT         path_MakeDir(
        DIR_DATA		*this,
        PATH_DATA       *pPath,
        uint16_t        mode
    );
    

    ERESULT         dir_ScanDir(
        DIR_DATA		*this,
        PATH_DATA       *pPath,
        bool            (*pScanner)(void *,DIRENTRY_DATA *),
        void            *pData
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = dir_ToDebugString(pObj,4);
     @endcode:
     @param:    this    DIR_DATA object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    dir_ToDebugString(
        DIR_DATA        *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* DIR_H */

