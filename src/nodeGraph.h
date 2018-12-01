// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//         A Graph of Nodes (nodeGraph) Header
//****************************************************************
/*
 * Program
 *			A Graph of Nodes (nodeGraph)
 * Purpose
 *			This object provides a directed graph of Nodes. A Graph
 *          consists of a set of Nodes with Arcs defining the
 *          relationship between the various nodes.
 *
 * Remarks
 *	1.      "Acyclic" means that there are no cycles within the graph
 *          (ie no arcs form loops) and is a characterisitic of Trees
 *          and Forests.
 *  2.      If the graph is "directed" (default), it is a graph in
 *          which each arc denotes a one-way connection. An "undirected"
 *          graph is one in which each arc denotes a two-way connection
 *          between the two nodes. This property must be set prior to
 *          adding any arcs to the graph.
 *
 * History
 *	07/14/2016 Generated
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
#include        <nodeLink.h>
#include        <nodeHash.h>
#include        <objArray.h>


#ifndef         NODEGRAPH_H
#define         NODEGRAPH_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    // NODEGRAPH_DATA is defined in node.h

    typedef struct nodeGraph_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in nodeGraph_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(NODEGRAPH_DATA *);
    } NODEGRAPH_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to nodeGraph object if successful, otherwise OBJ_NIL.
     */
    NODEGRAPH_DATA * nodeGraph_Alloc(
        void
    );
    
    
    NODEGRAPH_DATA * nodeGraph_New(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     Arcs property is an array of all the arcs in the graph. If this
     is a directed graph, then the arcs are one way.  Otherwise, the
     arcs represent a two-way connection.  All objects within the
     array should be the Node Arc object.
     */
    OBJARRAY_DATA * nodeGraph_getArcs(
        NODEGRAPH_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint32_t        nodeGraph_ArcAdd(
        NODEGRAPH_DATA  *this,
        NODELINK_DATA   *pFrom,             // [in] From Node
        NODELINK_DATA   *pTo,               // [in] To Node
        const
        char            *pName              // [in] Optional Name or NULL
    );
    
    
    NODEGRAPH_DATA * nodeGraph_Init(
        NODEGRAPH_DATA  *this
    );


    ERESULT         nodeGraph_NodeAdd(
        NODEGRAPH_DATA  *this,
        NODELINK_DATA   *pNode              // [in] node pointer
    );

    ERESULT         nodeGraph_NodeAddA(
        NODEGRAPH_DATA  *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    );

    
    NODE_DATA *     nodeGraph_FindA(
        NODEGRAPH_DATA  *this,
        int32_t         cls,
        const
        char            *pName
    );

    
    /*!
     Return an array of all nodes in the graph sorted by name in
     ascending order.
     @param     this    Object Pointer
     @return    NodeArray object pointer which must be released if
                successful.  Otherwise, OBJ_NIL and object's error
                code is set to the specific error.
     @warning   Remember to release the returned object.
     */
    NODEARRAY_DATA * nodeGraph_Nodes(
        NODEGRAPH_DATA  *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = nodeGraph_ToDebugString(pObj,4);
     @endcode
     @param     this    nodeGraph object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    nodeGraph_ToDebugString(
        NODEGRAPH_DATA  *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* NODEGRAPH_H */

