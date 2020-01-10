// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   u8Array_json.c
 *
 * Created on 09/9/2018 from szTbl_JSON
 *
 */

/*
 Notes:
    1.  None
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
#include    <u8Array_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <crc.h>
#include    <dec.h>
#include    <hex.h>
#include    <JsonIn.h>
#include    <node.h>
#include    <NodeArray.h>
#include    <nodeHash.h>
#include    <utf8_internal.h>

#define DEBUG_JSONIN 1


#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    void            u8Array_Int64ToChrClean(
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
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    U8ARRAY_DATA *  u8Array_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        U8ARRAY_DATA    *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        count = 0;
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        NODEARRAY_DATA  *pArray;
        ASTR_DATA       *pStr;
        uint32_t        i;
        int64_t         intIn = 0;

        pInfo = obj_getInfo(u8Array_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "Count", &intIn);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - count is invalid!\n");
            goto exit00;
        }
        count = (uint32_t)intIn;
        fprintf(stderr, "\tNode Count = %d\n", count);

        pObject = u8Array_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        if (count && pObject) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "Entries", &pArray);
            if (pArray) {
                if (count == NodeArray_getSize(pArray))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            count,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
            }
            else {
                fprintf(
                    stderr,
                    "ERROR - JSON Count, %d, is present, but Entries were not found!\n",
                    count
                );
                goto exit00;
            }

            for(i=0; i<count; ++i) {
                fprintf(stderr, "\t\tLooking for Node(%d)\n", i+1);
                pNode = NodeArray_Get(pArray, i+1);
                if (OBJ_NIL == pNode) {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            count,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
                pName = node_getName(pNode);
                if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer"))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - Node name is not valid!\n"
                    );
                    goto exit00;
                }
                pStr = node_getData(pNode);
                if (OBJ_NIL == pStr) {
                    fprintf(
                            stderr,
                            "ERROR - Node's data is not valid!\n"
                    );
                    goto exit00;
                }
                fprintf(stderr,
                        "\t\t...found - %s -- 0x%02X\n",
                        AStr_getData(pStr),
                        (uint8_t)AStr_ToInt64(pStr));
                eRc = u8Array_AppendData(pObject, (uint8_t)AStr_ToInt64(pStr));
            }
        }
        
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
    

    U8ARRAY_DATA *  u8Array_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        U8ARRAY_DATA    *pObject = OBJ_NIL;
#ifdef DEBUG_JSONIN
        ASTR_DATA       *pStrDebug = OBJ_NIL;
#endif
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
#ifdef DEBUG_JSONIN
        pStrDebug = nodeHash_ToDebugString(JsonIn_getHash(pParser), 0);
        if (pStrDebug) {
            fprintf(stderr, "%s\n\n", AStr_getData(pStrDebug));
            obj_Release(pStrDebug);
            pStrDebug = OBJ_NIL;
        }
#endif

        pObject = u8Array_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    U8ARRAY_DATA *  u8Array_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        U8ARRAY_DATA    *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = u8Array_NewFromJsonString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
    }
    
    
    
    ASTR_DATA *     u8Array_ToJson (
        U8ARRAY_DATA    *this
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        size = u8Array_getSize(this);
        uint8_t         data;

#ifdef NDEBUG
#else
        if( !u8Array_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        AStr_AppendPrint(pStr, "{\n\t\"objectType\":\"%s\",\n", pInfo->pClassName);
        AStr_AppendPrint(pStr, "\t\"Count\":%u,\n", size);
        if (size) {
            AStr_AppendA(pStr, "\t\"Entries\":[\n");
            for (i=0; i<(size - 1); ++i) {
                data = u8Array_Get(this, (i + 1));
                eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t\t%d,\n",
                                     data
                        );
            }
            data = u8Array_Get(this, (i + 1));
            eRc =   AStr_AppendPrint(
                                     pStr,
                                     "\t\t%d\n",
                                     data
                    );
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

