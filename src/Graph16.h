// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Graph with 16-Bit Indices (Graph16) Header
//****************************************************************
/*
 * Program
 *			Graph with 16-Bit Indices (Graph16)
 * Purpose
 *			This object provides an Adjacency List Graph using
 *          signed 16-bit indices.  It is assumed that the user
 *          will provide vertex and edge indices with data for
 *          those stored else where. This graph simply contains
 *          the relationship not the vertices or edges themselves.
 *
 * Remarks
 *	1.      After executing Graph16_EdgeSet(), Graph16_RebuildIndex()
 *          needs to be run so that the indices are up to date.
 *
 * References
 *  1.      "A Versatile Data Structure for Edge-oriented Graph Algorithms",
 *          Jurgen Ebert, "Communication of the ACM", June 1987, Volume 30,
 *          Number 6, pp 513-519
 *
 * History
 *	03/11/2020 Generated
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


#ifndef         GRAPH16_H
#define         GRAPH16_H


//#define   GRAPH16_IS_IMMUTABLE     1
#define   GRAPH16_JSON_SUPPORT     1
//#define   GRAPH16_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Graph16_data_s	GRAPH16_DATA;            // Inherits from OBJ
    typedef struct Graph16_class_data_s GRAPH16_CLASS_DATA;   // Inherits from OBJ

    typedef struct Graph16_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Graph16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GRAPH16_DATA *);
    } GRAPH16_VTBL;

    typedef struct Graph16_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Graph16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(GRAPH16_DATA *);
    } GRAPH16_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  GRAPH16_SINGLETON
    GRAPH16_DATA *  Graph16_Shared (
        void
    );

    void            Graph16_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Graph16 object if successful, otherwise OBJ_NIL.
     */
    GRAPH16_DATA *  Graph16_Alloc (
        void
    );
    
    
    OBJ_ID          Graph16_Class (
        void
    );
    
    
    GRAPH16_DATA *  Graph16_New (
        void
    );
    
    
    GRAPH16_DATA *  Graph16_NewWithSizes (
        int16_t         cMaxVertices,
        int16_t         cMaxEdges
    );


