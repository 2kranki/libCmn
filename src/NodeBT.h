// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A Red-Black Binary Tree of Nodes (NodeBT) Header
//****************************************************************
/*
 * Program
 *			A Red-Black Binary Tree of Nodes (NodeBT)
 * Purpose
 *          This object provides a Red-Black Binary Tree of Nodes.
 *          It is good for a quick indexed list or array of Nodes
 *          with order.
 *
 *          Currently, it does not handle duplicate entries.
 *
 * Remarks
 *    1.      None
 *
 * History
 *  11/22/2018 Generated
 *	01/10/2020 Regenerated
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
#include        <NodeEnum.h>


#ifndef         NODEBT_H
#define         NODEBT_H


#define   NODEBT_JSON_SUPPORT 1
//#define   NODEBT_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    //typedef struct NodeBT_data_s	NODEBT_DATA;            // Inherits from OBJ
    //typedef struct NodeBT_class_data_s NODEBT_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeBT_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeBT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBT_DATA *);
    } NODEBT_VTBL;

    typedef struct NodeBT_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeBT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEBT_DATA *);
    } NODEBT_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODEBT_SINGLETON
    NODEBT_DATA *   NodeBT_Shared (
        void
    );

    void            NodeBT_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeBT object if successful, otherwise OBJ_NIL.
     */
    NODEBT_DATA *   NodeBT_Alloc (
        void
    );
    
    
    OBJ_ID          NodeBT_Class (
        void
    );
    
    
    NODEBT_DATA *   NodeBT_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    NODE_DATA *     NodeBT_getRoot (
        NODEBT_DATA     *this
    );


    uint32_t        NodeBT_getSize(
        NODEBT_DATA     *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given node to the Tree. If duplicates are not allowed, then
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
    ERESULT         NodeBT_Add (
        NODEBT_DATA     *this,
        NODE_DATA       *pNode,
        bool            fReplace
    );

    ERESULT         NodeBT_AddA (
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA,            // UTF-8
        OBJ_ID          pData
    );


    /*!
     Add the given node to the Hash. Duplicates are not allowed.
     @param     this        Object Pointer
     @param     pNode       Data Object Pointer
     @param     fReplace    true == replace current entry if it exists,
                            otherwise, return ERESULT_DATA_ALREADY_EXISTS
                            error.
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         NodeBT_AddUpdate (
        NODEBT_DATA     *this,
        NODE_DATA       *pNode,
        bool            fReplace
    );

    ERESULT         NodeBT_AddUpdateA (
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA,            // UTF-8
        OBJ_ID          pData
    );


    ERESULT         NodeBT_Delete (
        NODEBT_DATA     *this,
        NODE_DATA       *pNode
    );

    ERESULT         NodeBT_DeleteA (
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA
    );


    /*!
     Create an enumerator for the Tree.
     @return    If successful, an ENUM object is returned.  Otherwise,
     OBJ_NIL.
     @warning   Remember to release the returned ENUM object.
     */
    NODEENUM_DATA * NodeBT_Enum (
        NODEBT_DATA     *this
    );


    /*!
     Substitute environment variables into the current string using a BASH-like
     syntax.  Variable names should have the syntax of:
     '$' '{'[a..zA..Z_][a..zA..Z0..9_]* '}'
     or
     '$'[A..Za..z_][A..Za..z0..9_]*
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
                is returned.
     */
    ERESULT         NodeBT_ExpandVars (
        NODEBT_DATA     *this,
        ASTR_DATA       *pStr
    );


    /*!
     Search the Tree for a particular node using the characteristics of
     the given node and its compare function.
     @return    If successful, an NODE object is returned.  Otherwise,
                OBJ_NIL.
     */
    NODE_DATA *     NodeBT_Find (
        NODEBT_DATA     *this,
        NODE_DATA       *pNode
    );

    NODE_DATA *     NodeBT_FindA (
        NODEBT_DATA     *this,
        int32_t         cls,
        const
        char            *pNameA
    );


    /*!
     Scan all the nodes of the Tree in no particular order.
     @return    ERESULT_SUCCESS if successful completion.  Otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         NodeBT_ForEach (
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,               // Used as first parameter of scan method
        void            *pArg3              // Used as third parameter of scan method
    );


    NODEBT_DATA *   NodeBT_Init (
        NODEBT_DATA     *this
    );


    NODEARRAY_DATA * NodeBT_Nodes (
        NODEBT_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeBT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeBT_ToDebugString (
        NODEBT_DATA     *this,
        int             indent
    );
    
    
    ERESULT         NodeBT_VerifyTree (
        NODEBT_DATA     *this
    );


    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         NodeBT_VisitNodesPostRecurse (
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );


    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         NodeBT_VisitNodesInParent (   // Use Parent link (not recursive).
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,
        void            *pArg3
    );

    ERESULT         NodeBT_VisitNodesInRecurse (
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );


    /*! Visit all the nodes in the Tree using a Post-order traversal.
     */
    ERESULT         NodeBT_VisitNodesPreParent (
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,
        void            *pArg3
    );

    ERESULT         NodeBT_VisitNodesPreRecurse (
        NODEBT_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEBT_H */

