// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Parser Base (parser) Header
//****************************************************************
/*
 * Program
 *			Parser Base (parser)
 * Purpose
 *			This object provides a base object for a parser.  It
 *          contains the basic elements that most parsers need.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal parser. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	07/03/2015 Generated
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
#include        <compiler.h>
#include        <node.h>
#include        <srcLoc.h>


#ifndef         PARSER_H
#define         PARSER_H    1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct parser_data_s	PARSER_DATA;

    typedef struct parser_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } PARSER_VTBL;

    
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the parser including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    PARSER_DATA *     parser_Alloc(
        void
    );
    
    
    PARSER_DATA *     parser_New(
        uint16_t        k
    );
    
    
    typedef enum parser_action_type_e {
        PARSER_ACTION_MATCH=1,          // Pop Parse Stack and Get Next Token
        PARSER_ACTION_ACCEPT,           // Accept the Parse
        PARSER_ACTION_PROD              // Push Production onto Parse Stack
    } PARSER_ACTION_TYPE;

    
    
    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJ_ID          parser_getAux1(
        PARSER_DATA     *this
    );
    
    bool            parser_setAux1(
        PARSER_DATA     *this,
        OBJ_ID           pValue
    );
    
    
    OBJ_ID          parser_getAux2(
        PARSER_DATA     *this
    );
    
    bool            parser_setAux2(
        PARSER_DATA     *this,
        OBJ_ID           pValue
    );
    
    
    COMPILER_DATA *  parser_getCompiler(
        PARSER_DATA     *this
    );
    
    bool            parser_setCompiler(
        PARSER_DATA     *this,
        COMPILER_DATA   *pValue
    );
    
    
    SRCERRORS_DATA * parser_getErrors(
        PARSER_DATA     *this
    );
    
    bool            parser_setErrors(
        PARSER_DATA     *this,
        SRCERRORS_DATA  *pValue
    );
    
    
    bool            parser_setParseFunction(
        PARSER_DATA    *this,
        bool            (*pParse)(OBJ_ID,NODETREE_DATA **),
        OBJ_ID          pParseObj
    );
    
    
    OBJARRAY_DATA * parser_getSemanticStack(
        PARSER_DATA     *this
    );
    
    
    bool            parser_setSourceFunction(
        PARSER_DATA     *this,
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID, uint16_t),
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID, uint16_t),
        OBJ_ID          pSrcObj
    );
    
    
    TOKEN_DATA *    parser_getToken(
        PARSER_DATA     *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    
    PARSER_DATA *   parser_Init(
        PARSER_DATA     *this,
        uint16_t        k
    );


    /*!
     Advance in the input token stream num tokens, refilling the
     empty positions in the input queue.
     @return:   If successful, the current token after the advance
                which must NOT be released, otherwise OBJ_NIL.
     */
    TOKEN_DATA *    parser_InputAdvance(
        PARSER_DATA     *this,
        uint16_t        numChrs
    );
    
    
    TOKEN_DATA *    parser_InputLookAhead(
        PARSER_DATA     *this,
        uint16_t        num
    );
    
    
    ERESULT         parser_Parse(
        PARSER_DATA     *this,
        NODETREE_DATA   **ppTree
    );
    
    
    NODE_DATA *     parser_Property(
        PARSER_DATA     *this,
        const
        char            *pName
    );
    
    
    ERESULT         parser_PropertyAdd(
        PARSER_DATA		*this,
        NODE_DATA       *pData
    );
    
    
    uint16_t        parser_PropertyCount(
        PARSER_DATA		*this
    );
    
    
    NODEARRAY_DATA * parser_Properties(
        PARSER_DATA     *this
    );
    
    
    NODE_DATA *     parser_SemPop(
        PARSER_DATA     *this
    );
    
    
    bool			parser_SemPush(
        PARSER_DATA     *this,
        NODE_DATA       *pItem
    );

    
    NODE_DATA *     parser_SemTop(
        PARSER_DATA     *this
    );
    
    
    

#ifdef	__cplusplus
}
#endif

#endif	/* PARSER_H */

