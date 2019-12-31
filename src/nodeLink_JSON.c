// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeLink.c
 * Copied from node_JSON 06/30/2018 21:24
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
#include    <nodeLink_internal.h>
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
    NODELINK_DATA * nodeLink_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODELINK_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;

        pInfo = obj_getInfo(node_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        pObject = nodeLink_New( );
        if (OBJ_NIL == pObject) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto exit00;
        }
        
        eRc = nodeLink_ParseObjectFields(pParser, pObject);
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
    ERESULT         nodeLink_ParseObjectFields(
        JSONIN_DATA     *pParser,
        NODELINK_DATA   *pObject
    )
    {
        ERESULT         eRc;
        const
        OBJ_INFO        *pInfo;
        uint32_t        uint32 = 0;
        //OBJ_ID          pObj = OBJ_NIL;
        //uint8_t         *pUtf8;
        //SRCLOC_DATA     *pSrc = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
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

        eRc = JsonIn_SubObjectInHash(pParser, "node");
        if (ERESULT_FAILED(eRc)) {
            eRc = node_ParseJsonObjectFields(pParser, (NODE_DATA *)pObject);
            JsonIn_SubObjectEnd(pParser);
            if (pNode) {
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
        }
        
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "index", &intIn);
        uint32  = (uint32_t)intIn;
        nodeLink_setIndex(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "leftIndex", &intIn);
        uint32  = (uint32_t)intIn;
        nodeLink_setLeftLink(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "middleIndex", &intIn);
        uint32  = (uint32_t)intIn;
        nodeLink_setMiddle(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "parentIndex", &intIn);
        uint32  = (uint32_t)intIn;
        nodeLink_setParent(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "rightIndex", &intIn);
        uint32  = (uint32_t)intIn;
        nodeLink_setRightLink(pObject, uint32);

        // Return to caller.
    exit00:
        return eRc;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    NODELINK_DATA * nodeLink_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        ERESULT         eRc;
        JSONIN_DATA     *pParser;
        NODELINK_DATA   *pNodeOut = OBJ_NIL;
        
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
    
    

    NODELINK_DATA * nodeLink_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODELINK_DATA   *pNode = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pNode = nodeLink_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    ASTR_DATA *     nodeLink_ToJSON(
        NODELINK_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;

#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(
                     pStr,
                     "{\"objectType\":\"%s\",\n",
                     pInfo->pClassName
        );
        AStr_AppendPrint(
                         pStr,
                         "\t\"index\":\"%s\","
                         "\t\"leftIndex\":\"%s\","
                         "\"middleIndex\":\"%d\","
                         "\"parentIndex\":\"%d\","
                         "\"rightIndex\":%d,\n",
                         this->index,
                         this->leftIndex,
                         this->middleIndex,
                         this->parentIndex,
                         this->rightIndex
        );

        if (this) {
            pWrkStr = node_ToJson((NODE_DATA *)this);
            AStr_AppendA(pStr, "\t\"node\":");
            AStr_Append(pStr, pWrkStr);\
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

