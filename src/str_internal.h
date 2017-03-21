/****************************************************************
 *          String Support (str) Internal Header                *
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
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        <str.h>


typedef struct str_sb_s STR_SB;

#pragma pack(1)
/* * *	String Buffer Definition * *
 */
struct str_sb_s {
    uint16_t        buflen;			/* Length of Data Buffer */
	uint16_t        len;			/* Length of String */
	char			*pData;			/* String Data Ptr */
									/* We used a Ptr here so that
									 * the data could be changed
									 * in length without the Con-
									 * trol Block having to move
									 * as well.  Some systems call
									 * this type of system a Dope
									 * Vector.	BASIC made this
									 * technique famous.
									 */
};


#pragma pack()


#pragma pack(1)
/* * *	Pascal String Buffer Definition * *
 */
typedef struct str_pascal_sb_s {
    uint8_t         bufLen;         // Length of buffer
	uint8_t         len;			// Length of String including NUL
	uint8_t			data[0];		// String Data
} STR_PASCAL_SB;


#pragma pack()



