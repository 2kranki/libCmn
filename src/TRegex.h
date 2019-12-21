// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Tiny REGEX  (TRegex) Header
//****************************************************************
/*
 * Program
 *			Tiny Regex (TRegex)
 * Purpose
 *          Mini regex-module inspired by Rob Pike's regex code described in:
 *          http://www.cs.princeton.edu/courses/archive/spr09/cos333/beautiful.html
 *
 *          This object is based on the work of kokke and was found at:
 *          https://github.com/kokke/tiny-regex-c
 *          This library is licensed by the Unlicense maintaining the
 *          primary license for this library.
 *
 * Supports:
 * ---------
 *   '.'        Dot, matches any character
 *   '^'        Start anchor, matches beginning of string
 *   '$'        End anchor, matches end of string
 *   '*'        Asterisk, match zero or more (greedy)
 *   '+'        Plus, match one or more (greedy)
 *   '?'        Question, match zero or one (non-greedy)
 *   '[abc]'    Character class, match if one of {'a', 'b', 'c'}
 *   '[^abc]'   Inverted class, match if NOT one of {'a', 'b', 'c'} -- NOTE: feature is currently broken!
 *   '[a-zA-Z]' Character ranges, the character set of the ranges { a-z | A-Z }
 *   '\s'       Whitespace, \t \f \r \n \v and spaces
 *   '\S'       Non-whitespace
 *   '\w'       Alphanumeric, [a-zA-Z0-9_]
 *   '\W'       Non-alphanumeric
 *   '\d'       Digits, [0-9]
 *   '\D'       Non-digits
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


#ifndef         TREGEX_H
#define         TREGEX_H


//#define   TREGEX_JSON_SUPPORT 1
//#define   TREGEX_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TRegex_data_s	TREGEX_DATA;            // Inherits from OBJ
    typedef struct TRegex_class_data_s TREGEX_CLASS_DATA;   // Inherits from OBJ

    typedef struct TRegex_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TRegex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TREGEX_DATA *);
    } TREGEX_VTBL;

    typedef struct TRegex_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TRegex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TREGEX_DATA *);
    } TREGEX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TREGEX_SINGLETON
    TREGEX_DATA *     TRegex_Shared (
        void
    );

    bool            TRegex_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TRegex object if successful, otherwise OBJ_NIL.
     */
    TREGEX_DATA *   TRegex_Alloc (
        void
    );
    
    
    OBJ_ID          TRegex_Class (
        void
    );
    
    
    TREGEX_DATA *   TRegex_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         TRegex_Compile (
        TREGEX_DATA     *this,
        const
        char            *pPattern
    );


    TREGEX_DATA *   TRegex_Init (
        TREGEX_DATA     *this
    );


    /*!
     Search the given text with the supplied pattern.
     @param     this        object pointer
     @param     pPattern    Regex Pattern
     @param     pText       Nul-terminated string
     @return    If unsuccessful or the pattern was not found, -1. Otherwise,
                an index into where pattern starts to match the text.
     */
    int             TRegex_Match(
        TREGEX_DATA     *this,
        const
        char            *pPattern,
        const
        char            *pText
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TRegex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    TRegex_ToDebugString (
        TREGEX_DATA     *this,
        int             indent
    );
    
    
    ASTR_DATA *     TRegex_ToStringPattern (
        TREGEX_DATA     *this
    );




#ifdef	__cplusplus
}
#endif

#endif	/* TREGEX_H */

