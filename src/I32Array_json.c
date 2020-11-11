// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   I32Array_json.c
 *
 *	Generated 01/14/2020 18:29:58
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
#include    <I32Array_internal.h>
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
    ERESULT         I32Array_ParseJsonFields(
        JSONIN_DATA     *pParser,
        I32ARRAY_DATA   *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        OBJ_INFO        *pInfo;
        int64_t         intIn;
        //ASTR_DATA       *pWrk;
        uint32_t        count;
        NODEARRAY_DATA  *pArray;
        uint32_t        i;
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        ASTR_DATA       *pStr;

        pInfo = obj_getInfo(I32Array_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "size", &intIn);
       count = (uint32_t)intIn;

        if (count && pObject) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "data", &pArray);
            if (pArray) {
                if (count == NodeArray_getSize(pArray))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            count,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
            }
            else {
                fprintf(
                    stderr,
                    "ERROR - JSON Count, %d, is present, but Entries were not found!\n",
                    count
                );
                goto exit00;
            }

            for(i=0; i<count; ++i) {
                //fprintf(stderr, "\t\tLooking for Node(%d)\n", i+1);
                pNode = NodeArray_Get(pArray, i+1);
                if (OBJ_NIL == pNode) {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            count,
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
                eRc = I32Array_AppendData(pObject, (uint8_t)AStr_ToInt64(pStr));
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
    I32ARRAY_DATA * I32Array_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        I32ARRAY_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(I32Array_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = I32Array_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  I32Array_ParseJsonFields(pParser, pObject);

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
    

    I32ARRAY_DATA *   I32Array_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        I32ARRAY_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = I32Array_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    I32ARRAY_DATA * I32Array_NewFromJsonStringA(
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        I32ARRAY_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = I32Array_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = I32Array_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     I32Array_ToJson(
        I32ARRAY_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
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
        int             j;
        int             jMax;
        int32_t         *pData;

#ifdef NDEBUG
#else
        if( !I32Array_Validate(this) ) {
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
            
            AStr_AppendPrint(pStr,
                             "\"size\":%d, \n\t\"data\":[",
                             I32Array_getSize(this)
            );

            jMax = array_getSize((ARRAY_DATA *)this);
            pData = array_Ptr((ARRAY_DATA *)this, 1);
            if (jMax) {
                for (j=0; j<(jMax-1); ++j) {
                    if ((j % 5) == 0) {
                        AStr_AppendA(pStr, "\n\t\t");
                    }
                    AStr_AppendPrint(pStr, "%d,", *pData++);
                }
                if ((j % 5) == 0) {
                    AStr_AppendA(pStr, "\n\t\t");
                }
                AStr_AppendPrint(pStr, "%d\n", *pData++);
            }
            AStr_AppendA(pStr, "\t]}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

