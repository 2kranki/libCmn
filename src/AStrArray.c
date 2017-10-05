// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AStrArray.c
 *	Copied from NodeArray 09/25/2015
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
#include "AStrArray_internal.h"



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

    ASTRARRAY_DATA *     AStrArray_Alloc(
    )
    {
        ASTRARRAY_DATA       *cbp;
        uint32_t        cbSize = sizeof(ASTRARRAY_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    ASTRARRAY_DATA *     AStrArray_New(
    )
    {
        ASTRARRAY_DATA       *cbp;
        
        // Do initialization.
        
        cbp = AStrArray_Alloc( );
        if (cbp) {
            cbp = AStrArray_Init(cbp);
        }
        
        // Return to caller.
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    OBJARRAY_DATA *  AStrArray_getArray(
        ASTRARRAY_DATA  *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pArray;
    }
    
    
    bool            AStrArray_setArray(
        ASTRARRAY_DATA  *cbp,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pArray) {
            obj_Release(cbp->pArray);
        }
        cbp->pArray = pValue;
        
        return true;
    }
    
    
    
    uint32_t        AStrArray_getSize(
        ASTRARRAY_DATA  *cbp
    )
    {
        uint32_t        i = 0;
        
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (cbp->pArray) {
            i = objArray_getSize(cbp->pArray);
        }
        return i;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         AStrArray_AppendStr(
        ASTRARRAY_DATA	*cbp,
        ASTR_DATA       *pObject,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc = objArray_AppendObj(cbp->pArray, pObject, pIndex);
        
        // Return to caller.
        return eRc;
    }

    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            AStrArray_Dealloc(
        OBJ_ID          objId
    )
    {
        ASTRARRAY_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (cbp->pArray) {
            obj_Release(cbp->pArray);
            cbp->pArray = OBJ_NIL;
        }

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrArray_DeleteFirst(
        ASTRARRAY_DATA	*cbp
    )
    {
        ASTR_DATA       *pNode;
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pNode = objArray_DeleteFirst(cbp->pArray);
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTR_DATA *     AStrArray_DeleteLast(
        ASTRARRAY_DATA	*cbp
    )
    {
        ASTR_DATA       *pNode;
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pNode = objArray_DeleteLast(cbp->pArray);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrArray_Get(
        ASTRARRAY_DATA	*cbp,
        uint32_t        index       // Relative to 1
    )
    {
        ASTR_DATA       *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pNode = objArray_Get(cbp->pArray,index);
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTR_DATA *     AStrArray_GetFirst(
        ASTRARRAY_DATA	*cbp
    )
    {
        ASTR_DATA       *pNode;
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pNode = objArray_GetFirst(cbp->pArray);
        
        // Return to caller.
        return pNode;
    }
    
    
    ASTR_DATA *     AStrArray_GetLast(
        ASTRARRAY_DATA	*cbp
    )
    {
        ASTR_DATA       *pNode;
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        pNode = objArray_GetLast(cbp->pArray);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTRARRAY_DATA * AStrArray_Init(
        ASTRARRAY_DATA  *this
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_NODEARRAY );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AStrArray_Vtbl);
        
        //cbp->stackSize = obj_getMisc1(cbp);

    #ifdef NDEBUG
    #else
        if( !AStrArray_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         AStrArray_InsertStr(
        ASTRARRAY_DATA	*this,
        uint32_t        index,
        ASTR_DATA       *pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc = objArray_InsertObj(this->pArray, index, pObject);
        
        // Return to caller.
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------
    
    ERESULT         AStrArray_SortAscending(
        ASTRARRAY_DATA	*cbp
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        eRc = objArray_SortAscending(cbp->pArray, (OBJ_COMPARE)&AStr_Compare);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            AStrArray_Validate(
        ASTRARRAY_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_ASTRARRAY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(ASTRARRAY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


