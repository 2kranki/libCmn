// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//       Generate an index for a subdirectory (Index) Header
//****************************************************************
/*
 * Program
 *          Generate an index for a subdirectory (Index)
 * Purpose
 *          This object builds a tree-like structure for a directory
 *          to represent that directory by an "index.html" file.
 *          The data to build the file consists of the directory
 *          leading into the subdirectory and "*.json.txt" files
 *          that describe the index entries in the "index.html" file.
 *          This data is then loaded into a Tree which can be used
 *          to generate the "index.html" file.
 *
 *          An "index.html" contains several components. First, you
 *          have the external named directory structure at the top
 *          of the index that provides direct linkage to its upper
 *          components. We have to look at all the upper directories
 *          to determine this list.
 *
 *          Second, you have the primary index (ie <ul></ul>) which
 *          contains most of the item entries. The entries can be
 *          file links, directory links and comments. This index
 *          list may contain sublists as well. If files are found
 *          within the directory that do not have an Item file for
 *          them, we create one that just uses the file name as
 *          name.
 *
 *          Third, you optionally have web links at the end of the
 *          index that takes to websites for further information.
 *          These links have to be verified and the index build.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/22/2021 Generated
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





#include        <Main_defs.h>
#include        <AStr.h>
#include        <Dir.h>
#include        <Item.h>
#include        <NodeTree.h>
#include        <Path.h>
#include        <PathArray.h>


#ifndef         INDEX_H
#define         INDEX_H


//#define   INDEX_IS_IMMUTABLE     1
//#define   INDEX_JSON_SUPPORT     1
//#define   INDEX_SINGLETON        1
//#define       INDEX_LOG   1


#ifdef   INDEX_LOG
#include        <logInterface.h>
#endif



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Index_data_s  INDEX_DATA;          // Inherits from INDEX
    typedef struct Index_class_data_s INDEX_CLASS_DATA;  // Inherits from OBJ

    typedef struct Index_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Index_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Index_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(INDEX_DATA *);
    } INDEX_VTBL;

    typedef struct Index_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Index_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(INDEX_DATA *);
    } INDEX_CLASS_VTBL;





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  INDEX_SINGLETON
    INDEX_DATA *     Index_Shared (
        void
    );

    void            Index_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Index object if successful, otherwise OBJ_NIL.
     */
    INDEX_DATA *     Index_Alloc (
        void
    );
    
    
    OBJ_ID          Index_Class (
        void
    );
    
    
    INDEX_DATA *     Index_New (
        void
    );
    
    
#ifdef  INDEX_JSON_SUPPORT
    INDEX_DATA *   Index_NewFromJsonString (
        ASTR_DATA       *pString
    );

    INDEX_DATA *   Index_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    PATH_DATA *     Index_getDir (
        INDEX_DATA      *this
    );

    bool            Index_setDir (
        INDEX_DATA      *this,
        PATH_DATA       *pValue
    );


    ASTR_DATA *     Index_getDrive (
        INDEX_DATA      *this
    );

    bool            Index_setDrive (
        INDEX_DATA      *this,
        ASTR_DATA       *pValue
    );


    PATHARRAY_DATA * Index_getExcludes (
        INDEX_DATA      *this
    );

    bool            Index_setExcludes (
        INDEX_DATA      *this,
        PATHARRAY_DATA  *pValue
    );


#ifdef INDEX_LOG
    /*! @property   Logging
        Allows information and warning messages to be issued for this
        object. Messages will be skipped if Log is not set.
     */
    bool            Index_setLog (
        INDEX_DATA    *this,
        OBJ_ID          pObj
    );
#endif


    PATH_DATA *     Index_getPath (
        INDEX_DATA      *this
    );

    bool            Index_setPath (
        INDEX_DATA      *this,
        PATH_DATA       *pValue
    );


    PATHARRAY_DATA * Index_getTop (
        INDEX_DATA      *this
    );

    bool            Index_setTop (
        INDEX_DATA      *this,
        PATHARRAY_DATA  *pValue
    );


    NODETREE_DATA * Index_getTree (
        INDEX_DATA      *this
    );

    bool            Index_setTree (
        INDEX_DATA      *this,
        NODETREE_DATA   *pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create the path to directory to be indexed.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    PATH_DATA *     Index_CreateDirPath (
        INDEX_DATA      *this
    );


    /*!
     Create an HTML index page for the given directory and its contents.
     At the top of the page will be an index to the upper level indices.
     @param     this        object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error.
     */
    ERESULT         Index_Generate (
        INDEX_DATA      *this
    );

   
    INDEX_DATA *    Index_Init (
        INDEX_DATA      *this
    );


    /*!
     Setup object to create an HTML index page for the given directory.
     @param     this        object pointer
     @param     pDrv        Drive object pointer
     @param     pExcludes   Directory Array object pointer for top level
                            directories that will not be included in the
                            index generation.
     @param     pTop        Directory Array object pointer for top level
                            directories that will be included in the index
                            generation.  These become the index at the top
                            of the generated page.
     @param     pDir        Directory object pointer for the index data and
                            to hold the generated index page.
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error.
     */
    ERESULT         Index_Setup (
        INDEX_DATA      *this,
        ASTR_DATA       *pDrv,
        PATHARRAY_DATA  *pExcludes,
        PATHARRAY_DATA  *pTop,
        PATH_DATA       *pDir
    );


#ifdef  INDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Index_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Index_ToJson (
        INDEX_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Index_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Index_ToDebugString (
        INDEX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* INDEX_H */

