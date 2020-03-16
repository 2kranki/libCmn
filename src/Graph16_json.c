// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Graph16_json.c
 *
 *	Generated 03/11/2020 17:37:49
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
#include    <Graph16_internal.h>
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
    ERESULT         Graph16_ParseJsonFields (
        JSONIN_DATA     *pParser,
        GRAPH16_DATA    *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int64_t         intIn;
        ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        uint16_t        max = 0;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        uint32_t        i;

        (void)JsonIn_FindU16NodeInHashA(pParser, "edgesMax", &max);
        eRc = Graph16_ExpandEdges(pObject, max);
        (void)JsonIn_FindU16NodeInHashA(pParser, "verticesMax", &max);
        eRc = Graph16_ExpandVertices(pObject, max);

        (void)JsonIn_FindU16NodeInHashA(pParser, "edgesUsed", &pObject->edgesUsed);
        (void)JsonIn_FindU16NodeInHashA(pParser, "verticesUsed", &pObject->verticesUsed);

        if (pObject->edgesUsed) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "edges", &pArray);
            if (pArray) {
                if ((pObject->edgesUsed) == NodeArray_getSize(pArray))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            pObject->edgesUsed,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
            }
            else {
                fprintf(
                    stderr,
                    "ERROR - JSON Count, %d, is present, but Entries were not found!\n",
                    pObject->edgesUsed
                );
                goto exit00;
            }
            for (i=0; i<(pObject->edgesUsed); i++) {
                NODEARRAY_DATA  *pEdge = OBJ_NIL;
                int16_t         e = 0;
                int16_t         vFrom = 0;
                int16_t         vTo = 0;
                //fprintf(stderr, "\t\tLooking for Node(%d)\n", i+1);
                pNode = NodeArray_Get(pArray, i+1);
                if (OBJ_NIL == pNode) {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            pObject->edgesMax,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
                pEdge = JsonIn_CheckNodeForArray(pNode);
                if (OBJ_NIL == pEdge) {
                    fprintf(
                            stderr,
                            "ERROR - Missing Edge Array, %d!\n",
                            i+1
                    );
                    goto exit00;
                }
                if (3 == NodeArray_getSize(pEdge))
                    ;
                else {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, 3, does not match edge array(%d) size, %d!\n",
                            i+1,
                            NodeArray_getSize(pEdge)
                    );
                    goto exit00;
                }
                pNode = NodeArray_Get(pEdge, 1);
                pWrk = JsonIn_CheckNodeForInteger(pNode);
                if (OBJ_NIL == pWrk) {
                    fprintf(
                            stderr,
                            "ERROR - Edge's data is not valid!\n"
                    );
                    goto exit00;
                }
#ifdef XYZZY
                fprintf(stderr,
                        "\t\t...found - %s -- 0x%02X\n",
                        AStr_getData(pWrk),
                        (uint8_t)AStr_ToInt64(pWrk));
#endif
                e = (int16_t)AStr_ToInt64(pWrk);
                pNode = NodeArray_Get(pEdge, 2);
                pWrk = JsonIn_CheckNodeForInteger(pNode);
                if (OBJ_NIL == pWrk) {
                    fprintf(
                            stderr,
                            "ERROR - Edge's data is not valid!\n"
                    );
                    goto exit00;
                }
#ifdef XYZZY
                fprintf(stderr,
                        "\t\t...found - %s -- 0x%02X\n",
                        AStr_getData(pWrk),
                        (uint8_t)AStr_ToInt64(pWrk));
#endif
                vFrom = (int16_t)AStr_ToInt64(pWrk);
                pNode = NodeArray_Get(pEdge, 3);
                if (OBJ_NIL == pNode) {
                    fprintf(
                            stderr,
                            "ERROR - JSON Count, %d, does not match array size, %d!\n",
                            pObject->edgesMax,
                            NodeArray_getSize(pArray)
                    );
                    goto exit00;
                }
                pWrk = JsonIn_CheckNodeForInteger(pNode);
                if (OBJ_NIL == pWrk) {
                    fprintf(
                            stderr,
                            "ERROR - Edge's data is not valid!\n"
                    );
                    goto exit00;
                }
#ifdef XYZZY
                fprintf(stderr,
                        "\t\t...found - %s -- 0x%02X\n",
                        AStr_getData(pWrk),
                        (uint8_t)AStr_ToInt64(pWrk));
#endif
                vTo = (int16_t)AStr_ToInt64(pWrk);
                if (e && vFrom && vTo) {
                    eRc = Graph16_EdgeSet(pObject, e, vFrom, vTo);
                }
            }
            Graph16_RebuildIndex(pObject);
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
    GRAPH16_DATA * Graph16_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        GRAPH16_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Graph16_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Graph16_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Graph16_ParseJsonFields(pParser, pObject);

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
    

    GRAPH16_DATA *   Graph16_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        GRAPH16_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Graph16_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    GRAPH16_DATA * Graph16_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        GRAPH16_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = Graph16_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Graph16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Graph16_ToJson (
        GRAPH16_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !Graph16_Validate(this) ) {
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
     
            eRc = Graph16_ToJsonFields(this, pStr);      

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
    ERESULT         Graph16_ToJsonFields (
        GRAPH16_DATA     *this,
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
        int16_t         e;

        JsonOut_Append_u16("edgesMax", this->edgesMax, pStr);
        JsonOut_Append_u16("edgesUsed", this->edgesUsed, pStr);
        JsonOut_Append_u16("verticesMax", this->verticesMax, pStr);
        JsonOut_Append_u16("verticesUsed", this->verticesUsed, pStr);

        AStr_AppendA(pStr, "\tedges: [\n//\t\t  Edge,  From,   To\n");
        for (e=Graph16_EdgeFirst(this); e; e=Graph16_EdgeNext(this, e)) {
            AStr_AppendPrint(
                             pStr,
                             "\t\t[%5d, %5d, %5d],\n",
                             e,
                             Graph16_EdgeFrom(this, e),
                             Graph16_EdgeTo(this, e)
            );
        }
        AStr_AppendA(pStr, "\t],\n");


        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

