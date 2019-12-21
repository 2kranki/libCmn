// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   TRegex32.c
 *	Generated 12/19/2019 23:09:03
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
#include        <TRegex32_internal.h>
#include        <ascii.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    
    // Warning: This must be kept in sync with REGEX_TYPES.
    static
    const
    char                *pTypesToStrA[] = {
        "UNUSED",
        "DOT", "BEGIN", "END",
        "QUESTIONMARK", "STAR", "PLUS",
        "CHAR", "CHAR_CLASS", "INV_CHAR_CLASS",
        "DIGIT", "NOT_DIGIT",
        "ALPHA", "NOT_ALPHA",
        "WHITESPACE", "NOT_WHITESPACE",
        "BRANCH"
    };




 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ERESULT         TRegex32_ExpandCompiled(
        TREGEX32_DATA   *this,
        uint16_t        num
    )
    {
        void            *pWork;
        uint32_t        oldMax;
        uint32_t        cbSize;
        uint16_t        elemSize = sizeof(regex_t);
        
        // Do initialization.
        if( this == NULL )
            return ERESULT_INVALID_OBJECT;
        if (num < this->maxCompiled) {
            return ERESULT_SUCCESSFUL_COMPLETION;
        }
        
        // Expand the Array.
        oldMax = this->maxCompiled;
        if (0 == oldMax) {
            oldMax = 1;
        }
        this->maxCompiled = oldMax << 1;                // max *= 2
        while (num > this->maxCompiled) {
            this->maxCompiled = this->maxCompiled << 1;
        }
        cbSize = this->maxCompiled * elemSize;
        pWork = (void *)mem_Malloc(cbSize);
        if( NULL == pWork ) {
            this->maxCompiled = oldMax;
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Copy the old entries into the new array.
        if( this->pCompiled == NULL )
            ;
        else {
            memmove(pWork, this->pCompiled, (oldMax * elemSize));
            mem_Free(this->pCompiled);
            // this->pCompiled = NULL;
        }
        this->pCompiled = pWork;
        memset(&this->pCompiled[oldMax], 0, ((this->maxCompiled - oldMax) * elemSize));
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    static
    bool        matchPattern(
        regex_t     *pattern,
        const
        W32CHR_T    *text
    );
    
    
    static
    bool        matchRange(
        W32CHR_T    c,
        const
        W32CHR_T    *pStr
    )
    {
        return ((c != '-') && (pStr[0] != '\0') && (pStr[0] != '-')
                && (pStr[1] == '-') && (pStr[1] != '\0')
                && (pStr[2] != '\0')
                && ((c >= pStr[0]) && (c <= pStr[2])));
    }
    
    
    static
    bool        isMetaChar(
        W32CHR_T    c
    )
    {
        return ((c == 's') || (c == 'S') == (c == 'w') || (c == 'W')
                || (c == 'd') || (c == 'D'));
    }

    
    static
    bool        matchMetaChar(
        W32CHR_T    c,
        const
        W32CHR_T    *pStr
    )
    {
        switch (pStr[0]) {
            case 'd':
                return  ascii_isNumericW32(c);
            case 'D':
                return !ascii_isNumericW32(c);
            case 'w':
                return  ascii_isLabelFirstCharW32(c);
            case 'W':
                return !ascii_isLabelFirstCharW32(c);
            case 's':
                return ascii_isWhiteSpaceW32(c);
            case 'S':
                return !(ascii_isWhiteSpaceW32(c));
            default:
                return (c == pStr[0]);
        }
    }

    
    static
    bool        matchCharClass(
        W32CHR_T    c,
        const
        W32CHR_T    *pStr
    )
    {
        do {
            if (matchRange(c, pStr)) {
                return true;
            }
            else if (pStr[0] == '\\') {
                /* Escape-char: increment str-ptr and match on next char */
                pStr += 1;
                if (matchMetaChar(c, pStr)) {
                    return true;
                } else if ((c == pStr[0]) && !isMetaChar(c)) {
                    return true;
                }
            } else if (c == pStr[0]) {
                if (c == '-') {
                    return ((pStr[-1] == '\0') || (pStr[1] == '\0'));
                } else {
                    return true;
                }
            }
        }
        
        // Skip to end of string.
        while (*pStr++ != '\0')
            ;
        
        return false;
    }

    
    static
    bool        matchOne(
        regex_t     p,
        W32CHR_T    c
    )
    {
        switch (p.type) {
            case DOT:
                return true;
            case CHAR_CLASS:
                return  matchCharClass(c, (const W32CHR_T *)p.ccl);
            case INV_CHAR_CLASS:
                return !matchCharClass(c, (const W32CHR_T *)p.ccl);
            case DIGIT:
                return  ascii_isNumericW32(c);
            case NOT_DIGIT:
                return !ascii_isNumericW32(c);
            case ALPHA:
                return  ascii_isLabelFirstCharW32(c);
            case NOT_ALPHA:
                return !ascii_isLabelFirstCharW32(c);
            case WHITESPACE:
                return  ascii_isWhiteSpaceW32(c);
            case NOT_WHITESPACE:
                return !(ascii_isWhiteSpaceW32(c));
            default:
                return  (p.ch == c);
        }
    }

    
    static
    bool        matchStar(
        regex_t     p,
        regex_t     *pattern,
        const
        W32CHR_T    *text
    )
    {
        do {
            if (matchPattern(pattern, text))
                return true;
        } while ((text[0] != '\0') && matchOne(p, *text++));
        
        return false;
    }

    
    static
    bool        matchPlus(
        regex_t     p,
        regex_t     *pattern,
        const
        W32CHR_T    *text
    )
    {
        while ((text[0] != '\0') && matchOne(p, *text++)) {
            if (matchPattern(pattern, text))
                return true;
        }
        return false;
    }

    
    static
    bool        matchQuestion(
        regex_t     p,
        regex_t     *pattern,
        const
        W32CHR_T    *text
    )
    {
        if ((text[0] == '\0') && p.type != UNUSED) {
            return matchPattern(pattern, &text[0]);
        }
        if ((text[0] != '\0') && matchOne(p, text[0])) {
            bool             match;
            match = matchPattern(pattern, &text[0]);
            if (!match) {
                return matchPattern(pattern, &text[1]);
            }
            return match;
        }
        return true;
    }


#ifdef  TREGEX_RECURSIVE

    /* Recursive matching */
    static
    bool        matchPattern(
        regex_t     *pPattern,
        const
        W32CHR_T    *text
    )
    {
        if ((pPattern[0].type == UNUSED) || (pPattern[1].type == QUESTIONMARK)) {
            return matchQuestion(pPattern[1], &pPattern[2], text);
        } else if (pPattern[1].type == STAR) {
            return matchStar(pPattern[0], &pPattern[2], text);
        } else if (pPattern[1].type == PLUS) {
            return matchPlus(pPattern[0], &pPattern[2], text);
        } else if ((pPattern[0].type == END) && pPattern[1].type == UNUSED) {
            return text[0] == '\0';
        } else if ((text[0] != '\0') && matchone(pPattern[0], text[0])) {
            return matchPattern(&pPattern[1], text+1);
        } else {
            return false;
        }
    }

#else

    /* Iterative matching */
    static
    bool        matchPattern(
        regex_t     *pPattern,
        const
        W32CHR_T    *pText
    )
    {
        do {
            if ((pPattern[0].type == UNUSED) || (pPattern[1].type == QUESTIONMARK)) {
                return matchQuestion(pPattern[0], &pPattern[2], pText);
            } else if (pPattern[1].type == STAR) {
                return matchStar(pPattern[0], &pPattern[2], pText);
            } else if (pPattern[1].type == PLUS) {
                return matchPlus(pPattern[0], &pPattern[2], pText);
            } else if ((pPattern[0].type == END) && pPattern[1].type == UNUSED) {
                return (pText[0] == '\0');
            }
            /*  Branching is not working properly
             else if (pPattern[1].type == BRANCH)
             {
             return (matchPattern(pPattern, text) || matchPattern(&pPattern[2], text));
             }
             */
        } while ((pText[0] != '\0') && matchOne(*pPattern++, *pText++));
        
        return false;
    }

#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TREGEX32_DATA * TRegex32_Alloc (
        void
    )
    {
        TREGEX32_DATA   *this;
        uint32_t        cbSize = sizeof(TREGEX32_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TREGEX32_DATA * TRegex32_New (
        void
    )
    {
        TREGEX32_DATA   *this;
        
        this = TRegex32_Alloc( );
        if (this) {
            this = TRegex32_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        TRegex32_getSize (
        TREGEX32_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  TRegex32_getSuperVtbl (
        TREGEX32_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
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
        ERESULT eRc = TRegex32_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TREGEX32 object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         TRegex32_Assign (
        TREGEX32_DATA		*this,
        TREGEX32_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TRegex32_Validate(pOther)) {
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
    ERESULT         TRegex32_Compare (
        TREGEX32_DATA     *this,
        TREGEX32_DATA     *pOther
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
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TRegex32_Validate(pOther)) {
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
    //                       C o m p i l e
    //---------------------------------------------------------------
    
    ERESULT         TRegex32_Compile (
        TREGEX32_DATA   *this,
        const
        W32CHR_T        *pPattern
    )
    {
        ERESULT         eRc;
        int             ccl_bufidx = 1;
        char            c;              /* current char in pattern  */
        int             i = 0;          /* index into pattern       */

#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        this->sizeCompiled = 0;

        while (pPattern[i] != '\0') {
            c = pPattern[i];
            if (++this->sizeCompiled > this->maxCompiled) {
                eRc = TRegex32_ExpandCompiled(this, this->sizeCompiled);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    return -1;
                }
            }
            
            switch (c) {
                    /* Meta-characters: */
                case '^':
                    this->pCompiled[this->sizeCompiled-1].type = BEGIN;
                    break;
                case '$':
                    this->pCompiled[this->sizeCompiled-1].type = END;
                    break;
                case '.':
                    this->pCompiled[this->sizeCompiled-1].type = DOT;
                    break;
                case '*':
                    this->pCompiled[this->sizeCompiled-1].type = STAR;
                    break;
                case '+':
                    this->pCompiled[this->sizeCompiled-1].type = PLUS;
                    break;
                case '?':
                    this->pCompiled[this->sizeCompiled-1].type = QUESTIONMARK;
                    break;
                    /*
                     --> NOT Working properly <--
                     case '|':
                            this->pCompiled[this->sizeCompiled-1].type = BRANCH;
                            break;
                     */
                    
                    /* Escaped character-classes (\s \w ...): */
                case '\\': {
                    if (pPattern[i+1] != '\0') {
                        /* Skip the escape-char '\\' */
                        i += 1;
                        /* ... and check the next */
                        switch (pPattern[i]) {
                                /* Meta-character: */
                            case 'd':
                                this->pCompiled[this->sizeCompiled-1].type = DIGIT;
                                break;
                            case 'D':
                                this->pCompiled[this->sizeCompiled-1].type = NOT_DIGIT;
                                break;
                            case 'w':
                                this->pCompiled[this->sizeCompiled-1].type = ALPHA;
                                break;
                            case 'W':
                                this->pCompiled[this->sizeCompiled-1].type = NOT_ALPHA;
                                break;
                            case 's':
                                this->pCompiled[this->sizeCompiled-1].type = WHITESPACE;
                                break;
                            case 'S':
                                this->pCompiled[this->sizeCompiled-1].type = NOT_WHITESPACE;
                                break;
                                
                                /* Escaped character, e.g. '.' or '$' */
                            default:
                                this->pCompiled[this->sizeCompiled-1].type = CHAR;
                                this->pCompiled[this->sizeCompiled-1].ch = pPattern[i];
                                break;
                        }
                    }
                    /* '\\' as last char in pattern -> invalid regular expression. */
                    /*
                     else {
                        this->pCompiled[this->sizeCompiled-1].type = CHAR;
                        this->pCompiled[this->sizeCompiled-1].ch = pPattern[i];
                     }
                     */
                }
                break;
                    
                    /* Character class: */
                case '[':
                {
                    /* Remember where the char-buffer starts. */
                    int buf_begin = ccl_bufidx;
                    
                    /* Look-ahead to determine if negated */
                    if (pPattern[i+1] == '^') {
                        this->pCompiled[this->sizeCompiled-1].type = INV_CHAR_CLASS;
                        i += 1; /* Increment i to avoid including '^' in the char-buffer */
                    } else {
                        this->pCompiled[this->sizeCompiled-1].type = CHAR_CLASS;
                    }
                    
                    /* Copy characters inside [..] to buffer */
                    while (    (pPattern[++i] != ']')
                           && (pPattern[i]   != '\0')) /* Missing ] */
                    {
                        if (ccl_bufidx >= MAX_CHAR_CLASS_LEN) {
                            //fputs("exceeded internal buffer!\n", stderr);
                            return 0;
                        }
                        this->ccl_buf[ccl_bufidx++] = pPattern[i];
                    }
                    if (ccl_bufidx >= MAX_CHAR_CLASS_LEN) {
                        /* Catches cases such as [00000000000000000000000000000000000000][ */
                        //fputs("exceeded internal buffer!\n", stderr);
                        return 0;
                    }
                    /* Null-terminate string end */
                    this->ccl_buf[ccl_bufidx++] = 0;
                    this->pCompiled[this->sizeCompiled-1].ccl = &this->ccl_buf[buf_begin];
                }
                break;
                    
                    /* Other characters: */
                default:
                    this->pCompiled[this->sizeCompiled-1].type = CHAR;
                    this->pCompiled[this->sizeCompiled-1].ch = c;
                    break;
            }
            i += 1;
        }
        
        // 'UNUSED' is a sentinel used to indicate end-of-pattern.
        if (++this->sizeCompiled > this->maxCompiled) {
            eRc = TRegex32_ExpandCompiled(this, this->sizeCompiled);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return -1;
            }
        }
        this->pCompiled[this->sizeCompiled-1].type = UNUSED;

      return ERESULT_SUCCESS;
    }

    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        TRegex32      *pCopy = TRegex32_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TREGEX32 object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TREGEX32_DATA *     TRegex32_Copy (
        TREGEX32_DATA       *this
    )
    {
        TREGEX32_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TRegex32_New( );
        if (pOther) {
            eRc = TRegex32_Assign(this, pOther);
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

    void            TRegex32_Dealloc (
        OBJ_ID          objId
    )
    {
        TREGEX32_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TREGEX32_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pCompiled) {
            mem_Free(this->pCompiled);
            this->pCompiled = NULL;
            this->maxCompiled = 0;
            this->sizeCompiled = 0;
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
    ERESULT         TRegex32_Disable (
        TREGEX32_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!TRegex32_Validate(this)) {
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
    ERESULT         TRegex32_Enable (
        TREGEX32_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!TRegex32_Validate(this)) {
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

    TREGEX32_DATA *   TRegex32_Init (
        TREGEX32_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TREGEX32_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TREGEX32);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&TRegex32_Vtbl);
        
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
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "TRegex32::sizeof(TREGEX32_DATA) = %lu\n", sizeof(TREGEX32_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TREGEX32_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         TRegex32_IsEnabled (
        TREGEX32_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
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
    //                          M a t c h
    //---------------------------------------------------------------
    
    int             TRegex32_MatchP(
        TREGEX32_DATA   *this,
        const
        W32CHR_T        *pText
    )
    {
        
                // Do initialization.
        #ifdef NDEBUG
        #else
                if (!TRegex32_Validate(this)) {
                    DEBUG_BREAK();
                    //return ERESULT_INVALID_OBJECT;
                    return -1;
                }
        #endif
                        
        if (this->pCompiled != NULL) {
            if (this->pCompiled[0].type == BEGIN) {
                return ((matchPattern(&this->pCompiled[1], pText)) ? 0 : -1);
            } else {
                int idx = -1;
                
                do {
                    idx += 1;
                    
                    if (matchPattern(this->pCompiled, pText)) {
                        if (pText[0] == '\0')
                            return -1;
                        
                        return idx;
                    }
                } while (*pText++ != '\0');
            }
        }
        return -1;
    }

    
    int             TRegex32_Match(
        TREGEX32_DATA   *this,
        const
        W32CHR_T        *pPattern,
        const
        W32CHR_T        *pText
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
#endif
                
        eRc = TRegex32_Compile(this, pPattern);
        if (ERESULT_FAILED(eRc)) {
            //return eRc;
            return -1;
        }
        
      return TRegex32_MatchP(this, pText);
    }

        

    //---------------------------------------------------------------
    //                P a r s e  J s o n  O b j e c t
    //---------------------------------------------------------------
    
#ifdef  TREGEX32_JSON_SUPPORT
     TREGEX32_DATA * TRegex32_ParseJsonObject (
         JSONIN_DATA     *pParser
    )
    {
        return OBJ_NIL;
    }
#endif
        
        
        
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
        void        *pMethod = TRegex32_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "TRegex32", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          TRegex32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TREGEX32_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TREGEX32_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)TRegex32_Class();
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
                            return TRegex32_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return TRegex32_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return TRegex32_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return TRegex32_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == TRegex32_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == TRegex32_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  TREGEX32_JSON_SUPPORT
     ASTR_DATA *     TRegex32_ToJson (
        TREGEX32_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
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
        ASTR_DATA      *pDesc = TRegex32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     TRegex32_ToDebugString (
        TREGEX32_DATA      *this,
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
        if (!TRegex32_Validate(this)) {
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
                    TRegex32_getSize(this),
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
    
    
    ASTR_DATA *     TRegex32_ToStringPattern (
        TREGEX32_DATA   *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        int             i;
        int             iMax;
        regex_t         *pattern = this->pCompiled;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex32_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
                      
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        iMax = this->sizeCompiled;
        for (i = 0; i < iMax; i++) {
            if (pattern[i].type == UNUSED) {
                break;
            }
            
            eRc =   AStr_AppendPrint(
                                   pStr,
                                   "\t%2d - type: %s ",
                                   i,
                                   pTypesToStrA[pattern[i].type]
                    );
            if (pattern[i].type == CHAR_CLASS || pattern[i].type == INV_CHAR_CLASS) {
                int         j;
                char        c;
                eRc = AStr_AppendA(pStr, "[");
                for (j = 0; j < MAX_CHAR_CLASS_LEN; ++j) {
                    c = pattern[i].ccl[j];
                    if ((c == '\0') || (c == ']')) {
                        break;
                    }
                    eRc = AStr_AppendCharW32(pStr, c);
                }
                eRc = AStr_AppendA(pStr, "]");
            } else if (pattern[i].type == CHAR) {
                eRc = AStr_AppendCharW32(pStr, pattern[i].ch);
            }
            eRc = AStr_AppendA(pStr,"\n");
        }
        
        return pStr;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            TRegex32_Validate (
        TREGEX32_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TREGEX32))
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


        if (!(obj_getSize(this) >= sizeof(TREGEX32_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


