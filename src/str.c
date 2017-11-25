/****************************************************************
 *              String Support (str) Subroutines				*
 ****************************************************************/

// vi: nu:noai:ts=4:sw=4

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

/* Header File Inclusion
 */
#include	<str_internal.h>


// Hashing function described in
// "Fast Hashing of Variable-Length Text Strings,"
// by Peter K. Pearson, CACM, June 1990, page 678.
static
uint8_t         hashRandomNumbers[256] =
{	// Pseudorandom Permutation of the Integers 0 through 255.
    1, 14,110, 25, 97,174,132,119,138,170,125,118, 27,233,140, 51,
    87,197,177,107,234,169, 56, 68, 30,  7,173, 73,188, 40, 36, 65,
    49,213,104,190, 57,211,148,223, 48,115, 15,  2, 67,186,210, 28,
    12,181,103, 70, 22, 58, 75, 78,183,167,238,157,124,147,172,144,
    176,161,141, 86, 60, 66,128, 83,156,241, 79, 46,168,198, 41,254,
    178, 85,253,237,250,154,133, 88, 35,206, 95,116,252,192, 54,221,
    102,218,255,240, 82,106,158,201, 61,  3, 89,  9, 42,155,159, 93,
    166, 80, 50, 34,175,195,100, 99, 26,150, 16,145,  4, 33,  8,189,
    121, 64, 77, 72,208,245,130,122,143, 55,105,134, 29,164,185,194,
    193,239,101,242,  5,171,126, 11, 74, 59,137,228,108,191,232,139,
    6, 24, 81, 20,127, 17, 91, 92,251,151,225,207, 21, 98,113,112,
    84,226, 18,214,199,187, 13, 32, 94,220,224,212,247,204,196, 43,
    249,236, 45,244,111,182,153,136,129, 90,217,202, 19,165,231, 71,
    230,142, 96,227, 62,179,246,114,162, 53,160,215,205,180, 47,109,
    44, 38, 31,149,135,  0,216, 52, 63, 23, 37, 69, 39,117,146,184,
    163,200,222,235,248,243,219, 10,152,131,123,229,203, 76,120,209
};





/****************************************************************
* * * * * * * * * * *  Internal Subroutines	* * * * * * * * * * *
****************************************************************/




/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/



/**********************************************************
	str_Compare - Compare Two Strings
 **********************************************************/

int             str_Compare(
    const
	char			*pszStr1,
    const
	char			*pszStr2
)
{
	int             i;
    int             result = 0;

	// Do initialization.

	//	Compare the strings.
	for( ;; ) {
		if( *pszStr1 )
			;
		else {
			if( *pszStr2 )
				result = -1;
			break;
		}
		if( *pszStr2 )
			;
		else {
			if( *pszStr1 )
				result = 1;
			break;
		}
		i = *pszStr1 - *pszStr2;
		if( i ) {
			if( i < 0 )
				result = -1;
			else
				result = 1;
			break;
		}
		++pszStr1;
		++pszStr2;
	}

	// Return to caller.
	return( result );
}


int             str_CompareW32(
    const
    W32CHR_T		*pszStr1,
    const
    W32CHR_T		*pszStr2
)
{
    int32_t         i;
    int             result = 0;
    
    // Do initialization.
    
    //	Compare the strings.
    for( ;; ) {
        if( *pszStr1 )
            ;
        else {
            if( *pszStr2 )
                result = -1;
            break;
        }
        if( *pszStr2 )
            ;
        else {
            if( *pszStr1 )
                result = 1;
            break;
        }
        i = *pszStr1 - *pszStr2;
        if( i ) {
            if( i < 0 )
                result = -1;
            else
                result = 1;
            break;
        }
        ++pszStr1;
        ++pszStr2;
    }
    
    // Return to caller.
    return result;
}


int             str_CompareNW32(
    const
    W32CHR_T		*pszStr1,
    const
    W32CHR_T		*pszStr2,
    uint32_t        len
)
{
    int32_t         i;
    int             result = 0;
    
    // Do initialization.
    
    //	Compare the strings.
    for( ;; ) {
        if( *pszStr1 )
            ;
        else {
            if( *pszStr2 )
                result = -1;
            break;
        }
        if( *pszStr2 )
            ;
        else {
            if( *pszStr1 )
                result = 1;
            break;
        }
        i = *pszStr1 - *pszStr2;
        if( i ) {
            if( i < 0 )
                result = -1;
            else
                result = 1;
            break;
        }
        ++pszStr1;
        ++pszStr2;
        --len;
        if (0 == len) {
            result = 0;
            break;
        }
    }
    
    // Return to caller.
    return result;
}




