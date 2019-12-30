// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   name_json.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on December 30, 2014
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
#include    <name_internal.h>
#include    <AStr_internal.h>
#include    <token_internal.h>
#include    <utf8_internal.h>
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
     @warning   Returned null object must be released.
     */
    NAME_DATA *     name_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NAME_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        type = 0;
        ASTR_DATA       *pWrk;
        uint8_t         *pUtf8;
        int64_t         integer;
        int64_t         intIn;

        pInfo = obj_getInfo(name_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "type", &intIn);
        type = (uint32_t)intIn;

        switch (type) {

            case NAME_TYPE_ASTR:
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                pWrk = AStr_ParseJsonObject(pParser);
                pObject = name_NewAStr(pWrk);
                obj_Release(pWrk);
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            case NAME_TYPE_INTEGER:
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject = name_NewInt(integer);
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;

            case NAME_TYPE_UTF8:
                eRc = jsonIn_SubobjectInHash(pParser, "data");
                pUtf8 = utf8_ParseObject(pParser, NULL);
                jsonIn_SubobjectEnd(pParser);
                if (pUtf8) {
                    pObject = name_Alloc();
                    pObject = name_Init(pObject);
                    if (pObject) {
                        pObject->type = NAME_TYPE_UTF8;
                        pObject->pChrs = (void *)pUtf8;
                        pUtf8 = NULL;
                    }
                }
                
                break;

            default:
                break;
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
    

    NAME_DATA *     name_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NAME_DATA       *pObject = OBJ_NIL;

        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = name_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NAME_DATA *     name_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pName = name_NewFromJsonString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pName;
    }
    
    
    
    ASTR_DATA *     name_ToJson(
        NAME_DATA       *this
    )
    {
        char            str[1024];
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !name_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr == OBJ_NIL) {
            //obj_Release(pWrkStr);
            return OBJ_NIL;
        }
        AStr_AppendA(pStr, "{\"objectType\":\"");
        AStr_AppendA(pStr, pInfo->pClassName);
        AStr_AppendA(pStr, "\", ");
        //FIXME: AStr_Append(pStr, pWrkStr);
        
        switch (this->type) {
                
            case NAME_TYPE_UNKNOWN:
                AStr_AppendPrint(
                             pStr,
                             "\"type\":%u /*NAME_TYPE_UNKNOWN*/ ",
                             NAME_TYPE_UNKNOWN
                 );
                break;
                
            case NAME_TYPE_INTEGER:
                AStr_AppendPrint(
                             pStr,
                             "\"type\":%u /*NAME_TYPE_INTEGER*/, \"data\":",
                             NAME_TYPE_INTEGER
                 );
                pWrkStr = dec_UInt64ToJSON(this->integer);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
            case NAME_TYPE_ASTR:
                AStr_AppendPrint(
                             pStr,
                             "\"type\":%u \"NAME_TYPE_ASTR\", \"data\":",
                             NAME_TYPE_ASTR
                 );
                AStr_AppendA(pStr, str);
                pWrkStr = AStr_ToJson(this->pObj);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
            case NAME_TYPE_UTF8:
            case NAME_TYPE_UTF8_CON:
                AStr_AppendPrint(
                                 pStr,
                                 "\"type\":%u /*NAME_TYPE_UTF8*/, \"data\":",
                                 NAME_TYPE_UTF8
                                 );
                pWrkStr = utf8_DataToJSON(this->pChrs);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                break;
                
        }

        if (pStr)
            AStr_AppendA(pStr, "}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

