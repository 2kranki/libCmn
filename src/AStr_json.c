// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AStr_json.c
 *
 *	Generated 01/15/2020 09:50:18
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
#include    <AStr_internal.h>
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
    ERESULT     AStr_ParseJsonFields(
        JSONIN_DATA     *pParser,
        ASTR_DATA       *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int64_t         intIn;
        ASTR_DATA       *pWrk;
        uint32_t        crc = 0;
        uint32_t        length = 0;
        uint32_t        i;
        W32CHR_T        ch;
        const
        char            *pSrc;

       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "crc", &intIn);
       crc = (uint32_t)intIn;

       eRc = JsonIn_FindIntegerNodeInHashA(pParser, "len", &intIn);
       length = (uint32_t)intIn;

        if (length && pObject) {
            eRc = JsonIn_FindStringNodeInHashA(pParser, "data", &pWrk);
            pSrc = AStr_getData(pWrk);
            for (i=0; i<length; ++i) {
                ch = utf8_ChrConToW32_Scan(&pSrc);
                AStr_AppendW32(pObject, 1, &ch);
            }
            if (!(crc == AStr_getCrcIEEE(pObject))) {
                obj_Release(pObject);
                pObject = OBJ_NIL;
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
    ASTR_DATA * AStr_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(AStr_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = AStr_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  AStr_ParseJsonFields(pParser, pObject);

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
    

    ASTR_DATA *   AStr_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        ASTR_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = AStr_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    ASTR_DATA * AStr_NewFromJsonStringA(
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = AStr_NewFromJsonString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObject;
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
    ERESULT         AStr_ToJsonFields(
        ASTR_DATA       *this,
        ASTR_DATA       *pStr

    )
    {
        ASTR_DATA       *pWrkStr;
        uint32_t        crc = 0;
        uint32_t        len;

        if (pStr) {
            len = (uint32_t)utf8_StrLenA(AStr_getData(this));
            AStr_AppendPrint(pStr, "\"len\":%u, ", len);
            crc = AStr_getCrcIEEE(this);
            AStr_AppendPrint(pStr, "\"crc\":%u, ", crc);

            if (len) {
                AStr_AppendA(pStr, "\"data\":\"");
                pWrkStr = AStr_ToChrCon(this);
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    BREAK_FALSE((1 == obj_getRetainCount(pWrkStr)));
                    obj_Release(pWrkStr);
                    pWrkStr = OBJ_NIL;
                }
                AStr_AppendA(pStr, "\"");
            }
            else {
                AStr_AppendA(pStr, ", \"data\":null ");
            }

        }

        return ERESULT_SUCCESS;
    }


    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = AStr_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStr_ToJson(
        ASTR_DATA   *this
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
#endif
        ERESULT         eRc;

#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
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

            eRc = AStr_ToJsonFields(this, pStr);

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

