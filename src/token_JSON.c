// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   token.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on December 30, 2014
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
#include    "token_internal.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    "hjson.h"
#include    "node.h"
#include    "nodeHash.h"
#include    "utf8.h"




#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    TOKEN_DATA *     token_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        HJSON_DATA      *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
        ERESULT         eRc;
        const
        char            *pFileName = NULL;
        uint32_t        lineNo = 0;
        uint16_t        colNo = 0;
        int32_t         cls = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pType = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
        TOKEN_DATA      *pToken = OBJ_NIL;
        PATH_DATA       *pPath = path_NewA("?");
        
        pParser = hjson_NewAStr(pString, 4);
        if (OBJ_NIL == pParser) {
            goto exit00;
        }
        //obj_TraceSet(pParser, true);
        pFileNode = hjson_ParseFile(pParser);
        if (OBJ_NIL == pFileNode) {
            goto exit00;
        }
        pHash = node_getData(pFileNode);
        if (OBJ_NIL == pFileNode) {
            goto exit00;
        }
        {
            ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr));
            obj_Release(pStr);
        }
        
        eRc = nodeHash_FindA(pHash, "FileName", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string")) {
                pStr = node_getData(pNode);
                pFileName = AStr_CStringA(pStr, NULL);
            }
            else {
                fprintf(stderr, "ERROR - fileName should have a string!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "LineNo", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                lineNo = AStr_ToInt64(pStr) & 0xFFFFFFFF;
            }
            else {
                fprintf(stderr, "ERROR - lineNo should have a integer!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "ColNo", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                colNo = AStr_ToInt64(pStr) & 0xFFFF;
            }
            else {
                fprintf(stderr, "ERROR - colNo should have a integer!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "Class", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                cls = (int32_t)AStr_ToInt64(pStr);
            }
            else {
                fprintf(stderr, "ERROR - class should have a integer!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "Type", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string")) {
                pType = node_getData(pNode);
            }
            else {
                fprintf(stderr, "ERROR - type should have a string!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        if (OBJ_NIL == pType) {
            if (pFileName) {
                mem_Free((void *)pFileName);
            }
            obj_Release(pFileNode);
            obj_Release(pParser);
            return OBJ_NIL;
        }
        pStr = OBJ_NIL;
        eRc = nodeHash_FindA(pHash, "Data", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
        }
        if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pType, "CHAR")) {
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                pToken =    token_NewCharW32(
                                           pFileName,
                                           lineNo,
                                           colNo,
                                           cls,
                                           (int32_t)AStr_ToInt64(pStr)
                                           );
            }
            else {
                fprintf(stderr, "ERROR - CHAR should have a integer!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pType, "NUMBER")) {
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                pToken =    token_NewInteger(
                                             pFileName,
                                             lineNo,
                                             colNo,
                                             cls,
                                             AStr_ToInt64(pStr)
                                             );
            }
            //TODO: Add float support!
            else {
                fprintf(stderr, "ERROR - NUMBER should have a integer or float!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pType, "STRING")) {
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string")) {
                pStr = node_getData(pNode);
                WSTR_DATA   *pWStr = AStr_ToWStr(pStr);
                pToken =    token_NewStringW(
                                             pFileName,
                                             lineNo,
                                             colNo,
                                             cls,
                                             pWStr
                                             );
                obj_Release(pWStr);
           }
            else {
                fprintf(stderr, "ERROR - STRING should have a string!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pType, "STRTOKEN")) {
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "number")) {
                pStr = node_getData(pNode);
                pToken =    token_NewStrToken(
                                              pFileName,
                                              lineNo,
                                              colNo,
                                              cls,
                                              (uint32_t)AStr_ToInt64(pStr)
                                              );
            }
            else {
                fprintf(stderr, "ERROR - STRTOKEN should have a number!\n");
                {
                    ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr));
                    obj_Release(pStr);
                }
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - Token Type is not implemented!\n");
            {
                ASTR_DATA       *pStr = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr));
                obj_Release(pStr);
            }
            DEBUG_BREAK();
            goto exit00;
        }
        
        // Return to caller.
    exit00:
        if (pFileName) {
            mem_Free((void *)pFileName);
            pFileName = NULL;
        }
        if (pFileNode) {
            obj_Release(pFileNode);
            pFileNode = OBJ_NIL;
        }
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        return pToken;
    }
    
    

    TOKEN_DATA *     token_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA      *pToken = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pToken = token_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pToken;
    }
    
    
    
    ASTR_DATA *     token_ToJSON(
        TOKEN_DATA      *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        char            str2[256];
        uint32_t        len;
        uint32_t        lenChars;
        const
        W32CHR_T        *pWStr = NULL;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\",\"FileName\":\"%s\",\"LineNo\":%d,\"ColNo\":%d,\"Class\":%d,",
                     pInfo->pClassName,
                     (token_getFileName(this) ? token_getFileName(this) : ""),
                     token_getLineNo(this),
                     token_getColNo(this),
                     this->data.cls
                     );
        AStr_AppendA(pStr, str);
        
        switch (this->data.type) {
                
            case TOKEN_TYPE_UNKNOWN:
                AStr_AppendA(pStr, "\"Type\":\"UNKNOWN\"");
                break;
                
            case TOKEN_TYPE_WCHAR:
                j = snprintf(
                             str,
                             sizeof(str),
                             "\"Type\":\"CHAR\",\"Data\":%d",
                             this->data.wchr[0]
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_WSTRING:
                AStr_AppendA(pStr, "\"Type\":\"STRING\",\"Data\":\"");
                if (OBJ_IDENT_WSTR == obj_getType(this->data.pObj)) {
                    pWStr = WStr_getData(this->data.pObj);
                }
                if (OBJ_IDENT_W32STRC == obj_getType(this->data.pObj)) {
                    pWStr = W32StrC_getData(this->data.pObj);
                }
                len = utf8_StrLenW32(pWStr);
                for (j=0; j<len; ++j) {
                    if (*pWStr == '"') {
                        AStr_AppendA(pStr, "\\");
                    }
                    lenChars = utf8_W32ToUtf8(*pWStr, str2);
                    if (lenChars) {
                        AStr_AppendA(pStr, str2);
                    }
                    ++pWStr;
                }
                AStr_AppendA(pStr, "\"");
                break;
                
            case TOKEN_TYPE_INTEGER:
                j = snprintf(
                             str,
                             sizeof(str),
                             "\"Type\":\"NUMBER\",\"Data\":%lld",
                             this->data.integer
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                j = snprintf(
                             str,
                             sizeof(str),
                             "\"Type\":\"STRTOKEN\",\"Data\":%lld",
                             this->data.integer
                             );
                AStr_AppendA(pStr, str);
                break;
                
            default:
                DEBUG_BREAK();
                AStr_AppendA(pStr, "\"Type\":\"UNKNOWN\"");
                break;
                
        }
        AStr_AppendA(pStr, "}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

