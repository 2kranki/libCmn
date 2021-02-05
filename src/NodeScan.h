// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Node Tree Scanner (NodeScan) Header
//****************************************************************
/*
 * Program
 *			Node Tree Scanner (NodeScan)
 * Purpose
 *          This object supports scanning a NodeTree that was con-
 *          verted to a NodeArray with up/down members. See
 *          nodeTree_ToLinearizationPost() or
 *          nodeTree_ToLinearizationPre().
 *
 * Remarks
 *	1.      None
 *
 * History
 *  10/16/2015 Generated
 *	12/17/2019 Regenerated
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
#include        <Node.h>
#include        <NodeTree.h>


#ifndef         NODESCAN_H
#define         NODESCAN_H


//#define   NODESCAN_JSON_SUPPORT 1
//#define   NODESCAN_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // See Node.h
    //typedef struct NodeScan_data_s	NODESCAN_DATA;            // Inherits from OBJ
    //typedef struct NodeScan_class_data_s NODESCAN_CLASS_DATA;   // Inherits from OBJ

    typedef struct NodeScan_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeScan_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODESCAN_DATA *);
    } NODESCAN_VTBL;

    typedef struct NodeScan_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in NodeScan_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODESCAN_DATA *);
    } NODESCAN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  NODESCAN_SINGLETON
    NODESCAN_DATA * NodeScan_Shared (
        void
    );

    bool            NodeScan_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to NodeScan object if successful, otherwise OBJ_NIL.
     */
    NODESCAN_DATA * NodeScan_Alloc (
        void
    );
    
    
    OBJ_ID          NodeScan_Class (
        void
    );
    
    
    NODESCAN_DATA * NodeScan_New (
        void
    );
    
    
    NODESCAN_DATA * NodeScan_NewFromArray(
        NODETREE_DATA   *pTree,
        OBJARRAY_DATA   *pArray     // Tree converted to array with up/down members.
    );


    // Convert the tree to a postorder array and
    // create a scanner from that.
    NODESCAN_DATA * NodeScan_NewFromTreePost(
        NODETREE_DATA   *pTree
    );


    // Convert the tree to a preorder array and
    // create a scanner from that.
    NODESCAN_DATA * NodeScan_NewFromTreePre(
        NODETREE_DATA   *pTree
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJARRAY_DATA * NodeScan_getArray(
        NODESCAN_DATA   *this
    );

    bool            NodeScan_setArray(
        NODESCAN_DATA   *this,
        OBJARRAY_DATA   *pValue
    );


    NODELINK_DATA * NodeScan_getCloseNode(
        NODESCAN_DATA   *this
    );


    /*!
     All matching and scanning uses the index property
     to know where to start the next match or scan.
     */
    uint32_t        NodeScan_getIndex(
        NODESCAN_DATA   *this
    );

    bool            NodeScan_setIndex(
        NODESCAN_DATA   *this,
        uint32_t        value
    );


    NODELINK_DATA * NodeScan_getOpenNode(
        NODESCAN_DATA   *this
    );


    /*!
     All matching and scanning set the start property
     to indicate where the scan started.
     */
    uint32_t        NodeScan_getStart(
        NODESCAN_DATA   *this
    );


    NODETREE_DATA * NodeScan_getTree(
        NODESCAN_DATA   *this
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    NODESCAN_DATA * NodeScan_Init (
        NODESCAN_DATA   *this
    );


    /*!
     Advance the scan the provided number of nodes.
     @param     this    Object Pointer
     @param     numChrs The number of nodes to advance over
     @return    If successful, the current node, otherwise OBJ_NIL
                and Last Error contains an error reason.
     */
    NODELINK_DATA * NodeScan_InputAdvance(
        NODESCAN_DATA   *this,
        uint32_t        numChrs
    );

    
    /*!
     Provide the node that is the provided number of nodes ahead of the current
     one without affecting the current index or node.
     @param     this    Object Pointer
     @param     num     The number of nodes to look ahead
     @return    If successful, the node in advance of the current one, otherwise
                OBJ_NIL and Last Error contains an error reason.
     */
    NODELINK_DATA * NodeScan_InputLookAhead(
        NODESCAN_DATA   *this,
        uint32_t        num
    );

    
    NODELINK_DATA * NodeScan_MatchName(
        NODESCAN_DATA   *this,
        char            *pStr
    );

    
    NODELINK_DATA * NodeScan_MatchClass(
        NODESCAN_DATA   *this,
        int32_t         cls
    );

    
    NODELINK_DATA * NodeScan_MatchClasses(
        NODESCAN_DATA   *this,
        int32_t         *pSet
    );
    
    
    /*!
     Scan the linerarized tree matching a regex-like array of types.
     @param     this    Object Pointer
     @param     pRegex  Pointer to a variable length array of node types which must
                        not be zero followed by a zero to terminate the list.
     @return    If successful, a starting index of the match relative to 1,
                otherwise 0.
     */
    NODELINK_DATA * NodeScan_MatchClassesRegex(
        NODESCAN_DATA   *this,
        int32_t         *pRegex             // [in] Zero-terminated array of
                                            //      node types
    );
    
    
    /*!
     Scan the linearized tree starting at the given index and stopping when the
     given class is found or at the end of the tree.
     @param     this    Object Pointer
     @param     cls     The node class to stop at (must not be zero)
     @return    If successful, an index of the match relative to 1,
                otherwise 0.
     */
    NODELINK_DATA * NodeScan_ScanClassUntil(
        NODESCAN_DATA   *this,
        int32_t         cls
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeScan_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    NodeScan_ToDebugString (
        NODESCAN_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODESCAN_H */

