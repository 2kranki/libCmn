// vi:nu:et:sts=4 ts=4 sw=4
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
#include    <psxThread.h>
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
        uint16_t        elemSize,       // Element Size in bytes (multiple of 4)
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
        if ((0 == elemSize) || (elemSize & (4-1))) {
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

    uint16_t        cb_getElementSize(
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
        return this->elemSize;
    }
    
    
    
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
        uint16_t        count = 0;
        bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            count = (uint16_t)(this->numWritten - this->numRead);
        }
        
        fRc = psxMutex_Unlock(this->pMutex);
        
        // Return to caller.
        return count;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void        cb_Dealloc(
        OBJ_ID      objId
    )
    {
        CB_DATA		*this = objId;
        bool        fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            obj_FlagSet(this, CB_FLAG_STOP, true);
            fRc = psxCond_Broadcast(this->pEmpty);
            fRc = psxCond_Broadcast(this->pFull);
            fRc = psxMutex_Unlock(this->pMutex);
        }
        psxThread_Wait(1000);

        if (this->pEmpty) {
            obj_Release(this->pEmpty);
            this->pEmpty = OBJ_NIL;
        }
        if (this->pFull) {
            obj_Release(this->pFull);
            this->pFull = OBJ_NIL;
        }
        if (this->pMutex) {
            obj_Release(this->pMutex);
            this->pMutex = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

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
        
        if (obj_Flag(this, CB_FLAG_STOP)) {
            return false;
        }
        
        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            while ((cb_NumEntries(this) == 0) && !obj_Flag(this, CB_FLAG_STOP)) {
                fRc = psxCond_Wait(this->pFull);
            }
        }

        fRc = false;
        if (cb_NumEntries(this)) {
            if (cb_NumEntries(this) < this->cEntries) {
                fNotFull = true;
            }
            if (pData) {
                pElem = cb_GetPtr(this, this->start);
                if( pElem ) {
                    TRC_OBJ(
                            this,
                            "cb_Get(%p):  %d Entries  start: %d\n",
                            this,
                            cb_NumEntries(this),
                            this->start
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
        
        if (fRc) {
            psxCond_Signal(this->pEmpty);
        }
        psxMutex_Unlock(this->pMutex);
        
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
        bool            fEmpty = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        fRc = psxMutex_Lock(this->pMutex);
        if (cb_NumEntries(this) == 0) {
            fEmpty = true;
        }
        fRc = psxMutex_Unlock(this->pMutex);
        
        return fEmpty;
    }


     
    //---------------------------------------------------------------
    //                       i s F u l l
    //---------------------------------------------------------------

    bool            cb_isFull(
        CB_DATA       *this
    )
    {
        bool            fRc = false;
        bool            fFull = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        fRc = psxMutex_Lock(this->pMutex);
        if (cb_NumEntries(this) == this->cEntries) {
            fFull = true;
        }
        fRc = psxMutex_Unlock(this->pMutex);

        return fFull;
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

        
        this = obj_Init(this, cbSize, OBJ_IDENT_CB);
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
        
        this->pMutex = psxMutex_New();
        if (OBJ_NIL == this->pMutex) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pEmpty = psxCond_New(this->pMutex);
        if (OBJ_NIL == this->pEmpty) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pFull = psxCond_New(this->pMutex);
        if (OBJ_NIL == this->pFull) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }

     

    //---------------------------------------------------------------
    //                       P a u s e
    //---------------------------------------------------------------
    
    bool            cb_Pause(
        CB_DATA         *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            obj_FlagSet(this, CB_FLAG_STOP, true);
            fRc = psxCond_Broadcast(this->pEmpty);
            fRc = psxCond_Broadcast(this->pFull);
            fRc = psxMutex_Unlock(this->pMutex);
        }
        
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

        if (obj_Flag(this, CB_FLAG_STOP)) {
            return false;
        }
        fRc = psxMutex_Lock(this->pMutex);
        while ((cb_NumEntries(this) == this->cEntries) && !obj_Flag(this, CB_FLAG_STOP)) {
            fRc = psxCond_Wait(this->pEmpty);
        }
        
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

        if (fRc) {
            psxCond_Signal(this->pFull);
        }
        psxMutex_Unlock(this->pMutex);
        
        return fRc;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          cb_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        CB_DATA         *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !cb_Validate(this) ) {
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
                            return cb_ToDebugString;
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
    //                       R e s u m e
    //---------------------------------------------------------------
    
    bool            cb_Resume(
        CB_DATA         *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = psxMutex_Lock(this->pMutex);
        obj_FlagSet(this, CB_FLAG_STOP, false);
        fRc = psxMutex_Unlock(this->pMutex);

        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     cb_ToDebugString(
        CB_DATA         *this,
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
                     "{%p(cb) side=%d ",
                     this,
                     cb_getSize(this)
                     );
        AStr_AppendA(pStr, str);
        
#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->toDebugString(
                                                                             this->pData,
                                                                             indent+3
                                                                             );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p(cb)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     cb_ToJSON(
        CB_DATA         *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !cb_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
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




