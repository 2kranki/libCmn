// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BPT32.c
 *  Generated 09/25/2021 10:01:15
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
#include        <BPT32_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            BPT32_task_body (
        void            *pData
    )
    {
        //BPT32_DATA  *this = pData;
        
    }
#endif



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
    //                            I O
    //---------------------------------------------------------------

    RRDS_DATA *     BPT32_getIO (
        BPT32_DATA      *this
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


    bool            BPT32_setIO (
        BPT32_DATA      *this,
        RRDS_DATA       *pValue
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
    //                            L R U
    //---------------------------------------------------------------

    LRU_DATA *      BPT32_getLRU (
        BPT32_DATA      *this
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

        return this->pLRU;
    }


    bool            BPT32_setLRU (
        BPT32_DATA      *this,
        LRU_DATA        *pValue
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
        if (this->pLRU) {
            obj_Release(this->pLRU);
        }
        this->pLRU = pValue;

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
     @param     this    object pointer
     @param     pOther  a pointer to another BPT32 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BPT32_Assign (
        BPT32_DATA       *this,
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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                B l o c k  F i n d  P a r e n t
    //---------------------------------------------------------------

    ERESULT         BPT32_BlockFindParent(
        BPT32_DATA      *this,
        uint32_t        lbn,
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          *pObj;
        uint32_t        iMax;
        uint32_t        i;
        uint32_t        lbnBlk;
        BPT32_BLK_VTBL  *pVtbl = NULL;

        TRC_OBJ(this, "bpt32_BlockFindParent lsn=%d\n", lbn);

        if (ppObj)
            *ppObj = OBJ_NIL;
        iMax = ObjArray_getSize(this->pSrchStk);
        for (i=iMax; i>0; --i) {
            pObj = ObjArray_Get(this->pSrchStk, i);
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
            lbnBlk = pVtbl->pGetLBN(pObj);
            if (lbn == lbnBlk) {
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



    //---------------------------------------------------------------
    //                  B l o c k  R e a d
    //---------------------------------------------------------------

    ERESULT         BPT32_BlockRead(
        BPT32_DATA      *this,
        uint32_t        lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
#ifdef NOT_IMPLEMENTED
        BPT32IDX_DATA   *pIndex = OBJ_NIL;
        BPT32LF_DATA    *pLeaf = OBJ_NIL;
#endif
        uint16_t        *pData;

        TRC_OBJ(this, "bpt32_BlockRead lsn=%d\n", lbn);

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

        pData = (uint16_t *)lru_FindBuffer(this->pLRU, lbn);
#ifdef NOT_IMPLEMENTED
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
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = bpt32idx_Verify(pIndex);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tIndex Block Verify Error!\n");
                    ASTR_DATA       *pStr = bpt32lf_ToDebugString(pLeaf, 4);
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
        else if (*pData == OBJ_IDENT_BPT32LF) {
            pLeaf = bpt32lf_New();
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
            eRc = bpt32lf_Setup(pLeaf, this->blockSize, this->dataSize, lsn, true);
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tLeaf Block Setup Error!\n");
                obj_Release(pLeaf);
                return eRc;
            }
            bpt32lf_setManager(pLeaf, (void *)this);
            bpt32lf_CopyFrom(pLeaf, (void *)pData);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = bpt32lf_Verify(pLeaf);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tLeaf Block Verify Error!\n");
                    ASTR_DATA       *pStr = bpt32lf_ToDebugString(pLeaf, 4);
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
#endif

        return eRc;
    }



    //---------------------------------------------------------------
    //                  B l o c k  R e q u e s t
    //---------------------------------------------------------------

    /*!
     @warning   This method must always conform to P_ERESULT_EXIT5.
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
        uint32_t        lbn = 0;            // Logical Block Number
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

            case BPT32_REQUEST_NEW_LBN:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Index Block %d\n", lbn);
                if (pParm3)
                    *((uint32_t *)pParm3) = lbn;
                break;

            case BPT32_REQUEST_NEW_INDEX:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Index Block %d\n", lbn);
#ifdef NOT_IMPLEMENTED
                pIndex =    BPT32Index_NewWithSizes(
                                             this->blockSize,
                                             this->keySize,
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
                                         BPT32Index_getIndex(pIndex),
                                         BPT32Index_getBlock(pIndex)
                        );
                if (pParm3)
                    *((void **)pParm3) = pIndex;
                else
                    obj_Release(pIndex);
                pIndex = NULL;
#endif
                break;

            case BPT32_REQUEST_NEW_LEAF:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Leaf Block %d\n", lbn);
                pLeaf = BPT32Leaf_NewWithSizes(
                                               this->blockSize,
                                               lbn,
                                               this->pHdr->keyLen,
                                               this->pHdr->keyOff,
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
                    eRc = ERESULT_DATA_MISSING;
                } else {
                    if (lbn && pBlock) {
                        eRc =   RRDS_RecordRead(
                                                this->pIO,
                                                lbn,
                                                pBlock
                                );
                    }
                    else
                        eRc = ERESULT_GENERAL_FAILURE;
                }
                break;

            case BPT32_REQUEST_SPLIT:
                TRC_OBJ(this, "\tSplit Block...\n");
                //FIXME: eRc = BPT32_BlockSplit(this, (OBJ_ID)pObj, pRet);
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
    ERESULT         bpt32_BlockSearchKey (
        BPT32_DATA      *this,
        uint32_t        lbn,
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
        TRC_OBJ(this, "bpt32_BlockSearchKey lsn=%d, key=%d\n", lbn, key);

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

#ifdef NOT_IMPLEMENTED
            if ( pObject) {
                if (obj_getType(pObject) == OBJ_IDENT_BPT32LF) {
                    eRc = bpt32lf_FindKey(pObject, key, pData);
                    if (ERESULT_FAILED(eRc)) {
                        TRC_OBJ(this, "\tLeaf block, key %d not found\n", key);
                    }
                    else {
                        pVtbl = (void *)obj_getVtbl((OBJ_ID)pObject);
                        this->lastLSN = pVtbl->pGetIndex(pObject);
                        this->lastKey = key;
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
#endif

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
    ERESULT         bpt32_BlockSplit(
        BPT32_DATA      *this,
        OBJ_ID          *pLeft,
        OBJ_ID          *pRight
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        //FIXME: BPT32IDX_DATA   *pIndex = OBJ_NIL;
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
#ifdef NOT_IMPLEMENTED
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
            eRc =   RRDS_RecordWrite(
                                     this->pIO,
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
#endif

        return eRc;
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
        BPT32_DATA     *this,
        BPT32_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
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

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
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
     @param     this    object pointer
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
        
#ifdef BPT32_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = BPT32_New( );
        if (pOther) {
            eRc = BPT32_Assign(this, pOther);
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

    void            BPT32_Dealloc (
        OBJ_ID          objId
    )
    {
        BPT32_DATA   *this = objId;
        //ERESULT         eRc;

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
        BPT32_setLRU(this, OBJ_NIL);

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
        BPT32      *pDeepCopy = BPT32_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPT32 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32_DATA *     BPT32_DeepCopy (
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
    ERESULT         BPT32_Disable (
        BPT32_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
        BPT32_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPT32_DATA *   BPT32_Init (
        BPT32_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPT32_DATA);
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
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of BPT32_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPT32);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BPT32_Vtbl);
#ifdef  BPT32_JSON_SUPPORT
        JsonIn_RegisterClass(BPT32_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!BPT32_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "BPT32::sizeof(BPT32_DATA) = %lu\n", 
                sizeof(BPT32_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPT32_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BPT32_IsEnabled (
        BPT32_DATA       *this
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

                    case 'P':
#ifdef  BPT32_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return BPT32_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return BPT32_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BPT32_ToDebugString;
                        }
#ifdef  BPT32_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return BPT32_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BPT32_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BPT32_ToDebugString)
                    return "ToDebugString";
#ifdef  BPT32_JSON_SUPPORT
                if (pData == BPT32_ToJson)
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
        ASTR_DATA      *pDesc = BPT32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
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
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
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
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    BPT32_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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


    
    
    
#ifdef  __cplusplus
}
#endif


