// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   psxSem.c
 *	Generated 02/11/2016 10:46:36
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
#include    <psxSem_internal.h>
#include    <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            psxSem_task_body(
        void            *pData
    )
    {
        //PSXSEM_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PSXSEM_DATA *     psxSem_Alloc(
    )
    {
        PSXSEM_DATA       *this;
        uint32_t        cbSize = sizeof(PSXSEM_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return( this );
    }



    PSXSEM_DATA *     psxSem_New(
        int32_t         start,
        int32_t         max
    )
    {
        PSXSEM_DATA       *this;
        
        this = psxSem_Alloc( );
        if (this) {
            this = psxSem_Init( this, start, max );
        } 
        return( this );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    int32_t         psxSem_getCount(
        PSXSEM_DATA     *this
    )
    {
        int32_t         count = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif

#if defined(__MACOSX_ENV__)
        count = this->count;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        count = 0;      //FIXME:
#endif
        
        return count;
    }

    bool            psxSem_setCount(
        PSXSEM_DATA     *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        this->count = value;
        
        return true;
    }



    ASTR_DATA *     psxSem_getName(
        PSXSEM_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !psxSem_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pName;
    }
    
    
    bool          psxSem_setName(
        PSXSEM_DATA     *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !psxSem_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;
        
        return true;
    }
    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            psxSem_Dealloc(
        OBJ_ID          objId
    )
    {
        PSXSEM_DATA     *this = objId;
#if defined(__MACOSX_ENV__)
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
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#if defined(__MACOSX_ENV__)
        iRc = pthread_cond_destroy(&this->cond);
        if (iRc) {
            DEBUG_BREAK();
        }
        iRc = pthread_mutex_destroy(&this->mutex);
        if (iRc) {
            DEBUG_BREAK();
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        if (this->m_hSem) {
            CloseHandle(this->m_hSem);
            this->m_hSem = NULL;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tRc = tn_sem_delete(&this->sem);
        if( TN_RC_OK == tRc )
            ;
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
        
        if (this->pName) {
            obj_Release(this->pName);
            this->pName = OBJ_NIL;
        }
        
        obj_Dealloc( this );
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PSXSEM_DATA *   psxSem_Init(
        PSXSEM_DATA     *this,
        int32_t         start,
        int32_t         max
    )
    {
        uint32_t        cbSize;
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        uint32_t        num32;
        SYSTEMTIME      time;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tRc;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (PSXSEM_DATA *)obj_Init( this, cbSize, OBJ_IDENT_PSXSEM );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_PSXSEM);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&psxSem_Vtbl);
        
        this->count = start;
        this->max = max;
#if defined(__MACOSX_ENV__)
        this->wakeups = 0;
        iRc = pthread_cond_init(&this->cond,NULL);
        if (iRc) {
            DEBUG_BREAK();
        }
        iRc = pthread_mutex_init(&this->mutex,NULL);
        if (iRc) {
            DEBUG_BREAK();
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        this->pName = AStr_NewA(".SEM32.P");
        num32 = GetCurrentProcessId( );
        AStr_AppendHex32(this->pName, num32);
        AStr_AppendA(this->pName, ".T");
        GetSystemTime(&time);
        num32 = (time.wSecond * 1000) + time.wMilliseconds;
        num32 += time.wMinute * 100000;
        num32 += time.wHour * 10000000;
        AStr_AppendHex32(this->pName, num32);
        
        this->m_hSem =  CreateSemaphore(
                                NULL,                   // Attributes
                                start,                  // Initial Count
                                max,                    // Maximum Count
                                AStr_getData(this->pName)
                        );
        if (this->m_hSem) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tRc = tn_sem_create(&this->sem, start, max);    // FIXME: Dunno if correct.
        if( TN_RC_OK == tRc )
            ;
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#endif

    #ifdef NDEBUG
    #else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
#if defined(__PIC32MX_TNEO_ENV__)
        BREAK_NOT_BOUNDARY4(&this->sem);
#endif
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          P o s t
    //---------------------------------------------------------------
    
    bool            psxSem_Post(
        PSXSEM_DATA		*this
    )
    {
        bool            fRc = false;
#if defined(__MACOSX_ENV__)
//        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        pthread_mutex_lock(&this->mutex);
        if (this->count < this->max) {
            ++this->count;
            if (this->count <= 0) {
                ++this->wakeups;
                //pthread_cond_broadcast(&this->cond);
                pthread_cond_signal(&this->cond);
            }
            fRc = true;
        }
        else {
            fRc = false;
        }
        pthread_mutex_unlock(&this->mutex);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
	    fRc = ReleaseSemaphore(this->m_hSem, 1, NULL);
	    if( !fRc ) {
		    return false;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tRc = tn_sem_signal(&cbp->sem);
        if (TN_RC_OK == tRc)
            fRc = true;
        else {
            DEBUG_BREAK();
        }
#endif
        
        // Return to caller.
        return fRc;
    }
    
    
    bool            psxSem_iPost(
        PSXSEM_DATA		*this
    )
    {
        bool            fRc = false;
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        fRc = psxSem_Post(this);
        return fRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tRc = tn_sem_isignal(&cbp->sem);
        if (TN_RC_OK == tRc)
            ;
        else {
            DEBUG_BREAK();
        }
#endif
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------
    
    bool            psxSem_Reset(
        PSXSEM_DATA		*this
    )
    {
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
      
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        fRc = SetEvent( this->m_hSem );
        if( !fRc ) {
            return false;
        }
#endif
        
        // Return to caller.
        return fRc;
    }

    
    
    //---------------------------------------------------------------
    //                          S i g n a l
    //---------------------------------------------------------------
    
    bool            psxSem_Signal(
        PSXSEM_DATA		*this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
      
        fRc = psxSem_Post(this);
        
        // Return to caller.
        return fRc;
    }
    
    
    bool            psxSem_iSignal(
        PSXSEM_DATA		*this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = psxSem_iPost(this);
        
        // Return to caller.
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     psxSem_ToDebugString(
        PSXSEM_DATA      *this,
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
#if defined(__MACOSX_ENV__)
        pthread_mutex_lock(&this->mutex);
#endif
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(psxSem) count=%d wakeup=%d max=%d",
                     this,
                     this->count,
                     this->wakeups,
                     this->max
            );
#if defined(__MACOSX_ENV__)
        pthread_mutex_unlock(&this->mutex);
#endif
        AStr_AppendA(pStr, str);

        j = snprintf( str, sizeof(str), " %p(psxSem)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            psxSem_Validate(
        PSXSEM_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_PSXSEM) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(PSXSEM_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                          W a i t
    //---------------------------------------------------------------
    
    bool            psxSem_TryWait(
        PSXSEM_DATA		*this
    )
    {
        bool            fRc = false;
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        pthread_mutex_lock(&this->mutex);
        if (this->count <= 0) {
            fRc = false;
        }
        else {
            --this->count;
            if (this->count < 0) {
                do {
                    pthread_cond_wait(&this->cond, &this->mutex);
                } while (this->wakeups < 1);
            }
            --this->wakeups;
            fRc = true;
        }
        pthread_mutex_unlock(&this->mutex);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tRc = tn_sem_wait_polling(&cbp->sem);
        if (TN_RC_OK == tRc) {
            fRc = true;
        }
        else {
            fRc = false;
        }
#endif
        
        // Return to caller.
        return fRc;
    }
    
    
    bool            psxSem_iTryWait(
        PSXSEM_DATA		*this
    )
    {
        bool            fRc = false;
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        fRc = psxSem_Wait(this);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tRc = tn_sem_iwait_polling(&cbp->sem);
        if (TN_RC_OK == tRc)
            fRc = true;
        else {
            fRc = false;
        }
#endif
        
        // Return to caller.
        return fRc;
    }
    
    
    bool            psxSem_Wait(
        PSXSEM_DATA		*this
    )
    {
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
	    ULONG           iRc = 0;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxSem_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        pthread_mutex_lock(&this->mutex);
        --this->count;
        if (this->count < 0) {
            do {
                pthread_cond_wait(&this->cond, &this->mutex);
            } while (this->wakeups < 1);
        }
        --this->wakeups;
        pthread_mutex_unlock(&this->mutex);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        //fprintf(stderr, "psxSem_wait: starting waiting (%d)...\n", GetTickCount());
	    iRc = WaitForSingleObject(this->m_hSem, INFINITE);
        if( iRc == (ULONG)-1 ) {
            fprintf(stderr, "psxSem_wait: wait error %d\n", GetLastError());
            return FALSE;
        }
        //fprintf(stderr, "psxSem_wait: wait is over (%d).\n", GetTickCount());
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tRc = tn_sem_wait(&cbp->sem, TN_WAIT_INFINITE);
        if (TN_RC_OK == tRc)
            ;
        else {
            return false;
        }
#endif
        
        // Return to caller.
        return false;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


