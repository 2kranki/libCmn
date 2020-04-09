// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Graph16.c
 *	Generated 03/11/2020 17:37:49
 *
 * Todo:
 *  *       Add Identity relationship.
 *  *       Add Reflexive-Transitive Closure
 *  *       Add DFS(vertex)
 *  *       Add BFS(vertex)
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <Graph16_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

#   define EdgeGet(index)        this->pEdges[this->edgesMax + index]
#   define EdgeSet(index,value)  this->pEdges[this->edgesMax + index] = value
#   define FirstGet(index)       this->pFirst[index]
#   define FirstSet(index,value) this->pFirst[index] = value
#   define NextGet(index)        this->pNext[this->edgesMax + index]
#   define NextSet(index,value)  this->pNext[this->edgesMax + index] = value


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                      I n d e x
    //---------------------------------------------------------------

    uint16_t        Graph16_IndexFrom (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        uint16_t        value = this->edgesMax;

        value -= index;
        value++;

        // Return to caller.
        return value;
    }


    uint16_t        Graph16_IndexTo (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        uint16_t        value = this->edgesMax;

        value += index;
        value++;

        // Return to caller.
        return value;
    }


    uint16_t        Graph16_MaxToActual (
        int16_t         max
    )
    {
        return ((max << 1) + 1);
    }


    void            Graph16_RebuildIndex (
        GRAPH16_DATA    *this
    )
    {
        int16_t         e;
        int16_t         v;

        if ((OBJ_NIL == this->pFirst) || (OBJ_NIL == this->pNext)) {
            return;
        }

        for (v=Graph16_VertexFirst(this); v > 0; v=Graph16_VertexNext(this, v)) {
            FirstSet(v, 0);
        }

        for (e=this->edgesMax; e > 0; e--) {
            Graph16_UpdateIndex(this, e);
        }

        // Return to caller.
    }



    void            Graph16_UpdateIndex (
        GRAPH16_DATA    *this,
        int16_t         e
    )
    {
        int16_t         e2;
        int16_t         v;

        if ((OBJ_NIL == this->pFirst) || (OBJ_NIL == this->pNext)) {
            return;
        }
        if (e < 0)
            e = -e;

        // Edge From node
        v = EdgeGet(-e);
        if (v) {
            // Link edge to top of vertex From List.
            e2 = FirstGet(v);
            NextSet(e, e2);
            FirstSet(v, e);
        }
        // Edge To node
        v = EdgeGet(e);
        if (v) {
            // Link edge to top of vertex To List.
            e2 = FirstGet(v);
            NextSet(-e, e2);
            FirstSet(v, -e);
        }

        // Return to caller.
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GRAPH16_DATA *     Graph16_Alloc (
        void
    )
    {
        GRAPH16_DATA    *this;
        uint32_t        cbSize = sizeof(GRAPH16_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GRAPH16_DATA *     Graph16_New (
        void
    )
    {
        GRAPH16_DATA       *this;
        
        this = Graph16_Alloc( );
        if (this) {
            this = Graph16_Init(this);
        } 
        return this;
    }



    GRAPH16_DATA *  Graph16_NewWithSizes (
        int16_t         cMaxVertices,
        int16_t         cMaxEdges
    )
    {
        GRAPH16_DATA    *this;
        ERESULT         eRc;

        this = Graph16_New( );
        if (this) {
            eRc = Graph16_ExpandVertices(this, cMaxVertices);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
            eRc = Graph16_ExpandEdges(this, cMaxEdges);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          E d g e
    //---------------------------------------------------------------
    
    uint16_t        Graph16_getEdgeMax (
        GRAPH16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->edgesMax;
    }


    bool            Graph16_setEdgeMax (
        GRAPH16_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->edgesMax = value;

        return true;
    }


    uint16_t        Graph16_getEdgeUsed (
        GRAPH16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->edgesUsed;
    }


    bool            Graph16_setEdgeUsed (
        GRAPH16_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->edgesUsed = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Graph16_getSize (
        GRAPH16_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Graph16_getSuperVtbl (
        GRAPH16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                     V e r t i c e s
    //---------------------------------------------------------------

    uint16_t        Graph16_getVerticesMax (
        GRAPH16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->verticesMax;
    }


    bool            Graph16_setVerticesMax (
        GRAPH16_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->verticesMax = value;

        return true;
    }


    uint16_t        Graph16_getVerticesUsed (
        GRAPH16_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->verticesUsed;
    }


    bool            Graph16_setVerticesUsed (
        GRAPH16_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->verticesUsed = value;

        return true;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                 A d d  I d e n t i t y
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
    )
    {
        //ERESULT         eRc;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=1; i <= this->verticesUsed; i++) {
            if (!Graph16_EdgeExistVertices(this, i, i)) {
                Graph16_EdgeSet(this, 0, i, i);
            }
        }

        obj_Disable(this);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Graph16_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another GRAPH16 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Graph16_Assign (
        GRAPH16_DATA	*this,
        GRAPH16_DATA    *pOther
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Graph16_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
        if (pOther->pEdges) {
            mem_Free(pOther->pEdges);
            pOther->pEdges = NULL;
        }
        if (pOther->pNext) {
            mem_Free(pOther->pNext);
            pOther->pNext = NULL;
        }
        if (pOther->pFirst) {
            mem_Free(pOther->pFirst);
            pOther->pFirst = NULL;
        }
        pOther->edgesMax = 0;
        pOther->edgesUsed = 0;
        pOther->verticesMax = 0;
        pOther->verticesUsed = 0;

        // Create a copy of objects and areas in this object placing
        // them in other.

        // Copy other data from this object to other.
        eRc = Graph16_ExpandEdges(pOther, this->edgesMax);
        eRc = Graph16_ExpandVertices(pOther, this->verticesMax);
        memcpy(
               pOther->pEdges,
               this->pEdges,
               (Graph16_MaxToActual(this->edgesMax) * sizeof(int16_t))
        );
        memcpy(
               pOther->pNext,
               this->pNext,
               (Graph16_MaxToActual(this->edgesMax) * sizeof(int16_t))
        );
        memcpy(
               pOther->pFirst,
               this->pFirst,
               (this->edgesMax * sizeof(int16_t))
        );
        pOther->edgesMax = this->edgesMax;
        pOther->edgesUsed = this->edgesUsed;
        pOther->verticesMax = this->verticesMax;
        pOther->verticesUsed = this->verticesUsed;

        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     C l o s u r e
    //---------------------------------------------------------------

    /*!
     Calculate the Transitive Closure on the graph.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Graph16_Closure (
        GRAPH16_DATA    *this
    )
    {
        //ERESULT         eRc;
        bool            fChanged = true;
        uint32_t        cAdded = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        while (fChanged) {
            int16_t         v1;
            fChanged = false;
            for (v1=Graph16_VertexFirst(this);
                 v1;
                 v1=Graph16_VertexNext(this, v1)) {
                int16_t         v2;
                for (v2=Graph16_VertexFromFirst(this,v1);
                     v2;
                     v2=Graph16_VertexFromNext(this, v2)) {
                    int16_t         v3;
                    for (v3=Graph16_VertexFromFirst(this,v2);
                         v3;
                         v3=Graph16_VertexFromNext(this, v3)) {
                        if (!Graph16_EdgeExistVertices(this, v1, v3)) {
                            Graph16_EdgeSet(this, 0, v1, v3);
                            fChanged = true;
                            cAdded++;
                        }
                    }
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Graph16_Compare (
        GRAPH16_DATA     *this,
        GRAPH16_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Graph16_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Graph16      *pCopy = Graph16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a GRAPH16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GRAPH16_DATA *     Graph16_Copy (
        GRAPH16_DATA       *this
    )
    {
        GRAPH16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef GRAPH16_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Graph16_New( );
        if (pOther) {
            eRc = Graph16_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Graph16_Dealloc (
        OBJ_ID          objId
    )
    {
        GRAPH16_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GRAPH16_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pEdges) {
            mem_Free(this->pEdges);
            this->pEdges = NULL;
        }
        if (this->pNext) {
            mem_Free(this->pNext);
            this->pNext = NULL;
        }
        if (this->pFirst) {
            mem_Free(this->pFirst);
            this->pFirst = NULL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Graph16      *pDeepCopy = Graph16_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a GRAPH16 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GRAPH16_DATA *     Graph16_DeepyCopy (
        GRAPH16_DATA       *this
    )
    {
        GRAPH16_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Graph16_New( );
        if (pOther) {
            eRc = Graph16_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Graph16_Disable (
        GRAPH16_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                           E d g e
    //---------------------------------------------------------------

    ERESULT         Graph16_EdgeExist (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        ERESULT         eRc = ERESULT_DATA_MISSING;
        int16_t         from;
        int16_t         to;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!((index > 0) && (index <= this->edgesMax))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        from = EdgeGet(-index);
        to = EdgeGet(index);
        if (from && to) {
            eRc = ERESULT_SUCCESS;
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         Graph16_EdgeExistVertices (
        GRAPH16_DATA    *this,
        int16_t         vFrom,
        int16_t         vTo
    )
    {
        ERESULT         eRc = ERESULT_DATA_MISSING;
        int16_t         e;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!((vFrom > 0) && (vFrom <= this->verticesMax))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (!((vTo > 0) && (vTo <= this->verticesMax))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        for (e=Graph16_VertexFromFirst(this, vFrom); e;
                                e=Graph16_VertexFromNext(this, e)) {
            if (vTo == EdgeGet(e)) {
                eRc = ERESULT_SUCCESS;
                break;
            }
        }

        // Return to caller.
        return eRc;
    }


    int16_t         Graph16_EdgeFirst (
        GRAPH16_DATA    *this
    )
    {
        //ERESULT         eRc;
        int16_t         index = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (this->edgesMax) {
            index = 1;
        }

        // Return to caller.
        return index;
    }


    int16_t         Graph16_EdgeFrom (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        //ERESULT         eRc;
        int16_t         value = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
        if (!((index > 0) && (index <= this->edgesMax))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif

        value = EdgeGet(-index);

        // Return to caller.
        return value;
    }


    int16_t         Graph16_EdgeNext (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (index < this->edgesMax) {
            index++;
        } else {
            index = 0;
        }

        // Return to caller.
        return index;
    }



    ERESULT         Graph16_EdgeRemove (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!((index > 0) && (index <= this->edgesMax))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        EdgeSet(-index, 0);
        EdgeSet(index, 0);

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         Graph16_EdgeSet (
        GRAPH16_DATA    *this,
        int16_t         index,
        int16_t         vFrom,
        int16_t         vTo
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!(index <= this->edgesMax)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (!((vFrom > 0) && (vFrom <= this->verticesMax))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (!((vTo > 0) && (vTo <= this->verticesMax))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (0 == index)
            index = ++this->edgesUsed;
        if (index > this->edgesUsed)
            this->edgesUsed = index;

        EdgeSet(-index, vFrom);
        if (vFrom > this->verticesUsed)
            this->verticesUsed = vFrom;
        EdgeSet(index, vTo);
        if (vTo > this->verticesUsed)
            this->verticesUsed = vTo;
        // Graph16_UpdateIndex(this, index); <== May not be executed
        //                                       in the proper order.

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    int16_t         Graph16_EdgeTo (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        //ERESULT         eRc;
        int16_t         value = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
        if (!((index > 0) && (index <= this->edgesMax))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif

        value = EdgeGet(index);

        // Return to caller.
        return value;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Graph16_Enable (
        GRAPH16_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                   E x p a n d  E d g e s
    //---------------------------------------------------------------

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
    )
    {
        //ERESULT         eRc;
        uint16_t        oldMax = this->edgesMax;
        int16_t         *pArray = NULL;
        uint32_t        diff;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((max > this->edgesMax) && (max <= 32767))
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Create a new array.
        pArray = mem_Calloc(Graph16_MaxToActual(max), sizeof(int16_t));
        if (NULL == pArray) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // copy in old data if present.
        if (oldMax) {
            diff = (Graph16_MaxToActual(max) - Graph16_MaxToActual(oldMax)) >> 1;
            //diff *= sizeof(int16_t);
            memcpy(
                   (pArray + diff),
                   this->pEdges,
                   (Graph16_MaxToActual(oldMax) * sizeof(int16_t))
            );
        }

        // Replace array with new one.
        if (this->pEdges) {
            mem_Free(this->pEdges);
            //this->pEdges = NULL;
        }
        this->pEdges = pArray;
        this->edgesMax = max;

        pArray = mem_Calloc(Graph16_MaxToActual(max), sizeof(int16_t));
        if (NULL == pArray) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // copy in old data if present.
        if (oldMax) {
            diff = (Graph16_MaxToActual(max) - Graph16_MaxToActual(oldMax)) >> 1;
            //diff *= sizeof(int16_t);
            memcpy(
                   (pArray + diff),
                   this->pNext,
                   (Graph16_MaxToActual(oldMax) * sizeof(int16_t))
            );
        }

        // Replace array with new one.
        if (this->pNext) {
            mem_Free(this->pNext);
            //this->pNext = NULL;
        }
        this->pNext = pArray;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                   E x p a n d  V e r t i c e s
    //---------------------------------------------------------------

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
    )
    {
        //ERESULT         eRc;
        uint16_t        oldMax = this->verticesMax;
        int16_t         *pArray = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((max > this->verticesMax) && (max < 32760))
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Create a new array.
        pArray = mem_Calloc((max + 1), sizeof(int16_t));
        if (NULL == pArray) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // copy in old data if present.
        if (oldMax) {
            memcpy(
                   pArray,
                   this->pFirst,
                   ((oldMax +1) * sizeof(int16_t))
            );
        }

        // Replace array with new one.
        if (this->pFirst) {
            mem_Free(this->pFirst);
            //this->pNext = NULL;
        }
        this->pFirst = pArray;
        this->verticesMax = max;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GRAPH16_DATA *   Graph16_Init (
        GRAPH16_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GRAPH16_DATA);
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_GRAPH16);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Graph16_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Graph16::sizeof(GRAPH16_DATA) = %lu\n", 
                sizeof(GRAPH16_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(GRAPH16_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Graph16_IsEnabled (
        GRAPH16_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    


    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Graph16_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Graph16", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Graph16_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GRAPH16_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(GRAPH16_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Graph16_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Graph16_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Graph16_Enable;
                        }
                        break;

                    case 'P':
#ifdef  GRAPH16_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Graph16_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Graph16_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Graph16_ToDebugString;
                        }
#ifdef  GRAPH16_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Graph16_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Graph16_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Graph16_ToDebugString)
                    return "ToDebugString";
#ifdef  GRAPH16_JSON_SUPPORT
                if (pData == Graph16_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Graph16_ToDebugString (
        GRAPH16_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        int             j;
        int             jMax;
        int16_t         *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Graph16_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "    edgesMax=%u edgesUsed=%u verticesMax=%u verticesUsed=%u\n",
                    this->edgesMax,
                    this->edgesUsed,
                    this->verticesMax,
                    this->verticesUsed
            );

        if (this->pEdges) {
            pData = this->pEdges;
            jMax = this->edgesMax;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            AStr_AppendA(pStr, "Edge Array:\n");
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            AStr_AppendA(pStr, "\t[");
            for (j=0; j<(jMax-1); ++j) {
                if ((j % 8) == 0) {
                    if (j != 0) {
                        AStr_AppendA(pStr, "\n");
                    }
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent, ' ');
                    }
                    AStr_AppendA(pStr, "\t");
                }
                AStr_AppendPrint(pStr, "%d,", *pData++);
            }
            if ((j % 8) == 0) {
                if (j != 0) {
                    AStr_AppendA(pStr, "\n");
                }
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "\t");
            }
            AStr_AppendPrint(pStr, "%d]\n", *pData);
        }

        if (this->pNext) {
            pData = this->pNext;
            jMax = this->edgesMax;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            AStr_AppendA(pStr, "Next Array:\n");
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            AStr_AppendA(pStr, "\t[");
            for (j=0; j<(jMax-1); ++j) {
                if ((j % 8) == 0) {
                    if (j != 0) {
                        AStr_AppendA(pStr, "\n");
                    }
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent, ' ');
                    }
                    AStr_AppendA(pStr, "\t");
                }
                AStr_AppendPrint(pStr, "%d,", *pData++);
            }
            if ((j % 8) == 0) {
                if (j != 0) {
                    AStr_AppendA(pStr, "\n");
                }
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "\t");
            }
            AStr_AppendPrint(pStr, "%d]\n", *pData);
        }

        if (this->pFirst) {
            pData = this->pFirst;
            jMax = this->verticesMax;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            AStr_AppendA(pStr, "First Array:\n");
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent, ' ');
            }
            AStr_AppendA(pStr, "\t[");
            for (j=0; j<(jMax-1); ++j) {
                if ((j % 8) == 0) {
                    if (j != 0) {
                        AStr_AppendA(pStr, "\n");
                    }
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent, ' ');
                    }
                    AStr_AppendA(pStr, "\t");
                }
                AStr_AppendPrint(pStr, "%d,", *pData++);
            }
            if ((j % 8) == 0) {
                if (j != 0) {
                    AStr_AppendA(pStr, "\n");
                }
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent, ' ');
                }
                AStr_AppendA(pStr, "\t");
            }
            AStr_AppendPrint(pStr, "%d]\n", *pData);
        }

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            Graph16_Validate (
        GRAPH16_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_GRAPH16))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(GRAPH16_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                           V e r t e x
    //---------------------------------------------------------------

    /*!
     Add the given element to the end of the array.
     @param     this    object pointer
     @param     pObject Node Object Pointer
     @param     pIndex  Index for Node
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_*
                error.
     */
#ifdef XYZZY
    ERESULT         Graph16_VertexAdd (
        GRAPH16_DATA    *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        uint32_t        index = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = ObjArray_AppendObj(this->pVertices, pObject, &index);

        // Return to caller.
        return eRc;
    }
#endif


    int16_t         Graph16_VertexFirst (
        GRAPH16_DATA    *this
    )
    {
        //ERESULT         eRc;
        int16_t         index = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (this->verticesMax) {
            index = 1;
        }

        // Return to caller.
        return index;
    }


    int16_t         Graph16_VertexNext (
        GRAPH16_DATA    *this,
        int16_t         index
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (index < this->verticesMax) {
            index++;
        } else {
            index = 0;
        }

        // Return to caller.
        return index;
    }



    int16_t         Graph16_VertexFromFirst (
        GRAPH16_DATA    *this,
        int16_t         vertex
    )
    {
        //ERESULT         eRc;
        int16_t         e = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
        if ((vertex > 0) &&(vertex <= this->verticesMax))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        e = FirstGet(vertex);
        while (e < 0) {
            e = NextGet(e);
        }

        // Return to caller.
        return e;
    }


    int16_t         Graph16_VertexFromNext (
        GRAPH16_DATA    *this,
        int16_t         edge                // Previous Edge from Graph16_VertexFromFirst
        //                                  // or this method
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
        if ((edge > 0) &&(edge <= this->edgesMax))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (edge < 0)
            edge = -edge;
        edge = NextGet(edge);
        while (edge < 0) {
            edge = NextGet(edge);
        }

        // Return to caller.
        return edge;
    }



    int16_t         Graph16_VertexToFirst (
        GRAPH16_DATA    *this,
        int16_t         vertex
    )
    {
        //ERESULT         eRc;
        int16_t         e = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
        if ((vertex > 0) &&(vertex <= this->verticesMax))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        e = FirstGet(vertex);
        while (e > 0) {
            e = NextGet(e);
        }

        // Return to caller.
        return (e < 0) ? -e : e;
    }


    int16_t         Graph16_VertexToNext (
        GRAPH16_DATA    *this,
        int16_t         edge                // Previous Edge from Graph16_VertexFromFirst
        //                                  // or this method
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Graph16_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
        if ((edge > 0) &&(edge <= this->edgesMax))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (edge > 0)
            edge = -edge;
        edge = NextGet(edge);
        while (edge > 0) {
            edge = NextGet(edge);
        }

        // Return to caller.
        return (edge < 0) ? -edge : edge;
    }





#ifdef	__cplusplus
}
#endif


