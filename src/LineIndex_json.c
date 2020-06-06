// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   LineIndex_json.c
 *
 *  Generated 06/04/2020 10:44:19
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
#include    <LineIndex_internal.h>
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
    ERESULT     LineIndex_ParseJsonFields (
        JSONIN_DATA     *pParser,
        LINEINDEX_DATA  *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode = OBJ_NIL;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        //uint32_t        len;

        (void)JsonIn_FindU32NodeInHashA(pParser, "max", &pObject->max);
        (void)JsonIn_FindU32NodeInHashA(pParser, "size", &iMax);
        eRc = JsonIn_FindArrayNodeInHashA(pParser, "array", &pArray);
        if (pArray && (iMax == NodeArray_getSize(pArray)))
            ;
        else {

        }
        for (i=0; i<iMax; i++) {
            SRCLOC          loc = {0};
            pNode = NodeArray_Get(pArray, i+1);
            pHash = JsonIn_CheckNodeForHash(pNode);
            if (pHash) {
                eRc = JsonIn_SubObjectFromHash(pParser, pHash);
                (void)JsonIn_FindU32NodeInHashA(pParser, "fileIndex", &loc.fileIndex);
                (void)JsonIn_FindU32NodeInHashA(pParser, "lineNo", &loc.lineNo);
                (void)JsonIn_FindU16NodeInHashA(pParser, "colNo", &loc.colNo);
                (void)JsonIn_FindI64NodeInHashA(pParser, "offset", &loc.offset);
                JsonIn_SubObjectEnd(pParser);
                eRc = LineIndex_Add(pObject, &loc);
            }
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
    LINEINDEX_DATA * LineIndex_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        LINEINDEX_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(LineIndex_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = LineIndex_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  LineIndex_ParseJsonFields(pParser, pObject);

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
    

    LINEINDEX_DATA *   LineIndex_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        LINEINDEX_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            SrcErrors_Print(OBJ_NIL, stderr);
            goto exit00;
        }
        
        pObject = LineIndex_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    LINEINDEX_DATA * LineIndex_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        LINEINDEX_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = LineIndex_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = LineIndex_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIndex_ToJson (
        LINEINDEX_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !LineIndex_Validate(this) ) {
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
     
            eRc = LineIndex_ToJsonFields(this, pStr);      

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
    ERESULT         LineIndex_ToJsonFields (
        LINEINDEX_DATA     *this,
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
        uint32_t        i;
        uint32_t        iMax;

        JsonOut_Append_u32("max", this->max, pStr);
        JsonOut_Append_u32("size", LineIndex_getSize(this), pStr);
        AStr_AppendA(pStr, "\tarray:[\n");
        iMax = LineIndex_getSize(this);
        for (i=0; i<iMax; i++) {
            SRCLOC          *pEntry = NULL;
            pEntry = array_GetAddrOf(this->pArray, (i + 1));
            if (pEntry) {
                AStr_AppendPrint(pStr,
                                 "\t\t{\"fileIndex\":%d, "
                                 "\"offset\":%lld, "
                                 "\"lineNo\":%d, "
                                 "\"colNo\":%d "
                                 "},\n",
                                 pEntry->fileIndex,
                                 pEntry->offset,
                                 pEntry->lineNo,
                                 pEntry->colNo
                );
            }
        }
        AStr_AppendA(pStr, "]\n");

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef  __cplusplus
}
#endif

