// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   psxMutex.c
 *	Generated 02/11/2016 10:46:32
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
#include "psxMutex_internal.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            psxMutex_task_body(
        void            *pData
    )
    {
        //PSXMUTEX_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PSXMUTEX_DATA *     psxMutex_Alloc(
    )
    {
        PSXMUTEX_DATA   *this;
        uint32_t        cbSize = sizeof(PSXMUTEX_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    PSXMUTEX_DATA *     psxMutex_New(
    )
    {
        PSXMUTEX_DATA       *this;
        
        this = psxMutex_Alloc( );
        if (this) {
            this = psxMutex_Init( this );
        } 
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================


    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            psxMutex_Dealloc(
        OBJ_ID          objId
    )
    {
        PSXMUTEX_DATA   *this = objId;
        int             iRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !psxMutex_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#if defined(__APPLE__)
        iRc = pthread_mutex_destroy(&this->mutex);
        if (iRc) {
            DEBUG_BREAK();
        }
        obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
#endif
#if defined(_MSC_VER)
#ifdef  USE_MSC_MUTEX
        CloseHandle(this->m_hMutex);
#else
        while( this->LockCount ) {
            (void)psxMutex_Unlock( &this->IntLock );
        }
        DeleteCriticalSection( &this->csSem );
#endif
#endif
        
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PSXMUTEX_DATA * psxMutex_Init(
        PSXMUTEX_DATA   *this
    )
    {
        uint32_t        cbSize;
#if defined(__APPLE__)
        int             iRc;
#endif
#if defined(__TNEO__)
        enum TN_RCode   tnRc;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (PSXMUTEX_DATA *)obj_Init( this, cbSize, OBJ_IDENT_PSXMUTEX );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_PSXMUTEX);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&psxMutex_Vtbl);
       
#if defined(__APPLE__)
        //this->mutex = PTHREAD_MUTEX_INITIALIZER;
        iRc = pthread_mutex_init(&this->mutex, NULL);
        if (iRc) {
            DEBUG_BREAK();
        }
#endif
#if defined(_MSC_VER)
#ifdef  USE_MSC_MUTEX
        this->m_hMutex =    CreateMutex(
                                    NULL,         // default security attributes
                                    FALSE,        // initially not owned
                                    NULL          // unnamed mutex
                            );
        
        if (this->m_hMutex == NULL) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#else
        this->LockCount	= 0;
        InitializeCriticalSection( &this->csSem );
#endif
#endif
#if defined(__TNEO__)
        tnRc = tn_mutex_create(&this->mutex,TN_MUTEX_PROT_INHERIT,0);
        if (tnRc == TN_RC_OK) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif

#ifdef NDEBUG
#else
        if( !psxMutex_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s L o c k e d
    //---------------------------------------------------------------
    
    bool            psxMutex_IsLocked(
        PSXMUTEX_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxMutex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsFlag(this, PSXMUTEX_FLAG_LOCKED))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       L o c k
    //---------------------------------------------------------------
    
    bool            psxMutex_Lock(
        PSXMUTEX_DATA   *this
    )
    {
#if defined(__APPLE__)
        int             iRc;
#endif
#if defined(_MSC_VER)
        DWORD			dwRc;
#endif
#if defined(__TNEO__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxMutex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__APPLE__)
        iRc = pthread_mutex_lock(&this->mutex);
        if (iRc == 0) {
            obj_FlagOn(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
#if defined(_MSC_VER)
#ifdef  USE_MSC_MUTEX
        dwRc = WaitForSingleObject(this->m_hMutex, INFINITE);
        switch (dwRc) {
            case WAIT_OBJECT_0:
                obj_FlagOn(this, PSXMUTEX_FLAG_LOCKED);
                return true;
                break;
                
            case WAIT_ABANDONED:
                break;
                
            case WAIT_TIMEOUT:
                break;
                
            case WAIT_FAILED:
                break;
                
        }
#else
        EnterCriticalSection( &this->csSem );
        ++this->LockCount;
#endif
#endif
#if defined(__TNEO__)
        tnRc = tn_mutex_unlock(&this->mutex);
        if (tnRc == TN_RC_OK) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     psxMutex_ToDebugString(
        PSXMUTEX_DATA   *this,
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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(psxMutex)   %s  ",
                     this,
                     (obj_IsFlag(this,PSXMUTEX_FLAG_LOCKED) ? "Locked" : "Unlocked")
            );
        AStr_AppendA(pStr, str);

        j = snprintf( str, sizeof(str), " %p(psxMutex)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T r y  L o c k
    //---------------------------------------------------------------
    
    bool            psxMutex_TryLock(
        PSXMUTEX_DATA	*this
    )
    {
#if defined(__APPLE__)
        int             iRc;
#endif
#if defined(_MSC_VER)
        DWORD			dwRc;
#endif
#if defined(__TNEO__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxMutex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__APPLE__)
        iRc = pthread_mutex_trylock(&this->mutex);
        if (iRc == 0) {
            obj_FlagOn(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
#if defined(_MSC_VER)
#ifdef  USE_MSC_MUTEX
        dwRc = WaitForSingleObject(this->m_hMutex, 0);
        switch (dwRc) {
            case WAIT_OBJECT_0:
                obj_FlagOn(this, PSXMUTEX_FLAG_LOCKED);
                return true;
                break;
                
            case WAIT_ABANDONED:
                break;
                
            case WAIT_TIMEOUT:
                break;
                
            case WAIT_FAILED:
                break;
                
        }
#else
        if (this->LockCount == 0) {
            EnterCriticalSection( &this->csSem );
            ++this->LockCount;
        }
#endif
#endif
#if defined(__TNEO__)
        tnRc = tn_mutex_lock_polling(&this->mutex);
        if (tnRc == TN_RC_OK) {
            obj_FlagOn(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       U n l o c k
    //---------------------------------------------------------------
    
    bool            psxMutex_Unlock(
        PSXMUTEX_DATA		*this
    )
    {
#if defined(__APPLE__)
        int                 iRc;
#endif
#if defined(__TNEO__)
        enum TN_RCode       tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxMutex_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__APPLE__)
        iRc = pthread_mutex_unlock(&this->mutex);
        if (iRc == 0) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
#if defined(_MSC_VER)
#ifdef  USE_MSC_MUTEX
        if (ReleaseMutex(this->m_hMutex)) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#else
        --this->LockCount;
        LeaveCriticalSection( &this->csSem );
#endif
#endif
#if defined(__TNEO__)
        tnRc = tn_mutex_unlock(&this->mutex);
        if (tnRc == TN_RC_OK) {
            obj_FlagOff(this, PSXMUTEX_FLAG_LOCKED);
            return true;
        }
#endif
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            psxMutex_Validate(
        PSXMUTEX_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_PSXMUTEX) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(PSXMUTEX_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


