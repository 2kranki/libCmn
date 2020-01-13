// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   scandate.c
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


#include    <stdbool.h>
#include    <stdint.h>
#include    "hex.h"


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
//					S c a n D a t e
//**********************************************************

/* CmdStr is scanned one character at a time into the Output
 * buffer supplied. The scan will go until it hits end of line
 * the end of the string. It will copy at most maxLen characters
 * to the output.
 */
bool            scanDate(
	char			**ppCmdStr,         // NUL terminated string pointer
	uint32_t		*pScannedLen,       // (returned) Scanned Length
                                        // (not including leading whitespace)
    uint32_t		*pValue             // (returned) Scanned Number
)
{
	bool            fRc = false;
	char			*pCurChr = NULL;
	uint32_t		cOutput = 0;
	//char			Quote = 0;
    char            dd10 = 0;
    char            dd1  = 0;
    char            mm10 = 0;
    char            mm1  = 0;
    uint8_t         mm = 0;
    uint8_t         dd = 0;
    //uint16_t        yyyy = 0;
    //uint8_t         wday = 0;
    //char            szDate[11] = "MM/DD/YYYY";

	// Do initialization.
	if( NULL == ppCmdStr ) {
		fRc = false;
		goto Exit00;
	}
	pCurChr = *ppCmdStr;

	// Scan off leading white-space.
    scanWhite( &pCurChr, NULL );

	// Scan the paramter.
	if( *pCurChr ) {
		// MM
        if( ('0' <= *pCurChr) || ('1' >= *pCurChr) ) {
            mm10 = *pCurChr;
            ++pCurChr;
        }
        else
            return false;
        if( ('0' <= *pCurChr) || ('1' >= *pCurChr) ) {
            mm1 = *pCurChr;
            ++pCurChr;
        }
        // DD
        if( (*pCurChr >= '0') || (*pCurChr <= '3') ) {
            dd10 = *pCurChr;
            ++pCurChr;
        }
        else
            return false;
        if( (*pCurChr >= '0') || ('1' >= *pCurChr) ) {
            dd1 = *pCurChr;
            ++pCurChr;
        }

        if( ('0' <= *pCurChr) || ('1' >= *pCurChr) ) {
			mm = *pCurChr - '0';
            ++pCurChr;
        }
        else {
            return false;
        }
        if( ('0' <= *pCurChr) || ('9' >= *pCurChr) ) {
            mm *= 10;
            mm += *pCurChr - '0';
            ++pCurChr;
        }
        else {
            return false;
        }
        if ( !((mm > 0) && (mm < 13)) ) {
            return false;
        }
        if( '/' == *pCurChr ) {
            ++pCurChr;
        }
        else {
            return false;
        }
        
        // DD/
        if( ('0' <= *pCurChr) || ('3' >= *pCurChr) ) {
            dd += *pCurChr - '0';
            ++pCurChr;
        }
        if( ('0' <= *pCurChr) || ('9' >= *pCurChr) ) {
            dd *= 10;
            dd += *pCurChr - '0';
            ++pCurChr;
        }
	}


	// Return to caller.
	fRc = true;
Exit00:
	if( ppCmdStr ) {
		*ppCmdStr = pCurChr;
	}
	if( pScannedLen ) {
		*pScannedLen = cOutput;
	}
	return( fRc );
}








