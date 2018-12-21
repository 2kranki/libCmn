// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   token.c
 *	Generated 05/26/2015 13:40:16
 *
 * Created on December 30, 2014
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
#include    "token_internal.h"
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>
#include    <ascii.h>
#include    <szTbl.h>
#include    <utf8.h>


//#define TOKEN_STORE_W32 1         // Store single W32CHR_T as unicode
//                                  // otherwise store as ASCII
// W-A-R-N-I-N-G -- Setting this breaks most of Lex, pplex, etc



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

    /*! Allocate an area large enough for the object data and the
        token data. Initialize the data pointer to within the area gotten.
     @return        A pointer to the combined data and object if
                    successful or OBJ_NIL if not.
     */
    TOKEN_DATA *     token_Alloc(
    )
    {
        TOKEN_DATA      *this;
        uint32_t        cbSize = sizeof(TOKEN_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }




    TOKEN_DATA *     token_NewCharW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32CHR_T        chr
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        if (this) {
            this = token_InitFnLCC(this, pLoc, cls);
            if (this) {
                token_setChrW32(this, chr);
            }
        }
        
        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewInteger(
        SRCLOC          *pLoc,
        int32_t         cls,
        int64_t         num
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        if (this) {
            this = token_InitFnLCC(this, pLoc, cls);
            if (this) {
                this->data.integer = num;
                this->data.type = TOKEN_TYPE_INTEGER;
            }
        }

        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewFromW32STR(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32STR_DATA     *pString
    )
    {
        TOKEN_DATA      *this;
        uint32_t        token;

        // Do initialization.
        
        this = token_Alloc( );
        if (this) {
            this = token_InitFnLCC(this, pLoc, cls);
            if (this) {
                token = szTbl_StringW32ToToken(szTbl_Shared(), W32Str_getData(pString));
                this->data.strToken = token;
                this->data.type = TOKEN_TYPE_STRTOKEN;
            }
        }

        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewStrA(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        char            *pStr
    )
    {
        TOKEN_DATA      *this;
        uint32_t        strlen = 0;
        uint32_t        token;

        // Do initialization.
        
        strlen = utf8_StrLenChars(pStr);
        this = token_Alloc( );
        if (this) {
            this = token_InitFnLCC(this, pLoc, cls);
            if (OBJ_NIL == this) {
                return OBJ_NIL;
            }
            
            // Create a string token.
            token = szTbl_StringToToken(szTbl_Shared(), pStr);
            this->data.strToken = token;
            this->data.type = TOKEN_TYPE_STRTOKEN;
        }
        
        // Return to caller.
        return this;
    }
    
    
    TOKEN_DATA *     token_NewStrW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStr
    )
    {
        TOKEN_DATA      *this;
        uint32_t        token;
        
        // Do initialization.
        
        this = token_Alloc( );
        if (this) {
            this = token_InitFnLCC(this, pLoc, cls);
            if (this) {
                token = szTbl_StringW32ToToken(szTbl_Shared(), pStr);
                this->data.strToken = token;
                this->data.type = TOKEN_TYPE_STRTOKEN;
            }
        }
        //FIXME: this = token_InitStrW(this, pFileName, lineNo, colNo, cls, pStr);
        
        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewStrToken(
        SRCLOC          *pLoc,
        int32_t         cls,
        uint32_t        token
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        if (this) {
            this = token_InitFnLCC(this, pLoc, cls);
            if (this) {
                this->data.strToken = token;
                this->data.type = TOKEN_TYPE_STRTOKEN;
            }
        }
        
        // Return to caller.
        return( this );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    W32CHR_T        token_getChrW32(
        TOKEN_DATA      *this
    )
    {
        W32CHR_T        chr = -1;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (TOKEN_TYPE_CHAR == this->data.type) {
            utf8_Utf8ToW32(this->data.chr, &chr);
        }
        if (TOKEN_TYPE_W32CHAR == this->data.type) {
            chr = this->data.w32chr[0];
        }
        return chr;
    }
    
    
    bool            token_setChrW32(
        TOKEN_DATA      *this,
        W32CHR_T        value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
      
#ifdef TOKEN_STORE_W32
        this->data.w32chr[0] = value;
        this->data.w32chr[1] = 0;
        this->data.type = TOKEN_TYPE_W32CHAR;
#else
        utf8_W32ToUtf8(value, this->data.chr);
        this->data.type = TOKEN_TYPE_CHAR;
#endif

        return true;
    }
    
    
    
    int32_t         token_getClass(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.cls;
    }

    
    bool            token_setClass(
        TOKEN_DATA      *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.cls = value;
        return true;
    }
    
    
    
    uint16_t        token_getColNo(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.src.colNo;
    }

    
    bool            token_setColNo(
        TOKEN_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.colNo = value;
        return true;
    }
    
    
    
    uint16_t        token_getFileIndex(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.src.fileIndex;
    }

    
    bool            token_setFileIndex(
        TOKEN_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.fileIndex = value;
        return true;
    }
    
    
    
    int64_t         token_getInteger(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (TOKEN_TYPE_INTEGER == this->data.type) {
            return this->data.integer;
        }
        return 0;
    }
    
    
    bool            token_setInteger(
        TOKEN_DATA      *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->data.type = TOKEN_TYPE_INTEGER;
        this->data.integer = value;
        
        return true;
    }
    
    
    
    uint16_t        token_getLen(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.len;
    }
    
    
    bool            token_setLen(
        TOKEN_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        this->data.len = value;
        return true;
    }
    
    
    
    uint32_t        token_getLineNo(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.src.lineNo;
    }
    
    bool            token_setLineNo(
        TOKEN_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.lineNo = value;
        return true;
    }
    
    
    
    SRCLOC *        token_getLoc(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return &this->data.src;
    }
    

    
    int16_t         token_getMisc(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.misc;
    }
    
    
    bool            token_setMisc(
        TOKEN_DATA      *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.misc = value;
        return true;
    }
    
    
    
    int64_t         token_getOffset(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.src.offset;
    }
    
    
    bool            token_setOffset(
        TOKEN_DATA      *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.offset = value;
        return true;
    }
    
    
    
    uint32_t        token_getStrToken(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (TOKEN_TYPE_STRTOKEN == this->data.type) {
            return this->data.strToken;
        }
        return 0;
    }
    
    
    bool            token_setStrToken(
        TOKEN_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->data.type = TOKEN_TYPE_STRTOKEN;
        this->data.strToken = value;
        
        return true;
    }
    
    
    
    bool            token_setStrW32(
        TOKEN_DATA      *this,
        const
        W32CHR_T        *pStr
    )
    {
        uint32_t        token;

#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        token = szTbl_StringW32ToToken(szTbl_Shared(), pStr);
        if (token) {
            this->data.type = TOKEN_TYPE_STRTOKEN;
            this->data.strToken = token;
        }
        else {
            return false;
        }
        
        return true;
    }
    
    
    char *          token_getTextA(
        TOKEN_DATA      *this
    )
    {
        char            *pStrA = NULL;
        const
        char            *pStrA2 = NULL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (this->data.type) {
                
            case TOKEN_TYPE_CHAR:
                pStrA = strdup(this->data.chr);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                pStrA2 = szTbl_TokenToString(szTbl_Shared(), this->data.strToken);
                pStrA = strdup(pStrA2);
                break;
                
            default:
                break;
        }
        
        return pStrA;
    }
    
    
    
    ASTR_DATA *     token_getTextAStr(
        TOKEN_DATA      *this
    )
    {
        const
        char            *pStrA = NULL;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (this->data.type) {
                
            case TOKEN_TYPE_CHAR:
                pStr = AStr_NewA(this->data.chr);
                break;
                
            case TOKEN_TYPE_W32CHAR:
                pStr = AStr_NewW32(this->data.w32chr);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                pStrA = szTbl_TokenToString(szTbl_Shared(), this->data.strToken);
                if (pStrA) {
                    pStr = AStr_NewA(pStrA);
                }
                break;
                
            default:
                break;
        }
        
        return pStr;
    }
    
    
    
    uint16_t        token_getType(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->data.type;
    }
    
    
    bool            token_setType(
        TOKEN_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.type = value;
        return true;
    }
    
    
    
    bool            token_setW32STR(
        TOKEN_DATA      *this,
        W32STR_DATA     *pStr
    )
    {
        uint32_t        token;
        
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        token = szTbl_StringW32ToToken(szTbl_Shared(), W32Str_getData(pStr));
        if (token) {
            this->data.type = TOKEN_TYPE_STRTOKEN;
            this->data.strToken = token;
        }
        else {
            return false;
        }
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         token_Assign(
        TOKEN_DATA      *this,
        TOKEN_DATA      *pOther
    )
    {
        
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !token_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pOther->data.src = this->data.src;
        pOther->data.cls = this->data.cls;
        pOther->data.type = this->data.type;
        pOther->data.len = this->data.len;
        pOther->data.misc = this->data.misc;
        switch (this->data.type) {
                
            case TOKEN_TYPE_UNKNOWN:
                break;
                
            case TOKEN_TYPE_CHAR:
                memmove(pOther->data.chr, this->data.chr, sizeof(this->data.chr));
                break;
                
            case TOKEN_TYPE_FLOAT:
                pOther->data.flt = this->data.flt;
                break;
                
            case TOKEN_TYPE_INTEGER:
                pOther->data.integer = this->data.integer;
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                pOther->data.strToken = this->data.strToken;
                break;
                
            case TOKEN_TYPE_W32CHAR:
                pOther->data.w32chr[0] = this->data.w32chr[0];
                pOther->data.w32chr[1] = this->data.w32chr[1];
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
                
        }
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         token_Compare(
        TOKEN_DATA       *this,
        TOKEN_DATA       *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !token_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (this->data.type == pOther->data.type) {
            switch (this->data.type) {
                    
            case TOKEN_TYPE_CHAR:
                i = strcmp(this->data.chr, pOther->data.chr);
                if (i == 0)
                    ;
                else {
                    eRc = ERESULT_SUCCESS_UNEQUAL;
                }
                break;
                    
            case TOKEN_TYPE_FLOAT:
                if (this->data.flt == pOther->data.flt)
                    ;
                else {
                    eRc = ERESULT_SUCCESS_UNEQUAL;
                }
                break;
                    
            case TOKEN_TYPE_INTEGER:
                if (this->data.integer == pOther->data.integer)
                    ;
                else {
                    eRc = ERESULT_SUCCESS_UNEQUAL;
                }
                break;
                    
            case TOKEN_TYPE_STRTOKEN:
                if (this->data.strToken == pOther->data.strToken)
                    ;
                else {
                    eRc = ERESULT_SUCCESS_UNEQUAL;
                }
                break;
                    
            case TOKEN_TYPE_W32CHAR:
                if (this->data.w32chr[0] == pOther->data.w32chr[0])
                    ;
                else {
                    eRc = ERESULT_SUCCESS_UNEQUAL;
                }
                break;
                    
            default:
                eRc = ERESULT_SUCCESS_UNEQUAL;
                break;
            }
        }
        else {
            eRc = ERESULT_SUCCESS_UNEQUAL;
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    TOKEN_DATA *   token_Copy(
        TOKEN_DATA      *this
    )
    {
        TOKEN_DATA      *pOther;
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        pOther = token_Alloc( );
        pOther = token_Init( pOther );
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        eRc = token_Assign(this, pOther);
        if (ERESULT_HAS_FAILED(eRc)) {
            obj_Release(pOther);
            pOther = OBJ_NIL;
            return OBJ_NIL;
        }
        
        return pOther;
    }
    
    

    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            token_Dealloc(
        OBJ_ID          objId
    )
    {
        TOKEN_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif


        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TOKEN_DATA *   token_Init(
        TOKEN_DATA      *this
    )
    {
        uint32_t        cbSize = sizeof(TOKEN_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init(this, cbSize, OBJ_IDENT_TOKEN);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&token_Vtbl);
        
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->data.integer);
        BREAK_NOT_BOUNDARY4(sizeof(TOKEN_DATA));
        BREAK_NOT_BOUNDARY4(sizeof(TOKEN));
#endif

        return this;
    }

     
    TOKEN_DATA *     token_InitFnLCC(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (pLoc)
            this->data.src = *pLoc;
        else
            memset(&this->data.src, 0, sizeof(SRCLOC));
        this->data.cls = cls;
        
        return this;
    }
    

    TOKEN_DATA *     token_InitCharW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        W32CHR_T        chr
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC(this, pLoc, cls);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        token_setChrW32(this, chr);
        
        return this;
    }
    
    
    TOKEN_DATA *     token_InitInteger(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        int64_t         integer
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC( this, pLoc, cls );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->data.type      = TOKEN_TYPE_INTEGER;
        this->data.integer   = integer;
        
        return this;
    }
    
    
    TOKEN_DATA *     token_InitStrToken(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        uint32_t        token
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC( this, pLoc, cls );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->data.strToken = token;
        this->data.type = TOKEN_TYPE_STRTOKEN;
        
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          token_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TOKEN_DATA      *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
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
                            return token_ToDebugString;
                        }
#ifdef XYZZY
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return token_ToJSON;
                        }
#endif
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
    //                              S e t
    //---------------------------------------------------------------
    
    ERESULT     token_SetupCharW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        chr
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = token_SetupFnLCC(this, pLoc, cls);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        token_setChrW32(this, chr);
        
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         token_SetupFnLCC(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pLoc)
            this->data.src = *pLoc;
        else
            memset(&this->data.src, 0, sizeof(SRCLOC));
        this->data.cls = cls;
        
        return ERESULT_SUCCESS;
    }
    

    
    ERESULT     token_SetupStrW32(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStr
    )
    {
        ERESULT         eRc;
        SZTBL_DATA      *pTbl = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pStr == NULL) {
            return ERESULT_INVALID_PARAMETER;
        }

        eRc = token_SetupFnLCC( this, pLoc, cls );
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        pTbl = szTbl_Shared();
        if (OBJ_NIL == pTbl) {
            return ERESULT_GENERAL_FAILURE;
        }
        this->data.strToken = szTbl_StringW32ToToken(pTbl, pStr);
        BREAK_ZERO(this->data.strToken);
        this->data.type = TOKEN_TYPE_STRTOKEN;
        
        return ERESULT_SUCCESS;
    }

    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     token_ToDataString(
        TOKEN_DATA      *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        const
        char            *pString;
        //ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        str[0] = '\0';
        
        switch (this->data.type) {
                
            case TOKEN_TYPE_CHAR:
                AStr_AppendA(pStr, this->data.chr);
                break;
                
           case TOKEN_TYPE_W32CHAR:
                if (ascii_isPrintableW32(this->data.w32chr[0])) {
                    str[0] = this->data.w32chr[0];
                    str[1] = '\0';
                }
                else {
                    str[0] = ' ';
                    str[1] = '\0';
                }                
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_INTEGER:
                j = snprintf(
                             str,
                             sizeof(str),
                             "%lld ",
                             this->data.integer
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                pString = szTbl_TokenToString(szTbl_Shared(), this->data.strToken);
                if (pString) {
                    //AStr_AppendA(pStr, "\"");
                    AStr_AppendA(pStr, pString);
                    //AStr_AppendA(pStr, "\"");
                }
                break;
                
            default:
                DEBUG_BREAK();
                AStr_AppendA(pStr, "type=>>>ERROR - Bad Type<<< ");
                break;
                
        }
        
        return pStr;
    }
    
    
    ASTR_DATA *     token_ToDebugString(
        TOKEN_DATA      *this,
        int             indent
    )
    {
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        W32CHR_T        w32;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        AStr_AppendPrint(
                         pStr,
                         "{%p(token) fileIndex=%2d offset=%4lld line=%2d col=%d cls=%4d ",
                         this,
                         token_getFileIndex(this),
                         token_getOffset(this),
                         token_getLineNo(this),
                         token_getColNo(this),
                         this->data.cls
        );
        
        switch (this->data.type) {
                
            case TOKEN_TYPE_UNKNOWN:
                AStr_AppendA(pStr, "type=UNKNOWN ");
                break;
                
            case TOKEN_TYPE_CHAR:
                utf8_Utf8ToW32(this->data.chr, &w32);
                AStr_AppendPrint(
                                 pStr,
                                 "type=CHAR char=(0x%X)%c ",
                                 w32,
                                 (((w32 >= ' ') && (w32 < 0x7F)) ? w32 : ' ')
                );
                break;
                
            case TOKEN_TYPE_W32CHAR:
                AStr_AppendPrint(
                        pStr,
                        "type=W32CHAR char=(0x%X)%c ",
                        this->data.w32chr[0],
                        (((this->data.w32chr[0] >= ' ') && (this->data.w32chr[0] < 0x7F))
                                  ? this->data.w32chr[0] : ' ')
                );
                break;
                
            case TOKEN_TYPE_INTEGER:
                AStr_AppendPrint(pStr, "type=INTEGER integer=%lld ", this->data.integer);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                AStr_AppendPrint(pStr,
                                 "type=STRTOKEN token=%d (\"%s\")",
                                 this->data.strToken,
                                 szTbl_TokenToString(szTbl_Shared(), this->data.strToken)
                );
                break;
                
            default:
                DEBUG_BREAK();
                AStr_AppendA(pStr, "type=>>>ERROR - Bad Type<<< ");
                break;
                
        }
        if (pStr)
            AStr_AppendA(pStr, "\n");

        if (pStr) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
            AStr_AppendPrint(pStr, " %p(token)}\n", this);
        }
        
        return pStr;
    }
    

    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            token_Validate(
        TOKEN_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_TOKEN) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(TOKEN_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


