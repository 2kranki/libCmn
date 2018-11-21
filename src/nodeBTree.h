// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Binary Tree of Nodes (nodeBTree) Header
//****************************************************************
/*
 * Program
 *			Binary Tree of Nodes (nodeBTree)
 * Purpose
 *			This object provides support for a binary tree of nodes.
 * Remarks
 *	1.      None
 *
 * History
 *	11/12/2018 Generated
 *
 * References
 *  * "Data Structures Using C", Tenenbaum, Langsam and Augenstein, Prentice-Hall,
 *      1990, ISBN: 0-13-199746-7
 *  * "The Art of Computer Programming - Searching and Sorting, 2nd Edition ", Knuth,
 *      Addison-Wesley, 1998, ISBN: 0-201-89685-0
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
#include        <nodeLnkP.h>


#ifndef         NODEBTREE_H
#define         NODEBTREE_H


//#define   NODEBTREE_SINGLETON    1

#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************



    typedef struct nodeBTree_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeBTree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBTREE_DATA *);
    } NODEBTREE_VTBL;

    typedef struct nodeBTree_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeBTree_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBTREE_DATA *);
    } NODEBTREE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEBTREE_SINGLETON
    NODEBTREE_DATA *     nodeBTree_Shared(
        void
    );

    bool            nodeBTree_SharedReset(
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeBTree object if successful, otherwise OBJ_NIL.
     */
    NODEBTREE_DATA * nodeBTree_Alloc(
        void
    );
    
    
    OBJ_ID          nodeBTree_Class(
        void
    );
    
    
    NODEBTREE_DATA * nodeBTree_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODELNKP_DATA * nodeBTree_getRoot(
        NODEBTREE_DATA  *this
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given node to the Hash. If duplicates are not allowed, then
     the node's name must not exist in the Hash.  Otherwise, the node will
     be added to the head of the Hash list effectively blocking access to
     other nodes with the same name.  The A versions creates a node from
     the data given before trying to add it to the Hash.
     @param     this        Object Pointer
     @param     pNode       Data Object Pointer
     @param     fReplace    true == replace current entry if it exists,
                            otherwise, return ERESULT_DATA_ALREADY_EXISTS
                            error.
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
     error code is returned.
     */
    ERESULT         nodeBTree_Add(
        NODEBTREE_DATA  *this,
        NODELNKP_DATA   *pNode,
        bool            fReplace
    );
    
    ERESULT         nodeBTree_AddA(
        NODEBTREE_DATA  *this,
        int32_t         cls,
        const
        char            *pNameA,            // UTF-8
        OBJ_ID          pData
    );
    
    
    NODE_DATA *     nodeBTree_FindA(
        NODEBTREE_DATA  *this,
        int32_t         cls,
        const
        char            *pNameA            // UTF-8
    );

   
    NODELNKP_DATA * nodeBTree_First(
        NODEBTREE_DATA  *this
    );
    
    
    NODEBTREE_DATA * nodeBTree_Init(
        NODEBTREE_DATA  *this
    );


    ERESULT         nodeBTree_InOrderTraversal(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,
        void            *pArg3
    );
    
    
    NODELINK_DATA * nodeBTree_Node(
        NODEBTREE_DATA  *this,
        uint32_t        index       // Relative to 1
    );
    
    
    ERESULT         nodeTree_Nodes(
        NODEBTREE_DATA  *this,
        NODEARRAY_DATA  **ppNodes
    );
    
    
    ERESULT         nodeBTree_PreOrderTraversal(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,
        void            *pArg3
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeBTree_ToDebugString(this,4);
     @endcode 
     @param     this    NODEBTREE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeBTree_ToDebugString(
        NODEBTREE_DATA  *this,
        int             indent
    );
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTree_VisitNodesPostRecurse(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );

    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTree_VisitNodesInParent(   // Use Parent link (not recursive).
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,
        void            *pArg3
    );
    
    ERESULT         nodeBTree_VisitNodesInRecurse(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         nodeBTree_VisitNodesPreRecurse(
        NODEBTREE_DATA  *this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEBTREE_H */

