// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   con.c
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

 
#include        "con_internal.h"
#include        <stdarg.h>
#include        <stdio.h>
#include        "hex.h"


//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************

static
CON_DATA        *con = NULL;

 
/****************************************************************
* * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
****************************************************************/

#ifdef NDEBUG
#else
bool			con_Validate(
    CON_DATA        *cbp
);
#endif


#define CON_FLAG_OFF(cbp,x) cbp->flags &= ~x
#define CON_FLAG_ON(cbp,x)  cbp->flags |= x




//---------------------------------------------------------------
//                      STDIO Overrides
//---------------------------------------------------------------

int             _mon_getc(
    int             canblock    // Non-zero == block
)
{
    uint32_t        charIn = 0;

    if( con == NULL )
        ;
    else {
        charIn = con_In( con, canblock );
    }

    return (int)charIn;
}


void            _mon_putc(
    char            charOut
)
{
    if( con == NULL )
        ;
    else {
        con_Out( con, charOut );
    }
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

CON_DATA *      con_Alloc(
    uint16_t        size
)
{
    CON_DATA        *cbp;
    uint32_t        cbSize = sizeof(CON_DATA);
    
    // Do initialization.
    
    cbSize += size * sizeof(char);
    if ((64 * 1024) <= cbSize) {
        return NULL;
    }
    
    cbp = obj_Alloc( cbSize );
    obj_setMisc1(cbp, (size * sizeof(char)));
    
    // Return to caller.
    return( cbp );
}



//---------------------------------------------------------------
//                        N e w
//---------------------------------------------------------------

CON_DATA *      con_New(
    uint16_t        size
)
{
    CON_DATA        *this;
    
    this = con_Alloc( size );
    if (this) {
        this = con_Init(this);
    }
    
    // Return to caller.
    return this;
}





//===============================================================
//                    P r o p e r t i e s
//===============================================================

bool            con_getAddCR2SingletonLF(
	CON_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

	// Return to caller.
	return obj_IsFlag(cbp,CON_FLAG_ADDCR2LF);
}

void            con_setAddCR2SingletonLF(
	CON_DATA        *cbp,
    bool            data
)
{
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    obj_FlagSet( cbp, CON_FLAG_ADDCR2LF, data);

}



bool            con_getAddLF2CR(
	CON_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

	// Return to caller.
	return obj_IsFlag(cbp,CON_FLAG_ADDLF2CR);
}

void            con_setAddLF2CR(
	CON_DATA        *cbp,
    bool            data
)
{
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    obj_FlagSet( cbp, CON_FLAG_ADDLF2CR, data);

}



bool            con_getEcho(
	CON_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

	return obj_IsFlag(cbp,CON_FLAG_ECHO);
}

void            con_setEcho(
	CON_DATA        *cbp,
    bool            data
)
{
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    obj_FlagSet( cbp, CON_FLAG_ECHO, data);

}



CHARIO_DATA *   con_getCharIO(
	CON_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

	// Return to caller.
	return( cbp->pCharIO );
}

void            con_setCharIO(
	CON_DATA        *cbp,
    CHARIO_DATA     *pCharIO
)
{
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    cbp->pCharIO = pCharIO;
}



bool            con_getUseXonXoff(
	CON_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

	// Return to caller.
	return obj_IsFlag(cbp,CON_FLAG_USEXONXOFF);
}

void            con_setUseXonXoff(
	CON_DATA        *cbp,
    bool            data
)
{
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    obj_FlagSet( cbp, CON_FLAG_USEXONXOFF, data);

}





//===============================================================
//                    M e t h o d s
//===============================================================


//**********************************************************
//                        D e a l l o c
//**********************************************************/

void            con_Dealloc(
    OBJ_ID          pObj
)
{
    CON_DATA        *this = pObj;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate(this) ) {
        DEBUG_BREAK();
        return;
    }
#endif
    
    if (this->pHex) {
        obj_Release(this->pHex);
        this->pHex = OBJ_NIL;
    }
    
    if (this->pMutex) {
        obj_Release(this->pMutex);
        this->pMutex = OBJ_NIL;
    }
    
    obj_setVtbl(this, this->pSuperVtbl);
    obj_Dealloc(this);
    this = OBJ_NIL;
    
	// Return to caller.
}



//**********************************************************
//                        C l o s e
//**********************************************************/

CON_DATA *      con_Close(
	CON_DATA        *this
)
{

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate(this) ) {
        DEBUG_BREAK();
    }
