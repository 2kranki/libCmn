// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//           Json Input Parsing Support (JsonIn) Header
//****************************************************************
/*
 * Program
 *			Json Input Parsing Support (JsonIn)
 * Purpose
 *          This object provides a standardized way of parsing an
 *          HJSON node tree. The support routines help the individual
 *          object's JSON parser to successfully find specific nodes
 *          in HJSON node trees.
 *
 *          In particular, it is capable of properly parsing
 *          sub-objects within the HSON tree as well as general
 *          parsing of objects that are unknown to begin with.
 *
 *
 * Remarks
 *  1.      The ParseObject() method requires that all classes
 *          to be parsed by it must be previously defined.
 *  2.      Warning - Using this object will require memory for
 *          all object methods being called by ParseObject().
 *
 * History
 *  12/21/2017 Generated
 *	12/30/2019 Regenerated
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
#include        <false.h>
#include        <node.h>
#include        <NodeHash.h>
#include        <null.h>
#include        <true.h>


#ifndef         JSONIN_H
#define         JSONIN_H


//#define   JSONIN_JSON_SUPPORT 1
//#define   JSONIN_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct JsonIn_data_s	JSONIN_DATA;            // Inherits from OBJ
    typedef struct JsonIn_class_data_s JSONIN_CLASS_DATA;   // Inherits from OBJ

    typedef struct JsonIn_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in JsonIn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONIN_DATA *);
    } JSONIN_VTBL;

    typedef struct JsonIn_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in JsonIn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(JSONIN_DATA *);
    } JSONIN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  JSONIN_SINGLETON
    JSONIN_DATA *   JsonIn_Shared (
        void
    );

    void            JsonIn_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to JsonIn object if successful, otherwise OBJ_NIL.
     */
    JSONIN_DATA *   JsonIn_Alloc (
        void
    );
    
    
    OBJ_ID          JsonIn_Class (
        void
    );
    
    
    JSONIN_DATA *   JsonIn_New (
        void
    );
    
    
    JSONIN_DATA *   JsonIn_NewFromAStr(
        ASTR_DATA       *pStr
    );

    JSONIN_DATA *   JsonIn_NewFromHash(
        NODEHASH_DATA   *pHash
    );

    JSONIN_DATA *   JsonIn_NewFromPath(
        PATH_DATA       *pPath
    );


    /*!
     Check the given node's data for a node array and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the node array; otherwise OBJ_NIL.
     */
    NODEARRAY_DATA * JsonIn_CheckNodeDataForArray(
        NODE_DATA       *pNode
    );


    FALSE_DATA *     JsonIn_CheckNodeDataForFalse(
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a float object and return the string
     representation of the integer if found.
     @param     pNode   the given node pointer
     @return    If successful, the string object; otherwise OBJ_NIL.
     */
    ASTR_DATA *     JsonIn_CheckNodeDataForFloat (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a node hash and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the node hash; otherwise OBJ_NIL.
     */
    NODEHASH_DATA * JsonIn_CheckNodeDataForHash(
         NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for an integer object and return the string
     representation of the integer if found.
     @param     pNode   the given node pointer
     @return    If successful, the string object; otherwise OBJ_NIL.
     */
    ASTR_DATA *     JsonIn_CheckNodeDataForInteger (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a null object and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the null object; otherwise OBJ_NIL.
     */
    NULL_DATA *     JsonIn_CheckNodeDataForNull (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a string and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the string; otherwise OBJ_NIL.
     */
    ASTR_DATA *     JsonIn_CheckNodeDataForString (
        NODE_DATA       *pNode
    );


    TRUE_DATA *     JsonIn_CheckNodeDataForTrue (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a node array and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the node array; otherwise OBJ_NIL.
     */
    NODEARRAY_DATA * JsonIn_CheckNodeForArray (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a false object (ie node's
     data) and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the false object; otherwise OBJ_NIL.
     */
    FALSE_DATA *     JsonIn_CheckNodeForFalse (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a float object and
     return the string representation of the integer if found.
     @param     pNode   the given node pointer
     @return    If successful, the string object; otherwise OBJ_NIL.
     */
    ASTR_DATA *     JsonIn_CheckNodeForFloat (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node for a string (ie data object is an
     ASTR_DATA object) and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the string; otherwise OBJ_NIL.
     */
    NODEHASH_DATA * JsonIn_CheckNodeForHash (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for an integer object and
     return the string representation of the integer if found.
     @param     pNode   the given node pointer
     @return    If successful, the string object; otherwise OBJ_NIL.
     */
    ASTR_DATA *     JsonIn_CheckNodeForInteger (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a null object and return
     it if found.
     @param     pNode   the given node pointer
     @return    If successful, the null object; otherwise OBJ_NIL.
     */
    NULL_DATA *     JsonIn_CheckNodeForNull (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a string object and
     return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the string; otherwise OBJ_NIL.
     */
    ASTR_DATA *     JsonIn_CheckNodeForString (
        NODE_DATA       *pNode
    );


    /*!
     Check the given node's data for a true object (ie node's
     data) and return it if found.
     @param     pNode   the given node pointer
     @return    If successful, the true object; otherwise OBJ_NIL.
     */
    TRUE_DATA *     JsonIn_CheckNodeForTrue (
        NODE_DATA       *pNode
    );


    NODE_DATA *     JsonIn_NodeFromArray (
        NODEARRAY_DATA  *pArray
    );


    NODE_DATA *     JsonIn_NodeFromHash (
        NODEHASH_DATA   *pHash
    );


    NODE_DATA *     JsonIn_NodeFromString (
        ASTR_DATA       *pStr
    );





    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODE_DATA *     JsonIn_getFileNode (
        JSONIN_DATA     *this
    );


    NODEHASH_DATA * JsonIn_getHash (
        JSONIN_DATA     *this
    );

    bool            JsonIn_setHash (
        JSONIN_DATA     *this,
        NODEHASH_DATA   *pValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Finds "objectType" in the highest level of the JSON Hash Node tree
     and insures that it contains the Type provided.
     @param     this    Object Pointer
     @param     pTypeA  Type Name to be searched for
     @return    If objectType contains the type name (ERESULT_SUCCESS);
                otherwise, an ERESULT_* error code.
     */
    ERESULT         JsonIn_ConfirmObjectType (
        JSONIN_DATA     *this,
        const
        char            *pTypeA
    );


    /*!
     Find a named node in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of Node to be looked for
     @param     pTypeA  Name of Data Node ("array", "false", "hash",
                        "integer", "null", or "true")
     @param     ppData  Pointer to Data Object Pointer to be returned if
                        ERESULT_SUCCESS is returned.
     @return    If successful, ERESULT_SUCCESS and an integer value in *pInt
                if pInt is non-null, otherwise, ERESULT_* error code.
     */
    ERESULT         JsonIn_FindNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        const
        char            *pTypeA,
        OBJ_ID          *ppData
    );


    /*!
     Find a named node array in the JSON Hash Node tree and apply the given
     method to each array node.
     @param     this        Object Pointer
     @param     pSectionA   Name of integer value (required)
     @param     pObj        Object Pointer for the apply method
     @param     pVisitNode  Method Pointer to execute for each member of the array. If
                            this method returns an ERESULT_* error, then processing is
                            halted and that error code is returned to the caller of this
                            method.
     @return    If successful, ERESULT_SUCCESS and a node array pointer in *ppArray
                if ppArray is non-null.  Otherwise, ERESULT_* error code.
     */
    ERESULT         JsonIn_FindArrayAndVisitInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        ERESULT         (*pVisitNode)(OBJ_ID, NODE_DATA *),
        OBJ_ID          *pObj
    );


    /*!
     Find a named node array in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     ppArray Pointer to a node array pointer where data is to be returned if
                ERESULT_SUCCESS is returned.
     @return    If successful, ERESULT_SUCCESS and a node array pointer in *ppArray
                if ppArray is non-null.  Otherwise, ERESULT_* error code.
     */
    ERESULT         JsonIn_FindArrayNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        NODEARRAY_DATA  **ppArray
    );


    ERESULT         JsonIn_FindFloatNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        double          *pFloat
    );


    /*!
     Find a named integer value in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     pInt    integer pointer where data is to be returned too if
                        succesful ERESULT is returned.
     @return    If successful, ERESULT_SUCCESS and an integer value in *pInt
                if pInt is non-null, otherwise, ERESULT_* error code.
     */
    ERESULT         JsonIn_FindIntegerNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        int64_t         *pInt
    );


    ERESULT         JsonIn_FindNullNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA
    );


    /*!
     Find a named string value in the JSON Hash Node tree.
     @param     this    Object Pointer
     @param     pSectionA Name of integer value (required)
     @param     ppStr   Pointer to a string pointer to be returned if
                        ERESULT_SUCCESS is returned and this pointer
                        is non-null.
     @return    If successful, ERESULT_SUCCESS and an sting value in *ppStr
                if ppStr is non-null. Otherwise, an ERESULT_* error code.
     */
    ERESULT         JsonIn_FindStringNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        ASTR_DATA       **ppStr
    );


    JSONIN_DATA *   JsonIn_Init (
        JSONIN_DATA     *this
    );


    /*!
     Parse the given input string using the HJSON parser and set up
     the returned node structure to be analyzed by other methods
     in this object. The parser is called with a default tab space
     of 4.
     @param     this    object pointer
     @param     pStr    pointer to AStr input string (required)
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code
     */
    ERESULT         JsonIn_ParseAStr (
        JSONIN_DATA     *this,
        ASTR_DATA       *pStr
    );


    /*!
     Parse an object from the current JSON Node tree using the object's
     class to call the specific JSON Input parsers for that class.
     @param     this    object pointer
     @return    If successful, a new object pointer and the last error is
                set to ERESULT_SUCCESS, otherwise, OBJ_NIL and the last
                error is set to an ERESULT_* error code
     */
    OBJ_ID          JsonIn_ParseObject (
        JSONIN_DATA     *this
    );


    /*!
     Parse the given input file using the HJSON parser and set up
     the returned node structure to be analyzed by other methods
     in this object. The parser is called with a default tab space
     of 4.
     @param     this    object pointer
     @param     pPath   File Path to be parsed (required)
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code
     */
    ERESULT         JsonIn_ParsePath(
        JSONIN_DATA     *this,
        PATH_DATA       *pPath
    );


    /*!
     Restore the JSON Node Tree that was saved from a prior call to the method,
     SubobjectInHash().
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code
     */
    ERESULT         JsonIn_SubObjectEnd (
        JSONIN_DATA     *this
    );


    /*!
     Set up the parser to process a JSON Hash Node tree by:
     *  Pushing the current JSON tree on the internal stack.
     *  Setting up the given JSON Hash Node as the parser input.
     @param     this    Object Pointer
     @param     pHash   JSON Hash Node (required)
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code.
     @warning   The SubobjectEnd() method should be called once the sub-object
                is parsed.
     */
    ERESULT         JsonIn_SubObjectFromHash (
        JSONIN_DATA     *this,
        NODEHASH_DATA   *pHash
    );


    /*!
     Set up the parser to process a sub-object of the JSON Node tree by:
     *  Pushing the current JSON tree on the internal stack.
     *  Setting up the found section as the parser input.
     @param     this    object pointer
     @param     pSect   Section Name String (required)
     @return    If successful, ERESULT_SUCCESS, otherwise, ERESULT_* error code.
     @warning   The SubobjectEnd() method should be called once the sub-object
                is parsed.
     */
    ERESULT         JsonIn_SubObjectInHash (
        JSONIN_DATA     *this,
        const
        char            *pSect
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = JsonIn_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    JsonIn_ToDebugString (
        JSONIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* JSONIN_H */

