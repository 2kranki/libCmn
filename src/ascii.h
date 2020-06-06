// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          ASCII Character Support (ascii) Header
//****************************************************************
/*
 * Program
 *			ASCII Character Support (ascii)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate ascii to run things without complications
 *          of interfering with the main ascii. A ascii may be 
 *          called a ascii on other O/S's.
 *
 * Remarks
 *	1.      A '\n' is considered to be EOL not whitespace.
 *
 * History
 *	10/01/2015 Generated
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
#include        <AStr.h>


#ifndef         ASCII_H
#define         ASCII_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ascii_data_s	ASCII_DATA;

    typedef struct ascii_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.
        // Properties:
        // Methods:
    } ASCII_VTBL;

    //  Common Ascii Character Definitions
#define     ASCII_NUL       0x00
#define     ASCII_SOH       0x01
#define     ASCII_STX       0x02
#define     ASCII_ETX       0x03
#define     ASCII_EOT       0x04
#define     ASCII_ENQ       0x05
#define     ASCII_ACK       0x06
#define     ASCII_BEL       0x07
#define     ASCII_BS        0x08
#define     ASCII_TAB       0x09
#define     ASCII_HT        0x09
#define     ASCII_LF        0x0A
#define     ASCII_VT        0x0B
#define     ASCII_FF        0x0C
#define     ASCII_CR        0x0D
#define     ASCII_SO        0x0E
#define     ASCII_SI        0x0F
#define     ASCII_DLE       0x10
#define     ASCII_DC1       0x11
#define     ASCII_DC2       0x12
#define     ASCII_DC3       0x13
#define     ASCII_DC4       0x14
#define     ASCII_NAK       0x15
#define     ASCII_SYN       0x16
#define     ASCII_ETB       0x17
#define     ASCII_CAN       0x18
#define     ASCII_EM        0x19
#define     ASCII_SUB       0x1A
#define     ASCII_ESC       0x1B
#define     ASCII_FS        0x1C
#define     ASCII_GS        0x1D
#define     ASCII_RS        0x1E
#define     ASCII_US        0x1F
#define     ASCII_DEL       0x7F
    
#define     ASCII_CPM_EOF   0x1A
#define     ASCII_XON       0x11        /* Ctrl+Q */
#define     ASCII_XOFF      0x13        /* Ctrl+S */
    
