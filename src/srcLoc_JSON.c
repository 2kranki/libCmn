// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcLoc.c
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
#include    <srcLoc_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dec.h>
#include    <jsonIn.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <utf8.h>




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
     @warning   Returned object must be released.
     */
    SRCLOC_DATA *   srcLoc_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        SRCLOC_DATA     *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        int64_t         intIn;

        pInfo = obj_getInfo(srcLoc_Class());
        
        eRc = jsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        

        pObject = srcLoc_Alloc( );
        pObject = srcLoc_Init(pObject);
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "fileIndex", &intIn);
        pObject->pData->fileIndex = (uint16_t)intIn;
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "offset", &pObject->pData->offset);
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "lineNo", &intIn);
        pObject->pData->lineNo = (uint32_t)intIn;
        eRc = jsonIn_FindIntegerNodeInHashA(pParser, "colNo", &intIn);
        pObject->pData->colNo = (uint16_t)intIn;

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
    

    SRCLOC_DATA *   srcLoc_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        SRCLOC_DATA     *pObject = OBJ_NIL;
        
        pParser = jsonIn_New();
        eRc = jsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = srcLoc_ParseObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    SRCLOC_DATA *   srcLoc_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SRCLOC_DATA     *pSrcLoc = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pSrcLoc = srcLoc_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pSrcLoc;
    }
    
    
    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = srcLoc_ToJSON(this);
     @endcode
     @param     this    SRCLOC object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcLoc_ToJSON(
        SRCLOC_DATA     *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !srcLoc_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr,
                         "{ \"objectType\":\"%s\", "
                         "\"fileIndex\":%d, "
                         "\"offset\":%lld, "
                         "\"lineNo\":%d, "
                         "\"colNo\":%d "
                         "}\n",
                         pInfo->pClassName,
                         this->pData->fileIndex,
                         this->pData->offset,
                         this->pData->lineNo,
                         this->pData->colNo
        );
        
        
        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

