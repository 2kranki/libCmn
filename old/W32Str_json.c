// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   W32Str_JSON.c
 *
 * Created on 10/13/2017 from AStr_JSON
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
#include    <W32Str_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <crc.h>
#include    <dec.h>
#include    <hex.h>
#include    <JsonIn.h>
#include    <JsonOut.h>
#include    <Node.h>
#include    <NodeArray.h>
#include    <NodeHash.h>
#include    <utf8.h>

//#define TRACE_FUNCTIONS 1


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
    ERESULT     W32Str_ParseJsonFields (
        JSONIN_DATA     *pParser,
        W32STR_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //NODE_DATA       *pNode = OBJ_NIL;
        //NODEARRAY_DATA  *pArray = OBJ_NIL;
        //NODEHASH_DATA   *pHash = OBJ_NIL;
        //uint32_t        i;
        //uint32_t        iMax;
        //int64_t         intIn;
        ASTR_DATA       *pWrk;
        //uint8_t         *pData;
        uint32_t        len = 0;
        uint32_t        crc = 0;
        W32CHR_T        ch;
        const
        char            *pSrc;
        uint32_t        i;

        (void)JsonIn_FindU32NodeInHashA(pParser, "crc", &crc);
        (void)JsonIn_FindU32NodeInHashA(pParser, "len", &len);

        if (len) {
            eRc = JsonIn_FindStrNodeInHashA(pParser, "data", &pWrk);
            pSrc = AStr_getData(pWrk);
            for (i=0; i<len; ++i) {
                ch = utf8_ChrConToW32_Scan(&pSrc);
                W32Str_AppendW32(pObject, 1, &ch);
            }
            if (!(crc == W32Str_getCrcIEEE(pObject))) {
                return ERESULT_DATA_ERROR;
            }
        }

#ifdef XYZZZY
        (void)JsonIn_FindU16NodeInHashA(pParser, "type", &pObject->type);
        (void)JsonIn_FindU32NodeInHashA(pParser, "attr", &pObject->attr);
        (void)JsonIn_FindIntegerNodeInHashA(pParser, "fileSize", &pObject->fileSize); //i64

        eRc = JsonIn_FindUtf8NodeInHashA(pParser, "name", &pData, &len);
        eRc = JsonIn_SubObjectInHash(pParser, "errorStr");
        if (ERESULT_OK(eRc)) {
            pWrk = AStr_ParseJsonObject(pParser);
            if (pWrk) {
                pObject->pErrorStr = pWrk;
            }
            JsonIn_SubObjectEnd(pParser);
        }
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
    W32STR_DATA *   W32Str_ParseJsonObject (
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        W32STR_DATA     *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        JsonIn_RegisterClass(W32Str_Class());

        pInfo = obj_getInfo(W32Str_Class());
        eRc = JsonIn_ConfirmObjectTypeA(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = W32Str_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }

        eRc =  W32Str_ParseJsonFields(pParser, pObject);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pObject);
            pObject = OBJ_NIL;
        }

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
    

    W32STR_DATA *   W32Str_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc = ERESULT_SUCCESS;
        W32STR_DATA     *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = W32Str_ParseJsonObject(pParser);
        
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    W32STR_DATA *   W32Str_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        W32STR_DATA     *pObject = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObject = W32Str_NewFromJSONString(pStr);
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
     ASTR_DATA      *pDesc = W32Str_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToJson (
        W32STR_DATA     *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
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

            eRc = W32Str_ToJsonFields(this, pStr);

            AStr_AppendPrint(pStr, "}\t/* %s */\n", pInfo->pClassName);
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
    ERESULT         W32Str_ToJsonFields (
        W32STR_DATA     *this,
        ASTR_DATA       *pStr
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
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
        char            *pChr;
        uint32_t        crc = 0;
        W32CHR_T        chrW;
        W32CHR_T        *pChrW;
        uint32_t        len;
        const
        char            *pData;
        char            str[16];
        uint32_t        i;

        crc = W32Str_getCrcIEEE(this);
        JsonOut_Append_u32("crc", crc, pStr);

        pData  = array_Ptr((ARRAY_DATA *)this, 1);
        len = array_getSize((ARRAY_DATA *)this) - 1;
        JsonOut_Append_u32("len", len, pStr);
        if (len) {
            AStr_AppendA(pStr, ", \"data\":\"");
            pChr = pData;
            for (i=0; i<len; ++i) {
                pChrW = array_Ptr((ARRAY_DATA *)this, i+1);
                chrW = *pChrW;
                utf8_W32ToChrCon(*pChrW, str);
                AStr_AppendA(pStr, str);
            }
            AStr_AppendA(pStr, "\" ");
        }
        else {
            AStr_AppendA(pStr, ", \"data\":null ");
        }

#ifdef XYZZZY
        JsonOut_Append_i32("x", this->x, pStr);
        JsonOut_Append_i64("t", this->t, pStr);
        JsonOut_Append_u32("o", this->o, pStr);
        JsonOut_Append_utf8("n", pEntry->pN, pStr);
        JsonOut_Append_Object("e", this->pE, pStr);
        JsonOut_Append_AStr("d", this->pAStr, pStr);
        JsonOut_Append_StrA("d", this->pStrA, pStr);
        JsonOut_Append_StrW32("d", this->pStrW32, pStr);
#endif

        return ERESULT_SUCCESS;
    }




    
    
    
    
    
#ifdef	__cplusplus
}
#endif

