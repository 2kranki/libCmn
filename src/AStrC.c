// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   AStrC.c
 *	Generated 02/19/2016 09:32:40
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
#include "AStrC_internal.h"
#include "utf8.h"
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

    ASTRC_DATA *     AStrC_Alloc(
    )
    {
        ASTRC_DATA      *this;
        uint32_t        cbSize = sizeof(ASTRC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    ASTRC_DATA *    AStrC_New(
    )
    {
        ASTRC_DATA      *this;
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_Init( this );
        } 
        return( this );
    }


    ASTRC_DATA *   AStrC_NewA(
        const
        char            *pStr
                              )
    {
        ASTRC_DATA      *this;
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_InitA( this, pStr );
        }
        return( this );
    }

    
    ASTRC_DATA *   AStrC_NewW(
        const
        int32_t        *pStr
    )
    {
        ASTRC_DATA      *this;
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_InitW( this, pStr );
        }
        return( this );
    }
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    const
    char *          AStrC_getData(
        ASTRC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    

    uint32_t        AStrC_getLength(
        ASTRC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->len;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         AStrC_Compare(
        ASTRC_DATA      *this,
        ASTRC_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !AStrC_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if( OBJ_NIL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        
        i = utf8_StrCmp(
                        this->pArray,
                        pOther->pArray
            );
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStrC_CompareA(
        ASTRC_DATA		*this,
        const
        char            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = utf8_StrCmp(
                this->pArray,
                pData
            );
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStrC_CompareW(
        ASTRC_DATA		*this,
        const
        int32_t         *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = utf8_StrCmpAW(
                this->pArray,
                pData
            );
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrC_Copy(
        ASTRC_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        obj_Retain(this);
        
        // Return to caller.
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            AStrC_Dealloc(
        OBJ_ID          objId
    )
    {
        ASTRC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (obj_IsFlag(this, ASTRC_FLAG_MALLOC)) {
            if (this->pArray) {
                mem_Free((void *)this->pArray);
                this->pArray = NULL;
            }
        }
        else {
            this->pArray = NULL;
        }

        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        AStrC_Hash(
        ASTRC_DATA      *this
    )
    {
        uint32_t        hash = 0;
        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (this->pArray) {
            hash = str_HashAcmA( this->pArray, NULL );
        }
        
        return hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTRC_DATA *   AStrC_Init(
        ASTRC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ASTRC_DATA);
        
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

        this = (ASTRC_DATA *)obj_Init( this, cbSize, OBJ_IDENT_ASTRC );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_ASTRC);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AStrC_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     
    ASTRC_DATA *   AStrC_InitA(
        ASTRC_DATA      *this,
        const
        char            *pStr
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = (ASTRC_DATA *)AStrC_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pArray = utf8_StrDup(pStr);
        if (NULL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->len = utf8_StrLenA(this->pArray);
        obj_FlagOn(this, ASTRC_FLAG_MALLOC);
        
        return this;
    }
    
    
    ASTRC_DATA *    AStrC_InitW(
        ASTRC_DATA      *this,
        const
        int32_t         *pStr
    )
    {
        uint32_t        len;
        uint32_t        lenChars;
        char            *pStr8;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        len = utf8_StrLenW(pStr);
        
        this = (ASTRC_DATA *)AStrC_Init( this );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        lenChars = utf8_WCToUtf8Str( len, pStr, 0, NULL );
        if (lenChars) {
            pStr8 = mem_Malloc(lenChars);
            if (OBJ_NIL == pStr8) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            utf8_WCToUtf8Str( len, pStr, lenChars, pStr8 );
            this->pArray = pStr8;
            this->len = len;
            obj_FlagOn(this, ASTRC_FLAG_MALLOC);
        }
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            AStrC_IsEnabled(
        ASTRC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrC_ToDebugString(
        ASTRC_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
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
                     "{%p(AStrC) len=%d  data=%s ",
                     this,
                     AStrC_getLength(this),
                     this->pArray
            );
        AStr_AppendA(pStr, str);

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
        
        j = snprintf( str, sizeof(str), " %p(AStrC)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            AStrC_Validate(
        ASTRC_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_ASTRC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(ASTRC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


