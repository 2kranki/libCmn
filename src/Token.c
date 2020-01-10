// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Token.c
 *	Generated 01/02/2020 15:58:08
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
#include        <Token_internal.h>
#include        <ascii.h>
#include        <szTbl.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    static
    const
    char            *pTypeStr[] = {
        "TOKEN_TYPE_UNKNOWN",
        "TOKEN_TYPE_CHAR",
        "TOKEN_TYPE_DOUBLE",
        "TOKEN_TYPE_INTEGER",
        "TOKEN_TYPE_STR_UTF8",
        "TOKEN_TYPE_STRCON_UTF8",
        "TOKEN_TYPE_STRTOKEN",
        "TOKEN_TYPE_W32CHAR",
        "TOKEN_TYPE_USER",
        NULL
    };





 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void            Token_FreeData (
        TOKEN_DATA      *this
    )
    {

        switch (this->data.type) {

            case TOKEN_TYPE_UNKNOWN:
            case TOKEN_TYPE_CHAR:
            case TOKEN_TYPE_DOUBLE:
            case TOKEN_TYPE_INTEGER:
            case TOKEN_TYPE_STR_UTF8:
            case TOKEN_TYPE_STRCON_UTF8:
            case TOKEN_TYPE_STRTOKEN:
            case TOKEN_TYPE_W32CHAR:
            case TOKEN_TYPE_USER:
                break;

#ifdef XYZZY
            case VALUE_TYPE_OBJECT:
                if (this->value.pObject) {
                    obj_Release(this->value.pObject);
                    this->value.pObject = OBJ_NIL;
                }
                break;

            case VALUE_TYPE_DATA:
                this->value.data.pData = NULL;
                this->value.data.length = 0;
                break;

            case VALUE_TYPE_DATA_FREE:
                if (this->value.data.pData) {
                    mem_Free(this->value.data.pData);
                    this->value.data.pData = NULL;
                }
                this->value.data.length = 0;
                break;
#endif

        }
        this->data.type = TOKEN_TYPE_UNKNOWN;

    }



    const
    char *     Token_TypeToString (
        TOKEN_DATA      *this,
        uint16_t        type
    )
    {

        // Do initialization.
        if (type > TOKEN_TYPE_USER) {
            return "";
        }

        // Return to caller.
        return pTypeStr[type];
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TOKEN_DATA *     Token_Alloc (
        void
    )
    {
        TOKEN_DATA       *this;
        uint32_t        cbSize = sizeof(TOKEN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TOKEN_DATA *     Token_New (
        void
    )
    {
        TOKEN_DATA       *this;
        
        this = Token_Alloc( );
        if (this) {
            this = Token_Init(this);
        } 
        return this;
    }


    TOKEN_DATA *    Token_NewCharW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32CHR_T        chr
    )
    {
        TOKEN_DATA       *this;

        this = Token_New( );
        if (this) {
            Token_SetupCharW32(this, pLoc, cls, chr);
        }
        return this;
    }


    TOKEN_DATA *    Token_NewInteger(
        SRCLOC          *pLoc,
        int32_t         cls,
        int64_t         integer
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *this;

        this = Token_New( );
        if (this) {
            eRc = Token_SetupFnLCC(this, pLoc, cls);
            Token_setInteger(this, integer);
        }
        return this;
    }


    TOKEN_DATA *   Token_NewFromW32STR(
        SRCLOC          *pLoc,
        int32_t         cls,
        W32STR_DATA     *pStrW32
    )
    {
        TOKEN_DATA      *this;
        ERESULT         eRc;
        uint32_t        token;

        this = Token_New( );
        if (this) {
            eRc = Token_SetupFnLCC(this, pLoc, cls);
            token = szTbl_StringW32ToToken(szTbl_Shared(), W32Str_getData(pStrW32));
            this->data.strToken = token;
            this->data.type = TOKEN_TYPE_STRTOKEN;
        }
        return this;
    }


    TOKEN_DATA *    Token_NewStrA(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        char            *pStrA
    )
    {
        TOKEN_DATA      *this;
        ERESULT         eRc;
        uint32_t        token;

        this = Token_New( );
        if (this) {
            eRc = Token_SetupFnLCC(this, pLoc, cls);
            token = szTbl_StringToToken(szTbl_Shared(), pStrA);
            this->data.strToken = token;
            this->data.type = TOKEN_TYPE_STRTOKEN;
        }
        return this;
    }


    TOKEN_DATA *    Token_NewStrW32(
        SRCLOC          *pLoc,
        int32_t         cls,
        const
        W32CHR_T        *pStrW32
    )
    {
        TOKEN_DATA       *this;
        ERESULT         eRc;
        uint32_t        token;

        this = Token_New( );
        if (this) {
            eRc = Token_SetupFnLCC(this, pLoc, cls);
            token = szTbl_StringW32ToToken(szTbl_Shared(), pStrW32);
            this->data.strToken = token;
            this->data.type = TOKEN_TYPE_STRTOKEN;
        }
        return this;
    }


    TOKEN_DATA *    Token_NewStrToken(
        SRCLOC          *pLoc,
        int32_t         cls,
        uint32_t        token
    )
    {
        TOKEN_DATA      *this;
        ERESULT         eRc;

        this = Token_New( );
        if (this) {
            eRc = Token_SetupFnLCC(this, pLoc, cls);
            this->data.strToken = token;
            this->data.type = TOKEN_TYPE_STRTOKEN;
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          C h a r
    //---------------------------------------------------------------

    W32CHR_T        Token_getChrW32(
        TOKEN_DATA      *this
    )
    {
        W32CHR_T        chr = -1;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
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


    bool            Token_setChrW32(
        TOKEN_DATA      *this,
        W32CHR_T        value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
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



    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------

    int32_t         Token_getClass(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.cls;
    }


    bool            Token_setClass(
        TOKEN_DATA      *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.cls = value;
        return true;
    }



    //---------------------------------------------------------------
    //                          C o l N o
    //---------------------------------------------------------------

    uint16_t        Token_getColNo(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.src.colNo;
    }


    bool            Token_setColNo(
        TOKEN_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.colNo = value;
        return true;
    }



    //---------------------------------------------------------------
    //                   F i l e  I n d e x
    //---------------------------------------------------------------

    uint32_t        Token_getFileIndex(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.src.fileIndex;
    }


    bool            Token_setFileIndex(
        TOKEN_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.fileIndex = value;
        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------

    int64_t         Token_getInteger(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (TOKEN_TYPE_INTEGER == this->data.type) {
            return this->data.integer;
        }
        return 0;
    }


    bool            Token_setInteger(
        TOKEN_DATA      *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->data.type = TOKEN_TYPE_INTEGER;
        this->data.integer = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------

    uint16_t        Token_getLen(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.len;
    }


    bool            Token_setLen(
        TOKEN_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        this->data.len = value;
        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------

    uint32_t        Token_getLineNo(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.src.lineNo;
    }

    bool            Token_setLineNo(
        TOKEN_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.lineNo = value;
        return true;
    }



    SRCLOC *        Token_getLoc(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->data.src;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------

    int16_t         Token_getMisc(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.misc;
    }


    bool            Token_setMisc(
        TOKEN_DATA      *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.misc = value;
        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------

    int64_t         Token_getOffset(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.src.offset;
    }


    bool            Token_setOffset(
        TOKEN_DATA      *this,
        int64_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.src.offset = value;
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Token_getSize (
        TOKEN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Token_getSuperVtbl (
        TOKEN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                        S t r i n g
    //---------------------------------------------------------------

    uint32_t        Token_getStrToken(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (TOKEN_TYPE_STRTOKEN == this->data.type) {
            return this->data.strToken;
        }
        return 0;
    }


    bool            Token_setStrToken(
        TOKEN_DATA      *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->data.type = TOKEN_TYPE_STRTOKEN;
        this->data.strToken = value;

        return true;
    }



    bool            Token_setStrW32(
        TOKEN_DATA      *this,
        const
        W32CHR_T        *pStr
    )
    {
        uint32_t        token;

#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
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


    //---------------------------------------------------------------
    //                            T e x t
    //---------------------------------------------------------------

    char *          Token_getTextA(
        TOKEN_DATA      *this
    )
    {
        char            *pStrA = NULL;
        const
        char            *pStrA2 = NULL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate( this ) ) {
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



    ASTR_DATA *     Token_getTextAStr(
        TOKEN_DATA      *this
    )
    {
        const
        char            *pStrA = NULL;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate( this ) ) {
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



    //---------------------------------------------------------------
    //                            T y p e
    //---------------------------------------------------------------

    uint16_t        Token_getType(
        TOKEN_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->data.type;
    }


    bool            Token_setType(
        TOKEN_DATA      *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        this->data.type = value;
        return true;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Token_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TOKEN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Token_Assign (
        TOKEN_DATA		*this,
        TOKEN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Token_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
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

            case TOKEN_TYPE_DOUBLE:
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


        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Token_Compare (
        TOKEN_DATA     *this,
        TOKEN_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Token_Validate(pOther)) {
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

            case TOKEN_TYPE_DOUBLE:
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
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Token      *pCopy = Token_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TOKEN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TOKEN_DATA *     Token_Copy (
        TOKEN_DATA       *this
    )
    {
        TOKEN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Token_New( );
        if (pOther) {
            eRc = Token_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Token_Dealloc (
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
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TOKEN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Token_FreeData(this);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Token_Disable (
        TOKEN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Token_Enable (
        TOKEN_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TOKEN_DATA *   Token_Init (
        TOKEN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TOKEN_DATA);
        //ERESULT         eRc;
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TOKEN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Token_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

    #ifdef NDEBUG
    #else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Token::sizeof(TOKEN_DATA) = %lu\n", sizeof(TOKEN_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TOKEN_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Token_IsEnabled (
        TOKEN_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = Token_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Token", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Token_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TOKEN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TOKEN_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Token_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return Token_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Token_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Token_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Token_ToJson;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Token_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == Token_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                              S e t
    //---------------------------------------------------------------

    ERESULT     Token_SetupCharW32(
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
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Token_SetupFnLCC(this, pLoc, cls);
        if (ERESULT_FAILED(eRc)) {
            return eRc;
        }

        Token_setChrW32(this, chr);

        return ERESULT_SUCCESS;
    }



    ERESULT         Token_SetupFnLCC(
        TOKEN_DATA      *this,
        SRCLOC          *pLoc,
        int32_t         cls
    )
    {

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
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



    ERESULT     Token_SetupStrW32(
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
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (pStr == NULL) {
            return ERESULT_INVALID_PARAMETER;
        }

        eRc = Token_SetupFnLCC( this, pLoc, cls );
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
    //                       T o  S r c L o c
    //---------------------------------------------------------------

    SRCLOC_DATA *   Token_ToSrcLoc(
        TOKEN_DATA      *this
    )
    {
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        return SrcLoc_NewSrcLoc(&this->data.src);
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     Token_ToDataString(
        TOKEN_DATA      *this
    )
    {
        ASTR_DATA       *pStr;
        const
        char            *pString;
        //ERESULT         eRc;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !Token_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();

        switch (this->data.type) {

            case TOKEN_TYPE_CHAR:
                AStr_AppendA(pStr, this->data.chr);
                break;

           case TOKEN_TYPE_W32CHAR:
                if (ascii_isPrintableW32(this->data.w32chr[0])) {
                    AStr_AppendCharW32(pStr, this->data.w32chr[0]);
                }
                else {
                    AStr_AppendCharA(pStr, ' ');
                }
                break;

            case TOKEN_TYPE_INTEGER:
                AStr_AppendPrint(pStr, "%lld ", this->data.integer);
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


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Token_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Token_ToDebugString (
        TOKEN_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        W32CHR_T        w32;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Token_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    Token_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        AStr_AppendPrint(
                         pStr,
                         "\tfileIndex=%2d offset=%4lld line=%2d col=%d cls=%4d ",
                         Token_getFileIndex(this),
                         Token_getOffset(this),
                         Token_getLineNo(this),
                         Token_getColNo(this),
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

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            Token_Validate (
        TOKEN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TOKEN))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(TOKEN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


