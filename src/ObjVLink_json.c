// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjVLink_json.c
 *
 *	Generated 01/14/2020 16:31:30
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
#include    <ObjVLink_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
#include    <I32Array_internal.h>
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
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT     ObjVLink_ParseJsonFields(
        JSONIN_DATA     *pParser,
        OBJVLINK_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        OBJ_INFO        *pInfo;
        int64_t         intIn;
        OBJ_ID          pWrk;

        pInfo = obj_getInfo(ObjVLink_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "index", &intIn);
       pObject->index = (int32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "left", &intIn);
        pObject->left = (int32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "middle", &intIn);
        pObject->middle = (int32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc", &intIn);
        pObject->misc = (int32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "parent", &intIn);
        pObject->parent = (int32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "right", &intIn);
        pObject->right = (int32_t)intIn;

#ifdef XYZZZY
        eRc = JsonIn_SubobjectInHash(pParser, "object");
        pWrk = AStr_ParseJsonObject(pParser);
        if (pWrk) {
            pObject->pErrorStr = pWrk;
        }
        JsonIn_SubobjectEnd(pParser);
#endif

        eRc = JsonIn_SubObjectInHash(pParser, "array");
        pWrk = I32Array_ParseJsonObject(pParser);
        if (pWrk) {
            pObject->pArray = pWrk;
        }
        JsonIn_SubObjectEnd(pParser);

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
    OBJVLINK_DATA * ObjVLink_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        OBJVLINK_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(ObjVLink_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = ObjVLink_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  ObjVLink_ParseJsonFields(pParser, pObject);

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
    

    OBJVLINK_DATA *   ObjVLink_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        OBJVLINK_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = ObjVLink_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    OBJVLINK_DATA * ObjVLink_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJVLINK_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = ObjVLink_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = ObjVLink_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjVLink_ToJson(
        OBJVLINK_DATA   *this
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
        ASTR_DATA       *pWrkStr;

#ifdef NDEBUG
#else
        if( !ObjVLink_Validate(this) ) {
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
            
            AStr_AppendPrint(pStr,
                             "\"index\":%d, "
                             "\"left\":%d, "
                             "\"middle\":%d, "
                             "\"misc\":%d "
                             "\"parent\":%d "
                             "\"right\":%d \n",
                             this->index,
                             this->left,
                             this->middle,
                             this->misc,
                             this->parent,
                             this->right
            );
            if (this->pObj) {
                pQueryInfo = obj_getVtbl(this->pObj)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              this->pObj,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(this->pObj);
                        if (pWrkStr) {
                            AStr_AppendA(pStr, "\t\"object\": ");
                            AStr_Append(pStr, pWrkStr);
                            obj_Release(pWrkStr);
                            pWrkStr = OBJ_NIL;
                            AStr_AppendA(pStr, "\n");
                        }
                    }
                }
            }
            if (this->pArray) {
                pQueryInfo = obj_getVtbl(this->pArray)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              this->pArray,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(this->pArray);
                        if (pWrkStr) {
                            AStr_AppendA(pStr, "\t\"array\": ");
                            AStr_Append(pStr, pWrkStr);
                            obj_Release(pWrkStr);
                            pWrkStr = OBJ_NIL;
                            AStr_AppendA(pStr, "\n");
                        }
                    }
                }
            }

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

