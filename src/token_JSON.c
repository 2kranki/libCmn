// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   token.c
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
#include    <token_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dec_internal.h>
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <srcLoc_internal.h>
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
     @warning   Returned null object must be released.
     */
    TOKEN_DATA *    token_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        cls = 0;
        uint32_t        type = 0;
        uint16_t        misc = 0;
        OBJ_ID          pObj;
        uint8_t         *pUtf8;
        int64_t         integer;
        SRCLOC_DATA     *pSrc = OBJ_NIL;
        
        pInfo = obj_getInfo(token_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObj = jsonIn_SubobjectInHash(pParser, "loc");
        pSrc = srcLoc_ParseObject(pParser);
        jsonIn_SubobjectEnd(pParser);
        if (OBJ_NIL == pSrc) {
            goto exit00;
        }

        cls  = (uint32_t)jsonIn_FindIntegerNodeInHash(pParser, "class");
        misc = (uint16_t)jsonIn_FindIntegerNodeInHash(pParser, "misc");
        type = (uint32_t)jsonIn_FindIntegerNodeInHash(pParser, "type");

        switch (type) {
                
            case TOKEN_TYPE_INTEGER:
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject = token_NewInteger(srcLoc_getSrc(pSrc), cls, integer);
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                pUtf8 = utf8_ParseObject(pParser, NULL);
                jsonIn_SubobjectEnd(pParser);
                if (pUtf8) {
                    pObject = token_NewStrA(srcLoc_getSrc(pSrc), cls, (char *)pUtf8);
                    mem_Free(pUtf8);
                    pUtf8 = NULL;
                }
                break;
                
            case TOKEN_TYPE_W32CHAR:
                pObj = jsonIn_SubobjectInHash(pParser, "data");
                integer = dec_ParseObject(pParser);
                pObject = token_NewCharW32(srcLoc_getSrc(pSrc), cls, (W32CHR_T)integer);
                jsonIn_SubobjectEnd(pParser);
                if (OBJ_NIL == pObject) {
                    goto exit00;
                }
                break;
                
            default:
                break;
        }
        
        if (pObject) {
            token_setMisc(pObject, misc);
        }
        
        // Return to caller.
    exit00:
        if (pSrc) {
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        return pObject;
    }
    
    
    

    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    TOKEN_DATA *     token_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        TOKEN_DATA      *pToken = OBJ_NIL;
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pToken = token_ParseObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pToken;
    }
    
    

    TOKEN_DATA *     token_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA      *pToken = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pToken = token_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pToken;
    }
    
    
    
    ASTR_DATA *     token_ToJSON(
        TOKEN_DATA      *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        const
        char            *pConStr;
        ASTR_DATA       *pWrkStr;
        SRCLOC_DATA     *pSrc = OBJ_NIL;

#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr,
                         "{\"objectType\":\"%s\", \"class\":%d, ",
                         pInfo->pClassName,
                         this->data.cls
        );
        pSrc = srcLoc_NewSrcLoc(&this->data.src);
        if (pSrc) {
            pWrkStr = srcLoc_ToJSON(pSrc);
            if (pWrkStr) {
                AStr_AppendPrint(pStr, "\"loc\":%s, ", AStr_getData(pWrkStr));
                obj_Release(pWrkStr);
                pWrkStr = OBJ_NIL;
            }
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        AStr_AppendPrint(pStr, "\"misc\":%d, ", token_getMisc(this));
        
        switch (this->data.type) {
                
            case TOKEN_TYPE_UNKNOWN:
                AStr_AppendPrint(
                                 pStr,
                                 "\"type\":%d /*TOKEN_TYPE_UNKNOWN*/ ",
                                 TOKEN_TYPE_UNKNOWN
                );
                break;
                
            case TOKEN_TYPE_W32CHAR:
                AStr_AppendPrint(
                                 pStr,
                                 "\"type\":%d /*TOKEN_TYPE_W32CHAR*/, \"data\":",
                                 TOKEN_TYPE_W32CHAR
                );
                pWrkStr = dec_UInt64ToJSON(this->data.w32chr[0]);
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
        
        if (pStr)
            AStr_AppendA(pStr, "}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

