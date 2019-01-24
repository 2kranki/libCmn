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

    /*!
     @warning   This method must always conform to P_ERESULT_EXIT4.
     */
    ERESULT         bpt32_BlockRequestIndex(
        BPT32_DATA      *this,
        BPT32IDX_DATA   *pObj,
        uint32_t        request,
        void            *pRet
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        index;
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (sizeof(void *) < sizeof(uint32_t)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        switch (request) {
                
            case BPT32_INDEX_REQUEST_BLOCK_NEW:
                index = ++this->pHdr->cRecords;
                *((uint32_t *)pRet) = index;
                break;
                
            case BPT32_INDEX_REQUEST_WRITE:
                eRc =   rrds_RecordWrite(
                                (RRDS_DATA *)this,
                                bpt32idx_getIndex(pObj),
                                bpt32idx_getBlock(pObj)
                        );
                break;
                
            default:
                return ERESULT_INVALID_REQUEST;
                break;
        }
        
        return eRc;
    }

    
    
    /*!
     @warning   This method must always conform to P_ERESULT_EXIT4.
     */
    ERESULT         bpt32_BlockRequestLeaf(
        BPT32_DATA      *this,
        BPT32IDX_DATA   *pObj,
        uint32_t        request,
        void            *pRet
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        switch (request) {
                
            case BPT32_LEAF_REQUEST_WRITE:
                eRc =   rrds_RecordWrite(
                                         (RRDS_DATA *)this,
                                         bpt32idx_getIndex(pObj),
                                         bpt32idx_getBlock(pObj)
                        );
                break;
                
            default:
                return ERESULT_INVALID_REQUEST;
                break;
        }
        
        return eRc;
    }
    
    
    
    ERESULT         bpt32_BlockFlushIdx(
        BPT32_DATA      *this,
        BPT32IDX_DATA   *pValue
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
        
        return ERESULT_NOT_IMPLEMENTED;
    }

    
    
    ERESULT         bpt32_BlockIndexChangedIdx(
        BPT32_DATA      *this,
        BPT32IDX_DATA   *pValue
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
        
        return ERESULT_NOT_IMPLEMENTED;
    }

    
    
    ERESULT         bpt32_BlockInit(
        BPT32_BLOCK     *pBlock,
        uint16_t        blockType,      // OBJ_IDENT_BPT32IDX or OBJ_IDENT_BPT32LF
        uint32_t        blockSize,
        uint16_t        dataSize,       // If Index, use sizeof(uint32_t) for this.
        uint32_t        blockIndex
    )
    {
        //ERESULT         eRc;

#ifdef NDEBUG
#else
        if (NULL == pBlock) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((blockType == OBJ_IDENT_BPT32IDX) || (blockType == OBJ_IDENT_BPT32LF))
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (blockType == OBJ_IDENT_BPT32IDX) {
            dataSize = sizeof(uint32_t);
        }
        
        memset(pBlock, 0, sizeof(BPT32_BLOCK));
        pBlock->blockType = blockType;
        pBlock->dataSize = dataSize;
        pBlock->actualSize = ROUNDUP4(dataSize);
        pBlock->max = (blockSize - sizeof(BPT32_BLOCK));
        pBlock->max /=  (sizeof(BPT32_NODE) + pBlock->actualSize);
        pBlock->index = blockIndex;

        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         bpt32_BlockRead(
        BPT32_DATA      *this,
        uint32_t        lsn
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        
        eRc =   rrds_RecordRead(bpt32_getRRDS(this), lsn, (void *)this->pBlock);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        this->blockLsn = lsn;
        this->blockIndex = -1;

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
    ERESULT         bpt32_BlockSearch (
        BPT32_DATA      *this,
        uint32_t        lsn,
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc;
        BPT32_NODE      *pNode = NULL;
        
        // Do initialization.
        
        // Read the root block into the common buffer.
    nextRecord:
        eRc = bpt32_BlockRead(this, lsn);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        if (this->srchCur < this->srchMax)
            this->pSrchStk[this->srchCur++] = lsn;
        else {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }

        this->blockIndex = -1;
        pNode = bpt32_NodeFind(this->pBlock, key, &this->blockIndex);
        if (this->pBlock->blockType == OBJ_IDENT_BPT32LF) {
            if (key == pNode->key) {
                if (pData) {
                    this->pBlockNode = pNode;
                    memmove(pData, pNode->data, this->dataSize);
                }
                return ERESULT_SUCCESS;
            }
            // Work Block will be set up for insert if needed.
            return ERESULT_DATA_NOT_FOUND;
        }
        
        lsn = *((uint32_t *)pNode->data);
        goto nextRecord;

        // Return to caller.
        return ERESULT_DATA_NOT_FOUND;
    }
    
    
    
    /*!
     Split the work block in half.  Moving the second half of the block to the new
     block.  After the block is split, the previous index of the next index
     from the current block will have to be updated to the new block.  This
     assumes that the new block has its own record index set before this method
     is called.
     @param     this        Object Pointer
     @param     pIndex      Optional pointer to the returned new block's index
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bpt32_BlockSplit(
        BPT32_DATA      *this,
        uint32_t        *pIndex         // New Block Index
    )
    {
        ERESULT         eRc;
        uint32_t        half;
        uint32_t        cNew;
        uint32_t        indexNew;
        uint32_t        indexNext = 0;
        BPT32_BLOCK     *pNew = NULL;

#ifdef NDEBUG
#else
        if (this->pBlock->used < 2) {
            DEBUG_BREAK();
            return ERESULT_DATA_TOO_SMALL;
        }
#endif
        if (pIndex)
            *pIndex = 0;

        half = this->pBlock->used >> 1;
        cNew = this->pBlock->used - half;
        
        pNew = mem_Malloc(this->blockSize);
        if (NULL == pNew) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Copy second half of data to new object.
        memmove(
                pNew->nodes,
                &this->pBlock->nodes[half],
                (cNew * (sizeof(BPT32_NODE) + this->pBlock->actualSize))
        );
        pNew->max = this->pBlock->max;
        pNew->used = cNew;
        this->pBlock->used = half;
        pNew->blockType = this->pBlock->blockType;
        pNew->actualSize = this->pBlock->actualSize;
        
        // Update the indices inserting the new block after the block being split.
        indexNew = ++this->pHdr->cRecords;
        pNew->index = indexNew;
        if (this->pBlock->blockType == OBJ_IDENT_BPT32LF) {
            pNew->next = this->pBlock->next;
            if (pNew->next == 0)
                this->pHdr->dataTail = indexNew;
            this->pBlock->next = indexNew;
            pNew->prev = this->pBlock->index;
            indexNext = pNew->next;
        }
        
        eRc = rrds_RecordWrite((RRDS_DATA *)this, indexNew, (void *)pNew);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            mem_Free(pNew);
            return eRc;
        }
        
        if (indexNext && (this->pBlock->blockType == OBJ_IDENT_BPT32LF)) {
            eRc = rrds_RecordRead((RRDS_DATA *)this, indexNew, (void *)pNew);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                mem_Free(pNew);
                return eRc;
            }
            pNew->prev = indexNew;
            eRc = rrds_RecordWrite((RRDS_DATA *)this, indexNew, (void *)pNew);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                mem_Free(pNew);
                return eRc;
            }
        }
        
        mem_Free(pNew);
        pNew = NULL;

        eRc = rrds_RecordWrite((RRDS_DATA *)this, this->blockIndex, (void *)this->pBlock);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        if (pIndex)
            *pIndex = indexNew;
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
    
    

    //---------------------------------------------------------------
    //                      N o d e  F i n d
    //---------------------------------------------------------------
    /*!
     This method is responsible for locating the smallest key in the
     block greater than or equal to the search key.  So, the index
     returned points to the node where the key was found or where the
     key should be inserted.
     @param pBlock      Pointer to Block
     @param key         search key
     @param pIndex      Optional pointer to index of found key or
                        insertion point returned
     */
    BPT32_NODE *    bpt32_NodeFind (
        BPT32_BLOCK     *pBlock,        // Block
        uint32_t        key,            // Search Key
        uint32_t        *pIndex
    )
    {
        //ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32_NODE      *pNode = NULL;
        uint32_t        i = 0;
        uint32_t        High = 0;
        uint32_t        Low = 0;
        uint32_t        Mid;
        int             rc;
        
        // Do initialization.
        
        if (pBlock->used < 10) {
            // Do a sequential search.
            for (i=0; i<pBlock->used; ++i) {
                pNode = bpt32_Index2Node(pBlock, i);
                if (key > pNode->key)
                    ;
                else {
                    break;
                }
            }
        }
        else {
            // Do a binary search.
            High = pBlock->used - 1;
            while( Low < High ) {
                Mid = (High + Low) / 2;
                i = Mid;
                pNode = bpt32_Index2Node(pBlock, Mid);
                rc = key - pNode->key;
                if( rc < 0 )
                    High = Mid;
                else if( rc == 0 ) {
                    break;
                }
                else
                    Low = Mid + 1;
            }
            if( High == Low ) {
                pNode = bpt32_Index2Node(pBlock, Low);
                i = Low;
                rc = key - pNode->key;
            }
        }
        
        // Return to caller.
        if (pIndex)
            *pIndex = i;
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                N o d e  F r o m  I n d e x
    //---------------------------------------------------------------
    
    BPT32_NODE *    bpt32_Index2Node (
        BPT32_BLOCK     *pBlock,
        uint32_t        index                // Relative to 0
    )
    {
        BPT32_NODE      *pNode = NULL;
        uint32_t        i = 0;
        
        if (index == 0) {
            return pBlock->nodes;
        }
        
        i = index * (sizeof(BPT32_NODE) + pBlock->actualSize);
        pNode = (BPT32_NODE *)(((uint8_t *)pBlock->nodes) + i);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D e l e t e  N o d e
    //---------------------------------------------------------------
    
    /*!
     Delete the entry if found.
     @param     this    object pointer
     @param     key     key of entry to be deleted
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         bpt32_NodeDelete (
        BPT32_DATA      *this,
        BPT32_BLOCK     *pBlock,
        uint32_t        key
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32_NODE      *pNode = NULL;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (0 == pBlock->used) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif
        
        pNode = bpt32_NodeFind(pBlock, key, &i);
        
        if (pNode) {
            // Shift the entries beyond this one left if needed.
            if (i == (pBlock->used - 1))
                ;
            else {
                if (pBlock->used > 1) {
                    memmove(
                            bpt32_Index2Node(pBlock, i),
                            bpt32_Index2Node(pBlock, i+1),
                            ((pBlock->used - i)
                             * (sizeof(BPT32_NODE) + pBlock->actualSize))
                            );
                }
            }
            eRc = ERESULT_SUCCESS;
            --pBlock->used;
#ifdef XYZZY
            if ((0 == pBlock->used) && this->pBlockEmpty) {
                // Inserting data in 0th position (ie block key)
                eRc = this->pBlockIndexChanged(this->pBlockObject, this);
            }
            else {
                if ((0 == i) && this->pBlockIndexChanged) {
                    // Inserting data in 0th position (ie block key)
                    eRc = this->pBlockIndexChanged(this->pBlockObject, this);
                }
            }
#endif
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                 I n s e r t  N o d e
    //---------------------------------------------------------------
    
    ERESULT         bpt32_NodeInsert (
        BPT32_DATA      *this,
        BPT32_BLOCK     *pBlock,            // Block must contain max+1 nodes
        uint32_t        key,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        BPT32_NODE      *pNode = NULL;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (NULL == pBlock) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pBlock->used < (pBlock->max + 1))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_BUFFER_FULL;
        }
#endif
        
        pNode = bpt32_NodeFind(pBlock, key, &i);
        
        if (pNode && (pNode->key == key)) {
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        else {
            for (; i<pBlock->used; ++i) {
                pNode = bpt32_Index2Node(pBlock, i);
                if (key < pNode->key) {
                    pNode = NULL;
                    break;
                }
                pNode = NULL;
            }
            if (i == pBlock->used)
                ;
            else {
                // Shift records right to make room for new node.
                memmove(
                        bpt32_Index2Node(pBlock, i+1),
                        bpt32_Index2Node(pBlock, i),
                        ((pBlock->used - i)
                         * (sizeof(BPT32_NODE) + pBlock->actualSize))
                        );
            }
            pNode = bpt32_Index2Node(pBlock, i);
            if (pNode) {
                pNode->key = key;
                memmove(pNode->data, pData, this->dataSize);
                ++pBlock->used;
            }
            else {
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
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
        uint32_t        curNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_NULL(this->pHdr);
#endif
        
        eRc = bpt32_BlockSearch(this, this->pHdr->root, key, pData);
        if (!ERESULT_FAILED(eRc)) {
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        // Work Block should be pointed to the insertion point and
        // srchStk should contain a list of the blocks that had to
        // be read to get there.
        
        
        eRc = bpt32_NodeInsert(this, this->pBlock, key, pData);
        if (!ERESULT_FAILED(eRc)) {
            return ERESULT_SUCCESS;
        }
        
        // Is block full?
        if (this->pBlock->max == this->pBlock->used) {
            
        }
        
        // Empty Index - so add leaf root block.
        if (0 == this->pHdr->cRecords) {
            curNode = 2;
            bpt32_BlockInit(
                            this->pBlock,
                            OBJ_IDENT_BPT32LF,
                            this->pHdr->blockSize,
                            this->pHdr->dataSize,
                            curNode
            );
            
            eRc = rrds_RecordWrite((RRDS_DATA *)this, curNode, (void *)this->pBlock);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
            }
            this->pHdr->root = curNode;
            this->pHdr->dataHead = curNode;
            this->pHdr->dataTail = curNode;
            this->pHdr->cRecords = curNode;
        }
        // Search for key and add to block if possible
        else {
            curNode = this->pHdr->root;
            //eRc = bpt32_BlockSearchKey(this, curNode, key);
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

        eRc = rrds_Create((RRDS_DATA *)this, pPath);
        
        // Create a work buffer with one extra node.
        if (this->pBlock) {
            mem_Free(this->pBlock);
            //this->pBlock = NULL;
        }
        this->pBlock =  mem_Calloc(
                                  1,
                                   this->blockSize
                                   + sizeof(BPT32_NODE)
                                   + this->pHdr->actualSize
                        );
        if (NULL == this->pBlock) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Create an empty Leaf Block to be Root.
        index = 2;                  // Header is First Block.
        eRc =   bpt32_BlockInit(
                              this->pBlock,
                              OBJ_IDENT_BPT32LF,
                              this->pHdr->blockSize,
                              this->pHdr->dataSize,
                              index
                );
        eRc = rrds_RecordWrite((RRDS_DATA *)this, index, (void *)this->pBlock);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
        }
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
        if (this->pBlock) {
            mem_Free(this->pBlock);
            this->pBlock = NULL;
        }
        if (this->pSrchStk) {
            mem_Free(this->pSrchStk);
            this->pSrchStk = NULL;
            this->srchMax = 0;
            this->srchCur = 0;
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
        this->srchCur = 0;
        eRc = bpt32_BlockSearch(this, this->pHdr->root, key, pData);

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
        
        this->srchMax = 32;
        this->pSrchStk = mem_Calloc(this->srchMax, sizeof(uint32_t));
        if (NULL == this->pSrchStk) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
    #else
        if (!bpt32_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "bpt32::sizeof(BPT32_DATA) = %lu\n", sizeof(BPT32_DATA));
        fprintf(stderr, "bpt32::sizeof(BPT32_NODE) = %lu\n", sizeof(BPT32_NODE));
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
        
        this->pBlock = mem_Calloc(1, this->blockSize);
        if (NULL == this->pBlock) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
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

                    case 'I':
                        if (str_Compare("IndexBlockRequest", (char *)pStr) == 0) {
                            return bpt32_BlockRequestIndex;
                        }
                        break;
                        
                    case 'L':
                        if (str_Compare("LeafBlockRequest", (char *)pStr) == 0) {
                            return bpt32_BlockRequestLeaf;
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
                AStr_AppendCharRepeatA(pStr, indent+3, ' ');
                AStr_AppendA(pStr, "* * *  Header Record  * * *\n");
                AStr_AppendCharRepeatA(pStr, indent+3, ' ');
                eRc = AStr_AppendPrint(
                                       pStr,
                                       "blockSize = %d  dataSize = %d  actualSize = %d  "
                                       "cRecords = %d\n",
                                       this->pHdr->blockSize,
                                       this->pHdr->dataSize,
                                       this->pHdr->actualSize,
                                       this->pHdr->cRecords
                        );
                AStr_AppendCharRepeatA(pStr, indent+3, ' ');
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

        }
#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
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


