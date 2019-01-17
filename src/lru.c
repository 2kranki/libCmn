// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   lru.c
 *	Generated 10/21/2016 23:23:20
 *
 * Notes:
 *
 *  We use multiple chains to keep track of the buffers allocated. The
 *  free chain contains all buffers that are not in-use.  Initially,
 *  this will be all of them.  As they are put inuse, they are moved
 *  from the free chain to the LRU chain.  They will remain there until
 *  more space is needed.  If a buffer becomes locked, it will be moved
 *  from either the free chain or the LRU chain to the locked chain and
 *  will remain there until it is unlocked or the program is terminated.
 *
 *  The buffers are also on a second chaining system that allows fast
 *  access by logical sector number using a hashing system.  All active
 *  buffers are on this secondary chain.
 
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
#include "lru_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //----------------------------------------------------------------
    //      uint32_hash - calculate a hash for a 32 bit number
    //----------------------------------------------------------------
    
    // See http://burtleburtle.net/bob/hash/
    // A Public Domain Hash Function
    // Thomas Wang's integer hash using multiplication that's faster than
    // any of mine on my Core 2 duo using gcc -O3, and it passes my favorite sanity
    // tests well. I've had reports it doesn't do well with integer sequences with
    // a multiple of 34.
    uint32_t        lru_HashInteger(
        uint32_t        a
    )
    {
        
        a = (a ^ 61) ^ (a >> 16);
        a = a + (a << 3);
        a = a ^ (a >> 4);
        a = a * 0x27d4eb2d;
        a = a ^ (a >> 15);
        
        return a;
    }
    
    
    
    /*!
     *  Search the lsn hash table for the sector. 
     *  @return     If found, move it to the head of the LRU list 
     *              and return it.  Otherwise, return NULL.
     */
    static
    LRU_BUFFER *    lru_FindLSN(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint32_t        hash
    )
    {
        LRU_BUFFER      *pBuffer = NULL;
        
        while ((pBuffer = listdl_Next(&this->pHash[hash % this->hashSize], pBuffer))) {
            if (pBuffer->lsn == lsn) {
                break;
            }
        }
        if (pBuffer) {
            if (pBuffer->flagLocked)
                ;
            else
                listdl_Move2Head(&this->lruList, pBuffer);
        }
        
        return pBuffer;
    }



    /*!
        Search the LRU and Locked chains flushing all the dirty
        buffers.
     @return        If found, move it to the head of the LRU list
                    and return it.  Otherwise, return NULL.
     */
    ERESULT         lru_FlushCache(
        LRU_DATA        *this
    )
    {
        LRU_BUFFER      *pBuffer = NULL;
        ERESULT         eRc;

        if (NULL == this->pLogicalWrite) {
            return ERESULT_SUCCESS;
        }

        while ((pBuffer = listdl_Next(&this->lruList, pBuffer))) {
            if (pBuffer->flagDirty) {
                eRc =   this->pLogicalWrite(
                                        this->pWriteObject,
                                        pBuffer->lsn,
                                        pBuffer->pData
                        );
                pBuffer->flagDirty = 0;
                ++this->numWrites;
            }
        }

        while ((pBuffer = listdl_Next(&this->lockList, pBuffer))) {
            if (pBuffer->flagDirty) {
                eRc =   this->pLogicalWrite(
                                        this->pWriteObject,
                                        pBuffer->lsn,
                                        pBuffer->pData
                        );
                pBuffer->flagDirty = 0;
                ++this->numWrites;
            }
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    /*!
     *  Search the lsn hash table for the sector.
     *  @return     If found, move it to the head of the LRU list
     *              and return it.  Otherwise, return NULL.
     */
    ERESULT         lru_FreeCache(
        LRU_DATA        *this
    )
    {
        ERESULT         eRc;
        
        eRc = lru_FlushCache(this);
        
        // Free the cache block.
        mem_Free(this->pCache);
        this->pCache = NULL;

        // Free the buffers.
        mem_Free(this->pBuffers);
        this->pBuffers = NULL;
        
        // Free the Hash Table.
        mem_Free(this->pHash);
        this->pHash = NULL;
        
        return ERESULT_SUCCESS;
    }
    
    
    
    /*!
     Get a buffer from the free chain for the end of the LRU chain to
     be used next, flush it if it was dirty and rechain it to the top
     of the LRU chain.
     @return        If found, the buffer control entry. Otherwise,
                    return NULL.
     */
    LRU_BUFFER *    lru_GetBuffer(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint32_t        hash
    )
    {
        LRU_BUFFER      *pBufCtl = NULL;
        ERESULT         eRc;
        
        // Get a sector to use.
        if (listdl_Count(&this->freeList)) {
            pBufCtl = listdl_DeleteHead(&this->freeList);
            pBufCtl->flagDirty = 0;
        }
        else {
            pBufCtl = listdl_DeleteTail(&this->lruList);
            listdl_Delete(&this->pHash[pBufCtl->hash % this->hashSize], pBufCtl);
        }
        
        // Flush buffer if it was dirty.
        if (pBufCtl->flagDirty && this->pLogicalWrite) {
            eRc =   this->pLogicalWrite(
                                        this->pWriteObject,
                                        pBufCtl->lsn,
                                        pBufCtl->pData
                    );
            pBufCtl->flagDirty = 0;
            ++this->numWrites;
        }
        
        // Chain it to the lru and hash lists.
        pBufCtl->flagLocked = 0;
        pBufCtl->lsn = lsn;
        pBufCtl->hash = hash;
        listdl_Add2Head(&this->lruList, pBufCtl);
        listdl_Add2Head(&this->pHash[hash % this->hashSize], pBufCtl);
        
        return pBufCtl;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LRU_DATA *      lru_Alloc(
    )
    {
        LRU_DATA       *this;
        uint32_t        cbSize = sizeof(LRU_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LRU_DATA *      lru_New(
        void
    )
    {
        LRU_DATA        *this;
        
        this = lru_Alloc( );
        if (this) {
            this = lru_Init(this);
        }
        return this;
    }
    
    
    LRU_DATA *      lru_NewWithSizes(
        uint32_t        blockSize,
        uint32_t        cacheSize,
        uint16_t        hashSize
    )
    {
        LRU_DATA        *this;
        ERESULT         eRc;
        
        this = lru_Alloc( );
        if (this) {
            this = lru_Init(this);
            if (this) {
                eRc = lru_Setup(this, blockSize, cacheSize, hashSize);
            }
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //----------------------------------------------------------------
    //                  D e l a y  W r i t e s
    //----------------------------------------------------------------
    
    bool            lru_getDelayWrites(
        LRU_DATA        *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        return obj_Flag(this, LRU_FLAG_DELAY_WRITE) ? true : false;
    }

    
    bool            lru_setDelayWrites(
        LRU_DATA        *this,
        bool            value
    )
    {
        bool            fRc;
        
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = obj_FlagSet(this, LRU_FLAG_DELAY_WRITE, value);
        
        return fRc;
    }
    
    
    
    //----------------------------------------------------------------
    //                          P r i o r i t y
    //----------------------------------------------------------------
    
    uint16_t        lru_getPriority(
        LRU_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            lru_setPriority(
        LRU_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    bool            lru_setLogicalSectorRead(
        LRU_DATA        *this,
        ERESULT         (*pLogicalRead)(
            OBJ_ID          pReadObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pReadObject
    )
    {
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pLogicalRead = pLogicalRead;
        this->pReadObject = pReadObject;
        
        return true;
    }
    
    
    
    uint32_t        lru_getSize(
        LRU_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    bool            lru_setLogicalSectorWrite(
        LRU_DATA        *this,
        ERESULT         (*pLogicalWrite)(
            OBJ_ID          pWriteObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pWriteObject
    )
    {
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pLogicalWrite = pLogicalWrite;
        this->pWriteObject = pWriteObject;
        
        return true;
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
        ERESULT eRc = lru__Assign(this,pOther);
     @endcode
     @param     this    LRU object pointer
     @param     pOther  a pointer to another LRU object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         lru_Assign(
        LRU_DATA		*this,
        LRU_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!lru_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
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
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
        eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        lru      *pCopy = lru_Copy(this);
     @endcode
     @param     this    LRU object pointer
     @return    If successful, a LRU object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the LRU object.
     */
    LRU_DATA *     lru_Copy(
        LRU_DATA       *this
    )
    {
        LRU_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = lru_New( );
        if (pOther) {
            eRc = lru_Assign(this, pOther);
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
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            lru_Dealloc(
        OBJ_ID          objId
    )
    {
        LRU_DATA        *this = objId;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LRU_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif
        
        eRc = lru_FreeCache(this);

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

    ERESULT         lru_Disable(
        LRU_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if (!lru_Validate(this)) {
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

    ERESULT         lru_Enable(
        LRU_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!lru_Validate(this)) {
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
    //                     F l u s h  A l l
    //---------------------------------------------------------------
    
    ERESULT         lru_FlushAll(
        LRU_DATA        *this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = lru_FlushCache(this);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LRU_DATA *      lru_Init(
        LRU_DATA        *this
    )
    {
        uint32_t        cbSize = sizeof(LRU_DATA);
        //uint32_t        i;
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LRU);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_LRU);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&lru_Vtbl);
      
#ifdef XYZZY
        listdl_Init(&this->freeList, offsetof(LRU_SECTOR, lruList));
        listdl_Init(&this->lruList, offsetof(LRU_SECTOR, lruList));
        for (i=0; i<NUM_HASH_LIST; ++i) {
            listdl_Init(&this->hashLists[i], offsetof(LRU_SECTOR, hashList));
        }
        this->sectorSize = sectorSize;
        this->cacheSize = cacheSize;
        this->hashSize = NUM_HASH_LIST;
        for (i=0; i<cacheSize; ++i) {
            LRU_SECTOR          *pSector;
            pSector = mem_Calloc(1, (sizeof(LRU_SECTOR) + sectorSize));
            if (pSector) {
                listdl_Add2Head(&this->freeList, pSector);
            }
            else {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
#endif

    #ifdef NDEBUG
    #else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          L o c k
    //---------------------------------------------------------------
    
    ERESULT         lru_Lock(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    )
    {
        ERESULT         eRc;
        LRU_BUFFER      *pBufCtl;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (listdl_Count(&this->lockList) > 3) {
            DEBUG_BREAK();
            return ERESULT_INSUFFICIENT_MEMORY;
        }
#endif
        
        eRc = lru_Read(this, lsn, pBuffer);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        
        hash = lru_HashInteger(lsn);
        pBufCtl = lru_FindLSN(this, lsn, hash);
        if (pBufCtl) {
            if (pBufCtl->flagLocked) {
                return ERESULT_SUCCESS;
            }
            pBufCtl->flagLocked = 1;
            listdl_Delete(&this->lruList, pBufCtl);
            listdl_Add2Head(&this->lockList, pBufCtl);
            if (pBufCtl->flagLocked) {
                return ERESULT_SUCCESS;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          lru_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LRU_DATA        *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return lru_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e a d
    //---------------------------------------------------------------
    
    ERESULT         lru_Read(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    )
    {
        LRU_BUFFER      *pBufCtl = NULL;
        ERESULT         eRc;
        uint32_t        hash;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pBuffer == NULL) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        hash = lru_HashInteger(lsn);

        // Use sector if already in LRU Cache.
        pBufCtl = lru_FindLSN(this, lsn, hash);
        if (pBufCtl) {
            memmove(pBuffer, pBufCtl->pData, this->blockSize);
            return ERESULT_SUCCESS;
        }
        
        // Get a sector to use.
        pBufCtl = lru_GetBuffer(this, lsn, hash);
        
        // Set up the sector.
        eRc = this->pLogicalRead(this->pReadObject, lsn, pBufCtl->pData);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        memmove(pBuffer, pBufCtl->pData, this->blockSize);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         lru_Setup(
        LRU_DATA        *this,
        uint32_t        blockSize,
        uint16_t        cacheSize,          // Number of Blocks in Cache
        uint16_t        hashSize
    )
    {
        ERESULT         eRc;
        LRU_BUFFER      *pBufCntl;
        uint8_t         *pBuffer;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (blockSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (cacheSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = lru_FreeCache(this);
        
        this->blockSize = blockSize;
        this->cacheSize = cacheSize;
        this->hashSize  = hashSize;
        
        // Setup the hash.
        listdl_Init(&this->freeList, offsetof(LRU_BUFFER, lruList));
        listdl_Init(&this->lockList, offsetof(LRU_BUFFER, lruList));
        listdl_Init(&this->lruList, offsetof(LRU_BUFFER, lruList));
        this->pHash = mem_Calloc(hashSize, sizeof(LISTDL_DATA));
        if (NULL == this->pHash) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        for (i=0; i<hashSize; ++i) {
            listdl_Init(&this->pHash[i], offsetof(LRU_BUFFER, hashList));
        }
        
        // Setup the buffers.
        this->pBuffers = mem_Calloc(cacheSize, blockSize);
        if (NULL == this->pBuffers) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        
        // Setup the buffer control blocks.
        this->pCache = mem_Calloc(cacheSize, sizeof(LRU_BUFFER));
        if (NULL == this->pCache) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        pBuffer = this->pBuffers;
        pBufCntl = this->pCache;
        for (i=0; i<cacheSize; ++i) {
            pBufCntl->pData = pBuffer;
            listdl_Add2Head(&this->freeList, pBufCntl);
            pBuffer += blockSize;
            ++pBufCntl;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = lru_ToDebugString(this,4);
     @endcode
     @param     this    LRU object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     lru_ToDebugString(
        LRU_DATA        *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(lru) size=%d\n",
                     this,
                     this->cacheSize
            );
        AStr_AppendA(pStr, str);

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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(lru)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            lru_Validate(
        LRU_DATA      *this
    )
    {
        if( this ) {
            if (obj_IsKindOf(this, OBJ_IDENT_LRU))
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(LRU_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                          U n l o c k
    //---------------------------------------------------------------
    
    ERESULT         lru_Unlock(
        LRU_DATA        *this,
        uint32_t        lsn
    )
    {
        LRU_BUFFER      *pBufCtl;
        uint32_t        hash;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        hash = lru_HashInteger(lsn);
        pBufCtl = lru_FindLSN(this, lsn, hash);
        if (pBufCtl) {
            if (pBufCtl->flagLocked)
                ;
            else {
                return ERESULT_DATA_NOT_FOUND;
            }
            pBufCtl->flagLocked = 1;
            listdl_Delete(&this->lockList, pBufCtl);
            listdl_Add2Head(&this->lruList, pBufCtl);
            if (pBufCtl->flagLocked) {
                return ERESULT_SUCCESS;
            }
        }
        else {
            return ERESULT_DATA_NOT_FOUND;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          W r i t e
    //---------------------------------------------------------------
    
    ERESULT         lru_Write(
        LRU_DATA        *this,
        uint32_t        lsn,
        uint8_t         *pBuffer
    )
    {
        ERESULT         eRc;
        LRU_BUFFER      *pBufCtl = NULL;
        uint32_t        hash;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!lru_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pBuffer == NULL) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        hash = lru_HashInteger(lsn);

        // Use sector if already in LRU Cache.
        pBufCtl = lru_FindLSN(this, lsn, hash);
        if (pBufCtl)
            ;
        else {
            pBufCtl = lru_GetBuffer(this, lsn, hash);
            if (pBufCtl)
                ;
            else {
                return ERESULT_INDEX_FULL;
            }
        }
        
        // Set up the sector and write it out.
        memmove(pBufCtl->pData, pBuffer, this->blockSize);
        pBufCtl->flagDirty = 1;
        if (this->pLogicalWrite && !lru_getDelayWrites(this)) {
            eRc = this->pLogicalWrite(this->pReadObject, lsn, pBuffer);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                listdl_Add2Head(&this->freeList, pBufCtl);
                return eRc;
            }
            pBufCtl->flagDirty = 0;
            ++this->numWrites;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


