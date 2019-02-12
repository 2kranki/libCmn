// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   psxLock.c
 *	Generated 05/19/2017 21:15:36
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
#include    <psxLock_internal.h>
#include    <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            psxLock_task_body(
        void            *pData
    )
    {
        //PSXLOCK_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PSXLOCK_DATA *  psxLock_Alloc(
    )
    {
        PSXLOCK_DATA    *this;
        uint32_t        cbSize = sizeof(PSXLOCK_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PSXLOCK_DATA *     psxLock_New(
    )
    {
        PSXLOCK_DATA       *this;
        
        this = psxLock_Alloc( );
        if (this) {
            this = psxLock_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    
    
    
    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = psxLock__Assign(this,pOther);
     @endcode
     @param     this    PSXLOCK object pointer
     @param     pOther  a pointer to another PSXLOCK object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         psxLock_Assign(
        PSXLOCK_DATA		*this,
        PSXLOCK_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !psxLock_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

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

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
    eom:
        return ERESULT_NOT_IMPLEMENTED;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        psxLock      *pCopy = psxLock_Copy(this);
     @endcode
     @param     this    PSXLOCK object pointer
     @return    If successful, a PSXLOCK object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the PSXLOCK object.
     */
    PSXLOCK_DATA *     psxLock_Copy(
        PSXLOCK_DATA       *this
    )
    {
        PSXLOCK_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = psxLock_New( );
        if (pOther) {
            eRc = psxLock_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            psxLock_Dealloc(
        OBJ_ID          objId
    )
    {
        PSXLOCK_DATA   *this = objId;
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#if defined(__MACOSX_ENV__)
        iRc = pthread_mutex_destroy(&this->mutex);
        if (iRc) {
            DEBUG_BREAK();
        }
        obj_FlagOff(this, PSXLOCK_FLAG_LOCKED);
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        DeleteCriticalSection( &this->csSem );
#endif

        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PSXLOCK_DATA *   psxLock_Init(
        PSXLOCK_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(PSXLOCK_DATA);
#if defined(__MACOSX_ENV__)
        int             iRc;
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PSXLOCK);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_PSXLOCK);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&psxLock_Vtbl);
        
        obj_FlagOff(this, PSXLOCK_FLAG_LOCKED);
#if defined(__MACOSX_ENV__)
        //this->mutex = PTHREAD_MUTEX_INITIALIZER;
        iRc = pthread_mutex_init(&this->mutex, NULL);
        if (iRc) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
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
            return OBJ_NIL;
        }
#endif

    #ifdef NDEBUG
    #else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //fprintf(stderr, "offsetof(eRc) = %lu\n", offsetof(PSXLOCK_DATA,eRc));
        //fprintf(stderr, "sizeof(PSXLOCK_DATA) = %lu\n", sizeof(PSXLOCK_DATA));
        BREAK_NOT_BOUNDARY4(sizeof(PSXLOCK_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s L o c k e d
    //---------------------------------------------------------------
    
    bool            psxLock_IsLocked(
        PSXLOCK_DATA	*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsFlag(this, PSXLOCK_FLAG_LOCKED)) {
            return true;
        }
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                          L o c k
    //---------------------------------------------------------------
    
    bool            psxLock_Lock(
        PSXLOCK_DATA	*this
    )
    {
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        iRc = pthread_mutex_lock(&this->mutex);
        if (iRc == 0)
            ;
        else {
            return false;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        EnterCriticalSection( &this->csSem );
#endif
        
        // Return to caller.
        obj_FlagOn(this, PSXLOCK_FLAG_LOCKED);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = psxLock_ToDebugString(this,4);
     @endcode
     @param     this    PSXLOCK object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     psxLock_ToDebugString(
        PSXLOCK_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(psxLock)\n",
                     this
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
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(psxLock)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                         T r y L o c k
    //---------------------------------------------------------------
    
    bool            psxLock_TryLock(
        PSXLOCK_DATA	*this
    )
    {
#if defined(__MACOSX_ENV__)
        int             iRc;
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        int             iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode   tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        iRc = pthread_mutex_trylock(&this->mutex);
        if (iRc) {
            return false;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        iRc = TryEnterCriticalSection( &this->csSem );
        if (iRc)
            ;
        else {
            obj_setLastError(this, ERESULT_BUSY);
            return false;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_lock_polling(&this->mutex);
        if (tnRc == TN_RC_OK)
            ;
        else {
            obj_setLastError(this, ERESULT_BUSY);
            return false;
        }
#endif
        
        // Return to caller.
        obj_FlagOn(this, PSXLOCK_FLAG_LOCKED);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        U n l o c k
    //---------------------------------------------------------------
    
    bool            psxLock_Unlock(
        PSXLOCK_DATA	*this
    )
    {
#if defined(__MACOSX_ENV__)
        int                 iRc;
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        enum TN_RCode       tnRc;
#endif
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !psxLock_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
#if defined(__MACOSX_ENV__)
        iRc = pthread_mutex_unlock(&this->mutex);
        if (iRc == 0) {
        }
        else {
            return false;
        }
#endif
#if defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
        if (obj_IsFlag(this, PSXLOCK_FLAG_LOCKED)) {
            LeaveCriticalSection( &this->csSem );
        }
        else {
            obj_setLastError(this, ERESULT_NOT_BUSY);
            return false;
        }
#endif
#if defined(__PIC32MX_TNEO_ENV__)
        tnRc = tn_mutex_unlock(&this->mutex);
        if (tnRc == TN_RC_OK) {
        }
        else {
            obj_setLastError(this, ERESULT_NOT_BUSY);
            return false;
        }
#endif
        
        // Return to caller.
        obj_FlagOff(this, PSXLOCK_FLAG_LOCKED);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            psxLock_Validate(
        PSXLOCK_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_PSXLOCK) )
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


        if( !(obj_getSize(this) >= sizeof(PSXLOCK_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


