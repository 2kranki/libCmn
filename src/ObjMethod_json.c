// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjMethod_json.c
 *
 *	Generated 12/30/2019 13:30:01
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
#include    <ObjMethod_internal.h>
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
    OBJMETHOD_DATA * ObjMethod_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        OBJMETHOD_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        ASTR_DATA       *pWrk;
        OBJ_ID          pObj;

        pInfo = obj_getInfo(ObjMethod_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = ObjMethod_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc = JsonIn_SubObjectInHash(pParser, "desc");
        pWrk = AStr_ParseJsonObject(pParser);
        if (pWrk) {
            pObject->pDesc = pWrk;
        }
        JsonIn_SubObjectEnd(pParser);

        eRc = JsonIn_SubObjectInHash(pParser, "methodName");
        pWrk = AStr_ParseJsonObject(pParser);
        if (pWrk) {
            pObject->pMethodName = pWrk;
        }
        JsonIn_SubObjectEnd(pParser);

        eRc = JsonIn_SubObjectInHash(pParser, "object");
        pObj = JsonIn_ParseObject(pParser);
        if (pObj) {
            pObject->pObject = pObj;
        }
        JsonIn_SubObjectEnd(pParser);

        eRc = JsonIn_SubObjectInHash(pParser, "objectName");
        pWrk = AStr_ParseJsonObject(pParser);
        if (pWrk) {
            pObject->pObjectName = pWrk;
        }
        JsonIn_SubObjectEnd(pParser);

        eRc = JsonIn_SubObjectInHash(pParser, "other");
        pObj = JsonIn_ParseObject(pParser);
        if (pObj) {
            pObject->pObject = pObj;
        }
        JsonIn_SubObjectEnd(pParser);

        //TODO: Need to translate Object Name to an object or do we
        //      just json the whole object to begin with???
        //      Hmmmm! JsonIn could be used find the object, but ...
        //      We really need to the actual object!

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
    

    OBJMETHOD_DATA *   ObjMethod_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        OBJMETHOD_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = ObjMethod_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    OBJMETHOD_DATA * ObjMethod_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJMETHOD_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = ObjMethod_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = ObjMethod_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjMethod_ToJson(
        OBJMETHOD_DATA   *this
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
        if( !ObjMethod_Validate(this) ) {
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
            
            if (this->pDesc) {
                pQueryInfo = obj_getVtbl(this->pDesc)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              this->pDesc,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(this->pDesc);
                        if (pWrkStr) {
                            AStr_AppendA(pStr, "\t\"desc\": ");
                            AStr_Append(pStr, pWrkStr);
                            obj_Release(pWrkStr);
                            pWrkStr = OBJ_NIL;
                            AStr_AppendA(pStr, "\n");
                        }
                    }
                }
            }
            
            if (this->pMethodName) {
                pQueryInfo = obj_getVtbl(this->pMethodName)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              this->pMethodName,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(this->pMethodName);
                        if (pWrkStr) {
                            AStr_AppendA(pStr, "\t\"methodName\": ");
                            AStr_Append(pStr, pWrkStr);
                            obj_Release(pWrkStr);
                            pWrkStr = OBJ_NIL;
                            AStr_AppendA(pStr, "\n");
                        }
                    }
                }
            }
            
            if (this->pObject) {
                pQueryInfo = obj_getVtbl(this->pObject)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              this->pObject,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(this->pObject);
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

            if (this->pObjectName) {
                pQueryInfo = obj_getVtbl(this->pObjectName)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              this->pObjectName,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(this->pObjectName);
                        if (pWrkStr) {
                            AStr_AppendA(pStr, "\t\"objectName\": ");
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

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

