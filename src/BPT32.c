// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BPT32.c
 *	Generated 01/12/2019 14:04:44
 *
 * Todo:
 *  *   Implement deletion using delete block upon empty and put block
 *      on a free list to be re-used.  See the article on header to
 *      understand why not to merge 1/2 full.  Or add the option to do
 *      either.
 *  *   Implement block/file locking.
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
#include        <BPT32_internal.h>
#include        <BPT32_Request.h>
#include        <FileIO.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         BPT32_BlockFindParent(
        BPT32_DATA      *this,
        LBN32_T         lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          *pObj;
        uint32_t        iMax;
        uint32_t        i;
        uint32_t        index;
        BPT32_BLK_VTBL  *pVtbl = NULL;

        TRC_OBJ(this, "BPT32_BlockFindParent lsn=%d\n", lbn);
        
        if (ppObj)
            *ppObj = OBJ_NIL;
        iMax = ObjArray_getSize(this->pSrchStk);
        for (i=iMax; i>0; --i) {
            pObj = ObjArray_Get(this->pSrchStk, i);
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
            index = pVtbl->pGetLBN(pObj);
            if (lbn == index) {
                if (i > 1) {
                    pObj = ObjArray_Get(this->pSrchStk, (i - 1));
                    if (ppObj)
                        *ppObj = pObj;
#ifdef NDEBUG
#else
                    if (obj_Trace(this)) {
                        OBJ_IUNKNOWN    *pVtbl = obj_getVtbl(pObj);
                        ASTR_DATA       *pStr = pVtbl->pToDebugString(pObj, 4);
                        TRC_OBJ(this, "\tFound:\n%s\n", AStr_getData(pStr));
                        obj_Release(pStr);
                    }
#endif
                    eRc = ERESULT_SUCCESS;
                }
                break;
            }
        }
        
        TRC_OBJ(this, "\tNot Found\n");
        return eRc;
    }
    
    
    
    /*!
     @warning   This method must always conform to P_ERESULT_EXIT4.
     */
    ERESULT         BPT32_BlockRequest(
        BPT32_DATA      *this,
        uint32_t        request,
        OBJ_ID          pObj,
        void            *pParm1,
        void            *pParm2,
        void            *pParm3
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPT32INDEX_DATA *pIndex = OBJ_NIL;
        BPT32LEAF_DATA  *pLeaf = OBJ_NIL;
        LBN32_T         lbn = 0;                    // Logical Block Number
        void            *pBlock = NULL;
        BPT32_BLK_VTBL  *pVtbl = NULL;

#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        TRC_OBJ(this, "BPT32_BlockRequest req=%d\n", request);
#endif
        
        switch (request) {
                
            case BPT32_REQUEST_NEW_INDEX:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Index Block  lsn: %d\n", lbn);
                pIndex =    BPT32Index_NewWithSizes(
                                             this->blockSize,
                                             this->dataSize,
                                             lbn,
                                             true,
                                             this
                            );
                if (OBJ_NIL == pIndex) {
                    DEBUG_BREAK();
                    --this->pHdr->cRecords;
                    return ERESULT_OUT_OF_MEMORY;
                }
#ifdef NDEBUG
#else
                if (obj_Trace(this))
                    obj_TraceSet(pIndex, true);
#endif
                eRc =   RRDS_RecordWrite(
                                         this->pIO,
                                         BPT32Index_getLBN(pIndex),
                                         BPT32Index_getBlock(pIndex)
                        );
                if (pParm3)
                    *((void **)pParm3) = pIndex;
                else
                    obj_Release(pIndex);
                pIndex = NULL;
                break;
                
            case BPT32_REQUEST_NEW_LEAF:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Leaf Block  lsn: %d\n", lbn);
                pLeaf = BPT32Leaf_NewWithSizes(
                                             this->blockSize,
                                             this->dataSize,
                                             lbn,
                                             true,
                                             this
                        );
                if (OBJ_NIL == pLeaf) {
                    DEBUG_BREAK();
                    --this->pHdr->cRecords;
                    return ERESULT_OUT_OF_MEMORY;
                }
#ifdef NDEBUG
#else
                if (obj_Trace(this))
                    obj_TraceSet(pLeaf, true);
#endif
                eRc =   RRDS_RecordWrite(
                                         this->pIO,
                                         BPT32Leaf_getLBN(pLeaf),
                                         BPT32Leaf_getBlock(pLeaf)
                        );
                if (pParm3)
                    *((void **)pParm3) = pLeaf;
                else
                    obj_Release(pLeaf);
                pLeaf = NULL;
                break;
                
            case BPT32_REQUEST_PARENT:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
                lbn = pVtbl->pGetLBN(pObj);
                TRC_OBJ(this, "\tFind Parent for %d...\n", lbn);
                eRc = BPT32_BlockFindParent(this, lbn, pParm3);
                break;
                
            case BPT32_REQUEST_READ:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
                lbn = pVtbl->pGetLBN(pObj);
                TRC_OBJ(this, "\tRead data for block %d...\n", lbn);
                pBlock = pVtbl->pGetBlock(pObj);
                if (NULL == pBlock) {
                    eRc = pVtbl->pSetup(
                                        pObj,
                                        this->blockSize,
                                        this->dataSize,
                                        lbn,
                                        true
                            );
                    pVtbl->pSetManager(pObj, this);
                    pBlock = pVtbl->pGetBlock(pObj);
                }
                if (lbn && pBlock) {
                    eRc =   RRDS_RecordRead(
                                            this->pIO,
                                            lbn,
                                            pBlock
                            );
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
#ifdef NDEBUG
#else
                if (obj_Trace(this) && !ERESULT_FAILED(eRc)) {
                    ASTR_DATA       *pStr = OBJ_NIL;
                    if (OBJ_IDENT_BPT32INDEX == obj_getType(pObj)) {
                        eRc = BPT32Index_Verify(pObj);
                        if (ERESULT_FAILED(eRc)) {
                            pStr = BPT32Index_ToDebugString(pObj, 4);
                        }
                    }
                    if (OBJ_IDENT_BPT32LEAF == obj_getType(pObj)) {
                        eRc = BPT32Leaf_Verify(pObj);
                        if (ERESULT_FAILED(eRc)) {
                            pStr = BPT32Leaf_ToDebugString(pObj, 4);
                        }
                    }
                   if (ERESULT_FAILED(eRc)) {
                       TRC_OBJ(this, "\tBlock Verify Error!\n");
                       if (pStr) {
                           fprintf(stderr, "%s\n", AStr_getData(pStr));
                           obj_Release(pStr);
                       }
                        DEBUG_BREAK();
                        obj_Release(pObj);
                        return eRc;
                    }
                }
#endif
                break;
                
            case BPT32_REQUEST_SPLIT:
                TRC_OBJ(this, "\tSplit Block...\n");
                eRc = BPT32_BlockSplit(this, (OBJ_ID)pObj, pParm1);
                break;
                
            case BPT32_REQUEST_SET_TAIL:
                TRC_OBJ(this, "\tSet new data tail...\n");
                if (OBJ_IDENT_BPT32LEAF == obj_getType(pObj)) {
                    this->pHdr->dataTail = BPT32Leaf_getLBN((BPT32LEAF_DATA *)pObj);
                    eRc = ERESULT_SUCCESS;
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
                break;
                
            case BPT32_REQUEST_WRITE:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
                lbn = pVtbl->pGetLBN(pObj);
                TRC_OBJ(this, "\tWrite data for block %d...\n", lbn);
                pBlock = pVtbl->pGetBlock(pObj);
                if (lbn && pBlock) {
                    eRc =   RRDS_RecordWrite(
                                             this->pIO,
                                             lbn,
                                             pBlock
                            );
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_INVALID_REQUEST;
                break;
        }
        
        return eRc;
    }
    
    
    
    ERESULT         BPT32_BlockRead(
        BPT32_DATA      *this,
        LBN32_T         lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        BPT32INDEX_DATA *pIndex = OBJ_NIL;
        BPT32LEAF_DATA  *pLeaf = OBJ_NIL;
        uint8_t         *pData;

        TRC_OBJ(this, "BPT32_BlockRead lsn=%d\n", lbn);
        
        // Load the block into the LRU.
        eRc =   RRDS_RecordRead(
                                    this->pIO,
                                    lbn,
                                    NULL
                );
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            TRC_OBJ(this, "\tRead Error!\n");
            return eRc;
        }
        
        pData = (uint8_t *)lru_FindBuffer(this->pLRU, lbn);
        if (*pData == OBJ_IDENT_BPT32INDEX) {
            pIndex = BPT32Index_New();
            if (OBJ_NIL == pIndex) {
                DEBUG_BREAK();
                TRC_OBJ(this, "\tCould not create Index Block Error!\n");
                return ERESULT_OUT_OF_MEMORY;
            }
#ifdef NDEBUG
#else
            if (obj_Trace(this))
                obj_TraceSet(pIndex, true);
#endif
            eRc = BPT32Index_Setup(pIndex, this->blockSize, lbn, this->dataSize, true);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tIndex Block Setup Error!\n");
                obj_Release(pIndex);
                return eRc;
            }
            BPT32Index_setManager(pIndex, (void *)this);
            BPT32Index_CopyFrom(pIndex, (void *)pData);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = BPT32Index_Verify(pIndex);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tIndex Block Verify Error!\n");
                    ASTR_DATA       *pStr = BPT32Leaf_ToDebugString(pLeaf, 4);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    DEBUG_BREAK();
                    obj_Release(pIndex);
                    return eRc;
                }
            }
#endif
            if (ppObj)
                *ppObj = pIndex;
            else
                obj_Release(pIndex);
            pIndex = OBJ_NIL;
            TRC_OBJ(this, "\tFound index Block\n");
        }
        else if (*pData == 'L') {
            pLeaf = BPT32Leaf_New();
            if (OBJ_NIL == pLeaf) {
                TRC_OBJ(this, "\tCould not create Leaf Block Error!\n");
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
#ifdef NDEBUG
#else
            if (obj_Trace(this))
                obj_TraceSet(pLeaf, true);
#endif
            eRc = BPT32Leaf_Setup(pLeaf, this->blockSize, this->dataSize, lbn, true);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tLeaf Block Setup Error!\n");
                obj_Release(pLeaf);
                return eRc;
            }
            BPT32Leaf_setManager(pLeaf, (void *)this);
            BPT32Leaf_CopyFrom(pLeaf, (void *)pData);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = BPT32Leaf_Verify(pLeaf);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tLeaf Block Verify Error!\n");
                    ASTR_DATA       *pStr = BPT32Leaf_ToDebugString(pLeaf, 4);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    DEBUG_BREAK();
                    obj_Release(pLeaf);
                    return eRc;
                }
            }
