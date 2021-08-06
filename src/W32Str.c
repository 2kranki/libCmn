// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   W32Str.c
 *  Generated 07/15/2021 16:05:13
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
#include        <W32Str_internal.h>
#include        <ascii.h>
#include        <str.h>
#include        <crc.h>
#include        <dec.h>
#include        <hex.h>
#include        <JsonIn.h>
//#include        <Node.h>
//#include        <NodeHash.h>
#include        <time.h>
#include        <trace.h>
#include        <utf8.h>
#include        <W32Array.h>
#include        <stdio.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            W32Str_task_body (
        void            *pData
    )
    {
        //W32STR_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    W32STR_DATA *     W32Str_Alloc (
        void
    )
    {
        W32STR_DATA       *this;
        uint32_t        cbSize = sizeof(W32STR_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    // Return offset of chr in string (relative to 1)
    // Returns 0 if not found.
    uint32_t        W32Str_ChrInStr(
        W32CHR_T        chr,
        const
        W32CHR_T        *pStr
    )
    {
        uint32_t        index = 1;

        while (*pStr) {
            if (*pStr == chr) {
                return index;
            }
            ++pStr;
            ++index;
        }

        return 0;
    }



    int             W32Str_Cmp(
        const
        W32CHR_T        *pStr1,
        const
        W32CHR_T        *pStr2
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int             i = 0;

        for( ;; ) {
            if( *pStr1 )
                ;
            else {
                if( *pStr2 )
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if( *pStr2 )
                ;
            else {
                if( *pStr1 )
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = *pStr1 - *pStr2;
            if( i ) {
                break;
            }
            ++pStr1;
            ++pStr2;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }


    int             W32Str_CmpA(
        const
        W32CHR_T        *pStr,
        const
        char            *pStrA
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        uint32_t        str1len;
        uint32_t        str2len;
        W32CHR_T        chr2;
        int             i = -1;

        // Do initialization.
        str1len = W32Str_StrLen(pStr);
        if (NULL == pStrA) {
            str2len = 0;
        }
        else {
            str2len = (uint32_t)utf8_StrLenA(pStrA);
        }

        if ((0 == str1len) && (0 == str2len)) {
            return 0;
        }

        for ( ;; ) {
            chr2 = utf8_Utf8ToW32_Scan(&pStrA);
            if (*pStr)
                ;
            else {
                if (chr2)
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if (chr2)
                ;
            else {
                if (*pStr)
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = *pStr - chr2;
            if (i) {
                break;
            }
            ++pStr;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }


    int             W32Str_CmpAN(
        const
        W32CHR_T        *pStr,
        const
        char            *pStrA,
        uint32_t        n
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        uint32_t        str1len;
        uint32_t        str2len;
        W32CHR_T        chr2;
        int             i = -1;

        // Do initialization.
        str1len = W32Str_StrLen(pStr);
        if (NULL == pStrA) {
            str2len = 0;
        }
        else {
            str2len = (uint32_t)utf8_StrLenA(pStrA);
        }

        if ((0 == str1len) && (0 == str2len)) {
            return 0;
        }

        while ( n-- ) {
            chr2 = utf8_Utf8ToW32_Scan(&pStrA);
            if (*pStr)
                ;
            else {
                if (chr2)
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if (chr2)
                ;
            else {
                if (*pStr)
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = *pStr - chr2;
            if (i) {
                break;
            }
            ++pStr;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }


    int             W32Str_CmpN(
        const
        W32CHR_T        *pStr1,
        const
        W32CHR_T        *pStr2,
        uint32_t        n
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int             i = 0;

        while (n--) {
            if( *pStr1 )
                ;
            else {
                if( *pStr2 )
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if( *pStr2 )
                ;
            else {
                if( *pStr1 )
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = *pStr1 - *pStr2;
            if( i ) {
                break;
            }
            ++pStr1;
            ++pStr2;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }



    uint32_t        W32Str_StrLen(
        const
        W32CHR_T        *pData
    )
    {
        uint32_t        len = 0;

        while (*pData++) {
            ++len;
        }

        return len;
    }



    W32STR_DATA *     W32Str_New (
        void
    )
    {
        W32STR_DATA       *this;
        
        this = W32Str_Alloc( );
        if (this) {
            this = W32Str_Init(this);
        } 
        return this;
    }



    W32STR_DATA *     W32Str_NewA(
        const
        char            *pStrA
    )
    {
        W32STR_DATA       *this;
        ERESULT         eRc;
        int32_t         len;

        // Do initialization.
        if (NULL == pStrA) {
            return OBJ_NIL;
        }

        this = W32Str_Alloc( );
        this = W32Str_Init(this);
        if (this) {
            len = utf8_StrLenA(pStrA);
            if (len) {
                eRc = W32Str_AppendA(this, pStrA);
                if (ERESULT_HAS_FAILED(eRc)) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }

        // Return to caller.
        return this;
    }



    W32STR_DATA *     W32Str_NewW32(
        uint32_t        len,
        const
        W32CHR_T        *pStr
    )
    {
        W32STR_DATA       *this;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == pStr) {
            return OBJ_NIL;
        }

        this = W32Str_Alloc( );
        this = W32Str_Init(this);
        if (this) {
            eRc = W32Str_AppendW32(this, len, pStr);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        // Return to caller.
        return this;
    }



    W32STR_DATA *     W32Str_NewFromEnv(
        const
        char            *pStrA
    )
    {
        W32STR_DATA       *this =  OBJ_NIL;
        char            *pData;
        size_t          len;

        // Do initialization.
        if (NULL == pStrA) {
            return this;
        }

        pData = getenv(pStrA);
        if (NULL == pData)
            ;
        else {
            len = strlen(pData);
            if (len) {
                this = W32Str_NewA(pData);
            }
        }

        // Return to caller.
        return this;
    }



    W32STR_DATA *     W32Str_NewFromUtf8File(
        PATH_DATA       *pPath
    )
    {
        W32STR_DATA       *this =  OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == pPath) {
            return this;
        }

        this = W32Str_New( );
        if (this) {
            eRc = W32Str_AppendUtf8File(this, pPath);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        // Return to caller.
        return this;
    }



    W32STR_DATA *     W32Str_NewFromTimeNow(
    )
    {
        W32STR_DATA       *this =  OBJ_NIL;
        time_t            startTime;
        char            timeStr[20];


        // Do initialization.
        startTime = time(NULL);
        strftime( timeStr, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime) );

        this = W32Str_NewA(timeStr);

        // Return to caller.
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  C r c  I E E E
    //---------------------------------------------------------------

    uint32_t        W32Str_getCrcIEEE(
        W32STR_DATA       *this
    )
    {
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
        uint32_t        len;
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        pCrc = crc_New(CRC_TYPE_IEEE_32);
        len = array_getSize((ARRAY_DATA *)this);
        crc =   crc_AccumBlock(
                    pCrc,
                    (len * sizeof(int32_t)),
                    (void *)array_Ptr((ARRAY_DATA *)this, 1)
                 );
        obj_Release(pCrc);
        pCrc = OBJ_NIL;

        return  crc;
    }



    //---------------------------------------------------------------
    //                        D a t a
    //---------------------------------------------------------------

    const
    W32CHR_T *      W32Str_getData(
        W32STR_DATA       *this
    )
    {
        W32CHR_T        *pData;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        pData = array_Ptr((ARRAY_DATA *)this, 1);

        return pData;
    }



    //---------------------------------------------------------------
    //                        L e n g t h
    //---------------------------------------------------------------

    uint32_t        W32Str_getLength(
        W32STR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return array_getSize((ARRAY_DATA *)this) - 1;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        W32Str_getPriority (
        W32STR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            W32Str_setPriority (
        W32STR_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
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
    
    uint32_t        W32Str_getSize (
        W32STR_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize((ARRAY_DATA *)this) - 1;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  W32Str_getSuperVtbl (
        W32STR_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
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
    //                       A p p e n d
    //---------------------------------------------------------------

    ERESULT         W32Str_Append(
        W32STR_DATA        *this,
        W32STR_DATA       *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        len = array_getSize((ARRAY_DATA *)this);
        uint32_t        len2add = array_getSize((ARRAY_DATA *)pOther);

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif

        if (len2add > 1) {
            eRc =   array_InsertData(
                                (ARRAY_DATA *)this,
                                len,
                                (len2add - 1),
                                array_getData((ARRAY_DATA *)pOther)
                    );
            if (ERESULT_IS_SUCCESSFUL(eRc)) {
                array_AdjustSize((ARRAY_DATA *)this, -1);
            }
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         W32Str_AppendA(
        W32STR_DATA        *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc;
        W32CHR_T        chr;
        uint32_t        i;
        uint32_t        len;
        uint32_t        index;
        W32CHR_T        *pInsert;


        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif

        len = (uint32_t)utf8_StrLenA(pStrA);
        if (0 == len) {
            return ERESULT_DATA_NOT_FOUND;
        }

        index = array_getSize((ARRAY_DATA *)this);
        eRc =   array_InsertSpacing(
                    (ARRAY_DATA *)this,
                    index,
                    len
                );

        // Copy the data converting UTF-8 to UTF-32.
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pInsert = array_Ptr((ARRAY_DATA *)this, index);
            for (i=0; i<len; ++i) {
                chr = utf8_Utf8ToW32_Scan(&pStrA);
                *pInsert++ = chr;
            }
            *pInsert = '\0';
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         W32Str_AppendStrA(
        W32STR_DATA        *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;
        W32CHR_T        chr;
        uint32_t        i;
        uint32_t        len;
        uint32_t        index;
        W32CHR_T        *pInsert;
        const
        char            *pText;


        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif

        len = AStr_getLength(pStr);
        if (0 == len) {
            return ERESULT_DATA_NOT_FOUND;
        }
        pText = AStr_getData(pStr);

        index = array_getSize((ARRAY_DATA *)this);
        eRc =   array_InsertSpacing((ARRAY_DATA *)this, index, len);

        // Copy the data.
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pInsert = array_Ptr((ARRAY_DATA *)this, index);
            for (i=0; i<len; ++i) {
                chr = AStr_CharGetW32(pStr, (i+1));
                *pInsert++ = chr;
            }
            *pInsert = '\0';
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    ERESULT         W32Str_AppendW32(
        W32STR_DATA     *this,
        uint32_t        len,
        const
        W32CHR_T        *pStr
    )
    {
        ERESULT         eRc = ERESULT_DATA_MISSING;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (0 == len) {
            len = W32Str_StrLen(pStr);
        }
        if (len) {
            eRc =   array_InsertData(
                            (ARRAY_DATA *)this,
                            array_getSize((ARRAY_DATA *)this),
                            len,
                            (void *)pStr
                    );
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       A p p e n d  C h a r
    //---------------------------------------------------------------

    ERESULT         W32Str_AppendCharW32(
        W32STR_DATA     *this,
        uint32_t        len,
        const
        W32CHR_T        chr
    )
    {
        W32CHR_T        *pData;
        uint32_t        offset;
        uint32_t        i;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        if (0 == len) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        offset = array_getSize((ARRAY_DATA *)this);
        eRc =   array_InsertSpacing(
                        (ARRAY_DATA *)this,
                        offset,
                        len
                );
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pData = array_Ptr( (ARRAY_DATA *)this, offset);
            for (i=0; i<len; ++i) {
                *pData++ = chr;
            };
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                    A p p e n d  F i l e
    //---------------------------------------------------------------

    ERESULT         W32Str_AppendUtf8File(
        W32STR_DATA     *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        W32CHR_T        chr;
        FILE            *pFile;

        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pFile = fopen(Path_getData(pPath), "r");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( (chr = fgetwc(pFile)) != EOF ) {
            eRc = W32Str_AppendCharW32(this, 1, chr);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                return eRc;
            }
        }
        fclose(pFile);
        pFile = NULL;

        return eRc;
    }



    //---------------------------------------------------------------
    //                    A p p e n d  P r i n t
    //---------------------------------------------------------------

    ERESULT         W32Str_AppendPrintA(
        W32STR_DATA     *this,
        const
        char            *pFormat,
        ...
    )
    {
        ERESULT         eRc;
        int             size;
        va_list         arg_ptr;
        char            *pStr = NULL;

        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        va_start( arg_ptr, pFormat );
        size = vsnprintf( NULL, 0, pFormat, arg_ptr );
        va_end( arg_ptr );
        ++size;
        pStr = (char *)mem_Malloc( size );
        if( pStr == NULL ) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        va_start( arg_ptr, pFormat );
        size = vsnprintf( pStr, size, pFormat, arg_ptr );
        va_end( arg_ptr );
        eRc = W32Str_AppendA(this, pStr);
        mem_Free( pStr );
        pStr = NULL;

        return eRc;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = W32Str_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another W32STR object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         W32Str_Assign (
        W32STR_DATA     *this,
        W32STR_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!W32Str_Validate(pOther)) {
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

        eRc = array_Assign((ARRAY_DATA *)this, (ARRAY_DATA *)pOther);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }

        // Copy other data from this object to other.
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //               C h a r  F i n d  N e x t
    //---------------------------------------------------------------

    ERESULT         W32Str_CharFindNextW32(
        W32STR_DATA     *this,
        uint32_t        *pIndex,
        const
        W32CHR_T        chr
    )
    {
        uint32_t        i;
        uint32_t        index;
        uint32_t        lenStr;
        W32CHR_T        *pChr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        lenStr = W32Str_getLength(this);

        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }

        pChr = array_Ptr((ARRAY_DATA *)this, index);
        for ( i=index; i<(lenStr+1); ++i,++pChr ) {
            if (chr == *pChr) {
                *pIndex = i;
                return ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }


    ERESULT         W32Str_CharsFindNextW32(
        W32STR_DATA     *this,
        uint32_t        *pIndex,
        const
        W32CHR_T        *pChrs
    )
    {
        uint32_t        i;
        uint32_t        index;
        uint32_t        lenStr;
        W32CHR_T        *pChr;
        const
        W32CHR_T        *pNext;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        lenStr = W32Str_getLength(this);

        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }

        pChr = array_Ptr((ARRAY_DATA *)this, index);
        for ( i=index; i<(lenStr+1); ++i,++pChr ) {
            pNext = pChrs;
            while (*pNext) {
                if (*pNext++ == *pChr) {
                    *pIndex = i;
                    return ERESULT_SUCCESS;
                }
            }
        }

        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }



    //---------------------------------------------------------------
    //               C h a r  F i n d  P r e v
    //---------------------------------------------------------------

    ERESULT         W32Str_CharFindPrevW32(
        W32STR_DATA     *cbp,
        uint32_t        *pIndex,
        const
        W32CHR_T        chr
    )
    {
        uint32_t        i;
        uint32_t        index;
        W32CHR_T        *pChr;
        uint32_t        lenStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        lenStr = W32Str_getLength(cbp);

        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
        index = *pIndex;
        if (0 == index) {
            index = lenStr;
        }
        if (index > lenStr) {
            return ERESULT_OUT_OF_RANGE;
        }

        pChr = array_Ptr((ARRAY_DATA *)cbp, index);
        for ( i=index; i; --i,--pChr ) {
            if (chr == *pChr) {
                *pIndex = i;
                return ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }



    //---------------------------------------------------------------
    //                       C h a r  G e t
    //---------------------------------------------------------------

    W32CHR_T        W32Str_CharGetW32(
        W32STR_DATA     *cbp,
        uint32_t        offset
    )
    {
        W32CHR_T        *pSrc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return -1;
        }
#endif
        if ((0 == offset)
            || (offset > (array_getSize((ARRAY_DATA *)cbp))-1)) {
            return -1;
        }

        pSrc = array_Ptr((ARRAY_DATA *)cbp, offset);

        // Return to caller.
        return *pSrc;
    }



    //---------------------------------------------------------------
    //                       C h a r  P u t
    //---------------------------------------------------------------

    ERESULT         W32Str_CharPutW32(
        W32STR_DATA     *cbp,
        uint32_t        offset,
        const
        W32CHR_T        chr
    )
    {
        uint32_t        lenStr;
        W32CHR_T        *pChr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        lenStr = W32Str_getLength(cbp);

        if ((0 == offset) || (offset > array_getSize((ARRAY_DATA *)cbp))) {
            return ERESULT_INVALID_PARAMETER;
        }

        pChr = array_Ptr((ARRAY_DATA *)cbp, offset);
        *pChr = chr;

        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //               C h a r  R e p l a c e  A l l
    //---------------------------------------------------------------

    ERESULT         W32Str_CharReplaceAllW32(
        W32STR_DATA     *cbp,
        const
        W32CHR_T        chrSrch,
        const
        W32CHR_T        chrRepl
    )
    {
        uint32_t        i;
        W32CHR_T        *pChr;
        uint32_t        lenStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(cbp);

        pChr = array_Ptr((ARRAY_DATA *)cbp, 1);
        for ( i=0; i<lenStr; ++i,++pChr ) {
            if (*pChr == chrSrch) {
                *pChr = chrRepl;
            }
        }

        // Return to caller.
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
    int             W32Str_Compare (
        W32STR_DATA     *this,
        W32STR_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!W32Str_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc =   W32Str_Cmp(
                         W32Str_getData(this),
                         W32Str_getData(pOther)
                );
     
        return iRc;
    }
    
   
    int             W32Str_CompareA(
        W32STR_DATA     *this,
        const
        char            *pString
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        uint32_t        str1len;
        const
        W32CHR_T        *pStr1;
        uint32_t        str2len;
        W32CHR_T        chr2;
        int             i = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
#endif

        str1len = W32Str_getLength(this);
        pStr1 = array_Ptr((ARRAY_DATA *)this, 1);
        if (NULL == pString) {
            str2len = 0;
        }
        else {
            str2len = (uint32_t)utf8_StrLenA(pString);
        }

        if ((0 == str1len) && (0 == str2len)) {
            return 0;
        }

        for( ;; ) {
            chr2 = utf8_Utf8ToW32_Scan(&pString);
            if( *pStr1 )
                ;
            else {
                if( chr2 )
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if( chr2 )
                ;
            else {
                if( *pStr1 )
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = *pStr1 - chr2;
            if( i ) {
                break;
            }
            ++pStr1;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }


    int             W32Str_CompareA_IC(
        W32STR_DATA     *this,
        const
        char            *pString
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        uint32_t        str1len;
        const
        W32CHR_T        *pStr1;
        uint32_t        str2len;
        W32CHR_T        chr2;
        int             i = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
#endif

        str1len = W32Str_getLength(this);
        pStr1 = array_Ptr((ARRAY_DATA *)this, 1);
        if (NULL == pString) {
            str2len = 0;
        }
        else {
            str2len = (uint32_t)utf8_StrLenA(pString);
        }

        if ((0 == str1len) && (0 == str2len)) {
            return 0;
        }

        for( ;; ) {
            chr2 = utf8_Utf8ToW32_Scan(&pString);
            if( *pStr1 )
                ;
            else {
                if( chr2 )
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if( chr2 )
                ;
            else {
                if( *pStr1 )
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = ascii_toUpperW32(*pStr1) - ascii_toUpperW32(chr2);
            if( i ) {
                break;
            }
            ++pStr1;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }


    int             W32Str_CompareA_N(
        W32STR_DATA     *this,
        const
        char            *pString,
        uint32_t        n
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        uint32_t        str1len;
        const
        W32CHR_T        *pStr1;
        uint32_t        str2len;
        W32CHR_T        chr2;
        int             i = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
#endif

        str1len = W32Str_getLength(this);
        pStr1 = array_Ptr((ARRAY_DATA *)this, 1);
        if (NULL == pString) {
            str2len = 0;
        }
        else {
            str2len = (uint32_t)utf8_StrLenA(pString);
        }

        if ((0 == str1len) && (0 == str2len)) {
            return 0;
        }

        while ( n-- ) {
            chr2 = utf8_Utf8ToW32_Scan(&pString);
            if (*pStr1)
                ;
            else {
                if (chr2)
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if (chr2)
                ;
            else {
                if (*pStr1)
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            i = *pStr1 - chr2;
            if (i) {
                break;
            }
            ++pStr1;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }


    int             W32Str_CompareW32(
        W32STR_DATA        *this,
        const
        W32CHR_T        *pString,
        bool            fIgnoreCase,
        bool            fIgnoreWS
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        uint32_t        str1len;
        const
        W32CHR_T        *pStr1;
        uint32_t        str2len;
        const
        W32CHR_T        *pStr2;
        int             i = -1;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
#endif

        str1len = W32Str_getLength(this);
        pStr1 = array_Ptr((ARRAY_DATA *)this, 1);
        if (NULL == pString) {
            str2len = 0;
            pStr2 = NULL;
        }
        else {
            str2len = (uint32_t)W32Str_StrLen(pString);
            pStr2 = pString;
        }

        if ((0 == str1len) && (0 == str2len)) {
            return 0;
        }

        for( ;; ) {
            if( *pStr1 )
                ;
            else {
                if( *pStr2 )
                    //eRc = ERESULT_SUCCESS_LESS_THAN;
                    i = -1;
                break;
            }
            if( *pStr2 )
                ;
            else {
                if( *pStr1 )
                    //eRc = ERESULT_SUCCESS_GREATER_THAN;
                    i = 1;
                break;
            }
            if (fIgnoreCase && ascii_isAlphaW32(*pStr1) && ascii_isAlphaW32(*pStr2))
                i = ascii_toLowerW32(*pStr1) - ascii_toLowerW32(*pStr2);
            else if (fIgnoreWS
                  && (ascii_isWhiteSpaceW32(*pStr1) || ascii_isWhiteSpaceW32(*pStr2))) {
                while (ascii_isWhiteSpaceW32(*pStr1)) {
                    pStr1++;
                }
                while (ascii_isWhiteSpaceW32(*pStr2)) {
                    pStr2++;
                }
                continue;
            } else
                i = *pStr1 - *pStr2;
            if( i ) {
                break;
            }
            pStr1++;
            pStr2++;
        }
        if (i < 0)
            i = -1;
        else if (i > 0)
            i = 1;

        // Return to caller.
        return i;
    }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        W32Str      *pCopy = W32Str_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a W32STR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32STR_DATA *     W32Str_Copy (
        W32STR_DATA       *this
    )
    {
        W32STR_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef W32STR_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = W32Str_New( );
        if (pOther) {
            eRc = W32Str_Assign(this, pOther);
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
    //                       C S t r i n g A
    //---------------------------------------------------------------

    char *          W32Str_CStringA(
        W32STR_DATA     *this,
        uint32_t        *pLen       // Optional returned string length
                                    // less terminating NUL
    )
    {
        char            *pszStr;
        uint32_t        lenStr;
        uint32_t        lenA = 0;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        lenStr = W32Str_getLength(this);

        lenA =  utf8_W32StrToUtf8Str(
                            lenStr,
                            array_Ptr((ARRAY_DATA *)this, 1),
                            0,
                            NULL
                );
        pszStr = (char *)mem_Malloc(lenA);
        if (pszStr) {
            i =     utf8_W32StrToUtf8Str(
                                     lenStr,
                                     array_Ptr((ARRAY_DATA *)this, 1),
                                     lenA,
                                     pszStr
                                     );
            if (i<lenA) {
            }
            else {
                mem_Free(pszStr);
                return NULL;
            }
        }

        // Return to caller.
        if (pLen) {
            *pLen = lenA - 1;
        }
        return pszStr;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            W32Str_Dealloc (
        OBJ_ID          objId
    )
    {
        W32STR_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((W32STR_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //W32Str_setStr(this, OBJ_NIL);

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
        W32Str      *pDeepCopy = W32Str_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a W32STR object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32STR_DATA *   W32Str_DeepCopy (
        W32STR_DATA     *this
    )
    {
        W32STR_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = W32Str_New( );
        if (pOther) {
            eRc = W32Str_Append(pOther, this);
            if (ERESULT_FAILED(eRc)) {
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
    ERESULT         W32Str_Disable (
        W32STR_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
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
    ERESULT         W32Str_Enable (
        W32STR_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
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
    //                     E s c a p e  F o r  C
    //---------------------------------------------------------------

    ERESULT         W32Str_EscapeForC(
        W32STR_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        W32CHR_T        chrEscape = '\\';
        W32CHR_T        *pData;
        uint32_t        lenStr;
        uint32_t        i;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);

        // The order matters in how we do these replacements.

        for (i=1; i<=W32Str_getLength(this); ++i) {
            pData = (W32CHR_T *)array_Ptr((ARRAY_DATA *)this, i);
            if (pData) {
                if (*pData == chrEscape) {
                    array_InsertData((ARRAY_DATA *)this, i, 1, &chrEscape);
                    i += 1;
                }
            }
        }

        for (i=1; i<=W32Str_getLength(this); ++i) {
            pData = (W32CHR_T *)array_Ptr((ARRAY_DATA *)this, i);
            if (pData) {
                if (*pData == '"') {
                    array_InsertData((ARRAY_DATA *)this, i, 1, &chrEscape);
                    i += 1;
                }
                else if (*pData == '\n') {
                    *pData = 'n';
                    array_InsertData((ARRAY_DATA *)this, i, 1, &chrEscape);
                    i += 1;
                }
                else if (*pData == '\r') {
                    *pData = 'r';
                    array_InsertData((ARRAY_DATA *)this, i, 1, &chrEscape);
                    i += 1;
                }
                else if (*pData == '\t') {
                    *pData = 't';
                    array_InsertData((ARRAY_DATA *)this, i, 1, &chrEscape);
                    i += 1;
                }
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                  E x p a n d  V a r i a b l e s
    //---------------------------------------------------------------

    /*!
     Substitute hash values or environment variables into the current string
     using a BASH-like syntax with the hash value having the highest priority.
     Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @param     pHash   optional node hash pointer where the node's data is a
     path or astr kind object.
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         W32Str_ExpandVars(
        W32STR_DATA     *this,
        OBJ_ID          pHash
    )
    {
        ERESULT         eRc;
        uint32_t        i = 0;
        uint32_t        j;
        uint32_t        len;
        bool            fMore = true;
        //PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        const
        char            *pEnvVar = NULL;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJ_ID          pData;
        W32CHR_T        *pChr;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pHash) {
            if(obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH))
                ;
            else {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
        } else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (pHash)
            return ERESULT_NOT_IMPLEMENTED;


        if (0 == W32Str_getLength(this)) {
            return ERESULT_SUCCESS;
        }
        pChr = array_Ptr((ARRAY_DATA *)this, 1);

        // Expand Environment variables.
        while (fMore) {
            fMore = false;
            eRc = W32Str_CharFindNextW32(this, &i, '$');
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            else {
                chr = W32Str_CharGetW32(this, i+1);
                if (chr == '{') {
                    i += 2;
                    j = i;
                    eRc = W32Str_CharFindNextW32(this, &j, '}');
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_PARSE_ERROR;
                    }
                    len = j - i;
                    //FIXME: eRc = W32Str_Mid(this, i, len, &pName);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    if (pHash) {
                        pNode = NodeHash_FindA(pHash, 0, AStr_getData(pName));
                        if (pNode) {
                            pData = Node_getData(pNode);
                            if (obj_IsKindOf(this, OBJ_IDENT_ASTR)
                                || obj_IsKindOf(this, OBJ_IDENT_PATH)) {
                                pEnvVar = AStr_getData((ASTR_DATA *)pData);
                            }
                            else if (obj_IsKindOf(this, OBJ_IDENT_ASTRC)) {
                                pEnvVar = AStrC_getData((ASTRC_DATA *)pData);
                            }
                            if (pNode && pEnvVar) {
                                goto expandIt;
                            }
                            // We did not find it in the Hash. So, fall
                            // through to normal environment variables
                            // search.
                        }
                    }
                    pEnvVar = getenv(AStr_getData(pName));
                    if (NULL == pEnvVar) {
                        obj_Release(pName);
                        return ERESULT_DATA_NOT_FOUND;
                    }
                expandIt:
                    obj_Release(pName);
                    pName = OBJ_NIL;
                    eRc = W32Str_Remove(this, i-2, len+3);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    eRc = W32Str_InsertA(this, i-2, pEnvVar);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    pEnvVar = NULL;
                    fMore = true;
                }
                // Not certain that we need this.
                else if (chr == '$') {
                    eRc = W32Str_Remove(this, i, 1);
                    ++i;
                    fMore = true;
                    continue;
                }
                else {
                    ++i;
                    fMore = true;
                    continue;
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      F i n d  N e x t
    //---------------------------------------------------------------

    ERESULT         W32Str_FindNextA(
        W32STR_DATA     *this,
        const
        char            *pStrA,             // UTF-8 String
        uint32_t        *pIndex
    )
    {
        uint32_t        i;
        uint32_t        index;
        uint32_t        lenStr;
        uint32_t        lenSrchStr;
        W32CHR_T        *pChr;
        W32CHR_T        chr;
        int             iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pStrA) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        iRc = utf8_Utf8ToW32(pStrA, &chr);
        if (iRc <= 0) {
            return ERESULT_INVALID_DATA;
        }
        lenSrchStr = utf8_StrLenA(pStrA);
        if (lenSrchStr == 0) {
            return ERESULT_INVALID_DATA;
        }
        lenStr = W32Str_getLength(this);

        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }

        pChr = array_Ptr((ARRAY_DATA *)this, index);
        for ( i=index; i<=(lenStr - lenSrchStr + 1); ++i,++pChr ) {
            if (*pChr == chr) {
                if (0 == str_CompareNW32A(pChr, pStrA, lenSrchStr)) {
                    *pIndex = i;
                    return ERESULT_SUCCESS;
                }
            }
        }

        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }


    ERESULT         W32Str_FindNextW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        *pStrW32,
        uint32_t        *pIndex
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        index;
        uint32_t        lenStr;
        uint32_t        lenSrchStr;
        W32CHR_T        *pChr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pStrW32) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        lenStr = W32Str_getLength(this);
        lenSrchStr = utf8_StrLenW32(pStrW32);
        if (lenSrchStr == 0) {
            return ERESULT_INVALID_DATA;
        }

        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }

        pChr = array_Ptr((ARRAY_DATA *)this, index);
        iMax = lenStr - lenSrchStr + 1;
        for ( i=index; i<=iMax; ++i,++pChr ) {
            if (*pChr == *pStrW32) {
                if (0 == str_CompareNW32(pChr, pStrW32, lenSrchStr)) {
                    *pIndex = i;
                    return ERESULT_SUCCESS;
                }
            }
        }

        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }


    //---------------------------------------------------------------
    //                       G e t  C h a r
    //---------------------------------------------------------------

    W32CHR_T        W32Str_GetCharW32(
        W32STR_DATA        *cbp,
        uint32_t        offset
    )
    {
        uint32_t        lenStr;
        W32CHR_T        chr = -1;
        W32CHR_T        *pChr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = W32Str_getLength(cbp);

        if( (0 == offset) || (offset > lenStr) ) {
            return EOF;
        }

        pChr = array_Ptr((ARRAY_DATA *)cbp, offset);
        if (pChr) {
            chr = *pChr;
        }

        // Return to caller.
        return chr;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------

    uint32_t        W32Str_Hash(
        W32STR_DATA       *this
    )
    {
        uint32_t        hash = 0;
        W32CHR_T        *pStr = NULL;

#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        pStr = array_Ptr((ARRAY_DATA *)this, 1);
        if (pStr) {
            hash = str_HashW32(pStr, NULL);
        }

        return hash;
    }


    //---------------------------------------------------------------
    //                      I n d e x  U n t i l
    //---------------------------------------------------------------

    ERESULT         W32Str_IndexUntil(
        W32STR_DATA        *this,
        const
        W32CHR_T        *pSetStr,
        uint32_t        *pIndex
    )
    {
        uint32_t        i;
        uint32_t        index;
        uint32_t        lenStr;
        W32CHR_T        *pChr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pSetStr) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        lenStr = W32Str_getLength(this);

        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }

        pChr = array_Ptr((ARRAY_DATA *)this, index);
        for ( i=index; i<lenStr; ++i,++pChr ) {
            if (W32Str_ChrInStr(*pChr, pSetStr)) {
                *pIndex = i;
                return ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    W32STR_DATA *   W32Str_Init (
        W32STR_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(W32STR_DATA);
        ERESULT         eRc;
        W32CHR_T        eod = 0;

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

        this = (OBJ_ID)array_Init((ARRAY_DATA *)this);          // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of W32Str_object.c
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_W32STR);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&W32Str_Vtbl);
#ifdef  W32STR_JSON_SUPPORT
        JsonIn_RegisterClass(W32Str_Class());
#endif
        
        array_setElemSize((ARRAY_DATA *)this, sizeof(W32CHR_T));
        array_setZeroNew((ARRAY_DATA *)this, false);

        // Set up the End-Of-Data marker (ie '\0')
        eRc = array_AppendData((ARRAY_DATA *)this, 1, &eod);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "W32Str::sizeof(W32STR_DATA) = %lu\n", 
                sizeof(W32STR_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(W32STR_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I n s e r t
    //---------------------------------------------------------------

    ERESULT         W32Str_InsertA(
        W32STR_DATA        *cbp,
        uint32_t        offset,
        const
        char            *pStr
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        len;
        W32CHR_T        *pInsert;
        W32CHR_T        chr;
        uint32_t        lenStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(cbp);

        if( (0 == offset) || (offset > (lenStr + 1)) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }

        len = (uint32_t)utf8_StrLenA(pStr);
        if (0 == len) {
            return ERESULT_DATA_NOT_FOUND;
        }

        eRc =   array_InsertSpacing(
                        (ARRAY_DATA *)cbp,
                        offset,
                        len
                );

        // Copy the data.
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pInsert = array_Ptr((ARRAY_DATA *)cbp, offset);
            for (i=0; i<len; ++i) {
                chr = utf8_Utf8ToW32_Scan(&pStr);
                *pInsert++ = chr;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT         W32Str_InsertW32(
        W32STR_DATA        *cbp,
        uint32_t        offset,
        const
        W32CHR_T        *pStr
    )
    {
        uint32_t        len;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        if( (0 == offset) || (offset > W32Str_getLength(cbp)) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        len = W32Str_StrLen(pStr);

        eRc = array_InsertData((ARRAY_DATA *)cbp, offset, len, (void *)pStr);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         W32Str_IsEnabled (
        W32STR_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
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
    //                     I s  O n l y  A S C I I
    //---------------------------------------------------------------

    ERESULT         W32Str_IsOnlyASCII(
        W32STR_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        W32CHR_T        *pData;
        uint32_t        lenStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);

        pData = array_Ptr((ARRAY_DATA *)this, 1);
        if (pData) {
            while (*pData && lenStr--) {
                if (*pData > 0x7F) {
                    eRc = ERESULT_GENERAL_FAILURE;
                    break;
                }
                ++pData;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          L e f t
    //---------------------------------------------------------------

    W32STR_DATA *   W32Str_Left(
        W32STR_DATA     *this,
        uint32_t        len
    )
    {
        //ERESULT         eRc;
        uint32_t        offset = 0;
        uint32_t        lenStr;
        W32STR_DATA     *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_DATA;
            return OBJ_NIL;
        }
#endif
        lenStr = W32Str_getLength(this);

        if( (len > lenStr) ) {
            len = lenStr;
        }
        if (0 == lenStr) {
            len = lenStr;
        }
        if ((offset + len - 1) > lenStr) {
            len = lenStr;
        }

        pStr = W32Str_Mid(this, 1, len);

        // Return to caller.
        return pStr;
    }



    //---------------------------------------------------------------
    //                       L o w e r
    //---------------------------------------------------------------

    ERESULT         W32Str_Lower(
        W32STR_DATA        *cbp
    )
    {
        W32CHR_T        *pData;
        uint32_t        lenStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif

        lenStr = W32Str_getLength(cbp);
        pData  = array_Ptr((ARRAY_DATA *)cbp, 1);
        if (lenStr) {
            while( *pData && lenStr-- ) {
                *pData = ascii_toLowerW32(*pData);
                ++pData;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          M i d
    //---------------------------------------------------------------

    W32STR_DATA *   W32Str_Mid(
        W32STR_DATA     *this,
        uint32_t        offset,
        uint32_t        len
    )
    {
        W32STR_DATA     *pNew = OBJ_NIL;
        ERESULT         eRc;
        uint32_t        lenStr;
        W32CHR_T        *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_DATA;
            return OBJ_NIL;
        }
#endif
        lenStr = W32Str_getLength(this);

        if( (offset > lenStr) ) {
            offset = 1;
        }
        if (0 == lenStr) {
            len = lenStr;
            offset = 1;
        }
        if ((offset + len - 1) > lenStr) {
            len = lenStr;
            offset = 1;
        }

        pNew = W32Str_New();
        if (OBJ_NIL == pNew) {
            return OBJ_NIL;
        }
        pData  = array_Ptr((ARRAY_DATA *)this, offset);
        if (pData) {
            eRc = W32Str_AppendW32(pNew, len, pData);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pNew);
                pNew = OBJ_NIL;
            }
        }
        else {
            obj_Release(pNew);
            pNew = OBJ_NIL;
        }

        // Return to caller.
        return pNew;
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
        void        *pMethod = W32Str_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "W32Str", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          W32Str_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        W32STR_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(W32STR_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)W32Str_Class();
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
                            return W32Str_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return W32Str_Enable;
                        }
                        break;

                    case 'P':
#ifdef  W32STR_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return W32Str_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return W32Str_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return W32Str_ToDebugString;
                        }
#ifdef  W32STR_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return W32Str_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return W32Str_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == W32Str_ToDebugString)
                    return "ToDebugString";
#ifdef  W32STR_JSON_SUPPORT
                if (pData == W32Str_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e m o v e
    //---------------------------------------------------------------

    ERESULT         W32Str_Remove(
        W32STR_DATA     *this,
        uint32_t        offset,
        uint32_t        len
    )
    {
        uint32_t        lenStr;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);
        if( (0 == offset) || (offset > lenStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if ((0 == lenStr) || ((offset + len - 1) > lenStr)) {
            return ERESULT_OUT_OF_RANGE;
        }

        eRc = array_Delete((ARRAY_DATA *)this, offset, len);

        // Return to caller.
        return eRc;
    }


    ERESULT         W32Str_RemoveNL(
        W32STR_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        lenStr;
        uint32_t        offset;
        W32CHR_T        *pData;
        W32CHR_T        chr;
        bool            fMore = true;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);
        if (lenStr == 0) {
            return ERESULT_SUCCESS;
        }
        offset = lenStr;

        pData = (W32CHR_T *)W32Str_getData(this);
        while (fMore) {
            fMore = false;
            chr = *(pData + offset - 1);
            if (('\r' == chr) || ('\n' == chr)) {
                offset--;
                fMore = true;
            }
        }

        if (offset < lenStr) {
            eRc = W32Str_Truncate(this, offset);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          R i g h t
    //---------------------------------------------------------------

    W32STR_DATA *   W32Str_Right(
        W32STR_DATA     *this,
        uint32_t        len
    )
    {
        //ERESULT         eRc;
        uint32_t        offset;
        uint32_t        lenStr;
        W32STR_DATA     *pNew = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_DATA;
            return OBJ_NIL;
        }
#endif
        lenStr = W32Str_getLength(this);
        offset = lenStr - len + 1;
        if( (offset > lenStr) ) {
            offset = lenStr;
        }
        if (0 == lenStr) {
            len = lenStr;
        }
        if ((offset + len - 1) > lenStr) {
            offset = 1;
            len = lenStr;
        }

        pNew = W32Str_Mid(this, offset, len);

        // Return to caller.
        return pNew;
    }



    //---------------------------------------------------------------
    //                       S e t C h a r
    //---------------------------------------------------------------

    ERESULT         W32Str_SetChar(
        W32STR_DATA        *this,
        uint32_t        offset,
        const
        char            chr
    )
    {
        uint32_t        lenStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);
        if ((0 == offset) || (offset > lenStr)) {
            return ERESULT_INVALID_PARAMETER;
        }

        *((uint32_t *)array_Ptr((ARRAY_DATA *)this, offset)) = chr;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                           S p a n
    //---------------------------------------------------------------

    ERESULT         W32Str_SpanW32(
        W32STR_DATA        *this,
        uint32_t        *pIndex,
        const
        W32CHR_T        *pSetStr
    )
    {
        uint32_t        i;
        uint32_t        index;
        uint32_t        lenStr;
        W32CHR_T        *pChr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pSetStr) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        lenStr = W32Str_getLength(this);

        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }

        pChr = array_Ptr((ARRAY_DATA *)this, index);
        for ( i=index; i<lenStr; ++i,++pChr ) {
            if (W32Str_ChrInStr(*pChr, pSetStr))
                ;
            else {
                *pIndex = i;
                return ERESULT_SUCCESS;
            }
        }

        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }



    //---------------------------------------------------------------
    //                     S p l i t  O n
    //---------------------------------------------------------------

    W32ARRAY_DATA * W32Str_SplitOnCharW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        chr
    )
    {
        ERESULT         eRc;
        W32ARRAY_DATA   *pArray = OBJ_NIL;
        uint32_t        i = 1;
        uint32_t        iMax;
        uint32_t        start;
        uint32_t        index = 1;
        uint32_t        len;
        W32STR_DATA     *pWrkStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif

        iMax = W32Str_getLength(this);
        pArray = W32Array_New( );
        if (OBJ_NIL == pArray) {
            return OBJ_NIL;
        }

        while (i < (iMax + 1)) {

            // We have to use i to store the current index since index
            // gets clobbered if the character is not found.
            index = i;
            start = index;
            eRc = W32Str_CharFindNextW32(this, &index, chr);
            if (ERESULT_FAILED(eRc)) {
                // index is unreliable.
                i = iMax + 1;
                len = i - start;
            } else {
                i = index + 1;
                len = index - start;
            }
            pWrkStr = OBJ_NIL;
            if (len) {
                pWrkStr = W32Str_Mid(this, start, len);
                if (OBJ_NIL == pWrkStr) {
                    obj_Release(pArray);
                    return OBJ_NIL;
                }
            }
            else {
                pWrkStr = W32Str_New( );
                if (OBJ_NIL == pWrkStr) {
                    obj_Release(pArray);
                    return OBJ_NIL;
                }
            }
            eRc = W32Array_AppendStr(pArray, pWrkStr, NULL);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pArray);
                return OBJ_NIL;
            }
        }

        return pArray;
    }


    W32ARRAY_DATA * W32Str_SplitOnCharsW32(
        W32STR_DATA     *this,
        const
        W32CHR_T        *pChrs
    )
    {
        ERESULT         eRc;
        W32ARRAY_DATA   *pArray = OBJ_NIL;
        uint32_t        i = 1;
        uint32_t        iMax;
        uint32_t        start;
        uint32_t        index = 1;
        uint32_t        len;
        W32STR_DATA     *pWrkStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            //obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif

        iMax = W32Str_getLength(this);
        pArray = W32Array_New( );
        if (OBJ_NIL == pArray) {
            return OBJ_NIL;
        }

        while (i < (iMax + 1)) {

            // We have to use i to store the current index since index
            // gets clobbered if the character is not found.
            index = i;
            start = index;
            eRc = W32Str_CharsFindNextW32(this, &index, pChrs);
            if (ERESULT_FAILED(eRc)) {
                // index is unreliable.
                i = iMax + 1;
                len = i - start;
            } else {
                i = index + 1;
                len = index - start;
            }
            pWrkStr = OBJ_NIL;
            if (len) {
                pWrkStr = W32Str_Mid(this, start, len);
                if (OBJ_NIL == pWrkStr) {
                    obj_Release(pArray);
                    return OBJ_NIL;
                }
            }
            else {
                pWrkStr = W32Str_New( );
                if (OBJ_NIL == pWrkStr) {
                    obj_Release(pArray);
                    return OBJ_NIL;
                }
            }
            eRc = W32Array_AppendStr(pArray, pWrkStr, NULL);
            obj_Release(pWrkStr);
            pWrkStr = OBJ_NIL;
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pArray);
                return OBJ_NIL;
            }
        }

        return pArray;
    }



    //---------------------------------------------------------------
    //                       T o  A S t r
    //---------------------------------------------------------------

    ASTR_DATA *     W32Str_ToAStr(
        W32STR_DATA       *this
    )
    {
        const
        W32CHR_T        *pData;
        W32CHR_T        wchr;
        ASTR_DATA       *pWrkStr;
        char            work[16];

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        pWrkStr = AStr_New();
        if (OBJ_NIL == pWrkStr) {
            return pWrkStr;
        }

        pData = W32Str_getData(this);
        while ((wchr = *pData++)) {
            utf8_W32ToChrCon(wchr, work);
            AStr_AppendA(pWrkStr, work);
        }


        return pWrkStr;
    }



    //---------------------------------------------------------------
    //                     T o  I n t 3 2
    //---------------------------------------------------------------

    int32_t         W32Str_ToInt32(
        W32STR_DATA        *this
    )
    {
        int32_t         i = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        i = dec_getInt32W32(W32Str_getData(this));

        // Return to caller.
        return i;
    }



    //---------------------------------------------------------------
    //                     T o  U t f 8  F i l e
    //---------------------------------------------------------------

    ERESULT         W32Str_ToFile(
        W32STR_DATA     *this,
        FILE            *pOut
    )
    {
        const
        W32CHR_T        *pBuffer;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pOut) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pBuffer = W32Str_getData(this);
        fprintf(pOut, "%ls", pBuffer);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                     T o  U t f 8  F i l e
    //---------------------------------------------------------------

    ERESULT         W32Str_ToUtf8File(
        W32STR_DATA        *this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile = NULL;
        uint32_t        size;
        char            *pChr;
        char            *pBuffer;
        int             chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pBuffer = W32Str_CStringA(this, &size);
        pChr = pBuffer;

        pFile = fopen(Path_getData(pPath), "wb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( size-- ) {
            chr = fputc(*pChr++,pFile);
            if (EOF == chr) {
                DEBUG_BREAK();
                return ERESULT_IO_ERROR;
            }
        }
        fclose(pFile);
        pFile = NULL;

        mem_Free(pBuffer);
        pBuffer = NULL;

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
        ASTR_DATA      *pDesc = W32Str_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Str_ToDebugString (
        W32STR_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Str_Validate(this)) {
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
                    W32Str_getSize(this),
                    obj_getRetainCount(this)
            );

        pWrkStr = array_ToDebugString( &this->super, indent+3 );
        if (pWrkStr) {
            AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
        }

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
    //                          T r i m
    //---------------------------------------------------------------

    ERESULT         W32Str_Trim(
        W32STR_DATA        *this
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        j;
        uint32_t        lenStr;
        W32CHR_T        *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);
        if ( 0 == lenStr ) {
            return ERESULT_SUCCESS;
        }

        // Remove leading characters.
        pData = (W32CHR_T *)W32Str_getData(this);
        j = 0;
        for (i=0; i<lenStr; ++i) {
            if (!ascii_isWhiteSpaceW32(*pData))
                break;
            ++j;
            ++pData;
        }
        if (j) {
            eRc = W32Str_Remove(this, 1, j);
        }

        lenStr = W32Str_getLength(this);
        if ( 0 == lenStr ) {
            return ERESULT_SUCCESS;
        }

        // Remove trailing characters.
        pData = (W32CHR_T *)W32Str_getData(this);
        j = 0;
        for (i=lenStr; i; --i) {
            if (!ascii_isWhiteSpaceW32(*(pData+i-1)))
                break;
            ++j;
        }
        if (j) {
            eRc = W32Str_Truncate(this, (lenStr - j));
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T r u n c a t e
    //---------------------------------------------------------------

    ERESULT         W32Str_Truncate(
        W32STR_DATA        *this,
        uint32_t        len
    )
    {
        uint32_t        lenStr;
        W32CHR_T        data = 0;
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);
        if (len > lenStr) {
            return ERESULT_INVALID_PARAMETER;
        }

        // Insert new EOD char and adjust size.
        eRc = array_Put((ARRAY_DATA *)this, (len + 1), 1, &data);
        BREAK_FAILED(eRc);
        array_setSize((ARRAY_DATA *)this, (len + 1));

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       U p p e r
    //---------------------------------------------------------------

    ERESULT         W32Str_Upper(
        W32STR_DATA        *this
    )
    {
        W32CHR_T        *pData;
        uint32_t        lenStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Str_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = W32Str_getLength(this);

        if (lenStr) {
            pData = array_Ptr((ARRAY_DATA *)this, 1);
            while( *pData && lenStr-- ) {
                *pData = ascii_toUpperW32(*pData);
                ++pData;
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            W32Str_Validate (
        W32STR_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_W32STR))
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


        if (!(obj_getSize(this) >= sizeof(W32STR_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


