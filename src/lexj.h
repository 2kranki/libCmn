// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          HJSON Lexical Scanner (lexj) Header
//****************************************************************
/*
 * Program
 *			HJSON Lexical Scanner (lexj)
 * Purpose
 *			This object provides a HJSON Lexical Analyzer/Scanner.  
 *          The Scanner accepts a source input token stream and 
 *          combines those character tokens into JSON sub-phrases
 *          such as numbers, strings, etc. It then emits an output
 *          token stream for use in a HJSON parser.
 *
 * Remarks
 *	1.      I changed the definition of the quoteless string to end
 *          with '\n' and any of '{','}','[',']',':',','. This al-
 *          lows it to be used for object names as well as quote-
 *          less strings. If any of those characters needs to be
 *          added to a string, then simply quote the string.
 *
 * History
 *	07/02/2017 Generated
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
#include        <lex.h>
#include        <token.h>


#ifndef         LEXJ_H
#define         LEXJ_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct lexj_data_s	LEXJ_DATA;    // Inherits from OBJ.

    typedef struct lexj_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in lexj_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXJ_DATA *);
    } LEXJ_VTBL;


    typedef enum lexj_class_e {
        /* Values below 128 are a character by itself that makes
         * its own token class. All other classes for groups of
         * characters should be allocated in the range above
         * LEXJ_CLASS_GROUP_LOWEST.
         */
        LEXJ_CLASS_EOF=-1,
        LEXJ_CLASS_RESERVED=0,
        
        LEXJ_CLASS_GROUP_LOWEST=128,
        
        LEXJ_CLASS_CONSTANT_GROUP=LEX_CLASS_CONSTANT_GROUP,
        LEXJ_CONSTANT_CHAR,
        LEXJ_CONSTANT_CHAR_WIDE,
        LEXJ_CONSTANT_FLOAT,
        LEXJ_CONSTANT_INTEGER,
        LEXJ_CONSTANT_STRING,
        LEXJ_CONSTANT_STRING_WIDE,
        
        LEXJ_SEP_LOWEST=LEX_CLASS_SEP_GROUP,
        LEXJ_SEP_COLON,                     // :
        LEXJ_SEP_COMMA,                     // ,
        LEXJ_SEP_LBRACKET,                  // [
        LEXJ_SEP_LBRACE,                    // {
        LEXJ_SEP_RBRACKET,                  // ]
        LEXJ_SEP_RBRACE,                    // }
        
        LEXJ_KWD_LOWEST=LEX_CLASS_KWD_GROUP,
        LEXJ_KWD_FALSE,                     // false
        LEXJ_KWD_NULL,                      // null
        LEXJ_KWD_TRUE,                      // true
        
    } LEXJ_CLASS;
    
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return:   pointer to lexj object if successful, otherwise OBJ_NIL.
     */
    LEXJ_DATA *     lexj_Alloc(
    );
    
    
    LEXJ_DATA *     lexj_NewFromAStr(
        ASTR_DATA       *pStr,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );
    
    LEXJ_DATA *     lexj_NewFromFile(
        FILE            *pFile,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );
    
    LEXJ_DATA *     lexj_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT     lexj_getLastError(
        LEXJ_DATA		*this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    LEXJ_DATA *     lexj_InitAStr(
        LEXJ_DATA       *this,
        ASTR_DATA       *pStr,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );
    
    LEXJ_DATA *     lexj_InitFile(
        LEXJ_DATA       *this,
        FILE            *pFile,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );
    
    LEXJ_DATA *     lexj_InitPath(
        LEXJ_DATA       *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );
    

    /*!
     Advance in the output token stream num tokens, refilling the
     empty positions in the parsed output queue.
     @return:   If successful, a token which must NOT be released,
     otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lexj_TokenAdvance(
        LEXJ_DATA		*this,
        uint16_t        numChrs
    );
    
    
    /*!
     Look Ahead in the token stream to the num'th token in the
     parsed output queue.
     @return:   If successful, a token which must NOT be released,
     otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lexj_TokenLookAhead(
        LEXJ_DATA       *this,
        uint16_t        num
    );
    
    
    /*!
     This routine adds the given token onto the tail of the
     FIFO output queue. Both, InputAdvance() and InputLookAhead(),
     return from this queue first if it contains any tokens
     before looking at the parsed input queue.
     @return:   If successful, ERESULT_SUCCESSFUL_COMPLETION,
     otherwise ERESULT_ERROR_???.
     */
    ERESULT         lexj_TokenPush(
        LEXJ_DATA       *this,
        TOKEN_DATA      *pChr
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = lexj_ToDebugString(this,4);
     @endcode:
     @param:    this    LEXJ object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *    lexj_ToDebugString(
        LEXJ_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* LEXJ_H */

