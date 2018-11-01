// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ptrArray.c
 *	Generated 07/02/2015 10:57:54
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
#include        <ptrArray_internal.h>
#include        <enum_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         ptrArray_ExpandArray(
        PTRARRAY_DATA   *this,
        uint16_t        num
    )
    {
        void            *pWork;
        uint32_t        oldMax;
        uint32_t        cbSize;
        uint16_t        elemSize = sizeof(uint8_t *);
        
        // Do initialization.
        if( this == NULL )
            return ERESULT_INVALID_OBJECT;
        if (num < this->max) {
            return ERESULT_SUCCESSFUL_COMPLETION;
        }
        
        // Expand the Array.
        oldMax = this->max;
        if (0 == oldMax) {
            oldMax = 1;
        }
        this->max = oldMax << 1;             // max *= 2
        while (num > this->max) {
            this->max = this->max << 1;
        }
        cbSize = this->max * elemSize;
        pWork = (void *)mem_Malloc(cbSize);
        if( NULL == pWork ) {
            this->max = oldMax;
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Copy the old entries into the new array.
        if( this->ppArray == NULL )
            ;
        else {
            memmove(pWork, this->ppArray, (oldMax * elemSize));
            mem_Free(this->ppArray);
            // this->ppArray = NULL;
        }
        this->ppArray = pWork;
        memset(&this->ppArray[oldMax], 0, ((this->max - oldMax) * elemSize));
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PTRARRAY_DATA * ptrArray_Alloc(
    )
    {
        PTRARRAY_DATA   *this;
        uint32_t        cbSize = sizeof(PTRARRAY_DATA);
        
        this = obj_Alloc( cbSize );
        
        return this;
    }



    PTRARRAY_DATA * ptrArray_New(
    )
    {
        PTRARRAY_DATA   *this;
        
        // Do initialization.
        
        this = ptrArray_Alloc(  );
        this = ptrArray_Init(this);
        
        // Return to caller.
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        ptrArray_getSize(
        PTRARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->size;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ptrArray_Dealloc(
        OBJ_ID          objId
    )
    {
        PTRARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->ppArray) {
            mem_Free(this->ppArray);
            this->ppArray = NULL;
            this->max = 0;
            this->size = 0;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;
        
        // Return to caller.
    }



    //---------------------------------------------------------------
    //                    A p p e n d  O b j e c t
    //---------------------------------------------------------------
    
    ERESULT         ptrArray_AppendData(
        PTRARRAY_DATA	*this,
        void            *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pObject) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        ++this->size;
        eRc = ptrArray_ExpandArray(this, this->size);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        this->ppArray[this->size-1] = (uint8_t *)pObject;
        if (pIndex) {
            *pIndex = this->size;
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    void *          ptrArray_Delete(
        PTRARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    )
    {
        uint8_t        *pData = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (index && (index <= this->size))
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        if (this->ppArray) {
            pData = this->ppArray[index-1];
            
            // Now shift array as needed.
            if (this->size - index) {
                memmove(
                        &this->ppArray[index-1],
                        &this->ppArray[index],
                        ((this->size - index) * sizeof(uint8_t *))
                );
            }
            --this->size;
        }
        
        return (void *)pData;
    }
    
    
    void *          ptrArray_DeleteFirst(
        PTRARRAY_DATA	*this
    )
    {
        void            *pObj = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (this->size)
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        --this->size;
        if (this->ppArray) {
            pObj = this->ppArray[0];
            memmove(
                    &this->ppArray[0],
                    &this->ppArray[1],
                    (this->size * sizeof(OBJ_DATA *))
                    );
        }
        
        return pObj;
    }
    
    
    void *          ptrArray_DeleteLast(
        PTRARRAY_DATA	*this
    )
    {
        void            *pObj = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (this->size)
            ;
        else {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        --this->size;
        if (this->ppArray) {
            pObj = this->ppArray[this->size];
            this->ppArray[this->size] = NULL;
        }
        
        return pObj;
    }
    
    
    
    //----------------------------------------------------------
    //                        E n u m
    //----------------------------------------------------------
    
    ERESULT         ptrArray_Enum(
        PTRARRAY_DATA   *this,
        ENUM_DATA       **ppEnum
    )
    {
        ENUM_DATA       *pEnum = OBJ_NIL;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            if (ppEnum) {
                *ppEnum = pEnum;
            }
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEnum = enum_New( );
        if (pEnum) {
        }
        else {
            if (ppEnum) {
                *ppEnum = pEnum;
            }
            return ERESULT_OUT_OF_MEMORY;
        }
        
        for (i=0; i<this->size; ++i) {
            if (this->ppArray[i]) {
                enum_Append(pEnum, (void *)this->ppArray[i], NULL);
            }
        }
        
        // Return to caller.
        if (ppEnum) {
            *ppEnum = pEnum;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------
    
    void *          ptrArray_GetData(
        PTRARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    )
    {
        void        *pObj = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (index && (index <= this->size))
            ;
        else {
            return NULL;
        }
#endif
        
        if (this->ppArray) {
            pObj = this->ppArray[index-1];
        }
        
        return pObj;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PTRARRAY_DATA *   ptrArray_Init(
        PTRARRAY_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_PTRARRAY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ptrArray_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->ppArray);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         ptrArray_InsertData(
        PTRARRAY_DATA	*this,
        uint32_t        index,
        void            *pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (index <= this->size) {
        }
        else {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        
        ++this->size;
        eRc = ptrArray_ExpandArray(this, this->size);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        if (index < this->size) {
            // Shift array starting at the current index.
            memmove(
                    &this->ppArray[index+1],
                    &this->ppArray[index],
                    ((this->size - index) * sizeof(void *))
            );
        }
        this->ppArray[index] = (uint8_t *)pObject;
        
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       S o r t
    //---------------------------------------------------------------
    
    ERESULT         ptrArray_Sort(
        PTRARRAY_DATA	*this,
        PTR_COMPARE     pCompare
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        j;
        void            *pSave;
        
        /*  Insertion Sort from Wikipedia
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
        if( !ptrArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->size < 2) {
            return ERESULT_SUCCESS;
        }
        
        for (i=1; i<this->size; ++i) {
            j = i;
            while (j > 0) {
                eRc = (*pCompare)(this->ppArray[j-1], this->ppArray[j]);
                if (ERESULT_SUCCESS_GREATER_THAN == eRc) {
                    pSave = this->ppArray[j-1];
                    this->ppArray[j-1] = this->ppArray[j];
                    this->ppArray[j] = pSave;
                    --j;
                }
                else
                    break;
            }
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     ptrArray_ToDebugString(
        PTRARRAY_DATA   *this,
        int             indent
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }

        AStr_AppendPrint(
                     pStr,
                     "{%p(%s) size=%d max=%d\n",
                     this,
                     pInfo->pClassName,
                     this->size,
                     this->max
        );
        
        if (this->ppArray) {
            for (i=0; i<this->size; ++i) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, (indent + 4), ' ');
                }
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "%8d - %p\n",
                                         (i + 1),
                                         this->ppArray[i]
                                         );
            }
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                                 pStr,
                                 "%p(%s)}\n",
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
    bool            ptrArray_Validate(
        PTRARRAY_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_PTRARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(PTRARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                          V i s i t
    //---------------------------------------------------------------
    
    ERESULT 		ptrArray_Visit(
        PTRARRAY_DATA   *cbp,
        P_VOIDEXIT2_BE  pVisitor,
        void            *pObj       // 1st parm to pVisitor
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ptrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<cbp->max; ++i) {
            eRc = pVisitor(pObj,cbp->ppArray[i]);
            if (ERESULT_HAS_FAILED(eRc)) {
                return eRc;
            }
        }
        
        return eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


