// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   u32Matrix.c
 *	Generated 08/12/2018 23:54:39
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
#include        <u32Matrix_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    uint32_t        u32Matrix_index(
        U32MATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x
    )
    {
        uint32_t        index;
        
#ifdef NDEBUG
#else
        if ((1 <= y) && (y <= this->ySize)) {
        }
        else {
            DEBUG_BREAK();
            return -1;
        }
        if ((1 <= x) && (x <= this->xSize)) {
        }
        else {
            DEBUG_BREAK();
            return -1;
        }
#endif
        
        index = ((y - 1) * this->xSize) + (x - 1);
        if (index < this->cElems) {
        }
        else {
            DEBUG_BREAK();
            return -1;
        }
        
        // Return to caller.
        return index;
    }
    
    
    
    static
    bool            u32Matrix_addRowToValueCheck(
        U32MATRIX_DATA  *this,
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
        iMax = pBuild->baseMax - this->xSize;   // Start at the last row added
        for( i=0; i < iMax; i++ ) {
            baseNew = i;
            for( j=1; j <= this->xSize; j++ ) {
                value = u32Matrix_Get(this, j, row);
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
        for( j=1; j<=this->ySize; j++ ) {
            value = u32Matrix_Get(this, j, row);
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
    
    
    
    MATRIX_BUILD *  u32Matrix_BuildValueCheck(
        U32MATRIX_DATA  *this
    )
    {
        MATRIX_BUILD    *pBuild = NULL;
        uint32_t        i;
        uint32_t        baseMax;
        
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pBuild = mem_Calloc( 1, sizeof(MATRIX_BUILD) );
        if( NULL == pBuild ) {
            return NULL;
        }
        pBuild->ySize = this->ySize;
        pBuild->xSize = this->xSize;
        baseMax = this->ySize * this->xSize;
        pBuild->baseMax = baseMax;
        pBuild->pBase = (int32_t *)mem_Calloc( this->ySize, sizeof(int32_t) );
        if( NULL == pBuild->pBase ) {
            mem_Free(pBuild);
            return NULL;
        }
        pBuild->pValue  = (uint32_t *)mem_Calloc( baseMax, sizeof(uint32_t) );
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
        for (i=1; i<=this->ySize; ++i) {
            u32Matrix_addRowToValueCheck(this, pBuild, i);
        }
        
        // Return to caller.
        return pBuild;
    }
    
    
    
    ERESULT         u32Matrix_FreeValueCheck(
        U32MATRIX_DATA  *this,
        MATRIX_BUILD    *pBuild
    )
    {
        
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
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

    U32MATRIX_DATA *     u32Matrix_Alloc(
        void
    )
    {
        U32MATRIX_DATA  *this;
        uint32_t        cbSize = sizeof(U32MATRIX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    U32MATRIX_DATA * u32Matrix_New(
        uint32_t        ySize,
        uint32_t        xSize
    )
    {
        U32MATRIX_DATA  *this;
        
        this = u32Matrix_Alloc( );
        if (this) {
            this = u32Matrix_Init(this, xSize, ySize);
        } 
        return this;
    }



    U32MATRIX_DATA * u32Matrix_NewIdentity(
        uint32_t        xSize
    )
    {
        U32MATRIX_DATA  *this;
        uint32_t        i;
        
        this = u32Matrix_NewSquare(xSize);
        if (this) {
            for (i=1; i<=xSize; ++i) {
                u32Matrix_Set(this, i, i, 1);
            }
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    U32MATRIX_DATA * u32Matrix_NewSquare(
        uint32_t        xSize
    )
    {
        U32MATRIX_DATA  *this;
        
        this = u32Matrix_New(xSize, xSize);
        
        // Return to caller.
        return this;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        u32Matrix_getPriority(
        U32MATRIX_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            u32Matrix_setPriority(
        U32MATRIX_DATA  *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        u32Matrix_getSize(
        U32MATRIX_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  u32Matrix_getSuperVtbl(
        U32MATRIX_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          x S i z e
    //---------------------------------------------------------------
    
    uint32_t        u32Matrix_getXSize(
        U32MATRIX_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->xSize;
    }
    
    
    bool            u32Matrix_setXSize(
        U32MATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->xSize = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          y S i z e
    //---------------------------------------------------------------
    
    uint32_t        u32Matrix_getYSize(
        U32MATRIX_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->ySize;
    }
    
    
    bool            u32Matrix_setYSize(
        U32MATRIX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->ySize = value;
        
        return true;
    }
    
    
    


    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A d d
    //---------------------------------------------------------------
    
    ERESULT         u32Matrix_Add(
        U32MATRIX_DATA    *this,
        U32MATRIX_DATA    *pOther
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !u32Matrix_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if( this->cElems == pOther->cElems )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        for (i=0; i<this->cElems; ++i) {
            this->pElems[i] += pOther->pElems[i];
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
        ERESULT eRc = u32Matrix__Assign(this,pOther);
     @endcode 
     @param     this    U32MATRIX object pointer
     @param     pOther  a pointer to another U32MATRIX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         u32Matrix_Assign(
        U32MATRIX_DATA  *this,
        U32MATRIX_DATA  *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !u32Matrix_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

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
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
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
    int             u32Matrix_Compare (
        U32MATRIX_DATA  *this,
        U32MATRIX_DATA  *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!u32Matrix_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!u32Matrix_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
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
        u32Matrix      *pCopy = u32Matrix_Copy(this);
     @endcode 
     @param     this    U32MATRIX object pointer
     @return    If successful, a U32MATRIX object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the U32MATRIX object.
     */
    U32MATRIX_DATA *     u32Matrix_Copy(
        U32MATRIX_DATA       *this
    )
    {
        U32MATRIX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = u32Matrix_New(this->xSize, this->ySize);
        if (pOther) {
            eRc = u32Matrix_Assign(this, pOther);
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

    void            u32Matrix_Dealloc(
        OBJ_ID          objId
    )
    {
        U32MATRIX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((U32MATRIX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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

    ERESULT         u32Matrix_Disable(
        U32MATRIX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !u32Matrix_Validate(this) ) {
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

    ERESULT         u32Matrix_Enable(
        U32MATRIX_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !u32Matrix_Validate(this) ) {
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
    //        G e n e r a t e  C o m p r e s s e d  T a b l e
    //---------------------------------------------------------------
    
    ASTR_DATA *     u32Matrix_CompressedTable(
        U32MATRIX_DATA  *this,
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
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pBuild = u32Matrix_BuildValueCheck(this);
        if( NULL == pBuild ) {
            return OBJ_NIL;
        }
        
        // Check savings.
        sizeMatrix = pBuild->ySize * pBuild->xSize * sizeof(uint32_t);
        if ((pBuild->ySize > (65536-1)) || (pBuild->highest > (65536-1))) {
            fSmall = false;
            sizeBuild  = pBuild->ySize * sizeof(uint32_t);      // Base
            sizeBuild += pBuild->highest * sizeof(uint32_t);    // Check
            sizeBuild += pBuild->highest * sizeof(uint32_t);    // Value
        }
        else {
            sizeBuild  = pBuild->ySize * sizeof(int16_t);           // Base
            sizeBuild += pBuild->highest * sizeof(uint16_t);    // Check
            sizeBuild += pBuild->highest * sizeof(uint16_t);    // Value
        }
        
        pStr = AStr_New();
        if( NULL == pStr ) {
            return OBJ_NIL;
        }
        
        snprintf( str, sizeof(str),
                 "//    ***  Compressed Matrix Table   ***\n\n"
                 );
        AStr_AppendA(pStr, str);
        iMax = this->ySize;
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
        
        u32Matrix_FreeValueCheck(this, pBuild);
        
        // Return to caller.
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    uint32_t        u32Matrix_Get(
        U32MATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x
    )
    {
        uint32_t        offset;
        uint32_t        value;
        //ERESULT         eRc = ERESULT_SUCCESS_FALSE;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((1 <= y) && (y <= this->ySize)) {
        }
        else {
            DEBUG_BREAK();
            return 0;
        }
        if ((1 <= x) && (x <= this->xSize)) {
        }
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        offset = u32Matrix_index(this, x, y);
        value = this->pElems[offset];

        // Return to caller.
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U32MATRIX_DATA *   u32Matrix_Init(
        U32MATRIX_DATA  *this,
        uint32_t        ySize,
        uint32_t        xSize
    )
    {
        uint32_t        cbSize = sizeof(U32MATRIX_DATA);
        uint32_t        cElems = 0;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (0 == xSize) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (0 == ySize) {
            DEBUG_BREAK();
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_U32MATRIX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_U32MATRIX);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&u32Matrix_Vtbl);
        
        cElems = xSize * ySize;
        cElems = ((cElems + 1) >> 1) << 1;    // Round up by factor of 2
        this->pElems = mem_Calloc(cElems, sizeof(uint32_t));
        if (NULL == this->pElems) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->xSize  = xSize;
        this->ySize  = ySize;
        this->cElems = cElems;

        //this->stackSize = obj_getMisc1(this);
        //this->pArray = ObjArray_New( );

    #ifdef NDEBUG
    #else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "u32Matrix::sizeof(U32MATRIX_DATA) = %lu\n", sizeof(U32MATRIX_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(U32MATRIX_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         u32Matrix_IsEnabled(
        U32MATRIX_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
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
    
    U32MATRIX_DATA * u32Matrix_Multiply(
        U32MATRIX_DATA  *this,
        U32MATRIX_DATA  *pOther
    )
    {
        U32MATRIX_DATA  *pMatrix = OBJ_NIL;
        uint32_t        i;
        uint32_t        j;
        uint32_t        k;
        uint16_t        sum;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( !u32Matrix_Validate(pOther) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (this->xSize == pOther->ySize)
            ;
        else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pMatrix = u32Matrix_New(this->ySize, pOther->xSize);
        if (pMatrix == OBJ_NIL) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        for (i=1; i <= pMatrix->ySize; ++i) {
            for (j=1; j <= pMatrix->xSize; ++j) {
                // Compute the inner product.
                sum = 0;
                for (k=1; k<=this->xSize; ++k) {
                    sum += u32Matrix_Get(this, i, k) * u32Matrix_Get(pOther, k, j);
                }
                u32Matrix_Set(pMatrix, i, j, sum);
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
        void        *pMethod = u32Matrix_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "u32Matrix", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          u32Matrix_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        U32MATRIX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)u32Matrix_Class();
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
                            return u32Matrix_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return u32Matrix_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return u32Matrix_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return u32Matrix_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == u32Matrix_ToDebugString)
                    return "ToDebugString";
                if (pData == u32Matrix_ToJSON)
                    return "ToJson";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                    S c a l a r  A d d
    //---------------------------------------------------------------
    
    ERESULT         u32Matrix_ScalarAdd(
        U32MATRIX_DATA  *this,
        uint32_t        value
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=1; i <= this->ySize; ++i) {
            for (j=1; j <= this->xSize; ++j) {
                offset = u32Matrix_index(this, i, j);
                this->pElems[offset] += value;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                 S c a l a r  M u l t i p l y
    //---------------------------------------------------------------
    
    ERESULT         u32Matrix_ScalarMultiply(
        U32MATRIX_DATA  *this,
        uint32_t        value
    )
    {
        uint32_t        i;
        uint32_t        j;
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=1; i <= this->ySize; ++i) {
            for (j=1; j <= this->xSize; ++j) {
                offset = u32Matrix_index(this, i, j);
                this->pElems[offset] *= value;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         u32Matrix_Set(
        U32MATRIX_DATA  *this,
        uint32_t        y,
        uint32_t        x,
        uint16_t        value
    )
    {
        uint32_t        offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((1 <= y) && (y <= this->ySize)) {
        }
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if ((1 <= x) && (x <= this->xSize)) {
        }
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        offset = u32Matrix_index(this, x, y);
        this->pElems[offset] = value;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     u32Matrix_ToJSON(
        U32MATRIX_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
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
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = u32Matrix_ToDebugString(this,4);
     @endcode 
     @param     this    U32MATRIX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     u32Matrix_ToDebugString(
        U32MATRIX_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        int             i;
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
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
        for (i=0; i<(this->xSize / 10); ++i) {
            AStr_AppendA(pStr, "1234567890");
        }
        AStr_AppendA(pStr, "\n");
        for (i=1; i<=this->ySize; ++i) {
            if (indent) {
                AStr_AppendCharRepeatW32(pStr, indent+3, ' ');
            }
            AStr_AppendPrint(pStr, "%2d |", i );
            for (j=1; j<=(this->xSize - 1); ++j) {
                AStr_AppendPrint(pStr, "%5d, ", u32Matrix_Get(this, i, j) );
            }
            AStr_AppendPrint(pStr,"%5d", u32Matrix_Get(this, i, this->xSize) );
            AStr_AppendA(pStr, " |\n");
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            u32Matrix_Validate(
        U32MATRIX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_U32MATRIX) )
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


        if( !(obj_getSize(this) >= sizeof(U32MATRIX_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                       Z e r o
    //---------------------------------------------------------------
    
    ERESULT         u32Matrix_Zero(
        U32MATRIX_DATA *this
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !u32Matrix_Validate(this) ) {
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


