// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Lexical Analyzer Base (lex) Header
//****************************************************************
/*
 * Program
 *			Lexical Analyzer Base (lex)
 * Purpose
 *			This object provides a basis for creating a Lexical
 *          Analyzer/Scanner.  A Lexical Analyzer/Scanner accepts
 *          a source input token stream and combines those tokens
 *          into sub-phrases of the language such as operators,
 *          keywords, etc. It then emits an output token stream
 *          for use in a parser to construct phrases.
 *
 *          This base uses a base output token and wide-char
 *          work string which are manipulated by protected
 *          methods.
 *
 *          The input token stream is provided by two functions
 *          which must be supplied. Those functions must allow 
 *          the lexer to look-ahead in the input stream and then
 *          advance the input pointer as needed.  Since we use
 *          look ahead, we will never scan backwards.
 *
 *          The lexical parser is provided at initialization
 *          and creates the output stream. A default one that
 *          just passes input tokens to the output is the default.
 *
 *          The output stream also has a push back facility that
 *          allows tokens to be pushed onto a FIFO queue. The
 *          queue provides output tokens until empty temporarily
 *          overriding the normal lexical parsing output queue.
 *
 * Remarks
 *	1.      To utilize this base class, you need to provide the
 *          input look ahead and advance function.  In addition,
 *          you probably want to provide a parse function and
 *          possibly error functions.
 *  2.      This object requires the use of the Static String table
 *          for any tokenized strings. Strings may not be self-
 *          contained within a token.
 *
 * History
 *	09/07/2015 Generated
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
#include        <szTbl.h>
#include        <token.h>


#ifndef         LEX_H
#define         LEX_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    typedef enum lex_class_e {
        /* Values below 256 are a character by itself that makes
         * its own token class. All other classes for groups of
         * characters should be allocated in the range above
         * LEX_CLASS_GROUP_LOWEST.
         */
        LEX_CLASS_EOF=-1,
        LEX_CLASS_RESERVED=0,
        
        LEX_CLASS_GROUP_LOWEST=256,
        
        LEX_CLASS_COMMENT_GROUP=256,
        
        LEX_CLASS_CONSTANT_GROUP=512,
        LEX_CONSTANT_CHAR,
        LEX_CONSTANT_CHAR_WIDE,
        LEX_CONSTANT_FLOAT,
        LEX_CONSTANT_INTEGER,
        LEX_CONSTANT_STRING,
        LEX_CONSTANT_STRING_WIDE,
        
        LEX_IDENTIFIER=750,
        
        LEX_CLASS_SEP_GROUP=756,
        
        LEX_CLASS_OP_GROUP=1024,
        
        LEX_CLASS_KWD_GROUP=1280,
        
        LEX_CLASS_SPCL_GROUP=1536,
        
        LEX_CLASS_HIGHEST=2048,
        
    } LEX_CLASS;
    
    
    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct lex_data_s	LEX_DATA;

    typedef struct lex_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in $P_object.c.

        // Properties:
        ERESULT_DATA *  (*pGetErrors)(
            LEX_DATA        *this
        );
        bool            (*pSetErrors)(
            LEX_DATA        *this,
            ERESULT_DATA    *pValue
        );
        
        bool            (*pSetParserFunction)(
            LEX_DATA        *this,
            bool            (*pParser)(OBJ_ID, TOKEN_DATA *),
            OBJ_ID          pParseObj
        );
        
        bool            (*pSetSourceFunction)(
            LEX_DATA        *this,
            TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t),
            TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
            OBJ_ID          pSrcObj
        );
        
        W32STR_DATA *   (*pGetString)(
            LEX_DATA        *this
        );
        
        TOKEN_DATA *    (*pGetToken)(
            LEX_DATA		*this
        );
        
        // Methods:
        TOKEN_DATA *    (*pInputAdvance)(
            LEX_DATA		*this,
            uint16_t        numChrs
        );

        TOKEN_DATA *    (*pInputLookAhead)(
            LEX_DATA        *this,
            uint16_t        num
        );
        
        TOKEN_DATA *    (*pTokenAdvance)(
            LEX_DATA        *this,
            uint16_t        num
        );
        
        TOKEN_DATA *    (*pTokenLookAhead)(
            LEX_DATA        *this,
            uint16_t        num
        );
        
        ERESULT         (*pTokenPush)(
            LEX_DATA        *this,
            TOKEN_DATA      *pChr
        );
        
    } LEX_VTBL;

    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the lex including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    LEX_DATA *     lex_Alloc(
        void
    );
    
    
    LEX_DATA *     lex_New(
        uint16_t        k
    );
    
    
    const
    int32_t *       lex_SetWhiteSpace(
        void
    );

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ERESULT_DATA *  lex_getErrors(
        LEX_DATA        *this
    );
    
    bool            lex_setErrors(
        LEX_DATA        *this,
        ERESULT_DATA    *pValue
    );
    
    
    ERESULT         lex_getLastError(
        LEX_DATA        *this
    );
    
    
    bool            lex_setParserFunction(
        LEX_DATA        *this,
        bool            (*pParser)(OBJ_ID, TOKEN_DATA *),
        OBJ_ID          pParseObj
    );
    
    
    bool            lex_setSourceFunction(
        LEX_DATA        *this,
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    );
    
    
    W32STR_DATA *   lex_getString(
        LEX_DATA        *this
    );
    
    
    TOKEN_DATA *    lex_getToken(
        LEX_DATA		*this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     This routine starts/restarts the checkpoint process for backtracking
     parsers by accumulating all tokens which are advanced over. The
     accumulated tokens can be re-used by calling the Restore() method 
     or abandoned by the Discard() method. If a restart is being requested,
     it is the same as a Discard() followed by a Checkpoint().
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         lex_Checkpoint(
        LEX_DATA        *this
    );
    
    
    /*!
     This routine discards all tokens accumulated since the last checkpoint
     and terminates the checkpoint process.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         lex_Restart(
        LEX_DATA        *this
    );
    
    
    LEX_DATA *      lex_Init(
        LEX_DATA        *this,
        uint16_t        k                   // Size of Look-ahead token buffer
    );


    /*!
     Advance in the input token stream num tokens, refilling the
     empty positions in the unparsed input queue.
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_InputAdvance(
        LEX_DATA        *this,
        uint16_t        num
    );
    
    
    /*!
     Look Ahead in the input token stream to the num'th token in the
     unparsed input queue.
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_InputLookAhead(
        LEX_DATA        *this,
        uint16_t        num
    );
    
    
    /*!
     This routine restarts token the flow from the last checkpoint and
     terminates the checkpoint process.
     @return:   If successful, ERESULT_SUCCESS, otherwise ERESULT_ERROR_???.
     */
    ERESULT         lex_Restart(
        LEX_DATA		*this
    );
    
    
    /*!
     Advance in the output token stream num tokens, refilling the
     empty positions in the parsed output queue.
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_TokenAdvance(
        LEX_DATA		*this,
        uint16_t        numChrs
    );
    
    
    /*!
     Look Ahead in the token stream to the num'th token in the
     parsed output queue.
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    lex_TokenLookAhead(
        LEX_DATA        *this,
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
    ERESULT         lex_TokenPush(
        LEX_DATA        *this,
        TOKEN_DATA      *pChr
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     lex_ToDebugString(
        LEX_DATA        *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* LEX_H */

