// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Lex01.c
 *  Generated 05/30/2020 14:51:55
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
#include        <Lex01_internal.h>
#include        <ascii.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    
    typedef struct Lex01_kwdtbl_entry_s {
        int32_t     value;                    // Lexical Scan Value (ie LEX_CLASS_*)
        uint32_t    tblNum;                   // szTbl Entry Number
        char        *pKwd;                    /* Key Word */
    } LEX01_KWDTBL_ENTRY;

    LEX01_KWDTBL_ENTRY  Lex01_Keywords[] = {
        { LEX_KWD_AUTO,         0,      "auto" },
        { LEX_KWD_BOOL,         0,      "bool" },
        { LEX_KWD_BREAK,        0,      "break" },
        { LEX_KWD_CASE,         0,      "case" },
        { LEX_KWD_CHAR,         0,      "char" },
        { LEX_KWD_CLASS,        0,      "class" },
        { LEX_KWD_COMPLEX,      0,      "complex" },
        { LEX_KWD_CONST,        0,      "const" },
        { LEX_KWD_CONTINUE,     0,      "continue" },
        { LEX_KWD_DEFAULT,      0,      "default" },
        { LEX_KWD_DO,           0,      "do" },
        { LEX_KWD_DOUBLE,       0,      "double" },
        { LEX_KWD_ELSE,         0,      "else" },
        { LEX_KWD_END,          0,      "end" },
        { LEX_KWD_ENUM,         0,      "enum" },
        { LEX_KWD_EXTERN,       0,      "extern" },
        { LEX_KWD_FLOAT,        0,      "float" },
        { LEX_KWD_FOR,          0,      "for" },
        { LEX_KWD_GOTO,         0,      "goto" },
        { LEX_KWD_IF,           0,      "if" },
        { LEX_KWD_IMAGINARY,    0,      "imaginary" },
        { LEX_KWD_INLINE,       0,      "inline" },
        { LEX_KWD_INT,          0,      "int" },
        { LEX_KWD_INT128,       0,      "int128_t" },
        { LEX_KWD_INT16,        0,      "int16_t" },
        { LEX_KWD_INT256,       0,      "int256_t" },
        { LEX_KWD_INT32,        0,      "int32_t" },
        { LEX_KWD_INT64,        0,      "int64_t" },
        { LEX_KWD_INT8,         0,      "int8_t" },
        { LEX_KWD_LONG,         0,      "long" },
        { LEX_KWD_REGISTER,     0,      "register" },
        { LEX_KWD_RESTRICT,     0,      "restrict" },
        { LEX_KWD_RETURN,       0,      "return" },
        { LEX_KWD_SHORT,        0,      "short" },
        { LEX_KWD_SIGNED,       0,      "signed" },
        { LEX_KWD_SIZEOF,       0,      "sizeof" },
        { LEX_KWD_STATIC,       0,      "static" },
        { LEX_KWD_STRUCT,       0,      "struct" },
        { LEX_KWD_SWITCH,       0,      "switch" },
        { LEX_KWD_THIS,         0,      "this" },
        { LEX_KWD_TYPEDEF,      0,      "typedef" },
        { LEX_KWD_UINT128,      0,      "uint128_t" },
        { LEX_KWD_UINT16,       0,      "uint16_t" },
        { LEX_KWD_UINT256,      0,      "uint256_t" },
        { LEX_KWD_UINT32,       0,      "uint32_t" },
        { LEX_KWD_UINT64,       0,      "uint64_t" },
        { LEX_KWD_UINT8,        0,      "uint8_t" },
        { LEX_KWD_UNION,        0,      "union" },
        { LEX_KWD_UNSIGNED,     0,      "unsigned" },
        { LEX_KWD_VOID,         0,      "void" },
        { LEX_KWD_VOLATILE,     0,      "volatile" },
        { LEX_KWD_WHILE,        0,      "while" },
    };

    static
    uint32_t        cLex01_Keywords = sizeof(Lex01_Keywords)/sizeof(LEX01_KWDTBL_ENTRY);
 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Lex01_task_body (
        void            *pData
    )
    {
        //LEX01_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEX01_DATA *     Lex01_Alloc (
        void
    )
    {
        LEX01_DATA       *this;
        uint32_t        cbSize = sizeof(LEX01_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LEX01_DATA *     Lex01_New (
        void
    )
    {
        LEX01_DATA       *this;
        
        this = Lex01_Alloc( );
        if (this) {
            this = Lex01_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      C o m m e n t s
    //---------------------------------------------------------------

    bool            Lex01_getComments (
        LEX01_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex01_getLex(this)) & LEX01_FLAG_RETURN_CM ? true : false;
    }

    bool            Lex01_setComments(
        LEX01_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex01_getLex(this));
        if (fValue)
            flags |= LEX01_FLAG_RETURN_CM;
        else
            flags &= ~LEX01_FLAG_RETURN_CM;
        fRc = Lex_setFlags(Lex01_getLex(this), flags);

        return fRc;
    }



    //---------------------------------------------------------------
    //                      F l a g s
    //---------------------------------------------------------------

    uint32_t        Lex01_getFlags(
        LEX01_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags((LEX_DATA *)this);
    }


    bool            Lex01_setFlags(
        LEX01_DATA      *this,
        uint32_t        value
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = Lex_setFlags((LEX_DATA *)this, value);

        return fRc;
    }



    //---------------------------------------------------------------
    //               L e x i c a l  S c a n n e r
    //---------------------------------------------------------------

    inline
    LEX_DATA *      Lex01_getLex(
        LEX01_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }



    //---------------------------------------------------------------
    //                      N e w - L i n e s
    //---------------------------------------------------------------

    bool            Lex01_getNL (
        LEX01_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex01_getLex(this)) & LEX01_FLAG_RETURN_NL ? true : false;
    }

    bool            Lex01_setNL(
        LEX01_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex01_getLex(this));
        if (fValue)
            flags |= LEX01_FLAG_RETURN_NL;
        else
            flags &= ~LEX01_FLAG_RETURN_NL;
        fRc = Lex_setFlags(Lex01_getLex(this), flags);

        return fRc;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Lex01_getPriority (
        LEX01_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Lex01_setPriority (
        LEX01_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
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
    
    uint32_t        Lex01_getSize (
        LEX01_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Lex01_getStr (
        LEX01_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Lex01_setStr (
        LEX01_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  Lex01_getSuperVtbl (
        LEX01_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      W h i t e - S p a c e
    //---------------------------------------------------------------

    bool            Lex01_getWS (
        LEX01_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex01_getLex(this)) & LEX01_FLAG_RETURN_WS ? true : false;
    }

    bool            Lex01_setWS(
        LEX01_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex01_getLex(this));
        if (fValue)
            flags |= LEX01_FLAG_RETURN_WS;
        else
            flags &= ~LEX01_FLAG_RETURN_WS;
        fRc = Lex_setFlags(Lex01_getLex(this), flags);

        return fRc;
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
        ERESULT eRc = Lex01_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LEX01 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Lex01_Assign (
        LEX01_DATA       *this,
        LEX01_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Lex01_Validate(pOther)) {
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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Lex01_Compare (
        LEX01_DATA     *this,
        LEX01_DATA     *pOther
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
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Lex01_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
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
        Lex01      *pCopy = Lex01_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX01 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX01_DATA *     Lex01_Copy (
        LEX01_DATA       *this
    )
    {
        LEX01_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LEX01_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Lex01_New( );
        if (pOther) {
            eRc = Lex01_Assign(this, pOther);
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

    void            Lex01_Dealloc (
        OBJ_ID          objId
    )
    {
        LEX01_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LEX01_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Lex01_setStr(this, OBJ_NIL);

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
        Lex01      *pDeepCopy = Lex01_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX01 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX01_DATA *     Lex01_DeepyCopy (
        LEX01_DATA       *this
    )
    {
        LEX01_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Lex01_New( );
        if (pOther) {
            eRc = Lex01_Assign(this, pOther);
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
    ERESULT         Lex01_Disable (
        LEX01_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
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
    ERESULT         Lex01_Enable (
        LEX01_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
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

    LEX01_DATA *   Lex01_Init (
        LEX01_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEX01_DATA);
        //ERESULT         eRc;
        bool            fRc;
        uint32_t        i;
        
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEX01);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Lex01_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

        // Initialize the Keyword Table.
        for (i=0; i<cLex01_Keywords; i++) {
            LEX01_KWDTBL_ENTRY  *pEntry = &Lex01_Keywords[i];
            pEntry->tblNum = szTbl_StringToToken(OBJ_NIL, pEntry->pKwd);
        }

        fRc =   Lex_setParserFunction(
                                (LEX_DATA *)this,
                                (void *)Lex01_ParseToken,
                                this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Lex01::sizeof(LEX01_DATA) = %lu\n", 
                sizeof(LEX01_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LEX01_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Lex01_IsEnabled (
        LEX01_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
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
    //                      P a r s e  T o k e n
    //--------------------------------------------------------------

    bool            Lex01_ParseToken(
        LEX01_DATA      *this
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *pToken = OBJ_NIL;
        TOKEN_DATA      *pTokenNext;
        int32_t         cls = LEX_CLASS_UNKNOWN;
        W32CHR_T        chr = -1;
        int32_t         cls2 = LEX_CLASS_UNKNOWN;
        W32CHR_T        chr2 = 1;
        int32_t         clsNew = LEX_CLASS_UNKNOWN;
        bool            fMore = true;
        bool            fSaveStr = true;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Lex01_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        TRC_OBJ(this, "Lex01_ParseToken:\n");

    nextToken:
        pToken =    Lex01_getLex(this)->pSrcChrLookAhead(
                                Lex01_getLex(this)->pSrcObj,
                                 1
                    );
        if (pToken) {
            cls = Token_getClass(pToken);
            chr = Token_getChrW32(pToken);
        }
        else {
            pToken = Lex_ParseEOF(Lex01_getLex(this));
            cls = Token_getClass(pToken);
            chr = -1;
            DEBUG_BREAK();
        }
        eRc = Lex_ParseTokenSetup((LEX_DATA *)this, pToken);
        pTokenNext = Lex_InputLookAhead(Lex01_getLex(this), 1);
        if (pTokenNext) {
            cls2 = Token_getClass(pTokenNext);
            chr2 = Token_getChrW32(pTokenNext);
        }
        switch (cls) {

            case ASCII_LEXICAL_WHITESPACE:
                if (Lex01_getWS(this)) {
                    for (;;) {
                        pToken =    Lex01_getLex(this)->pSrcChrAdvance(
                                                Lex01_getLex(this)->pSrcObj,
                                                 1
                                    );
                        if (pToken) {
                            cls = Token_getClass(pToken);
                            if (ASCII_LEXICAL_WHITESPACE == cls) {
                                Lex_ParseTokenAppendString(
                                                    Lex01_getLex(this),
                                                    pToken
                                );
                                continue;
                            } else {
                                break;
                            }
                        } else {
                            DEBUG_BREAK();
                            //TODO: Issue Fatal Error Message. This should never happen!
                            break;
                        }
                    }
                    clsNew = LEX_CLASS_WHITESPACE;
                    fMore = false;
                }
                else {
                    Lex_InputAdvance(Lex01_getLex(this), 1);
                    goto nextToken;
                }
                break;

            case ASCII_LEXICAL_EOL:
                if (Lex01_getNL(this)) {
                    clsNew = LEX_CLASS_EOL;
                    Lex_InputAdvance(Lex01_getLex(this), 1);
                    fMore = false;
                }
                else {
                    Lex_InputAdvance(Lex01_getLex(this), 1);
                }
                break;

            case '?':           /*** '?' ***/
                TRC_OBJ(this, "\tFound 1st ?\n");
                pToken = Lex_InputLookAhead(Lex01_getLex(this), 2);
                cls = Token_getClass(pToken);
                if( '?' == cls) {
                    TRC_OBJ(this, "\tFound 2nd ?\n");
                    pToken = Lex_InputLookAhead(Lex01_getLex(this), 3);
                    cls = Token_getClass(pToken);
                    TRC_OBJ(this, "\t3rd %d('%c')\n",
                            cls,
                            ((cls >= ' ') && (cls <0x7F) ? cls : ' ')
                            );
                    switch (cls) {
                        case '(':
                            chr = '[';
                            goto setupChr;
                            break;

                        case '/':
                            chr = '\\';
                            goto setupChr;
                            break;

                        case ')':
                            chr = ']';
                            goto setupChr;
                            break;

                        case '\'':
                            chr = '^';
                            goto setupChr;
                            break;

                        case '<':
                            chr = '{';
                            goto setupChr;
                            break;

                        case '!':
                            chr = '|';
                            goto setupChr;
                            break;

                        case '>':
                            chr = '}';
                            goto setupChr;
                            break;

                        case '-':
                            chr = '~';
                            goto setupChr;
                            break;

                        case '=':
                            chr = '#';
                        setupChr:
                            TRC_OBJ(this, "\tFound ??%c -> %c\n", cls, chr);
                            Token_setClass(pToken, chr);
                            Token_setChrW32(pToken, chr);
                            Lex_InputAdvance(Lex01_getLex(this), 2);
                            break;

                        default:
                            // Reset to 1st char.
                            pToken = Lex_InputLookAhead(Lex01_getLex(this), 1);
                            break;
                    }
                }
                break;
            default:
                break;
        }

        eRc = Lex_ParseTokenFinalize(Lex01_getLex(this), clsNew, fSaveStr);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            //TODO: Issue Internal Error Message.
        }

        // Return to caller.
        TRC_OBJ(this, "...Lex01_ParseToken");
        return true;
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
        void        *pMethod = Lex01_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Lex01", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Lex01_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEX01_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Lex01_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LEX01_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Lex01_Class();
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
                            return Lex01_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Lex01_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LEX01_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Lex01_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Lex01_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Lex01_ToDebugString;
                        }
#ifdef  LEX01_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Lex01_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Lex01_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Lex01_ToDebugString)
                    return "ToDebugString";
#ifdef  LEX01_JSON_SUPPORT
                if (pData == Lex01_ToJson)
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
        ASTR_DATA      *pDesc = Lex01_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex01_ToDebugString (
        LEX01_DATA      *this,
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
        if (!Lex01_Validate(this)) {
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
                    Lex01_getSize(this),
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
    bool            Lex01_Validate (
        LEX01_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LEX01))
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


        if (!(obj_getSize(this) >= sizeof(LEX01_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


