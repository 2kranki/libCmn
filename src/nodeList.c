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
#include "blocks_internal.h"
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
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
        if (0 == this->blockSize) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if ( 0 == listdl_Count(&this->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        pBlock = (NODELIST_BLOCK *)mem_Malloc( this->blockSize );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&this->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<this->cRecordsPerBlock; ++i) {
            listdl_Add2Tail(&this->freeList, &pBlock->node[i]);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    static
    NODELIST_NODE * nodeList_FindNode(
        NODELIST_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        NODELIST_NODE   *pNodeInt;
        ERESULT         eRc;
        
        pNodeInt = listdl_Head(&this->list);
        while ( pNodeInt ) {
            eRc = node_Compare(pNode, pNodeInt->pNode);
            if (ERESULT_SUCCESS_GREATER_THAN == eRc)
                ;
            else {
                return pNodeInt;
            }
            pNodeInt = listdl_Next(&this->list, pNodeInt);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    static
    NODELIST_NODE * nodeList_FindNodeA(
        NODELIST_DATA   *this,
        int32_t         cls,
        const
        char            *pKeyA
    )
    {
        NODELIST_NODE   *pNodeInt;
        ERESULT         eRc;
        
        pNodeInt = listdl_Head(&this->list);
        while ( pNodeInt ) {
            eRc = node_CompareA(pNodeInt->pNode, cls, pKeyA);
            if (eRc == ERESULT_SUCCESS_EQUAL) {
                return pNodeInt;
            }
            if (obj_Flag(this, LIST_FLAG_ORDERED)) {
                if (eRc == ERESULT_SUCCESS_LESS_THAN)
                    return pNodeInt;
            }
            pNodeInt = listdl_Next(&this->list, pNodeInt);
        }
                
        // Return to caller.
        return NULL;
    }
                    
                    
                    
    static
    int             nodeList_SortCompare(
        NODE_DATA       *pNode1,
        NODE_DATA       *pNode2
    )
    {
        int             iRc;
        ERESULT         eRc;
        
        iRc = node_getType(pNode1) - node_getType(pNode2);
        if (0 == iRc) {
            eRc =   name_Compare(
                                 node_getName(pNode1),
                                 node_getName(pNode2)
                    );
            if (ERESULT_SUCCESS_EQUAL == eRc)
                iRc = 0;
            else if (ERESULT_SUCCESS_LESS_THAN == eRc)
                iRc = -1;
            else
                iRc = 1;
        }

        // Return to caller.
        return iRc;
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

    //---------------------------------------------------------------
    //                       O r d e r e d
    //---------------------------------------------------------------
    
    bool            nodeList_getOrdered(
        NODELIST_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (obj_Flag(this, LIST_FLAG_ORDERED))
            return true;
        else
            return false;
    }
    
    bool            nodeList_setOrdered(
        NODELIST_DATA   *this,
        bool            fValue
    )
    {
        bool            fOrdered = false;
        ERESULT         eRc;
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (obj_Flag(this, LIST_FLAG_ORDERED))
            fOrdered = true;
        obj_FlagSet(this, LIST_FLAG_ORDERED, fValue);
        if (!fOrdered && fValue) {
            eRc = nodeList_SortAscending(this);
            if (ERESULT_FAILED(eRc))
                return false;
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P r i o r i t y
    //---------------------------------------------------------------
    
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



    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------
    
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
        if (obj_Flag(this, LIST_FLAG_ORDERED)) {
            NODELIST_NODE   *pNodeInt;
            // Find insertion point.
            pNodeInt = nodeList_FindNode(this, pNode);
            // Do the insertion.
            if (pNodeInt) {
                listdl_AddBefore(&this->list, pNodeInt, pEntry);
            }
            else
                listdl_Add2Tail(&this->list, pEntry);
        }
        else
            listdl_Add2Head(&this->list, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
        if (obj_Flag(this, LIST_FLAG_ORDERED)) {
            NODELIST_NODE   *pNodeInt;
            // Find insertion point.
            pNodeInt = nodeList_FindNode(this, pNode);
            // Do the insertion.
            if (pNodeInt) {
                listdl_AddBefore(&this->list, pNodeInt, pEntry);
            }
            else
                listdl_Add2Tail(&this->list, pEntry);
        }
        else
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
        NODELIST_DATA   *this = objId;
        NODELIST_BLOCK  *pBlock;
        NODELIST_NODE   *pEntry;
        
        // Do initialization.
        if (NULL == this) {
            return;
        }
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        // Release all the nodes.
        while ( (pEntry = listdl_Head(&this->list)) ) {
            if (pEntry->pNode) {
                obj_Release(pEntry->pNode);
                pEntry->pNode = OBJ_NIL;
            }
            listdl_DeleteHead(&this->list);
        }
        
        while ( listdl_Count(&this->blocks) ) {
            pBlock = listdl_DeleteHead(&this->blocks);
            mem_Free( pBlock );
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         nodeList_Delete(
        NODELIST_DATA	*this,
        int32_t         cls,
        const
        char            *pName
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = nodeList_FindNodeA(this, cls, pName);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    ERESULT         nodeList_DeleteHead(
        NODELIST_DATA	*this
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeList_DeleteTail(
        NODELIST_DATA	*this
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Tail(&this->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
        if (pEnum) {
            pEntry = listdl_Head(&this->list);
            while ( pEntry ) {
                eRc = enum_Append(pEnum, pEntry->pNode, NULL);
                pEntry = listdl_Next(&this->list, pEntry);
            }
        }
        
        // Return to caller.
        return pEnum;
    }
    
    

    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    NODE_DATA *     nodeList_FindA(
        NODELIST_DATA	*this,
        int32_t         cls,
        const
        char            *pName
    )
    {
        NODELIST_NODE   *pEntry = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
    #endif
        
        pEntry = nodeList_FindNodeA(this, cls, pName);
        if (pEntry) {
            return pEntry->pNode;
        }
        
        // Return to caller.
        //return ERESULT_DATA_NOT_FOUND;
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         nodeList_ForEach(
        NODELIST_DATA	*this,
        P_VOIDEXIT3_BE  pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
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
            eRc = pScan(pObj, pEntry->pNode, pArg3);
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeList_Get(
        NODELIST_DATA   *this,
        uint32_t        index
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        NODELIST_NODE   *pEntry = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((index >= 1) && (index <= listdl_Count(&this->list)) )
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEntry = listdl_Index(&this->list, index);
        if (pEntry)
            pNode = pEntry->pNode;
        
        // Return to caller.
        return pNode;
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
        
        this->blockSize = LIST_BLOCK_SIZE;
        cbSize = this->blockSize - sizeof(NODELIST_BLOCK);
        cbSize /= sizeof(NODELIST_NODE);
        this->cRecordsPerBlock = cbSize;
        
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
    
    NODEARRAY_DATA * nodeList_Nodes(
        NODELIST_DATA	*this
    )
    {
        NODEARRAY_DATA  *pKeys;
        NODELIST_NODE   *pEntry = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        
        pKeys = nodeArray_New();
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            eRc = nodeArray_AppendNode(pKeys, pEntry->pNode, NULL);
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }
        nodeArray_SortAscending(pKeys);
        
        // Return to caller.
        return pKeys;
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         nodeList_SortAscending(
        NODELIST_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        bool            fRc;
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !nodeList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (listdl_Count(&this->list) < 2) {
            return ERESULT_SUCCESS;
        }
        
        fRc = listdl_Sort(&this->list, (void *)nodeList_SortCompare);
        if (fRc)
            eRc = ERESULT_SUCCESS;
        
        // Return to caller.
        return eRc;
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
        NODELIST_DATA   *this
    )
    {
        uint32_t        i;
        
        if (this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODELIST) )
                ;
            else
                return false;
        }
        else
            return false;
        if (!(obj_getSize(this) >= sizeof(NODELIST_DATA)))
            return false;

        if (this->blockSize) {
            i = this->blockSize - sizeof(NODELIST_BLOCK);
            i /= sizeof(NODELIST_NODE);
            if (i == this->cRecordsPerBlock)
                ;
            else
                return false;
        }
        else {
            if (this->cRecordsPerBlock)
                return false;
        }
        
        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


