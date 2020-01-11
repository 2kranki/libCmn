// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Token_json.c
 *
 *	Generated 01/02/2020 15:58:09
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
#include    <Token_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec_internal.h>
#include    <JsonIn.h>
#include    <node.h>
#include    <NodeHash.h>
#include    <SrcLoc_internal.h>
#include    <szTbl.h>
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
    TOKEN_DATA * Token_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        TOKEN_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        int64_t         intIn;
        SRCLOC_DATA     *pSrc = OBJ_NIL;
        uint32_t        cls = 0;
        uint32_t        type = 0;
        int16_t         misc = 0;
        uint8_t         *pUtf8;
        int64_t         integer;

        pInfo = obj_getInfo(Token_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        eRc = JsonIn_SubObjectInHash(pParser, "loc");
        pSrc = SrcLoc_ParseJsonObject(pParser);
        JsonIn_SubObjectEnd(pParser);
        if (OBJ_NIL == pSrc) {
            goto exit00;
        }

        eRc  = JsonIn_FindIntegerNodeInHashA(pParser, "class", &intIn);
        cls = (uint32_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "misc", &intIn);
        misc = (uint16_t)intIn;
        eRc = JsonIn_FindIntegerNodeInHashA(pParser, "type", &intIn);
        type = (uint32_t)intIn;

        switch (type) {

            case TOKEN_TYPE_INTEGER:
                eRc = JsonIn_SubObjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject = Token_NewInteger(SrcLoc_getSrc(pSrc), cls, integer);
                JsonIn_SubObjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;

            case TOKEN_TYPE_STRTOKEN:
                eRc = JsonIn_SubObjectInHash(pParser, "data");
                pUtf8 = utf8_ParseObject(pParser, NULL);
                JsonIn_SubObjectEnd(pParser);
                if (pUtf8) {
                    pObject = Token_NewStrA(SrcLoc_getSrc(pSrc), cls, (char *)pUtf8);
                    mem_Free(pUtf8);
                    pUtf8 = NULL;
                }
                break;

            case TOKEN_TYPE_W32CHAR:
                eRc = JsonIn_SubObjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject = Token_NewCharW32(SrcLoc_getSrc(pSrc), cls, (W32CHR_T)integer);
                JsonIn_SubObjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;

            default:
                DEBUG_BREAK();
                break;
        }

        // Return to caller.
    exit00:
        obj_Release(pSrc);
        return pObject;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    TOKEN_DATA *   Token_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        TOKEN_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Token_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    TOKEN_DATA * Token_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = Token_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Token_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Token_ToJson(
        TOKEN_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ASTR_DATA       *pWrkStr;
        SRCLOC_DATA     *pSrc = OBJ_NIL;
        W32CHR_T        w32;
        const
        char            *pConStr;

#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            AStr_AppendPrint(pStr,
                             "{\"objectType\":\"%s\", \"class\":%d, ",
                             pInfo->pClassName,
                             this->data.cls
            );
            pSrc = SrcLoc_NewSrcLoc(&this->data.src);
            if (pSrc) {
                pWrkStr = SrcLoc_ToJson(pSrc);
                if (pWrkStr) {
                    AStr_AppendPrint(pStr, "\"loc\":%s, ", AStr_getData(pWrkStr));
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                obj_Release(pSrc);
                pSrc = OBJ_NIL;
            }
            AStr_AppendPrint(pStr, "\"misc\":%d, ", Token_getMisc(this));

            switch (this->data.type) {

                case TOKEN_TYPE_UNKNOWN:
                    AStr_AppendPrint(
                                     pStr,
                                     "\"type\":%d /*TOKEN_TYPE_UNKNOWN*/ ",
                                     TOKEN_TYPE_UNKNOWN
                    );
                    break;

                case TOKEN_TYPE_CHAR:
                case TOKEN_TYPE_W32CHAR:
                    w32 = Token_getChrW32(this);
                    AStr_AppendPrint(
                                     pStr,
                                     "\"type\":%d /*TOKEN_TYPE_W32CHAR*/, \"data\":",
                                     TOKEN_TYPE_W32CHAR
                    );
                    pWrkStr = dec_UInt64ToJSON(w32);
                    if (pWrkStr) {
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                    }
                    break;

                case TOKEN_TYPE_INTEGER:
                    AStr_AppendPrint(
                                     pStr,
                                     "\"type\":%d /*TOKEN_TYPE_INTEGER*/, \"data\":",
                                     TOKEN_TYPE_INTEGER
                    );
                    pWrkStr = dec_UInt64ToJSON(this->data.integer);
                    if (pWrkStr) {
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                    }
                    break;

                case TOKEN_TYPE_STRTOKEN:
                    pConStr = szTbl_TokenToString(szTbl_Shared(), this->data.strToken);
                    if (pConStr) {
                        AStr_AppendPrint(
                                     pStr,
                                     "\"type\":%d /*TOKEN_TYPE_STRTOKEN*/, \"data\":",
                                     TOKEN_TYPE_STRTOKEN
                        );
                        pWrkStr = utf8_DataToJSON(pConStr);
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                    }
                    else {
                        DEBUG_BREAK();
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                    break;

                default:
                    DEBUG_BREAK();
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                    break;

            }

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

