// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SqlCol_json.c
 *
 *	Generated 04/25/2020 18:28:59
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
#include    <SqlCol_internal.h>
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
#include    <utf8.h>
#include    <Value_internal.h>




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
    ERESULT     SqlCol_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SQLCOL_DATA     *pObject
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
        ASTR_DATA       *pWrk2 = OBJ_NIL;
        //uint8_t         *pData;
        //uint32_t        len;
        SQLCOL_TYPE_EXPR
                        *pTypeExpr;

        eRc = JsonIn_FindAStrNodeInHashA(pParser, "name", &pWrk);
        if (ERESULT_OK(eRc)) {
            pObject->pName = pWrk;
            //obj_Release(pWrk);
            //pWrk = OBJ_NIL;
        }
        eRc = JsonIn_FindAStrNodeInHashA(pParser, "desc", &pWrk);
        if (ERESULT_OK(eRc)) {
            pObject->pDesc = pWrk;
            //obj_Release(pWrk);
            //pWrk = OBJ_NIL;
        }
        eRc = JsonIn_FindAStrNodeInHashA(pParser, "check_expr", &pWrk);
        if (ERESULT_OK(eRc)) {
            pObject->pCheckExpr = pWrk;
            //obj_Release(pWrk);
            //pWrk = OBJ_NIL;
        }
        eRc = JsonIn_FindAStrNodeInHashA(pParser, "database_name", &pWrk);
        if (ERESULT_OK(eRc)) {
            pObject->pDBName = pWrk;
            //obj_Release(pWrk);
            //pWrk = OBJ_NIL;
        }
        eRc = JsonIn_FindAStrNodeInHashA(pParser, "default_value", &pWrk);
        if (ERESULT_OK(eRc)) {
            pObject->pDefVal = pWrk;
            //obj_Release(pWrk);
            //pWrk = OBJ_NIL;
        }
        eRc = JsonIn_SubObjectInHash(pParser, "value");
        if (ERESULT_OK(eRc)) {
            pObject->pValue = Value_ParseJsonObject(pParser);
            JsonIn_SubObjectEnd(pParser);
        }
        eRc = JsonIn_FindAStrNodeInHashA(pParser, "table_name", &pWrk);
        if (ERESULT_OK(eRc)) {
            pObject->pTableName = pWrk;
            //obj_Release(pWrk);
            //pWrk = OBJ_NIL;
        }
        eRc = JsonIn_FindAStrNodeInHashA(pParser, "type", &pWrk);
        if (ERESULT_OK(eRc)) {
            pWrk2 = AStr_ToUpper(pWrk);
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
            pTypeExpr = SqlCol_FindByName(AStr_getData(pWrk2));
            if (pTypeExpr) {
                pObject->type = pTypeExpr->type;
            } else {
                pObject->type = SQLCOL_TYPE_UNKNOWN;
            }
            obj_Release(pWrk2);
            pWrk2 = OBJ_NIL;
        }
        (void)JsonIn_FindU8NodeInHashA(pParser, "dec", &pObject->decimalPlaces);
        (void)JsonIn_FindU16NodeInHashA(pParser, "colSeq", &pObject->colSeq);
        (void)JsonIn_FindU16NodeInHashA(pParser, "keySeq", &pObject->keySeq);
        (void)JsonIn_FindU32NodeInHashA(pParser, "flags", &pObject->flags);
        (void)JsonIn_FindI32NodeInHashA(pParser, "length", &pObject->length);
        (void)JsonIn_FindI32NodeInHashA(pParser, "lengthMin", &pObject->lengthMin);

#ifdef XYZZZY
        (void)JsonIn_FindU16NodeInHashA(pParser, "type", &pObject->type);
        (void)JsonIn_FindU32NodeInHashA(pParser, "attr", &pObject->attr);
        (void)JsonIn_FindIntegerNodeInHashA(pParser, "fileSize", &pObject->fileSize); //i64

        eRc = JsonIn_FindUtf8NodeInHashA(pParser, "name", &pData, &len);
        eRc = JsonIn_SubObjectInHash(pParser, "errorStr");
        pWrk = AStr_ParseJsonObject(pParser);
        if (pWrk) {
            pObject->pErrorStr = pWrk;
        }
        JsonIn_SubObjectEnd(pParser);
#endif

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
    SQLCOL_DATA * SqlCol_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SQLCOL_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(SqlCol_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = SqlCol_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  SqlCol_ParseJsonFields(pParser, pObject);

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
    

    SQLCOL_DATA *   SqlCol_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        SQLCOL_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            SrcErrors_Print(OBJ_NIL, stderr);
            goto exit00;
        }
        
        pObject = SqlCol_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    SQLCOL_DATA * SqlCol_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SQLCOL_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = SqlCol_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = SqlCol_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_ToJson (
        SQLCOL_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !SqlCol_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
             AStr_AppendPrint(pStr,
                              "{\n\t\"objectType\":\"%s\",\n",
                              pInfo->pClassName
             );

            eRc = SqlCol_ToJsonFields(this, pStr);      

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
    ERESULT         SqlCol_ToJsonFields (
        SQLCOL_DATA     *this,
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
        const
        char            *pWrkStrA;
        SQLCOL_TYPE_EXPR
                        *pTypeExpr;

        JsonOut_Append_AStr("name", this->pName, pStr);
        if (this->pDBName) {
            JsonOut_Append_AStr("database_name", this->pDBName, pStr);
        }
        if (this->pDesc) {
            JsonOut_Append_AStr("desc", this->pDesc, pStr);
        }
        if (this->pCheckExpr) {
            JsonOut_Append_AStr("check_expr", this->pCheckExpr, pStr);
        }
        if (this->pDefVal) {
            JsonOut_Append_AStr("default_value", this->pDefVal, pStr);
        }
        if (this->pTableName) {
            JsonOut_Append_AStr("table_name", this->pTableName, pStr);
        }
        if (this->pValue) {
            JsonOut_Append_Object("value", this->pValue, pStr);
        }
        pTypeExpr = SqlCol_FindByType(this->type);
        if (pTypeExpr) {
            pWrkStrA = pTypeExpr->pNameA;
        } else {
            pWrkStrA = "==> UNKNOWN <==";
        }
        JsonOut_Append_StrA("type", pWrkStrA, pStr);
        JsonOut_Append_u8("dec", this->decimalPlaces, pStr);
        JsonOut_Append_u16("colSeq", this->colSeq, pStr);
        JsonOut_Append_u16("keySeq", this->keySeq, pStr);
        JsonOut_Append_u32("flags", this->flags, pStr);
        JsonOut_Append_i32("length", this->length, pStr);
        JsonOut_Append_i32("lengthMin", this->lengthMin, pStr);

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

