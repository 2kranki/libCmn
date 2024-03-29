// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BPT.c
 *  Generated 09/25/2021 10:01:15
 *
 * Notes:
 *  *   I started to implement Parent LBNs within the Index and Leaf
 *      blocks. The biggest problem with that is a block split on
 *      an index block may require lots of children to have their
 *      parent nodes updated. The current method is to have all the
 *      blocks from the root down to the current leaf node in a
 *      stack. That way, we can simply trace the stack backwards to
 *      find the parent.
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
#include        <BPT_internal.h>
#include        <BPT_Request.h>
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

    ERESULT         BPT_BlockFindParent(
        BPT_DATA      *this,
        uint32_t        lbn,
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          *pObj;
        uint32_t        iMax;
        uint32_t        i;
        uint32_t        index;
        BPT_BLK_VTBL  *pVtbl = NULL;

        TRC_OBJ(this, "BPT_BlockFindParent lbn=%d\n", lbn);

        if (ppObj)
            *ppObj = OBJ_NIL;
        iMax = ObjArray_getSize(this->pSrchStk);
        for (i=iMax; i>0; --i) {
            pObj = ObjArray_Get(this->pSrchStk, i);
            pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
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



    //---------------------------------------------------------------
    //               H e a d e r  R e a d / W r i t e
    //---------------------------------------------------------------

    /*
     Reading and Writing the file header is done independent of the
     main dataset processing. So that, it does not interfere with it.
     */

    ERESULT         BPT_HeaderRead(
        BPT_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        FILEIO_DATA     *pIO = OBJ_NIL;
        BPT_HEADER    *pHdr;
        uint32_t        readAmt = 0;

#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pHdr = mem_Malloc(sizeof(BPT_HEADER));
        if (NULL == pHdr) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        pIO = FileIO_New( );
        if (OBJ_NIL == pIO) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }

        eRc = FileIO_Open(pIO, pPath, false);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_OBJECT_CREATION;
        }


        eRc = FileIO_Read(pIO, (uint32_t)(sizeof(BPT_HEADER)), pHdr, &readAmt);
        if (ERESULT_OK(eRc) && (readAmt == sizeof(BPT_HEADER))) {
            this->blockSize = pHdr->blockSize;
            this->keyLen  = pHdr->keyLen;
            this->keyOff  = pHdr->keyOff;
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


    ERESULT         BPT_HeaderWrite(
        BPT_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        FILEIO_DATA     *pIO = OBJ_NIL;
        BPT_HEADER    hdr;
        uint32_t        readAmt = 0;

#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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

        eRc = FileIO_Open(pIO, pPath, false);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pIO);
            pIO = OBJ_NIL;
            return ERESULT_OBJECT_CREATION;
        }


        eRc = FileIO_Write(pIO, (uint32_t)(sizeof(BPT_HEADER)), this->pHdr);
        if (!ERESULT_FAILED(eRc) && (readAmt == sizeof(BPT_HEADER))) {
            this->blockSize = hdr.blockSize;
            //FIXME: this->dataSize  = hdr.dataSize;
        }

        FileIO_Close(pIO, false);
        obj_Release(pIO);
        pIO = OBJ_NIL;

        return eRc;
    }




    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPT_DATA *     BPT_Alloc (
        void
    )
    {
        BPT_DATA       *this;
        uint32_t        cbSize = sizeof(BPT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BPT_DATA *     BPT_New (
        void
    )
    {
        BPT_DATA      *this;
        
        this = BPT_Alloc( );
        if (this) {
            this = BPT_Init(this);
        } 
        return this;
    }


    BPT_DATA *    BPT_NewWithSizes (
        uint16_t        blockSize,
        uint16_t        keyLen,
        uint16_t        keyOff,
        uint16_t        cLRU,
        uint16_t        cHash
    )
    {
        ERESULT         eRc;
        BPT_DATA      *this;

        this = BPT_New( );
        if (this) {
            eRc = BPT_SetupSizes(this, blockSize, keyLen, keyOff, cLRU, cHash);
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
    //                            I O
    //---------------------------------------------------------------

    RRDS_DATA *     BPT_getIO (
        BPT_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pIO;
    }


    bool            BPT_setIO (
        BPT_DATA      *this,
        RRDS_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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

    LRU_DATA *      BPT_getLRU (
        BPT_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLRU;
    }


    bool            BPT_setLRU (
        BPT_DATA      *this,
        LRU_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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
    //                           P a t h
    //---------------------------------------------------------------

    PATH_DATA *     BPT_getPath (
        BPT_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPath;
    }


    bool            BPT_setPath (
        BPT_DATA      *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BPT_getPriority (
        BPT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BPT_setPriority (
        BPT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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
    
    uint32_t        BPT_getSize (
        BPT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BPT_getSuperVtbl (
        BPT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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
    ERESULT         BPT_Add (
        BPT_DATA      *this,
        uint16_t        size,
        void            *pRecord
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        //uint32_t        curNode;
        OBJ_ID          pObject = OBJ_NIL;


        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        BREAK_NULL(this->pHdr);
        if ((size < this->keyLen) || (NULL == pRecord)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        TRC_OBJ(this, "BPT_Add  key=%.*s\n", this->keyLen, (pRecord + this->keyOff));
        eRc = ObjArray_DeleteAll(this->pSrchStk);
        eRc = BPT_BlockSearchByKey(this, 0, (pRecord + this->keyOff));
        if (ERESULT_OK(eRc)) {
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        // Top of Search Stack should contain a Leaf block
        // that the key should be inserted into.

        pObject = ObjArray_Top(this->pSrchStk);
        if (OBJ_IDENT_BPTLEAF == obj_getType(pObject)) {
            eRc = BPTLeaf_Add(pObject, size, pRecord);
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
        ERESULT eRc = BPT_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BPT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BPT_Assign (
        BPT_DATA       *this,
        BPT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BPT_Validate(pOther)) {
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
    //                  B l o c k  R e a d
    //---------------------------------------------------------------

    /*!
     Read a block from the dataset, determine it's type and create an
     index or leaf object for it as appropriate, copying the block
     into the objeect.
     @param     this    object pointer
     @param     lbn     locigal record number to read
     @param     ppObj   pointer to where the object is to be returned
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT_BlockRead(
        BPT_DATA      *this,
        uint32_t        lbn,                // Logical Block Number
        OBJ_ID          *ppObj
    )
    {
        ERESULT         eRc = ERESULT_OUT_OF_MEMORY;
        BPTINDEX_DATA *pIndex = OBJ_NIL;
        BPTLEAF_DATA  *pLeaf = OBJ_NIL;
        uint8_t         *pData;

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

        pData = (uint8_t *)lru_FindBuffer(this->pLRU, lbn);
        if (*(pData+this->blockSize-1) == 'I') {
            pIndex = BPTIndex_New();
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
            eRc =   BPTIndex_Setup(
                                     pIndex,
                                     this->blockSize,
                                     lbn,
                                     this->keyLen,
                                     this->keyOff
                    );
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tIndex Block Setup Error!\n");
                obj_Release(pIndex);
                return eRc;
            }
            BPTIndex_setManager(pIndex, (void *)this);
            memmove(BPTIndex_getBlock(pIndex), pData, this->blockSize);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = BPTIndex_Verify(pIndex);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tIndex Block Verify Error!\n");
                    ASTR_DATA       *pStr = BPTIndex_ToDebugString(pIndex, 4);
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
        else if (*(pData+this->blockSize-1) == 'L') {
            pLeaf = BPTLeaf_New();
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
            eRc =   BPTLeaf_Setup(
                                    pLeaf,
                                    this->blockSize,
                                    lbn,
                                    this->keyLen,
                                    this->keyOff
                    );
            if (ERESULT_FAILED(eRc)) {
                TRC_OBJ(this, "\tLeaf Block Setup Error!\n");
                obj_Release(pLeaf);
                return eRc;
            }
            BPTLeaf_setManager(pLeaf, (void *)this);
            memmove(BPTLeaf_getBlock(pLeaf), pData, this->blockSize);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                eRc = BPTLeaf_Verify(pLeaf);
                if (ERESULT_FAILED(eRc)) {
                    TRC_OBJ(this, "\tLeaf Block Verify Error!\n");
                    ASTR_DATA       *pStr = BPTLeaf_ToDebugString(pLeaf, 4);
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
    //                  B l o c k  R e q u e s t
    //---------------------------------------------------------------

    /*!
     @warning   This method must always conform to P_ERESULT_EXIT5.
     */
    ERESULT         BPT_BlockRequest(
        BPT_DATA      *this,
        uint32_t        request,
        OBJ_ID          pObj,
        void            *pParm1,
        void            *pParm2,
        void            *pParm3
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPTINDEX_DATA *pIndex = OBJ_NIL;
        BPTLEAF_DATA  *pLeaf = OBJ_NIL;
        uint32_t        lbn = 0;            // Logical Block Number
        void            *pBlock = NULL;
        BPT_BLK_VTBL  *pVtbl = NULL;

#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        TRC_OBJ(this, "BPT_BlockRequest req=%d\n", request);
#endif

        switch (request) {

            case BPT_REQUEST_NEW_LBN:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Index Block %d\n", lbn);
                if (pParm3)
                    *((uint32_t *)pParm3) = lbn;
                break;

            case BPT_REQUEST_NEW_INDEX:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Index Block %d\n", lbn);
                pIndex =    BPTIndex_NewWithSizes(
                                            this->blockSize,
                                            lbn,
                                            this->keyLen,
                                            this->keyOff,
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
                                         BPTIndex_getLBN(pIndex),
                                         BPTIndex_getBlock(pIndex)
                        );
                if (pParm3)
                    *((void **)pParm3) = pIndex;
                else
                    obj_Release(pIndex);
                pIndex = NULL;
                break;

            case BPT_REQUEST_NEW_LEAF:
                if (NULL == pParm3) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                lbn = ++this->pHdr->cRecords;
                TRC_OBJ(this, "\tNew Leaf Block %d\n", lbn);
                pLeaf = BPTLeaf_NewWithSizes(
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
                                         BPTLeaf_getLBN(pLeaf),
                                         BPTLeaf_getBlock(pLeaf)
                        );
                if (pParm3)
                    *((void **)pParm3) = pLeaf;
                else
                    obj_Release(pLeaf);
                pLeaf = NULL;
                break;

            case BPT_REQUEST_PARENT:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
                lbn = pVtbl->pGetLBN(pObj);
                TRC_OBJ(this, "\tFind Parent for %d...\n", lbn);
                eRc = BPT_BlockFindParent(this, lbn, pParm3);
                break;

            case BPT_REQUEST_READ:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
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

            case BPT_REQUEST_SPLIT:
                TRC_OBJ(this, "\tSplit Block...\n");
                //FIXME: eRc = BPT_BlockSplit(this, (OBJ_ID)pObj, pRet);
                break;

            case BPT_REQUEST_SET_TAIL:
                TRC_OBJ(this, "\tSet new data tail...\n");
                if (OBJ_IDENT_BPTLEAF == obj_getType(pObj)) {
                    this->pHdr->dataTail = BPTLeaf_getLBN((BPTLEAF_DATA *)pObj);
                    eRc = ERESULT_SUCCESS;
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
                break;

            case BPT_REQUEST_WRITE:
                if (NULL == pObj) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_PARAMETER;
                }
                pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
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

    ERESULT         BPT_BlockSearchByKey (
        BPT_DATA      *this,
        uint32_t        lbn,
        uint8_t         *pKey
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          pObject = OBJ_NIL;
        bool            fMore = true;
        bool            fRead = false;
        uint16_t        rcdNum;
        uint16_t        insertRcd;

        // Do initialization.
        TRC_OBJ(this, "BPT_BlockSearchByKey lsn=%d, key=%s\n", lbn, pKey);

        if (0 == lbn) {         // Use the root.
            pObject = this->pRoot;
            TRC_OBJ(this, "\tUsing Root for first block\n");
        }

        while (fMore) {
            fRead = false;
            if (pObject)
                ;
            else {
                // Read the next block into the common buffer.
                TRC_OBJ(this, "\tReading %d\n", lbn);
                eRc = BPT_BlockRead(this, lbn, &pObject);
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
            if (fRead) {
                obj_Release(pObject);       // objArray has retained it.
            }

            if ( pObject) {
                if (obj_getType(pObject) == OBJ_IDENT_BPTLEAF) {
                    rcdNum = BPTLeaf_FindByKey(pObject, pKey, &insertRcd);
                    if (rcdNum) {
                        TRC_OBJ(this, "\tLeaf block, key %s found\n", pKey);
                        this->lastLBN = BPTLeaf_getLBN(pObject);
                        this->lastRcd = rcdNum;
                        eRc = ERESULT_SUCCESS;
                    }
                    else {
                        TRC_OBJ(this, "\tLeaf block, key %s not found\n", pKey);
                        this->lastLBN = BPTLeaf_getLBN(pObject);
                        this->lastRcd = insertRcd;
                    }
                    return eRc;
                }
                else if (obj_getType(pObject) == OBJ_IDENT_BPTINDEX) {
                    rcdNum = BPTIndex_FindByKey(pObject, pKey, &insertRcd);
                    if (rcdNum) {
                        TRC_OBJ(this, "\tIndex block, key %s not found\n", pKey);
                       return eRc;
                    }
                    TRC_OBJ(
                            this,
                            "\tIndex block, key %d found, index=%d\n",
                            pKey,
                            lbn
                    );
                }
                else {
                    DEBUG_BREAK();
                    return ERESULT_GENERAL_FAILURE;
                }
            }

            //FIXME: lbn = nodeIndex;
            pObject = OBJ_NIL;
        }

        // Return to caller.
        TRC_OBJ(this, "\tkey %d not found, returning\n", pKey);
        return ERESULT_DATA_NOT_FOUND;
    }



    //---------------------------------------------------------------
    //                       C l o s e
    //---------------------------------------------------------------

    ERESULT         BPT_Close (
        BPT_DATA      *this,
        bool            fDelete
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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

        eRc = BPT_HeaderWrite(this, this->pPath);
        BPT_setPath(this, OBJ_NIL);
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             BPT_Compare (
        BPT_DATA     *this,
        BPT_DATA     *pOther
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
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!BPT_Validate(pOther)) {
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
        BPT      *pCopy = BPT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT_DATA *     BPT_Copy (
        BPT_DATA       *this
    )
    {
        BPT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef BPT_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = BPT_New( );
        if (pOther) {
            eRc = BPT_Assign(this, pOther);
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
    //                       C r e a t e
    //---------------------------------------------------------------

    ERESULT         BPT_Create (
        BPT_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        uint32_t        lbn;
        BPTLEAF_DATA  *pLeaf = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == this->pIO) {
            eRc = BPT_SetupRRDS(this);
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

        if (this->pHdr) {
            mem_Free(this->pHdr);
            //this->pHdr = NULL;
        }
        this->pHdr = mem_Calloc(1, sizeof(BPT_HEADER));
        if (NULL == this->pHdr) {
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pHdr->blockSize = this->blockSize;
        this->pHdr->keyLen = this->keyLen;
        this->pHdr->keyOff = this->keyOff;
        this->pHdr->cRecords = 1;                   // Allow for Header

        eRc = RRDS_Create(this->pIO, pPath, false);

        eRc =   BPT_BlockRequest(
                                 this,
                                 BPT_REQUEST_NEW_LEAF,
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
        lbn = BPTLeaf_getLBN(pLeaf);

        this->pHdr->root     = lbn;
        this->pHdr->dataHead = lbn;
        this->pHdr->dataTail = lbn;
        this->pHdr->cRecords = lbn;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            BPT_Dealloc (
        OBJ_ID          objId
    )
    {
        BPT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BPT_setIO(this, OBJ_NIL);
        BPT_setLRU(this, OBJ_NIL);
        BPT_setPath(this, OBJ_NIL);

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
        BPT      *pDeepCopy = BPT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT_DATA *     BPT_DeepCopy (
        BPT_DATA       *this
    )
    {
        BPT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BPT_New( );
        if (pOther) {
            eRc = BPT_Assign(this, pOther);
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
    ERESULT         BPT_Disable (
        BPT_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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
    ERESULT         BPT_Enable (
        BPT_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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
    //                          F i n d
    //---------------------------------------------------------------

    ERESULT         BPT_Find (
        BPT_DATA      *this,
        uint8_t         *pKey,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pKey) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
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
        //FIXME: eRc = BPT_BlockSearchKey(this, this->pHdr->root, key, pData);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          F i r s t
    //---------------------------------------------------------------

    ERESULT         BPT_First (
        BPT_DATA        *this,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        OBJ_ID          pObj = OBJ_NIL;
        //uint32_t        key;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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
        this->lastLBN = this->pHdr->dataHead;

        if (this->lastLBN) {
            eRc = BPT_BlockRead(this, this->lastLBN, &pObj);
            if (ERESULT_FAILED(eRc) || (OBJ_NIL == pObj)) {
                return ERESULT_READ_ERROR;
            }
            //FIXME: eRc = BPTLeaf_GetNum(pObj, 1, &key, pData);
            obj_Release(pObj);
            if (ERESULT_OK(eRc)) {
                this->lastRcd = 1;
                return ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        return ERESULT_EOF_ERROR;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPT_DATA *   BPT_Init (
        BPT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPT_DATA);
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
        // in the OBJ_INFO at the end of BPT_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPT);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BPT_Vtbl);
#ifdef  BPT_JSON_SUPPORT
        JsonIn_RegisterClass(BPT_Class());
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
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "BPT::sizeof(BPT_DATA) = %lu\n", 
                sizeof(BPT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BPT_IsEnabled (
        BPT_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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

    ERESULT         BPT_Next (
        BPT_DATA      *this,
        uint8_t         *pKey,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    )
    {
        //ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        //OBJ_ID          pObj = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pKey) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == this->pHdr) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (0 == this->pHdr->root) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (0 == this->lastLBN) {
            DEBUG_BREAK();
            return ERESULT_EOF_ERROR;
        }
#endif

        //TODO: A leaf block split in the middle of this might mess
        //      up our tracking.  We might need to do a BlockSearchKey()
        //      on key to reset.  Deletion needs to check the saved key
        //      and update it as well.

        // Search for the key in the last block.
#ifdef XYZZY
        eRc = BPT_BlockRead(this, this->lastLBN, &pObj);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pObj)) {
            return ERESULT_READ_ERROR;
        }
        eRc = BPTLeaf_FindByNum(pObj, this->lastKey, NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pObj);
            return ERESULT_GENERAL_FAILURE;
        }
        eRc = BPTLeaf_Next(pObj, &key, pData);
        if (!ERESULT_FAILED(eRc)) {
            this->lastLBN++;
            obj_Release(pObj);
            return ERESULT_SUCCESS;
        }
        this->lastLBN = bpt32lf_getNext(pObj);
        obj_Release(pObj);

        if (this->lastLBN) {
            eRc = bpt32_BlockRead(this, this->lastLBN, &pObj);
            if (ERESULT_FAILED(eRc) || (OBJ_NIL == pObj)) {
                return ERESULT_READ_ERROR;
            }
            eRc = BPTLeaf_Get(pObj, 1, &key, pData);
            obj_Release(pObj);
            if (!ERESULT_FAILED(eRc)) {
                this->lastKey = key;
                if (pKey)
                    *pKey = key;
                return ERESULT_SUCCESS;
            }
        }
#endif

        // Return to caller.
        return ERESULT_EOF_ERROR;
    }



    //---------------------------------------------------------------
    //                       O p e n
    //---------------------------------------------------------------

    ERESULT         BPT_Open (
        BPT_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == this->pIO) {
            eRc = BPT_SetupRRDS(this);
            if (ERESULT_FAILED(eRc))
                return eRc;
        }

        this->pPath = Path_Copy(pPath);
        if (OBJ_NIL == this->pPath) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // Get block and data sizes from header.
        eRc = BPT_HeaderRead(this, pPath);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Setup sizes from our merged sizes.
        eRc =   RRDS_SetupSizes(
                                this->pIO,
                                this->blockSize,
                                RRDS_RCD_TRM_NONE,
                                this->cLRU,
                                this->cHash
                );

        eRc =   RRDS_Open(this->pIO, pPath, false);

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
        void        *pMethod = BPT_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BPT", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BPT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BPT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(BPT_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BPT_Class();
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
                            return BPT_BlockRequest;
                        }
                        break;

                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return BPT_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BPT_Enable;
                        }
                        break;

                    case 'P':
#ifdef  BPT_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return BPT_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return BPT_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BPT_ToDebugString;
                        }
#ifdef  BPT_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return BPT_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BPT_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BPT_ToDebugString)
                    return "ToDebugString";
#ifdef  BPT_JSON_SUPPORT
                if (pData == BPT_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------

    ERESULT         BPT_SetupRRDS(
        BPT_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
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


    ERESULT         BPT_SetupSizes(
        BPT_DATA      *this,
        uint32_t        blockSize,
        uint16_t        keyLen,
        uint16_t        keyOff,
        uint16_t        cLRU,
        uint16_t        cHash
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((blockSize > 0) && (blockSize > sizeof(BPT_HEADER)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((keyLen > 0) && (keyLen < 256))
            ;
        else {
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
        this->keyLen = keyLen;
        this->keyOff = keyOff;
        this->cLRU = cLRU;
        this->cHash = cHash;

        // Return to caller.
        return eRc;
    }



    //----------------------------------------------------------
    //                       S p l i t
    //----------------------------------------------------------

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
    ERESULT         BPT_BlockSplit(
        BPT_DATA      *this,
        OBJ_ID          *pLeft,
        OBJ_ID          *pRight
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        BPTINDEX_DATA *pIndex = OBJ_NIL;
        OBJ_ID          pObj;
        uint32_t        key = 0;
        uint32_t        index = 0;
        uint32_t        lbn = 0;
        BPT_BLK_VTBL  *pVtblL = NULL;
        BPT_BLK_VTBL  *pVtblR = NULL;

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
        pVtblL = (BPT_BLK_VTBL *)obj_getVtbl(pLeft);
        pVtblR = (BPT_BLK_VTBL *)obj_getVtbl(pRight);
        TRC_OBJ(
                this,
                "bpt32_BlockSplit Left: type=%d lsn=%d, Right: type=%d lsn=%d\n",
                obj_getType(pLeft),
                pVtblR->pGetLBN(pLeft),
                obj_getType(pRight),
                pVtblR->pGetLBN(pRight)
        );

        // We are splitting the Root!
        if (this->pRoot == pLeft) {
            TRC_OBJ(this, "\tSplitting the root...\n");
            eRc =   BPT_BlockRequest(
                                     this,
                                     BPT_REQUEST_NEW_INDEX,
                                     OBJ_NIL,
                                     NULL,
                                     NULL,
                                     &pIndex
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
            BPTIndex_setP0(pIndex, pVtblL->pGetLBN(pLeft));
            //FIXME: eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetLBN(pRight);
            //FIXME: BPTIndex_Add(pIndex, key, &index, NULL);
            // Note - No split should occur here.

            // Write the new block to the file.
            eRc =   RRDS_RecordWrite(
                                     this->pIO,
                                     BPTIndex_getLBN(pIndex),
                                     BPTIndex_getBlock(pIndex)
                    );
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }

            // Make the new index block the root.
            obj_Release(this->pRoot);
            this->pRoot = pIndex;
            this->pHdr->root = BPTIndex_getLBN(pIndex);
            fprintf(stderr, "\tAdded new Root Index Block, %d\n", BPTIndex_getLBN(pIndex));
        }
        // We need to adjust index in parent index block for new block added
        else {
            TRC_OBJ(this, "\tAdding key to the parent index...\n");
            lbn = pVtblL->pGetLBN(pLeft);
            eRc = BPT_BlockFindParent(this, lbn, &pObj);
            if (pObj && (OBJ_IDENT_BPTINDEX == obj_getType(pObj)))
                ;
            else {
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
            }
            //FIXME: eRc = pVtblR->pGet(pRight, 1, &key, NULL);
            index = pVtblR->pGetLBN(pRight);
            //FIXME: eRc = BPTIndex_Insert(pObj, key, &index, NULL);
            TRC_OBJ(
                    this,
                    "\tAdded key %d index %d to the index %d\n",
                    key,
                    index,
                    BPTIndex_getLBN(pObj)
            );
        }

        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT_ToDebugString (
        BPT_DATA      *this,
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
        if (!BPT_Validate(this)) {
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
                    BPT_getSize(this),
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
    bool            BPT_Validate (
        BPT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BPT))
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


        if (!(obj_getSize(this) >= sizeof(BPT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


