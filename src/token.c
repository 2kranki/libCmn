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
#include    "szTbl.h"
#include    "utf8.h"




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

    TOKEN_DATA *     token_Alloc(
    )
    {
        TOKEN_DATA      *cbp;
        uint32_t        cbSize = sizeof(TOKEN_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    TOKEN_DATA *     token_NewCharW(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        int32_t         chr
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        this = token_InitCharW(this, pFileName, lineNo, colNo, cls, chr);
        
        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewInteger(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        int64_t         num
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        this = token_InitInteger(this, pFileName, lineNo, colNo, cls, num);
        
        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewStringW(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        WSTR_DATA       *pString
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        this = token_InitStringW(this, pFileName, lineNo, colNo, cls, pString);
        
        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewStrW(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        const
        int32_t         *pStr
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        this = token_InitStrW(this, pFileName, lineNo, colNo, cls, pStr);
        
        // Return to caller.
        return( this );
    }
    
    
    TOKEN_DATA *     token_NewStrToken(
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        const
        uint32_t        token
    )
    {
        TOKEN_DATA      *this;
        
        // Do initialization.
        
        this = token_Alloc( );
        this = token_InitStrToken(this, pFileName, lineNo, colNo, cls, token);
        
        // Return to caller.
        return( this );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    int32_t         token_getChrW(
        TOKEN_DATA      *this
    )
    {
        int32_t         i = -1;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        if (TOKEN_TYPE_WCHAR == this->type) {
            i = this->wchr[0];
        }
        return i;
    }
    
    
    bool            token_setChrW(
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
        
        token_ReleaseDataIfObj(this);
        this->type = TOKEN_TYPE_WCHAR;
        //this->cls = value;
        this->wchr[0] = value;
        this->wchr[1] = 0;
        
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
        
        return this->cls;
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
        this->cls = value;
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
        
        return this->colNo;
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
        this->colNo = value;
        return true;
    }
    
    
    
    const char *    token_getFileName(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        return this->pFileName;
    }

    
    bool            token_setFileName(
        TOKEN_DATA      *this,
        const
        char            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->pFileName = pValue;
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
        
        if (TOKEN_TYPE_INTEGER == this->type) {
            return this->integer;
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

        token_ReleaseDataIfObj(this);
        this->type = TOKEN_TYPE_INTEGER;
        this->integer = value;
        
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
        
        return this->len;
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
        this->len = value;
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
        
        return this->lineNo;
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
        this->lineNo = value;
        return true;
    }
    
    
    
    uint16_t        token_getMisc(
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
        
        return this->misc;
    }
    
    
    bool            token_setMisc(
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
        this->misc = value;
        return true;
    }
    
    
    
    OBJ_ID          token_getObj(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (TOKEN_TYPE_OBJECT == this->type) {
            return this->pObj;
        }
        return OBJ_NIL;
    }
    
    
    bool            token_setObj(
        TOKEN_DATA      *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        
        token_ReleaseDataIfObj(this);
        this->type = TOKEN_TYPE_OBJECT;
        this->pObj = pValue;
        
        return true;
    }
    
    
    
    WSTR_DATA *     token_getStringW(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (TOKEN_TYPE_WSTRING == this->type) {
            return this->pObj;
        }
        
        return OBJ_NIL;
    }
    
    
    bool            token_setStringW(
        TOKEN_DATA      *this,
        OBJ_ID          pValue
    )
    {
        uint16_t        type;
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        type = obj_getType(pValue);
        if ((OBJ_IDENT_WSTR == type) || (OBJ_IDENT_WSTRC == type)) {
        }
        else
            return false;
#endif
        
        obj_Retain(pValue);
        
        token_ReleaseDataIfObj(this);
        this->type = TOKEN_TYPE_WSTRING;
        this->pObj = pValue;
        
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
        
        if (TOKEN_TYPE_STRTOKEN == this->type) {
            return this->strToken;
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
        
        token_ReleaseDataIfObj(this);
        this->type = TOKEN_TYPE_STRTOKEN;
        this->strToken = value;
        
        return true;
    }
    
    
    
    const
    int32_t *       token_getTextW(
        TOKEN_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        switch (this->type) {

            case TOKEN_TYPE_WCHAR:
                return this->wchr;
                break;
                
            case TOKEN_TYPE_WSTRING:
                if (OBJ_IDENT_WSTR == obj_getType(this->pObj)) {
                    return WStr_getData(this->pObj);
                }
                if (OBJ_IDENT_WSTRC == obj_getType(this->pObj)) {
                    return WStrC_getData(this->pObj);
                }
                break;
                
            default:
                break;
        }

        return &this->zero;
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
        
        return this->type;
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
        this->type = value;
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         token_Assign(
        TOKEN_DATA       *this,
        TOKEN_DATA       *pOther
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
        
        token_ReleaseDataIfObj(pOther);
        
        pOther->lineNo = this->lineNo;
        pOther->pFileName = this->pFileName;
        pOther->colNo = this->colNo;
        pOther->cls = this->cls;
        pOther->type = this->type;
        pOther->len = this->len;
        pOther->offset = this->offset;
        switch (this->type) {
                
            case TOKEN_TYPE_UNKNOWN:
                break;
                
            case TOKEN_TYPE_WCHAR:
                // Since integer is as large as anything,
                // we just use it to copy the data.
                pOther->integer = this->integer;
                break;
                
            case TOKEN_TYPE_OBJECT:
            case TOKEN_TYPE_WSTRING:
            {
                OBJ_IUNKNOWN *pVtbl = obj_getVtbl(this->pObj);
                if (pVtbl->pCopy) {
                    pOther->pObj = pVtbl->pCopy(this->pObj);
                }
                else {
                    obj_Retain(this->pObj);
                    pOther->pObj = this->pObj;
                }
            }
                break;
                
            case TOKEN_TYPE_INTEGER:
                pOther->integer = this->integer;
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
                
        }
        
        return ERESULT_SUCCESSFUL_COMPLETION;
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
        if (this->type == pOther->type)
            ;
        else {
            return ERESULT_SUCCESS_UNEQUAL;
        }
        switch (this->type) {
                
            case TOKEN_TYPE_UNKNOWN:
                return ERESULT_GENERAL_FAILURE;
                break;
                
            case TOKEN_TYPE_WCHAR:
                switch (pOther->type) {
                        
                    case TOKEN_TYPE_UNKNOWN:
                        return ERESULT_GENERAL_FAILURE;
                        break;
                        
                    case TOKEN_TYPE_WCHAR:
                        i = this->wchr[0] - pOther->wchr[0];
                        break;
                        
                    case TOKEN_TYPE_OBJECT:
                        return ERESULT_GENERAL_FAILURE;
                        break;
                        
                    case TOKEN_TYPE_WSTRING:
                        eRc = WStr_Cmp(this->wchr, WStr_getData(pOther->pObj));
                        return eRc;
                        
                    case TOKEN_TYPE_INTEGER:
                        return ERESULT_GENERAL_FAILURE;
                        break;
                        
                    default:
                        DEBUG_BREAK();
                        return ERESULT_GENERAL_FAILURE;
                        
                }
                break;
                
            case TOKEN_TYPE_OBJECT:
                if (pOther->type == TOKEN_TYPE_OBJECT) {
                    OBJ_IUNKNOWN *pVtbl = obj_getVtbl(this->pObj);
                    if (pVtbl->pCompare) {
                        return pVtbl->pCompare(this->pObj, pOther->pObj);
                    }
                }
                return ERESULT_GENERAL_FAILURE;
                break;
                
            case TOKEN_TYPE_WSTRING:
                eRc = WStr_Compare(this->pObj, pOther->pObj);
                switch (pOther->type) {
                        
                    case TOKEN_TYPE_UNKNOWN:
                        return ERESULT_GENERAL_FAILURE;
                        break;
                        
                    case TOKEN_TYPE_WCHAR:
                        eRc = WStr_Cmp(WStr_getData(this->pObj), pOther->wchr);
                        break;
                        
                    case TOKEN_TYPE_OBJECT:
                        return ERESULT_GENERAL_FAILURE;
                        break;
                        
                    case TOKEN_TYPE_WSTRING:
                        eRc = WStr_Compare(this->pObj, pOther->pObj);
                        break;
                        
                    case TOKEN_TYPE_INTEGER:
                        return ERESULT_GENERAL_FAILURE;
                        break;
                        
                    default:
                        DEBUG_BREAK();
                        return ERESULT_GENERAL_FAILURE;
                        
                }
                return eRc;
                
            case TOKEN_TYPE_INTEGER:
                if (pOther->type == TOKEN_TYPE_INTEGER) {
                    i = (int)(this->integer - pOther->integer);
                }
                break;
                
            default:
                DEBUG_BREAK();
                return ERESULT_GENERAL_FAILURE;
                
        }
       
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //         C o n v e r t  T o  S t r i n g  T o k e n
    //---------------------------------------------------------------
    
    ERESULT         token_ConvertToStringToken(
        TOKEN_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        token = 0;
        
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        switch (this->type) {
                
            case TOKEN_TYPE_UNKNOWN:
                break;
                
            case TOKEN_TYPE_WCHAR:
                eRc = szTbl_StringWToToken(szTbl_Shared(), this->wchr, &token);
                if (ERESULT_IS_SUCCESSFUL(eRc)) {
                    this->strToken = token;
                }
                break;
                
            case TOKEN_TYPE_WSTRING:
                eRc = szTbl_StringWToToken(szTbl_Shared(), WStr_getData(this->pObj), &token);
                if (ERESULT_IS_SUCCESSFUL(eRc)) {
                    this->strToken = token;
                }
                break;
                
            case TOKEN_TYPE_INTEGER:
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                eRc = ERESULT_SUCCESSFUL_COMPLETION;
                break;
                
            default:
                DEBUG_BREAK();
                break;
                
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

        pOther = token_Alloc();
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

        token_ReleaseDataIfObj(this);
        
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      E r r o r F L C
    //---------------------------------------------------------------
    
    void            token_ErrorFLC(
        TOKEN_DATA      *this,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        va_start( argsp, fmt );
        
        eResult_ErrorFLCArg(
            eResult_Shared(),
            token_getFileName(this),
            token_getLineNo(this),
            token_getColNo(this),
            fmt,
            argsp
        );
    }
    
    
    void            token_ErrorFatalFLC(
        TOKEN_DATA      *this,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        va_start( argsp, fmt );

        eResult_ErrorFatalFLCArg(
            eResult_Shared(),
            token_getFileName(this),
            token_getLineNo(this),
            token_getColNo(this),
            fmt,
            argsp
        );
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
        token_ReleaseDataIfObj(this);   // If a prior token was present.
        
        this = obj_Init( this, cbSize, OBJ_IDENT_TOKEN );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&token_Vtbl);
        
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->integer);
#endif

        return this;
    }

     
    TOKEN_DATA *     token_InitFnLCC(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls
    )
    {
        const
        char            *pSavedFileName = NULL;
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (pFileName) {
            eRc = szTbl_StringToString(szTbl_Shared(), pFileName, &pSavedFileName);
            BREAK_TRUE(ERESULT_FAILED(eRc));
        }
        this->pFileName = pSavedFileName;
        this->lineNo    = lineNo;
        this->colNo     = colNo;
        this->cls       = cls;
        
        return this;
    }
    
    
    TOKEN_DATA *     token_InitCharW(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        int32_t         chr
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC( this, pFileName, lineNo, colNo, cls );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        token_setChrW(this, chr);
        
        return this;
    }
    
    
    TOKEN_DATA *     token_InitInteger(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        int64_t         integer
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC( this, pFileName, lineNo, colNo, cls );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->type      = TOKEN_TYPE_INTEGER;
        this->integer   = integer;
        
        return this;
    }
    
    
    TOKEN_DATA *     token_InitObj(
        TOKEN_DATA      *cbp,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        OBJ_DATA        *pObj
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbp = token_InitFnLCC( cbp, pFileName, lineNo, colNo, cls );
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        token_setObj(cbp, pObj);
        
        return cbp;
    }
    
    
    
    TOKEN_DATA *     token_InitStringW(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        WSTR_DATA       *pString
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC( this, pFileName, lineNo, colNo, cls );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        token_setStringW(this, (OBJ_ID)pString);
        
        return this;
    }
    
    
    TOKEN_DATA *     token_InitStrA(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        const
        char            *pStr
    )
    {
        WSTR_DATA       *pString;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC( this, pFileName, lineNo, colNo, cls );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pString = WStr_NewA(pStr);
        if (OBJ_NIL == pString) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pObj = pString;
        this->type = TOKEN_TYPE_WSTRING;
        
        return this;
    }
    
    
    
    TOKEN_DATA *     token_InitStrW(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        const
        int32_t         *pStr
    )
    {
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_Init( this );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        eRc = token_SetupStrW(this, pFileName, lineNo, colNo, cls, pStr);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        return this;
    }
    
    
    TOKEN_DATA *     token_InitStrToken(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        const
        uint32_t        token
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = token_InitFnLCC( this, pFileName, lineNo, colNo, cls );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this->strToken = token;
        this->type = TOKEN_TYPE_STRTOKEN;
        
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //              R e l e a s e  D a t a  I f  O b j
    //---------------------------------------------------------------
    
    void            token_ReleaseDataIfObj(
        TOKEN_DATA      *this
    )
    {
        uint32_t        cbSize = sizeof(TOKEN_DATA);
        
        /* "this" might point to an area which is
         * an initialized token. Therefore, we need
         * to add as many checks as we can to insure
         * that we are releasing an object really
         * assigned to a token.
         */
        if ( (obj_getType(this) == OBJ_IDENT_TOKEN)
            && (obj_getSize(this) >= cbSize)
            && (this->pObj)
        ) {
            switch (this->type) {
                case TOKEN_TYPE_OBJECT:
                case TOKEN_TYPE_WSTRING:
                    obj_Release(this->pObj);
                    this->pObj = OBJ_NIL;
                    break;
                    
                default:
                    break;
            }
        }
        
    }
    
    
    
    //---------------------------------------------------------------
    //                              S e t
    //---------------------------------------------------------------
    
    ERESULT     token_SetupCharW(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        const
        int32_t         chr
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

        eRc = token_SetupFnLCC( this, pFileName, lineNo, colNo, cls );
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        token_setChrW(this, chr);
        
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         token_SetupFnLCC(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls
    )
    {
        const
        char            *pSavedFileName = NULL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !token_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pFileName) {
            eRc = szTbl_StringToString(szTbl_Shared(), pFileName, &pSavedFileName);
            if (ERESULT_FAILED(eRc)) {
                return eRc;
            }
        }
        
        token_ReleaseDataIfObj(this);
        this->pFileName = pSavedFileName;
        this->lineNo    = lineNo;
        this->colNo     = colNo;
        this->cls       = cls;
        
        return ERESULT_SUCCESS;
    }
    

    
    ERESULT     token_SetupStrW(
        TOKEN_DATA      *this,
        const
        char            *pFileName,
        uint32_t        lineNo,
        uint16_t        colNo,
        int32_t         cls,
        const
        int32_t         *pStr
    )
    {
        ERESULT         eRc;
        WSTR_DATA       *pString;
        
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

        eRc = token_SetupFnLCC( this, pFileName, lineNo, colNo, cls );
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }
        
        pString = WStr_NewW(0, pStr);
        if (OBJ_NIL == pString) {
            DEBUG_BREAK();
            return ERESULT_OUT_OF_MEMORY;
        }
        this->pObj = pString;
        this->type = TOKEN_TYPE_WSTRING;
        
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
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        str[0] = '\0';
        
        switch (this->type) {
                
            case TOKEN_TYPE_WCHAR:
                j = snprintf(
                             str,
                             sizeof(str),
                             "%c",
                             (((this->wchr[0] >= ' ') && (this->wchr[0] < 0x7F))
                                        ? this->wchr[0] : ' ')
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_WSTRING:
                AStr_AppendA(pStr, "\"");
                AStr_AppendW(pStr, WStr_getLength(this->pObj), WStr_getData(this->pObj));
                AStr_AppendA(pStr, "\"");
                break;
                
            case TOKEN_TYPE_INTEGER:
                j = snprintf(
                             str,
                             sizeof(str),
                             "%lld ",
                             this->integer
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                pStr = NULL;
                eRc = szTbl_TokenToString(szTbl_Shared(), this->strToken, &pString);
                if (pString) {
                    AStr_AppendA(pStr, "\"");
                    j = snprintf(
                                 str,
                                 sizeof(str),
                                 "%s",
                                 pString
                                 );
                    AStr_AppendA(pStr, str);
                    AStr_AppendA(pStr, "\"");
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
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        
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
                     "{%p(token) fileName=%s line=%d col=%d cls=%d ",
                     this,
                     (this->pFileName ? this->pFileName : ""),
                     this->lineNo,
                     this->colNo,
                     this->cls
                     );
        AStr_AppendA(pStr, str);
        
        switch (this->type) {
                
            case TOKEN_TYPE_UNKNOWN:
                AStr_AppendA(pStr, "type=UNKNOWN ");
                break;
                
            case TOKEN_TYPE_WCHAR:
                j = snprintf(
                            str,
                            sizeof(str),
                            "type=CHAR char=(0x%X)%c ",
                            this->wchr[0],
                            (((this->wchr[0] >= ' ') && (this->wchr[0] < 0x7F))
                                ? this->wchr[0] : ' ')
                    );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_WSTRING:
                AStr_AppendA(pStr, "type=STRING text=\"");
                AStr_AppendW(pStr, WStr_getLength(this->pObj), WStr_getData(this->pObj));
                AStr_AppendA(pStr, "\"");
                break;
                
            case TOKEN_TYPE_INTEGER:
                j = snprintf(
                            str,
                            sizeof(str),
                            "type=INTEGER integer=%lld ",
                            this->integer
                            );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                j = snprintf(
                             str,
                             sizeof(str),
                             "type=STRTOKEN token=%d ",
                             this->strToken
                             );
                AStr_AppendA(pStr, str);
                break;
                
            default:
                DEBUG_BREAK();
                AStr_AppendA(pStr, "type=>>>ERROR - Bad Type<<< ");
                break;
                
        }
        AStr_AppendA(pStr, "\n");

        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), " %p(token)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    

    ASTR_DATA *     token_ToJSON(
        TOKEN_DATA      *this
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        char            str2[256];
        uint32_t        len;
        uint32_t        lenChars;
        const
        int32_t         *pWStr = NULL;
        
#ifdef NDEBUG
#else
        if( !token_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"token\",\"fileName\":\"%s\",\"lineNo\":%d,\"colNo\":%d,\"cls\":%d,",
                     (this->pFileName ? this->pFileName : ""),
                     this->lineNo,
                     this->colNo,
                     this->cls
                     );
        AStr_AppendA(pStr, str);
        
        switch (this->type) {
                
            case TOKEN_TYPE_UNKNOWN:
                AStr_AppendA(pStr, "\"type\":\"UNKNOWN\"");
                break;
                
            case TOKEN_TYPE_WCHAR:
                j = snprintf(
                             str,
                             sizeof(str),
                             "\"type\":\"CHAR\",\"data\":%d",
                             this->wchr[0]
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_WSTRING:
                AStr_AppendA(pStr, "\"type\":\"STRING\",\"data\":\"");
                if (OBJ_IDENT_WSTR == obj_getType(this->pObj)) {
                    pWStr = WStr_getData(this->pObj);
                }
                if (OBJ_IDENT_WSTRC == obj_getType(this->pObj)) {
                    pWStr = WStrC_getData(this->pObj);
                }
                len = utf8_StrLenW(pWStr);
                for (j=0; j<len; ++j) {
                    if (*pWStr == '"') {
                        AStr_AppendA(pStr, "\\");
                    }
                    lenChars = utf8_WCToUtf8(*pWStr, str2);
                    if (lenChars) {
                        AStr_AppendA(pStr, str2);
                    }
                    ++pWStr;
                }
                AStr_AppendA(pStr, "\"");
                break;
                
            case TOKEN_TYPE_INTEGER:
                j = snprintf(
                             str,
                             sizeof(str),
                             "\"type\":\"NUMBER\",\"data\":%lld",
                             this->integer
                             );
                AStr_AppendA(pStr, str);
                break;
                
            case TOKEN_TYPE_STRTOKEN:
                j = snprintf(
                             str,
                             sizeof(str),
                             "\"type\":\"STRTOKEN\",\"data\":%lld",
                             this->integer
                             );
                AStr_AppendA(pStr, str);
                break;
                
            default:
                DEBUG_BREAK();
                AStr_AppendA(pStr, "\"type\":\"UNKNOWN\"");
                break;
                
        }
        AStr_AppendA(pStr, "}\n");
        //BREAK_TRUE(AStr_getLength(pStr) > 2048);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            token_Validate(
        TOKEN_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_TOKEN) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(TOKEN_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