#endif

	// Free the main control block.
    if (this) {
		mem_Free(this);
		this = NULL;
    }

	// Return to caller.
	return(this);
}



//**********************************************************
//                          I n
//**********************************************************

char            con_In(
	CON_DATA        *cbp,
    uint32_t        timeout
)
{
    bool            fRc = true;
    int32_t         charIn = ASCII_NUL;
    char            chr;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

getChar:
    fRc =   cbp->pCharIO->GetRxChar( 
                    cbp->pCharIO->pObjectRx,
                    &charIn, 
                    timeout 
            );
    if( fRc ) {
        chr = charIn & 0x7F;
        if( obj_IsFlag(cbp,CON_FLAG_USEXONXOFF) && (ASCII_XOFF == chr)) {
            obj_FlagSet(cbp,CON_FLAG_XON, true );
            goto getChar;
        }
    }
    else
        chr = ASCII_NUL;
    if( chr && obj_IsFlag(cbp,CON_FLAG_ECHO) ) {
        con_Out( cbp, chr );
    }

    return chr;
}



/**********************************************************
					I n  C  S t r i n g
 **********************************************************/

bool            con_InCString(
	CON_DATA        *cbp,
    uint16_t        cBufLen,
    uint16_t        *cLen,
    char            *pBuf,
    uint32_t        timeout
)
{
    bool            fRc = true;
    char            *pString;
    uint16_t        idxCur = 0;
    char            charIn;
    bool            fDone = false;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
    if( NULL == pBuf ) {
        DEBUG_BREAK();
        return false;
    }
    if( 0 == cBufLen ) {
        DEBUG_BREAK();
    }
#endif

    pString = pBuf;
    if( cLen )
        *cLen = 0;

    con_Lock( cbp );
    while( !fDone ) {
        if( idxCur == (cBufLen - 1) )
            break;
        charIn = con_In( cbp, timeout );
        switch( charIn ) {
            case ASCII_CTRL_A:
                while( idxCur-- ) {
                    con_Out( cbp, ASCII_BS );
                    con_Out( cbp, ' ' );
                    con_Out( cbp, ASCII_BS );
                }
                pString = pBuf;
                break;
            case ASCII_BS:
            case ASCII_DEL:
                if( idxCur > 0 ) {
                    --idxCur;
                    con_Out( cbp, ASCII_BS );
                    con_Out( cbp, ' ' );
                    con_Out( cbp, ASCII_BS );
                }
                break;
            case ASCII_CR:
                con_OutCrLf( cbp );
                fDone = true;
                break;
            default:
                if( (charIn >= ' ') && (charIn < ASCII_DEL)) {
                    pString[idxCur++] = charIn;
                }
                break;
        }
    }
    con_Unlock( cbp );
    pString[idxCur] = '\0';
    if( cLen )
        *cLen = idxCur;

#ifdef NDEBUG
#else
    if ( !(0 == pBuf[idxCur])  ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    return( fRc );
}



//**********************************************************
//                       I n i t
//**********************************************************

CON_DATA *      con_Init(
    CON_DATA		*this
)
{
    uint16_t        cbSize = sizeof(CON_DATA);
    
    if (NULL == this) {
        return NULL;
    }

    // Must be less than 2^15 because of numWritten and numRead.
    if ( !(obj_getMisc1(this) < 0x7FFF) ) {
        return NULL;
    }
    cbSize += obj_getMisc1(this);
    
    this = obj_Init( this, cbSize, OBJ_IDENT_CON );
    if (NULL == this) {
        return NULL;
    }
    this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
    obj_setVtbl(this, (OBJ_IUNKNOWN *)&con_Vtbl);
    
    this->max = obj_getMisc1(this);
#ifdef NDEBUG
#else
    int i = offsetof(CON_DATA, max);
    if ( i & 3 ) {
        DEBUG_BREAK();
    }
#endif
    
    obj_FlagSet(this,CON_FLAG_ADDCR2LF,true);

    this->pMutex = psxMutex_New();
    this->pHex = hex_New();
    
    return this;
}



/**********************************************************
                        L o c k
 **********************************************************/

bool			con_Lock(
	CON_DATA        *this
)
{
    bool			fRc = true;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate(this) ) {
        DEBUG_BREAK();
    }
#endif

    fRc = psxMutex_Lock(this->pMutex);

	// Return to caller.
	return( fRc );
}



/**********************************************************
						O u t
 **********************************************************/

