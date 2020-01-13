// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   scanstring.c
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
//					S c a n S t r i n g
//**********************************************************

/* CmdStr is scanned one character at a time into the Output
 * buffer supplied. The scan will go until it hits end of line or
 * the end of the string. It will copy at most maxLen characters
 * to the output.
 */
bool            scanString(
	char			**ppCmdStr,         // NUL terminated string pointer
    uint32_t        maxLen,
	uint32_t		*pScannedLen,       // (returned) Scanned Length
                                        // (not including leading whitespace)
	char			*pOutput            // Output Buffer Pointer
)
{
	bool            fRc = false;
	char			*pCurChr = NULL;
	uint32_t		cOutput = 0;
	char			Quote = 0;
    uint32_t        hexNumber;

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
		// Handle Quoted Arguments.
		if( ('"' == *pCurChr) || ('\'' == *pCurChr) ) {
			Quote = *pCurChr++;
			while( *pCurChr && (cOutput < maxLen) ) {
                if( *pCurChr == Quote ) {
                    if( *(pCurChr+1) == Quote ) {
                        ++pCurChr;
                    }
                    else {
                        break;
                    }
                }
                if( *pCurChr == '\\' ) {
                    if( *(pCurChr+1) == Quote ) {
                        ++pCurChr;
                    }
                    if( *(pCurChr+1) == '0' ) {
                        pCurChr += 2;
                        *pOutput++ = '\0';
                        ++cOutput;
                        continue;
                    }
                    if( *(pCurChr+1) == 'f' ) {
                        pCurChr += 2;
                        *pOutput++ = '\f';
                        ++cOutput;
                        continue;
                    }
                   if( *(pCurChr+1) == 'n' ) {
                        pCurChr += 2;
                        *pOutput++ = '\n';
                        ++cOutput;
                        continue;
                    }
                    if( *(pCurChr+1) == 'r' ) {
                        pCurChr += 2;
                        *pOutput++ = '\r';
                        ++cOutput;
                        continue;
                    }
                    if( *(pCurChr+1) == 'x' ) {
                        pCurChr += 2;
                        // At this point, we need two more characters of 0..9,a..f,A..F
                        // to give us our hex character.
                        if (('\0' == *pCurChr) || ('\0' == *(pCurChr+1))) {
                            return false;
                        }
                        fRc = hex_ScanUint32A(2, pCurChr, &hexNumber);
                        if (fRc) {
                            *pOutput++ = (char)hexNumber;
                            ++cOutput;
                            pCurChr += 2;
                        }
                        else {
                            return false;
                        }
                        continue;
                    }
               }
                *pOutput++ = *pCurChr++;
				++cOutput;
			}
			if( *pCurChr ) {
//				*pCurChr = '\0';
				++pCurChr;
			}
		}
		// Handle Non-Quoted Arguments.
		else {
			while( (cOutput < maxLen)
                   && *pCurChr
                   && !(('=' == *pCurChr) || (',' == *pCurChr)
                        || (' ' == *pCurChr) || ('\t' == *pCurChr))
            ) {
                *pOutput++ = *pCurChr++;
				++cOutput;
			}
            if (cOutput < maxLen) {
                *pOutput = '\0';
                //++cOutput;
            }
			while( *pCurChr
                  && !(('=' == *pCurChr) || (',' == *pCurChr) 
                       || (' ' == *pCurChr) || ('\t' == *pCurChr)) ) {
                ++pCurChr;
			}
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








