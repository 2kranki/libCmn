// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objCb.c
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




#include    "objCb_internal.h"
#include    <psxThread.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef NDEBUG
#else
    static
    bool			objCb_Validate(
        OBJCB_DATA         *this
    );
#endif


#ifdef XYZZY
    static
    OBJ_ID          objCb_GetPtr(
        OBJCB_DATA      *this,
        uint16_t        index
    )
    {
        OBJ_ID         ptr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( (index > 0) && (index <= this->cEntries) )
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        ptr = &this->entries[index];

        // Return to caller.
        return( ptr );
    }
#endif

    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    //---------------------------------------------------------------
    //                        A l l o c
    //---------------------------------------------------------------

    OBJCB_DATA *       objCb_Alloc(
        uint16_t        size            // Number of Elements in Buffer
    )
    {
        OBJCB_DATA      *this;
        uint32_t        cbSize;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (0 == size) {
            DEBUG_BREAK();
            return NULL;
        }
        // Must be less than 2^31 because of numWritten and numRead.
        // This should not happen since size is 16 bits.
        if (size < 0x7FFF)
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        cbSize = size * sizeof(OBJ_ID);
        cbSize += sizeof(OBJCB_DATA);
        if (cbSize < (64 * 1024))
            ;
        else {
            return NULL;
        }
        
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, size);
        
        // Return to caller.
        return this;
    }



    OBJCB_DATA *       objCb_New(
        uint16_t        size            // Number of Elements in Buffer
    )
    {
        OBJCB_DATA      *this;
        
        this = objCb_Alloc(size);
        this = objCb_Init(this);
        
        return this;
    }
    
    
    
    

    //===============================================================
    //                    P r o p e r t i e s
    //===============================================================

    uint16_t        objCb_getSize(
        OBJCB_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objCb_Validate(this) ) {
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

    uint16_t        objCb_Count(
        OBJCB_DATA       *this
    )
    {
        uint16_t        count;
        bool            fRc;
        
        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
    #endif
        
        fRc = psxMutex_Lock(this->pMutex);
        count = (uint16_t)(this->numWritten - this->numRead);
        fRc = psxMutex_Unlock(this->pMutex);

        // Return to caller.
        return  count;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void            objCb_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJCB_DATA	    *this = objId;
        uint32_t        i;
        OBJ_ID          pObj;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !objCb_Validate(this) ) {
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

        for (i=0; i<this->cEntries; ++i) {
            pObj = this->entries[i];
            if (pObj) {
                obj_Release(pObj);
                this->entries[i] = OBJ_NIL;
            }
        }
        
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

    bool            objCb_Get(
        OBJCB_DATA      *this,
        OBJ_ID          *ppData
    )
    {
        bool            fRc = false;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        if (obj_Flag(this, OBJCB_FLAG_STOP)) {
            return false;
        }
        
        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            while (((this->numWritten - this->numRead) == 0) && !obj_Flag(this, CB_FLAG_STOP)) {
                fRc = psxCond_Wait(this->pFull);
            }
        }
        
        if ( (ppData == NULL) || (((this->numWritten - this->numRead)) == 0) ) {
            fRc = false;
        }
        else {
            *ppData = this->entries[this->start];
            this->entries[this->start] = OBJ_NIL;
            // below needed if multi-processor (??)
            //__sync_fetch_and_add( &this->numRead, 1 );
            ++this->numRead;
            ++this->start;
            if (this->start == this->cEntries) {
                this->start = 0;
            }
            fRc = true;
        }
        
        if (fRc) {
            fRc = psxCond_Signal(this->pEmpty);
        }
        fRc = psxMutex_Unlock(this->pMutex);

        return fRc;
    }

     

    //---------------------------------------------------------------
    //                       i s E m p t y
    //---------------------------------------------------------------

    bool            objCb_isEmpty(
        OBJCB_DATA         *this
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        if (((uint16_t)(this->numWritten - this->numRead)) == 0) {
            fRc = true;
        }
        
        return fRc;
    }


     
    //---------------------------------------------------------------
    //                       i s F u l l
    //---------------------------------------------------------------

    bool            objCb_isFull(
        OBJCB_DATA       *this
    )
    {
        bool            fRc = false;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        if ( ((uint16_t)(this->numWritten - this->numRead)) == this->cEntries )
            fRc = true;
        
        return fRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJCB_DATA *       objCb_Init(
        OBJCB_DATA         *this
    )
    {
        uint32_t        cbSize;
        uint16_t        size =  obj_getMisc1(this);


        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
        
        cbSize = obj_getSize(this);
        this = obj_Init( this, cbSize, OBJ_IDENT_OBJCB );
        if (NULL == this) {
            return NULL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objCb_Vtbl);
        
        this->cEntries = size;
        
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
        
#ifdef NDEBUG
#else
        if ( !objCb_Validate(this) ) {
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
    
    bool            objCb_Pause(
        OBJCB_DATA      *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            obj_FlagSet(this, OBJCB_FLAG_STOP, true);
            fRc = psxCond_Broadcast(this->pEmpty);
            fRc = psxCond_Broadcast(this->pFull);
            fRc = psxMutex_Unlock(this->pMutex);
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------

    bool            objCb_Put(
        OBJCB_DATA      *this,
        OBJ_ID          pValue
    )
    {
        bool            fRc = false;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        if (obj_Flag(this, OBJCB_FLAG_STOP)) {
            return false;
        }
        fRc = psxMutex_Lock(this->pMutex);
        while (((this->numWritten - this->numRead) == this->cEntries) && !obj_Flag(this, OBJCB_FLAG_STOP)) {
            fRc = psxCond_Wait(this->pEmpty);
        }
        
        if ( ((uint16_t)(this->numWritten - this->numRead)) == this->cEntries ) {
            fRc = false;
        }
        else {
            obj_Retain(pValue);
            this->entries[this->end] = pValue;
            ++this->numWritten;
            ++this->end;
            if (this->end == this->cEntries) {
                this->end = 0;
            }
            fRc = true;
        }

        if (fRc) {
            psxCond_Signal(this->pFull);
        }
        psxMutex_Unlock(this->pMutex);

        return fRc;
    }



    //---------------------------------------------------------------
    //                       R e s u m e
    //---------------------------------------------------------------
    
    bool            objCb_Resume(
        OBJCB_DATA      *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = psxMutex_Lock(this->pMutex);
        obj_FlagSet(this, OBJCB_FLAG_STOP, false);
        fRc = psxMutex_Unlock(this->pMutex);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    static
    bool			objCb_Validate(
        OBJCB_DATA       *this
    )
    {

        // Do initialization.

        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_OBJCB) )
                ;
            else
                return false;
        }
        else {
            DEBUG_BREAK();
            return false;
        }
        if( obj_getSize(this) >= sizeof(OBJCB_DATA) )
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




