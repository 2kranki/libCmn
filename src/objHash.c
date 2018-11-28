// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objHash.c
 *	Generated 11/27/2018 11:34:09
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
#include        <objHash_internal.h>
#include        <objEnum_internal.h>
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
    
    ERESULT         objHash_DeleteExit(
        OBJHASH_DATA    *this,
        OBJHASH_RECORD  *pRecord,
        void            *pArg3
    )
    {
        
        if (pRecord->node.pData) {
            obj_Release(pRecord->node.pData);
            pRecord->node.pData = OBJ_NIL;
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      E n u m  E x i t
    //---------------------------------------------------------------
    
    ERESULT         objHash_EnumExit(
        OBJHASH_DATA    *this,
        OBJHASH_RECORD  *pRecord,
        OBJENUM_DATA    *pEnum
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        OBJ_ID          *pNode = pRecord->node.pData;
        
        if (pNode && pEnum) {
            eRc = objEnum_Append(pEnum, pNode);
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    F i n d  R e c o r d
    //---------------------------------------------------------------
    
    OBJHASH_RECORD * objHash_FindRecord(
        OBJHASH_DATA    *this,
        uint32_t        hash,
        NODE_DATA       *pNode
    )
    {
        OBJHASH_RECORD  *pRecord;
        RBT_TREE        *pTree;
        int             iRc;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
        pTree = objHash_TreeFromHash(this, hash);
        pVtbl = obj_getVtbl(pObject);
        
        pRecord = rbt_Find(pTree, pNode);
        while ( pNode ) {
            if (pNode->hash == hash) {
                iRc = pVtbl->pCompare(pObject, pNode->pObject);
                if (0 == iRc) {
                    return pNode;
                }
                if (iRc < 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    //---------------------------------------------------------------
    //                 I n d e x  F r o m  H a s h
    //---------------------------------------------------------------
    
    RBT_TREE *      objHash_TreeFromHash (
        OBJHASH_DATA    *this,
        uint32_t        hash
    )
    {
        uint16_t        index;
        RBT_TREE        *pTree = NULL;
        
        index = hash % this->cHash;
        pTree = &this->pHash[index];
        
        return  pTree;
    }
    
    
    
    //---------------------------------------------------------------
    //                  O b j e c t  C o m p a r e
    //---------------------------------------------------------------
    
    int             objHash_ObjCmp(
        RBT_TREE        *this,
        OBJHASH_RECORD  *pRecordA,
        OBJHASH_RECORD  *pRecordB
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        OBJ_ID          *pNodeA = pRecordA->node.pData;
        OBJ_ID          *pNodeB = pRecordB->node.pData;
        
        eRc = obj_getVtbl(pNodeA)->pCompare(pNodeA, pNodeB);
        if (eRc == ERESULT_SUCCESS_EQUAL) {
            return 0;
        }
        else if (eRc == ERESULT_SUCCESS_LESS_THAN) {
            return -1;
        }
        
        return 1;
    }
    
    
    
    //---------------------------------------------------------------
    //                  O b j e c t s  E x i t
    //---------------------------------------------------------------
    
    ERESULT         objHash_ObjectsExit(
        OBJHASH_DATA    *this,
        OBJHASH_RECORD  *pRecord,
        OBJARRAY_DATA   *pArray
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        NODE_DATA       *pNode = pRecord->node.pData;
        
        if (pNode && pArray) {
            eRc = objArray_AppendObj(pArray, (NODE_DATA *)pNode, NULL);
        }
        
        return eRc;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJHASH_DATA *     objHash_Alloc (
        void
    )
    {
        OBJHASH_DATA       *this;
        uint32_t        cbSize = sizeof(OBJHASH_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJHASH_DATA *     objHash_New (
        void
    )
    {
        OBJHASH_DATA       *this;
        
        this = objHash_Alloc( );
        if (this) {
            this = objHash_Init(this, OBJHASH_TABLE_SIZE_SMALL);
        } 
        return this;
    }


    OBJHASH_DATA *  objHash_NewWithSize (
        uint16_t        cHash
    )
    {
        OBJHASH_DATA       *this;
        
        this = objHash_Alloc( );
        if (this) {
            this = objHash_Init(this, cHash);
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                   D u p l i c a t e s
    //---------------------------------------------------------------
    
    bool            objHash_getDuplicates(
        OBJHASH_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return obj_Flag(this, OBJHASH_FLAG_DUPS);
    }
    
    
    bool            objHash_setDuplicates(
        OBJHASH_DATA    *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_FlagSet(this, OBJHASH_FLAG_DUPS, fValue);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        objHash_getPriority (
        OBJHASH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            objHash_setPriority (
        OBJHASH_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
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
    
    uint32_t        objHash_getSize (
        OBJHASH_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  objHash_getSuperVtbl (
        OBJHASH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
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
        ERESULT eRc = objHash_Assign(this,pOther);
     @endcode 
     @param     this    OBJHASH object pointer
     @param     pOther  a pointer to another OBJHASH object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         objHash_Assign (
        OBJHASH_DATA		*this,
        OBJHASH_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!objHash_Validate(pOther)) {
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
    ERESULT         objHash_Compare (
        OBJHASH_DATA     *this,
        OBJHASH_DATA     *pOther
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
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!objHash_Validate(pOther)) {
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
        objHash      *pCopy = objHash_Copy(this);
     @endcode 
     @param     this    OBJHASH object pointer
     @return    If successful, a OBJHASH object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJHASH_DATA *     objHash_Copy (
        OBJHASH_DATA       *this
    )
    {
        OBJHASH_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objHash_New( );
        if (pOther) {
            eRc = objHash_Assign(this, pOther);
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

    void            objHash_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJHASH_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJHASH_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pHash) {
            mem_Free(this->pHash);
            this->pHash = OBJ_NIL;
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

    ERESULT         objHash_Disable (
        OBJHASH_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!objHash_Validate(this)) {
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

    ERESULT         objHash_Enable(
        OBJHASH_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //----------------------------------------------------------
    //                        F i n d
    //----------------------------------------------------------
    
    OBJ_ID          objHash_Find(
        OBJHASH_DATA    *this,
        OBJ_ID          pObject
    )
    {
        OBJHASH_RECORD  *pRecord;
        uint32_t        hash;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);
        
        hash = pVtbl->pHash(pObject);
        
        pRecord = objHash_FindNode(this, hash, pObject);
        if (pRecord) {
            return pNode->node.pData;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    OBJ_ID          objHash_FindIndex(
                                      OBJHASH_DATA    *this,
                                      uint32_t        index
                                      )
    {
        OBJHASH_NODE    *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNode = objHash_FindUniqueInt(this, index);
        if (pNode) {
            return pNode->pObject;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJHASH_DATA *  objHash_Init(
        OBJHASH_DATA    *this,
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        uint32_t        cbSize = sizeof(OBJHASH_DATA);
        ERESULT         eRc;
        uint32_t        i;
        
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

        this = (OBJ_ID)blocks_Init((BLOCKS_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJHASH);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_OBJHASH);      // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objHash_Vtbl);
        
        eRc = blocks_SetupSizes((BLOCKS_DATA *)this, 0, sizeof(OBJHASH_RECORD));
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        blocks_setDeleteExit(
                        (BLOCKS_DATA *)this,
                        (void *)objHash_DeleteExit,
                        this,
                        NULL
        );

        this->cHash = cHash;
        cbSize = cHash * sizeof(RBT_TREE);
        this->pHash = (RBT_TREE *)mem_Malloc( cbSize );
        if (NULL == this->pHash) {
            DEBUG_BREAK();
            obj_Release(this);
            this = NULL;
            return this;
        }
        for (i=0; i<cHash; ++i) {
            rbt_Init(&this->pHash[i], (void *)objHash_ObjCmp);
            this->pHash[i].pNodeAlloc = (void *)blocks_RecordNew;
            this->pHash[i].pNodeFree = (void *)blocks_RecordFree;
            this->pHash[i].pObjAllocFree = this;
            this->pHash[i].dataSize = sizeof(OBJHASH_RECORD) - sizeof(RBT_NODE);
        }
        
    #ifdef NDEBUG
    #else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "objHash::sizeof(OBJHASH_DATA) = %lu\n", sizeof(OBJHASH_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJHASH_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         objHash_IsEnabled(
        OBJHASH_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
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
    //                         O b j e c t s
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * objHash_Objects(
        OBJHASH_DATA    *this
    )
    {
        OBJARRAY_DATA   *pNodes = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNodes = objArray_New();
        if (pNodes) {
            eRc =   blocks_ForEach(
                                   (BLOCKS_DATA *)this,
                                   (void *)objHash_ObjectsExit,
                                   this,
                                   pNodes
                                   );
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pNodes);
                pNodes = OBJ_NIL;
            }
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
        void        *pMethod = objHash_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "objHash", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          objHash_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJHASH_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJHASH_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)objHash_Class();
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
                            return objHash_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return objHash_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return objHash_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return objHash_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == objHash_ToDebugString)
                    return "ToDebugString";
                if (pData == objHash_ToJSON)
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
        ASTR_DATA      *pDesc = objHash_ToDebugString(this,4);
     @endcode 
     @param     this    OBJHASH object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     objHash_ToDebugString(
        OBJHASH_DATA    *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        LISTDL_DATA     *pList = NULL;
        BLOCKS_NODE     *pEntry = NULL;
        OBJHASH_RECORD  *pRecord;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!objHash_Validate(this)) {
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
                    objHash_getSize(this)
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
            OBJHASH_RECORD      *pRecord = (OBJHASH_RECORD *)pEntry->data;
            RBT_NODE            *pNode = &pRecord->node;
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+3, ' ');
            }
            eRc = AStr_AppendPrint(
                                   pStr,
                                   "%p  L=%p R=%p %s   D=%p\n",
                                   pNode,
                                   pNode->pLink[RBT_LEFT],
                                   pNode->pLink[RBT_RIGHT],
                                   pNode->color ? "red" : "black",
                                   pNode->pData
                                   );
            if (pNode->pData) {
                pWrkStr = obj_getVtbl(pNode->pData)->pToDebugString(pNode->pData, indent+6);
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objHash_Validate(
        OBJHASH_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJHASH))
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


        if (!(obj_getSize(this) >= sizeof(OBJHASH_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


