// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   bitSet.c
 *	Generated 06/21/2015 14:16:25
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
#include "bitSet_internal.h"
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

    BITSET_DATA *   bitSet_Alloc(
        uint16_t        size            // set size (in bits)
    )
    {
        BITSET_DATA     *cbp;
        uint32_t        cbSize = sizeof(BITSET_DATA);
        uint16_t        alloc;
        
        // Do initialization.
        
        if (0 == size) {
            size = 256;
        }
        alloc = ROUNDUP32(size);
        if (alloc < size) {
            return OBJ_NIL;
        }
        cbSize += (alloc / 8);
        cbp = obj_Alloc( cbSize );
        obj_setMisc1(cbp, size);
        obj_setMisc2(cbp, alloc);
        
        // Return to caller.
        return( cbp );
    }



    BITSET_DATA *  bitSet_New(
        uint16_t        size
    )
    {
        BITSET_DATA     *cbp;
        //ERESULT         eRc;
        
        cbp = bitSet_Alloc( size );
        cbp = bitSet_Init(cbp);
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        bitSet_getPriority(
        BITSET_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            bitSet_setPriority(
        BITSET_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint16_t        bitSet_getSize(
        BITSET_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return cbp->xMax;
    }



    uint16_t        bitSet_getSizeUsed(
        BITSET_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return cbp->cElems;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         bitSet_Assign(
        BITSET_DATA		*cbp,
        BITSET_DATA		*pOther
                                     )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->xMax == pOther->xMax )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
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
    //                       C o n t a i n s
    //---------------------------------------------------------------
    
    ERESULT         bitSet_Contains(
        BITSET_DATA		*cbp,
        BITSET_DATA		*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        BITSET_DATA		*pWork;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->xMax == pOther->xMax )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pWork = bitSet_Copy(cbp);
        if (OBJ_NIL == pWork) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = bitSet_Intersect(pWork, pOther);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            eRc = bitSet_IsEqual(pWork,pOther);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    BITSET_DATA *   bitSet_Copy(
        BITSET_DATA		*cbp
    )
    {
        BITSET_DATA     *pOther;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pOther = bitSet_Alloc(cbp->xMax);
        pOther = bitSet_Init(pOther);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        for (i=0; i<cbp->cElems; ++i) {
            pOther->elems[i] = cbp->elems[i];
        }
        
        // Return to caller.
        return( pOther );
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            bitSet_Dealloc(
        OBJ_ID          objId
    )
    {
        BITSET_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          E l e m e n t
    //---------------------------------------------------------------
    
    bool            bitSet_Element(
        BITSET_DATA		*cbp,
        uint16_t        index
    )
    {
        uint32_t        i;
        uint32_t        j;
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return fRc;
        }
        if ((index-1) < cbp->xMax)
            ;
        else {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        
        --index;
        //i = index / 32;			        /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);	    /* horizontal - bit */
        j = (32-1) - (index & 0x1F);
        
        if ( cbp->elems[i] & (1 << j) ) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------

    bool            bitSet_Get(
        BITSET_DATA		*cbp,
        uint16_t        index
    )
    {
        uint32_t        i;
        uint32_t        j;
        bool            fRc = false;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return fRc;
        }
        if ((index-1) < cbp->xMax)
            ;
        else {
            DEBUG_BREAK();
            return fRc;
        }
    #endif
        
        --index;
        //i = index / 32;			        /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);	    /* horizontal - bit */
        j = (32-1) - (index & 0x1F);
        
        if ( cbp->elems[i] & (1 << j) ) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BITSET_DATA *   bitSet_Init(
        BITSET_DATA       *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_BITSET );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&bitSet_Vtbl);
        
        this->xMax = obj_getMisc1(this);
        this->cElems = obj_getMisc2(this) / 32;

    #ifdef NDEBUG
    #else
        if( !bitSet_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I n t e r s e c t
    //---------------------------------------------------------------
    
    ERESULT         bitSet_Intersect(
        BITSET_DATA		*cbp,
        BITSET_DATA		*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->xMax == pOther->xMax )
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
    
    ERESULT         bitSet_Invert(
        BITSET_DATA		*cbp
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        for (i=0; i<cbp->cElems; ++i) {
            cbp->elems[i] = ~cbp->elems[i];
        }

        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                         I s E m p t y
    //---------------------------------------------------------------
    
    ERESULT         bitSet_IsEmpty(
        BITSET_DATA		*cbp
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            if (cbp->elems[i]) {
                return ERESULT_SUCCESS_FALSE;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_TRUE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s  E q u a l
    //---------------------------------------------------------------
    
    ERESULT         bitSet_IsEqual(
        BITSET_DATA		*cbp,
        BITSET_DATA		*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_TRUE;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->xMax == pOther->xMax )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            if (cbp->elems[i] == pOther->elems[i])
                ;
            else {
                eRc = ERESULT_SUCCESS_FALSE;
                break;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         bitSet_Set(
        BITSET_DATA		*cbp,
        uint16_t        index,
        bool            value
    )
    {
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((index-1) < cbp->xMax)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        --index;
        //i = index / 32;			        /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);	    /* horizontal - bit */
        j = (32-1) - (index & 0x1F);
        
        if (value )
            cbp->elems[i] |= (1 << j);
        else
            cbp->elems[i] &= ~(1 << j);
        
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                         S e t  E m p t y
    //---------------------------------------------------------------
    
    ERESULT         bitSet_SetEmpty(
        BITSET_DATA		*cbp
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            cbp->elems[i] = 0;
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       S u b t r a c t
    //---------------------------------------------------------------
    
    ERESULT         bitSet_Subtract(
        BITSET_DATA		*cbp,
        BITSET_DATA		*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->xMax == pOther->xMax )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        for (i=0; i<cbp->cElems; ++i) {
            j = cbp->elems[i];
            cbp->elems[i] &= ~pOther->elems[i];
            if (j != cbp->elems[i]) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     bitSet_ToDataString(
        BITSET_DATA		*this
    )
    {
        char            str[256];
        uint32_t        j;
        uint32_t        jMax;
        ASTR_DATA       *pStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        pStr = AStr_New();
        
        jMax = this->cElems;
        for (j=0; j<jMax-1; ++j) {
            j = snprintf(
                         str,
                         sizeof(str),
                         "\t0x%08X, ",
                         this->elems[j]
                );
            AStr_AppendA(pStr, str);
        }
        j = snprintf(
                     str,
                     sizeof(str),
                     "\t0x%08X",
                     this->elems[jMax-1]
            );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     bitSet_ToDebugString(
        BITSET_DATA		*cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        int             x;
        ASTR_DATA       *pStr;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(bitset) xMax=%d  size=%d\n",
                     cbp,
                     cbp->xMax,
                     cbp->cElems
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendCharRepeatA(pStr, indent+3, ' ');
        AStr_AppendA(pStr, " ");
        for (x=1; x<=cbp->xMax; ++x) {
            AStr_AppendCharRepeatW32(pStr, 1, '0'+(x % 10));
        }
        AStr_AppendA(pStr, "\n");
        AStr_AppendCharRepeatA(pStr, indent+3, ' ');
        AStr_AppendA(pStr, "|");
        for (x=1; x<=cbp->xMax; ++x) {
            if (bitSet_Get(cbp, x)) {
                AStr_AppendA(pStr, "1");
            }
            else {
                AStr_AppendA(pStr, " ");
            }
        }
        AStr_AppendA(pStr, "|\n");
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), " %p(bitset)}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    ASTR_DATA *     bitSet_ToUint32String(
        BITSET_DATA     *this,
        const
        char            *pName
    )
    {
        uint32_t        i;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !bitSet_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( NULL == pName ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        AStr_AppendPrint(
                         pStr,
                         "static\nconst\nuint32_t\t%s[%d] = {\n",
                         pName,
                         this->cElems
        );
        
        for (i=0; i<this->cElems-1; ++i) {
            AStr_AppendPrint(
                             pStr,
                             "\t0x%08X,\n",
                             this->elems[i]
            );
        }
        AStr_AppendPrint(
                         pStr,
                         "\t0x%08X\n};\n",
                         this->elems[this->cElems-1]
        );
        
        // Return to caller.
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U n i o n
    //---------------------------------------------------------------
    
    ERESULT         bitSet_Union(
        BITSET_DATA		*cbp,
        BITSET_DATA		*pOther
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
        if( !bitSet_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !bitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( cbp->xMax == pOther->xMax )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pCbpW = cbp->elems;
        pOtrW = pOther->elems;
        for (i=0; i<cbp->cElems; ++i) {
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
    bool            bitSet_Validate(
        BITSET_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_BITSET) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(BITSET_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


