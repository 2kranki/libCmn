// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   lexj.c
 *	Generated 07/02/2017 09:15:13
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
#include <lexj_internal.h>
#include <SrcErrors.h>
#include <trace.h>
#include <W32Str.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //           P a r s e  Q u o t e l e s s  S t r i n g
    //---------------------------------------------------------------
    
    // The first character of the string has already been parsed, but
    // not advanced. So, we just keep accumulating the proper letters
    // until there are no more that are acceptable.
    
    bool            lexj_ParseQuotelessString(
        LEXJ_DATA       *this
    )
    {
        int32_t         cls;
        TOKEN_DATA      *pInput;
        
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        for (;;) {
            pInput = lex_InputAdvance((LEX_DATA *)this, 1);
            cls = Token_getClass(pInput);
            if ((cls == ':') || (cls == ',')
                || (cls == '{') || (cls == '}')
                || (cls == '[') || (cls == ']')
                || (cls == ASCII_LEXICAL_EOL) || (cls == -1)) {
                break;
            }
            else {
                lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
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

    LEXJ_DATA *     lexj_Alloc(
    )
    {
        LEXJ_DATA       *this;
        uint32_t        cbSize = sizeof(LEXJ_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LEXJ_DATA *     lexj_New(
    )
    {
        LEXJ_DATA       *this;
        
        this = lexj_Alloc( );
        if (this) {
            this = lexj_Init(this);
        } 
        return this;
    }


    LEXJ_DATA *     lexj_NewA(
        const
        char            *pStr,
        uint16_t        tabSize,        // Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this = OBJ_NIL;
        ASTR_DATA       *pStrA = OBJ_NIL;

        pStrA = AStr_NewA(pStr);
        if (pStrA) {
            this = lexj_Alloc( );
            if (this) {
                this = lexj_InitAStr(this, pStrA, tabSize, fExpandTabs);
            }
            obj_Release(pStrA);
            pStrA = OBJ_NIL;
        }
        return this;
    }
    
    
    
    LEXJ_DATA *     lexj_NewFromAStr(
        ASTR_DATA       *pStr,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this;
        
        this = lexj_Alloc( );
        if (this) {
            this = lexj_InitAStr(this, pStr, tabSize, fExpandTabs);
        }
        return this;
    }
    
    
    
    LEXJ_DATA *     lexj_NewFromFile(
        FILE            *pFile,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this;
        
        this = lexj_Alloc( );
        if (this) {
            this = lexj_InitFile(this, pFile, tabSize, fExpandTabs);
        }
        return this;
    }
    
    
    
    LEXJ_DATA *     lexj_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        LEXJ_DATA       *this;
        
        this = lexj_Alloc( );
        if (this) {
            this = lexj_InitPath(this, pFilePath, tabSize, fExpandTabs);
        }
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    SRCFILE_DATA *  lexj_getInput(
        LEXJ_DATA       *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        lexj_setLastError(this, ERESULT_SUCCESS);
        return this->pInput;
    }
    
    
    bool            lexj_setInput(
        LEXJ_DATA       *this,
        SRCFILE_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pInput) {
            obj_Release(this->pInput);
        }
        this->pInput = pValue;
        
        lexj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         lexj_getLastError(
        LEXJ_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            lexj_setLastError(
        LEXJ_DATA       *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    uint16_t        lexj_getPriority(
        LEXJ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        lexj_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            lexj_setPriority(
        LEXJ_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        lexj_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = lexj__Assign(this,pOther);
     @endcode
     @param     this    LEXJ object pointer
     @param     pOther  a pointer to another LEXJ object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         lexj_Assign(
        LEXJ_DATA		*this,
        LEXJ_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !lexj_Validate(pOther) ) {
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
        
        //goto eom;

        // Return to caller.
        lexj_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        lexj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return lexj_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        lexj      *pCopy = lexj_Copy(this);
     @endcode
     @param     this    LEXJ object pointer
     @return    If successful, a LEXJ object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the LEXJ object.
     */
    LEXJ_DATA *     lexj_Copy(
        LEXJ_DATA       *this
    )
    {
        LEXJ_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = lexj_New( );
        if (pOther) {
            eRc = lexj_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        lexj_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            lexj_Dealloc(
        OBJ_ID          objId
    )
    {
        LEXJ_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        lexj_setInput(this, OBJ_NIL);

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

    ERESULT         lexj_Disable(
        LEXJ_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            lexj_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return lexj_getLastError(this);
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        lexj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         lexj_Enable(
        LEXJ_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        lexj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LEXJ_DATA *     lexj_Init(
        LEXJ_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEXJ_DATA);
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

        this = (OBJ_ID)lex_Init((LEX_DATA *)this, 4);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEXJ);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&lexj_Vtbl);
        
        lexj_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = ObjArray_New( );

        fRc =   lex_setParserFunction(
                            (LEX_DATA *)this,
                            (void *)lexj_ParseTokenJson,
                            this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(LEXJ_DATA));
    #endif

        return this;
    }

     
    LEXJ_DATA *     lexj_InitAStr(
        LEXJ_DATA       *this,
        ASTR_DATA       *pStr,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        bool            fRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = (OBJ_ID)lexj_Init(this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->pInput = srcFile_NewFromAStr(
                                    OBJ_NIL,
                                    pStr,
                                    1,
                                    tabSize
                        );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        fRc =   lex_setSourceInput(
                    (LEX_DATA *)this,
                    (void *)srcFile_InputAdvance,
                    (void *)srcFile_InputLookAhead,
                    this->pInput
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(LEXJ_DATA));
#endif
        
        return this;
    }
    
    
    LEXJ_DATA *     lexj_InitFile(
        LEXJ_DATA       *this,
        FILE            *pFile,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        bool            fRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = (OBJ_ID)lexj_Init(this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->pInput =  srcFile_NewFromFile(
                            pFile,
                            1,
                            tabSize
                        );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        fRc =   lex_setSourceInput(
                    (LEX_DATA *)this,
                    (void *)srcFile_InputAdvance,
                    (void *)srcFile_InputLookAhead,
                    this->pInput
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(LEXJ_DATA));
#endif
        
        return this;
    }
    
    
    LEXJ_DATA *     lexj_InitPath(
        LEXJ_DATA       *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize,		// Tab Spacing if any (0 will default to 4)
        bool            fExpandTabs
    )
    {
        bool            fRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = (OBJ_ID)lexj_Init(this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        this->pInput =  srcFile_NewFromPath(
                                        pFilePath,
                                        1,
                                        tabSize
                        );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        fRc =   lex_setSourceInput(
                                      (LEX_DATA *)this,
                                      (void *)srcFile_InputAdvance,
                                      (void *)srcFile_InputLookAhead,
                                      this->pInput
                                      );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(LEXJ_DATA));
#endif
        
        return this;
    }
    
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         lexj_IsEnabled(
        LEXJ_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            lexj_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        lexj_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //--------------------------------------------------------------
    //                      P a r s e  T o k e n
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lexj_ParseToken(
        LEXJ_DATA       *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        fRc = lexj_ParseTokenJson(this, &this->super.token);
        
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA           *pStr = Token_ToDebugString(&this->super.token, 0);
            TRC_OBJ( this, "lexj_ParseToken:  %s \n", AStr_getData(pStr) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        
        // Return to caller.
        return &this->super.token;
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
    
    bool            lexj_ParseTokenJson(
        LEXJ_DATA       *this,
        TOKEN_DATA      *pTokenOut          // Optional Output Token
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *pInput;
        int32_t         cls;
        int32_t         newCls = 0;
        bool            fMore = true;
        bool            fSaveStr = true;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        TRC_OBJ(this, "%s:\n", __func__);
        
        while (fMore) {
            pInput = lex_InputLookAhead((LEX_DATA *)this, 1);
            if (pInput) {
                cls = Token_getClass(pInput);
            }
            else {
                pInput = lex_ParseEOF(((LEX_DATA *)this));
                cls = Token_getClass(pInput);
                DEBUG_BREAK();
            }
            eRc = lex_ParseTokenSetup(((LEX_DATA *)this), pInput);
            if (cls == EOF) {
                fSaveStr = false;
                newCls = LEX_CLASS_EOF;
                break;
            }
            
            switch (cls) {
                    
                case ASCII_LEXICAL_WHITESPACE:
                    for (;;) {
                        pInput = lex_InputAdvance((LEX_DATA *)this, 1);
                        cls = Token_getClass(pInput);
                        if (cls == ASCII_LEXICAL_WHITESPACE) {
                        }
                        else {
                            break;
                        }
                    }
                    break;
                    
                case ASCII_LEXICAL_EOL:
                    for (;;) {
                        pInput = lex_InputAdvance((LEX_DATA *)this, 1);
                        cls = Token_getClass(pInput);
                        if (cls == ASCII_LEXICAL_WHITESPACE) {
                        }
                        else {
                            break;
                        }
                    }
                    break;
                    
                case ASCII_LEXICAL_ALPHA_LOWER:
                case ASCII_LEXICAL_ALPHA_UPPER:
                    lexj_ParseQuotelessString(this);
                    pStr = AStr_NewFromW32Str(this->super.pStr);
                    if (pStr) {
                        AStr_Trim(pStr);
                        if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "null")) {
                            newCls = LEXJ_KWD_NULL;
                            fMore = false;
                            obj_Release(pStr);
                            TRC_OBJ(this, "\tkeyword: null\n");
                            break;
                        }
                        if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "false")) {
                            newCls = LEXJ_KWD_FALSE;
                            fMore = false;
                            obj_Release(pStr);
                            TRC_OBJ(this, "\tkeyword: false\n");
                            break;
                        }
                        if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "true")) {
                            newCls = LEXJ_KWD_TRUE;
                            fMore = false;
                            obj_Release(pStr);
                            TRC_OBJ(this, "\tkeyword: true\n");
                            break;
                        }
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                    newCls = LEXJ_CONSTANT_STRING;
                    fMore = false;
                    TRC_OBJ(
                            this,
                            "\tquote-less string: \"%ls\"\n",
                            W32Str_getData(this->super.pStr)
                    );
                    break;
                    
                case ASCII_LEXICAL_NUMBER:
                parseNumber:
                    newCls = lex_ParseNumber((LEX_DATA *)this);
                    if (newCls) {
                        uint16_t            type;
                        type = lex_ParseIntegerSuffix((LEX_DATA *)this);
                        Token_setMisc(&this->super.token, type);
                    }
                    TRC_OBJ(
                            this,
                            "\tnumber: \"%ls\"\n",
                            W32Str_getData(this->super.pStr)
                    );
                    fMore = false;
                    break;
                    
                case '"':           /*** '"' ***/
                    // Quoted String
                    //TODO: "..." {<white-space> "..."}
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    lex_ParseTokenTruncate((LEX_DATA *)this);
                    while(lex_ParseChrConWS((LEX_DATA *)this, '"'))
                        ;
                    pInput = lex_InputLookAhead((LEX_DATA *)this, 1);
                    cls = Token_getClass(pInput);
                    if (cls == '"') {
                        lex_InputAdvance((LEX_DATA *)this, 1);
                        newCls = LEX_CONSTANT_STRING;
                        fMore = false;
                        TRC_OBJ(
                                this,
                                "\tquoted string: \"%ls\"\n",
                                W32Str_getData(this->super.pStr)
                        );
                        break;
                    }
                    else {
                        SrcErrors_AddFatalFromTokenA(
                                    OBJ_NIL,
                                    pInput,
                                    "Malformed String Constant"
                        );
                    }
                    break;
                    
                case '#':           /*** '#' ***/
                    // Comment
                    for (;;) {
                        pInput = lex_InputAdvance((LEX_DATA *)this, 1);
                        cls = Token_getClass(pInput);
                        if (cls == ASCII_LEXICAL_EOL) {
                            break;
                        }
                    }
                    break;
                    
                case '+':           /*** '+' ***/
                    newCls = LEXJ_SEP_PLUS;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: +\n");
                    break;
                    
                case ',':           /*** ',' ***/
                    newCls = LEXJ_SEP_COMMA;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: ,\n");
                    break;
                    
                case '-':           /*** '-' ***/
                    newCls = LEXJ_SEP_MINUS;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: -\n");
                    break;
                    
                case '/':           /*** '/' ***/
                    pInput = lex_InputLookAhead((LEX_DATA *)this, 2);
                    cls = Token_getClass(pInput);
                    if( '/' == cls) {
                        // Single Line Comment - // ... <eol>
                        lex_InputAdvance((LEX_DATA *)this, 2);
                        for (;;) {
                            pInput = lex_InputAdvance((LEX_DATA *)this, 1);
                            cls = Token_getClass(pInput);
                            if (cls == ASCII_LEXICAL_EOL) {
                                lex_InputAdvance((LEX_DATA *)this, 1); // Skip over '\n'.
                                break;
                            }
                        }
                        break;
                    }
                    if( '*' == cls) {
                        uint32_t        depth = 1;
                        bool            fMore2 = true;
                        // Multi-line comment - /* ... */
                        pInput = lex_InputAdvance((LEX_DATA *)this, 2);
                        while (fMore2) {
                            pInput = lex_InputLookAhead((LEX_DATA *)this, 1);
                            cls = Token_getClass(pInput);
                            if (cls == '*') {
                                pInput = lex_InputLookAhead((LEX_DATA *)this, 2);
                                cls = Token_getClass(pInput);
                                if (cls == '/') {
                                    lex_InputAdvance((LEX_DATA *)this, 2);
                                    --depth;
                                    if (0 == depth) {
                                        fMore2 = false;
                                    }
                                    continue;
                                }
                            }
                            if (cls == '/') {
                                pInput = lex_InputLookAhead((LEX_DATA *)this, 2);
                                cls = Token_getClass(pInput);
                                if (cls == '*') {
                                    lex_InputAdvance((LEX_DATA *)this, 2);
                                    ++depth;
                                    continue;
                                }
                            }
                            if (cls == -1) {
                                SrcErrors_AddFatalFromTokenA(
                                    OBJ_NIL,
                                    pInput,
                                    "Unexpected EOF within a Comment"
                                );
                            }
                            lex_InputAdvance((LEX_DATA *)this, 1);
                        }
                        break;
                    }
                    lexj_ParseQuotelessString(this);
                    newCls = LEX_CONSTANT_STRING;
                    fMore = false;
                    break;
                    
                case ':':           /*** ':' ***/
                    newCls = LEXJ_SEP_COLON;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: :\n");
                    break;
                    
                case '[':           /*** '[' ***/
                    newCls = LEXJ_SEP_LBRACKET;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: [\n");
                    break;
                    
                case ']':           /*** ']' ***/
                    newCls = LEXJ_SEP_RBRACKET;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: ]\n");
                    break;
                    
                case '{':           /*** '{' ***/
                    newCls = LEXJ_SEP_LBRACE;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: {\n");
                    break;
                    
                case '}':           /*** '}' ***/
                    newCls = LEXJ_SEP_RBRACE;
                    lex_InputAdvance((LEX_DATA *)this, 1);
                    fMore = false;
                    TRC_OBJ(this, "\tseperator: }\n");
                    break;
                    
                default:
                    lexj_ParseQuotelessString(this);
                    newCls = LEX_CONSTANT_STRING;
                    fMore = false;
                    TRC_OBJ(
                            this,
                            "\tquote-less string: \"%ls\"\n",
                            W32Str_getData(this->super.pStr)
                    );
                    break;
            }
            
        }
        
        // Return to caller.
        eRc = lex_ParseTokenFinalize((LEX_DATA *)this, newCls, fSaveStr);
        BREAK_FALSE(ERESULT_IS_SUCCESSFUL(eRc));
        return true;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          lexj_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEXJ_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
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
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return lexj_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return lexj_Enable;
                        }
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
    
    
    
    //--------------------------------------------------------------
    //                  T o k e n  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lexj_TokenAdvance(
        LEXJ_DATA		*this,
        uint16_t        numChrs
    )
    {
        TOKEN_DATA      *pToken = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pToken = lex_TokenAdvance((LEX_DATA *)this, numChrs);
        
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //               T o k e n  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    lexj_TokenLookAhead(
        LEXJ_DATA       *this,
        uint16_t        num
    )
    {
        TOKEN_DATA      *pToken;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pToken = lex_TokenLookAhead((LEX_DATA *)this, num);
        
        // Return to caller.
        return pToken;
    }
    
    
    
    //--------------------------------------------------------------
    //                      T o k e n  P u s h
    //--------------------------------------------------------------
    
    /*  This routine will save the current character on a queue
     *  where it will be retrieved by NextToken().
     */
    ERESULT         lexj_TokenPush(
        LEXJ_DATA       *this,
        TOKEN_DATA      *pToken
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        
        eRc = lex_TokenPush((LEX_DATA *)this, pToken);
        
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
        ASTR_DATA      *pDesc = lexj_ToDebugString(this,4);
     @endcode
     @param     this    LEXJ object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     lexj_ToDebugString(
        LEXJ_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !lexj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(lexj)\n",
                     this
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
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(lexj)}\n", this);
        AStr_AppendA(pStr, str);
        
        lexj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            lexj_Validate(
        LEXJ_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_LEXJ) )
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


        if( !(obj_getSize(this) >= sizeof(LEXJ_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


