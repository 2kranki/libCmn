// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   dec_JSON.c
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
#include    <dec_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <crc.h>
#include    <dec.h>
#include    <JsonIn.h>
#include    <node.h>
#include    <NodeHash.h>
#include    <utf8.h>


//#define TRACE_FUNCTIONS     1


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
    uint64_t        dec_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        const
        OBJ_INFO        *pInfo;
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
        uint32_t        crc2 = 0;
        uint32_t        length = 0;
        uint64_t        object = 0;
        int64_t         intIn;
        
        pInfo = obj_getInfo(dec_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "crc", &intIn);
        crc = (uint32_t)intIn;

        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "len", &intIn);
        length = (uint32_t)intIn;
        if (length == 8) {
            ;
        }
        else {
            fprintf(stderr, "ERROR - Invalid Length! %u\n", length);
            goto exit00;
        }

        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "data", &intIn);
        object = (uint64_t)intIn;

        pCrc = crc_New(CRC_TYPE_IEEE_32);
        if (pCrc) {
            crc2 = crc_AccumBlock(pCrc, 8, (void *)&object);
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
        return object;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    uint64_t        dec_UInt64FromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        uint64_t        data = 0;

        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        data = dec_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return data;
    }
    
    

    uint64_t        dec_UInt64FromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        uint64_t        object = 0;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            object = dec_UInt64FromJsonString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return object;
    }
    
    
    
    ASTR_DATA *     dec_UInt64ToJson(
        uint64_t        data
    )
    {
        char            str[256];
        //uint32_t        i;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        //ASTR_DATA       *pWrk;
        char            *pChr;
        char            chrs[32];
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        len = 32;
        uint32_t        crc;
        
        pInfo = dec_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{ \"objectType\":\"%s\", ",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendPrint(pStr, "\"len\":%u, ", 8);
        
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        crc = crc_AccumBlock(pCrc, 8, (void *)&data);
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        AStr_AppendPrint(pStr, "\"crc\":%u, ", crc);
        
        AStr_AppendA(pStr, "\"data\":");
        pChr = chrs;
        dec_putUint64A(data, &len, &pChr);
        pChr = chrs;
        len = 19;
        while ((*pChr == '0') && len--) {
            ++pChr;
        }
        AStr_AppendA(pStr, pChr);
        
        AStr_AppendA(pStr, " }\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

