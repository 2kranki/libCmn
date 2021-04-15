// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   U8VlArray_json.c
 *
 *	Generated 03/20/2020 11:56:58
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
#include    <U8VlArray_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
#include    <hex_internal.h>
#include    <JsonIn.h>
#include    <JsonOut.h>
#include    <Node.h>
#include    <NodeHash.h>
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
    ERESULT     U8VlArray_ParseJsonFields (
        JSONIN_DATA     *pParser,
        U8VLARRAY_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        uint32_t        len = 0;
        uint16_t        max = 0;

        (void)JsonIn_FindU16NodeInHashA(pParser, "max", &max);
        eRc = JsonIn_SubObjectInHash(pParser, "data");
        if (ERESULT_OK(eRc)) {
            pObject->pData = hex_ParseObject(pParser, &len);
            JsonIn_SubObjectEnd(pParser);
            if (pObject->pData) {
                if (len == max) {
                    obj_FlagOn(pObject, U8VLARRAY_FLAG_ALLOC);
                } else {
                    mem_Free(pObject->pData);
                    pObject->pData = NULL;
                }
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
    U8VLARRAY_DATA * U8VlArray_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        U8VLARRAY_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(U8VlArray_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = U8VlArray_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  U8VlArray_ParseJsonFields(pParser, pObject);

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
    

    U8VLARRAY_DATA *   U8VlArray_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        U8VLARRAY_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = U8VlArray_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    U8VLARRAY_DATA * U8VlArray_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        U8VLARRAY_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = U8VlArray_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = U8VlArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U8VlArray_ToJson (
        U8VLARRAY_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !U8VlArray_Validate(this) ) {
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
     
            eRc = U8VlArray_ToJsonFields(this, pStr);      

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
    ERESULT         U8VlArray_ToJsonFields (
        U8VLARRAY_DATA     *this,
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

        if (this->pData) {
            ASTR_DATA       *pWrk;
            JsonOut_Append_u16("max", this->pData[0], pStr);
            JsonOut_Append_u16("len", this->pData[1], pStr);
            pWrk = hex_DataToJSON(this->pData[0], this->pData);
            if (pWrk) {
                AStr_AppendA(pStr, "\t\"data\":");
                AStr_Append(pStr, pWrk);
                obj_Release(pWrk);
                pWrk = OBJ_NIL;

            }
        }

#ifdef XYZZZY
        JsonOut_Append_i32("fileIndex", this->fileIndex, pStr);
        JsonOut_Append_i64("offset", this->offset, pStr);
        JsonOut_Append_u32("lineNo", this->lineNo, pStr);
        JsonOut_Append_utf8("name", pEntry->pName, pStr);
        JsonOut_Append_Object("errorStr", this->pErrorStr, pStr);
        JsonOut_Append_String("data", this->pAStr, pStr);
        JsonOut_Append_StringA("data", this->pStrA, pStr);
        JsonOut_Append_StringW32("data", this->pStrW32, pStr);
#endif

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

