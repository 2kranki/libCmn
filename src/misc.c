// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   misc.c
 *	Generated 11/25/2015 16:57:23
 * Notes:
 *  *       Used some public domain functions written by
 *          Clarenc Lehman and Kevin Kenny.
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
#include    <misc_internal.h>
#include    <stdio.h>
#include    <ascii.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* Copy text until EOL or an '*' is found.
     */
    static
    bool            misc_CopyText(
        const
        char            **insp,
        char            **otsp
    )
    {
        int             len;
        int             i;
        W32CHR_T        wc;
        
        for (;;) {
            len = utf8_Utf8ToW32(*insp, &wc);
            if (len == -1) {    // *** Malformed UTF-8 Char ***
                return 0;
            }
            if ((wc == 0) || (wc == '*')) {
                break;
            }
            for (i=0; i<len; ++i) {
                *(*otsp)++ = *(*insp)++;
            }
        }
        
        return (wc != 0);
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MISC_DATA *     misc_Alloc(
        uint16_t        stackSize
    )
    {
        MISC_DATA       *cbp;
        uint32_t        cbSize = sizeof(MISC_DATA);
        
        // Do initialization.
        
        if (0 == stackSize) {
            stackSize = 256;
        }
        cbSize += stackSize << 2;
        cbp = obj_Alloc( cbSize );
        obj_setMisc1(cbp, stackSize);
        
        // Return to caller.
        return( cbp );
    }



    MISC_DATA *     misc_New(
        uint16_t        stackSize
    )
    {
        MISC_DATA       *cbp;
        
        cbp = misc_Alloc( stackSize );
        if (cbp) {
            cbp = misc_Init( cbp );
        } 
        return( cbp );
    }



    //---------------------------------------------------------------
    //                        A b b r e v
    //---------------------------------------------------------------
    
    /* AbbrevA() tests whether or not the input string, "text", is a valid
     * abbreviation of the pattern string, "pattern".  The pattern is a
     * string giving the input expected, with mandatory characters in
     * uppercase and optional ones in lowercase.  The function returns
     * true if the text string contains all of the required characters,
     * and no other characters except for any optional ones.
     * Examples:
     *     misc_AbbrevA("EXACT", "EXACT") == true;
     *     misc_AbbrevA("EXACT", "exact") == true;
     *     misc_AbbrevA("EXACT", "e") == false;
     *     misc_AbbrevA("Exact", "e") == true;
     *     misc_AbbrevA("eXact", "x") == true;
     *     misc_AbbrevA("eXact", "ext") == true;
     *     misc_AbbrevA("eXact", "xray") == false;
     */
    
    
    bool        misc_AbbrevA(
        const
        char            *pPattern,	// Pattern to match it against;
                                    // lowercase letters are optional
        const
        char            *pText		// Text to test
    )
    {
        while (*pPattern != '\0') {
            if ( ascii_isLowerA(*pPattern) ) {	/* Optional character */
                if ( (ascii_toLowerA(*pText) == *pPattern++)
                    && misc_AbbrevA((pText + 1), pPattern) ) {
                    return true;
                }
            }
            else {				/* Required character */
                if ( ascii_toUpperA(*pText++) != *pPattern++ ) {
                    return false;
                }
            }
        }
        
        return (*pText == '\0');
    }
    
    
    
    //---------------------------------------------------------------
    //                      B i t  R e v e r s a l
    //---------------------------------------------------------------
    
    // Knuth's bit reversal algorithm
    // from http://www.hackersdelight.org/revisions.pdf
    uint32_t        misc_BitReversal32(
        uint32_t        a
    )
    {
        uint32_t        t;
        
        a = (a << 15) | (a >> 17);
        t = (a ^ (a >> 10)) & 0x003f801f;
        a = (t + (t << 10)) ^ a;
        t = (a ^ (a >>  4)) & 0x0e038421;
        a = (t + (t <<  4)) ^ a;
        t = (a ^ (a >>  2)) & 0x22488842;
        a = (t + (t <<  2)) ^ a;
        
        return a;
    }
    
    
    // Knuth's bit reversal algorithm
    // from http://www.hackersdelight.org/revisions.pdf
    uint64_t        misc_BitReversal64(
        uint64_t        x
    )
    {
        uint64_t        t;
        x = (x << 31) | (x >> 33);   // I.e., shlr(x, 31).
        t = (x ^ (x >> 20)) & 0x00000FFF800007FFLL;
        x = (t |(t << 20)) ^ x;
        t = (x ^ (x >> 8)) & 0x00F8000F80700807LL;
        x = (t |(t << 8)) ^ x;
        t = (x ^ (x >> 4)) & 0x0808708080807008LL;
        x = (t |(t << 4)) ^ x;
        t = (x ^ (x >> 2)) & 0x1111111111111111LL;
        x = (t |(t << 2)) ^ x;
        return x;
    }
    
    
    
    //---------------------------------------------------------------
    //            C o m p u t e  E v e n  P a r i t y
    //---------------------------------------------------------------
    
    bool            misc_ComputeEvenParity32(
        uint32_t        x
    )
    {
        x ^= x >> 16;
        x ^= x >> 8;
        x ^= x >> 4;
        x ^= x >> 2;
        x ^= x >> 1;
        return ((~x) & 1) ? true : false;
    }
    
    
    bool            misc_ComputeEvenParity16(
        uint16_t        x
    )
    {
        x ^= x >> 8;
        x ^= x >> 4;
        x ^= x >> 2;
        x ^= x >> 1;
        return ((~x) & 1) ? true : false;
    }
    
    
    bool            misc_ComputeEvenParity8(
        uint8_t         x
    )
    {
        x ^= x >> 4;
        x ^= x >> 2;
        x ^= x >> 1;
        return ((~x) & 1) ? true : false;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P a t t e r n  M a t c h
    //---------------------------------------------------------------
    
    /*
     * PatternMatch() is a generalized procedure for working with "wild card"
     * names using the '*' and '?' conventions.  It is superior to the wild
     * card matcher provided in the CP/M BDOS in that it will allow operating
     * on named objects other than files.  It also will allow (and process
     * correctly) asterisks anywhere in the pattern; the pattern "*1.ASM" will
     * find any ".ASM" files whose names end in 1, no matter how long the names
     * are.
     *
     * There are two calling sequences for PatternMatch().  In the first, one
     * is interested merely in whether or not a name matches a pattern.  In
     * this calling sequence, the name is passed as the second argument, and
     * the pattern (possibly containing question marks and asterisks) is given
     * as the first.  The third argument ("equiv") is NULL, and the fourth
     * ("newname") need not be supplied.
     *
     * In the second calling sequence, the user also wishes to make an output
     * file name from the input name, in order to process requests like
     *     PIP *.BAK=*.C
     * In this case, the first two arguments are as above.  The third argument
     * "equiv" is the pattern to be used for the output name ("*.BAK" in the
     * example) and the fourth is a pointer to a character vector which will
     * receive the name.
     *
     * Question marks are not permitted in the "equiv" argument, but asterisks
     * are.  Each asterisk in the "equiv" string matches either (1) a single
     * asterisk in the input string, or (2) any number of consecutive question
     * marks in the input string.
     */
    bool            misc_PatternMatchA(
        const
        char            *pPattern,
        const
        char            *pName,
        const
        char            *pEquiv,
        char            *pNewname
    )
    {
        int             len;
        int             lenName;
        //int             i;
        W32CHR_T        cw;
        W32CHR_T        mcw;
        W32CHR_T        mcwn;
       // W32CHR_T        ncw;
        int             flag;
        bool            fRc;
        
        len = utf8_Utf8ToW32(pPattern, &mcw);
        if (len == -1) {    // *** Malformed Unicode Char ***
            return false;
        }
        pPattern += len;
        for (;;) {		/* Corresponding char */
            len = utf8_Utf8ToW32(pName, &cw);
            if (len == -1) {    // *** Malformed Unicode Char ***
                return false;
            }
            pName += len;
            lenName = len;
            if (cw == '\0') {
                break;
            }
            switch (mcw) {
                    
                case '?':				// '?' matches any single char
                    if (pEquiv) {
                        if (misc_CopyText(&pEquiv, &pNewname)) {
                            len = utf8_W32ToUtf8(cw, pNewname);
                            pNewname += len;
                            len = utf8_Utf8ToW32(pPattern, &mcwn);
                            if (mcwn != '?') {
                                len = utf8_Utf8ToW32(pEquiv, NULL);
                                pEquiv += len;
                            }
                        }
                    }
                    len = utf8_Utf8ToW32(pPattern, &mcw);
                    if (len == -1) {    // *** Malformed Unicode Char ***
                        return false;
                    }
                    pPattern += len;
                    break;
                    
                case '*':				// '*' matches any string
                    flag = 0;
                    if (pEquiv) {
                        if (misc_CopyText(&pEquiv, &pNewname))
                            flag = 1;
                    }
                    len = 0;
                    if (flag && pEquiv) {
                        len = utf8_Utf8ToW32(pEquiv, NULL);
                    }
                    fRc = misc_PatternMatchA(
                                     (pName - lenName), // Backup one char
                                     pPattern,
                                     (pEquiv + len),    // Optionally Advance one char
                                     pNewname
                             );
                    if ( fRc )
                        return true;
                    if (flag) {
                        len = utf8_W32ToUtf8(cw, pNewname);
                        pNewname += len;
                    }
                    break;
                    
                default:				/* Anything else matches only itself */
                    if (ascii_toUpperW32(mcw) != ascii_toUpperW32(cw))
                        return false;
                    len = utf8_Utf8ToW32(pPattern, &mcw);
                    if (len == -1) {    // *** Malformed Unicode Char ***
                        return false;
                    }
                    pPattern += len;
                    break;
            }
        }
        
        if ((mcw != '*' || *pPattern) && mcw) {
            return false;
        }
        if (pEquiv) {
            while (misc_CopyText(&pEquiv, &pNewname)) {
                len = utf8_Utf8ToW32(pEquiv, NULL);
                pEquiv += len;
            }
            *pNewname = '\0';
        }
        return true;
    }
    
    

    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        misc_getPriority(
        MISC_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !misc_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            misc_setPriority(
        MISC_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !misc_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        misc_getSize(
        MISC_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !misc_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            misc_Dealloc(
        OBJ_ID          objId
    )
    {
        MISC_DATA       *this = objId;
        bool            fRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !misc_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        fRc = misc_Disable(this);

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            misc_Disable(
        MISC_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !misc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            misc_Enable(
        MISC_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !misc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(cbp);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MISC_DATA *   misc_Init(
        MISC_DATA       *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (MISC_DATA *)obj_Init( this, cbSize, OBJ_IDENT_MISC );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_MISC);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&misc_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !misc_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            misc_IsEnabled(
        MISC_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !misc_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(cbp))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          misc_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MISC_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !misc_Validate(this) ) {
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
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return misc_ToDebugString;
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
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     misc_ToDebugString(
        MISC_DATA      *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(misc) side=%d ",
                     cbp,
                     misc_getSize(cbp)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString(
                                                    cbp->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            misc_Validate(
        MISC_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_MISC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(MISC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


