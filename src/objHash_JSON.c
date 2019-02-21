// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objHash_JSON.c
 *
 * Created on 12/19/2017 from W32Str_JSON
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
#include    <objHash_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <crc.h>
#include    <dec.h>
#include    <hex.h>
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeArray.h>
#include    <nodeHash.h>
#include    <utf8.h>

//#define TRACE_FUNCTIONS 1


#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    void            objHash_Int64ToChrClean(
        int64_t         num,
        char            *pBuffer
    )
    {
        char            data[32];
        int             i;
        
        dec_Int64ToChr(num, data);
        
        // Now output string without leading zeroes.
        *pBuffer++ = data[0];       // Sign
        for (i=1; i<21; ++i) {
            if (data[i] && (data[i] == '0')) {
            }
            else {
                break;
            }
        }
        for (; i<22; ++i) {
            if (data[i]) {
                *pBuffer++ = data[i];
            }
        }
        *pBuffer++ = '\0';
    }
    

    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    ERESULT         objHash_NewFromJSONString(
        ASTR_DATA       *pString,
        W32STR_DATA     **ppData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        JSONIN_DATA     *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
#ifdef XYZZY
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
        NODEARRAY_DATA  *pArray;
        const
        OBJ_INFO        *pInfo = objHash_Vtbl.iVtbl.pInfo;
        uint32_t        i = 0;
#endif
        ASTR_DATA       *pStr = OBJ_NIL;
#ifdef TRACE_FUNCTIONS
        ASTR_DATA       *pStr2 = OBJ_NIL;
#endif
#ifdef XYZZY
        NAME_DATA       *pName = OBJ_NIL;
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc;
        uint32_t        chkCrc;
        uint32_t        length = 0;
        //char            *pData = NULL;
        //char            *pChrOut;
        int32_t         chrW;
        W32STR_DATA     *pStrOut = OBJ_NIL;
#endif

        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        //FIXME: Rework below
#ifdef XYZZY
        eRc = nodeHash_FindA(pHash, "objectType", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string")) {
                pStr = node_getData(pNode);
                if (0 == strcmp(pInfo->pClassName, AStr_getData(pStr))) {
                }
                else {
                    fprintf(stderr,
                            "ERROR - objectType is \"%s\", but need \"%s\"!\n",
                            AStr_getData(pStr),
                            pInfo->pClassName
                            );
#ifdef TRACE_FUNCTIONS
                    pStr2 = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr2));
                    obj_Release(pStr2);
                    pStr2 = OBJ_NIL;
                    DEBUG_BREAK();
#endif
                    eRc = ERESULT_GENERAL_FAILURE;
                    goto exit00;
                }
            
            }
            else {
                fprintf(stderr,
                        "ERROR - objectType needs to be a \"string\"!\n"
                );
#ifdef TRACE_FUNCTIONS
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
#endif
                eRc = ERESULT_GENERAL_FAILURE;
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - objectType is missing!\n");
#ifdef TRACE_FUNCTIONS
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
            DEBUG_BREAK();
#endif
            eRc = ERESULT_GENERAL_FAILURE;
            goto exit00;
        }
        
        eRc = nodeHash_FindA(pHash, "crc", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                crc = (uint32_t)dec_getInt64A(AStr_getData(pStr));
            }
            else {
                fprintf(stderr, "ERROR - crc should have a integer!\n");
#ifdef TRACE_FUNCTIONS
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
#endif
                eRc = ERESULT_GENERAL_FAILURE;
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - crc is missing!\n");
#ifdef TRACE_FUNCTIONS
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
            DEBUG_BREAK();
#endif
            eRc = ERESULT_GENERAL_FAILURE;
            goto exit00;
        }
        
        eRc = nodeHash_FindA(pHash, "len", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                length = (uint32_t)dec_getInt64A(AStr_getData(pStr));
            }
            else {
                fprintf(stderr, "ERROR - length should be an integer!\n");
#ifdef TRACE_FUNCTIONS
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
#endif
                eRc = ERESULT_GENERAL_FAILURE;
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - length is missing!\n");
#ifdef TRACE_FUNCTIONS
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
            DEBUG_BREAK();
#endif
            eRc = ERESULT_GENERAL_FAILURE;
            goto exit00;
        }
        
        eRc = nodeHash_FindA(pHash, "data", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "array")) {
                pArray = node_getData(pNode);
                if (!(nodeArray_getSize(pArray) == length)) {
                    fprintf(stderr, "ERROR - length does not match array size!\n");
#ifdef TRACE_FUNCTIONS
                    pStr2 = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr2));
                    obj_Release(pStr2);
                    pStr2 = OBJ_NIL;
                    DEBUG_BREAK();
