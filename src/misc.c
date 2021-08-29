// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   misc.c
 *	Generated 11/25/2015 16:57:23
 * Notes:
 *  *       Used some public domain functions written by
 *          Clarence Lehman and Kevin Kenny.
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
    
    typedef struct pwr_of_2_w {
        uint32_t        pwr_of_2;
        uint32_t        shift;
        uint32_t        prime;      // prime number > power_of_2
    } PWR_OF_2;
    
    PWR_OF_2        pwr_of_2[33] = {
        {1, 0, 1},
        {2, 1, 3},
        {4, 2, 5},
        {8, 3, 11},
        {16, 4, 17},
        {32, 5, 37},
        {64, 6, 67},
        {128, 7, 131},
        {256, 8, 257},
        {512, 9, 521},
        {1024, 10, 1031},
        {2048, 11, 2053},
        {4096, 12, 4099},
        {8192, 13, 8209},
        {16384, 14, 16411},
        {32768, 15, 32771},
        {65536, 16, 65537},
        {131072, 17, 131101},
        {262144, 18, 262147},
        {524288, 19, 524309},
        {1048576, 20, 1048583},
        {2097152, 21, 2097169},
        {4194304, 22, 4194319},
        {8388608, 23, 8388617},
        {16777216, 24, 16777259},
        {33554432, 25, 33554467},
        {67108864, 26, 67108879},
        {134217728, 27, 134217757},
        {268435456, 28, 268435459},
        {536870912, 29, 536870923},
        {1073741824, 30, 1073741827},
        {2147483648, 31, 2147483659},
        {0, 0}
    };


 
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
    )
    {
        MISC_DATA       *this;
        uint32_t        cbSize = sizeof(MISC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    int             misc_RangeCmpI32(
        int32_t         amt1,
        int32_t         amt2,
        uint32_t        epsilon
    )
    {
        int32_t         iRc = 0;
        
        iRc = (amt1 - amt2);
        if (iRc < 0)
            iRc = -iRc;
        if (iRc <= epsilon)
            return 1;
        
        return 0;
    }
    

    
    MISC_DATA *     misc_New(
    )
    {
        MISC_DATA       *this;
        
        this = misc_Alloc( );
        if (this) {
            this = misc_Init(this);
        } 
        return this;
    }

    
    
    uint32_t        misc_Pwr2_Prime(
        uint32_t        amt
    )
    {
        uint32_t        prime = 0;
        
        if (amt < 32)
            prime = pwr_of_2[amt].prime;
        
        return prime;
    }
    
    
    uint32_t        misc_Pwr2_Shift(
        uint32_t        amt
    )
    {
        PWR_OF_2        *pEntry = pwr_of_2;
        uint32_t        shiftAmt = -1;
        
        while (pEntry->pwr_of_2) {
            if (amt == pEntry->pwr_of_2) {
                shiftAmt = pEntry->shift;
                break;
            }
            ++pEntry;
        }
        
        return shiftAmt;
    }



    // Simple but slow routine to check if a number is prime.
    bool            misc_IsPrime(
        uint64_t        amt
    )
    {
        uint64_t        i;
       
        if (amt < 2)
            return false;
        if (amt == 2)
            return true;
        if ( 0 == (amt & 1))
            return false;
        for (i=3; (i * i) <= amt; i+=2) {
            if ((amt % i) == 0)
                return false;
        }
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                 S e a r c h  B i n a r y
    //---------------------------------------------------------------

    /*    * * *  Search for an Element in an Array    * * *
     * This routine performs a Binary Search on a provided
     * array trying to located a specific entry.  It is as-
     * sumed that the array is in ascending order by key.
     */
    void  *         misc_SearchBinary(
        void            *pKey,
        void            *pArray,
        size_t          Num,
        size_t          Width,
        size_t          Offset,
        int             (*pCmp) (
            void            *,
            void            *
        )
    )
    {
        size_t          High = Num - 1;
        size_t          Low = 0;
        size_t          Mid;
        int             iRc;
        uint8_t         *pWrkPtr;
        size_t          i;

        /* Validate input parameters.
         */
        if ((pKey == NULL) || (pArray == NULL) || (pCmp == NULL))
            return NULL;
        if ((Num <= 0) || (Width <= 0))
            return NULL;

        // If small array, just do a simple search.
        if (Num <= 10) {
            for (i=0; i<Num; i++) {
                pWrkPtr = ((uint8_t *)pArray) + (i * Width) + Offset;
                iRc = (*pCmp)(pKey, (void *)pWrkPtr);
                if (iRc > 0)
                    return NULL;
                else if (iRc == 0)
                    return (void *)(pWrkPtr - Offset);
            }
        }

        /// Search the array using binary search.
        while (Low < High) {
            Mid = (High + Low) / 2;
            pWrkPtr = ((uint8_t *)pArray) + (Mid * Width) + Offset;
            iRc = (*pCmp)(pKey, (void *)pWrkPtr);
            if (iRc < 0)
                High = Mid;
            else if (iRc == 0)
                return (void *)(pWrkPtr - Offset);
            else
                Low = Mid + 1;
        }
        if (High == Low) {
            pWrkPtr = ((uint8_t *)pArray) + (Low * Width) + Offset;
            iRc = (*pCmp)(pKey, (void *)pWrkPtr);
            if (iRc == 0)
                return (void *)(pWrkPtr - Offset);
        }

        /* Return to caller.
         */
        return NULL;
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
    //                    E x c h a n g e  D a t a
    //---------------------------------------------------------------
    
    ERESULT         misc_Exchange(
        void            *pData1,
        void            *pData2,
        uint32_t        size
    )
    {
        uint32_t        *p1b = pData1;
        uint32_t        *p2b = pData2;
        uint32_t        wrk32;
        uint32_t        size32;
        uint8_t         *p1 = pData1;
        uint8_t         *p2 = pData2;
        uint8_t         wrk8;
        
        if ((NULL == pData1) || (NULL == pData2)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        
        size32 = size >> 2;
        if (size32) {
            for (; size32; --size32) {
                wrk32 = *p1b;
                *p1b++ = *p2b;
                *p2b++ = wrk32;
            }
            size -= (size >> 2) << 2;
            p1 = (uint8_t *)p1b;
            p2 = (uint8_t *)p2b;
        }
        
        for (; size; --size) {
            wrk8 = *p1;
            *p1++ = *p2;
            *p2++ = wrk8;
        }
        
        return ERESULT_SUCCESS;
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
        char            *pPatternA,
        const
        char            *pNameA,
        const
        char            *pEquivA,
        char            *pNewnameA
    )
    {
        int             len;
        int             lenName;
        //int             i;
        W32CHR_T        cw;             // Current Input Char
        W32CHR_T        mcw;            // Current Match/Pattern Char
        W32CHR_T        mcwn;
       // W32CHR_T        ncw;
        int             flag = 0;
        bool            fRc;

        // Get the next Pattern Character.
        len = utf8_Utf8ToW32(pPatternA, &mcw);
        if (len == -1) {    // *** Malformed Unicode Char ***
            return false;
        }
        pPatternA += len;

        for (;;) {		/* Corresponding char */
            len = utf8_Utf8ToW32(pNameA, &cw);
            if (len == -1) {    // *** Malformed Unicode Char ***
                return false;
            }
            pNameA += len;
            lenName = len;
            if (cw == '\0') {
                break;
            }
            switch (mcw) {
                    
                case '?':				// '?' matches any single char
                    if (pEquivA) {
                        if (misc_CopyText(&pEquivA, &pNewnameA)) {
                            len = utf8_W32ToUtf8(cw, pNewnameA);
                            pNewnameA += len;
                            len = utf8_Utf8ToW32(pPatternA, &mcwn);
                            if (mcwn != '?') {
                                len = utf8_Utf8ToW32(pEquivA, NULL);
                                pEquivA += len;
                            }
                        }
                    }
                    len = utf8_Utf8ToW32(pPatternA, &mcw);
                    if (len == -1) {    // *** Malformed Unicode Char ***
                        return false;
                    }
                    pPatternA += len;
                    break;
                    
                case '*':				// '*' matches any string
                    flag = 0;
                    if (pEquivA) {
                        if (misc_CopyText(&pEquivA, &pNewnameA))
                            flag = 1;
                    }
                    len = 0;
                    if (flag && pEquivA) {
                        len = utf8_Utf8ToW32(pEquivA, NULL);
                    }
                    fRc = misc_PatternMatchA(
                                    pPatternA,
                                    (pNameA - lenName), // Backup one char
                                    (pEquivA + len),    // Optionally Advance one char
                                    pNewnameA
                             );
                    if ( fRc )
                        return true;
                    if (flag) {
                        len = utf8_W32ToUtf8(cw, pNewnameA);
                        pNewnameA += len;
                    }
                    break;
                    
                default:				/* Anything else matches only itself */
                    if (ascii_toUpperW32(mcw) != ascii_toUpperW32(cw))
                        return false;
                    len = utf8_Utf8ToW32(pPatternA, &mcw);
                    if (len == -1) {    // *** Malformed Unicode Char ***
                        return false;
                    }
                    pPatternA += len;
                    break;
            }
        }
        
        if ((mcw != '*' || *pPatternA) && mcw) {
            return false;
        }
        if (pEquivA) {
            while (misc_CopyText(&pEquivA, &pNewnameA)) {
                len = utf8_Utf8ToW32(pEquivA, NULL);
                pEquivA += len;
            }
            *pNewnameA = '\0';
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

        //fRc = misc_Disable(this);

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

    bool            misc_Enable (
        MISC_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!misc_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(this);

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
        //this->pArray = ObjArray_New( );

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


