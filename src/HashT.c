/*
 * File:   HashT.c
 *  Generated 12/12/2021 15:40:13
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
#include        <HashT_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         HashT_DeleteExit(
        HASHT_DATA      *this,
        HASHT_NODE      *pNode,
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        if (this->pDelete) {
            eRc =   this->pDelete(
                                this->pDeleteObj,
                                pNode->data,
                                this->pDeleteArg3
                    );
        }

        return eRc;
    }




    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    HASHT_DATA *     HashT_Alloc (
        void
    )
    {
        HASHT_DATA       *this;
        uint32_t        cbSize = sizeof(HASHT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    HASHT_DATA *     HashT_New (
        void
    )
    {
        HASHT_DATA       *this;
        
        this = HashT_Alloc( );
        if (this) {
            this = HashT_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  C o m p a r e  M e t h o d
    //---------------------------------------------------------------

    bool            HashT_setCompare (
        HASHT_DATA      *this,
        int             (*pCompare)(void *, void *)
    )
    {
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pCompare = pCompare;

        return true;
    }



    //---------------------------------------------------------------
    //                     D e l e t e  E x i t
    //---------------------------------------------------------------

    bool            HashT_setDeleteExit (
        HASHT_DATA      *this,
        P_ERESULT_EXIT3 pDelete,
        OBJ_ID          pObj,           // Used as first parameter of scan method
        void            *pArg3          // Used as third parameter of scan method
    )
    {
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pDelete = pDelete;
        this->pDeleteObj = pObj;
        this->pDeleteArg3 = pArg3;

        return true;
    }



    //---------------------------------------------------------------
    //                          L o g
    //---------------------------------------------------------------

#ifdef   HASHT_LOG
    bool            HashT_setLog (
        HASHT_DATA   *this,
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pLog = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                        N u m  S c o p e s
    //---------------------------------------------------------------

    uint32_t        HashT_getNumScopes (
        HASHT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize(this->pLevels);
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        HashT_getPriority (
        HASHT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            HashT_setPriority (
        HASHT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
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
    
    uint32_t        HashT_getSize (
        HASHT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * HashT_getStr (
        HASHT_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        HashT_setStr (
        HASHT_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
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
    
    HASHT_DATA *  HashT_getSuper (
        HASHT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (HASHT_DATA *)this;
    }

    OBJ_IUNKNOWN *  HashT_getSuperVtbl (
        HASHT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
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

    ERESULT         HashT_Add (
        HASHT_DATA      *this,
        uint32_t        hash,
        void            *pData,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = HashT_AddInScope(this, HashT_getNumScopes(this)-1, hash, pData, pIndex);

        // Return to caller.
        return eRc;
    }


    ERESULT         HashT_AddInScope (
        HASHT_DATA      *this,
        uint32_t        scope,
        uint32_t        hash,
        void            *pData,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        unique;
        uint32_t        index;
        HASHT_NODE      *pNode;
        LISTDL_DATA     list;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        eRc = array_Get(this->pLevels, scope+1, 1, &list);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNode = Blocks_RecordNew((BLOCKS_DATA *)this, &unique);
        if (NULL == pNode) {
            return ERESULT_OUT_OF_MEMORY;
        }
        pNode->unique = unique;
        memmove(pNode->data, pData, this->dataSize);

        // Add to head of Hash Chain Bucket.
        index = hash % this->cHash;
        listdl_Add2Head(&this->pHash[index], pNode);

        // Add to head of given scope.
        eRc = array_Get(this->pLevels, scope+1, 1, &list);
        if (ERESULT_OK(eRc)) {
            listdl_Add2Head(&this->pHash[index], pNode);
            eRc = array_Put(this->pLevels, scope+1, 1, &list);
        }

        // Return to caller.
        if (pIndex) {
            if (ERESULT_OK(eRc)) {
                *pIndex = unique;
            } else {
                *pIndex = 0;
            }
        }
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
        ERESULT eRc = HashT_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another HASHT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         HashT_Assign (
        HASHT_DATA       *this,
        HASHT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!HashT_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             HashT_Compare (
        HASHT_DATA     *this,
        HASHT_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!HashT_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        HashT      *pCopy = HashT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a HASHT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    HASHT_DATA *     HashT_Copy (
        HASHT_DATA       *this
    )
    {
        HASHT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef HASHT_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = HashT_New( );
        if (pOther) {
            eRc = HashT_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            HashT_Dealloc (
        OBJ_ID          objId
    )
    {
        HASHT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((HASHT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pHash) {
            mem_Free(this->pHash);
            this->pHash = NULL;
            this->cHash = 0;
        }
        HashT_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        HashT      *pDeepCopy = HashT_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a HASHT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    HASHT_DATA *     HashT_DeepCopy (
        HASHT_DATA       *this
    )
    {
        HASHT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = HashT_New( );
        if (pOther) {
            eRc = HashT_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         HashT_Disable (
        HASHT_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         HashT_Enable (
        HASHT_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   HASHT_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    HASHT_DATA *   HashT_Init (
        HASHT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(HASHT_DATA);
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

        this = (OBJ_ID)Blocks_Init((BLOCKS_DATA *)this);    // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of HashT_object.c
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_HASHT);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&HashT_Vtbl);
#ifdef  HASHT_JSON_SUPPORT
        JsonIn_RegisterClass(HashT_Class());
#endif
        
        Blocks_setDeleteExit(
                        (BLOCKS_DATA *)this,
                        (void *)HashT_DeleteExit,
                        this,               // 1st parameter
                        NULL                // 3rd parameter
        );

        this->pLevels = array_NewWithSize(sizeof(LISTDL_DATA));
        if (OBJ_NIL == this->pLevels) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        } else {
            LISTDL_DATA     list;
            // Add Scope 0.
            listdl_Init(&list, offsetof(HASHT_NODE, level));
            eRc = array_Push(this->pLevels, &list);
        }


#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "HashT::sizeof(HASHT_DATA) = %lu\n", 
                sizeof(HASHT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(HASHT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         HashT_IsEnabled (
        HASHT_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = HashT_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "HashT", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          HashT_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        HASHT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(HASHT_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)HashT_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return HashT_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return HashT_Enable;
                        }
                        break;

                    case 'P':
#ifdef  HASHT_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return HashT_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return HashT_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return HashT_ToDebugString;
                        }
#ifdef  HASHT_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return HashT_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return HashT_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == HashT_ToDebugString)
                    return "ToDebugString";
#ifdef  HASHT_JSON_SUPPORT
                if (pData == HashT_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S c o p e
    //---------------------------------------------------------------

    ERESULT         HashT_ScopeClose (
        HASHT_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     list;
        HASHT_NODE      *pNode;
        HASHT_NODE      *pNext = NULL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Remove the scope.
        eRc = array_Pop(this->pLevels, &list);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        // Now remove the scope entries from the table.
#ifdef XYZZY
        pNode = listdl_Head(&list);
        while (pNode) {
            pNext = listdl_Next(&list, &pNext);
        }
#endif

        // Return to caller.
        return eRc;
    }


    uint32_t        HashT_ScopeOpen (
        HASHT_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        LISTDL_DATA     list;
        uint32_t        level = 0;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        listdl_Init(&list, offsetof(HASHT_NODE, level));
        eRc = array_Push(this->pLevels, &list);
        if (ERESULT_OK(eRc)) {
            level = HashT_getNumScopes(this) - 1;
        }

        // Return to caller.
        return level;
    }



    //---------------------------------------------------------------
    //                      S e t u p
    //---------------------------------------------------------------

    /*!
     Perform initial setup of the hash table.
     @param     this        object pointer
     @param     dataSize    Size in bytes of the data
     @param     cHash       Number of Buckets in the Hash Table.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         HashT_Setup (
        HASHT_DATA      *this,
        uint16_t        dataSize,
        uint16_t        cHash           // [in] Hash Table Size
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        cbSize;
        uint32_t        i;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  HASHT_SINGLETON
        if (OBJ_NIL == this) {
            this = HashT_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        dataSize = ROUNDUP4(dataSize);
        dataSize += sizeof(HASHT_NODE);

        eRc = Blocks_SetupSizes((BLOCKS_DATA *)this, 0, dataSize);
        if (ERESULT_FAILED(eRc)) {
           DEBUG_BREAK();
           return eRc;
        }

        // Allocate the Hash Table.
        cbSize = cHash * sizeof(LISTDL_DATA);
        this->pHash = (LISTDL_DATA *)mem_Malloc(cbSize);
        if (NULL == this->pHash) {
           DEBUG_BREAK();
           return ERESULT_OUT_OF_MEMORY;
        }
        this->cHash = cHash;
        for (i=0; i<cHash; ++i) {
           listdl_Init(&this->pHash[i], offsetof(HASHT_NODE, list));
        }
        listdl_Init(&this->freeList, offsetof(HASHT_NODE, list));

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = HashT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     HashT_ToDebugString (
        HASHT_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!HashT_Validate(this)) {
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
                    HashT_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            HashT_Validate (
        HASHT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_HASHT))
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


        if (!(obj_getSize(this) >= sizeof(HASHT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


