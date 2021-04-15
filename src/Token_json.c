// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Token_json.c
 *
 *  Generated 05/28/13 13:10:01
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
#include    <dec.h>
#include    <JsonIn.h>
#include    <JsonOut.h>
#include    <Node.h>
#include    <NodeHash.h>
#include    <SrcErrors.h>
#include    <SrcLoc_internal.h>
#include    <szTbl.h>
#include    <utf8.h>




#ifdef  __cplusplus
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
    ERESULT     Token_ParseJsonFields (
        JSONIN_DATA     *pParser,
        TOKEN_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //NODE_DATA       *pNode = OBJ_NIL;
        //NODEARRAY_DATA  *pArray = OBJ_NIL;
        //NODEHASH_DATA   *pHash = OBJ_NIL;
        //uint32_t        i;
        //uint32_t        iMax;
        //int64_t         intIn;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //uint8_t         *pData;
        //uint32_t        len;
        SRCLOC_DATA     *pSrc = OBJ_NIL;

        (void)JsonIn_FindU16NodeInHashA(pParser, "len", &pObject->data.len);
        (void)JsonIn_FindI16NodeInHashA(pParser, "cls", &pObject->data.cls);
        (void)JsonIn_FindI16NodeInHashA(pParser, "misc", &pObject->data.misc);
        eRc = JsonIn_SubObjectInHash(pParser, "loc");
        if (ERESULT_OK(eRc)) {
            pSrc = SrcLoc_ParseJsonObject(pParser);
            JsonIn_SubObjectEnd(pParser);
            if (OBJ_NIL == pSrc) {
                DEBUG_BREAK();
                obj_Release(pSrc);
                pSrc = OBJ_NIL;
                return ERESULT_DATA_ERROR;
            }
            memmove(&pObject->data.src, SrcLoc_getSrc(pSrc), sizeof(SRCLOC));
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }


        (void)JsonIn_FindStrNodeInHashA(pParser, "type", &pWrk);
        if (pWrk) {
            pObject->data.type = Token_StringToType(pObject, AStr_getData(pWrk));
        } else {
            DEBUG_BREAK();
            return ERESULT_DATA_ERROR;
        }

        switch (pObject->data.type) {

            case TOKEN_TYPE_INTEGER:
                (void)JsonIn_FindI64NodeInHashA(pParser, "data", &pObject->data.integer);
                break;

            case TOKEN_TYPE_STRTOKEN:
                (void)JsonIn_FindStrNodeInHashA(pParser, "data", &pWrk);
                pObject->data.strToken = szTbl_StringToToken(OBJ_NIL, AStr_getData(pWrk));
                break;

            case TOKEN_TYPE_W32CHAR:
                (void)JsonIn_FindI32NodeInHashA(pParser, "data", &pObject->data.w32chr[0]);
                pObject->data.w32chr[1] = 0;
                break;

            default:
                DEBUG_BREAK();
                break;
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
    TOKEN_DATA * Token_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        TOKEN_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Token_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Token_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Token_ParseJsonFields(pParser, pObject);

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
    

    TOKEN_DATA *   Token_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        TOKEN_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            SrcErrors_Print(OBJ_NIL, stderr);
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
    
    

    TOKEN_DATA * Token_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        TOKEN_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
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
    ASTR_DATA *     Token_ToJson (
        TOKEN_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

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
                              "{ \"objectType\":\"%s\",\n",
                              pInfo->pClassName
             );
     
            eRc = Token_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Token_ToJsonFields (
        TOKEN_DATA     *this,
        ASTR_DATA       *pStr
    )
    {
#ifdef XYZZZY 
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        ASTR_DATA *     (*pToJson)(
            OBJ_ID          objId
        );
#endif
        SRCLOC_DATA     *pSrc = OBJ_NIL;
        ASTR_DATA       *pWrkStr;
        const
        char            *pType;

        JsonOut_Append_u16("len", this->data.len, pStr);
        pType = Token_TypeToString(this, this->data.type);
        if (pType) {
            AStr_AppendPrint(pStr, "\t\"type\":\"%s\",\n", pType);
        }
        pSrc = SrcLoc_NewSrcLoc(&this->data.src);
        if (pSrc) {
            pWrkStr = SrcLoc_ToJson(pSrc);
            if (pWrkStr) {
                AStr_AppendPrint(pStr, "\t\"loc\":%s,\n", AStr_getData(pWrkStr));
                obj_Release(pWrkStr);
                pWrkStr = OBJ_NIL;
            }
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        JsonOut_Append_i16("cls", this->data.cls, pStr);
        JsonOut_Append_i16("misc", this->data.misc, pStr);

        switch (this->data.type) {
            case TOKEN_TYPE_UNKNOWN:
                break;
            case TOKEN_TYPE_CHAR:
            case TOKEN_TYPE_W32CHAR:
                JsonOut_Append_i32("data", this->data.w32chr[0], pStr);
                break;
            case TOKEN_TYPE_INTEGER:
                JsonOut_Append_i64("data", this->data.w32chr[0], pStr);
                break;
            case TOKEN_TYPE_STRTOKEN:
                pType = szTbl_TokenToString(szTbl_Shared(), this->data.strToken);
                if (pType) {
                    AStr_AppendPrint(pStr, "\t\"data\": %s,\n", pType);
                }
                else {
                    DEBUG_BREAK();
                    return ERESULT_DATA_ERROR;
                }
                break;
            default:
                DEBUG_BREAK();
                return ERESULT_DATA_ERROR;
                break;
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef  __cplusplus
}
#endif

