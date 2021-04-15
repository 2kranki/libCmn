// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Name_json.c
 *
 *	Generated 02/24/2020 08:50:41
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
#include    <dec.h>
#include    <JsonIn.h>
#include    <JsonOut.h>
#include    <Node.h>
#include    <NodeHash.h>
#include    <utf8_internal.h>




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
    ERESULT     Name_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NAME_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        (void)JsonIn_FindU16NodeInHashA(pParser, "type", &pObject->type);
        (void)JsonIn_FindU32NodeInHashA(pParser, "hash", &pObject->hash);

        switch (pObject->type) {

            case NAME_TYPE_INTEGER:
                (void)JsonIn_FindIntegerNodeInHashA(pParser, "integer", &pObject->integer);
                break;

            case NAME_TYPE_ASTR:
                eRc = JsonIn_SubObjectInHash(pParser, "object");
                if (!ERESULT_FAILED(eRc)) {
                    pObject->pObj = AStr_ParseJsonObject(pParser);
                    JsonIn_SubObjectEnd(pParser);
                }
                break;

            case NAME_TYPE_UTF8:
            case NAME_TYPE_UTF8_CON:
                eRc = JsonIn_SubObjectInHash(pParser, "utf8");
                if (!ERESULT_FAILED(eRc)) {
                    pObject->pChrs = (const char *)utf8_ParseJsonObject(pParser, NULL);
                    JsonIn_SubObjectEnd(pParser);
                }
                pObject->type = NAME_TYPE_UTF8;
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
    NAME_DATA * Name_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NAME_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Name_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Name_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Name_ParseJsonFields(pParser, pObject);

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
    

    NAME_DATA *   Name_NewFromJsonString (
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
    
    

    NAME_DATA * Name_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
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
    ASTR_DATA *     Name_ToJson (
        NAME_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

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
     
            eRc = Name_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    ERESULT         Name_ToJsonFields (
        NAME_DATA       *this,
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
        ASTR_DATA       *pWrkStr;
#endif

        JsonOut_Append_u32("hash", this->hash, pStr);
        JsonOut_Append_u16("type", this->type, pStr);
        switch (this->type) {

            case NAME_TYPE_INTEGER:
                AStr_AppendA(pStr, "\t/* Integer */\n");
                JsonOut_Append_i64("integer", this->integer, pStr);
                break;

            case NAME_TYPE_ASTR:
                AStr_AppendA(pStr, "\t/* AStr */\n");
                JsonOut_Append_Object("object", this->pObj, pStr);
                break;

            case NAME_TYPE_UTF8:
                AStr_AppendA(pStr, "\t/* UTF-8 */\n");
                JsonOut_Append_utf8("utf8", this->pChrs, pStr);
                break;

            case NAME_TYPE_UTF8_CON:
                AStr_AppendA(pStr, "\t/* UTF-8 Constant */\n");
                JsonOut_Append_utf8("utf8", this->pChrs, pStr);
                break;

            default:
                DEBUG_BREAK();
                break;
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

