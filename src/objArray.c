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
#include "objArray_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         objArray_ExpandArray(
        OBJARRAY_DATA   *this,
        uint32_t        num
    )
    {
        void            *pWork;
        uint32_t        oldMax;
        uint32_t        cbSize;
        uint16_t        elemSize = sizeof(OBJ_DATA *);
        
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
        this->max = oldMax << 1;
        while (num > this->max) {
            this->max = this->max << 1;
        }
        cbSize = this->max * elemSize;
        pWork = (void *)mem_Malloc( cbSize );
        if( NULL == pWork ) {
            this->max = oldMax;
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Copy the old entries into the new array.
        if( this->ppArray == NULL )
            ;
        else {
            memmove( pWork, this->ppArray, (oldMax * elemSize) );
            mem_Free( this->ppArray );
            // cbp->pArray = NULL;
        }
        this->ppArray = pWork;
        memset( &this->ppArray[oldMax], 0, ((this->max - oldMax) * elemSize) );
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    



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
        return this->size;
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
        ++this->size;
        eRc = objArray_ExpandArray(this, this->size);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        this->ppArray[this->size-1] = (OBJ_DATA *)pObject;
        if (pIndex) {
            *pIndex = this->size;
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
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        uint32_t        i;
        OBJ_DATA        *pItem;
        OBJ_IUNKNOWN    *pVtbl;
        
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
        OBJ_DATA        *pItem;
        OBJ_IUNKNOWN    *pVtbl;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objArray_Alloc();
        pOther = objArray_Init(pOther);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        eRc = objArray_ExpandArray(pOther, this->max);
        if (ERESULT_HAS_FAILED(eRc)) {
            obj_Release(pOther);
            return OBJ_NIL;
        }
        
        pOther->size = this->size;
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
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return( pOther );
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

        for (i=0; i<this->max; ++i) {
            if (this->ppArray[i] && obj_getRetainCount(this->ppArray[i])) {
                obj_Release(this->ppArray[i]);
                this->ppArray[i] = OBJ_NIL;
            }
        }
        
        mem_Free(this->ppArray);
        this->ppArray = NULL;
        this->max = 0;
        this->size = 0;
        
        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        //this->pOBJ->iVtbl.pDealloc( this );  // Needed for Inheritance
        this = OBJ_NIL;

        // Return to caller.
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
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (this->size)
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
        if (index && (index <= this->size))
            ;
        else {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        if (this->ppArray) {
            pObj = this->ppArray[index-1];
            if (index < this->size) {
                for (i=(index-1); i<this->size; ++i) {
                    this->ppArray[i] = this->ppArray[i+1];
                }
            }
            --this->size;
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    OBJ_ID          objArray_DeleteFirst(
        OBJARRAY_DATA	*this
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (this->size)
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        if (this->ppArray) {
            pObj = this->ppArray[0];
            for (i=0; i<this->size; ++i) {
                this->ppArray[i] = this->ppArray[i+1];
            }
            --this->size;
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    OBJ_ID          objArray_DeleteLast(
        OBJARRAY_DATA	*this
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (this->size)
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        if (this->ppArray) {
            --this->size;
            pObj = this->ppArray[this->size];
            this->ppArray[this->size] = OBJ_NIL;
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    
    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------
    
    OBJ_ID          objArray_Get(
        OBJARRAY_DATA	*this,
        uint32_t        index       // Relative to 1
    )
    {
        OBJ_ID          pObj = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (index && (index <= this->size))
            ;
        else {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return OBJ_NIL;
        }
#endif
        
        if (this->ppArray) {
            pObj = this->ppArray[index-1];
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    OBJ_ID          objArray_GetFirst(
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
#endif
        
        if (this->ppArray) {
            if (this->size) {
                pObj = this->ppArray[0];
            }
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    OBJ_ID          objArray_GetLast(
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
#endif
        
        if (this->ppArray) {
            if (this->size) {
                pObj = this->ppArray[this->size-1];
            }
        }
        
        this->eRc = ERESULT_SUCCESS;
        return pObj;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJARRAY_DATA *   objArray_Init(
        OBJARRAY_DATA       *this
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
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

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
        if (index <= this->size) {
        }
        else {
            return ERESULT_OUT_OF_RANGE;
        }
#endif
        
        obj_Retain(pObject);
        ++this->size;
        eRc = objArray_ExpandArray(this, this->size);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        if (index < this->size) {
            memmove(
                    &this->ppArray[index+1],
                    &this->ppArray[index],
                    ((this->size - index) * sizeof(OBJ_ID))
            );
        }
        this->ppArray[index] = (OBJ_DATA *)pObject;
        
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
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objArray_Validate( this ) ) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_OBJECT;
            return this->eRc;
        }
        if (index)
            ;
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        obj_Retain(pObj);
        if (index > this->max) {
            eRc = objArray_ExpandArray(this, index);
            if (ERESULT_HAS_FAILED(eRc)) {
                DEBUG_BREAK();
                this->eRc = eRc;
                return eRc;
            }
        }
        this->size = (index > this->size) ? index : this->size;

        if (this->ppArray[index - 1]) {
            obj_Release(this->ppArray[index - 1]);
            //this->ppArray[index - 1] = OBJ_NIL;
        }
        this->ppArray[index - 1] = (OBJ_DATA *)pObj;
        
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
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
        uint32_t        i;
        uint32_t        j;
        OBJ_ID          pSave;
        
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
        
        if (this->size < 2) {
            this->eRc = ERESULT_SUCCESS;
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
        OBJ_IUNKNOWN    *pEntry;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(objArray) size=%d\n",
                     this,
                     objArray_getSize(this)
            );
        AStr_AppendA(pStr, str);

        if (this->ppArray) {
            for (i=0; i<this->max; ++i) {
                AStr_AppendCharRepeatW(pStr, indent+3, ' ');
                str[0] = '\0';
                j = snprintf(str, sizeof(str), "%d\n", i+1);
                AStr_AppendA(pStr, str);
                if (this->ppArray[i]) {
                    pEntry = (OBJ_IUNKNOWN *)this->ppArray[i];
                    if (((OBJ_DATA *)(pEntry))->pVtbl->pToDebugString) {
                        pWrkStr =   ((OBJ_DATA *)(pEntry))->pVtbl->pToDebugString(
                                                        pEntry,
                                                        indent+6
                                    );
                        AStr_Append(pStr, pWrkStr);
                        obj_Release(pWrkStr);
                    }
                }
                else {
                    AStr_AppendCharRepeatW(pStr, indent+6, ' ');
                    AStr_AppendA(pStr, "NULL\n");
                }
            }
        }
        
        j = snprintf( str, sizeof(str), " %p(objArray)}\n", this );
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
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_OBJARRAY) )
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


