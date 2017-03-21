// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   cb8.c
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


#include "cb8_internal.h"


 
/****************************************************************
* * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
****************************************************************/

#ifdef NDEBUG
#else
bool			cb8_Validate(
    CB8_DATA       *cbp
);
#endif



/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/


//===============================================================
//                    P r o p e r t i e s
//===============================================================

uint16_t        cb8_getSize(
	CB8_DATA       *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cb8_Validate( cbp ) ) {
        DEBUG_BREAK();
        return -1;
    }
#endif

	// Return to caller.
	return( cbp->size );
}




//===============================================================
//                    M e t h o d s
//===============================================================


/**********************************************************
                        C l o s e
 **********************************************************/

CB8_DATA *     cb8_Close(
	CB8_DATA		*cbp
)
{

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb8_Validate(cbp) ) {
        DEBUG_BREAK();
        return cbp;
    }
#endif

	// Free the main control block.
    if ( cbp ) {
		mem_Free(cbp);
		cbp = NULL;
    }

	// Return to caller.
	return( cbp );
}



//**********************************************************
//                        C o u n t
//**********************************************************

uint16_t        cb8_Count(
    CB8_DATA       *cbp
)
{
    uint16_t        count;
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cb8_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
    count = (uint16_t)(cbp->numWritten - cbp->numRead);
    
	// Return to caller.
	return( count );
}



/**********************************************************
							G e t
 **********************************************************/

bool            cb8_Get(
	CB8_DATA       *cbp,
    uint8_t        *data
)
{
    bool            fRc = true;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb8_Validate(cbp) ) {
        DEBUG_BREAK();
        return cbp;
    }
#endif
    
    if ( (data == NULL) || cb8_IsEmpty(cbp) ) {
        fRc = false;
    }
    else {
        *data = cbp->elems[cbp->start];
        //__sync_fetch_and_add( &cbp->numRead, 1 ); // needed if multi-processor
		++cbp->numRead;
        ++cbp->start;
        if (cbp->start == cbp->size) {
            cbp->start = 0;
        }
    }
    
    return fRc;
}

 

//**********************************************************
//                       I s E m p t y
//**********************************************************

bool            cb8_IsEmpty(
	CB8_DATA       *cbp
)
{
    bool            fRc = false;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb8_Validate(cbp) ) {
        DEBUG_BREAK();
        return cbp;
    }
#endif

    if (((uint16_t)(cbp->numWritten - cbp->numRead)) == 0)
		fRc = true;
    
    return fRc;
}


 
//**********************************************************
//                       I s F u l l
//**********************************************************

bool            cb8_IsFull(
	CB8_DATA       *cbp
)
{
    bool            fRc = false;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb8_Validate(cbp) ) {
        DEBUG_BREAK();
        return cbp;
    }
#endif

    if ( ((uint16_t)(cbp->numWritten - cbp->numRead)) == cbp->size )
        fRc = true;
    
    return fRc;
}



//**********************************************************
//                       O p e n
//**********************************************************

CB8_DATA *     cb8_Open(
    uint16_t        size            // Size of Buffer in uint32_t's
)
{
	CB8_DATA		*cbp;
    uint32_t        cbSize;

    if( 0 == size )
        return NULL;

    // Must be less than 2^31 because of numWritten and numRead.
    if ( !(size < 0x7FFF) ) {
        return NULL;
    }
    
	cbSize = size * sizeof(uint8_t);
    cbSize += sizeof(CB8_DATA);
    cbSize = ROUNDUP4(cbSize);
    if (cbSize >= (64 * 1024)) {
        return NULL;
    }
    
    cbp = (CB8_DATA *)mem_Malloc( cbSize );
    if (cbp) {
        memset( cbp, 0, cbSize );
		cbp->cbSize = cbSize;
		cbp->identifier = CB8_IDENTIFIER;
        cbp->size  = size;
    }
    
    return cbp;
}

 

/**********************************************************
							P u t
 **********************************************************/

bool            cb8_Put(
	CB8_DATA       *cbp,
    uint8_t        value
)
{
    bool            fRc = true;

	// Do initialization.
#ifdef NDEBUG
#else
    if ( !cb8_Validate(cbp) ) {
        DEBUG_BREAK();
        return cbp;
    }
#endif

    if ( cb8_IsFull(cbp) ) {
        fRc = false;
    }
    else {
        cbp->elems[cbp->end] = value;
		++cbp->numWritten;
        ++cbp->end;
        if (cbp->end == cbp->size) {
            cbp->end = 0;
        }
    }

    return fRc;
}



/**********************************************************
                        V a l i d a t e
 **********************************************************/

#ifdef NDEBUG
#else
bool			cb8_Validate(
	CB8_DATA       *cbp
)
{
    bool			fRc = true;
    uint16_t        cbSize;

	// Do initialization.

	if( cbp && (cbp->identifier == CB8_IDENTIFIER) ) {
        cbSize = cbp->size * sizeof(uint8_t);
        cbSize += sizeof(CB8_DATA);
        cbSize = ROUNDUP4(cbSize);
        if( cbp->cbSize == cbSize )
            ;
        else {
            DEBUG_BREAK();
            fRc = false;
        }
    }
	else {
        DEBUG_BREAK();
		fRc = false;
    }

	// Return to caller.
	return( fRc );
}
#endif






