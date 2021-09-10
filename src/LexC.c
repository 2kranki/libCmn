// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   LexC.c
 *  Generated 09/02/2021 08:48:25
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
#include        <LexC_internal.h>
#include        <JsonIn.h>
#include        <misc.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.

    typedef struct Lex_Keyword2Tok_s {
        const
        char            str[16];
        int32_t         cls;
    } LEX_KEYWORD2TOK;

    static
    const
    LEX_KEYWORD2TOK      Kwd2Tok[] = {
        {"bool",        LEX_KWD_BOOL},
        {"break",       LEX_KWD_BREAK},
        {"case",        LEX_KWD_CASE},
        {"char",        LEX_KWD_CHAR},
        {"const",       LEX_KWD_CONST},
        {"continue",    LEX_KWD_CONTINUE},
        {"default",     LEX_KWD_DEFAULT},
        {"do",          LEX_KWD_DO},
        {"enum",        LEX_KWD_ENUM},
        {"else",        LEX_KWD_ELSE},
        {"extern",      LEX_KWD_EXTERN},
        {"false",       LEX_KWD_FALSE},
        {"for",         LEX_KWD_FOR},
        {"goto",        LEX_KWD_GOTO},
        {"if",          LEX_KWD_IF},
        {"int",         LEX_KWD_INT},
        {"long",        LEX_KWD_LONG},
        {"offset",      LEX_KWD_OFFSETOF},
        {"register",    LEX_KWD_REGISTER},
        {"return",      LEX_KWD_RETURN},
        {"short",       LEX_KWD_SHORT},
        {"signed",      LEX_KWD_SIGNED},
        {"sizeof",      LEX_KWD_SIZEOF},
        {"static",      LEX_KWD_STATIC},
        {"struct",      LEX_KWD_STRUCT},
        {"switch",      LEX_KWD_SWITCH},
        {"true",        LEX_KWD_TRUE},
        {"typedef",     LEX_KWD_TYPEDEF},
        {"union",       LEX_KWD_UNION},
        {"unsigned",    LEX_KWD_UNSIGNED},
        {"void",        LEX_KWD_VOID},
        {"volatile",    LEX_KWD_VOLATILE},
        {"while",       LEX_KWD_WHILE},
    };
    static
    const
    int             cKwd2Tok = sizeof(Kwd2Tok) / sizeof(LEX_KEYWORD2TOK);





    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    int32_t         LexC_Keyword2Token (
        W32STR_DATA     *pStrW32
    )
    {
        int32_t         iRc = 0;
        char            *pStrA = NULL;
        LEX_KEYWORD2TOK *pEntry;


        pStrA = W32Str_CStringA(pStrW32, 0);
        if (pStrA) {
            pEntry =    misc_SearchBinary(
                                          (void *)pStrA,
                                          (void *)Kwd2Tok,
                                          cKwd2Tok,
                                          sizeof(LEX_KEYWORD2TOK),
                                          offsetof(LEX_KEYWORD2TOK, str),
                                          (void *)strcmp
                        );
            if (pEntry) {
                iRc = pEntry->cls;
            }
            mem_Free(pStrA);
            pStrA = NULL;
        }

        return iRc;
    }


    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            LexC_task_body (
        void            *pData
    )
    {
        //LEXC_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEXC_DATA *     LexC_Alloc (
        void
    )
    {
        LEXC_DATA       *this;
        uint32_t        cbSize = sizeof(LEXC_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    const
    char *          LexC_ClassToString(
        int32_t         value
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        const
        LEX_KEYWORD2TOK *pEntry;

        if (-1 == value) {
            return "LEX_CLASS_EOF";
        }
        if (0 == value) {
            return "LEX_CLASS_UNKNOWN";
        }
        if ((value > 0) && (value < 256)) {
            return "LEX_CLASS_CHAR";
        }
        iMax = cKwd2Tok;
        for (i=0; i<iMax; ++i) {
            pEntry = &Kwd2Tok[i];
            if (pEntry->cls == value ) {
                return pEntry->str;
            };
        }

        return  Lex_ClassToString(value);
    }



    LEXC_DATA *     LexC_New (
        void
    )
    {
        LEXC_DATA       *this;
        
        this = LexC_Alloc( );
        if (this) {
            this = LexC_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //               L e x i c a l  S c a n n e r
    //---------------------------------------------------------------

    LEX_DATA *      LexC_getLex (
        LEXC_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !LexC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        LexC_getPriority (
        LEXC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            LexC_setPriority (
        LEXC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        LexC_getSize (
        LEXC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * LexC_getStr (
        LEXC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        LexC_setStr (
        LEXC_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  LexC_getSuperVtbl (
        LEXC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
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
        ERESULT eRc = LexC_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LEXC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         LexC_Assign (
        LEXC_DATA       *this,
        LEXC_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!LexC_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             LexC_Compare (
        LEXC_DATA     *this,
        LEXC_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!LexC_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        LexC      *pCopy = LexC_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEXC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEXC_DATA *     LexC_Copy (
        LEXC_DATA       *this
    )
    {
        LEXC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LEXC_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = LexC_New( );
        if (pOther) {
            eRc = LexC_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            LexC_Dealloc (
        OBJ_ID          objId
    )
    {
        LEXC_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LEXC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        LexC_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        LexC      *pDeepCopy = LexC_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEXC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEXC_DATA *     LexC_DeepCopy (
        LEXC_DATA       *this
    )
    {
        LEXC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = LexC_New( );
        if (pOther) {
            eRc = LexC_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
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
    ERESULT         LexC_Disable (
        LEXC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         LexC_Enable (
        LEXC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LEXC_DATA *   LexC_Init (
        LEXC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEXC_DATA);
        //ERESULT         eRc;
        bool            fRc;
        
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

        this = (OBJ_ID)Lex_Init((LEX_DATA *)this);          // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of LexC_object.c
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEXC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&LexC_Vtbl);
#ifdef  LEXC_JSON_SUPPORT
        JsonIn_RegisterClass(LexC_Class());
#endif
        
        fRc =   Lex_setParserPostExit(
                            (LEX_DATA *)this,
                            (void *)LexC_ParserPostExit,
                            this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "LexC::sizeof(LEXC_DATA) = %lu\n", 
                sizeof(LEXC_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LEXC_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         LexC_IsEnabled (
        LEXC_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
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
    
    
    
    //--------------------------------------------------------------
    //                    P a r s e r  E x i t s
    //--------------------------------------------------------------

    /*
     This exit is called just before an output token if finalized and
     allows aspects of it to be over-ridden or even skipped.
     The exist can call:
            Lex_TokenAppendStringW32(this, data.chr2);
            fRc = Lex_NextInput(this, &data, false);
     as needed to do its own scan if desired. It should return:
        0 == Accept token as scanned,
        1 == Reset data accumulated and scan next char.
        2 == Keep data as it is and scan next char.

     */
    int             LexC_ParserPostExit (
        LEXC_DATA       *this,
        LEX_DATA        *pLex,              // LEX Object Ptr
        LEX_PARSE_DATA  *pData              // Current Parse Data Ptr
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        //bool            fRc = false;
        int             iRc = 0;
        int             cls;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LexC_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        TRC_OBJ(this, "LexC_ParserPostExit:\n");

        switch (pData->clsNew) {
            case LEX_IDENTIFIER:
                cls = LexC_Keyword2Token(pData->pStr);
                if (cls) {
                    pData->clsNew = cls;
                }
                break;
            default:
                break;
        }

        return iRc;
    }


    /* ParserPreExit() gets the next token from the source file. It
     * saves that token for the file/line/col numbers and then
     * proceeds to build upon it. It accumulates tokens until
     * based on the class/type. When it finds a token which does
     * not belong to that class, it saves the current token
     * string to the string table, and tells the source file
     * to re-use the token which did not match on the next parse.
     * The token returned from this routine has the index of the
     * token string in the string table if it is larger than 1
     * character.
     */

    /*
     This exit allows the entire lexical scan to be over-ridden.
     The exit can call:
            Lex_TokenAppendStringW32(this, data.chr2);
            fRc = Lex_NextInput(this, &data, false);
     as needed to do its own scan if desired. It should return:
        0 == Accept what exit scanned
        1 == Skip to next token and continue scan.
        2 == Continue with default scanner.
     */
    int             LexC_ParserPreExit (
        LEXC_DATA       *this,
        LEX_DATA        *pLex,              // LEX Object Ptr
        LEX_PARSE_DATA  *pData              // Current Parse Data Ptr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //bool            fRc = false;
        //uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LexC_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        TRC_OBJ(this, "LexC_ParserPreExit:\n");

#ifdef NOT_IMPLEMENTED_YET
        switch (cls1) {
            // Note: Unless EOF is reached in a case, each case must leave the input
            // stream with an advance to be made for the first char of the following
            // token.

            case '}':           /*** '}' ***/
                data.clsNew = LEX_SEP_RBRACE;
                break;

            case '~':           /*** '~' ***/
                data.clsNew = LEX_OP_NEG;
                break;

           default:
                break;
        }
#endif

        // Return to caller.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToString(Lex_getToken(pLex));
            TRC_OBJ(this, "...LexC_ParseToken found token=%s", AStr_getData(pStr));
            obj_Release(pStr);
        }
#endif
        return eRc;
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
        void        *pMethod = LexC_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "LexC", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          LexC_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEXC_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LEXC_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)LexC_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return LexC_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return LexC_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LEXC_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return LexC_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return LexC_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return LexC_ToDebugString;
                        }
#ifdef  LEXC_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return LexC_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return LexC_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == LexC_ToDebugString)
                    return "ToDebugString";
#ifdef  LEXC_JSON_SUPPORT
                if (pData == LexC_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LexC_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexC_ToDebugString (
        LEXC_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexC_Validate(this)) {
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
                    LexC_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
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
    bool            LexC_Validate (
        LEXC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LEXC))
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


        if (!(obj_getSize(this) >= sizeof(LEXC_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


