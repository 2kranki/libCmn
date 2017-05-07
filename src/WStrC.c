// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   WStrC.c
 *	Generated 02/19/2016 09:34:06
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
#include "WStrC_internal.h"
#include "utf8.h"
#include "WStr.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                        C o p y  D a t a
    //---------------------------------------------------------------
    
    bool            WStrC_CopyData(
        WSTRC_DATA      *this,
        int32_t         *pData,
        uint32_t        len
    )
    {
        int32_t         *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        if (len == 0) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Create the new string from this one.
        pArray = mem_Malloc((len + 1) * sizeof(int32_t));
        if (NULL == pArray) {
            DEBUG_BREAK();
            return false;
        }
        memmove(pArray, pData, (len * sizeof(int32_t)));
        pArray[len] = 0;
        this->pArray = pArray;
        this->len = len;
        
        
        
        // Return to caller.
        return true;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    WSTRC_DATA *    WStrC_Alloc(
    )
    {
        WSTRC_DATA      *this;
        uint32_t        cbSize = sizeof(WSTRC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    WSTRC_DATA *     WStrC_New(
    )
    {
        WSTRC_DATA       *this;
        
        this = WStrC_Alloc( );
        if (this) {
            this = WStrC_Init( this );
        } 
        return( this );
    }


    WSTRC_DATA *     WStrC_NewA(
        const
        char            *pStr
    )
    {
        WSTRC_DATA      *this;
        
        this = WStrC_Alloc( );
        if (this) {
            this = WStrC_InitA( this, pStr );
        }
        return( this );
    }
    
    
    WSTRC_DATA *     WStrC_NewConW(
        const
        int32_t          *pStr
    )
    {
        WSTRC_DATA       *this;
        
        this = WStrC_Alloc( );
        if (this) {
            this = WStrC_InitConW( this, pStr );
        }
        return( this );
    }
    
    
    WSTRC_DATA *    WStrC_NewFromStrW(
        WSTR_DATA       *pStr
    )
    {
        WSTRC_DATA      *this;
        
        this = WStrC_Alloc( );
        if (this) {
            this = WStrC_InitW(this, WStr_getData(pStr));
        }
        return( this );
    }
    
    
    WSTRC_DATA *     WStrC_NewW(
        const
        int32_t          *pStr
    )
    {
        WSTRC_DATA       *this;
        
        this = WStrC_Alloc( );
        if (this) {
            this = WStrC_InitW( this, pStr );
        }
        return( this );
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    const
    int32_t *       WStrC_getData(
        WSTRC_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    uint32_t        WStrC_getLength(
        WSTRC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
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
    
    ERESULT         WStrC_Compare(
        WSTRC_DATA		*this,
        WSTRC_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !WStrC_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if( OBJ_NIL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        
        eRc = WStr_Cmp(this->pArray,pOther->pArray);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         WStrC_CompareA(
        WSTRC_DATA		*this,
        const
        char            *pString
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        const
        int32_t         *pStr1;
        uint32_t        chr2;
        int             i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pString) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pStr1 = this->pArray;
        for( ;; ) {
            chr2 = utf8_Utf8ToWC_Scan(&pString);
            if( *pStr1 )
                ;
            else {
                if( chr2 )
                    eRc = ERESULT_SUCCESS_LESS_THAN;
                break;
            }
            if( chr2 )
                ;
            else {
                if( *pStr1 )
                    eRc = ERESULT_SUCCESS_GREATER_THAN;
                break;
            }
            i = *pStr1 - chr2;
            if( i ) {
                if( i < 0 )
                    eRc = ERESULT_SUCCESS_LESS_THAN;
                else
                    eRc = ERESULT_SUCCESS_GREATER_THAN;
                break;
            }
            ++pStr1;
        }
        
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         WStrC_CompareW(
        WSTRC_DATA		*this,
        const
        int32_t         *pString
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = WStr_Cmp(this->pArray,pString);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    WSTRC_DATA *    WStrC_Copy(
        WSTRC_DATA     *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        obj_Retain(this);
        
        // Return to caller.
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C S t r i n g A
    //---------------------------------------------------------------
    
    char *          WStrC_CStringA(
        WSTRC_DATA		*this
    )
    {
        char            *pszStr;
        uint32_t        lenStr;
        uint32_t        lenA;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        lenStr = WStrC_getLength(this);
        
        lenA =  utf8_WCToUtf8Str(
                    lenStr,
                    this->pArray,
                    0,
                    NULL
                );
        pszStr = (char *)mem_Malloc(lenA);
        if (pszStr) {
            i =     utf8_WCToUtf8Str(
                                     lenStr,
                                     this->pArray,
                                     lenA,
                                     pszStr
                                     );
            if (i<lenA) {
            }
            else {
                mem_Free(pszStr);
                return NULL;
            }
        }
        
        // Return to caller.
        return pszStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            WStrC_Dealloc(
        OBJ_ID          objId
    )
    {
        WSTRC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (obj_IsFlag(this, WSTRC_FLAG_MALLOC)) {
            if (this->pArray) {
                mem_Free((void *)this->pArray);
                this->pArray = NULL;
            }
        }
        else {
            this->pArray = NULL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        WStrC_Hash(
        WSTRC_DATA      *this
    )
    {
        uint32_t        hash = 0;
        const
        int32_t         *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pStr = this->pArray;
        if (pStr) {
            hash = str_HashW( pStr, NULL );
        }
        
        return hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    WSTRC_DATA *    WStrC_Init(
        WSTRC_DATA      *this
    )
    {
        uint32_t        cbSize = sizeof(WSTRC_DATA);
        
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

        this = (WSTRC_DATA *)obj_Init( this, cbSize, OBJ_IDENT_WSTRC );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_WSTRC);
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&WStrC_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     
    WSTRC_DATA *    WStrC_InitA(
        WSTRC_DATA      *this,
        const
        char            *pStr
    )
    {
        uint32_t        len;
        uint32_t        i;
        int32_t         *pInsert;
        int32_t         chr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (NULL == pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        len = (uint32_t)utf8_StrLenA(pStr);
        if (0 == len) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (WSTRC_DATA *)WStrC_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pInsert = mem_Malloc((len + 1) * sizeof(int32_t));
        if (NULL == pInsert) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pArray = pInsert;
        this->len = len;
        obj_FlagOn(this, WSTRC_FLAG_MALLOC);
        
        for (i=0; i<len; ++i) {
            chr = utf8_Utf8ToWC_Scan(&pStr);
            *pInsert++ = chr;
        }
        *pInsert = '\0';
        
        return this;
    }
    
    
    WSTRC_DATA *    WStrC_InitConW(
        WSTRC_DATA      *this,
        const
        int32_t         *pStr
    )
    {
        uint32_t        len;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (NULL == pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        len = utf8_StrLenW(pStr);
        if (0 == len) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (WSTRC_DATA *)WStrC_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->pArray = pStr;
        this->len = len;
        
        return this;
    }
    
    
    
    WSTRC_DATA *    WStrC_InitW(
        WSTRC_DATA      *this,
        const
        int32_t         *pStr
    )
    {
        uint32_t        len;
        int32_t         *pInsert;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (NULL == pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        len = utf8_StrLenW(pStr);
        if (0 == len) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (WSTRC_DATA *)WStrC_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pInsert = mem_Malloc((len + 1) * sizeof(int32_t));
        if (NULL == pInsert) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pArray = pInsert;
        this->len = len;
        obj_FlagOn(this, WSTRC_FLAG_MALLOC);
        
        memmove(pInsert, pStr, (len * sizeof(int32_t)));
        pInsert[len] = '\0';
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                       M i d
    //---------------------------------------------------------------
    
    WSTRC_DATA *    WStrC_Mid(
        WSTRC_DATA      *this,
        uint32_t        offset,            /* Relative to 1 */
        uint32_t        len
    )
    {
        WSTRC_DATA      *pNewStr = OBJ_NIL;
        uint32_t        lenStr = WStrC_getLength(this);
        int32_t         *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !WStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (offset > lenStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (len == 0) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((0 == lenStr) || ((offset + len - 1) > lenStr)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        // Create the new string from this one.
        pNewStr = WStrC_New();
        pArray = mem_Malloc((len + 1) * sizeof(int32_t));
        if (NULL == pArray) {
            DEBUG_BREAK();
            obj_Release(pNewStr);
            return OBJ_NIL;
        }
        memmove(pArray, &this->pArray[offset-1], (len * sizeof(int32_t)));
        pArray[len] = 0;
        pNewStr->pArray = pArray;
        pNewStr->len = len;
        obj_FlagOn(pNewStr, WSTRC_FLAG_MALLOC);

        
        
        // Return to caller.
        return pNewStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     WStrC_ToDebugString(
        WSTRC_DATA      *this,
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
                     "{%p(WStrC) len=%d data=%ls",
                     this,
                     WStrC_getLength(this),
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
        
        j = snprintf( str, sizeof(str), " %p(WStrC)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            WStrC_Validate(
        WSTRC_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_WSTRC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(WSTRC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


