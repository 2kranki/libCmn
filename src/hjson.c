// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   hjson.c
 *	Generated 07/08/2017 17:18:30
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include <hjson_internal.h>
#include <LexJ_internal.h>
#include <trace.h>
#include <JsonIn.h>
#include <NodeArray.h>
#include <NodeHash.h>
#include <SrcErrors.h>



#ifdef	__cplusplus
extern "C" {
#endif
    



 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                   D i s p l a y  T o k e n
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    void            hjson_DisplayToken (
        HJSON_DATA      *this,
        TOKEN_DATA      *pToken
    )
    {
        int32_t         tokenClass;
        char            *pStrA;

        BREAK_NULL(pToken);
        if (pToken) {
            pStrA = Token_getTextA(pToken);
            tokenClass = Token_getClass(pToken);
            TRC_OBJ(
                    this,
                    "\tInput Token: %s\n\t\tClass: %s\n\n",
                    pStrA,
                    LexJ_Class2Str(tokenClass)
            );
            mem_Free(pStrA);
        }


    }
#endif



    //---------------------------------------------------------------
    //                   P a r s e  A r r a y
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseArray (
        HJSON_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pChild = OBJ_NIL;
        //bool            fRc;
        SRCLOC_DATA     *pLoc = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);

        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        if( tokenClass == LEXJ_SEP_LBRACKET ) {
            TRC_OBJ(this,"\t[ - found\n");
            if (OBJ_NIL == pLoc) {
                pLoc = Token_ToSrcLoc(pToken);
            }
            LexJ_TokenAdvance(this->pLexJ, 1);
        }
        else {
            return pNode;
        }
        
        pArray = NodeArray_New( );
        if (pArray == OBJ_NIL) {
            SrcErrors_AddFatalFromTokenA(OBJ_NIL, pToken, "Out of Memory");
            obj_Release(pLoc);
            return pNode;
        }
        
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        if( tokenClass == LEXJ_SEP_RBRACKET )   // Empty Array
            goto chkRBracket;
        
        pChild = hjson_ParseValue(this);
        if (pChild) {
            NodeArray_AppendNode(pArray, pChild, NULL);
            obj_Release(pChild);
            for (;;) {
                
                pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
                BREAK_NULL(pToken);
                TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
                tokenClass = Token_getClass(pToken);
                if( tokenClass == LEXJ_SEP_COMMA ) {
                    TRC_OBJ(this,"\t, - found\n");
                    LexJ_TokenAdvance(this->pLexJ, 1);
                    continue;
                }
                if( tokenClass == LEXJ_SEP_RBRACKET ) {
                    break;
                }
                
                pChild = hjson_ParseValue(this);
                if (pChild) {
                    NodeArray_AppendNode(pArray, pChild, NULL);
                    obj_Release(pChild);
                }
                else {
                    break;
                }
            }
            
        chkRBracket:
            pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
            TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
            tokenClass = Token_getClass(pToken);
            if( tokenClass == LEXJ_SEP_RBRACKET ) {
                TRC_OBJ(this,"\t] - found\n");
                LexJ_TokenAdvance(this->pLexJ, 1);
            }
            else {
                ASTR_DATA           *pStr;
                pStr = Token_ToDataString(pToken);
                SrcErrors_AddFatalFromTokenA(
                                             OBJ_NIL,
                                             pToken,
                                             "Expecting ']', but found %s",
                                             AStr_getData(pStr)
                                             );
                obj_Release(pStr);
                obj_Release(pLoc);
                obj_Release(pArray);
                return OBJ_NIL;
            }
        }
        
        pNode = JsonIn_NodeFromArray(pArray);
        obj_Release(pArray);
        pArray = OBJ_NIL;
        if (pNode == OBJ_NIL) {
            SrcErrors_AddFatalA(OBJ_NIL, NULL, "Out of Memory");
        } else {
            if (pLoc) {
                Node_setExtra(pNode, pLoc);
            }
        }
        obj_Release(pLoc);
        pLoc = OBJ_NIL;

        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  H a s h
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseHash (
        HJSON_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        NODE_DATA       *pNode = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        NODE_DATA       *pChild;
        ERESULT         eRc;
        SRCLOC_DATA     *pLoc = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        if( tokenClass == LEXJ_SEP_LBRACE ) {
            TRC_OBJ(this,"\t{ - found\n");
            if (OBJ_NIL == pLoc) {
                pLoc = Token_ToSrcLoc(pToken);
            }
            LexJ_TokenAdvance(this->pLexJ, 1);
        }
        else {
            return OBJ_NIL;
        }
        
        pHash = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
        if (pHash == OBJ_NIL) {
            DEBUG_BREAK();
            obj_Release(pLoc);
            return OBJ_NIL;
        }

        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        if( tokenClass == LEXJ_SEP_RBRACE )
            goto chkRBrace;
        
        pChild = hjson_ParsePair(this);
        if (pChild) {
            eRc = NodeHash_Add(pHash, pChild);
            obj_Release(pChild);
            pChild = OBJ_NIL;

            for (;;) {
                pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
                TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
                tokenClass = Token_getClass(pToken);
                if( tokenClass == LEXJ_SEP_COMMA ) {
                    TRC_OBJ(this,"\t, - found\n");
                    LexJ_TokenAdvance(this->pLexJ, 1);
                    continue;
                }
                if( tokenClass == LEXJ_SEP_RBRACE ) {
                    break;
                }
                
                pChild = hjson_ParsePair(this);
                if (pChild) {
                    eRc = NodeHash_Add(pHash, pChild);
                    obj_Release(pChild);
                    pChild = OBJ_NIL;
                }
                else {
                    break;
                }
            }
        }
        
    chkRBrace:
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        if( tokenClass == LEXJ_SEP_RBRACE ) {
            TRC_OBJ(this,"\t} - found\n");
            LexJ_TokenAdvance(this->pLexJ, 1);
        }
        else {
            ASTR_DATA           *pStr;
            pStr = Token_ToDataString(pToken);
            SrcErrors_AddFatalFromTokenA(
                OBJ_NIL,
                pToken,
                "Expecting '}', but found %s",
                AStr_getData(pStr)
            );
            obj_Release(pStr);
            obj_Release(pLoc);
            goto exit;
        }
        
        pNode = JsonIn_NodeFromHash(pHash);
        if (pLoc && pNode) {
            Node_setExtra(pNode, pLoc);
        }
        obj_Release(pLoc);
        pLoc = OBJ_NIL;

    exit:
        obj_Release(pHash);
        pHash = OBJ_NIL;
#ifdef NDEBUG
#else
        if (pNode == OBJ_NIL) {
            DEBUG_BREAK();
        }
#endif
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  K e y  W o r d
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseKeyWord (
        HJSON_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        NODE_DATA       *pNode = OBJ_NIL;
        FALSE_DATA      *pFalse = OBJ_NIL;
        NULL_DATA       *pNull = OBJ_NIL;
        TRUE_DATA       *pTrue = OBJ_NIL;
        SRCLOC_DATA     *pLoc = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        if (OBJ_NIL == pLoc) {
            pLoc = Token_ToSrcLoc(pToken);
        }

        switch (tokenClass) {
                
            case LEXJ_KWD_FALSE:
                pFalse = False_New();
                pNode = Node_NewWithUTF8ConAndClass(0, "false", pFalse);
                obj_Release(pFalse);
                pFalse = OBJ_NIL;
                LexJ_TokenAdvance(this->pLexJ, 1);
                TRC_OBJ(this, "\tfalse\n");
                if (pLoc && pNode) {
                    Node_setExtra(pNode, pLoc);
                    obj_Release(pLoc);
                    pLoc = OBJ_NIL;
                }
                break;
                
            case LEXJ_KWD_NULL:
                pNull = Null_New();
                pNode = Node_NewWithUTF8ConAndClass(0, "null", pNull);
                obj_Release(pNull);
                pNull = OBJ_NIL;
                LexJ_TokenAdvance(this->pLexJ, 1);
                TRC_OBJ(this, "\tnull\n");
                if (pLoc && pNode) {
                    Node_setExtra(pNode, pLoc);
                    obj_Release(pLoc);
                    pLoc = OBJ_NIL;
                }
                break;
                
            case LEXJ_KWD_TRUE:
                pTrue = True_New();
                pNode = Node_NewWithUTF8ConAndClass(0, "true", pTrue);
                obj_Release(pTrue);
                pTrue = OBJ_NIL;
                LexJ_TokenAdvance(this->pLexJ, 1);
                TRC_OBJ(this, "\ttrue\n");
                if (pLoc && pNode) {
                    Node_setExtra(pNode, pLoc);
                    obj_Release(pLoc);
                    pLoc = OBJ_NIL;
                }
                break;
                
            default:
                break;
        }
        
        obj_Release(pLoc);
        pLoc = OBJ_NIL;
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  N a m e
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseName (
        HJSON_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        SRCLOC_DATA     *pLoc = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        pStr = Token_ToDataString(pToken);
        AStr_Trim(pStr);
        if (OBJ_NIL == pLoc) {
            pLoc = Token_ToSrcLoc(pToken);
        }
        if( tokenClass == LEXJ_CONSTANT_STRING ) {
            LexJ_TokenAdvance(this->pLexJ, 1);
        }
        else {
            obj_Release(pStr);
            obj_Release(pLoc);
            return OBJ_NIL;
        }
        
        if (pStr) {
            TRC_OBJ(this, "\tname: \"%s\"\n", AStr_getData(pStr));
            pNode = Node_NewWithUTF8ConAndClass(0, "name", pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            if (pLoc && pNode) {
                Node_setExtra(pNode, pLoc);
            }
        }
        
        obj_Release(pLoc);
        pLoc = OBJ_NIL;
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  N u m b e r
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseNumber (
        HJSON_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pSign = OBJ_NIL;
        char            sign = 0;
        SRCLOC_DATA     *pLoc = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        TRC_OBJ(this, "\ttoken class = %d\n", tokenClass);
#ifdef NDEBUG
#else
        if (Token_getChrW32(pToken)) {
            TRC_OBJ(this, "\ttoken string = \"%lc\"\n", Token_getChrW32(pToken));
        }
        //fprintf(stderr, "\tLEX_SEP_MINUS = %d\n", LEXJ_SEP_MINUS);
#endif
        if( (tokenClass == LEXJ_SEP_MINUS) || (tokenClass == LEXJ_SEP_PLUS) ) {
            pSign = Token_getTextAStr(pToken);
            sign = *AStr_getData(pSign);
            obj_Release(pSign);
            pSign = OBJ_NIL;
            if (OBJ_NIL == pLoc) {
                pLoc = Token_ToSrcLoc(pToken);
            }
            LexJ_TokenAdvance(this->pLexJ, 1);
            TRC_OBJ(this, "\tsign = %c\n", sign);
            BREAK_FALSE(((sign == '-') || (sign == '+')));

            pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
            TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
            tokenClass = Token_getClass(pToken);
            TRC_OBJ(this, "\ttoken class = %d\n", tokenClass);
#ifdef NDEBUG
#else
            if (Token_getChrW32(pToken)) {
                TRC_OBJ(this, "\ttoken string = \"%lc\"\n", Token_getChrW32(pToken));
            }
#endif
        }
        if( tokenClass == LEXJ_CONSTANT_INTEGER ) {
            pStr = Token_ToDataString(pToken);
            if (pStr) {
                if (sign) {
                    AStr_CharInsertW32(pStr, 1, sign);
                }
                TRC_OBJ(this, "\tinteger: \"%s\"\n", AStr_getData(pStr));
                pNode = Node_NewWithUTF8ConAndClass(0, "integer", pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
                if (OBJ_NIL == pLoc) {
                    pLoc = Token_ToSrcLoc(pToken);
                }
            }
            LexJ_TokenAdvance(this->pLexJ, 1);
        }
        else if( tokenClass == LEXJ_CONSTANT_FLOAT ) {
            pStr = Token_ToDataString(pToken);
            if (pStr) {
                if (sign) {
                    AStr_CharInsertW32(pStr, 1, sign);
                }
                TRC_OBJ(this, "\tfloat: \"%s\"\n", AStr_getData(pStr));
                pNode = Node_NewWithUTF8ConAndClass(0, "float", pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
                if (OBJ_NIL == pLoc) {
                    pLoc = Token_ToSrcLoc(pToken);
                }
            }
            LexJ_TokenAdvance(this->pLexJ, 1);
        }
        
        if (pLoc && pNode) {
            Node_setExtra(pNode, pLoc);
        }
        obj_Release(pLoc);
        pLoc = OBJ_NIL;
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //          P a r s e  N a m e - V a l u e  P a i r
    //---------------------------------------------------------------
    
    // We scan the Name as a string and return a node with the name
    // being that string and the value being the data portion of the
    // node.
    
    NODE_DATA *     hjson_ParsePair (
        HJSON_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        NODE_DATA       *pData = OBJ_NIL;
        NODE_DATA       *pName = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pszName;
        SRCLOC_DATA     *pLoc = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));

        pName = hjson_ParseName(this);
        if (pName == OBJ_NIL) {
            return OBJ_NIL;
        }
        pLoc = Node_getExtra(pName);
        obj_Retain(pLoc);

        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        if((tokenClass == LEXJ_SEP_COLON) || (tokenClass == LEXJ_SEP_EQUAL)) {
            LexJ_TokenAdvance(this->pLexJ, 1);
            TRC_OBJ(this, "\tfound :\n");
        }
        else {
            SrcErrors_AddFatalFromTokenA(
                OBJ_NIL,
                pToken,
                "Expecting ':' or '='"
            );
            obj_Release(pName);
            obj_Release(pLoc);
            return OBJ_NIL;
        }
        
        pData = hjson_ParseValue(this);
        if (pData == OBJ_NIL) {
            SrcErrors_AddFatalFromTokenA(
                OBJ_NIL,
                pToken,
                "Expecting \"value\""
            );
            obj_Release(pName);
            obj_Release(pLoc);
            return OBJ_NIL;
        }
        
        pszName = AStr_CStringA(Node_getData(pName), NULL);
        TRC_OBJ(this, "%s found:\n", __func__);
        TRC_OBJ(this, "\tname: %s\n", pszName);
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStrA;
            pStrA = Node_ToDebugString(pData, 8);
            TRC_OBJ(this, "\tdata:\n");
            TRC_OBJ(this, "%s\n", AStr_getData(pStrA));
            obj_Release(pStrA);
        }
#endif
        pNode = Node_NewWithUTF8AndClass(0, pszName, pData);
        mem_Free((void *)pszName);
        pszName = NULL;
        obj_Release(pData);
        pData = OBJ_NIL;
        obj_Release(pName);
        pName = OBJ_NIL;
        if (pLoc) {
            Node_setExtra(pNode, pLoc);
        }
        obj_Release(pLoc);
        pLoc = OBJ_NIL;

        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  S t r i n g
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseString (
        HJSON_DATA      *this
    )
    {
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pStrAccum = OBJ_NIL;
        SRCLOC_DATA     *pLoc = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this,"%s:\n", __func__);
        
        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);
        while (tokenClass == LEX_CONSTANT_STRING) {
            TOKEN_DATA      *pToken2;
            int32_t         token2Class;
            pToken2 = LexJ_TokenLookAhead(this->pLexJ, 2);
            TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken2));
            token2Class = Token_getClass(pToken2);
            if (token2Class == LEXJ_SEP_COLON) {
                break;
            }
            pStr = Token_ToDataString(pToken);
            if (OBJ_NIL == pLoc) {
                pLoc = Token_ToSrcLoc(pToken);
            }
            if (OBJ_NIL == pStrAccum) {
                pStrAccum = pStr;
            } else {
                AStr_Append(pStrAccum, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            LexJ_TokenAdvance(this->pLexJ, 1);
            pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
            TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
            tokenClass = Token_getClass(pToken);
        }
        if (OBJ_NIL == pStrAccum) {
            return pNode;
        }

        TRC_OBJ(
                this,
                "\tstring: (%d) \"%s\"\n",
                AStr_getLength(pStrAccum),
                AStr_getData(pStrAccum)
        );
        if (pStrAccum) {
            pNode = JsonIn_NodeFromString(pStrAccum);
            obj_Release(pStrAccum);
            pStrAccum = OBJ_NIL;
            if (pLoc) {
                Node_setExtra(pNode, pLoc);
            }
        }
        obj_Release(pLoc);
        pLoc = OBJ_NIL;

        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                   P a r s e  V a l u e
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseValue (
        HJSON_DATA      *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        TOKEN_DATA      *pToken;
        int32_t         tokenClass;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);

        pToken = LexJ_TokenLookAhead(this->pLexJ, 1);
        TRC_OBJ_EXEC(this, hjson_DisplayToken(this,pToken));
        tokenClass = Token_getClass(pToken);

#ifdef XYZZY
        switch (tokenClass) {

            case LEXJ_CONSTANT_STRING:
                pStr = Token_ToDataString(pToken);
                obj_Release(pStr);
                pStr = OBJ_NIL;
                LexJ_TokenAdvance(this->pLexJ, 1);
                break;
                
            default:
                break;
        }
#endif
        if( tokenClass == LEXJ_SEP_LBRACE ) {
            pNode = hjson_ParseHash(this);
            if (pNode) {
                return pNode;
            }
        }
        if( tokenClass == LEXJ_SEP_LBRACKET ) {
            pNode = hjson_ParseArray(this);
            return pNode;
        }
        pNode = hjson_ParseNumber(this);
        if (pNode) {
            return pNode;
        }
        pNode = hjson_ParseKeyWord(this);
        if (pNode) {
            return pNode;
        }
        pNode = hjson_ParseString(this);
        if (pNode) {
            return pNode;
        }
        
        return OBJ_NIL;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    HJSON_DATA *    hjson_Alloc (
    )
    {
        HJSON_DATA      *this;
        uint32_t        cbSize = sizeof(HJSON_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    HJSON_DATA *     hjson_New (
        void
    )
    {
        HJSON_DATA       *this;
        
        this = hjson_Alloc( );
        if (this) {
            this = hjson_Init(this);
        } 
        return this;
    }



    HJSON_DATA *    hjson_NewA (
        const
        char            *pSzStr,        // Buffer of file data
        uint16_t        tabSize         // Tab Spacing if any
    )
    {
        HJSON_DATA      *this = OBJ_NIL;
        ASTR_DATA       *pAStr = OBJ_NIL;

        pAStr = AStr_NewA(pSzStr);
        if (pAStr) {
            this = hjson_Alloc( );
            if (this) {
                this = hjson_InitAStr(this, pAStr, tabSize);
            }
            obj_Release(pAStr);
            pAStr = OBJ_NIL;
        }

        return this;
    }
    
    
    
    HJSON_DATA *    hjson_NewAStr (
        ASTR_DATA       *pAStr,        // Buffer of file data
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        HJSON_DATA      *this;
        
        this = hjson_Alloc( );
        if (this) {
            this = hjson_InitAStr(this, pAStr, tabSize);
        }
        return this;
    }
    
    
    
    HJSON_DATA *    hjson_NewFromFile (
        FILE            *pFile,         // Input File
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        HJSON_DATA      *this;
        
        this = hjson_Alloc( );
        if (this) {
            this = hjson_InitFile(this, pFile, tabSize);
        }
        return this;
    }
    
    
    
    HJSON_DATA *    hjson_NewFromPath (
        PATH_DATA       *pFilePath,     // Input File Path
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        HJSON_DATA      *this;
        
        this = hjson_Alloc( );
        if (this) {
            this = hjson_InitPath(this, pFilePath, tabSize);
        }
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    NODEHASH_DATA * hjson_getFileObject (
        HJSON_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pFileObject;
    }
    
    
    bool        hjson_setFileObject (
        HJSON_DATA      *this,
        NODEHASH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pFileObject) {
            obj_Release(this->pFileObject);
        }
        this->pFileObject = pValue;
        
        return true;
    }
    
    
    
    uint16_t        hjson_getPriority (
        HJSON_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            hjson_setPriority (
        HJSON_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    uint32_t        hjson_getSize (
        HJSON_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = hjson__Assign(this,pOther);
     @endcode
     @param     this    HJSON object pointer
     @param     pOther  a pointer to another HJSON object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         hjson_Assign (
        HJSON_DATA		*this,
        HJSON_DATA      *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !hjson_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        hjson      *pCopy = hjson_Copy(this);
     @endcode
     @param     this    HJSON object pointer
     @return       If successful, a HJSON object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the HJSON object.
     */
    HJSON_DATA *     hjson_Copy (
        HJSON_DATA       *this
    )
    {
        HJSON_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = hjson_New( );
        if (pOther) {
            eRc = hjson_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            hjson_Dealloc (
        OBJ_ID          objId
    )
    {
        HJSON_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pLexJ) {
            obj_Release(this->pLexJ);
            this->pLexJ = OBJ_NIL;
        }
        hjson_setFileObject(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         hjson_Disable (
        HJSON_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         hjson_Enable (
        HJSON_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    HJSON_DATA *    hjson_Init (
        HJSON_DATA      *this
    )
    {
        uint32_t        cbSize = sizeof(HJSON_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_HJSON);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_HJSON);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&hjson_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = ObjArray_New( );

    #ifdef NDEBUG
    #else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pFileObject);
        BREAK_NOT_BOUNDARY4(sizeof(HJSON_DATA));
    #endif

        return this;
    }

     
    HJSON_DATA *    hjson_InitAStr (
        HJSON_DATA      *this,
        ASTR_DATA       *pAStr,         // Buffer of file data
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pAStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = hjson_Init(this);
        if (OBJ_NIL == this) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pLexJ = LexJ_NewFromAStr(pAStr, tabSize, true);
        if (OBJ_NIL == this->pLexJ) {
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        return this;
    }
    
    
    HJSON_DATA *    hjson_InitFile (
        HJSON_DATA      *this,
        FILE            *pFile,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pFile) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = hjson_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->pLexJ = LexJ_NewFromFile(pFile, tabSize, true);
        if (OBJ_NIL == this->pLexJ) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }
    
    
    HJSON_DATA *    hjson_InitPath (
        HJSON_DATA      *this,
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (OBJ_NIL == pPath) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = hjson_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->pLexJ = LexJ_NewFromPath(pPath, tabSize, true);
        if (OBJ_NIL == this->pLexJ) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         hjson_IsEnabled (
        HJSON_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a r s e
    //---------------------------------------------------------------
    
    NODE_DATA *     hjson_ParseFileHash (
        HJSON_DATA		*this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pNode = hjson_ParseHash(this);
        if (SrcErrors_getNumErrors(OBJ_NIL)) {
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    NODE_DATA *     hjson_ParseFileValue (
        HJSON_DATA        *this
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        pNode = hjson_ParseValue(this);
        if (SrcErrors_getNumErrors(OBJ_NIL)) {
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        // Return to caller.
        return pNode;
    }
    
    

    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          hjson_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        HJSON_DATA      *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return hjson_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return hjson_Enable;
                        }
                        break;

                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = hjson_ToDebugString(this,4);
     @endcode
     @param     this    HJSON object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     hjson_ToDebugString (
        HJSON_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !hjson_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(hjson) size=%d\n",
                     this,
                     hjson_getSize(this)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(hjson)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            hjson_Validate (
        HJSON_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_HJSON) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(HJSON_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


