// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   hexDataFromJSON.c
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
#include    <hex_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <crc.h>
#include    <dec.h>
#include    <hjson.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <utf8.h>




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
    

    ERESULT         hex_DataFromJSONString(
        ASTR_DATA       *pString,
        uint32_t        *pLength,
        void            **ppData
    )
    {
        HJSON_DATA      *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pStr2 = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc;
        uint32_t        chkCrc;
        uint32_t        length = 0;
        uint8_t         *pData = NULL;
        
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
#ifdef NDEBUG
#else
        pStr2 = nodeHash_ToDebugString(pHash, 0);
        fprintf(stderr, "%s\n", AStr_getData(pStr2));
        obj_Release(pStr2);
        pStr2 = OBJ_NIL;
#endif

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
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - crc is missing!\n");
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
            DEBUG_BREAK();
            goto exit00;
        }
        
        eRc = nodeHash_FindA(pHash, "len", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                length = (uint32_t)dec_getInt64A(AStr_getData(pStr));
                if (length == 0) {
                    fprintf(stderr, "ERROR - length must be greater than zero!\n");
                    pStr2 = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr2));
                    obj_Release(pStr2);
                    pStr2 = OBJ_NIL;
                    DEBUG_BREAK();
                    goto exit00;
                }
            }
            else {
                fprintf(stderr, "ERROR - length should have a integer!\n");
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - length is missing!\n");
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
            DEBUG_BREAK();
            goto exit00;
        }
        
        eRc = nodeHash_FindA(pHash, "data", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string")) {
                pStr = node_getData(pNode);
                if (AStr_getLength(pStr) == 2 * length) {
                    pData = mem_Malloc(length);
                    if (pData == NULL) {
                        fprintf(stderr, "ERROR - Out of Memory!\n");
                        DEBUG_BREAK();
                        goto exit00;
                    }
                    for (i=0; i<length; ++i) {
                        int         high;
                        int         low;
                        high = hex_DigitToIntA(AStr_CharGetW(pStr, (2*i)+1));
                        low  = hex_DigitToIntA(AStr_CharGetW(pStr, (2*i)+2));
                        if ((high == -1) || (low == -1)) {
                            fprintf(stderr, "ERROR - data contains invalud data!\n");
                            pStr2 = nodeHash_ToDebugString(pHash, 0);
                            fprintf(stderr, "%s\n", AStr_getData(pStr2));
                            obj_Release(pStr2);
                            pStr2 = OBJ_NIL;
                            DEBUG_BREAK();
                            goto exit00;
                        }
                        pData[i] = (high << 4) | low;
                    }
                    pCrc = crc_New(CRC_TYPE_IEEE_32);
                    chkCrc = crc_AccumBlock(pCrc, length, pData);
                    obj_Release(pCrc);
                    pCrc = OBJ_NIL;
                    if (chkCrc == crc)
                        ;
                    else {
                        fprintf(stderr, "ERROR - crc does not match!\n");
                        pStr2 = nodeHash_ToDebugString(pHash, 0);
                        fprintf(stderr, "%s\n", AStr_getData(pStr2));
                        obj_Release(pStr2);
                        pStr2 = OBJ_NIL;
                        DEBUG_BREAK();
                        goto exit00;
                    }
                }
                else {
                    fprintf(stderr, "ERROR - data size is wrong!\n");
                    pStr2 = nodeHash_ToDebugString(pHash, 0);
                    fprintf(stderr, "%s\n", AStr_getData(pStr2));
                    obj_Release(pStr2);
                    pStr2 = OBJ_NIL;
                    DEBUG_BREAK();
                    goto exit00;
                }
            }
            else {
                fprintf(stderr, "ERROR - data should have a string!\n");
                pStr2 = nodeHash_ToDebugString(pHash, 0);
                fprintf(stderr, "%s\n", AStr_getData(pStr2));
                obj_Release(pStr2);
                pStr2 = OBJ_NIL;
                DEBUG_BREAK();
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - data is missing!\n");
            pStr2 = nodeHash_ToDebugString(pHash, 0);
            fprintf(stderr, "%s\n", AStr_getData(pStr2));
            obj_Release(pStr2);
            pStr2 = OBJ_NIL;
            DEBUG_BREAK();
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
    
    

    ERESULT         hex_DataFromJSONStringA(
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
            eRc = hex_DataFromJSONString(pStr, pLength, ppData);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    ASTR_DATA *     hex_DataToJSON(
        uint32_t        length,
        void            *pData
    )
    {
        char            str[256];
        uint32_t        i;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        //ASTR_DATA       *pWrk;
        char            *pChr;
        char            chrs[12];
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc;
        
        pInfo = hex_Vtbl.iVtbl.pInfo;
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendPrint(pStr, ", \"len\":%d", length);
        
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        crc = crc_AccumBlock(pCrc, length, pData);
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        AStr_AppendPrint(pStr, ", \"crc\":%d", crc);
        
        AStr_AppendA(pStr, ", \"data\":\"");
        pChr = pData;
        for (i=0; i<length; ++i) {
            chrs[0] = hex_DigitToChrA((*pChr >> 4) & 0x0F);
            chrs[1] = hex_DigitToChrA(*pChr & 0x0F);
            chrs[2] = '\0';
            ++pChr;
            AStr_AppendA(pStr, chrs);
        }
        AStr_AppendA(pStr, "\"");
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif
