// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   JsonIn.c
 *	Generated 12/30/2019 21:36:00
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
#include        <JsonIn_internal.h>
#include        <AStr_internal.h>
#include        <BitMatrix_internal.h>
#include        <dec.h>
#include        <hex.h>
#include        <hjson.h>
#include        <I32Array_internal.h>
#include        <Name_internal.h>
#include        <Node_internal.h>
#include        <NodeArray_internal.h>
#include        <NodeBT_internal.h>
#include        <NodeHash_internal.h>
#include        <NodeLink_internal.h>
#include        <Null.h>
#include        <Number.h>
#include        <ObjArray_internal.h>
#include        <ObjHash_internal.h>
#include        <ObjList_internal.h>
#include        <ObjMethod_internal.h>
#include        <ObjHash.h>
#include        <Opcode_internal.h>
#include        <SrcError_internal.h>
#include        <SrcErrors_internal.h>
#include        <SrcLoc.h>
#include        <szData_internal.h>
#include        <szTbl.h>
#include        <Token_internal.h>
#include        <TokenList_internal.h>
#include        <trace.h>
#include        <utf8_internal.h>
#include        <Value_internal.h>
#include        <W32Str.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            JsonIn_task_body (
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

    JSONIN_DATA *     JsonIn_Alloc (
        void
    )
    {
        JSONIN_DATA       *this;
        uint32_t        cbSize = sizeof(JSONIN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    JSONIN_DATA *     JsonIn_New (
        void
    )
    {
        JSONIN_DATA       *this;
        
        this = JsonIn_Alloc( );
        if (this) {
            this = JsonIn_Init(this);
        } 
        return this;
    }



    JSONIN_DATA *   JsonIn_NewFromAStr(
        ASTR_DATA       *pStr
    )
    {
        JSONIN_DATA     *this;
        ERESULT         eRc;

        this = JsonIn_Alloc( );
        if (this) {
            this = JsonIn_Init(this);
            if (this) {
                eRc = JsonIn_ParseAStr(this, pStr);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }


    JSONIN_DATA *   JsonIn_NewFromHash(
        NODEHASH_DATA   *pHash
    )
    {
        JSONIN_DATA     *this;

        if ((OBJ_NIL == pHash) || !obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            return OBJ_NIL;
        }
        this = JsonIn_Alloc( );
        if (this) {
            this = JsonIn_Init(this);
            if (this) {
                JsonIn_setHash(this, pHash);
            }
        }
        return this;
    }


    JSONIN_DATA *   JsonIn_NewFromPath (
        PATH_DATA       *pPath
    )
    {
        JSONIN_DATA     *this;
        ERESULT         eRc;

        this = JsonIn_Alloc( );
        if (this) {
            this = JsonIn_Init(this);
            if (this) {
                eRc = JsonIn_ParsePath(this, pPath);
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

    NODEARRAY_DATA * JsonIn_CheckNodeDataForArray (
        NODE_DATA       *pNode
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "array"))) {
            return OBJ_NIL;
        }

        pArray = Node_getData(pObj);
        if ((OBJ_NIL == pArray) || !obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)) {
            return OBJ_NIL;
        }

        return pArray;
    }


    FALSE_DATA *    JsonIn_CheckNodeDataForFalse (
        NODE_DATA       *pNode
    )
    {
        FALSE_DATA      *pFalse = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "false"))) {
            return OBJ_NIL;
        }

        pFalse = Node_getData(pObj);
        if ((OBJ_NIL == pFalse) || !obj_IsKindOf(pFalse, OBJ_IDENT_FALSE)) {
            return OBJ_NIL;
        }

        return pFalse;
    }



    ASTR_DATA *     JsonIn_CheckNodeDataForFloat (
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "float"))) {
            return OBJ_NIL;
        }

        pStr = Node_getData(pObj);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }

        return pStr;
    }


    NODEHASH_DATA * JsonIn_CheckNodeDataForHash (
        NODE_DATA       *pNode
    )
    {
        NODEHASH_DATA   *pHash = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "hash"))) {
            return OBJ_NIL;
        }

        pHash = Node_getData(pObj);
        if ((OBJ_NIL == pHash) || !obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            return OBJ_NIL;
        }

        return pHash;
    }


    ASTR_DATA *     JsonIn_CheckNodeDataForInteger (
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "integer"))) {
            return OBJ_NIL;
        }

        pStr = Node_getData(pObj);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }

        return pStr;
    }


    NULL_DATA *     JsonIn_CheckNodeDataForNull (
        NODE_DATA       *pNode
    )
    {
        NULL_DATA       *pNull = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "null"))) {
            return OBJ_NIL;
        }

        pNull = Node_getData(pObj);
        if ((OBJ_NIL == pNull) || !obj_IsKindOf(pNull, OBJ_IDENT_NULL)) {
            return OBJ_NIL;
        }

        return pNull;
    }


    ASTR_DATA *     JsonIn_CheckNodeDataForString (
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "string"))) {
            return OBJ_NIL;
        }

        pStr = Node_getData(pObj);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }

        return pStr;
    }



    TRUE_DATA *     JsonIn_CheckNodeDataForTrue (
        NODE_DATA       *pNode
    )
    {
        TRUE_DATA       *pTrue = OBJ_NIL;
        OBJ_ID          pObj;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pObj = Node_getData(pNode);
        if ((OBJ_NIL == pObj) || !obj_IsKindOf(pObj, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }
        pName = Node_getName(pObj);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "true"))) {
            return OBJ_NIL;
        }

        pTrue = Node_getData(pObj);
        if ((OBJ_NIL == pTrue) || !obj_IsKindOf(pTrue, OBJ_IDENT_TRUE)) {
            return OBJ_NIL;
        }

        return pTrue;
    }



    NODEARRAY_DATA * JsonIn_CheckNodeForArray (
        NODE_DATA       *pNode
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "array"))) {
            return OBJ_NIL;
        }

        pArray = Node_getData(pNode);
        if ((OBJ_NIL == pArray) || !obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)) {
            return OBJ_NIL;
        }

        return pArray;
    }


    FALSE_DATA *    JsonIn_CheckNodeForFalse (
        NODE_DATA       *pNode
    )
    {
        FALSE_DATA      *pFalse = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "false"))) {
            return OBJ_NIL;
        }

        pFalse = Node_getData(pNode);
        if ((OBJ_NIL == pFalse) || !obj_IsKindOf(pFalse, OBJ_IDENT_FALSE)) {
            return OBJ_NIL;
        }

        return pFalse;
    }



    ASTR_DATA *     JsonIn_CheckNodeForFloat (
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "float"))) {
            return OBJ_NIL;
        }

        pStr = Node_getData(pNode);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }

        return pStr;
    }


    NODEHASH_DATA * JsonIn_CheckNodeForHash (
        NODE_DATA       *pNode
    )
    {
        NODEHASH_DATA   *pHash = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "hash"))) {
            return OBJ_NIL;
        }
        pHash = Node_getData(pNode);
        if ((OBJ_NIL == pHash) || !obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            return OBJ_NIL;
        }

        return pHash;
    }



    ASTR_DATA *     JsonIn_CheckNodeForInteger (
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "integer"))) {
            return OBJ_NIL;
        }

        pStr = Node_getData(pNode);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }

        return pStr;
    }


    NULL_DATA *     JsonIn_CheckNodeForNull (
        NODE_DATA       *pNode
    )
    {
        NULL_DATA       *pNull = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "null"))) {
            return OBJ_NIL;
        }

        pNull = Node_getData(pNode);
        if ((OBJ_NIL == pNull) || !obj_IsKindOf(pNull, OBJ_IDENT_NULL)) {
            return OBJ_NIL;
        }

        return pNull;
    }


    ASTR_DATA *     JsonIn_CheckNodeForString (
        NODE_DATA       *pNode
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "string"))) {
            return OBJ_NIL;
        }

        pStr = Node_getData(pNode);
        if ((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            return OBJ_NIL;
        }

        return pStr;
    }



    TRUE_DATA *     JsonIn_CheckNodeForTrue (
        NODE_DATA       *pNode
    )
    {
        TRUE_DATA       *pTrue = OBJ_NIL;
        NAME_DATA       *pName;

        if ((OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            return OBJ_NIL;
        }

        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "true"))) {
            return OBJ_NIL;
        }

        pTrue = Node_getData(pNode);
        if ((OBJ_NIL == pTrue) || !obj_IsKindOf(pTrue, OBJ_IDENT_TRUE)) {
            return OBJ_NIL;
        }

        return pTrue;
    }



    NODE_DATA *     JsonIn_NodeFromArray (
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

        pNode = Node_NewWithUTF8ConAndClass(0, "array", pArray);

        return pNode;
    }



    NODE_DATA *     JsonIn_NodeFromHash (
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

        pNode = Node_NewWithUTF8ConAndClass(0, "hash", pHash);

        return pNode;
    }



    NODE_DATA *     JsonIn_NodeFromString (
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

        pNode = Node_NewWithUTF8ConAndClass(0, "string", pStr);

        return pNode;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        H a s h
    //---------------------------------------------------------------

    NODEHASH_DATA * JsonIn_getHash (
        JSONIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pHash;
    }


    bool            JsonIn_setHash (
        JSONIN_DATA     *this,
        NODEHASH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_HASH_OWNED
        obj_Retain(pValue);
        if (this->pHash) {
            obj_Release(this->pHash);
        }
#endif
        this->pHash = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                        L i s t
    //---------------------------------------------------------------

    OBJLIST_DATA *  JsonIn_getList (
        JSONIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pList;
    }


    bool            JsonIn_setList (
        JSONIN_DATA     *this,
        OBJLIST_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_LIST_OWNED
        obj_Retain(pValue);
        if (this->pList) {
            obj_Release(this->pList);
        }
#endif
        this->pList = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        JsonIn_getPriority (
        JSONIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            JsonIn_setPriority (
        JSONIN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
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
    
    uint32_t        JsonIn_getSize (
        JSONIN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * JsonIn_getStr (
        JSONIN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        JsonIn_setStr (
        JSONIN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
#endif
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  JsonIn_getSuperVtbl (
        JSONIN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
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
        ERESULT eRc = JsonIn_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another JSONIN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         JsonIn_Assign (
        JSONIN_DATA		*this,
        JSONIN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!JsonIn_Validate(pOther)) {
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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         JsonIn_Compare (
        JSONIN_DATA     *this,
        JSONIN_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!JsonIn_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //              C o n f i r m  O b j e c t  T y p e
    //---------------------------------------------------------------

    ERESULT         JsonIn_ConfirmObjectType (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = JsonIn_FindStringNodeInHashA(this, "objectType", &pStr);
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
        JsonIn      *pCopy = JsonIn_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a JSONIN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    JSONIN_DATA *     JsonIn_Copy (
        JSONIN_DATA       *this
    )
    {
        JSONIN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = JsonIn_New( );
        if (pOther) {
            eRc = JsonIn_Assign(this, pOther);
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

    void            JsonIn_Dealloc (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((JSONIN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        while (ObjList_getSize(this->pList)) {
            JsonIn_SubObjectEnd(this);
        }
        JsonIn_setHash(this, OBJ_NIL);
        JsonIn_setList(this, OBJ_NIL);
        JsonIn_setStr(this, OBJ_NIL);
        if (this->pClasses) {
            obj_Release(this->pClasses);
            this->pClasses = OBJ_NIL;
        }

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

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         JsonIn_Disable (
        JSONIN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!JsonIn_Validate(this)) {
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

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         JsonIn_Enable (
        JSONIN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!JsonIn_Validate(this)) {
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

    ERESULT         JsonIn_FindArrayAndVisitInHashA (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "array", (void **)&pArray);
        if ((ERESULT_FAILED(eRc)) || (OBJ_NIL == pArray)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        if (obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_NOT_FOUND;
        }

        eRc = NodeArray_VisitAscending(pArray, pVisit, pObj);

        return eRc;
    }



    ERESULT         JsonIn_FindArrayNodeInHashA (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "array", (void **)&pArray);
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



    ERESULT         JsonIn_FindAStrNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        ASTR_DATA       **ppStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pData = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pData = AStr_New();
        if (OBJ_NIL == pData) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto Exit00;
        }

        eRc = JsonIn_SubObjectInHash(this, pSectionA);
        if (ERESULT_OK(eRc)) {
            eRc = AStr_ParseJsonFields(this, pData);
            JsonIn_SubObjectEnd(this);
        } else {
            obj_Release(pData);
            pData = OBJ_NIL;
        }

    Exit00:
        if (ppStr) {
            *ppStr = pData;
        }
        return eRc;
    }



    ERESULT         JsonIn_FindFloatNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        double          *pFloat
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        double          num = 0.0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "float", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        sscanf(AStr_getData(pData), "%le", &num);

        if (pFloat) {
            *pFloat = num;
        }
        return ERESULT_SUCCESS;
    }



    ERESULT         JsonIn_FindNodeInHashA (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, pTypeA, (void **)&pData);
        if ((ERESULT_FAILED(eRc)) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        if (ppData) {
            *ppData = pData;
        }
        return ERESULT_SUCCESS;
    }



    ERESULT         JsonIn_FindIntegerNodeInHashA (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToInt64(pData);

        if (pInt) {
            *pInt = num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindI8NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        int8_t          *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        int64_t         num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToInt64(pData);

        if (pInt) {
            *pInt = (int8_t)num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindI16NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        int16_t         *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        int64_t         num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToInt64(pData);

        if (pInt) {
            *pInt = (int16_t)num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindI16ArrayNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        uint16_t        max,
        int16_t         *pArray,
        uint16_t        *pSize
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        uint32_t        i;
        uint16_t        size = 0;
        NODEARRAY_DATA  *pNodeArray;
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        ASTR_DATA       *pStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = JsonIn_SubObjectInHash(this, pSectionA);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        eRc = JsonIn_FindStringNodeInHashA(this, "type", &pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            eRc = ERESULT_DATA_NOT_FOUND;
            goto eom;
        }
        eRc = AStr_CompareA(pData,"I16Array");
        if (eRc != ERESULT_SUCCESS_EQUAL) {
            eRc = ERESULT_DATA_NOT_FOUND;
            goto eom;
        }

        eRc = JsonIn_FindU16NodeInHashA(this, "size", &size);
        if (ERESULT_FAILED(eRc) || (size == 0) || (size > max)) {
            eRc = ERESULT_DATA_OUT_OF_RANGE;
            goto eom;
        }
        TRC_OBJ(this,  "\t\t...size: %u\n", size);

        if (size) {
            eRc = JsonIn_FindArrayNodeInHashA(this, "data", &pNodeArray);
            if (pArray) {
                if (size == NodeArray_getSize(pNodeArray))
                    ;
                else {
                    eRc = ERESULT_DATA_OUT_OF_RANGE;
                    goto eom;
                }
            }
            else {
                eRc = ERESULT_DATA_NOT_FOUND;
                goto eom;
            }

            for(i=0; i<size; i++) {
                //fprintf(stderr, "\t\tLooking for Node(%d)\n", i+1);
                pNode = NodeArray_Get(pNodeArray, i+1);
                if (OBJ_NIL == pNode) {
                    eRc = ERESULT_DATA_NOT_FOUND;
                    goto eom;
                }
                pName = Node_getName(pNode);
                if (ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "integer"))
                    ;
                else {
                    eRc = ERESULT_DATA_NOT_FOUND;
                    goto eom;
                }
                pStr = Node_getData(pNode);
                if (OBJ_NIL == pStr) {
                    eRc = ERESULT_DATA_NOT_FOUND;
                    goto eom;
                }
                TRC_OBJ(this,  "\t\t...found[%d] - %s -- %d\n",
                        i,
                        AStr_getData(pStr),
                        (int16_t)AStr_ToInt64(pStr)
                );
                pArray[i] = (int16_t)AStr_ToInt64(pStr);
            }
        }

        // Return to caller.
    eom:
        eRc = JsonIn_SubObjectEnd(this);
        if (pSize) {
            if (ERESULT_OK(eRc)) {
                *pSize = size;
            } else {
                *pSize = 0;
            }
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindI32NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        int32_t         *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        int64_t         num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToInt64(pData);

        if (pInt) {
            *pInt = (int32_t)num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindI32ArrayNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        uint32_t        max,
        int32_t         *pArray,
        uint32_t        *pSize
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        uint32_t        i;
        uint32_t        size = 0;
        NODEARRAY_DATA  *pNodeArray;
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        ASTR_DATA       *pStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = JsonIn_SubObjectInHash(this, pSectionA);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        eRc = JsonIn_FindStringNodeInHashA(this, "type", &pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            eRc = ERESULT_DATA_NOT_FOUND;
            goto eom;
        }
        eRc = AStr_CompareA(pData,"I32Array");
        if (eRc != ERESULT_SUCCESS_EQUAL) {
            eRc = ERESULT_DATA_NOT_FOUND;
            goto eom;
        }

        eRc = JsonIn_FindU32NodeInHashA(this, "size", &size);
        if (ERESULT_FAILED(eRc) || (size == 0) || (size > max)) {
            eRc = ERESULT_DATA_OUT_OF_RANGE;
            goto eom;
        }
        TRC_OBJ(this,  "\t\t...size: %u\n", size);

        if (size) {
            eRc = JsonIn_FindArrayNodeInHashA(this, "data", &pNodeArray);
            if (pArray) {
                if (size == NodeArray_getSize(pNodeArray))
                    ;
                else {
                    eRc = ERESULT_DATA_OUT_OF_RANGE;
                    goto eom;
                }
            }
            else {
                eRc = ERESULT_DATA_NOT_FOUND;
                goto eom;
            }

            for(i=0; i<size; i++) {
                //fprintf(stderr, "\t\tLooking for Node(%d)\n", i+1);
                pNode = NodeArray_Get(pNodeArray, i+1);
                if (OBJ_NIL == pNode) {
                    eRc = ERESULT_DATA_NOT_FOUND;
                    goto eom;
                }
                pName = Node_getName(pNode);
                if (ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "integer"))
                    ;
                else {
                    eRc = ERESULT_DATA_NOT_FOUND;
                    goto eom;
                }
                pStr = Node_getData(pNode);
                if (OBJ_NIL == pStr) {
                    eRc = ERESULT_DATA_NOT_FOUND;
                    goto eom;
                }
                TRC_OBJ(this,  "\t\t...found[%d] - %s -- %d\n",
                        i,
                        AStr_getData(pStr),
                        (int32_t)AStr_ToInt64(pStr)
                );
                pArray[i] = (int32_t)AStr_ToInt64(pStr);
            }
        }

        // Return to caller.
    eom:
        eRc = JsonIn_SubObjectEnd(this);
        if (pSize) {
            if (ERESULT_OK(eRc)) {
                *pSize = size;
            } else {
                *pSize = 0;
            }
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindI64NodeInHashA (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToInt64(pData);

        if (pInt) {
            *pInt = (int64_t)num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindU8NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        uint8_t         *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        uint64_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToUint64(pData);

        if (pInt) {
            *pInt = (uint8_t)num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindU16NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        uint16_t        *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        uint64_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToUint64(pData);

        if (pInt) {
            *pInt = (uint16_t)num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindU32NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        uint32_t        *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        uint64_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToUint64(pData);

        if (pInt) {
            *pInt = (uint32_t)num;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_FindU64NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        uint64_t        *pInt
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData;
        uint64_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToUint64(pData);

        if (pInt) {
            *pInt = (uint64_t)num;
        }
        return ERESULT_SUCCESS;
    }



    ERESULT         JsonIn_FindNullNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA
    )
    {
        ERESULT         eRc;
        NULL_DATA       *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "null", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        return ERESULT_SUCCESS;
    }



    ERESULT         JsonIn_FindStringNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        ASTR_DATA       **ppStr
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "string", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        if (ppStr)
            *ppStr = pData;
        return ERESULT_SUCCESS;
    }



    ERESULT         JsonIn_FindTrueNodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA
    )
    {
        ERESULT         eRc;
        OBJ_ID          pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = NodeHash_FindNodeInHashA(this->pHash, pSectionA, "true", (void **)&pData);
        if (ERESULT_OK(eRc) && (pData)) {
            return ERESULT_SUCCESS;
        }

        return ERESULT_DATA_NOT_FOUND;
    }



    ERESULT         JsonIn_FindUtf8NodeInHashA (
        JSONIN_DATA     *this,
        const
        char            *pSectionA,
        uint8_t         **ppStrA,
        uint32_t        *pLen
    )
    {
        ERESULT         eRc;
        uint8_t         *pData = NULL;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (ppStrA)
            *ppStrA = NULL;
        if (pLen)
            *pLen = 0;

        eRc = JsonIn_SubObjectInHash(this, pSectionA);
        if (ERESULT_FAILED(eRc)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        pData = utf8_ParseJsonObject(this, &len);
        if ((NULL == pData) || (0 == len)) {
            return ERESULT_DATA_NOT_FOUND;
        }

        eRc = JsonIn_SubObjectEnd(this);

        if (ppStrA)
            *ppStrA = pData;
        if (pLen)
            *pLen = len;
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    JSONIN_DATA *   JsonIn_Init (
        JSONIN_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(JSONIN_DATA);
        //ERESULT         eRc;
        
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
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&JsonIn_Vtbl);
        
        this->pList = ObjList_New( );
        if (OBJ_NIL == this->pList) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "JsonIn::sizeof(JSONIN_DATA) = %lu\n", sizeof(JSONIN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(JSONIN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         JsonIn_IsEnabled (
        JSONIN_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
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

    ERESULT         JsonIn_ParseAStr (
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
        if( !JsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (obj_Trace(this)) {
            fprintf(stderr, "JsonIn_ParseAStr: string=%s\n", AStr_getData(pStr));
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

        pHash = JsonIn_CheckNodeForHash(pNode);
        if (OBJ_NIL == pHash) {
            obj_Release(pNode);
            obj_Release(pParser);
            return ERESULT_DATA_ERROR;
        }
        JsonIn_setHash(this, pHash);

        obj_Release(pNode);
        pNode = OBJ_NIL;
        obj_Release(pParser);
        pParser = OBJ_NIL;

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    OBJ_ID          JsonIn_ParseObject (
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
        if( !JsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return pObj;
        }
        if (obj_Trace(this)) {
            fprintf(stderr, "JsonIn_ParseObject:\n");
        }
#endif

        pInfo = obj_getInfo(AStr_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)AStr_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(BitMatrix_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)BitMatrix_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(I32Array_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)I32Array_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(Name_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)Name_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(Node_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)Node_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(NodeArray_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)NodeArray_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(NodeBT_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)NodeBT_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(NodeHash_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)NodeHash_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(NodeLink_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)NodeLink_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(ObjArray_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)ObjArray_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(ObjHash_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)ObjHash_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(ObjList_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)ObjList_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(ObjMethod_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)ObjMethod_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(Opcode_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)Opcode_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(SrcError_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)SrcError_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(SrcErrors_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)SrcErrors_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(szData_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)szData_ParseObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(Token_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)Token_ParseJsonObject(this);
            return pObj;
        }

        pInfo = obj_getInfo(TokenList_Class());
        eRc = JsonIn_ConfirmObjectType(this, pInfo->pClassName);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pObj = (OBJ_ID)TokenList_ParseJsonObject(this);
            return pObj;
        }

        

        // Return to caller.
        return pObj;
    }


    ERESULT         JsonIn_ParsePath (
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
        if( !JsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (obj_Trace(this)) {
            fprintf(stderr, "JsonIn_ParseAStr: string=%s\n", Path_getData(pPath));
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

        pHash = JsonIn_CheckNodeDataForHash(pNode);
        if (OBJ_NIL == pHash) {
            obj_Release(pNode);
            obj_Release(pParser);
            return ERESULT_DATA_ERROR;
        }
        JsonIn_setHash(this, pHash);

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
        void        *pMethod = JsonIn_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "JsonIn", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          JsonIn_QueryInfo (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(JSONIN_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)JsonIn_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return JsonIn_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return JsonIn_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return JsonIn_ToDebugString;
                        }
#ifdef  JSONIN_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return JsonIn_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == JsonIn_ToDebugString)
                    return "ToDebugString";
#ifdef  JSONIN_JSON_SUPPORT
                if (pData == JsonIn_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  R e g i s t e r  C l a s s
    //---------------------------------------------------------------

    ERESULT         JsonIn_RegisterClass (
        JSONIN_DATA     *this,
        OBJMETHOD_DATA  *pCls
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (OBJ_NIL == this->pClasses) {
            this->pClasses = ObjArray_New();
            if (OBJ_NIL == this->pClasses) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     S u b  O b j e c t
    //---------------------------------------------------------------

    ERESULT         JsonIn_SubObjectEnd (
        JSONIN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_FAILURE;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !JsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (ObjList_getSize(this->pList) > 0) {
            this->pHash = ObjList_Tail(this->pList);
            ObjList_DeleteTail(this->pList);
            eRc = ERESULT_SUCCESS;
        }

        return eRc;
    }


    ERESULT         JsonIn_SubObjectFromHash (
        JSONIN_DATA     *this,
        NODEHASH_DATA   *pHash
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !JsonIn_Validate(this) ) {
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

        ObjList_Add2Tail(this->pList, this->pHash);
        this->pHash = pHash;

        return ERESULT_SUCCESS;
    }


    ERESULT         JsonIn_SubObjectInHash (
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
        if( !JsonIn_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNode = NodeHash_FindA(this->pHash, 0, pSection);
        if (OBJ_NIL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pNode = Node_getData(pNode);
        if (OBJ_NIL == pNode) {
            return ERESULT_DATA_ERROR;
        }
        pName = Node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "hash"))) {
            return ERESULT_DATA_ERROR;
        }

        ObjList_Add2Tail(this->pList, this->pHash);
        this->pHash = Node_getData(pNode);

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  JSONIN_JSON_SUPPORT
     ASTR_DATA *     JsonIn_ToJson (
        JSONIN_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = JsonIn_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     JsonIn_ToDebugString (
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
        if (!JsonIn_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    JsonIn_getSize(this),
                    obj_getRetainCount(this)
            );

        if (this->pHash) {
            if (((OBJ_DATA *)(this->pHash))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pHash))->pVtbl->pToDebugString(
                                                    this->pHash,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            JsonIn_Validate (
        JSONIN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_JSONIN))
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


        if (!(obj_getSize(this) >= sizeof(JSONIN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


