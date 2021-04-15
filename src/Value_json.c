// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Value_json.c
 *
 *	Generated 03/06/2020 15:29:02
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
#include    <Value_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
#include    <hex_internal.h>
#include    <JsonIn.h>
#include    <JsonOut.h>
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
    ERESULT     Value_ParseJsonFields (
        JSONIN_DATA     *pParser,
        VALUE_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        //uint32_t        len;

        (void)JsonIn_FindU16NodeInHashA(pParser, "misc16", &pObject->misc16);
        (void)JsonIn_FindU16NodeInHashA(pParser, "type", &pObject->type);
        (void)JsonIn_FindU32NodeInHashA(pParser, "user", &pObject->user);

        switch (pObject->type) {

            case VALUE_TYPE_DOUBLE:         // 64-bit Float
                JsonIn_FindFloatNodeInHashA(pParser, "data", &pObject->value.flt);
                break;

           case VALUE_TYPE_INT8:            // int8_t
                (void)JsonIn_FindI8NodeInHashA(pParser, "data", &pObject->value.i8);
                break;

            case VALUE_TYPE_INT16:          // int16_t
                (void)JsonIn_FindI16NodeInHashA(pParser, "data", &pObject->value.i16);
                break;

            case VALUE_TYPE_INT32:          // int32_t
                (void)JsonIn_FindI32NodeInHashA(pParser, "data", &pObject->value.i32);
                break;

            case VALUE_TYPE_INT64:          // int64_t
                (void)JsonIn_FindI64NodeInHashA(pParser, "data", &pObject->value.i64);
                break;

            case VALUE_TYPE_UINT8:          // int8_t
                (void)JsonIn_FindU8NodeInHashA(pParser, "data", &pObject->value.u8);
                break;

            case VALUE_TYPE_UINT16:         // int16_t
                (void)JsonIn_FindU16NodeInHashA(pParser, "data", &pObject->value.u16);
                break;

            case VALUE_TYPE_UINT32:         // int32_t
                (void)JsonIn_FindU32NodeInHashA(pParser, "data", &pObject->value.u32);
                break;

            case VALUE_TYPE_UINT64:         // int64_t
                (void)JsonIn_FindU64NodeInHashA(pParser, "data", &pObject->value.u64);
                break;

            case VALUE_TYPE_OBJECT:
                //TODO:  Use JsonIn_ParseObject();
                goto exit00;
                break;

            case VALUE_TYPE_DATA:
            case VALUE_TYPE_DATA_FREE:
                pObject->type = VALUE_TYPE_DATA_FREE;
                eRc = JsonIn_SubObjectInHash(pParser, "data");
                pObject->value.data.pData = hex_ParseObject(
                                                            pParser,
                                                            &pObject->value.data.length
                                            );
                JsonIn_SubObjectEnd(pParser);
                break;

            default:
                goto exit00;
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
    VALUE_DATA * Value_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        VALUE_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Value_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Value_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Value_ParseJsonFields(pParser, pObject);

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
    

    VALUE_DATA *   Value_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        VALUE_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Value_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    VALUE_DATA * Value_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        VALUE_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = Value_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Value_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Value_ToJson (
        VALUE_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !Value_Validate(this) ) {
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
     
            eRc = Value_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    ERESULT         Value_ToJsonFields (
        VALUE_DATA     *this,
        ASTR_DATA       *pStr
    )
    {
        ASTR_DATA *     (*pToJson)(
            OBJ_ID          objId
        );
        OBJ_IUNKNOWN    *pVtbl;
        ASTR_DATA       *pWrk;

        JsonOut_Append_u16("misc16", this->misc16, pStr);
        JsonOut_Append_u32("user", this->user, pStr);

        switch (this->type) {

            case VALUE_TYPE_DOUBLE:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_DOUBLE*/, \"data\":",
                                 VALUE_TYPE_DOUBLE
                );
                AStr_AppendPrint(pStr, "%le", this->value.flt);
                break;

            case VALUE_TYPE_INT8:
                AStr_AppendPrint(
                                 pStr,
                                 ", \"type\":%d /*VALUE_TYPE_INT8*/, \"data\":",
                                 VALUE_TYPE_INT8
                );
                pWrk = dec_UInt64ToJson(this->value.i8);
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
                pWrk = dec_UInt64ToJson(this->value.i16);
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
                pWrk = dec_UInt64ToJson(this->value.i32);
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
                pWrk = dec_UInt64ToJson(this->value.i64);
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
                pWrk = dec_UInt64ToJson(this->value.u8);
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
                pWrk = dec_UInt64ToJson(this->value.u16);
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
                pWrk = dec_UInt64ToJson(this->value.u32);
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
                pWrk = dec_UInt64ToJson(this->value.u64);
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
                        pToJson =   pVtbl->pQueryInfo(
                                                    this->value.pObject,
                                                    OBJ_QUERYINFO_TYPE_METHOD,
                                                    "ToJson"
                                    );
                        if (pToJson) {
                            pWrk = (*pToJson)(this->value.pObject);
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

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

