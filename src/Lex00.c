// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Lex00.c
 *  Generated 05/30/2020 14:51:43
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
#include        <Lex00_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Lex00_task_body (
        void            *pData
    )
    {
        //LEX00_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEX00_DATA *     Lex00_Alloc (
        void
    )
    {
        LEX00_DATA       *this;
        uint32_t        cbSize = sizeof(LEX00_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LEX00_DATA *     Lex00_New (
        void
    )
    {
        LEX00_DATA       *this;
        
        this = Lex00_Alloc( );
        if (this) {
            this = Lex00_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      F l a g s
    //---------------------------------------------------------------

    uint32_t        Lex00_getFlags(
        LEX00_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags((LEX_DATA *)this);
    }


    bool            Lex00_setFlags(
        LEX00_DATA      *this,
        uint32_t        value
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
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
    LEX_DATA *      Lex00_getLex (
        LEX00_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }



    //---------------------------------------------------------------
    //                      N e w - L i n e s
    //---------------------------------------------------------------

    bool            Lex00_getNL (
        LEX00_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex00_getLex(this)) & LEX00_FLAG_RETURN_NL ? true : false;
    }

    bool            Lex00_setNL(
        LEX00_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex00_getLex(this));
        if (fValue)
            flags |= LEX00_FLAG_RETURN_NL;
        else
            flags &= ~LEX00_FLAG_RETURN_NL;
        fRc = Lex_setFlags(Lex00_getLex(this), flags);

        return fRc;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Lex00_getPriority (
        LEX00_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Lex00_setPriority (
        LEX00_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
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
    
    uint32_t        Lex00_getSize (
        LEX00_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Lex00_getStr (
        LEX00_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Lex00_setStr (
        LEX00_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  Lex00_getSuperVtbl (
        LEX00_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      W h i t e - S p a c e
    //---------------------------------------------------------------

    bool            Lex00_getWS (
        LEX00_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex00_getLex(this)) & LEX00_FLAG_RETURN_WS ? true : false;
    }

    bool            Lex00_setWS(
        LEX00_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex00_getLex(this));
        if (fValue)
            flags |= LEX00_FLAG_RETURN_WS;
        else
            flags &= ~LEX00_FLAG_RETURN_WS;
        fRc = Lex_setFlags(Lex00_getLex(this), flags);

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
        ERESULT eRc = Lex00_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LEX00 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Lex00_Assign (
        LEX00_DATA       *this,
        LEX00_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Lex00_Validate(pOther)) {
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
    int             Lex00_Compare (
        LEX00_DATA      *this,
        LEX00_DATA      *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Lex00_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Lex00      *pCopy = Lex00_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX00 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX00_DATA *     Lex00_Copy (
        LEX00_DATA       *this
    )
    {
        LEX00_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LEX00_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Lex00_New( );
        if (pOther) {
            eRc = Lex00_Assign(this, pOther);
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

    void            Lex00_Dealloc (
        OBJ_ID          objId
    )
    {
        LEX00_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LEX00_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Lex00_setStr(this, OBJ_NIL);

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
        Lex00      *pDeepCopy = Lex00_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX00 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX00_DATA *     Lex00_DeepyCopy (
        LEX00_DATA       *this
    )
    {
        LEX00_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Lex00_New( );
        if (pOther) {
            eRc = Lex00_Assign(this, pOther);
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
    ERESULT         Lex00_Disable (
        LEX00_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
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
    ERESULT         Lex00_Enable (
        LEX00_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
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

    LEX00_DATA *   Lex00_Init (
        LEX00_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEX00_DATA);
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEX00);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Lex00_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

        fRc =   Lex_setParserFunction(
                                (LEX_DATA *)this,
                                (void *)Lex00_ParseToken,
                                this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Lex00::sizeof(LEX00_DATA) = %lu\n", 
                sizeof(LEX00_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LEX00_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Lex00_IsEnabled (
        LEX00_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
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

    /*!
        ParseToken()'s job is to parse one or more input tokens creating
        1 output token.  It gets the next token from it's input source. It
        saves that token for the file/line/col numbers and then proceeds
        to build upon it. It accumulates input tokens based on the class
        or type into Lex's work string. When it finds a token which does
        not belong to that classes that it is looking for, it saves the
        current output token string to the string table if it is more
        than 1 character, and tells the source file to advance the number
        of input tokens used.

        The token returned from this routine has the index of the
        token string in the string table if it is larger than 1
        character.

        Because on the input side, we use lookahead/advance to avoid
        having to back up the parse unlike some other lexical generators.
     @param     this        object pointer
     @param     pTokenOut   output token pointer
     @return    true == EOF not reached, false == EOF or Error occurred
     */

    bool            Lex00_ParseToken(
        LEX00_DATA      *this,
        TOKEN_DATA      *pTokenOut
    )
    {
        ERESULT         eRc;
        TOKEN_DATA      *pToken;
        int32_t         cls;
        int32_t         clsNew = LEX_CLASS_UNKNOWN;
        W32CHR_T        chr;
        bool            fSavStr = Lex00_getWS(this);

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Lex00_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        TRC_OBJ(this, "Lex00_ParseToken:\n");

    nextToken:
        pToken = Lex_InputLookAhead(Lex00_getLex(this), 1);
        if (pToken)
            ;
        else {
            pToken = Lex_ParseEOF(Lex00_getLex(this));
            DEBUG_BREAK();          // This should never happen!
        }
        cls = Token_getClass(pToken);
        chr = Token_getChrW32(pToken);
        eRc = Lex_ParseTokenSetup(Lex00_getLex(this), pToken); // Set up the input token
        //                              // as the basis for the output token.

        switch (cls) {
            // Note: Unless EOF is reached in a case, each case must leave the input
            // stream with an advance to be made for the first char of the following
            // token.

            case LEX_CLASS_WHITESPACE:
                if (Lex00_getWS(this)) {
                    // Sometimes, NL is handled as white-space. So, we must separate
                    // that back out here.
                    chr = Token_getChrW32(pToken);
                    if (Lex00_getNL(this)) {
                        if ('\n' ==  chr) {
                            clsNew = LEX_CLASS_EOL;
                            break;
                        }
                    }
                    // At this point, the LookAhead() character is white-space,
                    // but not EOL. Remember that we must stay one InputAdvance()
                    // back here, because we advance after the case and it must
                    // only absorb white-space characters..
                    for (;;) {
                        pToken = Lex_InputLookAhead(Lex00_getLex(this), 2);
                        if (pToken)
                            ;
                        else {
                            pToken = Lex_ParseEOF(Lex00_getLex(this));
                            DEBUG_BREAK();          // This should never happen!
                        }
                        cls = Token_getClass(pToken);
                        chr = Token_getChrW32(pToken);
                        if ( chr == '\n' ) {
                            break;
                        }
                        if (cls == LEX_CLASS_WHITESPACE) {
                            Lex_InputAdvance(Lex00_getLex(this), 1);
                            Lex_ParseTokenAppendString(Lex00_getLex(this), pToken);
                        }
                        else
                            break;
                    }
                    clsNew = LEX_CLASS_WHITESPACE;
                } else {
                    goto nextToken;
                }
                break;

            case LEX_CLASS_EOL:
                if (Lex00_getNL(this)) {
                    clsNew = LEX_CLASS_EOL;
                } else {
                    goto nextToken;
                }
                break;

            default:
                break;
        }
        if (Token_getClass(pToken) == LEX_CLASS_EOF)
            ;
        else
            Lex_InputAdvance((LEX_DATA *)this, 1);

        // Set up the output token.
        eRc = Lex_ParseTokenFinalize(Lex00_getLex(this), clsNew, fSavStr);

        // Return to caller.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToString(pTokenOut);
            TRC_OBJ(this, "...Lex00_ParseToken token=%s", AStr_getData(pStr));
            obj_Release(pStr);
        }
#endif
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
        void        *pMethod = Lex00_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Lex00", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Lex00_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEX00_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Lex00_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LEX00_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Lex00_Class();
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
                            return Lex00_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Lex00_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LEX00_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Lex00_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Lex00_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Lex00_ToDebugString;
                        }
#ifdef  LEX00_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Lex00_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Lex00_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Lex00_ToDebugString)
                    return "ToDebugString";
#ifdef  LEX00_JSON_SUPPORT
                if (pData == Lex00_ToJson)
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
        ASTR_DATA      *pDesc = Lex00_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex00_ToDebugString (
        LEX00_DATA      *this,
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
        if (!Lex00_Validate(this)) {
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
                    Lex00_getSize(this),
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
    bool            Lex00_Validate (
        LEX00_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LEX00))
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


        if (!(obj_getSize(this) >= sizeof(LEX00_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


