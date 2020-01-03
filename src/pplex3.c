// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   pplex3.c
 *	Generated 09/17/2015 10:00:30
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
#include        "pplex3_internal.h"
#include        "lex_internal.h"
#include        <AStr.h>
#include        <W32Str.h>
#include        <ascii.h>
#include        <utf8.h>
#include        <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
    /*          * * * Key Word Table * * *
     */
    

    // A binary search is performed on this table. So, it must
    // be kept sorted by key word.
    static
    PPLEX_KWDTBL_ENTRY   kwdTbl_C[] = {
        // Upper case keywords would go here!
        { PPLEX_KWD_ASM,            PPLEX_LANG_MSC,	    "_asm" },
        { PPLEX_KWD_CDECL,          PPLEX_LANG_MSC,	    "_cdecl" },
        { PPLEX_KWD_EMIT,           PPLEX_LANG_MSC,	    "_emit" },
        { PPLEX_KWD_ENTRY,          PPLEX_LANG_MSC,	    "_entry" },
        { PPLEX_KWD_FAR,            PPLEX_LANG_MSC,	    "_far" },
        { PPLEX_KWD_FORTRAN,        PPLEX_LANG_MSC,	    "_fortran" },
        { PPLEX_KWD_NEAR,           PPLEX_LANG_MSC,	    "_near" },
        { PPLEX_KWD_PASCAL,         PPLEX_LANG_MSC,	    "_pascal" },
        { PPLEX_KWD_AUTO,           PPLEX_LANG_C,		"auto" },
        { PPLEX_KWD_BREAK,          PPLEX_LANG_C,		"break" },
        { PPLEX_KWD_CASE,           PPLEX_LANG_C,		"case" },
        { PPLEX_KWD_CHAR,           PPLEX_LANG_C,		"char" },
        { PPLEX_KWD_CLASS,          PPLEX_LANG_CPP,	    "class" },
        { PPLEX_KWD_CONST,          PPLEX_LANG_C,       "const" },
        { PPLEX_KWD_CONTINUE,       PPLEX_LANG_C,		"continue" },
        { PPLEX_KWD_DEFAULT,        PPLEX_LANG_C,		"default" },
        { PPLEX_KWD_DELETE,         PPLEX_LANG_CPP,	    "delete" },
        { PPLEX_KWD_DO,             PPLEX_LANG_C,		"do" },
        { PPLEX_KWD_DOUBLE,         PPLEX_LANG_C,		"double" },
        { PPLEX_KWD_ELSE,           PPLEX_LANG_C,		"else" },
        { PPLEX_KWD_END,            PPLEX_LANG_C,		"end" },
        { PPLEX_KWD_ENUM,           PPLEX_LANG_C,		"enum" },
        { PPLEX_KWD_EXTERN,         PPLEX_LANG_C,		"extern" },
        { PPLEX_KWD_FLOAT,          PPLEX_LANG_C,		"float" },
        { PPLEX_KWD_FOR,            PPLEX_LANG_C,		"for" },
        { PPLEX_KWD_FRIEND,         PPLEX_LANG_CPP,	    "friend" },
        { PPLEX_KWD_GOTO,           PPLEX_LANG_C,		"goto" },
        { PPLEX_KWD_ID,             PPLEX_LANG_OBJC,	"id" },
        { PPLEX_KWD_IF,             PPLEX_LANG_C,		"if" },
        { PPLEX_KWD_INT,            PPLEX_LANG_C,		"int" },
        { PPLEX_KWD_INT128,         PPLEX_LANG_C,		"int128_t" },
        { PPLEX_KWD_INT16,          PPLEX_LANG_C,		"int16_t" },
        { PPLEX_KWD_INT256,         PPLEX_LANG_C,       "int256_t" },
        { PPLEX_KWD_INT32,          PPLEX_LANG_C,		"int32_t" },
        { PPLEX_KWD_INT64,          PPLEX_LANG_C,		"int64_t" },
        { PPLEX_KWD_INT8,           PPLEX_LANG_C,		"int8_t" },
        { PPLEX_KWD_LONG,           PPLEX_LANG_C,		"long" },
        { PPLEX_KWD_NEW,            PPLEX_LANG_CPP,	    "new" },
        { PPLEX_KWD_OPERATOR,       PPLEX_LANG_CPP,	    "operator" },
        { PPLEX_KWD_OVERLOAD,       PPLEX_LANG_CPP,	    "overload" },
        { PPLEX_KWD_PUBLIC,         PPLEX_LANG_CPP,	    "public" },
        { PPLEX_KWD_REGISTER,       PPLEX_LANG_C,		"register" },
        { PPLEX_KWD_RETURN,         PPLEX_LANG_C,		"return" },
        { PPLEX_KWD_SELECT,         PPLEX_LANG_C,		"select" },
        { PPLEX_KWD_SHORT,          PPLEX_LANG_C,		"short" },
        { PPLEX_KWD_SIGNED,         PPLEX_LANG_C,		"signed" },
        { PPLEX_KWD_SIZEOF,         PPLEX_LANG_C,		"sizeof" },
        { PPLEX_KWD_STATIC,         PPLEX_LANG_C,		"static" },
        { PPLEX_KWD_STRUCT,         PPLEX_LANG_C,		"struct" },
        { PPLEX_KWD_SWITCH,         PPLEX_LANG_C,		"switch" },
        { PPLEX_KWD_THIS,           PPLEX_LANG_CPP,	    "this" },
        { PPLEX_KWD_TYPEDEF,        PPLEX_LANG_C,		"typedef" },
        { PPLEX_KWD_UINT128,        PPLEX_LANG_C,		"uint128_t" },
        { PPLEX_KWD_UINT16,         PPLEX_LANG_C,		"uint16_t" },
        { PPLEX_KWD_UINT256,        PPLEX_LANG_C,		"uint256_t" },
        { PPLEX_KWD_UINT32,         PPLEX_LANG_C,		"uint32_t" },
        { PPLEX_KWD_UINT64,         PPLEX_LANG_C,		"uint64_t" },
        { PPLEX_KWD_UINT8,          PPLEX_LANG_C,		"uint8_t" },
        { PPLEX_KWD_UNION,          PPLEX_LANG_C,		"union" },
        { PPLEX_KWD_UNSIGNED,       PPLEX_LANG_C,		"unsigned" },
        { PPLEX_KWD_VIRTUAL,        PPLEX_LANG_CPP,	    "virtual" },
        { PPLEX_KWD_VOID,           PPLEX_LANG_C,		"void" },
        { PPLEX_KWD_VOLATILE,       PPLEX_LANG_C,		"volatile" },
        { PPLEX_KWD_WHILE,          PPLEX_LANG_C,		"while" },
        { PPLEX_KWD_NSENUM,         PPLEX_LANG_OBJC,	"NS_ENUM" },
        { PPLEX_KWD_NSOPTIONS,      PPLEX_LANG_OBJC,	"NS_OPTIONS" },
    };
    
    static
    int         cKwdTbl_C = sizeof(kwdTbl_C)/sizeof(PPLEX_KWDTBL_ENTRY);

    
    
    // A binary search is performed on this table. So, it must
    // be kept sorted by key word.
    static
    PPLEX_KWDTBL_ENTRY   kwdTbl_LL1[] = {
        // Upper case keywords would go here!
        { PPLEX_KWD_GOAL,           PPLEX_LANG_LL1,		"%goal" },
        { PPLEX_KWD_TERM,           PPLEX_LANG_LL1,		"%term" }
    };
    
    static
    int         cKwdTbl_LL1 = sizeof(kwdTbl_LL1)/sizeof(PPLEX_KWDTBL_ENTRY);
    
    
    
    // NOTE --  This table must be kept in alphabetical order by keyword
    //          for the searches to work properly.
    static
    PPLEX_KWDTBL_ENTRY   kwdTbl_ObjC[] = {
        { PPLEX_KWD_AT_AUTO,            PPLEX_LANG_OBJC,    "@autoreleasepool" },
        { PPLEX_KWD_AT_CATCH,           PPLEX_LANG_OBJC,	"@catch" },
        { PPLEX_KWD_AT_CLASS,           PPLEX_LANG_OBJC,	"@class" },
        { PPLEX_KWD_AT_DYNAMIC,         PPLEX_LANG_OBJC,	"@dynamic" },
        { PPLEX_KWD_AT_ENCODE,          PPLEX_LANG_OBJC,	"@encode" },
        { PPLEX_KWD_AT_END,             PPLEX_LANG_OBJC,	"@end" },
        { PPLEX_KWD_AT_FINALLY,         PPLEX_LANG_OBJC,	"@finally" },
        { PPLEX_KWD_AT_IMPLEMENTATION,  PPLEX_LANG_OBJC,	"@implementation" },
        { PPLEX_KWD_AT_INTERFACE,       PPLEX_LANG_OBJC,	"@interface" },
        { PPLEX_KWD_AT_OPTIONAL,        PPLEX_LANG_OBJC,	"@optional" },
        { PPLEX_KWD_AT_PKG,             PPLEX_LANG_OBJC,	"@package" },
        { PPLEX_KWD_AT_PRIVATE,         PPLEX_LANG_OBJC,	"@private" },
        { PPLEX_KWD_AT_PROPERTY,        PPLEX_LANG_OBJC,	"@property" },
        { PPLEX_KWD_AT_PROTECTED,       PPLEX_LANG_OBJC,	"@protected" },
        { PPLEX_KWD_AT_PROTOCOL,        PPLEX_LANG_OBJC,	"@protocol" },
        { PPLEX_KWD_AT_PUBLIC,          PPLEX_LANG_OBJC,	"@public" },
        { PPLEX_KWD_AT_SEL,             PPLEX_LANG_OBJC,	"@selector" },
        { PPLEX_KWD_AT_SYNC,            PPLEX_LANG_OBJC,	"@synchronized" },
        { PPLEX_KWD_AT_SYNTH,           PPLEX_LANG_OBJC,	"@synthesize" },
        { PPLEX_KWD_AT_THROW,           PPLEX_LANG_OBJC,	"@throw" },
        { PPLEX_KWD_AT_TRY,             PPLEX_LANG_OBJC,	"@try" },
    };
    
    static
    int         cKwdTbl_ObjC = sizeof(kwdTbl_ObjC)/sizeof(PPLEX_KWDTBL_ENTRY);
    
    
    
    
    
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    // Perform a binary search on the keyword table. (Keyword table
    // must be kept sorted!)
    static
    PPLEX_KWDTBL_ENTRY * kwSearch(
        const
        char            *pName,
        PPLEX_KWDTBL_ENTRY
                        *pTable,
        uint32_t        cTable
    )
    {
        PPLEX_KWDTBL_ENTRY
                        *pEntry;
        int             iRc;
        uint32_t        high = cTable - 1;
        uint32_t        low = 0;
        uint32_t        mid;
        
        while( low < high ) {
            mid = (high + low) / 2;
            pEntry = &pTable[mid];
            iRc = strcmp(pEntry->pKwd, pName);
            if( iRc < 0 ) {
                low = mid + 1;
            }
            else if( iRc == 0 ) {
                return pEntry;
            }
            else {
                high = mid;
            }
        }
        if( high == low ) {
            pEntry = &pTable[low];
            iRc = strcmp(pEntry->pKwd, pName);
            if(iRc == 0) {
                return pEntry;
            }
        }
        
        return NULL;
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PPLEX3_DATA *   pplex3_Alloc(
    )
    {
        PPLEX3_DATA     *cbp;
        uint32_t        cbSize = sizeof(PPLEX3_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    PPLEX3_DATA *     pplex3_New(
        uint16_t        k
    )
    {
        PPLEX3_DATA       *cbp;
        
        cbp = pplex3_Alloc( );
        if (cbp) {
            cbp = pplex3_Init( cbp, k );
        } 
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            pplex3_setAuxKwdTable(
        PPLEX3_DATA      *this,
        PPLEX_KWDTBL_ENTRY
                        *pAuxKwds,
        uint32_t        cAuxKwds
    )
    {
        
#ifdef NDEBUG
#else
        if( !pplex3_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pAuxKwds = pAuxKwds;
        this->cAuxKwds = cAuxKwds;
        
        return true;
    }
    
    
    
    bool            pplex3_setKwdSelection(
        PPLEX3_DATA     *this,
        uint16_t        value
    )
    {
        
#ifdef NDEBUG
#else
        if( !pplex3_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->kwdSel = value;
        
        // Return to caller.
        return true;
    }
    
    
    
    bool            pplex3_setParseFunction(
        PPLEX3_DATA     *this,
        bool            (*pUserExit)(OBJ_ID, TOKEN_DATA *),
        OBJ_ID          pUserObj
    )
    {
#ifdef NDEBUG
#else
        if( !pplex3_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pUserExit = pUserExit;
        this->pUserObject  = pUserObj;
        
        return true;
    }
    
    
    


    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                A d d  O b j C  t o  S z T b l
    //---------------------------------------------------------------
    
    ERESULT         pplex3_AddObjCToSzTbl(
        PPLEX3_DATA     *this
    )
    {
        SZTBL_DATA      *pSzTbl = szTbl_Shared();
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        iMax  = cKwdTbl_ObjC;
        PPLEX_KWDTBL_ENTRY
                        *pEntry;
        ASTR_DATA       *pAStr = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !pplex3_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        for (i=0; i<iMax; ++i) {
            pEntry = &kwdTbl_ObjC[i];
            pAStr = AStr_NewA(pEntry->pKwd);
            if (pAStr) {
                szTbl_StringToToken(pSzTbl, AStr_getData(pAStr));
                obj_Release(pAStr);
                pAStr = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  A d d  C  t o  S z T b l
    //---------------------------------------------------------------
    
    ERESULT         pplex3_AddCToSzTbl(
        PPLEX3_DATA     *this
    )
    {
        SZTBL_DATA      *pSzTbl = szTbl_Shared();
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        iMax  = cKwdTbl_C;
        PPLEX_KWDTBL_ENTRY
                        *pEntry;
        ASTR_DATA       *pAStr = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !pplex3_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        for (i=0; i<iMax; ++i) {
            pEntry = &kwdTbl_C[i];
            pAStr = AStr_NewA(pEntry->pKwd);
            if (pAStr) {
                szTbl_StringToToken(pSzTbl, AStr_getData(pAStr));
                obj_Release(pAStr);
                pAStr = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            pplex3_Dealloc(
        OBJ_ID          objId
    )
    {
        PPLEX3_DATA     *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !pplex3_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PPLEX3_DATA *   pplex3_Init(
        PPLEX3_DATA     *this,
        uint16_t        k
    )
    {
        uint32_t        cbSize = sizeof(PPLEX3_DATA);
        bool            fRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);         // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = (PPLEX3_DATA *)lex_Init( (LEX_DATA *)this, k );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&pplex3_Vtbl);
        
        fRc =   lex_setParserFunction(
                            (LEX_DATA *)this,
                            (void *)pplex3_ParseToken,
                            this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !pplex3_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                      P a r s e  T o k e n
    //--------------------------------------------------------------
    
    /* ParseToken() gets the next token from the source file. It
     * saves that token for the file/line/col numbers and then
     * proceeds to build upon it. It accumulates tokens until
     * based on the class/type. When it finds a token which does
     * not belong to that class, it saves the current token
     * string to the string table, and tells the source file
     * to re-use the token which did not match on the next parse.
     * The token returned from this routine has the index of the
     * token string in the string table if it is larger than 1
     * character.
     *
     * This method does not use the Output Token, but uses lex_
     * functions to create the parsed token.
     */
    
    bool            pplex3_ParseToken(
        PPLEX3_DATA		*this,
        TOKEN_DATA      *pTokenOut
    )
    {
        TOKEN_DATA      *pInput;
        //uint16_t        numDigits;
        int32_t         cls;
        //int32_t         chr;
        PPLEX_KWDTBL_ENTRY
                        *pKWD;
        bool            fMore = true;
        bool            fExternal;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !pplex3_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        while (fMore) {
            pInput = lex_InputLookAhead((LEX_DATA *)this, 1);
            if (pInput) {
                cls = Token_getClass(pInput);
            }
            else {
                pInput = lex_ParseEOF((LEX_DATA *)this);
                cls = Token_getClass(pInput);
                DEBUG_BREAK();
            }
            Token_Assign(pInput, lex_getToken((LEX_DATA *)this));
            
            switch (cls) {
                    
                case LEX_CLASS_EOF:
                    fMore = false;
                    break;
                    
                case PPLEX_IDENTIFIER:
                    if (this->pUserExit) {
                        fExternal = this->pUserExit(
                                                this->pUserObject,
                                                lex_getToken((LEX_DATA *)this)
                                    );
                        if (fExternal) {
                            lex_InputAdvance((LEX_DATA *)this, 1);
                            fMore = false;
                            obj_Release(pStr);
                            break;
                        }
                    }
                    pStr = Token_getTextAStr(pInput);
                    if (this->pAuxKwds) {
                        pKWD =  kwSearch(
                                        AStr_getData(pStr),
                                        this->pAuxKwds,
                                        this->cAuxKwds
                                );
                        if (pKWD) {
                            Token_setClass(lex_getToken((LEX_DATA *)this), pKWD->value);
                            lex_InputAdvance((LEX_DATA *)this, 1);
                            fMore = false;
                            obj_Release(pStr);
                            break;
                        }
                    }
                    if ('@' == AStr_CharGetW32(pStr, 1)) {
                        pKWD = kwSearch(
                                    AStr_getData(pStr),
                                    kwdTbl_ObjC,
                                    cKwdTbl_ObjC
                                );
                        if (pKWD) {
                            Token_setClass(lex_getToken((LEX_DATA *)this),pKWD->value);
                            lex_InputAdvance((LEX_DATA *)this, 1);
                            fMore = false;
                            obj_Release(pStr);
                            break;
                        }
                    }
                    pKWD = kwSearch(
                                AStr_getData(pStr),
                                kwdTbl_C,
                                cKwdTbl_C
                                );
                    if (pKWD) {
                        Token_setClass(lex_getToken((LEX_DATA *)this),pKWD->value);
                        lex_InputAdvance((LEX_DATA *)this, 1);
                        fMore = false;
                        obj_Release(pStr);
                        break;
                    }
                    pKWD = kwSearch(
                                AStr_getData(pStr),
                                kwdTbl_LL1,
                                cKwdTbl_LL1
                                );
                    if (pKWD) {
                        Token_setClass(lex_getToken((LEX_DATA *)this), pKWD->value);
                        lex_InputAdvance((LEX_DATA *)this, 1);
                        fMore = false;
                        obj_Release(pStr);
                        break;
                    }
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    obj_Release(pStr);
                    break;

                default:
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    break;
            }
        }
        
        // Return to caller.
    //done:
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          pplex3_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PPLEX3_DATA     *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !pplex3_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PPLEX3_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return hex_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return hex_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return hex_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return hex_ToJSON;
                        }
                        break;
#endif
                        
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     pplex3_ToDebugString(
        PPLEX3_DATA      *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //SZSTR_DATA      *pWrkStr;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(pplex3) ",
                     cbp
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
    bool            pplex3_Validate(
        PPLEX3_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_PPLEX3) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(PPLEX3_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


