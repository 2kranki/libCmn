// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   jsonIn.c
 *	Generated 12/21/2017 05:41:06
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
#include        <jsonIn_internal.h>
#include        <AStr_internal.h>
#include        <bitMatrix_internal.h>
#include        <dec.h>
#include        <hex.h>
#include        <name_internal.h>
#include        <node_internal.h>
#include        <nodeArray_internal.h>
#include        <nodeBTP_internal.h>
#include        <nodeHash_internal.h>
#include        <null.h>
#include        <number.h>
#include        <objHash.h>
#include        <SrcLoc.h>
#include        <symAttr.h>
#include        <symEntry.h>
#include        <szData_internal.h>
#include        <szTbl.h>
#include        <token_internal.h>
#include        <utf8_internal.h>
#include        <value.h>
#include        <W32Str.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            jsonIn_task_body(
        void            *pData
    )
    {
        //JSONIN_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    JSONIN_DATA *     jsonIn_Alloc(
    )
    {
        JSONIN_DATA     *this;
        uint32_t        cbSize = sizeof(JSONIN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    JSONIN_DATA *   jsonIn_New(
    )
    {
        JSONIN_DATA     *this;
        
        this = jsonIn_Alloc( );
        if (this) {
            this = jsonIn_Init(this);
        } 
        return this;
    }


    JSONIN_DATA *   jsonIn_NewFromAStr(
        ASTR_DATA       *pStr
    )
    {
        JSONIN_DATA     *this;
        ERESULT         eRc;
        
        this = jsonIn_Alloc( );
        if (this) {
            this = jsonIn_Init(this);
            if (this) {
                eRc = jsonIn_ParseAStr(this, pStr);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }
    
    
    JSONIN_DATA *   jsonIn_NewFromHash(
        NODEHASH_DATA   *pHash
    )
    {
        JSONIN_DATA     *this;
        
        if ((OBJ_NIL == pHash) || !obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            return OBJ_NIL;
        }
        this = jsonIn_Alloc( );
        if (this) {
            this = jsonIn_Init(this);
            if (this) {
                jsonIn_setHash(this, pHash);
            }
        }
        return this;
    }
    
    
    JSONIN_DATA *   jsonIn_NewFromPath(
        PATH_DATA       *pPath
    )
    {
        JSONIN_DATA     *this;
        ERESULT         eRc;
        
        this = jsonIn_Alloc( );
        if (this) {
            this = jsonIn_Init(this);
            if (this) {
                eRc = jsonIn_ParsePath(this, pPath);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }
    
    

    //---------------------------------------------------------------
    //          C h e c k  F o r  S p e c i f i c  D a t a
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * jsonIn_CheckNodeDataForArray(
        NODE_DATA       *pNode
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pObj = node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "array"))) {
            return OBJ_NIL;
        }
        
        pArray = node_getData(pObj);
        if ((OBJ_NIL == pArray) || !obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)) {
            return OBJ_NIL;
        }
        
        return pArray;
    }
    
    
    FALSE_DATA *    jsonIn_CheckNodeDataForFalse(
        NODE_DATA       *pNode
    )
    {
        FALSE_DATA      *pFalse = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pObj = node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "false"))) {
            return OBJ_NIL;
        }
        
        pFalse = node_getData(pObj);
        if ((OBJ_NIL == pFalse) || !obj_IsKindOf(pFalse, OBJ_IDENT_FALSE)) {
            return OBJ_NIL;
        }
        
        return pFalse;
    }
    
    
    
    NODEHASH_DATA * jsonIn_CheckNodeDataForHash(
        NODE_DATA       *pNode
    )
    {
        NODEHASH_DATA   *pHash = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pObj = node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "hash"))) {
            return OBJ_NIL;
        }
        
        pHash = node_getData(pObj);
        if ((OBJ_NIL == pHash) || !obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            return OBJ_NIL;
        }
        
        return pHash;
    }
    
    
    ASTR_DATA *     jsonIn_CheckNodeDataForInteger(
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pObj = node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer"))) {
            return OBJ_NIL;
        }
        
        pStr = node_getData(pObj);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }
        
        return pStr;
    }
    
    
    NULL_DATA *     jsonIn_CheckNodeDataForNull(
        NODE_DATA       *pNode
    )
    {
        NULL_DATA       *pNull = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pObj = node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "null"))) {
            return OBJ_NIL;
        }
        
        pNull = node_getData(pObj);
        if ((OBJ_NIL == pNull) || !obj_IsKindOf(pNull, OBJ_IDENT_NULL)) {
            return OBJ_NIL;
        }
        
        return pNull;
    }
    
    
    ASTR_DATA *     jsonIn_CheckNodeDataForString(
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pObj = node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string"))) {
            return OBJ_NIL;
        }
        
        pStr = node_getData(pObj);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }
        
        return pStr;
    }
    
    
    
    TRUE_DATA *     jsonIn_CheckNodeDataForTrue(
        NODE_DATA       *pNode
    )
    {
        TRUE_DATA       *pTrue = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pObj = node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "true"))) {
            return OBJ_NIL;
        }
        
        pTrue = node_getData(pObj);
        if ((OBJ_NIL == pTrue) || !obj_IsKindOf(pTrue, OBJ_IDENT_TRUE)) {
            return OBJ_NIL;
        }
        
        return pTrue;
    }
    
    

    NODEARRAY_DATA * jsonIn_CheckNodeForArray(
        NODE_DATA       *pNode
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "array"))) {
            return OBJ_NIL;
        }
        
        pArray = node_getData(pNode);
        if ((OBJ_NIL == pArray) || !obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)) {
            return OBJ_NIL;
        }
        
        return pArray;
    }
    
    
    FALSE_DATA *    jsonIn_CheckNodeForFalse(
        NODE_DATA       *pNode
    )
    {
        FALSE_DATA      *pFalse = OBJ_NIL;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "false"))) {
            return OBJ_NIL;
        }
        
        pFalse = node_getData(pNode);
        if ((OBJ_NIL == pFalse) || !obj_IsKindOf(pFalse, OBJ_IDENT_FALSE)) {
            return OBJ_NIL;
        }
        
        return pFalse;
    }
    
    
    
    NODEHASH_DATA * jsonIn_CheckNodeForHash(
        NODE_DATA       *pNode
    )
    {
        NODEHASH_DATA   *pHash = OBJ_NIL;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "hash"))) {
            return OBJ_NIL;
        }
        pHash = node_getData(pNode);
        if ((OBJ_NIL == pHash) || !obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            return OBJ_NIL;
        }
        
        return pHash;
    }
    

    
    ASTR_DATA *     jsonIn_CheckNodeForInteger(
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "integer"))) {
            return OBJ_NIL;
        }
        
        pStr = node_getData(pNode);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }
        
        return pStr;
    }
    
    
    NULL_DATA *     jsonIn_CheckNodeForNull(
        NODE_DATA       *pNode
    )
    {
        NULL_DATA       *pNull = OBJ_NIL;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "null"))) {
            return OBJ_NIL;
        }
        
        pNull = node_getData(pNode);
        if ((OBJ_NIL == pNull) || !obj_IsKindOf(pNull, OBJ_IDENT_NULL)) {
            return OBJ_NIL;
        }
        
        return pNull;
    }
    
    
    ASTR_DATA *     jsonIn_CheckNodeForString(
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "string"))) {
            return OBJ_NIL;
        }
        
        pStr = node_getData(pNode);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }
        
        return pStr;
    }
    
    
    
    TRUE_DATA *     jsonIn_CheckNodeForTrue(
        NODE_DATA       *pNode
    )
    {
        TRUE_DATA       *pTrue = OBJ_NIL;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
#endif
        
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "true"))) {
            return OBJ_NIL;
        }
        
        pTrue = node_getData(pNode);
        if ((OBJ_NIL == pTrue) || !obj_IsKindOf(pTrue, OBJ_IDENT_TRUE)) {
            return OBJ_NIL;
        }
        
        return pTrue;
    }
    
    
    
    NODE_DATA *     jsonIn_NodeFromArray(
        NODEARRAY_DATA  *pArray
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pArray) || !obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)) {
            return OBJ_NIL;
        }
