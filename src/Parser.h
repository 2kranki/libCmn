// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Parser Base (Parser) Header
//****************************************************************
/*
 * Program
 *			Parser Base (Parser)
 * Purpose
 *          This object provides a base object for a parser.  It
 *          contains the basic elements that most parsers need.
 *
 * Remarks
 *	1.      None
 *
 * History
 *  07/03/2015 Generated
 *	12/15/2019 Regenerated
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
#include        <Compiler.h>
#include        <laInterface.h>
#include        <Lex.h>
#include        <Node.h>
#include        <ObjList.h>
#include        <SrcLoc.h>
#include        <Syms.h>


#ifndef         PARSER_H
#define         PARSER_H


//#define   PARSER_JSON_SUPPORT 1
//#define   PARSER_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Parser_data_s	    PARSER_DATA;        // Inherits from OBJ
    typedef struct Parser_class_data_s  PARSER_CLASS_DATA;  // Inherits from OBJ

    typedef struct Parser_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Parser_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PARSER_DATA *);
    } PARSER_VTBL;

    typedef struct Parser_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Parser_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(PARSER_DATA *);
    } PARSER_CLASS_VTBL;


    typedef enum Parser_action_type_e {
        PARSER_ACTION_MATCH=1,          // Pop Parse Stack and Get Next Token
        PARSER_ACTION_ACCEPT,           // Accept the Parse
        PARSER_ACTION_PROD              // Push Production onto Parse Stack
    } PARSER_ACTION_TYPE;


    typedef struct Parser_common_s {
        TOKEN_DATA      *pToken;
        LA_INTERFACE    *pLA;           // Look-ahead Lexical Interface
        LEX_DATA        *pLex;
        NODETREE_DATA   *pTree;         // Parse Tree
        SYMS_DATA       *pGlobals;      // Global Symbols
        SYMS_DATA       *pLocals;
        OBJ_ID          pAux1;
        OBJ_ID          pAux2;
        int32_t         tokenClass;
        uint32_t        xtra[15];       // Extra space to be used as needed
    } PARSER_COMMON;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  PARSER_SINGLETON
    PARSER_DATA *   Parser_Shared (
        void
    );

    bool            Parser_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Parser object if successful, otherwise OBJ_NIL.
     */
    PARSER_DATA *   Parser_Alloc (
        void
    );
    
    
    OBJ_ID          Parser_Class (
        void
    );
    
    
    PARSER_DATA *   Parser_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJ_ID          Parser_getAux1 (
        PARSER_DATA     *this
    );

    bool            Parser_setAux1 (
        PARSER_DATA     *this,
        OBJ_ID           pValue
    );


    OBJ_ID          Parser_getAux2 (
        PARSER_DATA     *this
    );

    bool            Parser_setAux2 (
        PARSER_DATA     *this,
        OBJ_ID           pValue
    );


    PARSER_COMMON * Parser_getCommon (
        PARSER_DATA     *this
    );


    COMPILER_DATA * Parser_getCompiler (
        PARSER_DATA     *this
    );

    bool            Parser_setCompiler (
        PARSER_DATA     *this,
        COMPILER_DATA   *pValue
    );


    SYMS_DATA *     Parser_getGlobals (
        PARSER_DATA     *this
    );


    /*! Lexer property which is separate from the
        source methods.  If you use this property,
        you will probably want to set it up as the
        source functions/object as well.
    */
    LEX_DATA *      Parser_getLex (
        PARSER_DATA     *this
    );

    bool            Parser_setLex (
        PARSER_DATA     *this,
        LEX_DATA        *pValue
    );


    SYMS_DATA *     Parser_getLocals (
        PARSER_DATA     *this
    );


    bool            Parser_setParseFunction (
        PARSER_DATA    *this,
        bool            (*pParse)(OBJ_ID,NODETREE_DATA **),
        OBJ_ID          pParseObj
    );


    OBJARRAY_DATA * Parser_getSemanticStack (
        PARSER_DATA     *this
    );


    bool            Parser_setSourceFunction (
        PARSER_DATA     *this,
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID, uint16_t),
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID, uint16_t),
        OBJ_ID          pSrcObj
    );


    TOKEN_DATA *    Parser_getToken (
        PARSER_DATA     *this
    );


    OBJ_ID          Parser_getSymbols (
        PARSER_DATA     *this
    );

    bool            Parser_setSymbols (
        PARSER_DATA     *this,
        OBJ_ID          pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create a new fatal error and add it to the internal collection.
     Execute the Fatal Error Exit if available.
     @param     this    object pointer
     @param     severity error severity as defined in enum srcError_Severity
     @param     pLocation Location of first character where error occurred (optional)
     @param     pErrorString  A character string describing the error without
                        the source location
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_* error code.
     */
    bool            Parser_AddErrorA (
        PARSER_DATA     *this,
        uint16_t        severity,
        const
        SRCLOC          *pLocation,
        const
        char            *pErrorString,
        ...
    );

    bool            Parser_AddErrorArgsA (
        PARSER_DATA     *this,
        uint16_t        severity,
        const
        SRCLOC          *pLocation,
        const
        char            *pErrorString,
        va_list         arg_ptr
    );


    /*!
     Create a new fatal error and add it to the internal collection.
     Execute the Fatal Error Exit if available.
     @param     this    object pointer
     @param     pLocation Location of first character where error occurred (optional)
     @param     pErrorString  A character string describing the error without
                            the source location
     @return    If successful, ERESULT_SUCCESS; otherwise, an ERESULT_* error code.
     */
    ERESULT         Parser_AddFatalA (
        PARSER_DATA     *this,
        const
        SRCLOC          *pLocation,
        const
        char            *pErrorString,
        ...
    );

    ERESULT         Parser_AddFatalArgsA (
        PARSER_DATA     *this,
        const
        SRCLOC          *pLocation,
        const
        char            *pErrorString,
        va_list         arg_ptr
    );


    PARSER_DATA *   Parser_Init (
        PARSER_DATA     *this
    );


    /*!
     Advance in the input token stream num tokens, refilling the
     empty positions in the input queue.
     @return:   If successful, the current token after the advance
                which must NOT be released, otherwise OBJ_NIL.
     */
    int32_t         Parser_Advance (
        PARSER_DATA     *this,
        uint16_t        num,
        TOKEN_DATA      **ppToken   // Optional Token pointer
    );
    
    
    int32_t         Parser_LookAhead (
        PARSER_DATA     *this,
        uint16_t        num,
        TOKEN_DATA      **ppToken   // Optional Token pointer
    );
    
    
    /*!
     Try to match the current input token with the given character.
     If it matches, advance the input token stream and return
     the matched token.
     @return:   If successful, the matched token which must be
                copied if it needs to be retained, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Parser_MatchInputChr (
        PARSER_DATA     *this,
        int32_t         chr
    );


    /*!
     Try to match the current input token with the given class.
     If it matches, advance the input token stream and return
     the matched token.
     @return:   If successful, the matched token which must be
                copied if it needs to be retained, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Parser_MatchInputCls (
        PARSER_DATA     *this,
        int32_t         cls
    );


    /*!
     Try to match the current input token with a set of classes.
     If it matches, advance the input token stream and return
     the matched token.
     @return:   If successful, the matched token which must be
                copied if it needs to be retained, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Parser_MatchInputClsSet (
        PARSER_DATA     *this,
        int32_t         *pSet           // NULL-terminated Set of Classes
    );


    /*!
     Try to match the current input token with a range of
     characters. The range includes the range characters.
     If it matches, advance the input token stream and return
     the matched token.
     @return:   If successful, the matched token which must be
                copied if it needs to be retained, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Parser_MatchInputRange (
        PARSER_DATA     *this,
        int32_t         chrBeg,
        int32_t         chrEnd
    );


    /*!
     Try to match the current input token with a set of characters.
     If it matches, advance the input token stream and return
     the matched token.
     @return:   If successful, the matched token which must be
                copied if it needs to be retained, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    Parser_MatchInputSet (
        PARSER_DATA     *this,
        int32_t         *pSet           // NULL-terminated Set of Characters
    );


    ERESULT         Parser_Parse (
        PARSER_DATA     *this,
        NODETREE_DATA   **ppTree
    );
    
    
    NODE_DATA *     Parser_Property (
        PARSER_DATA     *this,
        const
        char            *pName
    );
    
    
    ERESULT         Parser_PropertyAdd (
        PARSER_DATA     *this,
        NODE_DATA       *pData
    );
    
    
    uint16_t        Parser_PropertyCount (
        PARSER_DATA     *this
    );
    
    
    NODEARRAY_DATA * Parser_Properties (
        PARSER_DATA     *this
    );
    
    
    OBJ_ID          Parser_SemPop (
        PARSER_DATA     *this
    );
    
    
    bool            Parser_SemPush (
        PARSER_DATA     *this,
        OBJ_ID          pItem
    );

    
    OBJ_ID          Parser_SemTop (
        PARSER_DATA     *this
    );
    
    
    ERESULT         Parser_SetupLex (
        PARSER_DATA     *this,
        LEX_DATA        *pLex
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Parser_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Parser_ToDebugString (
        PARSER_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* PARSER_H */

