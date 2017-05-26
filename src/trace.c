// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   trace.c
 *	Generated 06/17/2015 20:19:13
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
#include    "trace_internal.h"
#include    <stdarg.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    
    static
    TRACE_DATA      *pShared = OBJ_NIL;


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/


    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TRACE_DATA *     trace_Alloc(
    )
    {
        TRACE_DATA      *this;
        uint32_t        cbSize = sizeof(TRACE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TRACE_DATA *     trace_Shared(
    )
    {
        
        if (OBJ_NIL == pShared) {
            pShared = trace_Alloc( );
            pShared = trace_InitStream(pShared, stderr);
            trace_setTrace(pShared, true);
        }
        
        return( pShared );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    FILE *          trace_getStream(
        TRACE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->pFileOut;
    }
    
    
    bool            trace_setStream(
        TRACE_DATA      *this,
        FILE            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->pFileOut = pValue;
        return true;
    }
    
    
    bool            trace_getTrace(
        TRACE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->fTrace;
    }

    
    bool            trace_setTrace(
        TRACE_DATA      *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        this->fTrace = value;
        return true;
    }


    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            trace_Dealloc(
        OBJ_ID          objId
    )
    {
        TRACE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->fOpened && this->pFileOut) {
            fclose(this->pFileOut);
            this->pFileOut = NULL;
        }
        
        if (this->pLock) {
            obj_Release(this->pLock);
            this->pLock = OBJ_NIL;
        }

        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TRACE_DATA *   trace_Init(
        TRACE_DATA      *this,
        const
        char            *pszFilePath
    )
    {
        uint32_t        cbSize = sizeof(TRACE_DATA);
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_TRACE );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_TRACE);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&trace_Vtbl);
        
        if (pszFilePath) {
            this->pFileOut = fopen(pszFilePath, "w");
            if (NULL == this->pFileOut) {
                obj_Release(this);
                return OBJ_NIL;
            }
            this->fOpened = true;
        }
        else {
            this->pFileOut = stderr;
            this->fOpened = false;
        }
        
        this->pLock = psxLock_New();

    #ifdef NDEBUG
    #else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pFileOut);
    #endif

        return this;
    }

     
    TRACE_DATA *   trace_InitStream(
        TRACE_DATA      *this,
        FILE            *pTraceFile
    )
    {
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = trace_Init( this, NULL );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        if (this->fOpened) {
            fclose(this->pFileOut);
            this->pFileOut = NULL;
            this->fOpened = false;
        }
        
        if (pTraceFile) {
            this->pFileOut = pTraceFile;
            this->fOpened = false;
        }
        
        return this;
    }
    
    

    //---------------------------------------------------------------
    //						L i n e  O u t
    //---------------------------------------------------------------
    
    void            trace_LineOut(
        TRACE_DATA      *this,
        const
        char            *pszData
    )
    {

        psxLock_Lock(this->pLock);
        if (this->pFileOut) {
            fputs(pszData, this->pFileOut);
        }
        else {
            fprintf(stderr, "%s\n", pszData);
        }
        psxLock_Unlock(this->pLock);
        
    }

    
    //---------------------------------------------------------------
    //						T r a c e  F l a g  A
    //---------------------------------------------------------------
    
    void            trace_FlagA(
        TRACE_DATA		*this,
        bool			flg,
        const
        char			*pszFormat,
        ...
    )
    {
        va_list			pArgs;
        char			Buffer[1024];
        
        // Do initialization.
        if( !this->fTrace ) {
            return;
        }
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        Buffer[0] = '\0';
        
        if( flg ) {
            psxLock_Lock(this->pLock);
            va_start( pArgs, pszFormat );
            vsnprintf( Buffer, sizeof(Buffer), pszFormat, pArgs );
            va_end( pArgs );
            psxLock_Unlock(this->pLock);

            trace_LineOut( this, Buffer );
        }
        
        // Return to caller.
    }
    
    
    
    
    //---------------------------------------------------------------
    //                       F l a g  G e t
    //---------------------------------------------------------------
    
    bool            trace_FlagGet(
        TRACE_DATA		*this,
        uint16_t        index
    )
    {
        uint32_t        i;
        uint32_t        j;
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
            return fRc;
        }
        if (index < NUM_FLAGS)
            ;
        else {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        
        //i = index / 32;			        /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);	    /* horizontal - bit */
        j = (32-1) - (index & 0x1F);
        
        if ( this->flags[i] & (1 << j) ) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        F l a g  S e t
    //---------------------------------------------------------------
    
    ERESULT         trace_FlagSet(
        TRACE_DATA		*this,
        uint16_t        index,
        bool            fValue
    )
    {
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (index < NUM_FLAGS)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        psxLock_Lock(this->pLock);
        //i = index / 32;			        /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);	    /* horizontal - bit */
        j = (32-1) - (index & 0x1F);
        
        if (fValue )
            this->flags[i] |= (1 << j);
        else
            this->flags[i] &= ~(1 << j);
        psxLock_Unlock(this->pLock);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T r a c e
    //---------------------------------------------------------------
    
    void            trace_TraceA(
        TRACE_DATA		*this,
        const
        char			*pszFormat,
        ...
    )
    {
        va_list			pArgs;
        char			Buffer[1024];
        
        // Do initialization.
        if( !this->fTrace ) {
            return;
        }
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        Buffer[0] = '\0';
        
        psxLock_Lock(this->pLock);
        va_start( pArgs, pszFormat );
        vsnprintf( Buffer, sizeof(Buffer), pszFormat, pArgs );
        va_end( pArgs );
        psxLock_Unlock(this->pLock);
        
        trace_LineOut( this, Buffer );
        
    }
    
    
    void            trace_TraceFuncA(
        TRACE_DATA		*this,
        const
        char			*pszFunc,           // __func__
        const
        char			*pszFormat,
        ...
    )
    {
        va_list			pArgs;
        char			Buffer1[512];
        char			Buffer2[512];
        
        // Do initialization.
        if( !this->fTrace ) {
            return;
        }
#ifdef NDEBUG
#else
        if( !trace_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        Buffer2[0] = '\0';
        psxLock_Lock(this->pLock);
        va_start( pArgs, pszFormat );
        vsnprintf( Buffer2, sizeof(Buffer2), pszFormat, pArgs );
        va_end( pArgs );
        snprintf( Buffer1, sizeof(Buffer1), "%s: %s", pszFunc, Buffer2 );
        psxLock_Unlock(this->pLock);
        
        trace_LineOut( this, Buffer1 );
        
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            trace_Validate(
        TRACE_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_TRACE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(TRACE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


