// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjHash_json.c
 *
 *	Generated 02/02/2020 09:55:43
 *
 * Todo:
 *   **     Scoping is only partialy implemented and is not operational.
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
#include    <ObjHash_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
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
    ERESULT     ObjHash_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OBJHASH_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;
        uint32_t        cHash = 0;
        uint32_t        count = 0;
        uint32_t        i;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pNode;

        eRc = ObjHash_Reset(pObject);
        (void)JsonIn_FindU32NodeInHashA(pParser, "cHash", &cHash);
        eRc = ObjHash_Setup(pObject, cHash);
        (void)JsonIn_FindU32NodeInHashA(pParser, "count", &count);
        eRc = JsonIn_FindArrayNodeInHashA(pParser, "entries", &pArray);
        if (!ERESULT_FAILED(eRc)) {
            for (i=0; i<count; i++) {
                OBJ_ID          pObj = OBJ_NIL;
                pNode = NodeArray_Get(pArray, i+1);
                pHash = JsonIn_CheckNodeForHash(pNode);
                if (pHash) {
                    eRc = JsonIn_SubObjectFromHash(pParser, pHash);
                    eRc = JsonIn_SubObjectInHash(pParser, "Object");
                    pObj = JsonIn_ParseObject(pParser);
                    if (pObj) {
                        eRc = ObjHash_Add(pObject, pObj, NULL);
                        obj_Release(pObj);
                    }
                    JsonIn_SubObjectEnd(pParser);
                    JsonIn_SubObjectEnd(pParser);
                }
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
    OBJHASH_DATA * ObjHash_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        OBJHASH_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(ObjHash_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = ObjHash_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  ObjHash_ParseJsonFields(pParser, pObject);

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
    

    OBJHASH_DATA *   ObjHash_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        OBJHASH_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = ObjHash_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    OBJHASH_DATA * ObjHash_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJHASH_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = ObjHash_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = ObjHash_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjHash_ToJson (
        OBJHASH_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !ObjHash_Validate(this) ) {
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
     
            eRc = ObjHash_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    ERESULT         ObjHash_ToJsonFields (
        OBJHASH_DATA     *this,
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
        //ASTR_DATA       *pWrkStr;
        uint32_t        i;
        uint32_t        j;
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        ASTR_DATA       *pData;

        AStr_AppendPrint(
                         pStr,
                         "\t\"cHash\":%d, \"count\":%d,\n\t\"entries\":[\n\t\t",
                         this->cHash,
                         this->num
        );

        // Scan the Hash Table creating entries for each of the objects
        // in the table and appending them to the array.
        j = this->num;
        for (i=0; i < this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pNode = listdl_Head(pNodeList);
            while (pNode) {
                pData = OBJ_NIL;
                pQueryInfo = obj_getVtbl(pNode->pObject)->pQueryInfo;
                if (pQueryInfo) {
                    pToJson =   (*pQueryInfo)(
                                          pNode->pObject,
                                          OBJ_QUERYINFO_TYPE_METHOD,
                                          "ToJson"
                                );
                    if (pToJson) {
                        pData = (*pToJson)(pNode->pObject);
                        if (pData) {
                            AStr_AppendPrint(
                                        pStr,
                                        "{Object: %s}",
                                        AStr_getData(pData)
                            );
                            obj_Release(pData);
                            pData = OBJ_NIL;
                            if (j-- > 1) {
                                AStr_AppendA(pStr, ",\n\t\t");
                            }
                            else {
                                AStr_AppendA(pStr, "\n");
                            }
                        }
                    }
                }
                pNode = listdl_Next(pNodeList, pNode);
            }
        }
        AStr_AppendA(pStr, "\t]\n");

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

