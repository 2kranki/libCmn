// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/*
 * File:   AStrC.c
 *	Generated 02/19/2016 09:32:40
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
#include <AStrC_internal.h>
#include <AStr_internal.h>
#include <ascii.h>
#include <crc.h>
#include <stdio.h>
#include <utf8.h>
#include <W32Str.h>



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

    ASTRC_DATA *     AStrC_Alloc(
    )
    {
        ASTRC_DATA      *this;
        uint32_t        cbSize = sizeof(ASTRC_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    ASTRC_DATA *    AStrC_New(
    )
    {
        ASTRC_DATA      *this;
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_Init( this );
        } 
        return( this );
    }


    ASTRC_DATA *   AStrC_NewA(
        const
        char            *pStr
    )
    {
        ASTRC_DATA      *this;
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_InitA(this, pStr);
        }
        return( this );
    }

    
    ASTRC_DATA *   AStrC_NewW32(
        const
        W32CHR_T       *pStr
    )
    {
        ASTRC_DATA     *this;
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_InitW32(this, pStr);
        }
        return( this );
    }

    
    ASTRC_DATA *   AStrC_NewFromAStr(
        ASTR_DATA       *pStr
    )
    {
        ASTRC_DATA      *this;
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_InitA(this, AStr_getData(pStr));
        }
        return( this );
    }
    
    
    ASTRC_DATA *   AStrC_NewFromConstant(
        const
        char            *pStrA
    )
    {
        ASTRC_DATA      *this;
        
        if (pStrA)
            ;
        else {
            return OBJ_NIL;
        }
        
        this = AStrC_Alloc( );
        if (this) {
            this = AStrC_Init(this);
            if (this) {
                this->len = utf8_StrLenA(pStrA);
                this->pData = pStrA;
            }
        }
        
        return this;
    }
    
    

    ASTRC_DATA *    AStrC_NewFromPrint(
        const
        char            *pFormat,
        ...
    )
    {
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStrA = NULL;
        ASTRC_DATA      *pStrC = OBJ_NIL;
        
        va_start( arg_ptr, pFormat );
        str[0] = '\0';
        size = vsnprintf(str, sizeof(str), pFormat, arg_ptr);
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStrA = (char *)mem_Malloc(size);
            if( pStrA == NULL ) {
                return OBJ_NIL;
            }
            va_start( arg_ptr, pFormat );
            size = vsnprintf(pStrA, size, pFormat, arg_ptr);
            va_end( arg_ptr );
            pStrC = AStrC_NewA(pStrA);
            mem_Free(pStrA);
            pStrA = NULL;
        }
        else {
            pStrC = AStrC_NewA(str);
        }
        
        return pStrC;
    }
    
    
    


    
    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        AStrC_getCrcIEEE(
        ASTRC_DATA       *this
    )
    {
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc = 0;
        uint32_t        len;
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        len = (uint32_t)utf8_StrLenChars(this->pData);
        crc = crc_AccumBlock(pCrc, len, (void *)this->pData);
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        
        return  crc;
    }
    
    
    
    const
    char *          AStrC_getData(
        ASTRC_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pData;
    }
    
    
    bool            AStrC_setData(
        ASTRC_DATA      *this,
        const
        char            *pDataA
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->len = 0;
        if (obj_IsFlag(this, ASTRC_FLAG_MALLOC)) {
            if (this->pData) {
                mem_Free((void *)this->pData);
                this->pData = NULL;
            }
        }

        this->pData = pDataA;
        this->len = utf8_StrLenA(this->pData);
        
        return true;
    }
    
    

    uint32_t        AStrC_getDataLength(
        ASTRC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return  (uint32_t)utf8_StrLenChars(this->pData);
        
    }
    
    
    
    uint32_t        AStrC_getLength(
        ASTRC_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return  (uint32_t)utf8_StrLenA(this->pData);

    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A p p e n d
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrC_Append(
        ASTRC_DATA      *this,
        ASTRC_DATA      *pOther
    )
    {
        ASTRC_DATA      *pNew = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if ((OBJ_NIL == pOther) || !(obj_IsKindOf(pOther, OBJ_IDENT_ASTRC))) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNew = AStrC_AppendA(this, pOther->pData);
        
        // Return to caller.
        return pNew;
    }
    
    
    ASTRC_DATA *    AStrC_AppendA(
        ASTRC_DATA      *this,
        const
        char            *pStr
    )
    {
        uint32_t        len;
        uint32_t        lenData;
        uint32_t        lenStr;
        char            *pData;
        ASTRC_DATA      *pOther;

        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AStrC_New( );
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        // This depends on the fact that a new AStrC object
        // doesn't have any data internally.
        
        // Get the data area needed.
        lenStr = (uint32_t)utf8_StrLenChars(pStr);
        if (0 == lenStr) {
            obj_Release(pOther);
            return OBJ_NIL;
        }
        lenData = this->len;
        len = lenStr + lenData + 1;
        pData = mem_Malloc(len);
        if (NULL == pData) {
            obj_Release(pOther);
            return OBJ_NIL;
        }

        // Copy the data to the new area.
        memmove(pData, this->pData, lenData);
        memmove(pData+lenData, pStr, lenStr);
        pData[lenData+lenStr] = '\0';
        
        // Now place the data in the new AStrC.
        pOther->pData = pData;
        pOther->len = lenStr + lenData;
        obj_FlagOn(pOther, ASTRC_FLAG_MALLOC);

        // Return to caller.
        return pOther;
    }
    
    
    ASTRC_DATA *    AStrC_AppendAStr(
        ASTRC_DATA      *this,
        ASTR_DATA       *pStr
    )
    {
        ASTRC_DATA      *pNew = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( OBJ_NIL == pStr ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pNew = AStrC_AppendA(this, AStr_getData(pStr));
        
        // Return to caller.
        return pNew;
    }
    
    
    
    //---------------------------------------------------------------
    //                    A p p e n d  F i l e
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrC_AppendUtf8File(
        ASTRC_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        wint_t          chr;
        FILE            *pFile;
        ASTRC_DATA      *pNew = OBJ_NIL;

        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if( (OBJ_NIL == pPath) || !(obj_IsKindOf(pPath, OBJ_IDENT_PATH)) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pFile = fopen(Path_getData(pPath), "r");
        if (NULL == pFile) {
            //FIXME: return ERESULT_FILE_NOT_FOUND;
        }
        while ( (chr = fgetwc(pFile)) != EOF ) {
            //FIXME: eRc = AStr_AppendCharRepeatW(this, 1, chr);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                //FIXME: return eRc;
            }
        }
        fclose(pFile);
        pFile = NULL;
        
        return pNew;
    }
    
    
    
    //---------------------------------------------------------------
    //                       C h a r  G e t
    //---------------------------------------------------------------
    
    W32CHR_T        AStrC_CharGetW32(
        ASTRC_DATA      *this,
        uint32_t        offset
    )
    {
        uint32_t        lenStr;
        uint32_t        off;
        W32CHR_T        chr = -1;
        const
        char            *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = AStrC_getLength(this);
        
        if( (0 == offset) || (offset > lenStr) ) {
            return EOF;
        }
        off = utf8_StrOffset(this->pData, offset);
        
        pChr = this->pData + (off - 1);
        if (pChr) {
            lenStr = utf8_Utf8ToW32(pChr, &chr);
        }
        
        // Return to caller.
        return chr;
    }
    

    W32CHR_T        AStrC_CharGetFirstW32(
        ASTRC_DATA      *this
    )
    {
        uint32_t        lenStr;
        uint32_t        off;
        W32CHR_T        chr = -1;
        const
        char            *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = AStrC_getLength(this);
        if (0 == lenStr) {
            return chr;
        }
        
        off = utf8_StrOffset(this->pData, 1);
        
        pChr = this->pData + (off - 1);
        if (pChr) {
            if ('\0' == *pChr)
                ;
            else {
                lenStr = utf8_Utf8ToW32(pChr, &chr);
                if (0 == chr)
                    chr = -1;
            }
        }
        
        // Return to caller.
        return chr;
    }
            
            
    W32CHR_T        AStrC_CharGetLastW32(
        ASTRC_DATA      *this
    )
    {
        uint32_t        lenStr;
        uint32_t        off;
        W32CHR_T        chr = -1;
        const
        char            *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        lenStr = AStrC_getLength(this);
        if (0 == lenStr) {
            return chr;
        }
        
        off = utf8_StrOffset(this->pData, lenStr);
        
        pChr = this->pData + (off - 1);
        if (pChr) {
            if ('\0' == *pChr)
                ;
            else {
                lenStr = utf8_Utf8ToW32(pChr, &chr);
                if (0 == chr)
                    chr = -1;
            }
        }
        
        // Return to caller.
        return chr;
    }
        
        

    //---------------------------------------------------------------
    //                       C o m p a r e
    //---------------------------------------------------------------
    
    int             AStrC_Compare(
        ASTRC_DATA      *this,
        ASTRC_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !AStrC_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if( OBJ_NIL == pOther ) {
            DEBUG_BREAK();
            return ERESULT_SUCCESS_GREATER_THAN;
        }
        
        i = utf8_StrCmp(
                        this->pData,
                        pOther->pData
            );
        if( i < 0 )
            eRc = ERESULT_SUCCESS_LESS_THAN;
        if( i > 0 )
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        
        // Return to caller.
        return eRc;
    }
    
    
    int             AStrC_CompareA(
        ASTRC_DATA		*this,
        const
        char            *pData
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -1;
        }
#endif
        
        i = utf8_StrCmp(
                this->pData,
                pData
            );

        // Return to caller.
        return i;
    }
    
    
    int             AStrC_CompareW32(
        ASTRC_DATA		*this,
        const
        W32CHR_T        *pData
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int32_t         i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
        if( NULL == pData ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -1;
        }
#endif
        
        i = utf8_StrCmpAW32(
                this->pData,
                pData
            );

        // Return to caller.
        return i;
    }
    
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrC_Copy(
        ASTRC_DATA      *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        // This object is immutable.
        obj_Retain(this);
        
        // Return to caller.
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            AStrC_Dealloc(
        OBJ_ID          objId
    )
    {
        ASTRC_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (obj_IsFlag(this, ASTRC_FLAG_MALLOC)) {
            if (this->pData) {
                mem_Free((void *)this->pData);
                this->pData = NULL;
            }
        }
        else {
            this->pData = NULL;
        }
        this->len = 0;

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;
        

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          D e e p  C o p y
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrC_DeepCopy(
        ASTRC_DATA      *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        obj_Retain(this);
        
        // Return to caller.
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                      F i n d  N e x t
    //---------------------------------------------------------------
    
    /*  These methods rely on the fact that UTF-8 unicode characters
        never contain a NUL and each encoded unicode character is
        unique.
     */
    ERESULT         AStrC_FindNextA(
        ASTRC_DATA      *this,
        const
        char            *pSrchA,            // UTF-8 String
        uint32_t        *pIndex
    )
    {
        uint32_t        i;
        uint32_t        offset;
        uint32_t        index;
        uint32_t        lenStr;
        uint32_t        lenSrchStr;
        W32CHR_T        chrW32;
        W32CHR_T        chrSrchW32;
        int             iRc;
        const
        char            *pChrA;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pIndex) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == pSrchA) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        iRc = utf8_Utf8ToW32(pSrchA, &chrSrchW32);
        if (iRc <= 0) {
            return ERESULT_INVALID_DATA;
        }
        lenSrchStr = utf8_StrLenA(pSrchA);
        if (lenSrchStr == 0) {
            return ERESULT_INVALID_DATA;
        }
        lenStr = AStrC_getLength(this);
        
        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }
        
        offset = utf8_StrOffset(this->pData, index);
        pChrA = this->pData + (offset - 1);
        for (i=index; i<=(lenStr - lenSrchStr + 1); i++) {
            const
            char            *pChrA_old = pChrA;
            chrW32 = utf8_Utf8ToW32_Scan(&pChrA);
            if (chrW32 == chrSrchW32) {
                if (0 == str_CompareN(pChrA_old, pSrchA, lenSrchStr)) {
                    *pIndex = index;
                    return ERESULT_SUCCESS;
                }
            }
            index++;
        }
        
        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }
                
                
    ERESULT         AStrC_FindNextW32(
        ASTRC_DATA      *this,
        const
        W32CHR_T        *pStrW32,
        uint32_t        *pIndex
    )
    {
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        offset;
        uint32_t        index;
        uint32_t        lenStr;
        uint32_t        lenSrchStr;
        W32CHR_T        chrW32;
        W32CHR_T        chrSrchW32;
        const
        char            *pChrA;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
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
        lenStr = AStrC_getLength(this);
        lenSrchStr = utf8_StrLenW32(pStrW32);
        if (lenSrchStr == 0) {
            return ERESULT_INVALID_DATA;
        }
        chrSrchW32 = *pStrW32;

        index = *pIndex;
        if (0 == index) {
            index = 1;
        }
        if (index > lenStr) {
            *pIndex = 0;
            return ERESULT_OUT_OF_RANGE;
        }
        
        offset = utf8_StrOffset(this->pData, index);
        pChrA = this->pData + (offset - 1);
        iMax = lenStr - lenSrchStr + 1;
        for ( i=index; i<=iMax; i++) {
            const
            char            *pChrA_old = pChrA;
            chrW32 = utf8_Utf8ToW32_Scan(&pChrA);
            if (chrW32 == chrSrchW32) {
                if (0 == str_CompareNW32A(pStrW32, pChrA_old, lenSrchStr)) {
                    *pIndex = index;
                    return ERESULT_SUCCESS;
                }
            }
            index++;
        }
        
        // Return to caller.
        *pIndex = 0;
        return ERESULT_OUT_OF_RANGE;
    }
            
            
            
    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------
    
    uint32_t        AStrC_Hash(
        ASTRC_DATA      *this
    )
    {
        uint32_t        hash = 0;
        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        
        if (this->pData) {
            hash = str_HashAcmA( this->pData, NULL );
        }
        
        return hash;
    }
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTRC_DATA *   AStrC_Init(
        ASTRC_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ASTRC_DATA);
        
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

        this = (ASTRC_DATA *)obj_Init(this, cbSize, OBJ_IDENT_ASTRC);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AStrC_Vtbl);
        
    #ifdef NDEBUG
    #else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     
    ASTRC_DATA *   AStrC_InitA(
        ASTRC_DATA      *this,
        const
        char            *pStr
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = (ASTRC_DATA *)AStrC_Init(this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pData = utf8_StrDup(pStr);
        if (NULL == this->pData) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->len = utf8_StrLenA(this->pData);
        obj_FlagOn(this, ASTRC_FLAG_MALLOC);
        
        obj_FlagSet(this, OBJ_FLAG_RO, true);
        return this;
    }
    
    
    ASTRC_DATA *    AStrC_InitW32(
        ASTRC_DATA      *this,
        const
        W32CHR_T        *pStr
    )
    {
        uint32_t        len;
        uint32_t        lenChars;
        char            *pStr8;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        len = utf8_StrLenW32(pStr);
        
        this = (ASTRC_DATA *)AStrC_Init(this);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        lenChars = utf8_W32StrToUtf8Str(len, pStr, 0, NULL);
        if (lenChars) {
            pStr8 = mem_Malloc(lenChars);
            if (OBJ_NIL == pStr8) {
                DEBUG_BREAK();
                obj_Release(this);
                return OBJ_NIL;
            }
            utf8_W32StrToUtf8Str(len, pStr, lenChars, pStr8);
            this->pData = pStr8;
            this->len = len;
            obj_FlagOn(this, ASTRC_FLAG_MALLOC);
        }
        else {
            this->pData = "";
        }

        obj_FlagSet(this, OBJ_FLAG_RO, true);
        return this;
    }
    
    

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            AStrC_IsEnabled(
        ASTRC_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          M i d
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrC_Mid(
        ASTRC_DATA      *this,
        uint32_t        offset,
        uint32_t        len
    )
    {
        uint32_t        lenStr;
        uint32_t        offBgn;
        uint32_t        offEnd;
        char            *pData;
        ASTRC_DATA      *pOther = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            //AStrC_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
        if ((offset > 0) && (offset < this->len))
            ;
        else {
            DEBUG_BREAK();
            return pOther;
        }
        if ((0 == this->len) || ((offset + len - 1) > this->len)) {
            return pOther;
        }
#endif
        offBgn = utf8_StrOffset(this->pData, offset);
        offEnd = utf8_StrOffset(this->pData, (offset + len)) - 1;
        lenStr = offEnd - offBgn + 1;

        pData = mem_Malloc(lenStr + 1);
        if (pData) {
            memmove(pData, (this->pData + offBgn - 1), lenStr);
            pData[lenStr] = '\0';
        }
        else {
            return pOther;
        }
        
        pOther = AStrC_New();
        if (pOther) {
            pOther->pData = pData;
            obj_FlagOn(pOther, ASTRC_FLAG_MALLOC);
        }
        else {
            mem_Free(pData);
            return pOther;
        }
        
        // Return to caller.
        return pOther;
    }


    
    //---------------------------------------------------------------
    //                       P r e p e n d
    //---------------------------------------------------------------

    ASTRC_DATA *    AStrC_PrependA(
        ASTRC_DATA      *this,
        const
        char            *pStr
    )
    {
        uint32_t        len;
        uint32_t        lenData;
        uint32_t        lenStr;
        char            *pData;
        ASTRC_DATA      *pOther;

        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AStrC_New( );
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        // This depends on the fact that a new AStrC object
        // doesn't have any data internally.
        
        // Get the data area needed.
        lenStr = (uint32_t)utf8_StrLenChars(pStr);
        if (0 == lenStr) {
            obj_Release(pOther);
            return OBJ_NIL;
        }
        lenData = this->len;
        len = lenStr + lenData + 1;
        pData = mem_Malloc(len);
        if (NULL == pData) {
            obj_Release(pOther);
            return OBJ_NIL;
        }

        // Copy the data to the new area.
        memmove(pData, pStr, lenStr);
        memmove(pData+lenStr, this->pData, lenData);
        pData[lenData+lenStr] = '\0';
        
        // Now place the data in the new AStrC.
        pOther->pData = pData;
        pOther->len = lenStr + lenData;
        obj_FlagOn(pOther, ASTRC_FLAG_MALLOC);

        // Return to caller.
        return pOther;
    }

    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          AStrC_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ASTRC_DATA      *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !AStrC_Validate(this) ) {
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
                            return AStrC_ToDebugString;
                        }
                        if (str_Compare("ToString", (char *)pStr) == 0) {
                            return AStrC_ToString;
                        }
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
    //                          T o  A S t r
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrC_ToAStr(
        ASTRC_DATA      *this
    )
    {
        ASTR_DATA       *pNew = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        pNew = AStr_NewA(this->pData);
        
        return pNew;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T o  L o w e r
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrC_ToLower(
        ASTRC_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        const
        char            *pData;
        W32CHR_T        curChr;

#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (pStr) {
            pData = AStrC_getData(this);
            for (;;) {
                curChr = utf8_ChrConToW32_Scan(&pData);
                if (curChr == -1)
                    break;
                curChr = ascii_toLowerW32(curChr);
                eRc = AStr_AppendCharW32(pStr, curChr);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
            }
        }

        return pStr;
    }
            
            
            
    //---------------------------------------------------------------
    //                          T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTRC_DATA *    AStrC_ToString(
        ASTRC_DATA      *this
    )
    {
        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        obj_Retain(this);
        
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrC_ToDebugString(
        ASTRC_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
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
                     "{%p(AStrC) len=%d  data=%s ",
                     this,
                     AStrC_getLength(this),
                     this->pData
            );
        AStr_AppendA(pStr, str);

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
        
        j = snprintf( str, sizeof(str), " %p(AStrC)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T o  U p p e r
    //---------------------------------------------------------------
    
    ASTR_DATA *     AStrC_ToUpper(
        ASTRC_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        const
        char            *pData;
        W32CHR_T        curChr;

#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        pStr = AStr_New();
        if (pStr) {
            pData = AStrC_getData(this);
            for (;;) {
                curChr = utf8_ChrConToW32_Scan(&pData);
                if (curChr == -1)
                    break;
                curChr = ascii_toUpperW32(curChr);
                eRc = AStr_AppendCharW32(pStr, curChr);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
            }
        }

        return pStr;
    }
        
        
        
    //---------------------------------------------------------------
    //                          T o  W 3 2 S t r
    //---------------------------------------------------------------
    
    W32STR_DATA *   AStrC_ToW32Str(
        ASTRC_DATA      *this
    )
    {
        W32STR_DATA     *pNew = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        pNew = W32Str_NewA(this->pData);
        
        return pNew;
    }
        
        
        
    //---------------------------------------------------------------
    //                          T r i m
    //---------------------------------------------------------------
    
    ASTRC_DATA *   AStrC_Trim(
        ASTRC_DATA       *this
    )
    {
        ASTRC_DATA      *pNew = OBJ_NIL;
        
#ifdef NDEBUG
#else
        if( !AStrC_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        //TODO: Finish this!
        
        return pNew;
    }
    
    

    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            AStrC_Validate(
        ASTRC_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_ASTRC) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(ASTRC_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


