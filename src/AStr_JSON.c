// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AStr_JSON.c
 *
 * Created on 10/9/2017 from utf8Data_JSON
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
#include    <AStr_internal.h>
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
    
    void            AStr_Int64ToChrClean(
        int64_t         num,
        char            *pBuffer
    )
    {
        char            data[32];
        int             i;
        
        dec_Int64ToChr(num, data);
        
        // Now output string without leading zeroes.
        if (*pBuffer == '-') {
            *pBuffer = data[0];
        }
        ++pBuffer;
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
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    ASTR_DATA *     AStr_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pObject = OBJ_NIL;
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
        
        pObject = AStr_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }

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
    

    ASTR_DATA *     AStr_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        ERESULT         eRc;
        JSONIN_DATA     *pParser;
        ASTR_DATA       *pObject = OBJ_NIL;
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = AStr_ParseObject(pParser);

        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    ASTR_DATA *     AStr_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = AStr_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
    }
    
    
    
    ASTR_DATA *     AStr_ToJSON(
        ASTR_DATA       *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        crc = 0;
        uint32_t        len;
        const
        char            *pData;
        ASTR_DATA       *pWrk = OBJ_NIL;

#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pInfo = AStr_Vtbl.iVtbl.pInfo;
        pData  = array_Ptr(this->pData, 1);

        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{ \"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        len = (uint32_t)utf8_StrLenA(pData);
        AStr_AppendPrint(pStr, ", \"len\":%u", len);
        crc = AStr_getCrcIEEE(this);
        AStr_AppendPrint(pStr, ", \"crc\":%u", crc);
        
        if (len) {
            AStr_AppendA(pStr, ", \"data\":\"");
            pWrk = AStr_ToChrCon(this);
            if (pWrk) {
                AStr_Append(pStr, pWrk);
                BREAK_FALSE((1 == obj_getRetainCount(pWrk)));
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
            AStr_AppendA(pStr, "\"");
        }
        else {
            AStr_AppendA(pStr, ", \"data\":null ");
        }
        
        if (pStr)
            AStr_AppendA(pStr, "}\n");

        BREAK_FALSE((1 == obj_getRetainCount(pStr)));
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