//**********************************************************
//		str_Concat - Concatenate one string to another
//**********************************************************

bool            str_Concat(
    char			*pszOut,		/* Output Buffer Pointer */
    int             outLen,			/* Output Buffer Length */
    const
    char            *pszIn          /* Input String Pointer */
)
{
	int             i;
    size_t          len;
	bool			fRc = true;
    
	// Do initialization.
    if( outLen > 0 )
        ;
    else
        return false;
    if( NULL == pszIn )
        return false;
    if( NULL == pszOut )
        return false;
    
    len = str_LengthA(pszOut);
    pszOut += len;
    outLen -= len;
    
	// Copy the String.
	for( i=0; (*pszIn && (i < outLen-1)); i++ ) {
		*pszOut++ = *pszIn++;
	}
	if( *pszIn )
		fRc = false;
    
	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen); i++ ) {
		*pszOut++ = '\0';
	}
    
	// Return to caller.
	return fRc ;
}




//**********************************************************
//			str_Copy - Copy one string to another
//**********************************************************

bool            str_Copy(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
	char            *pszIn          /* Input String Pointer */
)
{
	int             i;
	bool			fRc = true;

	// Do initialization.
    if( outLen > 0 )
        ;
    else
        return false;
    if( NULL == pszIn )
        return false;
    if( NULL == pszOut )
        return false;

	// Copy the String.
	for( i=0; (*pszIn && (i < outLen-1)); i++ ) {
		*pszOut++ = *pszIn++;
	}
	if( *pszIn )
		fRc = false;

	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen); i++ ) {
		*pszOut++ = '\0';
	}

	// Return to caller.
	return( fRc );
}




//----------------------------------------------------------
//        str_DupA - Create a new copy of a string
//----------------------------------------------------------

char *          str_DupA(
    const
	char            *pszIn          /* Input String Pointer */
)
{
	int             i;
	char			*pszOut;		/* Output Buffer Pointer */
	char			*pszCur;		/* Output Buffer Pointer */
	size_t          outLen;			/* Output Buffer Length */

	// Do initialization.
    if( NULL == pszIn )
        return NULL;

    outLen = str_LengthA( pszIn );
    pszOut = (char *)mem_Malloc( outLen+1 );
    if( NULL == pszOut )
        return NULL;
    pszCur = pszOut;

	// Copy the String.
	for( i=0; i < outLen; i++ ) {
		*pszCur++ = *pszIn++;
	}

	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen+1); i++ ) {
		*pszCur++ = '\0';
	}

	// Return to caller.
	return( pszOut );
}



//----------------------------------------------------------
//        str_DupW32 - Create a new copy of a string
//----------------------------------------------------------

W32CHR_T *      str_DupW32(
    const
    W32CHR_T        *pszIn          /* Input String Pointer */
)
{
    int             i;
    W32CHR_T		*pszOut;		/* Output Buffer Pointer */
    W32CHR_T		*pszCur;		/* Output Buffer Pointer */
    size_t          outLen;			/* Output Buffer Length */
    
    // Do initialization.
    if( NULL == pszIn )
        return NULL;
    
    outLen = str_LengthW32( pszIn );
    pszOut = (W32CHR_T *)mem_Malloc( (outLen + 1) * sizeof(W32CHR_T) );
    if( NULL == pszOut )
        return NULL;
    pszCur = pszOut;
    
    // Copy the String.
    for( i=0; i < outLen; i++ ) {
        *pszCur++ = *pszIn++;
    }
    
    //	Zero-fill the remainder of the output string.
    for( ; (i < outLen+1); i++ ) {
        *pszCur++ = 0;
    }
    
    // Return to caller.
    return( pszOut );
}



//-----------------------------------------------------------------
//          Create a new copy of a N chars of a string
//-----------------------------------------------------------------

