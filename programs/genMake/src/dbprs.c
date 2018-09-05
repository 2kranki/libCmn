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
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            dbprs_task_body(
        void            *pData
    )
    {
        //DBPRS_DATA  *this = pData;
        
    }
#endif



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



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

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

        obj_setLastError(this, ERESULT_SUCCESS);
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

        obj_setLastError(this, ERESULT_SUCCESS);
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

        obj_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * dbprs_getStr(
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
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

        
        obj_setLastError(this, ERESULT_SUCCESS);
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
        obj_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        obj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return obj_getLastError(this);
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
        
        obj_setLastError(this, eRc);
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
        obj_setLastError(this, ERESULT_SUCCESS);
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

        dbprs_setGen(this, OBJ_NIL);
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
        obj_setLastError(this, ERESULT_SUCCESS);
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
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
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
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
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
            obj_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  I n p u t
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseInputFile(
        DBPRS_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        //ERESULT         eRc;
        HJSON_DATA      *pObj = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        //NODEHASH_DATA   *pHash;
        NODE_DATA       *pFileNode;
        //NODE_DATA       *pNode;
        //NODEARRAY_DATA  *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pObj = hjson_NewFromPath(pPath, 4);
        if (pObj) {
            
            if  (appl_getDebug((APPL_DATA *)this)) {
                obj_TraceSet(pObj, true);
            }
            pFileNode = hjson_ParseFileHash(pObj);
            if (pFileNode) {
                this->pNodes = pFileNode;
                if (appl_getDebug((APPL_DATA *)this)) {
                    pStr = node_ToDebugString(pFileNode, 0);
                    fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         dbprs_ParseInputStr(
        DBPRS_DATA      *this,
        const
        char            *pStrA
    )
    {
        //ERESULT         eRc;
        HJSON_DATA      *pObj = OBJ_NIL;
        NODE_DATA       *pFileNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStrA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pObj = hjson_NewA(pStrA, 4);
        if (pObj) {
            
            pFileNode = hjson_ParseFileHash(pObj);
            if (pFileNode) {
                this->pNodes = pFileNode;
                if (obj_Trace((APPL_DATA *)this)) {
                    ASTR_DATA       *pWrk = OBJ_NIL;
                    pWrk = node_ToDebugString(pFileNode, 8);
                    fprintf(stderr, "%s\n\n\n", AStr_getData(pWrk));
                    obj_Release(pWrk);
                    pWrk = OBJ_NIL;
                }
            }
            
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                  P a r s e  O b j e c t
    //---------------------------------------------------------------
    
    ERESULT         dbprs_ParseObject(
        DBPRS_DATA      *this,
        NODE_DATA       *pNode
    )
    {
        //NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        OBJ_ID          pData = OBJ_NIL;
        NODEARRAY_DATA  *pDeps = OBJ_NIL;
        bool            fJson = false;
        bool            fTest = true;
        char            *pName;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !dbprs_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pNode) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if(!obj_IsKindOf(pNode, OBJ_IDENT_NODE)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pName = node_getNameUTF8(pNode);
        if(OBJ_NIL == pName) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }

        pData = node_getData(pNode);
        if(OBJ_NIL == pData) {
            DEBUG_BREAK();
            if (pName) {
                mem_Free(pName);
                pName = NULL;
            }
            return ERESULT_DATA_MISSING;
        }
        pData = node_getData(pData);
        if(OBJ_NIL == pData) {
            DEBUG_BREAK();
            if (pName) {
                mem_Free(pName);
                pName = NULL;
            }
            return ERESULT_DATA_MISSING;
        }
        if(obj_IsKindOf(pData, OBJ_IDENT_NODEARRAY)) {
            pDeps = node_getData((NODE_DATA *)pData);
        }
        else if(obj_IsKindOf(pData, OBJ_IDENT_NODEHASH)) {
            NODE_DATA           *pHashNode;
            pHash = pData;
            pHashNode = nodeHash_FindA(pHash, "deps");
            if (pHashNode) {
                pDeps = node_getData(pHashNode);
            }
            pHashNode = nodeHash_FindA(pHash, "json");
            if (pHashNode) {
                pData = node_getData(pHashNode);
                if (pData) {
                    pData = node_getData(pData);
                    if (pData) {
                        if(obj_IsKindOf(pData, OBJ_IDENT_TRUE)) {
                            fJson = true;
                        }
                    }
                }
            }
            pHashNode = nodeHash_FindA(pHash, "test");
            if (pHashNode) {
                pData = node_getData(pHashNode);
                if (pData) {
                    pData = node_getData(pData);
                    if (pData) {
                        if(obj_IsKindOf(pData, OBJ_IDENT_FALSE)) {
                            fTest = false;
                        }
                    }
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

        if (this->pGen) {
            pStr = genBase_GenCompileObject(this->pGen, pName, NULL, NULL, NULL);
            if (pStr) {
                AStr_Append(this->pStr, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            if (fJson) {
                pStr = genBase_GenCompileJson(this->pGen, pName, NULL, NULL, NULL);
                if (pStr) {
                    AStr_Append(this->pStr, pStr);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            if (fTest) {
                pStr = genBase_GenCompileTest(this->pGen, pName, NULL, NULL, NULL);
                if (pStr) {
                    AStr_Append(this->pStr, pStr);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
        }

        // Return to caller.
        if (pName) {
            mem_Free(pName);
            pName = NULL;
        }
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
        int             j;
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
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
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