bool            con_Out(
	CON_DATA        *cbp,
    uint8_t         value
)
{
    bool            fRc = true;
    uint16_t        charIn;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    while( obj_IsFlag(cbp,CON_FLAG_XON) ) {
        charIn = con_In( cbp, true );
        if( charIn == ASCII_XON ) {
            obj_FlagSet(cbp,CON_FLAG_XON, false );
            break;
        }
    }

    value &= 0x7F;
    if( (value == ASCII_LF) 
            && obj_IsFlag(cbp,CON_FLAG_ADDCR2LF)
            && !(cbp->lastChar == ASCII_CR)) {
        fRc =   cbp->pCharIO->PutTxChar( 
                        cbp->pCharIO->pObjectTx,
                        ASCII_CR,
                        WAIT_INFINITE
                );
    }

    fRc =   cbp->pCharIO->PutTxChar( 
                    cbp->pCharIO->pObjectTx,
                    value,
                    WAIT_INFINITE
            );
    cbp->lastChar = value;

    if( obj_IsFlag(cbp,CON_FLAG_ADDLF2CR) && (value == ASCII_CR) ) {
        fRc =   cbp->pCharIO->PutTxChar( 
                        cbp->pCharIO->pObjectTx,
                        ASCII_LF,
                        WAIT_INFINITE
                );
    }

    return fRc;
}


void            con_OutCrLf(
	CON_DATA        *cbp
)
{
    bool            fRc;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    fRc = con_Out( cbp, ASCII_CR );
    if( !obj_IsFlag(cbp,CON_FLAG_ADDLF2CR) )
        fRc = con_Out( cbp, ASCII_LF );

}


void            con_OutLfOffset(
	CON_DATA        *cbp,
    uint32_t        value
)
{
    uint32_t        i;
    bool            fRc;

#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    fRc = con_Out( cbp, ASCII_LF );
    for( i=0; i<value; ++i ) {
        fRc = con_Out( cbp, ' ' );
    }

}


void            con_OutOffset(
    CON_DATA        *cbp,
    uint32_t        value
)
{
    uint32_t        i;
    bool            fRc;
    
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif
    
    for( i=0; i<value; ++i ) {
        fRc = con_Out( cbp, ' ' );
    }
    
}



/**********************************************************
					O u t  C  S t r i n g
 **********************************************************/

void            con_OutCString(
	CON_DATA        *cbp,
    uint16_t        cLen,
    const
    char            *pString
)
{
    bool            fRc = true;
    char            chr;
    char            prevchr = 0;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
    if( NULL == pString ) {
        DEBUG_BREAK();
        return;
    }
#endif
    if( 0 == cLen ) {
        cLen = 128;         // Set maximum.
    }

    while( *pString && cLen-- ) {
        chr = *pString;
        if( (chr == '\n') && !(prevchr == '\r') ) {
            fRc = con_Out( cbp, '\r' );
        }
        fRc = con_Out( cbp, chr );
        prevchr = chr;
        ++pString;
    }

}



//**********************************************************
//                         P u t s
//**********************************************************

void            con_Puts(
	CON_DATA        *cbp,
    const
    char            *pString
)
{

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif

    con_OutCString( cbp, 128, pString );
    con_OutCrLf( cbp );

}



//**********************************************************
//                   P u t s D e c 3 2
//**********************************************************

void            con_PutsDec32(
    CON_DATA        *cbp,
    uint16_t        offset,
    const
    char            *pString,
    uint32_t        num
)
{
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif
    con_OutOffset( cbp, offset );
    if (pString) {
        con_OutCString( cbp, 128, pString );
    }
    con_OutDec32( cbp, num );
    con_OutCrLf( cbp );
    
}



//**********************************************************
//                    P u t s H e x 1 6
//**********************************************************

void            con_PutsHex16(
    CON_DATA        *cbp,
    uint16_t        offset,
    const
    char            *pString,
    uint16_t        num
)
{
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif
    con_OutOffset( cbp, offset );
    if (pString) {
        con_OutCString( cbp, 128, pString );
    }
    con_OutHex16( cbp, num );
    con_OutCrLf( cbp );
    
}



//**********************************************************
//                    P u t s H e x 3 2
//**********************************************************

void            con_PutsHex32(
    CON_DATA        *cbp,
    uint16_t        offset,
    const
    char            *pString,
    uint32_t        num
)
{
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif
    con_OutOffset( cbp, offset );
    if (pString) {
        con_OutCString( cbp, 128, pString );
    }
    con_OutHex32( cbp, num );
    con_OutCrLf( cbp );
    
}



//**********************************************************
//                    P u t s S t r
//**********************************************************