char *          str_DupLeft(
    const
    char            *pszIn,         /* Input String Pointer */
    size_t          inLen
)
{
	int             i;
    char            *pszOutStr;
	char			*pszOut;		/* Output Buffer Pointer */
	size_t          outLen;			/* Output Buffer Length */
    
	// Do initialization.
    if( NULL == pszIn )
        return NULL;
    if (0 == inLen) {
        return NULL;
    }
    
    outLen = str_LengthA( pszIn );
    if (outLen > inLen) {
        outLen = inLen;
    }
    pszOutStr = (char *)mem_Malloc( outLen + 1 );
    if( NULL == pszOutStr )
        return NULL;
    pszOut = pszOutStr;
    
	// Copy the String.
	for( i=0; (*pszIn && (i < outLen)); i++ ) {
		*pszOut++ = *pszIn++;
	}
    
	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen+1); i++ ) {
		*pszOut++ = '\0';
	}
    
	// Return to caller.
	return( pszOutStr );
}



//-----------------------------------------------------------------
//          Create a new copy of the right N chars of a string
//-----------------------------------------------------------------

char *      str_DupRight(
    const
    char			*pszIn,			/* Input String Pointer */
    size_t          outLen			/* rightmost outLen characters */
)
{
	int             i;
    size_t          offset = 0;
	size_t          inLen;
    char			*pszOut;         /* Output Buffer Pointer */
    char            *pszCur;
    
	// Do initialization.
    if( NULL == pszIn )
        return NULL;
    if (outLen <= 0) {
        return NULL;
    }
    
	// Set up Lengths and Offsets.
	inLen = str_LengthA( pszIn );
    if (outLen > inLen) {
        outLen = inLen;
        offset = 0;
    }
    else {
        offset = inLen - outLen;
    }
	pszIn += offset;
    
	//	Copy the string.
    pszOut = mem_Malloc(outLen+1);
    if (NULL == pszOut) {
        return NULL;
    }
    pszCur = pszOut;
	for( i=0; *pszIn && (i < outLen); i++ ) {
        *pszCur++ = *pszIn++;
	}
    
	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen+1); i++ ) {
		*pszCur++ = '\0';
	}
    
	// Return to caller.
	return( pszOut );
}



/**********************************************************
		str_ExpandTabs - Expand Tab in	a String
 **********************************************************/

bool            str_ExpandTabs(
	char			*pszOut,
	int             outLen,
    const
	char			*pszIn,
	int             tabSiz
)
{
	int             i;
	bool			fRc = true;

	// Do initialization.
    if( outLen > 0 )
        ;
    else
        return false;
    if( NULL == pszIn )
        return false;
    if( NULL == pszOut )
        return false;

	/* Copy the String expanding Horizontal Tabs.
	 */
	for( i=0; *pszIn && (i < outLen-1); pszIn++ ) {
		if( *pszIn == '\t' ) {
			do {
				if( i < outLen-1 )
					*pszOut++ = ' ';
				else {
					fRc = false;
					break;
				}
			} while( ++i % tabSiz );
		}
		else {
			if( i++ < outLen-1 )
				*pszOut++ = *pszIn;
			else {
				fRc = false;
				break;
			}
		}
	}

	//	Zero-fill the remainder of the output string.
    if( fRc ) {
        for( ; (i < outLen); i++ ) {
            *pszOut++ = '\0';
        }
    }

	// Return to caller.
	return( fRc );
}




/**********************************************************
	str_FindWrap - Find the String Size for Word-Wrapping
 **********************************************************/

int             str_FindWrap(
    const
	char			*pszIn,
	int             wrapCol         /* Wrap Column Number */
)
{
	int             i;
	int             j;

	// Do initialization.

	/* Scan off each word keeping track of the end of
	 * the previous word.
	 */
	for( i=0,j=0; *pszIn && (i < wrapCol); pszIn++, i++ ) {
		if( *pszIn == ' ' )
			j = i;
	}

	/* Check for end of word being just after word-wrap
	 * length and handle appropriately.
	 */
	if( (i == wrapCol) && (*pszIn != '\0') ) {
		if( *pszIn == ' ' )
			j = wrapCol;
	}

	// Return to caller.
	return( j );
}




//-----------------------------------------------------------------
//                        H a s h
//-----------------------------------------------------------------

/* This routine creates a Hash Number given a pointer to a
 * string.  It relies on the fact that the number may over-
 * flow in the accumulation phase.
 */
