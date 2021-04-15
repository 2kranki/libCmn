// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeLink_json.c
 *
 *  Generated 02/03/2021 18:58:16
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
#include    <JsonOut.h>
#include    <Node_internal.h>
#include    <NodeHash.h>
#include    <SrcErrors.h>
#include    <utf8.h>




#ifdef  __cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT     NodeLink_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NODELINK_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        //NODEHASH_DATA   *pHash = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        int64_t         intIn;
        //ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        //uint32_t        len;
        uint32_t        uint32 = 0;

        eRc = JsonIn_SubObjectInHash(pParser, "Node");
        if (ERESULT_OK(eRc)) {
            eRc = Node_ParseJsonFields(pParser, (NODE_DATA *)pObject);
            JsonIn_SubObjectEnd(pParser);
        }

        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "misc", &intIn);
        uint32  = (uint32_t)intIn;
        obj_setMisc(pObject, uint32);
        eRc  = JsonIn_FindU32NodeInHashA(pParser, "index", &pObject->index);
        eRc  = JsonIn_FindU32NodeInHashA(pParser, "leftIndex", &pObject->leftIndex);
        eRc  = JsonIn_FindU32NodeInHashA(pParser, "middleIndex", &pObject->middleIndex);
        eRc  = JsonIn_FindU32NodeInHashA(pParser, "parentIndex", &pObject->parentIndex);
        eRc  = JsonIn_FindU32NodeInHashA(pParser, "rightIndex", &pObject->rightIndex);

        eRc = JsonIn_FindArrayNodeInHashA(pParser, "flags", &pArray);
        if (!ERESULT_FAILED(eRc)) {
            iMax = NodeArray_getSize(pArray);
            for (i=0; i<iMax; i++) {
                NODE_DATA       *pNode = NodeArray_Get(pArray, i+1);
                ASTR_DATA       *pName = OBJ_NIL;
                pName = JsonIn_CheckNodeForString(pNode);
                if (pName) {
                    if (0 == AStr_CompareA(pName, "LEFT")) {
                        obj_FlagSet(pObject, NODELINK_LEFT_LINK, true);
                    }
                    else if (0 == AStr_CompareA(pName, "RIGHT")) {
                        obj_FlagSet(pObject, NODELINK_RIGHT_LINK, true);
                    }
                    else if (0 == AStr_CompareA(pName, "RIGHT_CHILD")) {
                        obj_FlagSet(pObject, NODELINK_RIGHT_CHILD, true);
                    }
                    else {
                        //TODO: Issue error message.
                    }
                }
            }
        }

        {
            ASTR_DATA       *pStr = JsonIn_ToDebugString(pParser, 0);
            if (pStr) {
                fprintf(stderr, "====> Before Scanning Node:\n%s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
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
    NODELINK_DATA * NodeLink_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODELINK_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        JsonIn_RegisterClass(NodeLink_Class());
        JsonIn_RegisterClass(Node_Class());

        pInfo = obj_getInfo(NodeLink_Class());
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = NodeLink_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  NodeLink_ParseJsonFields(pParser, pObject);

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
    

    NODELINK_DATA *   NodeLink_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODELINK_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            SrcErrors_Print(OBJ_NIL, stderr);
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
    
    

    NODELINK_DATA * NodeLink_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODELINK_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
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
    ASTR_DATA *     NodeLink_ToJson (
        NODELINK_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

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
                              "{ \"objectType\":\"%s\",\n",
                              pInfo->pClassName
             );
     
            eRc = NodeLink_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         NodeLink_ToJsonFields (
        NODELINK_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;
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
        //ASTR_DATA       *pWrkStr;

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
        JsonOut_Append_u32("misc", obj_getMisc(this), pStr);

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

        AStr_AppendA(pStr, "\tNode:{\n");
        eRc = Node_ToJsonFields((NODE_DATA *)this, pStr);
        AStr_AppendA(pStr, "\t},\n");

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef  __cplusplus
}
#endif