#define     ASCII_CTRL_A    0x01
#define     ASCII_CTRL_B    0x02
#define     ASCII_CTRL_C    0x03
#define     ASCII_CTRL_D    0x04
#define     ASCII_CTRL_E    0x05
#define     ASCII_CTRL_F    0x06
#define     ASCII_CTRL_G    0x07        /* <bel> */
#define     ASCII_CTRL_H    0x08
#define     ASCII_CTRL_I    0x09        /* <tab> */
#define     ASCII_CTRL_J    0x0A        /* <lf> */
#define     ASCII_CTRL_K    0x0B
#define     ASCII_CTRL_L    0x0C
#define     ASCII_CTRL_M    0x0D        /* <cr> */
#define     ASCII_CTRL_N    0x0E
#define     ASCII_CTRL_O    0x0F
#define     ASCII_CTRL_P    0x10
#define     ASCII_CTRL_Q    0x11
#define     ASCII_CTRL_R    0x12
#define     ASCII_CTRL_S    0x13
#define     ASCII_CTRL_T    0x14
#define     ASCII_CTRL_U    0x15
#define     ASCII_CTRL_V    0x16
#define     ASCII_CTRL_W    0x17
#define     ASCII_CTRL_X    0x18
#define     ASCII_CTRL_Y    0x19
#define     ASCII_CTRL_Z    0x1A
    
    
    //      Lexical Scan Group Character Classes
    // If a character is by itself lexically important,
    // then it is returned as its own class. If the
    // character is part of a group, then the group
    // number is returned for its class.
    typedef enum ascii_Lexical_CharClasses_e {
        ASCII_LEXICAL_UNKNOWN=0,
        ASCII_LEXICAL_ALPHA_LOWER=256,      // a-z
        ASCII_LEXICAL_ALPHA_UPPER,          // A-Z
        ASCII_LEXICAL_DELETE,               // ascii 127
        ASCII_LEXICAL_NUMBER,               // 0-9
        ASCII_LEXICAL_EOL,                  // '\n'
        ASCII_LEXICAL_WHITESPACE,           // ' ', '\t', '\n', '\r', '\f'
        ASCII_LEXICAL_UNICODE,              // >256
    } ASCII_LEXICAL_CharClasses;
    
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the ascii including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    ASCII_DATA *        ascii_Alloc (
        void
    );
    
    
    ASCII_DATA *        ascii_New (
        void
    );
    
    
    /*!
     Convert a hexadecimal character to internal binary if possible.
     @return:   If valid hexadecimal character, return it converted to
                binary (ie 0..15), otherwise -1.
     */
    int                 ascii_FromHexW32 (
        W32CHR_T            w32Char
    );
    
    
    bool                ascii_isAlphaA (
        char                asciiChar
    );
    
    bool                ascii_isAlphaW32 (
        W32CHR_T            asciiChar
    );
    

    bool                ascii_isAlphanumericA (
        char                asciiChar
    );
    
    
    bool                ascii_isAlphanumericW32 (
        W32CHR_T            w32Char
    );
    
    
    bool                ascii_isAsciiW32 (
        W32CHR_T            w32Char
    );
    
    
    /*!
     @return:   true if w32Char is [a..f] or [A..F] or [0..9].
                Otherwise, false is returned.
     */
    bool                ascii_isHexW32 (
        W32CHR_T            w32Char
    );
    
    
    /*!
     @return:   true if asciiChar is [a..z] or [A..Z] or [0..9] or '_'.
                Otherwise, false is returned.
     */
    bool                ascii_isLabelCharW32 (
        W32CHR_T            asciiChar
    );
    
    
    /*!
     @return:   true if asciiChar is [a..z] or [A..Z] or '_'.
                Otherwise, false is returned.
     */
    bool                ascii_isLabelFirstCharW32 (
        W32CHR_T            asciiChar
    );
    
    
    /*!
     @return:   true if asciiChar is [a..z].
                Otherwise, false is returned.
     */
    bool                ascii_isLowerA (
        char                asciiChar
    );
    
    bool                ascii_isLowerW32 (
        W32CHR_T            unicodeChar
    );


    bool                ascii_isNumericA (
        char                asciiChar
    );
    
    bool                ascii_isNumericW32 (
        W32CHR_T            unicodeChar
    );


    bool                ascii_isPrintableA (
        char                asciiChar
    );
    
    bool                ascii_isPrintableW32 (
        W32CHR_T            w32Char
    );
    

    bool                ascii_isQuoteA (
        char                asciiChar
    );
    
    
    /*!
     @return:   true if asciiChar is [A..Z].
                Otherwise, false is returned.
     */
    bool                ascii_isUpperA (
        char                asciiChar
    );
    
    bool                ascii_isUpperW32 (
        W32CHR_T            unicodeChar
    );


    bool                ascii_isWhiteSpaceA (
        char                asciiChar
    );
    
    bool                ascii_isWhiteSpaceW32 (
        W32CHR_T            unicodeChar
    );
    
    
    /* Convert an ascii character to a Lexical scan class
     * as defined in ascii_LexicalCharClasses definitions
     * or the character itself if it doesn't fit into any
     * class.
     */
    int32_t             ascii_toLexicalClassA (
        char                asciiChar
    );
    
    W32CHR_T            ascii_toLexicalClassW32 (
        W32CHR_T            unicodeChar
    );
    
    
    char                ascii_toLowerA (
        char                asciiChar
    );
    
    
    W32CHR_T            ascii_toLowerW32 (
        W32CHR_T            unicodeChar
    );
    
    
    char                ascii_toUpperA (
        char                asciiChar
    );
    
    
    W32CHR_T            ascii_toUpperW32 (
        W32CHR_T            unicodeChar
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    ASCII_DATA *    ascii_Init (
        ASCII_DATA     *this
    );


    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     ascii_ToDebugString (
        ASCII_DATA      *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* ASCII_H */

