// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   scanhex32.c
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


#include "cmn_defs.h"



//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************


 
/****************************************************************
* * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
****************************************************************/



/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/


//**********************************************************
//					S c a n H e x
//**********************************************************

bool            scanHex32(
	char			**ppCmdStr,         // NUL terminated string pointer
	uint32_t		*pScannedLen,       // (returned) Scanned Length
	uint32_t		*pValue             // (returned) Scanned Number
)
{
	bool            fRc = false;
	char			*pCurChr = NULL;
	uint32_t		cLen = 0;
	uint32_t		cHex = 0;
	uint32_t		value = 0;
    char            chr;

	// Do initialization.
	if( NULL == ppCmdStr ) {
		fRc = false;
		goto Exit00;
	}
	pCurChr = *ppCmdStr;

	// Scan off leading white-space.
    scanWhite( &pCurChr, &cLen );

	// Scan off each parameter.
	while( (chr = *pCurChr) && (cHex < 8) ) {
		// Handle Quoted Arguments.
		if( ('0' <= chr) && ('9' >= chr) ) {
            value = (value << 4) + (chr - '0');
            ++cHex;
        }
        else if( ('a' <= chr) && ('f' >= chr) ) {
            value = (value << 4) + (chr - 'a' + 10);
            ++cHex;
        }
        else if( ('A' <= chr) && ('F' >= chr) ) {
            value = (value << 4) + (chr - 'A' + 10);
            ++cHex;
        }
        else {
            break;
        }
        ++cLen;
        ++pCurChr;
	}


	// Return to caller.
    if( cHex ) {
        fRc = true;
    }
Exit00:
	if( ppCmdStr ) {
		*ppCmdStr = pCurChr;
	}
	if( pScannedLen ) {
		*pScannedLen = cLen;
	}
	if( pValue ) {
		*pValue = value;
	}
	return( fRc );
}








