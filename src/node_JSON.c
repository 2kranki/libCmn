// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   node.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on December 30, 2014
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
#include    <node_internal.h>
#include    <name_internal.h>
#include    <token_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <JsonIn.h>
#include    <node.h>
#include    <nodeHash.h>
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
     @warning   Returned null object must be released.
     */
    NODE_DATA *     node_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;

        pInfo = obj_getInfo(node_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        pObject = node_New( );
        if (OBJ_NIL == pObject) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto exit00;
        }
        
        eRc = node_ParseJsonObjectFields(pParser, pObject);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - Parsing Fields failed!\n");
            goto exit00;
        }

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    exit00:
        return pObject;
    }
    
    
    
    /*!
     Parse the fields for a given object from an established parser.
     This is used by the normal object parser for this object type
     and where this object is inherited by a different object.
     @param pParser     an established jsonIn Parser Object
     @return    ERESULT_SUCCESS if successful, otherwise, an
                ERESULT_* error code
     */
    ERESULT         node_ParseJsonObjectFields(
        JSONIN_DATA     *pParser,
        NODE_DATA       *pObject
    )
    {
        ERESULT         eRc;
        const
        OBJ_INFO        *pInfo;
        uint32_t        uint32 = 0;
        int32_t         int32 = 0;
        OBJ_ID          pObj = OBJ_NIL;
        //uint8_t         *pUtf8;
        SRCLOC_DATA     *pSrc = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
        int64_t         intIn;
        
        pInfo = obj_getInfo(node_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        if (pObject)
            ;
        else {
            fprintf(stderr, "ERROR - object is missing!\n");
            eRc = ERESULT_DATA_MISSING;
            goto exit00;
        }

        eRc = JsonIn_SubObjectInHash(pParser, "name");
        if (ERESULT_FAILED(eRc)) {
            pName = name_ParseJsonObject(pParser);
            JsonIn_SubObjectEnd(pParser);
            if (pName) {
                node_setProperties(pObject, pObj);
                obj_Release(pObj);
                pObj = OBJ_NIL;
            }
            else {
                fprintf(stderr, "ERROR - name is invalid!\n");
                eRc = ERESULT_DATA_MISSING;
                goto exit00;
            }
        }
        
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "class", &intIn);
        uint32  = (uint32_t)intIn;
        node_setClass(pObject, uint32);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "type", &intIn);
        int32   = (int32_t)intIn;
        node_setType(pObject, int32);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc", &intIn);
        uint32   = (uint32_t)intIn;
        node_setMisc(pObject, uint32);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc1", &intIn);
        uint32   = (uint32_t)intIn;
        node_setMisc1(pObject, uint32);
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc2", &intIn);
        uint32   = (uint32_t)intIn;
        node_setMisc2(pObject, uint32);

        eRc = JsonIn_SubObjectInHash(pParser, "data");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObj = JsonIn_ParseObject(pParser);
            JsonIn_SubObjectEnd(pParser);
            if (pObj) {
                node_setData(pObject, pObj);
                obj_Release(pObj);
                pObj = OBJ_NIL;
            }
        }
        
        eRc = JsonIn_SubObjectInHash(pParser, "other");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObj = JsonIn_ParseObject(pParser);
            JsonIn_SubObjectEnd(pParser);
            if (pObj) {
                node_setOther(pObject, pObj);
                obj_Release(pObj);
                pObj = OBJ_NIL;
            }
        }
        
        eRc = JsonIn_SubObjectInHash(pParser, "extra");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObj = JsonIn_ParseObject(pParser);
            JsonIn_SubObjectEnd(pParser);
            if (pObj) {
                node_setExtra(pObject, pObj);
                obj_Release(pObj);
                pObj = OBJ_NIL;
            }
        }
        
        eRc = JsonIn_SubObjectInHash(pParser, "properties");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObj = JsonIn_ParseObject(pParser);
            JsonIn_SubObjectEnd(pParser);
            if (pObj) {
                node_setProperties(pObject, pObj);
                obj_Release(pObj);
                pObj = OBJ_NIL;
            }
        }
        
        // Return to caller.
        eRc = ERESULT_SUCCESS;
    exit00:
        if (pSrc) {
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        return eRc;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    NODE_DATA *     node_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODE_DATA       *pNodeOut = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pNodeOut;
    }
    
    

    NODE_DATA *     node_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pNode = node_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    ASTR_DATA *     node_ToJson(
        NODE_DATA       *this
    )
    {
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        //ASTR_DATA       *pWrkStr;
        ASTR_DATA *     (*pToJSON)(
            OBJ_ID          objId
        );

#ifdef NDEBUG
#else
        if( !node_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(
                     pStr,
                     "{ \"objectType\":\"%s\", "
                         "\"class\":%d, "
                         "\"type\":%d, "
                         "\"unique\":%d, "
                         "\"misc\":%d, "
                         "\"misc1\":%d, "
                         "\"misc2\":%d, \n",
                     pInfo->pClassName,
                     this->cls,
                     this->type,
                     this->unique,
                     this->misc,
                     node_getMisc1(this),
                     node_getMisc2(this)
        );

        if (this->pName) {
            pWrkStr = name_ToJson(this->pName);
            AStr_AppendA(pStr, "\t\"name\": ");
            AStr_Append(pStr, pWrkStr);\
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
            AStr_AppendA(pStr, "\n");
        }
        
        if (this->pData) {
            pQueryInfo = obj_getVtbl(this->pData)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pData,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pData);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"data\": ");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        if (this->pOther) {
            pQueryInfo = obj_getVtbl(this->pOther)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pOther,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pOther);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"other\": ");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        if (this->pExtra) {
            pQueryInfo = obj_getVtbl(this->pExtra)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pExtra,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pExtra);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"extra\": ");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        if (this->pProperties) {
            pQueryInfo = obj_getVtbl(this->pProperties)->pQueryInfo;
            if (pQueryInfo) {
                pToJSON =   (*pQueryInfo)(
                                          this->pProperties,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJSON) {
                    pWrkStr = (*pToJSON)(this->pProperties);
                    if (pWrkStr) {
                        AStr_AppendA(pStr, "\t\"properties\": ");
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        AStr_AppendA(pStr, "\n");
                    }
                }
            }
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

