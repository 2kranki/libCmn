// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objMatrix.c
 *	Generated 10/07/2015 22:21:27
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
#include "objMatrix_internal.h"
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

    OBJMATRIX_DATA * objMatrix_Alloc(
    )
    {
        OBJMATRIX_DATA  *cbp;
        uint32_t        cbSize = sizeof(OBJMATRIX_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    OBJMATRIX_DATA * objMatrix_New(
        uint32_t        n,
        uint32_t        m
    )
    {
        OBJMATRIX_DATA  *cbp;
        
        cbp = objMatrix_Alloc( );
        if (cbp) {
            cbp = objMatrix_Init( cbp, n, m );
        } 
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        objMatrix_getPriority(
        OBJMATRIX_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            objMatrix_setPriority(
        OBJMATRIX_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !objMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        objMatrix_getX(
        OBJMATRIX_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !objMatrix_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->xMax;
    }



    uint32_t        objMatrix_getY(
        OBJMATRIX_DATA  *this
    )
    {
#ifdef NDEBUG
#else
        if( !objMatrix_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->yMax;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         objMatrix_Assign(
        OBJMATRIX_DATA	*cbp,
        OBJMATRIX_DATA	*pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        uint32_t        i;
        OBJ_ID          pObj;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !objMatrix_Validate( pOther ) ) {
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
            pObj = cbp->pElems[i];
            if (pObj) {
                obj_Release(pObj);
            }
            cbp->pElems[i] = obj_Retain(pOther->pElems[i]);
            if (pObj != cbp->pElems[i]) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    OBJMATRIX_DATA * objMatrix_Copy(
        OBJMATRIX_DATA	*cbp
    )
    {
        OBJMATRIX_DATA  *pOther;
        uint32_t        i;
        OBJ_DATA        *pItem;
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objMatrix_Alloc();
        pOther = objMatrix_Init(pOther, cbp->xMax, cbp->yMax);
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        pOther->xMax = cbp->xMax;
        pOther->yMax = cbp->yMax;
        pOther->cElems = cbp->cElems;
        for (i=0; i<cbp->cElems; ++i) {
            pItem = cbp->pElems[i];
            pVtbl = obj_getVtbl(pItem);
            if (pVtbl->pCopy) {
                pItem = pVtbl->pCopy(pItem);
            }
            else {
                obj_Retain(pItem);
            }
            pOther->pElems[i] = pItem;
        }
        
        // Return to caller.
        return( pOther );
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objMatrix_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJMATRIX_DATA  *cbp = objId;
        uint32_t        i;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !objMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (cbp->pElems) {
            for (i=0; i<cbp->cElems; ++i) {
                if (cbp->pElems[i]) {
                    obj_Release(cbp->pElems[i]);
                    cbp->pElems[i] = OBJ_NIL;
                }
            }
            mem_Free(cbp->pElems);
            cbp->pElems = NULL;
            cbp->cElems = 0;
        }
        

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          G e t
    //---------------------------------------------------------------
    
    OBJ_ID          objMatrix_Get(
        OBJMATRIX_DATA	*cbp,
        uint32_t        x,
        uint32_t        y
    )
    {
        uint32_t        i;
        OBJ_ID          value;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
        if ((x > 0) && (x <= cbp->xMax))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
        if ((y > 0) && (y <= cbp->yMax))
            ;
        else {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        i = ((x- 1) * cbp->yMax) + (y - 1);
        value = cbp->pElems[i];
        
        // Return to caller.
        return value;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJMATRIX_DATA * objMatrix_Init(
        OBJMATRIX_DATA  *cbp,
        uint32_t        x,
        uint32_t        y
    )
    {
        uint32_t        cbSize;
        uint64_t        matrixMax = 0;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(cbp);
        cbp = (OBJMATRIX_DATA *)obj_Init( cbp, cbSize, OBJ_IDENT_OBJMATRIX );
        if (OBJ_NIL == cbp) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_OBJMATRIX);
        obj_setVtbl(cbp, &objMatrix_Vtbl);
        
        cbp->xMax = x;
        cbp->yMax = y;
        matrixMax = x * y;
        if (matrixMax > (UINT32_MAX - 1)) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        cbp->cElems = matrixMax;
        cbp->pElems = mem_Calloc(matrixMax, sizeof(OBJ_ID));
        if (NULL == cbp->pElems) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !objMatrix_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return cbp;
    }

     

    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         objMatrix_Set(
        OBJMATRIX_DATA  *cbp,
        uint32_t        x,
        uint32_t        y,
        OBJ_ID          pValue
    )
    {
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objMatrix_Validate( cbp ) ) {
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
        
        i = ((x- 1) * cbp->yMax) + (y - 1);
        obj_Retain(pValue);
        if (cbp->pElems[i]) {
            obj_Release(cbp->pElems[i]);
        }
        cbp->pElems[i] = pValue;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     objMatrix_ToDebugString(
        OBJMATRIX_DATA  *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        int             x;
        int             y;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pStrWrk;
        OBJ_ID          pObj;
        
        if (OBJ_NIL == cbp) {
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
                     "{%p(objMatrix) x=%d y=%d ",
                     cbp,
                     cbp->xMax,
                     cbp->yMax
            );
        AStr_AppendA(pStr, str);

        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent+5, ' ');
        }
        AStr_AppendA(pStr, " ");
        for (x=0; x<(cbp->xMax/10); ++x) {
            AStr_AppendA(pStr, "1234567890");
        }
        AStr_AppendA(pStr, "\n");
        for (x=1; x<=cbp->xMax; ++x) {
            if (indent) {
                AStr_AppendCharRepeatW(pStr, indent+3, ' ');
            }
            j = snprintf( str, sizeof(str), "%2d |", x );
            AStr_AppendA(pStr, str);
            for (y=1; y<=(cbp->yMax-1); ++y) {
                pObj = objMatrix_Get(cbp, x, y);
                pStrWrk = obj_ToDebugString(pObj, 0);
                AStr_Append(pStr, pStrWrk);
                obj_Release(pStrWrk);
            }
            pObj = objMatrix_Get(cbp, x, y);
            pStrWrk = obj_ToDebugString(pObj, 0);
            AStr_Append(pStr, pStrWrk);
            obj_Release(pStrWrk);
            AStr_AppendA(pStr, " |\n");
        }
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objMatrix_Validate(
        OBJMATRIX_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_OBJMATRIX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(OBJMATRIX_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


