// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Disk Directory Entries (Dir) Header
//****************************************************************
/*
 * Program
 *			Disk Directory Entries (Dir)
 * Purpose
 *			This object provides a standardized way of handling
 *          disk directories.
 *
 * Remarks
 *	1.      None
 *
 * History
 *  06/22/2015 Generated
 *	01/31/2020 Regenerated
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
#include        <DirEntry.h>
#include        <ObjEnum.h>
#include        <Path.h>


#ifndef         DIR_H
#define         DIR_H


//#define   DIR_IS_IMMUTABLE     1
#define   DIR_JSON_SUPPORT     1
//#define   DIR_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Dir_data_s	DIR_DATA;            // Inherits from OBJ
    typedef struct Dir_class_data_s DIR_CLASS_DATA;   // Inherits from OBJ

    typedef struct Dir_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Dir_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DIR_DATA *);
    } DIR_VTBL;

    typedef struct Dir_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Dir_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DIR_DATA *);
    } DIR_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  DIR_SINGLETON
    DIR_DATA *      Dir_Shared (
        void
    );

    void            Dir_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Dir object if successful, otherwise OBJ_NIL.
     */
    DIR_DATA *      Dir_Alloc (
        void
    );
    
    
    OBJ_ID          Dir_Class (
        void
    );
    
    
    /*!
     Get the current working directory (CWD) as a C string.
     @return    If successful, an mem object which must be freed containing the
                CWD, otherwise NULL.
     @warning   Remember to free the returned area with mem_Free().
     */
    const
    char *          Dir_GetCWD (
        void
    );


    ERESULT         Dir_IsDirA (
        const
        char            *pPath
    );


    ERESULT         Dir_IsExistingA (
        const
        char            *pPath
    );


    ERESULT         Dir_IsFileA (
        const
        char            *pPath
    );


    ERESULT         Dir_IsLinkA (
        const
        char            *pPath
    );


    /*! Create a new directory if needed.
     */
    ERESULT         Dir_MakeDir (
        PATH_DATA       *pPath,
        uint16_t        mode
    );


    DIR_DATA *      Dir_New (
        void
    );
    
    
#ifdef  DIR_JSON_SUPPORT
    DIR_DATA *      Dir_NewFromJsonString (
        ASTR_DATA       *pString
    );

    DIR_DATA *      Dir_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*! Collect the matching files in the given directory.
     @param this        object pointer
     @param pPath       path for directory to scan
     @param fRecurse    FALSE == Scan all the entries in the specified directory,
                        TRUE == Do FALSE, then scan each subdirectory as the
                        specified directory until there are no more directories
                        to scan.
     @return    an ObjEnum object which conttains the Direcory Entries (DirEntry)
                found.
     */
    OBJENUM_DATA *  Dir_EnumDir (
        DIR_DATA        *this,
        PATH_DATA       *pPath,
        bool            fRecurse
    );


    /*!
     Scan a directory using the supplied method.  The "." and ".." directory
     entries are skipped.  All other entries are returned to the Scanner
     routine unless a match if given in the provided path. The DirEntry's
     Match method is used to select the appropriate directory entries to
     be scanned.
     @param     this        object pointer
     @param     pPath       path for directory to start scan
     @param     pMatchA     Pattern to be matched against which may include directory
                            entries.
     @param     fRecurse    True == recurse through the directory structure, False
                            == just remain in the specified directory.
     @param     pScanner    scan method to be called for directory entry.  It should
                            return true to continue the scan or false to end it.
     @param     pObject     object parameter or 1st parameter of pScanner method
     @param     pData       optional data pointer to be passed as 3rd parameter of
                            pScanner method
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Dir_GlobMatch (
        DIR_DATA        *this,
        PATH_DATA       *pPath,
        const
        char            *pMatchA,
        bool            fRecurse,
        int             (*pScanner)(void *, DIRENTRY_DATA *, void *),
        void            *pObject,
        void            *pData
    );


    DIR_DATA *      Dir_Init (
        DIR_DATA        *this
    );


    /*!
     Scan a directory using the supplied method.  The "." and ".." directory
     entries are skipped.  All other entries are returned to the Scanner
     routine.
     @param this        object pointer
     @param pPath       path for directory to scan
     @param fRecurse    FALSE == Scan all the entries in the specified directory,
                        TRUE == Do FALSE, then scan each subdirectory as the
                        specified directory until there are no more directories
                        to scan.
     @param pScanner    scan method to be called for directory entry.  It should
                        return true to continue the scan or false to end it.
     @param pObject     object parameter or 1st parameter of pScanner method
     @param pData       optional data pointer to be passed as 3rd parameter of
                        pScanner method
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Dir_ScanDir (
        DIR_DATA        *this,
        PATH_DATA       *pPath,
        bool            fRecurse,
        bool            (*pScanner)(void *, DIRENTRY_DATA *, void *),
        void            *pObject,
        void            *pData
    );


    /*!
     SearchList() searches a Bash PATH-like list of directories for a
     specific file and returns the full path if it is found. The list
     of directories are passed in one string with ':' as a separator.
     The first file to match the criteria is returned.
     @param     this        object pointer
     @param     pPathListA  directory path list (Required)
     @param     pMatchA     regex match criteria (Defualt '*')
     @return    if successful, a DirEntry object which must be released.
                Otherwise, OBJ_NIL.
     */
    DIRENTRY_DATA * Dir_SearchList (
        DIR_DATA        *this,
        const
        char            *pPathListA,
        const
        char            *pMatchA
    );


#ifdef  DIR_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Dir_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Dir_ToJson (
        DIR_DATA        *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Dir_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Dir_ToDebugString (
        DIR_DATA        *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DIR_H */

