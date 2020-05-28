// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Parser_internal.h
 *	Generated 12/15/2019 15:07:38
 *
 * Notes:
 *  --	N/A
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




#include        <Parser.h>
#include        <JsonIn.h>
#include        <lex_internal.h>
#include        <ObjArray.h>
#include        <pplex.h>
#include        <SrcErrors.h>


#ifndef PARSER_INTERNAL_H
#define	PARSER_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Parser_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    LEX_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    #define PARSER_INIT_DONE    OBJ_FLAG_USER1

    // Common Data
    LEX_DATA        *pLex;
    COMPILER_DATA   *pCompiler;
    SRCERRORS_DATA  *pErrors;
    OBJ_ID          pAux1;
    OBJ_ID          pAux2;
    NODEHASH_DATA   *pProperties;

    // Input Data/Routines
    TOKEN_DATA *    (*pSrcChrAdvance)(OBJ_ID, uint16_t);
    TOKEN_DATA *    (*pSrcChrLookAhead)(OBJ_ID, uint16_t);
    OBJ_ID          pSrcObj;
    uint16_t        sizeInputs;
    uint16_t        curInputs;
    TOKEN_DATA      *pInputs;
    
    // Parse Data
    bool            (*pParse)(OBJ_ID, NODETREE_DATA **);
    OBJ_ID          pParseObj;
    NODEARRAY_DATA  *pSemanticStack;
    
    uint32_t        numErrors;

};
#pragma pack(pop)

    extern
    struct Parser_class_data_s  Parser_ClassObj;

    extern
    const
    PARSER_VTBL         Parser_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PARSER_SINGLETON
    PARSER_DATA *   Parser_getSingleton (
        void
    );

    bool            Parser_setSingleton (
     PARSER_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Parser_getSuperVtbl (
        PARSER_DATA     *this
    );


    void            Parser_Dealloc (
        OBJ_ID          objId
    );


    TOKEN_DATA *    Parser_InputAdvance(
        PARSER_DATA     *cbp,
        uint16_t        numChrs
    );


    TOKEN_DATA *    Parser_InputLookAhead(
        PARSER_DATA     *cbp,
        uint16_t        num
    );


    ERESULT         Parser_InputNextChar(
        PARSER_DATA     *cbp
    );


    TOKEN_DATA *    Parser_MatchInputChr(
        PARSER_DATA     *cbp,
        int32_t         chr
    );


#ifdef  PARSER_JSON_SUPPORT
    PARSER_DATA *       Parser_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          Parser_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     Parser_ToJson (
        PARSER_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			Parser_Validate (
        PARSER_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PARSER_INTERNAL_H */