#endif
        
        pNode = node_NewWithUTF8ConAndClass(0, "array", pArray);
        
        return pNode;
    }
    
    
    
    NODE_DATA *     jsonIn_NodeFromHash(
        NODEHASH_DATA   *pHash
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pHash) || !obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            return OBJ_NIL;
        }
#endif
        
        pNode = node_NewWithUTF8ConAndClass(0, "hash", pHash);
        
        return pNode;
    }
    
    
    
    NODE_DATA *     jsonIn_NodeFromString(
        ASTR_DATA       *pStr
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }
#endif
        
        pNode = node_NewWithUTF8ConAndClass(0, "string", pStr);
        
        return pNode;
    }
    
    
    

    
    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         H a s h
    //---------------------------------------------------------------
    
    NODEHASH_DATA * jsonIn_getHash(
        JSONIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pHash;
    }
    
    
    bool            jsonIn_setHash(
        JSONIN_DATA     *this,
        NODEHASH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pHash) {
            obj_Release(this->pHash);
        }
        this->pHash = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                         L i s t
    //---------------------------------------------------------------
    
    OBJLIST_DATA *  jsonIn_getList(
        JSONIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pList;
    }
    
    
    bool            jsonIn_setList(
        JSONIN_DATA     *this,
        OBJLIST_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pList) {
            obj_Release(this->pList);
        }
        this->pList = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        jsonIn_getPriority(
        JSONIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            jsonIn_setPriority(
        JSONIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        jsonIn_getSize(
        JSONIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  jsonIn_getSuperVtbl(
        JSONIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = jsonIn__Assign(this,pOther);
     @endcode 
     @param     this    JSONIN object pointer
     @param     pOther  a pointer to another JSONIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         jsonIn_Assign(
        JSONIN_DATA		*this,
        JSONIN_DATA     *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !jsonIn_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //              C o n f i r m  O b j e c t  T y p e
    //---------------------------------------------------------------
    
    ERESULT         jsonIn_ConfirmObjectType(
        JSONIN_DATA     *this,
        const
        char            *pType
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = jsonIn_FindStringNodeInHashA(this, "objectType", &pStr);
        if (OBJ_NIL == pStr) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        iRc = strcmp(pType, AStr_getData(pStr));
        if (!(0 == iRc)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        jsonIn      *pCopy = jsonIn_Copy(this);
     @endcode 
     @param     this    JSONIN object pointer
     @return    If successful, a JSONIN object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the JSONIN object.
     */
    JSONIN_DATA *   jsonIn_Copy(
        JSONIN_DATA     *this
    )
    {
        JSONIN_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = jsonIn_New( );
        if (pOther) {
            eRc = jsonIn_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            jsonIn_Dealloc(
        OBJ_ID          objId
    )
    {
        JSONIN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        while (objList_getSize(this->pList)) {
            jsonIn_SubobjectEnd(this);
        }
        jsonIn_setHash(this, OBJ_NIL);
        jsonIn_setList(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         jsonIn_Disable(
        JSONIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         jsonIn_Enable(
        JSONIN_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    ERESULT         jsonIn_FindArrayAndVisitInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        ERESULT         (*pVisit)(OBJ_ID, NODE_DATA *),
        OBJ_ID          *pObj
    )
    {
        ERESULT         eRc;
        NODEARRAY_DATA  *pArray = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if(!jsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = nodeHash_FindNodeInHashA(this->pHash, pSectionA, "array", (void **)&pArray);
        if ((ERESULT_FAILED(eRc)) || (OBJ_NIL == pArray)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_NOT_FOUND;
        }
        
        eRc = nodeArray_VisitAscending(pArray, pVisit, pObj);
        
        return eRc;
    }
    
    
    
    ERESULT         jsonIn_FindArrayNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        NODEARRAY_DATA  **ppArray
    )
    {
        ERESULT         eRc;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!jsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = nodeHash_FindNodeInHashA(this->pHash, pSectionA, "array", (void **)&pArray);
        if ((ERESULT_FAILED(eRc)) || (OBJ_NIL == pArray)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_NOT_FOUND;
        }

        if (ppArray)
            *ppArray = pArray;
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         jsonIn_FindNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        const
        char            *pTypeA,
        OBJ_ID          *ppData
    )
    {
        ERESULT         eRc;
        OBJ_ID          pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = nodeHash_FindNodeInHashA(this->pHash, pSectionA, pTypeA, (void **)&pData);
        if ((ERESULT_FAILED(eRc)) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        if (ppData) {
            *ppData = pData;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         jsonIn_FindIntegerNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        int64_t         *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        int64_t         num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = nodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToInt64(pData);
        
        if (pInt) {
            *pInt = num;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         jsonIn_FindNullNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA
    )
    {
        ERESULT         eRc;
        NULL_DATA       *pData;
        
        eRc = nodeHash_FindNodeInHashA(this->pHash, pSectionA, "null", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         jsonIn_FindStringNodeInHashA(
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        ASTR_DATA       **ppStr
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData = OBJ_NIL;
        
        eRc = nodeHash_FindNodeInHashA(this->pHash, pSectionA, "string", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        if (ppStr)
            *ppStr = pData;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    JSONIN_DATA *   jsonIn_Init(
        JSONIN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(JSONIN_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_JSONIN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_JSONIN);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&jsonIn_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        this->pList = objList_New( );

    #ifdef NDEBUG
    #else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "jsonIn::offsetof(eRc) = %lu\n", offsetof(JSONIN_DATA,eRc));
        //fprintf(stderr, "jsonIn::sizeof(JSONIN_DATA) = %lu\n", sizeof(JSONIN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(JSONIN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         jsonIn_IsEnabled(
        JSONIN_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       P a r s e
    //---------------------------------------------------------------
    
    ERESULT         jsonIn_ParseAStr(
        JSONIN_DATA     *this,
        ASTR_DATA       *pStr
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        HJSON_DATA      *pParser;
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (obj_Trace(this)) {
            fprintf(stderr, "jsonIn_ParseAStr: string=%s\n", AStr_getData(pStr));
        }
#endif
        
        pParser = hjson_NewAStr(pStr, 4);
        if (OBJ_NIL == pParser) {
            return ERESULT_OUT_OF_MEMORY;
        }
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            obj_TraceSet(pParser, true);
        }
#endif

        pNode = hjson_ParseFileHash(pParser);
        if (OBJ_NIL == pNode) {
            obj_Release(pParser);
            return ERESULT_PARSE_ERROR;
        }
        
        pHash = jsonIn_CheckNodeForHash(pNode);
        if (OBJ_NIL == pHash) {
            obj_Release(pNode);
            obj_Release(pParser);
            return ERESULT_DATA_ERROR;
        }
        jsonIn_setHash(this, pHash);

        obj_Release(pNode);
        pNode = OBJ_NIL;
        obj_Release(pParser);
        pParser = OBJ_NIL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    OBJ_ID          jsonIn_ParseObject(
        JSONIN_DATA     *this
    )
    {
        ERESULT         eRc;
        OBJ_ID          *pObj = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return pObj;
        }
        if (obj_Trace(this)) {
            fprintf(stderr, "jsonIn_ParseObject:\n");
        }
#endif

        pInfo = obj_getInfo(AStr_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)AStr_ParseObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(bitMatrix_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)bitMatrix_ParseObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(name_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)name_ParseObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(node_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)node_ParseObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(nodeArray_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)nodeArray_ParseObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(nodeBTP_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)nodeBTP_ParseObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(nodeHash_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)nodeHash_ParseJsonObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(szData_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)szData_ParseObject(this);
            return pObj;
        }
        
        pInfo = obj_getInfo(token_Class());
        eRc = jsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)token_ParseObject(this);
            return pObj;
        }
        
        // Return to caller.
        return pObj;
    }
    
    
    ERESULT         jsonIn_ParsePath(
        JSONIN_DATA     *this,
        PATH_DATA       *pPath
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        HJSON_DATA      *pParser;
        NODE_DATA       *pNode;
        NODEHASH_DATA   *pHash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (obj_Trace(this)) {
            fprintf(stderr, "jsonIn_ParseAStr: string=%s\n", path_getData(pPath));
        }
#endif
        
        pParser = hjson_NewFromPath(pPath, 4);
        if (OBJ_NIL == pParser) {
            return ERESULT_OUT_OF_MEMORY;
        }
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            obj_TraceSet(pParser, true);
        }
#endif
        
        pNode = hjson_ParseFileHash(pParser);
        if (OBJ_NIL == pNode) {
            obj_Release(pParser);
            return ERESULT_PARSE_ERROR;
        }
        
        pHash = jsonIn_CheckNodeDataForHash(pNode);
        if (OBJ_NIL == pHash) {
            obj_Release(pNode);
            obj_Release(pParser);
            return ERESULT_DATA_ERROR;
        }
        jsonIn_setHash(this, pHash);
        
        obj_Release(pNode);
        pNode = OBJ_NIL;
        obj_Release(pParser);
        pParser = OBJ_NIL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = jsonIn_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "jsonIn", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          jsonIn_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        JSONIN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)jsonIn_Class();
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return jsonIn_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return jsonIn_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return jsonIn_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return jsonIn_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == jsonIn_ToDebugString)
                    return "ToDebugString";
                if (pData == jsonIn_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                     S u b  O b j e c t
    //---------------------------------------------------------------
    
    ERESULT         jsonIn_SubobjectEnd(
        JSONIN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_FAILURE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (objList_getSize(this->pList) > 0) {
            this->pHash = objList_Tail(this->pList);
            objList_DeleteTail(this->pList);
            eRc = ERESULT_SUCCESS;
        }
        
        return eRc;
    }
    
    
    ERESULT         jsonIn_SubobjectFromHash(
        JSONIN_DATA     *this,
        NODEHASH_DATA   *pHash
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pHash) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_ERROR;
        }
#endif
        
        objList_Add2Tail(this->pList, this->pHash);
        this->pHash = pHash;
        
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         jsonIn_SubobjectInHash(
        JSONIN_DATA     *this,
        const
        char            *pSection
    )
    {
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = nodeHash_FindA(this->pHash, 0, pSection);
        if (OBJ_NIL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pNode = node_getData(pNode);
        if (OBJ_NIL == pNode) {
            return ERESULT_DATA_ERROR;
        }
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "hash"))) {
            return ERESULT_DATA_ERROR;
        }
        
        objList_Add2Tail(this->pList, this->pHash);
        this->pHash = node_getData(pNode);
        
        return ERESULT_SUCCESS;
    }
    
    
    

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = jsonIn_ToDebugString(this,4);
     @endcode 
     @param     this    JSONIN object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     jsonIn_ToDebugString(
        JSONIN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = jsonIn_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{%p(%s)\n",
                    this,
                    pInfo->pClassName
                );

        if (this->pHash) {
            if (((OBJ_DATA *)(this->pHash))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pHash))->pVtbl->pToDebugString(
                                                    this->pHash,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
                pWrkStr = OBJ_NIL;
            }
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     jsonIn_ToJSON(
        JSONIN_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !jsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            jsonIn_Validate(
        JSONIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_JSONIN) )
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if( !(obj_getSize(this) >= sizeof(JSONIN_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


