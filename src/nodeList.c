// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeList.c
 *	Generated 07/22/2015 10:03:31
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
#include "nodeList_internal.h"
#include "nodeArray.h"
#include "enum_internal.h"
#include "utf8.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            nodeList_AddBlock(
        NODELIST_DATA   *this
    )
    {
        NODELIST_BLOCK  *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&this->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(NODELIST_BLOCK) + (this->cBlock * sizeof(NODELIST_NODE));
        pBlock = (NODELIST_BLOCK *)mem_Malloc( i );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&this->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<this->cBlock; ++i) {
            listdl_Add2Tail(&this->freeList, &pBlock->node[i]);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    static
    NODELIST_NODE * nodeList_FindNode(
        NODELIST_DATA   *this,
        const
        char            *pKey
    )
    {
        NODELIST_NODE   *pNode;
        int             iRc;
        const
        char            *pName;
        
        pNode = listdl_Head(&this->list);
        while ( pNode ) {
            pName = node_getNameUTF8(pNode->pNode);
            iRc = utf8_StrCmp(pKey,pName);
            mem_Free((void *)pName);
            if (0 == iRc) {
                return pNode;
            }
            pNode = listdl_Next(&this->list, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODELIST_DATA * nodeList_Alloc(
    )
    {
        NODELIST_DATA   *this;
        uint32_t        cbSize = sizeof(NODELIST_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODELIST_DATA * nodeList_New(
    )
    {
        NODELIST_DATA   *this;
        
        this = nodeList_Alloc( );
        if (this) {
            this = nodeList_Init(this);
        }
        
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        nodeList_getPriority(
        NODELIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            nodeList_setPriority(
        NODELIST_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        //this->priority = value;
        
        return true;
    }



    uint32_t        nodeList_getSize(
        NODELIST_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return listdl_Count(&this->list);
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         nodeList_Add2Head(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        NODELIST_NODE   *pEntry;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif

        if (0 == listdl_Count(&this->freeList)) {
            if ( nodeList_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        obj_Retain(pNode);
        pEntry->pNode = pNode;
        listdl_Add2Head(&this->list, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }


    ERESULT         nodeList_Add2Tail(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        NODELIST_NODE   *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (0 == listdl_Count(&this->freeList)) {
            if ( nodeList_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        obj_Retain(pNode);
        pEntry->pNode = pNode;
        listdl_Add2Tail(&this->list, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    

    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODELIST_DATA * nodeList_Copy(
        NODELIST_DATA	*this
    )
    {
        NODELIST_DATA   *pOther;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeList_Alloc();
        pOther = nodeList_Init(pOther);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        //FIXME: pOther->pArray = objArray_Copy(this->pArray);
        //FIXME: if (pOther->pArray) {
            //FIXME: pOther->pCompare = this->pCompare;
            //FIXME: return pOther;
        //FIXME: }
        
        // Return to caller.
        obj_Release(pOther);
        //pOther = OBJ_NIL;
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void            nodeList_Dealloc(
        OBJ_ID          objId
    )
    {
        NODELIST_DATA   *cbp = objId;
        NODELIST_BLOCK  *pBlock;
        NODELIST_NODE   *pEntry;
        
        // Do initialization.
        if (NULL == cbp) {
            return;
        }
#ifdef NDEBUG
#else
        if( !nodeList_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        // Release all the nodes.
        while ( (pEntry = listdl_Head(&cbp->list)) ) {
            if (pEntry->pNode) {
                obj_Release(pEntry->pNode);
                pEntry->pNode = OBJ_NIL;
            }
            listdl_DeleteHead(&cbp->list);
        }
        
        while ( listdl_Count(&cbp->blocks) ) {
            pBlock = listdl_DeleteHead(&cbp->blocks);
            mem_Free( pBlock );
        }
        
        obj_Dealloc( cbp );
        cbp = NULL;
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         nodeList_Delete(
        NODELIST_DATA	*cbp,
        const
        char            *pName
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = nodeList_FindNode(cbp, pName);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(&cbp->list, pEntry);
        listdl_Add2Tail(&cbp->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    ERESULT         nodeList_DeleteHead(
        NODELIST_DATA	*cbp
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Head(&cbp->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(&cbp->list, pEntry);
        listdl_Add2Tail(&cbp->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    ERESULT         nodeList_DeleteTail(
        NODELIST_DATA	*cbp
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Tail(&cbp->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(&cbp->list, pEntry);
        listdl_Add2Tail(&cbp->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                        E n u m
    //---------------------------------------------------------------
    
    ENUM_DATA *     nodeList_Enum(
        NODELIST_DATA   *this
    )
    {
        ERESULT         eRc;
        ENUM_DATA       *pEnum = OBJ_NIL;
        //uint32_t        size;
        //uint32_t        index;
        //NODE_DATA       *pNode;
        NODELIST_NODE   *pEntry = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEnum = enum_New();
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            eRc = enum_Append(pEnum, pEntry->pNode, NULL);
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        // Return to caller.
        return pEnum;
    }
    
    
    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    ERESULT         nodeList_Find(
        NODELIST_DATA	*cbp,
        const
        char            *pName,
        NODE_DATA       **ppNode
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeList_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif
        
        pEntry = nodeList_FindNode( cbp, pName );
        if (pEntry) {
            if (ppNode) {
                *ppNode = pEntry->pNode;
            }
            return ERESULT_SUCCESSFUL_COMPLETION;
        }
        
        // Return to caller.
        if (ppNode) {
            *ppNode = OBJ_NIL;
        }
        return ERESULT_DATA_NOT_FOUND;
    }



    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         nodeList_ForEach(
        NODELIST_DATA	*this,
        P_VOIDEXIT2_BE  pScan,
        OBJ_ID          pObj            // Used as first parameter of scan method
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
       
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            eRc = pScan(pObj,pEntry->pNode);
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODELIST_DATA * nodeList_Init(
        NODELIST_DATA   *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_NODELIST );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeList_Vtbl);
        
        cbSize = HASH_BLOCK_SIZE - sizeof(NODELIST_BLOCK);
        cbSize /= sizeof(NODELIST_NODE);
        this->cBlock = cbSize;
        
        // Initialize the lists.
        listdl_Init(&this->freeList, offsetof(NODELIST_NODE, list));
        listdl_Init(&this->blocks, offsetof(NODELIST_NODE, list));
        listdl_Init(&this->list, offsetof(NODELIST_NODE, list));
        
    #ifdef NDEBUG
    #else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->list);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                         N o d e s
    //---------------------------------------------------------------
    
    ERESULT         nodeList_Nodes(
        NODELIST_DATA	*cbp,
        NODEARRAY_DATA  **ppKeys
    )
    {
        NODEARRAY_DATA  *pKeys;
        NODELIST_NODE   *pEntry = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == ppKeys ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pKeys = nodeArray_New();
        pEntry = listdl_Head(&cbp->list);
        while ( pEntry ) {
            eRc = nodeArray_AppendNode(pKeys, pEntry->pNode, NULL);
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&cbp->list, pEntry);
        }
        nodeArray_SortAscending(pKeys);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeList_ToDebugString(
        NODELIST_DATA   *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        NODE_DATA       *pNode;
        NODELIST_NODE   *pEntry = OBJ_NIL;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(nodeList) Size=%d\n",
                     cbp,
                     cbp->size
                     );
        AStr_AppendA(pStr, str);
        
        pEntry = listdl_Head(&cbp->list);
        while ( pEntry ) {
            pNode = pEntry->pNode;
            if (((OBJ_DATA *)(pNode))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(pNode))->pVtbl->pToDebugString(
                                    pNode,
                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
            pEntry = listdl_Next(&cbp->list, pEntry);
        }
        
        AStr_AppendCharRepeatA(pStr, 1, '\n');
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), "%p(nodeList)}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeList_Validate(
        NODELIST_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_NODELIST) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(NODELIST_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


