// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Disk Directory or File Path (Path) Header
//****************************************************************
/*
 * Program
 *			Disk Directory or File Path (Path)
 * Purpose
 *          This object provides a standardized way of handling a Path
 *
 *          This Path is based partially on url format and Unix Path
 *          format. The general form of a Path is:
 *              [driveSpecifier:] [/directory]* fileName [.ext]
 *
 * Remarks
 *    1.    The object User flags and Misc data are not used in this
 *          object.
 *
 * History
 *  06/09/2015 Generated
 *	01/29/2020 Regenerated and added json support
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
#include        <DateTime.h>


#ifndef         PATH_H
#define         PATH_H


//#define   PATH_IS_IMMUTABLE     1
#define   PATH_JSON_SUPPORT     1
//#define   PATH_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    //typedef struct Path_data_s	PATH_DATA;            // Inherits from OBJ
    //typedef struct Path_class_data_s PATH_CLASS_DATA;   // Inherits from OBJ

#ifdef DEFINED_IN_CMNDEFS
    typedef struct Path_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Path_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PATH_DATA *);
    } PATH_VTBL;
#endif

    typedef struct Path_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Path_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PATH_DATA *);
    } PATH_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PATH_SINGLETON
    PATH_DATA *     Path_Shared (
        void
    );

    void            Path_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Path object if successful, otherwise OBJ_NIL.
     */
    PATH_DATA *     Path_Alloc (
        void
    );
    
    
    OBJ_ID          Path_Class (
        void
    );
    
    
    PATH_DATA *     Path_New (
        void
    );
    
    
    PATH_DATA *     Path_NewA (
        const
        char            *pStr
    );


    PATH_DATA *     Path_NewFromAStr (
        ASTR_DATA       *pStr
    );


    /*! Create a new path from the supplied components. You should pass NULL for
     any optional component that you don't want to supply. If the necessary seperators
     are missing from the supplied components, they will be added.
     @param     pDriveA     optional drive with or without the trailing seperator,
                            ':'
     @param     pDirA       optional directory with or without the trailing
                            seperator, '/'
     @param     pFileNameA  required filename with or without a file extension.
     @param     pExtA       optional file extension with or without the leading '.'
     @return    If successful, a new path object, otherwise OBJ_NIL.
     */
    PATH_DATA *     Path_NewFromComponentsA(
        const
        char            *pDriveA,
        const
        char            *pDirA,
        const
        char            *pFileNameA,
        const
        char            *pExtA
    );


    PATH_DATA *     Path_NewFromCurrentDirectory (
        void
    );


    PATH_DATA *     Path_NewFromDirExt (
        ASTR_DATA       *pFilePath,
        ASTR_DATA       *pFileExt
    );


    PATH_DATA *     Path_NewFromDriveDirFilename (
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName      // includes file extension
    );


    PATH_DATA *     Path_NewFromEnv (
        const
        char            *pStr
    );


    PATH_DATA *     Path_NewFromW32STR (
        W32STR_DATA     *pStr
    );


    PATH_DATA *     Path_NewW32 (
        uint32_t        len,
        const
        W32CHR_T        *pStr
    );


