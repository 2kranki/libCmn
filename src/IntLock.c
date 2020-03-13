// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   IntLock.c
 *	Generated 03/13/2020 09:43:27
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
#include        <IntLock.h>






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

    INTLOCK_DATA *  IntLock_Alloc (
        void
    )
    {
        INTLOCK_DATA    *this;
        uint32_t        cbSize = sizeof(INTLOCK_DATA);
        
        // Do initialization.
        
         this = mem_Calloc(1, cbSize);
         this->fAlloc = true;
        
        // Return to caller.
        return this;
    }



    INTLOCK_DATA *  IntLock_Free (
        INTLOCK_DATA	*this
    )
    {
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
        
        if (this->fLocked) {
            IntLock_Unlock(this);
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = pthread_mutex_destroy(&this->mutex);
        if (iRc) {
            DEBUG_BREAK();
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        DeleteCriticalSection( &this->csSem );
#endif

        if (this->fAlloc) {
            mem_Free(this);
        }
        this = OBJ_NIL;
        
        return this;
    }



    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    INTLOCK_DATA *   IntLock_Init (
        INTLOCK_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(INTLOCK_DATA);
        //ERESULT         eRc;
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        //this->mutex = PTHREAD_MUTEX_INITIALIZER;
        iRc = pthread_mutex_init(&this->mutex, NULL);
        if (iRc) {
            DEBUG_BREAK();
            obj_Release(this);
            this = OBJ_NIL;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        InitializeCriticalSection( &this->csSem );
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_create(&this->mutex, TN_MUTEX_PROT_INHERIT, 0);
        if (tnRc == TN_RC_OK) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            this = OBJ_NIL;
        }
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      L o c k
    //---------------------------------------------------------------

    ERESULT         IntLock_Lock (
        INTLOCK_DATA	*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif

        // Do not allow a double locked situation.
        if (this->fLocked) {
            return eRc;
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = pthread_mutex_lock(&this->mutex);
        if (iRc == 0)
            ;
        else {
            eRc = ERESULT_GENERAL_FAILURE;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        EnterCriticalSection( &this->csSem );
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_lock(&this->mutex);
        if (tnRc == TN_RC_OK)
            ;
        else {
            eRc = ERESULT_BUSY;
        }
#endif
        if (ERESULT_OK(eRc))
            this->fLocked = true;
         
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      T r y L o c k
    //---------------------------------------------------------------
    
    ERESULT         IntLock_TryLock (
        INTLOCK_DATA	*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
       
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = pthread_mutex_trylock(&this->mutex);
        if (iRc) {
            eRc = ERESULT_BUSY;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        iRc = TryEnterCriticalSection( &this->csSem );
        if (iRc)
            ;
        else {
            eRc = ERESULT_BUSY;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_lock_polling(&this->mutex);
        if (tnRc == TN_RC_OK)
            ;
        else {
            eRc = ERESULT_BUSY;
        }
#endif
        if (ERESULT_OK(eRc))
            this->fLocked = true;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      U n l o c k
    //---------------------------------------------------------------

    ERESULT         IntLock_Unlock (
        INTLOCK_DATA	*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif

        // Do not allow a double locked situation.
        if (!this->fLocked) {
            return eRc;
        }

#if defined(__MACOS32_ENV__) || defined(__MACOS64_ENV__)
        iRc = pthread_mutex_unlock(&this->mutex);
        if (iRc == 0)
            ;
        else {
            eRc = ERESULT_GENERAL_FAILURE;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        LeaveCriticalSection( &this->csSem );
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_unlock(&this->mutex);
        if (tnRc == TN_RC_OK) 
            ;
        else {
            eRc = ERESULT_GENERAL_FAILURE;
        }
#endif
        if (ERESULT_OK(eRc))
            this->fLocked = false;
         
        // Return to caller.
        return eRc;
    }



    
#ifdef	__cplusplus
}
#endif


