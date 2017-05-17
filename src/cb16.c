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
    CB16_DATA       *cbp;
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
    
    cbp = obj_Alloc( cbSize );
    
    // Return to caller.
    return( cbp );
}





//===============================================================
//                    P r o p e r t i e s
//===============================================================

uint16_t        cb16_getSize(
	CB16_DATA       *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cb16_Validate( cbp ) )
        return -1;
#endif

	// Return to caller.
	return( cbp->size );
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
	CB16_DATA		*cbp = objId;
#ifdef __PIC32MX_TNEO_ENV__
    enum TN_RCode   tRc;
#endif

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(cbp) ) {
        DEBUG_BREAK();
        return;
    }
#endif

#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_delete(&cbp->semEmpty);
    tRc = tn_sem_delete(&cbp->semFull);
#endif
    
    obj_Dealloc(cbp);
    cbp = NULL;
    
	// Return to caller.
}



//----------------------------------------------------------------
//                              G e t
//----------------------------------------------------------------

bool            cb16_Get(
	CB16_DATA       *cbp,
    uint16_t        *pData,
    uint32_t        timeout
)
{
#ifdef __PIC32MX_TNEO_ENV__
    enum TN_RCode   tRc;
#endif
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(cbp) ) {
        return false;
    }
#endif
    
#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_wait(&cbp->semFull, timeout);
    if (TN_RC_OK == tRc)
        ;
    else {
        return false;
    }
#endif
    
    if (pData) {
        *pData = cbp->elems[cbp->start];
    }
    ++cbp->numRead;
    ++cbp->start;
    if (cbp->start == cbp->size) {
        cbp->start = 0;
    }
    
#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_signal(&cbp->semEmpty);
#endif
    
    return true;
}

 

bool            cb16_iGet(
    CB16_DATA       *cbp,
    uint16_t        *pData
)
{
#ifdef __PIC32MX_TNEO_ENV__
    enum TN_RCode   tRc;
#endif
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(cbp) ) {
        return false;
    }
#endif
    
#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_iwait_polling(&cbp->semFull);
    if (TN_RC_OK == tRc)
        ;
    else {
        return false;
    }
#endif
    
    if (pData) {
        *pData = cbp->elems[cbp->start];
    }
    ++cbp->numRead;
    ++cbp->start;
    if (cbp->start == cbp->size) {
        cbp->start = 0;
    }
    
#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_isignal(&cbp->semEmpty);
#endif
    
    return true;
}



//**********************************************************
//                       I s E m p t y
//**********************************************************

bool            cb16_IsEmpty(
	CB16_DATA       *cbp
)
{
    bool            fRc = false;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(cbp) ) {
        return cbp;
    }
#endif

    if (((uint32_t)(cbp->numWritten - cbp->numRead)) == 0)
		fRc = true;
    
    return fRc;
}


 
//**********************************************************
//                       I s F u l l
//**********************************************************

bool            cb16_IsFull(
	CB16_DATA       *cbp
)
{
    bool            fRc = false;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(cbp) ) {
        return cbp;
    }
#endif

    if ( ((uint32_t)(cbp->numWritten - cbp->numRead)) == cbp->size )
        fRc = true;
    
    return fRc;
}



//**********************************************************
//                       I n i t
//**********************************************************

CB16_DATA *     cb16_Init(
    CB16_DATA		*this,
    uint16_t        size            // Size of Buffer in uint16_t's
)
{
    uint32_t        cbSize;
#ifdef __PIC32MX_TNEO_ENV__
    enum TN_RCode   tRc;
#endif

    if (NULL == this) {
        return NULL;
    }
    if( 0 == size )
        return NULL;

    // Must be less than 2^31 because of numWritten and numRead.
    if ( !(size < 0x7FFF) ) {
        return NULL;
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
#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_create(&this->semEmpty, size, size);
    tRc = tn_sem_create(&this->semFull, 0, size);
#endif
    
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
	CB16_DATA       *cbp,
    uint16_t        value,
    uint32_t        timeout
)
{
    bool            fRc = true;
#ifdef __PIC32MX_TNEO_ENV__
    enum TN_RCode   tRc;
#endif

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb16_Validate(cbp) ) {
        return false;
    }
#endif

#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_wait(&cbp->semEmpty, timeout);
    if (TN_RC_OK == tRc)
        ;
    else {
        return false;
    }
#endif
    
    cbp->elems[cbp->end] = value;
    ++cbp->numWritten;
    ++cbp->end;
    if (cbp->end == cbp->size) {
        cbp->end = 0;
    }

#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_signal(&cbp->semFull);
    if (TN_RC_OK == tRc)
        ;
    else {
        DEBUG_BREAK();
    }
#endif

    return fRc;
}

 
bool            cb16_iPut(
    CB16_DATA       *cbp,
    uint16_t        value
)
{
    bool            fRc = true;
#ifdef __PIC32MX_TNEO_ENV__
    enum TN_RCode   tRc;
#endif
    
#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_iwait_polling(&cbp->semEmpty);
    if (TN_RC_OK == tRc)
        ;
    else {
        return false;
    }
#endif

    cbp->elems[cbp->end] = value;
    ++cbp->numWritten;
    ++cbp->end;
    if (cbp->end == cbp->size) {
        cbp->end = 0;
    }

#ifdef __PIC32MX_TNEO_ENV__
    tRc = tn_sem_isignal(&cbp->semFull);
    if (TN_RC_OK == tRc)
        ;
    else {
        DEBUG_BREAK();
    }
#endif
    
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






