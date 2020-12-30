// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Expr.c
 *	Generated 03/03/2020 17:03:28
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
#include        <Expr_internal.h>
#include        <ascii.h>
#include        <trace.h>

// If debugging, provide trace of all look-aheads.
#ifdef NDEBUG
#   define  LOOKAHEAD(num)  this->pInputLookAhead(this->pObjInput, num);
#else
#   define  LOOKAHEAD(num)  Expr_LookAhead(this, num);
#endif
#define     ADVANCE(num)    this->pInputAdvance(this->pObjInput, num);




#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /*! Get the next LookAhead Token with optional tracing.
     */
#ifdef NDEBUG
#else
    W32CHR_T        Expr_LookAhead(
        EXPR_DATA       *this,
        uint32_t        index
    )
    {
        W32CHR_T         chr;

        chr = this->pInputLookAhead(this->pObjInput, index);
#ifdef NDEBUG
#else
        {
            TRC_OBJ( this,
                    "Expr_LookAhead(%d): %s (%d)\n",
                    index,
                    ascii_isPrintableW32(chr) ? chr : ' ',
                    chr
            );
        }
#endif

        return chr;
    }
#endif


    bool            Expr_MatchStrA(
        EXPR_DATA       *this,
        const
        char            *pStrA
    )
    {
        W32CHR_T        chr;
        int32_t         index = 1;
        int32_t         len = 0;
        bool            fMatch = true;

        for (;;) {
            chr = LOOKAHEAD(index);
            if (chr == '\0') {
                if (*pStrA == '\0')
                    ;
                else {
                    fMatch = false;
                }
                break;
            }
            if (chr == *pStrA) {
                ++pStrA;
                ++index;
                ++len;
            }
            else {
                fMatch = false;
                break;
            }
        }

        if (fMatch) {
            ADVANCE(len);
        }

        return fMatch;
    }


    /*!
     Add
        : Add '+' Mult
        | Add '-' Mult
        | Mult
        ;
     */
    int32_t         Expr_Add(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Mult(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '+') {
                    ADVANCE(1);
                    iRc2 = Expr_Mult(this);
                    iRc += iRc2;
            } else if (chr == '-') {
                    ADVANCE(1);
                    iRc2 = Expr_Mult(this);
                    iRc -= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     And
        : And "&" Eq
        | Eq
        ;
     */
    int32_t         Expr_And(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Eq(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '&') {
                    ADVANCE(1);
                    iRc2 = Expr_Eq(this);
                    iRc &= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Eq
        : Eq "==" Rel
        | Eq "!=" Rel
        | Rel
        ;
     */
    int32_t         Expr_Eq(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Rel(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '=') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Expr_Rel(this);
                if (iRc == iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if ((chr == '!') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Expr_Rel(this);
                if (iRc != iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Expr
        : LogicalOr
        ;
     */
    int32_t         Expr_Expr(
        EXPR_DATA       *this
    )
    {
        return Expr_LogicalOr(this);
    }


    /*!
     LogicalAnd
        : LogicalAnd "&&" Or
        | Or
        ;
     */
    int32_t         Expr_LogicalAnd(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Or(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '&') && (chr2 == '&')) {
                ADVANCE(2);
                iRc2 = Expr_Or(this);
                if (iRc && iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     LogicalOr
        : LogicalOr "||" LogicalAnd
        | LogicalAnd
        ;
     */
    int32_t         Expr_LogicalOr(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_LogicalAnd(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '|')  && (chr2 == '|')){
                ADVANCE(2);
                iRc2 = Expr_LogicalAnd(this);
                if (iRc || iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Mult
        : Mult '*' Primary
        | Mult '/' Primary
        | Mult '%' Primary
        | Primary
        ;
     */
    int32_t         Expr_Mult(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Primary(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '*') {
                ADVANCE(1);
                iRc2 = Expr_Primary(this);
                iRc *= iRc2;
            } else if (chr == '/') {
                ADVANCE(1);
                iRc2 = Expr_Primary(this);
                iRc /= iRc2;
            } else if (chr == '%') {
                ADVANCE(1);
                iRc2 = Expr_Primary(this);
                iRc %= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Or
        : Or '|' Xor
        | Xor
        ;
     */
    int32_t         Expr_Or(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Xor(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '|') {
                ADVANCE(1);
                iRc2 = Expr_Xor(this);
                iRc |= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*
     primary
        : identifier
        | INTEGER
        | FLOAT
        | '(' expr ')'
        ;
     */
    int32_t         Expr_Primary(
        EXPR_DATA       *this
    )
    {
        int32_t         iRc = 0;
        W32CHR_T        chr;
        //ERESULT         eRc;
        bool            fRc;

        chr = LOOKAHEAD(1);
        if (chr == '(') {
            ADVANCE(1);
            iRc = Expr_Expr(this);
            chr = LOOKAHEAD(1);
            if (chr != ')') {
                fprintf(stderr, "ERROR - Expecting ')' but found %c\n", chr);
                exit(4);
            }
            ADVANCE(1);
            return iRc;
        }

        if (this->pInputScanInteger32) {
            fRc = this->pInputScanInteger32(this->pObjParse, &iRc);
            if (fRc) {
                return iRc;
            }
        }

#ifdef XYZZY
        switch (chr) {
            case PPLEX_CONSTANT_FLOAT:
                // Process number
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_IDENTIFIER:
                idxList =   cgmrTree_NodeNewUTF8(
                                                 this->pTree,
                                                 "PrimaryExpr",
                                                 CGMR_NODECLASS_PRIMARY_EXPR,
                                                 OBJ_NIL
                            );
                if (0 == idxList) {
                    srcErrors_AddFatalA(OBJ_NIL, NULL, "Out of Memory");
                }
                TOKEN_DATA          *pTokenNew = Token_Copy(pToken);
                idxNode =   cgmrTree_NodeNewUTF8(
                                                 this->pTree,
                                                 "Id",
                                                 CGMR_NODECLASS_ID,
                                                 pTokenNew
                                                 );
                obj_Release(pTokenNew);
                if (0 == idxNode) {
                    srcErrors_AddFatalA(OBJ_NIL, NULL, "Out of Memory");
                }
                eRc = cgmrTree_NodeLinkChild(this->pTree, idxList, idxNode);
                BREAK_FAILED(eRc);
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_CONSTANT_INTEGER:
                // Process number
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_OP_SUB:
                // Process unary '-'
                // Look for and process Integer or Float.
                ADVANCE(1);
                return iRc;
                break;
            case PPLEX_SEP_LPAREN:
                iRc = Expr_Expr(this);
                // Process unary '-'
                // Look for and process Integer or Float.
                ADVANCE(1);
                return iRc;
                break;
            default:
                // ERROR - Needed ... but found <cls>!
                break;
        }
#endif

#ifdef XYZZY
        idxNode = prsC_Const(this);
        if (idxNode) {
            idxList =   cgmrTree_NodeNewUTF8(
                                             this->pTree,
                                             "PrimaryExpr",
                                             CGMR_NODECLASS_PRIMARY_EXPR,
                                             OBJ_NIL
                                             );
            if (0 == idxList) {
                srcErrors_AddFatalA(OBJ_NIL, NULL, "Out of Memory");
            }
            eRc = cgmrTree_NodeLinkChild(this->pTree, idxList, idxNode);
            BREAK_FAILED(eRc);
            return idxList;
        }
#endif

        return iRc;
    }


    /*!
     Rel
        : Rel ">=" Shift
        | Rel "<=" Shift
        | Rel '>'  Shift
        | Rel '<'  Shift
        | Shift
        ;
     */
    int32_t         Expr_Rel(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Shift(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '>') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Expr_Shift(this);
                if (iRc >= iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if ((chr == '<') && (chr2 == '=')) {
                ADVANCE(2);
                iRc2 = Expr_Shift(this);
                if (iRc <= iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if (chr == '>') {
                ADVANCE(1);
                iRc2 = Expr_Shift(this);
                if (iRc > iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else if (chr == '<') {
                ADVANCE(1);
                iRc2 = Expr_Shift(this);
                if (iRc <= iRc2)
                    iRc = 1;
                else
                    iRc = 0;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Shift
        : Shift ">>" Add
        | Shift "<<" Add
        | Add
        ;
     */
    int32_t         Expr_Shift(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        W32CHR_T        chr2;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_Add(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            chr2 = LOOKAHEAD(2);
            if ((chr == '<') && (chr2 == '<')) {
                ADVANCE(2);
                iRc2 = Expr_Rel(this);
                iRc <<= iRc2;
            } else if ((chr == '>') && (chr2 == '>')) {
                ADVANCE(2);
                iRc2 = Expr_Rel(this);
                iRc >>= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }


    /*!
     Xor
        : Xor '^' And
        | And
        ;
     */
    int32_t         Expr_Xor(
        EXPR_DATA       *this
    )
    {
        W32CHR_T        chr;
        int32_t         iRc = 0;
        int32_t         iRc2 = 0;

        iRc = Expr_And(this);
        for (;;) {
            chr = LOOKAHEAD(1);
            if (chr == '^') {
                ADVANCE(1);
                iRc2 = Expr_And(this);
                iRc ^= iRc2;
            } else {
                break;
            }
        }

        return iRc;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    EXPR_DATA *     Expr_Alloc (
        void
    )
    {
        EXPR_DATA       *this;
        uint32_t        cbSize = sizeof(EXPR_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    EXPR_DATA *     Expr_New (
        void
    )
    {
        EXPR_DATA       *this;
        
        this = Expr_Alloc( );
        if (this) {
            this = Expr_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  L e x i c a l  S c a n n e r
    //---------------------------------------------------------------

    LEX_DATA *      Expr_getLex (
        EXPR_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLex;
    }


    bool            Expr_setLex (
        EXPR_DATA       *this,
        LEX_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
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
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Expr_getPriority (
        EXPR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Expr_setPriority (
        EXPR_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
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
    
    uint32_t        Expr_getSize (
        EXPR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Expr_getSuperVtbl (
        EXPR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
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
        ERESULT eRc = Expr_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another EXPR object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Expr_Assign (
        EXPR_DATA		*this,
        EXPR_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Expr_Validate(pOther)) {
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
    //                         C a l c
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Expr_Calc (
        EXPR_DATA       *this,
        int32_t         *pAnswer
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int32_t         ans = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        ans = Expr_Expr(this);

        // Return to caller.
        if (pAnswer)
            *pAnswer = ans;
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
    int             Expr_Compare (
        EXPR_DATA       *this,
        EXPR_DATA       *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Expr_Validate(pOther)) {
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
        Expr      *pCopy = Expr_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a EXPR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    EXPR_DATA *     Expr_Copy (
        EXPR_DATA       *this
    )
    {
        EXPR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef EXPR_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Expr_New( );
        if (pOther) {
            eRc = Expr_Assign(this, pOther);
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

    void            Expr_Dealloc (
        OBJ_ID          objId
    )
    {
        EXPR_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((EXPR_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Expr_setLex(this, OBJ_NIL);
        if (this->pObjFind) {
            obj_Release(this->pObjFind);
            this->pObjFind = OBJ_NIL;
        }
        if (this->pObjInput) {
            obj_Release(this->pObjInput);
            this->pObjInput = OBJ_NIL;
        }
        if (this->pObjParse) {
            obj_Release(this->pObjParse);
            this->pObjParse = OBJ_NIL;
        }

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
        Expr      *pDeepCopy = Expr_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a EXPR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    EXPR_DATA *     Expr_DeepyCopy (
        EXPR_DATA       *this
    )
    {
        EXPR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Expr_New( );
        if (pOther) {
            eRc = Expr_Assign(this, pOther);
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
    ERESULT         Expr_Disable (
        EXPR_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
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
    ERESULT         Expr_Enable (
        EXPR_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
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

    EXPR_DATA *   Expr_Init (
        EXPR_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(EXPR_DATA);
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

        this = (OBJ_ID)Parser_Init((PARSER_DATA *)this);        // Needed for Inheritance
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Expr_Vtbl);
        
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
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Expr::sizeof(EXPR_DATA) = %lu\n", 
                sizeof(EXPR_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(EXPR_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Expr_IsEnabled (
        EXPR_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
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
        void        *pMethod = Expr_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Expr", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Expr_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        EXPR_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(EXPR_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Expr_Class();
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
                            return Expr_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Expr_Enable;
                        }
                        break;

#ifdef  EXPR_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Expr_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Expr_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Expr_ToDebugString;
                        }
#ifdef  EXPR_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Expr_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Expr_ToDebugString)
                    return "ToDebugString";
#ifdef  EXPR_JSON_SUPPORT
                if (pData == Expr_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    ERESULT     Expr_SetupScanner (
        EXPR_DATA       *this,
        SCANNER_DATA    *pScan
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Expr_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        obj_Retain(pScan);
        obj_Retain(pScan);

        this->pObjInput = pScan;
        this->pInputAdvance        = (void *)Scanner_Advance;
        this->pInputLookAhead      = (void *)Scanner_LookAhead;

        this->pObjParse = pScan;
        this->pInputMatchA         = (void *)Scanner_MatchChr;
        this->pInputMatchStrA      = (void *)Scanner_MatchStrA;
        this->pInputScanIdentifier = (void *)Scanner_ScanIdentifierToAStr;
        this->pInputScanInteger32  = (void *)Scanner_ScanInteger32;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Expr_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Expr_ToDebugString (
        EXPR_DATA      *this,
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
        if (!Expr_Validate(this)) {
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
                    Expr_getSize(this),
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
    bool            Expr_Validate (
        EXPR_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_EXPR))
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


        if (!(obj_getSize(this) >= sizeof(EXPR_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


