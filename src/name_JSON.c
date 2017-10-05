// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   name_JSON.c
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
#include    "name_internal.h"
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
    

    NAME_DATA *     name_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        HJSON_DATA      *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
        //NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
        //ERESULT         eRc;
        const
        char            *pFileName = "";
#ifdef XYZZY
        uint32_t        lineNo = 0;
        uint16_t        colNo = 0;
        int32_t         cls = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pType = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
#endif
        NAME_DATA       *pNameOut = OBJ_NIL;
        PATH_DATA       *pPath = path_NewA("?");
        
        pParser = hjson_NewAStr(pString, 4);
        if (OBJ_NIL == pParser) {
            goto exit00;
        }
        pFileNode = hjson_ParseFile(pParser);
        if (OBJ_NIL == pFileNode) {
            goto exit00;
        }
        pHash = node_getData(pFileNode);
        if (OBJ_NIL == pFileNode) {
            goto exit00;
        }
        //fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));

#ifdef XYZZY
        eRc = nodeHash_FindA(pHash, "fileName", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string")) {
                pStr = node_getData(pNode);
                pFileName = AStr_CStringA(pStr,NULL);
            }
            else {
                fprintf(stderr, "ERROR - fileName should have a string!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "lineNo", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                lineNo = AStr_ToInt64(pStr) & 0xFFFFFFFF;
            }
            else {
                fprintf(stderr, "ERROR - lineNo should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "colNo", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                colNo = AStr_ToInt64(pStr) & 0xFFFF;
            }
            else {
                fprintf(stderr, "ERROR - colNo should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "cls", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                cls = (int32_t)AStr_ToInt64(pStr);
            }
            else {
                fprintf(stderr, "ERROR - cls should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "type", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string")) {
                pType = node_getData(pNode);
            }
            else {
                fprintf(stderr, "ERROR - type should have a string!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        if (OBJ_NIL == pType) {
            mem_Free((void *)pFileName);
            obj_Release(pFileNode);
            obj_Release(pParser);
            return OBJ_NIL;
        }
        pStr = OBJ_NIL;
        eRc = nodeHash_FindA(pHash, "data", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
        }
        if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pType, "CHAR")) {
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                pToken =    token_NewCharW(
                                           pFileName,
                                           lineNo,
                                           colNo,
                                           cls,
                                           (int32_t)AStr_ToInt64(pStr)
                                           );
            }
            else {
                fprintf(stderr, "ERROR - CHAR should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
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
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
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
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
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
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - Token Type is not implemented!\n");
            fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
            DEBUG_BREAK();
            goto exit00;
        }
#endif
        
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
        return pNameOut;
    }
    
    

    NAME_DATA *     name_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pName = name_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pName;
    }
    
    
    
    ASTR_DATA *     name_ToJSON(
        NAME_DATA       *this
    )
    {
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !name_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr == OBJ_NIL) {
            //obj_Release(pWrkStr);
            return OBJ_NIL;
        }
        AStr_AppendA(pStr, "{\"objectType\":\"");
        AStr_AppendA(pStr, pInfo->pClassName);
        AStr_AppendA(pStr, "\", \"data\":\"");
        //FIXME: AStr_Append(pStr, pWrkStr);
        AStr_AppendA(pStr, "\"}\n");
        //FIXME: obj_Release(pWrkStr);
        
#ifdef XYZZY
        switch (this->type) {
                
            case NAME_TYPE_UNKNOWN:
                AStr_AppendA(pStr, "\"type\":\"NAME_TYPE_UNKNOWN\"");
                break;
                
            case NAME_TYPE_INTEGER:
                j = snprintf(
                             str,
                             sizeof(str),
                             "\"type\":\"NAME_TYPE_INTEGER\",\"data\":%lld",
                             this->integer
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case NAME_TYPE_WSTR:
                AStr_AppendA(pStr, "\"type\":\"NAME_TYPE_WSTR\",\"data\":\"");
                AStr_AppendA(pStr, str);
                AStr_AppendA(pStr, "\" ");
                break;
                
            case NAME_TYPE_UTF8:
#ifdef XYZZY
                AStr_AppendA(pStr, "\"type\":\"STRING\",\"data\":\"");
                if (OBJ_IDENT_WSTR == obj_getType(this->pObj)) {
                    pWStr = WStr_getData(this->pObj);
                }
                if (OBJ_IDENT_WSTRC == obj_getType(this->pObj)) {
                    pWStr = WStrC_getData(this->pObj);
                }
                len = utf8_StrLenW(pWStr);
                for (j=0; j<len; ++j) {
                    if (*pWStr == '"') {
                        AStr_AppendA(pStr, "\\");
                    }
                    lenChars = utf8_WCToUtf8(*pWStr, str2);
                    if (lenChars) {
                        AStr_AppendA(pStr, str2);
                    }
                    ++pWStr;
                }
                AStr_AppendA(pStr, "\" ");
#endif
                break;
                
            case NAME_TYPE_UTF8_CON:
                AStr_AppendA(pStr, "\"type\":\"NAME_TYPE_UTF8\", \"data\":\"");
                AStr_AppendA(pStr, str);
                break;
                
        }
#endif
        AStr_AppendA(pStr, "\"}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

