// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeArray.c
 *	Generated  08/08/2015 09:07:21
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
#include    <nodeArray_internal.h>
#include    <NodeEnum_internal.h>
#include    <i32Array.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    


    
    
    
 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/


    
    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEARRAY_DATA *     nodeArray_Alloc(
    )
    {
        NODEARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(NODEARRAY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEARRAY_DATA *     nodeArray_New(
    )
    {
        NODEARRAY_DATA       *this;
        
        // Do initialization.
        
        this = nodeArray_Alloc( );
        if (this) {
            this = nodeArray_Init(this);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                        M a t c h  S e t
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeArray_MatchSet(
        int             (*pCompare)(NODE_DATA *,NODE_DATA *),
        NODE_DATA       *pNode,
        NODE_DATA       **ppNodeSet     // NULL-terminated Set of Nodes
    )
    {
        int             cmp;
        NODE_DATA       *pFound = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (NULL == ppNodeSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        while (*ppNodeSet) {
            cmp = pCompare(pNode, *ppNodeSet);
            if(0 == cmp) {
                pFound = *ppNodeSet;
                break;
            }
            ++ppNodeSet;
        }
        
        // Return to caller.
        return pFound;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA *  nodeArray_getArray(
        NODEARRAY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            nodeArray_setArray(
        NODEARRAY_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
    
    
    
    bool            nodeArray_setCompare(
        NODEARRAY_DATA  *this,
        int             (*pCompare)(NODE_DATA *,NODE_DATA *)
    )
    {
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pCompare = pCompare;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                     o b j A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA *  nodeArray_getObjArray(
        NODEARRAY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
        
        
    //---------------------------------------------------------------
    //                        O t h e r
    //---------------------------------------------------------------
    
    OBJ_ID          nodeArray_getOther(
        NODEARRAY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOther;
    }
    
    
    bool            nodeArray_setOther(
        NODEARRAY_DATA  *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pOther) {
            obj_Release(this->pOther);
        }
        this->pOther = pValue;
        
        return true;
    }
    
    
    
    uint32_t        nodeArray_getSize(
        NODEARRAY_DATA  *this
    )
    {
        uint32_t        i = 0;
        
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->pArray) {
            i = objArray_getSize(this->pArray);
        }
        return i;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_Append(
        NODEARRAY_DATA	*this,
        NODEARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        max;
        NODE_DATA       *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        max = nodeArray_getSize(pOther);
        
        for (i=0; i<max; ++i) {
            pNode = nodeArray_Get(pOther, i+1);
            if (pNode) {
                eRc = nodeArray_AppendNode(this, pNode, NULL);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeArray_AppendNode(
        NODEARRAY_DATA	*this,
        NODE_DATA       *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((pObject == OBJ_NIL) || (!obj_IsKindOf(pObject, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }
        
        eRc = objArray_AppendObj(this->pArray, pObject, pIndex);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_Assign(
        NODEARRAY_DATA	*this,
        NODEARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = objArray_Assign(this->pArray, pOther->pArray);
        pOther->pCompare = this->pCompare;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeArray_Copy(
        NODEARRAY_DATA	*this
    )
    {
        NODEARRAY_DATA  *pOther;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeArray_New();
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        pOther->pArray = objArray_Copy(this->pArray);
        if (pOther->pArray) {
            pOther->pCompare = this->pCompare;
            return pOther;
        }
        
        // Return to caller.
        obj_Release(pOther);
        return( OBJ_NIL );
    }
    
    
    
    uint32_t        nodeArray_Count(
        NODEARRAY_DATA  *this
    )
    {
        uint32_t        i = 0;
        
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (this->pArray) {
            i = objArray_getSize(this->pArray);
        }
        return i;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeArray_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pArray) {
#ifdef NDEBUG
#else
            if (obj_getRetainCount(this->pArray) > 1) {
                DEBUG_BREAK();
            }
#endif
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }
        if (this->pOther) {
            obj_Release(this->pOther);
            this->pOther = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeArray_DeepCopy(
        NODEARRAY_DATA    *this
    )
    {
        NODEARRAY_DATA  *pOther;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeArray_New();
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        pOther->pArray = objArray_DeepCopy(this->pArray);
        if (pOther->pArray) {
            pOther->pCompare = this->pCompare;
            return pOther;
        }
        
        // Return to caller.
        obj_Release(pOther);
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeArray_Delete(
        NODEARRAY_DATA	*this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_Delete(this->pArray, index);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     nodeArray_DeleteFirst(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     nodeArray_DeleteLast(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                        E n u m
    //---------------------------------------------------------------
    
    NODEENUM_DATA * nodeArray_Enum(
        NODEARRAY_DATA  *this
    )
    {
        ERESULT         eRc;
        NODEENUM_DATA   *pEnum = OBJ_NIL;
        uint32_t        size;
        uint32_t        index;
        NODE_DATA       *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pEnum = NodeEnum_New();
            size = objArray_getSize(this->pArray);
            for (index = 0; index < size; ++index) {
                pNode = objArray_Get(this->pArray, index+1);
                eRc = NodeEnum_AppendObj(pEnum, pNode);
            }
        }
        
        // Return to caller.
        return pEnum;
    }
    
    

    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeArray_Find (
        NODEARRAY_DATA  *this,
        NODE_DATA       *pNode
    )
    {
        NODE_DATA       *pWork = OBJ_NIL;
        uint32_t        size;
        uint32_t        i;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNode ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        size = nodeArray_getSize(this);
        for (i=0; i<size; ++i) {
            pWork = (NODE_DATA *)objArray_Get(this->pArray, i+1);
            if (pWork) {
                eRc = node_Compare(pNode, pWork);
                if( eRc == ERESULT_SUCCESS_EQUAL ) {
                    return pWork;
                }
            }
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    NODE_DATA *     nodeArray_FindA(
        NODEARRAY_DATA	*this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        NODE_DATA       *pFound = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNameA ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

        pNode = node_NewWithUTF8AndClass(cls, pNameA, OBJ_NIL);
        pFound = nodeArray_Find(this, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return pFound;
    }
    
    
    
    //---------------------------------------------------------------
    //                     F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_ForEach(
        NODEARRAY_DATA  *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        index;
        uint32_t        size;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pArray && pScan) {
            size = objArray_getSize(this->pArray);
            for (index = 0; index < size; ++index) {
                pNode = objArray_Get(this->pArray, (index + 1));
                eRc = pScan(pObj, pNode, pArg3);
                if (ERESULT_FAILED(eRc))
                    break;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeArray_Get(
        NODEARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_Get(this->pArray, index);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     nodeArray_GetFirst(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     nodeArray_GetLast(
        NODEARRAY_DATA	*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEARRAY_DATA *   nodeArray_Init(
        NODEARRAY_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_NODEARRAY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeArray_Vtbl);
        
        this->pCompare = &node_Compare;
        
    #ifdef NDEBUG
    #else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_InsertAfter(
        NODEARRAY_DATA	*this,
        uint32_t        index,
        NODE_DATA       *pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((pObject == OBJ_NIL) || (!obj_IsKindOf(pObject, OBJ_IDENT_NODE))) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }
        
        eRc = objArray_InsertObj(this->pArray, index, pObject);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    ERESULT         nodeArray_Put(
        NODEARRAY_DATA  *this,
        uint32_t        index,
        NODE_DATA       *pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pObject == OBJ_NIL)
            ;
        else if (!obj_IsKindOf(pObject, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_MEMORY_EXCEEDED;
            }
        }
        
        eRc = objArray_Put(this->pArray, index, pObject);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          nodeArray_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEARRAY_DATA  *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeArray_ToDebugString;
                        }
                        if (str_Compare("ToString", (char *)pStr) == 0) {
                            return nodeArray_ToString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_SortAscending(
        NODEARRAY_DATA	*this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pArray) {
            eRc = objArray_SortAscending(this->pArray, (OBJ_COMPARE)this->pCompare);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    T o  C l a s s  A r r a y
    //---------------------------------------------------------------
    
    I32ARRAY_DATA * nodeArray_ToClassArray(
        NODEARRAY_DATA  *this
    )
    {
        int             j;
        I32ARRAY_DATA   *pArray = OBJ_NIL;
        NODE_DATA       *pNode;
        int32_t         chr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pArray = i32Array_New( );
        
        if (pArray && this->pArray) {
            for (j=0; j<objArray_getSize(this->pArray); ++j) {
                pNode = objArray_Get(this->pArray, j+1);
                if (pNode) {
                    chr = node_getClass(pNode);
                }
                else {
                    chr = 0;
                }
                i32Array_AppendData(pArray, chr);
            }
        }
        
        
        return pArray;
    }
    

    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeArray_ToDebugString(
        NODEARRAY_DATA  *this,
        int             indent
    )
    {
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        NODE_DATA       *pNode;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        AStr_AppendPrint(
                         pStr,
                         "{%p(nodeArray) Size=%d pArray=%p\n\n",
                         this,
                         (this->pArray ? objArray_getSize(this->pArray) : 0),
                         this->pArray
        );
        
        if (this->pArray) {
            for (j=0; j<objArray_getSize(this->pArray); ++j) {
                pNode = objArray_Get(this->pArray, j+1);
                if ( pNode && ((OBJ_DATA *)(pNode))->pVtbl->pToDebugString) {
                    pWrkStr =   ((OBJ_DATA *)(pNode))->pVtbl->pToDebugString(
                                        pNode,
                                        indent+3
                                );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
                AStr_AppendCharA(pStr, '\n');
            }
        }
        
        AStr_AppendCharA(pStr, '\n');
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        AStr_AppendPrint(pStr, "%p(nodeArray)}\n", this);
        
        return pStr;
    }
    
    
    ASTR_DATA *     nodeArray_ToString(
        NODEARRAY_DATA  *this
    )
    {
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk;
        NODE_DATA       *pNode;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendA(pStr, "Array[\n");
        
        if (this->pArray) {
            for (j=0; j<objArray_getSize(this->pArray); ++j) {
                pNode = objArray_Get(this->pArray, j+1);
                pWrk = node_ToString(pNode);
                if (pWrk) {
                    AStr_AppendA(pStr, "  ");
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                }
            }
        }
        
        AStr_AppendA(pStr, "]\n\n");
        
        return pStr;
    }
    
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeArray_Validate(
        NODEARRAY_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODEARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODEARRAY_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                   V i s i t  A s c e n d i n g
    //---------------------------------------------------------------
    
    ERESULT         nodeArray_VisitAscending(
        NODEARRAY_DATA	*this,
        ERESULT         (pVisitor)(
                                   OBJ_ID,             // Object supplied below
                                   NODE_DATA *         // Current Node
                        ),
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
;
        }
        BREAK_NULL(this->pArray);
#endif
        
        iMax = objArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pNode = objArray_Get(this->pArray, (i+1));
            eRc = pVisitor(pObject, pNode);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


