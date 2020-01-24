// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   W32StrC_json.c
 *
 *	Generated 01/23/2020 22:22:04
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
#include    <W32StrC_internal.h>
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
    ERESULT     W32StrC_ParseJsonFields(
        JSONIN_DATA     *pParser,
        W32STRC_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        OBJ_INFO        *pInfo;
        int64_t         intIn;
        ASTR_DATA       *pWrk;
        uint32_t        crc = 0;
        uint32_t        length = 0;
        const
        char            *pSrcA;
        bool            fRc;

        pInfo = obj_getInfo(W32StrC_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "crc", &intIn);
       crc = (uint32_t)intIn;

       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "len", &intIn);
       length = (uint32_t)intIn;

        if (length && pObject) {
            eRc = JsonIn_FindStringNodeInHashA(pParser, "data", &pWrk);
            pSrcA = AStr_getData(pWrk);
            fRc = W32StrC_CopyFromA(pObject, pSrcA);
            if (!fRc) {
                W32StrC_FreeLine(pObject);
                eRc = ERESULT_INVALID_SYNTAX;
            } else if (!(length == W32StrC_getLength(pObject))) {
                W32StrC_FreeLine(pObject);
                eRc = ERESULT_INVALID_SYNTAX;
            } else if (!(crc == W32StrC_getCrcIEEE(pObject))) {
                W32StrC_FreeLine(pObject);
                eRc = ERESULT_INVALID_SYNTAX;
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
    W32STRC_DATA * W32StrC_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        W32STRC_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(W32StrC_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = W32StrC_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  W32StrC_ParseJsonFields(pParser, pObject);

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
    

    W32STRC_DATA *   W32StrC_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        W32STRC_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = W32StrC_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    W32STRC_DATA * W32StrC_NewFromJsonStringA(
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        W32STRC_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = W32StrC_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = W32StrC_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32StrC_ToJson(
        W32STRC_DATA   *this
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
        uint32_t        crc = 0;
        W32CHR_T        *pChrW;
        char            str[16];
        uint32_t        i;

#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
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
            
        crc = W32StrC_getCrcIEEE(this);
        AStr_AppendPrint(pStr, ", \"crc\":%u", crc);
        AStr_AppendPrint(pStr, ", \"len\":%u", this->len);

        if (this->len) {
            AStr_AppendA(pStr, ", \"data\":\"");
            pChrW = this->pArray;
            for (i=0; i<this->len; ++i) {
                utf8_W32ToChrCon(*pChrW, str);
                AStr_AppendA(pStr, str);
                pChrW++;
            }
            AStr_AppendA(pStr, "\" ");
        }
        else {
            AStr_AppendA(pStr, ", \"data\":null ");
        }

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