uint32_t        str_HashA(
    const
	char            *pszIn,             /* Input String Ptr */
    size_t          *pLength            /* Returned Length if not NULL */
)
{
	int             len = 0;
    uint32_t        hash = 0;
    int             c;

	while( (c = *pszIn++) ) {
        hash = c + (hash << 6) + (hash << 16) - hash;
        ++len;
	}

    if( pLength )
        *pLength = len;
	return( hash );
}


uint32_t        str_HashW32(
    const
    W32CHR_T        *pszIn,             /* Input String Ptr */
    size_t          *pLength            /* Returned Length if not NULL */
)
{
    int             len = 0;
    uint32_t        hash = 0;
    int             c;
    
    while( (c = *pszIn++) ) {
        hash = c + (hash << 6) + (hash << 16) - hash;
        ++len;
    }
    
    if( pLength )
        *pLength = len;
    return( hash );
}




//-----------------------------------------------------------------
//                        H a s h A c m
//-----------------------------------------------------------------

// This routine creates a Hash Number given a pointer to a
// string.  It relies on the fact that the number may over-
// flow in the accumulation phase.

// Hashing function described in
// "Fast Hashing of Variable-Length Text Strings,"
// by Peter K. Pearson, CACM, June 1990.

uint32_t        str_HashAcmA(
    const
    char            *pszIn,             /* Input String Ptr */
    size_t          *pLength            /* Returned Length if not NULL */
)
{
    int             len = 0;
    uint32_t        hash = 0;
    uint32_t        hash1 = 0;
    uint32_t        hash2 = 0;
    int             c;
    
    for( ;; ) {
        // Hash function is XOR of successive characters, randomized by
        // the hash table.
        c = *pszIn++;
        if( c ) {
            hash1 ^= hashRandomNumbers[ c & 0xFF ];
        }
        else
            break;
        c = *pszIn++;
        if( c ) {
            hash2 ^= hashRandomNumbers[ c & 0xFF ];
        }
        else
            break;
        ++len;
    }
    hash = (hash1 << 8) | hash2;
    
    if( pLength )
        *pLength = len;
    return( hash );
}


uint32_t        str_HashAcmW32(
    const
    W32CHR_T        *pszIn,             /* Input String Ptr */
    size_t          *pLength            /* Returned Length if not NULL */
)
{
    int             len = 0;
    uint32_t        hash = 0;
    uint32_t        hash1 = 0;
    uint32_t        hash2 = 0;
    int             c;
    
    for( ;; ) {
        // Hash function is XOR of successive characters, randomized by
        // the hash table.
        c = *pszIn++;
        if( c ) {
            hash1 ^= hashRandomNumbers[ c & 0xFF ];
        }
        else
            break;
        c = *pszIn++;
        if( c ) {
            hash2 ^= hashRandomNumbers[ c & 0xFF ];
        }
        else
            break;
        ++len;
    }
    hash = (hash1 << 8) | hash2;
    
    if( pLength )
        *pLength = len;
    return( hash );
}




//-----------------------------------------------------------------
//                    H a s h _ F N V 1
//-----------------------------------------------------------------

/* This routine creates a Hash Number given a pointer to a
 * string.  It relies on the fact that the number may over-
 * flow in the accumulation phase.
 */
uint32_t        str_Hash_FNV1A(
    const
	char            *pszIn,             /* Input String Ptr */
    size_t          *pLength            /* Returned Length if not NULL */
)
{
	int             len = 0;
    uint32_t        hash = 0;
    int             c;

    while( (c = *pszIn++) ) {
        hash = (hash * 16777619) ^ c;
        ++len;
	}

    if( pLength )
        *pLength = len;
	return( hash );
}




//-----------------------------------------------------------------
//                    H a s h _ F N V 1 a
//-----------------------------------------------------------------

/* This routine creates a Hash Number given a pointer to a
 * string.  It relies on the fact that the number may over-
 * flow in the accumulation phase.
 */
uint32_t        str_Hash_FNV1aA(
    const
	char            *pszIn,             /* Input String Ptr */
	size_t          *pLength            /* Returned Length if not NULL */
)
{
	int             len = 0;
    uint32_t        hash = 0;
    int             c;

    while( (c = *pszIn++) ) {
        hash = (hash ^ c) * 16777619;
        ++len;
	}

    if( pLength )
        *pLength = len;
	return( hash );
}




//-----------------------------------------------------------------
//              Copy Left-most N Bytes of a String
//-----------------------------------------------------------------

