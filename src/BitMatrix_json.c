// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BitMatrix_JSON.c
 *
 * Created on 01/18/2018 from szTbl_JSON.c
 *
 */

/*
 Notes:
    1.  ???
        The hash and the table size may change between the destruction
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
#include    <BitMatrix_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <crc.h>
#include    <dec.h>
#include    <hex.h>
#include    <JsonIn.h>
#include    <node.h>
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
    
    void            BitMatrix_Int64ToChrClean(
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
    BITMATRIX_DATA * BitMatrix_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        BITMATRIX_DATA  *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        xSize = 0;
        uint32_t        xWords = 0;
        uint32_t        ySize = 0;
        uint32_t        cElems = 0;
        uint32_t        i;
        uint64_t        iWrk;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        int64_t         intIn;

        pInfo = obj_getInfo(BitMatrix_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "xSize", &intIn);
        xSize = (uint32_t)intIn;
        fprintf(stderr, "\txSize = %u\n", xSize);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "xWords", &intIn);
        xWords = (uint32_t)intIn;
        fprintf(stderr, "\txWords = %u\n", xWords);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "ySize", &intIn);
        ySize = (uint32_t)intIn;
        fprintf(stderr, "\tySize = %u\n", ySize);
        cElems = JsonIn_FindIntegerNodeInHashA(pParser, "cElems", &intIn);
        cElems = (uint32_t)intIn;
        fprintf(stderr, "\tcElems = %u\n", cElems);

        pObject = BitMatrix_NewWithSizes(ySize, xSize);
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        if (cElems) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "Elems", &pArray);
            if (OBJ_NIL == pArray) {
                obj_Release(pObject);
                pObject = OBJ_NIL;
                goto exit00;
            }
            if (cElems == NodeArray_getSize(pArray))
                ;
            else {
                obj_Release(pObject);
                pObject = OBJ_NIL;
                goto exit00;
            }
            for (i=0; i<cElems; ++i) {
                pNode = NodeArray_Get(pArray, i+1);
                if (OBJ_NIL == pNode) {
                    obj_Release(pObject);
                    pObject = OBJ_NIL;
                    goto exit00;
                }
                pName = node_getName(pNode);
                if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                    pStr = node_getData(pNode);
                    iWrk = AStr_ToUint64(pStr);
                    pObject->pElems[i] = (uint32_t)iWrk;
                }
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
    

    BITMATRIX_DATA * BitMatrix_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        BITMATRIX_DATA  *pObject = OBJ_NIL;
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

        pObject = BitMatrix_ParseJsonObject(pParser);
        
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    BITMATRIX_DATA * BitMatrix_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        BITMATRIX_DATA  *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = BitMatrix_NewFromJsonString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
    }
    
    
    
    ASTR_DATA *     BitMatrix_ToJson(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;

#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
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
        AStr_AppendPrint(pStr, "{\"objectType\":\"%s\",\n", pInfo->pClassName);
        AStr_AppendPrint(pStr, "\t\"xSize\":%u,\n", this->xSize);
        AStr_AppendPrint(pStr, "\t\"xWords\":%u,\n", this->xWords);
        AStr_AppendPrint(pStr, "\t\"ySize\":%u,\n", this->ySize);
        AStr_AppendPrint(pStr, "\t\"cElems\":%u,\n", this->cElems);
        if (this->cElems) {
            AStr_AppendA(pStr, "\t\"Elems\":[\n");
            for (i=0; i<this->cElems-1; ++i) {
                AStr_AppendPrint(pStr, "\t\t%u,\n", this->pElems[i]);
            }
            AStr_AppendPrint(pStr, "\t\t%u\n", this->pElems[i]);
            AStr_AppendA(pStr, "\t]\n");
        }
        else {
            AStr_AppendA(pStr, "\t\"Elems\":null\n");
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

