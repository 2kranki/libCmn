// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   I16Matrix_json.c
 *
 *	Generated 02/19/2020 09:50:41
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
#include    <I16Matrix_internal.h>
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
    ERESULT     I16Matrix_ParseJsonFields (
        JSONIN_DATA     *pParser,
        I16MATRIX_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        NODEARRAY_DATA  *pArray;
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        ASTR_DATA       *pStr;
        uint16_t        *pValue;

        {
            ASTR_DATA       *pStr = JsonIn_ToDebugString(pParser, 4);
            fprintf(stderr, "Base:\n%s\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        eRc = JsonIn_FindU32NodeInHashA(pParser, "m", &pObject->m);
        eRc = JsonIn_FindU32NodeInHashA(pParser, "n", &pObject->n);
        (void)JsonIn_FindU32NodeInHashA(pParser, "cElems", &pObject->cElems);
        if (pObject->m && pObject->n) {
            eRc = I16Matrix_Setup(pObject, pObject->m, pObject->n);
        }
        if (pObject->cElems && pObject) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "Data", &pArray);
            if (pArray) {
                if (pObject->cElems == NodeArray_getSize(pArray))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            pObject->cElems,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
            }
            else {
                fprintf(
                    stderr,
                    "ERROR - JSON Count, %d, is present, but Entries were not found!\n",
                    pObject->cElems
                );
                goto exit00;
            }

            for(i=0; i<pObject->cElems; i++) {
                //fprintf(stderr, "\t\tLooking for Node(%d)\n", i+1);
                pNode = NodeArray_Get(pArray, i+1);
                if (OBJ_NIL == pNode) {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            pObject->cElems,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
                pName = Node_getName(pNode);
                if (0 == Name_CompareA(pName, "integer"))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - Node name is not valid!\n"
                    );
                    goto exit00;
                }
                pStr = Node_getData(pNode);
                if (OBJ_NIL == pStr) {
                    fprintf(
                            stderr,
                            "ERROR - Node's data is not valid!\n"
                    );
                    goto exit00;
                }
#ifdef XYZZY
                fprintf(stderr,
                        "\t\t...found - %s -- 0x%02X\n",
                        AStr_getData(pStr),
                        (uint8_t)AStr_ToInt64(pStr));
#endif
                pValue = array_GetAddrOf((ARRAY_DATA *)pObject, i+1);
                if (pValue)
                    *pValue = (int16_t)AStr_ToInt64(pStr);
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
    I16MATRIX_DATA * I16Matrix_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        I16MATRIX_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(I16Matrix_Class());
        
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = I16Matrix_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  I16Matrix_ParseJsonFields(pParser, pObject);

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
    

    I16MATRIX_DATA *   I16Matrix_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        I16MATRIX_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        if (obj_Trace(pString)) {
            obj_TraceSet(pParser, true);
        }
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = I16Matrix_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    I16MATRIX_DATA * I16Matrix_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        I16MATRIX_DATA  *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = I16Matrix_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = I16Matrix_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     I16Matrix_ToJson (
        I16MATRIX_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !I16Matrix_Validate(this) ) {
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
     
            eRc = I16Matrix_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    ERESULT         I16Matrix_ToJsonFields (
        I16MATRIX_DATA     *this,
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
        uint16_t        value = 0;
        uint16_t        *pValue;

        JsonOut_Append_u32("m", this->m, pStr);
        JsonOut_Append_u32("n", this->n, pStr);
        JsonOut_Append_u32("cElems", this->cElems, pStr);
        if (this->cElems) {
            AStr_AppendA(pStr, "\tData:[\n");
            for (i=0; i<this->cElems-1; i++) {
                pValue = array_GetAddrOf((ARRAY_DATA *)this, i+1);
                if (pValue)
                    value = *pValue;
                AStr_AppendPrint(pStr, "\t\t%d,\n", *pValue);
            }
            pValue = array_GetAddrOf((ARRAY_DATA *)this, i+1);
            if (pValue)
                value = *pValue;
            AStr_AppendPrint(pStr, "\t\t%d\n", *pValue);
            AStr_AppendA(pStr, "\t]\n");
        } else {
            AStr_AppendA(pStr, "\tData:null\n");
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

