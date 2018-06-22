// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   node.c
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
#include    <node_internal.h>
#include    <name_internal.h>
#include    <token_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <utf8.h>




#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    NODE_DATA *     node_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        cls = 0;
        OBJ_ID          pObj = OBJ_NIL;
        //uint8_t         *pUtf8;
        SRCLOC_DATA     *pSrc = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;

        pInfo = obj_getInfo(node_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        pObj = jsonIn_SubobjectInHash(pParser, "name");
        if (pObj) {
            pName = name_ParseObject(pParser);
            jsonIn_SubobjectEnd(pParser);
            if (pName) {
                pObject = node_New( );
                obj_Release(pName);
                pName = OBJ_NIL;
            }
        }
        
        if (pObject) {
            cls  = (uint32_t)jsonIn_FindIntegerNodeInHash(pParser, "class");
            node_setClass(pObject, cls);
            
#ifdef XYZZY
            pObj = jsonIn_SubobjectInHash(pParser, "data");
            if (pObj) {
                pObj = jsonIn_ParseObject(pParser);
                jsonIn_SubobjectEnd(pParser);
                if (pObj) {
                    szData_setData(pObject, pObj);
                    obj_Release(pObj);
                    pObj = OBJ_NIL;
                }
            }
#endif
        }
        
        // Return to caller.
    exit00:
        if (pSrc) {
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        return pObject;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    NODE_DATA *     node_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
        //NODE_DATA       *pNode;
        //NODEHASH_DATA   *pHash;
        ERESULT         eRc;
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
        NODE_DATA       *pNodeOut = OBJ_NIL;
        PATH_DATA       *pPath = path_NewA("?");
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        //FIXME: Rework below
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
        return pNodeOut;
    }
    
    

    NODE_DATA *     node_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pNode = node_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    ASTR_DATA *     node_ToJSON(
        NODE_DATA       *this
    )
    {
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        //ASTR_DATA       *pWrkStr;
        ASTR_DATA *     (*pToJSON)(
            OBJ_ID          objId
        );

#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(
                     pStr,
                     "{\"objectType\":\"%s\","
                         "\"class\":\"%d\","
                         "\"type\":\"%d\","
                         "\"index\":%d,\n",
                     pInfo->pClassName,
                     this->cls,
                     this->type,
                     this->index
                     );
        AStr_AppendPrint(
                         pStr,
                         "\t\"leftIndex\":\"%s\","
                         "\"middleIndex\":\"%d\","
                         "\"parentIndex\":\"%d\","
                         "\"rightIndex\":%d,\n",
                         this->leftIndex,
                         this->middleIndex,
                         this->parentIndex,
                         this->rightIndex
                         );

        if (this->pName) {
            pWrkStr = name_ToJSON(this->pName);
            AStr_AppendA(pStr, "\"name\":");
            AStr_Append(pStr, pWrkStr);\
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        
        if (this->pData) {
            pQueryInfo = obj_getVtbl(this->pData)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pData,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJSON"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pData);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"data\":\n");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        if (this->pOther) {
            pQueryInfo = obj_getVtbl(this->pOther)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pOther,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJSON"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pOther);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"other\":\n");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        if (this->pExtra) {
            pQueryInfo = obj_getVtbl(this->pExtra)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pExtra,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJSON"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pExtra);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"extra\":\n");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        if (this->pProperties) {
            pQueryInfo = obj_getVtbl(this->pProperties)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pProperties,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJSON"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pProperties);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"properties\":\n");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

