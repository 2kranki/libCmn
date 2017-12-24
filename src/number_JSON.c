// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   number_JSON.c
 *
 * Created on 12/19/2017 from value_JSON
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
#include    <number_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dec_internal.h>
#include    <hex.h>
#include    <jsonIn.h>
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
     @warning   Returned object must be released.
     */
    NUMBER_DATA *   number_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NUMBER_DATA     *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint16_t        type;               // See NUMBER_TYPE;
        OBJ_ID          pObj;
        int64_t         integer;

        pInfo = obj_getInfo(number_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        type = (uint16_t)jsonIn_FindIntegerNodeInHash(pParser, "type");
        
        pObject = number_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        switch (type) {
#if defined(__MACOSX_ENV__) || defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
            case NUMBER_TYPE_FLOAT:          // Float or Double
                obj_Release(pObject);
                pObject = OBJ_NIL;
                break;
#endif
 
            case NUMBER_TYPE_INT16:          // int16_t
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->i16 = (int16_t)integer;
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;

            case NUMBER_TYPE_INT32:          // int32_t
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->i32 = (int32_t)integer;
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            case NUMBER_TYPE_INT64:          // int64_t
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->i64 = (int64_t)integer;
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            case NUMBER_TYPE_UINT16:         // uint16_t
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->u16 = (uint16_t)integer;
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            case NUMBER_TYPE_UINT32:         // uint32_t
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->u32 = (uint32_t)integer;
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            case NUMBER_TYPE_UINT64:         // uint64_t
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject->u64 = (uint64_t)integer;
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            //case NUMBER_TYPE_INT128:         // int128_t
            //case NUMBER_TYPE_UINT128:        // uint128_t

            default:
                obj_Release(pObject);
                pObject = OBJ_NIL;
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
    

    NUMBER_DATA *   number_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NUMBER_DATA     *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        
        pInfo = obj_getInfo(number_Class());
        

        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = number_ParseObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NUMBER_DATA *   number_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NUMBER_DATA     *pValue = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pValue = number_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pValue;
    }
    
    
    
    ASTR_DATA *     number_ToJSON(
        NUMBER_DATA     *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ASTR_DATA       *pWrkStr;

#ifdef NDEBUG
#else
        if( !number_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr, "{\"objectType\":\"%s\"", pInfo->pClassName);
        
        switch (this->type) {
                
            case NUMBER_TYPE_INT16:
                AStr_AppendPrint(pStr, ", \"type\":%d /*NUMBER_TYPE_INT16*/, \"data\":",
                                        NUMBER_TYPE_INT16);
                pWrkStr = dec_UInt64ToJSON(this->i16);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
            case NUMBER_TYPE_INT32:
                AStr_AppendPrint(pStr, ", \"type\":%d /*NUMBER_TYPE_INT32*/, \"data\":",
                                        NUMBER_TYPE_INT32);
                pWrkStr = dec_UInt64ToJSON(this->i32);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
            case NUMBER_TYPE_INT64:
                AStr_AppendPrint(pStr, ", \"type\":%d /*NUMBER_TYPE_INT64*/, \"data\":",
                                        NUMBER_TYPE_INT64);
                pWrkStr = dec_UInt64ToJSON(this->i64);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
            case NUMBER_TYPE_UINT16:
                AStr_AppendPrint(pStr, ", \"type\":%d /*NUMBER_TYPE_UINT16*/, \"data\":",
                                        NUMBER_TYPE_UINT16);
                pWrkStr = dec_UInt64ToJSON(this->u16);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
            case NUMBER_TYPE_UINT32:
                AStr_AppendPrint(pStr, ", \"type\":%d /*NUMBER_TYPE_UINT32*/, \"data\":",
                                        NUMBER_TYPE_UINT32);
                pWrkStr = dec_UInt64ToJSON(this->u32);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
            case NUMBER_TYPE_UINT64:
                AStr_AppendPrint(pStr, ", \"type\":%d /*NUMBER_TYPE_UINT64*/, \"data\":",
                                        NUMBER_TYPE_UINT64);
                pWrkStr = dec_UInt64ToJSON(this->u64);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
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

