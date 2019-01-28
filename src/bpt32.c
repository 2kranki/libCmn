// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   bpt32.c
 *	Generated 01/12/2019 14:04:44
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
#include        <bpt32_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         bpt32_BlockFindParent(
        BPT32_DATA      *this,
        uint32_t        lsn,
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          *pObj;
        uint32_t        iMax;
        uint32_t        i;
        uint32_t        index;
        BPT32_BLK_VTBL  *pVtbl = NULL;

        TRC_OBJ(this, "bpt32_BlockFindParent lsn=%d\n", lsn);
        
        if (ppObj)
            *ppObj = OBJ_NIL;
        iMax = objArray_getSize(this->pSrchStk);
        for (i=iMax; i>0; --i) {
            pObj = objArray_Get(this->pSrchStk, i);
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
            index = pVtbl->pGetIndex(pObj);
            if (lsn == index) {
                if (i > 1) {
                    pObj = objArray_Get(this->pSrchStk, (i - 1));
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
    ERESULT         bpt32_BlockRequest(
        BPT32_DATA      *this,
        OBJ_ID          pObj,
        uint32_t        request,
        void            *pRet
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPT32IDX_DATA   *pIndex = OBJ_NIL;
        BPT32LF_DATA    *pLeaf = OBJ_NIL;
        uint32_t        lsn = 0;
        void            *pBlock = NULL;
        BPT32_BLK_VTBL  *pVtbl = NULL;
        
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        TRC_OBJ(this, "bpt32_BlockRequest req=%d\n", request);
#endif
        
        switch (request) {
                
            case BPT32_REQUEST_NEW_INDEX:
                if (NULL == pRet) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lsn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Index Block %d\n", lsn);
                pIndex =    bpt32idx_NewWithSizes(
                                             this->blockSize,
                                             this->dataSize,
                                             lsn,
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
                eRc =   rrds_RecordWrite(
                                         (RRDS_DATA *)this,
                                         bpt32idx_getIndex(pIndex),
                                         bpt32idx_getBlock(pIndex)
                                         );
                if (pRet)
                    *((void **)pRet) = pIndex;
                else
                    obj_Release(pIndex);
                pIndex = NULL;
                break;
                
            case BPT32_REQUEST_NEW_LEAF:
                if (NULL == pRet) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lsn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Leaf Block %d\n", lsn);
                pLeaf = bpt32lf_NewWithSizes(
                                             this->blockSize,
                                             this->dataSize,
                                             lsn,
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
                eRc =   rrds_RecordWrite(
                                         (RRDS_DATA *)this,
                                         bpt32lf_getIndex(pLeaf),
                                         bpt32lf_getBlock(pLeaf)
                        );
                if (pRet)
                    *((void **)pRet) = pLeaf;
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
                lsn = pVtbl->pGetIndex(pObj);
                TRC_OBJ(this, "\tFind Parent for %d...\n", lsn);
                eRc = bpt32_BlockFindParent(this, lsn, pRet);
                break;
                
            case BPT32_REQUEST_READ:
                if (OBJ_IDENT_BPT32IDX == obj_getType(pObj)) {
                    lsn = bpt32idx_getIndex((BPT32IDX_DATA *)pObj);
                    TRC_OBJ(this, "\tRead data for index block %d...\n", lsn);
                    if (NULL == bpt32idx_getBlock((BPT32IDX_DATA *)pObj)) {
                        eRc =   bpt32idx_Setup(
                                              (BPT32IDX_DATA *)pObj,
                                              this->blockSize,
                                               this->dataSize,
                                              lsn,
                                              true
                                              );
                        bpt32idx_setManager((BPT32IDX_DATA *)pObj, (OBJ_ID)this);
                    }
                    pBlock = bpt32idx_getBlock(pObj);
                }
                if (OBJ_IDENT_BPT32LF == obj_getType(pObj)) {
                    if (NULL == pObj) {
                        DEBUG_BREAK();
                        return ERESULT_INVALID_PARAMETER;
                    }
                    pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
                    lsn = pVtbl->pGetIndex(pObj);
                    TRC_OBJ(this, "\tRead data for leaf block %d...\n", lsn);
                    pBlock = pVtbl->pGetBlock(pObj);
                    if (NULL == pBlock) {
                        eRc = pVtbl->pSetup(
                                            pObj,
                                            this->blockSize,
                                            this->dataSize,
                                            lsn,
                                            true
                                );
                        pVtbl->pSetManager(pObj, this);
                    }
                    pBlock = bpt32lf_getBlock((BPT32LF_DATA *)pObj);
                }
                if (lsn && pBlock) {
                    eRc =   rrds_RecordRead(
                                            (RRDS_DATA *)this,
                                            lsn,
                                            pBlock
                            );
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
                break;
                
            case BPT32_REQUEST_SPLIT:
                TRC_OBJ(this, "\tSplit Block...\n");
                eRc = bpt32_BlockSplit(this, (OBJ_ID)pObj, pRet);
                break;
                
            case BPT32_REQUEST_TAIL:
                TRC_OBJ(this, "\tSet new data tail...\n");
                if (OBJ_IDENT_BPT32LF == obj_getType(pObj)) {
                    this->pHdr->dataTail = bpt32lf_getIndex((BPT32LF_DATA *)pObj);
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
                lsn = pVtbl->pGetIndex(pObj);
                TRC_OBJ(this, "\tWrite data for block %d...\n", lsn);
                pBlock = pVtbl->pGetBlock(pObj);
                if (lsn && pBlock) {
                    eRc =   rrds_RecordWrite(
                                             (RRDS_DATA *)this,
                                             lsn,
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
    
    
    
    ERESULT         bpt32_BlockRead(
        BPT32_DATA      *this,
        uint32_t        lsn,
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        BPT32IDX_DATA   *pIndex = OBJ_NIL;
        BPT32LF_DATA    *pLeaf = OBJ_NIL;
        uint16_t        *pData;
        
        TRC_OBJ(this, "bpt32_BlockRead lsn=%d\n", lsn);
        
        // Load the block into the LRU.
        eRc =   rrds_RecordRead((RRDS_DATA *)this, lsn, NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            TRC_OBJ(this, "\tRead Error!\n");
            return eRc;
        }
        
        pData = (uint16_t *)lru_FindBuffer((LRU_DATA *)this, lsn);
        if (*pData == OBJ_IDENT_BPT32IDX) {
            pIndex = bpt32idx_New();
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
            eRc = bpt32idx_Setup(pIndex, this->blockSize, this->dataSize, lsn, true);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tIndex Block Setup Error!\n");
                obj_Release(pIndex);
                return eRc;
            }
            bpt32idx_setManager(pIndex, (void *)this);
            bpt32idx_CopyFrom(pIndex, (void *)pData);
            if (ppObj)
                *ppObj = pIndex;
            else
                obj_Release(pIndex);
            pIndex = OBJ_NIL;
            TRC_OBJ(this, "\tFound index Block\n");
        }
        else if (*pData == OBJ_IDENT_BPT32LF) {
            pLeaf = bpt32lf_New();
            if (OBJ_NIL == pLeaf) {
                DEBUG_BREAK();
                TRC_OBJ(this, "\tCould not create Leaf Block Error!\n");
                return ERESULT_OUT_OF_MEMORY;
            }
#ifdef NDEBUG
#else
            if (obj_Trace(this))
                obj_TraceSet(pLeaf, true);
#endif
            eRc = bpt32lf_Setup(pLeaf, this->blockSize, this->dataSize, lsn, true);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tLeaf Block Setup Error!\n");
                obj_Release(pLeaf);
                return eRc;
            }
            bpt32lf_setManager(pLeaf, (void *)this);
            bpt32lf_CopyFrom(pLeaf, (void *)pData);
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
     @param     lsn         Block Number to start with
     @param     key         key to be looked for
     @param     pData       Optional pointer to the returned data for the key
                            if found
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   this->srchCur should be zeroed before a search begins.
     */
    ERESULT         bpt32_BlockSearchKey (
        BPT32_DATA      *this,
        uint32_t        lsn,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc;
        uint32_t        nodeIndex = 0;
        OBJ_ID          pObject = OBJ_NIL;
        bool            fMore = true;
        bool            fRead = false;
        
        // Do initialization.
        TRC_OBJ(this, "bpt32_BlockSearchKey lsn=%d, key=%d\n", lsn, key);
        
        if (0 == lsn) {         // Use the root.
            pObject = this->pRoot;
            TRC_OBJ(this, "\tUsing Root for first block\n");
        }
        
        while (fMore) {
            fRead = false;
            if (pObject)
                ;
            else {
                // Read the root block into the common buffer.
                TRC_OBJ(this, "\tReading %d\n", lsn);
                eRc = bpt32_BlockRead(this, lsn, &pObject);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    return eRc;
                }
                fRead = true;
            }
            
            if (pObject) {
                objArray_Push(this->pSrchStk, pObject);
            }
            else {
                return ERESULT_GENERAL_FAILURE;
            }
            if (fRead)
                obj_Release(pObject);       // objArray has retained it.

            if ( pObject) {
                if (obj_getType(pObject) == OBJ_IDENT_BPT32LF) {
                    eRc = bpt32lf_FindKey(pObject, key, pData);
                    if (ERESULT_FAILED(eRc)) {
                        TRC_OBJ(this, "\tLeaf block, key %d not found\n", key);
                    }
                    else {
                        TRC_OBJ(this, "\tLeaf block, key %d found\n", key);
                    }
                    return eRc;
                }
                else if (obj_getType(pObject) == OBJ_IDENT_BPT32IDX) {
                    eRc = bpt32idx_FindKey(pObject, key, &nodeIndex);
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
            
            lsn = nodeIndex;
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
    ERESULT         bpt32_BlockSplit(
        BPT32_DATA      *this,
        OBJ_ID          *pLeft,
        OBJ_ID          *pRight
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPT32IDX_DATA   *pIndex = OBJ_NIL;
        OBJ_ID          pObj;
        uint32_t        key = 0;
        uint32_t        index = 0;
        uint32_t        lsn = 0;
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
                "bpt32_BlockSplit Left: type=%d lsn=%d, Right: type=%d lsn=%d\n",
                obj_getType(pLeft),
                pVtblR->pGetIndex(pLeft),
                obj_getType(pRight),
                pVtblR->pGetIndex(pRight)
        );

        // We are splitting the Root!
        if (this->pRoot == pLeft) {
            TRC_OBJ(this, "\tSplitting the root...\n");
            eRc = bpt32_BlockRequest(this, OBJ_NIL, BPT32_REQUEST_NEW_INDEX, &pIndex);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
            bpt32idx_setP0(pIndex, pVtblL->pGetIndex(pLeft));
            eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetIndex(pRight);
            bpt32idx_Insert(pIndex, key, &index, NULL);
            // Note - No split should occur here.
            
            // Write the new block to the file.
            eRc =   rrds_RecordWrite(
                                     (RRDS_DATA *)this,
                                     bpt32idx_getIndex(pIndex),
                                     bpt32idx_getBlock(pIndex)
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
            
            // Make the new index block the root.
            obj_Release(this->pRoot);
            this->pRoot = pIndex;
            this->pHdr->root = bpt32idx_getIndex(pIndex);
            fprintf(stderr, "\tAdded new Root Index Block, %d\n", bpt32idx_getIndex(pIndex));
        }
        // We need to adjust index in parent index block for new block added
        else {
            TRC_OBJ(this, "\tAdding key to the parent index...\n");
            lsn = pVtblL->pGetIndex(pLeft);
            eRc = bpt32_BlockFindParent(this, lsn, &pObj);
            if (pObj && (OBJ_IDENT_BPT32IDX == obj_getType(pObj)))
                ;
            else {
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetIndex(pRight);
            eRc = bpt32idx_Insert(pObj, key, &index, NULL);
            TRC_OBJ(
                    this,
                    "\tAdded key %d index %d to the index %d\n",
                    key,
                    index,
                    bpt32idx_getIndex(pObj)
            );
        }
        
        return eRc;
    }

    
    
    //---------------------------------------------------------------
    //               H e a d e r  R e a d / W r i t e
    //---------------------------------------------------------------
    
    ERESULT         bpt32_HeaderRead(
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
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pHdr = mem_Malloc(sizeof(BPT32_HEADER));
        if (NULL == pHdr) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        pIO = fileio_New( );
        if (OBJ_NIL == pIO) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }
        
        eRc = fileio_Open(pIO, pPath);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }
        
        
        eRc = fileio_Read(pIO, (uint32_t)(sizeof(BPT32_HEADER)), pHdr, &readAmt);
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

        fileio_Close(pIO, false);
        obj_Release(pIO);
        pIO = OBJ_NIL;
        
        return eRc;
    }
    
    
    ERESULT         bpt32_HeaderWrite(
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
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        BREAK_NULL(this->pHdr);
#endif
        
        pIO = fileio_New( );
        if (OBJ_NIL == pIO) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }
        
        eRc = fileio_Open(pIO, pPath);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pIO);
            pIO = OBJ_NIL;
            return ERESULT_OBJECT_CREATION;
        }
        
        
        eRc = fileio_Write(pIO, (uint32_t)(sizeof(BPT32_HEADER)), this->pHdr);
        if (!ERESULT_FAILED(eRc) && (readAmt == sizeof(BPT32_HEADER))) {
            this->blockSize = hdr.blockSize;
            this->dataSize  = hdr.dataSize;
        }
        
        fileio_Close(pIO, false);
        obj_Release(pIO);
        pIO = OBJ_NIL;
        
        return eRc;
    }
    
    




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPT32_DATA *     bpt32_Alloc (
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



    BPT32_DATA *     bpt32_New (
        void
    )
    {
        BPT32_DATA       *this;
        
        this = bpt32_Alloc( );
        if (this) {
            this = bpt32_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          L R U
    //---------------------------------------------------------------
    
    LRU_DATA *  bpt32_getLRU (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (LRU_DATA *)this;
    }
    
    

    //---------------------------------------------------------------
    //                          P a t h
    //---------------------------------------------------------------
    
    PATH_DATA * bpt32_getPath (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pPath;
    }
    
    
    bool        bpt32_setPath (
        BPT32_DATA  *this,
        PATH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
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
    
    uint16_t        bpt32_getPriority (
        BPT32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            bpt32_setPriority (
        BPT32_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                     R e a d  W r i t e
    //---------------------------------------------------------------
    
    bool            bpt32_setReadWrite (
        BPT32_DATA     *this,
        ERESULT         (*pBlockRead) (
            OBJ_ID          pObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
                        ),
        ERESULT         (*pBlockWrite) (
            OBJ_ID          pObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
                        ),
        OBJ_ID          pBlockObject
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pBlockRead   = pBlockRead;
        this->pBlockWrite  = pBlockWrite;
        this->pBlockObject = pBlockObject;

        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        R o o t
    //---------------------------------------------------------------
    
    OBJ_ID      bpt32_getRoot (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pRoot;
    }
    
    
    bool        bpt32_setRoot (
        BPT32_DATA  *this,
        OBJ_ID      pValue
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
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
    
    RRDS_DATA * bpt32_getRRDS (
        BPT32_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (RRDS_DATA *)this;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        bpt32_getSize (
        BPT32_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * bpt32_getStr (
        BPT32_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        bpt32_setStr (
        BPT32_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  bpt32_getSuperVtbl (
        BPT32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
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
    ERESULT         bpt32_Add (
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
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_NULL(this->pHdr);
#endif
        TRC_OBJ(this, "bpt32_Add  key=%d\n", key);
        eRc = objArray_DeleteAll(this->pSrchStk);
        eRc = bpt32_BlockSearchKey(this, 0, key, pData);
        if (!ERESULT_FAILED(eRc)) {
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        // Top of Search Stack should contain a Leaf block
        // that the key should be inserted into.
        
        pObject = objArray_Top(this->pSrchStk);
        if (OBJ_IDENT_BPT32LF == obj_getType(pObject)){
            eRc = bpt32lf_Insert(pObject, key, pData);
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
        ERESULT eRc = bpt32_Assign(this,pOther);
     @endcode 
     @param     this    BPT32 object pointer
     @param     pOther  a pointer to another BPT32 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         bpt32_Assign (
        BPT32_DATA		*this,
        BPT32_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!bpt32_Validate(pOther)) {
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
    
    ERESULT         bpt32_Close (
        BPT32_DATA      *this,
        bool            fDelete
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = rrds_Close((RRDS_DATA *)this, fDelete);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        eRc = bpt32_HeaderWrite(this, this->pPath);
        bpt32_setPath(this, OBJ_NIL);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        if (this->pHdr) {
            mem_Free(this->pHdr);
            this->pHdr = NULL;
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
    ERESULT         bpt32_Compare (
        BPT32_DATA     *this,
        BPT32_DATA     *pOther
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
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!bpt32_Validate(pOther)) {
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
        bpt32      *pCopy = bpt32_Copy(this);
     @endcode 
     @param     this    BPT32 object pointer
     @return    If successful, a BPT32 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32_DATA *     bpt32_Copy (
        BPT32_DATA       *this
    )
    {
        BPT32_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = bpt32_New( );
        if (pOther) {
            eRc = bpt32_Assign(this, pOther);
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
    
    ERESULT         bpt32_Create (
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        uint32_t        index;
        BPT32LF_DATA    *pLeaf = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        this->pPath = path_Copy(pPath);
        if (OBJ_NIL == this->pPath) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Set up rrds.
        eRc =   rrds_SetupSizes(
                                (RRDS_DATA *)this,
                                this->blockSize,
                                RRDS_RCD_TRM_NONE,
                                this->cLRU,
                                this->cHash
                );
        
        if (this->pHdr) {
            mem_Free(this->pHdr);
            //this->pHdr = NULL;
        }
        this->pHdr = mem_Calloc(1, sizeof(BPT32_HEADER));
        if (NULL == this->pHdr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pHdr->blockSize = this->blockSize;
        this->pHdr->dataSize = this->dataSize;
        this->pHdr->actualSize = ROUNDUP4(this->dataSize);
        this->pHdr->cRecords = 1;                   // Allow for Header

        eRc = rrds_Create((RRDS_DATA *)this, pPath);
        
        eRc = bpt32_BlockRequest(this, OBJ_NIL, BPT32_REQUEST_NEW_LEAF, &pLeaf);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pRoot = pLeaf;
        index = bpt32lf_getIndex(pLeaf);

        this->pHdr->root = index;
        this->pHdr->dataHead = index;
        this->pHdr->dataTail = index;
        this->pHdr->cRecords = index;

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            bpt32_Dealloc (
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
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPT32_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        bpt32_setPath(this, OBJ_NIL);
        bpt32_setRoot(this, OBJ_NIL);
        bpt32_setStr(this, OBJ_NIL);
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
    ERESULT         bpt32_Disable (
        BPT32_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!bpt32_Validate(this)) {
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
    ERESULT         bpt32_Enable (
        BPT32_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!bpt32_Validate(this)) {
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
    
    ERESULT         bpt32_Find (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
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
        objArray_DeleteAll(this->pSrchStk);
        eRc = bpt32_BlockSearchKey(this, this->pHdr->root, key, pData);

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPT32_DATA *   bpt32_Init (
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

        this = (OBJ_ID)rrds_Init((RRDS_DATA *)this);      // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPT32);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_BPT32);    // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&bpt32_Vtbl);
        
        eRc = bpt32_SetupSizes(this, 64, sizeof(uint32_t), 8, 11);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pSrchStk = objArray_New();
        if (OBJ_NIL == this->pSrchStk) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        rrds_setFillChar((RRDS_DATA *)this, '\0');

#ifdef NDEBUG
    #else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "bpt32::sizeof(BPT32_DATA) = %lu\n", sizeof(BPT32_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPT32_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         bpt32_IsEnabled (
        BPT32_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
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
    //                       O p e n
    //---------------------------------------------------------------
    
    ERESULT         bpt32_Open (
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        this->pPath = path_Copy(pPath);
        if (OBJ_NIL == this->pPath) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Get block and data sizes from header.
        eRc = bpt32_HeaderRead(this, pPath);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        // Setup sizes from our merged sizes.
        eRc =   rrds_SetupSizes(
                                (RRDS_DATA *)this,
                                this->blockSize,
                                RRDS_RCD_TRM_NONE,
                                this->cLRU,
                                this->cHash
                                );

        eRc = rrds_Open((RRDS_DATA *)this, pPath);
        
#ifdef XYZZY
        this->pBlock = mem_Calloc(1, this->blockSize);
        if (NULL == this->pBlock) {
            return ERESULT_OUT_OF_MEMORY;
        }
#endif
        
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
        void        *pMethod = bpt32_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "bpt32", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          bpt32_QueryInfo (
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
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BPT32_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)bpt32_Class();
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
                            return bpt32_BlockRequest;
                        }
                        break;
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return bpt32_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return bpt32_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return bpt32_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return bpt32_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == bpt32_ToDebugString)
                    return "ToDebugString";
                if (pData == bpt32_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         bpt32_SetupSizes(
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
        if (!bpt32_Validate(this)) {
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
        if (dataSize > (blockSize - sizeof(BPT32IDX_BLOCK))) {
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
    
     ASTR_DATA *     bpt32_ToJSON (
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
        if (!bpt32_Validate(this)) {
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
        ASTR_DATA      *pDesc = bpt32_ToDebugString(this,4);
     @endcode 
     @param     this    BPT32 object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     bpt32_ToDebugString (
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
        if (!bpt32_Validate(this)) {
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
                eRc = bpt32_BlockRead(this, i, &pObj);
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
    bool            bpt32_Validate (
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


