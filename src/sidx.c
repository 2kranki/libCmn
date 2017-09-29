// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   sidx.c
 *	Generated 09/07/2015 14:04:21
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
#include "sidx_internal.h"
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

    SIDX_DATA *     sidx_Alloc(
        uint16_t        tableSize
    )
    {
        SIDX_DATA       *this;
        uint32_t        cbSize = sizeof(SIDX_DATA);
        
        // Do initialization.
        
        if (0 == tableSize) {
            tableSize = 256;
        }
        tableSize = ROUNDUP2(tableSize);
        cbSize += (tableSize * sizeof(SIDX_ENTRY));
        if (cbSize >= (64 * 1024)) {
            return OBJ_NIL;
        }
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, tableSize);
        
        // Return to caller.
        return this;
    }



    SIDX_DATA *     sidx_New(
        uint16_t        tableSize
    )
    {
        SIDX_DATA       *this;
        
        this = sidx_Alloc( tableSize );
        if (this) {
            this = sidx_Init( this, 0 );
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        sidx_getInterval(
        SIDX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !sidx_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->interval;
    }
    
    
    
    uint16_t        sidx_getSize(
        SIDX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !sidx_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->size;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        A d d  I n d e x
    //---------------------------------------------------------------
    
    bool            sidx_AddIndex(
        SIDX_DATA       *cbp,
        uint32_t        index,
        size_t          offset
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        //uint32_t        j;
        SIDX_ENTRY      *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !sidx_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (0 == cbp->used) {
            if ( (index % cbp->interval) == 0 ) {
                pEntry = &cbp->elems[cbp->used++];
                pEntry->index = index;
                pEntry->offset = offset;
                cbp->max = index;
            }
        }
        else {
            if ((index > cbp->max) && ((index % cbp->interval) == 0)) {
                if (cbp->size == cbp->used) {
                    // Remove every other entry and double interval.
                    iMax = cbp->size >> 1;
                    for (i=0; i<iMax; ++i) {
                        cbp->elems[i] = cbp->elems[i*2];
                    }
                    cbp->used = cbp->used >> 1;
                    cbp->interval = cbp->interval << 1;
                }
                pEntry = &cbp->elems[cbp->used++];
                pEntry->index = index;
                pEntry->offset = offset;
                cbp->max = index;
            }
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            sidx_Dealloc(
        OBJ_ID          objId
    )
    {
        SIDX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !sidx_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      F i n d  I n d e x
    //---------------------------------------------------------------

    bool            sidx_FindIndex(
        SIDX_DATA		*this,
        uint32_t        index,
        uint32_t        *pIndex,
        size_t          *pOffset
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        //uint32_t        j;
        SIDX_ENTRY      *pEntry = NULL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !sidx_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        if (pIndex) {
            *pIndex = 0;
        }
        if (pOffset) {
            *pOffset = 0;
        }
        
        iMax = this->used;
        if (iMax) {
            for (i=0; i<iMax; ++i) {
                pEntry = &this->elems[i];
                if (index < pEntry->index)
                    break;
            }
            if (i) {
                pEntry = &this->elems[i-1];
            }
        }
        else
            return false;
        
        // Return to caller.
        if (pEntry) {
            if (pIndex) {
                *pIndex = pEntry->index;
            }
            if (pOffset) {
                *pOffset = pEntry->offset;
            }
        }
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SIDX_DATA *     sidx_Init(
        SIDX_DATA       *this,
        uint32_t        interval
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_SIDX );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&sidx_Vtbl);
        
        if (interval == 0) {
            interval = 5;
        }
        this->interval = interval;
        this->size = obj_getMisc1(this);

    #ifdef NDEBUG
    #else
        if( !sidx_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(this->elems);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     sidx_ToDebugString(
        SIDX_DATA       *this,
        int             indent
    )
    {
        char            str[256];
        int             i;
        //int             iMax;
        int             j;
        ASTR_DATA       *pStr;
        SIDX_ENTRY      *pEntry;
        
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
                     "{%p(sidx) int=%d size=%d used=%d  ",
                     this,
                     this->interval,
                     this->size,
                     this->used
            );
        AStr_AppendA(pStr, str);

        for (i=0; i<(this->used - 1); ++i) {
            pEntry = &this->elems[i];
            j = snprintf(
                         str,
                         sizeof(str),
                         "[%d,%zu], ",
                         pEntry->index,
                         pEntry->offset
                );
            AStr_AppendA(pStr, str);
        }
        pEntry = &this->elems[i];
        j = snprintf(
                     str,
                     sizeof(str),
                     "[%d,%zu] ",
                     pEntry->index,
                     pEntry->offset
                     );
        AStr_AppendA(pStr, str);
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            sidx_Validate(
        SIDX_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SIDX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(SIDX_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


