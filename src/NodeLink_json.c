// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeLink_json.c
 *
 *	Generated 01/12/2020 10:31:46
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
#include    <NodeLink_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
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
     Parse the fields for a given object from an established parser.
     This is used by the normal object parser for this object type
     and where this object is inherited by a different object.
     @param pParser     an established jsonIn Parser Object
     @return    ERESULT_SUCCESS if successful, otherwise, an
     ERESULT_* error code
     */
    ERESULT         NodeLink_ParseJsonFields(
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
        NODEARRAY_DATA  *pArray = OBJ_NIL;

        pInfo = obj_getInfo(Node_Class());

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
            eRc = Node_ParseJsonFields(pParser, (NODE_DATA *)pObject);
            JsonIn_SubObjectEnd(pParser);
            if (pNode) {
                obj_Release(pNode);
                pNode = OBJ_NIL;
            }
        }

        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "index", &intIn);
        uint32  = (uint32_t)intIn;
        NodeLink_setIndex(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "leftIndex", &intIn);
        uint32  = (uint32_t)intIn;
        NodeLink_setLeftLink(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "middleIndex", &intIn);
        uint32  = (uint32_t)intIn;
        NodeLink_setMiddle(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "parentIndex", &intIn);
        uint32  = (uint32_t)intIn;
        NodeLink_setParent(pObject, uint32);
        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "rightIndex", &intIn);
        uint32  = (uint32_t)intIn;
        NodeLink_setRightLink(pObject, uint32);

        eRc = JsonIn_FindArrayNodeInHashA(pParser, "flags", &pArray);
        if (!ERESULT_FAILED(eRc)) {
            ASTR_DATA       *pStr = NodeArray_ToDebugString(pArray, 0);
            if (pStr) {
                fprintf(stderr, "ARRAY= %s\n", AStr_getData(pStr));
                obj_Release(pStr);
            }
        }

        // Return to caller.
    exit00:
        return eRc;
    }



    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODELINK_DATA * NodeLink_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODELINK_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(NodeLink_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = NodeLink_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc = NodeLink_ParseJsonFields(pParser, pObject);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - Parsing Fields failed!\n");
            goto exit00;
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
    

    NODELINK_DATA *   NodeLink_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODELINK_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = NodeLink_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NODELINK_DATA * NodeLink_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODELINK_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = NodeLink_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = NodeLink_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeLink_ToJson(
        NODELINK_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
#ifdef XYZZZY 
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        ASTR_DATA *     (*pToJson)(
            OBJ_ID          objId
        );
#endif
        ASTR_DATA       *pWrkStr;

#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
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
            
            AStr_AppendPrint(
                             pStr,
                             "\t\"index\":%d,"
                             " \"leftIndex\":%d,"
                             " \"middleIndex\":%d,"
                             " \"parentIndex\":%d,"
                             " \"rightIndex\":%d,\n",
                             this->index,
                             this->leftIndex,
                             this->middleIndex,
                             this->parentIndex,
                             this->rightIndex
            );
            AStr_AppendA(pStr, "\tflags:[ ");
            if (obj_Flag(this, NODELINK_LEFT_LINK)) {
                AStr_AppendA(pStr, "\"LEFT\", ");
            }
            if (obj_Flag(this, NODELINK_RIGHT_LINK)) {
                AStr_AppendA(pStr, "\"RIGHT\", ");
            }
            if (obj_Flag(this, NODELINK_RIGHT_CHILD)) {
                AStr_AppendA(pStr, "\"RIGHT_CHILD\", ");
            }
            AStr_AppendA(pStr, "],\n");

            if (this) {
                pWrkStr = Node_ToJson((NODE_DATA *)this);
                AStr_AppendA(pStr, "\t\"node\":");
                AStr_Append(pStr, pWrkStr);\
                obj_Release(pWrkStr);
                pWrkStr = OBJ_NIL;
            }

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

