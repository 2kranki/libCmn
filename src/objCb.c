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




#include        "objCb_internal.h"

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
        OBJCB_DATA         *cbp
    );
#endif


#ifdef XYZZY
    static
    OBJ_ID          objCb_GetPtr(
        OBJCB_DATA      *cbp,
        uint16_t        index
    )
    {
        OBJ_ID         ptr;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objCb_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if( (index > 0) && (index <= cbp->cEntries) )
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        ptr = &cbp->entries[index];

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
        OBJCB_DATA      *cbp;
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
        if ((64 * 1024) <= cbSize) {
            return NULL;
        }
        
        cbp = obj_Alloc( cbSize );
        obj_setMisc1( cbp, size );
        
        // Return to caller.
        return( cbp );
    }



    OBJCB_DATA *       objCb_New(
        uint16_t        size            // Number of Elements in Buffer
    )
    {
        OBJCB_DATA      *cbp;
        
        cbp = objCb_Alloc( size );
        cbp = objCb_Init( cbp );
        
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                    P r o p e r t i e s
    //===============================================================

    uint16_t        objCb_getSize(
        OBJCB_DATA       *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objCb_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        // Return to caller.
        return( cbp->cEntries );
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
#ifdef __PIC32MX_ENV__
        INTERRUPT_STATUS;
#endif
        
        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if( !objCb_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
    #endif
        
        // We need to disable interrupts so that we have
        // uninterrupted access to both variables.
#ifdef __PIC32MX_ENV__
        DISABLE_INTERRUPTS();
#endif
        
        count = (uint16_t)(this->numWritten - this->numRead);
        
#ifdef __PIC32MX_ENV__
        RESTORE_INTERRUPTS;
#endif
        
        // Return to caller.
        return( count );
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void        objCb_Dealloc(
        OBJ_ID      objId
    )
    {
        OBJCB_DATA		*this = objId;
        uint32_t        i;
        OBJ_ID          pObj;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ( !objCb_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        for (i=0; i<this->cEntries; ++i) {
            pObj = this->entries[i];
            if (pObj) {
                obj_Release(pObj);
                this->entries[i] = OBJ_NIL;
            }
        }
        
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
        
        obj_Dealloc(this);
        this = NULL;
        
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
        
        psxSem_Wait(this->pSemFull);
        
        psxLock_Lock(this->pLock);
        
        if ( (ppData == NULL) || (((uint16_t)(this->numWritten - this->numRead)) == 0) ) {
        }
        else {
            *ppData = this->entries[this->start];
            this->entries[this->start] = OBJ_NIL;
            // below needed if multi-processor
            //__sync_fetch_and_add( &this->numRead, 1 );
            ++this->numRead;
            ++this->start;
            if (this->start == this->cEntries) {
                this->start = 0;
            }
            fRc = true;
        }
        
        psxLock_Unlock(this->pLock);
        
        psxSem_Post(this->pSemEmpty);
        
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
        uint16_t        size =  obj_getMisc1(this);


        // Do initialization.
        if (NULL == this) {
            return NULL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_OBJCB );
        if (NULL == this) {
            return NULL;
        }
        obj_setVtbl(this, &objCb_Vtbl);
        
        this->cEntries = size;
        
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
        
        return this;
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

        psxSem_Wait(this->pSemEmpty);
        
        psxLock_Lock(this->pLock);
        
        if ( ((uint16_t)(this->numWritten - this->numRead)) == this->cEntries ) {
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

        psxLock_Unlock(this->pLock);
        
        psxSem_Post(this->pSemFull);
        
        return fRc;
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




