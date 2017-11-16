// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          NODEARRAY Console Transmit Task (nodeArray) Header
//****************************************************************
/*
 * Program
 *				Array of Node Pointers (nodeArray)
 * Purpose
 *				This object provides an array of node pointers. It
 *              does not store the actual node, just a pointer to
 *              it.
 *
 * Remarks
 *	1.      You can create a Queue of Nodes by using AddToTop() 
 *          to add nodes to the queue and DeleteFromBottom() to 
 *          remove nodes from the queue.
 *	2.      You can create a Stack of Nodes by using AddToTop() 
 *          to add nodes to the stack and DeleteFromTop() to
 *          remove nodes from the stack.
 *
 * History
 *	08/08/2015 Generated
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
#include        <enum.h>
#include        <node.h>


#ifndef         NODEARRAY_H
#define         NODEARRAY_H 1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

    typedef struct nodeArray_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } NODEARRAY_VTBL;
    
    




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    NODEARRAY_DATA * nodeArray_Alloc(
        void
    );
    
    
    /*!
     Search the given NULL-terminated Set of Nodes for a node that
     matches the given node using the comparison routine provided.
     @return    If successful, the node that matches from the list,
                 otherwise OBJ_NIL.
     */
    NODE_DATA *     nodeArray_MatchSet(
        int             (*pCompare)(NODE_DATA *,NODE_DATA *),
        NODE_DATA       *pNode,
        NODE_DATA       **ppNodeSet         // NULL-terminated Set of Nodes
    );
    
    
    NODEARRAY_DATA * nodeArray_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            nodeArray_setCompare(
        NODEARRAY_DATA  *this,
        int             (*pCompare)(NODE_DATA *,NODE_DATA *)
    );
    
    
    uint32_t        nodeArray_getSize(
        NODEARRAY_DATA	*this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         nodeArray_AddToTop(
        NODEARRAY_DATA	*this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    );
    
    
    /*!
     Append the contents of the other array to this array. This is
     the same as AddToTop() of each element of the other array.
     @return    If successful, return ERESULT_SUCCESSFUL_COMPLETION
                otherwise an eResult error code.
     */
    ERESULT         nodeArray_Append(
        NODEARRAY_DATA	*this,
        NODEARRAY_DATA	*pOther
    );
    
    ERESULT         nodeArray_AppendNode(
        NODEARRAY_DATA	*this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    );
    
    
    
    /*!
     Assign the contents of this array to the other array. The
     contents of the other array are released. Then we simply
     retain them so that they are in both arrays.
     @return    If successful, return ERESULT_SUCCESSFUL_COMPLETION
                otherwise an eResult error code.
     */
    ERESULT         nodeArray_Assign(
        NODEARRAY_DATA	*this,
        NODEARRAY_DATA	*pOther
    );
    
    
    /*!
     Copy this array. Any element of the array that has a copy method
     will have that used to create a new object. Otherwise, the object
     is just retained and added to the new array.
     @return    If successful, return a new array that must be released
                 otherwise return OBJ_NIL.
     */
    NODEARRAY_DATA * nodeArray_Copy(
        NODEARRAY_DATA	*this
    );
    
    
    /*!
     Remove the index'th element from the array and return it.
     @return    If successful, an object pointer, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODE_DATA *     nodeArray_Delete(
        NODEARRAY_DATA	*this,
        uint32_t        index
    );
    
    
    // DeleteFromBottom() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    NODE_DATA *     nodeArray_DeleteFirst(
        NODEARRAY_DATA	*this
    );
    
    
    // DeleteFromTop() returns the top element after deleting it,
    // but not releasing it. It needs to be released before it is
    // discarded.
    NODE_DATA *     nodeArray_DeleteLast(
        NODEARRAY_DATA	*this
    );
    
    
    /*! Create an enumerator for the array.
     @return    If successful, an ENUM object is returned.  Otherwise,
                 OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    ENUM_DATA *     nodeArray_Enum(
        NODEARRAY_DATA  *this
    );
    
    
    /*!
     Find the first occurrence of a node in the array by name.
     @return    If successful, ERESULT_SUCCESSFUL_COMPLETION is returned and
                ppNode will contain the node ptr otherwise an error code
                will be returned.
     */
    ERESULT         nodeArray_FindA(
        NODEARRAY_DATA   *this,
        const
        char             *pName,
        NODE_DATA        **ppNode
    );
    
    
    NODE_DATA *     nodeArray_Get(
        NODEARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    );
    
    NODE_DATA *     nodeArray_GetFirst(
        NODEARRAY_DATA  *this
    );
    
    NODE_DATA *     nodeArray_GetLast(
        NODEARRAY_DATA	*this
    );
    
    
    NODEARRAY_DATA * nodeArray_Init(
        NODEARRAY_DATA  *this
    );


    ERESULT         nodeArray_SortAscending(
        NODEARRAY_DATA	*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeArray_ToDebugString(
        NODEARRAY_DATA	*this,
        int             indent
    );
    
    
    ERESULT         nodeArray_VisitAscending(
        NODEARRAY_DATA	*this,
        void            (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *         // Current Node
                        ),
        OBJ_ID          pObject
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEARRAY_H */

