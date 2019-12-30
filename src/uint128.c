// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   uint128.c
 *	Generated 10/12/2015 19:40:43
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
#include "uint128_internal.h"
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

    UINT128_DATA *     uint128_Alloc(
        uint16_t        stackSize
    )
    {
        UINT128_DATA       *cbp;
        uint32_t        cbSize = sizeof(UINT128_DATA);
        
        // Do initialization.
        
        if (0 == stackSize) {
            stackSize = 256;
        }
        cbSize += stackSize << 2;
        cbp = obj_Alloc( cbSize );
        obj_setMisc1(cbp, stackSize);
        
        // Return to caller.
        return( cbp );
    }



    UINT128_DATA *     uint128_New(
        uint16_t        stackSize
    )
    {
        UINT128_DATA       *cbp;
        
        cbp = uint128_Alloc( stackSize );
        if (cbp) {
            cbp = uint128_Init( cbp );
        } 
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint64_t        uint128_getLower(
        UINT128_DATA    *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        return cbp->lower;
    }

    bool            uint128_setLower(
        UINT128_DATA    *cbp,
        uint64_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        cbp->lower = value;
        return true;
    }



    uint32_t        uint128_getSize(
        UINT128_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return 16;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------
    
    bool            uint128_Add(
        UINT128_DATA    *cbp,
        UINT128_DATA    *pOther
    )
    {
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        cbp->lower += pOther->lower;
        if (cbp->lower < pOther->lower) {
            cbp->upper++;
        }
        cbp->upper += cbp->upper;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            uint128_Dealloc(
        OBJ_ID          objId
    )
    {
        UINT128_DATA    *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
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

    bool            uint128_Disable(
        UINT128_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !uint128_Validate( cbp ) ) {
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
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            uint128_Enable(
        UINT128_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(cbp);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    UINT128_DATA *   uint128_Init(
        UINT128_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (UINT128_DATA *)obj_Init(this, cbSize, OBJ_IDENT_UINT128);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_UINT128);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&uint128_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = ObjArray_New( );

    #ifdef NDEBUG
    #else
        if( !uint128_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            uint128_IsEnabled(
        UINT128_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !uint128_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          uint128_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        UINT128_DATA    *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !uint128_Validate(this) ) {
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
                            return uint128_ToDebugString;
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
    //              S h i f t  L e f t  L o g i c a l
    //---------------------------------------------------------------
    
    bool            uint128_ShiftLeftLogical(
        UINT128_DATA		*cbp
    )
    {
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        cbp->upper <<= 1;
        if (cbp->lower & ((uint64_t)1 << (64 - 1))) {
            cbp->upper |= 1;
        }
        cbp->lower <<= 1;
        
        
        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //              S h i f t  R i g h t  L o g i c a l
    //---------------------------------------------------------------
    
    bool            uint128_ShiftRightLogical(
        UINT128_DATA		*cbp
    )
    {
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        cbp->lower >>= 1;
        if (cbp->upper & 1) {
            cbp->lower |= (uint64_t)1 << (64 - 1);
        }
        cbp->upper >>= 1;
        
        
        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        S u b t r a c t
    //---------------------------------------------------------------
    
    bool            uint128_Subtract(
        UINT128_DATA    *cbp,
        UINT128_DATA    *pOther
    )
    {
        
        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !uint128_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        cbp->upper -= cbp->upper;
        if (cbp->lower < pOther->lower) {
            cbp->upper--;
        }
        cbp->lower -= pOther->lower;
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     uint128_ToDebugString(
        UINT128_DATA    *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(uint128) side=%d ",
                     cbp,
                     uint128_getSize(cbp)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString(
                                                    cbp->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            uint128_Validate(
        UINT128_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_UINT128) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(UINT128_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


