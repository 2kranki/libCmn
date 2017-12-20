// vi: nu:noai:ts=4:sw=4
/****************************************************************
 *			   String Manipulation Subroutines Header			*
 ****************************************************************/

/*Purpose
 *	 This set of subroutines provide generalized for manipulating
 *	 strings and contains several safeguards the C Library left out.
 *Input
 *Output
 *Outline
 *Remarks
 *	1.			All string lengths include 1 byte for the
 *				zero value to mark the end of the string.
 *	2.			All routines which copy one string or portion
 *				thereof to another zero fill any remaining
 *				chars in the output string.
 * References
 *		"Data Structures and Algorithms", Alfred V. Aho et al,
 *			Addison-Wesley Publishing, 1982, ISBN 0-201-00023-7
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




#ifndef             W32CHR_T
#define             W32CHR_T    int32_t
#endif
#include            <stdbool.h>
#include            <stdint.h>
#include            <stdio.h>



/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

#ifndef STR_H
#define STR_H	1





/****************************************************************
* * * * * * * * * *  subroutine definitions	  * * * * * * * * * *
****************************************************************/

/* str_Compare() compares two Input Strings to each other.
 * Returns:
 *	-1              =	Str1 <	Str2
 *	0				=	Str1 == Str2
 *	1               =	Str1 >	Str2
 */
int             str_Compare(
    const
	char			*pszStr1,
    const
	char			*pszStr2
);

int             str_CompareW32(
    const
    W32CHR_T		*pszStr1,
    const
    W32CHR_T		*pszStr2
);

int             str_CompareNW32(
    const
    W32CHR_T		*pszStr1,
    const
    W32CHR_T		*pszStr2,
    uint32_t        len
);


/* str_Concat() concatenates the Input String to the Output String in-
 * cluding the nul-terminator for the Maximum number of Chars
 * specified.  The Output String is always left nul-terminated even
 * if the input string must be truncated.
 * Returns:
 *	TRUE				=	Successful Completion
 *	FALSE               =	Output Field Overflow or Invalid Parameters
 */
bool            str_Concat(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
	char            *pszIn          /* Input String Pointer */
);


/* str_Copy() copies the Input String to the Output String in-
 * cluding the nul-terminator for the Maximum number of Chars
 * specified.  The Output String is always left nul-terminated.
 * Returns:
 *	TRUE				=	Successful Completion
 *	FALSE               =	Output Field Overflow or Invalid Parameters
 */
bool            str_Copy(
    char			*pszOut,		/* Output Buffer Pointer */
    int             outLen,			/* Output Buffer Length */
    const
    char            *pszIn          /* Input String Pointer */
);


/* Duplicate() copies the Input String to a new string that
 * was allocated with malloc(). 
 * The string will need to be free()'d when you are done with it.
 * Returns:
 *	NULL				=	Unsuccessful Completion
 *	string ptr          =	Duplicated String Address
 */
char *          str_DupA(
    const
	char            *pszIn          /* Input String Pointer */
);

W32CHR_T *      str_DupW32(
    const
    W32CHR_T        *pszIn          /* Input String Pointer */
);


/* DupLeft() copies the leftmost cChrs characters of the Input
 * String to a new string that was allocated with malloc(). 
 * The string will need to be free()'d when you are done with it.
 * Returns:
 *	NULL				=	Unsuccessful Completion
 *	string ptr          =	Duplicated String Address
 */
char *          str_DupLeft(
    const
    char            *pszIn,         /* Input String Pointer */
    size_t          cChrs           /* Input String Length */
);


/* DupLeft() copies the rightmost cChrs characters of the Input
 * String to a new string that was allocated with malloc().
 * The string will need to be free()'d when you are done with it.
 * Returns:
 *	NULL				=	Unsuccessful Completion
 *	string ptr          =	Duplicated String Address
 */
char *          str_DupRight(
    const
    char            *pszIn,         /* Input String Pointer */
    size_t          cChrs           /* Number of Characters */
);


/* ExpandTabs() copies the Input String to the Output String in-
 * cluding the null-terminator for the Maximum number of Chars
 * specified and expands all Horizontal Tabls to the required number
 * of Spaces.	The Output String is always left nul-terminated.
 * Returns:
 *	TRUE			=	Successful Completion
 *	FALSE           =	Invalid Parmeters || Buffer Overflow
 */
bool            str_ExpandTabs(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
	char			*pszIn,
	int             tabSiz
);


/* str_FindWrap() finds the length of the input string up
 * to as many characters as specified in the length
 * always returning whole words. 
 * Warning - This only considers spaces to be whitespace
 *          separating words. Tabs are not analyzed.
 * Returns:
 *	0               =	no wrap point
 *	>0              =	wrap point offset relative to one
 */
int             str_FindWrap(
    const
	char			*pszIn,
	int             wrapCol         /* Wrap Column Number */
);


/* str_Hash() creates a hash for a string and optionally provides
 * the length of the string as well. The length does not include
 * the trailing NUL.
 * Returns:
 *  the hash
 *  if length is not NULL, then the length is set.
 */
