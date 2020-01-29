// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Disk Directory Entry (DirEntry) Header
//****************************************************************
/*
 * Program
 *			Disk Directory Entry (DirEntry)
 * Purpose
 *              This object encapsulates Directory Entries from many
 *              different operating system for a common interface.
 *
 * Remarks
 *    1.      Some properties are OS dependent and will not be present
 *          in all OSes.
 *
 * History
 *  06/23/2015 Generated
 *  10/04/2018 Changed to be more consistant with the path object.
 *	01/28/2020 Regenerated, adding json support
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
#include        <dateTime.h>
#include        <path.h>


#ifndef         DIRENTRY_H
#define         DIRENTRY_H


//#define   DIRENTRY_IS_IMMUTABLE     1
#define   DIRENTRY_JSON_SUPPORT     1
//#define   DIRENTRY_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct DirEntry_data_s	DIRENTRY_DATA;            // Inherits from OBJ
    typedef struct DirEntry_class_data_s DIRENTRY_CLASS_DATA;   // Inherits from OBJ

    typedef struct DirEntry_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DirEntry_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DIRENTRY_DATA *);
    } DIRENTRY_VTBL;

    typedef struct DirEntry_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in DirEntry_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(DIRENTRY_DATA *);
    } DIRENTRY_CLASS_VTBL;


    typedef enum dirEntry_types_e {
        DIRENTRY_TYPE_UNKNOWN=0,
        DIRENTRY_TYPE_FIFO=1,
        DIRENTRY_TYPE_CHR=2,            // Character Device
        DIRENTRY_TYPE_DIR=4,            // Directory Entry
        DIRENTRY_TYPE_BLK=6,            // Block Device
        DIRENTRY_TYPE_REG=8,            // Regular File
        DIRENTRY_TYPE_LNK=10,           // File Link
        DIRENTRY_TYPE_SOCK=12,          // Network Socket
        DIRENTRY_TYPE_WHT=14            // White Out (???)
    } DIRENTRY_TYPES;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  DIRENTRY_SINGLETON
    DIRENTRY_DATA * DirEntry_Shared (
        void
    );

    void            DirEntry_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to DirEntry object if successful, otherwise OBJ_NIL.
     */
    DIRENTRY_DATA * DirEntry_Alloc (
        void
    );
    
    
    OBJ_ID          DirEntry_Class (
        void
    );
    
    
    DIRENTRY_DATA * DirEntry_New (
        void
    );
    
    
    DIRENTRY_DATA * DirEntry_NewA (
        const
        char            *pPathA,
        uint8_t         type
    );


#ifdef  DIRENTRY_JSON_SUPPORT
    DIRENTRY_DATA * DirEntry_NewFromJsonString(
        ASTR_DATA       *pString
    );

    DIRENTRY_DATA * DirEntry_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif


    DIRENTRY_DATA * DirEntry_NewWithData(
        ASTR_DATA       *pDrive,
        PATH_DATA       *pDir,
        PATH_DATA       *pFileName,     // includes file extension
        uint8_t         type            // See DIRENTRY_TYPES above.
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! Property: Creation Date / Time
     */

    DATETIME_DATA * DirEntry_getCreationTime (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setCreationTime (
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    );


    /*! Property: Directory
     */

    PATH_DATA *     DirEntry_getDir (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setDir (
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    );


    /*! Property: Disk Drive
     */

    ASTR_DATA *     DirEntry_getDrive (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setDrive (
        DIRENTRY_DATA   *this,
        ASTR_DATA       *pValue
    );


    /*! Property: Extended Attributes Size
     */

    uint32_t        DirEntry_getEASize (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setEASize (
        DIRENTRY_DATA   *this,
        uint32_t        value
    );


    /*! Property: File Name
     */

    PATH_DATA *     DirEntry_getFileName (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setFileName (
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    );


    /*! Property: Full Path
     */

    PATH_DATA *     DirEntry_getFullPath (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setFullPath (
        DIRENTRY_DATA   *this,
        PATH_DATA       *pValue
    );


    /*! Property: Generation Number
     */

    uint32_t        DirEntry_getGenerationNumber (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setGenerationNumber (
        DIRENTRY_DATA   *this,
        uint32_t        value
    );


    /*! Property: Last Data Modification Date / Time
     */

    DATETIME_DATA * DirEntry_getModifiedTime (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setModifiedTime (
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    );


    /*! Property: Short File Name
     */

    ASTR_DATA *     DirEntry_getShortName (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setShortName (
        DIRENTRY_DATA   *this,
        ASTR_DATA       *pValue
    );


    /*! Property: Last Status Change Date / Time
     */

    DATETIME_DATA * DirEntry_getStatusChangeTime (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setStatusChangeTime (
        DIRENTRY_DATA   *this,
        DATETIME_DATA   *pValue
    );


    /*! Property: Type indicates the type of directory entry that this
     represents.  See DIRENT_TYPES above.
    */

    uint16_t        DirEntry_getType (
        DIRENTRY_DATA   *this
    );

    bool            DirEntry_setType (
        DIRENTRY_DATA   *this,
        uint16_t        value
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = DirEntry_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another DIRENTRY object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         DirEntry_Assign (
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         DirEntry_Compare (
        DIRENTRY_DATA   *this,
        DIRENTRY_DATA   *pOther
    );


    /*! Complete the remaining data by accessing the actual directory
        entry on disk.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                 error code.
     */
    ERESULT         DirEntry_Complete (
        DIRENTRY_DATA   *this
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        DirEntry      *pCopy = DirEntry_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a DIRENTRY object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DIRENTRY_DATA * DirEntry_Copy (
        DIRENTRY_DATA   *this
    );

   
    DIRENTRY_DATA * DirEntry_Init (
        DIRENTRY_DATA   *this
    );


    /*! Match this entry's file name against a pattern.
        which may include '?' and '*'.
     @param     this        object pointer
     @param     pPatternA   pattern to match against
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_* error.
     */
    ERESULT         DirEntry_MatchA (
        DIRENTRY_DATA   *this,
        const
        char            *pPatternA
    );


#ifdef  DIRENTRY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = DirEntry_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     DirEntry_ToJson(
        DIRENTRY_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = DirEntry_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    DirEntry_ToDebugString (
        DIRENTRY_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DIRENTRY_H */

