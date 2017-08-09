// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          UTF8 Console Transmit Task (utf8) Header
//****************************************************************
/*
 * Program
 *				Separate utf8 (utf8)
 * Purpose
 *				In C, UTF-8 for I/O is handled by fgetwc, fputwc and
 *              ungetwc among others. Translating from UTF-8 to wc
 *              and back is handled by the functions:
 *                  mblen,mbrlen
 *                  mbrtowc,mbrtowcs,mbsrtowcs,mbstowcs,mbtowc
 *                  wcrtomb,wcstombs,wcsrtombs,wctomb
 *              So, encoding/decoding is supported using the stdlib
 *              routines making the need for this object much less.
 *              However, if stdlib is not available and these func-
 *              are needed, then this becomes more necessary.
 *
 *      # bits  First  Last
 *      code    Code   Code
 *      points  Point  Point     Bytes
 *        7     U+0000    U+007F      1    0xxxxxxx
 *       11     U+0080    U+07FF      2    110xxxxx 10xxxxxx
 *       16     U+0800    U+FFFF      3    1110xxxx 10xxxxxx 10xxxxxx
 *       21     U+1000    U+1FFFFF    4    11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *       26     U+20000   U+3FFFFFF   5    111110xx 10xxxxxx 10xxxxxx 10xxxxxx
 *                                         10xxxxxx
 *       31     U+4000000 U+7FFFFFFF  6    1111110x 10xxxxxx 10xxxxxx 10xxxxxx
 *                                         10xxxxxx 10xxxxxx
 *      The range of the 2nd - 6th bytes is 0x80 - 0xBF.
 *
 *
 *
 * Remarks
 *	1.      Based on routines found in Basic UTF-8 manipulation 
 *          routines by Jeff Bezanson placed in the public domain
 *          Fall 2005
 *  2.      UTF-16 is used extensively in Win2K and newer. It encodes all
 *          code points as either 2 or 4 byte sequences as follows:
 *          0x0000 - 0xD7FF are encoded as 2 bytes.
 *          0xE000 - 0xFFFD are encoded as 2 bytes.
 *          0x010000 - 0x10FFFF are encoded as 4 byte sequences using:
 *              0xD800 - 0xDBFF encode 2 bytes with 0x3FF (10) bits.
 *              0xDC00 - 0xDFFF encode 2 bytes with 0x3FF (10) bits.
 *          Little Endian BOM == 0xFF 0xFE
 *          Big Endian BOM == 0xFE 0xFF
 *
 * History
 *	08/06/2015 Generated
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





#include        <cmn_defs.h>


#ifndef         UTF8_H
#define         UTF8_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct utf8_data_s	UTF8_DATA;

    typedef struct utf8_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fat16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FBSI_DATA *);
    } UTF8_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the utf8 including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    UTF8_DATA *     utf8_Alloc(
        uint16_t        stackSize           // Stack Size in Words
    );
    

    int             utf8_StrCmp(
        const
        char            *pSrc1,
        const
        char            *pSrc2
    );
    
    int             utf8_StrCmpAW(
        const
        char            *pSrc1,
        const
        int32_t         *pSrc2
    );
    
    
    char *          utf8_StrDup(
        const
        char            *pSrc
    );
    
    
    // Given the first character of a UTF-8 sequence, this
    // routine returns the number of total characters needed.
    // -1 is returned if the first byte is not valid as a
    // first character.
    int             utf8_ChrLen(
        const
        char            src
    );
    

    // Return the number of actual unicode and ASCII characters
    // in a string excluding the NUL-terminator.
    int             utf8_StrLenA(
        const
        char            *pSrc
    );
    
    int             utf8_StrLenW(
        const
        int32_t         *pSrc
    );
    
    
    // Return the number of actual characters in the string
    // excluding the NUL-terminator.
    int             utf8_StrLenChars(
        const
        char            *pSrc
    );
    
    
    // Convert an offset into a string of Unicode and ascii
    // characters to a byte offset.
    int32_t         utf8_StrOffset(
        const
        char            *pSrc,
        int32_t         offset          // Relative to 1
    );
    
    
    bool            utf8_isValidWC(
        int32_t         ch
    );
    
    
    // Utf8ToWC() converts the UTF-8 string to one UNICODE character
    // if possible and returns the length used of the UTF-8 string.
    // If an error occurred, -1 is returned for both the UNICODE
    // character and the length. If the UNICODE Pointer is NULL,
    // then the length or -1 is still returned.
    int             utf8_Utf8ToWC(
        const
        char            *pSrc,
        int32_t         *pChr       // Optional UNICODE Character Ptr
    );
    
    
    int32_t         utf8_Utf8ToWC_Scan(
        const
        char            **ppSrc
    );
    
    
    /*!
     utf8_WCToChrCon() converts the given UNICODE character to a
     NUL-terminated ascii string and returns its length.
     If pDest is NULL, we simply return the length needed
     excluding the NUL-terminator.
     */
    int             utf8_WCToChrCon(
        int32_t         chr,            // Input
        char            *pDest          // max 11-byte buffer
    );
    
    
    /*!
     WCToChrConStr() converts an input string to a character
     constant string and returns the size of the new string 
     excluding the NUL-terminator. If pDest is NULL, we cal-
     culate the size of area needed including NUL-terminator 
     and return that.
     */
    uint32_t         utf8_WCToUtf8Str(
        uint32_t        lenStr,       // Input String Length (if zero,
                                      // we use NUL-terminator to stop)
        const
        int32_t         *pStr,        // Input String pointer
        uint32_t        lenDest,      // In bytes including NUL
        char            *pDest
    );
    
    
    /* WCToUtf8() converts the given UNICODE character to a
     * NUL-terminated UTF-8 string and returns its length.
     * If pDest is NULL, we simply return the length needed
     * excluding the NUL-terminator.
     */
    int             utf8_WCToUtf8(
        int32_t         chr,            // Input
        char            *pDest          // max 7-byte buffer
    );
    
    
    /*!
    WCToUtf8Str() converts an input string to a UTF-8 character
    string and returns the size of the new string excluding the
    NUL-terminator. If pDest is NULL, we calculate the size of
    area needed including NUL-terminator and return that.
     */
    uint32_t         utf8_WCToUtf8Str(
        uint32_t        lenStr,       // Input String Length (if zero,
                                      // we use NUL-terminator to stop)
        const
        int32_t         *pStr,        // Input String pointer
        uint32_t        lenDest,      // In bytes including NUL
        char            *pDest
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    UTF8_DATA *     utf8_Init(
        UTF8_DATA       *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     Example:
     @code:
     ASTR_DATA      *pDesc = utf8_ToDebugString(pObj,4);
     @endcode:
     @param:    this    object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released,
     otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     utf8_ToDebugString(
        UTF8_DATA       *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* UTF8_H */

