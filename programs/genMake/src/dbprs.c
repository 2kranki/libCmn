// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   dbprs.c
 *	Generated 09/04/2018 13:50:27
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
#include        <dbprs_internal.h>
#include        <NodeBase.h>
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <NodeObj.h>
#include        <NodePgm.h>
#include        <NodeRtn.h>
#include        <srcErrors.h>
#include        <trace.h>
#include        <NodeTest.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //              A c c u m u l a t e  S t r i n g s
    //---------------------------------------------------------------
    
    /*!
     Given an node array of strings accumulate them into the given
     ASTR array.
     @param     this    DBPRS object pointer
     @return    If successful, a DBPRS object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ERESULT         dbprs_AccumStrings(
        DBPRS_DATA      *this,
        NODEARRAY_DATA  *pNodes,
        ASTRARRAY_DATA  *pArray
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODE_DATA       *pNode;
        uint32_t        i;
        uint32_t        iMax;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNodes) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == pArray) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        iMax = nodeArray_getSize(pNodes);
        for (i=0; i<iMax; i++) {
            pNode = nodeArray_Get(pNodes, i+1);
            if (pNode) {
                pStr = jsonIn_CheckNodeForString(pNode);
                if (pStr) {
                    eRc = AStrArray_AppendStr(pArray, pStr, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    /*!
     Dependencies and Extra Source files are common to several
     different type, so, we parse them here and accumulate
     them in the given node.
     @param     this    object pointer
     @param     pNode   Input Node to be searched and parsed
     @param     ppBase  Base Node to be filled in with the data or released.
     @param     ppHash  Hash Node if found
     @return    If successful, a DBPRS object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ERESULT         dbprs_ParseSubObj(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode,
        NODEBASE_DATA   **ppBase,
        NODEHASH_DATA   **ppHash
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEARRAY_DATA  *pArray;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pHashItem;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == ppBase) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (OBJ_NIL == *ppBase) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (jsonIn_CheckNodeForNull(pNode)) {
            return ERESULT_SUCCESS;
        }
        else if (jsonIn_CheckNodeForFalse(pNode)) {
            obj_Release(*ppBase);
            *ppBase = OBJ_NIL;
            return ERESULT_SUCCESS;
        }
        else if (jsonIn_CheckNodeForTrue(pNode)) {
            return ERESULT_SUCCESS;
        }
        pArray = jsonIn_CheckNodeForArray(pNode);
        if (pArray) {
            // We have an array of Dependencies. So, add them to the base routine.
            eRc = dbprs_AccumStrings(this, node_getData(pNode), NodeBase_getDeps(*ppBase));
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
            return ERESULT_SUCCESS;
        }
        pHash = jsonIn_CheckNodeForHash(pNode);
        if (pHash) {
            // Ok, we have a hash, so there might a lot to parse here.
            if (ppHash) {
                *ppHash = pHash;
            }
            
            pHashItem = nodeHash_FindA(pHash, 0, "deps");
            if (pHashItem) {
                pArray = jsonIn_CheckNodeDataForArray(pHashItem);
                if (pArray) {
                    eRc = dbprs_AccumStrings(this, pArray, NodeBase_getDeps(*ppBase));
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }

            pHashItem = nodeHash_FindA(pHash, 0, "srcs");
            if (pHashItem) {
                pArray = jsonIn_CheckNodeDataForArray(pHashItem);
                if (pArray) {
                    eRc = dbprs_AccumStrings(this, pArray, NodeBase_getSrcs(*ppBase));
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
            
            pHashItem = nodeHash_FindA(pHash, 0, "reqArch");
            if (pHashItem) {
                ASTR_DATA       *pStr = jsonIn_CheckNodeForString(node_getData(pHashItem));
                if (pStr) {
                    eRc = NodeBase_setReqArch(*ppBase, pStr);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
            
            pHashItem = nodeHash_FindA(pHash, 0, "reqOS");
            if (pHashItem) {
                ASTR_DATA       *pStr = jsonIn_CheckNodeForString(node_getData(pHashItem));
                if (pStr) {
                    eRc = NodeBase_setReqOS(*ppBase, pStr);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
            
        }    // End of Hash Checking

        // Return to caller.
        return eRc;
    }
            
            
            



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    DBPRS_DATA *     dbprs_Alloc(
        void
    )
    {
        DBPRS_DATA       *this;
        uint32_t        cbSize = sizeof(DBPRS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }


    //---------------------------------------------------------------
    //           I n p u t  F i l e  t o  J S O N
    //---------------------------------------------------------------

    ERESULT         dbprs_InputFileToJSON(
        PATH_DATA       *pPath,
        NODE_DATA       **ppNodes
    )
    {
        HJSON_DATA      *pObj = OBJ_NIL;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pNodes = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif

        pObj = hjson_NewFromPath(pPath, 4);
        if (pObj) {
            pNodes = hjson_ParseFileHash(pObj);
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        srcErrors_ExitOnFatal(OBJ_NIL);

        if (pNodes) {
            pHash = node_getData(pNodes);
            if (OBJ_NIL == pHash) {
                fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
                exit(12);
            }
            if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
                fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
                exit(12);
            }
        }
        else {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
        }

        // Return to caller.
        if (ppNodes) {
            *ppNodes = pNodes;
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         dbprs_InputStrToJSON(
        const
        char            *pStrA,
        NODE_DATA       **ppNodes
    )
    {
        HJSON_DATA      *pObj = OBJ_NIL;
        NODEHASH_DATA   *pHash;
        NODE_DATA       *pFileNode = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (NULL == pStrA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif

        pObj = hjson_NewA(pStrA, 4);
        if (pObj) {
            pFileNode = hjson_ParseFileHash(pObj);
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        srcErrors_ExitOnFatal(OBJ_NIL);

        if (pFileNode) {
            pHash = node_getData(pFileNode);
            if (OBJ_NIL == pHash) {
                fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
                exit(12);
            }
            if (!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
                fprintf(stderr, "ERROR - Missing JSON Hash to process\n\n\n");
                exit(12);
            }
        }
        else {
            fprintf(stderr, "ERROR - No JSON Nodes to process\n\n\n");
            exit(12);
        }

        // Return to caller.
        if (ppNodes) {
            *ppNodes = pFileNode;
        }
        return ERESULT_SUCCESS;
    }



    DBPRS_DATA *     dbprs_New(
        void
    )
    {
        DBPRS_DATA       *this;
        
        this = dbprs_Alloc( );
        if (this) {
            this = dbprs_Init(this);
        } 
        return this;
    }


    DBPRS_DATA *    dbprs_NewWithDictAndGen(
        NODEHASH_DATA   *pDict,
        GENBASE_DATA    *pGen
    )
    {
        DBPRS_DATA       *this;
        
        this = dbprs_Alloc( );
        if (this) {
            this = dbprs_Init(this);
            if (this) {
                dbprs_setDict(this, pDict);
                dbprs_setGen(this, pGen);
            }
        }
        return this;
    }
    
    

    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  D i c t i o n a r y
    //---------------------------------------------------------------
    
    NODEHASH_DATA * dbprs_getDict(
        DBPRS_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pDict;
    }
    
    
    bool            dbprs_setDict(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDict) {
            obj_Release(this->pDict);
        }
        this->pDict = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                           G e n
    //---------------------------------------------------------------
    
    GENBASE_DATA * dbprs_getGen(
        DBPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pGen;
    }
    
    
    bool            dbprs_setGen(
        DBPRS_DATA      *this,
        GENBASE_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pGen) {
            obj_Release(this->pGen);
        }
        this->pGen = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      J s o n  I n
    //---------------------------------------------------------------
    
    JSONIN_DATA *   dbprs_getJson(
        DBPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pJson;
    }
    
    
    bool            dbprs_setJson(
        DBPRS_DATA      *this,
        JSONIN_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pJson) {
            obj_Release(this->pJson);
        }
        this->pJson = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                           N o d e s
    //---------------------------------------------------------------
    
    NODE_DATA *     dbprs_getNodes(
        DBPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pNodes;
    }
    
    
    bool            dbprs_setNodes(
        DBPRS_DATA      *this,
        NODE_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pNodes) {
            obj_Release(this->pNodes);
        }
        this->pNodes = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        dbprs_getPriority(
        DBPRS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            dbprs_setPriority(
        DBPRS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
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
    
    uint32_t        dbprs_getSize(
        DBPRS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     dbprs_getStr(
        DBPRS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        dbprs_setStr(
        DBPRS_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  dbprs_getSuperVtbl(
        DBPRS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
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
        ERESULT eRc = dbprs_Assign(this,pOther);
     @endcode 
     @param     this    DBPRS object pointer
     @param     pOther  a pointer to another DBPRS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         dbprs_Assign(
        DBPRS_DATA		*this,
        DBPRS_DATA      *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !dbprs_Validate(pOther) ) {
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
    ERESULT         dbprs_Compare(
        DBPRS_DATA     *this,
        DBPRS_DATA     *pOther
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
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !dbprs_Validate(pOther) ) {
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
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        dbprs      *pCopy = dbprs_Copy(this);
     @endcode 
     @param     this    DBPRS object pointer
     @return    If successful, a DBPRS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    DBPRS_DATA *     dbprs_Copy(
        DBPRS_DATA       *this
    )
    {
        DBPRS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = dbprs_New( );
        if (pOther) {
            eRc = dbprs_Assign(this, pOther);
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

    void            dbprs_Dealloc(
        OBJ_ID          objId
    )
    {
        DBPRS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((DBPRS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        dbprs_setDict(this, OBJ_NIL);
        dbprs_setGen(this, OBJ_NIL);
        dbprs_setJson(this, OBJ_NIL);
        dbprs_setNodes(this, OBJ_NIL);
        dbprs_setStr(this, OBJ_NIL);

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

    ERESULT         dbprs_Disable(
        DBPRS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !dbprs_Validate(this) ) {
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

    ERESULT         dbprs_Enable(
        DBPRS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !dbprs_Validate(this) ) {
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
    //                       F i n a l i z e
    //---------------------------------------------------------------
    
    ERESULT         dbprs_Finalize(
        DBPRS_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = ((GENBASE_VTBL *)obj_getVtbl(this->pGen))->pGenFinal(this->pGen);
        if (pStr) {
            AStr_Append(this->pStr, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            eRc = ERESULT_SUCCESS;
        }

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    DBPRS_DATA *   dbprs_Init(
        DBPRS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(DBPRS_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_DBPRS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_DBPRS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&dbprs_Vtbl);
        
        this->pStr = AStr_New( );
        if (OBJ_NIL == this->pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "dbprs::sizeof(DBPRS_DATA) = %lu\n", sizeof(DBPRS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(DBPRS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         dbprs_IsEnabled(
        DBPRS_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
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
    //                  P a r s e  L i b r a r y
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseLibrary(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pHash
    )
    {
        ERESULT         eRc;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        JSONIN_DATA     *pJsonIn = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pHash) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if(!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_NULL(this->pDict);
#endif
        
        pJsonIn = jsonIn_NewFromHash(pHash);
        if(OBJ_NIL == pJsonIn) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        
        genBase_DictAddA(this->pGen, namePrefixID, "lib");
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, namePrefixID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAdd(this->pGen, namePrefixID, pStr);
        }

        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, nameID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAdd(this->pGen, nameID, pStr);
        }
        
        eRc = jsonIn_FindArrayNodeInHashA(pJsonIn, libDepsID, &pArray);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_setLibDeps(this->pGen, pArray);
        }
        
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, libBaseID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAdd(this->pGen, libBaseID, pStr);
        }
        
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, objBaseID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAdd(this->pGen, objBaseID, pStr);
        }
        
        genBase_setMakeType(this->pGen, GENMAKE_TYPE_LIB);
        pStr = ((GENBASE_VTBL *)obj_getVtbl(this->pGen))->pGenInitial(this->pGen);
        if (pStr) {
            AStr_Append(this->pStr, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            eRc = ERESULT_SUCCESS;
        }

        // Return to caller.
        obj_Release(pJsonIn);
        pJsonIn = OBJ_NIL;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  O b j e c t
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseObject(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode,
        NODEARRAY_DATA  **ppNodes
    )
    {
        ERESULT         eRc;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        ASTR_DATA       *pNameH = OBJ_NIL;
        ASTR_DATA       *pNameInternalH = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        NODEARRAY_DATA  *pNodes = OBJ_NIL;
        NODERTN_DATA    *pRtn = OBJ_NIL;        // Primary Object
        NODERTN_DATA    *pRtnObj = OBJ_NIL;     // Object's Object
        NODERTN_DATA    *pRtnJSON = OBJ_NIL;    // Object's JSON methods
        NODETEST_DATA   *pTst = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!dbprs_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (ppNodes) {
            *ppNodes = OBJ_NIL;
        }
        
        // The node passed in has its name being the object's name and
        // its data is a node hash.
        pName = node_getNameStr(pNode);
        if (OBJ_NIL == pName) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        pNameH = AStr_Copy(pName);
        if (OBJ_NIL == pNameH) {
            DEBUG_BREAK();
            eRc = ERESULT_DATA_MISSING;
            goto errorExit;
        }
        eRc = AStr_AppendA(pNameH, ".h");
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        pNameInternalH = AStr_Copy(pName);
        if (OBJ_NIL == pNameH) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        eRc = AStr_AppendA(pNameInternalH, "_internal.h");
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }

        // Set up the primary node.
        pRtn = NodeRtn_New();
        if (OBJ_NIL == pRtn) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        NodeRtn_setName(pRtn, pName);
        eRc = NodeRtn_AppendDeps(pRtn, pNameH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        eRc = NodeRtn_AppendDeps(pRtn, pNameInternalH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }

        // Set up the optional JSON Node.
        pRtnJSON = NodeRtn_New();
        if (OBJ_NIL == pRtnJSON) {
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        pStr = AStr_Copy(pName);
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        eRc = AStr_AppendA(pStr, "_JSON");
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        NodeRtn_setName(pRtnJSON, pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = NodeRtn_AppendDeps(pRtnJSON, pNameH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        eRc = NodeRtn_AppendDeps(pRtnJSON, pNameInternalH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }

        // Set up the Object Node.
        pRtnObj = NodeRtn_New();
        if (OBJ_NIL == pRtnObj) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        pStr = AStr_Copy(pName);
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        eRc = AStr_AppendA(pStr, "_object");
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        NodeRtn_setName(pRtnObj, pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = NodeRtn_AppendDeps(pRtnObj, pNameH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        eRc = NodeRtn_AppendDeps(pRtnObj, pNameInternalH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }

        // Set up the Optional Test Node. The default is
        // for it to be provided.  It is only gotten rid
        // of if "test=false" is found.
        pTst = NodeTest_New();
        if (OBJ_NIL == pRtn) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        pStr = AStr_Copy(pName);
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        eRc = AStr_AppendA(pStr, "_test");
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        NodeTest_setName(pTst, pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = NodeTest_AppendDeps(pTst, pNameH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        eRc = NodeTest_AppendDeps(pTst, pNameInternalH);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }

        pHash = OBJ_NIL;
        eRc = dbprs_ParseSubObj(this, node_getData(pNode),
                                        (NODEBASE_DATA **)&pRtn, &pHash);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        if (pHash) {
            NODE_DATA       *pHashNode;
            pHashNode = nodeHash_FindA(pHash, 0, "json");
            if (pHashNode) {
                eRc = dbprs_ParseSubObj(this, node_getData(pHashNode),
                                            (NODEBASE_DATA **)&pRtnJSON, NULL);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    goto errorExit;
                }
            }
            else {
                obj_Release(pRtnJSON);
                pRtnJSON = OBJ_NIL;
            }
            pHashNode = nodeHash_FindA(pHash, 0, "test");
            if (pHashNode) {
                eRc = dbprs_ParseSubObj(this, node_getData(pHashNode),
                                            (NODEBASE_DATA **)&pTst, NULL);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    goto errorExit;
                }
            }
        }
        else {
            obj_Release(pRtnJSON);
            pRtnJSON = OBJ_NIL;
        }

        // Create a node array and add the routine/test nodes to the array.
        pNodes = nodeArray_New();
        if (OBJ_NIL == pNodes) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        eRc = NodeBase_SortArrays(NodeRtn_getNodeBase(pRtn));
        eRc = nodeArray_AppendNode(pNodes, NodeRtn_getNode(pRtn), NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pNodes);
            goto errorExit;
        }
        eRc = NodeBase_SortArrays(NodeRtn_getNodeBase(pRtnObj));
        eRc = nodeArray_AppendNode(pNodes, NodeRtn_getNode(pRtnObj), NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pNodes);
            goto errorExit;
        }
        if (pRtnJSON) {
            eRc = NodeBase_SortArrays(NodeRtn_getNodeBase(pRtnJSON));
            eRc = nodeArray_AppendNode(pNodes, NodeRtn_getNode(pRtnJSON), NULL);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pNodes);
                goto errorExit;
            }
        }
        if (pTst) {
            eRc = NodeBase_SortArrays(NodeTest_getNodeBase(pTst));
            eRc = nodeArray_AppendNode(pNodes, NodeTest_getNode(pTst), NULL);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pNodes);
                goto errorExit;
            }
        }

        // Return to caller.
        eRc = ERESULT_SUCCESS;
        if (ppNodes) {
            *ppNodes = pNodes;
        }
    errorExit:
        obj_Release(pNameInternalH);
        obj_Release(pNameH);
        obj_Release(pName);
        obj_Release(pRtn);
        obj_Release(pRtnJSON);
        obj_Release(pRtnObj);
        obj_Release(pTst);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  O b j e c t s
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseObjects(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pHash,
        NODEARRAY_DATA  **ppArray
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        NODEARRAY_DATA  *pItems = OBJ_NIL;
        NODEARRAY_DATA  *pWork = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pHash) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if(!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (ppArray) {
            *ppArray = pItems;
        }
        pItems = nodeArray_New();
        if (OBJ_NIL == pItems) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        pArray = nodeHash_Nodes(pHash);
        if (pArray) {
            iMax = nodeArray_getSize(pArray);
            for(i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(pArray, (i+1));
                if (pNode) {
                    eRc = dbprs_ParseObject(this, pNode, &pWork);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pItems);
                        pItems = OBJ_NIL;
                        break;
                    }
                    else {
                        eRc = nodeArray_Append(pItems, pWork);
                        obj_Release(pWork);
                        pWork = OBJ_NIL;
                    }
                }
            }
            obj_Release(pArray);
            pArray = OBJ_NIL;
        }

        // Return to caller.
        if (ppArray) {
            *ppArray = pItems;
        }
        else {
            obj_Release(pItems);
            pItems = OBJ_NIL;
        }
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  P r o g r a m
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseProgram(
        DBPRS_DATA      *this,
        NODEHASH_DATA   *pHash
    )
    {
        ERESULT         eRc;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        //ASTR_DATA       *pStrWrk = OBJ_NIL;
        JSONIN_DATA     *pJsonIn = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pHash) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if(!obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        BREAK_NULL(this->pDict);
#endif
        
        pJsonIn = jsonIn_NewFromHash(pHash);
        if(OBJ_NIL == pJsonIn) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        
        genBase_DictAddUpdateA(this->pGen, namePrefixID, "lib");
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, namePrefixID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAddUpdate(this->pGen, namePrefixID, pStr);
        }
        
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, nameID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAddUpdate(this->pGen, nameID, pStr);
        }
        
        eRc = jsonIn_FindArrayNodeInHashA(pJsonIn, libDepsID, &pArray);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_setLibDeps(this->pGen, pArray);
        }
        
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, libBaseID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAddUpdate(this->pGen, libBaseID, pStr);
        }
        
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, mainID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAddUpdate(this->pGen, mainID, pStr);
        }
        
        eRc = jsonIn_FindStringNodeInHashA(pJsonIn, objBaseID, &pStr);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_DictAddUpdate(this->pGen, objBaseID, pStr);
        }
        
        eRc = jsonIn_FindArrayNodeInHashA(pJsonIn, srcDepsID, &pArray);
        if (!ERESULT_FAILED(eRc) && pStr) {
            genBase_setSrcDeps(this->pGen, pArray);
        }
        
        genBase_setMakeType(this->pGen, GENMAKE_TYPE_PGM);
        pStr = ((GENBASE_VTBL *)obj_getVtbl(this->pGen))->pGenInitial(this->pGen);
        if (pStr) {
            AStr_Append(this->pStr, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pJsonIn);
        pJsonIn = OBJ_NIL;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  R o u t i n e
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseRoutine(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode,
        NODEARRAY_DATA  **ppNodes
    )
    {
        ERESULT         eRc;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        NODERTN_DATA    *pRtn = OBJ_NIL;        // Primary Object
        NODETEST_DATA   *pTst = OBJ_NIL;
        NODEARRAY_DATA  *pNodes = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!dbprs_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // The node passed in has its name being the object's name and
        // its data is a node hash.
        pName = node_getNameStr(pNode);
        if (OBJ_NIL == pName) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        
        pHash = OBJ_NIL;
        eRc = dbprs_ParseSubObj(this, node_getData(pNode),
                                        (NODEBASE_DATA **)&pRtn, &pHash);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            goto errorExit;
        }
        if (pHash) {
            NODE_DATA       *pHashNode;
            pHashNode = nodeHash_FindA(pHash, 0, "test");
            if (pHashNode) {
                eRc = dbprs_ParseSubObj(this, node_getData(pHashNode),
                                            (NODEBASE_DATA **)&pTst, NULL);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    goto errorExit;
                }
            }
        }

        // Create a node array and add the routine/test nodes to the array.
        pNodes = nodeArray_New();
        if (OBJ_NIL == pNodes) {
            DEBUG_BREAK();
            eRc = ERESULT_OUT_OF_MEMORY;
            goto errorExit;
        }
        eRc = NodeBase_SortArrays(NodeRtn_getNodeBase(pRtn));
        eRc = nodeArray_AppendNode(pNodes, NodeRtn_getNode(pRtn), NULL);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pNodes);
            goto errorExit;
        }
        if (pTst) {
            eRc = NodeBase_SortArrays(NodeTest_getNodeBase(pTst));
            eRc = nodeArray_AppendNode(pNodes, NodeTest_getNode(pTst), NULL);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pNodes);
                goto errorExit;
            }
        }
        // Return to caller.
        eRc = ERESULT_SUCCESS;
        if (ppNodes) {
            *ppNodes = pNodes;
        }
    errorExit:
        obj_Release(pName);
        obj_Release(pRtn);
        obj_Release(pTst);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  R o u t i n e s
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseRoutines(
        DBPRS_DATA      *this,
        NODEARRAY_DATA  *pArray
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        //ASTR_DATA       *pStr = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pArray) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if(!obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        iMax = nodeArray_getSize(pArray);
        for(i=0; i<iMax; ++i) {
            pNode = nodeArray_Get(pArray, (i+1));
            if (pNode) {
                if (obj_IsKindOf(node_getData(pNode), OBJ_IDENT_ASTR)) {
                    //eRc = dbprs_ParseRoutine(this, pNode);
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  T e s t
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseTest(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode,
        ASTR_DATA       *pName          // Base Name for Test
    )
    {
        NODEHASH_DATA   *pHash = OBJ_NIL;
        OBJ_ID          pData = OBJ_NIL;
        NODEARRAY_DATA  *pDepsObj = OBJ_NIL;
        NODEARRAY_DATA  *pSrcsObj = OBJ_NIL;
        char            *pNameA;
        ASTR_DATA       *pStr = OBJ_NIL;
        NODETEST_DATA   *pTest = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!dbprs_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNameA = node_getNameUTF8(pNode);
        if (OBJ_NIL == pName) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        
        if (0 == strcmp(pNameA, "string")) {
            mem_Free(pName);
            //pName = NULL;
            pNameA = AStr_CStringA((ASTR_DATA *)node_getData(pNode), NULL);
        }
        else {
            pData = node_getData(pNode);
            if (OBJ_NIL == pData) {
                DEBUG_BREAK();
                if (pName) {
                    mem_Free(pName);
                    pName = NULL;
                }
                return ERESULT_DATA_MISSING;
            }
            pData = node_getData(pData);
            if (OBJ_NIL == pData) {
                DEBUG_BREAK();
                if (pName) {
                    mem_Free(pName);
                    pName = NULL;
                }
                return ERESULT_DATA_MISSING;
            }
            if (obj_IsKindOf(pData, OBJ_IDENT_NULL))
                ;
            else if (obj_IsKindOf(pData, OBJ_IDENT_NODEARRAY)) {
                pDepsObj = node_getData((NODE_DATA *)pData);
            }
            else if (obj_IsKindOf(pData, OBJ_IDENT_NODEHASH)) {
                NODE_DATA           *pHashNode;
                pHash = pData;
                pHashNode = nodeHash_FindA(pHash, 0, srcDepsID);
                if (pHashNode) {
                    pData = node_getData(pHashNode);    // Get "array" node.
                    pData = node_getData(pData);        // Get NodeArray.
                    if(obj_IsKindOf(pData, OBJ_IDENT_NODEARRAY)) {
                        pDepsObj = pData;
                    }
                }
                pHashNode = nodeHash_FindA(pHash, 0, "srcs");
                if (pHashNode) {
                    pData = node_getData(pHashNode);    // Get "array" node.
                    pData = node_getData(pData);        // Get NodeArray.
                    if(obj_IsKindOf(pData, OBJ_IDENT_NODEARRAY)) {
                        pSrcsObj = pData;
                    }
                }
            }
            else {
                DEBUG_BREAK();
                if (pName) {
                    mem_Free(pName);
                    pName = NULL;
                }
                return ERESULT_DATA_ERROR;
            }
        }
        
        if (this->pGen) {
            if (((GENBASE_VTBL *)obj_getVtbl(this->pGen))->pGenCompileTest) {
                pStr =  ((GENBASE_VTBL *)obj_getVtbl(this->pGen))->pGenCompileTest(
                                                    this->pGen,
                                                    pNameA,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    NULL,
                                                    pDepsObj,
                                                    pSrcsObj
                        );
            }
            if (pStr) {
                AStr_Append(this->pStr, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        // Return to caller.
        if (pNameA) {
            mem_Free(pNameA);
            pNameA = NULL;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  R o u t i n e s
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseTests(
        DBPRS_DATA      *this,
        NODEARRAY_DATA  *pArray
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        //ASTR_DATA       *pStr = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pArray) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if(!obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        iMax = nodeArray_getSize(pArray);
        for(i=0; i<iMax; ++i) {
            pNode = nodeArray_Get(pArray, (i+1));
            if (pNode) {
                if (obj_IsKindOf(node_getData(pNode), OBJ_IDENT_ASTR)) {
                    //FIXME: eRc = dbprs_ParseTest(this, pNode);
                }
            }
        }
        
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
        void        *pMethod = dbprs_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "dbprs", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          dbprs_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        DBPRS_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)dbprs_Class();
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
                            return dbprs_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return dbprs_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return dbprs_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return dbprs_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == dbprs_ToDebugString)
                    return "ToDebugString";
                if (pData == dbprs_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     dbprs_ToJSON(
        DBPRS_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = dbprs_ToDebugString(this,4);
     @endcode 
     @param     this    DBPRS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     dbprs_ToDebugString(
        DBPRS_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
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
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    dbprs_getSize(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
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
    bool            dbprs_Validate(
        DBPRS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, MAIN_IDENT_DBPRS) )
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


        if( !(obj_getSize(this) >= sizeof(DBPRS_DATA)) ) {
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        //obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


