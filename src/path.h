// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          PATH Console Transmit Task (path) Header
//****************************************************************
/*
 * Program
 *			Separate path (path)
 * Purpose
 *			This object provides a standardized way of handling a path
 *
 *          This path is based partially on url format and Unix path
 *          format. The general form of a path is:
 *              [driveSpecifier:] [/directory]* fileName [.ext]
 *          of interfering with the main path. A path may be called a 
 *          path on other O/S's.
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


#ifndef         PATH_H
#define         PATH_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // PATH_DATA and PATH_VTBL are defined in "cmn.h"




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the path including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    PATH_DATA *     path_Alloc(
        void
    );
    
    
    PATH_DATA *     path_NewA(
        const
        char            *pStr
    );
    
    
    PATH_DATA *     path_NewFromAStr(
        ASTR_DATA       *pStr
    );
    

    PATH_DATA *     path_NewFromCurrentDirectory(
        void
    );
    
    
    PATH_DATA *     path_NewFromEnv(
        const
        char            *pStr
    );
    
    
    PATH_DATA *     path_NewFromWStr(
        WSTR_DATA       *pStr
    );
    
    
    PATH_DATA *     path_NewW(
        uint32_t        len,
        const
        int32_t         *pStr
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    const
    char *          path_getData(
        PATH_DATA       *this
    );
    
    
    ASTR_DATA *     path_getAStr(
        PATH_DATA       *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // AppendExt() first appends a '.' if needed. Then it appends the
    // Extension which could also be a directory component if needed.
    ERESULT         path_AppendExtA(
        PATH_DATA		*this,
        const
        char            *pExt
    );
    
    
    // AppendDir() first appends a '/'. Then it appends the
    // directory component.
    ERESULT         path_AppendDir(
        PATH_DATA		*this,
        ASTR_DATA       *pDir
    );
    
    ERESULT         path_AppendDirA(
        PATH_DATA		*this,
        const
        char            *pDirA
    );
    
    
    // AppendFileName() first appends a '/'. Then it appends the
    // FileName which could also be a directory component if needed.
    ERESULT         path_AppendFileName(
        PATH_DATA		*this,
        ASTR_DATA       *pFileName
    );

    ERESULT         path_AppendFileNameA(
        PATH_DATA		*this,
        const
        char            *pFileName
    );
    
    
    /*!
     Clean up the path by removing "//", "/./" or "/../"
        - replacingstring that describes this object and the objects within it.
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         path_Clean(
        PATH_DATA		*this
    );
    
    
    ERESULT         path_Compare(
        PATH_DATA		*this,
        PATH_DATA       *pOther
    );
    
    
    ERESULT         path_CompareA(
        PATH_DATA		*this,
        const
        char            *pOther
    );
    
    
    ERESULT         path_CompareRightA(
        PATH_DATA		*this,
        const
        char            *pOther
    );
    
    
    PATH_DATA *     path_Copy(
        PATH_DATA       *this
    );
    
    
    /*!
     Create an empty file for the path. If the file exists, ignore.
     @return:   ERESULT_SUCCESS if successful, otherwise an error result code.
     */
    ERESULT         path_CreateEmpty(
        PATH_DATA		*this
    );
    
    
    /* CStringA() returns a NUL terminated
     * ascii character string that was
     * gotten with mem_Malloc(). Therefore,
     * you must mem_Free() it when you are
     * done.
     */
    char *          path_CStringA(
        PATH_DATA		*this
    );
    
    
    ERESULT         path_FileSize(
        PATH_DATA       *this,
        int64_t         *pFileSize
    );
    
    
    PATH_DATA *     path_Init(
        PATH_DATA       *this
    );


    ERESULT         path_IsDir(
        PATH_DATA		*this
    );
    
    
    bool            path_IsEmpty(
        PATH_DATA     *this
    );
    
    
    ERESULT         path_IsExisting(
        PATH_DATA		*this
    );
    
    
    ERESULT         path_IsFile(
        PATH_DATA		*this
    );
    
    
    ERESULT         path_IsLink(
        PATH_DATA		*this
    );
    
    
    ERESULT         path_MakeFile(
        PATH_DATA		*this,
        ASTR_DATA       *pFileName,
        ASTR_DATA       *pFileExt
    );
    
    
    ERESULT         path_MakePath(
        PATH_DATA		*this,
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName      // includes file extension
    );
    
    
    ERESULT         path_SplitFile(
        PATH_DATA		*this,
        ASTR_DATA       **ppFileName,
        ASTR_DATA       **ppFileExt
    );
    
    
    ERESULT         path_SplitPath(
        PATH_DATA		*this,
        ASTR_DATA       **ppDrive,
        PATH_DATA       **ppDir,
        PATH_DATA       **ppFileName    // includes file extension
    );

    
    /*!
     Create a string that escapes any internal space characters as
     needed in Bash. ' ' becomes "\ " on output.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         path_ToBash(
        PATH_DATA		*this,
        ASTR_DATA       **ppAStr
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = path_ToDebugString(pObj,4);
     @endcode:
     @param:    this    object pointer
     @param:    indent  number of characters to indent every line of output, 
                can be 0
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     path_ToDebugString(
        PATH_DATA       *this,
        int             indent
    );
    
    
    ERESULT         path_ToWin(
        PATH_DATA		*this,
        ASTR_DATA       **ppAStr
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* PATH_H */

