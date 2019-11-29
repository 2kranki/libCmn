// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeHash.c
 *	Generated 11/27/2018 11:33:59
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
#include        <nodeHash_internal.h>
#include        <ascii.h>
#include        <nodeEnum_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_DeleteExit(
        NODEHASH_DATA   *this,
        NODEHASH_RECORD *pRecord,
        void            *pArg3
    )
    {
        
        if (pRecord->node.pKey) {
            obj_Release(pRecord->node.pKey);
            pRecord->node.pKey = OBJ_NIL;
        }
        if (pRecord->node.pValue) {
            obj_Release(pRecord->node.pValue);
            pRecord->node.pValue = OBJ_NIL;
        }

        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      E n u m  E x i t
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_EnumExit(
        NODEHASH_DATA   *this,
        NODEHASH_RECORD *pRecord,
        NODEENUM_DATA   *pEnum
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = pRecord->node.pKey;
        
        if (pNode && pEnum) {
            eRc = nodeEnum_Append(pEnum, pNode);
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    F i n d  R e c o r d
    //---------------------------------------------------------------
    
    NODEHASH_RECORD * nodeHash_FindRecord(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        NODEHASH_RECORD record = {0};
        NODEHASH_RECORD *pFound = NULL;
        RBT_TREE        *pTree;
        
        // Do initialization.
        
        pTree = nodeHash_TreeFromHash(this, node_getHash(pNode));
        if (pTree) {
            record.node.pKey = pNode;
            pFound = (NODEHASH_RECORD *)rbt_FindNode(pTree, (RBT_NODE *)&record);
        }
        
        // Return to caller.
        return pFound;
    }
    
    
    NODEHASH_RECORD * nodeHash_FindRecordA(
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        NODEHASH_RECORD record = {0};
        NODEHASH_RECORD *pFound = NULL;
        RBT_TREE        *pTree;
        
        // Do initialization.
        pNode = node_NewWithUTF8AndClass(cls, pNameA, OBJ_NIL);
        if (pNode) {
            pTree = nodeHash_TreeFromHash(this, node_getHash(pNode));
            if (pTree) {
                record.node.pKey = pNode;
                pFound = (NODEHASH_RECORD *)rbt_FindNode(pTree, (RBT_NODE *)&record);
            }
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
        // Return to caller.
        return pFound;
    }
    
    

    //---------------------------------------------------------------
    //                  N o d e  C o m p a r e
    //---------------------------------------------------------------
    
    int             nodeHash_NodeCompare(
        void            *pRecordA,
        void            *pRecordB
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNodeA = pRecordA;
        NODE_DATA       *pNodeB = pRecordB;
        
        eRc = node_Compare(pNodeA, pNodeB);
        if (eRc == ERESULT_SUCCESS_EQUAL) {
            return 0;
        }
        else if (eRc == ERESULT_SUCCESS_LESS_THAN) {
            return -1;
        }
        
        return 1;
    }
    
    
    
    //---------------------------------------------------------------
    //                      N o d e s  E x i t
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_NodesExit(
        NODEHASH_DATA   *this,
        NODEHASH_RECORD *pRecord,
        NODEARRAY_DATA  *pArray
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = pRecord->node.pKey;
        
        if (pNode && pArray) {
            eRc = nodeArray_AppendNode(pArray, (NODE_DATA *)pNode, NULL);
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      T r e e  F r o m  H a s h
    //---------------------------------------------------------------
    
    RBT_TREE *      nodeHash_TreeFromHash (
        NODEHASH_DATA   *this,
        uint32_t        hash
    )
    {
        uint16_t        index;
        RBT_TREE        *pTree = NULL;
        
        index = hash % this->cHash;
        pTree = &this->pHash[index];
        
        return  pTree;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEHASH_DATA *     nodeHash_Alloc (
        void
    )
    {
        NODEHASH_DATA       *this;
        uint32_t        cbSize = sizeof(NODEHASH_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEHASH_DATA *     nodeHash_New (
        void
    )
    {
        NODEHASH_DATA       *this;
        
        this = nodeHash_Alloc( );
        if (this) {
            this = nodeHash_Init(this, NODEHASH_TABLE_SIZE_SMALL);
        } 
        return this;
    }


    NODEHASH_DATA *     nodeHash_NewWithSize (
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        NODEHASH_DATA       *this;
        
        this = nodeHash_Alloc( );
        if (this) {
            this = nodeHash_Init(this, cHash);
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          B l o c k s
    //---------------------------------------------------------------
    
    BLOCKS_DATA *   nodeHash_getBlocks (
        NODEHASH_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (BLOCKS_DATA *)this;
    }


    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        nodeHash_getPriority (
        NODEHASH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            nodeHash_setPriority (
        NODEHASH_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
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
    
    uint32_t        nodeHash_getSize (
        NODEHASH_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->size;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  nodeHash_getSuperVtbl (
        NODEHASH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
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
    //                          A d d
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_Add(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        RBT_TREE        *pTree;
        NODEHASH_RECORD *pRecord = NULL;
        int             iRc;
        ERESULT         eRc = ERESULT_FAILURE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode,OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pTree = nodeHash_TreeFromHash(this, node_getHash(pNode));
        if (pTree) {
            pRecord = blocks_RecordNew((BLOCKS_DATA *)this);
            if (NULL == pRecord) {
                return ERESULT_OUT_OF_MEMORY;
            }
            pRecord->node.pKey = pNode;
            pRecord->unique = ++this->unique;
            listdl_Init(&pRecord->dups, offsetof(NODEHASH_RECORD, dups));
            iRc = rbt_InsertNode(pTree, (RBT_NODE *)pRecord);
            if (iRc) {
                obj_Retain(pNode);
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_DATA_ALREADY_EXISTS;
        }
        
        ++this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeHash_AddA(
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = node_NewWithUTF8AndClass(cls, pName, pData);
        if (OBJ_NIL == pNode) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        eRc = nodeHash_Add(this, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeHash_AddUpdate(
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pNode) || !obj_IsKindOf(pNode, OBJ_IDENT_NODE) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
       
        eRc = nodeHash_Delete(this, pNode);
        eRc = nodeHash_Add(this, pNode);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeHash_AddUpdateA (
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pName ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = node_NewWithUTF8AndClass(cls, pName, pData);
        if (OBJ_NIL == pNode) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        eRc = nodeHash_AddUpdate(this, pNode);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = nodeHash_Assign(this,pOther);
     @endcode 
     @param     this    NODEHASH object pointer
     @param     pOther  a pointer to another NODEHASH object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         nodeHash_Assign (
        NODEHASH_DATA		*this,
        NODEHASH_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!nodeHash_Validate(pOther)) {
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
    //       C a l c  H a s h  I n d e x  S t a t i s t i c s
    //---------------------------------------------------------------
    
    ERESULT            nodeHash_CalcHashStats (
        NODEHASH_DATA   *this,
        uint32_t        *pNumBuckets,   // Number of Hash Buckets
        uint32_t        *pNumEmpty,     // Number of Empty Hash Buckets
        uint32_t        *pNumMax,       // Maximum Number in any one Hash Bucket
        uint32_t        *pNumAvg        // Average Number in each Hash Bucket
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        RBT_TREE        *pTree;
        uint32_t        i;
        uint32_t        count;
        uint32_t        numEmpty = 0;
        uint32_t        numMax = 0;
        uint32_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        // Do the calculations.
        for (i=0; i<this->cHash; ++i) {
            pTree = &this->pHash[i];
            count = (uint32_t)rbt_getSize(pTree);
            if (0 == count) {
                ++numEmpty;
            }
            if (count > numMax) {
                numMax = count;
            }
            num += count;
        }
        
        // Return to caller.
        if (pNumBuckets)
            *pNumBuckets = this->cHash;
        if (pNumEmpty)
            *pNumEmpty = numEmpty;
        if (pNumMax)
            *pNumMax = numMax;
        if (pNumAvg) {
            if (this->cHash - numEmpty) {
                *pNumAvg = num / (this->cHash - numEmpty);
            }
            else
                *pNumAvg = 0;
        }
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
    ERESULT         nodeHash_Compare (
        NODEHASH_DATA     *this,
        NODEHASH_DATA     *pOther
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
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!nodeHash_Validate(pOther)) {
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
        nodeHash      *pCopy = nodeHash_Copy(this);
     @endcode 
     @param     this    NODEHASH object pointer
     @return    If successful, a NODEHASH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEHASH_DATA *     nodeHash_Copy (
        NODEHASH_DATA       *this
    )
    {
        NODEHASH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeHash_New( );
        if (pOther) {
            eRc = nodeHash_Assign(this, pOther);
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

    void            nodeHash_Dealloc (
        OBJ_ID          objId
    )
    {
        NODEHASH_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEHASH_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pHash) {
            mem_Free(this->pHash);
            this->pHash = NULL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_Delete (
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        RBT_TREE        *pTree;
        int             iRc;
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
      
        pTree = nodeHash_TreeFromHash(this, node_getHash(pNode));
        if (pTree) {
            iRc = rbt_Delete(pTree, pNode);
            if (iRc) {
                --this->size;
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_DATA_NOT_FOUND;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         nodeHash_DeleteA (
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
       
        pNode = node_NewWithUTF8ConAndClass(cls, pNameA, OBJ_NIL);
        if (pNode) {
            eRc = nodeHash_Delete(this, pNode);
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
        
        // Return to caller.
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         nodeHash_Disable (
        NODEHASH_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!nodeHash_Validate(this)) {
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

    ERESULT         nodeHash_Enable (
        NODEHASH_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!nodeHash_Validate(this)) {
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
    //                         E n u m
    //---------------------------------------------------------------
    
    NODEENUM_DATA * nodeHash_Enum (
        NODEHASH_DATA   *this
    )
    {
        NODEENUM_DATA   *pEnum = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEnum = nodeEnum_New();
        if (pEnum) {
            eRc =   blocks_ForEach(
                                   (BLOCKS_DATA *)this,
                                   (void *)nodeHash_EnumExit,
                                   this,
                                   pEnum
                                   );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pEnum);
                pEnum = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //---------------------------------------------------------------
    //     E x p a n d  E n v i r o n m e n t  V a r i a b l e s
    //---------------------------------------------------------------
    
    /*!
     Substitute environment variables into the current string using a BASH-like
     syntax.  Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         nodeHash_ExpandVars (
        NODEHASH_DATA   *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;
        uint32_t        i = 0;
        uint32_t        iBegin;
        uint32_t        len;
        uint32_t        lenPrefix;
        uint32_t        lenSuffix;
        int32_t         chr;
        bool            fMore = true;
        //PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        ASTR_DATA       *pData = OBJ_NIL;
        const
        char            *pEnvVar = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if((OBJ_NIL == pStr) || !obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (0 == AStr_getLength(pStr)) {
            return ERESULT_SUCCESS;
        }
        
        // Expand Environment variables.
        while (fMore) {
            fMore = false;
            eRc = AStr_CharFindNextW32(pStr, &i, '$');
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            else {
                chr = AStr_CharGetW32(pStr, i+1);
                if (chr == '{') {
                    i += 2;
                    iBegin = i;
                    eRc = AStr_CharFindNextW32(pStr, &i, '}');
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_PARSE_ERROR;
                    }
                    len = i - iBegin;
                    eRc = AStr_Mid(pStr, iBegin, len, &pName);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    lenPrefix = 2;
                    lenSuffix = 1;
                    
                    // Find the name from the Dictionary.
                do_replace:
                    pNode = nodeHash_FindA(this, 0, AStr_getData(pName));
                    if (OBJ_NIL == pNode) {
                        obj_Release(pName);
                        return ERESULT_DATA_NOT_FOUND;
                    }
                    obj_Release(pName);
                    pName = OBJ_NIL;
                    pData = node_getData(pNode);
                    if((OBJ_NIL == pData) || !obj_IsKindOf(pData, OBJ_IDENT_ASTR)) {
                        DEBUG_BREAK();
                        return ERESULT_DATA_MISSING;
                    }
                    
                    // Substitute the name from the Dictionary.
                    eRc =   AStr_Remove(
                                        pStr,
                                        (iBegin - lenPrefix),
                                        (len + lenPrefix + lenSuffix)
                                        );
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    eRc = AStr_InsertA(pStr, (iBegin - lenPrefix), AStr_getData(pData));
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    i = iBegin - lenPrefix + AStr_getSize(pData);
                    pEnvVar = NULL;
                    pData = OBJ_NIL;
                    pNode = OBJ_NIL;
                    fMore = true;
                }
                else if (chr == '$') {
                    eRc = AStr_Remove(pStr, i, 1);
                    ++i;
                    fMore = true;
                    continue;
                }
                else {
                    //chr = AStr_CharGetW32(pStr, i+1);
                    if (ascii_isLabelFirstCharW32(chr)) {
                        ++i;
                        iBegin = i;
                        for (;;) {
                            ++i;
                            chr = AStr_CharGetW32(pStr, i);
                            if (!ascii_isLabelCharW32(chr)) {
                                break;
                            }
                        }
                        len = i - iBegin;
                        eRc = AStr_Mid(pStr, iBegin, len, &pName);
                        if (ERESULT_FAILED(eRc)) {
                            return ERESULT_OUT_OF_MEMORY;
                        }
                        lenPrefix = 1;
                        lenSuffix = 0;
                        
                        goto do_replace;
                        
                    }
                    else
                        return ERESULT_PARSE_ERROR;
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    NODE_DATA *     nodeHash_Find (
        NODEHASH_DATA   *this,
        NODE_DATA       *pNode
    )
    {
        NODEHASH_RECORD *pRecord = NULL;
        NODE_DATA       *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNode ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pRecord = nodeHash_FindRecord(this, pNode);
        if (pRecord) {
            pFound = pRecord->node.pKey;
        }
        
        // Return to caller.
        return pFound;
    }
    
    
    NODE_DATA *     nodeHash_FindA (
        NODEHASH_DATA   *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        NODEHASH_RECORD *pRecord = OBJ_NIL;
        NODE_DATA       *pFound = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( OBJ_NIL == pNameA ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pRecord = nodeHash_FindRecordA(this, cls, pNameA);
        if (pRecord) {
            pFound = pRecord->node.pKey;
        }
        
        // Return to caller.
        return pFound;
    }
    
    
    ERESULT         nodeHash_FindArrayNodeInHashA (
        NODEHASH_DATA   *this,
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
        if(!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = nodeHash_FindNodeInHashA(this, pSectionA, "array", (void **)&pArray);
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
    
    
    ERESULT         nodeHash_FindIntegerNodeInHashA (
        NODEHASH_DATA    *this,
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
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = nodeHash_FindNodeInHashA(this, pSectionA, "integer", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        num = AStr_ToInt64(pData);
        
        if (pInt) {
            *pInt = num;
        }
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeHash_FindNodeInHashA (
        NODEHASH_DATA   *this,
        const
        char            *pSectionA,
        const
        char            *pTypeA,
        OBJ_ID          *ppData
    )
    {
        NODE_DATA       *pNode;
        NAME_DATA       *pName;
        OBJ_ID          pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pNode = nodeHash_FindA(this, 0, pSectionA);
        if (OBJ_NIL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pNode = node_getData(pNode);
        if (OBJ_NIL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pName = node_getName(pNode);
        if (!(ERESULT_SUCCESS_EQUAL == name_CompareA(pName, pTypeA))) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pData = node_getData(pNode);
        if (OBJ_NIL == pData) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        if (ppData) {
            *ppData = pData;
        }
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         nodeHash_FindStringNodeInHashA (
        NODEHASH_DATA   *this,
        const
        char            *pSectionA,
        ASTR_DATA       **ppStr
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pData = OBJ_NIL;
        
        eRc = nodeHash_FindNodeInHashA(this, pSectionA, "string", (void **)&pData);
        if (ERESULT_FAILED(eRc) || (OBJ_NIL == pData)) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        if (ppStr)
            *ppStr = pData;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_ForEach(
        NODEHASH_DATA   *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,               // Used as first parameter of scan method
        void            *pArg3              // Used as third parameter of scan method
    )
    {
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
        //NODEHASH_RECORD *pRecord;
        //uint32_t        i;
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pList = blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            NODEHASH_RECORD     *pRecord = (NODEHASH_RECORD *)pEntry->data;
            
            eRc =   pScan(pObj, pRecord->node.pKey, pArg3);
            if (ERESULT_FAILED(eRc))
                break;
            
            pEntry = listdl_Next(pList, pEntry);
        }

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEHASH_DATA * nodeHash_Init(
        NODEHASH_DATA   *this,
        uint16_t        cHash
    )
    {
        uint32_t        cbSize = sizeof(NODEHASH_DATA);
        uint32_t        i;
        ERESULT         eRc;
        
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

        this = (OBJ_ID)blocks_Init((BLOCKS_DATA *)this); // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEHASH);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeHash_Vtbl);
        
        eRc = blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(NODEHASH_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        blocks_setDeleteExit(
             (BLOCKS_DATA *)this,
             (void *)nodeHash_DeleteExit,
             this,
             NULL
        );
        
        this->cHash = cHash;
        cbSize = cHash * sizeof(RBT_TREE);
        this->pHash = (RBT_TREE *)mem_Malloc(cbSize);
        if (NULL == this->pHash) {
            DEBUG_BREAK();
            obj_Release(this);
            this = NULL;
            return this;
        }
        for (i=0; i<cHash; ++i) {
            rbt_Init(
                     &this->pHash[i],
                     (void *)nodeHash_NodeCompare,
                     (sizeof(NODEHASH_RECORD) - sizeof(RBT_NODE)),
                     (void *)blocks_RecordNew,
                     (void *)blocks_RecordFree,
                     this
            );
            this->pHash[i].pNodeAlloc = (void *)blocks_RecordNew;
            this->pHash[i].pNodeFree = (void *)blocks_RecordFree;
            this->pHash[i].pObjAllocFree = this;
            this->pHash[i].dataSize = (sizeof(NODEHASH_RECORD) - sizeof(RBT_NODE));
        }

    #ifdef NDEBUG
    #else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "nodeHash::sizeof(NODEHASH_DATA) = %lu\n", sizeof(NODEHASH_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEHASH_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         nodeHash_IsEnabled(
        NODEHASH_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
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
    //                         N o d e s s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * nodeHash_Nodes(
        NODEHASH_DATA   *this
    )
    {
        NODEARRAY_DATA   *pNodes = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNodes = nodeArray_New();
        if (pNodes) {
            eRc =   blocks_ForEach(
                                   (BLOCKS_DATA *)this,
                                   (void *)nodeHash_NodesExit,
                                   this,
                                   pNodes
                                   );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pNodes);
                pNodes = OBJ_NIL;
            }
            else
                nodeArray_SortAscending(pNodes);
        }
        
        // Return to caller.
        return pNodes;
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
        void        *pMethod = nodeHash_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "nodeHash", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeHash_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEHASH_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(NODEHASH_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)nodeHash_Class();
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
                            return nodeHash_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return nodeHash_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeHash_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return nodeHash_ToJSON;
                        }
                        if (str_Compare("ToString", (char *)pStr) == 0) {
                            return nodeHash_ToString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == nodeHash_ToDebugString)
                    return "ToDebugString";
                if (pData == nodeHash_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeHash_ToDebugString(this,4);
     @endcode 
     @param     this    NODEHASH object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeHash_ToDebugString(
        NODEHASH_DATA   *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
        //NODEHASH_RECORD *pRecord;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
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
                    nodeHash_getSize(this)
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
        
        pList = blocks_getList((BLOCKS_DATA *)this);
        pEntry = listdl_Head(pList);
        while (pEntry) {
            NODEHASH_RECORD     *pRecord = (NODEHASH_RECORD *)pEntry->data;
            RBT_NODE            *pNode = &pRecord->node;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            }
            eRc =   AStr_AppendPrint(
                                   pStr,
                                   "%p  L=%p R=%p %s   D=%p U=%d\n",
                                   pNode,
                                   pNode->pLink[RBT_LEFT],
                                   pNode->pLink[RBT_RIGHT],
                                   pNode->color ? "red" : "black",
                                   pNode->pKey,
                                   pRecord->unique
                    );
            if (pNode->pKey) {
                pWrkStr = obj_getVtbl(pNode->pKey)->pToDebugString(pNode->pKey, indent+6);
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
            pEntry = listdl_Next(pList, pEntry);
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
    
    
    ASTR_DATA *     nodeHash_ToString(
        NODEHASH_DATA   *this
    )
    {
        ERESULT         eRc;
        int             i;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrk = OBJ_NIL;
        NODEARRAY_DATA  *pArray;
        NODE_DATA       *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!nodeHash_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        eRc = AStr_AppendPrint(pStr, "Hash{\n");
        pArray = nodeHash_Nodes(this);
        if (pArray) {
            for (i=0; i < nodeArray_getSize(pArray); i++) {
                pNode = nodeArray_Get(pArray, i);
                if (pNode) {
                    pWrk = node_ToString(pNode);
                    if (pWrk) {
                        AStr_Append(pStr, pWrk);
                        obj_Release(pWrk);
                        pWrk = OBJ_NIL;
                    }
                }
            }
        }
        
        eRc =   AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeHash_Validate(
        NODEHASH_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODEHASH))
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


        if (!(obj_getSize(this) >= sizeof(NODEHASH_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


