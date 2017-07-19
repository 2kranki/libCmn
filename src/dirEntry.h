// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Directory Entry (direntry) Header
//****************************************************************
/*
 * Program
 *				Directory Entry (direntry)
 * Purpose
 *				This object encapsulates Directory Entries from many
 *              different operating system for a common interface.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/23/2015 Generated
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
#include        <path.h>
#include        <AStr.h>


#ifndef         DIRENTRY_H
#define         DIRENTRY_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct dirEntry_data_s	DIRENTRY_DATA;

    typedef struct dirEntry_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in hjson_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DIRENTRY_DATA *);
    } DIRENTRY_VTBL;
    
    

    typedef enum dirEntry_types_e {
        DIRENTRY_TYPE_UNKNOWN=0,
        DIRENTRY_TYPE_FIFO=1,
        DIRENTRY_TYPE_CHR=2,            // Character Device
        DIRENTRY_TYPE_DIR=4,            // Directory Entry
        DIRENTRY_TYPE_BLK=6,            // Block Device
        DIRENTRY_TYPE_REG=8,            // Regular File
        DIRENTRY_TYPE_LNK=10,           // File Link
        DIRENTRY_TYPE_SOCK=12,          // Network Socket
        DIRENTRY_TYPE_WHT=14            // ???
    } DIRENTRY_TYPES;


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the direntry including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    DIRENTRY_DATA *     dirEntry_Alloc(
    );
    
    
    DIRENTRY_DATA *     dirEntry_NewA(
        PATH_DATA           *pDir,
        const
        char                *pNameStr,
        uint8_t             type
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    PATH_DATA *     dirEntry_getDir(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setDir(
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    );
    
    
    ASTR_DATA *     dirEntry_getName(
        DIRENTRY_DATA   *this
    );
    
    bool            dirEntry_setName(
        DIRENTRY_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    uint8_t         dirEntry_getType(
        DIRENTRY_DATA   *this
    );

    bool            dirEntry_setType(
        DIRENTRY_DATA   *this,
        uint8_t         value
    );

    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Disable() terminates the direntry direntry.
     */
    bool            dirEntry_Disable(
        DIRENTRY_DATA		*this
    );


    /* Enable() starts the direntry.
     */
    bool            dirEntry_Enable(
        DIRENTRY_DATA		*this
    );


    bool            dirEntry_IsEnabled(
        DIRENTRY_DATA		*this
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    DIRENTRY_DATA * dirEntry_Init(
        DIRENTRY_DATA       *this
    );


    void *          dirEntry_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = dirEntry_ToDebugString(this, 4);
     @endcode:
     @param:    this    DIRENTRY object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     dirEntry_ToDebugString(
        DIRENTRY_DATA   *this,
        int             indent
    );

    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DIRENTRY_H */

