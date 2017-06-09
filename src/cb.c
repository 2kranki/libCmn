// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   cb.c
 * Author: bob
 *
 * Created on October 25, 2014
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




#include    <cb_internal.h>
#include    <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    void *          cb_GetPtr(
        CB_DATA         *this,
        uint16_t        index
    );
    
    uint16_t        cb_NumEntries(
        CB_DATA         *this
    );
    
#ifdef NDEBUG
#else
    static
    bool			cb_Validate(
        CB_DATA         *this
    );
#endif


    
#ifdef NDEBUG
#else
    void                cb_DumpBuffer(
        CB_DATA             *this
    )
    {
        uint32_t        i;
        
        if (obj_Trace(this)) {
            TRC_OBJ(
                    this,
                    "Buffer(%d) currently:%d\n",
                    this->cEntries,
                    cb_NumEntries(this)
            );
            for (i=0; i<cb_NumEntries(this); ++i) {
                TRC_OBJ(this, "\t%d - %s\n", i, cb_GetPtr(this, i));
            }
        }
    }
#endif
    
    
    
    void *          cb_GetPtr(
        CB_DATA         *this,
        uint16_t        index
    )
    {
        uint8_t         *ptr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( index >= this->cEntries ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        ptr = &this->entries[(index * this->elemSize)];

        // Return to caller.
        return( ptr );
    }



    uint16_t        cb_NumEntries(
        CB_DATA         *this
    )
    {
        uint16_t        numEntries = 0;
        
        numEntries = (uint16_t)(this->numWritten - this->numRead);
        
        // Return to caller.
        return numEntries;
    }
    
    
    

    
    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    //---------------------------------------------------------------
    //                        A l l o c
    //---------------------------------------------------------------

    CB_DATA *       cb_Alloc(
        uint16_t        elemSize,       // Element Size in bytes
        uint16_t        size            // Number of Elements in Buffer
    )
    {
        CB_DATA         *this;
        uint32_t        cbSize;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (0 == size) {
            DEBUG_BREAK();
            return NULL;
        }
        if (0 == elemSize) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        elemSize = ROUNDUP4(elemSize);
        cbSize = size * elemSize;
        cbSize += sizeof(CB_DATA);
        if ((64 * 1024) <= cbSize) {
            return NULL;
        }
        
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, size);
        obj_setMisc2(this, elemSize);
        
        // Return to caller.
        return this;
    }


    //---------------------------------------------------------------
    //                          N e w
    //---------------------------------------------------------------
    
    CB_DATA *       cb_New(
        uint16_t        elemSize,       // Element Size in bytes
        uint16_t        size            // Number of Elements in Buffer
    )
    {
        CB_DATA         *this;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (0 == size) {
            DEBUG_BREAK();
            return NULL;
        }
        if (0 == elemSize) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        this = cb_Alloc(elemSize, size);
        if (this) {
            this = cb_Init(this);
        }
        
        // Return to caller.
        return this;
    }
    
    
    


    

    //===============================================================
    //                    P r o p e r t i e s
    //===============================================================

    uint16_t        cb_getSize(
        CB_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        // Return to caller.
        return this->cEntries;
    }




    
    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        C o u n t
    //---------------------------------------------------------------

    uint16_t        cb_Count(
        CB_DATA       *this
    )
    {
        uint16_t        count;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
#ifdef XYZZY
        psxLock_Lock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_lock(&this->mutex);
#endif
        
        count = (uint16_t)(this->numWritten - this->numRead);
        
#ifdef XYZZY
        psxLock_Unlock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_unlock(&this->mutex);
#endif
        
        // Return to caller.
        return( count );
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void        cb_Dealloc(
        OBJ_ID      objId
    )
    {
        CB_DATA		*this = objId;
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
#ifdef XYZZY
        if (this->pSemEmpty) {
            obj_Release(this->pSemEmpty);
            this->pSemEmpty = OBJ_NIL;
        }
        if (this->pSemFull) {
            obj_Release(this->pSemFull);
            this->pSemFull = OBJ_NIL;
        }
        if (this->pLock) {
            obj_Release(this->pLock);
            this->pLock = OBJ_NIL;
        }
#endif
#if defined(__MACOSX_ENV__)
        // We must release any Get()s/Put()s.
        obj_FlagSet(this, CB_FLAG_PAUSE, true);
        pthread_cond_broadcast(&this->cond);
        usleep(500000);
        
        iRc = pthread_cond_destroy(&this->cond);
        if (iRc) {
            DEBUG_BREAK();
        }
        iRc = pthread_mutex_destroy(&this->mutex);
        if (iRc) {
            DEBUG_BREAK();
        }
#endif
        
        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------

    bool            cb_Get(
        CB_DATA         *this,
        void            *pData
    )
    {
        bool            fRc = false;
        uint8_t         *pElem;
        bool            fNotFull = false;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
#ifdef XYZZY
        psxSem_Wait(this->pSemFull);
        psxLock_Lock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        if (obj_Flag(this, CB_FLAG_PAUSE)) {
            return false;
        }
        pthread_mutex_lock(&this->mutex);
        while (cb_NumEntries(this) == 0) { // queue is empty
            if (obj_Flag(this, CB_FLAG_PAUSE)) {
                pthread_mutex_unlock(&this->mutex);
                return false;
            }
            pthread_cond_wait(&this->cond, &this->mutex);
        }
#endif
        
        if (cb_NumEntries(this)) {
            if (cb_NumEntries(this) < this->cEntries) {
                fNotFull = true;
            }
            if (pData) {
                pElem = cb_GetPtr(this, this->start);
                if( pElem ) {
                    TRC_OBJ(
                            this,
                            "cb_Get(%p):  %d Entries  start: %d - %s\n",
                            this,
                            cb_NumEntries(this),
                            this->start,
                            pElem
                    );
                    memmove(pData, pElem, this->elemSize);
                    // below needed if multi-processor (???)
                    //__sync_fetch_and_add( &this->numRead, 1 );
                    ++this->numRead;
                    ++this->start;
                    if (this->start == this->cEntries) {
                        this->start = 0;
                    }
                    fRc = true;
                }
            }
        }
        
#ifdef XYZZY
        pthread_mutex_unlock(&this-mutex);
        psxLock_Unlock(this->pLock);
        psxSem_Post(this->pSemEmpty);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_unlock(&this->mutex);
        if (fNotFull) {
            pthread_cond_signal(&this->cond);
        }
#endif
        
        return fRc;
    }

     

    //---------------------------------------------------------------
    //                       i s E m p t y
    //---------------------------------------------------------------

    bool            cb_isEmpty(
        CB_DATA         *this
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

#ifdef XYZZY
        psxLock_Lock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_lock(&this->mutex);
#endif
        
        if (cb_NumEntries(this) == 0) {
            fRc = true;
        }
        
#ifdef XYZZY
        psxLock_Unlock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_unlock(&this->mutex);
#endif
        
        return fRc;
    }


     
    //---------------------------------------------------------------
    //                       i s F u l l
    //---------------------------------------------------------------

    bool            cb_isFull(
        CB_DATA       *this
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

#ifdef XYZZY
        psxLock_Lock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_lock(&this->mutex);
#endif
        
        if (cb_NumEntries(this) == this->cEntries) {
            fRc = true;
        }
        
#ifdef XYZZY
        psxLock_Unlock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_unlock(&this->mutex);
#endif
        
        return fRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    CB_DATA *       cb_Init(
        CB_DATA         *this
    )
    {
        uint32_t        cbSize = sizeof(CB_DATA);
        uint32_t        dataSize;
        uint16_t        size =  obj_getMisc1(this);
        uint16_t        elemSize =  obj_getMisc2(this);
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif

        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( 0 == size ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( 0 == elemSize ) {
            DEBUG_BREAK();
            return NULL;
        }
        // Must be less than 2^31 because of numWritten and numRead.
        // This should not happen since size is 16 bits.
        if ( !(size < 0x7FFF) ) {
            return NULL;
        }
#endif
        cbSize += size * elemSize;

        
        this = obj_Init( this, cbSize, OBJ_IDENT_CB );
        if (NULL == this) {
            return NULL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&cb_Vtbl);
        
        dataSize = size * elemSize;
        if (dataSize >= (64 * 1024)) {
            DEBUG_BREAK();
            obj_Release(this);
            return NULL;
        }        
        this->cEntries = size;
        this->elemSize = elemSize;
        
#ifdef XYZZY
        this->pSemEmpty = psxSem_New(size,size);
        if (OBJ_NIL == this->pSemEmpty) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pSemFull = psxSem_New(0,size);
        if (OBJ_NIL == this->pSemFull) {
            DEBUG_BREAK();
            obj_Release(this->pSemEmpty);
            this->pSemEmpty = OBJ_NIL;
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pLock = psxLock_New();
        if (OBJ_NIL == this->pLock) {
            DEBUG_BREAK();
            obj_Release(this->pSemFull);
            this->pSemFull = OBJ_NIL;
            obj_Release(this->pSemEmpty);
            this->pSemEmpty = OBJ_NIL;
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
#if defined(__MACOSX_ENV__)
        //this->mutex = PTHREAD_MUTEX_INITIALIZER;
        iRc = pthread_mutex_init(&this->mutex, NULL);
        if (iRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        // this->cond = PTHREAD_COND_INITIALIZER;
        iRc = pthread_cond_init(&this->cond, NULL);
        if (iRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        return this;
    }

     

    //---------------------------------------------------------------
    //                       P a u s e
    //---------------------------------------------------------------
    
    bool            cb_Pause(
        CB_DATA         *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        obj_FlagSet(this, CB_FLAG_PAUSE, true);
        pthread_cond_broadcast(&this->cond);
        usleep(100000);
#endif
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------

    bool            cb_Put(
        CB_DATA         *this,
        void            *pValue
    )
    {
        bool            fRc = false;
        uint8_t         *pElem;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

#ifdef XYZZY
        psxSem_Wait(this->pSemEmpty);
        psxLock_Lock(this->pLock);
#endif
#if defined(__MACOSX_ENV__)
        if (obj_Flag(this, CB_FLAG_PAUSE)) {
            return false;
        }
        pthread_mutex_lock(&this->mutex);
        while (cb_NumEntries(this) == this->cEntries) { // queue is full
            if (obj_Flag(this, CB_FLAG_PAUSE)) {
                pthread_mutex_unlock(&this->mutex);
                return false;
            }
            pthread_cond_wait (&this->cond, &this->mutex);
        }
#endif
        
        if (cb_NumEntries(this) < this->cEntries) {
            TRC_OBJ(
                    this,
                    "cb_Put(%p): %d Entries  end: %d\n",
                    this,
                    cb_NumEntries(this),
                    this->end
                    );
            pElem = cb_GetPtr(this, this->end);
            if (pElem) {
                memmove(pElem, pValue, this->elemSize);
                ++this->numWritten;
                ++this->end;
                if (this->end == this->cEntries) {
                    this->end = 0;
                }
                fRc = true;
            }
        }

#ifdef XYZZY
        psxLock_Unlock(this->pLock);
        psxSem_Post(this->pSemFull);
#endif
#if defined(__MACOSX_ENV__)
        pthread_mutex_unlock(&this->mutex);
        pthread_cond_signal(&this->cond);
#endif
        
        return fRc;
    }



    //---------------------------------------------------------------
    //                       R e s u m e
    //---------------------------------------------------------------
    
    bool            cb_Resume(
        CB_DATA         *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        obj_FlagSet(this, CB_FLAG_PAUSE, false);
#endif
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool			cb_Validate(
        CB_DATA       *this
    )
    {

        // Do initialization.

        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_CB) )
                ;
            else
                return false;
        }
        else {
            DEBUG_BREAK();
            return false;
        }
        if( obj_getSize(this) >= sizeof(CB_DATA) )
            ;
        else {
            DEBUG_BREAK();
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif



#ifdef	__cplusplus
}
#endif




