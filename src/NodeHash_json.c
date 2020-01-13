// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeHash_json.c
 *
 *	Generated 01/10/2020 16:43:06
 *
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
#include    <NodeHash_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <crc.h>
#include    <dec.h>
#include    <hex.h>
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
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODEHASH_DATA * NodeHash_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODEHASH_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(NodeHash_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = NodeHash_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
#ifdef XYZZZY 
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "fileIndex", &intIn);
        pObject->loc.fileIndex = (uint32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "offset", &pObject->loc.offset);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "lineNo", &intIn);
        pObject->loc.lineNo = (uint32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "colNo", &intIn);
        pObject->loc.colNo = (uint16_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "severity", &intIn);
        pObject->severity = (uint16_t)intIn;

        eRc = JsonIn_SubobjectInHash(pParser, "errorStr");
        pWrk = AStr_ParseJsonObject(pParser);
        if (pWrk) {
            pObject->pErrorStr = pWrk;
        }
        JsonIn_SubobjectEnd(pParser);
#endif

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
    

    NODEHASH_DATA *   NodeHash_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODEHASH_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = NodeHash_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NODEHASH_DATA * NodeHash_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODEHASH_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = NodeHash_NewFromJsonString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
    }
    
    
    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = NodeHash_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeHash_ToJson(
        NODEHASH_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        ASTR_DATA *     (*pToJson)(
            OBJ_ID          objId
        );
        //ASTR_DATA       *pWrkStr;
        uint32_t        i;
        bool            fRc;
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
        ASTR_DATA       *pData;

#ifdef NDEBUG
#else
        if( !NodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
             AStr_AppendPrint(pStr,
                              "{ \"objectType\":\"%s\", ",
                              pInfo->pClassName
             );
            
            // Scan the Hash Table insuring that all entries are Nodes
            // which have the "ToJson" method.
            fRc = true;
            pList = Blocks_getList((BLOCKS_DATA *)this);
            pEntry = listdl_Head(pList);
            while (pEntry) {
                NODEHASH_RECORD     *pRecord = (NODEHASH_RECORD *)pEntry->data;
                RBT_NODE            *pNode = &pRecord->node;

                if (!obj_IsKindOf(pNode->pKey, OBJ_IDENT_NODE)) {
                    fRc = false;
                    break;
                }
                pQueryInfo = obj_getVtbl(pNode->pKey)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson = (*pQueryInfo)(
                                            pNode->pKey,
                                            OBJ_QUERYINFO_TYPE_METHOD,
                                            "ToJson"
                                            );
                    if (NULL == pToJson) {
                        fRc = false;
                        break;
                    }
                }
                else {
                    fRc = false;
                    break;
                }

                pEntry = listdl_Next(pList, pEntry);
            }

            if (!fRc) {
                return OBJ_NIL;
            }

            pStr = AStr_New();
            AStr_AppendPrint(
                        pStr,
                        "{ \"objectType\":\"%s\", \"count\":%d, \"entries\":[\n",
                        pInfo->pClassName,
                        this->size
            );

            // Scan the Hash Table creating entries for each of the objects
            // in the table and appending them to the array.
            i = this->size;
            pList = Blocks_getList((BLOCKS_DATA *)this);
            pEntry = listdl_Head(pList);
            while (pEntry) {
                NODEHASH_RECORD     *pRecord = (NODEHASH_RECORD *)pEntry->data;
                RBT_NODE            *pNode = &pRecord->node;

                pData = OBJ_NIL;
                pQueryInfo = obj_getVtbl(pNode->pKey)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                          pNode->pKey,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                );
                    if (pToJson) {
                        pData = (*pToJson)(pNode->pKey);
                        if (pData) {
                            //AStr_AppendPrint(pStr, "/* %d */\n", j++);
                            AStr_Append(pStr, pData);
                            obj_Release(pData);
                            pData = OBJ_NIL;
                            if (i-- > 1) {
                                AStr_AppendA(pStr, ",\n");
                            }
                            else {
                                AStr_AppendA(pStr, "\n");
                            }
                        }
                    }
                }
                pEntry = listdl_Next(pList, pEntry);
            }
            AStr_AppendA(pStr, "]\n\n\n");

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

