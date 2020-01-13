// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeArray_json.c
 *
 *	Generated 01/10/2020 13:58:02
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
#include    <NodeArray_internal.h>
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
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    NODEARRAY_DATA * NodeArray_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODEARRAY_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(NodeArray_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = NodeArray_New( );
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
    

    NODEARRAY_DATA *   NodeArray_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODEARRAY_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = NodeArray_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NODEARRAY_DATA * NodeArray_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODEARRAY_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = NodeArray_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = NodeArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeArray_ToJson(
        NODEARRAY_DATA   *this
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
        ASTR_DATA       *pWrkStr;
#endif

#ifdef NDEBUG
#else
        if( !NodeArray_Validate(this) ) {
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
            
#ifdef XYZZZY 
            AStr_AppendPrint(pStr,
                             "\"fileIndex\":%d, "
                             "\"offset\":%lld, "
                             "\"lineNo\":%d, "
                             "\"colNo\":%d "
                             "\"severity\":%d ",
                             this->loc.fileIndex,
                             this->loc.offset,
                             this->loc.lineNo,
                             this->loc.colNo,
                             this->severity
            );
             if (this->pErrorStr) {
                pQueryInfo = obj_getVtbl(this->pErrorStr)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              this->pErrorStr,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(this->pErrorStr);
                        if (pWrkStr) {
                            AStr_AppendA(pStr, "\t\"errorStr\": ");
                            AStr_Append(pStr, pWrkStr);
                            obj_Release(pWrkStr);
                            pWrkStr = OBJ_NIL;
                            AStr_AppendA(pStr, "\n");
                        }
                    }
                }
            }
#endif

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

