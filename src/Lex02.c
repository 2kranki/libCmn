// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Lex02.c
 *  Generated 05/30/2020 14:52:09
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
#include        <Lex02_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Lex02_task_body (
        void            *pData
    )
    {
        //LEX02_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LEX02_DATA *     Lex02_Alloc (
        void
    )
    {
        LEX02_DATA       *this;
        uint32_t        cbSize = sizeof(LEX02_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LEX02_DATA *     Lex02_New (
        void
    )
    {
        LEX02_DATA       *this;
        
        this = Lex02_Alloc( );
        if (this) {
            this = Lex02_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      C o m m e n t s
    //---------------------------------------------------------------

    bool            Lex02_getCM (
        LEX02_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex02_getLex(this)) & LEX02_FLAG_RETURN_CM ? true : false;
    }

    bool            Lex02_setCM(
        LEX02_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex02_getLex(this));
        if (fValue)
            flags |= LEX02_FLAG_RETURN_CM;
        else
            flags &= ~LEX02_FLAG_RETURN_CM;
        fRc = Lex_setFlags(Lex02_getLex(this), flags);

        return fRc;
    }



    //---------------------------------------------------------------
    //                      F l a g s
    //---------------------------------------------------------------

    uint32_t        Lex02_getFlags(
        LEX02_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags((LEX_DATA *)this);
    }


    bool            Lex02_setFlags(
        LEX02_DATA      *this,
        uint32_t        value
    )
    {
        bool            fRc;

#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
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

    LEX_DATA *      Lex02_getLex (
        LEX02_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return (LEX_DATA *)this;
    }



    //---------------------------------------------------------------
    //                      N e w - L i n e s
    //---------------------------------------------------------------

    bool            Lex02_getNL (
        LEX02_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex02_getLex(this)) & LEX02_FLAG_RETURN_NL ? true : false;
    }

    bool            Lex02_setNL(
        LEX02_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex02_getLex(this));
        if (fValue)
            flags |= LEX02_FLAG_RETURN_NL;
        else
            flags &= ~LEX02_FLAG_RETURN_NL;
        fRc = Lex_setFlags(Lex02_getLex(this), flags);

        return fRc;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Lex02_getPriority (
        LEX02_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Lex02_setPriority (
        LEX02_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
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
    
    uint32_t        Lex02_getSize (
        LEX02_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Lex02_getStr (
        LEX02_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Lex02_setStr (
        LEX02_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  Lex02_getSuperVtbl (
        LEX02_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      W h i t e - S p a c e
    //---------------------------------------------------------------

    bool            Lex02_getWS (
        LEX02_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return Lex_getFlags(Lex02_getLex(this)) & LEX02_FLAG_RETURN_WS ? true : false;
    }

    bool            Lex02_setWS(
        LEX02_DATA      *this,
        bool            fValue
    )
    {
        bool            fRc;
        uint32_t        flags;

#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        flags = Lex_getFlags(Lex02_getLex(this));
        if (fValue)
            flags |= LEX02_FLAG_RETURN_WS;
        else
            flags &= ~LEX02_FLAG_RETURN_WS;
        fRc = Lex_setFlags(Lex02_getLex(this), flags);

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
        ERESULT eRc = Lex02_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LEX02 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Lex02_Assign (
        LEX02_DATA       *this,
        LEX02_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Lex02_Validate(pOther)) {
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
    int             Lex02_Compare (
        LEX02_DATA      *this,
        LEX02_DATA      *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Lex02_Validate(pOther)) {
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
        Lex02      *pCopy = Lex02_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX02 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX02_DATA *     Lex02_Copy (
        LEX02_DATA       *this
    )
    {
        LEX02_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LEX02_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Lex02_New( );
        if (pOther) {
            eRc = Lex02_Assign(this, pOther);
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

    void            Lex02_Dealloc (
        OBJ_ID          objId
    )
    {
        LEX02_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LEX02_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Lex02_setStr(this, OBJ_NIL);

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
        Lex02      *pDeepCopy = Lex02_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LEX02 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LEX02_DATA *     Lex02_DeepyCopy (
        LEX02_DATA       *this
    )
    {
        LEX02_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Lex02_New( );
        if (pOther) {
            eRc = Lex02_Assign(this, pOther);
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
    ERESULT         Lex02_Disable (
        LEX02_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
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
    ERESULT         Lex02_Enable (
        LEX02_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
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

    LEX02_DATA *   Lex02_Init (
        LEX02_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LEX02_DATA);
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LEX02);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Lex02_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

        fRc =   Lex_setParserFunction(
                                Lex02_getLex(this),
                                (void *)Lex02_ParseToken,
                                this
                );
        if (!fRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Lex02::sizeof(LEX02_DATA) = %lu\n", 
                sizeof(LEX02_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LEX02_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Lex02_IsEnabled (
        LEX02_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
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
     */

    ERESULT         Lex02_ParseToken(
        LEX02_DATA      *this,
        TOKEN_DATA      *pTokenOut
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TOKEN_DATA      *pToken;
        int32_t         cls1;           // Input: 1 Lookahead
        W32CHR_T        chr1;
        int32_t         cls2;           // Input: 2 Lookahead
        W32CHR_T        chr2;
        int32_t         clsNew = LEX_CLASS_UNKNOWN;
        bool            fSavStr = true;
        //uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        TRC_OBJ(this, "Lex02_ParseToken:\n");

    nextToken:
        pToken = Lex_InputLookAhead(Lex02_getLex(this), 1);
        if (pToken)
            ;
        else {
            pToken = Lex_SetupTokenEOF(Lex02_getLex(this));
            DEBUG_BREAK();          // This should never happen!
        }
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "\tToken1: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
#endif
        cls1 = Token_getClass(pToken);
        chr1 = Token_getChrW32(pToken);
        clsNew = cls1;              // Default to Input Class.
        // Set up the input token as the basis for the output token.
        eRc = Lex_ParseTokenSetup(Lex02_getLex(this), pToken);
        Lex_InputAdvance(Lex02_getLex(this), 1);

        pToken = Lex_InputLookAhead(Lex02_getLex(this), 1);
        if (pToken)
            ;
        else {
            pToken = Lex_SetupTokenEOF(Lex02_getLex(this));
            DEBUG_BREAK();          // This should never happen!
        }
        cls2 = Token_getClass(pToken);
        chr2 = Token_getChrW32(pToken);
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
            if (pStr) {
                fprintf(stderr, "\tToken2: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
#endif

        switch (cls1) {
            // Note: Unless EOF is reached in a case, each case must leave the input
            // stream with an advance to be made for the first char of the following
            // token.

            case LEX_CLASS_WHITESPACE:
                if (Lex02_getWS(this)) {
                    // Sometimes, NL is handled as white-space. So, we must separate
                    // that back out here.
                    if (Lex02_getNL(this)) {
                        if ('\n' ==  chr1) {
                            clsNew = LEX_CLASS_EOL;
                            break;
                        }
                    }
                    // At this point, the LookAhead() character is white-space,
                    // but not EOL. Remember that we must stay one InputAdvance()
                    // back here, because we advance after the case and it must
                    // only absorb white-space characters.
                    for (;;) {
                        pToken = Lex_InputLookAhead(Lex02_getLex(this), 1);
                        if (pToken)
                            ;
                        else {
                            pToken = Lex_SetupTokenEOF(Lex02_getLex(this));
                            DEBUG_BREAK();          // This should never happen!
                        }
                        cls2 = Token_getClass(pToken);
                        chr2 = Token_getChrW32(pToken);
                        if ( chr2 == '\n' ) {
                            break;
                        }
                        if (cls2 == LEX_CLASS_WHITESPACE) {
                            Lex_InputAdvance(Lex02_getLex(this), 1);
                            Lex_ParseTokenAppendString(Lex02_getLex(this), pToken);
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
                if (Lex02_getNL(this)) {
                    Lex_InputAdvance(Lex02_getLex(this), 1);
                    clsNew = LEX_CLASS_EOL;
                } else {
                    goto nextToken;
                }
                break;

            case '_':
            case LEX_CLASS_ALPHA_LOWER:
            case LEX_CLASS_ALPHA_UPPER:
                TRC_OBJ(this, "\tScanning Identifier...\n");
                for (;;) {
                    if (   (cls2 == LEX_CLASS_ALPHA_LOWER)
                        || (cls2 == LEX_CLASS_ALPHA_UPPER)
                        || (cls2 == LEX_CLASS_NUMBER)
                        || (cls2 == '_')
                    ) {
                        Lex_ParseTokenAppendString(Lex02_getLex(this), pToken);
                        Lex_InputAdvance(Lex02_getLex(this), 1);
                        pToken = Lex_InputLookAhead(Lex02_getLex(this), 1);
                        if (pToken)
                            ;
                        else {
                            pToken = Lex_SetupTokenEOF(Lex02_getLex(this));
                            DEBUG_BREAK();          // This should never happen!
                        }
#ifdef NDEBUG
#else
                        if (obj_Trace(this)) {
                            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 0);
                            if (pStr) {
                                fprintf(stderr, "\tNext Token: %s\n", AStr_getData(pStr));
                                obj_Release(pStr);
                                pStr = OBJ_NIL;
                            }
                        }
#endif
                        cls2 = Token_getClass(pToken);
                        //chr2 = Token_getChrW32(pToken);
                    } else {
                        break;
                    }
                }
                clsNew = LEX_IDENTIFIER;
                break;

            case LEX_CLASS_NUMBER:
#ifdef XYZZY
                clsNew = Lex_ParseNumber((LEX_DATA *)this);
                if (clsNew) {
                    uint16_t        type;
                    type = Lex_ParseIntegerSuffix((LEX_DATA *)this);
                    Token_setMisc(&this->super.token, type);
                }
#endif
                break;

            case '!':           /*** '!' ***/
                clsNew = LEX_OP_NOT;
                if( '=' == cls2) {
                    clsNew = LEX_OP_NE;
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                }
                break;

            case '"':           /*** '"' ***/
#ifdef XYZZY
                ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                while(Lex_ParseChrCon((LEX_DATA *)this,'"'))
                    ;
                pInput = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj,1);
                cls = Token_getClass(pInput);
                if (cls == '"') {
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pInput);
                    ((LEX_DATA *)this)->pSrcChrAdvance(((LEX_DATA *)this)->pSrcObj, 1);
                    newCls = LEX_CONSTANT_STRING;
                    fMore = false;
                    break;
                }
                else {
                    SrcErrors_AddFatalFromTokenA(
                            OBJ_NIL,
                            pInput,
                            "Malformed String constant"
                    );
                }
#endif
                break;

            case '%':
                clsNew = LEX_OP_MOD;
                if( '=' == cls2) {
                    clsNew = LEX_OP_ASSIGN_MOD;
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                }
                break;

            case '&':
                clsNew = LEX_OP_AND;
                if( '=' == cls2) {
                    clsNew = LEX_OP_ASSIGN_AND;
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                } else if( '&' == cls2) {
                    clsNew = LEX_OP_LOG_AND;
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                }
                break;

            case '\'':
#ifdef XYZZY
                if (Lex_getMultiCharConstant((LEX_DATA *)this)) {
                    while(Lex_ParseChrCon((LEX_DATA *)this, '\''))
                        ;
                }
                else {
                    Lex_ParseChrCon((LEX_DATA *)this, '\'');
                }
                pToken = ((LEX_DATA *)this)->pSrcChrLookAhead(((LEX_DATA *)this)->pSrcObj, 1);
                cls = Token_getClass(pInput);
                if (cls == '\'') {
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                    if (Lex_getMultiCharConstant((LEX_DATA *)this)) {
                        clsNew = LEX_CONSTANT_STRING;
                    }
                    else {
                        clsNew = LEX_CONSTANT_CHAR;
                    }
                    fMore = false;
                    break;
                }
                else {
                    SrcErrors_AddFatalFromTokenA(
                                                 OBJ_NIL,
                                                 pToken,
                                                 "Malformed Character Constant"
                    );
                }
#endif
                break;

            case '(':           /*** '(' ***/
                clsNew = LEX_SEP_LPAREN;
                break;

            case ')':           /*** ')' ***/
                clsNew = LEX_SEP_RPAREN;
                break;

            case '*':           /*** '*' ***/
                clsNew = LEX_OP_MUL;
                if( '=' == cls2) {
                    clsNew = LEX_OP_ASSIGN_MUL;
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                    break;
                }
                break;

            case '+':           /*** '+' ***/
                clsNew = LEX_OP_ADD;
                if( '+' == cls2) {
                    clsNew = LEX_OP_INC;
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                    break;
                }
                if( '=' == cls2) {
                    clsNew = LEX_OP_ASSIGN_ADD;
                    Lex_ParseTokenAppendString((LEX_DATA *)this, pToken);
                    Lex_InputAdvance((LEX_DATA *)this, 1);
                    break;
                }
                break;

            case ',':           /*** ',' ***/
                clsNew = LEX_SEP_COMMA;
                break;

            default:
                break;
        }

        // Set up the output token.
        eRc = Lex_ParseTokenFinalize(Lex02_getLex(this), clsNew, fSavStr);

        // Return to caller.
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToString(pTokenOut);
            TRC_OBJ(this, "...Lex00_ParseToken found token=%s", AStr_getData(pStr));
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
        void        *pMethod = Lex02_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Lex02", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Lex02_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LEX02_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Lex02_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LEX02_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Lex02_Class();
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
                            return Lex02_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Lex02_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LEX02_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Lex02_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Lex02_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Lex02_ToDebugString;
                        }
#ifdef  LEX02_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Lex02_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Lex02_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Lex02_ToDebugString)
                    return "ToDebugString";
#ifdef  LEX02_JSON_SUPPORT
                if (pData == Lex02_ToJson)
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

    TOKEN_DATA *    Lex02_TokenAdvance(
        LEX02_DATA      *this,
        uint16_t        numTokens
    )
    {
        TOKEN_DATA      *pToken = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        pToken = Lex_TokenAdvance(Lex02_getLex(this), numTokens);

        // Return to caller.
        return pToken;
    }



    //--------------------------------------------------------------
    //               T o k e n  L o o k  A h e a d
    //--------------------------------------------------------------

    TOKEN_DATA *    Lex02_TokenLookAhead(
        LEX02_DATA      *this,
        uint16_t        numTokens
    )
    {
        TOKEN_DATA      *pToken;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Lex02_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pToken = Lex_TokenLookAhead(Lex02_getLex(this), numTokens);

        // Return to caller.
        return pToken;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Lex02_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex02_ToDebugString (
        LEX02_DATA      *this,
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
        if (!Lex02_Validate(this)) {
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
                    Lex02_getSize(this),
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
    bool            Lex02_Validate (
        LEX02_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LEX02))
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


        if (!(obj_getSize(this) >= sizeof(LEX02_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


