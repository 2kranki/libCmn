// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeProp_json.c
 *
 *	Generated 04/26/2020 17:31:56
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
#include    <NodeProp_internal.h>
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
    ERESULT     NodeProp_ParseJsonFields (
        JSONIN_DATA     *pParser,
        NODEPROP_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //NODE_DATA       *pNode = OBJ_NIL;
        //NODEARRAY_DATA  *pArray = OBJ_NIL;
        //NODEHASH_DATA   *pHash = OBJ_NIL;
        //uint32_t        i;
        //uint32_t        iMax;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        //uint32_t        len;
        ASTR_DATA       *pStr = OBJ_NIL;

        (void)JsonIn_FindStringNodeInHashA(pParser, "external", &pObject->pExternal);
        obj_Retain(pObject->pExternal);
        (void)JsonIn_FindStringNodeInHashA(pParser, "init", &pObject->pInit);
        obj_Retain(pObject->pInit);
        (void)JsonIn_FindStringNodeInHashA(pParser, "internal", &pObject->pInternal);
        obj_Retain(pObject->pInternal);
        (void)JsonIn_FindStringNodeInHashA(pParser, "long", &pObject->pLong);
        obj_Retain(pObject->pLong);
        (void)JsonIn_FindStringNodeInHashA(pParser, "name", &pObject->pName);
        obj_Retain(pObject->pName);
        (void)JsonIn_FindStringNodeInHashA(pParser, "short", &pObject->pShort);
        obj_Retain(pObject->pShort);
        (void)JsonIn_FindStringNodeInHashA(pParser, "typedef", &pObject->pTypeDef);
        obj_Retain(pObject->pTypeDef);
        (void)JsonIn_FindU8NodeInHashA(pParser, "object", &pObject->fObj);
        (void)JsonIn_FindStringNodeInHashA(pParser, "vis", &pStr);
        if (pStr) {
            if (0 == AStr_CompareA(pStr, "PUBLIC")) {
                pObject->vis = NODEPROP_VIS_PUBLIC;
            }
            else if (0 == AStr_CompareA(pStr, "READ_ONLY")) {
                pObject->vis = NODEPROP_VIS_READ_ONLY;
            }
        }

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
    NODEPROP_DATA * NodeProp_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODEPROP_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(NodeProp_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = NodeProp_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  NodeProp_ParseJsonFields(pParser, pObject);

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
    

    NODEPROP_DATA *   NodeProp_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODEPROP_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            SrcErrors_Print(OBJ_NIL, stderr);
            goto exit00;
        }
        
        pObject = NodeProp_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NODEPROP_DATA * NodeProp_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODEPROP_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = NodeProp_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = NodeProp_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_ToJson (
        NODEPROP_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !NodeProp_Validate(this) ) {
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
     
            eRc = NodeProp_ToJsonFields(this, pStr);      

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
    ERESULT         NodeProp_ToJsonFields (
        NODEPROP_DATA     *this,
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

        if (this->pExternal) {
            JsonOut_Append_StrA("external", AStr_getData(this->pExternal), pStr);
        }
        if (this->pInit) {
            JsonOut_Append_StrA("init", AStr_getData(this->pInit), pStr);
        }
        if (this->pInternal) {
            JsonOut_Append_StrA("internal", AStr_getData(this->pInternal), pStr);
        }
        if (this->pLong) {
            JsonOut_Append_StrA("long", AStr_getData(this->pLong), pStr);
        }
        JsonOut_Append_StrA("name", AStr_getData(this->pName), pStr);
        if (this->pShort) {
            JsonOut_Append_StrA("short", AStr_getData(this->pShort), pStr);
        }
        JsonOut_Append_u8("object", this->fObj, pStr);
        JsonOut_Append_StrA("typedef", AStr_getData(this->pTypeDef), pStr);
        switch (this->vis) {
            case NODEPROP_VIS_PUBLIC:
                JsonOut_Append_StrA("vis", "PUBLIC", pStr);
                break;
            case NODEPROP_VIS_READ_ONLY:
                JsonOut_Append_StrA("vis", "READ_ONLY", pStr);
                break;
        }

#ifdef XYZZZY
        JsonOut_Append_i32("x", this->x, pStr);
        JsonOut_Append_i64("t", this->t, pStr);
        JsonOut_Append_u32("o", this->o, pStr);
        JsonOut_Append_utf8("n", pEntry->pN, pStr);
        JsonOut_Append_Object("e", this->pE, pStr);
        JsonOut_Append_AStr("d", this->pAStr, pStr);
        JsonOut_Append_StringA("d", this->pStrA, pStr);
        JsonOut_Append_StringW32("d", this->pStrW32, pStr);
#endif

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

