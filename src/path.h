// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          File/Directory Path (path) Header
//****************************************************************
/*
 * Program
 *			File/Directory Path (path)
 * Purpose
 *			This object provides a standardized way of handling a path
 *
 *          This path is based partially on url format and Unix path
 *          format. The general form of a path is:
 *              [driveSpecifier:] [/directory]* fileName [.ext]
 *
 * Remarks
 *    1.    The object User flags and Misc data are not used in this
 *          object.
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
#include        <dateTime.h>


#ifndef         PATH_H
#define         PATH_H


#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // PATH_DATA and PATH_VTBL are defined in "cmn_defs.h"
    // PATH_DATA inherits from ASTR_DATA.




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
    
    
    PATH_DATA *     path_New(
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
    
    
    PATH_DATA *     path_NewFromDirExt(
        ASTR_DATA       *pFilePath,
        ASTR_DATA       *pFileExt
    );
    
    
    PATH_DATA *     path_NewFromDriveDirFilename(
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName      // includes file extension
    );
    
    
    PATH_DATA *     path_NewFromEnv(
        const
        char            *pStr
    );
    
    
    PATH_DATA *     path_NewFromW32STR(
        W32STR_DATA     *pStr
    );
    
    
    PATH_DATA *     path_NewW32(
        uint32_t        len,
        const
        W32CHR_T        *pStr
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

    // AppendAStr() just appends the string without any further
    // changes.
    ERESULT         path_AppendA(
        PATH_DATA       *this,
        const
        char            *pStr
    );
    
    
    // AppendAStr() just appends the string without any further
    // changes.
    ERESULT         path_AppendAStr(
        PATH_DATA       *this,
        ASTR_DATA       *pStr
    );
    
    
    // AppendExt() first appends a '.' if needed. Then it appends the
    // Extension which could also be a directory component if needed.
    ERESULT         path_AppendExtA(
        PATH_DATA		*this,
        const
        char            *pExt
    );
    
    
    // AppendDir() first appends a '/'. Then it appends the
    // directory component.
    /*!
     Append a '/' if needed followed by the directory entry if it is present
     and insure that the path is terminated by a '/'.
     @param     this    object pointer
     @param     pDir    optional directory
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
                is returned.
     */
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
     Clean up the path by removing "//", "/./" or "/../" combinations and
     replace a leading '~' with the $HOME or $HOMEDRIVE Environment variable.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
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
    
    
    /*!
     Compare the given string against 'this' from the right hand side of the string
     (ie compare the trailing part of the string)
     @param     this    object pointer
     @return    If str == const, ERESULT_SUCCESS_EQUAL. Otherwise, ERESULT_SUCCESS_LESS_THAN,
                 ERESULT_SUCCESS_GREATER_THAN or an ERESULT_* error code.
     */
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
     @return    ERESULT_SUCCESS if successful, otherwise an error result code.
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
    
    
    ERESULT         path_DateLastUpdated(
        PATH_DATA        *this,
        DATETIME_DATA    **ppDate
    );
    
    
    /*!
     Substitute hash values or environment variables into the current string
     using a BASH-like syntax with the hash value having the highest priority.
     Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @param     pHash   optional node hash pointer where the node's data is a
                        path or astr object(s).
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         path_ExpandVars(
        PATH_DATA       *this,
        OBJ_ID          pHash
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
    
    
    /*!
     Match this string against a pattern using misc_PatternMatchA.
     @param     this    object pointer
     @param     pPattern pointer to a pattern string as containing optional
     match characters, '?' and '*'.
     @return    If successful, ERESULT_SUCCESS is returned, otherwise an ERESULT_*
                 error is returned.
     */
    ERESULT         path_MatchA(
        PATH_DATA       *this,
        const
        char            *pPattern
    );
    
    
    /*!
     Split the path into its 2 basic components of the file name and file
     extension.  The file name consists of drive (optionally), directory (optionally)
     and file name.  Generally, this is used to parse the file name and file
     extension on the full File Name output from the SplitPath() method.
     @param     this        object pointer
     @param     ppFileName  optional pointer to an AStr object pointer where the
                            leading file path will be returned if present.
     @param     ppFileExt   optional pointer to an AStr object pointer where the
                            trailing file extension will be returned if present.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         path_SplitFile(
        PATH_DATA		*this,
        ASTR_DATA       **ppFileName,       // (out) - optional
        ASTR_DATA       **ppFileExt         // (out) - optional
    );
    
    
    /*!
     Split the path into its 3 basic components of the drive, directory and
     FileName.  If a scan from the left of ':' fails, then no drive is
     assumed and OBJ_NIL is returned for the drive.  A scan from right to
     left for a trailing '/' is searched to find the end of the directory
     portion of the path.  It also denotes the beginning of the file name.
     So, if the path consists of optionally the drive and the directory
     portions, it must end in a '/' to be properly parsed.
     @param     this        object pointer
     @param     ppDrive     pointer to ASTR object pointer which will contain
                            the drive if it exists in the path.  The drive
                            returned is without its ':' separator.
     @param     ppDir       pointer to a path object pointer which will contain
                            directory portion of the path.
     @param     ppFileName  pointer to a path object pointer which will contain
                            the file name portion of the path
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         path_SplitPath(
        PATH_DATA		*this,
        ASTR_DATA       **ppDrive,
        PATH_DATA       **ppDir,
        PATH_DATA       **ppFileName    // includes file extension
    );

    
    /*!
     Return the AStr component of the Path.
     @return    If successful, the AStr component of the path, otherwise OBJ_NIL.
     */
    ASTR_DATA *     path_ToAStr(
        PATH_DATA       *this
    );
    
    
    /*!
     Create a string that escapes any internal space characters as
     needed in Bash. ' ' becomes "\ " on output.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         path_ToBash(
        PATH_DATA		*this,
        ASTR_DATA       **ppAStr
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
     ASTR_DATA      *pDesc = path_ToDebugString(pObj,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output,
                can be 0
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     path_ToDebugString(
        PATH_DATA       *this,
        int             indent
    );
    
    
    /*!
     Copy the string to stderr.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         path_ToStderr(
        PATH_DATA        *this
    );
    
    
    /*!
     Create a path from the current one that is extended by a version number
     just before the file extension.  For example, "/a/abc.txt"  becomes
     "/a/abc.0000.txt".  Note that the version number is 4 digits.
     @param     this    object pointer
     @return    If successful, a path object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned path object.
     @warning  This can not be used from two or more threads on the same
                file path at the same time.
     */
    PATH_DATA *     path_ToVersioned(
        PATH_DATA       *this
    );
    
    
    ERESULT         path_ToWin(
        PATH_DATA		*this,
        ASTR_DATA       **ppAStr
    );
    
    
    /*!
     Rename the file on disk of the current path to the versioned form
     as given by ToVersioned.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         path_VersionedRename(
        PATH_DATA       *this
    );
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* PATH_H */

