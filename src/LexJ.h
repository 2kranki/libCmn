// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  HJSON Lexical Analyzer (LexJ) Header
//****************************************************************
/*
 * Program
 *          HJSON Lexical Analyzer (LexJ)
 * Purpose
 *          This object provides a HJSON Lexical Analyzer/Scanner.
 *          The Scanner accepts a source input token stream and
 *          combines those character tokens into JSON sub-phrases
 *          such as numbers, strings, etc. It then emits an output
 *          token stream for use in a HJSON parser. It absorbs
 *          white-space and does not pass it on.
 *
 * Remarks
 *    1.    I changed the definition of the quoteless string to end
 *          with '\n' and any of '{','}','[',']',':',','. This al-
 *          lows it to be used for object names as well as quote-
 *          less strings. If any of those characters needs to be
 *          added to a string, then simply quote the string.
 *
 * History
 *  07/02/2017 Generated
 *  12/09/2020 Regenerated
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
#include        <laInterface.h>
#include        <Lex.h>
#include        <Token.h>


#ifndef         LEXJ_H
#define         LEXJ_H


//#define   LEXJ_IS_IMMUTABLE     1
//#define   LEXJ_JSON_SUPPORT     1
//#define   LEXJ_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct LexJ_data_s  LEXJ_DATA;            // Inherits from LEX
    typedef struct LexJ_class_data_s LEXJ_CLASS_DATA;   // Inherits from OBJ

    typedef struct LexJ_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexJ_object.c.
        // Properties:
        // Methods:

        /*! Advance() advances the current input source num elements.
         @param     this    object pointer
         @param     num     number of tokens to advance
         @param     ppToken optional pointer to return token pointer into
                            (If this token needs to be retained, then it
                            must be copied. The lexical analyzer may re-
                            use it.)
         @return    token type and token address if ppToken is non-null;
                    otherwise, EOF(-1).
         */
        int32_t             (*pAdvance)(
                OBJ_ID          this,
                uint16_t        num,
                TOKEN_DATA      *ppToken    // Optional Token pointer
        );

        /*! LookAhead() returns the requested token if it is within its
            look-ahead buffer. The look-ahead queue size is set when the
            Lexical Analyzer is created.
         @param     this    object pointer
         @param     num     number of tokens to advance
         @param     ppToken optional pointer to return token pointer into
                            (If this token needs to be retained, then it
                            must be copied. The lexical analyzer may re-
                            use it.)
         @return    token type and token address if ppToken is non-null;
                    otherwise, EOF(-1).
         */
        int32_t             (*pLookAhead)(
                OBJ_ID,
                uint16_t        num,
                TOKEN_DATA      *ppToken    // Optional Token pointer
        );

        /*! BufferSize() returns the Lexical Analyzer's look-ahead queue
         size.
         @param     this    object pointer
         @return    the Lexical Analyzer's look-ahead queue size
         */
        int32_t             (*pQueueSize)(
                OBJ_ID          this
        );

    } LEXJ_VTBL;

    typedef struct LexJ_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexJ_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXJ_DATA *);
    } LEXJ_CLASS_VTBL;


    typedef enum LexJ_class_e {
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
        LEXJ_SEP_EQUAL,                     // =
        LEXJ_SEP_LBRACKET,                  // [
        LEXJ_SEP_LBRACE,                    // {
        LEXJ_SEP_MINUS,                     // -
        LEXJ_SEP_PLUS,                      // +
        LEXJ_SEP_RBRACKET,                  // ]
        LEXJ_SEP_RBRACE,                    // }

        LEXJ_KWD_LOWEST=LEX_CLASS_KWD_GROUP,
        LEXJ_KWD_FALSE,                     // false
        LEXJ_KWD_NULL,                      // null
        LEXJ_KWD_TRUE,                      // true

    } LEXJ_CLASS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEXJ_SINGLETON
    LEXJ_DATA *     LexJ_Shared (
        void
    );

    void            LexJ_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to LexJ object if successful, otherwise OBJ_NIL.
     */
    LEXJ_DATA *     LexJ_Alloc (
        void
    );
    
    
    OBJ_ID          LexJ_Class (
        void
    );
    
    
    LEXJ_DATA *     LexJ_New (
        void
    );
    
    LEXJ_DATA *     LexJ_NewA(
        const
        char            *pStr,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );

    LEXJ_DATA *     LexJ_NewFromAStr(
        ASTR_DATA       *pStr,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );

    LEXJ_DATA *     LexJ_NewFromFile(
        FILE            *pFile,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );

    LEXJ_DATA *     LexJ_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    );


#ifdef  LEXJ_JSON_SUPPORT
    LEXJ_DATA *     LexJ_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEXJ_DATA *     LexJ_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    LA_INTERFACE *  Lex_getLaInterface (
        LEX_DATA        *this
    );


    LEX_DATA *      LexJ_getLex(
        LEXJ_DATA       *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    LEXJ_DATA *     LexJ_Init (
        LEXJ_DATA       *this
    );


#ifdef  LEXJ_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LexJ_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexJ_ToJson (
        LEXJ_DATA   *this
    );
#endif


    /*!
     Advance in the output token stream num tokens, refilling the
     empty positions in the parsed output queue.
     @return:   If successful, a token which must NOT be released,
     otherwise OBJ_NIL.
     */
    TOKEN_DATA *    LexJ_TokenAdvance(
        LEXJ_DATA        *this,
        uint16_t        numChrs
    );


    /*!
     Look Ahead in the token stream to the num'th token in the
     parsed output queue.
     @return:   If successful, a token which must NOT be released,
     otherwise OBJ_NIL.
     */
    TOKEN_DATA *    LexJ_TokenLookAhead(
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
    ERESULT         LexJ_TokenPush(
        LEXJ_DATA       *this,
        TOKEN_DATA      *pChr
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LexJ_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexJ_ToDebugString (
        LEXJ_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEXJ_H */

