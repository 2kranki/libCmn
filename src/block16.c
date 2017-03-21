// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        Data Block (block) Support Subroutines
//****************************************************************

/*
 * Program
 *              Data block (block) Subroutines
 * Purpose
 *              See block.H for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See block.H for the history.
 * References
 *              See block.H for the references.
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



/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include "block16_internal.h"



/****************************************************************
* * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
****************************************************************/



/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/



//----------------------------------------------------------
//                    A d d D a t a
//----------------------------------------------------------

bool			block16_AddData(
    BLOCK16_DATA		*cbp,
    uint16_t        size,
    void            *data
)
{
    void            *blockData;

	/* Validate the input parameters.
	 */
#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
	if( size > block16_UnusedDataSize(cbp) )
		return( false );
#endif

    blockData = block16_UnusedDataPtr( cbp );
    if (blockData == NULL )
        return( false );
    memmove( blockData, data, size );
    cbp->dataUsed += size;
    
	// Return to caller.
	return( true );
}



//**********************************************************
//                C a l c B l o c k S i z e
//**********************************************************

// Given the data size, block16_blockSize returns the size of
// the block that will be acquired.
uint16_t		block16_CalcBlockSize(
    uint16_t        headerSize,
    uint16_t        dataSize
)
{
    uint32_t        cbSize;

	// Do initialization.
    cbSize  = ROUNDUP_WORD(sizeof(BLOCK16_DATA));
    cbSize += ROUNDUP_WORD(headerSize);
    cbSize += ROUNDUP_WORD(dataSize);

    if( cbSize > (64 * 1024) )
        cbSize = 0;                 // TOO Big!
    
	// Return to caller.
	return( cbSize );
}



/**********************************************************
                        Close
 **********************************************************/

BLOCK16_DATA *    block16_Close(
    BLOCK16_DATA      *cbp
)
{
    
	// Do initialization.
    
	// Free the main control block.
	if( cbp == NULL )
        return NULL;
    
    mem_Free( cbp );
    cbp = NULL;
    
	// Return to caller.
	return( cbp );
}



/**********************************************************
                            Copy
 **********************************************************/

BLOCK16_DATA *	block16_Copy(
    BLOCK16_DATA		*cbp
)
{
    BLOCK16_DATA      *pNew;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif

    pNew = block16_Open( cbp->headerSize, cbp->dataSize );
    if( pNew == NULL )
        return NULL;

    // Move in the header.
    if( cbp->headerSize ) {
        block16_HeaderPut( pNew, &cbp->header[0] );
    }

	// Move in the data.
	if( cbp->dataUsed ) {
        block16_AddData( pNew, cbp->dataUsed, block16_DataPtr(cbp) );
    }

	// Return to caller.
	return( pNew );
}




/**********************************************************
                   D a t a  O f f s e t
 **********************************************************/

uint32_t        block16_DataOffset(
    BLOCK16_DATA      *this
)
{
    uint32_t        offset = 0;
    
    offset = this->headerSize;
    
    return( offset );
}



/**********************************************************
                    D a t a P t r
 **********************************************************/

void *          block16_DataPtr(
    BLOCK16_DATA      *this
)
{
    void                 *ptr;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !block16_Validate( this ) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif

    ptr = &this->header[block16_DataOffset(this)];

	// Return to caller.
	return( ptr );
}



//----------------------------------------------------------
//                     D a t a  S i z e
//----------------------------------------------------------

uint16_t        block16_DataSize(
    BLOCK16_DATA      *cbp
)
{

#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

    return( cbp->dataSize );
}



//----------------------------------------------------------
//                     D a t a  U s e d
//----------------------------------------------------------

uint16_t        block16_DataUsed(
    BLOCK16_DATA      *cbp
)
{
    
#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
    return( cbp->dataUsed );
}



//----------------------------------------------------------
//                   D a t a  U s e  A l l
//----------------------------------------------------------

bool            block16_DataUseAll(
    BLOCK16_DATA      *cbp
)
{
    
#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    cbp->dataUsed = cbp->dataSize;
    
    return true;
}



/**********************************************************
                    H e a d e r G e t
 **********************************************************/

