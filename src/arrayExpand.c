// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   arrayExpand.c
 *	Generated 10/07/2016 10:36:42
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
#include "arrayExpand_internal.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT             arrayExpand_Expand(
        ARRAYEXPAND_DATA  *this,
        uint32_t        min
    )
    {
        void            *pWork;
        uint32_t        oldMax;
        uint32_t        cbSize;
        
        // Do initialization.
        if( this == NULL )
            return ERESULT_INVALID_OBJECT;
        
        // Expand the Array.
        oldMax = this->max;
        if (0 == oldMax) {
            oldMax = 1;
        }
        if (min && (min > oldMax)) {
            this->max = min;
        }
        else {
            this->max = oldMax << 1;
        }
        cbSize = this->max * this->elemSize;
        pWork = (void *)mem_Malloc( cbSize );
        if( NULL == pWork ) {
            this->max = oldMax;
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Copy the old entries into the new array.
        if( this->pArray == NULL )
            ;
        else {
            memmove( pWork, this->pArray, (oldMax * this->elemSize) );
            mem_Free( this->pArray );
            // cbp->pArray = NULL;
        }
        this->pArray = pWork;
        memset(&this->pArray[oldMax], 0, ((this->max - oldMax) * this->elemSize));
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    static
    void                arrayExpand_FreeArray(
        ARRAYEXPAND_DATA  *this
    )
    {
        if (this->pArray) {
            mem_Free( this->pArray );
            this->pArray = NULL;
            this->max = 0;
            this->size = 0;
        }
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ARRAYEXPAND_DATA * arrayExpand_Alloc(
    )
    {
        ARRAYEXPAND_DATA *this;
        uint32_t        cbSize = sizeof(ARRAYEXPAND_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ARRAYEXPAND_DATA * arrayExpand_New(
        uint16_t        elemSize
    )
    {
        ARRAYEXPAND_DATA *this;
        
        this = arrayExpand_Alloc( );
        if (this) {
            this = arrayExpand_Init(this, elemSize);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    void *          arrayExpand_getData(
        ARRAYEXPAND_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return this->pArray;
    }
    
    
    uint32_t        arrayExpand_getElemSize(
        ARRAYEXPAND_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return this->elemSize;
    }
    
    
    
    ERESULT         arrayExpand_getLastError(
        ARRAYEXPAND_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        return this->eRc;
    }



    uint32_t        arrayExpand_getSize(
        ARRAYEXPAND_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code:
        ERESULT eRc = arrayExpand__Assign(this,pOther);
     @endcode:
     @param:    this    ARRAYEXPAND object pointer
     @param:    pOther  a pointer to another ARRAYEXPAND object
     @return:   If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         arrayExpand_Assign(
        ARRAYEXPAND_DATA    *this,
        ARRAYEXPAND_DATA    *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !arrayExpand_Validate(pOther) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif

        // Release objects and areas in other object.
        arrayExpand_FreeArray(this);

        pOther->elemSize = this->elemSize;
        pOther->pArray = mem_Malloc(this->max * this->elemSize);
        if (pOther->pArray == NULL) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return this->eRc;
        }
        memmove(pOther->pArray, this->pArray, (this->max * this->elemSize));
        pOther->max = this->max;
        pOther->size = this->size;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    ERESULT         arrayExpand_AssignData(
        ARRAYEXPAND_DATA *this,
        uint16_t        elemSize,
        uint32_t        size,
        const
        void            *pBuffer
    )
    {
        void            *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if (elemSize == 0) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
        if (size && pBuffer) {
        }
        else {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
#endif
        
        arrayExpand_FreeArray(this);
        this->elemSize = elemSize;
        
        pData = arrayExpand_Elem(this, size);
        if (pData) {
            memmove(pData, pBuffer, (size * elemSize));
            this->eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code:
        arrayExpand      *pCopy = arrayExpand_Copy(this);
     @endcode:
     @param:    this    ARRAYEXPAND object pointer
     @return:   If successful, a ARRAYEXPAND object which must be released,
                otherwise OBJ_NIL.
     @warning: Remember to release the returned the ARRAYEXPAND object.
     */
    ARRAYEXPAND_DATA *     arrayExpand_Copy(
        ARRAYEXPAND_DATA       *this
    )
    {
        ARRAYEXPAND_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = arrayExpand_New(this->elemSize);
        if (pOther) {
            eRc = arrayExpand_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            arrayExpand_Dealloc(
        OBJ_ID          objId
    )
    {
        ARRAYEXPAND_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ARRAYEXPAND_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        arrayExpand_FreeArray(this);

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          E l e m
    //---------------------------------------------------------------

    void *          arrayExpand_Elem(
        ARRAYEXPAND_DATA *this,
        uint32_t        index
    )
    {
        ERESULT         eRc;
        uint8_t         *pData = NULL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (index == 0) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return NULL;
        }
    #endif

        while (index > this->max) {
            eRc = arrayExpand_Expand(this, 0);
            if (ERESULT_HAS_FAILED(eRc)) {
                return NULL;
            }
        }
        
        switch (this->elemSize) {
                
            case 1:
                pData = this->pArray + (index - 1);
                break;
                
            case 2:
                pData = this->pArray + ((index - 1) << 1);
                break;
                
            case 4:
                pData = this->pArray + ((index - 1) << 2);
                break;
                
            case 8:
                pData = this->pArray + ((index - 1) << 3);
                break;
                
            case 16:
                pData = this->pArray + ((index - 1) << 4);
                break;
                
            case 32:
                pData = this->pArray + ((index - 1) << 5);
                break;
                
            case 64:
                pData = this->pArray + ((index - 1) << 6);
                break;
                
            case 128:
                pData = this->pArray + ((index - 1) << 7);
                break;
                
            case 256:
                pData = this->pArray + ((index - 1) << 8);
                break;
                
            case 512:
                pData = this->pArray + ((index - 1) << 9);
                break;
                
            case 1024:
                pData = this->pArray + ((index - 1) << 10);
                break;
                
            default:
                pData = this->pArray + ((index - 1) * this->elemSize);
                break;
        }
        if (index > this->size) {
            this->size = index;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pData;
    }



    //---------------------------------------------------------------
    //                      E x p a n d  T o
    //---------------------------------------------------------------

    ERESULT         arrayExpand_ExpandTo(
        ARRAYEXPAND_DATA *this,
        uint32_t        size
    )
    {
        ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if (size <= this->max) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return this->eRc;
        }
    #endif
        
        eRc = arrayExpand_Expand(this, size);

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }



    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    ERESULT         arrayExpand_Get(
        ARRAYEXPAND_DATA *this,
        uint32_t        index,              // (relative to 1)
        uint32_t        cBuffer,
        void            *pBuffer
    )
    {
        uint32_t        size;
        void            *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        if (cBuffer == 0) {
            cBuffer = this->elemSize;
        }
        
        pData = arrayExpand_Elem(this, index);
        if (pData) {
            size = this->elemSize;
            if (cBuffer < size) {
                size = cBuffer;
            }
            memmove(pBuffer, pData, size);
            this->eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ARRAYEXPAND_DATA *   arrayExpand_Init(
        ARRAYEXPAND_DATA *this,
        uint16_t    elemSize        // Element Size in bytes
    )
    {
        uint32_t        cbSize = sizeof(ARRAYEXPAND_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ARRAYEXPAND);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_ARRAYEXPAND);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&arrayExpand_Vtbl);
        
        this->elemSize = elemSize;

    #ifdef NDEBUG
    #else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pArray);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         arrayExpand_Set(
        ARRAYEXPAND_DATA *this,
        uint32_t        index,              // (relative to 1)
        uint32_t        cBuffer,
        const
        void            *pBuffer
    )
    {
        uint32_t        size;
        void            *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !arrayExpand_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        if (cBuffer == 0) {
            cBuffer = this->elemSize;
        }
        
        pData = arrayExpand_Elem(this, index);
        if (pData) {
            size = this->elemSize;
            if (cBuffer < size) {
                size = cBuffer;
            }
            memmove(pData, pBuffer, size);
            this->eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code:
        ASTR_DATA      *pDesc = arrayExpand_ToDebugString(this,4);
     @endcode:
     @param:    this    ARRAYEXPAND object pointer
     @param:    indent  number of characters to indent every line of output, can be 0
     @return:   If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning: Remember to release the returned AStr object.
     */
    ASTR_DATA *     arrayExpand_ToDebugString(
        ARRAYEXPAND_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
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
                     "{%p(arrayExpand) size=%d\n",
                     this,
                     arrayExpand_getSize(this)
            );
        AStr_AppendA(pStr, str);

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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(arrayExpand)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            arrayExpand_Validate(
        ARRAYEXPAND_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_ARRAYEXPAND) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(ARRAYEXPAND_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


