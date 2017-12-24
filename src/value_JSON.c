// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   value.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on August 27, 2017
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
#include    <value_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dec_internal.h>
#include    <hex_internal.h>
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <utf8_internal.h>




#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new null object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    VALUE_DATA *    value_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        VALUE_DATA      *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        crc = 0;
        uint32_t        length = 0;
        uint32_t        i;
        W32CHR_T        ch;
        const
        char            *pSrc;
        ASTR_DATA       *pWrk;
        
        pInfo = obj_getInfo(AStr_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        crc = (uint32_t)jsonIn_FindIntegerNodeInHash(pParser, "crc");
        
        length = (uint32_t)jsonIn_FindIntegerNodeInHash(pParser, "len");
        
        pObject = value_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
#ifdef XYZZY
        if (length && pObject) {
            pWrk = jsonIn_FindStringNodeInHash(pParser, "data");
            pSrc = AStr_getData(pWrk);
            for (i=0; i<length; ++i) {
                ch = utf8_ChrConToW32_Scan(&pSrc);
                AStr_AppendW32(pObject, 1, &ch);
            }
            if (!(crc == AStr_getCrcIEEE(pObject))) {
                obj_Release(pObject);
                pObject = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
    exit00:
        return pObject;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    VALUE_DATA *    value_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
        //NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
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
        VALUE_DATA      *pValueOut = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        
        pInfo = value_Vtbl.iVtbl.pInfo;
        
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
        return pValueOut;
    }
    
    

    VALUE_DATA *    value_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        VALUE_DATA      *pValue = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pValue = value_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pValue;
    }
    
    
    
    ASTR_DATA *     value_ToJSON(
        VALUE_DATA      *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ASTR_DATA       *pWrk;
        //char            *pChr;
        //char            chrs[12];
        ASTR_DATA *     (*pToJSON)(OBJ_ID);
        OBJ_IUNKNOWN    *pVtbl;
        
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr, "{\"objectType\":\"%s\"", pInfo->pClassName);
        
        switch (this->type) {
                
            case VALUE_TYPE_INT16:
                AStr_AppendPrint(pStr, ", \"type\":\"VALUE_TYPE_INT16\", \"data\":%d", this->value.i16);
                break;
                
            case VALUE_TYPE_INT32:
                AStr_AppendPrint(pStr, ", \"type\":\"VALUE_TYPE_INT32\", \"data\":%d", this->value.i32);
                break;
                
            case VALUE_TYPE_INT64:
                AStr_AppendPrint(pStr, ", \"type\":\"VALUE_TYPE_INT64\", \"data\":%d", this->value.i64);
                break;
                
            case VALUE_TYPE_UINT16:
                AStr_AppendPrint(pStr, ", \"type\":\"VALUE_TYPE_UINT16\", \"data\":%d", this->value.u16);
                break;
                
            case VALUE_TYPE_UINT32:
                AStr_AppendPrint(pStr, ", \"type\":\"VALUE_TYPE_UINT32\", \"data\":%d", this->value.u32);
                break;
                
            case VALUE_TYPE_UINT64:
                AStr_AppendPrint(pStr, ", \"type\":\"VALUE_TYPE_UINT64\", \"data\":%d", this->value.u64);
                break;
                
            case VALUE_TYPE_OBJECT:
                AStr_AppendA(pStr, ", \"type\":\"VALUE_TYPE_OBJECT\", \"data\":");
                if (this->value.pObject) {
                    pVtbl = obj_getVtbl(this->value.pObject);
                    if (pVtbl) {
                        pToJSON =   pVtbl->pQueryInfo(
                                                    this->value.pObject,
                                                    OBJ_QUERYINFO_TYPE_METHOD,
                                                    "ToJSON"
                                    );
                        if (pToJSON) {
                            pWrk = (*pToJSON)(this->value.pObject);
                            if (pWrk) {
                                AStr_Append(pStr, pWrk);
                                obj_Release(pWrk);
                                pWrk = OBJ_NIL;
                            }
                        }
                    }
                }
                else {
                    AStr_AppendA(pStr, "null");
                }
                break;
                
            case VALUE_TYPE_DATA:
            case VALUE_TYPE_DATA_FREE:
                AStr_AppendA(pStr, ", \"type\":\"VALUE_TYPE_DATA_FREE\", \"data\":");
                pWrk = hex_DataToJSON(this->value.data.length, this->value.data.pData);
                AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
                break;
                
            default:
                obj_Release(pStr);
                pStr = OBJ_NIL;
        }
        
        if (pStr)
            AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

