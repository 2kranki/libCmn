// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   DirEntry_json.c
 *
 *	Generated 01/28/2020 23:56:00
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
#include    <DirEntry_internal.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <AStr_internal.h>
#include    <dec.h>
#include    <JsonIn.h>
#include    <JsonOut.h>
#include    <Node.h>
#include    <NodeHash.h>
#include    <path_internal.h>
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
    ERESULT     DirEntry_ParseJsonFields(
        JSONIN_DATA     *pParser,
        DIRENTRY_DATA     *pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(DirEntry_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        (void)JsonIn_FindU16NodeInHashA(pParser, "type", &pObject->type);
        (void)JsonIn_FindU32NodeInHashA(pParser, "attr", &pObject->attr);
        (void)JsonIn_FindU32NodeInHashA(pParser, "userID", &pObject->userID);
        (void)JsonIn_FindU32NodeInHashA(pParser, "groupID", &pObject->groupID);
        (void)JsonIn_FindU32NodeInHashA(pParser, "genNum", &pObject->genNum);
        (void)JsonIn_FindU32NodeInHashA(pParser, "eaSize", &pObject->eaSize);
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        (void)JsonIn_FindIntegerNodeInHashA(pParser, "fileSize", &pObject->fileSize);
#endif
#if     defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        (void)JsonIn_FindIntegerNodeInHashA(pParser, "fileSize", &pObject->fileSize);
#endif

        eRc = JsonIn_SubObjectInHash(pParser, "FullPath");
        pObject->pFullPath = path_ParseJsonObject(pParser);
        JsonIn_SubObjectEnd(pParser);

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
    DIRENTRY_DATA * DirEntry_ParseJsonObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        DIRENTRY_DATA   *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //int64_t         intIn;
        //ASTR_DATA       *pWrk;

        pInfo = obj_getInfo(DirEntry_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }

        pObject = DirEntry_New( );
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        eRc =  DirEntry_ParseJsonFields(pParser, pObject);

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
    

    DIRENTRY_DATA *   DirEntry_NewFromJsonString(
        ASTR_DATA       *pString
    )
    {
        JSONIN_DATA     *pParser;
        ERESULT         eRc;
        DIRENTRY_DATA   *pObject = OBJ_NIL;
        
        pParser = JsonIn_New();
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            goto exit00;
        }
        
        pObject = DirEntry_ParseJsonObject(pParser);
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    DIRENTRY_DATA * DirEntry_NewFromJsonStringA(
        const
        char            *pStringA
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        DIRENTRY_DATA   *pObject = OBJ_NIL;
        
        if (pStringA) {
            pStr = AStr_NewA(pStringA);
            pObject = DirEntry_NewFromJsonString(pStr);
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
     ASTR_DATA      *pDesc = DirEntry_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     DirEntry_ToJson(
        DIRENTRY_DATA   *this
    )
    {
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;

#ifdef NDEBUG
#else
        if( !DirEntry_Validate(this) ) {
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
            
            AStr_AppendPrint(pStr,
                             "\t\"type\":%d, "
                             "\"attr\":%d, "
                             "\"userID\":%d, "
                             "\"groupID\":%d "
                             "\"genNum\":%d "
                             "\"eaSize\":%d\n",
                             this->type,
                             this->attr,
                             this->userID,
                             this->groupID,
                             this->genNum,
                             this->eaSize
            );
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            JsonOut_Append_i64("fileSize", this->fileSize, pStr);
#endif
#if     defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
            JsonOut_Append_i64("fileSize", this->fileSize, pStr);
#endif
            JsonOut_Append_Object("FullPath", this->pFullPath, pStr);
            JsonOut_Append_Object("Drive", this->pDrive, pStr);
            JsonOut_Append_Object("Dir", this->pDir, pStr);
            JsonOut_Append_Object("FileName", this->pFileName, pStr);
            JsonOut_Append_Object("ShortName", this->pShortName, pStr);
            JsonOut_Append_Object("CreationTime", this->pCreationTime, pStr);
            JsonOut_Append_Object("ModifiedTime", this->pModifiedTime, pStr);
            JsonOut_Append_Object("StatusChangeTime", this->pStatusChangeTime, pStr);

            AStr_AppendA(pStr, "}\n");
        }

        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

