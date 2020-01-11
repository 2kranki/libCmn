// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   null_JSON.c
 *
 * Created on December 20, 2017 from SrcLoc_json
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
#include    "null_internal.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <dec.h>
#include    <JsonIn_internal.h>
#include    <node.h>
#include    <NodeHash.h>
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
     @return    a new null object if successful, otherwise, OBJ_NIL
     @warning   Returned null object must be released.
     */
    NULL_DATA *     null_ParseObject(
        JSONIN_DATA     *pParser
    )
    {
        ERESULT         eRc;
        NULL_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        
        pInfo = obj_getInfo(null_Class());
        
        eRc = JsonIn_ConfirmObjectType(pParser, pInfo->pClassName);
        if (ERESULT_FAILED(eRc)) {
            fprintf(stderr, "ERROR - objectType is invalid!\n");
            goto exit00;
        }
        
        // Create the object since "objectType" checked out.
        pObject = null_New();
        if (OBJ_NIL == pObject) {
            goto exit00;
        }
        
        // Return to caller.
    exit00:
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    
    

    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    NULL_DATA *     null_NewFromHash(
        NODEHASH_DATA   *pHash
    )
    {
        JSONIN_DATA     *pParser;
        NULL_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        
        pInfo = obj_getInfo(null_Class());
        
        pParser = JsonIn_New();
        if (OBJ_NIL == pParser) {
            return OBJ_NIL;
        }
        JsonIn_setHash(pParser, pHash);
        
        pObject = null_ParseObject(pParser);
        
        // Return to caller.
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    
    
    NULL_DATA *     null_NewFromJSONString(
        ASTR_DATA       *pString
    )
    {
        ERESULT         eRc;
        JSONIN_DATA     *pParser;
        NULL_DATA       *pObject = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;

        pInfo = obj_getInfo(null_Class());

        pParser = JsonIn_New();
        if (OBJ_NIL == pParser) {
            return OBJ_NIL;
        }
        eRc = JsonIn_ParseAStr(pParser, pString);
        if (ERESULT_FAILED(eRc)) {
            return OBJ_NIL;
        }
        
        pObject = null_ParseObject(pParser);
        
        // Return to caller.
        if (pParser) {
            obj_Release(pParser);
            pParser = OBJ_NIL;
        }
        return pObject;
    }
    
    

    NULL_DATA *     null_NewFromJSONStringA(
        const
        char            *pString
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NULL_DATA       *pObj = OBJ_NIL;
        
        if (pString) {
            pStr = AStr_NewA(pString);
            pObj = null_NewFromJSONString(pStr);
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
     ASTR_DATA      *pDesc = null_ToJSON(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     null_ToJSON(
        NULL_DATA       *this
    )
    {
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !null_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        AStr_AppendPrint(pStr, "{\"objectType\":\"%s\"}\n", pInfo->pClassName);
        
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif

