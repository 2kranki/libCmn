// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Node_json.c
 *
 *	Generated 01/12/2020 21:04:57
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
#include    <Node_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
#include    <JsonIn.h>
#include    <Name_internal.h>
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
    ERESULT     Node_ParseJsonFields(
        JSONIN_DATA     *pParser,
        NODE_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        OBJ_INFO        *pInfo;
        int64_t         intIn;
        uint32_t        uint32 = 0;
        int32_t         int32 = 0;
        //ASTR_DATA       *pWrk;
        NAME_DATA       *pName = OBJ_NIL;
        OBJ_ID          pObj = OBJ_NIL;

        pInfo = obj_getInfo(Node_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

       eRc = JsonIn_SubObjectInHash(pParser, "name");
       if (ERESULT_FAILED(eRc)) {
           pName = Name_ParseJsonObject(pParser);
           JsonIn_SubObjectEnd(pParser);
           if (pName) {
               Node_setProperties(pObject, pObj);
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
       Node_setClass(pObject, uint32);
       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "type", &intIn);
       int32   = (int32_t)intIn;
       Node_setType(pObject, int32);
       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc", &intIn);
       uint32   = (uint32_t)intIn;
       Node_setMisc(pObject, uint32);
       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc1", &intIn);
       uint32   = (uint32_t)intIn;
       Node_setMisc1(pObject, uint32);
       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc2", &intIn);
       uint32   = (uint32_t)intIn;
       Node_setMisc2(pObject, uint32);

       eRc = JsonIn_SubObjectInHash(pParser, "data");
       if (ERESULT_FAILED(eRc)) {
           ;
       }
       else {
           pObj = JsonIn_ParseObject(pParser);
           JsonIn_SubObjectEnd(pParser);
           if (pObj) {
               Node_setData(pObject, pObj);
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
               Node_setOther(pObject, pObj);
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
               Node_setExtra(pObject, pObj);
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
               Node_setProperties(pObject, pObj);
               obj_Release(pObj);
               pObj = OBJ_NIL;
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
    NODE_DATA * Node_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODE_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Node_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Node_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Node_ParseJsonFields(pParser, pObject);

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
    

    NODE_DATA *   Node_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODE_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Node_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NODE_DATA * Node_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODE_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = Node_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Node_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Node_ToJson(
        NODE_DATA   *this
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
        if( !Node_Validate(this) ) {
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
                             "\"class\":%d, "
                             "\"type\":%d, "
                             "\"unique\":%d, "
                             "\"misc\":%d "
                             "\"misc1\":%d "
                             "\"misc2\":%d \n",
                             this->cls,
                             this->type,
                             this->unique,
                             this->misc,
                             Node_getMisc1(this),
                             Node_getMisc2(this)
            );

            AStr_AppendA(pStr, "}\n");
        }

        if (this->pName) {
            pWrkStr = Name_ToJson(this->pName);
            AStr_AppendA(pStr, "\t\"name\": ");
            AStr_Append(pStr, pWrkStr);\
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
            AStr_AppendA(pStr, "\n");
        }

        if (this->pData) {
            pQueryInfo = obj_getVtbl(this->pData)->pQueryInfo;
            if (pQueryInfo) {
                pToJson =   (*pQueryInfo)(
                                          this->pData,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJson) {
                    pWrkStr = (*pToJson)(this->pData);
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
                pToJson =   (*pQueryInfo)(
                                          this->pOther,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJson) {
                    pWrkStr = (*pToJson)(this->pOther);
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
                pToJson =   (*pQueryInfo)(
                                          this->pExtra,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJson) {
                    pWrkStr = (*pToJson)(this->pExtra);
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
                pToJson =   (*pQueryInfo)(
                                          this->pProperties,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                          );
                if (pToJson) {
                    pWrkStr = (*pToJson)(this->pProperties);
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

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

