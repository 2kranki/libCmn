// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   utf8.c
 *
 * Notes:
 *  1.  We chose to use integers to represent the wide characters. Other formats
 *      seemed to create longer strings.
 *
 * Generated 08/06/2015 20:23:35
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include    <utf8_internal.h>
#include    <ascii.h>
#include    <hex.h>
#include    <stdarg.h>
#include    <stdbool.h>
#include    <stdint.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

#ifdef XYZZY
    static
    const
    W32CHR_T        offsetsFromUTF8[6] = {
        0x00000000UL,
        0x00003080UL,
        0x000E2080UL,
        0x03C82080UL,
        0xFA082080UL,
        0x82082080UL
    };

    
    static
    const
    char            trailingBytesForUTF8[256] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
    };
#endif
    

    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/


    /* returns length of next utf-8 sequence */
#ifdef XYZZY
    static
    int             utf8_seqlen(
        char            *s
    )
    {
        return trailingBytesForUTF8[(unsigned int)(unsigned char)s[0]] + 1;
    }
#endif
    


    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    UTF8_DATA *     utf8_Alloc(
    )
    {
        UTF8_DATA       *this;
        uint32_t        cbSize = sizeof(UTF8_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    int             utf8_StrCmp(
        const
        char            *pSrc1,
        const
        char            *pSrc2
    )
    {
        W32CHR_T        ch1 = 1;
        W32CHR_T        ch2 = 1;
        int             i = 0;
        
        if ((NULL == pSrc1) && (NULL == pSrc2)) {
            return 0;
        }
        if ((NULL == pSrc1) && pSrc2) {
            return -1;
        }
        if ((NULL == pSrc2) && pSrc1) {
            return 1;
        }
        
        while ((i == 0) && ch1 && ch2) {
            ch1 = utf8_Utf8ToW32_Scan( &pSrc1 );
            ch2 = utf8_Utf8ToW32_Scan( &pSrc2 );
            i = ch1 - ch2;
        }
        if (i == 0) {
            if (ch1) {
                i = 1;
            }
            if (ch2) {
                i = -1;
            }
        }
        
        return i;
    }
    
    
    
    int             utf8_StrCmpAW32(
        const
        char            *pSrc1,
        const
        W32CHR_T        *pSrc2
    )
    {
        W32CHR_T        ch1 = 1;
        W32CHR_T        ch2 = 1;
        int             i = 0;
        
        if ((NULL == pSrc1) && (NULL == pSrc2)) {
            return 0;
        }
        if ((NULL == pSrc1) && pSrc2) {
            return -1;
        }
        if ((NULL == pSrc2) && pSrc1) {
            return 1;
        }
        
        while ((i == 0) && ch1 && ch2) {
            ch1 = utf8_Utf8ToW32_Scan( &pSrc1 );
            ch2 = *pSrc2++;
            i = ch1 - ch2;
        }
        if (i == 0) {
            if (ch1) {
                i = 1;
            }
            if (ch2) {
                i = -1;
            }
        }
        
        return i;
    }
    
    
    
    int             utf8_StrNCmp(
        const
        char            *pSrc1,
        const
        char            *pSrc2,
        uint32_t        len
    )
    {
        W32CHR_T        ch1 = 1;
        W32CHR_T        ch2 = 1;
        int             i = 0;
        
        if ((NULL == pSrc1) && (NULL == pSrc2)) {
            return 0;
        }
        if ((NULL == pSrc1) && pSrc2) {
            return -1;
        }
        if ((NULL == pSrc2) && pSrc1) {
            return 1;
        }
        
        while ((i == 0) && ch1 && ch2 && len--) {
            ch1 = utf8_Utf8ToW32_Scan( &pSrc1 );
            ch2 = utf8_Utf8ToW32_Scan( &pSrc2 );
            i = ch1 - ch2;
        }
        if (i < 0) {
            i = -1;
        }
        if (i > 0) {
            i = 1;
        }
        
        return i;
    }
    
    
    
    char *          utf8_StrDup(
        const
        char            *pSrc
    )
    {
        char            *pStr;
        
        /* UTF-8 is just a string of bytes with a NUL-terminator
         * so casting to mem_StrDup should work.
         */
        pStr = (char *)mem_StrDup((const char *)pSrc);
        
        return pStr;
    }
    
    
    
    int             utf8_ChrLen(
        const
        char            src
    )
    {
        
            if ((src & 0x80) == 0) {
                return 1;
            }
            else if ((src & 0xE0) == 0xC0) {
                return 2;
            }
            else if ((src & 0xF0) == 0xE0) {
                return 3;
            }
            else if ((src & 0xFC) == 0xF8) {
                return 4;
            }
        
        return -1;
    }
    
    
    
    int             utf8_StrLenA(
        const
        char            *pSrc
    )
    {
        int             len = 0;

        if (pSrc == NULL) {
            return 0;
        }
        while (*pSrc) {
            if ((pSrc[0] & 0x80) == 0) {
                len += 1;
                pSrc += 1;
            }
            else if (((pSrc[0] & 0xE0) == 0xC0)
                     && ((pSrc[1] & 0xC0) == 0x80)) {
                len += 1;
                pSrc += 2;
            }
            else if (((pSrc[0] & 0xF0) == 0xE0)
                     && ((pSrc[1] & 0xC0) == 0x80)
                     && ((pSrc[2] & 0xC0) == 0x80)) {
                len += 1;
                pSrc += 3;
            }
            else if (((pSrc[0] & 0xFC) == 0xF8)
                     && ((pSrc[1] & 0xC0) == 0x80)
                     && ((pSrc[2] & 0xC0) == 0x80)
                     && ((pSrc[3] & 0xC0) == 0x80)) {
                len += 1;
                pSrc += 4;
            }
            else {
                return -1;
            }
        }
        
        return len;
    }
    
    
    
    int             utf8_StrLenW32(
        const
        W32CHR_T        *pSrc
    )
    {
        int             len = 0;
        
        while (*pSrc++) {
            len += 1;
        }
        
        return len;
    }
    
    
    
    int             utf8_StrLenChars(
        const
        char            *pSrc
    )
    {
        int             len = 0;
        
        if (pSrc) {
            while (*pSrc++) {
                ++len;
            }
        }
        
        return len;
    }
    
    
    
    int32_t         utf8_StrOffset(
        const
        char            *pSrc,
        uint32_t        offset          // Relative to 1
    )
    {
        const
        char            *pBgn = pSrc;
        int32_t         len = 0;
        
        if ((NULL == pSrc) || (offset < 1)) {
            return -1;
        }
        --offset;
        
        while (*pSrc && (len < offset)) {
            if ((pSrc[0] & 0x80) == 0) {
                len += 1;
                pSrc += 1;
            }
            else if (((pSrc[0] & 0xE0) == 0xC0)
                     && ((pSrc[1] & 0xC0) == 0x80)) {
                len += 1;
                pSrc += 2;
            }
            else if (((pSrc[0] & 0xF0) == 0xE0)
                     && ((pSrc[1] & 0xC0) == 0x80)
                     && ((pSrc[2] & 0xC0) == 0x80)) {
                len += 1;
                pSrc += 3;
            }
            else if (((pSrc[0] & 0xFC) == 0xF8)
                     && ((pSrc[1] & 0xC0) == 0x80)
                     && ((pSrc[2] & 0xC0) == 0x80)
                     && ((pSrc[3] & 0xC0) == 0x80)) {
                len += 1;
                pSrc += 4;
            }
            else {
                return -1;
            }
        }
        if (len == offset) {
            len = (int32_t)(pSrc - pBgn) + 1;
        }
        else {
            len = -1;
        }
        
        return len;
    }
    
    
    
    W32CHR_T        utf8_ChrConToW32_Scan(
        const
        char            **ppSrc
    )
    {
        char            wrk;
        W32CHR_T        ch = 0;

        if (**ppSrc == '\0')
            return -1;
        
        // Look for escaped sequence.
        if (**ppSrc == '\\') {
            wrk = *(*ppSrc + 1);
            switch (wrk) {
                case '\\':
                    *ppSrc += 2;
                    return '\\';
                    break;
                case '\"':
                    *ppSrc += 2;
                    return '\"';
                    break;
                case 'f':
                    *ppSrc += 2;
                    return '\f';
                    break;
                case 'n':
                    *ppSrc += 2;
                    return '\n';
                    break;
                case 'r':
                    *ppSrc += 2;
                    return '\r';
                    break;
                case 't':
                    *ppSrc += 2;
                    return '\t';
                    break;
                case 'x':
                    ch  = hex_DigitToIntA(*(*ppSrc + 2)) << 4;
                    ch |= hex_DigitToIntA(*(*ppSrc + 3));
                    *ppSrc += 4;
                    return ch;
                    break;
                case 'u':
                    ch  = hex_DigitToIntA(*(*ppSrc + 2)) << 12;
                    ch |= hex_DigitToIntA(*(*ppSrc + 3)) << 8;
                    ch |= hex_DigitToIntA(*(*ppSrc + 4)) << 4;
                    ch |= hex_DigitToIntA(*(*ppSrc + 5));
                    *ppSrc += 6;
                    return ch;
                    break;
                case 'U':
                    ch  = hex_DigitToIntA(*(*ppSrc + 2)) << 28;
                    ch |= hex_DigitToIntA(*(*ppSrc + 3)) << 24;
                    ch |= hex_DigitToIntA(*(*ppSrc + 4)) << 20;
                    ch |= hex_DigitToIntA(*(*ppSrc + 5)) << 16;
                    ch |= hex_DigitToIntA(*(*ppSrc + 6)) << 12;
                    ch |= hex_DigitToIntA(*(*ppSrc + 7)) <<  8;
                    ch |= hex_DigitToIntA(*(*ppSrc + 8)) <<  4;
                    ch |= hex_DigitToIntA(*(*ppSrc + 9));
                    *ppSrc += 10;
                    return ch;
                    break;
                default:
                    return -1;
            }
        }
        
        ch = **ppSrc;
        *ppSrc += 1;
        return ch;
    }
    
    
    
    W32CHR_T *      utf8_ChrConToW32Str(
        const
        char            *pSrc
    )
    {
        W32CHR_T        *pW32Str = NULL;
        W32CHR_T        *pW32Wrk = NULL;
        W32CHR_T        ch = 0;
        uint32_t        len;
        uint32_t        i;

        
        if (pSrc == NULL)
            return NULL;
        len = (uint32_t)utf8_StrLenA(pSrc);

        pW32Str = mem_Malloc((len + 1) * sizeof(W32CHR_T));
        if (NULL == pW32Str) {
            DEBUG_BREAK();
            return NULL;
        }
        
        pW32Wrk = pW32Str;
        for (i=0; i<len; ++i) {
            ch = utf8_Utf8ToW32_Scan(&pSrc);
            *pW32Wrk++ = ch;
        }
        *pW32Wrk = '\0';

        return pW32Str;
    }
    
    
    
    int             utf8_Utf16beToW32(
        const
        char            *pSrc,
        W32CHR_T        *pChr
    )
    {
        W32CHR_T        ch;
        uint16_t        first = 0;
        uint16_t        second = 0;
        int             i = 2;
        
        first = ((uint8_t)pSrc[1] & 0xFF) | ((uint8_t)pSrc[0] << 8);
        ch = first;
        if ((first >= 0xD800) && (first <= 0xDBFF)) {
            second = ((uint8_t)pSrc[3] & 0xFF) | ((uint8_t)pSrc[2] << 8);
            if ((second >= 0xDC00) && (second <= 0xDFFF)) {
                ch = 0x10000 + ((first & 0x03FF) | ((second & 0x03FF) << 10));
                i = 4;
            }
            else {
                return -1;
            }
        }
        
        if (pChr) {
            *pChr = ch;
        }
        return i;
    }
    
    
    
    int             utf8_Utf16leToW32(
        const
        char            *pSrc,
        W32CHR_T        *pChr
    )
    {
        W32CHR_T        ch;
        uint16_t        first = 0;
        uint16_t        second = 0;
        int             i = 2;

        first = ((uint8_t)pSrc[0] & 0xFF) | ((uint8_t)pSrc[1] << 8);
        ch = first;
        if ((first >= 0xD800) && (first <= 0xDBFF)) {
            second = ((uint8_t)pSrc[2] & 0xFF) | ((uint8_t)pSrc[3] << 8);
            if ((second >= 0xDC00) && (second <= 0xDFFF)) {
                ch = 0x10000 + ((first & 0x03FF) | ((second & 0x03FF) << 10));
                i = 4;
            }
            else {
                return -1;
            }
        }
        
        if (pChr) {
            *pChr = ch;
        }
        return i;
    }
    
    
    
    int             utf8_Utf8ToW32(
        const
        char            *pSrc,
        W32CHR_T        *pChr
    )
    {
        W32CHR_T        ch = -1;
        int             i = -1;
        
        if ((pSrc == NULL) || (*pSrc == '\0')) {
            if (pChr) {
                *pChr = 0;
            }
            return 0;
        }
        if ((pSrc[0] & 0x80) == 0) {
            ch = pSrc[0];
            i = 1;
        }
        else if (((pSrc[0] & 0xE0) == 0xC0)
                 && ((pSrc[1] & 0xC0) == 0x80)) {
            ch = ((pSrc[0] & 0x1F) << 6)
                    | (pSrc[1] & 0x3F);
            i = 2;
        }
        else if (((pSrc[0] & 0xF0) == 0xE0)
                 && ((pSrc[1] & 0xC0) == 0x80)
                 && ((pSrc[2] & 0xC0) == 0x80)) {
            ch = ((pSrc[0] & 0x0F) << 12)
                    | ((pSrc[1] & 0x3F) << 6)
                    | (pSrc[2] & 0x3F);
            i = 3;
        }
        else if (((pSrc[0] & 0xFC) == 0xF8)
                 && ((pSrc[1] & 0xC0) == 0x80)
                 && ((pSrc[2] & 0xC0) == 0x80)
                 && ((pSrc[3] & 0xC0) == 0x80)) {
            ch = ((pSrc[0] & 0x07) << 18)
                    | ((pSrc[1] & 0x3F) << 12)
                    | ((pSrc[2] & 0x3F) << 6)
                    | (pSrc[3] & 0x3F);
            i = 4;
        }
        
        if (pChr) {
            *pChr = ch;
        }
        return i;
    }
    
    
    
    W32CHR_T        utf8_Utf8ToW32_Scan(
        const
        char            **ppSrc
    )
    {
        W32CHR_T        ch = -1;
        
        if ((**ppSrc & 0x80) == 0) {
            ch = *ppSrc[0];
            *ppSrc += 1;
        }
        else if (((**ppSrc & 0xE0) == 0xC0)
                 && ((*(*ppSrc+1) & 0xC0) == 0x80)) {
            ch = ((**ppSrc & 0x1F) << 6)
                    | (*(*ppSrc+1) & 0x3F);
            *ppSrc += 2;
        }
        else if (((**ppSrc & 0xF0) == 0xE0)
                 && ((*(*ppSrc+1) & 0xC0) == 0x80)
                 && ((*(*ppSrc+2) & 0xC0) == 0x80)) {
            ch = ((*ppSrc[0] & 0x0F) << 12)
                    | ((*(*ppSrc+1) & 0x3F) << 6)
                    | (*(*ppSrc+2) & 0x3F);
            *ppSrc += 3;
        }
        else if (((**ppSrc & 0xFC) == 0xF8)
                 && ((*(*ppSrc+1) & 0xC0) == 0x80)
                 && ((*(*ppSrc+2) & 0xC0) == 0x80)
                 && ((*(*ppSrc+3) & 0xC0) == 0x80)) {
            ch = ((**ppSrc & 0x07) << 18)
                    | ((*(*ppSrc+1) & 0x3F) << 12)
                    | ((*(*ppSrc+2) & 0x3F) << 6)
                    | (*(*ppSrc+3) & 0x3F);
            *ppSrc += 4;
        }
        
        return ch;
    }
    
    
    
    bool            utf8_isValidW32(
        W32CHR_T        ch
    )
    {
        if ((ch <= 0x0000) && (ch <= 0x07BF)) {
            return true;
        }
        if ((ch <= 0x0900) && (ch <= 0x137F)) {
            return true;
        }
        if ((ch <= 0x13A0) && (ch <= 0x18AF)) {
            return true;
        }
        if ((ch <= 0x1900) && (ch <= 0x197F)) {
            return true;
        }
        if ((ch <= 0x19E0) && (ch <= 0x19FF)) {
            return true;
        }
        if ((ch <= 0x1D00) && (ch <= 0x1D7F)) {
            return true;
        }
        if ((ch <= 0x1E00) && (ch <= 0x2BFF)) {
            return true;
        }
        if ((ch <= 0x2E80) && (ch <= 0x2FDF)) {
            return true;
        }
        if ((ch <= 0x2FF0) && (ch <= 0x31BF)) {
            return true;
        }
        if ((ch <= 0x31F0) && (ch <= 0xA4CF)) {
            return true;
        }
        if ((ch <= 0xAC00) && (ch <= 0xFE0F)) {
            return true;
        }
        if ((ch <= 0xFE20) && (ch <= 0x1013F)) {
            return true;
        }
        if ((ch <= 0x10300) && (ch <= 0x1034F)) {
            return true;
        }
        if ((ch <= 0x10380) && (ch <= 0x1039F)) {
            return true;
        }
        if ((ch <= 0x10400) && (ch <= 0x104AF)) {
            return true;
        }
        if ((ch <= 0x10800) && (ch <= 0x1083F)) {
            return true;
        }
        if ((ch <= 0x1D000) && (ch <= 0x1D1FF)) {
            return true;
        }
        if ((ch <= 0x1D300) && (ch <= 0x1D35F)) {
            return true;
        }
        if ((ch <= 0x1D400) && (ch <= 0x1D7FF)) {
            return true;
        }
        if ((ch <= 0x20000) && (ch <= 0x2A6DF)) {
            return true;
        }
        if ((ch <= 0x2F800) && (ch <= 0x2FA1F)) {
            return true;
        }
        if ((ch <= 0xE0000) && (ch <= 0xE007F)) {
            return true;
        }
        if ((ch <= 0xE0100) && (ch <= 0xE01EF)) {
            return true;
        }
        return false;
    }
    
    
    
    int             utf8_W32ToChrCon(
        W32CHR_T        ch,
        char            *pDest          // max 10-byte buffer.
    )
    {
        if (ch < 256) {
            switch (ch) {
                    
                case 9:
                    if (pDest) {
                        *pDest++ = '\\';
                        *pDest++ = 't';
                        *pDest = '\0';
                    }
                    return 2;
                    break;
                    
                case 10:
                    if (pDest) {
                        *pDest++ = '\\';
                        *pDest++ = 'n';
                        *pDest = '\0';
                    }
                    return 2;
                    break;
                    
                case 11:
                    if (pDest) {
                        *pDest++ = '\\';
                        *pDest++ = 'v';
                        *pDest = '\0';
                    }
                    return 2;
                    break;
                    
                case 12:
                    if (pDest) {
                        *pDest++ = '\\';
                        *pDest++ = 'f';
                        *pDest = '\0';
                    }
                    return 2;
                    break;
                    
                case 13:
                    if (pDest) {
                        *pDest++ = '\\';
                        *pDest++ = 'r';
                        *pDest = '\0';
                    }
                    return 2;
                    break;
                    
                case '"':
                    if (pDest) {
                        *pDest++ = '\\';
                        *pDest++ = '"';
                        *pDest = '\0';
                    }
                    return 2;
                    break;
                    
                default:
                    if (ascii_isAsciiW32(ch) && ascii_isPrintableA(ch)) {
                        if (pDest) {
                            *pDest++ = ch;
                            *pDest = '\0';
                        }
                        return 1;
                    }
                    if (pDest) {
                        *pDest++ = '\\';
                        *pDest++ = 'x';
                        *pDest++ = hex_DigitToChrA((ch >> 4) & 0xF);
                        *pDest++ = hex_DigitToChrA(ch & 0xF);
                        *pDest = '\0';
                    }
                    return 4;
                    break;
            }
        }
        else if (ch < 65236) {
            if (pDest) {
                *pDest++ = '\\';
                *pDest++ = 'u';
                *pDest++ = hex_DigitToChrA((ch >> 12) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 8) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 4) & 0xF);
                *pDest++ = hex_DigitToChrA(ch & 0xF);
                *pDest = '\0';
            }
            return 6;
        }
        else {
            if (pDest) {
                *pDest++ = '\\';
                *pDest++ = 'U';
                *pDest++ = hex_DigitToChrA((ch >> 28) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 24) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 20) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 16) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 12) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 8) & 0xF);
                *pDest++ = hex_DigitToChrA((ch >> 4) & 0xF);
                *pDest++ = hex_DigitToChrA(ch & 0xF);
                *pDest = '\0';
            }
            return 10;
        }
        return 0;
    }
    
    
    
    uint32_t         utf8_W32ToChrConStr(
        uint32_t        lenStr,         // Input String Length (if zero,
        //                              // we use NUL-terminator to stop)
        const
        W32CHR_T        *pStr,          // Input String pointer
        uint32_t        lenDest,        // in bytes including NUL
        char            *pDest
    )
    {
        uint32_t        lenUsed = 0;    // In bytes exluding NUL
        uint32_t        lenChr;
        
        if (0 == lenStr) {
            lenStr = -1;
        }
        
        while (lenStr && *pStr) {
            lenChr = utf8_W32ToChrCon(*pStr, NULL);
            if (pDest) {
                if (lenChr <= lenDest) {
                    lenUsed += utf8_W32ToChrCon(*pStr, pDest);
                    pDest += lenChr;
                    lenDest -= lenChr;
                }
                else
                    break;
            }
            else {
                lenUsed += lenChr;
            }
            ++pStr;
            --lenStr;
        }
        if (pDest && lenDest) {
            *pDest = '\0';
        }
        else {
            ++lenUsed;      // bump for NUL-terminator
        }
        
        return lenUsed;
    }
    
    
    
    int             utf8_W32ToUtf16be(
        W32CHR_T        wc,
        char            *pSrc
    )
    {
        uint16_t        first = 0;
        uint16_t        second = 0;
        int             i = 2;
        
        if (wc >= 0x10000) {
            wc -= 0x10000;
            first = 0xD800 | (wc & 0x03FF);
            second = 0xDC00 | ((wc >> 10) & 0x03FF);
            pSrc[0] = (first >> 8) & 0xFF;
            pSrc[1] = first & 0xFF;
            pSrc[2] = (second >> 8) & 0xFF;
            pSrc[3] = second & 0xFF;
            i = 4;
        }
        else {
            first = wc & 0x03FF;
            pSrc[0] = (first >> 8) & 0xFF;
            pSrc[1] = first & 0xFF;
        }
        
        return i;
    }
    
    
    
    int             utf8_W32ToUtf16le(
        W32CHR_T        wc,
        char            *pSrc
    )
    {
        uint16_t        first = 0;
        uint16_t        second = 0;
        int             i = 2;
        
        if (wc >= 0x10000) {
            wc -= 0x10000;
            first = 0xD800 | (wc & 0x03FF);
            second = 0xDC00 | ((wc >> 10) & 0x03FF);
            pSrc[0] = first & 0xFF;
            pSrc[1] = (first >> 8) & 0xFF;
            pSrc[2] = second & 0xFF;
            pSrc[3] = (second >> 8) & 0xFF;
            i = 4;
        }
        else {
            first = wc & 0x03FF;
            pSrc[0] = first & 0xFF;
            pSrc[1] = (first >> 8) & 0xFF;
        }
        
        return i;
    }
    
    
    
    int             utf8_W32ToUtf8(
        W32CHR_T        ch,
        char            *pDest          // max 5-byte buffer.
    )
    {
        if (ch < 0x80) {
            if (pDest) {
                pDest[0] = (char)ch;
                pDest[1] = '\0';
            }
            return 1;
        }
        if (ch < 0x800) {
            if (pDest) {
                pDest[0] = (ch>>6) | 0xC0;
                pDest[1] = (ch & 0x3F) | 0x80;
                pDest[2] = '\0';
            }
            return 2;
        }
        if (ch < 0x10000) {
            if (pDest) {
                pDest[0] = (ch>>12) | 0xE0;
                pDest[1] = ((ch>>6) & 0x3F) | 0x80;
                pDest[2] = (ch & 0x3F) | 0x80;
                pDest[3] = '\0';
            }
            return 3;
        }
        if (ch < 0x110000) {
            if (pDest) {
                pDest[0] = (ch>>18) | 0xF0;
                pDest[1] = ((ch>>12) & 0x3F) | 0x80;
                pDest[2] = ((ch>>6) & 0x3F) | 0x80;
                pDest[3] = (ch & 0x3F) | 0x80;
                pDest[4] = '\0';
            }
            return 4;
        }
        if (pDest) {
            pDest[0] = '\0';
        }
        return 0;
    }
    


    uint32_t         utf8_W32ToUtf8Str(
        uint32_t        lenStr,         // Input String Length (if zero,
                                        // we use NUL-terminator to stop)
        const
        W32CHR_T        *pStr,          // Input String pointer
        uint32_t        lenDest,        // in bytes including NUL
        char            *pDest
    )
    {
        uint32_t        lenUsed = 0;    // In bytes exluding NUL
        uint32_t        lenChr;

        if (0 == lenStr) {
            lenStr = -1;
        }
        
        while (lenStr && *pStr) {
            lenChr = utf8_W32ToUtf8(*pStr, NULL);
            if (pDest) {
                if (lenChr <= lenDest) {
                    lenUsed += utf8_W32ToUtf8(*pStr, pDest);
                    pDest += lenChr;
                    lenDest -= lenChr;
                }
                else
                    break;
            }
            else {
                lenUsed += lenChr;
            }
            ++pStr;
            --lenStr;
        }
        if (pDest && lenDest) {
            *pDest = '\0';
        }
        else {
            ++lenUsed;      // bump for NUL-terminator
        }
        
        return lenUsed;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        utf8_getPriority(
        UTF8_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !utf8_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            utf8_setPriority(
        UTF8_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !utf8_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        utf8_getSize(
        UTF8_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !utf8_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            utf8_Dealloc(
        OBJ_ID          objId
    )
    {
        UTF8_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !utf8_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    UTF8_DATA *   utf8_Init(
        UTF8_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_UTF8 );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&utf8_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);

    #ifdef NDEBUG
    #else
        if( !utf8_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            utf8_IsEnabled(
        UTF8_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !utf8_Validate(cbp) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(cbp))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     utf8_ToDebugString(
        UTF8_DATA       *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(utf8) \n",
                     this
                     );
        AStr_AppendA(pStr, str);
        
#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                                               this->pData,
                                                                               indent+3
                                                                               );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p(utf8)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            utf8_Validate(
        UTF8_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_UTF8) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(UTF8_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif




#ifdef XYZZY
/*
 Basic UTF-8 manipulation routines
 by Jeff Bezanson
 placed in the public domain Fall 2005
 
 This code is designed to provide the utilities you need to manipulate
 UTF-8 as an internal string encoding. These functions do not perform the
 error checking normally needed when handling UTF-8 data, so if you happen
 to be from the Unicode Consortium you will want to flay me alive.
 I do this because error checking can be performed at the boundaries (I/O),
 with these routines reserved for higher performance on data known to be
 valid.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#ifdef WIN32
#include <malloc.h>
#else
#include <alloca.h>
#endif

/* conversions without error checking
 only works for valid UTF-8, i.e. no 5- or 6-byte sequences
 srcsz = source size in bytes, or -1 if 0-terminated
 sz = dest size in # of wide characters
 
 returns # characters converted
 dest will always be L'\0'-terminated, even if there isn't enough room
 for all the characters.
 if sz = srcsz+1 (i.e. 4*srcsz+4 bytes), there will always be enough space.
 */
int                 u8_toucs(
    int                 sz,         // Size of pDest in Wide Chars
    uint32_t            *pDest,
    int                 srcsz,
    char                *src
)
{
    uint32_t            ch;
    char                *src_end = src + srcsz;
    int                 nb;
    int                 i = 0;
    
    while (i < sz-1) {
        nb = trailingBytesForUTF8[(unsigned char)*src];
        if (srcsz == -1) {
            if (*src == 0)
                goto done_toucs;
        }
        else {
            if (src + nb >= src_end)
                goto done_toucs;
        }
        ch = 0;
        switch (nb) {
                /* these fall through deliberately */
            case 3:
                ch += (unsigned char)*src++;
                ch <<= 6;
            case 2:
                ch += (unsigned char)*src++;
                ch <<= 6;
            case 1:
                ch += (unsigned char)*src++;
                ch <<= 6;
            case 0:
                ch += (unsigned char)*src++;
        }
        ch -= offsetsFromUTF8[nb];
        pDest[i++] = ch;
    }
done_toucs:
    pDest[i] = 0;
    return i;
}



/* srcsz = number of source characters, or -1 if 0-terminated
 sz = size of dest buffer in bytes
 
 returns # characters converted
 dest will only be '\0'-terminated if there is enough space. this is
 for consistency; imagine there are 2 bytes of space left, but the next
 character requires 3 bytes. in this case we could NUL-terminate, but in
 general we can't when there's insufficient space. therefore this function
 only NUL-terminates if all the characters fit, and there's space for
 the NUL as well.
 the destination string will never be bigger than the source string.
 */
int u8_ToUtf8(char *dest, int sz, u_int32_t *src, int srcsz)
{
    u_int32_t ch;
    int i = 0;
    char *dest_end = dest + sz;
    
    while (srcsz<0 ? src[i]!=0 : i < srcsz) {
        ch = src[i];
        if (ch < 0x80) {
            if (dest >= dest_end)
                return i;
            *dest++ = (char)ch;
        }
        else if (ch < 0x800) {
            if (dest >= dest_end-1)
                return i;
            *dest++ = (ch>>6) | 0xC0;
            *dest++ = (ch & 0x3F) | 0x80;
        }
        else if (ch < 0x10000) {
            if (dest >= dest_end-2)
                return i;
            *dest++ = (ch>>12) | 0xE0;
            *dest++ = ((ch>>6) & 0x3F) | 0x80;
            *dest++ = (ch & 0x3F) | 0x80;
        }
        else if (ch < 0x110000) {
            if (dest >= dest_end-3)
                return i;
            *dest++ = (ch>>18) | 0xF0;
            *dest++ = ((ch>>12) & 0x3F) | 0x80;
            *dest++ = ((ch>>6) & 0x3F) | 0x80;
            *dest++ = (ch & 0x3F) | 0x80;
        }
        i++;
    }
    if (dest < dest_end)
        *dest = '\0';
    return i;
}



/* charnum => byte offset */
int u8_offset(char *str, int charnum)
{
    int offs=0;
    
    while (charnum > 0 && str[offs]) {
        (void)(isutf(str[++offs]) || isutf(str[++offs]) ||
               isutf(str[++offs]) || ++offs);
        charnum--;
    }
    return offs;
}



/* byte offset => charnum */
int u8_charnum(char *s, int offset)
{
    int charnum = 0, offs=0;
    
    while (offs < offset && s[offs]) {
        (void)(isutf(s[++offs]) || isutf(s[++offs]) ||
               isutf(s[++offs]) || ++offs);
        charnum++;
    }
    return charnum;
}



/* number of characters */
int u8_strlen(char *s)
{
    int count = 0;
    int i = 0;
    
    while (u8_nextchar(s, &i) != 0)
        count++;
    
    return count;
}



/* reads the next utf-8 sequence out of a string, updating an index */
uint32_t u8_nextchar(char *s, int *i)
{
    uint32_t    ch = 0;
    int         sz = 0;
    
    do {
        ch <<= 6;
        ch += (unsigned char)s[(*i)++];
        sz++;
    } while (s[*i] && !isutf(s[*i]));
    ch -= offsetsFromUTF8[sz-1];
    
    return ch;
}



void u8_inc(char *s, int *i)
{
    (void)(isutf(s[++(*i)]) || isutf(s[++(*i)]) ||
           isutf(s[++(*i)]) || ++(*i));
}

void u8_dec(char *s, int *i)
{
    (void)(isutf(s[--(*i)]) || isutf(s[--(*i)]) ||
           isutf(s[--(*i)]) || --(*i));
}

int octal_digit(char c)
{
    return (c >= '0' && c <= '7');
}

int hex_digit(char c)
{
    return ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'F') ||
            (c >= 'a' && c <= 'f'));
}



/* assumes that src points to the character after a backslash
 returns number of input characters processed */
int u8_read_escape_sequence(char *str, u_int32_t *dest)
{
    u_int32_t ch;
    char digs[9]="\0\0\0\0\0\0\0\0";
    int dno=0, i=1;
    
    ch = (u_int32_t)str[0];    /* take literal character */
    if (str[0] == 'n')
        ch = L'\n';
    else if (str[0] == 't')
        ch = L'\t';
    else if (str[0] == 'r')
        ch = L'\r';
    else if (str[0] == 'b')
        ch = L'\b';
    else if (str[0] == 'f')
        ch = L'\f';
    else if (str[0] == 'v')
        ch = L'\v';
    else if (str[0] == 'a')
        ch = L'\a';
    else if (octal_digit(str[0])) {
        i = 0;
        do {
            digs[dno++] = str[i++];
        } while (octal_digit(str[i]) && dno < 3);
        ch = strtol(digs, NULL, 8);
    }
    else if (str[0] == 'x') {
        while (hex_digit(str[i]) && dno < 2) {
            digs[dno++] = str[i++];
        }
        if (dno > 0)
            ch = strtol(digs, NULL, 16);
    }
    else if (str[0] == 'u') {
        while (hex_digit(str[i]) && dno < 4) {
            digs[dno++] = str[i++];
        }
        if (dno > 0)
            ch = strtol(digs, NULL, 16);
    }
    else if (str[0] == 'U') {
        while (hex_digit(str[i]) && dno < 8) {
            digs[dno++] = str[i++];
        }
        if (dno > 0)
            ch = strtol(digs, NULL, 16);
    }
    *dest = ch;
    
    return i;
}



/* convert a string with literal \uxxxx or \Uxxxxxxxx characters to UTF-8
 example: u8_unescape(mybuf, 256, "hello\\u220e")
 note the double backslash is needed if called on a C string literal */
int u8_unescape(char *buf, int sz, char *src)
{
    int c=0, amt;
    u_int32_t ch;
    char temp[4];
    
    while (*src && c < sz) {
        if (*src == '\\') {
            src++;
            amt = u8_read_escape_sequence(src, &ch);
        }
        else {
            ch = (u_int32_t)*src;
            amt = 1;
        }
        src += amt;
        amt = u8_wc_toutf8(temp, ch);
        if (amt > sz-c)
            break;
        memcpy(&buf[c], temp, amt);
        c += amt;
    }
    if (c < sz)
        buf[c] = '\0';
    return c;
}



int u8_escape_wchar(char *buf, int sz, u_int32_t ch)
{
    if (ch == L'\n')
        return snprintf(buf, sz, "\\n");
    else if (ch == L'\t')
        return snprintf(buf, sz, "\\t");
    else if (ch == L'\r')
        return snprintf(buf, sz, "\\r");
    else if (ch == L'\b')
        return snprintf(buf, sz, "\\b");
    else if (ch == L'\f')
        return snprintf(buf, sz, "\\f");
    else if (ch == L'\v')
        return snprintf(buf, sz, "\\v");
    else if (ch == L'\a')
        return snprintf(buf, sz, "\\a");
    else if (ch == L'\\')
        return snprintf(buf, sz, "\\\\");
    else if (ch < 32 || ch == 0x7f)
        return snprintf(buf, sz, "\\x%hhX", (unsigned char)ch);
    else if (ch > 0xFFFF)
        return snprintf(buf, sz, "\\U%.8X", (u_int32_t)ch);
    else if (ch >= 0x80 && ch <= 0xFFFF)
        return snprintf(buf, sz, "\\u%.4hX", (unsigned short)ch);
    
    return snprintf(buf, sz, "%c", (char)ch);
}



int u8_escape(char *buf, int sz, char *src, int escape_quotes)
{
    int c=0, i=0, amt;
    
    while (src[i] && c < sz) {
        if (escape_quotes && src[i] == '"') {
            amt = snprintf(buf, sz - c, "\\\"");
            i++;
        }
        else {
            amt = u8_escape_wchar(buf, sz - c, u8_nextchar(src, &i));
        }
        c += amt;
        buf += amt;
    }
    if (c < sz)
        *buf = '\0';
    return c;
}



char *u8_strchr(char *s, u_int32_t ch, int *charn)
{
    int i = 0, lasti=0;
    u_int32_t c;
    
    *charn = 0;
    while (s[i]) {
        c = u8_nextchar(s, &i);
        if (c == ch) {
            return &s[lasti];
        }
        lasti = i;
        (*charn)++;
    }
    return NULL;
}



char *u8_memchr(char *s, u_int32_t ch, size_t sz, int *charn)
{
    int i = 0, lasti=0;
    u_int32_t c;
    int csz;
    
    *charn = 0;
    while (i < sz) {
        c = csz = 0;
        do {
            c <<= 6;
            c += (unsigned char)s[i++];
            csz++;
        } while (i < sz && !isutf(s[i]));
        c -= offsetsFromUTF8[csz-1];
        
        if (c == ch) {
            return &s[lasti];
        }
        lasti = i;
        (*charn)++;
    }
    return NULL;
}



int u8_is_locale_utf8(char *locale)
{
    /* this code based on libutf8 */
    const char* cp = locale;
    
    for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++) {
        if (*cp == '.') {
            const char* encoding = ++cp;
            for (; *cp != '\0' && *cp != '@' && *cp != '+' && *cp != ','; cp++)
                ;
            if ((cp-encoding == 5 && !strncmp(encoding, "UTF-8", 5))
                || (cp-encoding == 4 && !strncmp(encoding, "utf8", 4)))
                return 1; /* it's UTF-8 */
            break;
        }
    }
    return 0;
}



int u8_vprintf(char *fmt, va_list ap)
{
    int cnt, sz=0;
    char *buf;
    u_int32_t *wcs;
    
    sz = 512;
    buf = (char*)alloca(sz);
try_print:
    cnt = vsnprintf(buf, sz, fmt, ap);
    if (cnt >= sz) {
        buf = (char*)alloca(cnt - sz + 1);
        sz = cnt + 1;
        goto try_print;
    }
    wcs = (u_int32_t*)alloca((cnt+1) * sizeof(u_int32_t));
    cnt = u8_toucs(wcs, cnt+1, buf, cnt);
    printf("%ls", (wchar_t*)wcs);
    return cnt;
}



int u8_printf(char *fmt, ...)
{
    int cnt;
    va_list args;
    
    va_start(args, fmt);
    
    cnt = u8_vprintf(fmt, args);
    
    va_end(args);
    return cnt;
}
#endif


