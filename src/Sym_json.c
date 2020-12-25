// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Sym_json.c
 *
 *	Generated 02/22/2020 20:18:12
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
#include    <Sym_internal.h>
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
    ERESULT     Sym_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SYM_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //int64_t         intIn;
        ASTR_DATA       *pWrk = OBJ_NIL;
        uint32_t        len = 0;
        //uint16_t        max = 0;
        uint8_t         *pData;

        eRc = JsonIn_FindStringNodeInHashA(pParser, "name", &pWrk);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            fprintf(stderr, "FATAL - Failed to find Name!\n\n\n");
            exit(EXIT_FAILURE);
        }
        if (AStr_getLength(pWrk) > sizeof(pObject->entry.name)-1) {
            DEBUG_BREAK();
            fprintf(stderr, "FATAL - Name was too big!\n\n\n");
            exit(EXIT_FAILURE);
        }
        Sym_setNameA(pObject, AStr_getData(pWrk));
        (void)JsonIn_FindU8NodeInHashA(pParser,  "fFlgs1",  &pObject->entry.fFlgs1);
        (void)JsonIn_FindU8NodeInHashA(pParser,  "fFlgs2",  &pObject->entry.fFlgs2);
        (void)JsonIn_FindU32NodeInHashA(pParser, "hash",    &pObject->entry.hash);
        (void)JsonIn_FindU32NodeInHashA(pParser, "token",   &pObject->entry.token);
        (void)JsonIn_FindI32NodeInHashA(pParser, "cls",     &pObject->entry.cls);
        (void)JsonIn_FindI32NodeInHashA(pParser, "type",    &pObject->entry.type);
        (void)JsonIn_FindU32NodeInHashA(pParser, "section", &pObject->entry.section);
        (void)JsonIn_FindU16NodeInHashA(pParser, "prim",    &pObject->entry.prim);
        (void)JsonIn_FindU16NodeInHashA(pParser, "len",     &pObject->entry.len);
        (void)JsonIn_FindU16NodeInHashA(pParser, "dup",     &pObject->entry.dup);
        (void)JsonIn_FindU16NodeInHashA(pParser, "align",   &pObject->entry.align);
        (void)JsonIn_FindU32NodeInHashA(pParser, "record",  &pObject->entry.record);
        (void)JsonIn_FindU16NodeInHashA(pParser, "scale",   &pObject->entry.scale);
        (void)JsonIn_FindI32NodeInHashA(pParser, "value",   &pObject->entry.value);
        eRc = JsonIn_SubObjectInHash(pParser, "extra");
        if (ERESULT_OK(eRc)) {
            pData = hex_ParseObject(pParser, &len);
            JsonIn_SubObjectEnd(pParser);
            if (pData) {
                memmove(pObject->entry.extra2, pData, sizeof(pObject->entry.extra2));
                mem_Free(pData);
                pData = NULL;
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
    SYM_DATA * Sym_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SYM_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(Sym_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = Sym_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  Sym_ParseJsonFields(pParser, pObject);

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
    

    SYM_DATA *   Sym_NewFromJsonString (
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        SYM_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = Sym_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    SYM_DATA * Sym_NewFromJsonStringA (
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SYM_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = Sym_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = Sym_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sym_ToJson (
        SYM_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !Sym_Validate(this) ) {
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
     
            eRc = Sym_ToJsonFields(this, pStr);      

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    ERESULT         Sym_ToJsonFields (
        SYM_DATA        *this,
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
        char            NameA[256];
        uint32_t        len;
        ASTR_DATA       *pWrk;

        len = utf8_Utf8ToChrConStr(0, this->entry.name, sizeof(NameA), NameA);
        AStr_AppendPrint(pStr, "\tname:\"%s\",\n", NameA);
        (void)JsonOut_Append_u8("fFlgs1",   this->entry.fFlgs1, pStr);
        (void)JsonOut_Append_u8("fFlgs2",   this->entry.fFlgs2, pStr);
        (void)JsonOut_Append_u32("hash",    this->entry.hash, pStr);
        (void)JsonOut_Append_u32("token",   this->entry.token, pStr);
        (void)JsonOut_Append_i32("cls",     this->entry.cls, pStr);
        (void)JsonOut_Append_i32("type",    this->entry.type, pStr);
        (void)JsonOut_Append_u32("section", this->entry.section, pStr);
        (void)JsonOut_Append_u16("prim",    this->entry.prim, pStr);
        (void)JsonOut_Append_u16("len",     this->entry.len, pStr);
        (void)JsonOut_Append_u16("dup",     this->entry.dup, pStr);
        (void)JsonOut_Append_u16("align",   this->entry.align, pStr);
        (void)JsonOut_Append_u32("record",  this->entry.record, pStr);
        (void)JsonOut_Append_u16("scale",   this->entry.scale, pStr);
        (void)JsonOut_Append_i32("value",   this->entry.value, pStr);
        pWrk = hex_DataToJSON(sizeof(this->entry.extra2), this->entry.extra2);
        if (pWrk) {
            AStr_AppendA(pStr, "\t\"extra\":");
            AStr_Append(pStr, pWrk);
            obj_Release(pWrk);
            pWrk = OBJ_NIL;

        }

        return ERESULT_SUCCESS;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

