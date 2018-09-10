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
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeArray.h>
#include    <nodeHash.h>
#include    <srcErrors.h>
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
    
    

    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new UTF-8 String if successful, otherwise, NULL
     @warning   Returned UTF-8 string must be freed using mem_Free().
     */
    uint8_t *       utf8_ParseObject(
        JSONIN_DATA     *pParser,
        uint32_t        *pLength
    )
    {
        ERESULT         eRc;
        uint8_t         *pData = NULL;
        const
        OBJ_INFO        *pInfo;
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
        uint32_t        crc2 = 0;
        uint32_t        length = 0;
        int64_t         intIn = 0;
        ASTR_DATA       *pWrk = OBJ_NIL;
        W32CHR_T        ch;
        const
        char            *pSrc;
        uint8_t         *pOut;
        uint32_t        i;

        pInfo = obj_getInfo(utf8_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "crc", &intIn);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        crc = (uint32_t)intIn;
        
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "len", &intIn);
        length = (uint32_t)intIn;
        if (0 == length) {
            goto exit00;
        }
        
        pData = mem_Malloc(length + 1);
        if (NULL == pData) {
            length = 0;
            goto exit00;
        }
        
        eRc = jsonIn_FindStringNodeInHashA(pParser, "data", &pWrk);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pWrk)) {
            length = 0;
            goto exit00;
        }
        pSrc = AStr_getData(pWrk);
        pOut = pData;
        for (i=0; i<length; ++i) {
            ch = utf8_ChrConToW32_Scan(&pSrc);
            *pOut++ = ch & 0xFF;
        }
        *pOut = '\0';
        
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        if (pCrc) {
            crc2 = crc_AccumBlock(pCrc, length, pData);
            obj_Release(pCrc);
            pCrc = OBJ_NIL;
            if (crc == crc2) {
                ;
            }
            else {
                fprintf(stderr, "ERROR - CRC check failed! %u vs %u\n", crc, crc2);
                goto exit00;
            }
        }
        else {
            fprintf(stderr, "ERROR - CRC object creation failed!\n");
            goto exit00;
        }
        
        // Return to caller.
    exit00:
        if (pLength) {
            *pLength = length;
        }
        return pData;
    }
    
    
    

    
    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    uint8_t *       utf8_DataFromJSONString(
        ASTR_DATA       *pString,
        uint32_t        *pLength
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        uint8_t         *pData = NULL;

        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            if (pLength)
                *pLength = 0;
            goto exit00;
        }
        
        pData = utf8_ParseObject(pParser, pLength);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pData;
    }
    
    

    uint8_t *       utf8_DataFromJSONStringA(
        const
        char            *pString,
        uint32_t        *pLength
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        uint8_t         *pData = NULL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pData = utf8_DataFromJSONString(pStr, pLength);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pData;
    }
    
    
    
    ASTR_DATA *     utf8_DataToJSON(
        const
        char            *pData
    )
    {
        uint32_t        i;
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
        if (OBJ_NIL == pStr) {
            return pStr;
        }
        AStr_AppendPrint(pStr, "{ \"objectType\":\"%s\"", pInfo->pClassName);
        
        len = utf8_StrLenChars(pData);
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        crc = crc_AccumBlock(pCrc, len, (void *)pData);
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        
        len = (uint32_t)utf8_StrLenA(pData);
        AStr_AppendPrint(pStr, ", \"len\":%u", len);
        AStr_AppendPrint(pStr, ", \"crc\":%u", crc);

        if (len) {
            AStr_AppendA(pStr, ", \"data\":\"");
            pChr = pData;
            for (i=0; i<len; ++i) {
                chrW = utf8_Utf8ToW32_Scan(&pChr);
                utf8_W32ToChrCon(chrW, chrs);
                AStr_AppendA(pStr, chrs);
            }
            AStr_AppendA(pStr, "\" ");
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

