// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   psxCond.c
 *	Generated 07/05/2016 10:02:43
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
#include    <psxCond_internal.h>
#include    <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            psxCond_task_body(
        void            *pData
    )
    {
        //PSXCOND_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PSXCOND_DATA *     psxCond_Alloc(
    )
    {
        PSXCOND_DATA       *this;
        uint32_t        cbSize = sizeof(PSXCOND_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    PSXCOND_DATA *     psxCond_New(
        PSXMUTEX_DATA   *pMutex
    )
    {
        PSXCOND_DATA    *this;
        
        this = psxCond_Alloc( );
        if (this) {
            this = psxCond_Init(this, pMutex);
        } 
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        psxCond_getPriority(
        PSXCOND_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !psxCond_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            psxCond_setPriority(
        PSXCOND_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !psxCond_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }



    uint32_t        psxCond_getSize(
        PSXCOND_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !psxCond_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                      B r o a d c a s t
    //---------------------------------------------------------------
    
    bool            psxCond_Broadcast(
        PSXCOND_DATA    *this
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        bool            fRc;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxCond_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        fRc = psxMutex_IsLocked(this->pMutex);
        if (!fRc) {
            DEBUG_BREAK();
            return false;
        }
        iRc = pthread_cond_broadcast(&this->cond);
        if (!(iRc == 0)) {
            DEBUG_BREAK();
            return false;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_unlock(&this->mutex);
        if (tnRc == TN_RC_OK) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        WakeAllConditionVariable(&this->cvCondEmpty);
        WakeAllConditionVariable(&this->cvCondFull);
        Sleep(500);
#endif
#endif

        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            psxCond_Dealloc(
        OBJ_ID          objId
    )
    {
        PSXCOND_DATA    *this = objId;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !psxCond_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (obj_IsFlag(this, PSXCOND_FLAG_COND_INIT)) {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
            iRc = pthread_cond_destroy(&this->cond);
            if (iRc) {
                DEBUG_BREAK();
            }
            obj_FlagOff(this, PSXCOND_FLAG_COND_INIT);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
        }
        
        if (this->pMutex) {
            obj_Release(this->pMutex);
            this->pMutex = OBJ_NIL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        //this->pOBJ->iVtbl.pDealloc( this );  // Needed for Inheritance
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            psxCond_Disable(
        PSXCOND_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !psxCond_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            psxCond_Enable(
        PSXCOND_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !psxCond_Validate( this ) ) {
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

    PSXCOND_DATA *   psxCond_Init(
        PSXCOND_DATA    *this,
        PSXMUTEX_DATA   *pMutex
    )
    {
        uint32_t        cbSize = sizeof(PSXCOND_DATA);
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
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

        this = (OBJ_ID)obj_Init( this, cbSize, OBJ_IDENT_PSXCOND );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_PSXCOND); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&psxCond_Vtbl);
        
        obj_Retain(pMutex);
        this->pMutex = pMutex;
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        // this->cond = PTHREAD_COND_INITIALIZER;
        iRc = pthread_cond_init(&this->cond, NULL);
        if (iRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_FlagOn(this, PSXCOND_FLAG_COND_INIT);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        InitializeCriticalSection(&this->csMutex);
        InitializeConditionVariable(&this->cvCondEmpty);
        InitializeConditionVariable(&this->cvCondFull);
#endif
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_create(&this->mutex,TN_MUTEX_PROT_INHERIT,0);
        if (tnRc == TN_RC_OK) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
        
    #ifdef NDEBUG
    #else
        if( !psxCond_Validate( this ) ) {
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
    
    bool            psxCond_IsEnabled(
        PSXCOND_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxCond_Validate( this ) ) {
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
    //                      S i g n a l
    //---------------------------------------------------------------
    
    bool            psxCond_Signal(
        PSXCOND_DATA    *this
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        bool            fRc;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxCond_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        fRc = psxMutex_IsLocked(this->pMutex);
        if (!fRc) {
            DEBUG_BREAK();
            return false;
        }
        iRc = pthread_cond_signal(&this->cond);
        if (!(iRc == 0)) {
            DEBUG_BREAK();
            return false;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_unlock(&this->mutex);
        if (tnRc == TN_RC_OK) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        LeaveCriticalSection(&this->csMutex);
        WakeConditionVariable(&this->cvCondFull);
#endif

        // Return to caller.
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     psxCond_ToDebugString(
        PSXCOND_DATA      *this,
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
                     "{%p(psxCond) size=%d ",
                     this,
                     psxCond_getSize(this)
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
        
        j = snprintf( str, sizeof(str), " %p(psxCond)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            psxCond_Validate(
        PSXCOND_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_PSXCOND) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(PSXCOND_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                          W a i t
    //---------------------------------------------------------------
    
    bool            psxCond_Wait(
        PSXCOND_DATA    *this
    )
    {
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        bool            fRc;
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxCond_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
        fRc = psxMutex_IsLocked(this->pMutex);
        if (!fRc) {
            DEBUG_BREAK();
            return false;
        }
        iRc = pthread_cond_wait(&this->cond, &this->pMutex->mutex);
        if (!(iRc == 0)) {
            DEBUG_BREAK();
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        EnterCriticalSection(&this->csMutex);
        while(cb_NumEntries(this) == 0) {
            if (obj_Flag(this, CB_FLAG_PAUSE)) {
                LeaveCriticalSection(&this->csMutex);
                return false;
            }
            SleepConditionVariableCS(&this->cvCondFull, &this->csMutex, INFINITE);
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_unlock(&this->mutex);
        if (!(tnRc == TN_RC_OK)) {
            return false;
        }
#endif
        
        // Return to caller.
        return true;
    }
    
    
    

    
    
#ifdef	__cplusplus
}
#endif


