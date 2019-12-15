// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   value.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on August 27, 2017
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
#include    <value_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dec_internal.h>
#include    <hex_internal.h>
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <utf8_internal.h>




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
    VALUE_DATA *    value_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        VALUE_DATA      *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint16_t        type;
        //OBJ_ID          pObj;
        int64_t         integer;
        int64_t         intIn;

        pInfo = obj_getInfo(value_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        pObject = value_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }

        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "user", &intIn);
        pObject->user = (uint32_t)intIn;
        
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "type", &intIn);
        type = (uint16_t)intIn;
        pObject->type = type;
        
        switch (type) {

            case VALUE_TYPE_FLOAT:           // 32-bit Float
           case VALUE_TYPE_DOUBLE:          // 64-bit Float
                goto exit00;
                break;
                
           case VALUE_TYPE_INT8:            // int8_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.i8 = (int8_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_INT16:           // int16_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.i16 = (int16_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_INT32:           // int32_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.i32 = (int32_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_INT64:           // int64_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.i64 = (int64_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_UINT8:           // int8_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.u8 = (uint8_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_UINT16:          // int16_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.u16 = (uint16_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_UINT32:          // int32_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.u32 = (uint32_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_UINT64:          // int64_t
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->value.u64 = (uint64_t)integer;
                jsonIn_SubobjectEnd(pParser);
                break;
                
            case VALUE_TYPE_OBJECT:
                //TODO:  Look in value class object to see if pObjCatalog has
                // a pointer.  If so, use it to restore the object.
                goto exit00;
                break;
                
            case VALUE_TYPE_DATA:
            case VALUE_TYPE_DATA_FREE:
                pObject->type = VALUE_TYPE_DATA_FREE;
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                pObject->value.data.pData = hex_ParseObject(
                                                            pParser,
                                                            &pObject->value.data.length
                                            );
                jsonIn_SubobjectEnd(pParser);
                break;
                
            default:
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
    

    VALUE_DATA *    value_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        VALUE_DATA      *pObject = OBJ_NIL;
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = value_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    VALUE_DATA *    value_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        VALUE_DATA      *pValue = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            if (pStr) {
                pValue = value_NewFromJSONString(pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pValue;
    }
    
    
    
    ASTR_DATA *     value_ToJson(
        VALUE_DATA      *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ASTR_DATA       *pWrk;
        //char            *pChr;
        //char            chrs[12];
        ASTR_DATA *     (*pToJSON)(OBJ_ID);
        OBJ_IUNKNOWN    *pVtbl;
        
#ifdef NDEBUG
#else
        if( !value_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        // We can't convert any object that doesn't support "ToJson".
        if (this->type == VALUE_TYPE_OBJECT) {
            if (this->value.pObject) {
                pVtbl = obj_getVtbl(this->value.pObject);
                if (pVtbl) {
                    pToJSON =   pVtbl->pQueryInfo(
                                            this->value.pObject,
                                            OBJ_QUERYINFO_TYPE_METHOD,
                                            "ToJson"
                                );
                    if (pToJSON == NULL) {
                        return OBJ_NIL;
                    }
                }
                else {
                    return OBJ_NIL;
                }
            }
            else {
                return OBJ_NIL;
            }
        }
        
        pStr = AStr_New();
        AStr_AppendPrint(
                         pStr,
                         "{ \"objectType\":\"%s\", \"user\":%d",
                         pInfo->pClassName,
                         this->user
        );
        
        switch (this->type) {
                
            case VALUE_TYPE_INT8:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_INT8*/, \"data\":",
                                 VALUE_TYPE_INT8
                );
                pWrk = dec_UInt64ToJSON(this->value.i8);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
           case VALUE_TYPE_INT16:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_INT16*/, \"data\":",
                                 VALUE_TYPE_INT16
                );
                pWrk = dec_UInt64ToJSON(this->value.i16);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_INT32:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_INT32*/, \"data\":",
                                 VALUE_TYPE_INT32
                );
                pWrk = dec_UInt64ToJSON(this->value.i32);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_INT64:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_INT64*/, \"data\":",
                                 VALUE_TYPE_INT64
                );
                pWrk = dec_UInt64ToJSON(this->value.i64);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_UINT8:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_UINT8*/, \"data\":",
                                 VALUE_TYPE_UINT8
                                 );
                pWrk = dec_UInt64ToJSON(this->value.u8);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_UINT16:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_UINT16*/, \"data\":",
                                 VALUE_TYPE_UINT16
                );
                pWrk = dec_UInt64ToJSON(this->value.u16);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_UINT32:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_UINT32*/, \"data\":",
                                 VALUE_TYPE_UINT32
                );
                pWrk = dec_UInt64ToJSON(this->value.u32);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_UINT64:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_UINT64*/, \"data\":",
                                 VALUE_TYPE_UINT64
                );
                pWrk = dec_UInt64ToJSON(this->value.u64);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
                break;
                
            case VALUE_TYPE_OBJECT:
                AStr_AppendPrint(
                             pStr,
                             ", \"type\":%d /*VALUE_TYPE_OBJECT*/, \"data\":",
                             VALUE_TYPE_OBJECT
                );
                if (this->value.pObject) {
                    pVtbl = obj_getVtbl(this->value.pObject);
                    if (pVtbl) {
                        pToJSON =   pVtbl->pQueryInfo(
                                                    this->value.pObject,
                                                    OBJ_QUERYINFO_TYPE_METHOD,
                                                    "ToJson"
                                    );
                        if (pToJSON) {
                            pWrk = (*pToJSON)(this->value.pObject);
                            if (pWrk) {
                                AStr_Append(pStr, pWrk);
                                obj_Release(pWrk);
                                pWrk = OBJ_NIL;
                            }
                        }
                    }
                }
                else {
                    AStr_AppendA(pStr, "null");
                }
                break;
                
            case VALUE_TYPE_DATA:
            case VALUE_TYPE_DATA_FREE:
                AStr_AppendPrint(
                             pStr,
                             ", \"type\":%d /*VALUE_TYPE_DATA_FREE*/, \"data\":",
                             VALUE_TYPE_DATA_FREE
                );
                pWrk = hex_DataToJSON(this->value.data.length, this->value.data.pData);
                AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
                break;
                
            default:
                obj_Release(pStr);
                pStr = OBJ_NIL;
        }
        
        if (pStr)
            AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

