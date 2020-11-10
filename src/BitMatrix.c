// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BitMatrix.c
 *	Generated 12/18/2019 08:00:28
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
#include        <BitMatrix_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct BitMatrix_Acyclic_s {
        uint32_t    depth;
        uint32_t    marks[0];
    } BITMATRIX_ACYCLIC;
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    ERESULT         BitMatrix_BFS_Visit(
        BITMATRIX_DATA  *this,
        BITSET_DATA     *pMark,
        uint32_t        i,
        uint32_t        j,
        P_ERESULT_EXIT12 pExit,
        OBJ_ID          pObjExit
    )
    {
        ERESULT         eRc;

        if (j && pExit) {
            eRc = pExit(pObjExit, this, i, j);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }

        eRc = BitSet_Set(pMark, i, true);
        // Handle self-reflexive.
        if (j == 0) {
            if (BitMatrix_Get(this, i, i)) {
                eRc = BitMatrix_BFS_Visit(this, pMark, i, j, pExit, pObjExit);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }
        // Handle the other adjacent vertices.
        for (j=1; j <= this->xSize; j++) {
            if (BitMatrix_Get(this, i, j)) {
                if (!BitSet_Get(pMark, j)) {
                    eRc = BitMatrix_BFS_Visit(this, pMark, i, j, pExit, pObjExit);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         BitMatrix_DFS_Visit(
        BITMATRIX_DATA  *this,
        BITSET_DATA     *pMark,
        uint32_t        vFrom,
        uint32_t        vTo,
        P_ERESULT_EXIT12 pExit,
        OBJ_ID          pObjExit
    )
    {
        ERESULT         eRc;
        uint32_t        j;

        // Check for and handle Self Reflexive Back Arc which won't be handled
        // once we set the visited mark.
        if (vTo == 0) {
            vTo = vFrom;
            if (BitMatrix_Get(this, vFrom, vTo)) {
                eRc = BitMatrix_DFS_Visit(this, pMark, vFrom, vFrom, pExit, pObjExit);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        } else {
            if (pExit) {
                eRc = pExit(pObjExit, this, vFrom, vTo);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        eRc = BitSet_Set(pMark, vTo, true);
        for (j=1; j <= this->xSize; j++) {
            if (BitMatrix_Get(this, vFrom, j)) {
                if (!BitSet_Get(pMark, j)) {
                    eRc = BitMatrix_DFS_Visit(this, pMark, vFrom, j, pExit, pObjExit);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         BitMatrix_AcyclicTest(
        BITMATRIX_ACYCLIC
                        *this,
        BITMATRIX_DATA  *pMatrix,
        uint32_t        i,
        uint32_t        j
    )
    {

        if (this->marks[j-1] == 0) {
            this->depth++;
            this->marks[i-1] = this->depth;
        }
        if (this->marks[i-1] <= this->marks[j-1]) {
            return ERESULT_DATA_ALREADY_EXISTS;
        }

        return ERESULT_SUCCESS;
    }



    /*!
     @param     y       y-axis index (relative to 1)
     @param     x       x-axis index (relative to 1)
     @param     pOffset return address for offset within word of bit
     @return    If successful, the index into the matrix of the word
                which contains the bit needed and optionally the
                offset of the bit within the word.
     */
    uint32_t        BitMatrix_Index(
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
        offset = ((x - 1) & (32 - 1));

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

    BITMATRIX_DATA *     BitMatrix_Alloc (
        void
    )
    {
        BITMATRIX_DATA       *this;
        uint32_t        cbSize = sizeof(BITMATRIX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BITMATRIX_DATA *  BitMatrix_New (
        void
    )
    {
        BITMATRIX_DATA  *this;
        
        this = BitMatrix_Alloc( );
        if (this) {
            this = BitMatrix_Init(this);
        } 
        return this;
    }


    BITMATRIX_DATA * BitMatrix_NewWithSizes (
        uint32_t        ySize,
        uint32_t        xSize
    )
    {
        ERESULT         eRc;
        BITMATRIX_DATA  *this;
        
        this = BitMatrix_New( );
        if (this) {
            eRc = BitMatrix_SetSize(this, ySize, xSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }


    BITMATRIX_DATA * BitMatrix_NewIdentity (
        uint32_t        xSize
    )
    {
        ERESULT         eRc;
        BITMATRIX_DATA  *this;
        uint32_t        j;
        
        this = BitMatrix_New( );
        if (this) {
            eRc = BitMatrix_SetSize(this, xSize, xSize);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            // Add the Identity Matrix.
            for (j=1; j<=this->xSize; ++j) {
                BitMatrix_Set(this, j, j, true);
            }
            
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         Y  S i z e
    //---------------------------------------------------------------
    
    uint32_t        BitMatrix_getXSize (
        BITMATRIX_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->xSize;
    }


    bool            BitMatrix_setXSize (
        BITMATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->xSize = value;

        return true;
    }



    //---------------------------------------------------------------
    //                         Y  S i z e
    //---------------------------------------------------------------
    
    uint32_t        BitMatrix_getYSize (
        BITMATRIX_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->ySize;
    }


    bool            BitMatrix_setYSize (
        BITMATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->ySize = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        BitMatrix_getSize (
        BITMATRIX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cElems;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BitMatrix_getSuperVtbl (
        BITMATRIX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
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
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = BitMatrix_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BITMATRIX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BitMatrix_Assign (
        BITMATRIX_DATA		*this,
        BITMATRIX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BitMatrix_Validate(pOther)) {
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
            eRc = ERESULT_OUT_OF_MEMORY;
            goto eom;
        }

        // Copy other data from this object to other.
        pOther->xSize = this->xSize;
        pOther->ySize = this->ySize;
        pOther->cElems = this->cElems;

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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             BitMatrix_Compare (
        BITMATRIX_DATA  *this,
        BITMATRIX_DATA  *pOther
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int             iRc = 0;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
        if (!BitMatrix_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -1;
        }
#endif

#ifdef  xyzzy        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        iRc = strcmp(pStr1, pStr2);
#endif

        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        BitMatrix      *pCopy = BitMatrix_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BITMATRIX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BITMATRIX_DATA *     BitMatrix_Copy (
        BITMATRIX_DATA       *this
    )
    {
        BITMATRIX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BitMatrix_New( );
        if (pOther) {
            eRc = BitMatrix_Assign(this, pOther);
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

    void            BitMatrix_Dealloc (
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
        if (!BitMatrix_Validate(this)) {
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
    //              D e p t h - F i r s t  S e a r c h
    //---------------------------------------------------------------

    /*!
     Depth-First Search works from a start vertex. It then visits
     each vertex adjacent to the then current vertex recursively
     until no more vertices can be visited.

     This assumes that this matrix represents a relationship formed
     by adding edges(vFrom, vTo) to the matrix and that it is a
     square matrix (ie N X N).
     .
     @param     this    object pointer
     @param     i       vertex/node to search
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BitMatrix_DFS (
        BITMATRIX_DATA  *this,
        uint32_t        i,
        P_ERESULT_EXIT12 pExit, // (pExitObj, this, y)
        OBJ_ID          pObjExit
    )
    {
        ERESULT         eRc;
        BITSET_DATA     *pMark = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((!this->xSize) || (this->xSize != this->ySize)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if ((!i) || (i > this->xSize)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Create a zeroed bit set the size of N.
        pMark = BitSet_New();
        if (OBJ_NIL == pMark) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        eRc = BitSet_Expand(pMark, this->xSize);

        eRc = BitMatrix_DFS_Visit(this, pMark, i, 0, pExit, pObjExit);

        // Return to caller.
        if (pMark) {
            obj_Release(pMark);
        }
        return eRc;
    }



    //---------------------------------------------------------------
    //              D e p t h - F i r s t  S e a r c h
    //---------------------------------------------------------------

    /*!
     Depth-First Search works from a start vertex. It then visits
     each vertex adjacent to the then current vertex recursively
     until no more vertices can be visited.

     This assumes that this matrix represents a relationship formed
     by adding edges(vFrom, vTo) to the matrix and that it is a
     square matrix (ie N X N).
     .
     @param     this    object pointer
     @param     pExit   vertex/node exit
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BitMatrix_DFS_All (
        BITMATRIX_DATA  *this,
        P_ERESULT_EXIT12 pExit, // (pExitObj, this, y)
        OBJ_ID          pObjExit
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        BITSET_DATA     *pMark = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((!this->xSize) || (this->xSize != this->ySize)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif

        // Create a zeroed bit set the size of N.
        pMark = BitSet_New();
        if (OBJ_NIL == pMark) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        eRc = BitSet_Expand(pMark, this->xSize);

        for (i=1; i <= this->xSize; i++) {
            if (!BitSet_Get(pMark, i)) {
                eRc = BitMatrix_DFS_Visit(this, pMark, i, 0, pExit, pObjExit);
            }
        }

        // Return to caller.
        if (pMark) {
            obj_Release(pMark);
        }
        return eRc;
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
    ERESULT         BitMatrix_Disable (
        BITMATRIX_DATA  *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!BitMatrix_Validate(this)) {
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
    //                         E m p t y
    //---------------------------------------------------------------
    
    ERESULT         BitMatrix_Empty(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
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

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BitMatrix_Enable (
        BITMATRIX_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!BitMatrix_Validate(this)) {
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
    //                          G e t
    //---------------------------------------------------------------
    
    ERESULT         BitMatrix_Get(
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x
    )
    {
        uint32_t        i;
        uint32_t        j;
        ERESULT         eRc = ERESULT_FALSE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((x > 0) && (x <= this->xSize))
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
        if ((y > 0) && (y <= this->ySize))
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = BitMatrix_Index(this, y, x, &j);
        
        //uint32_t xx = cbp->elems[i];
        if ( this->pElems[i] & (1 << j) ) {
            eRc = ERESULT_TRUE;
        }
        
        // Return to caller.
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                      G e t  C o l
    //---------------------------------------------------------------
    
    BITSET_DATA *   BitMatrix_GetCol(
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
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (0 == len)
            len = this->ySize;
#ifdef NDEBUG
#else
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

        pWork = BitSet_New();
        if (OBJ_NIL == pWork) {
            return pWork;
        }
        for (i=0; i<len; ++i) {
            if (ERESULT_TRUE == BitMatrix_Get(this, y+i, x)) {
                BitSet_Set(pWork, i+1, true);
            }
            else {
                BitSet_Set(pWork, i+1, false);
            }
        }
        
        // Return to caller.
        return pWork;
    }
    
    
    U32ARRAY_DATA * BitMatrix_GetColU32(
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    )
    {
        U32ARRAY_DATA   *pWork = OBJ_NIL;
        uint16_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (0 == len)
            len = this->ySize;
#ifdef NDEBUG
#else
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
        
        pWork = u32Array_New( );
        if (OBJ_NIL == pWork) {
            return pWork;
        }
        
        for (i=0; i<len; ++i) {
            if (ERESULT_TRUE == BitMatrix_Get(this, y+i, x)) {
                u32Array_AppendData(pWork, 1);
            }
            else {
                u32Array_AppendData(pWork, 0);
            }
        }
        
        // Return to caller.
        return pWork;
    }
    
    

    //---------------------------------------------------------------
    //                      G e t  R o w
    //---------------------------------------------------------------
    
    BITSET_DATA *   BitMatrix_GetRow(
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
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (0 == len)
            len = this->xSize;
#ifdef NDEBUG
#else
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

        pWork = BitSet_New();
        if (OBJ_NIL == pWork) {
            return pWork;
        }
        
        for (i=0; i<len; ++i) {
            if (ERESULT_TRUE == BitMatrix_Get(this, y, x+i)) {
                BitSet_Set(pWork, i+1, true);
            }
            else {
                BitSet_Set(pWork, i+1, false);
            }
        }
        
        // Return to caller.
        return pWork;
    }
    
    
    U32ARRAY_DATA * BitMatrix_GetRowU32(
        BITMATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint32_t        len
    )
    {
        U32ARRAY_DATA   *pWork = OBJ_NIL;
        uint16_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (0 == len)
            len = this->xSize;
#ifdef NDEBUG
#else
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
        
        pWork = u32Array_New( );
        if (OBJ_NIL == pWork) {
            return pWork;
        }
        
        for (i=0; i<len; ++i) {
            if (ERESULT_TRUE == BitMatrix_Get(this, y, x+i)) {
                u32Array_AppendData(pWork, 1);
            }
            else {
                u32Array_AppendData(pWork, 0);
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
    ERESULT         BitMatrix_InflateX(
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
        if( !BitMatrix_Validate(this) ) {
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
                if (this->pElems) {
                    pOld = &this->pElems[y * this->xWords];
                    memmove(
                            pNew,
                            pOld,
                            (this->xWords * sizeof(uint32_t))
                    );
                }
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
                BitMatrix_Set(this, y+1, x+1, false);
            }
        }
        
        return eRc;
    }
    

    // Inflating the y-axis is fairly easy since the matrix
    // is stored in x-axis order.  We simplay must expand
    // the array adding the additional y-axis.
    ERESULT         BitMatrix_InflateY(
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
        if( !BitMatrix_Validate(this) ) {
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
            
            if(this->pElems) {
                memmove(
                        pElems,
                        this->pElems,
                        (this->cElems * sizeof(uint32_t))
                );
            }
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

    BITMATRIX_DATA *   BitMatrix_Init (
        BITMATRIX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(BITMATRIX_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BITMATRIX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BitMatrix_Vtbl);
        
    #ifdef NDEBUG
    #else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "BitMatrix::sizeof(BITMATRIX_DATA) = %lu\n", sizeof(BITMATRIX_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BITMATRIX_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I n t e r s e c t
    //---------------------------------------------------------------
    
    ERESULT         BitMatrix_Intersect(
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
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !BitMatrix_Validate( pOther ) ) {
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
    
    ERESULT         BitMatrix_Invert(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        uint32_t        x;
        uint32_t        y;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
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
    //                      I s  C y c l i c
    //---------------------------------------------------------------

    /*!
     Check the relation for cyclic edges.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BitMatrix_IsCyclic (
        BITMATRIX_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        BITMATRIX_ACYCLIC
                        *pData = NULL;
        uint32_t        i;
        uint32_t        j;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        i = this->xSize * sizeof(uint32_t);
        i += sizeof(BITMATRIX_ACYCLIC);
        pData = mem_Calloc(1, i);
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }

        for (i=1; i <= this->xSize; i++) {
            for (j=0; j < this->xSize; j++) {
                pData->marks[j] = 0;
            }
            eRc = BitMatrix_DFS(this, i, (void *)BitMatrix_AcyclicTest, pData);
            if (ERESULT_FAILED(eRc)) {
                break;              // Break if cyclic.
            }
        }
        if (ERESULT_OK(eRc))
            eRc = ERESULT_DATA_OUT_OF_RANGE;
        else
            eRc = ERESULT_SUCCESS;

        // Return to caller.
        if (pData)
            mem_Free(pData);
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s E m p t y
    //---------------------------------------------------------------
    
    ERESULT         BitMatrix_IsEmpty(
        BITMATRIX_DATA  *this
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
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
    
    ERESULT         BitMatrix_IsEnabled (
        BITMATRIX_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
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
    //                          P r e d
    //---------------------------------------------------------------
    
    U32ARRAY_DATA * BitMatrix_Pred (
        BITMATRIX_DATA  *this,
        uint32_t        n
    )
    {
        BITSET_DATA     *pBitSet = OBJ_NIL;
        U32ARRAY_DATA   *pSet = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pSet;
        }
        if ((0 == n) || (n > this->xSize)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pSet;
        }
#endif
        
        //                               y  x  len
        pBitSet = BitMatrix_GetCol(this, 1, n,  0);
        if (OBJ_NIL == pBitSet) {
            return pSet;
        }
        
        // Calculate the set.
        pSet = BitSet_ToArrayU32(pBitSet);
        
        // Return to caller.
        obj_Release(pBitSet);
        pBitSet = OBJ_NIL;
        return pSet;
    }
        
        
        
    //---------------------------------------------------------------
    //                    P r o d u c t
    //---------------------------------------------------------------
    
    BITMATRIX_DATA * BitMatrix_Product(
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
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( !BitMatrix_Validate(pOther) ) {
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
        
        pProduct = BitMatrix_NewWithSizes(this->xSize, this->ySize);
        if (OBJ_NIL == pProduct) {
            return OBJ_NIL;
        }
        
        for (j=1; j<=this->xSize; ++j) {
            for (i=1; i<=this->xSize; ++i) {
                if (ERESULT_TRUE == BitMatrix_Get(this, i, j)) {
                    for (k=1; k<=this->xSize; ++k) {
                        if (ERESULT_TRUE == BitMatrix_Get(pOther, j, k)) {
                            BitMatrix_Set(pProduct, i, k, true);
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
        void        *pMethod = BitMatrix_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BitMatrix", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BitMatrix_QueryInfo (
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
        if (!BitMatrix_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BITMATRIX_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BitMatrix_Class();
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
                            return BitMatrix_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return BitMatrix_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BitMatrix_ToDebugString;
                        }
#ifdef  BITMATRIX_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BitMatrix_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BitMatrix_ToDebugString)
                    return "ToDebugString";
#ifdef  BITMATRIX_JSON_SUPPORT
                if (pData == BitMatrix_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //    R e f l e c t i v e  T r a n s i t i v e  C l o s u r e
    //---------------------------------------------------------------
    
    ERESULT         BitMatrix_ReflectiveTransitiveClosure(
        BITMATRIX_DATA  *this
    )
    {
        uint16_t        j;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
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
            BitMatrix_Set(this, j, j, true);
        }
        
        eRc = BitMatrix_TransitiveClosure(this);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         BitMatrix_Set(
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
        if( !BitMatrix_Validate(this) ) {
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
        
        i = BitMatrix_Index(this, y, x, &j);

        if (fValue) {
            this->pElems[i] |= (1 << j);
        }
        else {
            this->pElems[i] &= ~(1 << j);
        }
        
        // Return to caller.
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
    ERESULT         BitMatrix_SetSize(
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
        if( !BitMatrix_Validate(this) ) {
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
                            BitMatrix_Set(this, y+1, x+1, false);
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
    //                          S u c c
    //---------------------------------------------------------------
    
    U32ARRAY_DATA * BitMatrix_Succ (
        BITMATRIX_DATA  *this,
        uint32_t        n
    )
    {
        BITSET_DATA     *pBitSet = OBJ_NIL;
        U32ARRAY_DATA   *pSet = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pSet;
        }
        if ((0 == n) || (n > this->ySize)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return pSet;
        }
#endif
        
        //                               y  x  len
        pBitSet = BitMatrix_GetCol(this, n, 1,  0);
        if (OBJ_NIL == pBitSet) {
            return pSet;
        }
        
        // Calculate the set.
        pSet = BitSet_ToArrayU32(pBitSet);
        
        // Return to caller.
        obj_Release(pBitSet);
        pBitSet = OBJ_NIL;
        return pSet;
    }
            
            
            
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BitMatrix_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BitMatrix_ToDebugString (
        BITMATRIX_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        int             x;
        int             y;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitMatrix_Validate(this)) {
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
                    "{%p(%s) xSize=%d ySize=%d size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    this->xSize,
                    this->ySize,
                    BitMatrix_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent+5, ' ');
        }
        AStr_AppendA(pStr, " ");
        for (x=0; x<(this->xSize/10); ++x) {
            AStr_AppendA(pStr, "  123456789012");
        }
        AStr_AppendA(pStr, "\n");
        for (y=1; y<=this->ySize; ++y) {
            if (indent) {
                AStr_AppendCharRepeatW32(pStr, indent+3, ' ');
            }
            AStr_AppendPrint(pStr, "%3d |", y);
            for (x=1; x<=this->xSize; ++x) {
                if (ERESULT_TRUE == BitMatrix_Get(this, y, x)) {
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
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  U 1 6 M a t r i x
    //---------------------------------------------------------------
    
#ifdef XYZZY
    U16MATRIX_DATA * BitMatrix_ToU16Matrix (
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
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pMatrix = u16Matrix_New(this->xSize,this->ySize);
        if (pMatrix == OBJ_NIL) {
            return OBJ_NIL;
        }
        
        for (x=1; x<=this->xSize; ++x) {
            for (y=1; y<=this->ySize; ++y) {
                if (ERESULT_TRUE == BitMatrix_Get(this, x, y)) {
                    eRc = u16Matrix_Set(pMatrix, x, y, 1);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pMatrix);
                        pMatrix = OBJ_NIL;
                        return OBJ_NIL;
                    }
                }
                else {
                    eRc = u16Matrix_Set(pMatrix, x, y, 0);
                    if (ERESULT_FAILED(eRc)) {
                        obj_Release(pMatrix);
                        pMatrix = OBJ_NIL;
                        return OBJ_NIL;
                    }
                }
            }
        }
        
        return pMatrix;
    }
#endif
        
        
        
    //---------------------------------------------------------------
    //           T r a n s i t i v e  C l o s u r e
    //---------------------------------------------------------------
    
    ERESULT         BitMatrix_TransitiveClosure (
        BITMATRIX_DATA  *this
    )
    {
        uint16_t        i;
        uint16_t        j;
        uint16_t        k;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitMatrix_Validate(this) ) {
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
                if (ERESULT_TRUE == BitMatrix_Get(this, i, j)) {
                    for (k=1; k<=this->xSize; ++k) {
                        if (ERESULT_TRUE == BitMatrix_Get(this, j, k)) {
                            BitMatrix_Set(this, i, k, true);
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
    
    ERESULT         BitMatrix_Union(
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
        if( !BitMatrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !BitMatrix_Validate( pOther ) ) {
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
    bool            BitMatrix_Validate (
        BITMATRIX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BITMATRIX))
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


        if (!(obj_getSize(this) >= sizeof(BITMATRIX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