bool			block16_HeaderGet(
    BLOCK16_DATA	*cbp,
    void            *pHeader
)
{
    void            *blockData;

	/* Validate the input parameters.
	 */
#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif

    blockData = block16_UnusedDataPtr( cbp );
    if (blockData == NULL )
        return( false );
    memmove( pHeader, &cbp->header[0], cbp->headerSize );

	// Return to caller.
	return( true );
}



/**********************************************************
                H e a d e r O f f s e t
 **********************************************************/

uint16_t        block16_HeaderOffset(
    void
)
{
    uint32_t        offset;
   
    offset = (size_t)((char *)&(((struct block16_data_s*)0)->header)-(char *)0);
    
    return( offset );
}



/**********************************************************
                    H e a d e r P t r
 **********************************************************/

void *          block16_HeaderPtr(
    BLOCK16_DATA      *cbp
)
{
    void                 *ptr;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif

    ptr = &cbp->header[0];

	// Return to caller.
	return( ptr );
}



/**********************************************************
                    H e a d e r P u t
 **********************************************************/

bool			block16_HeaderPut(
    BLOCK16_DATA		*cbp,
    void            *pHeader
)
{
    void            *blockData;

	/* Validate the input parameters.
	 */
#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif

    blockData = block16_UnusedDataPtr( cbp );
    if (blockData == NULL )
        return( false );
    memmove( &cbp->header[0], pHeader, cbp->headerSize );

	// Return to caller.
	return( true );
}



//----------------------------------------------------------
//                    H e a d e r S i z e
//----------------------------------------------------------

uint16_t        block16_HeaderSize(
    BLOCK16_DATA      *cbp
)
{

#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

    return( cbp->headerSize );
}



//----------------------------------------------------------
//                        I n i t
//----------------------------------------------------------

bool			block16_Init(
    BLOCK16_DATA	*cbp,
    uint16_t        headerSize,
    uint16_t        dataSize
)
{
	uint16_t		cbSize;
    
	// Allocate the control block.
	cbSize = block16_CalcBlockSize( headerSize, dataSize );
    if( cbSize == 0 )
        return false;
    if (cbp) {
        memset( cbp, 0, cbSize );
        cbp->cbSize = cbSize;
        cbp->headerSize = ROUNDUP_WORD(headerSize);
        cbp->dataSize = ROUNDUP_WORD(dataSize);
        BREAK_NOT_BOUNDARY4(cbp->header);
    }
    
	// Return to caller.
	return( true );
}



//----------------------------------------------------------
//                        O p e n
//----------------------------------------------------------

BLOCK16_DATA *	block16_Open(
    uint16_t        headerSize,
    uint16_t        dataSize
)
{
	uint16_t		cbSize;
    BLOCK16_DATA      *cbp = NULL;
    
	// Allocate the control block.
	cbSize = block16_CalcBlockSize( headerSize, dataSize );
    if( cbSize == 0 )
        return NULL;
	cbp = (BLOCK16_DATA *)mem_Malloc( cbSize );
	if( cbp == NULL )
		return( cbp );
    block16_Init( cbp, headerSize, dataSize );
    
	// Return to caller.
	return( cbp );
}



//----------------------------------------------------------
//                U n u s e d D a t a S i z e
//----------------------------------------------------------

uint16_t        block16_UnusedDataSize(
    BLOCK16_DATA      *cbp
)
{
    uint32_t            unused;

#ifdef NDEBUG
#else
    if( !block16_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

    unused = cbp->dataSize - cbp->dataUsed;
    return( unused );
}




//----------------------------------------------------------
//                 U n u s e d D a t a P t r
//----------------------------------------------------------

void *          block16_UnusedDataPtr(
    BLOCK16_DATA      *this
)
{
    void                 *ptr;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !block16_Validate(this) ) {
        DEBUG_BREAK();
        return NULL;
    }
#endif

    ptr = &this->header[block16_DataOffset(this) + this->dataUsed];

	// Return to caller.
	return( ptr );
}




//----------------------------------------------------------
//                      Validate
//----------------------------------------------------------

#ifdef NDEBUG
#else
bool            block16_Validate(
    BLOCK16_DATA      *cbp
)
{
	if( cbp->dataUsed <= cbp->dataSize )
		;
	else
		return(false);
    return( true );
}
#endif