int             str_Left(
	char			*pszOut,		/* Output String Pointer */
	int             outLen,			/* Output String Length */
    const
	char			*pszIn,			/* Input String Pointer */
	int             inLen			/* Input String Length */
)
{
	int             i;
    int             len = 0;

	// Do initialization.
    if( NULL == pszOut )
        return 0;

	//	Copy the string.
	for( i=0; (*pszIn && (i < inLen)); i++ ) {
		if( i < outLen-1 ) {
			*pszOut++ = *pszIn++;
            ++len;
        }
		else {
            return false;
			break;
		}
	}

	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen); i++ ) {
		*pszOut++ = '\0';
	}

	// Return to caller.
	return( len+1 );                // Include NUL in length
}





//-----------------------------------------------------------------
//             Length - Find the Length of a String
//-----------------------------------------------------------------

size_t          str_LengthA(
    const
	char			*pszIn			/* Input String Pointer */
)
{
	int             i = 0;

    if( NULL == pszIn )
        ;
    else {
        while( *pszIn++ )
            ++i;        
    }

	return( i );
}


size_t          str_LengthW32(
    const
    W32CHR_T		*pszIn			/* Input String Pointer */
)
{
    int             i = 0;
    
    if( NULL == pszIn )
        ;
    else {
        while( *pszIn++ )
            ++i;
    }
    
    return( i );
}




#ifdef ZZZ_ZZZ
/**********************************************************
	str_Match - Find a String within a String
 **********************************************************/

APIRET APIENTRY	str_Match(
	PBYTE			InPat,			/* Input Pattern */
	char			*pszIn,			/* Input String Pointer */
)
{

	/* Do initialization.
	 */
	RW_ASSERT( InPat );
	RW_ASSERT( InStr );

	if( *InPat == '\0' ) {
		if( *InStr == '\0' )
			return( 11 );
		else
			return( 1 );
	}
	else if( *InPat == '?' ) {
		if( *InStr == '\0' )
			return( 6 );
		++InPat;
		++InStr;
		return( str_Match( InPat, InStr ) );
	}
	else if( *InPat == ' ' ) {
		++InPat;
		return( str_Match( InPat, InStr ) );
	}
	else if( *InPat == '*' ) {
		++InPat;
		if( *InPat == '\0' )
			return( 12 );
		while( (BYTE)tolower(*(++InPat)) == *InStr )
			++InStr;
		return( str_Match( InPat, InStr ) );
	}
	else if( *InPat == '\\' ) {
		if( (BYTE)tolower(*(++InPat)) == *InStr ) {
			if( (*InPat == '\0') && (*InStr == '\0') )
				return( 1 );
			else
				return( str_Match( InPat, InStr ) );
		}
		else
			return( 3 );
	}
	else if( (BYTE)toupper(*InPat) == *InStr ) {
			++InPat;
			++InStr;
			return( str_Match( InPat, InStr ) );
	}
	else
		return( 4 );
}
#endif




/**********************************************************
	str_Mid - Copy a SubString from a String
 **********************************************************/

int             str_Mid(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
	char			*pszIn,			/* Input String Pointer */
	int				lenMid,			/* Length to extract */
	int             offset			/* Offset for 1st char */
)
{
	int             i;
    int             len = 0;
	size_t          inLen;

	// Do initialization.
    if( NULL == pszOut )
        return 0;

	//	Copy the string.
	inLen = str_LengthA( pszIn );
	if( offset <= (inLen - 1) ) {
		pszIn += offset;
		for( i=0; (*pszIn && (i < lenMid)); i++ ) {
			if( i < (outLen - 1) ) {
				*pszOut++ = *pszIn++;
                ++len;
            }
			else {
				break;
			}
		}
	}
	else
		i = 0;

	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen); i++ ) {
		*pszOut++ = '\0';
	}

	// Return to caller.
	return( len+1 );
}




/**********************************************************
	str_Right - Copy the Right-most N Chars of a String
 **********************************************************/

int             str_Right(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
	char			*pszIn,			/* Input String Pointer */
	int             offset			/* Offset for 1st char */
)
{
	int             i;
    int             len = 0;
	size_t          inLen;

	// Do initialization.
    if( NULL == pszOut )
        return 0;

	// Set up Lengths and Offsets.
	inLen = str_LengthA( pszIn );
	inLen = (offset >= (inLen - 1)) ? inLen : (inLen - 1 - offset);
	pszIn += inLen;

	//	Copy the string.
	for( i=0; *pszIn; i++ ) {
		if( i < outLen-1 ) {
			*pszOut++ = *pszIn++;
            ++len;
        }
		else {
			break;
		}
	}

	//	Zero-fill the remainder of the output string.
	for( ; (i < outLen); i++ ) {
		*pszOut++ = '\0';
	}

	// Return to caller.
	return( len );
}




