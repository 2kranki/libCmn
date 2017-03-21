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
        TRACE_DATA       *cbp;
        uint32_t        cbSize = sizeof(TRACE_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
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
        TRACE_DATA     *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pFileOut;
    }
    
    
    bool            trace_setStream(
        TRACE_DATA      *cbp,
        FILE            *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        cbp->pFileOut = pValue;
        return true;
    }
    
    
    bool            trace_getTrace(
        TRACE_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        return cbp->fTrace;
    }

    
    bool            trace_setTrace(
        TRACE_DATA      *cbp,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        cbp->fTrace = value;
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
        TRACE_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (cbp->fOpened && cbp->pFileOut) {
            fclose(cbp->pFileOut);
            cbp->pFileOut = NULL;
        }

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TRACE_DATA *   trace_Init(
        TRACE_DATA      *cbp,
        const
        char            *pszFilePath
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbp = obj_Init( cbp, obj_getSize(cbp), OBJ_IDENT_TRACE );
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        obj_setVtbl(cbp, &trace_Vtbl);
        
        if (pszFilePath) {
            cbp->pFileOut = fopen(pszFilePath, "w");
            if (NULL == cbp->pFileOut) {
                obj_Release(cbp);
                return OBJ_NIL;
            }
            cbp->fOpened = true;
        }

    #ifdef NDEBUG
    #else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return cbp;
    }

     
    TRACE_DATA *   trace_InitStream(
        TRACE_DATA      *cbp,
        FILE            *pTraceFile
    )
    {
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbp = obj_Init( cbp, obj_getSize(cbp), OBJ_IDENT_TRACE );
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        obj_setVtbl(cbp, &trace_Vtbl);
        
        if (pTraceFile) {
            cbp->pFileOut = pTraceFile;
            cbp->fOpened = false;
        }
        
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
#endif
        
        return cbp;
    }
    
    

    //---------------------------------------------------------------
    //						L i n e  O u t
    //---------------------------------------------------------------
    
    void            trace_LineOut(
        TRACE_DATA      *cbp,
        const
        char            *pszData
    )
    {
        if (cbp->pFileOut) {
            fputs(pszData, cbp->pFileOut);
        }
        else {
            fprintf(stderr, "%s\n", pszData);
        }
        
    }

    
    //---------------------------------------------------------------
    //						T r a c e  F l a g  A
    //---------------------------------------------------------------
    
    void            trace_FlagA(
        TRACE_DATA		*cbp,
        bool			flg,
        const
        char			*pszFormat,
        ...
    )
    {
        va_list			pArgs;
        char			Buffer[1024];
        
        // Do initialization.
        if( !cbp->fTrace ) {
            return;
        }
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        Buffer[0] = '\0';
        
        if( flg ) {
            va_start( pArgs, pszFormat );
            vsnprintf( Buffer, sizeof(Buffer), pszFormat, pArgs );
            va_end( pArgs );

            trace_LineOut( cbp, Buffer );
        }
        
        // Return to caller.
    }
    
    
    
    
    //---------------------------------------------------------------
    //                       F l a g  G e t
    //---------------------------------------------------------------
    
    bool            trace_FlagGet(
        TRACE_DATA		*cbp,
        uint16_t        index
    )
    {
        uint32_t        i;
        uint32_t        j;
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
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
        
        if ( cbp->flags[i] & (1 << j) ) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        F l a g  S e t
    //---------------------------------------------------------------
    
    ERESULT         trace_FlagSet(
        TRACE_DATA		*cbp,
        uint16_t        index,
        bool            fValue
    )
    {
        uint32_t        i;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
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
        
        //i = index / 32;			        /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);	    /* horizontal - bit */
        j = (32-1) - (index & 0x1F);
        
        if (fValue )
            cbp->flags[i] |= (1 << j);
        else
            cbp->flags[i] &= ~(1 << j);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T r a c e
    //---------------------------------------------------------------
    
    void            trace_TraceA(
        TRACE_DATA		*cbp,
        const
        char			*pszFormat,
        ...
    )
    {
        va_list			pArgs;
        char			Buffer[1024];
        
        // Do initialization.
        if( !cbp->fTrace ) {
            return;
        }
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        Buffer[0] = '\0';
        
        va_start( pArgs, pszFormat );
        vsnprintf( Buffer, sizeof(Buffer), pszFormat, pArgs );
        va_end( pArgs );
        
        trace_LineOut( cbp, Buffer );
        
    }
    
    
    void            trace_TraceFuncA(
        TRACE_DATA		*cbp,
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
        if( !cbp->fTrace ) {
            return;
        }
#ifdef NDEBUG
#else
        if( !trace_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        Buffer2[0] = '\0';
        va_start( pArgs, pszFormat );
        vsnprintf( Buffer2, sizeof(Buffer2), pszFormat, pArgs );
        va_end( pArgs );
        snprintf( Buffer1, sizeof(Buffer1), "%s: %s", pszFunc, Buffer2 );
        
        trace_LineOut( cbp, Buffer1 );
        
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            trace_Validate(
        TRACE_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_TRACE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(TRACE_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


