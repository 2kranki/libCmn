// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   pwr2Array.c
 *	Generated 08/25/2015 20:42:16
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
#include        "pwr2Array_internal.h"
#include        <stdio.h>
#include        "hex.h"



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

    PWR2ARRAY_DATA * pwr2Array_Alloc(
    )
    {
        PWR2ARRAY_DATA  *this;
        uint32_t        cbSize = sizeof(PWR2ARRAY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PWR2ARRAY_DATA * pwr2Array_New(
        uint16_t        powerOf2    // Element Size as a Power of 2
    )
    {
        PWR2ARRAY_DATA       *this;
        
        this = pwr2Array_Alloc( );
        if (this) {
            this = pwr2Array_Init( this, powerOf2 );
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    void *          pwr2Array_getData(
        PWR2ARRAY_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->pArray;
    }

    
    
    bool            pwr2Array_getDontZero(
        PWR2ARRAY_DATA   *this
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (this->dontZero) {
            return true;
        }
        return false;
    }
    
    
    bool            pwr2Array_setDontZero(
        PWR2ARRAY_DATA  *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (value) {
            this->dontZero = 1;
        }
        else
            this->dontZero = 0;
        
        return false;
    }
    
    
    
    ERESULT         pwr2Array_getLastError(
        PWR2ARRAY_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->eRc;
    }
    
    
    
    uint32_t        pwr2Array_getMax(
        PWR2ARRAY_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->max;
    }
    
    
    uint32_t        pwr2Array_getSize(
        PWR2ARRAY_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->size;
    }


    bool            pwr2Array_setSize(
        PWR2ARRAY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (value <= this->max) {
            this->size = value;
            return true;
        }
        
        return false;
    }


    
    uint32_t        pwr2Array_getSizeInBytes(
        PWR2ARRAY_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return (this->size  << this->powerOf2);
    }
    
    

    
    //===============================================================
    //                          M e t h o d s
    //===============================================================


    bool            pwr2Array_AdjustSize(
        PWR2ARRAY_DATA  *this,
        int32_t         value
    )
    {
        uint32_t        newSize;
        ERESULT         eRc;
        
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        newSize = this->size + value;
        if (value <= this->max) {
            this->size = newSize;
            return true;
        }
        else {
            if (value > 0) {
                while (value > this->max) {
                    eRc = pwr2Array_Expand(this);
                    if (ERESULT_HAS_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
        }
        
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                         A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         pwr2Array_Append(
        PWR2ARRAY_DATA  *this,
        PWR2ARRAY_DATA  *other
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !pwr2Array_Validate(other) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (this->powerOf2 == other->powerOf2) {
        }
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = ERESULT_SUCCESS;
        if (other->size) {
            eRc = pwr2Array_AppendData(this, other->size, other->pArray);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         pwr2Array_AppendData(
        PWR2ARRAY_DATA  *cbp,
        uint32_t        numElems,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
        offset = cbp->size + 1;
        
        // Check parameters.
        if (numElems) {
            if ((numElems + cbp->size) >= UINT32_MAX) {
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pData) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        eRc = pwr2Array_InsertData(cbp, offset, numElems, pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         pwr2Array_AppendSpacing(
        PWR2ARRAY_DATA  *this,
        uint32_t        numElems
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (numElems) {
            if ((numElems + this->size) >= UINT32_MAX) {
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        offset = this->size + 1;

        eRc = pwr2Array_InsertSpacing(this, offset, numElems);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                         A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         pwr2Array_Assign(
        PWR2ARRAY_DATA	*this,
        PWR2ARRAY_DATA	*pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pOther->powerOf2 = this->powerOf2;
        pOther->dontZero = this->dontZero;
        
        if (pOther->pArray) {
            mem_Free(pOther->pArray);
            pOther->pArray = NULL;
            pOther->max = 0;
            pOther->size = 0;
        }
        
        while (pOther->max < this->size) {
            eRc = pwr2Array_Expand(pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                return eRc;
            }
        }
        
        memmove(
                pOther->pArray,
                this->pArray,
                (this->size << this->powerOf2)
        );
        pOther->size = this->size;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                         C o p y
    //---------------------------------------------------------------
    
    PWR2ARRAY_DATA *  pwr2Array_Copy(
        PWR2ARRAY_DATA	*this
    )
    {
        PWR2ARRAY_DATA	*pOther;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = pwr2Array_New(this->powerOf2);
        if (pOther) {
            eRc = pwr2Array_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            pwr2Array_Dealloc(
        OBJ_ID          objId
    )
    {
        PWR2ARRAY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pArray) {
            mem_Free(this->pArray);
            this->pArray = OBJ_NIL;
            this->size = 0;
            this->max = 0;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         pwr2Array_Delete(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if( (0 ==  offset) || (offset > this->size) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (numElems) {
            if ((numElems + offset - 1) > this->size) {
                return ERESULT_DATA_OUT_OF_RANGE;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Move elements past deletion point if necessary.
        if ((offset + numElems - 1) < this->size) {
            memmove(
                    pwr2Array_Ptr(this, offset),
                    pwr2Array_Ptr(this, (offset + numElems)),
                    ((this->size - (numElems + offset - 1)) << this->powerOf2)
            );
        }
        this->size -= numElems;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      E x p a n d
    //---------------------------------------------------------------

    ERESULT             pwr2Array_Expand(
        PWR2ARRAY_DATA		*this
    )
    {
        void                *pWork;
        uint32_t            oldMax;
        uint64_t            newMax;
        uint64_t            cbSize;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Expand the Array.
        oldMax = this->max;
        if (0 == oldMax) {
            newMax = 2;
        }
        else {
            newMax = oldMax * 2;
        }
        cbSize = newMax << this->powerOf2;
        if (cbSize == 0) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        if (cbSize >= UINT32_MAX) {
            return ERESULT_DATA_TOO_BIG;
        }
        pWork = (void *)mem_Malloc( cbSize );
        if( NULL == pWork ) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Copy the old entries into the new array.
        if( this->pArray == NULL )
            ;
        else {
            memmove( pWork, this->pArray, (oldMax << this->powerOf2) );
        }
        
        // Zero the new entries.
        if (0 == (this->dontZero)) {
            memset(
                   (this->pArray + (oldMax << this->powerOf2)),
                   0,
                   ((this->max - oldMax) << this->powerOf2)
            );
        }
        
        this->max = (uint32_t)newMax;
        mem_Free(this->pArray);
        this->pArray = pWork;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      E l e m  S i z e
    //---------------------------------------------------------------

    uint32_t        pwr2Array_ElemSize(
        PWR2ARRAY_DATA	*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        // Return to caller.
        return (1 << this->powerOf2);
    }



    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    ERESULT         pwr2Array_Get(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pData
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        // Check parameters.
        if( (offset > this->size) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (numElems) {
            if ((numElems + offset - 1) > this->size) {
                return ERESULT_DATA_OUT_OF_RANGE;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pData) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Copy in given elements.
        memmove(
                pData,
                pwr2Array_Ptr(this, offset),
                (numElems << this->powerOf2)
        );
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PWR2ARRAY_DATA * pwr2Array_Init(
        PWR2ARRAY_DATA  *this,
        uint16_t        powerOf2    // Element Size as a Power of 2
    //                              // 0 == 1 byte, 1 == 2, 2 == 4, ...
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if (powerOf2 < 32)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_PWR2ARRAY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&pwr2Array_Vtbl);
        
        this->powerOf2 = powerOf2;

    #ifdef NDEBUG
    #else
        if( !pwr2Array_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         pwr2Array_InsertData(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        // Check parameters.
        if (0 == offset) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( ((offset-1) > this->size) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (numElems) {
            if ((numElems + this->size) >= UINT32_MAX) {
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pData) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Make room in array for data in the array if needed.
        while ((this->size + numElems) > this->max) {
            eRc = pwr2Array_Expand(this);
            if (ERESULT_HAS_FAILED(eRc)) {
                return eRc;
            }
        }
        
        // Move elements above insertion point if necessary.
        if (offset <= this->size) {
            memmove(
                    pwr2Array_Ptr(this, (offset + numElems)),
                    pwr2Array_Ptr(this, offset),
                    ((this->size - offset + 1) << this->powerOf2)
            );
        }
        
        // Copy in given elements.
        memmove(
                pwr2Array_Ptr(this, offset),
                pData,
                (numElems << this->powerOf2)
        );
        this->size += numElems;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         pwr2Array_InsertSpacing(
        PWR2ARRAY_DATA  *this,
        uint32_t        offset,             // in elements (relative to 1)
        uint32_t        numElems
    )
    {
        ERESULT         eRc = ERESULT_INSUFFICIENT_MEMORY;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        // Check parameters.
        if (0 == offset) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( ((offset-1) > this->size) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (numElems) {
            if ((numElems + this->size) >= UINT32_MAX) {
                return ERESULT_DATA_TOO_BIG;
            }
        }
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        // Make room in array for data in the array if needed.
        while ((this->size + numElems) > this->max) {
            eRc = pwr2Array_Expand(this);
            if (ERESULT_HAS_FAILED(eRc)) {
                return eRc;
            }
        }
        
        // Move elements above insertion point if necessary.
        if (offset <= this->size) {
            memmove(
                    pwr2Array_Ptr(this, (offset + numElems)),
                    pwr2Array_Ptr(this, offset),
                    ((this->size - offset + 1) << this->powerOf2)
            );
        }
        this->size += numElems;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                             P t r
    //---------------------------------------------------------------
    
    void *              pwr2Array_Ptr(
        PWR2ARRAY_DATA      *this,
        uint32_t            elem        // Element Number (relative to 1)
    )
    {
        ERESULT             eRc;
        uint8_t             *pData = NULL;
        
        if (0 == elem) {
            return NULL;
        }
        
        while (elem > this->max) {
            eRc = pwr2Array_Expand(this);
            if (ERESULT_HAS_FAILED(eRc)) {
                return NULL;
            }
        }
        
        pData = this->pArray + ((elem - 1) << this->powerOf2);
        
        return pData;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          pwr2Array_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PWR2ARRAY_DATA  *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
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
                            return pwr2Array_ToDebugString;
                        }
                        if (str_Compare("Truncate", (char *)pStr) == 0) {
                            return pwr2Array_Truncate;
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     pwr2Array_ToDebugString(
        PWR2ARRAY_DATA  *this,
        int             indent
    )
    {
        char            strBuf[256];
        char            *pMem;
        uint32_t        j;
        ASTR_DATA       *pStr;
        //SZSTR_DATA      *pWrkStr;
        uint32_t        size;
        HEX_DATA        *pHex = OBJ_NIL;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        pHex = hex_New();
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(
                     strBuf,
                     sizeof(strBuf),
                     "{%p(pwr2Array) elemSize= %d  length=%d\n",
                     this,
                     (1 << this->powerOf2),
                     pwr2Array_getSize(this)
            );
        AStr_AppendA(pStr, strBuf);

        if (this->pArray) {
            pMem = (char *)this->pArray;
            size = ((1 << this->powerOf2) * pwr2Array_getSize(this));
            while (size) {
                if (indent) {
                    AStr_AppendCharRepeatW32(pStr, indent+3, ' ');
                }
                j = hex_put16BytesObj_64(
                        pHex,
                        (uint64_t)pMem,
                        size,
                        (void *)pMem,
                        pStr,
                        (void *)AStr_AppendCharA
                    );
                AStr_AppendA(pStr, "\n");
                if (size > 16) {
                    size -= 16;
                    pMem += 16;
                }
                else
                    break;
            }
        }
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf( strBuf, sizeof(strBuf), "  %p(pwr2Array)}\n", this );
        AStr_AppendA(pStr, strBuf);
        
        obj_Release(pHex);
        pHex = OBJ_NIL;
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T r u n c a t e
    //---------------------------------------------------------------
    
    ERESULT         pwr2Array_Truncate(
        PWR2ARRAY_DATA	*this,
        uint32_t        len
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pwr2Array_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        if (len > this->size) {
            return ERESULT_INVALID_PARAMETER;
        }
        
        this->size = len;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            pwr2Array_Validate(
        PWR2ARRAY_DATA  *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_PWR2ARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(PWR2ARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


