// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   szTbl_JSON.c
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
#include    <szTbl_internal.h>
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
    
    void            szTbl_Int64ToChrClean(
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
    SZTBL_DATA *    szTbl_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SZTBL_DATA      *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
#ifdef XYZZY
        uint32_t        crc = 0;
        uint32_t        length = 0;
        uint32_t        i;
        W32CHR_T        ch;
        const
        char            *pSrc;
        ASTR_DATA       *pWrk;
#endif
        
        pInfo = obj_getInfo(szTbl_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
#ifdef XYZZY
        crc = (uint32_t)jsonIn_FindIntegerNodeInHash(pParser, "crc");
        
        length = (uint32_t)jsonIn_FindIntegerNodeInHash(pParser, "len");

        pObject = szTbl_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        if (length && pObject) {
            pWrk = jsonIn_FindStringNodeInHash(pParser, "data");
            pSrc = AStr_getData(pWrk);
            for (i=0; i<length; ++i) {
                ch = utf8_ChrConToW32_Scan(&pSrc);
                szTbl_AppendW32(pObject, 1, &ch);
            }
            if (!(crc == szTbl_getCrcIEEE(pObject))) {
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
    

    SZTBL_DATA *    szTbl_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        SZTBL_DATA      *pObject = OBJ_NIL;
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = szTbl_ParseObject(pParser);
        
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    SZTBL_DATA *    szTbl_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SZTBL_DATA      *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = szTbl_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
    }
    
    
    
    ASTR_DATA *     szTbl_ToJSON(
        SZTBL_DATA      *this
    )
    {
        //char            str[256];
        uint32_t        i;
        uint32_t        j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        SZTBL_NODE      *pNode;
        uint32_t        size = szTbl_getSize(this);

#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pInfo = szTbl_Vtbl.iVtbl.pInfo;
        //FIXME: pData  = array_Ptr((ARRAY_DATA *)this, 1);

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        AStr_AppendPrint(pStr, "{\"objectType\":\"%s\"", pInfo->pClassName);
        
        AStr_AppendPrint(pStr, ", \"Count\":%u", size);
        if (size) {
            AStr_AppendA(pStr, "\t\"Entries\":[\n");
            for (i=0; i<(size - 1); ++i) {
                pNode = ptrArray_GetData(this->pPtrArray, i+1);
                if (pNode) {
                    AStr_AppendPrint(
                                     pStr,
                                     "\t{Length:%u,\"Hash\":%u,\"Ident\":%u,\n",
                                     pNode->len,
                                     pNode->hash,
                                     pNode->ident
                                     );
                    if (pNode->len) {
                        AStr_AppendA(pStr, "\t\t\"Data\":[");
                        for (j=0; j<(pNode->len - 1); ++j) {
                            AStr_AppendPrint(pStr, "%u,", pNode->data[j]);
                        }
                        AStr_AppendPrint(pStr, "%u", pNode->data[j]);
                        AStr_AppendA(pStr, "]\n");
                    }
                    else {
                        AStr_AppendA(pStr, "\t\t\"Data\":null");
                    }
                    AStr_AppendA(pStr, "\t},\n");
                }
            }
            pNode = ptrArray_GetData(this->pPtrArray, i+1);
            if (pNode) {
                AStr_AppendPrint(
                                 pStr,
                                 "\t{Length:%u,\"Hash\":%u,\"Ident\":%u,\n",
                                 pNode->len,
                                 pNode->hash,
                                 pNode->ident
                                 );
                if (pNode->len) {
                    AStr_AppendA(pStr, "\t\t\"Data\":[");
                    for (j=0; j<(pNode->len - 1); ++j) {
                        AStr_AppendPrint(pStr, "%u,", pNode->data[j]);
                    }
                    AStr_AppendPrint(pStr, "%u", pNode->data[j]);
                    AStr_AppendA(pStr, "]\n");
                }
                else {
                    AStr_AppendA(pStr, "\t\t\"Data\":null");
                }
                AStr_AppendA(pStr, "\t}\n");
            }
            AStr_AppendA(pStr, "\t]\n");
        }
        else {
            AStr_AppendA(pStr, "\t\"Entries\":null\n");
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

