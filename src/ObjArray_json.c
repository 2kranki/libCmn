// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjArray_json.c
 *
 *	Generated 12/29/2019 20:07:08
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
#include    <ObjArray_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
#include    <JsonIn.h>
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
    ERESULT     ObjArray_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OBJARRAY_DATA   *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int64_t         intIn;
        uint32_t        numEntries = 0;
        uint32_t        i;
        NODEARRAY_DATA  *pArray;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pNode;

        (void)JsonIn_FindU32NodeInHashA(pParser, "Size", &numEntries);
        eRc = JsonIn_FindArrayNodeInHashA(pParser, "Objects", &pArray);
        for (i=0; i<numEntries; i++) {
            uint32_t        index = 0;
            OBJ_ID          pObj = OBJ_NIL;
            pNode = NodeArray_Get(pArray, i+1);
            pHash = JsonIn_CheckNodeForHash(pNode);
            if (pHash) {
                eRc = JsonIn_SubObjectFromHash(pParser, pHash);
                eRc = JsonIn_FindIntegerNodeInHashA(pParser, "Index", &intIn);
                index = (uint32_t)intIn;
                eRc = JsonIn_SubObjectInHash(pParser, "Object");
                pObj = JsonIn_ParseObject(pParser);
                if (index && pObj) {
                    eRc = ObjArray_Put(pObject, index, pObj);
                    obj_Release(pObj);
                }
                JsonIn_SubObjectEnd(pParser);
                JsonIn_SubObjectEnd(pParser);
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
    OBJARRAY_DATA * ObjArray_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        OBJARRAY_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;

        pInfo = obj_getInfo(ObjArray_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = ObjArray_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  ObjArray_ParseJsonFields(pParser, pObject);

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
    

    OBJARRAY_DATA *   ObjArray_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        OBJARRAY_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = ObjArray_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    OBJARRAY_DATA * ObjArray_NewFromJsonStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJARRAY_DATA   *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = ObjArray_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = ObjArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjArray_ToJson(
        OBJARRAY_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr,
                         "{ \"objectType\":\"%s\", ",
                         pInfo->pClassName
        );


        eRc = ObjArray_ToJsonFields(this, pStr);

        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    ERESULT         ObjArray_ToJsonFields (
        OBJARRAY_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        ASTR_DATA *     (*pToJson)(
            OBJ_ID          objId
        );
        ASTR_DATA       *pWrkStr;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        numEntries = 0;
        OBJ_ID          pObj;

        iMax = ObjArray_getSize(this);
        for (i=0; i<iMax; i++) {
            pObj = ObjArray_Get(this, i+1);
            if (pObj) {
                numEntries++;
            }
        }

        AStr_AppendPrint(pStr,
                         "\"Size\":%d, "
                         "\"Objects\":[\n",
                         numEntries
        );

        if (iMax > 1) {
            for (i=0; i<iMax-1; i++) {
                pObj = ObjArray_Get(this, i+1);
                if (pObj) {
                    pQueryInfo = obj_getVtbl(pObj)->pQueryInfo;
                    if (pQueryInfo) {
                        pToJson =   (*pQueryInfo)(
                                                  pObj,
                                                  OBJ_QUERYINFO_TYPE_METHOD,
                                                  "ToJson"
                                                  );
                        if (pToJson) {
                            pWrkStr = (*pToJson)(pObj);
                            if (pWrkStr) {
                                AStr_AppendPrint(pStr, "\t{Index:%d, Object:", i+1);
                                AStr_Append(pStr, pWrkStr);
                                obj_Release(pWrkStr);
                                pWrkStr = OBJ_NIL;
                                AStr_AppendA(pStr, "},\n");
                            }
                        }
                    }
                }
            }
        }
        if (iMax) {
            pObj = ObjArray_Get(this, i+1);
            if (pObj) {
                pQueryInfo = obj_getVtbl(pObj)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                              pObj,
                                              OBJ_QUERYINFO_TYPE_METHOD,
                                              "ToJson"
                                              );
                    if (pToJson) {
                        pWrkStr = (*pToJson)(pObj);
                        if (pWrkStr) {
                            AStr_AppendPrint(pStr, "\t{Index:%d, Object:", i+1);
                            AStr_Append(pStr, pWrkStr);
                            obj_Release(pWrkStr);
                            pWrkStr = OBJ_NIL;
                            AStr_AppendA(pStr, "}\n");
                        }
                    }
                }
            }
        }
        AStr_AppendA(pStr, "]\n");

        return ERESULT_SUCCESS;
    }




    
#ifdef	__cplusplus
}
#endif