void            con_PutsStr(
    CON_DATA        *cbp,
    uint16_t        offset,
    const
    char            *pString1,
    const
    char            *pString2
)
{
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
#endif
    con_OutOffset( cbp, offset );
    if (pString1) {
        con_OutCString( cbp, 128, pString1 );
    }
    if (pString2) {
        con_OutCString( cbp, 128, pString2 );
    }
    con_OutCrLf( cbp );
    
}



//**********************************************************
//              D e c i m a l  O u t p u t
//**********************************************************

void            con_OutDec16(
	CON_DATA        *cbp,
    uint16_t        data
)
{
    bool            fRc;

    if( data > 9 ) {
        con_OutDec16( cbp, (data / 10) );
    }
    fRc = con_Out( cbp, ((data % 10) + '0') );

}


void            con_OutDec32(
                             CON_DATA        *cbp,
                             uint32_t        data
                             )
{
    bool            fRc;
    
    if( data > 9 ) {
        con_OutDec32( cbp, (data / 10) );
    }
    fRc = con_Out( cbp, ((data % 10) + '0') );
    
}



//**********************************************************
//          H e x a d e c i m a l  O u t p u t
//**********************************************************

void            con_OutHex4(
	CON_DATA        *cbp,
    uint32_t        data
)
{
    static
    const
    char            hexchrs[16] = "0123456789ABCDEF";
    bool            fRc;

    fRc = con_Out( cbp, hexchrs[data & 0x0F] );

}


void            con_OutHex8(
	CON_DATA        *this,
    uint32_t        data
)
{

    hex_putU8Obj(this->pHex, data, this, (void *)con_Out);

}


void            con_OutHex16(
	CON_DATA        *this,
    uint32_t        data
)
{

    hex_putU16Obj(this->pHex, data, this, (void *)con_Out);

}


void            con_OutHex32(
	CON_DATA        *this,
    uint32_t        data
)
{

    hex_putU32Obj(this->pHex, data, this, (void *)con_Out);

}


void            con_OutHex64(
	CON_DATA        *this,
    uint64_t        data
)
{

    hex_putU64Obj(this->pHex, data, this, (void *)con_Out);

}



//**************************************************************
//						con_OutBytes16
//**************************************************************

void            con_OutBytes16_32(
	CON_DATA        *this,
    const
    uint32_t        offset,
    uint16_t        cLen,
    const
	void            *pData
)
{

	// Do initialization.
    if( 0 == cLen ) {
        return;
    }
    if( NULL == pData ) {
        return;
    }

    for (;;) {
        hex_put16BytesObj_32(this->pHex, offset, cLen, pData, this, (void *)con_Out);
        if (cLen <= 16) {
            break;
        }
        cLen -= 16;
        pData += 16;
    }

    // Return to caller.
}



/**********************************************************
                    P r i n t f
 **********************************************************/

bool            con_Printf(
	CON_DATA        *this,
    const
	char			*pFormat,
	...
)
{
    bool            fRc = true;
    char            buffer[120];
	va_list			ArgPtr;
	uint32_t		i;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate(this) ) {
        DEBUG_BREAK();
    }
#endif
    con_Lock(this);

    va_start( ArgPtr, pFormat );
    i = vsprintf( buffer, pFormat, ArgPtr );
    va_end( ArgPtr );
    buffer[i] = '\0';   // Insure trailing NUL;

    con_OutCString( this, i, buffer );

    con_Unlock(this);
    return fRc;
}



/**********************************************************
                        U n l o c k
 **********************************************************/

bool			con_Unlock(
	CON_DATA        *this
)
{
    bool			fRc = true;

	// Do initialization.
#ifdef NDEBUG
#else
    if( !con_Validate(this) ) {
        DEBUG_BREAK();
    }
#endif

    fRc = psxMutex_Unlock(this->pMutex);

	// Return to caller.
	return( fRc );
}



/**********************************************************
                        V a l i d a t e
 **********************************************************/

#ifdef NDEBUG
#else
bool			con_Validate(
	CON_DATA        *this
)
{

	// Do initialization.
    this->eRc = ERESULT_INVALID_OBJECT;
    if(this) {
        if ( this->super.pVtbl->pIsKindOf(OBJ_IDENT_CON) )
            ;
        else
            return false;
    }
    else
        return false;
    if( !(obj_getSize(this) >= sizeof(CON_DATA)) )
        return false;
    

	// Return to caller.
    this->eRc = ERESULT_SUCCESS;
	return true;
}
#endif






