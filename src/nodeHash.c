// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeHash.c
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
#include "nodeHash_internal.h"
#include "nodeArray.h"
#include "utf8.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            nodeHash_AddBlock(
        NODEHASH_DATA   *cbp
    );
    
    static
    uint16_t        nodeHash_IndexFromHash(
        NODEHASH_DATA   *cbp,
        uint32_t        hash
    );
    
    static
    LISTDL_DATA *   nodeHash_NodeListFromHash(
        NODEHASH_DATA   *cbp,
        uint32_t        hash
    );
    
    
    
    /* Expand the current Pointer Array by Inc entries.
     */
    static
    bool            nodeHash_AddBlock(
        NODEHASH_DATA   *cbp
    )
    {
        NODEHASH_BLOCK  *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&cbp->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(NODEHASH_BLOCK) + (cbp->cBlock * sizeof(NODEHASH_NODE));
        pBlock = (NODEHASH_BLOCK *)mem_Malloc( i );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&cbp->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<cbp->cBlock; ++i) {
            listdl_Add2Tail(&cbp->freeList, &pBlock->node[i]);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    static
    NODEHASH_NODE * nodeHash_FindNodeA(
        NODEHASH_DATA   *cbp,
        uint32_t        hash,
        const
        char            *pKey
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pNode;
        int             iRc;
        const
        char            *pName;
        
        // Do initialization.
        pNodeList = nodeHash_NodeListFromHash( cbp, hash );
        
        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (pNode->hash == hash) {
                pName = node_getNameUTF8(pNode->pNode);
                iRc = utf8_StrCmp(pKey,pName);
                mem_Free((void *)pName);
                pName = NULL;
                if (0 == iRc) {
                    return pNode;
                }
                if (iRc < 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    static
    NODEHASH_NODE * nodeHash_FindNodeW(
        NODEHASH_DATA   *cbp,
        uint32_t        hash,
        const
        int32_t         *pKey
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pNode;
        int             iRc;
        const
        char            *pName;
        
        // Do initialization.
        pNodeList = nodeHash_NodeListFromHash( cbp, hash );
        
        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (pNode->hash == hash) {
                pName = node_getNameUTF8(pNode->pNode);
                iRc = utf8_StrCmpAW(pName,pKey);
                mem_Free((void *)pName);
                pName = NULL;
                if (0 == iRc) {
                    return pNode;
                }
                if (iRc > 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    static
    uint16_t        nodeHash_IndexFromHash(
        NODEHASH_DATA   *cbp,
        uint32_t        hash
    )
    {
        uint16_t        index;
        
        index = hash % cbp->cHash;
        return index;
    }
    
    
    
    static
    LISTDL_DATA *   nodeHash_NodeListFromHash(
        NODEHASH_DATA   *cbp,
        uint32_t        hash
    )
    {
        LISTDL_DATA     *pNodeList;
        
        pNodeList = &cbp->pHash[nodeHash_IndexFromHash(cbp,hash)];
        return( pNodeList );
    }
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEHASH_DATA * nodeHash_Alloc(
    )
    {
        NODEHASH_DATA   *cbp;
        uint32_t        cbSize = sizeof(NODEHASH_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    NODEHASH_DATA * nodeHash_New(
        uint16_t        cHash           // [in] Hash Table Size
    )
    {
        NODEHASH_DATA   *cbp;
        
        cbp = nodeHash_Alloc( );
        if (cbp) {
            cbp = nodeHash_Init(cbp, cHash);
        }
        
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        nodeHash_getPriority(
        NODEHASH_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            nodeHash_setPriority(
        NODEHASH_DATA   *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        nodeHash_getSize(
        NODEHASH_DATA   *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return cbp->size;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         nodeHash_Add(
        NODEHASH_DATA   *cbp,
        NODE_DATA       *pNode
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry;
        uint32_t        hash;
        const
        char            *pName;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif

        pName = node_getNameUTF8(pNode);
        hash = name_Hash(node_getName(pNode));
        pEntry = nodeHash_FindNodeA(cbp, hash, pName);
        mem_Free((void *)pName);
        pName = NULL;
        if (pEntry) {
            DEBUG_BREAK();
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        
        // Determine the entry number.
        if (0 == listdl_Count(&cbp->freeList)) {
            if ( nodeHash_AddBlock(cbp) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        pEntry = listdl_DeleteHead(&cbp->freeList);
        if (NULL == pEntry) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Add it to the table.
        obj_Retain(pNode);
        pEntry->pNode = pNode;
        pEntry->hash = hash;
        
        pNodeList = nodeHash_NodeListFromHash( cbp, hash );
        listdl_Add2Tail(pNodeList, pEntry);
        
        ++cbp->size;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODEHASH_DATA * nodeHash_Copy(
        NODEHASH_DATA	*this
    )
    {
        NODEHASH_DATA   *pOther;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        i;
        NODE_DATA       *pItem;
        OBJ_IUNKNOWN    *pVtbl;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeHash_Alloc();
        pOther = nodeHash_Init(pOther, this->cHash);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }

        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                pItem = pEntry->pNode;
                if (pItem) {
                    pVtbl = obj_getVtbl(pItem);
                    if (pVtbl->pCopy) {
                        pItem = pVtbl->pCopy(pItem);
                    }
                    else {
                        obj_Retain(pEntry);
                    }
                    eRc = nodeHash_Add(pOther, pItem);
                    if (ERESULT_HAS_FAILED(eRc)) {
                        obj_Release(pOther);
                        return OBJ_NIL;
                    }
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void            nodeHash_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEHASH_DATA   *cbp = objId;
        LISTDL_DATA     *pNodeList;
        NODEHASH_BLOCK  *pBlock;
        NODEHASH_NODE   *pEntry;
        uint32_t        i;
        
        // Do initialization.
        if (NULL == cbp) {
            return;
        }
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        // Release all the nodes.
        for (i=0; i<cbp->cHash; ++i) {
            pNodeList = &cbp->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                obj_Release(pEntry->pNode);
                pEntry->pNode = OBJ_NIL;
                pEntry = listdl_Next(pNodeList, pEntry);
            }
        }
        
        while ( listdl_Count(&cbp->blocks) ) {
            pBlock = listdl_DeleteHead(&cbp->blocks);
            mem_Free( pBlock );
        }
        
        if( cbp->pHash ) {
            mem_Free( cbp->pHash );
            cbp->pHash = NULL;
        }
        
        obj_Dealloc( cbp );
        cbp = NULL;
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_Delete(
        NODEHASH_DATA	*cbp,
        const
        char            *pName
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        hash = str_HashAcmA((const char *)pName, NULL);
        pEntry = nodeHash_FindNodeA(cbp, hash, pName);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        pNodeList = nodeHash_NodeListFromHash( cbp, hash );
        obj_Release(pEntry->pNode);
        pEntry->pNode = OBJ_NIL;
        listdl_Delete(pNodeList, pEntry);
        listdl_Add2Tail(&cbp->freeList, pEntry);
        --cbp->size;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    ERESULT         nodeHash_FindA(
        NODEHASH_DATA	*cbp,
        const
        char            *pName,
        NODE_DATA       **ppNode
    )
    {
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        hash;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif
        
        hash = str_HashAcmA((const char *)pName, NULL);
        pEntry = nodeHash_FindNodeA( cbp, hash, pName );
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


    ERESULT         nodeHash_FindW(
        NODEHASH_DATA	*this,
        const
        int32_t         *pName,
        NODE_DATA       **ppNode
    )
    {
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        hash = str_HashAcmW(pName, NULL);
        pEntry = nodeHash_FindNodeW( this, hash, pName );
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
    
    ERESULT         nodeHash_ForEach(
        NODEHASH_DATA	*cbp,
        P_VOIDEXIT2_BE  pScan,
        OBJ_ID          pObj            // Used as first parameter of scan method
    )
    {
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        i;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
       
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        for (i=0; i<cbp->cHash; ++i) {
            pNodeList = &cbp->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                eRc = pScan(pObj,pEntry->pNode);
                if (ERESULT_HAS_FAILED(eRc)) {
                    break;
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEHASH_DATA * nodeHash_Init(
        NODEHASH_DATA   *this,
        uint16_t        cHash           // [in] Hash Table Size
    )
    {
        uint32_t        cbSize;
        uint32_t        i;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_NODEHASH );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeHash_Vtbl);
        
        this->cHash = cHash;
        cbSize = HASH_BLOCK_SIZE - sizeof(NODEHASH_BLOCK);
        cbSize /= sizeof(NODEHASH_NODE);
        this->cBlock = cbSize;
        
        // Allocate the Hash Table.
        cbSize = cHash * sizeof(LISTDL_DATA);
        this->pHash = (LISTDL_DATA *)mem_Malloc( cbSize );
        if (NULL == this->pHash) {
            DEBUG_BREAK();
            mem_Free(this);
            this = NULL;
            return this;
        }
        for (i=0; i<cHash; ++i) {
            listdl_Init(&this->pHash[i], offsetof(NODEHASH_NODE, list));
        }
        listdl_Init(&this->freeList, offsetof(NODEHASH_NODE, list));
        
    #ifdef NDEBUG
    #else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pHash);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                         N o d e s
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_Nodes(
        NODEHASH_DATA	*cbp,
        NODEARRAY_DATA  **ppKeys
    )
    {
        NODEARRAY_DATA  *pKeys;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        uint32_t        i;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == ppKeys ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pKeys = nodeArray_New();
        for (i=0; i<cbp->cHash; ++i) {
            pNodeList = &cbp->pHash[i];
            pEntry = listdl_Head(pNodeList);
            while ( pEntry ) {
                eRc = nodeArray_AppendNode(pKeys, pEntry->pNode, NULL);
                if (ERESULT_HAS_FAILED(eRc)) {
                    break;
                }
                pEntry = listdl_Next(pNodeList, pEntry);
            }
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
        }
        nodeArray_SortAscending(pKeys);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeHash_ToDebugString(
        NODEHASH_DATA   *cbp,
        int             indent
    )
    {
        char            str[256];
        uint32_t        i;
        uint32_t        j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        NODE_DATA       *pNode;
        LISTDL_DATA     *pNodeList;
        NODEHASH_NODE   *pEntry = OBJ_NIL;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(nodeHash) Size=%d\n",
                     cbp,
                     cbp->size
                     );
        AStr_AppendA(pStr, str);
        
        for (i=0; i<cbp->cHash; ++i) {
            pNodeList = &cbp->pHash[i];
            pEntry = listdl_Head(pNodeList);
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
                pEntry = listdl_Next(pNodeList, pEntry);
            }
        }
        
        AStr_AppendCharRepeatA(pStr, 1, '\n');
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), "%p(nodeHash)}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeHash_Validate(
        NODEHASH_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_NODEHASH) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(NODEHASH_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


