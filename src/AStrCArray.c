// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AStrCArray.c
 *	Generated 11/07/2019 08:58:19
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
#include        <AStrCArray_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            AStrCArray_task_body (
        void            *pData
    )
    {
        //ASTRCARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ASTRCARRAY_DATA *     AStrCArray_Alloc (
        void
    )
    {
        ASTRCARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(ASTRCARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTRCARRAY_DATA * AStrCArray_New (
        void
    )
    {
        ASTRCARRAY_DATA *this;
        
        this = AStrCArray_Alloc( );
        if (this) {
            this = AStrCArray_Init(this);
        } 
        return this;
    }



    ASTRCARRAY_DATA * AStrCArray_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgV[]
    )
    {
        ASTRCARRAY_DATA *pArray = OBJ_NIL;
        ASTRC_DATA      *pStr = OBJ_NIL;
        int             i;
        
        if ((cArgs < 1) || (NULL == ppArgV)) {
            return OBJ_NIL;
        }
        pArray = AStrCArray_New( );
        if (pArray) {
            for (i=0; i<cArgs; ++i) {
                if (ppArgV[i]) {
                    pStr = AStrC_NewA(ppArgV[i]);
                    if (pStr) {
                        AStrCArray_AppendAStrC(pArray, pStr, NULL);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                    else {
                        obj_Release(pArray);
                        pArray = OBJ_NIL;
                        break;
                    }
                }
            }
        }
        
        return pArray;
    }
    
    
    ASTRCARRAY_DATA * AStrCArray_NewFromArrayA(
        const
        char            *ppArgV[]
    )
    {
        ASTRCARRAY_DATA *pArray = OBJ_NIL;
        ASTRC_DATA      *pStr = OBJ_NIL;
        
        if (NULL == ppArgV) {
            return OBJ_NIL;
        }
        pArray = AStrCArray_New( );
        if (pArray) {
            while (*ppArgV) {
                pStr = AStrC_NewA(*ppArgV);
                if (pStr) {
                    AStrCArray_AppendAStrC(pArray, pStr, NULL);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                else {
                    obj_Release(pArray);
                    pArray = OBJ_NIL;
                    break;
                }
                ++ppArgV;
            }
        }
        
        return pArray;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * AStrCArray_getArray (
        ASTRCARRAY_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            AStrCArray_setArray (
        ASTRCARRAY_DATA *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_ARRAY_OWNED
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
#endif
        this->pArray = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        AStrCArray_getPriority (
        ASTRCARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            AStrCArray_setPriority (
        ASTRCARRAY_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
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
    
    uint32_t        AStrCArray_getSize (
        ASTRCARRAY_DATA       *this
    )
    {
        uint32_t        i = 0;

#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->pArray) {
            i = objArray_getSize(this->pArray);
        }
        
        return i;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  AStrCArray_getSuperVtbl (
        ASTRCARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
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
    //                          A p p e n d
    //---------------------------------------------------------------
    
    /*!
     Append the given string to the array and return its index.
     @param     this    Object Pointer
     @param     pObject String Object to be added
     @param     pIndex  (Optional) Index Pointer
     @return    If successful, ERESULT_SUCCESS and the index in pIndex
                if it is not NULL.  Otherwise, an ERESULT_* error.
     */
    ERESULT         AStrCArray_AppendAStr(
        ASTRCARRAY_DATA *this,
        ASTR_DATA       *pObject,
        uint32_t        *pIndex
        )
        {
            ERESULT         eRc;
            ASTRC_DATA      *pStrC;
            
            // Do initialization.
            if (NULL == this) {
                return ERESULT_INVALID_OBJECT;
            }
    #ifdef NDEBUG
    #else
            if( !AStrCArray_Validate(this) ) {
                DEBUG_BREAK();
                return ERESULT_INVALID_OBJECT;
            }
    #endif
            
            if (OBJ_NIL == this->pArray) {
                this->pArray = objArray_New();
                if (OBJ_NIL == this->pArray) {
                    return ERESULT_OUT_OF_MEMORY;
                }
            }
            
            pStrC = AStrC_NewFromAStr(pObject);
            if (OBJ_NIL == pStrC)
                return ERESULT_OUT_OF_MEMORY;
            eRc = objArray_AppendObj(this->pArray, pStrC, pIndex);
            obj_Release(pStrC);
            pStrC = OBJ_NIL;
            
            // Return to caller.
            return eRc;
        }

        
    ERESULT         AStrCArray_AppendAStrC(
        ASTRCARRAY_DATA *this,
        ASTRC_DATA      *pObject,
        uint32_t        *pIndex
        )
        {
            ERESULT         eRc;
            
            // Do initialization.
            if (NULL == this) {
                return ERESULT_INVALID_OBJECT;
            }
    #ifdef NDEBUG
    #else
            if( !AStrCArray_Validate(this) ) {
                DEBUG_BREAK();
                return ERESULT_INVALID_OBJECT;
            }
    #endif
            
            if (OBJ_NIL == this->pArray) {
                this->pArray = objArray_New();
                if (OBJ_NIL == this->pArray) {
                    return ERESULT_OUT_OF_MEMORY;
                }
            }
            
            eRc = objArray_AppendObj(this->pArray, pObject, pIndex);
            
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
        ERESULT eRc = AStrCArray_Assign(this,pOther);
     @endcode 
     @param     this    ASTRCARRAY object pointer
     @param     pOther  a pointer to another ASTRCARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         AStrCArray_Assign (
        ASTRCARRAY_DATA	*this,
        ASTRCARRAY_DATA *pOther
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        ASTRC_DATA      *pAStrC = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AStrCArray_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pArray) {
            objArray_DeleteAll(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
        
        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pArray) {
            iMax = AStrCArray_getSize(this);
            for (i=0; i<iMax; i++) {
                pAStrC = AStrCArray_Get(this, i+1);
                if (pAStrC) {
                    eRc = AStrCArray_AppendAStrC(pOther, pAStrC, NULL);
                }
            }
        }
        
        // Copy other data from this object to other.
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         AStrCArray_Compare (
        ASTRCARRAY_DATA     *this,
        ASTRCARRAY_DATA     *pOther
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
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AStrCArray_Validate(pOther)) {
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
        AStrCArray      *pCopy = AStrCArray_Copy(this);
     @endcode 
     @param     this    ASTRCARRAY object pointer
     @return    If successful, a ASTRCARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ASTRCARRAY_DATA *     AStrCArray_Copy (
        ASTRCARRAY_DATA *this
    )
    {
        ASTRCARRAY_DATA *pOther = OBJ_NIL;
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        ASTRC_DATA      *pAStrC = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AStrCArray_New( );
        if (pOther) {
            iMax = AStrCArray_getSize(this);
            for (i=0; i<iMax; i++) {
                pAStrC = AStrCArray_Get(this, i+1);
                if (pAStrC) {
                    eRc = AStrCArray_AppendAStrC(pOther, pAStrC, NULL);
                }
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            AStrCArray_Dealloc (
        OBJ_ID          objId
    )
    {
        ASTRCARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ASTRCARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pArray) {
            if (obj_getRetainCount(this->pArray) > 1) {
                DEBUG_BREAK();
            }
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrCArray_DeleteFirst(
        ASTRCARRAY_DATA *this
    )
    {
        ASTRC_DATA      *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrCArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTRC_DATA *    AStrCArray_DeleteLast(
        ASTRCARRAY_DATA *this
    )
    {
        ASTRC_DATA      *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrCArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_DeleteLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
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
    ERESULT         AStrCArray_Disable (
        ASTRCARRAY_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!AStrCArray_Validate(this)) {
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
    ERESULT         AStrCArray_Enable (
        ASTRCARRAY_DATA        *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!AStrCArray_Validate(this)) {
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

    uint32_t        AStrCArray_Find (
        ASTRCARRAY_DATA *this,
        ASTRC_DATA      *pStrC
    )
    {
        //ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        ASTRC_DATA      *pWrk;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (OBJ_NIL == this->pArray)
            return 0;
        
        iMax = objArray_getSize(this->pArray);
        for (i=0; i<iMax; i++) {
            pWrk = objArray_Get(this->pArray, i+1);
            if (ERESULT_SUCCESS_EQUAL == AStrC_Compare(pStrC, pWrk)) {
                return i+1;
            }
        }

        // Return to caller.
        return 0;
    }



    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------
    
    ASTRC_DATA *     AStrCArray_Get(
        ASTRCARRAY_DATA *this,
        uint32_t        index       // Relative to 1
    )
    {
        ASTRC_DATA      *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrCArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_Get(this->pArray, index);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTRC_DATA *     AStrCArray_GetFirst(
        ASTRCARRAY_DATA *this
    )
    {
        ASTRC_DATA      *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !AStrCArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetFirst(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTRC_DATA *    AStrCArray_GetLast(
        ASTRCARRAY_DATA *this
    )
    {
        ASTRC_DATA      *pNode = OBJ_NIL;
        
        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !AStrCArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            pNode = objArray_GetLast(this->pArray);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTRCARRAY_DATA *   AStrCArray_Init (
        ASTRCARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ASTRCARRAY_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ASTRCARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AStrCArray_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "AStrCArray::sizeof(ASTRCARRAY_DATA) = %lu\n", sizeof(ASTRCARRAY_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(ASTRCARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         AStrCArray_InsertStr(
        ASTRCARRAY_DATA *this,
        uint32_t        index,
        ASTRC_DATA      *pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrCArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = objArray_New();
            if (OBJ_NIL == this->pArray) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        eRc = objArray_InsertObj(this->pArray, index, pObject);
        
        // Return to caller.
        return eRc;
    }
        
        
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         AStrCArray_IsEnabled (
        ASTRCARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
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
        void        *pMethod = AStrCArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "AStrCArray", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          AStrCArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ASTRCARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(ASTRCARRAY_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)AStrCArray_Class();
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
                            return AStrCArray_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return AStrCArray_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return AStrCArray_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return AStrCArray_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == AStrCArray_ToDebugString)
                    return "ToDebugString";
                if (pData == AStrCArray_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         AStrCArray_SortAscending(
        ASTRCARRAY_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrCArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (this->pArray) {
            eRc = objArray_SortAscending(this->pArray, (OBJ_COMPARE)&AStrC_Compare);
        }
        
        // Return to caller.
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     AStrCArray_ToJSON (
        ASTRCARRAY_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
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
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrCArray_ToStringSep (
        ASTRCARRAY_DATA *this,
        const
        char            *pSep,
        const
        char            *pPrefix,           // Optional
        const
        char            *pSuffix            // Optional
    )
    {
        //ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        ASTR_DATA       *pStr;
        ASTRC_DATA      *pWrk;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrCArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pSep) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (OBJ_NIL == this->pArray) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        iMax = objArray_getSize(this->pArray);
        if (0 == iMax) {
            return pStr;
        }
        if (1 == iMax) {
            pWrk = objArray_Get(this->pArray, 1);
            if (pWrk) {
                if (pPrefix) {
                    AStr_AppendA(pStr, pPrefix);
                }
                AStr_AppendA(pStr, AStrC_getData(pWrk));
                if (pSuffix) {
                    AStr_AppendA(pStr, pSuffix);
                }
            }
            return pStr;
        }

        for (i=0; i<iMax-1; i++) {
            pWrk = objArray_Get(this->pArray, i+1);
            if (pWrk) {
                if (pPrefix) {
                    AStr_AppendA(pStr, pPrefix);
                }
                AStr_AppendA(pStr, AStrC_getData(pWrk));
                if (pSuffix) {
                    AStr_AppendA(pStr, pSuffix);
                }
                AStr_AppendA(pStr, pSep);
            }
        }
        pWrk = objArray_Get(this->pArray, i+1);
        if (pWrk) {
            if (pPrefix) {
                AStr_AppendA(pStr, pPrefix);
            }
            AStr_AppendA(pStr, AStrC_getData(pWrk));
            if (pSuffix) {
                AStr_AppendA(pStr, pSuffix);
            }
        }

        // Return to caller.
        return pStr;
    }



    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = AStrCArray_ToDebugString(this,4);
     @endcode 
     @param     this    ASTRCARRAY object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStrCArray_ToDebugString (
        ASTRCARRAY_DATA      *this,
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
        if (!AStrCArray_Validate(this)) {
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
                    AStrCArray_getSize(this)
            );

        if (this->pArray) {
            pWrkStr = objArray_ToDebugString(this->pArray, indent+4);
            if (pWrkStr) {
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
    bool            AStrCArray_Validate (
        ASTRCARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_ASTRCARRAY))
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


        if (!(obj_getSize(this) >= sizeof(ASTRCARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