uint32_t        str_HashA(
    const
	char            *pszIn,             // Input String Ptr
	size_t          *pLength            // Returned Length if not NULL
);

uint32_t        str_HashW32(
    const
    W32CHR_T        *pszIn,             // Input String Ptr
    size_t          *pLength            // Returned Length if not NULL
);


// Hashing function described in
// "Fast Hashing of Variable-Length Text Strings,"
// by Peter K. Pearson, CACM, June 1990.
/* Returns:
 *      the hash
 *      If length is not NULL, then the length is set.
 */
uint32_t        str_HashAcmA(
    const
    char            *pszIn,             /* Input String Ptr */
    size_t          *pLength            /* Returned Length if not NULL */
);

uint32_t        str_HashAcmW32(
    const
    W32CHR_T        *pszIn,             /* Input String Ptr */
    size_t          *pLength            /* Returned Length if not NULL */
);


/* str_Hash_FNV1() creates a hash for a string and optionally provides
 * the length of the string as well.
 * Returns:
 *  the hash
 *  if length is not NULL, then the length is set.
 */
uint32_t        str_Hash_FNV1A(
    const
	char            *pszIn,             // Input String Ptr
	size_t          *pLength            // Returned Length if not NULL
);


/* str_Hash_FNV1a() creates a hash for a string and optionally provides
 * the length of the string as well.
 * Returns:
 *  the hash
 *  if length is not NULL, then the length is set.
 */
uint32_t        str_Hash_FNV1aA(
    const
	char            *pszIn,             // Input String Ptr
	size_t          *pLength            // Returned Length if not NULL
);


/* str_Left() copies the Left-most portion of the Input String
 * to the Output String including the null-terminator for the
 * Maximum number of Chars specified.  The Output String is al-
 * ways left nul-terminated.
 * Returns:
 *	Length of string written
 */
int             str_Left(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
    char			*pszIn,			/* Input String Pointer */
	int             inLen			/* Number of Characters to copy */
);


/* Length() finds the length of the input string in
 * characterss excluding the nul-terminator.
 * Returns:
 *      length of string
 */
size_t          str_LengthA(
    const
	char			*pszIn			/* Input String Pointer */
);

size_t          str_LengthW32(
    const
    W32CHR_T		*pszIn			/* Input String Pointer */
);


/* Find first occurrence of chr in pszIn. Return relative offset
 * of chr if found or -1 if not.
 */
int             str_Lindex(
    const
    char			*pszIn,
    const
    char            chr
);


#ifdef ZZZ_ZZZ
APIRET APIENTRY str_Match(
	PBYTE	ipat,				/* Input Pattern */
	PBYTE	istr				/* Input String Pointer */
);
#endif


/* str_Mid() copies a portion of the Input String to the Output
 * String including the NUL-terminator for the Maximum number
 * of Chars specified.	The Output String is always left null-
 * terminated.
 * Returns:
 *	Length of string written
 */
int             str_Mid(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
	char			*pszIn,			/* Input String Pointer */
	int				len,			/* Length to extract */
	int             offset			/* Offset for 1st char */
);


/* str_Right() copies the Right-most portion of the Input String
 * to the Output String including the null-terminator for the
 * Maximum number of Chars specified.  The Output String is al-
 * ways left null-terminated.
 * Returns:
 *	Length of string written
 */
int             str_Right(
	char			*pszOut,		/* Output Buffer Pointer */
	int             outLen,			/* Output Buffer Length */
    const
	char			*pszIn,			/* Input String Pointer */
	int             offset			/* Offset for 1st char */
);


#ifdef ZZZ_ZZZ
/* str_Str2Long() converts a String to a Long Integer removing
 * commas, leading dollar sign and allowing the sign to precede
 * or trail the number.
 * Returns:
 *	str_OK			=	Successful Completion
 *	AST_ERROR_BADCB	=	Invalid AST_CB Pointer
 *	AST_ERROR_BADKY	=	Invalid Parent or Current Entry Index
 *	AST_ERROR_LOCKO	=	Lock Count Overflow/Underflow
 *	AST_ERROR_NOMEM	=	No Memory Available
 */
APIRET APIENTRY str_Str2Long(
	char			*,				/* Input String Pointer */
	PLONG							/* (Signed) Output Number Ptr */
);
#endif


/* str_ToLower() converts all upper case letters in a string
 * to lower case.
 * Returns:
 *     pointer to input string
 */
char *          str_ToLowerA(
	char			*pszIn			/* Input String Pointer */
);

W32CHR_T *      str_ToLowerW32(
    W32CHR_T		*pszIn			/* Input String Pointer */
);


/* str_ToUpper() converts all lower case letters in a string
 * to upper case.
 * Returns:
 *      pointer to input string
 */
char *          str_ToUpperA(
	char			*pszIn			/* Input String Pointer */
);

W32CHR_T *      str_ToUpperW32(
    W32CHR_T		*pszIn			/* Input String Pointer */
);





#endif      // STR_H