//-----------------------------------------------------------------
//       Index - Find first occurranceof a char in a String
//-----------------------------------------------------------------

int             str_Lindex(
    const
    char			*pszIn,
    const
    char            chr
)
{
	int             i = 0;
    size_t          len;
    
    if( NULL == pszIn )
        return -1;

    len = str_LengthA(pszIn);
    while( *pszIn && (*pszIn != chr)) {
        ++i;
        ++pszIn;
    }
    if (i >= len) {
        i = -1;
    }
    
	return( i );
}




#ifdef ZZZ_ZZZ
/**********************************************************
		str_Str2Long - Convert a String to a Long Integer
 **********************************************************/

APIRET APIENTRY	str_Str2Long(
    const
	char			*pszIn,			/* Input String Pointer */
	PLONG			OutNum
)
{
	short			Sign = 1;
	BOOL			SignPres = FALSE;
	APIRET			rc = str_OK;

	/* Validate the input parameters.
	 */
	RW_ASSERT( InStr );
	RW_ASSERT( OutNum );
	*OutNum = 0;

	/*	Scan the string.
	 */
	while( *InStr ) {
		if( (*InStr == ' ') || (*InStr == '\t') )
			++InStr;
		else
			break;
	}
	if( *InStr && (*InStr == '$') ) {
		++InStr;
	}
	else if( *InStr && (*InStr == '+') ) {
		SignPres = TRUE;
		++InStr;
	}
	else if( *InStr && (*InStr == '-') ) {
		SignPres = TRUE;
		Sign = -1;
		++InStr;
	}
	while( *InStr ) {
		if( (*InStr >= '0') && (*InStr <= '9') )
			*OutNum = (*OutNum * 10) + (*InStr - '0');
		else if( *InStr == ',' )
			;
		else if( *InStr == '.' )
			;
		else
			break;
		++InStr;
	}
	if( SignPres ) {
		if( *InStr )
			return( 2 );
	}
	else {
		if( *InStr && (*InStr == '+') ) {
			SignPres = TRUE;
			++InStr;
		}
		else if( *InStr && (*InStr == '-') ) {
			SignPres = TRUE;
			Sign = -1;
			++InStr;
		}
		else if( *InStr )
			return( 2 );
	}

	/* Return to caller.
	 */
	*OutNum *= Sign;
	return( rc );
}
#endif





/**********************************************************
    str_ToLower - Convert a String to a Lower Case in place
 **********************************************************/

char *          str_ToLowerA(
	char			*pszIn			/* Input String Pointer */
)
{
    char            *pFirst = pszIn;

	// Validate the input parameters.
    if( NULL == pszIn )
        return pFirst;

	//	Scan the string converting it to lower-case.
	for( ; *pszIn; ++pszIn ) {
		if( (*pszIn >= 'A') && (*pszIn <= 'Z') )
			*pszIn = (char)(*pszIn + ('a' - 'A'));
	}

	// Return to caller.
    return pFirst;
}


W32CHR_T *      str_ToLowerW32(
    W32CHR_T		*pszIn			/* Input String Pointer */
)
{
    W32CHR_T        *pFirst = pszIn;
    
    // Validate the input parameters.
    if( NULL == pszIn )
        return pFirst;
    
    //	Scan the string converting it to lower-case.
    for( ; *pszIn; ++pszIn ) {
        if( (*pszIn >= 'A') && (*pszIn <= 'Z') )
            *pszIn = (char)(*pszIn + ('a' - 'A'));
    }
    
    // Return to caller.
    return pFirst;
}




/**********************************************************
    str_ToUpper - Convert a String to a Upper Case in place
 **********************************************************/

char *          str_ToUpperA(
	char			*pszIn			/* Input String Pointer */
)
{
    char            *pFirst = pszIn;

	// Validate the input parameters.
    if( NULL == pszIn )
        return pFirst;

	//	Scan the string converting it to lower-case.
	for( ; *pszIn; ++pszIn ) {
		if( (*pszIn >= 'a') && (*pszIn <= 'z') )
			*pszIn = (char)(*pszIn - ('a' - 'A'));
	}

	// Return to caller.
    return pFirst;
}


