// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   utf8DataFromJSON.c
 *
 * Created on 10/9/2017 from hexData_JSON
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
#include    <utf8_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <crc.h>
#include    <dec.h>
#include    <hex.h>
#include    <hjson.h>
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
    
    void            utf8_Int64ToChrClean(
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
    

    ERESULT         utf8_DataFromJSONString(
        ASTR_DATA       *pString,
        uint32_t        *pLength,
        void            **ppData
    )
    {
        HJSON_DATA      *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
        NODEARRAY_DATA  *pArray;
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        OBJ_INFO        *pInfo = utf8_Vtbl.iVtbl.pInfo;
        uint32_t        i = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
#ifdef TRACE_FUNCTIONS
        ASTR_DATA       *pStr2 = OBJ_NIL;
#endif
        NAME_DATA       *pName = OBJ_NIL;
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc;
        uint32_t        chkCrc;
        uint32_t        length = 0;
        uint32_t        dataSize = 0;
        char            *pData = NULL;
        char            *pChrOut;
        W32CHR_T        chrW;
        
        pParser = hjson_NewAStr(pString, 4);
        if (OBJ_NIL == pParser) {
            eRc = ERESULT_GENERAL_FAILURE;
            goto exit00;
        }
        pFileNode = hjson_ParseFile(pParser);
        if (OBJ_NIL == pFileNode) {
            eRc = ERESULT_GENERAL_FAILURE;
            goto exit00;
        }
        pHash = node_getData(pFileNode);
        if (OBJ_NIL == pFileNode) {
            eRc = ERESULT_GENERAL_FAILURE;
            goto exit00;
        }
#ifdef NDEBUG
#else
#ifdef TRACE_FUNCTIONS
        {
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
        }
#endif
#endif

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
                crc = dec_getUint32A(AStr_getData(pStr));
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
            if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "array"))) {
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
            // Get an area large enough to hold the max size UTF-8 chars
            // given the length plus a byte for the trailing NUL.
            dataSize = (length * 6) + 1;
            pData = mem_Malloc(dataSize);
            if (pData == NULL) {
                fprintf(stderr, "ERROR - Out of Memory!\n");
                DEBUG_BREAK();
                eRc = ERESULT_OUT_OF_MEMORY;
                goto exit00;
            }
            // Parse the data array creating the UTF-8 string.
            pChrOut = pData;
            dataSize = 0;
            for (i=0; i<length; ++i) {
                int             len;
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
                len = utf8_W32ToUtf8(chrW, pChrOut);
                pChrOut += len;
                dataSize += len;
            }
            *pChrOut = '\0';
            // Now verify the crc.
            pCrc = crc_New(CRC_TYPE_IEEE_32);
            chkCrc = crc_AccumBlock(pCrc, dataSize, (void *)pData);
            obj_Release(pCrc);
            pCrc = OBJ_NIL;
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
        if (pLength)
            *pLength = length;
        if (ppData) {
            *ppData = pData;
        }
        else {
            mem_Free(pData);
            pData = NULL;
        }
        return eRc;
    }
    
    

    ERESULT         utf8_DataFromJSONStringA(
        const
        char            *pString,
        uint32_t        *pLength,
        void            **ppData
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        ERESULT         eRc = ERESULT_FAILURE;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            eRc = utf8_DataFromJSONString(pStr, pLength, ppData);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    ASTR_DATA *     utf8_DataToJSON(
        const
        char            *pData
    )
    {
        char            str[256];
        uint32_t        i;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        //ASTR_DATA       *pWrk;
        const
        char            *pChr;
        char            chrs[32];
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
        W32CHR_T        chrW;
        uint32_t        len;
        
        if (NULL == pData) {
            return OBJ_NIL;
        }
        pInfo = utf8_Vtbl.iVtbl.pInfo;
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        len = utf8_StrLenChars(pData);
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        crc = crc_AccumBlock(pCrc, len, (void *)pData);
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        AStr_AppendPrint(pStr, ", \"crc\":%u", crc);
        
        len = (uint32_t)utf8_StrLenA(pData);
        AStr_AppendPrint(pStr, ", \"len\":%u", len);
        if (len) {
            AStr_AppendA(pStr, ", \"data\":[");
            pChr = pData;
            for (i=0; i<(len-1); ++i) {
                chrW = utf8_Utf8ToW32_Scan(&pChr);
                utf8_Int64ToChrClean(chrW, chrs);
                AStr_AppendA(pStr, chrs);
                AStr_AppendA(pStr, ",");
            }
            chrW = utf8_Utf8ToW32_Scan(&pChr);
            utf8_Int64ToChrClean(chrW, chrs);
            AStr_AppendA(pStr, chrs);
            AStr_AppendA(pStr, "] ");
        }
        else {
            AStr_AppendA(pStr, ", \"data\":null ");
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