#ifdef  GRAPH16_JSON_SUPPORT
    GRAPH16_DATA *  Graph16_NewFromJsonString (
        ASTR_DATA       *pString
    );

    GRAPH16_DATA *  Graph16_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        Graph16_getMaxEdge (
       GRAPH16_DATA     *this
    );


    uint16_t        Graph16_getEdgeUsed (
        GRAPH16_DATA     *this
    );


    uint16_t        Graph16_getVerticesMax (
        GRAPH16_DATA     *this
    );


    /*! Property: Vertices Used
     This is the number of vertices actually used which
     must be less than or equal to the Vertices Maximum
     property.  You can set this higher than the actual
     number used so that those vertices are included in
     certain calculations.  However, you should never
     set it to less than that actually used or greater
     than the Vertices Maximum property.
     */
    uint16_t        Graph16_getVerticesUsed (
        GRAPH16_DATA     *this
    );

    bool            Graph16_setVerticesUsed (
        GRAPH16_DATA    *this,
        uint16_t        value
    );


    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the Identity relationship to this graph (ie every vertex has
     an edge from itself to itself).
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Graph16_AddIdentity (
        GRAPH16_DATA    *this
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Graph16_Assign(pGraph, pGraphOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another GRAPH16 object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Graph16_Assign (
        GRAPH16_DATA     *this,
        GRAPH16_DATA     *pOther
    );


    /*!
     Calculate the Transitive Closure on the graph.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Graph16_Closure (
        GRAPH16_DATA    *this
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Graph16      *pCopy = Graph16_Copy(pGraph);
     @endcode
     @param     this    object pointer
     @return    If successful, a GRAPH16 object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GRAPH16_DATA *  Graph16_Copy (
        GRAPH16_DATA    *this
    );

   
    /*!
    Check to see if an edge exists.
    @param     this    object pointer
    @param     index   Edge Index
    @return    If it exists, ERESULT_SUCCESS, otherwise an ERESULT_*
               error.
    */
    ERESULT         Graph16_EdgeExist (
        GRAPH16_DATA    *this,
        int16_t         index
    );


    /*!
    Check to see if an edge exists.
    @param     this     object pointer
    @param     vFrom    From Vertex Index
    @param     vTo      To Vertex Index
    @return    If it exists, ERESULT_SUCCESS, otherwise an ERESULT_*
               error.
    */
    ERESULT         Graph16_EdgeExistVertices (
        GRAPH16_DATA    *this,
        int16_t         vFrom,
        int16_t         vTo
    );


    /*!
     EdgeFirst() and EdgeNext() let you for-loop through the edges.
     Example:
     @code
            int16_t     i;
            for (i=Graph16_EdgeFirst(pGraph); i; i=Graph16_EdgeNext(pGraph,i)) {
                do_something();
            }
     @endcode
     @param     this    object pointer
     @return    If successful, 1 otherwise 0;
     */
    int16_t         Graph16_EdgeFirst (
        GRAPH16_DATA    *this
    );


    int16_t         Graph16_EdgeNext (
        GRAPH16_DATA    *this,
        int16_t         index
    );


    /*!
    Get an edge's from node index.
    @param     this    object pointer
    @param     index   Edge Index
    @return    If it exists, the node index (relative to 1), otherwise 0.
    */
    int16_t         Graph16_EdgeFrom (
        GRAPH16_DATA    *this,
        int16_t         index
    );


    /*!
    Remove the edge if it exists.
    @param     this    object pointer
    @param     index   Edge Index
    @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
               error.
    */
    ERESULT         Graph16_EdgeRemove(
        GRAPH16_DATA    *this,
        int16_t         index
    );


/*!
     Add the given element to the end of the array.
     @param     this    object pointer
     @param     index   Edge Index (Relative to 1; if 0, next sequential used
                        edge number is used)
     @param     from    From Node Index (Relative to 1)
     @param     to      To Node Index (Relative to 1)
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     @warning   Upon successful completion of this method, Graph16_RebuildIndex()
                needs to be run to update the internal indices. This can wait
                until a group of EdgeSet's without intervening calls to other
                methods.
     */
    ERESULT         Graph16_EdgeSet (
        GRAPH16_DATA    *this,
        int16_t         index,
        int16_t         from,
        int16_t         to
    );


    /*!
    Get an edge's to node index.
    @param     this    object pointer
    @param     index   Edge Index
    @return    If it exists, the node index (relative to 1), otherwise 0.
    */
    int16_t         Graph16_EdgeTo (
        GRAPH16_DATA    *this,
        int16_t         index
    );


    /*!
     Expand the maximum number of edges allowed in this graph.
     @param     this    object pointer
     @param     max     new number of edges allowed
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Graph16_ExpandEdges (
        GRAPH16_DATA    *this,
        int16_t         max
    );


    /*!
     Expand the maximum number of vertices allowed in this graph.
     @param     this    object pointer
     @param     max     new number of vertices allowed
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Graph16_ExpandVertices (
        GRAPH16_DATA    *this,
        int16_t         max
    );


    GRAPH16_DATA *  Graph16_Init (
        GRAPH16_DATA    *this
    );


#ifdef  GRAPH16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Graph16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Graph16_ToJson (
        GRAPH16_DATA   *this
    );
#endif


    void            Graph16_RebuildIndex (
        GRAPH16_DATA    *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Graph16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Graph16_ToDebugString (
        GRAPH16_DATA     *this,
        int             indent
    );
    

    /*!
     VertexFirst() and VertexNext() let you for-loop through the vertices.
     Example:
     @code
            int16_t     v;
            for (v=Graph16_VertexFirst(pGraph); v; v=Graph16_VertexNext(pGraph, v)) {
                do_something();
            }
     @endcode
     @param     this    object pointer
     @return    If successful, vertex_index otherwise 0;
     */
    int16_t         Graph16_VertexFirst (
        GRAPH16_DATA    *this
    );


    int16_t         Graph16_VertexNext (
        GRAPH16_DATA    *this,
        int16_t         index
    );


    /*!
     VertexFromFirst() and VertexFromNext() let you for-loop through
     from/outgoing edges of a vertex.
     Example:
     @code
            int16_t         e;
            int16_t         v;

            for (e=Graph16_VertexFromFirst(pGraph,v); e;
                    e=Graph16_VertexFromNext(pGraph,e)) {
                do_something();
            }
     @endcode
     @param     this    object pointer
     @return    If successful, edge_index otherwise 0;
     */
    int16_t         Graph16_VertexFromFirst (
        GRAPH16_DATA    *this,
        int16_t         vertex
    );


    int16_t         Graph16_VertexFromNext (
        GRAPH16_DATA    *this,
        int16_t         edge
    );


    /*!
     VertexToFirst() and VertexToNext() let you for-loop through
     to/incoming edges of a vertex.
     Example:
     @code
            int16_t         e;
            int16_t         v;

            for (e=Graph16_VertexToFirst(pGraph,v); e;
                    e=Graph16_VertexToNext(pGraph,e)) {
                do_something();
            }
     @endcode
     @param     this    object pointer
     @return    If successful, edge_index otherwise 0;
     */
    int16_t         Graph16_VertexToFirst (
        GRAPH16_DATA    *this,
        int16_t         vertex
    );


    int16_t         Graph16_VertexToNext (
        GRAPH16_DATA    *this,
        int16_t         edge
    );



#ifdef	__cplusplus
}
#endif

#endif	/* GRAPH16_H */

