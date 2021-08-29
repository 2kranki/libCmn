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
 *              tions are needed, then this becomes more necessary.
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
 *          0xD800 - 0xDBFF are encoded as 2 bytes with 0x3FF (10) bits.
 *          0xDC00 - 0xDFFF are encoded as 2 bytes with 0x3FF (10) bits.
 *          0xE000 - 0xFFFD are encoded as 2 bytes.
 *          0x010000 - 0x10FFFF are encoded as 4 byte sequences using:
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

    /*!
     utf8_Utf16beToW32() converts from UTF-16 to UTF-32
     */
    int             utf8_Utf16beToW32(
        const
        char            *pSrc,
        W32CHR_T        *pChr
    );
    
    int             utf8_Utf16leToW32(
        const
        char            *pSrc,
        W32CHR_T        *pChr
    );
    

    /* Alloc() allocates an area large enough for the utf8 including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    UTF8_DATA *     utf8_Alloc(
        void
    );
    

    OBJ_ID          utf8_Class(
        void
    );
    
    
    /*!
     Extract a UTF-8 string from a previously saved UTF-8 JSON String.
     @param     pInputString required pointer to JSON input string
     @return    If successful, a pointer to UTF-8 string which must be
                freed using mem_Free() and a returned length,
                 otherwise NULL and length of 0.
     @warning   Remember to free the returned UTF-8 string using mem_Free().
     */
    uint8_t *       utf8_DataFromJsonString(
        ASTR_DATA       *pInputString,
        uint32_t        *pLengthOut
    );
    
    uint8_t *       utf8_DataFromJsonStringA(
        const
        char            *pInputString,
        uint32_t        *pLengthOut
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @param     pData   pointer to a NUL-terminated UTF-8 string
     @return    If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     utf8_DataToJson(
        const
        char            *pData
    );
    
    
    /*!
     Compare the UTF-8 characters of src1 and src2.
     @return    0   for (src1 == src2),
                < 0 for (src1 < src2) or
                > 0 for (src1 > src2)
     */
    int             utf8_StrCmp(
        const
        char            *pSrc1,
        const
        char            *pSrc2
    );
    
    /*!
     Compare the UTF-8 characters of src1 and src2 ignoring case.
     @return    0   for (src1 == src2),
                < 0 for (src1 < src2) or
                > 0 for (src1 > src2)
     */
    int             utf8_StrCmp_IC(
        const
        char            *pSrc1,
        const
        char            *pSrc2
    );

    int             utf8_StrCmpAW32(
        const
        char            *pSrc1,
        const
        W32CHR_T        *pSrc2
    );
    
    /*!
     Compare at most the first N UTF-8 characters of src1 and src2.
     @return    0 for (src1 == src2), < 0 for (src1 < src2) or
                > 0 for (src1 > src2)
     */
    int             utf8_StrCmpN(
        const
        char            *pSrc1,
        const
        char            *pSrc2,
        uint32_t        N
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
    
    int             utf8_StrLenW32(
        const
        W32CHR_T        *pSrc
    );
    
    
    // Return the number of characters in the string
    // excluding the NUL-terminator (ie physical length).
    int             utf8_StrLenChars(
        const
        char            *pSrc
    );
    
    
    // Get the byte offset of a Unicode character in a UTF-8 string
    // given its Unicode offset.
    int32_t         utf8_StrOffset(
        const
        char            *pSrc,
        uint32_t        offset          // Relative to 1
    );
    
    
    bool            utf8_isValidW32(
        W32CHR_T        ch
    );
    
    
    /*!
     Convert a character constant to a Unicode Character string.
     @return    NULL for error; otherwise, a new Unicode Character
                String which must be released with mem_Free().
     */
    W32CHR_T *      utf8_ChrConToW32Str(
        const
        char            *pSrcA
    );


    /*!
     Convert a character constant to a Unicode Character incrementing
     the source pointer as data is used.
     @return    -1 for EOL or error; otherwise, a Unicode Character
     */
    W32CHR_T        utf8_ChrConToW32_Scan(
        const
        char            **ppSrc
    );
    
    
    /*!
     utf8_Utf8ToChrConStr() converts the given UTF-8 string to a
     NUL-terminated ascii string and returns its length.
     If pDest is NULL, it simply returns the length needed
     including the NUL-terminator.
     */
    uint32_t         utf8_Utf8ToChrConStr(
        uint32_t        lenStr,         // Input String Length (if zero,
        //                              // we use NUL-terminator to stop)
        const
        char            *pStrA,         // Input String pointer
        uint32_t        lenDest,        // in bytes including NUL
        char            *pDest
    );


    /*!
     Convert the UTF-8 input string to a NUL-terminated UTF-32 string
     or calculates the size of the area needed to do the conversion.
     @param     lenStrA length of input string excluding NUL-terminator
                        (0 == calculate string length)
     @param     pStrA   UTF-8 String Pointer
     @param     lenDest length of output string including NUL-terminator
                        (Optional if pDestW32 is NULL)
     @param     pDest   UTF-32 String Pointer
                        (if NULL, just return length needed)
     @return    If successful, length of the string used in pDest excluding
                NUL-terminator or the calculated length needed which includes
                a NUL-terminator; otherwise, -1.
     */
    int32_t         utf8_Utf8StrToW32Str(
        uint32_t        lenStrA,        // Input String Length (if zero,
        //                              // we use NUL-terminator to stop)
        const
        char            *pStrA,         // Input String pointer
        uint32_t        lenDest,        // in bytes including NUL
        W32CHR_T        *pDest
    );


    // Utf8ToW32() converts the UTF-8 string to one UNICODE character
    // if possible and returns the length used of the UTF-8 string.
    // If an error occurred, -1 is returned for both the UNICODE
    // character and the length. If the UNICODE Pointer is NULL,
    // then the length or -1 is still returned.
    int             utf8_Utf8ToW32(
        const
        char            *pSrc,
        W32CHR_T        *pChr       // Optional UNICODE Character Ptr
    );
    
    
    W32CHR_T        utf8_Utf8ToW32_Scan(
        const
        char            **ppSrc
    );
    
    
    /*!
     utf8_W32ToChrCon() converts the given UNICODE character to a
     NUL-terminated ascii string and returns its length.
     If pDest is NULL, we simply return the length needed
     excluding the NUL-terminator.
     */
    int             utf8_W32ToChrCon(
        W32CHR_T        chr,            // Input
        char            *pDest          // max 11-byte buffer
    );
    
    
    int             utf8_W32ToUtf16be(
        W32CHR_T        wc,
        char            *pSrc
    );
    
    int             utf8_W32ToUtf16le(
        W32CHR_T        wc,
        char            *pSrc
    );

    
    /*!
     Convert the UTF-32 input string to a NUL-terminated UTF-8
     string or calculates the length needed to do the conversion.
     @param     lenStr  length of input string excluding NUL-terminator
                        (0 == calculate string length)
     @param     pStrW32 UTF-32 String Pointer
     @param     lenDest length of output string including NUL-terminator
                        (Optional if pDest is NULL)
     @param     pDest   UTF-8 String Pointer
                        (if NULL, just return length needed)
     @return    If successful, length of the string used in pDest excluding
                NUL-terminator or the calculated length needed which includes
                a NUL-terminator; otherwise, -1.
     */
    int32_t         utf8_W32StrToUtf8Str(
        uint32_t        lenStr,       // Input String Length (if zero,
                                      // we use NUL-terminator to stop)
        const
        W32CHR_T        *pStrW32,     // Input String pointer
        uint32_t        lenDest,      // output area size including NUL
        char            *pDest
    );
    
    
    /* W32ToUtf8() converts the given UNICODE character to a
     * NUL-terminated UTF-8 string and returns its length.
     * If pDest is NULL, we simply return the length needed
     * excluding the NUL-terminator.
     */
    int             utf8_W32ToUtf8(
        W32CHR_T        chr,            // Input
        char            *pDest          // max 7-byte buffer
    );
    
    
    /*!
    W32ToUtf8Str() converts an input string to a UTF-8 character
    string and returns the size of the new string excluding the
    NUL-terminator. If pDest is NULL, we calculate the size of
    area needed including NUL-terminator and return that.
     */
    int32_t         utf8_W32StrToUtf8Str(
        uint32_t        lenStr,       // Input String Length (if zero,
                                      // we use NUL-terminator to stop)
        const
        W32CHR_T        *pStr,        // Input String pointer
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
     @code
     ASTR_DATA      *pDesc = utf8_ToDebugString(pObj,4);
     @endcode
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released,
                 otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     utf8_ToDebugString(
        UTF8_DATA       *this,
        int             indent
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* UTF8_H */