#ifdef  PATH_JSON_SUPPORT
    PATH_DATA *   Path_NewFromJsonString (
        ASTR_DATA       *pString
    );

    PATH_DATA *   Path_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    /*!
     Clean up an AStr that represents a Path by removing "//", "/./" or "/../"
     combinations and replacing a leading '~' with the $HOME or $HOMEDRIVE Environ-
     ment variable.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         Path_CleanAStr(
        ASTR_DATA       *pStr
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    const
    char *          Path_getData (
        PATH_DATA       *this
    );


    ASTR_DATA *     Path_getAStr (
        PATH_DATA       *this
    );


    /*!
     @return:   return the number of Unicode characters in
                the path, not the actual size of the path in
                memory.  -1 indicates an error occurred.
     */
    uint32_t        Path_getLength(
        PATH_DATA      *this
    );


    /*!
     @return:   return the number of Unicode characters in
                the path, not the actual size of the path in
                memory.  -1 indicates an error occurred.
     */
    uint32_t        Path_getSize (
        PATH_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    // AppendAStr() just appends the string without any further
    // changes.
    ERESULT         Path_AppendA (
        PATH_DATA       *this,
        const
        char            *pStr
    );


    // AppendAStr() just appends the string without any further
    // changes.
    ERESULT         Path_AppendAStr (
        PATH_DATA       *this,
        ASTR_DATA       *pStr
    );


    // AppendExt() first appends a '.' if needed. Then it appends the
    // Extension which could also be a directory component if needed.
    ERESULT         Path_AppendExtA (
        PATH_DATA       *this,
        const
        char            *pExt
    );


    // AppendDir() first appends a '/'. Then it appends the
    // directory component.
    /*!
     Append a '/' if needed followed by the directory entry if it is present
     and insure that the Path is terminated by a '/'.
     @param     this    object pointer
     @param     pDir    optional directory
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
                is returned.
     */
    ERESULT         Path_AppendDir (
        PATH_DATA       *this,
        ASTR_DATA       *pDir
    );

    ERESULT         Path_AppendDirA (
        PATH_DATA       *this,
        const
        char            *pDirA
    );


    // AppendFileName() first appends a '/'. Then it appends the
    // FileName which could also be a directory component if needed.
    ERESULT         Path_AppendFileName (
        PATH_DATA       *this,
        ASTR_DATA       *pFileName
    );

    ERESULT         Path_AppendFileNameA (
        PATH_DATA       *this,
        const
        char            *pFileName
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Path_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another PATH object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT       Path_Assign (
        PATH_DATA     *this,
        PATH_DATA     *pOther
    );


    /*!
     Clean up the Path by removing "//", "/./" or "/../" combinations,
     replace a leading '~' with the $HOME or $HOMEDRIVE Environment variable
     and expand environment variables.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         Path_Clean (
        PATH_DATA       *this
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Path_Compare (
        PATH_DATA       *this,
        PATH_DATA       *pOther
    );


    ERESULT         Path_CompareA (
        PATH_DATA       *this,
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
    ERESULT         Path_CompareRightA (
        PATH_DATA       *this,
        const
        char            *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Path      *pCopy = Path_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a PATH object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PATH_DATA *     Path_Copy (
        PATH_DATA       *this
    );


    /*!
     Create an empty file for the path. If the file exists, ignore.
     @return    ERESULT_SUCCESS if successful, otherwise an error result code.
     */
    ERESULT         Path_CreateEmpty (
        PATH_DATA       *this
    );


    /* CStringA() returns a NUL terminated
     * ascii character string that was
     * gotten with mem_Malloc(). Therefore,
     * you must mem_Free() it when you are
     * done.
     */
    char *          Path_CStringA (
        PATH_DATA       *this
    );


    ERESULT         Path_DateLastUpdated (
        PATH_DATA       *this,
        DATETIME_DATA   **ppDate
    );


    ERESULT         Path_Delete (
        PATH_DATA       *this
    );


    /*!
     Substitute hash values or environment variables into the current string
     using a BASH-like syntax with the hash value having the highest priority.
     Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @param     pFindA      optional method to find the variable by name
     @param     pFindObj    Object for FindA
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         Path_ExpandVars (
        PATH_DATA       *this,
        const
        char *          (*pFindA)(OBJ_ID, const char *pName),
        OBJ_ID          pFindObj
    );


    ERESULT         Path_FileSize (
        PATH_DATA       *this,
        int64_t         *pFileSize
    );


    PATH_DATA *     Path_Init (
        PATH_DATA       *this
    );


    /*!
     Check to see if a path is a directory. If so, insure that the last character
     of the path is the path seperator so that it will parse more cleanly.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS is returned, otherwise an ERESULT_*
                 error is returned.
     */
    ERESULT         Path_IsDir (
        PATH_DATA       *this
    );


    bool            Path_IsEmpty (
        PATH_DATA       *this
    );


    ERESULT         Path_IsExisting (
        PATH_DATA       *this
    );


    ERESULT         Path_IsFile (
        PATH_DATA       *this
    );


    ERESULT         Path_IsLink (
        PATH_DATA       *this
    );


    /*!
     Split the Path into its 3 basic components of the drive, directory and
     FileName.  If a scan from the left of ':' fails, then no drive is
     assumed and OBJ_NIL is returned for the drive.  A scan from right to
     left for a trailing '/' is searched to find the end of the directory
     portion of the Path.  It also denotes the beginning of the file name.
     So, if the Path consists of optionally the drive and the directory
     portions, it must end in a '/' to be properly parsed.
     @param     this        object pointer
     @param     pDrive      pointer to ASTR object pointer which will contain
                            the drive if it exists in the Path.  The drive
                            returned is without its ':' separator.
     @param     pDir        pointer to an AStr object pointer which will contain
                            directory portion of the Path.
     @param     pFileName   optional pointer to an AStr object pointer where the
                            leading file Path will be returned if present.
     @param     pFileExt    optional pointer to an AStr object pointer where the
                            trailing file extension will be returned if present.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         Path_Make (
        PATH_DATA        *this,
        ASTR_DATA       *pDrive,
        ASTR_DATA       *pDir,
        ASTR_DATA       *pFileName,
        ASTR_DATA       *pFileExt
    );


    ERESULT         Path_MakeFile (
        PATH_DATA       *this,
        ASTR_DATA       *pFileName,
        ASTR_DATA       *pFileExt
    );


    ERESULT         Path_MakePath (
        PATH_DATA       *this,
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName      // includes file extension
    );


    /*!
     Match the file name and externsion in this path against a pattern using
     misc_PatternMatchA.
     @param     this    object pointer
     @param     pPattern pointer to a pattern string as containing optional
                        match characters, '?' and '*'.
     @return    If successful, ERESULT_SUCCESS is returned, otherwise an ERESULT_*
                 error is returned.
     */
    ERESULT         Path_MatchA (
        PATH_DATA       *this,
        const
        char            *pPattern
    );


    /*!
     Split the Path into its 3 basic components of the drive, directory and
     FileName.  If a scan from the left of ':' fails, then no drive is
     assumed and OBJ_NIL is returned for the drive.  A scan from right to
     left for a trailing '/' is searched to find the end of the directory
     portion of the Path.  It also denotes the beginning of the file name.
     So, if the Path consists of optionally the drive and the directory
     portions, it must end in a '/' to be properly parsed.
     @param     this        object pointer
     @param     ppDrive     pointer to ASTR object pointer which will contain
                            the drive if it exists in the Path.  The drive
                            returned is without its ':' separator.
     @param     ppDir       pointer to an AStr object pointer which will contain
                            directory portion of the Path.
     @param     ppFileName  optional pointer to an AStr object pointer where the
                            leading file Path will be returned if present.
     @param     ppFileExt   optional pointer to an AStr object pointer where the
                            trailing file extension will be returned if present.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         Path_Split (
        PATH_DATA        *this,
        ASTR_DATA       **ppDrive,
        ASTR_DATA       **ppDir,
        ASTR_DATA       **ppFileName,
        ASTR_DATA       **ppFileExt
    );


    /*!
     Split the Path into its 2 basic components of the file name and file
     extension.  The file name consists of drive (optionally), directory (optionally)
     and file name.  Generally, this is used to parse the file name and file
     extension on the full File Name output from the SplitPath() method.
     @param     this        object pointer
     @param     ppFileName  optional pointer to an AStr object pointer where the
                            leading file Path will be returned if present.
     @param     ppFileExt   optional pointer to an AStr object pointer where the
                            trailing file extension will be returned if present.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         Path_SplitFile (
        PATH_DATA        *this,
        ASTR_DATA       **ppFileName,       // (out) - optional
        ASTR_DATA       **ppFileExt         // (out) - optional
    );


    /*!
     Split the Path into its 3 basic components of the drive, directory and
     FileName.  If a scan from the left of ':' fails, then no drive is
     assumed and OBJ_NIL is returned for the drive.  A scan from right to
     left for a trailing '/' is searched to find the end of the directory
     portion of the Path.  It also denotes the beginning of the file name.
     So, if the Path consists of optionally the drive and the directory
     portions, it must end in a '/' to be properly parsed.
     @param     this        object pointer
     @param     ppDrive     pointer to ASTR object pointer which will contain
                            the drive if it exists in the Path.  The drive
                            returned is without its ':' separator.
     @param     ppDir       pointer to a Path object pointer which will contain
                            directory portion of the Path.
     @param     ppFileName  pointer to a Path object pointer which will contain
                            the file name portion of the Path
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         Path_SplitPath (
        PATH_DATA        *this,
        ASTR_DATA       **ppDrive,
        PATH_DATA       **ppDir,
        PATH_DATA       **ppFileName    // includes file extension
    );


    /*!
     Return the AStr component of the Path.
     @return    If successful, the AStr component of the path, otherwise OBJ_NIL.
     */
    ASTR_DATA *     Path_ToAStr (
        PATH_DATA       *this
    );


    /*!
     Create a string that escapes any internal space characters as
     needed in Bash. ' ' becomes "\ " on output.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         Path_ToBash (
        PATH_DATA       *this,
        ASTR_DATA       **ppAStr
    );


#ifdef  PATH_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Path_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Path_ToJson (
        PATH_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Path_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Path_ToDebugString (
        PATH_DATA      *this,
        int            indent
    );
    
    
    /*!
     Copy the string to stderr.
     @return    If successful, ERESULT_SUCCESS, otherwise ERESULT_* error.
     */
    ERESULT         Path_ToStderr(
        PATH_DATA       *this
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
    PATH_DATA *     Path_ToVersioned(
        PATH_DATA       *this
    );


    ERESULT         Path_ToWin(
        PATH_DATA       *this,
        ASTR_DATA       **ppAStr
    );


    /*!
     Rename the file on disk of the current path to the versioned form
     as given by ToVersioned.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Path_VersionedRename(
        PATH_DATA       *this
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* PATH_H */

