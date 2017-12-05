// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   W32StrC.c
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
#include <W32StrC_internal.h>
#include <utf8.h>
#include <WStr.h>
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
    
    bool            W32StrC_CopyData(
        W32STRC_DATA    *this,
        W32CHR_T        *pData,
        uint32_t        len
    )
    {
        W32CHR_T        *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        if (len == 0) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        // Create the new string from this one.
        pArray = mem_Malloc((len + 1) * sizeof(uint32_t));
        if (NULL == pArray) {
            DEBUG_BREAK();
            return false;
        }
        memmove(pArray, pData, (len * sizeof(uint32_t)));
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

    W32STRC_DATA *  W32StrC_Alloc(
    )
    {
        W32STRC_DATA    *this;
        uint32_t        cbSize = sizeof(W32STRC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    W32STRC_DATA *  W32StrC_New(
    )
    {
        W32STRC_DATA    *this;
        
        this = W32StrC_Alloc( );
        if (this) {
            this = W32StrC_Init( this );
        } 
        return( this );
    }


    W32STRC_DATA *  W32StrC_NewA(
        const
        char            *pStr
    )
    {
        W32STRC_DATA    *this;
        
        this = W32StrC_Alloc( );
        if (this) {
            this = W32StrC_InitA( this, pStr );
        }
        return this;
    }
    
    
    W32STRC_DATA *   W32StrC_NewConW32(
        const
        W32CHR_T         *pStr
    )
    {
        W32STRC_DATA     *this;
        
        this = W32StrC_Alloc( );
        if (this) {
            this = W32StrC_InitConW32(this, pStr);
        }
        return( this );
    }
    
    
    W32STRC_DATA *  W32StrC_NewFromStrW32(
        WSTR_DATA       *pStr
    )
    {
        W32STRC_DATA    *this;
        
        this = W32StrC_Alloc( );
        if (this) {
            this = W32StrC_InitW32(this, WStr_getData(pStr));
        }
        return( this );
    }
    
    
    W32STRC_DATA *  W32StrC_NewW32(
        const
        W32CHR_T         *pStr
    )
    {
        W32STRC_DATA     *this;
        
        this = W32StrC_Alloc( );
        if (this) {
            this = W32StrC_InitW32(this, pStr);
        }
        return( this );
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    const
    W32CHR_T *      W32StrC_getData(
        W32STRC_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    uint32_t        W32StrC_getLength(
        W32STRC_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
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
    
    ERESULT         W32StrC_Compare(
        W32STRC_DATA	*this,
        W32STRC_DATA    *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !W32StrC_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if(OBJ_NIL == pOther) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        
        eRc = WStr_Cmp(this->pArray, pOther->pArray);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         W32StrC_CompareA(
        W32STRC_DATA	*this,
        const
        char            *pString
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        const
        W32CHR_T        *pStr1;
        W32CHR_T        chr2;
        int             i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
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
            chr2 = utf8_Utf8ToW32_Scan(&pString);
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
    
    
    ERESULT         W32StrC_CompareW32(
        W32STRC_DATA	*this,
        const
        W32CHR_T        *pString
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = WStr_Cmp(this->pArray, pString);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    W32STRC_DATA *  W32StrC_Copy(
        W32STRC_DATA   *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
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
    
    char *          W32StrC_CStringA(
        W32STRC_DATA	*this
    )
    {
        char            *pszStr;
        uint32_t        lenStr;
        uint32_t        lenA;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        lenStr = W32StrC_getLength(this);
        
        lenA =  utf8_W32ToUtf8Str(
                    lenStr,
                    this->pArray,
                    0,
                    NULL
                );
        pszStr = (char *)mem_Malloc(lenA);
        if (pszStr) {
            i =     utf8_W32ToUtf8Str(
                                     lenStr,
                                     this->pArray,
                                     lenA,
                                     pszStr
                                     );
            if (i < lenA) {
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

    void            W32StrC_Dealloc(
        OBJ_ID          objId
    )
    {
        W32STRC_DATA    *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (obj_IsFlag(this, W32STRC_FLAG_MALLOC)) {
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
    
    uint32_t        W32StrC_Hash(
        W32STRC_DATA    *this
    )
    {
        uint32_t        hash = 0;
        const
        W32CHR_T        *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        pStr = this->pArray;
        if (pStr) {
            hash = str_HashW32( pStr, NULL );
        }
        
        return hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    W32STRC_DATA *  W32StrC_Init(
        W32STRC_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(W32STRC_DATA);
        
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

        this = (W32STRC_DATA *)obj_Init( this, cbSize, OBJ_IDENT_W32STRC );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_WSTRC);
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&W32StrC_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !W32StrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     
    W32STRC_DATA *  W32StrC_InitA(
        W32STRC_DATA    *this,
        const
        char            *pStr
    )
    {
        uint32_t        len;
        uint32_t        i;
        W32CHR_T        *pInsert;
        uint32_t        chr;
        
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
        
        this = (W32STRC_DATA *)W32StrC_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pInsert = mem_Malloc((len + 1) * sizeof(W32CHR_T));
        if (NULL == pInsert) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pArray = pInsert;
        this->len = len;
        obj_FlagOn(this, W32STRC_FLAG_MALLOC);
        
        for (i=0; i<len; ++i) {
            chr = utf8_Utf8ToW32_Scan(&pStr);
            *pInsert++ = chr;
        }
        *pInsert = '\0';
        
        obj_FlagSet(this, OBJ_FLAG_RO, true);
        return this;
    }
    
    
    W32STRC_DATA *  W32StrC_InitConW32(
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pStr
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
        
        len = utf8_StrLenW32(pStr);
        if (0 == len) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (W32STRC_DATA *)W32StrC_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->pArray = pStr;
        this->len = len;
        
        obj_FlagSet(this, OBJ_FLAG_RO, true);
        return this;
    }
    
    
    
    W32STRC_DATA *  W32StrC_InitW32(
        W32STRC_DATA    *this,
        const
        W32CHR_T        *pStr
    )
    {
        uint32_t        len;
        W32CHR_T        *pInsert;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (NULL == pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        len = utf8_StrLenW32(pStr);
        if (0 == len) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (W32STRC_DATA *)W32StrC_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pInsert = mem_Malloc((len + 1) * sizeof(W32CHR_T));
        if (NULL == pInsert) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pArray = pInsert;
        this->len = len;
        obj_FlagOn(this, W32STRC_FLAG_MALLOC);
        
        memmove(pInsert, pStr, (len * sizeof(W32CHR_T)));
        pInsert[len] = '\0';
        
        obj_FlagSet(this, OBJ_FLAG_RO, true);
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                       M i d
    //---------------------------------------------------------------
    
    W32STRC_DATA *  W32StrC_Mid(
        W32STRC_DATA    *this,
        uint32_t        offset,            /* Relative to 1 */
        uint32_t        len
    )
    {
        W32STRC_DATA    *pNewStr = OBJ_NIL;
        uint32_t        lenStr = W32StrC_getLength(this);
        W32CHR_T        *pArray;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32StrC_Validate(this) ) {
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
        pNewStr = W32StrC_New();
        pArray = mem_Malloc((len + 1) * sizeof(W32CHR_T));
        if (NULL == pArray) {
            DEBUG_BREAK();
            obj_Release(pNewStr);
            return OBJ_NIL;
        }
        memmove(pArray, &this->pArray[offset-1], (len * sizeof(W32CHR_T)));
        pArray[len] = 0;
        pNewStr->pArray = pArray;
        pNewStr->len = len;
        obj_FlagOn(pNewStr, W32STRC_FLAG_MALLOC);

        
        
        // Return to caller.
        return pNewStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     W32StrC_ToDebugString(
        W32STRC_DATA    *this,
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(W32StrC) len=%d data=%ls",
                     this,
                     W32StrC_getLength(this),
                     (wchar_t *)this->pArray
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
        
        j = snprintf( str, sizeof(str), " %p(W32StrC)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            W32StrC_Validate(
        W32STRC_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_W32STRC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(W32STRC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


