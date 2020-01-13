// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   hex_JSON.c
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
#include    <JsonIn.h>
#include    <Node.h>
#include    <NodeHash.h>
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
     @return    a new null object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    uint8_t *       hex_ParseObject(
        JSONIN_DATA     *pParser,
        uint32_t        *pLength
    )
    {
        ERESULT         eRc;
        const
        OBJ_INFO        *pInfo;
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
        uint32_t        crc2 = 0;
        uint32_t        length = 0;
        ASTR_DATA       *pWrk = OBJ_NIL;
        uint8_t         *pData = NULL;
        const
        char            *pChr;
        W32CHR_T        ch;
        uint32_t        i;
        uint8_t         *pOut;
        int64_t         intIn;

        pInfo = obj_getInfo(hex_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "crc", &intIn);
        crc = (uint32_t)intIn;

        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "len", &intIn);
        length = (uint32_t)intIn;

        if (length) {
            pData = mem_Malloc(length);
            if (NULL == pData) {
                fprintf(stderr, "ERROR - Out of Memory!\n");
                goto exit00;
            }
            eRc = JsonIn_FindStringNodeInHashA(pParser, "data", &pWrk);
            //fprintf(stderr, "\tDATA=\"%s\"\n", AStr_getData(pWrk));
            pChr = AStr_getData(pWrk);
            pOut = pData;
            for (i=0; ((i < length) && *pChr); ++i) {
                ch = utf8_ChrConToW32_Scan(&pChr);
                *pOut++ = ch & 0xFF;
            }
        }

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
        if (pLength && pData) {
            *pLength = length;
        }
        else if (pLength)
            *pLength = 0;
        return pData;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    uint8_t *       hex_DataFromJSONString(
        ASTR_DATA       *pString,
        uint32_t        *pLength
    )
    {
        ERESULT         eRc;
        JSONIN_DATA     *pParser;
        uint8_t         *pData = NULL;
        
        pParser = JsonIn_New();
        if (OBJ_NIL == pParser) {
            goto exit00;
        }
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }

        pData = hex_ParseObject(pParser, pLength);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pData;
    }
    
    

    uint8_t *       hex_DataFromJSONStringA(
        const
        char            *pString,
        uint32_t        *pLength
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        uint8_t         *pData = NULL;

        if (pString) {
            pStr = AStr_NewA(pString);
            if (pStr) {
                pData = hex_DataFromJSONString(pStr, pLength);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pData;
    }
    
    
    
    ASTR_DATA *     hex_DataToJSON(
        uint32_t        length,
        uint8_t         *pData
    )
    {
        uint32_t        i;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        uint8_t         *pChr;
        char            chrs[12];
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc;
        
        pInfo = hex_Vtbl.iVtbl.pInfo;
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr, "{\"objectType\":\"%s\"", pInfo->pClassName);
        
        AStr_AppendPrint(pStr, ", \"len\":%u", length);
        
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        crc = crc_AccumBlock(pCrc, length, pData);
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        AStr_AppendPrint(pStr, ", \"crc\":%u", crc);
        
        AStr_AppendA(pStr, ", \"data\":\"");
        pChr = pData;
        for (i=0; i<length; ++i) {
            utf8_W32ToChrCon(*pChr++, chrs);
            AStr_AppendA(pStr, chrs);
        }
        AStr_AppendA(pStr, "\"");
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

