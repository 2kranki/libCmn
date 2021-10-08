// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BPT32Index.c
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
#include        <BPT32Index_internal.h>
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
    void            BPT32Index_task_body (
        void            *pData
    )
    {
        //BPT32INDEX_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BPT32INDEX_DATA *     BPT32Index_Alloc (
        void
    )
    {
        BPT32INDEX_DATA       *this;
        uint32_t        cbSize = sizeof(BPT32INDEX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BPT32INDEX_DATA *     BPT32Index_New (
        void
    )
    {
        BPT32INDEX_DATA       *this;
        
        this = BPT32Index_Alloc( );
        if (this) {
            this = BPT32Index_Init(this);
        } 
        return this;
    }


    BPT32INDEX_DATA * BPT32Index_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff,
        OBJ_ID          pMgr
    )
    {
        ERESULT         eRc;
        BPT32INDEX_DATA *this = OBJ_NIL;

        if (keyLen) {
            this = BPT32Index_New( );
            if (this) {
                eRc = BPT32Index_Setup(this, blockSize, lbn, keyLen, keyOff);
                if (ERESULT_OK(eRc)) {
                    BPT32Index_setManager(this, pMgr);
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

    uint8_t *       BPT32Index_getBlock (
        BPT32INDEX_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return BlkdRcds16_getData((BLKDRCDS16_DATA *)this);
    }



    //---------------------------------------------------------------
    //                        K e y  L e n g t h
    //---------------------------------------------------------------

    uint16_t        BPT32Index_getKeyLen (
        BPT32INDEX_DATA *this
    )
    {
        BPT32INDEX_RSVD *pRsvd;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        pRsvd = (BPT32INDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        return pRsvd->keyLen;
    }


    bool            BPT32Index_setKeyLen (
        BPT32INDEX_DATA *this,
        uint16_t        value
    )
    {
        BPT32INDEX_RSVD *pRsvd;

#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pRsvd = (BPT32INDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        pRsvd->keyLen = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        K e y  O f f s e t
    //---------------------------------------------------------------

    uint16_t        BPT32Index_getKeyOff (
        BPT32INDEX_DATA *this
    )
    {
        BPT32INDEX_RSVD *pRsvd;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        pRsvd = (BPT32INDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        return pRsvd->keyOff;
    }


    bool            BPT32Index_setKeyOff (
        BPT32INDEX_DATA *this,
        uint16_t        value
    )
    {
        BPT32INDEX_RSVD *pRsvd;

#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        pRsvd = (BPT32INDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);

        pRsvd->keyOff = value;

        return true;
    }



    //---------------------------------------------------------------
    //             L o g i c a l  B l o c k  N u m b e r
    //---------------------------------------------------------------

    uint32_t        BPT32Index_getLBN (
        BPT32INDEX_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->lbn;
    }


    bool            BPT32Index_setLBN (
        BPT32INDEX_DATA *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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

    bool            BPT32Index_setManager(
        BPT32INDEX_DATA  *this,
        OBJ_ID           *pMgr          // Block Manager
    )
    {
        OBJ_IUNKNOWN    *pVtbl;

#ifdef NDEBUG
#else
        if( !BPT32Index_Validate(this) ) {
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

    uint16_t        BPT32Index_getNumRecords (
        BPT32INDEX_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return BlkdRcds16_getNumRecords((BLKDRCDS16_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        BPT32Index_getPriority (
        BPT32INDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            BPT32Index_setPriority (
        BPT32INDEX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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
    
    uint32_t        BPT32Index_getSize (
        BPT32INDEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * BPT32Index_getStr (
        BPT32INDEX_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        BPT32Index_setStr (
        BPT32INDEX_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  BPT32Index_getSuperVtbl (
        BPT32INDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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

    ERESULT         BPT32Index_Add (
        BPT32INDEX_DATA *this,
        uint32_t        lbn,
        void            *pKey
    )
    {
        ERESULT         eRc = ERESULT_DATA_NOT_FOUND;
        int             iRc;
        uint32_t        i = 0;
        uint32_t        iMax;
        uint8_t         rcd[sizeof(uint32_t)+256];
        BPT32INDEX_NODE *pNode = (BPT32INDEX_NODE *)rcd;
        uint16_t        nodeLen;
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pKey) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Build the record.
        pNode->lbn = lbn;
        memmove(pNode->key, pKey, BPT32Index_getKeyLen(this));
        nodeLen = sizeof(uint32_t) + BPT32Index_getKeyLen(this);

        // Search the keys already in the block.
        iMax = BlkdRcds16_getNumRecords((BLKDRCDS16_DATA *)this);
        if (iMax) {
            for (i=0; i<iMax; i++) {
                BPT32INDEX_NODE *pRcd = BlkdRcds16_DataAddr((BLKDRCDS16_DATA *)this, i+1);
                if (pRcd) {
                    iRc =   memcmp(
                                   pKey,
                                   pRcd->key,
                                   BPT32Index_getKeyLen(this)
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
        ERESULT eRc = BPT32Index_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BPT32INDEX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BPT32Index_Assign (
        BPT32INDEX_DATA       *this,
        BPT32INDEX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BPT32Index_Validate(pOther)) {
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
    int             BPT32Index_Compare (
        BPT32INDEX_DATA     *this,
        BPT32INDEX_DATA     *pOther
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
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!BPT32Index_Validate(pOther)) {
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
        BPT32Index      *pCopy = BPT32Index_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPT32INDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32INDEX_DATA *     BPT32Index_Copy (
        BPT32INDEX_DATA       *this
    )
    {
        BPT32INDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef BPT32INDEX_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = BPT32Index_New( );
        if (pOther) {
            eRc = BPT32Index_Assign(this, pOther);
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

    void            BPT32Index_Dealloc (
        OBJ_ID          objId
    )
    {
        BPT32INDEX_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BPT32INDEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BPT32Index_setStr(this, OBJ_NIL);

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
        BPT32Index      *pDeepCopy = BPT32Index_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BPT32INDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BPT32INDEX_DATA *     BPT32Index_DeepCopy (
        BPT32INDEX_DATA       *this
    )
    {
        BPT32INDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BPT32Index_New( );
        if (pOther) {
            eRc = BPT32Index_Assign(this, pOther);
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
    ERESULT         BPT32Index_Disable (
        BPT32INDEX_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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
    ERESULT         BPT32Index_Enable (
        BPT32INDEX_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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
    //                              G e t
    //---------------------------------------------------------------

    uint8_t *       BPT32Index_GetNum (
        BPT32INDEX_DATA *this,
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
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
        if ((0 == index) || !((index - 1) < BPT32Index_getNumRecords(this))) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return NULL;
        }
#endif

        size = BlkdRcds16_RecordSize((BLKDRCDS16_DATA *)this, index);
        pData = mem_Malloc(size+1);
        if (pData) {
            eRc = BlkdRcds16_RecordGet((BLKDRCDS16_DATA *)this, index, size+1, pData, &used);
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
        return pData;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BPT32INDEX_DATA *   BPT32Index_Init (
        BPT32INDEX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BPT32INDEX_DATA);
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
        // in the OBJ_INFO at the end of BPT32Index_object.c
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BPT32INDEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BPT32Index_Vtbl);
#ifdef  BPT32INDEX_JSON_SUPPORT
        JsonIn_RegisterClass(BPT32Index_Class());
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
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "BPT32Index::sizeof(BPT32INDEX_DATA) = %lu\n", 
                sizeof(BPT32INDEX_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BPT32INDEX_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BPT32Index_IsEnabled (
        BPT32INDEX_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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

    void            BPT32Index_LruAttach (
        BPT32INDEX_DATA *this,
        void            *pData,
        uint32_t        lsn
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return;
        }
#endif

        //FIXME: update below
#ifdef NOT_IMPLEMENTED
        if (obj_Flag(this, BPT32IDX_BLOCK_ALLOC)) {
            mem_Free(this->pBlock);
            obj_FlagOff(this, BPT32IDX_BLOCK_ALLOC);
        }
        this->pBlock = pData;
        this->index = lsn;
#endif

        // Return to caller.
    }


    void            BPT32Index_LruDetach (
        BPT32INDEX_DATA *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = BPT32Index_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BPT32Index", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BPT32Index_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BPT32INDEX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(BPT32INDEX_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BPT32Index_Class();
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
                            return BPT32Index_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BPT32Index_Enable;
                        }
                        break;

                    case 'L':
                        if (str_Compare("LRU_Attach", (char *)pStr) == 0) {
                            return BPT32Index_LruAttach;
                        }
                        if (str_Compare("LRU_Detach", (char *)pStr) == 0) {
                            return BPT32Index_LruDetach;
                        }
                        break;
                                            case 'P':
#ifdef  BPT32INDEX_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return BPT32Index_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return BPT32Index_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BPT32Index_ToDebugString;
                        }
#ifdef  BPT32INDEX_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return BPT32Index_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BPT32Index_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BPT32Index_ToDebugString)
                    return "ToDebugString";
#ifdef  BPT32INDEX_JSON_SUPPORT
                if (pData == BPT32Index_ToJson)
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

    ERESULT         BPT32Index_Setup(
        BPT32INDEX_DATA *this,
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff                  // relative to zero
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        BPT32INDEX_RSVD *pRsvd;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
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
                                    sizeof(BPT32INDEX_RSVD),
                                    NULL
                );
        if (ERESULT_OK(eRc)) {
            pRsvd = (BPT32INDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)this);
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
        ASTR_DATA      *pDesc = BPT32Index_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Index_ToDebugString (
        BPT32INDEX_DATA      *this,
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
        if (!BPT32Index_Validate(this)) {
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
                    BPT32Index_getSize(this),
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
    bool            BPT32Index_Validate (
        BPT32INDEX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BPT32INDEX))
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


        if (!(obj_getSize(this) >= sizeof(BPT32INDEX_DATA))) {
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
    ERESULT         BPT32Index_Verify (
        BPT32INDEX_DATA *this
    )
    {
        //ERESULT         eRc;
        int             iRc;
        uint32_t        key = 0;
        uint32_t        i;
        uint32_t        iMax;
        //FIXME: BPT32LF_NODE    *pNode = NULL;
        uint8_t         *pData1;
        uint8_t         *pData2;
        uint16_t        rcdLen;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BPT32Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (BlkdRcds16_Verify((BLKDRCDS16_DATA *)this))
            ;
        else
            return ERESULT_GENERAL_FAILURE;

        // Verify marker.
        pData1 = BPT32Index_getBlock(this);
        pData1 += BlkdRcds16_getBlockSize((BLKDRCDS16_DATA *)this) - 1;
        if ('L' == *pData1)
            ;
        else {
            return false;
        }

        // Verify Key Order.
        if (BPT32Index_getKeyLen(this))
            ;
        else
            return false;

        iMax = BlkdRcds16_getNumRecords((BLKDRCDS16_DATA *)this);
        pData1 = BPT32Index_GetNum(this, 1, NULL);
        if (NULL == pData1)
            return false;
        rcdLen = BlkdRcds16_RecordSize((BLKDRCDS16_DATA *)this, 1);
        if (rcdLen < BPT32Index_getKeyLen(this))
            return false;
        if (pData1) {
            for (i=1; i<iMax; ++i) {
                pData2 = BPT32Index_GetNum(this, i+1, NULL);
                if (NULL == pData2)
                    return false;
                rcdLen = BlkdRcds16_RecordSize((BLKDRCDS16_DATA *)this, i+1);
                if (rcdLen < BPT32Index_getKeyLen(this))
                    return false;
                iRc =   memcmp(
                               pData1+BPT32Index_getKeyOff(this),
                               pData2+BPT32Index_getKeyOff(this),
                               BPT32Index_getKeyLen(this)
                        );
                if (0 == iRc)
                    ;
                else
                    return false;
                mem_Free(pData1);
                pData1 = pData2;
            }
            mem_Free(pData1);
        }

        // Return to caller.
        return true;
    }




#ifdef  __cplusplus
}
#endif


