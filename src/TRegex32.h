// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Tiny REGEX 32-bit (TRegex32) Header
//****************************************************************
/*
 * Program
 *			Tiny REGEX 32-bit (TRegex32)
 * Purpose
 *          This object provides a version of Rob Pike's recursive
 *          regex code. Primary, it checks to see if the regex pat-
 *          tern exists in the supplied text.
 *
 *          Mini regex-module inspired by Rob Pike's regex code described in:
 *          http://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
 *
 *          This object is based on the work of kokke and was found at:
 *              https://github.com/kokke/tiny-regex-c
 *              https://github.com/Koxiaet/tiny-regex-c
 *          This library is licensed by the Unlicense maintaining the
 *          primary license for this library.
 *
 * Supports:
 * ---------
 *  '.'         Dot, matches any character
 *  '^'         Start anchor, matches beginning of string
 *  '$'         End anchor, matches end of string
 *  '*'         Asterisk, match zero or more (greedy)
 *  '+'         Plus, match one or more (greedy)
 *  '?'         Question, match zero or one (non-greedy)
 *  '?'         Question, make quantifier non-greedy
 *  '[abc]'     Character class, match if one of {'a', 'b', 'c'}
 *  '[^abc]'    Inverted class, match if NOT one of {'a', 'b', 'c'}
 *  '[a-zA-Z]'  Character ranges, the character set of the ranges { a-z | A-Z }
 *  '\s'        Whitespace, \t \f \r \n \v and spaces
 *  '\S'        Non-whitespace
 *  '\w'        Alphanumeric, [a-zA-Z0-9_]
 *  '\W'        Non-alphanumeric
 *  '\d'        Digits, [0-9]
 *  '\D'        Non-digits
 *  '\R'        Any newline (\r\n or \n)
 *  '\b'        A word boundary (where one side is \w and the other is \W)
 *  '\B'        Non-word boundary
 *  'i'         case Insensitive modifier
 *  's'         Single line modifier (where a dot matches newlines too)
 *  '()'        Groups (capturing is not currently implemented)
 *  '(?:)'      Non-capturing groups
 *  '(?is:)'    Non-capturing groups with modifiers
 *  '(?=)'      Lookaheads (do not absorb any chars, they only assert true or false
 *              as to the lookahead matching or not)
 *  '(?!)'      Inverted lookaheads (do not absorb any chars, they only assert true
 *              or false as to the lookahead matching or not)
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/19/2019 Generated
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


#ifndef         TREGEX32_H
#define         TREGEX32_H


//#define   TREGEX32_JSON_SUPPORT 1
//#define   TREGEX32_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TRegex32_data_s	TREGEX32_DATA;            // Inherits from OBJ
    typedef struct TRegex32_class_data_s TREGEX32_CLASS_DATA;   // Inherits from OBJ

    typedef struct TRegex32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TRegex32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TREGEX32_DATA *);
    } TREGEX32_VTBL;

    typedef struct TRegex32_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TRegex32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TREGEX32_DATA *);
    } TREGEX32_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TREGEX32_SINGLETON
    TREGEX32_DATA * TRegex32_Shared (
        void
    );

    bool            TRegex32_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TRegex32 object if successful, otherwise OBJ_NIL.
     */
    TREGEX32_DATA * TRegex32_Alloc (
        void
    );
    
    
    OBJ_ID          TRegex32_Class (
        void
    );
    
    
    TREGEX32_DATA * TRegex32_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         TRegex32_Compile (
        TREGEX32_DATA   *this,
        const
        W32CHR_T        *pPattern
    );


    TREGEX32_DATA * TRegex32_Init (
        TREGEX32_DATA   *this
    );


   /*!
    Search the given text with the supplied pattern.
    @param     this        object pointer
    @param     pPattern    Regex Pattern
    @param     pText       Nul-terminated string
    @param     pLength     Returned length of match (0 == no match)
    @return    If unsuccessful or the pattern was not found, 0 and
                length of zero. Otherwise, an index into where pat-
                tern starts to match the text and the length of the
                match.
    */
    int             TRegex32_Match(
        TREGEX32_DATA   *this,
        const
        W32CHR_T        *pPattern,
        const
        W32CHR_T        *pText,
        int             *pLength
    );
       
    
    /*!
     Search the given text with the previously compiled pattern.
     @param     this        object pointer
     @param     pText       Nul-terminated string
     @param     pLength     Returned length of match (0 == no match)
     @return    If unsuccessful or the pattern was not found, 0 and
                 length of zero. Otherwise, an index into where pat-
                 tern starts to match the text and the length of the
                 match.
     */
    int             TRegex_MatchP(
        TREGEX32_DATA   *this,
        const
        W32CHR_T        *pText,
        int             *pLength
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TRegex32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    TRegex32_ToDebugString (
        TREGEX32_DATA   *this,
        int             indent
    );
    
    
    ASTR_DATA *    TRegex32_ToStringPattern (
        TREGEX32_DATA   *this
    );


    
#ifdef	__cplusplus
}
#endif

#endif	/* TREGEX32_H */

