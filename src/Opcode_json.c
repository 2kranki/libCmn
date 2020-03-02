// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Opcode_json.c
 *
 *	Generated 02/27/2020 14:36:27
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
#include    <Opcode_internal.h>
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
    ERESULT     Opcode_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OPCODE_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int64_t         intIn;
        ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        //uint32_t        len;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode;
        uint32_t        i;

        eRc = JsonIn_FindStringNodeInHashA(pParser, "Name", &pWrk);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            fprintf(stderr, "FATAL - Failed to find Name!\n\n\n");
            exit(EXIT_FAILURE);
        }
        if (AStr_getLength(pWrk) > OPCODE_ENTRY_NAME_MAX-1) {
            DEBUG_BREAK();
            fprintf(stderr, "FATAL - Name was too big!\n\n\n");
            exit(EXIT_FAILURE);
        }
        Opcode_setNameA(pObject, AStr_getData(pWrk));
        (void)JsonIn_FindU8NodeInHashA(pParser, "cCode", &pObject->entry.cCode);
        if (pObject->entry.cCode) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "iCode", &pArray);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to find iCode!\n\n\n");
                exit(EXIT_FAILURE);
            }
            if (NodeArray_getSize(pArray) > OPCODE_ENTRY_CCODE_MAX) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - cCode is too big!\n\n\n");
                exit(EXIT_FAILURE);
            }
            pObject->entry.cCode = NodeArray_getSize(pArray);
            for (i=0; i<NodeArray_getSize(pArray); i++) {
                pNode = NodeArray_Get(pArray, i+1);
                if (pNode) {
                    pWrk = JsonIn_CheckNodeForInteger(pNode);
                    if (pWrk) {
                        int64_t         num = AStr_ToInt64(pWrk);
                        pObject->entry.iCode[i] = (uint8_t)num;
                    }
                }
            }
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "iMask", &pArray);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Failed to find iCode!\n\n\n");
                exit(EXIT_FAILURE);
            }
            if (NodeArray_getSize(pArray) != pObject->entry.cCode) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - number of iMasks must match number of iCodes!\n\n\n");
                exit(EXIT_FAILURE);
            }
            for (i=0; i<NodeArray_getSize(pArray); i++) {
                pNode = NodeArray_Get(pArray, i+1);
                if (pNode) {
                    pWrk = JsonIn_CheckNodeForInteger(pNode);
                    if (pWrk) {
                        int64_t         num = AStr_ToInt64(pWrk);
                        pObject->entry.iMask[i] = (uint8_t)num;
                    }
                }
            }
        }
        // iType can be integer or string description.
        eRc = JsonIn_FindStringNodeInHashA(pParser, "iType", &pWrk);
        if (ERESULT_OK(eRc)) {
            if (pObject->pTypeValue) {
                if (pWrk) {
                    uint16_t        type = pObject->pTypeValue(AStr_getData(pWrk));
                    pObject->entry.iType = type;
                }
            } else {
                goto tryIntType;
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - Opcode type description, "
                                "but no conversion routine!\n\n\n");
                exit(EXIT_FAILURE);
            }
        } else {
        tryIntType:
            eRc = JsonIn_FindU8NodeInHashA(pParser, "iType", &pObject->entry.iType);
        }
        (void)JsonIn_FindU8NodeInHashA(pParser, "iLen", &pObject->entry.iLen);
        // The optional iFeatures can be integer or array of descriptions.
        if (pObject->pFeatureValue) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "iFeatures", &pArray);
            if (ERESULT_FAILED(eRc)) {
                    eRc = JsonIn_FindU16NodeInHashA(pParser, "iFeatures",
                                                    &pObject->entry.iFeatures);
            } else {
                for (i=0; i<NodeArray_getSize(pArray); i++) {
                    pNode = NodeArray_Get(pArray, i+1);
                    if (pNode) {
                        pWrk = JsonIn_CheckNodeForString(pNode);
                        if (pWrk) {
                            if (pObject->pFeatureValue) {
                                pObject->entry.iFeatures |=
                                                pObject->pFeatureValue(AStr_getData(pWrk));
                            }
                        }
                    }
                }
            }
        } else {
            eRc = JsonIn_FindU16NodeInHashA(pParser, "iFeatures",
                                            &pObject->entry.iFeatures);
        }
        (void)JsonIn_FindU8NodeInHashA(pParser, "cCondCodes", &pObject->entry.cCondCodes);
        eRc = JsonIn_FindArrayNodeInHashA(pParser, "szCondCodes", &pArray);
        if (!ERESULT_FAILED(eRc)) {
            if (NodeArray_getSize(pArray) > OPCODE_ENTRY_CCODE_MAX) {
                DEBUG_BREAK();
                fprintf(stderr, "FATAL - too many condition codes!\n\n\n");
                exit(EXIT_FAILURE);
            }
            for (i=0; i<NodeArray_getSize(pArray); i++) {
                pNode = NodeArray_Get(pArray, i+1);
                if (pNode) {
                    pWrk = JsonIn_CheckNodeForString(pNode);
                    if (pWrk) {
                        str_Copy(
                                 (char *)pObject->entry.szCondCodes[i],
                                 OPCODE_ENTRY_SZCONDCODE_MAX,
                                 AStr_getData(pWrk)
                        );
                    }
                }
            }
        }
        // The optional iInterrupts can be integer or array of descriptions.
        if (pObject->pInterruptValue) {
            eRc = JsonIn_FindArrayNodeInHashA(pParser, "iInterrupts", &pArray);
            if (ERESULT_FAILED(eRc)) {
                eRc = JsonIn_FindU32NodeInHashA(pParser, "iInterrupts",
                                                            &pObject->entry.iInterrupts);
            } else {
                for (i=0; i<NodeArray_getSize(pArray); i++) {
                    pNode = NodeArray_Get(pArray, i+1);
                    if (pNode) {
                        pWrk = JsonIn_CheckNodeForString(pNode);
                        if (pWrk) {
                            uint16_t        num =
                                            pObject->pInterruptValue(AStr_getData(pWrk));
                            if (num)
                                pObject->entry.iInterrupts |= 1 << (num-1);
                        }
                    }
                }
            }
        } else {
            eRc = JsonIn_FindU32NodeInHashA(pParser, "iInterrupts",
                                                        &pObject->entry.iInterrupts);
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
    OPCODE_DATA * Opcode_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        OPCODE_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Opcode_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Opcode_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Opcode_ParseJsonFields(pParser, pObject);

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
    

    OPCODE_DATA *   Opcode_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        OPCODE_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Opcode_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    OPCODE_DATA * Opcode_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OPCODE_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = Opcode_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Opcode_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcode_ToJson (
        OPCODE_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !Opcode_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
             AStr_AppendPrint(pStr,
                              "{ \"objectType\":\"%s\", \n",
                              pInfo->pClassName
             );
     
            eRc = Opcode_ToJsonFields(this, pStr);

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    ERESULT         Opcode_ToJsonFields (
        OPCODE_DATA     *this,
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
        char            *pDesc;
        uint32_t        i;

        AStr_AppendPrint(pStr, "\tName:\"%s\",\n", this->entry.Name);
        JsonOut_Append_u8("cCode", this->entry.cCode, pStr);
        JsonOut_Append_u8_array("iCode", this->entry.cCode, this->entry.iCode, pStr);
        JsonOut_Append_u8_array("iMask", this->entry.cCode, this->entry.iMask, pStr);
        if (this->pTypeDesc) {
            pDesc = this->pTypeDesc(this->entry.iType);
            if (pDesc) {
                AStr_AppendPrint(pStr, "\tiType:\"%s\",\n", pDesc);
            }
        } else {
            JsonOut_Append_u8("iType", this->entry.iType, pStr);
        }
        JsonOut_Append_u8("iLen", this->entry.iLen, pStr);
        if (this->entry.cCondCodes) {
            JsonOut_Append_u8("cCondCodes", this->entry.cCondCodes, pStr);
            AStr_AppendA(pStr, "\tszCondCodes:[\n");
            for (i=0; i<this->entry.cCondCodes-1; i++) {
                AStr_AppendPrint(pStr, "\t\t\"%s\",\n", this->entry.szCondCodes[i]);
            }
            AStr_AppendPrint(pStr, "\t\t\"%s\"\n", this->entry.szCondCodes[i]);
            AStr_AppendA(pStr, "\t],\n");
        }
        if (this->entry.iFeatures) {
            if (this->pFeatureDesc) {
                AStr_AppendA(pStr, "\tiFeatures:[\n");
                for (i=0; i<OPCODE_ENTRY_IFEATURES_MAX; i++) {
                    uint16_t    mask = 1 << i;
                    if (this->entry.iFeatures & mask) {
                        pDesc = this->pFeatureDesc(this->entry.iFeatures & mask);
                        if (pDesc) {
                            AStr_AppendPrint(pStr, "\t\t\"%s\",\n", pDesc);
                        }
                    }
                }
                AStr_AppendA(pStr, "\t],\n");
            } else {
                JsonOut_Append_u16("iFeatures", this->entry.iFeatures, pStr);
            }
        }
        if (this->entry.iInterrupts) {
            if (this->pInterruptDesc) {
                AStr_AppendA(pStr, "\tiInterrupts:[\n");
                for (i=0; i<OPCODE_ENTRY_IINTERRUPTS_MAX; i++) {
                    uint32_t    mask = 1 << i;
                    if (this->entry.iInterrupts & mask) {
                        pDesc = this->pInterruptDesc(i+1);
                        if (pDesc) {
                            AStr_AppendPrint(pStr, "\t\t\"%s\",\n", pDesc);
                        }
                    }
                }
                AStr_AppendA(pStr, "\t],\n");
            } else {
                JsonOut_Append_u32("iInterrupts", this->entry.iInterrupts, pStr);
            }
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

