// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   srcError.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on December 17, 2017 from srcLoc_JSON
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
#include    <srcError_internal.h>
#include    <srcLoc.h>
#include    <hjson.h>
#include    <node.h>
#include    <nodeHash.h>
#include    <utf8.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>




#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /*****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    
    /*****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    SRCERROR_DATA * srcError_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        HJSON_DATA      *pParser;
        NODE_DATA       *pFileNode = OBJ_NIL;
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
        ERESULT         eRc;
        uint16_t        fileIndex = 0;
        int32_t         offset = 0;
        uint32_t        lineNo = 0;
        uint16_t        colNo = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName = OBJ_NIL;
        SRCLOC_DATA     *pSrcLoc = OBJ_NIL;
        SRCERROR_DATA   *pError = OBJ_NIL;
        PATH_DATA       *pPath = path_NewA("?");
        
        pParser = hjson_NewAStr(pString, 4);
        if (OBJ_NIL == pParser) {
            goto exit00;
        }
        pFileNode = hjson_ParseFile(pParser);
        if (OBJ_NIL == pFileNode) {
            goto exit00;
        }
        pHash = node_getData(pFileNode);
        if (OBJ_NIL == pFileNode) {
            goto exit00;
        }
        pError = srcError_New(0, NULL, OBJ_NIL);
        if (OBJ_NIL == pError) {
            goto exit00;
        }
        //fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
        
        eRc = nodeHash_FindA(pHash, "FileIndex", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                fileIndex = AStr_ToInt64(pStr) & 0xFFFFFFFF;
            }
            else {
                fprintf(stderr, "ERROR - lineNo should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "Offset", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                offset = AStr_ToInt64(pStr) & 0xFFFFFFFF;
            }
            else {
                fprintf(stderr, "ERROR - lineNo should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "LineNo", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                lineNo = AStr_ToInt64(pStr) & 0xFFFFFFFF;
            }
            else {
                fprintf(stderr, "ERROR - lineNo should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
        
        eRc = nodeHash_FindA(pHash, "ColNo", &pNode);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pNode = node_getData(pNode);
            pName = node_getName(pNode);
            if (ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer")) {
                pStr = node_getData(pNode);
                colNo = AStr_ToInt64(pStr) & 0xFFFF;
            }
            else {
                fprintf(stderr, "ERROR - colNo should have a integer!\n");
                fprintf(stderr, "%s\n", AStr_getData(nodeHash_ToDebugString(pHash, 0)));
                DEBUG_BREAK();
                goto exit00;
            }
        }
              
        // Return to caller.
    exit00:
        if (pFileNode) {
            obj_Release(pFileNode);
            pFileNode = OBJ_NIL;
        }
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        return pError;
    }
    
    

    SRCERROR_DATA * srcError_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        SRCERROR_DATA   *pObj = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObj = srcError_NewFromJSONString(pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        // Return to caller.
        return pObj;
    }
    
    
    
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = srcError_ToJSON(this);
     @endcode
     @param     this    SRCERROR object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     srcError_ToJSON(
        SRCERROR_DATA   *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !srcError_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{ \"objectType\":\"%s\", \"FileIndex\":%d, \"Offset\":%lld, \"LineNo\":%d, \"ColNo\":%d ",
                     pInfo->pClassName,
                     this->loc.fileIndex,
                     this->loc.offset,
                     this->loc.lineNo,
                     this->loc.colNo
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendA(pStr, "}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

