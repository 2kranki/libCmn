// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   szData.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on December 30, 2014
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
#include    <szData_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dec_internal.h>
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <srcLoc_internal.h>
#include    <szTbl.h>
#include    <utf8_internal.h>




#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    SZDATA_DATA *   szData_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SZDATA_DATA     *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        uint32_t        cls = 0;
        int64_t         intIn = 0;
        OBJ_ID          pObj = OBJ_NIL;
        uint8_t         *pUtf8;
        SRCLOC_DATA     *pSrc = OBJ_NIL;
        
        pInfo = obj_getInfo(szData_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        // Create the initial object once the key is established.
        eRc = jsonIn_SubobjectInHash(pParser, "name");
        if (ERESULT_FAILED(eRc))
            ;
        else {
            pUtf8 = utf8_ParseObject(pParser, NULL);
            jsonIn_SubobjectEnd(pParser);
            if (pUtf8) {
                pObject = szData_NewA((char *)pUtf8);
                mem_Free(pUtf8);
                pUtf8 = NULL;
            }
        }
        
        // Now add this object's other fields.
        if (pObject) {
            eRc  = jsonIn_FindIntegerNodeInHashA(pParser, "class", &intIn);
            cls = (uint32_t)intIn;
            szData_setClass(pObject, cls);
            
            eRc = jsonIn_SubobjectInHash(pParser, "data");
            if (ERESULT_FAILED(eRc))
                ;
            else {
                pObj = jsonIn_ParseObject(pParser);
                jsonIn_SubobjectEnd(pParser);
                if (pObj) {
                    szData_setData(pObject, pObj);
                    obj_Release(pObj);
                    pObj = OBJ_NIL;
                }
            }
        }
        
        // Return to caller.
    exit00:
        if (pSrc) {
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        return pObject;
    }
    
    
    

    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    SZDATA_DATA *   szData_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        SZDATA_DATA     *pData = OBJ_NIL;
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pData = szData_ParseObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pData;
    }
    
    

    SZDATA_DATA *   szData_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SZDATA_DATA     *pData = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pData = szData_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pData;
    }
    
    
    
    ASTR_DATA *     szData_ToJSON(
        SZDATA_DATA     *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        const
        OBJ_IUNKNOWN    *pUnk;
        const
        char            *pConStr;
        ASTR_DATA       *pWrkStr;
        ASTR_DATA *     (*pToJSON)(OBJ_ID);

#ifdef NDEBUG
#else
        if( !szData_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr,
                         "{\"objectType\":\"%s\", \"class\":%d, ",
                         pInfo->pClassName,
                         this->cls
        );
       
        pConStr = szTbl_TokenToString(OBJ_NIL, this->token);
        if (pConStr) {
            pWrkStr = utf8_DataToJSON(pConStr);
            AStr_AppendPrint(pStr, "\"name\":%s, ", AStr_getData(pWrkStr));
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
        }
        else {
            DEBUG_BREAK();
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        if (this->pData) {
            pUnk = obj_getVtbl(this->pData);
            if (pUnk->pQueryInfo) {
                pToJSON = pUnk->pQueryInfo(this->pData, OBJ_QUERYINFO_TYPE_METHOD, "ToJSON");
                if (pToJSON) {
                    pWrkStr = pToJSON(this->pData);
                    if (pWrkStr) {
                        AStr_AppendPrint(pStr, "\"data\":%s ", AStr_getData(pWrkStr));
                        obj_Release(pWrkStr);
                        pWrkStr = OBJ_NIL;
                        goto dataOK;
                    }
                }
            }
            this->eRc = ERESULT_DATA_ERROR;
            obj_Release(pStr);
            pStr = OBJ_NIL;
            return pStr;
        }
    dataOK:

        if (pStr)
            AStr_AppendA(pStr, "}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

