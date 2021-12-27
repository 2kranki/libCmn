// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Misc.c
 *  Generated 12/27/2021 08:59:35
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
#include        <Misc_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.

    typedef struct pwr_of_2_w {
        uint32_t        pwr_of_2;
        uint32_t        shift;
        uint32_t        prime;      // prime number > power_of_2
    } PWR_OF_2;

    static
    const
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
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* Copy text until EOL or an '*' is found.
     */
    static
    bool            Misc_CopyText(
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






    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

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


    bool        Misc_AbbrevA(
        const
        char            *pPattern,    // Pattern to match it against;
                                    // lowercase letters are optional
        const
        char            *pText        // Text to test
    )
    {
        while (*pPattern != '\0') {
            if ( ascii_isLowerA(*pPattern) ) {    /* Optional character */
                if ( (ascii_toLowerA(*pText) == *pPattern++)
                    && Misc_AbbrevA((pText + 1), pPattern) ) {
                    return true;
                }
            }
            else {                /* Required character */
                if ( ascii_toUpperA(*pText++) != *pPattern++ ) {
                    return false;
                }
            }
        }

        return (*pText == '\0');
    }



    MISC_DATA *     Misc_Alloc (
        void
    )
    {
        MISC_DATA       *this;
        uint32_t        cbSize = sizeof(MISC_DATA);

        // Do initialization.

         this = obj_Alloc( cbSize );

        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                      B i t  R e v e r s a l
    //---------------------------------------------------------------

    // Knuth's bit reversal algorithm
    // from http://www.hackersdelight.org/revisions.pdf
    uint32_t        Misc_BitReversal32(
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
    uint64_t        Misc_BitReversal64(
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
    //                    E x c h a n g e  D a t a
    //---------------------------------------------------------------

    ERESULT         Misc_Exchange(
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
    //            T e s t  f o r  E v e n  P a r i t y
    //---------------------------------------------------------------

    bool            Misc_IsEvenParity32(
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


    bool            Misc_IsEvenParity16(
        uint16_t        x
    )
    {
        x ^= x >> 8;
        x ^= x >> 4;
        x ^= x >> 2;
        x ^= x >> 1;
        return ((~x) & 1) ? true : false;
    }


    bool            Misc_IsEvenParity8(
        uint8_t         x
    )
    {
        x ^= x >> 4;
        x ^= x >> 2;
        x ^= x >> 1;
        return ((~x) & 1) ? true : false;
    }



    MISC_DATA *     Misc_New (
        void
    )
    {
        MISC_DATA       *this;
        
        this = Misc_Alloc( );
        if (this) {
            this = Misc_Init(this);
        } 
        return this;
    }



    //---------------------------------------------------------------
    //                  P r i m e  N u m b e r
    //---------------------------------------------------------------

    uint32_t        Misc_Pwr2_Prime(
        uint32_t        amt
    )
    {
        uint32_t        prime = 0;

        if (amt < 32)
            prime = pwr_of_2[amt].prime;

        return prime;
    }


    uint32_t        Misc_Pwr2_Shift(
        uint32_t        amt
    )
    {
        const
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
    bool            Misc_IsPrime(
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
    bool            Misc_PatternMatchA(
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

        for (;;) {        /* Corresponding char */
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

                case '?':                // '?' matches any single char
                    if (pEquivA) {
                        if (Misc_CopyText(&pEquivA, &pNewnameA)) {
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

                case '*':                // '*' matches any string
                    flag = 0;
                    if (pEquivA) {
                        if (Misc_CopyText(&pEquivA, &pNewnameA))
                            flag = 1;
                    }
                    len = 0;
                    if (flag && pEquivA) {
                        len = utf8_Utf8ToW32(pEquivA, NULL);
                    }
                    fRc = Misc_PatternMatchA(
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

                default:                /* Anything else matches only itself */
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
            while (Misc_CopyText(&pEquivA, &pNewnameA)) {
                len = utf8_Utf8ToW32(pEquivA, NULL);
                pEquivA += len;
            }
            *pNewnameA = '\0';
        }
        return true;
    }



    int             Misc_RangeCmpI32(
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


    //---------------------------------------------------------------
    //                 S e a r c h  B i n a r y
    //---------------------------------------------------------------

    /*    * * *  Search for an Element in an Array    * * *
     * This routine performs a Binary Search on a provided
     * array trying to located a specific entry.  It is as-
     * sumed that the array is in ascending order by key
     * and that the keys are embedded in the entry.
     */
    void  *         Misc_SearchBinary(
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
//#ifdef TEST_BINARY_ONLY
        if (Num <= 10) {
            for (i=0; i<Num; i++) {
                pWrkPtr = ((uint8_t *)pArray) + (i * Width) + Offset;
                iRc = (*pCmp)(pKey, (void *)pWrkPtr);
                if (iRc < 0)
                    return NULL;
                else if (iRc == 0)
                    return (void *)(pWrkPtr - Offset);
            }
        }
//#endif

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


    void  *         Misc_SearchBinaryStrA(
        void            *pKey,
        void            *pArray,
        size_t          Num,
        size_t          Width,
        size_t          Offset
    )
    {
        size_t          High = Num - 1;
        size_t          Low = 0;
        size_t          Mid;
        int             iRc;
        uint8_t         *pWrkPtr;
        size_t          i;
        char            **ppStrA;

        /* Validate input parameters.
         */
        if ((pKey == NULL) || (pArray == NULL))
            return NULL;
        if ((Num <= 0) || (Width <= 0))
            return NULL;

//#ifdef TEST_BINARY_ONLY
        // If small array, just do a simple search.
        if (Num <= 10) {
            for (i=0; i<Num; i++) {
                pWrkPtr = ((uint8_t *)pArray) + (i * Width) + Offset;
                ppStrA = (void *)pWrkPtr;
                iRc = strcmp(pKey, *ppStrA);
                if (iRc < 0)
                    return NULL;
                else if (iRc == 0)
                    return (void *)(pWrkPtr - Offset);
            }
        }
//#endif

        /// Search the array using binary search.
        while (Low < High) {
            Mid = (High + Low) / 2;
            pWrkPtr = ((uint8_t *)pArray) + (Mid * Width) + Offset;
            ppStrA = (void *)pWrkPtr;
            iRc = strcmp(pKey, *ppStrA);
            if (iRc < 0)
                High = Mid;
            else if (iRc == 0)
                return (void *)(pWrkPtr - Offset);
            else
                Low = Mid + 1;
        }
        if (High == Low) {
            pWrkPtr = ((uint8_t *)pArray) + (Low * Width) + Offset;
            ppStrA = (void *)pWrkPtr;
            iRc = strcmp(pKey, *ppStrA);
            if (iRc == 0)
                return (void *)(pWrkPtr - Offset);
        }

        /* Return to caller.
         */
        return NULL;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          L o g
    //---------------------------------------------------------------

#ifdef   MISC_LOG
    bool            Misc_setLog (
        MISC_DATA   *this,
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pLog = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Misc_getPriority (
        MISC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Misc_setPriority (
        MISC_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
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
    
    uint32_t        Misc_getSize (
        MISC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Misc_getStr (
        MISC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Misc_setStr (
        MISC_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
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
    
    MISC_DATA *  Misc_getSuper (
        MISC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (MISC_DATA *)this;
    }

    OBJ_IUNKNOWN *  Misc_getSuperVtbl (
        MISC_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
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
        ERESULT eRc = Misc_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another MISC object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Misc_Assign (
        MISC_DATA       *this,
        MISC_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Misc_Validate(pOther)) {
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
    int             Misc_Compare (
        MISC_DATA     *this,
        MISC_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  MISC_SINGLETON
        if (OBJ_NIL == this) {
            this = Misc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Misc_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Misc      *pCopy = Misc_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MISC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MISC_DATA *     Misc_Copy (
        MISC_DATA       *this
    )
    {
        MISC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef MISC_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Misc_New( );
        if (pOther) {
            eRc = Misc_Assign(this, pOther);
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

    void            Misc_Dealloc (
        OBJ_ID          objId
    )
    {
        MISC_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MISC_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Misc_setStr(this, OBJ_NIL);

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
        Misc      *pDeepCopy = Misc_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MISC object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MISC_DATA *     Misc_DeepCopy (
        MISC_DATA       *this
    )
    {
        MISC_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Misc_New( );
        if (pOther) {
            eRc = Misc_Assign(this, pOther);
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
    ERESULT         Misc_Disable (
        MISC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  MISC_SINGLETON
        if (OBJ_NIL == this) {
            this = Misc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
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
    ERESULT         Misc_Enable (
        MISC_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  MISC_SINGLETON
        if (OBJ_NIL == this) {
            this = Misc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   MISC_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
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

    MISC_DATA *   Misc_Init (
        MISC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MISC_DATA);
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

        //this = (OBJ_ID)Misc_Init((MISC_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Misc_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MISC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Misc_Vtbl);
#ifdef  MISC_JSON_SUPPORT
        JsonIn_RegisterClass(Misc_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Misc::sizeof(MISC_DATA) = %lu\n", 
                sizeof(MISC_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MISC_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Misc_IsEnabled (
        MISC_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  MISC_SINGLETON
        if (OBJ_NIL == this) {
            this = Misc_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
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
        void        *pMethod = Misc_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Misc", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Misc_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MISC_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Misc_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(MISC_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Misc_Class();
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
                            return Misc_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Misc_Enable;
                        }
                        break;

                    case 'P':
#ifdef  MISC_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Misc_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Misc_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Misc_ToDebugString;
                        }
#ifdef  MISC_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Misc_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Misc_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Misc_ToDebugString)
                    return "ToDebugString";
#ifdef  MISC_JSON_SUPPORT
                if (pData == Misc_ToJson)
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
        ASTR_DATA      *pDesc = Misc_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Misc_ToDebugString (
        MISC_DATA      *this,
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
        if (!Misc_Validate(this)) {
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
                    Misc_getSize(this),
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
    bool            Misc_Validate (
        MISC_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MISC))
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


        if (!(obj_getSize(this) >= sizeof(MISC_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


