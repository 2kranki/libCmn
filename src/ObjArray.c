// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjArray.c
 *	Generated 12/29/2019 20:07:07
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
#include        <ObjArray_internal.h>
#include        <ObjEnum_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ObjArray_task_body (
        void            *pData
    )
    {
        //OBJARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJARRAY_DATA *     ObjArray_Alloc (
        void
    )
    {
        OBJARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(OBJARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJARRAY_DATA *     ObjArray_New (
        void
    )
    {
        OBJARRAY_DATA       *this;
        
        this = ObjArray_Alloc( );
        if (this) {
            this = ObjArray_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         A r r a y
    //---------------------------------------------------------------
    
    ARRAY_DATA *    ObjArray_getArray (
        OBJARRAY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return (ARRAY_DATA *)this;
    }
        
     
    
    //---------------------------------------------------------------
    //                           O b j e c t
    //---------------------------------------------------------------
    
    OBJ_ID          ObjArray_getOther (
        OBJARRAY_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOther;
    }
    
    
    bool        ObjArray_setOther (
        OBJARRAY_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_OTHER_OWNED
        obj_Retain(pValue);
        if (this->pOther) {
            obj_Release(this->pOther);
        }
#endif
        this->pOther = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjArray_getSize (
        OBJARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize((ARRAY_DATA *)this);;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ObjArray_getSuperVtbl (
        OBJARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
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
    //                       A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_Append (
        OBJARRAY_DATA    *this,
        OBJARRAY_DATA    *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        max;
        OBJ_DATA        *pItem;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !ObjArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        max = ObjArray_getSize(pOther);
        
        // Copy over the elements.
        for (i=0; i<max; ++i) {
            pItem = ObjArray_Get(pOther, i+1);
            if (pItem) {
                eRc = ObjArray_AppendObj(this, pItem, NULL);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         ObjArray_AppendObj (
        OBJARRAY_DATA   *this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        obj_Retain(pObject);
        eRc = array_AppendData((ARRAY_DATA *)this, 1, &pObject);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pObject);
            return eRc;
        }
        if (pIndex) {
            *pIndex = array_getSize((ARRAY_DATA *)this);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
        ERESULT eRc = ObjArray_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjArray_Assign (
        OBJARRAY_DATA   *this,
        OBJARRAY_DATA   *pOther
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        OBJ_ID          pEntry;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjArray_Validate(pOther)) {
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
        ObjArray_DeleteAll(pOther);
        ObjArray_setOther(pOther, OBJ_NIL);

        // Create a copy of objects and areas in this object placing
        // them in other.
        iMax = ObjArray_getSize(this);
        for (i=0; i<iMax; i++) {
            pEntry = ObjArray_Get(this, i+1);
            ObjArray_AppendObj(pOther, pEntry, NULL);
        }
        if (this->pOther) {
            if (obj_getVtbl(this->pOther)->pCopy) {
                pOther->pOther = obj_getVtbl(this->pOther)->pCopy(this->pOther);
            }
            else {
                obj_Retain(this->pOther);
                pOther->pOther = this->pOther;
            }
        }

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
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
    ERESULT         ObjArray_Compare (
        OBJARRAY_DATA     *this,
        OBJARRAY_DATA     *pOther
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
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjArray_Validate(pOther)) {
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
        ObjArray      *pCopy = ObjArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJARRAY_DATA *     ObjArray_Copy (
        OBJARRAY_DATA       *this
    )
    {
        OBJARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjArray_New( );
        if (pOther) {
            eRc = ObjArray_Assign(this, pOther);
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

    void            ObjArray_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ObjArray_setOther(this, OBJ_NIL);
        ObjArray_DeleteAll(this);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * ObjArray_DeepCopy(
        OBJARRAY_DATA   *this
    )
    {
        OBJARRAY_DATA   *pOther;
        uint32_t        i;
        uint32_t        iMax;
        OBJ_IUNKNOWN    *pVtbl;
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pItem;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjArray_New();
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        iMax = array_getSize((ARRAY_DATA *)this);
        for (i=0; i<iMax; ++i) {
            pEntry = array_Ptr((ARRAY_DATA *)this, (i + 1));
            if (pEntry && pEntry->pObj) {
                pItem = pEntry->pObj;
                pVtbl = obj_getVtbl(pItem);
                if (pVtbl->pDeepCopy) {
                    pItem = pVtbl->pDeepCopy(pItem);
                }
                else if (pVtbl->pCopy) {
                    pItem = pVtbl->pCopy(pItem);
                }
                else {
                    obj_Retain(pItem);
                }
                array_AppendData((ARRAY_DATA *)pOther, 1, &pItem);
            }
        }
        
        // Return to caller.
        return pOther;
    }
        
        
        
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    OBJ_ID          ObjArray_Delete (
        OBJARRAY_DATA   *this,
        uint32_t        index
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (array_getSize((ARRAY_DATA *)this))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (index && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            return OBJ_NIL;
        }
#endif
        
        eRc = array_Get((ARRAY_DATA *)this, index, 1, &pObj);
        if (ERESULT_FAILED(eRc)) {
            return OBJ_NIL;
        }
        eRc = array_Delete((ARRAY_DATA *)this, index, 1);
        if (ERESULT_FAILED(eRc)) {
            return OBJ_NIL;
        }
        
        return pObj;
    }
    
    
    ERESULT         ObjArray_DeleteAll (
        OBJARRAY_DATA   *this
    )
    {
        ERESULT         eRc;
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        iMax = array_getSize((ARRAY_DATA *)this);
        for (i=iMax; i>0; --i) {
            eRc = array_Get((ARRAY_DATA *)this, i, 1, &pObj);
            if (ERESULT_FAILED(eRc)) {
                return ERESULT_GENERAL_FAILURE;
            }
            eRc = array_Delete((ARRAY_DATA *)this, i, 1);
            if (ERESULT_FAILED(eRc)) {
                return ERESULT_GENERAL_FAILURE;
            }
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    OBJ_ID          ObjArray_DeleteFirst (
        OBJARRAY_DATA    *this
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (array_getSize((ARRAY_DATA *)this))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pObj = ObjArray_Delete(this, 1);
        
        return pObj;
    }
    
    
    OBJ_ID          ObjArray_DeleteLast (
        OBJARRAY_DATA   *this
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (array_getSize((ARRAY_DATA *)this))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        size = array_getSize((ARRAY_DATA *)this);
        
        pObj = ObjArray_Delete(this, size);
        
        return pObj;
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
    ERESULT         ObjArray_Disable (
        OBJARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjArray_Validate(this)) {
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
    ERESULT         ObjArray_Enable (
        OBJARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjArray_Validate(this)) {
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
    //                      E n u m
    //---------------------------------------------------------------
    
    OBJENUM_DATA *  ObjArray_Enum (
        OBJARRAY_DATA   *this
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum = OBJ_NIL;
        uint32_t        i;
        OBJ_ID          *ppObj;

        // Do initialization.
        if (NULL == this) {
            return pEnum;
        }
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return pEnum;
        }
#endif
        
        pEnum = ObjEnum_New();
        if (pEnum) {
            for (i=0; i<array_getSize((ARRAY_DATA *)this); ++i) {
                ppObj = array_Ptr((ARRAY_DATA *)this, (i + 1));
                if (*ppObj) {
                    eRc = ObjEnum_AppendObj(pEnum, *ppObj);
                }
            }
            if (pEnum->pArray) {
                eRc = ObjArray_SortAscending(pEnum->pArray, NULL);
            }
        }
        
        // Return to caller.
        return pEnum;
    }
        
        
        
    //---------------------------------------------------------------
    //                     F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_ForEach (
        OBJARRAY_DATA   *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        index;
        uint32_t        size;
        OBJ_ID          *ppNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (pScan) {
            size = array_getSize((ARRAY_DATA *)this);
            for (index = 0; index < size; ++index) {
                ppNode = array_Ptr((ARRAY_DATA *)this, index+1);
                eRc = pScan(pObj, *ppNode, pArg3);
                if (ERESULT_FAILED(eRc))
                    break;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------
    
    OBJ_ID          ObjArray_Get (
        OBJARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    )
    {
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (index && (index <= array_getSize((ARRAY_DATA *)this)))
            ;
        else {
            return OBJ_NIL;
        }
#endif
        
        pEntry = array_Ptr((ARRAY_DATA *)this, index);
        if (pEntry && pEntry->pObj) {
            pObj = pEntry->pObj;
        }

        return pObj;
    }
    
    
    OBJ_ID          ObjArray_GetFirst (
        OBJARRAY_DATA    *this
    )
    {
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEntry = array_Ptr((ARRAY_DATA *)this, 1);
        if (pEntry && pEntry->pObj) {
            pObj = pEntry->pObj;
        }

        return pObj;
    }
    
    
    OBJ_ID          ObjArray_GetLast (
        OBJARRAY_DATA   *this
    )
    {
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        size = array_getSize((ARRAY_DATA *)this);
        
        if (size) {
            pEntry = array_Ptr((ARRAY_DATA *)this, size);
            if (pEntry && pEntry->pObj) {
                pObj = pEntry->pObj;
            }
        }

        return pObj;
    }
    
        
        
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJARRAY_DATA *   ObjArray_Init (
        OBJARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJARRAY_DATA);
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

        this = (OBJ_ID)array_Init((ARRAY_DATA *)this);          // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjArray_Vtbl);
        array_setElemSize((ARRAY_DATA *)this, sizeof(ARRAY_ENTRY));

        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

    #ifdef NDEBUG
    #else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "ObjArray::sizeof(OBJARRAY_DATA) = %lu\n", sizeof(OBJARRAY_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJARRAY_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                   I n s e r t  O b j e c t
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_InsertObj (
        OBJARRAY_DATA   *this,
        uint32_t        index,
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (index <= array_getSize((ARRAY_DATA *)this)) {
        }
        else {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        
        obj_Retain(pObject);

        eRc = array_InsertData((ARRAY_DATA *)this, index, 1, &pObject);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pObject);
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
        
        
        
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_IsEnabled (
        OBJARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
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
    //                            P o p
    //---------------------------------------------------------------
    
    OBJ_ID          ObjArray_Pop (
        OBJARRAY_DATA   *this
    )
    {
        ERESULT         eRc;
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        size = array_getSize((ARRAY_DATA *)this);
        if (size) {
            pEntry = array_Ptr((ARRAY_DATA *)this, size);
            if (pEntry && pEntry->pObj) {
                pObj = pEntry->pObj;
                eRc = array_Delete((ARRAY_DATA *)this, size, 1);
            }
        }
        
        return pObj;
    }
    
    
    
    //---------------------------------------------------------------
    //                            P u s h
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_Push (
        OBJARRAY_DATA   *this,
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        obj_Retain(pObject);
        eRc = array_AppendData((ARRAY_DATA *)this, 1, &pObject);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pObject);
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_Put (
        OBJARRAY_DATA   *this,
        uint32_t        index,          // Relative to 1
        OBJ_ID          pObj
    )
    {
        ERESULT         eRc;
        OBJ_ID          pOld;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        obj_Retain(pObj);

        pOld = ObjArray_Get(this, index);
        if (pOld) {
            obj_Release(pOld);
        }

        eRc = array_Put((ARRAY_DATA *)this, index, 1, &pObj);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
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
        void        *pMethod = ObjArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjArray", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJARRAY_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjArray_Class();
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
                            return ObjArray_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjArray_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjArray_ToDebugString;
                        }
#ifdef  OBJARRAY_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjArray_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjArray_ToDebugString)
                    return "ToDebugString";
#ifdef  OBJARRAY_JSON_SUPPORT
                if (pData == ObjArray_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S o r t
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_SortAscending (
        OBJARRAY_DATA    *this,
        OBJ_COMPARE     pCompare
    )
    {
        ERESULT         eRc;
        ARRAY_ENTRY     *pEntry;
        OBJ_ID          pObj1 = OBJ_NIL;
        OBJ_ID          pObj2;
        uint32_t        i;
        uint32_t        j;
        //OBJ_ID          pSave;
        OBJ_IUNKNOWN    *pUnk;
        
        /*      Insertion Sort from Wikipedia
         *
         *  for i = 1 to length(A)
         *      j = i
         *      while j > 0 and A[j-1] > A[j]
         *          swap A[j] and A[j-1]
         *          j = j - 1
         *      end while
         *  end for
         *
         *  NOTE:   indexing is relative to zero.
         *          adjust as necessary.
         */
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (array_getSize((ARRAY_DATA *)this) < 2) {
            return ERESULT_SUCCESS;
        }
        
        if (NULL == pCompare) {
            pEntry = array_Ptr((ARRAY_DATA *)this, 1);
            if (pEntry) {
                pObj1 = pEntry->pObj;
            }
            if (OBJ_NIL == pObj1) {
                return ERESULT_INVALID_OBJECT;
            }
            pUnk = obj_getVtbl(pObj1);
            if (pUnk)
                pCompare = pUnk->pCompare;
            if (pCompare == NULL) {
                return ERESULT_INVALID_FUNCTION;
            }
        }
        
        for (i=1; i<array_getSize((ARRAY_DATA *)this); ++i) {
            j = i;
            while (j > 0) {
                pEntry = array_Ptr((ARRAY_DATA *)this, j);
                pObj1 = pEntry->pObj;
                ++pEntry;
                pObj2 = pEntry->pObj;
                eRc = (*pCompare)(pObj1, pObj2);
                if (ERESULT_SUCCESS_GREATER_THAN == eRc) {
                    pEntry->pObj = pObj1;
                    --pEntry;
                    pEntry->pObj = pObj2;
                    --j;
                }
                else
                    break;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                            T o p
    //---------------------------------------------------------------
    
    OBJ_ID          ObjArray_Top (
        OBJARRAY_DATA   *this
    )
    {
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        size = array_getSize((ARRAY_DATA *)this);
        if (size) {
            pEntry = array_Ptr((ARRAY_DATA *)this, size);
            if (pEntry && pEntry->pObj) {
                pObj = pEntry->pObj;
            }
        }
        
        return pObj;
    }
    
        
        
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjArray_ToDebugString (
        OBJARRAY_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        uint32_t        iMax;
        OBJ_ID          pObj;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjArray_Validate(this)) {
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
        iMax = ObjArray_getSize(this);
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    ObjArray_getSize(this),
                    obj_getRetainCount(this)
            );

        for (i=0; i<iMax; i++) {
            pObj = ObjArray_Get(this, i+1);
            if (pObj) {
                if (((OBJ_DATA *)(pObj))->pVtbl->pToDebugString) {
                    pWrkStr =   ((OBJ_DATA *)(pObj))->pVtbl->pToDebugString(
                                                        pObj,
                                                        indent+3
                                );
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            ObjArray_Validate (
        OBJARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJARRAY))
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


        if (!(obj_getSize(this) >= sizeof(OBJARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                            X c h g
    //---------------------------------------------------------------
    
    ERESULT         ObjArray_Xchg (
        OBJARRAY_DATA   *this,
        uint32_t        index1,         // Relative to 1
        uint32_t        index2          // Relative to 1
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = array_Xchg((ARRAY_DATA *)this, index1, index2);
        
        return eRc;
    }
        
        


    
#ifdef	__cplusplus
}
#endif


