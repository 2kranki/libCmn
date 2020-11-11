// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   TRegex.c
 *	Generated 12/19/2019 23:08:58
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
#include        <TRegex_internal.h>
#include        <ascii.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    



#define UNUSED(variable) (void)(variable)
    
    /* compileOne: compiles one regex token, returns number of chars eaten */
    int             TRegex_CompileOne(
        TREGEX_DATA     *this,
        re_Token        *pCompiled,
        const
        char            *pPattern,
        ClassChar       cclbuf[CCLBUFLEN],
        int             *ccli
    );
    /* compileoneclc: compiles one class character, returns number of chars eaten */
    int             TRegex_CompileOneCLC(
        ClassChar       *pCompiled,
        const
        char            *pPattern
    );
    /* compilerange: compiles a range, returns number of chars eaten */
    int             TRegex_CompileRange(
        ClassChar       *pCompiled,
        const
        char            *pPattern
    );
    /* compilequantifier: compiles a quantifier, returns number of chars eaten */
    int             TRegex_CompileQuantifier(
        re_Token        *pCompiled,
        const
        char            *pPattern
    );
    /* compilegreedy: sets whether the quantifier is greedy, returns number of chars eaten */
    int             TRegex_CompileGreedy(
        re_Token        *pCompiled,
        const
        char            *pPattern
    );
    /* compileatomic: sets whether the quantifier is atomic, returns number of chars eaten */
    int             TRegex_CompileAtomic(
        re_Token        *pCompiled,
        const
        char            *pPattern
    );

    /* matchpattern: matches one pattern on a string, returns number of chars eaten */
    int             TRegex_MatchPattern(
        TREGEX_DATA     *this,
        const
        re_Token        *pPattern,
        MatchData       *pMatchData,
        int             pi,
        const
        char            *pText,
        int             i
    );
    /* backtrack: backtrack into the pattern, returns new starting index */
    int             TRegex_BackTrack(
        TREGEX_DATA     *this,
        const
        re_Token        *pattern,
        MatchData       *pMatchData,
        int             pi
    );
    /* matchcount: matches one regex token including quantifiers and sets count
    for number of quantifiers, returns number of characters eaten */
    int             TRegex_MatchCount(
        TREGEX_DATA     *this,
        const
        re_Token        *pattern,
        MatchData       *pMatchData,
        int             pi,
        const
        char            *text,
        int             i
    );
    /* matchone: matches one regex token ignoring quantifiers, returns number of characters eaten */
    int             TRegex_MatchOne(
        TREGEX_DATA     *this,
        const
        re_Token        *pattern,
        MatchData       *pMatchData,
        int             pi,
        const
        char            *text,
        int             i
    );
    /* matchOneCLC: matches one class character, returns number of chars eaten */
    int             TRegex_MatchOneCLC(
        ClassChar       pattern,
        const
        char            *pText,
        int             i,
        Modifiers       modifiers
    );
    /* more matching functions which must ALL have the same interface */
    int             TRegex_MatchWhiteSpace(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchNotWhiteSpace(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchDigit(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchNotDigit(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchWordChar(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchNotWordChar(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchNewLine(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchWordBoundary(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchNotWordBoundary(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );

    int TRegex_MatchStart(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchEnd(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );
    int TRegex_MatchAny(
        const
        char            *pText,         // Text pointer
        int             i,              // Index into pText
        Modifiers       modifiers
    );

    /* the array of all Metabsls (sequences that begin with a backslash) */
    static
    const
    struct {
        char       pattern;
        int        (*validator)(const char*, int, Modifiers);
    } Metabsls[] = {
        {'s', TRegex_MatchWhiteSpace},
        {'S', TRegex_MatchNotWhiteSpace},
        {'d', TRegex_MatchDigit},
        {'D', TRegex_MatchNotDigit},
        {'w', TRegex_MatchWordChar},
        {'W', TRegex_MatchNotWordChar},
        {'R', TRegex_MatchNewLine},
        {'b', TRegex_MatchWordBoundary},
        {'B', TRegex_MatchNotWordBoundary}
    };
    static
    const
    int     cMetabsls =  sizeof(Metabsls)/sizeof(Metabsls[0]);

    
    /* the array of all metachars */
    static
    const
    struct {
         char       pattern;
         int        (*validator)(const char*, int, Modifiers);
    } MetaChars[] = {
         {'^', TRegex_MatchStart},
         {'$', TRegex_MatchEnd},
         {'.', TRegex_MatchAny}
    };
    static
    const
    int     cMetaChars =  sizeof(MetaChars)/sizeof(MetaChars[0]);

    
     /* the array of all quantifiers */
    static
    const
    struct {
         char       pattern;
         Quantifier min;
         Quantifier max;
     } Quantifiers[] = {
         {'?', 0, 1},
         {'*', 0, QUANTIFIER_MAX},
         {'+', 1, QUANTIFIER_MAX}
     };
    static
    const
    int     cQuantifiers =  sizeof(Quantifiers)/sizeof(Quantifiers[0]);

 #define MOD_I 0b00000001
 #define MOD_S 0b00000010
 #define MOD_B 0b00000100

    static
    const
    struct {
        char       pattern;
        Modifiers  modifier;
    } ModifierChars[] = {
        {'i', MOD_I}, /* case Insensitive */
        {'s', MOD_S}, /* Single line (DOTALL) */
        {'<', MOD_B}  /* backwards */
    };
    static
    const
    int     cModifierChars =  sizeof(ModifierChars)/sizeof(ModifierChars[0]);

    
 /*
  * GLOBAL VARIABLES
  */

 // stack of pointers to GROUP/CGROUP/LOOKAROUND/INVLOOKAROUND tokens
 //re_Token* groupstack[MAXGROUPS] = {0};
 //int groupstacki = 0;

 // ====================== END OF NEW ==============================


    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

// ====================== NEW =====================================
/*
 * COMPILATION FUNCTIONS
 */

int         TRegex_CompileGreedy(
    re_Token*       pToken,
    const
    char*           pPattern
)
{
    switch (pPattern[0]) {
        case '?':
            pToken->greedy = false;
            return 1;
        default:
            pToken->greedy = true;
            return 0;
    }
}



int          TRegex_CompileAtomic(
    re_Token*       pToken,
    const
    char*           pPattern
)
{
    switch (pPattern[0]) {
        case '+':
            pToken->atomic = true;
            return 1;
        default:
            pToken->atomic = false;
            return 0;
    }
}



int      TRegex_CompileQuantifier(
    re_Token    *pToken,
    const
    char        *pPattern
)
{
    int         i;

    pToken->quantifierMin = 1;
    pToken->quantifierMax = 1;

    /* is a quantifier char */
    for (int i = 0; i < cQuantifiers; ++i) {
        if (pPattern[0] == Quantifiers[i].pattern) {
            pToken->quantifierMin = Quantifiers[i].min;
            pToken->quantifierMax = Quantifiers[i].max;
            return 1;
        }
    }
    if (pPattern[0] != '{')
        /* there is no quantifier */
        return 0;

    /* from now in, it checks inside the {} */

    /* loop to check min quantifier */
    pToken->quantifierMin = 0;
    for (i = 1; pPattern[i]; ++i) {
        if (ascii_isNumericA(pPattern[i])) {
            pToken->quantifierMin *= 10;
            pToken->quantifierMin += pPattern[i] - '0';
        } else if (pPattern[i] == ',') {
            /* start entering the max, but first if there is no max set it to
             *  QUANTIFIERMAX (infinity)
             */
            ++i;
            if (pPattern[i] == '}') {
                pToken->quantifierMax = QUANTIFIER_MAX;
                return i+1;
            }
            break;
        } else if (pPattern[i] == '}') {
            // it only has one value with no comma
            pToken->quantifierMax = pToken->quantifierMin;
            return i+1;
        } else {
            /* invalid character in {}, treat entire thing as literal */
            pToken->quantifierMin = 1;
            pToken->quantifierMax = 1;
            return 0;
        }
    }
    /* loop to check max quantifier */
    pToken->quantifierMax = 0;
    for (; pPattern[i]; ++i) {
        if (ascii_isNumericA(pPattern[i])) {
            pToken->quantifierMax *= 10;
            pToken->quantifierMax += pPattern[i] - '0';
        } else if (pPattern[i] == '}') {
            /* finish entering max */
            return i+1;
        } else {
            /* invalid character in {}, treat entire thing as literal */
            pToken->quantifierMin = 1;
            pToken->quantifierMax = 1;
            return 0;
        }
    }
    if (!pPattern[i])
        /* pattern ends on an open {, treat entire thing as literal */
        return 0;

    return i+1;
}



/*
 Compile one class character,
 return number of chars eaten
 */
int          TRegex_CompileOneCLC(
    ClassChar       *pCCL,
    const
    char*           pPattern
)
{
    switch (pPattern[0]) {
        case '\\':
            if (!pPattern[1]) {
                /* invalid regex, doesn't end the \ or close the [ */
                errno = EINVAL;
                return 0;
            }
            /* is a metabsls */
            for (int i = 0; i < cMetabsls; ++i) {
                if (pPattern[1] == Metabsls[i].pattern) {
                    pCCL->type = CCL_METABSL;
                    pCCL->meta = i;
                    return 2;
                }
            }
            /* literal escaped char */
            pCCL->type = CCL_CHARRANGE;
            pCCL->first = pPattern[1];
            return 2;
        case '\0': /* FALLTHROUGH */
        case ']':
            /* shouldn't happen */
            errno = EINVAL;
            return 0;
        default:
            /* literal char */
            pCCL->type = CCL_CHARRANGE;
            pCCL->first = pPattern[0];
            return 1;
    }
    /* UNREACHABLE */
}



int         TRegex_CompileRange(
    ClassChar*  pCCL,
    const
    char*       pattern
)
{
    if (pattern[0] != '-') {
        /* not a range */
        if (pCCL->type == CCL_CHARRANGE)
            pCCL->last = pCCL->first;
        return 0;
    }
    if (pCCL->type != CCL_CHARRANGE) {
        /* the previous char was not range-able (e.g. was a Metabsl [\w-b] ) */
        errno = EINVAL;
        return 0;
    }
    // pattern[0] == '-'
    switch (pattern[1]) {
        case '\\':
            if (pattern[2] == '\0') {
                /* invalid regex, ends on a backslash */
                errno = EINVAL;
                return 0;
            }
            for (int i = 0; i < cMetabsls; ++i) {
                if (pattern[2] == Metabsls[i].pattern) {
                    /* a range from a character to a metabsl; error (e.g. [b-\w] )*/
                    errno = EINVAL;
                    return 0;
                }
            }
            /* range from a character to an escaped literal char (e.g. [H-\Z]) */
            pCCL->last = pattern[2];
            return 4;
        case ']':
            /* ccl ends on dash; (e.g. [asdf-]); treat dash as literal */
            pCCL->last = pCCL->first;
            return 0;
        case '\0':
            /* ccl ends unclosed on dash; error */
            errno = EINVAL;
            return 0;
        default:
            /* regular range from char to char */
            pCCL->last = pattern[1];
            return 2;
    }
    /* UNREACHABLE */
}



/*
 Compile one regex token,
 return number of chars eaten
 */
int         TRegex_CompileOne(
    TREGEX_DATA     *this,
    re_Token        *pToken,
    const
    char            *pPattern,
    ClassChar       cclbuf[CCLBUFLEN],
    int             *ccli)
{
    int             i;
    
    switch (pPattern[0]) {
        case '\\':
            if (!pPattern[1]) {
                /* invalid regex, has \ as last character */
                errno = EINVAL;
                return 0;
            }
            /* is a metabsls */
            for (int i = 0; i < cMetabsls; ++i) {
                if (pPattern[1] == Metabsls[i].pattern) {
                    /* metabackslash */
                    pToken->type = TOKEN_METABSL;
                    pToken->meta = i;
                    /* used by both compilation and matching to store modifiers of groups */
                    return 2;
                }
            }
            /* literal escaped char */
            pToken->type = TOKEN_CHAR;
            pToken->ch = pPattern[1];
            return 2;
        case '[':
            /* character class */
            pToken->type = TOKEN_CHARCLASS;
            pToken->ccl = &cclbuf[*ccli];
            i = 1;
            if (pPattern[i] == '^') {
                ++i;
                pToken->type = TOKEN_INVCHARCLASS;
            }
            while (pPattern[i] && pPattern[i] != ']') {
                errno = 0;
                if (*ccli >= CCLBUFLEN) {
                    /* buffer is too small */
                    errno = ENOBUFS; /* technically, this errno code refers to
                                      buffer space in a file stream, but I think
                                      it is still appropriate */
                    return 0;
                }
                i += TRegex_CompileOneCLC(&cclbuf[*ccli], pPattern+i);
                if (errno)
                    return 0;
                i += TRegex_CompileRange(&cclbuf[*ccli], pPattern+i);
                if (errno)
                    return 0;
                ++*ccli;
            }
            if (!pPattern[i]) {
                /* invalid regex, doesn't close the [ */
                errno = EINVAL;
                return 0;
            }
            if (*ccli >= CCLBUFLEN) {
                /* buffer is too small for null terminator */
                errno = ENOBUFS;
                return 0;
            }
            cclbuf[(*ccli)++].type = CCL_END;
            return i+1;
        case '(':
            /* group, cgroup, lookahead or inverted lookahead */
            i = 1;

            pToken->type = TOKEN_CGROUP;
            if (pPattern[i] == '?') {
                pToken->type = TOKEN_GROUP;
                ++i;
            }

            for (;;) {
                for (int j = 0; j < cModifierChars; ++j) {
                    if (pPattern[i] == ModifierChars[j].pattern) {
                        pToken->modifiers |= ModifierChars[j].modifier;
                        ++i;
                        goto modifierFound;
                    }
                }
                if (pPattern[i] == '-') {
                    ++i;
                    for (int j = 0; j < cModifierChars; ++j) {
                        if (pPattern[i] == ModifierChars[j].pattern) {
                            pToken->modifiers &= ~ModifierChars[j].modifier;
                            ++i;
                            goto modifierFound;
                        }
                    }
                    --i;
                }
                break;
modifierFound:
                continue;
            }

            if (pPattern[i] == '=') {
                pToken->type = TOKEN_LOOKAROUND;
                ++i;
            } else if (pPattern[i] == '!') {
                pToken->type = TOKEN_INVLOOKAROUND;
                ++i;
            } else if (pPattern[i] == ':') {
                ++i;
            }

            ptrArray_PushData(this->pTokenStack, pToken);

            return i;
        case ')':
            /* group end */
            pToken->type = TOKEN_END;
            if (0 == ptrArray_getSize(this->pTokenStack)) {
                errno = EINVAL;
                return 0;
            }
            re_Token        *pSavedToken = ptrArray_PopData(this->pTokenStack);
            pToken->grouplen = pSavedToken->grouplen
                             = (int)(pToken - pSavedToken);
            return 1;
        case '\0':
            /* shouldn't happen */
            errno = EINVAL;
            return 0;
        default:
            /* is a metachar */
            for (int i = 0; i < cMetaChars; ++i) {
                if (pPattern[0] == MetaChars[i].pattern) {
                    pToken->type = TOKEN_METACHAR;
                    pToken->meta = i;
                    return 1;
                }
            }
            
            /* literal char */
            pToken->type = TOKEN_CHAR;
            pToken->ch = pPattern[0];
            return 1;
    }
    /* UNREACHABLE */
}



void            TRegex_CompilePattern(
    TREGEX_DATA     *this,
    const
    char            *pPattern
)
{
    int         pi = 0; /* index into pattern  */
    int         ri = 0; /* index into tokens */

    ptrArray_DeleteAll(this->pTokenStack);
    TRegex_DeleteTokens(this);
    this->ccli = 0;

    while (pPattern[pi] != '\0') {
        errno = 0;
        TRegex_ExpandTokens(this, ri+1);
        ++this->sizeTokens;
        if (!ri)
            this->pTokens[ri].modifiers = 0;
        else
            this->pTokens[ri].modifiers = this->pTokens[ri-1].modifiers;
        pi +=   TRegex_CompileOne(
                                this,
                                &this->pTokens[ri],
                                &pPattern[pi],
                                this->cclbuf,
                                &this->ccli
                );
        if (errno)
            return;
    
        pi += TRegex_CompileQuantifier(&this->pTokens[ri], &pPattern[pi]);
        if (errno)
            return;
        pi += TRegex_CompileGreedy(&this->pTokens[ri], &pPattern[pi]);
        if (errno)
            return;
        pi += TRegex_CompileAtomic(&this->pTokens[ri], &pPattern[pi]);
        if (errno)
            return;
        
        if (this->pTokens[ri].type == TOKEN_END) {
            int         adj = ri - this->pTokens[ri].grouplen;
            this->pTokens[adj].quantifierMin = this->pTokens[ri].quantifierMin;
            this->pTokens[adj].quantifierMax = this->pTokens[ri].quantifierMax;
            this->pTokens[adj].atomic = this->pTokens[ri].atomic;
            this->pTokens[adj].greedy = this->pTokens[ri].greedy;
        }

        ++ri;
    }

    /* indicate the end of the regex */
    TRegex_ExpandTokens(this, ri+1);
    ++this->sizeTokens;
    this->pTokens[ri].type = TOKEN_END;
    this->pTokens[ri].grouplen = -1;

    if (ptrArray_getSize(this->pTokenStack))
        errno = EINVAL;
}



/*
 * MATCHING FUNCTIONS
 */

    int         TRegex_MatchWhiteSpace(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers)
    {
        UNUSED(modifiers);
        if (!ascii_isWhiteSpaceA(pText[i])) {
            errno = EINVAL;
            return 0;
        }
        return 1;
    }
        
        
        
    int         TRegex_MatchNotWhiteSpace(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (!pText[i] || ascii_isWhiteSpaceA(pText[i])) {
            errno = EINVAL;
            return 0;
        }
        return 1;
    }
        
        
        
    int         TRegex_MatchDigit(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (!ascii_isNumericA(pText[i])) {
            errno = EINVAL;
            return 0;
        }
        return 1;
    }
        
        
        
    int         TRegex_MatchNotDigit(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (!pText[i] || ascii_isNumericA(pText[i])) {
            errno = EINVAL;
            return 0;
        }
        return 1;
    }
        
        

    int         TRegex_MatchWordChar(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (!ascii_isLabelCharW32(pText[i])) {
            errno = EINVAL;
            return 0;
        }
        return 1;
    }
        
        

    int         TRegex_MatchNotWordChar(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (!pText[i] || ascii_isLabelCharW32(pText[i])) {
            errno = EINVAL;
            return 0;
        }
        return 1;
    }
        
        
        
    int     TRegex_MatchNewLine(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (pText[i] == '\r' && pText[i+1] == '\n')
            return 2;
        else if (pText[i] == '\n')
            return 1;
        errno = EINVAL;
        return 0;
    }
        
        
    int     TRegex_MatchWordBoundary(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (
            (i > 0 && ascii_isLabelCharW32(pText[i-1]) != !ascii_isLabelCharW32(pText[i]))
            || (i == 0 && !ascii_isLabelCharW32(pText[0]))
        ) {
            errno = EINVAL;
            return 0;
        }
        return 0;
    }
        
        

    int         TRegex_MatchNotWordBoundary(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (
            (i > 0 && ascii_isLabelCharW32(pText[i-1]) == !ascii_isLabelCharW32(pText[i]))
            || (i == 0 && ascii_isLabelCharW32(pText[0]))
        ) {
            errno = EINVAL;
            return 0;
        }
        return 0;
    }

        

    int         TRegex_MatchStart(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(pText);
        UNUSED(modifiers);
        if (i) {
            errno = EINVAL;
            return 0;
        }
        return 0;
    }
        
        

    int         TRegex_MatchEnd(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        UNUSED(modifiers);
        if (pText[i] != '\0') {
            errno = EINVAL;
            return 0;
        }
        return 0;
    }
        
        

    int         TRegex_MatchAny(
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        if (pText[i] == '\0' || (!(modifiers & MOD_S) && pText[i] == '\n')) {
            errno = EINVAL;
            return 0;
        }
        return 1;
    }



    int         TRegex_MatchOneCLC(
        ClassChar   pattern,
        const
        char        *pText,
        int         i,
        Modifiers   modifiers
    )
    {
        /* this function always returns 1 */
        switch (pattern.type) {
            case CCL_METABSL:
                errno = 0;
                Metabsls[pattern.meta].validator(pText, i, modifiers);
                if (errno)
                    return 0;
                return 1;
            case CCL_CHARRANGE:
                if (
                    ( (modifiers & MOD_I)
                     && (ascii_toLowerA(pText[i]) < ascii_toLowerA(pattern.first)
                            || ascii_toLowerA(pText[i]) > ascii_toLowerA(pattern.last)))
                    || (!(modifiers & MOD_I) && (pText[i]  <  pattern.first
                                        || pText[i] > pattern.last ))
                ) {
                    errno = EINVAL;
                    return 0;
                }
                return 1;
            default:
                /* should never happen */
                errno = EINVAL;
                return 0;
        }
        /* UNREACHABLE */
    }

        
        
    /*  Compiles one regex token,
        returns number of chars eaten
     */
    int         TRegex_MatchOne(
        TREGEX_DATA     *this,
        const
        re_Token        *pPattern,
        MatchData       *pMatchData,
        int             pi,
        const
        char            *pText,
        int             i
    )
    {
        int             cChars;
        int             ccli;
        
        switch (pPattern[pi].type) {
            case TOKEN_CGROUP:
                /* TODO capturing */
                /* FALLTHROUGH */
            case TOKEN_GROUP:
                cChars = TRegex_MatchPattern(this, pPattern, pMatchData, pi+1, pText, i);
                return cChars;
            case TOKEN_LOOKAROUND:
                cChars = TRegex_MatchPattern(this, pPattern, pMatchData, pi+1, pText, i);
                return 0;
            case TOKEN_INVLOOKAROUND:
                cChars = TRegex_MatchPattern(this, pPattern, pMatchData, pi+1, pText, i);
                if (errno == EINVAL)
                    errno = 0;
                else if (!errno)
                    errno = EINVAL;
                return 0;
            case TOKEN_METABSL:
                errno = 0;
                cChars =     Metabsls[pPattern[pi].meta].validator(
                                                              pText,
                                                              i,
                                                              pPattern[pi].modifiers
                            );
                if (errno)
                    return 0;
                return cChars;
            case TOKEN_METACHAR:
                errno = 0;
                cChars = MetaChars[pPattern[pi].meta].validator(
                                                        pText,
                                                        i,
                                                        pPattern[pi].modifiers
                        );
                if (errno)
                    return 0;
                return cChars;
            case TOKEN_CHARCLASS:
                ccli = 0;
                while (pPattern[pi].ccl[ccli].type != CCL_END) {
                    errno = 0;
                    i +=    TRegex_MatchOneCLC(
                                        pPattern[pi].ccl[ccli],
                                        pText,
                                        i,
                                        pPattern[pi].modifiers
                            );
                    if (!errno)
                        return 1;
                    ++ccli;
                }
                // all the chars in the class failed; matching failed
                errno = EINVAL;
                return 0;
            case TOKEN_INVCHARCLASS:
                if (!pText[i]) {
                    errno = EINVAL;
                    return 0;
                }
                ccli = 0;
                while (pPattern[pi].ccl[ccli].type != CCL_END) {
                    errno = 0;
                    i += TRegex_MatchOneCLC(pPattern[pi].ccl[ccli], pText, i, pPattern[pi].modifiers);
                    if (!errno) {
                        // matchOneCLC succeeded; fail the charclass
                        errno = EINVAL;
                        return 0;
                    }
                    ++ccli;
                }
                /* all the chars in the class failed; matching succeeded */
                errno = 0;
                return 1;
            case TOKEN_CHAR:
                if (
                    ( (pPattern[pi].modifiers & MOD_I) && ascii_toLowerA(pPattern[pi].ch) != ascii_toLowerA(pText[i])) ||
                    (!(pPattern[pi].modifiers & MOD_I) && pPattern[pi].ch != pText[i] )
                ) {
                    errno = EINVAL;
                    return 0;
                }
                return 1;
            default:
                // unknown re_Token type: should never happen
                errno = EINVAL;
                return 0;
        }
        /* UNREACHABLE */
    }
        
        

/*
 match one pattern on a string,
 return number of chars eaten
 */
int             TRegex_MatchPattern(
    TREGEX_DATA     *this,
    const
    re_Token        *pToken,
    MatchData       *pMatchData,
    int             pi,
    const
    char            *pText,
    int             i
)
{
    int         pos = i;

    for (; pToken[pi].type != TOKEN_END; ++pi) {
        pMatchData[pi].position = pos;
        pos += TRegex_MatchCount(this, pToken, pMatchData, pi, pText, pos);

        while (pMatchData[pi].count < pToken[pi].quantifierMin) {
            errno = 0;
            pi = TRegex_BackTrack(this, pToken, pMatchData, pi);
            if (errno)
                return 0;

            pos = pMatchData[pi].position;
            pos += TRegex_MatchCount(this, pToken, pMatchData, pi, pText, pos);
        }
        if (    pToken[pi].type == TOKEN_GROUP
            ||  pToken[pi].type == TOKEN_CGROUP
            ||  pToken[pi].type == TOKEN_LOOKAROUND
            ||  pToken[pi].type == TOKEN_INVLOOKAROUND
            ) {
            pi += pToken[pi].grouplen;
        }
    }
    errno = 0;
    return pos-i;
}

    

/*
 Backtrack into the pattern, (why? and where?)
 returns new starting index
 */
int         TRegex_BackTrack(
    TREGEX_DATA     *this,
    const
    re_Token        *pPattern,
    MatchData       *pMatchData,
    int             pi
)
{
    
    while (pi--) {
        if (    pPattern[pi].type == TOKEN_GROUP
            ||  pPattern[pi].type == TOKEN_CGROUP
            ||  pPattern[pi].type == TOKEN_LOOKAROUND
            ||  pPattern[pi].type == TOKEN_INVLOOKAROUND
            ) {
            errno = EINVAL;
            return 0;
        }
        if (pPattern[pi].type == TOKEN_END) {
            const
            int         endpi = pi;
            pi -= pPattern[pi].grouplen;
            if (    pPattern[pi].type == TOKEN_LOOKAROUND
                ||  pPattern[pi].type == TOKEN_INVLOOKAROUND
                ||  pPattern[pi].atomic
                ) {
                continue;
            }

            errno = 0;
            TRegex_BackTrack(this, pPattern, pMatchData, endpi);
            if (!errno)
                return pi;
        }
        if (!pPattern[pi].atomic
            &&  pPattern[pi].greedy
            &&  pMatchData[pi].count > pPattern[pi].quantifierMin
            ) {
            --pMatchData[pi].count;
            for (int j = pi+1; j < this->sizeTokens; ++j) {
                pMatchData[j].count = pPattern[j].greedy
                                    ? pPattern[j].quantifierMax
                                    : pPattern[j].quantifierMin;
            }
            errno = 0;
            return pi;
        } else if (     !pPattern[pi].atomic
                   &&   !pPattern[pi].greedy
                   &&   pMatchData[pi].count < pPattern[pi].quantifierMax
                   ) {
            ++pMatchData[pi].count;
            for (int j = pi+1; j < this->sizeTokens; ++j) {
                pMatchData[j].count = pPattern[j].greedy
                                    ? pPattern[j].quantifierMax
                                    : pPattern[j].quantifierMin;
            }
            errno = 0;
            return pi;
        }
    }
    
    /* all backtracking has been done, fail */
    errno = EINVAL;
    return 0;
}

    
        
/*
 Match one regex token including quantifiers and set count
 for number of quantifiers,
 returns number of characters eaten
 */
int             TRegex_MatchCount(
    TREGEX_DATA     *this,
    const
    re_Token        *pToken,
    MatchData       *pMatchData,
    int             pi,
    const
    char            *pText,
    int             i
)
{
    const
    int             oldi = i;
    Quantifier      c;

    for (c = 0; c < pMatchData[pi].count; ++c) {
        errno = 0;
        i += TRegex_MatchOne(this, pToken, pMatchData, pi, pText, i);
        if (errno) {
            pMatchData[pi].count = c;
            return i - oldi;
        }
    }
    return i - oldi;
}

    

// re_match
/*
 re_match: returns index of first match of pattern in text
 stores the length of the match in length if it is not NULL
 */
int             TRegex_MatchInt(
    TREGEX_DATA     *this,
    const
    char            *pText,
    int             *pLength
)
{
    int             i;
    int             j;
    MatchData       *pMatchData;

    if (0 == this->sizeTokens) {
        errno = ENODATA;
        return 0;
    }
    pMatchData = mem_Malloc(this->sizeTokens * sizeof(MatchData));
    if (NULL == pMatchData) {
        errno = ENOMEM;
        if (pLength)
            pLength = 0;
        return 0;
    }

    for (i = 0; (i == 0 || pText[i-1]); i++) {
        int             lengthBuf;

        errno = 0;
        for (j = 0; j < this->sizeTokens; j++) {
            pMatchData[j].count = this->pTokens[j].greedy
                        ? this->pTokens[j].quantifierMax
                        : this->pTokens[j].quantifierMin;
            
        }
        lengthBuf = TRegex_MatchPattern(this, this->pTokens, pMatchData, 0, pText, i);
        if (!errno) {
            mem_Free(pMatchData);
            /* first successful match */
            if (pLength)
                *pLength = lengthBuf;
            return i;
        }
    }
    
    /* no matches */
    mem_Free(pMatchData);
    errno = EINVAL;
    if (pLength)
        pLength = 0;
    return 0;
}

    

/*
 re_matchg: returns number of matches of pattern in text
 */
int             TRegex_Matchg(
    TREGEX_DATA     *this,
    const
    char            *pText
)
{
    int             i = 0;
    int             c = 0;
    int             length = 0;

    while (pText[i]) {
        errno = 0;
        i += TRegex_MatchInt(this, pText+i, &length);
        if (errno)
            return c;
        ++c;
        i += length;
    }
    
    return c;
}

    
    
    


    /*
     * PRINTING FUNCTIONS
     */

    static
    ASTR_DATA *     TRegex_PrintOneCLC(
        ClassChar       *pPattern
    )
    {
        ASTR_DATA       *pStr;
        
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }
        
        switch (pPattern->type) {
            case CCL_METABSL:
                AStr_AppendPrint(pStr, "\\%c", Metabsls[pPattern->meta].pattern);
                break;
            case CCL_CHARRANGE:
                AStr_AppendCharA(pStr, pPattern->first);
                if (pPattern->last != pPattern->first) {
                    AStr_AppendCharA(pStr, pPattern->last);
                }
                break;
            default:
                /* shouldn't happen */
                errno = EINVAL;
                obj_Release(pStr);
                return OBJ_NIL;
        }
        
        return pStr;
    }

    
    
    static
    ASTR_DATA *     TRegex_PrintOne(
        re_Token        *pToken
    )
    {
        ASTR_DATA       *pStr;
        ASTR_DATA       *pStrWrk;

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }
        
        switch (pToken->type) {
            case TOKEN_END:
                AStr_AppendA(pStr, ")");
                break;
            case TOKEN_GROUP:
                AStr_AppendA(pStr, "(?:");
                return pStr;
            case TOKEN_CGROUP:
                AStr_AppendA(pStr, "(");
                return pStr;
            case TOKEN_LOOKAROUND:
                AStr_AppendA(pStr, "(?=");
                return pStr;
            case TOKEN_INVLOOKAROUND:
                AStr_AppendA(pStr, "(?!");
                return pStr;
            case TOKEN_METABSL:
                AStr_AppendPrint(pStr, "\\%c", Metabsls[pToken->meta].pattern);
                break;
            case TOKEN_METACHAR:
                AStr_AppendCharA(pStr, MetaChars[pToken->meta].pattern);
                break;
            case TOKEN_CHARCLASS: /* fallthrough */
            case TOKEN_INVCHARCLASS:
                AStr_AppendA(pStr, "[");
                if (pToken->type == TOKEN_INVCHARCLASS)
                    printf("^");
                for (int i = 0; pToken->ccl[i].type != CCL_END; ++i) {
                    pStrWrk = TRegex_PrintOneCLC(&pToken->ccl[i]);
                    AStr_Append(pStr, pStrWrk);
                    obj_Release(pStrWrk);
                }
                AStr_AppendA(pStr, "]");
                break;
            case TOKEN_CHAR:
                AStr_AppendCharA(pStr, pToken->ch);
                break;
            default:
                /* unknown token type: shouldn't happen */
                errno = EINVAL;
                obj_Release(pStr);
                return OBJ_NIL;
        }
        for (int i = 0; i < sizeof(Quantifiers)/sizeof(Quantifiers[0]); ++i) {
            if (pToken->quantifierMin == Quantifiers[i].min && pToken->quantifierMax == Quantifiers[i].max) {
                AStr_AppendCharA(pStr, Quantifiers[i].pattern);
                goto nocharquantifier;
            }
        }
        if (pToken->quantifierMin != 1 || pToken->quantifierMax != 1) {
            AStr_AppendA(pStr, "{");
            if (pToken->quantifierMin != 0)
                AStr_AppendPrint(pStr, "%d", pToken->quantifierMin);
            if (pToken->quantifierMax == QUANTIFIER_MAX)
                AStr_AppendA(pStr, ",");
            else if (pToken->quantifierMax != pToken->quantifierMin)
                AStr_AppendPrint(pStr, "%d", pToken->quantifierMax);
            AStr_AppendA(pStr, "}");
        }
    nocharquantifier:
        if (!pToken->greedy)
            AStr_AppendA(pStr, "?");
        if (pToken->atomic)
            AStr_AppendA(pStr, "+");

        return pStr;
    }

    

    ERESULT         TRegex_DeleteTokens(
        TREGEX_DATA     *this
    )
    {
        
        // Do initialization.
        if( this == NULL )
            return ERESULT_INVALID_OBJECT;
        
        if (this->pTokens) {
            mem_Free(this->pTokens);
            this->pTokens = NULL;
            this->sizeTokens = 0;
            this->maxTokens = 0;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         TRegex_ExpandTokens(
        TREGEX_DATA     *this,
        int             num
    )
    {
        void            *pWork;
        uint32_t        oldMax;
        uint32_t        cbSize;
        int             elemSize = sizeof(re_Token);
        int             i;
        
        // Do initialization.
        if( this == NULL )
            return ERESULT_INVALID_OBJECT;
        if (num < this->maxTokens) {
            return ERESULT_SUCCESSFUL_COMPLETION;
        }
        
        // Expand the Array.
        oldMax = this->maxTokens;
        if (0 == oldMax) {
            oldMax = 1;
        }
        this->maxTokens = oldMax << 1;                // max *= 2
        while (num > this->maxTokens) {
            this->maxTokens = this->maxTokens << 1;
        }
        cbSize = this->maxTokens * elemSize;
        pWork = (void *)mem_Malloc(cbSize);
        if( NULL == pWork ) {
            this->maxTokens = oldMax;
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Copy the old entries into the new array.
        if( this->pTokens == NULL )
            ;
        else {
            memmove(pWork, this->pTokens, (oldMax * elemSize));
            mem_Free(this->pTokens);
            // this->pTokens = NULL;
        }
        this->pTokens = pWork;
        memset(&this->pTokens[oldMax], 0, ((this->maxTokens - oldMax) * elemSize));
        for (i=oldMax; i<this->maxTokens; i++) {
            this->pTokens[i].index = i;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TREGEX_DATA *   TRegex_Alloc (
        void
    )
    {
        TREGEX_DATA     *this;
        uint32_t        cbSize = sizeof(TREGEX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TREGEX_DATA *   TRegex_New (
        void
    )
    {
        TREGEX_DATA     *this;
        
        this = TRegex_Alloc( );
        if (this) {
            this = TRegex_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        TRegex_getSize (
        TREGEX_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  TRegex_getSuperVtbl (
        TREGEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
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
        ERESULT eRc = TRegex_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TREGEX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         TRegex_Assign (
        TREGEX_DATA		*this,
        TREGEX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TRegex_Validate(pOther)) {
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
    //                       C o m p i l e
    //---------------------------------------------------------------
    
    ERESULT         TRegex_Compile (
        TREGEX_DATA     *this,
        const
        char            *pPattern
    )
    {

#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        this->sizeTokens = 0;

        TRegex_CompilePattern(this, pPattern);

        return ERESULT_SUCCESS;
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
    int             TRegex_Compare (
        TREGEX_DATA     *this,
        TREGEX_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!TRegex_Validate(pOther)) {
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
        TRegex      *pCopy = TRegex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TREGEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TREGEX_DATA *   TRegex_Copy (
        TREGEX_DATA     *this
    )
    {
        TREGEX_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TRegex_New( );
        if (pOther) {
            eRc = TRegex_Assign(this, pOther);
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

    void            TRegex_Dealloc (
        OBJ_ID          objId
    )
    {
        TREGEX_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TREGEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pTokens) {
            mem_Free(this->pTokens);
            this->pTokens = NULL;
            this->maxTokens = 0;
            this->sizeTokens = 0;
        }
        if (this->pTokenStack) {
            obj_Release(this->pTokenStack);
            this->pTokenStack = OBJ_NIL;
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
    ERESULT         TRegex_Disable (
        TREGEX_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!TRegex_Validate(this)) {
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
    ERESULT         TRegex_Enable (
        TREGEX_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!TRegex_Validate(this)) {
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

    TREGEX_DATA *   TRegex_Init (
        TREGEX_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(TREGEX_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TREGEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&TRegex_Vtbl);
        
        this->pTokenStack = ptrArray_New();
        if (OBJ_NIL == this->pTokenStack) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "TRegex::sizeof(TREGEX_DATA) = %lu\n", sizeof(TREGEX_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TREGEX_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         TRegex_IsEnabled (
        TREGEX_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
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
    
    int             TRegex_MatchP(
        TREGEX_DATA     *this,
        const
        char            *pText,
        int             *pLength
    )
    {
        int             idx = 0;
        int             length = 0;

                // Do initialization.
        #ifdef NDEBUG
        #else
                if (!TRegex_Validate(this)) {
                    DEBUG_BREAK();
                    //return ERESULT_INVALID_OBJECT;
                    return -1;
                }
        #endif

        if (this->pTokens != NULL) {
            idx = TRegex_MatchInt(this, pText, &length);
        }

        if (pLength)
            *pLength = length;
        return idx;
    }

    
    int             TRegex_Match(
        TREGEX_DATA     *this,
        const
        char            *pattern,
        const
        char            *pText,
        int             *pLength
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
#endif
                
        eRc = TRegex_Compile(this, pattern);
        if (ERESULT_FAILED(eRc)) {
            //return eRc;
            return -1;
        }
        
      return TRegex_MatchP(this, pText, pLength);
    }

    

    //---------------------------------------------------------------
    //                P a r s e  J s o n  O b j e c t
    //---------------------------------------------------------------
    
#ifdef  TREGEX_JSON_SUPPORT
     TREGEX_DATA * TRegex_ParseJsonObject (
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
        void        *pMethod = TRegex_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "TRegex", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          TRegex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TREGEX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TREGEX_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)TRegex_Class();
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
                            return TRegex_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return TRegex_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return TRegex_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return TRegex_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == TRegex_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == TRegex_ToJson)
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
    
#ifdef  TREGEX_JSON_SUPPORT
     ASTR_DATA *     TRegex_ToJson (
        TREGEX_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
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
        ASTR_DATA      *pDesc = TRegex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     TRegex_ToDebugString (
        TREGEX_DATA     *this,
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
        if (!TRegex_Validate(this)) {
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
                    TRegex_getSize(this),
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
    
    
    ASTR_DATA *     TRegex_ToStringPattern (
        TREGEX_DATA     *this
    )
    {
        ASTR_DATA       *pStr;
        ASTR_DATA       *pStrWrk;
        int             i;
        int             iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TRegex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
                      
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        AStr_AppendPrint(pStr, "\tcTokens: %d\n", this->sizeTokens);
        
        iMax = this->sizeTokens;
        for (i = 0; i < iMax; i++) {
            if (this->pTokens[i].type == TOKEN_END) {
                break;
            }
            if (this->pTokens[i].grouplen == SIZE_MAX) {
                break;
            }
            pStrWrk = TRegex_PrintOne(&this->pTokens[i]);
            obj_Release(pStrWrk);
            pStrWrk = OBJ_NIL;
        }
        
        return pStr;
    }




    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            TRegex_Validate (
        TREGEX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TREGEX))
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


        if (!(obj_getSize(this) >= sizeof(TREGEX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


