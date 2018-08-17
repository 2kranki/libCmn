// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   bitMatrix.c
 *	Generated 08/12/2018 15:05:02
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
#include        <bitMatrix_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /*!
     @param     y       y-axis index (relative to 1)
     @param     x       x-axis index (relative to 1)
     @param     pOffset return address for offset within word of bit
     @return    If successful, the index into the matrix of the word
                which contains the bit needed and optionally the
                offset of the bit within the word.
     */
    uint32_t        bitMatrix_Index(
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        *pOffset
    )
    {
        uint32_t        index;
        uint32_t        offset;
     
        // Do initialization.
        
        index  = ((y - 1) * this->xWords) + ((x - 1) >> 5);
        offset = 31 - ((x - 1) & 0x1F);

        if (pOffset)
            *pOffset = offset;

        return index;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BITMATRIX_DATA * bitMatrix_Alloc(
        void
    )
    {
        BITMATRIX_DATA  *this;
        uint32_t        cbSize = sizeof(BITMATRIX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BITMATRIX_DATA * bitMatrix_New(
        uint32_t        ySize,
        uint32_t        xSize
    )
    {
        BITMATRIX_DATA  *this;
        
        this = bitMatrix_Alloc( );
        if (this) {
            this = bitMatrix_Init(this, ySize, xSize);
        } 
        return this;
    }



    BITMATRIX_DATA * bitMatrix_NewIdentity(
        uint32_t        xSize
    )
    {
        BITMATRIX_DATA  *this;
        uint32_t        i;
        ERESULT         eRc;

        if (xSize)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this = bitMatrix_NewSquare(xSize);
        if (this) {
            for (i=0; i<xSize; ++i) {
                eRc = bitMatrix_Set(this, i, i, true);
            }
        }
        
        return this;
    }
    
    
    
    BITMATRIX_DATA * bitMatrix_NewSquare(
        uint32_t        xSize
    )
    {
        BITMATRIX_DATA  *this;
        
        this = bitMatrix_New(xSize, xSize);
        
        return this;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        bitMatrix_getSize(
        BITMATRIX_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        return this->cElems;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  bitMatrix_getSuperVtbl(
        BITMATRIX_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          x S i z e
    //---------------------------------------------------------------
    
    uint32_t        bitMatrix_getXSize(
        BITMATRIX_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->xSize;
    }
    
    
    bool            bitMatrix_setXSize(
        BITMATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->xSize = value;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          y S i z e
    //---------------------------------------------------------------
    
    uint32_t        bitMatrix_getYSize(
        BITMATRIX_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->ySize;
    }
    
    
    bool            bitMatrix_setYSize(
        BITMATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->ySize = value;
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
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
        ERESULT eRc = bitMatrix__Assign(this,pOther);
     @endcode 
     @param     this    BITMATRIX object pointer
     @param     pOther  a pointer to another BITMATRIX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         bitMatrix_Assign(
        BITMATRIX_DATA		*this,
        BITMATRIX_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitMatrix_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pElems && !(pOther->pElems == this->pElems)) {
            mem_Free(pOther->pElems);
            //pOther->pElems = NULL;
            pOther->pElems = mem_Malloc(this->cElems * sizeof(uint32_t));
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (pOther->pElems) {
            memmove(pOther->pElems, this->pElems, (this->cElems * sizeof(uint32_t)));
        }
        else {
            DEBUG_BREAK();
            pOther->xSize = 0;
            pOther->ySize = 0;
            pOther->cElems = 0;
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            goto eom;
        }

        // Copy other data from this object to other.
        pOther->xSize = this->xSize;
        pOther->ySize = this->ySize;
        pOther->cElems = this->cElems;
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
    eom:
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
    ERESULT         bitMatrix_Compare(
        BITMATRIX_DATA     *this,
        BITMATRIX_DATA     *pOther
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
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitMatrix_Validate(pOther) ) {
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
        bitMatrix      *pCopy = bitMatrix_Copy(this);
     @endcode 
     @param     this    BITMATRIX object pointer
     @return    If successful, a BITMATRIX object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the BITMATRIX object.
     */
    BITMATRIX_DATA *     bitMatrix_Copy(
        BITMATRIX_DATA       *this
    )
    {
        BITMATRIX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = bitMatrix_New(this->xSize, this->ySize);
        if (pOther) {
            eRc = bitMatrix_Assign(this, pOther);
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

    void            bitMatrix_Dealloc(
        OBJ_ID          objId
    )
    {
        BITMATRIX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BITMATRIX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pElems) {
            mem_Free(this->pElems);
            this->pElems = NULL;
            this->xSize = 0;
            this->ySize = 0;
            this->cElems = 0;
        }
        
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

    ERESULT         bitMatrix_Disable(
        BITMATRIX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !bitMatrix_Validate(this) ) {
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
    //                         E m p t y
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Empty(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<this->cElems; ++i) {
            this->pElems[i] = 0;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         bitMatrix_Enable(
        BITMATRIX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !bitMatrix_Validate(this) ) {
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
    //                          G e t
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Get(
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x
    )
    {
        uint32_t        i;
        uint32_t        j;
        ERESULT         eRc = ERESULT_SUCCESS_FALSE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((x > 0) && (x <= this->xSize))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((y > 0) && (y <= this->ySize))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = ((y - 1) * (ROUNDUP32(this->xSize) >> 5)) + ((x - 1) >> 5);
        j = 31 - ((x - 1) & 0x1F);
        
        //uint32_t xx = cbp->elems[i];
        if ( this->pElems[i] & (1 << j) ) {
            eRc = ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      G e t  C o l u m n
    //---------------------------------------------------------------
    
    BITSET_DATA *   bitMatrix_GetColumn(
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    )
    {
        BITSET_DATA     *pWork = OBJ_NIL;
        uint16_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((x > 0) && (x <= this->xSize))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((y > 0) && (y <= this->ySize))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((x + len - 1) <= this->xSize)
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
            if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, x+i, y)) {
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
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    )
    {
        BITSET_DATA     *pWork = OBJ_NIL;
        uint16_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if ((x > 0) && (x <= this->xSize))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((y > 0) && (y <= this->ySize))
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((y + len - 1) <= this->ySize)
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
            if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, x, y+i)) {
                bitSet_Set(pWork, i+1, true);
            }
        }
        
        // Return to caller.
        return pWork;
    }
    
    
    
    //---------------------------------------------------------------
    //                      I n f l a t e
    //---------------------------------------------------------------
    
    // Inflating the x-axis is easy if the bits are already available
    // in the rounding.  Otherwise, we must expand each row by the
    // amount given since the matrix is stored in x-axis order.
    ERESULT         bitMatrix_InflateX(
        BITMATRIX_DATA  *this,
        uint32_t        amt             // number of bits
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        size;
        uint32_t        xWords;
        uint32_t        xNew;
        uint32_t        yNew;
        uint32_t        xOld = this->xSize;
        uint32_t        yOld = this->ySize;
        uint32_t        cElems = 0;
        uint32_t        *pElems;
        uint32_t        *pOld;
        uint32_t        *pNew;
        uint32_t        x;
        uint32_t        y;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( amt )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        xNew = ROUNDUP32(xOld + amt);
        xWords = xNew >> 5;
        yNew = yOld;
        size = xNew * yNew;
        if (size) {
            cElems = size >> 5;
        }
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        
        // Allocate and clear the bit memory.
        if (xNew == ROUNDUP32(xOld))
            ;
        else {
            pElems = mem_Malloc(cElems * sizeof(uint32_t));
            if (NULL == pElems) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
            for (y=0; y<yNew; ++y) {
                pNew = &pElems[y * xWords];
                pOld = &this->pElems[y * this->xWords];
                memmove(
                        pNew,
                        pOld,
                        (this->xWords * sizeof(uint32_t))
                );
                memset(
                       &pNew[this->xWords],
                       0,
                       ((xWords - this->xWords) * sizeof(uint32_t))
                );
            }
            this->cElems = cElems;
            if (this->pElems) {
                mem_Free(this->pElems);
            }
            this->pElems = pElems;
        }
        this->xSize = xOld + amt;
        this->xWords = xWords;
        
        // Zero the bits within the last word of each row.
        size = (xOld + amt) < 32 ? (xOld + amt) : 32;
        for (y=0; y<yOld; ++y) {
            for (x=xOld; x<size; ++x) {
                bitMatrix_Set(this, y+1, x+1, false);
            }
        }
        
        return eRc;
    }
    

    // Inflating the y-axis is fairly easy since the matrix
    // is stored in x-axis order.  We simplay must expand
    // the array adding the additional y-axis.
    ERESULT         bitMatrix_InflateY(
        BITMATRIX_DATA  *this,
        uint32_t        amt             // number of bits
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        yNew;
        uint32_t        yOld = this->ySize;
        uint32_t        cElems = 0;
        uint32_t        *pElems;
        //uint32_t        x;
        //uint32_t        y;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( amt )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        yNew = yOld + amt;
        cElems = this->xWords * yNew;
        if (cElems)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
        
        // Allocate and clear the bit memory if needed.
        if (this->cElems == cElems)
            ;
        else {
            pElems = mem_Malloc(cElems * sizeof(uint32_t));
            if (NULL == pElems) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
            
            memmove(
                    pElems,
                    this->pElems,
                    (this->cElems * sizeof(uint32_t))
            );
            if (cElems > this->cElems) {
                memset(
                       (pElems + this->cElems),
                       0,
                       ((cElems - this->cElems) * sizeof(uint32_t))
                );
            }
            if (this->pElems) {
                mem_Free(this->pElems);
            }
            this->pElems = pElems;
            this->cElems = cElems;
        }
        this->ySize = yOld + amt;
        
        return eRc;
    }
    
    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BITMATRIX_DATA * bitMatrix_Init(
        BITMATRIX_DATA  *this,
        uint32_t        ySize,
        uint32_t        xSize
    )
    {
        uint32_t        cbSize = sizeof(BITMATRIX_DATA);
        ERESULT         eRc;
        uint32_t        xWords;
        uint32_t        xNew;
        uint32_t        yNew;

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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BITMATRIX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BITMATRIX);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&bitMatrix_Vtbl);
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

        if (ySize && xSize) {
            this->ySize = ySize;
            this->xSize = xSize;
            xNew = ROUNDUP32(xSize);
            this->xWords = xNew >> 5;
            this->cElems = this->xWords * ySize;
            this->pElems = mem_Calloc(this->cElems, sizeof(uint32_t));
            if (NULL == this->pElems) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "bitMatrix::sizeof(BITMATRIX_DATA) = %lu\n", sizeof(BITMATRIX_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BITMATRIX_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I n t e r s e c t
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Intersect(
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        j;
        
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
        
        for (i=0; i<this->cElems; ++i) {
            j = this->pElems[i];
            this->pElems[i] &= pOther->pElems[i];
            if (j != this->pElems[i]) {
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
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        uint32_t        x;
        uint32_t        y;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (y=0; y<this->ySize; ++y) {
            for (x=0; x<this->xWords; ++x) {
                i = (y * this->xWords) + x;
                this->pElems[i] = ~this->pElems[i];
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E m p t y
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_IsEmpty(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<this->cElems; ++i) {
            if (this->pElems[i]) {
                return ERESULT_FAILURE_FALSE;
            }
        }
        
        
        // Return to caller.
        return ERESULT_SUCCESS_TRUE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_IsEnabled(
        BITMATRIX_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
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
    //                    P r o d u c t
    //---------------------------------------------------------------
    
    BITMATRIX_DATA * bitMatrix_Product(
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
    )
    {
        BITMATRIX_DATA  *pProduct;
        uint16_t        i;
        uint16_t        j;
        uint16_t        k;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (this->xSize == this->ySize)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (pOther->xSize == pOther->ySize)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (this->ySize == pOther->ySize)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pProduct = bitMatrix_New(this->xSize, this->ySize);
        if (OBJ_NIL == pProduct) {
            return OBJ_NIL;
        }
        
        for (j=1; j<=this->xSize; ++j) {
            for (i=1; i<=this->xSize; ++i) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, i, j)) {
                    for (k=1; k<=this->xSize; ++k) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = bitMatrix_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "bitMatrix", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          bitMatrix_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BITMATRIX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)bitMatrix_Class();
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
                            return bitMatrix_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return bitMatrix_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return bitMatrix_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return bitMatrix_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == bitMatrix_ToDebugString)
                    return "ToDebugString";
                if (pData == bitMatrix_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //    R e f l e c t i v e  T r a n s i t i v e  C l o s u r e
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_ReflectiveTransitiveClosure(
        BITMATRIX_DATA  *this
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
        if (this->xSize == this->ySize)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        // Add the Identity Matrix.
        for (j=1; j<=this->xSize; ++j) {
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
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        bool            fValue
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
        if ((x > 0) && (x <= this->xSize))
            ;
        else {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
        if ((y > 0) && (y <= this->ySize))
            ;
        else {
            DEBUG_BREAK();
            obj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = ((y - 1) * this->xWords) + ((x - 1) >> 5);
        j = 31 - ((x - 1) & 0x1F);

        if (fValue) {
            this->pElems[i] |= (1 << j);
        }
        else {
            this->pElems[i] &= ~(1 << j);
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t  S i z e
    //---------------------------------------------------------------
    
    /*!
     Set up  a newly sized matrix.  If xSize and ySize are different from the
     current size, then a new maxtrix is gotten and the old data that is pertinent
     is copied over.
     If xSize and ySize are both zero, then the bit matrix is set to zero size.
     @param     this    BITMATRIX object pointer
     @param     xSize   x-axis number of bits, can be 0
     @param     ySize   x-axis number of bits, can be 0
     @return    If successful, an AStr object which must be released containing the
     description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ERESULT         bitMatrix_SetSize(
        BITMATRIX_DATA  *this,
        uint32_t        ySize,
        uint32_t        xSize
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        sizeInBits;
        uint32_t        xWords;
        uint32_t        xNew;
        uint32_t        yNew;
        uint32_t        xOld = this->xSize;
        uint32_t        yOld = this->ySize;
        uint32_t        cElems = 0;
        uint32_t        *pElems;
        uint32_t        *pOld;
        uint32_t        *pNew;
        uint32_t        x;
        uint32_t        y;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        xNew = ROUNDUP32(xSize);
        xWords = xNew >> 5;
        yNew = ySize;
        sizeInBits = xNew * yNew;
        if (sizeInBits) {
            cElems = sizeInBits >> 5;
        }
        else {
            this->xSize = 0;
            this->ySize = 0;
            this->cElems = 0;
            if (this->pElems) {
                mem_Free(this->pElems);
            }
            this->pElems = NULL;
            return eRc;
        }
        
         // Allocate and clear the bit memory.
        if (this->cElems == cElems) {
            // Zero the new bits if we expanded the array.
            if ((xOld < xNew) || (yOld < yNew)) {
                for (y=0; y<yNew; ++y) {
                    for (x=0; x<xNew; ++x) {
                        if ((x >= xOld) || (y >= yOld)) {
                            bitMatrix_Set(this, y+1, x+1, false);
                        }
                    }
                }
            }
        }
        else {
            pElems = mem_Calloc(cElems, sizeof(uint32_t));
            if (NULL == pElems) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
            
            if (xOld && yOld) {
                //TODO: Maybe use memmove() and copy x-axis at a time.
                xOld = ROUNDUP32(this->xSize);
                if (xOld)
                    xOld >>= 5;
                yOld = ROUNDUP32(this->ySize);
                if (yOld)
                    yOld >>= 5;
                if (xNew)
                    xNew >>= 5;
                if (yNew)
                    yNew >>= 5;
                for (x=0; x<xNew; ++x) {
                    for (y=0; y<yNew; ++y) {
                        if ((x < xOld) && (y < yOld)) {
                            pOld = &this->pElems[x + (y * xOld)];
                            pNew = &pElems[x + (y * xNew)];
                            *pNew = *pOld;
                        }
                    }
                }
            }
            this->cElems = cElems;
            if (this->pElems) {
                mem_Free(this->pElems);
            }
            this->pElems = pElems;
        }
        this->xWords = ROUNDUP32(xSize) >> 5;
        this->xSize = xSize;
        this->ySize = ySize;

        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     bitMatrix_ToJSON(
        BITMATRIX_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
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
        ASTR_DATA      *pDesc = bitMatrix_ToDebugString(this,4);
     @endcode 
     @param     this    BITMATRIX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     bitMatrix_ToDebugString(
        BITMATRIX_DATA  *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        int             x;
        int             y;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
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
                    "{%p(%s) xSize=%d ySize=%d size=%d\n",
                    this,
                    pInfo->pClassName,
                    this->xSize,
                    this->ySize,
                    this->cElems
            );

        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent+5, ' ');
        }
        AStr_AppendA(pStr, " ");
        for (x=0; x<(this->xSize/10); ++x) {
            AStr_AppendA(pStr, "1234567890");
        }
        AStr_AppendA(pStr, "\n");
        for (x=1; x<=this->xSize; ++x) {
            if (indent) {
                AStr_AppendCharRepeatW32(pStr, indent+3, ' ');
            }
            AStr_AppendPrint(pStr, "%3d |", x);
            for (y=1; y<=this->ySize; ++y) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, y, x)) {
                    AStr_AppendA(pStr, "1");
                }
                else {
                    AStr_AppendA(pStr, " ");
                }
            }
            AStr_AppendA(pStr, "|\n");
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  U 1 6 M a t r i x
    //---------------------------------------------------------------
    
    U16MATRIX_DATA * bitMatrix_ToU16Matrix(
        BITMATRIX_DATA  *this
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
        
        pMatrix = u16Matrix_New(this->xSize,this->ySize);
        if (pMatrix == OBJ_NIL) {
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        for (x=1; x<=this->xSize; ++x) {
            for (y=1; y<=this->ySize; ++y) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, x, y)) {
                    eRc = u16Matrix_Set(pMatrix, x, y, 1);
                    if (ERESULT_FAILED(eRc)) {
                        obj_setLastError(this, eRc);
                        obj_Release(pMatrix);
                        pMatrix = OBJ_NIL;
                        return OBJ_NIL;
                    }
                }
                else {
                    eRc = u16Matrix_Set(pMatrix, x, y, 0);
                    if (ERESULT_FAILED(eRc)) {
                        obj_setLastError(this, eRc);
                        obj_Release(pMatrix);
                        pMatrix = OBJ_NIL;
                        return OBJ_NIL;
                    }
                }
            }
        }
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pMatrix;
    }
    
    
    
    //---------------------------------------------------------------
    //           T r a n s i t i v e  C l o s u r e
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_TransitiveClosure(
        BITMATRIX_DATA  *this
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
        if (this->xSize == this->ySize)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        for (j=1; j<=this->xSize; ++j) {
            for (i=1; i<=this->xSize; ++i) {
                if (ERESULT_SUCCESS_TRUE == bitMatrix_Get(this, i, j)) {
                    for (k=1; k<=this->xSize; ++k) {
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
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
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
        
        pCbpW = this->pElems;
        pOtrW = pOther->pElems;
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
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_BITMATRIX) )
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


        if( !(obj_getSize(this) >= sizeof(BITMATRIX_DATA)) ) {
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                         Z e r o
    //---------------------------------------------------------------
    
    ERESULT         bitMatrix_Zero(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<this->cElems; ++i) {
            this->pElems[i] = 0;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    

    
#ifdef	__cplusplus
}
#endif