#endif
                    eRc = ERESULT_BAD_LENGTH;
                    goto exit00;
                }
                // Parse the data array creating the UTF-8 string.
                //FIXME: pStrOut = W32Str_New();
                for (i=0; i<length; ++i) {
                    pNode = nodeArray_Get(pArray, i+1);
                    pName = node_getName(pNode);
                    pStr = node_getData(pNode);
                    if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer"))) {
                        fprintf(stderr, "ERROR - data contains invalud data!\n");
#ifdef TRACE_FUNCTIONS
                        pStr2 = nodeHash_ToDebugString(pHash, 0);
                        fprintf(stderr, "%s\n", AStr_getData(pStr2));
                        obj_Release(pStr2);
                        pStr2 = OBJ_NIL;
                        DEBUG_BREAK();
#endif
                        eRc = ERESULT_GENERAL_FAILURE;
                        goto exit00;
                    }
                    chrW = (int32_t)dec_getInt64A(AStr_getData(pStr));
                    //FIXME: W32Str_AppendCharW32(pStrOut, 1, chrW);
                }
            }
            else if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "null")) {
                //FIXME: pStrOut = W32Str_New();
            }
            else {
                fprintf(stderr, "ERROR - data should be an array!\n");
#ifdef TRACE_FUNCTIONS
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
#endif
                eRc = ERESULT_GENERAL_FAILURE;
                goto exit00;
            }
            // Now verify the crc.
            pCrc = crc_New(CRC_TYPE_IEEE_32);
            //FIXME: chkCrc = W32Str_getCrcIEEE(pStrOut);
            obj_Release(pCrc);
            pCrc = OBJ_NIL;
#ifdef XYZZY
            if (chkCrc == crc)
                ;
            else {
                fprintf(stderr, "ERROR - crc does not check against data!\n");
#ifdef TRACE_FUNCTIONS
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
#endif
                eRc = ERESULT_BAD_CRC;
                goto exit00;
            }
#endif
        }
        else {
            fprintf(stderr, "ERROR - data is missing!\n");
#ifdef TRACE_FUNCTIONS
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
            DEBUG_BREAK();
#endif
            eRc = ERESULT_GENERAL_FAILURE;
            goto exit00;
        }
#endif
        
        // Return to caller.
    exit00:
        if (pStr) {
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        if (pFileNode) {
            obj_Release(pFileNode);
            pFileNode = OBJ_NIL;
        }
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
#ifdef XYZZY
        if (ppData) {
            *ppData = pStrOut;
        }
        else {
            obj_Release(pStrOut);
            pStrOut = NULL;
        }
#endif
        return eRc;
    }
    
    

    ERESULT         objHash_NewFromJSONStringA(
        const
        char            *pString,
        W32STR_DATA     **ppData
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        ERESULT         eRc = ERESULT_FAILURE;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            eRc = objHash_NewFromJSONString(pStr, ppData);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    ASTR_DATA *     objHash_ToJSON(
        OBJHASH_DATA    *this
    )
    {
        uint32_t        j;
        bool            fRc;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ASTR_DATA       *pData;
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
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
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pInfo = objHash_Vtbl.iVtbl.pInfo;

        // Scan the Hash Table insuring that all entries have
        // an "ToJSON" method.
        fRc = true;
        pList = blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            OBJHASH_RECORD      *pRecord = (OBJHASH_RECORD *)pEntry->data;
            RBT_NODE            *pNode = &pRecord->node;
            
            //FIXME: pQueryInfo = obj_getVtbl(pNode->pData)->pQueryInfo;
#ifdef XYZZY
            if (pQueryInfo) {
                pToJSON = (*pQueryInfo)(
                                        pNode->pData,
                                        OBJ_QUERYINFO_TYPE_METHOD,
                                        "ToJSON"
                                        );
                if (NULL == pToJSON) {
                    fRc = false;
                    break;
                }
            }
            else {
                fRc = false;
                break;
            }
#endif

            pEntry = listdl_Next(pList, pEntry);
        }
        
        if (fRc) {
            pList = blocks_getList((BLOCKS_DATA *)this);
            pEntry = listdl_Head(pList);
            while (pEntry) {
                OBJHASH_RECORD      *pRecord = (OBJHASH_RECORD *)pEntry->data;
                RBT_NODE            *pNode = &pRecord->node;
                
#ifdef XYZZY
                pQueryInfo = obj_getVtbl(pNode->pData)->pQueryInfo;
                if (pQueryInfo) {
                    pToJSON = (*pQueryInfo)(
                                            pNode->pData,
                                            OBJ_QUERYINFO_TYPE_METHOD,
                                            "ToJSON"
                                            );
                    if (NULL == pToJSON) {
                        fRc = false;
                        break;
                    }
                }
                else {
                    fRc = false;
                    break;
                }
#endif
                
                pEntry = listdl_Next(pList, pEntry);
            }
        }
        if (!fRc) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendPrint(
                         pStr,
                         "{\"objectType\":\"%s\",\n\t\"count\":%d,\n\t\"entries:[\n",
                         pInfo->pClassName,
                         this->size
        );
        
        // Scan the Hash Table creating entries for each of the objects
        // in the table and appending them to the array.
        j = this->size;
        pList = blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            OBJHASH_RECORD      *pRecord = (OBJHASH_RECORD *)pEntry->data;
            RBT_NODE            *pNode = &pRecord->node;
            
#ifdef XYZZY
            pQueryInfo = obj_getVtbl(pNode->pData)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON = (*pQueryInfo)(
                                        pNode->pData,
                                        OBJ_QUERYINFO_TYPE_METHOD,
                                        "ToJSON"
                                        );
                if (pToJSON) {
                    pData = (*pToJSON)(pNode->pData);
                    if (pData) {
                        AStr_Append(pStr, pData);
                        obj_Release(pData);
                        pData = OBJ_NIL;
                        if (j-- > 1) {
                            AStr_AppendA(pStr, ",\n");
                        }
                        else {
                            AStr_AppendA(pStr, "\n");
                        }
                    }
                }
            }
#endif
            
            pEntry = listdl_Next(pList, pEntry);
        }
        AStr_AppendA(pStr, "]\n\n\n");

        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

