// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   cb16.c
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


#include "cb16_internal.h"


 
/****************************************************************
* * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
****************************************************************/

#ifdef NDEBUG
#else
bool			cb16_Validate(
    CB16_DATA       *cbp
);
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

CB16_DATA *     cb16_Alloc(
    uint16_t        size           // Number of Elements in Buffer
)
{
    CB16_DATA       *this;
    uint32_t        cbSize;
    
    // Do initialization.
#ifdef NDEBUG
#else
    if (0 == size) {
        DEBUG_BREAK();
        return NULL;
    }
#endif
    
    cbSize = size * sizeof(uint16_t);
    cbSize += sizeof(CB16_DATA);
    if ((64 * 1024) <= cbSize) {
        return NULL;
    }
    
    this = obj_Alloc( cbSize );
    obj_setMisc1(this, size);
    
    // Return to caller.
    return this;
}



//---------------------------------------------------------------
//                        N e w
//---------------------------------------------------------------

CB16_DATA *     cb16_New(
    uint16_t        size           // Number of Elements in Buffer
)
{
    CB16_DATA       *this;
    
    // Do initialization.
#ifdef NDEBUG
#else
    if (0 == size) {
        DEBUG_BREAK();
        return NULL;
    }
#endif
    
    this = cb16_Alloc(size);
    if (this) {
        this = cb16_Init(this);
    }
    
    // Return to caller.
    return this;
}





//===============================================================
//                    P r o p e r t i e s
//===============================================================

uint16_t        cb16_getSize(
	CB16_DATA       *this
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cb16_Validate(this) )
        return -1;
#endif

	// Return to caller.
	return( this->size );
}




//================================================================
//                      M e t h o d s
//================================================================


//----------------------------------------------------------------
//                      D e a l l o c
//----------------------------------------------------------------

void            cb16_Dealloc(
	OBJ_ID          objId
)
{
	CB16_DATA		*this = objId;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(this) ) {
        DEBUG_BREAK();
        return;
    }
#endif

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



//----------------------------------------------------------------
//                              G e t
//----------------------------------------------------------------

bool            cb16_Get(
	CB16_DATA       *this,
    uint16_t        *pData,
    uint32_t        timeout
)
{
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(this) ) {
        return false;
    }
#endif
    
    psxSem_Wait(this->pSemFull);
    
    psxLock_Lock(this->pLock);
    
    if (pData) {
        *pData = this->elems[this->start];
    }
    ++this->numRead;
    ++this->start;
    if (this->start == this->size) {
        this->start = 0;
    }
    
    psxLock_Unlock(this->pLock);
    
    psxSem_Post(this->pSemEmpty);
    
    return true;
}

 

bool            cb16_iGet(
    CB16_DATA       *this,
    uint16_t        *pData
)
{
    bool            fRc;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(this) ) {
        return false;
    }
#endif
    
    fRc = psxSem_iTryWait(this->pSemFull);
    if (!fRc) {
        return fRc;
    }
    
    //psxLock_Lock(this->pLock);
    
    if (pData) {
        *pData = this->elems[this->start];
    }
    ++this->numRead;
    ++this->start;
    if (this->start == this->size) {
        this->start = 0;
    }
    
    //psxLock_Unlock(this->pLock);
    
    psxSem_iPost(this->pSemEmpty);
    
    return true;
}



//**********************************************************
//                       I s E m p t y
//**********************************************************

bool            cb16_IsEmpty(
	CB16_DATA       *this
)
{
    bool            fRc = false;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(this) ) {
        return false;
    }
#endif

    if (((uint32_t)(this->numWritten - this->numRead)) == 0)
		fRc = true;
    
    return fRc;
}


 
//**********************************************************
//                       I s F u l l
//**********************************************************

bool            cb16_IsFull(
	CB16_DATA       *this
)
{
    bool            fRc = false;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(this) ) {
        return false;
    }
#endif

    if ( ((uint32_t)(this->numWritten - this->numRead)) == this->size )
        fRc = true;
    
    return fRc;
}



//**********************************************************
//                       I n i t
//**********************************************************

CB16_DATA *     cb16_Init(
    CB16_DATA		*this
)
{
    uint32_t        cbSize;
    uint16_t        size;

    if (NULL == this) {
        return NULL;
    }

    size = obj_getMisc1(this);
    if( 0 == size ) {
        DEBUG_BREAK();
        obj_Release(this);
        return OBJ_NIL;
    }
    
	cbSize = size * sizeof(uint16_t);
    cbSize += sizeof(CB16_DATA);
    cbSize = ROUNDUP4(cbSize);
    if (cbSize >= (64 * 1024)) {
        return NULL;
    }
    
    this = obj_Init( this, cbSize, OBJ_IDENT_CB16 );
    if (NULL == this) {
        return NULL;
    }
    this->pSuperVtbl = obj_getVtbl(this);
    obj_setVtbl(this, (OBJ_IUNKNOWN *)&cb16_Vtbl);
    
    this->size = size;

    this->pSemEmpty = psxSem_New(size, size);
    if (OBJ_NIL == this->pSemEmpty) {
        DEBUG_BREAK();
        obj_Release(this);
        return OBJ_NIL;
    }
    this->pSemFull = psxSem_New(0, size);
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
    
#ifdef NDEBUG
#else
    if ( !cb16_Validate(this) ) {
        return this;
    }
#ifdef __PIC32MX_TNEO_ENV__
    BREAK_NOT_BOUNDARY4(&this->semEmpty);
    BREAK_NOT_BOUNDARY4(&this->semFull);
#endif
    BREAK_NOT_BOUNDARY4(&this->numWritten);
#endif
    
    return this;
}



//**********************************************************
//							P u t
//**********************************************************

bool            cb16_Put(
	CB16_DATA       *this,
    uint16_t        value,
    uint32_t        timeout
)
{
    bool            fRc = true;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(this) ) {
        return false;
    }
#endif

    psxSem_Wait(this->pSemEmpty);
    
    psxLock_Lock(this->pLock);
    
    this->elems[this->end] = value;
    ++this->numWritten;
    ++this->end;
    if (this->end == this->size) {
        this->end = 0;
    }

    psxLock_Unlock(this->pLock);
    
    psxSem_Post(this->pSemFull);
    
    return fRc;
}

 
bool            cb16_iPut(
    CB16_DATA       *this,
    uint16_t        value
)
{
    bool            fRc = true;
    
    psxSem_Wait(this->pSemEmpty);
    
    psxLock_Lock(this->pLock);
    
#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_iwait_polling(&this->semEmpty);
    if (TN_RC_OK == tRc)
        ;
    else {
        return false;
    }
#endif

    this->elems[this->end] = value;
    ++this->numWritten;
    ++this->end;
    if (this->end == this->size) {
        this->end = 0;
    }

#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_isignal(&cbp->semFull);
    if (TN_RC_OK == tRc)
        ;
    else {
        DEBUG_BREAK();
    }
#endif
    
    psxLock_Unlock(this->pLock);
    
    psxSem_Post(this->pSemFull);
    
    return fRc;
}



//**********************************************************
//                        V a l i d a t e
//**********************************************************

#ifdef NDEBUG
#else
bool			cb16_Validate(
	CB16_DATA       *cbp
)
{

	// Do initialization.

    if( cbp ) {
        if ( obj_IsKindOf(cbp,OBJ_IDENT_CB16) )
            ;
        else
            return false;
    }
    else
        return false;
    if( !(obj_getSize(cbp) >= sizeof(CB16_DATA)) )
        return false;

	// Return to caller.
	return true;
}
#endif






