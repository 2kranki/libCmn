// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Name_json.c
 *
 *	Generated 01/11/2020 10:01:40
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
#include    <Name_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec_internal.h>
#include    <JsonIn.h>
#include    <node.h>
#include    <NodeHash.h>
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
    NAME_DATA * Name_ParseJsonObject(
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

        pInfo = obj_getInfo(Name_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "type", &intIn);
        type = (uint32_t)intIn;

        switch (type) {

            case NAME_TYPE_ASTR:
                eRc = JsonIn_SubObjectInHash(pParser, "data");
                pWrk = AStr_ParseJsonObject(pParser);
                pObject = Name_NewAStr(pWrk);
                obj_Release(pWrk);
                JsonIn_SubObjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;

            case NAME_TYPE_INTEGER:
                eRc = JsonIn_SubObjectInHash(pParser, "data");
                integer = dec_ParseJsonObject(pParser);
                pObject = Name_NewInt(integer);
                JsonIn_SubObjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;

            case NAME_TYPE_UTF8:
                eRc = JsonIn_SubObjectInHash(pParser, "data");
                pUtf8 = utf8_ParseJsonObject(pParser, NULL);
                JsonIn_SubObjectEnd(pParser);
                if (pUtf8) {
                    pObject = Name_New();
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
    

    NAME_DATA *   Name_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NAME_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Name_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NAME_DATA * Name_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = Name_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Name_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Name_ToJson(
        NAME_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ASTR_DATA       *pWrkStr;

#ifdef NDEBUG
#else
        if( !Name_Validate(this) ) {
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
                    pWrkStr = dec_UInt64ToJson(this->integer);
                    if (pWrkStr) {
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                    }
                    break;

                case NAME_TYPE_ASTR:
                    AStr_AppendPrint(
                                 pStr,
                                 "\"type\":%u /*NAME_TYPE_ASTR*/, \"data\":",
                                 NAME_TYPE_ASTR
                     );
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
                    pWrkStr = utf8_DataToJson(this->pChrs);
                    if (pWrkStr) {
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                    }
                    break;

            }

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

