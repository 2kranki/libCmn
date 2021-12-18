// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   LexJ.c
 *  Generated 12/09/2020 23:26:59
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
#include        <LexJ_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
#include        <SrcErrors.h>
#include        <trace.h>
#include        <utf8.h>
#include        <W32Str.h>






#ifdef  __cplusplus
extern "C" {
#endif
    
    typedef struct LexJ_Class2Str_s {
        int32_t         cls;
        const
        char            *pStr;
    } LEXJ_CLASS2STR;
    
    static
    LEXJ_CLASS2STR      Cls2Str[] = {
        {LEXJ_CLASS_EOF,            "LEXJ_CLASS_EOF"},
        {LEXJ_CONSTANT_CHAR,        "LEXJ_CONSTANT_CHAR"},
        {LEXJ_CONSTANT_CHAR_WIDE,   "LEXJ_CONSTANT_CHAR_WIDE"},
        {LEXJ_CONSTANT_FLOAT,       "LEXJ_CONSTANT_FLOAT"},
        {LEXJ_CONSTANT_INTEGER,     "LEXJ_CONSTANT_INTEGER"},
        {LEXJ_CONSTANT_STRING,      "LEXJ_CONSTANT_STRING"},
        {LEXJ_CONSTANT_STRING_WIDE, "LEXJ_CONSTANT_STRING_WIDE"},
        {LEXJ_SEP_COLON,            "LEXJ_SEP_COLON"},
        {LEXJ_SEP_COMMA,            "LEXJ_SEP_COMMA"},
        {LEXJ_SEP_EQUAL,            "LEXJ_SEP_EQUAL"},
        {LEXJ_SEP_LBRACKET,         "LEXJ_SEP_LBRACKET"},
        {LEXJ_SEP_LBRACE,           "LEXJ_SEP_LBRACE"},
        {LEXJ_SEP_MINUS,            "LEXJ_SEP_MINUS"},
        {LEXJ_SEP_PLUS,             "LEXJ_SEP_PLUS"},
        {LEXJ_SEP_RBRACKET,         "LEXJ_SEP_RBRACKET"},
        {LEXJ_SEP_RBRACE,           "LEXJ_SEP_RBRACE"},
        {LEXJ_KWD_FALSE,            "LEXJ_KWD_FALSE"},
        {LEXJ_KWD_NULL,             "LEXJ_KWD_NULL"},
        {LEXJ_KWD_TRUE,             "LEXJ_KWD_TRUE"}
    };
    const
    int             cCls2Str = sizeof(Cls2Str) / sizeof(LEXJ_CLASS2STR);

 


    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //              C l a s s  t o  S t r i n g
    //---------------------------------------------------------------

    const
    char *          LexJ_Class2Str(
        int32_t         cls
    )
    {
        int             i;

        for (i=0; i<cCls2Str; i++) {
            if (Cls2Str[i].cls == cls) {
                return Cls2Str[i].pStr;
            }
        }
        return "LEXJ_UNKNOWN_CLASS";
    }


    //---------------------------------------------------------------
    //           P a r s e  Q u o t e l e s s  S t r i n g
    //---------------------------------------------------------------

    // The first character of the string has already been parsed, but
    // not advanced. So, we just keep accumulating the proper letters
    // until there are no more that are acceptable.

    bool            LexJ_ParseQuotelessString(
        LEXJ_DATA       *this,
        LEX_DATA        *pLex,              // LEX Object Ptr
        LEX_PARSE_DATA  *pData              // Current Parse Data Ptr
    )
    {
        bool            fMore = true;
        bool            fRc;

#ifdef NDEBUG
#else
        if( !LexJ_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        while (fMore) {
            switch (pData->cls2) {
                case ':':
                case ',':
                case '{':
                case '}':
                case '[':
                case ']':
                case ASCII_LEXICAL_EOL:
                case -1:
                    fMore = false;
                    break;
                default:
                    Lex_TokenAppendStringW32(pLex, pData->chr2);
                    fRc = Lex_NextInput(pLex, pData, false);
            }
        }

        return true;
    }




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEXJ_DATA *     LexJ_Alloc (
        void
    )
    {
        LEXJ_DATA       *this;
        uint32_t        cbSize = sizeof(LEXJ_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LEXJ_DATA *     LexJ_New (
        void
    )
    {
        LEXJ_DATA       *this;
        
        this = LexJ_Alloc( );
        if (this) {
            this = LexJ_Init(this);
        } 
        return this;
    }


    LEXJ_DATA *     LexJ_NewA (
        const
        char            *pStrA,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        bool            fRc;

        pStr = AStr_NewA(pStrA);
        if (pStr) {
            this = LexJ_New( );
            if (this) {
                this->pInput = SrcFile_NewFromAStr(
                                            OBJ_NIL,
                                            pStr,
                                            1,
                                            tabSize
                                );
                obj_Release(pStr);
                pStr = OBJ_NIL;
                if (OBJ_NIL == this->pInput) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

                fRc =   Lex_setSourceInput(
                            (LEX_DATA *)this,
                            (void *)SrcFile_InputAdvance,
                            (void *)SrcFile_InputLookAhead,
                            this->pInput
                        );
                if (!fRc) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

            }
        }
        return this;
    }


    LEXJ_DATA *     LexJ_NewFromAStr(
        ASTR_DATA       *pStr,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this = OBJ_NIL;
        bool            fRc;

        if (pStr) {
            this = LexJ_New( );
            if (this) {
                this->pInput = SrcFile_NewFromAStr(
                                            OBJ_NIL,
                                            pStr,
                                            1,
                                            tabSize
                                );
                if (OBJ_NIL == this->pInput) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

                fRc =   Lex_setSourceInput(
                            (LEX_DATA *)this,
                            (void *)SrcFile_InputAdvance,
                            (void *)SrcFile_InputLookAhead,
                            this->pInput
                        );
                if (!fRc) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

            }
        }
        return this;
    }


    LEXJ_DATA *     LexJ_NewFromFile(
        FILE            *pFile,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this = OBJ_NIL;
        bool            fRc;

        if (pFile) {
            this = LexJ_New( );
            if (this) {
                this->pInput = SrcFile_NewFromFile(
                                            pFile,
                                            1,
                                            tabSize
                                );
                if (OBJ_NIL == this->pInput) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

                fRc =   Lex_setSourceInput(
                            (LEX_DATA *)this,
                            (void *)SrcFile_InputAdvance,
                            (void *)SrcFile_InputLookAhead,
                            this->pInput
                        );
                if (!fRc) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

            }
        }
        return this;
    }


    LEXJ_DATA *     LexJ_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this = OBJ_NIL;
        bool            fRc;

        if (pFilePath) {
            this = LexJ_New( );
            if (this) {
                this->pInput = SrcFile_NewFromPath(
                                            pFilePath,
                                            1,
                                            tabSize
                                );
                if (OBJ_NIL == this->pInput) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

                fRc =   Lex_setSourceInput(
                            (LEX_DATA *)this,
                            (void *)SrcFile_InputAdvance,
                            (void *)SrcFile_InputLookAhead,
                            this->pInput
                        );
                if (!fRc) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }

            }
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          I n p u t
    //---------------------------------------------------------------

    SRCFILE_DATA *  LexJ_getInput (
        LEXJ_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pInput;
    }


    bool            LexJ_setInput (
        LEXJ_DATA       *this,
        SRCFILE_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pInput) {
            obj_Release(this->pInput);
        }
        this->pInput = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //          L o o k  A h e a d  I n t e r f a c e
    //---------------------------------------------------------------

    LA_INTERFACE *  LexJ_getLaInterface (
        LEXJ_DATA       *this
    )
    {
        LEX_DATA        *pLex;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pLex = LexJ_getLex(this);

        return Lex_getLaInterface(pLex);
    }



    //---------------------------------------------------------------
    //                              L e x
    //---------------------------------------------------------------

    inline
    LEX_DATA *      LexJ_getLex(
        LEXJ_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !LexJ_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        LexJ_getPriority (
        LEXJ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            LexJ_setPriority (
        LEXJ_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
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
    
    uint32_t        LexJ_getSize (
        LEXJ_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  LexJ_getSuperVtbl (
        LEXJ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
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
        ERESULT eRc = LexJ_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LEXJ object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         LexJ_Assign (
        LEXJ_DATA       *this,
        LEXJ_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!LexJ_Validate(pOther)) {
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
    int             LexJ_Compare (
        LEXJ_DATA     *this,
        LEXJ_DATA     *pOther
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
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!LexJ_Validate(pOther)) {
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
        LexJ      *pCopy = LexJ_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEXJ object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEXJ_DATA *     LexJ_Copy (
        LEXJ_DATA       *this
    )
    {
        LEXJ_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LEXJ_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = LexJ_New( );
        if (pOther) {
            eRc = LexJ_Assign(this, pOther);
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

    void            LexJ_Dealloc (
        OBJ_ID          objId
    )
    {
        LEXJ_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LEXJ_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        LexJ_setInput(this, OBJ_NIL);

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
        LexJ      *pDeepCopy = LexJ_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEXJ object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEXJ_DATA *     LexJ_DeepyCopy (
        LEXJ_DATA       *this
    )
    {
        LEXJ_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = LexJ_New( );
        if (pOther) {
            eRc = LexJ_Assign(this, pOther);
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
    ERESULT         LexJ_Disable (
        LEXJ_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

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
    ERESULT         LexJ_Enable (
        LEXJ_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LEXJ_DATA *   LexJ_Init (
        LEXJ_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEXJ_DATA);
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEXJ);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&LexJ_Vtbl);
#ifdef  LEXJ_JSON_SUPPORT
        JsonIn_RegisterClass(LexJ_Class());
#endif
        
        fRc =   Lex_setParserPreExit(
                            (LEX_DATA *)this,
                            (void *)LexJ_ParserPreExit,
                            this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
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
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "LexJ::sizeof(LEXJ_DATA) = %lu\n", 
                sizeof(LEXJ_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LEXJ_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         LexJ_IsEnabled (
        LEXJ_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
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
    //                P a r s e  P r e  E x i t
    //--------------------------------------------------------------

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
     *
     * This method does not use the Output Token, but uses lex_
     * functions to create the parsed token.
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
    int             LexJ_ParserPreExit (
        LEXJ_DATA       *this,
        LEX_DATA        *pLex,              // LEX Object Ptr
        LEX_PARSE_DATA  *pData              // Current Parse Data Ptr
    )
    {
        //ERESULT         eRc;
        bool            fRc;
        int             iRc;
        bool            fMore = true;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LexJ_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        Lex_setFlags(
                     pLex,
                     Lex_getFlags(pLex) & ~(LEX_FLAG_WS | LEX_FLAG_NL | LEX_FLAG_CMT)
        );

        while (fMore) {

            switch (pData->cls1) {

                case ASCII_LEXICAL_WHITESPACE:
                case ASCII_LEXICAL_EOL:
                    TRC_OBJ(this, "\tWhite space/EOL - giving to default parser...\n");
                    return 2;           // Just absorb the WS.
                    break;

                case ASCII_LEXICAL_ALPHA_LOWER:
                case ASCII_LEXICAL_ALPHA_UPPER:
                    TRC_OBJ(this, "\tScanning Quoteless string from (a..z)...\n");
                    pData->clsNew = LEXJ_CONSTANT_STRING;
                    LexJ_ParseQuotelessString(this, pLex, pData);
                    pStr = AStr_NewFromW32Str(this->super.pStr);
                    if (pStr) {
                        AStr_Trim(pStr);
                        if (0 == AStr_CompareA(pStr, "null")) {
                            pData->clsNew = LEXJ_KWD_NULL;
                            fMore = false;
                            obj_Release(pStr);
                            TRC_OBJ(this, "\tkeyword: null\n");
                            break;
                        }
                        if (0 == AStr_CompareA(pStr, "false")) {
                            pData->clsNew = LEXJ_KWD_FALSE;
                            fMore = false;
                            obj_Release(pStr);
                            TRC_OBJ(this, "\tkeyword: false\n");
                            break;
                        }
                        if (0 == AStr_CompareA(pStr, "true")) {
                            pData->clsNew = LEXJ_KWD_TRUE;
                            fMore = false;
                            obj_Release(pStr);
                            TRC_OBJ(this, "\tkeyword: true\n");
                            break;
                        }
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                    fMore = false;
                    TRC_OBJ(
                            this,
                            "\t\tstring: (%d)\"%ls\"\n",
                            W32Str_getLength(this->super.pStr),
                            W32Str_getData(this->super.pStr)
                    );
                    break;

                case ASCII_LEXICAL_NUMBER:
                    TRC_OBJ(this, "\tScanning Number...\n");
                    pData->clsNew = Lex_ParseNumber(pLex, pData);
                    switch (pData->clsNew) {
                        case LEX_CONSTANT_FLOAT:
                            pData->clsNew = LEXJ_CONSTANT_FLOAT;
                            TRC_OBJ(this, "\t...Floating Point\n");
                            break;
                        case LEX_CONSTANT_INTEGER:
                            pData->clsNew = LEXJ_CONSTANT_INTEGER;
                            TRC_OBJ(this, "\t...Integer\n");
                            break;
                        default:
                            TRC_OBJ(
                                    this,
                                    "\t...Unknown number type! %3d\n",
                                    pData->clsNew
                            );
                            break;
                    }
                    TRC_OBJ(
                            this,
                            "\t\tnumber: \"%ls\"\n",
                            W32Str_getData(this->super.pStr)
                    );
                    fMore = false;
                    break;

                case '"':           /*** '"' ***/
                    // Quoted String
                    //TODO: "..." {<white-space> "..."}
                    TRC_OBJ(this, "\tScanning Quoted string...\n");
                    Lex_ParseTokenTruncate(pLex);
                    pData->clsNew = LEXJ_CONSTANT_STRING;
                    fMore = false;
                    if (pData->cls2 == '"') {         // Empty String
                        fRc = Lex_NextInput(pLex, pData, false);
                    } else {
                        // Token starts with 2nd initial token.
                        for (;;) {
                            iRc = Lex_ParseChrCon(pLex, pData, '"');
                            if (iRc == -1) {
                                SrcErrors_AddFatalFromTokenA(
                                                    OBJ_NIL,
                                                    &pData->token2,
                                                    "Malformed String constant"
                                );
                            } else if (iRc == 0) {
                                break;
                            } else if (iRc == 1) {
                                continue;
                            } else {
                                SrcErrors_AddFatalFromTokenA(
                                                    OBJ_NIL,
                                                    &pData->token2,
                                                    "Unknown Error in String constant"
                                );
                            }
                        }
                        if (iRc == 0) {
                            fRc = Lex_NextInput(pLex, pData, false);
                        } else {
                            SrcErrors_AddFatalFromTokenA(
                                                OBJ_NIL,
                                                &pData->token2,
                                                "Malformed String constant"
                            );
                        }
                    }
                    TRC_OBJ(
                            this,
                            "\t\tstring: (%d)\"%ls\"\n",
                            W32Str_getLength(this->super.pStr),
                            W32Str_getData(this->super.pStr)
                    );
                    break;

                case '#':           /*** '#' ***/
                    // Comment
                    TRC_OBJ(this, "\tSkipping # comment...\n");
                    for (;;) {
                        if (pData->cls2 == ASCII_LEXICAL_EOL) {
                            fRc = Lex_NextInput(pLex, pData, false);
                            break;
                        }
                        fRc = Lex_NextInput(pLex, pData, false);
                    }
                    TRC_OBJ(this, "\t...Comment # skipped...\n");
                    return 1;           // Just absorb the WS.
                    break;

                case '+':           /*** '+' ***/
                    pData->clsNew = LEXJ_SEP_PLUS;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: +\n");
                    break;

                case ',':           /*** ',' ***/
                    pData->clsNew = LEXJ_SEP_COMMA;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: ,\n");
                    break;

                case '-':           /*** '-' ***/
                    pData->clsNew = LEXJ_SEP_MINUS;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: -\n");
                    break;

                case '/':           /*** '/' ***/
                    if ('/' == pData->cls2) {
                        TRC_OBJ(this, "\tSkipping // comment - giving to default parser...\n");
                        return 2;           // Just absorb the WS.
                        break;
                    } else if ('*' == pData->cls2) {
                        TRC_OBJ(this, "\tSkipping /**/ comment - giving to default parser...\n");
                        return 2;           // Just absorb the WS.
                    } else {
                        TRC_OBJ(this, "\tScanning Quoteless string...\n");
                        LexJ_ParseQuotelessString(this, pLex, pData);
                        pData->clsNew = LEX_CONSTANT_STRING;
                        fMore = false;
                        TRC_OBJ(
                                this,
                                "\t\tstring: (%d)\"%ls\"\n",
                                W32Str_getLength(this->super.pStr),
                                W32Str_getData(this->super.pStr)
                        );
                    }
                    break;

                case ':':           /*** ':' ***/
                    pData->clsNew = LEXJ_SEP_COLON;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: :\n");
                    break;

                case '=':           /*** '=' ***/
                    pData->clsNew = LEXJ_SEP_EQUAL;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: :\n");
                    break;

                case '[':           /*** '[' ***/
                    pData->clsNew = LEXJ_SEP_LBRACKET;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: [\n");
                    break;

                case ']':           /*** ']' ***/
                    pData->clsNew = LEXJ_SEP_RBRACKET;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: ]\n");
                    break;

                case '{':           /*** '{' ***/
                    pData->clsNew = LEXJ_SEP_LBRACE;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: {\n");
                    break;

                case '}':           /*** '}' ***/
                    pData->clsNew = LEXJ_SEP_RBRACE;
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: }\n");
                    break;

                default:
                    TRC_OBJ(this, "\tScanning Quoteless string...\n");
                    LexJ_ParseQuotelessString(this, pLex, pData);
                    pData->clsNew = LEX_CONSTANT_STRING;
                    fMore = false;
                    TRC_OBJ(
                            this,
                            "\t\tstring: (%d)\"%ls\"\n",
                            W32Str_getLength(this->super.pStr),
                            W32Str_getData(this->super.pStr)
                    );
                    break;
            }

        }

        // Return to caller.
        TRC_OBJ(this, "...%s - Completed token\n", __func__);
        return 0;
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
        void        *pMethod = LexJ_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "LexJ", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          LexJ_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEXJ_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!LexJ_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LEXJ_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)LexJ_Class();
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
                            return LexJ_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return LexJ_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LEXJ_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return LexJ_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return LexJ_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return LexJ_ToDebugString;
                        }
#ifdef  LEXJ_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return LexJ_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return LexJ_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == LexJ_ToDebugString)
                    return "ToDebugString";
#ifdef  LEXJ_JSON_SUPPORT
                if (pData == LexJ_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //--------------------------------------------------------------
    //                  T o k e n  A d v a n c e
    //--------------------------------------------------------------

    TOKEN_DATA *    LexJ_TokenAdvance(
        LEXJ_DATA        *this,
        uint16_t        numChrs
    )
    {
        TOKEN_DATA      *pToken = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LexJ_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        pToken = Lex_TokenAdvance((LEX_DATA *)this, numChrs);

        return pToken;
    }



    //--------------------------------------------------------------
    //               T o k e n  L o o k  A h e a d
    //--------------------------------------------------------------

    TOKEN_DATA *    LexJ_TokenLookAhead(
        LEXJ_DATA       *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LexJ_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pToken = Lex_TokenLookAhead((LEX_DATA *)this, num);

        // Return to caller.
#ifdef NDEBUG
#else
        if( obj_Trace(this) ) {
            fprintf(stderr, "\tLexJ_TokenLookAhead(%d)\n", num);
            if (pToken) {
                ASTR_DATA       *pStr2 = Token_ToDataString(pToken);
                fprintf(stderr, "\t\tToken Class  = %d\n", Token_getClass(pToken));
                fprintf(stderr, "\t\tToken String = \"%s\"\n", AStr_getData(pStr2));
                obj_Release(pStr2);
            } else {
                fprintf(stderr, "\t\tNULL Token!\n");
                DEBUG_BREAK();
                return OBJ_NIL;
            }
        }
#endif
        return pToken;
    }



    //--------------------------------------------------------------
    //                      T o k e n  P u s h
    //--------------------------------------------------------------

    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    ERESULT         LexJ_TokenPush(
        LEXJ_DATA       *this,
        TOKEN_DATA      *pToken
    )
    {
        ERESULT         eRc;

        // Do initialization.

        eRc = Lex_TokenPush((LEX_DATA *)this, pToken);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LexJ_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexJ_ToDebugString (
        LEXJ_DATA      *this,
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
        if (!LexJ_Validate(this)) {
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
                    LexJ_getSize(this),
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
    bool            LexJ_Validate (
        LEXJ_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LEXJ))
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


        if (!(obj_getSize(this) >= sizeof(LEXJ_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


