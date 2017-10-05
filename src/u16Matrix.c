// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   u16Matrix.c
 *	Generated 07/30/2015 11:30:14
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
#include "u16Matrix_internal.h"
#include "fbso.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    uint32_t        u16Matrix_index(
        U16MATRIX_DATA  *this,
        uint32_t        i,
        uint32_t        j
    )
    {
        uint32_t        index;

#ifdef NDEBUG
#else
#ifdef ALREADY_DONE
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        if ((1 <= i) && (i <= this->m)) {
        }
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_OUT_OF_RANGE;
            return -1;
        }
        if ((1 <= j) && (j <= this->n)) {
        }
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_OUT_OF_RANGE;
            return -1;
        }
#endif
        
        index = ((i - 1) * this->n) + (j - 1);
        if (index < this->cElems) {
        }
        else {
            DEBUG_BREAK();
            this->eRc = ERESULT_OUT_OF_RANGE;
            return -1;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return index;
    }
    
    
    
    
    static
    bool            u16Matrix_addRowToValueCheck(
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
        int32_t         baseNew = 0;		/* new base for value/check */
        
        /*
         * Now search the value table for a base such that the non-
         * zero entries of the row fit into zero entries of the value
         * table.
         */
        iMax = pBuild->baseMax - this->n;   // Start at the last row added
        for( i=0; i < iMax; i++ ) {
            baseNew = i;
            for( j=1; j <= this->n; j++ ) {
                value = u16Matrix_Get(this, row, j);
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
            value = u16Matrix_Get(this, row, j);
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
    
    
    
    MATRIX_BUILD *  u16Matrix_BuildValueCheck(
        U16MATRIX_DATA  *this
    )
    {
        MATRIX_BUILD    *pBuild = NULL;
        uint32_t        i;
        uint32_t        baseMax;
        
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pBuild = mem_Calloc( 1, sizeof(MATRIX_BUILD) );
        if( NULL == pBuild ) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return NULL;
        }
        pBuild->m = this->m;
        pBuild->n = this->n;
        baseMax = this->m * this->n;
        pBuild->baseMax = baseMax;
        pBuild->pBase = (int32_t *)mem_Calloc( this->m, sizeof(int32_t) );
        if( NULL == pBuild->pBase ) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            mem_Free(pBuild);
            return NULL;
        }
        pBuild->pValue  = (uint16_t *)mem_Calloc( baseMax, sizeof(uint16_t) );
        if( NULL == pBuild->pValue ) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            mem_Free(pBuild->pBase);
            mem_Free(pBuild);
            return NULL;
        }
        pBuild->pCheck  = (uint32_t *)mem_Calloc( baseMax, sizeof(uint32_t) );
        if( NULL == pBuild->pCheck ) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            mem_Free(pBuild->pValue);
            mem_Free(pBuild->pBase);
            mem_Free(pBuild);
            return NULL;
        }
        
        // Build the compressed table adding each row.
        for (i=1; i<=this->m; ++i) {
            u16Matrix_addRowToValueCheck( this, pBuild, i );
        }
        
        // Return to caller.
        return pBuild;
    }
    
    
    
    ERESULT         u16Matrix_FreeValueCheck(
        U16MATRIX_DATA  *this,
        MATRIX_BUILD    *pBuild
    )
    {
        
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
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

        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    U16MATRIX_DATA * u16Matrix_Alloc(
    )
    {
        U16MATRIX_DATA  *this;
        uint32_t        cbSize = sizeof(U16MATRIX_DATA);
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }


    
    U16MATRIX_DATA * u16Matrix_New(
        uint32_t        m,
        uint32_t        n
    )
    {
        U16MATRIX_DATA  *this;
        
        this = u16Matrix_Alloc( );
        this = u16Matrix_Init(this, m, n);
       
        // Return to caller.
        return this;
    }
    
    
    
    U16MATRIX_DATA * u16Matrix_NewIdentity(
        uint32_t        n
    )
    {
        U16MATRIX_DATA  *this;
        uint32_t        i;
        
        this = u16Matrix_Alloc( );
        this = u16Matrix_Init(this, n, n);
        if (this) {
            for (i=1; i<=n; ++i) {
                u16Matrix_Set(this, i, i, 1);
            }
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    U16MATRIX_DATA * u16Matrix_NewSquare(
        uint32_t        n
    )
    {
        U16MATRIX_DATA  *this;
        
        this = u16Matrix_Alloc( );
        this = u16Matrix_Init(this, n, n);
        
        // Return to caller.
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         u16Matrix_getLastError(
        U16MATRIX_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        return this->eRc;
    }
    
    
    bool            u16Matrix_setLastError(
        U16MATRIX_DATA  *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    uint32_t        u16Matrix_getM(
        U16MATRIX_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->m;
    }
    
    
    
    uint32_t        u16Matrix_getN(
        U16MATRIX_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->n;
    }
    
    
    
    uint32_t        u16Matrix_getSize(
        U16MATRIX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->cElems;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A d d
    //---------------------------------------------------------------
    
    ERESULT         u16Matrix_Add(
        U16MATRIX_DATA	*this,
        U16MATRIX_DATA	*pOther
    )
    {
        uint32_t        i;
        
        // Do initialization.
        u16Matrix_setLastError(this, ERESULT_SUCCESS);
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !u16Matrix_Validate(pOther) ) {
            DEBUG_BREAK();
            u16Matrix_setLastError(this, ERESULT_INVALID_OBJECT);
            return this->eRc;
        }
        if( this->cElems == pOther->cElems )
            ;
        else {
            DEBUG_BREAK();
            u16Matrix_setLastError(this, ERESULT_INVALID_PARAMETER);
            return this->eRc;
        }
#endif
        
        for (i=0; i<this->cElems; ++i) {
            this->pElems[i] += pOther->pElems[i];
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         u16Matrix_Assign(
        U16MATRIX_DATA	*this,
        U16MATRIX_DATA	*pOther
    )
    {
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
        u16Matrix_setLastError(this, ERESULT_SUCCESS);
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
        if( !u16Matrix_Validate(pOther) ) {
            DEBUG_BREAK();
            u16Matrix_setLastError(this, ERESULT_INVALID_OBJECT);
            return this->eRc;
        }
        if( this->cElems == pOther->cElems )
            ;
        else {
            DEBUG_BREAK();
            u16Matrix_setLastError(this, ERESULT_INVALID_PARAMETER);
            return this->eRc;
        }
#endif
        
        this->m = pOther->m;
        this->n = pOther->n;
        
        for (i=0; i<this->cElems; ++i) {
            j = this->pElems[i];
            this->pElems[i] = pOther->pElems[i];
            if (j != this->pElems[i]) {
                u16Matrix_setLastError(this, ERESULT_SUCCESS_DATA_CHANGED);
            }
        }
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    U16MATRIX_DATA *   u16Matrix_Copy(
        U16MATRIX_DATA		*this
    )
    {
        U16MATRIX_DATA  *pOther;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = u16Matrix_Alloc();
        pOther = u16Matrix_Init(pOther, this->m, this->n);
        if (OBJ_NIL == pOther) {
            u16Matrix_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        pOther->m = this->m;
        pOther->n = this->n;
        pOther->cElems = this->cElems;
        for (i=0; i<this->cElems; ++i) {
            pOther->pElems[i] = this->pElems[i];
        }
        
        // Return to caller.
        u16Matrix_setLastError(this, ERESULT_SUCCESS);
        return( pOther );
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            u16Matrix_Dealloc(
        OBJ_ID          objId
    )
    {
        U16MATRIX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pElems) {
            mem_Free(this->pElems);
            this->pElems = NULL;
            this->cElems = 0;
            this->m = 0;
            this->n = 0;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //        G e n e r a t e  C o m p r e s s e d  T a b l e
    //---------------------------------------------------------------
    
    ASTR_DATA *     u16Matrix_CompressedTable(
        U16MATRIX_DATA  *this,
        const
        char            *pPrefix
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        MATRIX_BUILD    *pBuild = NULL;
        ASTR_DATA       *pStr = OBJ_NIL;
        char            str[128];
        uint32_t        sizeMatrix;
        uint32_t        sizeBuild;
        bool            fSmall = true;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pBuild = u16Matrix_BuildValueCheck(this);
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
        if (sizeMatrix > sizeBuild) {
            u16Matrix_setLastError(this, ERESULT_SUCCESS);
        }
        else {
            u16Matrix_setLastError(this, ERESULT_OUT_OF_RANGE);
        }
        
        pStr = AStr_New();
        if( NULL == pStr ) {
            u16Matrix_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        snprintf( str, sizeof(str),
                 "//    ***  Compressed Matrix Table   ***\n\n"
        );
        AStr_AppendA(pStr, str);
        iMax = this->m;
        if (fSmall) {
            snprintf( str, sizeof(str),
                     "static\nconst\nuint16_t baseTable[%d] = {\n",
                     iMax
            );
        }
        else {
            snprintf( str, sizeof(str),
                     "static\nconst\nuint32_t baseTable[%d] = {\n",
                     iMax
                     );
        }
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                 "\t\t\t// X\n"
                 );
        AStr_AppendA(pStr, str);
        for (i=0; i<(iMax-1); ++i) {
            snprintf( str, sizeof(str),
                       "\t%d,\t\t// %d\n",
                       pBuild->pBase[i],
                       i+1
            );
            AStr_AppendA(pStr, str);
        }
        snprintf( str, sizeof(str),
                   "\t%d\t\t// %d\n};\n",
                   pBuild->pBase[iMax-1],
                   iMax
        );
        AStr_AppendA(pStr, str);
        iMax = pBuild->highest;
        snprintf( str, sizeof(str),
                   "static\nconst\nuint16_t valueTable[%d] = {\n",
                   iMax
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                 "\t\t\t//     Y\n"
                 );
        AStr_AppendA(pStr, str);
        for (i=0; i<(iMax-1); ++i) {
            snprintf( str, sizeof(str),
                       "\t%d,\t\t// %d - %d\n",
                       pBuild->pValue[i],
                       i,
                       pBuild->pCheck[i]
            );
            AStr_AppendA(pStr, str);
        }
        snprintf( str, sizeof(str),
                   "\t%d\t\t// %d - %d\n};\n",
                   pBuild->pValue[iMax-1],
                   (iMax-1),
                   pBuild->pCheck[iMax-1]
        );
        AStr_AppendA(pStr, str);
        if (fSmall) {
            snprintf( str, sizeof(str),
                     "static\nconst\nuint16_t checkTable[%d] = {\n",
                     iMax
                     );
        }
        else {
            snprintf( str, sizeof(str),
                     "static\nconst\nuint32_t checkTable[%d] = {\n",
                     iMax
                     );
        }
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                 "//  Y\n"
                 );
        AStr_AppendA(pStr, str);
        for (i=0; i<(iMax-1); ++i) {
            snprintf( str, sizeof(str),
                       "\t%d,\t\t// %d\n",
                       pBuild->pCheck[i],
                       i
            );
            AStr_AppendA(pStr, str);
        }
        snprintf( str, sizeof(str),
                   "\t%d\t\t// %d\n};\n",
                   pBuild->pCheck[iMax-1],
                   (iMax-1)
        );
        AStr_AppendA(pStr, str);
        AStr_AppendA(pStr, "#ifdef XYZZY\n");
        snprintf( str, sizeof(str),
                   "static\nconst\nuint32_t tableMax = %d;\n",
                   iMax
        );
        AStr_AppendA(pStr, str);
        AStr_AppendA(pStr, "#endif");
        snprintf( str, sizeof(str),
                   "\n\n\n"
        );
        AStr_AppendA(pStr, str);
        
        snprintf( str, sizeof(str),
                   "uint16_t\t\t%s_Get(uint16_t i, uint16_t j)\n",
                   pPrefix
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "{\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\tuint32_t\t\tbase;\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\tuint32_t\t\tindex;\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                 "\tuint32_t\t\thighest = %d;\n",
                 pBuild->highest
                 );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\tuint16_t\t\tvalue;\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\tbase = baseTable[i-1];\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\tindex = base + j - 1;\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                 "\tif (index >= highest)\n"
                 );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                 "\t\treturn 0;\n"
                 );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\tif (checkTable[index] == j)\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\t\tvalue = valueTable[index];\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\telse\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\t\tvalue = 0;\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\treturn value;\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "}\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\n\n\n"
        );
        AStr_AppendA(pStr, str);
        snprintf( str, sizeof(str),
                   "\n\n\n"
        );
        AStr_AppendA(pStr, str);
        
        u16Matrix_FreeValueCheck(this, pBuild);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    uint16_t        u16Matrix_Get(
        U16MATRIX_DATA	*this,
        uint32_t        i,
        uint32_t        j
    )
    {
        uint32_t        offset;
        uint16_t        value;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        offset = u16Matrix_index(this, i, j);
        if (ERESULT_FAILED(this->eRc)) {
            DEBUG_BREAK();
            return 0;
        }
        value = this->pElems[offset];
        
        // Return to caller.
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U16MATRIX_DATA *    u16Matrix_Init(
        U16MATRIX_DATA      *this,
        uint32_t            m,              // Height (Number of Rows, j)
        uint32_t            n               // Width (Number of Columns, i)
    )
    {
        uint32_t            matrixMax = 0;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (0 == n) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (0 == m) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_U16MATRIX );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&u16Matrix_Vtbl);
        
        this->n = n;
        this->m = m;
        matrixMax = n * m;
        matrixMax = ((matrixMax + 1) >> 1) << 1;    // Round up by factor of 2
        this->cElems = matrixMax;
        this->pElems = mem_Calloc(matrixMax, sizeof(uint16_t));
        if (NULL == this->pElems) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      M u l t i p l y
    //---------------------------------------------------------------
    
    U16MATRIX_DATA * u16Matrix_Multiply(
        U16MATRIX_DATA	*this,
        U16MATRIX_DATA	*pOther
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
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( !u16Matrix_Validate(pOther) ) {
            DEBUG_BREAK();
            u16Matrix_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
        if (this->n == pOther->m)
            ;
        else {
            DEBUG_BREAK();
            u16Matrix_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
#endif
        
        pMatrix = u16Matrix_New(this->m, pOther->n);
        if (pMatrix == OBJ_NIL) {
            DEBUG_BREAK();
            u16Matrix_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        for (i=1; i <= pMatrix->m; ++i) {
            for (j=1; j <= pMatrix->n; ++j) {
                // Compute the inner product.
                sum = 0;
                for (k=1; k<=this->n; ++k) {
                    sum += u16Matrix_Get(this, i, k) * u16Matrix_Get(pOther, k, j);
                }
                u16Matrix_Set(pMatrix, i, j, sum);
            }
        }
        
        // Return to caller.
        u16Matrix_setLastError(this, ERESULT_SUCCESS);
        return pMatrix;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          u16Matrix_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        const
        char            *pStr
    )
    {
        U16MATRIX_DATA  *this = objId;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
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
                            return u16Matrix_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pStr);
    }
    
    
    
    //---------------------------------------------------------------
    //                    S c a l a r  A d d
    //---------------------------------------------------------------
    
    ERESULT         u16Matrix_ScalarAdd(
        U16MATRIX_DATA	*this,
        uint16_t        value
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=1; i <= this->m; ++i) {
            for (j=1; j <= this->n; ++j) {
                offset = u16Matrix_index(this, i, j);
                this->pElems[offset] += value;
            }
        }
        
        // Return to caller.
        u16Matrix_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                 S c a l a r  M u l t i p l y
    //---------------------------------------------------------------
    
    ERESULT         u16Matrix_ScalarMultiply(
        U16MATRIX_DATA	*this,
        uint16_t        value
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        for (i=1; i <= this->m; ++i) {
            for (j=1; j <= this->n; ++j) {
                offset = u16Matrix_index(this, i, j);
                this->pElems[offset] *= value;
            }
        }
        
        // Return to caller.
        u16Matrix_setLastError(this, ERESULT_SUCCESS);
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         u16Matrix_Set(
        U16MATRIX_DATA	*this,
        uint32_t        i,
        uint32_t        j,
        uint16_t        value
    )
    {
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        offset = u16Matrix_index(this, i, j);
        if (ERESULT_FAILED(this->eRc)) {
            DEBUG_BREAK();
            return this->eRc;
        }
        this->pElems[offset] = value;
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     u16Matrix_ToDebugString(
        U16MATRIX_DATA	*this,
        int             indent
    )
    {
        char            str[256];
        uint32_t        i;
        uint32_t        j;
        uint32_t        k;
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
                     "{%p(u16Matrix) m=%d n=%d size=%d\n",
                     this,
                     this->m,
                     this->n,
                     this->cElems
                     );
        AStr_AppendA(pStr, str);
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent+5, ' ');
        }
        AStr_AppendA(pStr, " ");
        for (i=0; i<(this->m/10); ++i) {
            AStr_AppendA(pStr, "1234567890");
        }
        AStr_AppendA(pStr, "\n");
        for (i=1; i<=this->m; ++i) {
            if (indent) {
                AStr_AppendCharRepeatW(pStr, indent+3, ' ');
            }
            j = snprintf( str, sizeof(str), "%2d |", i );
            AStr_AppendA(pStr, str);
            for (j=1; j<=(this->n-1); ++j) {
                k = snprintf( str, sizeof(str), "%2d, ", u16Matrix_Get(this, i, j) );
                AStr_AppendA(pStr, str);
            }
            k = snprintf( str, sizeof(str), "%2d", u16Matrix_Get(this, i, this->n) );
            AStr_AppendA(pStr, str);
            AStr_AppendA(pStr, " |\n");
        }
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            u16Matrix_Validate(
        U16MATRIX_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_U16MATRIX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(U16MATRIX_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                       Z e r o
    //---------------------------------------------------------------
    
    ERESULT         u16Matrix_Zero(
        U16MATRIX_DATA	*this
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u16Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        for (i=0; i<this->cElems; ++i) {
            this->pElems[i] = 0;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


