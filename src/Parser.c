// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Parser.c
 *	Generated 12/15/2019 15:07:38
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
#include <Parser_internal.h>
#include <NodeHash.h>
#include <Token_internal.h>
#include <trace.h>
#include <stdarg.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Parser_task_body (
        void            *pData
    )
    {
        //PARSER_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PARSER_DATA *     Parser_Alloc (
        void
    )
    {
        PARSER_DATA       *this;
        uint32_t        cbSize = sizeof(PARSER_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PARSER_DATA *     Parser_New (
        void
    )
    {
        PARSER_DATA       *this;
        
        this = Parser_Alloc( );
        if (this) {
            this = Parser_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                           A u x
    //---------------------------------------------------------------
    
    OBJ_ID          Parser_getAux1 (
        PARSER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pAux1;
    }
    
    
    bool            Parser_setAux1 (
        PARSER_DATA     *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pAux1) {
            obj_Release(this->pAux1);
        }
        this->pAux1 = pValue;
        
        return true;
    }
        
        
    OBJ_ID          Parser_getAux2 (
        PARSER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pAux2;
    }
    
    
    bool            Parser_setAux2 (
        PARSER_DATA     *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pAux2) {
            obj_Release(this->pAux2);
        }
        this->pAux2 = pValue;
        
        return true;
    }
                
                

    //---------------------------------------------------------------
    //                      C o m p i l e r
    //---------------------------------------------------------------
    
    COMPILER_DATA * Parser_getCompiler (
        PARSER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pCompiler;
    }
    
    
    bool            Parser_setCompiler (
        PARSER_DATA     *this,
        COMPILER_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pCompiler) {
            obj_Release(this->pCompiler);
        }
        this->pCompiler = pValue;
        
        return true;
    }
            
            

    //---------------------------------------------------------------
    //              L e x i c a l  S c a n n e r
    //---------------------------------------------------------------

    LEX_DATA *      Parser_getLex (
        PARSER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLex;
    }


    bool            Parser_setLex (
        PARSER_DATA     *this,
        LEX_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pLex) {
            obj_Release(this->pLex);
        }
        this->pLex = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  P a r s e  F u n c t i o n
    //---------------------------------------------------------------

    bool            Parser_setParseFunction(
        PARSER_DATA     *this,
        bool            (*pParse)(OBJ_ID,NODETREE_DATA **),
        OBJ_ID          pParseObj
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pParse = pParse;
        this->pParseObj = pParseObj;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                 S e m a n t i c  S t a c k
    //---------------------------------------------------------------
    
    OBJLIST_DATA *  Parser_getSemanticStack (
        PARSER_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pSemanticStack;
    }
    
    
    bool            Parser_setSemanticStack (
        PARSER_DATA     *this,
        OBJLIST_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pSemanticStack) {
            obj_Release(this->pSemanticStack);
        }
        this->pSemanticStack = pValue;
        
        return true;
    }
                
                

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Parser_getSize (
        PARSER_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                  S o u r c e  F u n c t i o n
    //---------------------------------------------------------------
    
    bool            Parser_setSourceFunction (
        PARSER_DATA     *this,
        TOKEN_DATA *    (*pSrcChrAdvance)(OBJ_ID,uint16_t),
        TOKEN_DATA *    (*pSrcChrLookAhead)(OBJ_ID,uint16_t),
        OBJ_ID          pSrcObj
    )
    {
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        this->pSrcChrAdvance = pSrcChrAdvance;
        this->pSrcChrLookAhead = pSrcChrLookAhead;
        this->pSrcObj = pSrcObj;
        
        return true;
    }



    //---------------------------------------------------------------
    //              S o u r c e  I n p u t
    //---------------------------------------------------------------

    OBJ_ID          Parser_getSourceInput (
        PARSER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pSrcInput;
    }


    bool            Parser_setSourceInput (
        PARSER_DATA     *this,
        OBJ_ID          pValue
    )
    {

#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pSrcInput) {
            obj_Release(this->pSrcInput);
        }
        this->pSrcInput = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Parser_getSuperVtbl (
        PARSER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                 S y m b o l  T a b l e
    //---------------------------------------------------------------

    OBJ_ID          Parser_getSymbols (
        PARSER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (OBJ_NIL == this->pCompiler)
            return OBJ_NIL;
        else
            return Compiler_getSymbolTable(this->pCompiler);
    }


    bool            Parser_setSymbols (
        PARSER_DATA     *this,
        OBJ_ID          pValue
    )
    {
        bool            fRc = false;
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pCompiler) {
            fRc = Compiler_setSymbolTable(this->pCompiler, pValue);
        }

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
        ERESULT eRc = Parser_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another PARSER object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Parser_Assign (
        PARSER_DATA		*this,
        PARSER_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Parser_Validate(pOther)) {
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
        
        //goto eom;

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
    ERESULT         Parser_Compare (
        PARSER_DATA     *this,
        PARSER_DATA     *pOther
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
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Parser_Validate(pOther)) {
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
        Parser      *pCopy = Parser_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PARSER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PARSER_DATA *     Parser_Copy (
        PARSER_DATA       *this
    )
    {
        PARSER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Parser_New( );
        if (pOther) {
            eRc = Parser_Assign(this, pOther);
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

    void            Parser_Dealloc (
        OBJ_ID          objId
    )
    {
        PARSER_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

        this->pErrors = OBJ_NIL;                // (Not Owned)
        Parser_setAux1(this, OBJ_NIL);
        Parser_setAux2(this, OBJ_NIL);
        Parser_setCompiler(this, OBJ_NIL);
        Parser_setLex(this, OBJ_NIL);

        if (this->pProperties) {
            obj_Release(this->pProperties);
            this->pProperties = OBJ_NIL;
        }

        if (this->pSemanticStack) {
            obj_Release(this->pSemanticStack);
            this->pSemanticStack = OBJ_NIL;
        }

        if (this->pInputs) {
            uint16_t        ui16;
            for (ui16=0; ui16<this->sizeInputs; ++ui16) {
                if (obj_getType(&this->pInputs[ui16]) == OBJ_IDENT_TOKEN) {
                    //Token_ReleaseDataIfObj(&this->pInputs[ui16]);
                }
            }
            mem_Free(this->pInputs);
            this->pInputs = NULL;
            this->sizeInputs = 0;
            this->curInputs = 0;
        }

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
    ERESULT         Parser_Disable (
        PARSER_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Parser_Validate(this)) {
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
    ERESULT         Parser_Enable (
        PARSER_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Parser_Validate(this)) {
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

    PARSER_DATA *   Parser_Init (
        PARSER_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(PARSER_DATA);
        uint32_t        i;
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

        //this = (OBJ_ID)lex_Init((LEX_DATA *)this, 8);           // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PARSER);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Parser_Vtbl);
        
        this->sizeInputs = 4;
        this->pInputs = mem_Calloc(this->sizeInputs, sizeof(TOKEN_DATA));
        if (OBJ_NIL == this->pInputs) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        for (i=0; i<this->sizeInputs; ++i) {
            TOKEN_DATA      *pToken;
            pToken = &this->pInputs[i];
            Token_Init(pToken);
        }
        
        //FIXME: this->pErrors = eResult_Shared();
        
    #ifdef NDEBUG
    #else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "Parser::sizeof(PARSER_DATA) = %lu\n", sizeof(PARSER_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(PARSER_DATA));
    #endif

        return this;
    }

     

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    Parser_InputAdvance(
        PARSER_DATA     *this,
        uint16_t        numChrs
    )
    {
        uint32_t        i;
        
        // Do initialization.
        TRC_OBJ( this, "parser_InputAdvance: %d\n", numChrs );
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Shift inputs.
        for (i=0; i<numChrs; ++i) {
            Parser_InputNextChar(this);
        }
        
        // Return to caller.
        return &this->pInputs[this->curInputs];
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    TOKEN_DATA *    Parser_InputLookAhead(
        PARSER_DATA     *this,
        uint16_t        num
    )
    {
        uint16_t        idx;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
        TRC_OBJ( this, "parser_InputLookAhead: %d\n", num );
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (!obj_IsFlag(this, PARSER_INIT_DONE)) {
            Parser_InputAdvance(this, this->sizeInputs);
            obj_FlagOn(this, PARSER_INIT_DONE);
        }
        
        idx = (this->curInputs + num - 1) % this->sizeInputs;
        pToken = &this->pInputs[idx];
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToDebugString(pToken, 4);
            TRC_OBJ( this, "\treturning token = %s\n", AStr_getData(pStr) );
            obj_Release(pStr);
        }
#endif
        
        // Return to caller.
        return pToken;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                  I n p u t  N e x t  C h a r
    //--------------------------------------------------------------
    
    ERESULT         Parser_InputNextChar(
        PARSER_DATA     *this
    )
    {
        TOKEN_DATA      *scp;
        TOKEN_DATA      *pToken;
        
        // Do initialization.
        TRC_OBJ( this, "parser_InputNextChar: \n" );
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        BREAK_NULL(this->pSrcChrLookAhead);
        BREAK_NULL(this->pSrcChrAdvance);
        
        // Release top token;
        //Token_ReleaseDataIfObj(&this->pInputs[this->curInputs]);
        
        // Add the next char to the queue.
        pToken = &this->pInputs[this->curInputs];
        scp = this->pSrcChrLookAhead(this->pSrcObj, 1);
        BREAK_NULL(scp);
#ifdef NDEBUG
#else
        if (obj_Trace(this)) {
            ASTR_DATA       *pStr = Token_ToDebugString(scp, 4);
            TRC_OBJ( this, "\ttoken(%d) = %s\n", this->curInputs, AStr_getData(pStr) );
            obj_Release(pStr);
        }
#endif
        Token_Assign(scp, pToken);
        this->curInputs = (this->curInputs + 1) % this->sizeInputs;
        this->pSrcChrAdvance(this->pSrcObj,1);
        
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
        
        
        
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Parser_IsEnabled (
        PARSER_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
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
    //                 M a t c h  I n p u t  C h r
    //--------------------------------------------------------------
    
    TOKEN_DATA *    Parser_MatchInputChr (
        PARSER_DATA     *this,
        int32_t         chr
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate( this ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        if(chr == Token_getChrW32(&this->pInputs[0]) ) {
            obj_Retain(&this->pInputs[0]);
            scp = &this->pInputs[0];
            (void)Parser_InputNextChar(this);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s
    //--------------------------------------------------------------
    
    TOKEN_DATA *    Parser_MatchInputCls (
        PARSER_DATA     *this,
        int32_t         cls
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        scp = &this->pInputs[0];
        if(cls == Token_getClass(scp) ) {
            obj_Retain(scp);
            (void)Parser_InputNextChar(this);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //           M a t c h  I n p u t  C l a s s  S e t
    //--------------------------------------------------------------

    TOKEN_DATA *    Parser_MatchInputClsSet (
        PARSER_DATA     *this,
        int32_t         *pSet           // NULL-terminated Set of Classes
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        int32_t         cls;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        scp = &this->pInputs[0];
        cls = Token_getClass(scp);
        while (*pSet) {
            if(cls == *pSet) {
                obj_Retain(scp);
                (void)Parser_InputNextChar(this);
                return scp;
            }
            ++pSet;
        }

        // Return to caller.
        return OBJ_NIL;
    }



    //--------------------------------------------------------------
    //               M a t c h  I n p u t  R a n g e
    //--------------------------------------------------------------
    
    TOKEN_DATA *    Parser_MatchInputRange (
        PARSER_DATA     *this,
        int32_t         chrBeg,
        int32_t         chrEnd
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        scp = &this->pInputs[0];
        chr = Token_getChrW32(scp);
        if((chr >= chrBeg) && (chr <= chrEnd) ) {
            obj_Retain(scp);
            (void)Parser_InputNextChar(this);
            return scp;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  S e t
    //--------------------------------------------------------------
    
    TOKEN_DATA *    Parser_MatchInputSet (
        PARSER_DATA     *this,
        int32_t         *pSet           // NULL-terminated Set
    )
    {
        TOKEN_DATA      *scp = OBJ_NIL;
        int32_t         chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        scp = &this->pInputs[0];
        chr = Token_getChrW32(scp);
        while (*pSet) {
            if(chr == *pSet) {
                obj_Retain(scp);
                (void)Parser_InputNextChar(this);
                return scp;
            }
            ++pSet;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
        
        
        
    //---------------------------------------------------------------
    //                          P a r s e
    //---------------------------------------------------------------
    
    ERESULT         Parser_Parse (
        PARSER_DATA     *this,
        NODETREE_DATA   **ppTree
    )
    {
        //ERESULT         eRc;
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        BREAK_NULL(this->pParse);
        fRc = this->pParse(this->pParseObj,ppTree);
        if (!fRc) {
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P r o p e r t y
    //---------------------------------------------------------------
    
    NODE_DATA *     Parser_Property (
        PARSER_DATA     *this,
        const
        char            *pName
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pProperty = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperty = NodeHash_FindA(this->pProperties, 0, pName);
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------
    
    ERESULT         Parser_PropertyAdd (
        PARSER_DATA     *this,
        NODE_DATA       *pData
        )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = NodeHash_NewWithSize( 17 );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = NodeHash_Add(this->pProperties, pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //              P r o p e r t y  C o u n t
    //---------------------------------------------------------------
    
    uint16_t        Parser_PropertyCount (
        PARSER_DATA     *this
    )
    {
        uint16_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = NodeHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t i e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * Parser_Properties (
        PARSER_DATA     *this
    )
    {
        //ERESULT         eRc;
        NODEARRAY_DATA  *pProperties = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperties = NodeHash_Nodes(this->pProperties);
        }
        
        // Return to caller.
        return pProperties;
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
        void        *pMethod = Parser_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Parser", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Parser_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PARSER_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(PARSER_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Parser_Class();
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
                            return Parser_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Parser_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Parser_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Parser_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Parser_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == Parser_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e m  G e t
    //---------------------------------------------------------------
    
    NODE_DATA *     Parser_SemGet(
        PARSER_DATA     *this,
        uint16_t        index
    )
    {
        NODE_DATA       *pItem = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if( this->pSemanticStack ) {
            pItem = ObjList_Get(this->pSemanticStack, index);
        }
        
        // Return to caller.
#ifdef NDEBUG
#else
        if (pItem) {
            TRC_OBJ( this,
                    "\tparser_SemGet(%d):  returning: %s\n",
                    index,
                    Node_getName(pItem)
                    );
        }
        else {
            TRC_OBJ( this,
                    "\tparser_SemGet(%d):  returning: NULL\n",
                    index
                    );
        }
#endif
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e m  P o p
    //---------------------------------------------------------------
    
    OBJ_ID          Parser_SemPop(
        PARSER_DATA     *this
    )
    {
        OBJ_ID          pItem = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        /* Pop 1 element from the top of the semantic stack.
         */
        if( this->pSemanticStack ) {
            pItem = ObjList_Pop(this->pSemanticStack);
        }
        
        // Return to caller.
        return pItem;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e m  P u s h
    //---------------------------------------------------------------
    
    bool            Parser_SemPush(
        PARSER_DATA     *this,
        OBJ_ID          pItem
    )
    {
        ERESULT         eRc;
        bool            fRc = true;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if  (NULL == pItem) {
            DEBUG_BREAK();
            return false;
        }
        
        if (this->pSemanticStack == OBJ_NIL) {
            this->pSemanticStack = ObjList_New();
            if (this->pSemanticStack == OBJ_NIL) {
                DEBUG_BREAK();
                return false;
            }
        }
        
        eRc = ObjList_Push(this->pSemanticStack, pItem);
        if (ERESULT_IS_SUCCESSFUL(eRc))
            ;
        else {
            DEBUG_BREAK();
            fRc = false;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e m  T o p
    //---------------------------------------------------------------
    
    OBJ_ID          Parser_SemTop (
        PARSER_DATA     *this
    )
    {
        OBJ_ID          pItem = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !Parser_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if( this->pSemanticStack ) {
            pItem = ObjList_Top(this->pSemanticStack);
        }
        
        // Return to caller.
        return pItem;
    }
        
        
        
    //---------------------------------------------------------------
    //         S e t u p  p p l e x  f r o m  A S t r
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Parser_SetupPPLexFromAStr (
        PARSER_DATA     *this,
        PATH_DATA       *pPath,
        ASTR_DATA       *pStr,
        bool            fLex1,
        bool            fLex3,
        bool            fNL,
        bool            fWS,
        uint16_t        tabSize
    )
    {
        //ERESULT         eRc;
        //LEX_DATA        *pLex = OBJ_NIL;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        //FIXME: Set up for LEX??.
#ifdef XYZZY
        pLex = (LEX_DATA *)pplex_New(tabSize);
        if (OBJ_NIL == pLex) {
            return ERESULT_OUT_OF_MEMORY;
        }

        // We must establish if we want NL or WS tokens before
        // we start the lexical scanner.
        pplex_setReturnNL((PPLEX_DATA *)pLex, fNL);
        pplex_setReturnWS((PPLEX_DATA *)pLex, fWS);

        // Create the lexers. We always get pplex2. pplex1 and pplex3 are
        // optional.
        eRc = pplex_CreateLexers((PPLEX_DATA *)pLex, fLex1, fLex3);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pLex);
            return eRc;
        }

        // Plug in the input source into the lexer(s).
        eRc =   pplex_CreateSourceFromAStr(
                                      (PPLEX_DATA *)pLex,
                                      pPath,
                                      pStr
                );
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(pLex);
            return eRc;
        }
        Parser_setLex(this, pLex);
        obj_Release(pLex);

        // Now set up the lexer chain as the parser's input without
        // ownership.
        Parser_setSourceFunction(
                                this,
                                (void *)pplex_InputAdvance,
                                (void *)pplex_InputLookAhead,
                                pLex
        );
#endif

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  PARSER_JSON_SUPPORT
     ASTR_DATA *     Parser_ToJson (
        PARSER_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Parser_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Parser_ToDebugString (
        PARSER_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Parser_Validate(this)) {
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
                    Parser_getSize(this),
                    obj_getRetainCount(this)
            );

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
    bool            Parser_Validate (
        PARSER_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_PARSER))
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


        if (!(obj_getSize(this) >= sizeof(PARSER_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


