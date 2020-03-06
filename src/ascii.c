// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ascii.c
 *	Generated 10/01/2015 16:06:39
 *
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
#include        "ascii_internal.h"
#include        <stdbool.h>
#include        <stddef.h>
#include        <stdint.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    //**********************************************************
    //			ASCII  Character Type Table
    //**********************************************************
    
#define			CharType_Alpha			0x80
#define			CharType_Lower			0x40
#define			CharType_Numeric		0x20
#define			CharType_Punct			0x10
#define			CharType_Quote			0x08
#define			CharType_Upper			0x04
#define			CharType_White			0x02
#define         CharType_Escape         0x01    // String Escape Characters
    //                                          // (Such as b,r,n,f,x)

    static
    const
    uint8_t     CharTypeTable[128] = {
        0,									                    //   0 00 - NUL
        0,									                    //   1 01 - SOH
        0,									                    //   2 02 - STX
        0,									                    //   3 03 - ETX
        0,									                    //   4 04 - EOT
        0,									                    //   5 05 - ENQ
        0,									                    //   6 06 - ACK
        0,									                    //   7 07 - BEL
        CharType_White,						                    //   8 08 - BS (Backspace)
        CharType_White,						                    //   9 09 - HT (Horizontal Tab)
        CharType_White,						                    //  10 0A - LF/NL (Line Feed/New Line)
        0,									                    //  11 0B - VT (Vertical Tab)
        CharType_White,						                    //  12 0C - FF (Form Feed)
        CharType_White,						                    //  13 0D - CR (Carriage Return)
        0,									                    //  14 0E - SO
        0,									                    //  15 0F - SI
        0,									                    //  16 10 - DLE
        0,									                    //  17 11 - DC1
        0,									                    //  18 12 - DC2
        0,									                    //  19 13 - DC3
        0,									                    //  20 14 - DC4
        0,									                    //  21 15 - NAK
        0,									                    //  22 16 - SYN
        0,									                    //  23 17 - ETB
        0,									                    //  24 18 - CAN
        0,									                    //  25 19 - EM
        0,									                    //  26 1A - SUB
        0,									                    //  27 1B - ESC
        0,									                    //  28 1C - FS
        0,									                    //  29 1D - GS
        0,									                    //  30 1E - RS
        0,									                    //  31 1F - US
        CharType_White,						                    //  32 20 - SP - space/blank
        0,									                    //  33 21 - '!'
        CharType_Quote,						                    //  34 22 - '"'
        0,									                    //  35 23 - '#'
        0,									                    //  36 24 - '$'
        0,									                    //  37 25 - '%'
        0,									                    //  38 26 - '&'
        CharType_Quote,						                    //  39 27 - "'"
        0,									                    //  40 28 - ')'
        0,									                    //  41 29 - '('
        0,									                    //  42 2A - '*'
        0,									                    //  43 2B - '+'
        0,									                    //  44 2C - ','
        0,									                    //  45 2D - '-'
        0,									                    //  46 2E - '.'
        0,									                    //  47 2F - '/'
        CharType_Numeric,					                    //  48 30 - '0'
        CharType_Numeric,					                    //  49 31 - '1'
        CharType_Numeric,					                    //  50 32 - '2'
        CharType_Numeric,					                    //  51 33 - '3'
        CharType_Numeric,					                    //  52 34 - '4'
        CharType_Numeric,					                    //  53 35 - '5'
        CharType_Numeric,					                    //  54 36 - '6'
        CharType_Numeric,					                    //  55 37 - '7'
        CharType_Numeric,					                    //  56 38 - '8'
        CharType_Numeric,					                    //  57 39 - '9'
        0,									                    //  58 3A - ':'
        0,									                    //  59 3B - ';'
        0,									                    //  60 3C - '<'
        0,									                    //  61 3D - '='
        0,									                    //  62 3E - '>'
        CharType_Escape,							            //  63 3F - '?'
        0,									                    //  64 40 - '@'
        (CharType_Alpha|CharType_Upper),	                    //  65 41 - 'A'
        (CharType_Alpha|CharType_Upper),	                    //  66 42 - 'B'
        (CharType_Alpha|CharType_Upper),	                    //  67 43 - 'C'
        (CharType_Alpha|CharType_Upper),	                    //  68 44 - 'D'
        (CharType_Alpha|CharType_Upper),	                    //  69 45 - 'E'
        (CharType_Alpha|CharType_Upper),	                    //  70 46 - 'F'
        (CharType_Alpha|CharType_Upper),	                    //  71 47 - 'G'
        (CharType_Alpha|CharType_Upper),	                    //  72 48 - 'H'
        (CharType_Alpha|CharType_Upper),	                    //  73 49 - 'I'
        (CharType_Alpha|CharType_Upper),	                    //  74 4A - 'J'
        (CharType_Alpha|CharType_Upper),	                    //  75 4B - 'K'
        (CharType_Alpha|CharType_Upper),	                    //  76 4C - 'L'
        (CharType_Alpha|CharType_Upper),	                    //  77 4D - 'M'
        (CharType_Alpha|CharType_Upper),	                    //  78 4E - 'N'
        (CharType_Alpha|CharType_Upper),	                    //  79 4F - 'O'
        (CharType_Alpha|CharType_Upper),	                    //  80 50 - 'P'
        (CharType_Alpha|CharType_Upper),	                    //  81 51 - 'Q'
        (CharType_Alpha|CharType_Upper),	                    //  82 52 - 'R'
        (CharType_Alpha|CharType_Upper),	                    //  83 53 - 'S'
        (CharType_Alpha|CharType_Upper),	                    //  84 54 - 'T'
        (CharType_Alpha|CharType_Upper),	                    //  85 55 - 'U'
        (CharType_Alpha|CharType_Upper),	                    //  86 56 - 'V'
        (CharType_Alpha|CharType_Upper),	                    //  87 57 - 'W'
        (CharType_Alpha|CharType_Upper),	                    //  88 58 - 'X'
        (CharType_Alpha|CharType_Upper),	                    //  89 59 - 'Y'
        (CharType_Alpha|CharType_Upper),	                    //  90 5A - 'Z'
        0,									                    //  91 5B - '['
        CharType_Escape,									    //  92 5C - '\'
        0,									                    //  93 5D - ']'
        0,									                    //  94 5E - '^'
        0,									                    //  95 5F - '_'
        0,									                    //  96 60 - '`'
        (CharType_Alpha|CharType_Lower),	                    //  97 61 - 'a'
        (CharType_Alpha|CharType_Lower|CharType_Escape),	    //  98 62 - 'b'
        (CharType_Alpha|CharType_Lower),	                    //  99 63 - 'c'
        (CharType_Alpha|CharType_Lower),	                    // 100 64 - 'd'
        (CharType_Alpha|CharType_Lower),	                    // 101 65 - 'e'
        (CharType_Alpha|CharType_Lower|CharType_Escape),	    // 102 66 - 'f'
        (CharType_Alpha|CharType_Lower),	                    // 103 67 - 'g'
        (CharType_Alpha|CharType_Lower),	                    // 104 68 - 'h'
        (CharType_Alpha|CharType_Lower),	                    // 105 69 - 'i'
        (CharType_Alpha|CharType_Lower),	                    // 106 6A - 'j'
        (CharType_Alpha|CharType_Lower),	                    // 107 6B - 'k'
        (CharType_Alpha|CharType_Lower),	                    // 108 6C - 'l'
        (CharType_Alpha|CharType_Lower),	                    // 109 6D - 'm'
        (CharType_Alpha|CharType_Lower|CharType_Escape),	    // 110 6E - 'n'
        (CharType_Alpha|CharType_Lower),	                    // 111 6F - 'o'
        (CharType_Alpha|CharType_Lower),	                    // 112 70 - 'p'
        (CharType_Alpha|CharType_Lower),	                    // 113 71 - 'q'
        (CharType_Alpha|CharType_Lower|CharType_Escape),	    // 114 72 - 'r'
        (CharType_Alpha|CharType_Lower),	                    // 115 73 - 's'
        (CharType_Alpha|CharType_Lower),	                    // 116 74 - 't'
        (CharType_Alpha|CharType_Lower),	                    // 117 75 - 'u'
        (CharType_Alpha|CharType_Lower|CharType_Escape),	    // 118 76 - 'v'
        (CharType_Alpha|CharType_Lower),	                    // 119 77 - 'w'
        (CharType_Alpha|CharType_Lower|CharType_Escape),	    // 120 78 - 'x'
        (CharType_Alpha|CharType_Lower),	                    // 121 79 - 'y'
        (CharType_Alpha|CharType_Lower),	                    // 122 7A - 'z'
        0,									                    // 123 7B - '{'
        0,									                    // 124 7C - '|'
        0,									                    // 125 7D - '}'
        0,									                    // 126 7E - '~'
        CharType_White						                    // 127 7F - DEL
    };
    
    
    //**********************************************************
    //		ASCII Lexical Character Classification Table
    //**********************************************************
    
    static
    const
    int32_t     LexicalCharClassTable[128] = {
        ASCII_LEXICAL_UNKNOWN,              // 00 - NUL
        ASCII_LEXICAL_UNKNOWN,              // 01 - SOH
        ASCII_LEXICAL_UNKNOWN,              // 02 - STX
        ASCII_LEXICAL_UNKNOWN,              // 03 - ETX
        ASCII_LEXICAL_UNKNOWN,              // 04 - EOT
        ASCII_LEXICAL_UNKNOWN,              // 05 - ENQ
        ASCII_LEXICAL_UNKNOWN,              // 06 - ACK
        ASCII_LEXICAL_UNKNOWN,              // 07 - BEL
        ASCII_LEXICAL_WHITESPACE,           // 08 - BS (backspace)
        ASCII_LEXICAL_WHITESPACE,           // 09 - HT (horizontal tab)
        ASCII_LEXICAL_EOL,                  // 0A - LF/NL (line feed | new line)
        ASCII_LEXICAL_UNKNOWN,              // 0B - VT (vertical tab)
        ASCII_LEXICAL_WHITESPACE,           // 0C - FF (form feed)
        ASCII_LEXICAL_WHITESPACE,           // 0D - CR (carriage return)
        ASCII_LEXICAL_UNKNOWN,              // 0E - SO
        ASCII_LEXICAL_UNKNOWN,              // 0F - SI
        ASCII_LEXICAL_UNKNOWN,              // 10 - DLE
        ASCII_LEXICAL_UNKNOWN,              // 11 - DC1
        ASCII_LEXICAL_UNKNOWN,              // 12 - DC2
        ASCII_LEXICAL_UNKNOWN,              // 13 - DC3
        ASCII_LEXICAL_UNKNOWN,              // 14 - DC4
        ASCII_LEXICAL_UNKNOWN,              // 15 - NAK
        ASCII_LEXICAL_UNKNOWN,              // 16 - SYN
        ASCII_LEXICAL_UNKNOWN,              // 17 - ETB
        ASCII_LEXICAL_UNKNOWN,              // 18 - CAN
        ASCII_LEXICAL_UNKNOWN,              // 19 - EM
        ASCII_LEXICAL_UNKNOWN,              // 1A - SUB
        ASCII_LEXICAL_UNKNOWN,              // 1B - ESC
        ASCII_LEXICAL_UNKNOWN,              // 1C - FS
        ASCII_LEXICAL_UNKNOWN,              // 1D - GS
        ASCII_LEXICAL_UNKNOWN,              // 1E - RS
        ASCII_LEXICAL_UNKNOWN,              // 1F - US
        ASCII_LEXICAL_WHITESPACE,           // 20 - SP - space/blank
        '!',								// 21 - '!'
        '"',								// 22 - '"'
        '#',								// 23 - '#'
        '$',								// 24 - '$'
        '%',								// 25 - '%'
        '&',								// 26 - '&'
        '\'',								// 27 - "'"
        '(',								// 28 - '('
        ')',								// 29 - ')'
        '*',								// 2A - '*'
        '+',								// 2B - '+'
        ',',								// 2C - ','
        '-',								// 2D - '-'
        '.',								// 2E - '.'
        '/',								// 2F - '/'
        ASCII_LEXICAL_NUMBER,               // 30 - '0'
        ASCII_LEXICAL_NUMBER,               // 31 - '1'
        ASCII_LEXICAL_NUMBER,               // 32 - '2'
        ASCII_LEXICAL_NUMBER,               // 33 - '3'
        ASCII_LEXICAL_NUMBER,               // 34 - '4'
        ASCII_LEXICAL_NUMBER,               // 35 - '5'
        ASCII_LEXICAL_NUMBER,               // 36 - '6'
        ASCII_LEXICAL_NUMBER,               // 37 - '7'
        ASCII_LEXICAL_NUMBER,               // 38 - '8'
        ASCII_LEXICAL_NUMBER,               // 39 - '9'
        ':',								// 3A - ':'
        ';',								// 3B - ';'
        '<',								// 3C - '<'
        '=',								// 3D - '='
        '>',								// 3E - '>'
        '?',								// 3F - '?'
        '@',								// 40 - '@'
        ASCII_LEXICAL_ALPHA_UPPER,          // 41 - 'A'
        ASCII_LEXICAL_ALPHA_UPPER,          // 42 - 'B'
        ASCII_LEXICAL_ALPHA_UPPER,          // 43 - 'C'
        ASCII_LEXICAL_ALPHA_UPPER,          // 44 - 'D'
        ASCII_LEXICAL_ALPHA_UPPER,          // 45 - 'E'
        ASCII_LEXICAL_ALPHA_UPPER,          // 46 - 'F'
        ASCII_LEXICAL_ALPHA_UPPER,          // 47 - 'G'
        ASCII_LEXICAL_ALPHA_UPPER,          // 48 - 'H'
        ASCII_LEXICAL_ALPHA_UPPER,          // 49 - 'I'
        ASCII_LEXICAL_ALPHA_UPPER,          // 4A - 'J'
        ASCII_LEXICAL_ALPHA_UPPER,          // 4B - 'K'
        ASCII_LEXICAL_ALPHA_UPPER,          // 4C - 'L'
        ASCII_LEXICAL_ALPHA_UPPER,          // 4D - 'M'
        ASCII_LEXICAL_ALPHA_UPPER,          // 4E - 'N'
        ASCII_LEXICAL_ALPHA_UPPER,          // 4F - 'O'
        ASCII_LEXICAL_ALPHA_UPPER,          // 50 - 'P'
        ASCII_LEXICAL_ALPHA_UPPER,          // 51 - 'Q'
        ASCII_LEXICAL_ALPHA_UPPER,          // 52 - 'R'
        ASCII_LEXICAL_ALPHA_UPPER,          // 53 - 'S'
        ASCII_LEXICAL_ALPHA_UPPER,          // 54 - 'T'
        ASCII_LEXICAL_ALPHA_UPPER,          // 55 - 'U'
        ASCII_LEXICAL_ALPHA_UPPER,          // 56 - 'V'
        ASCII_LEXICAL_ALPHA_UPPER,          // 57 - 'W'
        ASCII_LEXICAL_ALPHA_UPPER,          // 58 - 'X'
        ASCII_LEXICAL_ALPHA_UPPER,          // 59 - 'Y'
        ASCII_LEXICAL_ALPHA_UPPER,          // 5A - 'Z'
        '[',								// 5B - '['
        '\\',								// 5C - '\\'
        ']',								// 5D - ']'
        '^',								// 5E - '^'
        '_',								// 5F - '_'
        '`',								// 60 - '`'
        ASCII_LEXICAL_ALPHA_LOWER,          // 61 - 'a'
        ASCII_LEXICAL_ALPHA_LOWER,          // 62 - 'b'
        ASCII_LEXICAL_ALPHA_LOWER,          // 63 - 'c'
        ASCII_LEXICAL_ALPHA_LOWER,          // 64 - 'd'
        ASCII_LEXICAL_ALPHA_LOWER,          // 65 - 'e'
        ASCII_LEXICAL_ALPHA_LOWER,          // 66 - 'f'
        ASCII_LEXICAL_ALPHA_LOWER,          // 67 - 'g'
        ASCII_LEXICAL_ALPHA_LOWER,          // 68 - 'h'
        ASCII_LEXICAL_ALPHA_LOWER,          // 69 - 'i'
        ASCII_LEXICAL_ALPHA_LOWER,          // 6A - 'j'
        ASCII_LEXICAL_ALPHA_LOWER,          // 6B - 'k'
        ASCII_LEXICAL_ALPHA_LOWER,          // 6C - 'l'
        ASCII_LEXICAL_ALPHA_LOWER,          // 6D - 'm'
        ASCII_LEXICAL_ALPHA_LOWER,          // 6E - 'n'
        ASCII_LEXICAL_ALPHA_LOWER,          // 6F - 'o'
        ASCII_LEXICAL_ALPHA_LOWER,          // 70 - 'p'
        ASCII_LEXICAL_ALPHA_LOWER,          // 71 - 'q'
        ASCII_LEXICAL_ALPHA_LOWER,          // 72 - 'r'
        ASCII_LEXICAL_ALPHA_LOWER,          // 73 - 's'
        ASCII_LEXICAL_ALPHA_LOWER,          // 74 - 't'
        ASCII_LEXICAL_ALPHA_LOWER,          // 75 - 'u'
        ASCII_LEXICAL_ALPHA_LOWER,          // 76 - 'v'
        ASCII_LEXICAL_ALPHA_LOWER,          // 77 - 'w'
        ASCII_LEXICAL_ALPHA_LOWER,          // 78 - 'x'
        ASCII_LEXICAL_ALPHA_LOWER,          // 79 - 'y'
        ASCII_LEXICAL_ALPHA_LOWER,          // 7A - 'z'
        '{',								// 7B - '{'
        '|',								// 7C - '|'
        '}',								// 7D - '}'
        '~',								// 7E - '~'
        ASCII_LEXICAL_DELETE                // 7F - DEL
    };
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ASCII_DATA *     ascii_Alloc(
    )
    {
        ASCII_DATA      *cbp;
        uint32_t        cbSize = sizeof(ASCII_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    ASCII_DATA *     ascii_New(
    )
    {
        ASCII_DATA       *cbp;
        
        cbp = ascii_Alloc( );
        if (cbp) {
            cbp = ascii_Init( cbp );
        } 
        return( cbp );
    }



    //**********************************************************
    //                      i s A s c i i
    //**********************************************************
    
    bool                ascii_isAsciiW32(
        W32CHR_T            chr
    )
    {
        bool                fRc = false;
        
        if (chr < 128) {
            fRc = true;
        }
        
        return( fRc );
    }
    
    
    
    
    //**********************************************************
    //                      i s A l p h a
    //**********************************************************
    
    bool                ascii_isAlphaA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if ( asciiChar > 127 ) {
            fRc = false;
        }
        else if ( CharTypeTable[(asciiChar & 0x7F)] & CharType_Alpha ) {
            fRc = true;
        }
        
        return( fRc );
    }
    
    
    bool                ascii_isAlphaW32(
        W32CHR_T            asciiChar
    )
    {
        bool                fRc = false;
        
        fRc = ascii_isLowerW32(asciiChar);
        if (!fRc)
            fRc = ascii_isUpperW32(asciiChar);
        
        return fRc;
    }
    
    

    
    //**********************************************************
    //                i s A l p h a n u m e r i c
    //**********************************************************
    
    bool                ascii_isAlphanumericA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if ( asciiChar > 127 ) {
            fRc = false;
        }
        else if ( CharTypeTable[(asciiChar & 0x7F)] & CharType_Alpha ) {
            fRc = true;
        }
        else if ( CharTypeTable[(asciiChar & 0x7F)] & CharType_Numeric ) {
            fRc = true;
        }
        
        return( fRc );
    }
    
    
    bool                ascii_isAlphanumericW32(
        W32CHR_T            asciiChar
    )
    {
        bool                fRc = false;
        
        fRc = ascii_isAlphaW32(asciiChar);
        if (!fRc)
            fRc = ascii_isNumericW32(asciiChar);
        
        return fRc;
    }
    
    
    
    
    //**********************************************************
    //                  i s H e x
    //**********************************************************
    
    bool                ascii_isHexW32(
        W32CHR_T            w32Char
    )
    {
        bool                fRc = false;
        
        if ( (w32Char >= '0') && (w32Char <= '9') ) {
            fRc = true;
        }
        else if ( (w32Char >= 'a') && (w32Char <= 'f') ) {
            fRc = true;
        }
        else if ( (w32Char >= 'A') && (w32Char <= 'F') ) {
            fRc = true;
        }
        else if ( (w32Char >= 0xFF10) && (w32Char <= 0xFF19) ) {
            fRc = true;
        }
        else if ( (w32Char >= 0xFF21) && (w32Char <= 0xFF26) ) {
            fRc = true;
        }
        else if ( (w32Char >= 0xFF41) && (w32Char <= 0xFF46) ) {
            fRc = true;
        }

        return fRc;
        
    }
    
    
    int                 ascii_FromHexW32(
        W32CHR_T            w32Char
    )
    {
        int                 iRc = -1;
        
        if ( (w32Char >= '0') && (w32Char <= '9') ) {
            iRc = w32Char - '0';
        }
        else if ( (w32Char >= 'a') && (w32Char <= 'f') ) {
            iRc = w32Char - 'a' + 10;
        }
        else if ( (w32Char >= 'A') && (w32Char <= 'F') ) {
            iRc = w32Char - 'A' + 10;
        }
        else if ( (w32Char >= 0xFF10) && (w32Char <= 0xFF19) ) {
            iRc = w32Char - 0xFF10 + 10;
        }
        else if ( (w32Char >= 0xFF21) && (w32Char <= 0xFF26) ) {
            iRc = w32Char - 0xFF21 + 10;
        }
        else if ( (w32Char >= 0xFF41) && (w32Char <= 0xFF46) ) {
            iRc = w32Char - 0xFF41 + 10;
        }

        return iRc;
        
    }
    
    

    
    //**********************************************************
    //                  i s L o w e r
    //**********************************************************
    
    bool                ascii_isLowerA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if ( (asciiChar >= 'a') && (asciiChar <= 'z') ) {
            fRc = true;
        }
        
        return( fRc );
        
    }
    
    
    bool                ascii_isLowerW32(
        W32CHR_T            unicodeChar
    )
    {
        bool                fRc = false;
        
        if ( (unicodeChar >= 'a') && (unicodeChar <= 'z') ) {
            fRc = true;
        } else if ((unicodeChar >= 0xFF41) && (unicodeChar >= 0xFF5A)) {
                fRc = true;
        }
        
        return( fRc );
        
    }
    
    

    
    //**********************************************************
    //                  i s N u m e r i c
    //**********************************************************
    
    bool                ascii_isNumericA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if ( asciiChar > 127 ) {
            fRc = false;
        }
        else if ( CharTypeTable[(asciiChar & 0x7F)] & CharType_Numeric ) {
            fRc = true;
        }
        
        return fRc;
    }
    
    
    bool                ascii_isNumericW32(
        W32CHR_T            unicodeChar
    )
    {
        bool                fRc = false;
        
        if ((unicodeChar >= 0xFF10) && (unicodeChar >= 0xFF19)) {
            fRc = true;
        } else if ( unicodeChar > 127 ) {
            fRc = false;
        } else if ( CharTypeTable[(unicodeChar & 0x7F)] & CharType_Numeric ) {
            fRc = true;
        }

        return fRc;
    }
    
    

    
    //**********************************************************
    //                  i s P r i n t a b l e
    //**********************************************************
    
    bool                ascii_isPrintableA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if ( (asciiChar >= ' ') && (asciiChar < 0x7F) ) {
            fRc = true;
        }
        
        return( fRc );
        
    }
    
    
    bool                ascii_isPrintableW32(
        W32CHR_T            w32Char
    )
    {
        bool                fRc = false;
        
        if ( (w32Char >= ' ') && (w32Char < 0x7F) ) {
            fRc = true;
        }
        
        return( fRc );
        
    }
    
    

    
    //**********************************************************
    //                      i s Q u o t e
    //**********************************************************
    
    bool                ascii_isQuoteA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if ( asciiChar > 127 ) {
            fRc = false;
        }
        else if ( CharTypeTable[(asciiChar & 0x7F)] & CharType_Quote ) {
            fRc = true;
        }
        
        return( fRc );
    }
    
    
    
    
    //**********************************************************
    //                  i s U p p e r
    //**********************************************************
    
    bool                ascii_isUpperA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if ( (asciiChar >= 'A') && (asciiChar <= 'Z') ) {
            fRc = true;
        }
        
        return( fRc );
        
    }
    
    
    bool                ascii_isUpperW32(
        W32CHR_T            unicodeChar
    )
    {
        bool                fRc = false;
        
        if ( (unicodeChar >= 'A') && (unicodeChar <= 'Z') ) {
            fRc = true;
        } else if ((unicodeChar >= 0xFF21) && (unicodeChar >= 0xFF3A)) {
                fRc = true;
        }
        
        return( fRc );
        
    }
    
    

    
    //**********************************************************
    //                  i s W h i t e S p a c e
    //**********************************************************
    
    bool                ascii_isWhiteSpaceA(
        char                asciiChar
    )
    {
        bool                fRc = false;
        
        if (CharTypeTable[(asciiChar & 0x7F)] & CharType_White) {
            fRc = true;
        }
        
        return( fRc );
    }
    
    
    bool                ascii_isWhiteSpaceW32(
        W32CHR_T            unicodeChar
    )
    {
        bool                fRc = false;
        
        if (unicodeChar < 0x80) {
            if (CharTypeTable[(unicodeChar & 0x7F)] & CharType_White) {
                fRc = true;
            }
        }
        else {
            switch (unicodeChar) {
                case 0x0085:            // NEL - Next Line (same as ebcdic NL)
                case 0x00A0:            // no-break space
                case 0x1680:            // OGHAM space mark
                case 0x2000:            // General Punctuation space
                case 0x2001:
                case 0x2002:
                case 0x2003:
                case 0x2004:
                case 0x2005:
                case 0x2006:
                case 0x2007:
                case 0x2008:
                case 0x2009:
                case 0x200A:
                case 0x200B:
                case 0x2028:            // LS - Line Separator
                case 0x2029:            // PS - Paragraph Separator
                case 0x205F:            // Medium Mathematical space
                case 0x202F:            // Narrow No-Break space
                case 0x3000:            // ideographic space
                case 0xFEFF:            // zero width no-break space
                    fRc = true;
                    break;
                default:
                    break;
            }
        }
        
        return( fRc );
    }
    
    
    
    
    //**********************************************************
    //                  I s  L a b e l  C h a r
    //**********************************************************
    
    bool                ascii_isLabelCharW32(
        W32CHR_T            asciiChar
    )
    {
        bool                fRc = false;
        
        fRc = ascii_isAlphaW32(asciiChar);
        if (!fRc)
            fRc = ascii_isNumericW32(asciiChar);
        if (!fRc) {
            switch (asciiChar) {
                case '_':
                case 0xFF3F:                // Full Width Low Line
                    fRc = true;
                    break;
                default:
                    break;
            }
        }

        return fRc;
    }
    
    
    bool                ascii_isLabelFirstCharW32(
        W32CHR_T            asciiChar
    )
    {
        
        if (ascii_isAlphaW32(asciiChar)) {
            return true;
        }
        if (('_' == asciiChar) || (0xFF3F == asciiChar)) {
             return true;
       }
        
        return false;
    }
    
    

    //**********************************************************
    //                  L e x i c a l  C l a s s
    //**********************************************************
    
    int32_t             ascii_toLexicalClassA(
        char                asciiChar
    )
    {
        int32_t             lexical;
        
        lexical = (LexicalCharClassTable[(asciiChar & 0x7F)]);
        
        return( lexical );
    }
    
    
    int32_t             ascii_toLexicalClassW32(
        int32_t             unicodeChar
    )
    {
        int32_t             lexical = ASCII_LEXICAL_UNKNOWN;
        
        if (unicodeChar < 0x80) {
            lexical = (LexicalCharClassTable[unicodeChar]);
        }
        else if (unicodeChar == 0x00A0) {       // no-break space
            lexical = ASCII_LEXICAL_WHITESPACE;
        }
        else if (unicodeChar == 0x200B) {       // zero width space
            lexical = ASCII_LEXICAL_WHITESPACE;
        }
        else if (unicodeChar == 0x2060) {       // word joiner
            lexical = ASCII_LEXICAL_WHITESPACE;
        }
        else if (unicodeChar == 0x3000) {       // ideographic space
            lexical = ASCII_LEXICAL_WHITESPACE;
        }
        else if (unicodeChar == 0xFEFF) {       // zero width no-break space
            lexical = ASCII_LEXICAL_WHITESPACE;
        }
        
        return( lexical );
    }
    
    
    
    //**********************************************************
    //					t o L o w e r
    //**********************************************************
    
    char                ascii_toLowerA(
        char                asciiChar
    )
    {
        char                chr = asciiChar;
        
        if ((asciiChar >= 'A') && (asciiChar <= 'Z')) {
            chr = (asciiChar - 'A') + 'a';
        }
        
        return( chr );
    }
    
    W32CHR_T            ascii_toLowerW32(
        W32CHR_T            asciiChar
    )
    {
        W32CHR_T            chr = asciiChar;
        
        if ((asciiChar >= 'A') && (asciiChar <= 'Z')) {
            chr = (asciiChar - 'A') + 'a';
        } else if ((asciiChar >= 0xFF21) && (asciiChar <= 0xFF3A)) {
            chr = (asciiChar - 0xFF21) + 0xFF41;
        }


        return chr;
    }
    
    

    
    //**********************************************************
    //					t o U p p e r
    //**********************************************************
    
    char                ascii_toUpperA(
        char                asciiChar
    )
    {
        char                chr = asciiChar;
        
        if ((asciiChar >= 'a') && (asciiChar <= 'z')) {
            chr = (asciiChar - 'a') + 'A';
        }
        
        return( chr );
    }
    
    
    W32CHR_T            ascii_toUpperW32(
        W32CHR_T            asciiChar
    )
    {
        W32CHR_T            chr = asciiChar;
        
        if ((asciiChar >= 'a') && (asciiChar <= 'z')) {
            chr = (asciiChar - 'a') + 'A';
        } else if ((asciiChar >= 0xFF41) && (asciiChar <= 0xFF5A)) {
            chr = (asciiChar - 0xFF41) + 0xFF21;
        }

        
        return chr;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJARRAY_DATA * ascii_getArray(
        ASCII_DATA     *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ascii_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return cbp->pArray;
    }
    
    
    bool            ascii_setArray(
        ASCII_DATA     *cbp,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ascii_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pArray) {
            obj_Release(cbp->pArray);
        }
        cbp->pArray = pValue;
        
        return true;
    }
    
    
    
    uint16_t        ascii_getPriority(
        ASCII_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ascii_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            ascii_setPriority(
        ASCII_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !ascii_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        ascii_getSize(
        ASCII_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !ascii_Validate( cbp ) ) {
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

    void            ascii_Dealloc(
        OBJ_ID          objId
    )
    {
        ASCII_DATA      *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !ascii_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            ascii_Disable(
        ASCII_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !ascii_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            ascii_Enable(
        ASCII_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !ascii_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(cbp);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASCII_DATA *   ascii_Init(
        ASCII_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (ASCII_DATA *)obj_Init( this, cbSize, OBJ_IDENT_ASCII );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_ASCII);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ascii_Vtbl);
        
        //this->stackSize = obj_getMisc1(cbp);
        //this->pArray = ObjArray_New( );

    #ifdef NDEBUG
    #else
        if( !ascii_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            ascii_IsEnabled(
        ASCII_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ascii_Validate( cbp ) ) {
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
    
    ASTR_DATA *     ascii_ToDebugString(
        ASCII_DATA      *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == cbp) {
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
                     "{%p(ascii) side=%d ",
                     cbp,
                     ascii_getSize(cbp)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString(
                                                    cbp->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            ascii_Validate(
        ASCII_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_ASCII) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(ASCII_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


