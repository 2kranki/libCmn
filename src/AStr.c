// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AStr.c
 *	Generated 09/19/2015 10:15:50
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
#include    <AStr_internal.h>
#include    <ascii.h>
#include    <AStrC.h>
#include    <crc.h>
#include    <dec.h>
#include    <hex.h>
#include    <misc.h>
#include    <str.h>
#include    <utf8.h>
#include    <W32Str.h>
#include    <stdio.h>
#include    <time.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ASTR_DATA *     AStr_Alloc(
    )
    {
        ASTR_DATA      *this;
        uint32_t        cbSize = sizeof(ASTR_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTR_DATA *     AStr_New(
    )
    {
        ASTR_DATA      *this;
        
        this = AStr_Alloc( );
        if (this) {
            this = AStr_Init(this);
        } 
        return this;
    }

    
    
    ASTR_DATA *     AStr_NewA(
        const
        char			*pszIn			/* Input String Pointer */
    )
    {
        ASTR_DATA      *this;
        ERESULT         eRc;
        uint32_t        len;
        
        this = AStr_New( );
        if (this) {
            len = (uint32_t)utf8_StrLenChars(pszIn);
            if (len) {
                eRc = AStr_AppendA(this, pszIn);
                if (ERESULT_HAS_FAILED(eRc)) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
            }
        }
        return this;
    }
    

    
    ASTR_DATA *    AStr_NewFromCharA(
        uint32_t        len,
        const
        char            chr
    )
    {
        ASTR_DATA      *this;
        ERESULT         eRc;
        
        this = AStr_New( );
        if (this) {
            eRc = AStr_AppendCharRepeatA(this, len, chr);
            if (ERESULT_HAS_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }

    
    
    ASTR_DATA *     AStr_NewFromEnv(
        const
        char            *pStr
    )
    {
        ASTR_DATA      *this =  OBJ_NIL;
        char            *pData;
        size_t          len;
        
        // Do initialization.
        if (NULL == pStr) {
            return this;
        }
        
        pData = getenv(pStr);
        if (NULL == pData)
            ;
        else {
            len = strlen(pData);
            if (len) {
                this = AStr_NewA(pData);
            }
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    ASTR_DATA *     AStr_NewFromInt64(
        int64_t         value
    )
    {
        ASTR_DATA       *this =  OBJ_NIL;
        char            str[65];
        int             j;
        
        
        // Do initialization.
        j = snprintf(str, sizeof(str), "%0lld", value);
        if (j) {
            this = AStr_NewA(str);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    ASTR_DATA *     AStr_NewFromW32Str(
        W32STR_DATA     *pStr
    )
    {
        ASTR_DATA       *this =  OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        if (OBJ_NIL == pStr) {
            return this;
        }
        
        this = AStr_New();
        if (this) {
            eRc = AStr_AppendW32Str(this, pStr);
        }
        
        // Return to caller.
        return( this );
    }
    
    
    
    ASTR_DATA *   AStr_NewFromTimeNow(
    )
    {
        ASTR_DATA      *cbp =  OBJ_NIL;
        time_t			startTime;
        char            timeStr[20];
        
        
        // Do initialization.
        startTime = time(NULL);
        strftime( timeStr, 20, "%Y-%m-%d %H:%M:%S", localtime(&startTime) );
        cbp = AStr_NewA(timeStr);
        
        // Return to caller.
        return cbp;
    }
    
    
    
    ASTR_DATA *     AStr_NewFromUInt64(
        uint64_t        value
    )
    {
        ASTR_DATA       *this =  OBJ_NIL;
        char            str[65];
        int             j;
        
        
        // Do initialization.
        j = snprintf(str, sizeof(str), "%0llu", value);
        if (j) {
            this = AStr_NewA(str);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    ASTR_DATA *     AStr_NewFromUtf8File(
        PATH_DATA       *pPath
    )
    {
        ASTR_DATA       *this =  OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == pPath) {
            return this;
        }
        
        this = AStr_New( );
        if (this) {
            eRc = AStr_AppendUtf8File(this, pPath);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    ASTR_DATA *    AStr_NewParenthesizedFromAStr(
        ASTR_DATA       *this
    )
    {
        ASTR_DATA       *pNew =  OBJ_NIL;
        uint32_t        len;
        uint32_t        i;
        int32_t         chr;
        
        // Do initialization.
        if (NULL == this) {
            return this;
        }
        len = AStr_getLength(this);
        
        pNew = AStr_New();
        if (pNew) {
            AStr_AppendCharA(pNew, '"');
            for (i=0; i<len; ++i) {
                chr = AStr_CharGetW32(this, i+1);
                if (chr == '\\') {
                    AStr_AppendCharA(pNew, '\\');
                }
                else if (chr == '"') {
                    AStr_AppendCharA(pNew, '\\');
                }
                else if (chr == '\n') {
                    AStr_AppendCharA(pNew, '\\');
                    chr = 'n';
                }
                else if (chr == '\r') {
                    AStr_AppendCharA(pNew, '\\');
                    chr = 'r';
                }
                else if (chr == '\t') {
                    AStr_AppendCharA(pNew, '\\');
                    chr = 't';
                }
                AStr_AppendCharA(pNew, chr);
            }
            AStr_AppendCharA(pNew, '"');
        }
        
        // Return to caller.
        return pNew;
    }
    
    
    
    ASTR_DATA *     AStr_NewW32(
        const
        W32CHR_T        *pszIn			/* Input String Pointer */
    )
    {
        ASTR_DATA       *this;
        ERESULT         eRc;
        
        this = AStr_New( );
        if (this) {
            eRc = AStr_AppendW32(this, 0, pszIn);
            if (ERESULT_HAS_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
        }
        return this;
    }
    
    
    
    


    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        AStr_getCrcIEEE(
        ASTR_DATA       *this
    )
    {
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
        uint32_t        len;
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        pCrc = crc_New(CRC_TYPE_IEEE_32);
        len = array_getSize(this->pData);
        crc = crc_AccumBlock(
                            pCrc,
                            len,
                            (void *)array_Ptr(this->pData, 1)
              );
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        
        return  crc;
    }
    
    
    
    const
    char *          AStr_getData(
        ASTR_DATA      *this
    )
    {
        char            *pData;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        pData = array_Ptr(this->pData, 1);
        
        return pData;
    }
    
    
    uint32_t        AStr_getLength(
        ASTR_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return  utf8_StrLenA(AStr_getData(this));
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         AStr_Append(
        ASTR_DATA		*this,
        ASTR_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        if (array_getSize(pOther->pData) > 1) {
            eRc =   array_InsertData(
                                    this->pData,
                                    array_getSize(this->pData),
                                    array_getSize(pOther->pData)-1,
                                    array_getData(pOther->pData)
                    );
            if (ERESULT_IS_SUCCESSFUL(eRc)) {
                array_AdjustSize(this->pData, -1);
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_AppendA(
        ASTR_DATA		*this,
        const
        char            *pStr
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        len;
        uint32_t        index;
        char            *pInsert;
        
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        len = (uint32_t)utf8_StrLenChars(pStr);
        if (0 == len) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        // Insert space for the data and then copy it.
        index = array_getSize(this->pData);
        eRc =   array_InsertSpacing(
                        this->pData,
                        index,
                        len
                );
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pInsert = array_Ptr(this->pData, index);
            for (i=0; i<len; ++i) {
                *pInsert++ = *pStr++;
            }
            *pInsert = '\0';
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         AStr_AppendW32Str(
        ASTR_DATA		*this,
        W32STR_DATA     *pStr
    )
    {
        ERESULT         eRc = ERESULT_DATA_MISSING;
        uint32_t        len;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pStr ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        len = W32Str_getLength(pStr);
        if (len) {
            eRc = AStr_AppendW32(this, len, W32Str_getData(pStr));
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_AppendW32(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        W32CHR_T        *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        lenChars;
        char            *pStr8;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
      
        lenChars = utf8_W32ToUtf8Str(len, pStr, 0, NULL);
        if (lenChars) {
            pStr8 = mem_Malloc(lenChars);
            if (pStr8) {
                lenChars = utf8_W32ToUtf8Str(len, pStr, lenChars, pStr8);
                if (lenChars) {
                    eRc =   array_InsertData(
                                    this->pData,
                                    array_getSize(this->pData),
                                    lenChars,
                                    (void *)pStr8
                            );
                }
            }
            mem_Free(pStr8);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A p p e n d  C h a r
    //---------------------------------------------------------------
    
    ERESULT         AStr_AppendCharA(
        ASTR_DATA		*this,
        const
        char            chr
    )
    {
        char            *pData;
        uint32_t        offset;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        offset = array_getSize(this->pData);
        eRc =   array_InsertSpacing(this->pData, offset, 1);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pData = array_Ptr(this->pData, offset);
            *pData = chr;
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_AppendCharW32(
        ASTR_DATA		*this,
        const
        W32CHR_T        chr
    )
    {
        char            *pData;
        uint32_t        offset;
        ERESULT         eRc = ERESULT_SUCCESS;
        int32_t         len;
        char            data[8];
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        len = utf8_W32ToUtf8(chr, data);
        if (len) {
            offset = array_getSize(this->pData);
            eRc =   array_InsertSpacing(
                                            this->pData,
                                            offset,
                                            len
                                            );
            if (ERESULT_IS_SUCCESSFUL(eRc)) {
                pData = array_Ptr(this->pData, offset);
                memmove(pData, data, len);
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_AppendCharRepeatA(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        char            chr
    )
    {
        char            *pData;
        uint32_t        offset;
        uint32_t        i;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        if (0 == len) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        offset = array_getSize(this->pData);
        eRc =   array_InsertSpacing(
                                        this->pData,
                                        offset,
                                        len
                                        );
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pData = array_Ptr(this->pData, offset);
            for (i=0; i<len; ++i) {
                *pData++ = chr;
            };
            //*pData = '\0';
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_AppendCharRepeatW32(
        ASTR_DATA		*this,
        uint32_t        len,
        const
        W32CHR_T        chr
    )
    {
        char            *pData;
        uint32_t        offset;
        uint32_t        i;
        uint32_t        j;
        ERESULT         eRc;
        uint32_t        chrsLen;
        char            chrs[8];
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        if (0 == len) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        chrsLen = utf8_W32ToUtf8(chr, chrs);
        
        offset = array_getSize(this->pData);
        eRc =   array_InsertSpacing(
                        this->pData,
                        offset,
                        (len * chrsLen)
                );
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            pData = array_Ptr(this->pData, offset);
            if (chrsLen ==  1) {
                for (i=0; i<len; ++i) {
                    *pData++ = chrs[0];
                };
            }
            else {
                for (i=0; i<len; ++i) {
                    for (j=0; j<chrsLen; ++j) {
                        *pData++ = chrs[j];
                    };
                };
            }
            //*pData = '\0';
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    A p p e n d  H e x
    //---------------------------------------------------------------
    
    ERESULT         AStr_AppendHex8(
        ASTR_DATA        *this,
        const
        uint8_t         num
    )
    {
        ERESULT         eRc;
        HEX_DATA        *pHex;
        uint32_t        chrsLen = 32;
        char            chrs[33];
        char            *pChrs = chrs;
        uint32_t        len;
        
        pHex = hex_New();
        if (pHex == OBJ_NIL) {
            return ERESULT_GENERAL_FAILURE;
        }
        
        len = hex_putU8A(pHex, num, &chrsLen, &pChrs);
        if (len) {
            chrs[len] = '\0';
            eRc = AStr_AppendA(this, chrs);
        }
        else {
            obj_Release(pHex);
            return ERESULT_GENERAL_FAILURE;
        }
        
        obj_Release(pHex);
        return eRc;
    }
    
    
    ERESULT         AStr_AppendHex16(
        ASTR_DATA		*this,
        const
        uint16_t        num
    )
    {
        ERESULT         eRc;
        HEX_DATA        *pHex;
        uint32_t        chrsLen = 32;
        char            chrs[33];
        char            *pChrs = chrs;
        uint32_t        len;
       
        pHex = hex_New();
        if (pHex == OBJ_NIL) {
            return ERESULT_GENERAL_FAILURE;
        }
        
        len = hex_putU16A(pHex, num, &chrsLen, &pChrs);
        if (len) {
            chrs[len] = '\0';
            eRc = AStr_AppendA(this, chrs);
        }
        else {
            obj_Release(pHex);
            return ERESULT_GENERAL_FAILURE;
        }
        
        obj_Release(pHex);
        return eRc;
    }
    
    
    ERESULT         AStr_AppendHex32(
        ASTR_DATA		*this,
        const
        uint32_t        num
    )
    {
        ERESULT         eRc;
        HEX_DATA        *pHex;
        uint32_t        chrsLen = 32;
        char            chrs[33];
        char            *pChrs = chrs;
        uint32_t        len;
        
        pHex = hex_New();
        if (pHex == OBJ_NIL) {
            return ERESULT_GENERAL_FAILURE;
        }
        
        len = hex_putU32A(pHex, num, &chrsLen, &pChrs);
        if (len) {
            chrs[len] = '\0';
            eRc = AStr_AppendA(this, chrs);
        }
        else {
            obj_Release(pHex);
            return ERESULT_GENERAL_FAILURE;
        }
        
        obj_Release(pHex);
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                    A p p e n d  F i l e
    //---------------------------------------------------------------
    
    ERESULT         AStr_AppendUtf8File(
        ASTR_DATA		*this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        wint_t          chr;
        FILE            *pFile;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !AStr_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pFile = fopen(path_getData(pPath), "r");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( (chr = fgetwc(pFile)) != EOF ) {
            eRc = AStr_AppendCharRepeatW32(this, 1, chr);
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
    
    ERESULT         AStr_AppendPrint(
        ASTR_DATA		*this,
        const
        char            *pFormat,
        ...
    )
    {
        ERESULT         eRc;
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStr = NULL;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        va_start( arg_ptr, pFormat );
        str[0] = '\0';
        size = vsnprintf( str, sizeof(str), pFormat, arg_ptr );
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStr = (char *)mem_Malloc(size);
            if( pStr == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start( arg_ptr, pFormat );
            size = vsnprintf( pStr, size, pFormat, arg_ptr );
            va_end( arg_ptr );
            eRc = AStr_AppendA(this, pStr);
            mem_Free( pStr );
            pStr = NULL;
        }
        else {
            eRc = AStr_AppendA(this, str);
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         AStr_Assign(
        ASTR_DATA	    *this,
        ASTR_DATA       *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !AStr_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = array_Assign(this->pData, pOther->pData);
        if (ERESULT_HAS_FAILED(eRc)) {
            return eRc;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //               C h a r  F i n d  N e x t
    //---------------------------------------------------------------
    
    ERESULT         AStr_CharFindNextW32(
        ASTR_DATA		*this,
        uint32_t        *pIndex,
        const
        W32CHR_T        chr
    )
    {
        uint32_t        i;
        uint32_t        lenStr;
        uint32_t        index;
        uint32_t        off;
        char            *pChr;
        W32CHR_T        cChrsSrch;
        char            chrsSrch[8];
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        lenStr = AStr_getLength(this);
        cChrsSrch = utf8_W32ToUtf8(chr, chrsSrch);
        
        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }
        
        for ( i=index; i<=lenStr; ++i ) {
            off = utf8_StrOffset(AStr_getData(this), i);
            pChr = array_Ptr(this->pData, off);
            if (0 == strncmp(pChr, chrsSrch, cChrsSrch)) {
                *pIndex = i;
                return ERESULT_SUCCESS;
            }
        }
        
        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }
    
    
    
    //---------------------------------------------------------------
    //               C h a r  F i n d  P r e v
    //---------------------------------------------------------------
    
    ERESULT         AStr_CharFindPrevW32(
        ASTR_DATA		*this,
        uint32_t        *pIndex,
        const
        W32CHR_T        chr
    )
    {
        uint32_t        i;
        uint32_t        index;
        uint32_t        off;
        char            *pChr;
        uint32_t        lenStr;
        W32CHR_T        cChrsSrch;
        char            chrsSrch[8];
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        lenStr = AStr_getLength(this);
        cChrsSrch = utf8_W32ToUtf8(chr, chrsSrch);
        
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
        
        for ( i=index; i; --i ) {
            off = utf8_StrOffset(AStr_getData(this), i);
            pChr = array_Ptr(this->pData, off);
            if (0 == strncmp(pChr, chrsSrch, cChrsSrch)) {
                *pIndex = i;
                return ERESULT_SUCCESSFUL_COMPLETION;
            }
        }
        
        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C h a r  G e t
    //---------------------------------------------------------------
    
    W32CHR_T        AStr_CharGetW32(
        ASTR_DATA		*this,
        uint32_t        offset
    )
    {
        uint32_t        lenStr;
        uint32_t        off;
        W32CHR_T        chr = -1;
        char            *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = AStr_getLength(this);
        
        if( (0 == offset) || (offset > lenStr) ) {
            return EOF;
        }
        off = utf8_StrOffset(AStr_getData(this), offset);
        
        pChr = array_Ptr(this->pData, off);
        if (pChr) {
            lenStr = utf8_Utf8ToW32(pChr, &chr);
        }
        
        // Return to caller.
        return chr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C h a r  I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         AStr_CharInsertW32(
        ASTR_DATA       *this,
        uint32_t        offset,
        W32CHR_T        chr
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        lenStr;
        uint32_t        off;
        char            *pChr;
        uint32_t        chrsLen;
        char            chrs[8];
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = AStr_getLength(this);
        chrsLen = utf8_W32ToUtf8(chr, chrs);
        
        if( (0 == offset) || (offset > lenStr) ) {
            return -1;
        }
        off = utf8_StrOffset(AStr_getData(this), offset);
        
        pChr = array_Ptr(this->pData, off);
        lenStr = utf8_Utf8ToW32(pChr, NULL);
        if (pChr && lenStr) {
            eRc = array_InsertData(this->pData, off, chrsLen, chrs);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_CharInsertW32Repeat(
        ASTR_DATA       *this,
        uint32_t        offset,
        uint32_t        len,
        W32CHR_T        chr
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        lenStr;
        uint32_t        off;
        char            *pChr;
        uint32_t        chrsLen;
        char            chrs[8];
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = AStr_getLength(this);
        chrsLen = utf8_W32ToUtf8(chr, chrs);
        
        if( (0 == offset) || (offset > lenStr) ) {
            return -1;
        }
        off = utf8_StrOffset(AStr_getData(this), offset);
        
        pChr = array_Ptr(this->pData, off);
        lenStr = utf8_Utf8ToW32(pChr, NULL);
        if (pChr && lenStr) {
            while (len--) {
                eRc = array_InsertData(this->pData, off, chrsLen, chrs);
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C h a r  P u t
    //---------------------------------------------------------------
    
    ERESULT         AStr_CharPutW32(
        ASTR_DATA		*this,
        uint32_t        offset,
        W32CHR_T        chr
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        lenStr;
        uint32_t        off;
        char            *pChr;
        uint32_t        chrsLen;
        char            chrs[8];
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = AStr_getLength(this);
        chrsLen = utf8_W32ToUtf8(chr, chrs);
        
        if( (0 == offset) || (offset > lenStr) ) {
            return -1;
        }
        off = utf8_StrOffset(AStr_getData(this), offset);
        
        pChr = array_Ptr(this->pData, off);
        lenStr = utf8_Utf8ToW32(pChr, NULL);
        if (pChr && lenStr) {
            eRc = array_Delete(this->pData, off, lenStr);
            if (ERESULT_IS_SUCCESSFUL(eRc)) {
                eRc = array_InsertData(this->pData, off, chrsLen, chrs);
            }
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //               C h a r  R e p l a c e  A l l
    //---------------------------------------------------------------
    
    ERESULT         AStr_CharReplaceAllW32(
        ASTR_DATA		*this,
        const
        W32CHR_T        chrSrch,
        const
        W32CHR_T        chrRepl
    )
    {
        uint32_t        i;
        uint32_t        off;
        char            *pChr;
        uint32_t        lenStr;
        W32CHR_T        cChrsSrch;
        char            chrsSrch[8];
        W32CHR_T        cChrsRepl;
        char            chrsRepl[8];
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif

        lenStr = AStr_getLength(this);
        cChrsSrch = utf8_W32ToUtf8(chrSrch, chrsSrch);
        cChrsRepl = utf8_W32ToUtf8(chrRepl, chrsRepl);
        
        pChr = array_Ptr(this->pData, 1);
        for ( i=0; i<lenStr; ++i ) {
            off = utf8_StrOffset(AStr_getData(this), i+1);
            pChr = array_Ptr(this->pData, off);
            if (0 == strncmp(pChr, chrsSrch, cChrsSrch)) {
                eRc = array_Delete(this->pData, off, cChrsSrch);
                if (ERESULT_IS_SUCCESSFUL(eRc)) {
                    eRc =   array_InsertData(
                                            this->pData,
                                            off,
                                            cChrsRepl,
                                            chrsRepl
                            );
                    if (ERESULT_HAS_FAILED(eRc)) {
                        return eRc;
                    }
                }
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    ERESULT         AStr_Compare(
        ASTR_DATA		*this,
        ASTR_DATA       *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !AStr_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if( OBJ_NIL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        
        i = utf8_StrCmp(
                    array_Ptr(this->pData,1),
                    array_Ptr(pOther->pData,1)
            );
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
       
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_CompareA(
        ASTR_DATA		*this,
        const
        char            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = utf8_StrCmp(
                        array_Ptr(this->pData, 1),
                        pData
            );
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        
        // Return to caller.
        return eRc;
    }
    

    ERESULT         AStr_CompareRightA(
        ASTR_DATA		*this,
        const
        char            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int32_t         i;
        int32_t         len;
        int             lenData;
        int             offset;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        lenData = utf8_StrLenA(pData);
        len = AStr_getLength(this);
        if (len < lenData) {
            return ERESULT_DATA_TOO_SMALL;
        }
        
        offset = len - lenData + 1;
        i = utf8_StrCmp(array_Ptr(this->pData, offset), pData);
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         AStr_CompareW32(
        ASTR_DATA		*this,
        const
        W32CHR_T        *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        i = utf8_StrCmpAW32(array_Ptr(this->pData, 1), pData);
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    ASTR_DATA *    AStr_Copy(
        ASTR_DATA      *this
    )
    {
        ASTR_DATA      *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AStr_New();
        if (pOther) {
            eRc = AStr_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C S t r i n g A
    //---------------------------------------------------------------
    
    char *          AStr_CStringA(
        ASTR_DATA		*this,
        uint32_t        *pLen       // Optional returned string length
                                    // less terminating NUL
    )
    {
        char            *pAStr;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        lenStr = array_getSize(this->pData);
        
        pAStr = (char *)mem_Malloc(lenStr);
        if (pAStr) {
            memmove(pAStr, array_Ptr(this->pData, 1), lenStr);
        }
        
        // Return to caller.
        if (pLen) {
            *pLen = lenStr - 1;
        }
        return pAStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            AStr_Dealloc(
        OBJ_ID          objId
    )
    {
        ASTR_DATA      *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if (this->pData) {
            obj_Release(this->pData);
            this->pData = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D e e p  C o p y
    //---------------------------------------------------------------
    
    ASTR_DATA *    AStr_DeepCopy(
        ASTR_DATA      *this
    )
    {
        ASTR_DATA      *pOther = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AStr_New();
        if (pOther) {
            obj_Release(pOther->pData);
            //pOther->pData = OBJ_NIL;
            pOther->pData = array_DeepCopy(this->pData);
            if (OBJ_NIL == pOther->pData) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        AStr_Hash(
        ASTR_DATA       *this
    )
    {
        uint32_t        hash = 0;
        char            *pStr = NULL;
        
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        pStr = array_Ptr(this->pData, 1);
        if (pStr) {
            hash = str_HashAcmA( pStr, NULL );
        }
        
        return hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTR_DATA *    AStr_Init(
        ASTR_DATA      *this
    )
    {
        uint32_t        cbSize;
        ERESULT         eRc;
        char            eod = 0;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (ASTR_DATA *)obj_Init( this, cbSize, OBJ_IDENT_ASTR );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);         // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_ASTR);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AStr_Vtbl);
        
        this->pData = array_New(1);
        if (OBJ_NIL == this->pData) {
            obj_Release(this);
            return OBJ_NIL;
        }
        //array_setZeroNew(this->pData, true);
        
        // Set up the End-Of-Data marker (ie '\0')
        eRc = array_AppendData(this->pData, 1, &eod);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I n s e r t
    //---------------------------------------------------------------
    
    ERESULT         AStr_InsertA(
        ASTR_DATA		*this,
        uint32_t        offset,
        const
        char            *pStr
    )
    {
        ERESULT         eRc;
        uint32_t        len;
        uint32_t        off;
        uint32_t        lenStr;     // in bytes
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        
        if( (0 == offset) || (offset > (lenStr + 1)) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        
        off = utf8_StrOffset(AStr_getData(this), offset);
        len = (uint32_t)utf8_StrLenChars(pStr);
        if (0 == len) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        eRc =   array_InsertData(
                            this->pData,
                            off,
                            len,
                            (void *)pStr
                );
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    ERESULT         AStr_InsertW32(
        ASTR_DATA		*this,
        uint32_t        offset,
        const
        W32CHR_T        *pStr
    )
    {
        uint32_t        len;
        uint32_t        off;
        ERESULT         eRc;
        char            *pChrs;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
        if( (0 == offset) || (offset > AStr_getLength(this)) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (NULL == pStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        off = utf8_StrOffset(AStr_getData(this), offset);
        
        len = utf8_W32ToUtf8Str(0,pStr,0,NULL);
        pChrs = mem_Malloc(len);
        if (pChrs) {
            len = utf8_W32ToUtf8Str(0,pStr,len,pChrs);
            eRc = array_InsertData(
                                this->pData,
                                off,
                                len,
                                (void *)pChrs
                    );
            mem_Free(pChrs);
            pChrs = NULL;
        }
        else {
            eRc = ERESULT_MEMORY_EXCEEDED;
        }
        
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     I s  O n l y  A S C I I
    //---------------------------------------------------------------
    
    ERESULT         AStr_IsOnlyASCII(
        ASTR_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        W32CHR_T        *pData;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        
        pData = array_Ptr(this->pData, 1);
        if (pData) {
            while (*pData) {
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
    
    ERESULT         AStr_Left(
        ASTR_DATA		*this,
        uint32_t        len,
        ASTR_DATA      **ppOther           // [out]
    )
    {
        ERESULT         eRc;
        uint32_t        offset = 0;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        
        if (NULL == ppOther) {
            return ERESULT_INVALID_PARAMETER;
        }
        if( (len > lenStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if ((0 == lenStr) || ((offset + len - 1) > lenStr)) {
            return ERESULT_OUT_OF_RANGE;
        }
        
        eRc = AStr_Mid(this, 1, len, ppOther);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       L o w e r
    //---------------------------------------------------------------
    
    ERESULT         AStr_Lower(
        ASTR_DATA		*this
    )
    {
        char            *pData;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        
        lenStr = AStr_getLength(this);
        pData  = array_Ptr(this->pData, 1);
        if (lenStr) {
            while( *pData ) {
                if( (*pData >= 'A') && (*pData <= 'Z') )
                    *pData = (char)(*pData + ('a' - 'A'));
                ++pData;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M a t c h
    //---------------------------------------------------------------
    
    ERESULT         AStr_MatchA(
        ASTR_DATA       *this,
        const
        char            *pPattern
    )
    {
        bool            fRc;
        ERESULT         eRc = ERESULT_SUCCESS;
        
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (pPattern) {
            fRc =   misc_PatternMatchA(
                        pPattern,
                        AStr_getData(this),
                        NULL,
                        NULL
                    );
            if (!fRc) {
                eRc = ERESULT_DATA_NOT_FOUND;
            }
        }
        
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M i d
    //---------------------------------------------------------------
    
    ERESULT         AStr_Mid(
        ASTR_DATA		*this,
        uint32_t        offset,
        uint32_t        len,
        ASTR_DATA      **ppOther           // [out]
    )
    {
        ASTR_DATA      *pNew;
        ERESULT         eRc;
        uint32_t        lenStr;
        uint32_t        offBgn;
        uint32_t        offEnd;
        char            *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        
        if (NULL == ppOther) {
            return ERESULT_INVALID_PARAMETER;
        }
        else {
            *ppOther = OBJ_NIL;
        }
        if( (offset > lenStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if ((0 == lenStr) || ((offset + len - 1) > lenStr)) {
            return ERESULT_OUT_OF_RANGE;
        }
        offBgn = utf8_StrOffset(AStr_getData(this), offset);
        offEnd = utf8_StrOffset(AStr_getData(this), (offset + len)) - 1;
        lenStr = offEnd - offBgn + 1;
        
        pNew = AStr_Alloc();
        pNew = AStr_Init(pNew);
        if (OBJ_NIL == pNew) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        pData  = array_Ptr(this->pData, offBgn);
        if (pData) {
            eRc =   array_InsertData(
                                pNew->pData,
                                1,
                                lenStr,
                                (void *)pData
                    );
            if (ERESULT_HAS_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pNew);
                return ERESULT_GENERAL_FAILURE;
            }
        }
        else {
            return ERESULT_OUT_OF_RANGE;
        }
        
        // Return to caller.
        *ppOther = pNew;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          AStr_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ASTR_DATA       *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
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
                            return AStr_ToDebugString;
                        }
#ifdef XYZZY
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return AStr_ToJSON;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e m o v e
    //---------------------------------------------------------------
    
    ERESULT         AStr_Remove(
        ASTR_DATA		*this,
        uint32_t        offset,
        uint32_t        len
    )
    {
        uint32_t        lenStr;
        uint32_t        offBgn;
        uint32_t        offEnd;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        if( (0 == offset) || (offset > lenStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if ((0 == lenStr) || ((offset + len - 1) > lenStr)) {
            return ERESULT_OUT_OF_RANGE;
        }
        offBgn = utf8_StrOffset(AStr_getData(this), offset);
        offEnd = utf8_StrOffset(AStr_getData(this), (offset + len - 1));
        
        eRc =   array_Delete(
                            this->pData,
                            offBgn,
                            (offEnd - offBgn + 1)
                );
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R i g h t
    //---------------------------------------------------------------
    
    ERESULT         AStr_Right(
        ASTR_DATA		*this,
        uint32_t        len,
        ASTR_DATA      **ppOther           // [out]
    )
    {
        ERESULT         eRc;
        uint32_t        offset;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        if (NULL == ppOther) {
            return ERESULT_INVALID_PARAMETER;
        }
        offset = lenStr - len + 1;
        if( (offset > lenStr) ) {
            return ERESULT_INVALID_PARAMETER;
        }
        if ((0 == lenStr) || ((offset + len - 1) > lenStr)) {
            return ERESULT_OUT_OF_RANGE;
        }
        
        eRc = AStr_Mid(this, offset, len, ppOther);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                           S p a n
    //---------------------------------------------------------------
    
    ERESULT         AStr_SpanW32(
        ASTR_DATA		*this,
        uint32_t        *pIndex,
        const
        W32CHR_T        *pSetStr
    )
    {
        uint32_t        i;
        uint32_t        index;
        uint32_t        lenStr;
        uint32_t        off;
        char            *pData;
        W32CHR_T        chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
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
        lenStr = AStr_getLength(this);
        
        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }
        
        pData = array_Ptr(this->pData,index);
        for ( i=index; i<lenStr; ++i ) {
            off = utf8_StrOffset(AStr_getData(this), i);
            pData  = array_Ptr(this->pData, off);
            utf8_Utf8ToW32(pData, &chr);
            if (W32Str_ChrInStr(chr,pSetStr))
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
    //                       T o  C h r  C o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStr_ToChrCon(
        ASTR_DATA       *this
    )
    {
        uint32_t        i;
        uint32_t        iMax;
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
        iMax = AStr_getLength(this);
        
        for (i=0; i<iMax; ++i) {
            wchr = AStr_CharGetW32(this, i+1);
            if (wchr) {
            }
            else {
                break;
            }
            utf8_W32ToChrCon(wchr, work);
            AStr_AppendA(pWrkStr, work);
        }
        
        
        return pWrkStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                     T o  I n t 6 4
    //---------------------------------------------------------------
    
    int64_t         AStr_ToInt64(
        ASTR_DATA		*this
    )
    {
        int64_t         num = 0;
        char            *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pData  = array_Ptr(this->pData, 1);
        if ((*pData == '0') && ((*(pData+1) == 'x') || (*(pData+1) == 'x'))) {
            num = hex_getInt64A(pData);
        }
        else {
            num = dec_getInt64A(pData);
        }

        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                     T o  U i n t 6 4
    //---------------------------------------------------------------
    
    uint64_t        AStr_ToUint64(
        ASTR_DATA		*this
    )
    {
        uint64_t        num = 0;
        char            *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pData  = array_Ptr(this->pData, 1);
        if ((*pData == '0') && ((*(pData+1) == 'x') || (*(pData+1) == 'x'))) {
            num = (uint64_t)hex_getInt64A(pData);
        }
        else {
            num = (uint64_t)dec_getInt64A(pData);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  L o w e r
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStr_ToLower(
        ASTR_DATA       *this
    )
    {
        ASTR_DATA       *pStr;
        char            *pData;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_Copy(this);
        if (pStr) {
            lenStr = AStr_getLength(pStr);
            if (lenStr) {
                pData = array_Ptr(pStr->pData,1);
                while( *pData ) {
                    if( (*pData >= 'A') && (*pData <= 'Z') )
                        *pData = (char)(*pData + ('a' - 'A'));
                    ++pData;
                }
            }
        }
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStr_ToAStrC(
        ASTR_DATA       *this
    )
    {
        ASTRC_DATA      *pStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStrC_NewA(AStr_getData(this));
        
        return pStr;
    }
    
    
    ASTR_DATA *     AStr_ToDebugString(
        ASTR_DATA       *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //uint32_t        j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{%p(%s) retain=%d\n",
                    this,
                    pInfo->pClassName,
                    obj_getRetainCount(this)
                );

        pWrkStr = array_ToDebugString(this->pData, indent+3);
        if (pWrkStr) {
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
        }
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(pStr, "\n   %p(AStr)}\n", this);
        
        return pStr;
    }
    
    
    W32STR_DATA *   AStr_ToW32Str(
        ASTR_DATA      *this
    )
    {
        W32STR_DATA    *pStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = W32Str_NewA(AStr_getData(this));
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  U p p e r
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStr_ToUpper(
        ASTR_DATA       *this
    )
    {
        ASTR_DATA       *pStr;
        char            *pData;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_Copy(this);
        if (pStr) {
            lenStr = AStr_getLength(pStr);
            if (lenStr) {
                pData = array_Ptr(pStr->pData,1);
                while( *pData ) {
                    if( (*pData >= 'a') && (*pData <= 'z') )
                        *pData = (char)(*pData - ('a' - 'A'));
                    ++pData;
                }
            }
        }
        
        return pStr;
    }
    
    

    //---------------------------------------------------------------
    //                     T o  U t f 8  F i l e
    //---------------------------------------------------------------
    
    ERESULT         AStr_ToUtf8File(
        ASTR_DATA		*this,
        PATH_DATA       *pPath
    )
    {
        FILE            *pFile = NULL;
        uint32_t        size = 0;
        char            *pChr;
        char            *pBuffer;
        int             chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pBuffer = AStr_CStringA(this, &size);
        pChr = pBuffer;
        
        pFile = fopen(path_getData(pPath), "wb");
        if (NULL == pFile) {
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( size-- ) {
            chr = fputc(*pChr++, pFile);
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
    //                          T r i m
    //---------------------------------------------------------------
    
    ERESULT         AStr_Trim(
        ASTR_DATA		*this
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        j;
        uint32_t        k;
        uint32_t        lenStr;
        uint32_t        off;
        char            *pData;
        W32CHR_T        chr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        if ( 0 == lenStr ) {
            return ERESULT_SUCCESS;
        }
        
        // Remove leading characters.
        k = 0;
        for (i=1; i<=lenStr; ++i) {
            off = utf8_StrOffset(AStr_getData(this), i);
            pData  = array_Ptr(this->pData, off);
            utf8_Utf8ToW32(pData, &chr);
            j = W32Str_ChrInStr(chr, W32Str_WhiteSpaceW32());
            if (0 == j) {
                break;
            }
            ++k;
        }
        if (k) {
            eRc = AStr_Remove(this, 1, k);
        }
        
        lenStr = AStr_getLength(this);
        if ( 0 == lenStr ) {
            return ERESULT_SUCCESS;
        }
        
        // Remove trailing characters.
        k = 0;
        for (i=lenStr; i; --i) {
            off = utf8_StrOffset(AStr_getData(this), i);
            pData  = array_Ptr(this->pData, off);
            utf8_Utf8ToW32(pData, &chr);
            j = W32Str_ChrInStr(chr, W32Str_WhiteSpaceW32());
            if (0 == j) {
                break;
            }
            ++k;
        }
        if (k) {
            eRc = AStr_Truncate(this, (lenStr - k));
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T r u n c a t e
    //---------------------------------------------------------------
    
    ERESULT         AStr_Truncate(
        ASTR_DATA		*this,
        uint32_t        len
    )
    {
        uint32_t        lenStr;
        uint32_t        off;
        char            *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        if (len > lenStr) {
            return ERESULT_INVALID_PARAMETER;
        }
        
        // Insert new EOD char and adjust size.
        if (len) {
            off = utf8_StrOffset(AStr_getData(this), (len + 1));
            pData  = array_Ptr(this->pData, off);
            if (pData) {
                *pData = '\0';
            }
            array_setSize(this->pData, off);
        }
        else {
            pData  = array_Ptr(this->pData, 1);
            if (pData) {
                *pData = '\0';
            }
            array_setSize(this->pData, 1);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       U p p e r
    //---------------------------------------------------------------
    
    ERESULT         AStr_Upper(
        ASTR_DATA		*this
    )
    {
        char            *pData;
        uint32_t        lenStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStr_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_DATA;
        }
#endif
        lenStr = AStr_getLength(this);
        
        if (lenStr) {
            pData = array_Ptr(this->pData,1);
            while( *pData ) {
                if( (*pData >= 'a') && (*pData <= 'z') )
                    *pData = (char)(*pData - ('a' - 'A'));
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
    bool            AStr_Validate(
        ASTR_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_ASTR) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(ASTR_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


