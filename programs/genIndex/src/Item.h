// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          File/Directory Description Item (Item) Header
//****************************************************************
/*
 * Program
 *          File/Directory Description Item (Item)
 * Purpose
 *          This object represents an entry in an HTML index (ie
 *          (<li></li> entry). It can represent a directory, a
 *          file link or a comment. The comment can be to define
 *          an external name for the current directory or for a
 *          directory link.
 *
 *          A file link should include a file name and
 *          a description since both are required to generate
 *          the link. Optionally, an identifier can be specified
 *          as well.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  11/12/2021 Generated
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
#include        <AStrArray.h>


#ifndef         ITEM_H
#define         ITEM_H


//#define   ITEM_IS_IMMUTABLE     1
#define   ITEM_JSON_SUPPORT     1
//#define   ITEM_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Item_data_s  ITEM_DATA;          // Inherits from ITEM
    typedef struct Item_class_data_s ITEM_CLASS_DATA;  // Inherits from OBJ

    typedef struct Item_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //Item_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Item_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ITEM_DATA *);
    } ITEM_VTBL;

    typedef struct Item_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Item_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(ITEM_DATA *);
    } ITEM_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  ITEM_SINGLETON
    ITEM_DATA *     Item_Shared (
        void
    );

    void            Item_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Item object if successful, otherwise OBJ_NIL.
     */
    ITEM_DATA *     Item_Alloc (
        void
    );
    
    
    OBJ_ID          Item_Class (
        void
    );
    
    
    ITEM_DATA *     Item_New (
        void
    );
    
    
#ifdef  ITEM_JSON_SUPPORT
    ITEM_DATA *   Item_NewFromJsonString (
        ASTR_DATA       *pString
    );

    ITEM_DATA *   Item_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     Item_getDesc (
        ITEM_DATA       *this
    );

    bool            Item_setDesc (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     Item_getDir (
        ITEM_DATA       *this
    );

    bool            Item_setDir (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     Item_getFileName (
        ITEM_DATA       *this
    );

    bool            Item_setFileName (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );


    ASTRARRAY_DATA * Item_getHeadings (
        ITEM_DATA       *this
    );

    bool            Item_setHeadings (
        ITEM_DATA       *this,
        ASTRARRAY_DATA  *pValue
    );


    ASTR_DATA *     Item_getIdent (
        ITEM_DATA       *this
    );

    bool            Item_setIdent (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );


    ASTRARRAY_DATA * Item_getKeyWords (
        ITEM_DATA       *this
    );

    bool            Item_setKeyWords (
        ITEM_DATA       *this,
        ASTRARRAY_DATA  *pValue
    );


    ASTR_DATA *     Item_getName (
        ITEM_DATA       *this
    );

    bool            Item_setName (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );


    /*! @property   Type defines what type of Item that is present.
     The allowed types are "file", "dir", "comment".
     If no type is specified, then "file" is assumed.
     */
    ASTR_DATA *     Item_getType (
        ITEM_DATA       *this
    );

    bool            Item_setType (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add headings from a NULL terminated list of strings.
     @param     this        object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Item_AddHeadingsA (
        ITEM_DATA       *this,
        ...
    );


    /*!
     Add keywords from a NULL terminated list of strings.
     @param     this        object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Item_AddKeyWordsA (
        ITEM_DATA       *this,
        ...
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Item_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another ITEM object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Item_Assign (
        ITEM_DATA       *this,
        ITEM_DATA       *pOther
    );


    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Item_Compare (
        ITEM_DATA     *this,
        ITEM_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Item      *pCopy = Item_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a ITEM object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ITEM_DATA *     Item_Copy (
        ITEM_DATA       *this
    );


    /*!
     Generate the HTML link for this item if it has a file name and
     a deescription.
     @param     this    object pointer
     @param     pStr    AStr object pointer that the link string will
                        be appended to
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Item_Generate (
        ITEM_DATA       *this,
        ASTR_DATA       *pStr
    );


    ITEM_DATA *     Item_Init (
        ITEM_DATA       *this
    );


    /*!
     Establish an item from a set of strings. The item must have a
     directory name or a file name, but not both. If a file name is
     present, it will be linked with the description to become an
     HTML link (ie <li></li>). The optional headings follow the
     description parameter followed by a NULL. The NULL must be
     present whether there are headings for not.
     @param     this        object pointer
     @param     pDirA       optional directory name (which should match current
                            directory)
     @param     pFileNameA  optional file name (which must match a file name in
                            the current directory)
     @param     pDescA      description (which will become the visible portion
                            of the generated link <li></li>)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Item_SetupA (
        ITEM_DATA       *this,
        const
        char            *pDirA,
        const
        char            *pFileNameA,
        const
        char            *pDescA,
        ...
    );


#ifdef  ITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Item_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Item_ToJson (
        ITEM_DATA       *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Item_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Item_ToDebugString (
        ITEM_DATA       *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* ITEM_H */

