// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objArray.c
 *	Generated 03/22/2016 17:01:56
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
#include    <objArray_internal.h>
#include    <objEnum_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJARRAY_DATA *     objArray_Alloc(
    )
    {
        OBJARRAY_DATA   *this;
        uint32_t        cbSize = sizeof(OBJARRAY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    OBJARRAY_DATA *     objArray_New(
    )
    {
        OBJARRAY_DATA       *this;
        
        this = objArray_Alloc( );
        if (this) {
            this = objArray_Init( this );
        } 
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         objArray_getLastError(
        OBJARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->eRc;
    }
    
    
    
    uint32_t        objArray_getSize(
        OBJARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return array_getSize(this->pArray);
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                         A p p e n d  O b j e c t
    //---------------------------------------------------------------
    
    //---------------------------------------------------------------
    //                       A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         objArray_Append(
        OBJARRAY_DATA	*this,
        OBJARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        max;
        OBJ_DATA        *pItem;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !objArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        max = objArray_getSize(pOther);
        
        // Copy over the elements.
        for (i=0; i<max; ++i) {
            pItem = objArray_Get(pOther, i+1);
            if (pItem) {
                eRc = objArray_AppendObj(this, pItem, NULL);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
            }
        }
        
        // Return to caller.
        this->eRc = eRc;
        return eRc;
    }
    
    
    ERESULT         objArray_AppendObj(
        OBJARRAY_DATA	*this,
        OBJ_ID          pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        obj_Retain(pObject);
        eRc = array_AppendData(this->pArray, 1, &pObject);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pObject);
            this->eRc = array_getLastError(this->pArray);
            return this->eRc;
        }
        if (pIndex) {
            *pIndex = array_getSize(this->pArray);
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return ERESULT_SUCCESS;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         objArray_Assign(
        OBJARRAY_DATA	*this,
        OBJARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //uint32_t        i;
        //OBJ_DATA        *pItem;
        //OBJ_IUNKNOWN    *pVtbl;
        //ARRAY_ENTRY     *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !objArray_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //FIXME: Restore this.
#ifdef XYZZY
        // Release any objects that the Other Array has.
        for (i=0; i<pOther->size; ++i) {
            pItem = pOther->ppArray[i];
            obj_Release(pItem);
            pOther->ppArray[i] = OBJ_NIL;
        }
        pOther->size = 0;
        
        // Increase size of the other array if needed.
        while (pOther->max < this->max) {
            if ((this->max - pOther->max) < 32768) {
                i = this->max - pOther->max;
            }
            else {
                i = 32768;
            }
            objArray_ExpandArray( pOther, i );
        }
        
        // Copy over the elements.
        for (i=0; i<this->size; ++i) {
            pItem = this->ppArray[i];
            pVtbl = obj_getVtbl(pItem);
            if (pVtbl->pCopy) {
                pItem = pVtbl->pCopy(pItem);
            }
            else {
                obj_Retain(pItem);
            }
            pOther->ppArray[i] = pItem;
        }
        pOther->size = this->size;
#endif
        
        // Return to caller.
        this->eRc = eRc;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * objArray_Copy(
        OBJARRAY_DATA	*this
    )
    {
        OBJARRAY_DATA   *pOther;
        uint32_t        i;
        uint32_t        iMax;
        ARRAY_ENTRY     *pEntry;
        OBJ_ID          pItem;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objArray_New();
        if (OBJ_NIL == pOther) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        
        iMax = array_getMax(this->pArray);
        for (i=0; i<iMax; ++i) {
            pEntry = array_Ptr(this->pArray, (i + 1));
            if (pEntry && pEntry->pObj) {
                pItem = pEntry->pObj;
                obj_Retain(pItem);
                array_AppendData(pOther->pArray, 1, &pItem);
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objArray_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJARRAY_DATA   *this = objId;
        uint32_t        i;
        uint32_t        iMax;
        ARRAY_ENTRY     *pEntry = NULL;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        iMax = array_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pEntry = array_Ptr(this->pArray, (i + 1));
            if (pEntry && pEntry->pObj) {
                if (obj_getRetainCount(pEntry->pObj)) {
                    obj_Release(pEntry->pObj);
                    memset(pEntry, 0, sizeof(ARRAY_ENTRY));
                }
            }
        }
        
        obj_Release(this->pArray);
        this->pArray = OBJ_NIL;
        
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
    
    OBJARRAY_DATA * objArray_DeepCopy(
        OBJARRAY_DATA    *this
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
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objArray_New();
        if (OBJ_NIL == pOther) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return OBJ_NIL;
        }
        
        iMax = array_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pEntry = array_Ptr(this->pArray, (i + 1));
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
                array_AppendData(pOther->pArray, 1, &pItem);
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    OBJ_ID          objArray_Delete(
        OBJARRAY_DATA	*this,
        uint32_t        index
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NULL(this->pArray);
        if (array_getSize(this->pArray))
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
        if (index && (index <= array_getSize(this->pArray)))
            ;
        else {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        if (this->pArray) {
            eRc = array_Get(this->pArray, index, 1, &pObj);
            if (ERESULT_FAILED(eRc)) {
                this->eRc = ERESULT_DATA_NOT_FOUND;
                return OBJ_NIL;
            }
            eRc = array_Delete(this->pArray, index, 1);
            if (ERESULT_FAILED(eRc)) {
                this->eRc = ERESULT_GENERAL_FAILURE;
                return OBJ_NIL;
            }
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    OBJ_ID          objArray_DeleteFirst(
        OBJARRAY_DATA	*this
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NULL(this->pArray);
        if (array_getSize(this->pArray))
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif

        pObj = objArray_Delete(this, 1);
        
        return pObj;
    }
    
    
    OBJ_ID          objArray_DeleteLast(
        OBJARRAY_DATA	*this
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        BREAK_NULL(this->pArray);
        if (array_getSize(this->pArray))
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        size = array_getSize(this->pArray);
        
        pObj = objArray_Delete(this, size);
        
        return pObj;
    }
    
    
    
    //---------------------------------------------------------------
    //                      E n u m
    //---------------------------------------------------------------
    
    OBJENUM_DATA *  objArray_Enum(
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
        if( !objArray_Validate(this) ) {
            DEBUG_BREAK();
            return pEnum;
        }
#endif
        
        if (this->pArray) {
            for (i=0; i<array_getSize(this->pArray); ++i) {
                ppObj = array_Ptr(this->pArray, (i + 1));
                if (*ppObj) {
                    eRc = objEnum_Append(pEnum, *ppObj);
                }
            }
            eRc = objArray_SortAscending(pEnum->pArray, NULL);
        }
        
        // Return to caller.
        return pEnum;
    }
    
    
    
    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------
    
    OBJ_ID          objArray_Get(
        OBJARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    )
    {
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (index && (index <= array_getSize(this->pArray)))
            ;
        else {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        pEntry = array_Ptr(this->pArray, index);
        if (pEntry && pEntry->pObj) {
            pObj = pEntry->pObj;
        }

        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    OBJ_ID          objArray_GetFirst(
        OBJARRAY_DATA	*this
    )
    {
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEntry = array_Ptr(this->pArray, 1);
        if (pEntry && pEntry->pObj) {
            pObj = pEntry->pObj;
        }

        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    OBJ_ID          objArray_GetLast(
        OBJARRAY_DATA	*this
    )
    {
        ARRAY_ENTRY     *pEntry = NULL;
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        size;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NULL(this->pArray);
#endif
        size = array_getSize(this->pArray);
        
        if (size) {
            pEntry = array_Ptr(this->pArray, size);
            if (pEntry && pEntry->pObj) {
                pObj = pEntry->pObj;
            }
        }

        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJARRAY_DATA * objArray_Init(
        OBJARRAY_DATA   *this
    )
    {
        uint32_t        cbSize = sizeof(OBJARRAY_DATA);
        
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

        this = (OBJ_ID)obj_Init( this, cbSize, OBJ_IDENT_OBJARRAY );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_OBJARRAY); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objArray_Vtbl);
        
        this->pArray = array_New(sizeof(ARRAY_ENTRY));
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        array_setZeroNew(this->pArray, true);

    #ifdef NDEBUG
    #else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                   I n s e r t  O b j e c t
    //---------------------------------------------------------------
    
    ERESULT         objArray_InsertObj(
        OBJARRAY_DATA	*this,
        uint32_t        index,
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return ERESULT_INVALID_PARAMETER;
        }
        if (index <= array_getSize(this->pArray)) {
        }
        else {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        
        obj_Retain(pObject);

        eRc = array_InsertData(this->pArray, index, 1, &pObject);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pObject);
            this->eRc = ERESULT_GENERAL_FAILURE;
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------
    
    ERESULT         objArray_Put(
        OBJARRAY_DATA	*this,
        uint16_t        index,          // Relative to 1
        OBJ_ID          pObj
    )
    {
        ERESULT         eRc;
        OBJ_ID          pOld;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return this->eRc;
        }
        BREAK_NULL(this->pArray);
        if (index)
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        obj_Retain(pObj);

        pOld = objArray_Get(this, index);
        if (pOld) {
            obj_Release(pOld);
        }

        eRc = array_Put(this->pArray, index, 1, &pObj);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            this->eRc = eRc;
            return eRc;
        }
        
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
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
     void        *pMethod = objArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   OBJARRAY object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                        character string which represents the method name without
                        the object name, "name", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          objArray_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJARRAY_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !objArray_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return objArray_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S o r t
    //---------------------------------------------------------------
    
    ERESULT         objArray_SortAscending(
        OBJARRAY_DATA	*this,
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
         */
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (array_getSize(this->pArray) < 2) {
            this->eRc = ERESULT_SUCCESS;
            return ERESULT_SUCCESS;
        }
        
        if (NULL == pCompare) {
            pEntry = array_Ptr(this->pArray, 1);
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
        
        for (i=1; i<array_getSize(this->pArray); ++i) {
            j = i;
            while (j > 0) {
                pEntry = array_Ptr(this->pArray, j);
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
        this->eRc = ERESULT_SUCCESS;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     objArray_ToDebugString(
        OBJARRAY_DATA   *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        uint32_t        i;
        uint32_t        size;
        ARRAY_ENTRY     *pEntry;
        OBJ_ID          pObj;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        size = objArray_getSize(this);
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(objArray) size=%d\n",
                     this,
                     size
            );
        BREAK_FALSE( (j < sizeof(str)) );
        AStr_AppendA(pStr, str);

        if (this->pArray) {
            for (i=0; i<size; ++i) {
                AStr_AppendCharRepeatW32(pStr, indent+3, ' ');
                str[0] = '\0';
                j = snprintf(str, sizeof(str), "%d\n", i+1);
                BREAK_FALSE( (j < sizeof(str)) );
                AStr_AppendA(pStr, str);
                pEntry = array_Ptr(this->pArray, (i + 1));
                if (pEntry && pEntry->pObj) {
                    pObj = pEntry->pObj;
                    if (obj_getVtbl(pObj)->pToDebugString) {
                        pWrkStr =   obj_getVtbl(pObj)->pToDebugString(
                                                        pObj,
                                                        indent+6
                                    );
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                    }
                }
                else {
                    AStr_AppendCharRepeatW32(pStr, indent+6, ' ');
                    AStr_AppendA(pStr, "NULL\n");
                }
            }
        }
        
        j = snprintf( str, sizeof(str), " %p(objArray)}\n", this );
        BREAK_FALSE( (j < sizeof(str)) );
        AStr_AppendA(pStr, str);
        
        this->eRc = ERESULT_SUCCESS;
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objArray_Validate(
        OBJARRAY_DATA      *this
    )
    {
        if (OBJ_NIL == this) {
            return false;
        }
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_OBJARRAY) )
                ;
            else {
                return false;
            }
        }
        else {
            return false;
        }
        if( !(obj_getSize(this) >= sizeof(OBJARRAY_DATA)) ) {
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


