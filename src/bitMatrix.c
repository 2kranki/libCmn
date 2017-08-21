// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   bitMatrix.c
 *	Generated 07/21/2015 00:03:29
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
#include "bitMatrix_internal.h"
#include <stdio.h>



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

    BITMATRIX_DATA * bitMatrix_Alloc(
        uint16_t        x,
        uint16_t        y
    )
    {
        BITMATRIX_DATA  *cbp = OBJ_NIL;
        uint32_t        cbSize = sizeof(BITMATRIX_DATA);
        uint32_t        sizeInBits;
        uint32_t        sizeInBytes;
        uint16_t        xNew;
        uint16_t        yNew;
        
        // Do initialization.
        xNew = ROUNDUP32(x);
        if (xNew < x) {
            return OBJ_NIL;
        }
        yNew = ROUNDUP32(y);
        if (xNew < x) {
            return OBJ_NIL;
        }
        sizeInBits = xNew * yNew;
        if (0 == sizeInBits) {
            return OBJ_NIL;
        }
        
        sizeInBytes = sizeInBits / 8;
        cbSize += sizeInBytes;
        cbp = obj_Alloc( cbSize );
        if (cbp) {
            obj_setMisc1(cbp, x);
            obj_setMisc2(cbp, y);
        }
        
        // Return to caller.
        return cbp;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         bitMatrix_getLastError(
        BITMATRIX_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        return this->eRc;
    }
    
    
    bool            bitMatrix_setLastError(
        BITMATRIX_DATA  *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    uint16_t        bitMatrix_getXMax(
        BITMATRIX_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        return cbp->xMax;
    }

    uint16_t        bitMatrix_getYMax(
        BITMATRIX_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return cbp->yMax;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Assign(
        BITMATRIX_DATA	*cbp,
        BITMATRIX_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitMatrix_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->cElems == pOther->cElems )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        cbp->xMax = pOther->xMax;
        cbp->yMax = pOther->yMax;
        
        for (i=0; i<cbp->cElems; ++i) {
            j = cbp->elems[i];
            cbp->elems[i] = pOther->elems[i];
            if (j != cbp->elems[i]) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    BITMATRIX_DATA *   bitMatrix_Copy(
        BITMATRIX_DATA		*cbp
    )
    {
        BITMATRIX_DATA  *pOther;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = bitMatrix_Alloc(cbp->xMax,cbp->yMax);
        pOther = bitMatrix_Init(pOther);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        pOther->xMax = cbp->xMax;
        pOther->yMax = cbp->yMax;
        pOther->cElems = cbp->cElems;
        for (i=0; i<cbp->cElems; ++i) {
            pOther->elems[i] = cbp->elems[i];
        }
        
        // Return to caller.
        return( pOther );
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            bitMatrix_Dealloc(
        OBJ_ID          objId
    )
    {
        BITMATRIX_DATA  *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            bitMatrix_Disable(
        BITMATRIX_DATA	*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                         E m p t y
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Empty(
        BITMATRIX_DATA	*cbp
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            cbp->elems[i] = 0;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Get(
        BITMATRIX_DATA	*cbp,
        uint16_t        x,
        uint16_t        y
    )
    {
        uint32_t        i;
        uint32_t        j;
        ERESULT         eRc = ERESULT_SUCCESS_FALSE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((x > 0) && (x <= cbp->xMax))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((y > 0) && (y <= cbp->yMax))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = ((x- 1) * (ROUNDUP32(cbp->xMax) >> 5)) + ((y - 1) >> 5);
        j = 31 - ((y - 1) & 0x1F);
        
        //uint32_t xx = cbp->elems[i];
        if ( cbp->elems[i] & (1 << j) ) {
            eRc = ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      G e t  C o l u m n
    //---------------------------------------------------------------
    
    BITSET_DATA *   bitMatrix_GetColumn(
        BITMATRIX_DATA	*cbp,
        uint16_t        x,
        uint16_t        y,
        uint16_t        len
    )
    {
        BITSET_DATA     *pWork = OBJ_NIL;
        uint16_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((x > 0) && (x <= cbp->xMax))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((y > 0) && (y <= cbp->yMax))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((x + len - 1) <= cbp->xMax)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pWork = bitSet_Alloc(len);
        pWork = bitSet_Init(pWork);
        if (OBJ_NIL == pWork) {
            return pWork;
        }
        
        for (i=0; i<len; ++i) {
            if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(cbp, x+i, y)) {
                bitSet_Set(pWork, i+1, true);
            }
        }
        
        // Return to caller.
        return pWork;
    }
    
    
    
    //---------------------------------------------------------------
    //                      G e t  R o w
    //---------------------------------------------------------------
    
    BITSET_DATA *   bitMatrix_GetRow(
        BITMATRIX_DATA	*cbp,
        uint16_t        x,
        uint16_t        y,
        uint16_t        len
    )
    {
        BITSET_DATA     *pWork = OBJ_NIL;
        uint16_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
        if ((x > 0) && (x <= cbp->xMax))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((y > 0) && (y <= cbp->yMax))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((y + len - 1) <= cbp->yMax)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pWork = bitSet_Alloc(len);
        pWork = bitSet_Init(pWork);
        if (OBJ_NIL == pWork) {
            return pWork;
        }
        
        for (i=0; i<len; ++i) {
            if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(cbp, x, y+i)) {
                bitSet_Set(pWork, i+1, true);
            }
        }
        
        // Return to caller.
        return pWork;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BITMATRIX_DATA * bitMatrix_Init(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        sizeInBits;
        uint32_t        sizeInWords;
        uint16_t        xNew;
        uint16_t        yNew;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_BITMATRIX );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&bitMatrix_Vtbl);
        
        this->xMax = obj_getMisc1(this);
        this->yMax = obj_getMisc2(this);
        xNew = ROUNDUP32(this->xMax);
        yNew = ROUNDUP32(this->yMax);
        sizeInBits = xNew * yNew;
        sizeInWords = sizeInBits / 32;
        this->cElems = sizeInWords;

    #ifdef NDEBUG
    #else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->elems);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I n t e r s e c t
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Intersect(
        BITMATRIX_DATA	*cbp,
        BITMATRIX_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitMatrix_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->cElems == pOther->cElems )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            j = cbp->elems[i];
            cbp->elems[i] &= pOther->elems[i];
            if (j != cbp->elems[i]) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                         I n v e r t
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Invert(
        BITMATRIX_DATA	*cbp
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            cbp->elems[i] = ~cbp->elems[i];
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E m p t y
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_IsEmpty(
        BITMATRIX_DATA	*cbp
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            if (cbp->elems[i]) {
                return ERESULT_FAILURE_FALSE;
            }
        }
        
        
        // Return to caller.
        return ERESULT_SUCCESS_TRUE;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o d u c t
    //---------------------------------------------------------------
    
    BITMATRIX_DATA *   bitMatrix_Product(
        BITMATRIX_DATA		*cbp,
        BITMATRIX_DATA		*pOther
    )
    {
        BITMATRIX_DATA  *pProduct;
        uint16_t        i;
        uint16_t        j;
        uint16_t        k;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (cbp->xMax == cbp->yMax)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (pOther->xMax == pOther->yMax)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (cbp->yMax == pOther->yMax)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pProduct = bitMatrix_Alloc(cbp->xMax,cbp->yMax);
        pProduct = bitMatrix_Init(pProduct);
        if (OBJ_NIL == pProduct) {
            return OBJ_NIL;
        }
        
        for (j=1; j<=cbp->xMax; ++j) {
            for (i=1; i<=cbp->xMax; ++i) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(cbp, i, j)) {
                    for (k=1; k<=cbp->xMax; ++k) {
                        if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(pOther, j, k)) {
                            bitMatrix_Set(pProduct, i, k, true);
                        }
                    }
                };
            }
        }
        
        // Return to caller.
        return( pProduct );
    }
    
    
    
    //---------------------------------------------------------------
    //    R e f l e c t i v e  T r a n s i t i v e  C l o s u r e
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_ReflectiveTransitiveClosure(
        BITMATRIX_DATA	*this
    )
    {
        uint16_t        j;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->xMax == this->yMax)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        for (j=1; j<=this->xMax; ++j) {
            bitMatrix_Set(this, j, j, true);
        }
        eRc = bitMatrix_TransitiveClosure(this);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Set(
        BITMATRIX_DATA	*this,
        uint16_t        x,
        uint16_t        y,
        bool            value
    )
    {
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((x > 0) && (x <= this->xMax))
            ;
        else {
            DEBUG_BREAK();
            bitMatrix_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if ((y > 0) && (y <= this->yMax))
            ;
        else {
            DEBUG_BREAK();
            bitMatrix_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = ((x- 1) * (ROUNDUP32(this->xMax) >> 5)) + ((y - 1) >> 5);
        j = 31 - ((y - 1) & 0x1F);
        
        if (value ) {
            this->elems[i] |= (1 << j);
        }
        else {
            this->elems[i] &= ~(1 << j);
        }
        
        // Return to caller.
        bitMatrix_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     bitMatrix_ToDebugString(
        BITMATRIX_DATA	*this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        int             x;
        int             y;
        ASTR_DATA       *pStr;
        
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
                     "{%p(bitMatrix) xMax=%d yMax=%d size=%d\n",
                     this,
                     this->xMax,
                     this->yMax,
                     this->cElems
                     );
        AStr_AppendA(pStr, str);
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent+5, ' ');
        }
        AStr_AppendA(pStr, " ");
        for (x=0; x<(this->xMax/10); ++x) {
            AStr_AppendA(pStr, "1234567890");
        }
        AStr_AppendA(pStr, "\n");
        for (x=1; x<=this->xMax; ++x) {
            if (indent) {
                AStr_AppendCharRepeatW(pStr, indent+3, ' ');
            }
            j = snprintf( str, sizeof(str), "%3d |", x );
            AStr_AppendA(pStr, str);
            for (y=1; y<=this->yMax; ++y) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, x, y)) {
                    AStr_AppendA(pStr, "1");
                }
                else {
                    AStr_AppendA(pStr, " ");
                }
            }
            AStr_AppendA(pStr, "|\n");
        }
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  U 1 6 M a t r i x
    //---------------------------------------------------------------
    
    U16MATRIX_DATA * bitMatrix_ToU16Matrix(
        BITMATRIX_DATA	*this
    )
    {
        int             x;
        int             y;
        U16MATRIX_DATA  *pMatrix;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pMatrix = u16Matrix_New(this->xMax,this->yMax);
        if (pMatrix == OBJ_NIL) {
            bitMatrix_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        for (x=1; x<=this->xMax; ++x) {
            for (y=1; y<=this->yMax; ++y) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, x, y)) {
                    eRc = u16Matrix_Set(pMatrix, x, y, 1);
                    if (ERESULT_FAILED(eRc)) {
                        bitMatrix_setLastError(this, eRc);
                        obj_Release(pMatrix);
                        pMatrix = OBJ_NIL;
                        return OBJ_NIL;
                    }
                }
                else {
                    eRc = u16Matrix_Set(pMatrix, x, y, 0);
                    if (ERESULT_FAILED(eRc)) {
                        bitMatrix_setLastError(this, eRc);
                        obj_Release(pMatrix);
                        pMatrix = OBJ_NIL;
                        return OBJ_NIL;
                    }
                }
            }
        }
        
        bitMatrix_setLastError(this, ERESULT_SUCCESS);
        return pMatrix;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s i t i v e  C l o s u r e
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_TransitiveClosure(
        BITMATRIX_DATA	*this
    )
    {
        uint16_t        i;
        uint16_t        j;
        uint16_t        k;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->xMax == this->yMax)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        for (j=1; j<=this->xMax; ++j) {
            for (i=1; i<=this->xMax; ++i) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, i, j)) {
                    for (k=1; k<=this->xMax; ++k) {
                        if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, j, k)) {
                            bitMatrix_Set(this, i, k, true);
                        }
                    }
                };
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U n i o n
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Union(
        BITMATRIX_DATA	*this,
        BITMATRIX_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        uint32_t        i;
        uint32_t        j;
        uint32_t        *pCbpW;
        uint32_t        *pOtrW;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitMatrix_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( this->cElems == pOther->cElems )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pCbpW = this->elems;
        pOtrW = pOther->elems;
        for (i=0; i<this->cElems; ++i) {
            j = *pCbpW;
            *pCbpW |= *pOtrW;
            if (j != *pCbpW) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
            ++pCbpW;
            ++pOtrW;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            bitMatrix_Validate(
        BITMATRIX_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_BITMATRIX) )
                ;
            else
                return false;
        }
        else
            return false;
        this->eRc = ERESULT_INVALID_OBJECT;
        if( !(obj_getSize(this) >= sizeof(BITMATRIX_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


