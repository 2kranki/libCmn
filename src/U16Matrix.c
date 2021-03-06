// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   U16Matrix.c
 *	Generated 02/18/2020 11:52:42
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
#include        <U16Matrix_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    bool            U16Matrix_IsIndexValid (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
    )
    {

        if ((1 <= i) && (i <= this->m)) {
        }
        else {
            return false;
        }
        if ((1 <= j) && (j <= this->n)) {
        }
        else {
            return false;
        }

        // Return to caller.
        return true;
    }



    uint32_t        U16Matrix_Index (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
    )
    {
        uint32_t        index;

#ifdef NDEBUG
#else
        if (!U16Matrix_IsIndexValid(this, i, j)) {
            return -1;
        }
#endif

        index = ((i - 1) * this->n) + (j - 1);

        // Return to caller.
        return index;
    }



    bool            U16Matrix_AddRowToValueCheck (
        U16MATRIX_DATA  *this,
        MATRIX_BUILD    *pBuild,
        uint32_t        row
    )
    // This routine adds the specified row from the sparse matrix to the
    // compressed matrix.  We try to fit the row as best as possible given
    // the current state of the compressed matrix.
    {
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        uint16_t        value;
        int32_t         baseNew = 0;        /* new base for value/check */

        /*
         * Now search the value table for a base such that the non-
         * zero entries of the row fit into zero entries of the value
         * table.
         */
        iMax = pBuild->baseMax - this->n;   // Start at the last row added
        for( i=0; i < iMax; i++ ) {
            baseNew = i;
            for( j=1; j <= this->n; j++ ) {
                value = U16Matrix_Get(this, row, j);
                if( value ) {
                    if( pBuild->pCheck[i+j-1] == 0 )
                        ;
                    else {
                        baseNew = -1;
                        break;
                    }
                }
            }
            // Break if we found a fit for the row.
            if( baseNew == i )
                break;
        }
        if( baseNew == -1 ) {           /*** table overflow ***/
            return false;
        }
        if( baseNew > pBuild->baseMax ) {
            pBuild->baseMax = baseNew;
        }
        pBuild->pBase[row-1] = baseNew;

        // Now add the row to the base/value/check table.
        for( j=1; j<=this->n; j++ ) {
            value = U16Matrix_Get(this, row, j);
            if( value ) {
                if (pBuild->pValue[baseNew+j-1]) {
                    DEBUG_BREAK();
                }
                pBuild->pValue[baseNew+j-1] = value;
                pBuild->pCheck[baseNew+j-1] = row;
                if ((baseNew + j) > pBuild->highest) {
                    pBuild->highest = baseNew + j;
                }
            }
        }

        // Return to caller.
        return true;
    }



    MATRIX_BUILD *  U16Matrix_BuildValueCheck (
        U16MATRIX_DATA  *this
    )
    {
        MATRIX_BUILD    *pBuild = NULL;
        uint32_t        i;
        uint32_t        baseMax;

#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        pBuild = mem_Calloc( 1, sizeof(MATRIX_BUILD) );
        if( NULL == pBuild ) {
            return NULL;
        }
        pBuild->m = this->m;
        pBuild->n = this->n;
        baseMax = this->m * this->n;
        pBuild->baseMax = baseMax;
        pBuild->pBase = (int32_t *)mem_Calloc( this->m, sizeof(int32_t) );
        if( NULL == pBuild->pBase ) {
            mem_Free(pBuild);
            return NULL;
        }
        pBuild->pValue  = (uint16_t *)mem_Calloc( baseMax, sizeof(uint16_t) );
        if( NULL == pBuild->pValue ) {
            mem_Free(pBuild->pBase);
            mem_Free(pBuild);
            return NULL;
        }
        pBuild->pCheck  = (uint32_t *)mem_Calloc( baseMax, sizeof(uint32_t) );
        if( NULL == pBuild->pCheck ) {
            mem_Free(pBuild->pValue);
            mem_Free(pBuild->pBase);
            mem_Free(pBuild);
            return NULL;
        }

        // Build the compressed table adding each row.
        for (i=1; i<=this->m; ++i) {
            U16Matrix_AddRowToValueCheck( this, pBuild, i );
        }

        // Return to caller.
        return pBuild;
    }



    ERESULT         U16Matrix_FreeValueCheck (
        U16MATRIX_DATA  *this,
        MATRIX_BUILD    *pBuild
    )
    {

#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pBuild) {
            if (pBuild->pCheck) {
                mem_Free(pBuild->pCheck);
                pBuild->pCheck = NULL;
            }
            if (pBuild->pValue) {
                mem_Free(pBuild->pValue);
                pBuild->pValue = NULL;
            }
            if (pBuild->pBase) {
                mem_Free(pBuild->pBase);
                pBuild->pBase = NULL;
            }
            mem_Free(pBuild);
            pBuild = NULL;
        }

        return ERESULT_SUCCESS;
    }




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    U16MATRIX_DATA *     U16Matrix_Alloc (
        void
    )
    {
        U16MATRIX_DATA       *this;
        uint32_t        cbSize = sizeof(U16MATRIX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    U16MATRIX_DATA *     U16Matrix_New (
        void
    )
    {
        U16MATRIX_DATA       *this;
        
        this = U16Matrix_Alloc( );
        if (this) {
            this = U16Matrix_Init(this);
        } 
        return this;
    }


    U16MATRIX_DATA * U16Matrix_NewWithSizes (
        uint32_t        ySize,          // Height (y-axis, Number of Rows, i)
        uint32_t        xSize           // Width (x-axis, Number of Columns, j)

    )
    {
        ERESULT         eRc;
        U16MATRIX_DATA  *this;

        this = U16Matrix_New( );
        if (this) {
            eRc = U16Matrix_Setup(this, ySize, xSize);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }

        // Return to caller.
        return this;
    }



    U16MATRIX_DATA * U16Matrix_NewIdentity (
        uint32_t        n
    )
    {
        ERESULT         eRc;
        U16MATRIX_DATA  *this;
        uint32_t        i;

        this = U16Matrix_New( );
        if (this) {
            eRc = U16Matrix_Setup(this, n, n);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
            for (i=1; i<=n; ++i) {
                U16Matrix_Set(this, i, i, 1);
            }
        }

        // Return to caller.
        return this;
    }



    U16MATRIX_DATA * U16Matrix_NewSquare (
        uint32_t        n
    )
    {
        U16MATRIX_DATA  *this;
        ERESULT         eRc;

        this = U16Matrix_New( );
        if (this) {
            eRc = U16Matrix_Setup(this, n, n);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }

        // Return to caller.
        return this;
    }




    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              M
    //---------------------------------------------------------------

    uint32_t        U16Matrix_getM (
        U16MATRIX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->m;
    }


    bool            U16Matrix_setM (
        U16MATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->m = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              N
    //---------------------------------------------------------------

    uint32_t        U16Matrix_getN (
        U16MATRIX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->n;
    }


    bool            U16Matrix_setN (
        U16MATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->n = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        U16Matrix_getSize (
        U16MATRIX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  U16Matrix_getSuperVtbl (
        U16MATRIX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
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
    //                       A d d
    //---------------------------------------------------------------

    ERESULT         U16Matrix_Add (
        U16MATRIX_DATA  *this,
        U16MATRIX_DATA  *pOther
    )
    {
        uint32_t        i;
        uint16_t        *pDst;
        uint16_t        *pSrc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!U16Matrix_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->cElems == pOther->cElems)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        for (i=0; i<this->cElems; ++i) {
            pDst = array_GetAddrOf((ARRAY_DATA *)this, i+1);
            pSrc = array_GetAddrOf((ARRAY_DATA *)pOther, i+1);
            *pDst += *pSrc;
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
        ERESULT eRc = U16Matrix_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another U16MATRIX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         U16Matrix_Assign (
        U16MATRIX_DATA	*this,
        U16MATRIX_DATA  *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!U16Matrix_Validate(pOther)) {
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
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        pOther->m =this->m;
        pOther->n =this->n;
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
     @return    0 if this == other
                1 if this != other
     */
    int             U16Matrix_Compare (
        U16MATRIX_DATA  *this,
        U16MATRIX_DATA  *pOther
    )
    {
        uint32_t        i = 0;
        uint16_t        *pValue1;
        uint16_t        *pValue2;

#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!U16Matrix_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        if ((this->m == pOther->m) && (this->m == pOther->m))
            ;
        else {
            return 1;
        }
        if (this->cElems == pOther->cElems)
            ;
        else {
            return 1;
        }

        for (i=0; i<this->cElems; i++) {
            pValue1 = array_GetAddrOf((ARRAY_DATA *)this, i+1);
            pValue2 = array_GetAddrOf((ARRAY_DATA *)pOther, i+1);
            if (pValue1 && pValue2) {
                if (*pValue1 == *pValue2)
                    ;
                else {
                    return 1;
                }
            } else {
                return 1;
            }
        }

        return 0;
    }
    
   
 
    //---------------------------------------------------------------
    //        G e n e r a t e  C o m p r e s s e d  T a b l e
    //---------------------------------------------------------------

    ASTR_DATA *     U16Matrix_CompressedTable(
        U16MATRIX_DATA  *this,
        const
        char            *pPrefix
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        MATRIX_BUILD    *pBuild = NULL;
        ASTR_DATA       *pStr = OBJ_NIL;
        uint32_t        sizeMatrix;
        uint32_t        sizeBuild;
        bool            fSmall = true;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        pBuild = U16Matrix_BuildValueCheck(this);
        if( NULL == pBuild ) {
            return OBJ_NIL;
        }

        // Check savings.
        sizeMatrix = pBuild->m * pBuild->n * sizeof(uint16_t);
        if ((pBuild->m > (65536-1)) || (pBuild->highest > (65536-1))) {
            fSmall = false;
            sizeBuild  = pBuild->m * sizeof(uint32_t);          // Base
            sizeBuild += pBuild->highest * sizeof(uint32_t);    // Check
            sizeBuild += pBuild->highest * sizeof(uint16_t);    // Value
        }
        else {
            sizeBuild  = pBuild->m * sizeof(int16_t);           // Base
            sizeBuild += pBuild->highest * sizeof(uint16_t);    // Check
            sizeBuild += pBuild->highest * sizeof(uint16_t);    // Value
        }
        if (sizeMatrix > sizeBuild)
            ;
        else {
            return OBJ_NIL;
        }

        pStr = AStr_New();
        if( NULL == pStr ) {
            return OBJ_NIL;
        }

        AStr_AppendPrint( pStr,
                 "//    ***  Compressed Matrix Table   ***\n\n"
        );
        iMax = this->m;
        if (fSmall) {
            AStr_AppendPrint( pStr,
                     "static\nconst\nuint16_t baseTable[%d] = {\n",
                     iMax
            );
        }
        else {
            AStr_AppendPrint( pStr,
                     "static\nconst\nuint32_t baseTable[%d] = {\n",
                     iMax
                     );
        }
        AStr_AppendPrint( pStr,
                 "\t\t\t// X\n"
                 );
        for (i=0; i<(iMax-1); ++i) {
            AStr_AppendPrint( pStr,
                       "\t%d,\t\t// %d\n",
                       pBuild->pBase[i],
                       i+1
            );
        }
        AStr_AppendPrint( pStr,
                   "\t%d\t\t// %d\n};\n",
                   pBuild->pBase[iMax-1],
                   iMax
        );
        iMax = pBuild->highest;
        AStr_AppendPrint( pStr,
                   "static\nconst\nuint16_t valueTable[%d] = {\n",
                   iMax
        );
        AStr_AppendPrint( pStr,
                 "\t\t\t//     Y\n"
                 );
        for (i=0; i<(iMax-1); ++i) {
            AStr_AppendPrint( pStr,
                       "\t%d,\t\t// %d - %d\n",
                       pBuild->pValue[i],
                       i,
                       pBuild->pCheck[i]
            );
        }
        AStr_AppendPrint( pStr,
                   "\t%d\t\t// %d - %d\n};\n",
                   pBuild->pValue[iMax-1],
                   (iMax-1),
                   pBuild->pCheck[iMax-1]
        );
        if (fSmall) {
            AStr_AppendPrint( pStr,
                     "static\nconst\nuint16_t checkTable[%d] = {\n",
                     iMax
                     );
        }
        else {
            AStr_AppendPrint( pStr,
                     "static\nconst\nuint32_t checkTable[%d] = {\n",
                     iMax
                     );
        }
        AStr_AppendPrint( pStr,
                 "//  Y\n"
                 );
        for (i=0; i<(iMax-1); ++i) {
            AStr_AppendPrint( pStr,
                       "\t%d,\t\t// %d\n",
                       pBuild->pCheck[i],
                       i
            );
        }
        AStr_AppendPrint( pStr,
                   "\t%d\t\t// %d\n};\n",
                   pBuild->pCheck[iMax-1],
                   (iMax-1)
        );
        AStr_AppendA(pStr, "#ifdef XYZZY\n");
        AStr_AppendPrint(pStr,
                   "static\nconst\nuint32_t tableMax = %d;\n",
                   iMax
        );
        AStr_AppendA(pStr, "#endif\n\n\n");

        AStr_AppendPrint(pStr,
                   "uint16_t\t\t%s_Get(uint16_t i, uint16_t j)\n",
                   pPrefix
        );
        AStr_AppendA(pStr, "{\n");
        AStr_AppendA(pStr, "\tuint32_t\t\tbase;\n");
        AStr_AppendA(pStr, "\tuint32_t\t\tindex;\n");
        AStr_AppendPrint(pStr, "\tuint32_t\t\thighest = %d;\n", pBuild->highest);
        AStr_AppendA(pStr, "\tuint16_t\t\tvalue;\n\n");
        AStr_AppendA(pStr, "\tbase = baseTable[i-1];\n");
        AStr_AppendA(pStr,  "\tindex = base + j - 1;\n");
        AStr_AppendA(pStr, "\tif (index >= highest)\n");
        AStr_AppendA(pStr,  "\t\treturn 0;\n");
        AStr_AppendA(pStr, "\tif (checkTable[index] == j)\n");
        AStr_AppendA(pStr, "\t\tvalue = valueTable[index];\n");
        AStr_AppendA(pStr, "\telse\n");
        AStr_AppendA(pStr, "\t\tvalue = 0;\n\n");
        AStr_AppendA(pStr, "\treturn value;\n");
        AStr_AppendA(pStr, "}\n");
        AStr_AppendA(pStr, "\n\n\n\n\n\n");

        U16Matrix_FreeValueCheck(this, pBuild);

        // Return to caller.
        return pStr;
    }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        U16Matrix      *pCopy = U16Matrix_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a U16MATRIX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U16MATRIX_DATA *     U16Matrix_Copy (
        U16MATRIX_DATA       *this
    )
    {
        U16MATRIX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef U16MATRIX_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = U16Matrix_New( );
        if (pOther) {
            eRc = U16Matrix_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            U16Matrix_Dealloc (
        OBJ_ID          objId
    )
    {
        U16MATRIX_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((U16MATRIX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        U16Matrix      *pDeepCopy = U16Matrix_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a U16MATRIX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U16MATRIX_DATA *     U16Matrix_DeepyCopy (
        U16MATRIX_DATA       *this
    )
    {
        U16MATRIX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = U16Matrix_New( );
        if (pOther) {
            eRc = U16Matrix_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         U16Matrix_Disable (
        U16MATRIX_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
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
    ERESULT         U16Matrix_Enable (
        U16MATRIX_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
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

    uint16_t        U16Matrix_Get (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
    )
    {
        uint32_t        offset;
        uint16_t        value = 0;
        uint16_t        *pValue;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        offset = U16Matrix_Index(this, i, j);
        if (-1 == offset) {
            DEBUG_BREAK();
            return 0;
        }
        pValue = array_GetAddrOf((ARRAY_DATA *)this, offset+1);
        if (pValue)
            value = *pValue;

        // Return to caller.
        return value;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U16MATRIX_DATA *   U16Matrix_Init (
        U16MATRIX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(U16MATRIX_DATA);
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
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&U16Matrix_Vtbl);
        JsonIn_RegisterClass(U16Matrix_Class());

        array_setElemSize((ARRAY_DATA *)this, sizeof(int16_t));

#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "U16Matrix::sizeof(U16MATRIX_DATA) = %lu\n", 
                sizeof(U16MATRIX_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(U16MATRIX_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         U16Matrix_IsEnabled (
        U16MATRIX_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
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
    //                      M u l t i p l y
    //---------------------------------------------------------------

    U16MATRIX_DATA * U16Matrix_Multiply(
        U16MATRIX_DATA    *this,
        U16MATRIX_DATA    *pOther
    )
    {
        U16MATRIX_DATA  *pMatrix = OBJ_NIL;
        uint32_t        i;
        uint32_t        j;
        uint32_t        k;
        uint16_t        sum;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( !U16Matrix_Validate(pOther) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (this->n == pOther->m)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pMatrix = U16Matrix_NewWithSizes(this->m, pOther->n);
        if (pMatrix == OBJ_NIL) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        for (i=1; i <= pMatrix->m; ++i) {
            for (j=1; j <= pMatrix->n; ++j) {
                // Compute the inner product.
                sum = 0;
                for (k=1; k<=this->n; ++k) {
                    sum += U16Matrix_Get(this, i, k) * U16Matrix_Get(pOther, k, j);
                }
                U16Matrix_Set(pMatrix, i, j, sum);
            }
        }

        // Return to caller.
        return pMatrix;
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
        void        *pMethod = U16Matrix_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "U16Matrix", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          U16Matrix_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        U16MATRIX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(U16MATRIX_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)U16Matrix_Class();
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
                            return U16Matrix_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return U16Matrix_Enable;
                        }
                        break;

#ifdef  U16MATRIX_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return U16Matrix_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return U16Matrix_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return U16Matrix_ToDebugString;
                        }
#ifdef  U16MATRIX_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return U16Matrix_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == U16Matrix_ToDebugString)
                    return "ToDebugString";
#ifdef  U16MATRIX_JSON_SUPPORT
                if (pData == U16Matrix_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                    S c a l a r  A d d
    //---------------------------------------------------------------

    ERESULT         U16Matrix_ScalarAdd(
        U16MATRIX_DATA    *this,
        uint16_t        value
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        offset;
        uint16_t        *pValue;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=1; i <= this->m; ++i) {
            for (j=1; j <= this->n; ++j) {
                offset = U16Matrix_Index(this, i, j);
                if (-1 == offset)
                    ;
                else {
                    pValue = array_GetAddrOf((ARRAY_DATA *)this, offset+1);
                    if (pValue)
                        *pValue += value;
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                 S c a l a r  M u l t i p l y
    //---------------------------------------------------------------

    ERESULT         U16Matrix_ScalarMultiply(
        U16MATRIX_DATA    *this,
        uint16_t        value
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        offset;
        uint16_t        *pValue;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=1; i <= this->m; ++i) {
            for (j=1; j <= this->n; ++j) {
                offset = U16Matrix_Index(this, i, j);
                if (-1 == offset)
                    ;
                else {
                    pValue = array_GetAddrOf((ARRAY_DATA *)this, offset+1);
                    if (pValue)
                        *pValue *= value;
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------

    ERESULT         U16Matrix_Set (
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j,
        uint16_t        value
    )
    {
        uint32_t        offset;
        uint16_t        *pValue;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        offset = U16Matrix_Index(this, i, j);
        if (-1 == offset) {
            DEBUG_BREAK();
            return ERESULT_INVALID_INDEX;
        }
        pValue = array_GetAddrOf((ARRAY_DATA *)this, offset+1);
        if (pValue)
            *pValue = value;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    ERESULT         U16Matrix_Setup (
        U16MATRIX_DATA  *this,
        uint32_t        m,
        uint32_t        n
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        matrixMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        this->n = n;
        this->m = m;
        this->cElems = n * m;
        matrixMax = ((this->cElems + 1) >> 1) << 1;    // Round up by factor of 2

        if (matrixMax) {
            eRc = array_Expand((ARRAY_DATA *)this, matrixMax);
        }
        eRc = array_Truncate((ARRAY_DATA *)this, matrixMax);
        if (matrixMax) {
            eRc = array_ZeroAll((ARRAY_DATA *)this);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = U16Matrix_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     U16Matrix_ToDebugString (
        U16MATRIX_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        uint32_t        j;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U16Matrix_Validate(this)) {
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
                    "{%p(%s) size=%d retain=%d m=%d n=%d\n",
                    this,
                    pInfo->pClassName,
                    U16Matrix_getSize(this),
                    obj_getRetainCount(this),
                    this->m,
                    this->n
            );

        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent+5, ' ');
        }
        AStr_AppendA(pStr, " ");
        for (i=0; i<(this->m/10); ++i) {
            AStr_AppendA(pStr, "1234567890");
        }
        AStr_AppendA(pStr, "\n");
        for (i=1; i<=this->m; ++i) {
            if (indent) {
                AStr_AppendCharRepeatW32(pStr, indent+3, ' ');
            }
            AStr_AppendPrint(pStr, "%2d |", i );
            for (j=1; j<=(this->n-1); ++j) {
                AStr_AppendPrint(pStr, "%2d, ", U16Matrix_Get(this, i, j) );
            }
            AStr_AppendPrint(pStr,"%2d", U16Matrix_Get(this, i, this->n) );
            AStr_AppendA(pStr, " |\n");
        }

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
    bool            U16Matrix_Validate (
        U16MATRIX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_U16MATRIX))
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


        if (!(obj_getSize(this) >= sizeof(U16MATRIX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                       Z e r o
    //---------------------------------------------------------------

    ERESULT         U16Matrix_Zero(
        U16MATRIX_DATA  *this
    )
    {
        uint32_t        i;
        uint16_t        *pValue;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !U16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=0; i<this->cElems; ++i) {
            pValue = array_GetAddrOf((ARRAY_DATA *)this, i+1);
            if (pValue)
                *pValue = 0;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }




    
#ifdef	__cplusplus
}
#endif


