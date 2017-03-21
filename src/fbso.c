// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   fbso.c
 *	Generated 07/01/2015 10:14:52
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
#include    "fbso_internal.h"
#include    <stdarg.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    FBSO_DATA *   fbso_InternalInit(
        FBSO_DATA       *this,
        PATH_DATA       *pPath,
        const
        char            *pWriteStr
    )
    {
        uint32_t        cbSize = sizeof(FBSO_DATA);
        char            *pFilePath = NULL;
        ERESULT         eRc;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_FBSO );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&fbso_Vtbl);
        
        
        this->pPath = path_Copy(pPath);
        eRc = path_Clean(this->pPath);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        pFilePath = path_CStringA(this->pPath);
        if (pFilePath == NULL) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pFile = fopen(pFilePath, pWriteStr);
        mem_Free(pFilePath);
        pFilePath = NULL;
        if (NULL == this->pFile) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pFile);
#endif
        
        return this;
    }
    
    
    

    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    FBSO_DATA *     fbso_Alloc(
    )
    {
        FBSO_DATA       *this;
        uint32_t        cbSize = sizeof(FBSO_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    FBSO_DATA *     fbso_New(
        PATH_DATA       *pPath
    )
    {
        FBSO_DATA       *this;
        
        // Do initialization.
        
        this = fbso_Alloc( );
        if (this) {
            this = fbso_Init(this, pPath);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool            fbso_setBigEndian(
        FBSO_DATA       *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        obj_FlagSet(this, FBSO_FLAG_BIGENDIAN, value);

        return true;
    }
    
    
    
    PATH_DATA *     fbso_getPath(
        FBSO_DATA		*this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pPath;
    }
    
    
    bool            fbso_setPath(
        FBSO_DATA		*this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;
        
        return true;
    }
    
    
    
    uint16_t        fbso_getPriority(
        FBSO_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            fbso_setPriority(
        FBSO_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    uint32_t        fbso_getSize(
        FBSO_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //              C h a n g e  B u f f e r  S i z e
    //---------------------------------------------------------------
    
    ERESULT         fbso_ChangeBufferSize(
        FBSO_DATA		*this,
        uint16_t        newBufferSize
    )
    {
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (NULL == this->pFile) {
            return ERESULT_FILE_CLOSED;
        }
        
        iRc = fflush(this->pFile);
        if (iRc == EOF) {
            return ERESULT_WRITE_ERROR;
        }
        
        if (this->pBuffer) {
            mem_Free(this->pBuffer);
            this->pBuffer = NULL;
            this->bufferSize = 0;
        }
        
        iRc = setvbuf(this->pFile, NULL, _IOFBF, 0);
        
        if (newBufferSize) {
            this->pBuffer = mem_Malloc(newBufferSize);
        }
        
        if (NULL == this->pBuffer) {
            iRc = setvbuf(this->pFile, this->pBuffer, _IOFBF, newBufferSize);
            this->bufferSize = newBufferSize;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l o s e
    //---------------------------------------------------------------
    
    ERESULT         fbso_Close(
        FBSO_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pFile) {
            fflush(this->pFile);
            fclose(this->pFile);
            this->pFile = NULL;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F l u s h
    //---------------------------------------------------------------
    
    ERESULT         fbso_Flush(
        FBSO_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pFile) {
            fflush(this->pFile);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            fbso_Dealloc(
        OBJ_ID          objId
    )
    {
        FBSO_DATA       *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pFile) {
            fflush(this->pFile);
            fclose(this->pFile);
            this->pFile = NULL;
        }
        
        if (this->pBuffer) {
            mem_Free(this->pBuffer);
            this->pBuffer = NULL;
        }
        
        fbso_setPath(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    FBSO_DATA *   fbso_Init(
        FBSO_DATA       *this,
        PATH_DATA       *pPath
    )
    {

        this = fbso_InternalInit(this, pPath, "w");

        return this;
    }

     

    FBSO_DATA *   fbso_InitConCat(
        FBSO_DATA       *this,
        PATH_DATA       *pPath
    )
    {
        
        this = fbso_InternalInit(this, pPath, "w+");
        
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i n t
    //---------------------------------------------------------------
    
    ERESULT         fbso_Print(
        FBSO_DATA		*this,
        const
        char            *pFormat,
        ...
    )
    {
        va_list         arg_ptr;
        char            *str;
        char            *ptr;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        str = (char *)mem_Malloc( 8192 );
        if( str == NULL )
            return ERESULT_INSUFFICIENT_MEMORY;
        va_start( arg_ptr, pFormat );
        vsnprintf( str, 8192, pFormat, arg_ptr );
        va_end( arg_ptr );
        ptr = str;
        while( *ptr ) {
            fbso_Putc( this, *ptr );
            ++ptr;
        }
        mem_Free( str );
        str = NULL;

        return ERESULT_SUCCESS;
    }

    
    
    //---------------------------------------------------------------
    //                     P u t  U n s i g n e d
    //---------------------------------------------------------------
    
    ERESULT         fbso_PutU8(
        FBSO_DATA		*this,
        const
        uint8_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        fbso_Putc(this, (value & 0xFF));
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         fbso_PutU16(
        FBSO_DATA		*this,
        const
        uint16_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_Flag(this,FBSO_FLAG_BIGENDIAN)) {
            fbso_Putc(this, ((value >> 8) & 0xFF));
            fbso_Putc(this, (value & 0xFF));
        }
        else {
            fbso_Putc(this, (value & 0xFF));
            fbso_Putc(this, ((value >> 8) & 0xFF));
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         fbso_PutU24(
        FBSO_DATA		*this,
        const
        uint32_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_Flag(this,FBSO_FLAG_BIGENDIAN)) {
            fbso_Putc(this, ((value >> 16) & 0xFF));
            fbso_Putc(this, ((value >> 8) & 0xFF));
            fbso_Putc(this, (value & 0xFF));
        }
        else {
            fbso_Putc(this, (value & 0xFF));
            fbso_Putc(this, ((value >> 8) & 0xFF));
            fbso_Putc(this, ((value >> 16) & 0xFF));
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         fbso_PutU32(
        FBSO_DATA		*this,
        const
        uint32_t        value
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_Flag(this,FBSO_FLAG_BIGENDIAN)) {
            fbso_Putc(this, ((value >> 24) & 0xFF));
            fbso_Putc(this, ((value >> 16) & 0xFF));
            fbso_Putc(this, ((value >> 8) & 0xFF));
            fbso_Putc(this, (value & 0xFF));
        }
        else {
            fbso_Putc(this, (value & 0xFF));
            fbso_Putc(this, ((value >> 8) & 0xFF));
            fbso_Putc(this, ((value >> 16) & 0xFF));
            fbso_Putc(this, ((value >> 24) & 0xFF));
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P u t c
    //---------------------------------------------------------------
    
    ERESULT         fbso_Putc(
        FBSO_DATA		*this,
        char            chr
    )
    {
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        iRc = fputc(chr, this->pFile);
        if (iRc == EOF)
            return ERESULT_WRITE_ERROR;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P u t s
    //---------------------------------------------------------------
    
    ERESULT         fbso_Puts(
        FBSO_DATA		*this,
        const
        char            *pStr
    )
    {
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        iRc = fputs(pStr, this->pFile);
        if (iRc == EOF)
            return ERESULT_WRITE_ERROR;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P u t w c
    //---------------------------------------------------------------
    
    ERESULT         fbso_Putwc(
        FBSO_DATA		*this,
        uint32_t        chr
    )
    {
        int             iRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (chr < 128) {
            return fbso_Putc(this, chr);
        }
        iRc = putw(chr, this->pFile);
        if (iRc == EOF)
            return ERESULT_WRITE_ERROR;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      P u t  A S t r
    //---------------------------------------------------------------
    
    ERESULT         fbso_PutStr(
        FBSO_DATA		*this,
        ASTR_DATA       *pStr
    )
    {
        int             iRc;
        const
        char            *pChr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pChr = AStr_getData(pStr);
        while (*pChr) {
            iRc = fputc(*pChr, this->pFile);
            if (iRc == EOF) {
                return ERESULT_WRITE_ERROR;
            }
            ++pChr;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T e l l
    //---------------------------------------------------------------
    
    ERESULT         fbso_Tell(
        FBSO_DATA		*this,
        long            *pFileOffset
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !fbso_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pFileOffset) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        *pFileOffset = ftell(this->pFile);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            fbso_Validate(
        FBSO_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_FBSO) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(FBSO_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


