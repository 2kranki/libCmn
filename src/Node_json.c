// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Node_json.c
 *
 *	Generated 02/24/2020 08:50:49
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
#include    <Node_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec_internal.h>
#include    <JsonIn.h>
#include    <JsonOut.h>
#include    <Name_internal.h>
#include    <NodeBT_internal.h>
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
    ERESULT     Node_ParseJsonFields (
        JSONIN_DATA   *pParser,
        NODE_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint16_t        u16 = 0;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        (void)JsonIn_FindI32NodeInHashA(pParser, "class", &pObject->cls);
        (void)JsonIn_FindI32NodeInHashA(pParser, "type", &pObject->type);
        (void)JsonIn_FindU32NodeInHashA(pParser, "unique", &pObject->unique);
        (void)JsonIn_FindU32NodeInHashA(pParser, "misc", &pObject->misc);
        u16 = 0;
        (void)JsonIn_FindU16NodeInHashA(pParser, "misc1", &u16);
        Node_setMisc1(pObject, u16);
        u16 = 0;
        (void)JsonIn_FindU16NodeInHashA(pParser, "misc2", &u16);
        Node_setMisc2(pObject, u16);

        eRc = JsonIn_SubObjectInHash(pParser, "name");
        if (ERESULT_FAILED(eRc)) {
            //TODO: Handle error.
        } else {
            pObject->pName = Name_ParseJsonObject(pParser);
            if (OBJ_NIL == pObject->pName) {
                //TODO: Handle error.
            }
            JsonIn_SubObjectEnd(pParser);
        }

        eRc = JsonIn_SubObjectInHash(pParser, "data");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObject->pData = JsonIn_ParseObject(pParser);
            JsonIn_SubObjectEnd(pParser);
        }

        eRc = JsonIn_SubObjectInHash(pParser, "other");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObject->pOther = JsonIn_ParseObject(pParser);
            JsonIn_SubObjectEnd(pParser);
        }

        eRc = JsonIn_SubObjectInHash(pParser, "extra");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObject->pExtra = JsonIn_ParseObject(pParser);
            JsonIn_SubObjectEnd(pParser);
        }

        eRc = JsonIn_SubObjectInHash(pParser, "properties");
        if (ERESULT_FAILED(eRc)) {
            ;
        }
        else {
            pObject->pProperties = NodeBT_ParseJsonObject(pParser);
            JsonIn_SubObjectEnd(pParser);
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
    NODE_DATA * Node_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Node_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Node_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Node_ParseJsonFields(pParser, pObject);

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
    

    NODE_DATA *   Node_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        NODE_DATA       *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Node_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NODE_DATA * Node_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NODE_DATA       *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = Node_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Node_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Node_ToJson (
        NODE_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !Node_Validate(this) ) {
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
     
            eRc = Node_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    ERESULT         Node_ToJsonFields (
        NODE_DATA     *this,
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

        JsonOut_Append_i32("class", this->cls, pStr);
        JsonOut_Append_i32("type", this->type, pStr);
        JsonOut_Append_u32("unique", this->unique, pStr);
        JsonOut_Append_u32("misc", this->misc, pStr);
        JsonOut_Append_u16("misc1", Node_getMisc1(this), pStr);
        JsonOut_Append_u16("misc2", Node_getMisc2(this), pStr);
        JsonOut_Append_Object("name", this->pName, pStr);
        if (this->pData) {
            JsonOut_Append_Object("data", this->pData, pStr);
        }
        if (this->pOther) {
            JsonOut_Append_Object("other", this->pOther, pStr);
        }
        if (this->pExtra) {
            JsonOut_Append_Object("extra", this->pExtra, pStr);
        }
        if (this->pProperties) {
            JsonOut_Append_Object("properties", this->pProperties, pStr);
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