W32CHR_T *      str_ToUpperW32(
    W32CHR_T		*pszIn			/* Input String Pointer */
)
{
    W32CHR_T        *pFirst = pszIn;
    
    // Validate the input parameters.
    if( NULL == pszIn )
        return pFirst;
    
    //	Scan the string converting it to lower-case.
    for( ; *pszIn; ++pszIn ) {
        if( (*pszIn >= 'a') && (*pszIn <= 'z') )
            *pszIn = (char)(*pszIn - ('a' - 'A'));
    }
    
    // Return to caller.
    return pFirst;
}










#ifdef	TEST_PROG
				/*0 		1		  2 		3		  4*/
		 		/*01234567890123456789012345678901234567890*/
char	*tstr1 = "Now is the time for all good men to come.";
char	tstr2[42];
char	tstr3[42];


int 			main(
)
{
	int				i;
	int				j;
	long			lInt;
	char			*chr;
	USHORT			Wrap;
	APIRET			rc;

	/* Test the str_FindWrap function.
	 */
	printf( "str_FindWrap+str_Left+Str_Right Test\n" );
	printf( "01234567890123456789012345678901234567890\n" );
	printf( "%s\n", tstr1 );
	for( i=10; i<30; ++i ) {
		rc = str_FindWrap( tstr1, i, &Wrap );
		rc = str_Left( tstr2, sizeof(tstr2), tstr1, Wrap );
		rc = str_Right( tstr3, sizeof(tstr3), tstr1, strlen(tstr1)-Wrap );
		printf( "MaxWrap=%d Wrap=%d  >>%s<<  <<%s>>\n", i, Wrap, tstr2, tstr3	);
	}
	printf( "\n\n" );


	printf( "str_Mid Test\n" );
	printf( "01234567890123456789012345678901234567890\n" );
	printf( "%s\n", tstr1 );
	rc = str_Length( tstr1, &Wrap );
	printf( "Length=%d  rc=%d\n", Wrap, rc );
	for( i=30; i<41; ++i ) {
		j = 6;
		rc = str_Mid( tstr2, sizeof(tstr2), tstr1, i, j );
		printf( "s=%d w=%d rc=%d >>%s<<\n", i, j, rc, tstr2 );
	}
	printf( "\n\n" );


	/* Test the str_Str2Lower function.
	 */
	printf( "str_Str2Upper Test\n" );
	rc = str_Copy( tstr2, sizeof(tstr2), "ABCD1234" );
	rc = str_Copy( tstr3, sizeof(tstr3), "ABCD1234" );
	rc = str_Str2Lower( tstr3 );
	printf( "Test=%s  Result=%s  rc=%d\n", tstr2, tstr3, rc );
	printf( "\n\n" );


	/* Test the str_Str2Upper function.
	 */
	printf( "str_Str2Upper Test\n" );
	rc = str_Copy( tstr2, sizeof(tstr2), "abcd1234" );
	rc = str_Copy( tstr3, sizeof(tstr3), "abcd1234" );
	rc = str_Str2Upper( tstr3 );
	printf( "Test=%s  Result=%s  rc=%d\n", tstr2, tstr3, rc );
	printf( "\n\n" );


	/* Test the str_ExpandTabs function.
	 */
	printf( "str_ExpandTabs Test\n" );
	printf( "01234567890123456789012345678901234567890\n" );
	printf( "0   1   2   3   4   5   6  <== Should be\n" );
	rc = str_Copy( tstr2, sizeof(tstr2), "0\t1\t2\t3\t4\t5\t6" );
	rc = str_ExpandTabs( tstr3, sizeof(tstr3), tstr2, 4 );
	printf( "%s  rc=%d\n", tstr3, rc );
	printf( "\n\n" );


	printf( "str_Str2Long Test\n" );
	chr = "+123";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "-986";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "123+";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "986-";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "$123,456";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "+123,456";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "123,456-";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "123.456-";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	chr = "+123";
	i = str_Str2Long( chr, &lInt );
	printf( "char=%s rc=%d val=%ld\n", chr, i, lInt );
	printf( "\n\n" );

	return( 0 );
}
#endif
