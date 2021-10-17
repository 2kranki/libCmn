// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BPTIndex.c
 *  Generated 09/25/2021 10:00:36
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
#include        <BPTIndex_internal.h>
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

    //---------------------------------------------------------------
    //                      F i n d
    //---------------------------------------------------------------

    uint16_t        BPTIndex_FindByKey (
        BPTINDEX_DATA *this,
        void            *pKey,
        uint16_t        *pInsert
    )
    {
        //ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        int             iRc;
        uint32_t        i = 0;
        uint32_t        iMax;
        uint16_t        keyLen;
        int             high = 0;
        int             low = 0;
        int             mid = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pInsert)
            *pInsert = 0;
        keyLen = BPTIndex_getKeyLen(this);

        iMax = BPTIndex_getNumRecords(this);
        if (iMax < 10) {            // *** Sequential Search ***
            for (i=0; i<iMax; i++) {
                BPTINDEX_NODE *pRcd = BlkdRcds16_DataAddr((BLKDRCDS16_DATA *)this, i+1);
                if (pRcd) {
                    iRc =   memcmp(
                                   pKey,
                                   pRcd->key,
                                   keyLen
                            );
                    if (0 == iRc) {
                        return i+1;
                        break;
                    }
                    if (iRc < 0)
                        break;
                }
            }
        } else {                    // *** Binary Search ***
            // Do a binary search.
            high = iMax - 1;
            while (low < high) {
                mid = (high + low) / 2;
                i = mid + 1;
                BPTINDEX_NODE *pRcd = BlkdRcds16_DataAddr(
                                                            (BLKDRCDS16_DATA *)this,
                                                            mid+1
                                        );
                if (pRcd) {
                    iRc =   memcmp(
                                   pKey,
                                   pRcd->key,
                                   keyLen
                            );
                    if (iRc < 0)
                        high = mid;
                    else if (iRc == 0) {
                        return i;
                    }
                    else
                        low = mid + 1;
                } else {                // *** Record Not Found ***
                    // Warning: This will cause an infinitte loop. We need an
                    // interrupt here.  On the other hand, this should never
                    // happen!
                }
            }
            if( high == low ) {
                BPTINDEX_NODE *pRcd = BlkdRcds16_DataAddr(
                                                            (BLKDRCDS16_DATA *)this,
                                                            low+1
                                        );
                i = low;
                iRc =   memcmp(
                               pKey,
                               pRcd->key,
                               keyLen
                        );
                if (iRc == 0)
                    return i+1;
                else if (iRc > 0)
                    ++i;
            }
        }

        // Return to caller.
        if (pInsert)
            *pInsert = i;
        return 0;
    }




    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPTINDEX_DATA *     BPTIndex_Alloc (
        void
    )
    {
        BPTINDEX_DATA       *this;
        uint32_t        cbSize = sizeof(BPTINDEX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BPTINDEX_DATA *     BPTIndex_New (
        void
    )
    {
        BPTINDEX_DATA       *this;
        
        this = BPTIndex_Alloc( );
        if (this) {
            this = BPTIndex_Init(this);
        } 
        return this;
    }


    BPTINDEX_DATA * BPTIndex_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff,
        OBJ_ID          pMgr
    )
    {
        ERESULT         eRc;
        BPTINDEX_DATA *this = OBJ_NIL;

        if (keyLen) {
            this = BPTIndex_New( );
            if (this) {
                eRc = BPTIndex_Setup(this, blockSize, lbn, keyLen, keyOff);
                if (ERESULT_OK(eRc)) {
                    BPTIndex_setManager(this, pMgr);
                } else {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          B l o c k
    //---------------------------------------------------------------

    uint8_t *       BPTIndex_getBlock (
        BPTINDEX_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return BlkdRcds16_getData((BLKDRCDS16_DATA *)this);
    }



    //---------------------------------------------------------------
    //                        K e y  L e n g t h
    //---------------------------------------------------------------

    uint16_t        BPTIndex_getKeyLen (
        BPTINDEX_DATA *this
    )
    {
        BPTINDEX_RSVD *pRsvd;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        return pRsvd->keyLen;
    }


    bool            BPTIndex_setKeyLen (
        BPTINDEX_DATA *this,
        uint16_t        value
    )
    {
        BPTINDEX_RSVD *pRsvd;

#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        pRsvd->keyLen = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        K e y  O f f s e t
    //---------------------------------------------------------------

    uint16_t        BPTIndex_getKeyOff (
        BPTINDEX_DATA *this
    )
    {
        BPTINDEX_RSVD *pRsvd;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        return pRsvd->keyOff;
    }


    bool            BPTIndex_setKeyOff (
        BPTINDEX_DATA *this,
        uint16_t        value
    )
    {
        BPTINDEX_RSVD *pRsvd;

#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        pRsvd->keyOff = value;

        return true;
    }



    //---------------------------------------------------------------
    //             L o g i c a l  B l o c k  N u m b e r
    //---------------------------------------------------------------

    uint32_t        BPTIndex_getLBN (
        BPTINDEX_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->lbn;
    }


    bool            BPTIndex_setLBN (
        BPTINDEX_DATA *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->lbn = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      M a n a g e r
    //---------------------------------------------------------------

    bool            BPTIndex_setManager(
        BPTINDEX_DATA  *this,
        OBJ_ID           *pMgr          // Block Manager
    )
    {
        OBJ_IUNKNOWN    *pVtbl;

#ifdef NDEBUG
#else
        if( !BPTIndex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pMgr = pMgr;
        if (pMgr) {
            pVtbl = obj_getVtbl(pMgr);
            this->pReq =    pVtbl->pQueryInfo(
                                            pMgr,
                                            OBJ_QUERYINFO_TYPE_METHOD,
                                            "BlockRequest"
                            );
            if (NULL == this->pReq) {
                this->pMgr = OBJ_NIL;
                return false;
            }
        }
        else
            this->pReq = NULL;

        return true;
    }



    //---------------------------------------------------------------
    //               N u m b e r  O f  R e c o r d s
    //---------------------------------------------------------------

    uint16_t        BPTIndex_getNumRecords (
        BPTINDEX_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return BlkdRcds16_getNumRecords((BLKDRCDS16_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          P 0
    //---------------------------------------------------------------

    uint32_t        BPTIndex_getP0 (
        BPTINDEX_DATA *this
    )
    {
        BPTINDEX_RSVD *pRsvd;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        return pRsvd->p0;
    }


    bool            BPTIndex_setP0 (
        BPTINDEX_DATA *this,
        uint32_t        value
    )
    {
        BPTINDEX_RSVD *pRsvd;

#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        pRsvd->p0 = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BPTIndex_getPriority (
        BPTINDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BPTIndex_setPriority (
        BPTINDEX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
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
    
    uint32_t        BPTIndex_getSize (
        BPTINDEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * BPTIndex_getStr (
        BPTINDEX_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        BPTIndex_setStr (
        BPTINDEX_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BPTIndex_getSuperVtbl (
        BPTINDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
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
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         BPTIndex_Add (
        BPTINDEX_DATA *this,
        uint32_t        lbn,
        void            *pKey
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        int             iRc;
        uint32_t        i = 0;
        uint32_t        iMax;
        uint8_t         rcd[sizeof(uint32_t)+256];  // Maximum Sized Record
        BPTINDEX_NODE *pNode = (BPTINDEX_NODE *)rcd;
        uint16_t        nodeLen;
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pKey) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Search the keys already in the block.
        iMax = BlkdRcds16_getNumRecords((BLKDRCDS16_DATA *)this);
        if (iMax) {
            for (i=0; i<iMax; i++) {
                BPTINDEX_NODE *pRcd = BlkdRcds16_DataAddr((BLKDRCDS16_DATA *)this, i+1);
                if (pRcd) {
                    iRc =   memcmp(
                                   pKey,
                                   pRcd->key,
                                   BPTIndex_getKeyLen(this)
                            );
                    if (0 == iRc) {
                        return ERESULT_DATA_ALREADY_EXISTS;
                    }
                    if (iRc < 0)
                        break;
                }
            }
        }
        // i will be insert point

        // Build the record and add it.
        pNode->lbn = lbn;
        memmove(pNode->key, pKey, BPTIndex_getKeyLen(this));
        nodeLen = sizeof(BPTINDEX_NODE) + BPTIndex_getKeyLen(this);
        eRc = BlkdRcds16_RecordInsert((BLKDRCDS16_DATA *)this, i, nodeLen, pNode);

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
        ERESULT eRc = BPTIndex_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BPTINDEX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BPTIndex_Assign (
        BPTINDEX_DATA       *this,
        BPTINDEX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BPTIndex_Validate(pOther)) {
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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             BPTIndex_Compare (
        BPTINDEX_DATA     *this,
        BPTINDEX_DATA     *pOther
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
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!BPTIndex_Validate(pOther)) {
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
        BPTIndex      *pCopy = BPTIndex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPTINDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPTINDEX_DATA *     BPTIndex_Copy (
        BPTINDEX_DATA       *this
    )
    {
        BPTINDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef BPTINDEX_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = BPTIndex_New( );
        if (pOther) {
            eRc = BPTIndex_Assign(this, pOther);
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

    void            BPTIndex_Dealloc (
        OBJ_ID          objId
    )
    {
        BPTINDEX_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPTINDEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BPTIndex_setStr(this, OBJ_NIL);

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
        BPTIndex      *pDeepCopy = BPTIndex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPTINDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPTINDEX_DATA *     BPTIndex_DeepCopy (
        BPTINDEX_DATA       *this
    )
    {
        BPTINDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BPTIndex_New( );
        if (pOther) {
            eRc = BPTIndex_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------

    ERESULT         BPTIndex_Delete (
        BPTINDEX_DATA *this,
        void            *pKey
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        int             iRc;
        uint32_t        i;
        uint32_t        iMax;
        uint16_t        keyLen;
        BPTINDEX_NODE *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pKey) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        keyLen = BPTIndex_getKeyLen(this);

        iMax = BPTIndex_getNumRecords(this);
        for (i=0; i<iMax; i++) {
            pNode = BlkdRcds16_DataAddr((BLKDRCDS16_DATA *)this, i+1);
            if (pNode) {
                iRc =   memcmp(
                               pKey,
                               pNode->key,
                               keyLen
                        );
                if (0 == iRc) {
                    eRc = BlkdRcds16_RecordDelete((BLKDRCDS16_DATA *)this, i+1);
                    break;
                }
                if (iRc < 0)
                    break;
            }
        }

        // Return to caller.
        return eRc;
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
    ERESULT         BPTIndex_Disable (
        BPTINDEX_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
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
    ERESULT         BPTIndex_Enable (
        BPTINDEX_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
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
    //                          F l u s h
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         BPTIndex_Flush (
        BPTINDEX_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_INVALID_REQUEST;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->lbn && this->pMgr)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_REQUEST;
        }
#endif

        if (this->pMgr && this->pReq) {
            eRc =   this->pReq(
                             this->pMgr,
                             BPT_REQUEST_WRITE,
                             this,
                             NULL,
                             NULL,
                             NULL
                    );
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      F o r  E a c h
    //---------------------------------------------------------------

    ERESULT         BPTIndex_ForEach (
        BPTINDEX_DATA *this,
        P_BOOL_EXIT4A   pScan,              // Return false to stop scan
        OBJ_ID          pObj,               // Used as first parameter of scan method
        //                                  // second parameter is record length
        //                                  // third parameter is recard address
        void            *pArg4              // Used as fourth parameter of scan method
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = BlkdRcds16_ForEach((BLKDRCDS16_DATA *)this, pScan, pObj, pArg4);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                              G e t
    //---------------------------------------------------------------

    ERESULT         BPTIndex_Get (
        BPTINDEX_DATA *this,
        void            *pKey,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        int             iRc;
        uint32_t        i = 0;
        uint32_t        iMax;
        uint32_t        size;
        uint16_t        keyLen;
        BPTINDEX_NODE *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pKey) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Search the keys in the block.
        keyLen = BPTIndex_getKeyLen(this);
        iMax = BlkdRcds16_getNumRecords((BLKDRCDS16_DATA *)this);
        if (iMax) {
            for (i=0; i<iMax; i++) {
                pNode = BlkdRcds16_DataAddr((BLKDRCDS16_DATA *)this, i+1);
                if (pNode) {
                    iRc =   memcmp(
                                   pKey,
                                   pNode->key,
                                   keyLen
                            );
                    if (0 == iRc) {
                        size = keyLen + sizeof(BPTINDEX_NODE);
                        if (size > cData)
                            size = cData;
                        if (pData) {
                            memmove(pData, pNode, size);
                        }
                        if (pUsed) {
                            *pUsed = size;
                        }
                        return ERESULT_SUCCESS;
                    }
                    if (iRc < 0)
                        break;
                }
            }
        }


        // Return to caller.
        return eRc;
    }


    BPTINDEX_NODE * BPTIndex_GetNum (
        BPTINDEX_DATA *this,
        uint32_t        index,          // Relative to 1
        uint16_t        *pLen
    )
    {
        ERESULT         eRc;
        uint16_t        size;
        uint8_t         *pData = NULL;
        uint16_t        used = 0;

        // Do initialization.
        if (pLen)
            *pLen = 0;
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
        if ((0 == index) || !((index - 1) < BPTIndex_getNumRecords(this))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return NULL;
        }
#endif

        size = BlkdRcds16_RecordSize((BLKDRCDS16_DATA *)this, index);
        pData = mem_Malloc(size+1);
        if (pData) {
            eRc =   BlkdRcds16_RecordGet(
                                         (BLKDRCDS16_DATA *)this,
                                         index,
                                         size+1,
                                         pData,
                                         &used
                    );
            if (ERESULT_FAILED(eRc)) {
                mem_Free(pData);
                pData = NULL;
            } else {
                *(pData+size) = '\0';
            }
        }

        // Return to caller.
        if (pLen) {
            *pLen = size;
        }
        return (BPTINDEX_NODE *)pData;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPTINDEX_DATA *   BPTIndex_Init (
        BPTINDEX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPTINDEX_DATA);
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

        this = (OBJ_ID)BlkdRcds16_Init((BLKDRCDS16_DATA *)this); // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of BPTIndex_object.c
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPTINDEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BPTIndex_Vtbl);
#ifdef  BPTINDEX_JSON_SUPPORT
        JsonIn_RegisterClass(BPTIndex_Class());
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
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "BPTIndex::sizeof(BPTINDEX_DATA) = %lu\n", 
                sizeof(BPTINDEX_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPTINDEX_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BPTIndex_IsEnabled (
        BPTINDEX_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
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
    //                          L R U
    //---------------------------------------------------------------

    void            BPTIndex_LruAttach (
        BPTINDEX_DATA *this,
        void            *pData,
        uint32_t        lsn
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif

        //FIXME: update below
#ifdef NOT_IMPLEMENTED
        if (obj_Flag(this, BPTIDX_BLOCK_ALLOC)) {
            mem_Free(this->pBlock);
            obj_FlagOff(this, BPTIDX_BLOCK_ALLOC);
        }
        this->pBlock = pData;
        this->index = lsn;
#endif

        // Return to caller.
    }


    void            BPTIndex_LruDetach (
        BPTINDEX_DATA *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif

        //FIXME: update below
#ifdef NOT_IMPLEMENTED
        this->pBlock = NULL;
        this->index = 0;
#endif

        // Return to caller.
    }



    //---------------------------------------------------------------
    //         M a x i m u m  N u m b e r  o f  R e c o r d s
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    uint32_t        BPTIndex_MaxRcds (
        BPTINDEX_DATA *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        maxRcds = 0;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        maxRcds =   BlkdRcds16_CalcNumFixedRcds(
                            BlkdRcds16_getBlockSize((BLKDRCDS16_DATA *)this),
                                              sizeof(BPTINDEX_RSVD),
                                              (sizeof(BPTINDEX_NODE)
                                               + BPTIndex_getKeyLen(this))
                    );

        // Return to caller.
        return maxRcds;
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
        void        *pMethod = BPTIndex_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BPTIndex", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BPTIndex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BPTINDEX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(BPTINDEX_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BPTIndex_Class();
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
                            return BPTIndex_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BPTIndex_Enable;
                        }
                        break;

                    case 'L':
                        if (str_Compare("LRU_Attach", (char *)pStr) == 0) {
                            return BPTIndex_LruAttach;
                        }
                        if (str_Compare("LRU_Detach", (char *)pStr) == 0) {
                            return BPTIndex_LruDetach;
                        }
                        break;
                                            case 'P':
#ifdef  BPTINDEX_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return BPTIndex_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return BPTIndex_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BPTIndex_ToDebugString;
                        }
#ifdef  BPTINDEX_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return BPTIndex_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BPTIndex_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BPTIndex_ToDebugString)
                    return "ToDebugString";
#ifdef  BPTINDEX_JSON_SUPPORT
                if (pData == BPTIndex_ToJson)
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

    ERESULT         BPTIndex_Setup(
        BPTINDEX_DATA *this,
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff                  // relative to zero
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        BPTINDEX_RSVD *pRsvd;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (blockSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (keyLen <= 255)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc =   BlkdRcds16_SetupWithBlockSize(
                                    (BLKDRCDS16_DATA *)this,
                                    blockSize,
                                    sizeof(BPTINDEX_RSVD),
                                    NULL
                );
        if (ERESULT_OK(eRc)) {
            pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);
            pRsvd->blockType = 'I';
            pRsvd->keyLen = keyLen;
            pRsvd->keyOff = keyOff;
            this->lbn = lbn;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPTIndex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTIndex_ToDebugString (
        BPTINDEX_DATA      *this,
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
        if (!BPTIndex_Validate(this)) {
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
                    BPTIndex_getSize(this),
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
    //                          U p d a t e
    //---------------------------------------------------------------

    ERESULT         BPTIndex_Update (
        BPTINDEX_DATA *this,
        uint32_t        lbn,
        uint8_t         *pKey
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        int             iRc;
        uint32_t        i;
        uint32_t        iMax;
        BPTINDEX_NODE *pNode;
        uint16_t        keyLen;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pKey) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        keyLen = BPTIndex_getKeyLen(this);

        // Search the keys already in the block.
        iMax = BPTIndex_getNumRecords(this);
        for (i=0; i<iMax; i++) {
            pNode = BlkdRcds16_DataAddr((BLKDRCDS16_DATA *)this, i+1);
            if (pNode) {
                iRc =   memcmp(
                               pKey,
                               pNode->key,
                               keyLen
                        );
                if (0 == iRc) {
                    pNode->lbn = lbn;
                    eRc = ERESULT_SUCCESS;
                    break;
                }
                if (iRc > 0)
                    break;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            BPTIndex_Validate (
        BPTINDEX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BPTINDEX))
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


        if (!(obj_getSize(this) >= sizeof(BPTINDEX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    //---------------------------------------------------------------
    //                       V e r i f y
    //---------------------------------------------------------------

    /*!
     Verify as much of this object as we can.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPTIndex_Verify (
        BPTINDEX_DATA *this
    )
    {
        //ERESULT         eRc;
        int             iRc;
        uint32_t        i;
        uint32_t        iMax;
        BPTINDEX_NODE *pNode1 = NULL;
        BPTINDEX_NODE *pNode2 = NULL;
        uint8_t         *pData1;
        uint8_t         *pData2;
        uint16_t        keyLen;
        uint16_t        rcdLen;
        BPTINDEX_RSVD *pRsvd;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPTIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (BlkdRcds16_Verify((BLKDRCDS16_DATA *)this))
            ;
        else
            return ERESULT_GENERAL_FAILURE;

        // Verify block type.
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);
        if (pRsvd->blockType == 'I')
            ;
        else
            return false;

        // Verify marker.
        pData1 = BPTIndex_getBlock(this);
        pData1 += BlkdRcds16_getBlockSize((BLKDRCDS16_DATA *)this) - 1;
        if ('I' == *pData1)
            ;
        else {
            return false;
        }

        // Verify Key Order.
        keyLen = BPTIndex_getKeyLen(this);
        if (keyLen)
            ;
        else
            return false;

        iMax = BlkdRcds16_getNumRecords((BLKDRCDS16_DATA *)this);
        if (iMax) {
            rcdLen = 0;
            pNode1 = BPTIndex_GetNum(this, 1, &rcdLen);
            if (NULL == pNode1)
                return false;
            if (rcdLen == (keyLen + sizeof(BPTINDEX_NODE)))
                ;
            else
                return false;
            if (pData1) {
                for (i=1; i<iMax; ++i) {
                    rcdLen = 0;
                    pNode2 = BPTIndex_GetNum(this, i+1, &rcdLen);
                    if (NULL == pNode2)
                        return false;
                    if (rcdLen == (keyLen + sizeof(BPTINDEX_NODE)))
                        ;
                    else
                        return false;
                    iRc =   memcmp(
                                   pNode1->key,
                                   pNode2->key,
                                   keyLen
                            );
                    if (0 > iRc)
                        ;
                    else
                        return false;
                    mem_Free(pNode1);
                    pNode1 = pNode2;
                }
                mem_Free(pNode1);
            }
        }

        // Return to caller.
        return true;
    }




#ifdef  __cplusplus
}
#endif


