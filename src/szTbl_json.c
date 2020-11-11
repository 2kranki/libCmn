// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   szTbl_JSON.c
 *
 * Created on 01/18/2018 from W32Str_JSON
 *
 */

/*
 Notes:
    1.  The hash and the table size may change between the destruction
        and creation of the new table based on the JSON text.  So, to
        keep the unique numbers constant, we create the JSON text in
        unique number order and recreate the table in that same order.
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
#include    <JsonIn.h>
#include    <Node.h>
#include    <NodeArray.h>
#include    <NodeHash.h>
#include    <utf8_internal.h>

#define DEBUG_JSONIN 1


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
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SZTBL_DATA *    szTbl_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SZTBL_DATA      *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        count = 0;
        uint32_t        hash = 0;
        uint32_t        len = 0;
        uint32_t        len2 = 0;
        uint32_t        ident = 0;
        uint32_t        unique = 0;
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        NODEARRAY_DATA  *pArray;
        NODEHASH_DATA   *pHash;
        uint32_t        i;
        char            *pData = NULL;
        int64_t         intIn = 0;

        pInfo = obj_getInfo(szTbl_Class());
        
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

        pObject = szTbl_New();
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
                pName = Node_getName(pNode);
                if (0 == Name_CompareA(pName, "hash"))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - Node name is not valid!\n"
                    );
                    goto exit00;
                }
                pHash = Node_getData(pNode);
                if (OBJ_NIL == pHash) {
                    fprintf(
                            stderr,
                            "ERROR - Node's data is not valid!\n"
                    );
                    goto exit00;
                }
                if (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - Node's data is not a hash!\n"
                    );
                    goto exit00;
                }
                eRc = JsonIn_SubObjectFromHash(pParser, pHash);
                eRc = JsonIn_FindIntegerNodeInHashA(pParser, "Hash", &intIn);
                if (ERESULT_FAILED(eRc)) {
                    fprintf(
                            stderr,
                            "ERROR - Hash code for a node could not be found!\n"
                    );
                    goto exit00;
                }
                hash = (uint32_t)intIn;
                //fprintf(stderr, "\t\tHash(%d) = %u\n", i+1, hash);
                eRc = JsonIn_FindIntegerNodeInHashA(pParser, "Ident", &intIn);
                if (ERESULT_FAILED(eRc)) {
                    fprintf(
                            stderr,
                            "ERROR - Ident code for a node could not be found!\n"
                    );
                    goto exit00;
                }
                ident = (uint32_t)intIn;
                //fprintf(stderr, "\t\tIdent(%d) = %u\n", i+1, ident);
                eRc = JsonIn_FindIntegerNodeInHashA(pParser, "Length", &intIn);
                if (ERESULT_FAILED(eRc)) {
                    fprintf(
                            stderr,
                            "ERROR - Length for a node could not be found!\n"
                    );
                    goto exit00;
                }
                len = (uint32_t)intIn;
                //fprintf(stderr, "\t\tlen(%d) = %u\n", i+1, len);
                eRc = JsonIn_SubObjectInHash(pParser, "Data");
                if (ERESULT_FAILED(eRc)) {
                    fprintf(
                            stderr,
                            "ERROR - Data for a node could not be found!\n"
                    );
                    goto exit00;
                }
                pData = (char *)utf8_ParseJsonObject(pParser, &len2);
                if (OBJ_NIL == pHash) {
                    fprintf(
                            stderr,
                            "ERROR - UTF-8 data for a node could not be found!\n"
                    );
                    goto exit00;
                }
                if (len == len2)
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - UTF-8 data length is possibly invalid (%d:%d)!\n",
                            len,
                            len2
                    );
                    goto exit00;
                }
                //fprintf(stderr, "\t\tdata(%d) = %s\n", i+1, pData);
                unique = szTbl_StringToToken(pObject, pData);
                if (pData) {
                    mem_Free(pData);
                    pData = NULL;
                }
                if (unique == ident)
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - UTF-8 data length is possibly invalid!\n"
                    );
                    goto exit00;
                }
                eRc = JsonIn_SubObjectEnd(pParser);
                eRc = JsonIn_SubObjectEnd(pParser);
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
    

    SZTBL_DATA *    szTbl_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        SZTBL_DATA      *pObject = OBJ_NIL;
#ifdef DEBUG_JSONIN
        ASTR_DATA       *pStrDebug = OBJ_NIL;
#endif
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
#ifdef DEBUG_JSONIN
        pStrDebug = NodeHash_ToDebugString(JsonIn_getHash(pParser), 0);
        if (pStrDebug) {
            fprintf(stderr, "%s\n\n", AStr_getData(pStrDebug));
            obj_Release(pStrDebug);
            pStrDebug = OBJ_NIL;
        }
#endif

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
        ASTR_DATA       *pStr;
        ASTR_DATA       *pStrWrk = OBJ_NIL;
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

        // We need to insure that the table entries are in ascending order
        // by their unique number so that they are restored in the table
        // properly.  Other objects such as szHash rely on this number staying
        // constant.
        // We do not have the ability to add specific entries
        // with a given unique number.  Other
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        AStr_AppendPrint(pStr, "{\"objectType\":\"%s\",\n", pInfo->pClassName);
        AStr_AppendPrint(pStr, "\t\"Count\":%u,\n", size);
        if (size) {
            AStr_AppendA(pStr, "\t\"Entries\":[\n");
            for (i=0; i<size; ++i) {
                pNode = ptrArray_GetData(this->pPtrArray, i+1);
                if (pNode) {
                    AStr_AppendPrint(
                                     pStr,
                                     "\t\t{Length:%u, \"Hash\":%u, \"Ident\":%u,\n",
                                     pNode->len,
                                     pNode->hash,
                                     pNode->ident
                                     );
                    if (pNode->len) {
                        pStrWrk = utf8_DataToJson((const char *)pNode->data);
                        AStr_AppendA(pStr, "\t\t\t\"Data\":");
                        AStr_Append(pStr, pStrWrk);
                        obj_Release(pStrWrk);
                        pStrWrk = OBJ_NIL;
                    }
                    else {
                        AStr_AppendA(pStr, "\t\t\t\"Data\":null");
                    }
                    if (i == (size - 1)) {
                        AStr_AppendA(pStr, "\t\t}\n");
                    }
                    else {
                        AStr_AppendA(pStr, "\t\t},\n");
                    }
                }
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

