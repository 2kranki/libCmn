// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   symEntry_JSON.c
 *
 * Created on 01/18/2018 from W32Str_JSON
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
#include    <symEntry_internal.h>
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
    
    void            symEntry_Int64ToChrClean(
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
     @return    a new null object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    SYMENTRY_DATA * symEntry_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SYMENTRY_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        crc = 0;
        uint32_t        length = 0;
        int64_t         intIn = 0;
#ifdef XYZZY
        uint32_t        i;
        W32CHR_T        ch;
        const
        char            *pSrc;
        ASTR_DATA       *pWrk;
#endif
        
        pInfo = obj_getInfo(symEntry_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "crc", &intIn);
        crc = (uint32_t)intIn;
        
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "len", &intIn);
        length = (uint32_t)intIn;

#ifdef XYZZY
        pObject = symEntry_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        if (length && pObject) {
            eRc = jsonIn_FindStringNodeInHashA(pParser, "data", &pWrk);
            pSrc = AStr_getData(pWrk);
            for (i=0; i<length; ++i) {
                ch = utf8_ChrConToW32_Scan(&pSrc);
                symEntry_AppendW32(pObject, 1, &ch);
            }
            if (!(crc == symEntry_getCrcIEEE(pObject))) {
                obj_Release(pObject);
                pObject = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    SYMENTRY_DATA * symEntry_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        SYMENTRY_DATA   *pObject = OBJ_NIL;
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = symEntry_ParseObject(pParser);
        
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    SYMENTRY_DATA * symEntry_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SYMENTRY_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = symEntry_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
    }
    
    
    
    ASTR_DATA *     symEntry_ToJSON(
        SYMENTRY_DATA   *this
    )
    {
        char            str[256];
        //uint32_t        i;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
#ifdef XYZZY
        const
        char            *pChr;
        uint32_t        crc = 0;
        W32CHR_T        chrW;
        W32CHR_T        *pChrW;
        uint32_t        len;
        const
        char            *pData;
#endif
        SYM_ENTRY       *pEntry = NULL;

#ifdef NDEBUG
#else
        if( !symEntry_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        //FIXME: pData  = array_Ptr((ARRAY_DATA *)this, 1);

        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        if (this->pEntry) {
            pEntry = this->pEntry;
            AStr_AppendPrint(pStr, ", \"nameToken\":%u", pEntry->nameToken);
#ifdef XYZZY            
            len = array_getSize((ARRAY_DATA *)this) - 1;
            AStr_AppendPrint(pStr, ", \"len\":%u", len);
            if (len) {
                AStr_AppendA(pStr, ", \"data\":\"");
                pChr = pData;
                for (i=0; i<(len-1); ++i) {
                    pChrW = array_Ptr((ARRAY_DATA *)this, i+1);
                    chrW = *pChrW;
                    utf8_W32ToChrCon(*pChrW, str);
                    AStr_AppendA(pStr, str);
                }
                AStr_AppendA(pStr, "\" ");
            }
            else {
                AStr_AppendA(pStr, ", \"data\":null ");
            }
#endif
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

