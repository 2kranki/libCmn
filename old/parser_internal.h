// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   parser_internal.h
 *	Generated 07/03/2015 21:39:30
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




#include    <parser.h>
#include    <objArray.h>
#include    <srcErrors.h>


#ifndef PARSER_INTERNAL_H
#define	PARSER_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


    
#pragma pack(push, 1)
    struct parser_data_s	{
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA        super;
        OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
#define PARSER_INIT_DONE    5

        // Common Data
        COMPILER_DATA   *pCompiler;
        SRCERRORS_DATA  *pErrors;
        OBJ_ID          pAux1;
        OBJ_ID          pAux2;
        NODEHASH_DATA   *pProperties;

        // Input Data/Routines
        TOKEN_DATA *   (*pSrcChrAdvance)(OBJ_ID, uint16_t);
        TOKEN_DATA *   (*pSrcChrLookAhead)(OBJ_ID, uint16_t);
        OBJ_ID          pSrcObj;
        uint16_t        sizeInputs;
        uint16_t        curInputs;
        TOKEN_DATA      *pInputs;
        
        // Parse Data
        bool            (*pParse)(OBJ_ID, NODETREE_DATA **);
        OBJ_ID          pParseObj;
        OBJARRAY_DATA   *pSemanticStack;
        
        uint32_t        numErrors;

    };
#pragma pack(pop)

    
    extern
    const
    struct parser_class_data_s  parser_ClassObj;
    
    extern
    const
    PARSER_VTBL     parser_Vtbl;



    // Internal Functions
    void            parser_Dealloc(
        OBJ_ID          objId
    );

    
    TOKEN_DATA *    parser_InputAdvance(
        PARSER_DATA     *cbp,
        uint16_t        numChrs
    );
    
    
    TOKEN_DATA *    parser_InputLookAhead(
        PARSER_DATA     *cbp,
        uint16_t        num
    );
    
    
    ERESULT         parser_InputNextChar(
        PARSER_DATA     *cbp
    );
    
    
    TOKEN_DATA *    parser_MatchInputChr(
        PARSER_DATA     *cbp,
        int32_t         chr
    );
    
    
    void *          parser_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			parser_Validate(
        PARSER_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PARSER_INTERNAL_H */