#endif
            if (ppObj)
                *ppObj = pLeaf;
            else
                obj_Release(pLeaf);
            pLeaf = OBJ_NIL;
            TRC_OBJ(this, "\tFound Leaf Block\n");
        }
        else {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                 B l o c k  S e a r c h
    //---------------------------------------------------------------
    
    /*!
     Search the blocks down to the leaf blocks for a specific key.  If found,
     set up work block for the found key.  If not found, set up work block for
     insertion point in block.  Also, the srchStk will contain all the blocks
     searched to find the leaf block.  So, it can be used for figuring out
     parent blocks.
     @param     this        Object Pointer
     @param     lbn         Block Number to start with
     @param     key         key to be looked for
     @param     pData       Optional pointer to the returned data for the key
                            if found
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   this->srchCur should be zeroed before a search begins.
     */
    ERESULT         BPT32_BlockSearchKey (
        BPT32_DATA      *this,
        LBN32_T         lbn,                // Logical Block Number
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc;
        uint32_t        nodeIndex = 0;
        OBJ_ID          pObject = OBJ_NIL;
        bool            fMore = true;
        bool            fRead = false;
        BPT32_BLK_VTBL  *pVtbl;
        
        // Do initialization.
        TRC_OBJ(this, "BPT32_BlockSearchKey lsn=%d, key=%d\n", lbn, key);
        
        if (0 == lbn) {         // Use the root.
            pObject = this->pRoot;
            TRC_OBJ(this, "\tUsing Root for first block\n");
        }
        
        while (fMore) {
            fRead = false;
            if (pObject)
                ;
            else {
                // Read the root block into the common buffer.
                TRC_OBJ(this, "\tReading %d\n", lbn);
                eRc = BPT32_BlockRead(this, lbn, &pObject);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    return eRc;
                }
                fRead = true;
            }
            
            if (pObject) {
                ObjArray_Push(this->pSrchStk, pObject);
            }
            else {
                return ERESULT_GENERAL_FAILURE;
            }
            if (fRead)
                obj_Release(pObject);       // objArray has retained it.

            if ( pObject) {
                if (obj_getType(pObject) == OBJ_IDENT_BPT32LEAF) {
                    eRc = BPT32Leaf_FindKey(pObject, key, pData);
                    if (ERESULT_FAILED(eRc)) {
                        TRC_OBJ(this, "\tLeaf block, key %d not found\n", key);
                    }
                    else {
                        pVtbl = (void *)obj_getVtbl((OBJ_ID)pObject);
                        this->lastLSN = pVtbl->pGetLBN(pObject);
                        this->lastKey = key;
                        TRC_OBJ(this, "\tLeaf block, key %d found\n", key);
                    }
                    return eRc;
                }
                else if (obj_getType(pObject) == OBJ_IDENT_BPT32INDEX) {
                    eRc = BPT32Index_FindKey(pObject, key, &nodeIndex);
                    if (ERESULT_FAILED(eRc)) {
                        TRC_OBJ(this, "\tIndex block, key %d not found\n", key);
                       return eRc;
                    }
                    TRC_OBJ(
                            this,
                            "\tIndex block, key %d found, index=%d\n",
                            key,
                            nodeIndex
                    );
                }
                else {
                    DEBUG_BREAK();
                    return ERESULT_GENERAL_FAILURE;
                }
            }
            
            lbn = nodeIndex;
            pObject = OBJ_NIL;
        }

        // Return to caller.
        TRC_OBJ(this, "\tkey %d not found, returning\n", key);
        return ERESULT_DATA_NOT_FOUND;
    }
    
    
    
    /*!
     This method is called after a block split occurs.  It's job is to further
     propogate the split up the Tree as high as it needs to go.  If a new index
     block is needed, that shows a split of the root and this method handles
     that as well.
     
     The first split should always be in a leaf block.  All splits after that will
     be index block(s).  When a split occurs, the index block which is parent will
     only be new if the root needs to be split.  When the root is split whether it
     is a leaf or index block, a new block will be needed.  The new block's p0
     should be set to the index of the left block and the first node entry should
     be to the lowest key of the right block.
     
     @param     this        Object Pointer
     @param     pLeft       Object Pointer for the lefthand block of the split
     @param     pRight      Object Pointer for the righthand block of the split
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32_BlockSplit(
        BPT32_DATA      *this,
        OBJ_ID          *pLeft,
        OBJ_ID          *pRight
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPT32INDEX_DATA *pIndex = OBJ_NIL;
        OBJ_ID          pObj;
        uint32_t        key = 0;
        uint32_t        index = 0;
        LBN32_T         lbn = 0;
        BPT32_BLK_VTBL  *pVtblL = NULL;
        BPT32_BLK_VTBL  *pVtblR = NULL;

#ifdef NDEBUG
#else
        if (OBJ_NIL == pLeft) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == pRight) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pVtblL = (BPT32_BLK_VTBL *)obj_getVtbl(pLeft);
        pVtblR = (BPT32_BLK_VTBL *)obj_getVtbl(pRight);
        TRC_OBJ(
                this,
                "BPT32_BlockSplit Left: type=%d lsn=%d, Right: type=%d lsn=%d\n",
                obj_getType(pLeft),
                pVtblR->pGetLBN(pLeft),
                obj_getType(pRight),
                pVtblR->pGetLBN(pRight)
        );

        // We are splitting the Root!
        if (this->pRoot == pLeft) {
            TRC_OBJ(this, "\tSplitting the root...\n");
            eRc =   BPT32_BlockRequest(
                                     this,
                                     BPT32_REQUEST_NEW_INDEX,
                                     OBJ_NIL,
                                     NULL,
                                     NULL,
                                     &pIndex
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
            BPT32Index_setP0(pIndex, pVtblL->pGetLBN(pLeft));
            eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetLBN(pRight);
            BPT32Index_Insert(pIndex, key, &index, NULL);
            // Note - No split should occur here.
            
            // Write the new block to the file.
            eRc =   RRDS_RecordWrite(
                                     this->pIO,
                                     BPT32Index_getLBN(pIndex),
                                     BPT32Index_getBlock(pIndex)
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
            
            // Make the new index block the root.
            obj_Release(this->pRoot);
            this->pRoot = pIndex;
            this->pHdr->root = BPT32Index_getLBN(pIndex);
            TRC_OBJ(this, "\tAdded new Root Index Block, %d\n", BPT32Index_getLBN(pIndex));
        }
        // We need to adjust index in parent index block for new block added
        else {
            TRC_OBJ(this, "\tAdding key to the parent index...\n");
            lbn = pVtblL->pGetLBN(pLeft);
            eRc = BPT32_BlockFindParent(this, lbn, &pObj);
            if (pObj && (OBJ_IDENT_BPT32INDEX == obj_getType(pObj)))
                ;
            else {
                // Parent should always be an index block if present.
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetLBN(pRight);
            eRc = BPT32Index_Insert(pObj, key, &index, NULL);
            TRC_OBJ(
                    this,
                    "\tAdded key %d index %d to the index %d\n",
                    key,
                    index,
                    BPT32Index_getLBN(pObj)
            );
        }
        
        return eRc;
    }

    

#ifdef XYZZY
    //---------------------------------------------------------------
    //               H e a d e r  R e a d / W r i t e
    //---------------------------------------------------------------
    
    ERESULT         BPT32_HeaderRead(
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        FILEIO_DATA     *pIO = OBJ_NIL;
        BPT32_HEADER    *pHdr;
        uint32_t        readAmt = 0;
        
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pHdr = mem_Malloc(sizeof(BPT32_HEADER));
        if (NULL == pHdr) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        pIO = FileIO_New( );
        if (OBJ_NIL == pIO) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }
        
        eRc = FileIO_Open(pIO, pPath, this->fMem);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }
        
        
        eRc = FileIO_Read(pIO, (uint32_t)(sizeof(BPT32_HEADER)), pHdr, &readAmt);
        if (!ERESULT_FAILED(eRc) && (readAmt == sizeof(BPT32_HEADER))) {
            this->blockSize = pHdr->blockSize;
            this->dataSize  = pHdr->dataSize;
            if (this->pHdr) {
                mem_Free(this->pHdr);
            }
            this->pHdr = pHdr;
            pHdr = NULL;
        }
        else {
            mem_Free(pHdr);
            pHdr = NULL;
        }

        FileIO_Close(pIO, false);
        obj_Release(pIO);
        pIO = OBJ_NIL;
        
        return eRc;
    }
    
    
    ERESULT         BPT32_HeaderWrite(
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        FILEIO_DATA     *pIO = OBJ_NIL;
        BPT32_HEADER    hdr;
        uint32_t        readAmt = 0;
        
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        BREAK_NULL(this->pHdr);
#endif
        
        pIO = FileIO_New( );
        if (OBJ_NIL == pIO) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }
        
        eRc = FileIO_Open(pIO, pPath, this->fMem);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pIO);
            pIO = OBJ_NIL;
            return ERESULT_OBJECT_CREATION;
        }
        
        
        eRc = FileIO_Write(pIO, (uint32_t)(sizeof(BPT32_HEADER)), this->pHdr);
        if (!ERESULT_FAILED(eRc) && (readAmt == sizeof(BPT32_HEADER))) {
            this->blockSize = hdr.blockSize;
            this->dataSize  = hdr.dataSize;
        }
        
        FileIO_Close(pIO, false);
        obj_Release(pIO);
        pIO = OBJ_NIL;
        
        return eRc;
    }
#endif
    
    




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPT32_DATA *     BPT32_Alloc (
        void
    )
    {
        BPT32_DATA       *this;
        uint32_t        cbSize = sizeof(BPT32_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BPT32_DATA *     BPT32_New (
        void
    )
    {
        BPT32_DATA       *this;
        
        this = BPT32_Alloc( );
        if (this) {
            this = BPT32_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          I/O
    //---------------------------------------------------------------
    
    RRDS_DATA * BPT32_getIO (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pIO;
    }
    
    
    bool        BPT32_setIO (
        BPT32_DATA  *this,
        RRDS_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pIO) {
            obj_Release(this->pIO);
        }
        this->pIO = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      M e m o r y  F i l e
    //---------------------------------------------------------------

    bool            BPT32_getMem (
        BPT32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return this->fMem;
    }


    bool            BPT32_setMem (
        BPT32_DATA      *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fMem = fValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P a t h
    //---------------------------------------------------------------
    
    PATH_DATA * BPT32_getPath (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pPath;
    }
    
    
    bool        BPT32_setPath (
        BPT32_DATA  *this,
        PATH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_PATH_OWNED
        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
#endif
        this->pPath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BPT32_getPriority (
        BPT32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BPT32_setPriority (
        BPT32_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        R o o t
    //---------------------------------------------------------------
    
    OBJ_ID      BPT32_getRoot (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pRoot;
    }
    
    
    bool        BPT32_setRoot (
        BPT32_DATA  *this,
        OBJ_ID      pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef  PROPERTY_ROOT_OWNED
        obj_Retain(pValue);
        if (this->pRoot) {
            obj_Release(this->pRoot);
        }
#endif
        this->pRoot = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R R D S
    //---------------------------------------------------------------
    
    RRDS_DATA * BPT32_getRRDS (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (RRDS_DATA *)this;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        BPT32_getSize (
        BPT32_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * BPT32_getStr (
        BPT32_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        BPT32_setStr (
        BPT32_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
#endif
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BPT32_getSuperVtbl (
        BPT32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                              A d d
    //---------------------------------------------------------------
    
    /*!
     @warning   This routine assumes that the root block exists before
                it is called.
     */
    ERESULT         BPT32_Add (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        //uint32_t        curNode;
        OBJ_ID          pObject = OBJ_NIL;

        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_NULL(this->pHdr);
        if (0 == key) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        TRC_OBJ(this, "BPT32_Add  key=%d\n", key);
        eRc = ObjArray_DeleteAll(this->pSrchStk);
        eRc = BPT32_BlockSearchKey(this, 0, key, pData);
        if (!ERESULT_FAILED(eRc)) {
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        // Top of Search Stack should contain a Leaf block
        // that the key should be inserted into.
        
        pObject = ObjArray_Top(this->pSrchStk);
        if (OBJ_IDENT_BPT32LEAF == obj_getType(pObject)){
            eRc = BPT32Leaf_Insert(pObject, key, pData);
        }
        else {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return eRc;
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
        ERESULT eRc = BPT32_Assign(this,pOther);
     @endcode 
     @param     this    BPT32 object pointer
     @param     pOther  a pointer to another BPT32 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BPT32_Assign (
        BPT32_DATA		*this,
        BPT32_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BPT32_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C l o s e
    //---------------------------------------------------------------
    
    ERESULT         BPT32_Close (
        BPT32_DATA      *this,
        bool            fDelete
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc =   RRDS_Close(
                    this->pIO,
                    fDelete
                );
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        this->pHdr = NULL;
        
        BPT32_setPath(this, OBJ_NIL);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             BPT32_Compare (
        BPT32_DATA      *this,
        BPT32_DATA      *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!BPT32_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

    

    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        BPT32      *pCopy = BPT32_Copy(this);
     @endcode 
     @param     this    BPT32 object pointer
     @return    If successful, a BPT32 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32_DATA *     BPT32_Copy (
        BPT32_DATA       *this
    )
    {
        BPT32_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BPT32_New( );
        if (pOther) {
            eRc = BPT32_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C r e a t e
    //---------------------------------------------------------------
    
    ERESULT         BPT32_Create (
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        LBN32_T         lbn;                // Logical Block Number
        BPT32LEAF_DATA  *pLeaf = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == this->pIO) {
            eRc = BPT32_SetupRRDS(this);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }
        
        this->pPath = Path_Copy(pPath);
        if (OBJ_NIL == this->pPath) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Set up rrds.
        eRc =   RRDS_SetupSizes(
                                this->pIO,
                                this->blockSize,
                                RRDS_RCD_TRM_NONE,
                                this->cLRU,
                                this->cHash
                );
        
        RRDS_setReserveSize(this->pIO, sizeof(BPT32_HEADER));
        eRc = RRDS_Create(this->pIO, pPath, this->fMem);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        this->pHdr = RRDS_getReserve(this->pIO);
        this->pHdr->blockSize = this->blockSize;
        this->pHdr->dataSize = this->dataSize;
        this->pHdr->actualSize = ROUNDUP4(this->dataSize);
        this->pHdr->cRecords = 1;                   // Allow for Header

        eRc =   BPT32_BlockRequest(
                                   this,
                                   BPT32_REQUEST_NEW_LEAF,
                                   OBJ_NIL,
                                   NULL,
                                   NULL,
                                   &pLeaf
                );
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pRoot = pLeaf;
        lbn = BPT32Leaf_getLBN(pLeaf);

        this->pHdr->root = lbn;
        this->pHdr->dataHead = lbn;
        this->pHdr->dataTail = lbn;
        this->pHdr->cRecords = lbn;

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            BPT32_Dealloc (
        OBJ_ID          objId
    )
    {
        BPT32_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPT32_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BPT32_setIO(this, OBJ_NIL);
        BPT32_setPath(this, OBJ_NIL);
        BPT32_setRoot(this, OBJ_NIL);
        BPT32_setStr(this, OBJ_NIL);
        if (this->pSrchStk) {
            obj_Release(this->pSrchStk);
            this->pSrchStk = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
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
    ERESULT         BPT32_Disable (
        BPT32_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!BPT32_Validate(this)) {
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
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32_Enable (
        BPT32_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!BPT32_Validate(this)) {
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
    //                          F i n d
    //---------------------------------------------------------------
    
    ERESULT         BPT32_Find (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pHdr) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (0 == this->pHdr->root) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        // Search for the key.
        ObjArray_DeleteAll(this->pSrchStk);
        eRc = BPT32_BlockSearchKey(this, this->pHdr->root, key, pData);

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F i r s t
    //---------------------------------------------------------------
    
    ERESULT         BPT32_First (
        BPT32_DATA      *this,
        uint32_t        *pKey,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        key;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pHdr) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (0 == this->pHdr->root) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        this->lastLSN = this->pHdr->dataHead;
        
        if (this->lastLSN) {
            eRc = BPT32_BlockRead(this, this->lastLSN, &pObj);
            if (ERESULT_FAILED(eRc) || (OBJ_NIL == pObj)) {
                return ERESULT_READ_ERROR;
            }
            eRc = BPT32Leaf_Get(pObj, 1, &key, pData);
            obj_Release(pObj);
            if (!ERESULT_FAILED(eRc)) {
                this->lastKey = key;
                if (pKey)
                    *pKey = key;
                return ERESULT_SUCCESS;
            }
        }
        
        // Return to caller.
        return ERESULT_EOF_ERROR;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPT32_DATA *   BPT32_Init (
        BPT32_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPT32_DATA);
        ERESULT         eRc;
        
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

        //this = (OBJ_ID)rrds_Init((RRDS_DATA *)this);      // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPT32);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BPT32_Vtbl);

        this->fMem = false;
        
        eRc = BPT32_SetupSizes(this, 64, sizeof(uint32_t), 8, 11);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pSrchStk = ObjArray_New();
        if (OBJ_NIL == this->pSrchStk) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
    #else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "BPT32::sizeof(BPT32_DATA) = %lu\n", sizeof(BPT32_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPT32_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BPT32_IsEnabled (
        BPT32_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
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
    //                          N e x t
    //---------------------------------------------------------------
    
    ERESULT         BPT32_Next (
        BPT32_DATA      *this,
        uint32_t        *pKey,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        key;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pHdr) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (0 == this->pHdr->root) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (0 == this->lastLSN) {
            DEBUG_BREAK();
            return ERESULT_EOF_ERROR;
        }
#endif
        
        //TODO: A leaf block split in the middle of this might mess
        //      up our tracking.  We might need to do a BlockSearchKey()
        //      on key to reset.  Deletion needs to check the saved key
        //      and update it as well.

        // Search for the key in the last block.
        eRc = BPT32_BlockRead(this, this->lastLSN, &pObj);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pObj)) {
            return ERESULT_READ_ERROR;
        }
        eRc = BPT32Leaf_FindKey(pObj, this->lastKey, NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pObj);
            return ERESULT_GENERAL_FAILURE;
        }
        eRc = BPT32Leaf_NextKey(pObj, &key, pData);
        if (!ERESULT_FAILED(eRc)) {
            this->lastKey = key;
            if (pKey)
                *pKey = key;
            obj_Release(pObj);
            return ERESULT_SUCCESS;
        }
        this->lastLSN = BPT32Leaf_getNext(pObj);
        obj_Release(pObj);

        if (this->lastLSN) {
            eRc = BPT32_BlockRead(this, this->lastLSN, &pObj);
            if (ERESULT_FAILED(eRc) || (OBJ_NIL == pObj)) {
                return ERESULT_READ_ERROR;
            }
            eRc = BPT32Leaf_Get(pObj, 1, &key, pData);
            obj_Release(pObj);
            if (!ERESULT_FAILED(eRc)) {
                this->lastKey = key;
                if (pKey)
                    *pKey = key;
                return ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        return ERESULT_EOF_ERROR;
    }
    
    
    
    //---------------------------------------------------------------
    //                       O p e n
    //---------------------------------------------------------------
    
    ERESULT         BPT32_Open (
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == this->pIO) {
            eRc = BPT32_SetupRRDS(this);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }

        this->pPath = Path_Copy(pPath);
        if (OBJ_NIL == this->pPath) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Setup sizes from our merged sizes.
        eRc =   RRDS_SetupSizes(
                                this->pIO,
                                this->blockSize,
                                RRDS_RCD_TRM_NONE,
                                this->cLRU,
                                this->cHash
                );

        RRDS_setReserveSize(this->pIO, sizeof(BPT32_HEADER));
        eRc =   RRDS_Open(this->pIO, pPath, this->fMem);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        this->pHdr = RRDS_getReserve(this->pIO);

        // Return to caller.
        return eRc;
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
        void        *pMethod = BPT32_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BPT32", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BPT32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BPT32_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BPT32_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'B':
                        if (str_Compare("BlockRequest", (char *)pStr) == 0) {
                            return BPT32_BlockRequest;
                        }
                        break;
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return BPT32_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BPT32_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BPT32_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BPT32_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BPT32_ToDebugString)
                    return "ToDebugString";
                if (pData == BPT32_ToJSON)
                    return "ToJson";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         BPT32_SetupRRDS(
        BPT32_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pIO) {
            this->pIO = RRDS_New( );
            if (OBJ_NIL == this->pIO) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc =   RRDS_SetupSizes(
                    this->pIO,
                    this->blockSize,
                    RRDS_RCD_TRM_NONE,
                    this->cLRU,
                    this->cHash
                );

        this->pLRU = RRDS_getLRU(this->pIO);

        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         BPT32_SetupSizes(
        BPT32_DATA      *this,
        uint32_t        blockSize,
        uint16_t        dataSize,
        uint16_t        cLRU,
        uint16_t        cHash
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((blockSize > 0) && (blockSize > sizeof(BPT32_HEADER)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (dataSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (dataSize > (blockSize - sizeof(BPT32INDEX_BLOCK))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (cLRU > 2)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Just store values.  We will set up the LRU and RRDS systems
        // upon Create() or Open(), because we don't need them until
        // then.
        
        this->blockSize = blockSize;
        this->dataSize = dataSize;
        this->cLRU = cLRU;
        this->cHash = cHash;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     BPT32_ToJSON (
        BPT32_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT32_ToDebugString(this,4);
     @endcode 
     @param     this    BPT32 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32_ToDebugString (
        BPT32_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
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
                    "{%p(%s)\n",
                    this,
                    pInfo->pClassName
            );

        if (this->pHdr) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+2, ' ');
                AStr_AppendA(pStr, "* * *  Header Record  * * *\n");
                AStr_AppendCharRepeatA(pStr, indent+2, ' ');
                eRc = AStr_AppendPrint(
                                       pStr,
                                       "blockSize = %d  dataSize = %d  actualSize = %d  "
                                       "cRecords = %d\n",
                                       this->pHdr->blockSize,
                                       this->pHdr->dataSize,
                                       this->pHdr->actualSize,
                                       this->pHdr->cRecords
                        );
                AStr_AppendCharRepeatA(pStr, indent+2, ' ');
                eRc = AStr_AppendPrint(
                                       pStr,
                                       "root = %d  dataHead = %d  dataTail = %d  "
                                       "deleteHead = %d\n",
                                       this->pHdr->root,
                                       this->pHdr->dataHead,
                                       this->pHdr->dataTail,
                                       this->pHdr->deleteHead
                    );
            }

            AStr_AppendCharRepeatA(pStr, indent+2, ' ');
            AStr_AppendA(pStr, "* * *  Blocks  * * *\n");
            iMax = this->pHdr->cRecords;
            for (i=2; i<=iMax; ++i) {
                ASTR_DATA           *pWrk;
                OBJ_ID              pObj;
                OBJ_IUNKNOWN        *pVtbl;
                eRc = BPT32_BlockRead(this, i, &pObj);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
                pVtbl = obj_getVtbl(pObj);
                pWrk = pVtbl->pToDebugString(pObj, indent+4);
                AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                obj_Release(pObj);
            }
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
    bool            BPT32_Validate (
        BPT32_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BPT32))
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


        if (!(obj_getSize(this) >= sizeof(BPT32_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


