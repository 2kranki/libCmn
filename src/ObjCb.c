// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjCb.c
 *	Generated 02/21/2020 14:01:14
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
#include        <ObjCb_internal.h>
#include        <psxThread.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ObjCb_task_body (
        void            *pData
    )
    {
        //OBJCB_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJCB_DATA *     ObjCb_Alloc (
        void
    )
    {
        OBJCB_DATA       *this;
        uint32_t        cbSize = sizeof(OBJCB_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJCB_DATA *     ObjCb_New (
        void
    )
    {
        OBJCB_DATA       *this;
        
        this = ObjCb_Alloc( );
        if (this) {
            this = ObjCb_Init(this);
        } 
        return this;
    }



    OBJCB_DATA *     ObjCb_NewWithSize (
        uint32_t        max            // Maximum Number of Elements in Circular Buffer
    )
    {
        OBJCB_DATA      *this;
        ERESULT         eRc;

        this = ObjCb_New( );
        if (this) {
            eRc = ObjCb_Setup(this, max);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                return OBJ_NIL;
            }
        }

        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         E m p t y
    //---------------------------------------------------------------

    PSXCOND_DATA *  ObjCb_getEmpty (
        OBJCB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pEmpty;
    }


    bool            ObjCb_setEmpty (
        OBJCB_DATA     *this,
        PSXCOND_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pEmpty) {
            obj_Release(this->pEmpty);
        }
        this->pEmpty = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         F u l l
    //---------------------------------------------------------------

    PSXCOND_DATA *  ObjCb_getFull (
        OBJCB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pFull;
    }


    bool            ObjCb_setFull (
        OBJCB_DATA     *this,
        PSXCOND_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pFull) {
            obj_Release(this->pFull);
        }
        this->pFull = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         M u t e x
    //---------------------------------------------------------------

    PSXMUTEX_DATA * ObjCb_getMutex (
        OBJCB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pMutex;
    }


    bool            ObjCb_setMutex (
        OBJCB_DATA     *this,
        PSXMUTEX_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pMutex) {
            obj_Release(this->pMutex);
        }
        this->pMutex = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjCb_getSize (
        OBJCB_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cEntries;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ObjCb_getSuperVtbl (
        OBJCB_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

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
        ERESULT eRc = ObjCb_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJCB object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjCb_Assign (
        OBJCB_DATA		*this,
        OBJCB_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjCb_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

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
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             ObjCb_Compare (
        OBJCB_DATA      *this,
        OBJCB_DATA      *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!ObjCb_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ObjCb      *pCopy = ObjCb_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJCB object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJCB_DATA *     ObjCb_Copy (
        OBJCB_DATA       *this
    )
    {
        OBJCB_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OBJCB_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = ObjCb_New( );
        if (pOther) {
            eRc = ObjCb_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        C o u n t
    //---------------------------------------------------------------

    uint32_t        ObjCb_Count (
        OBJCB_DATA      *this
    )
    {
        uint16_t        count;
        bool            fRc;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjCb_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        fRc = psxMutex_Lock(this->pMutex);
        count = (uint16_t)(this->numWritten - this->numRead);
        fRc = psxMutex_Unlock(this->pMutex);

        // Return to caller.
        return  count;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ObjCb_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJCB_DATA      *this = objId;
        uint32_t        i;
        OBJ_ID          pObj;
        bool            fRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJCB_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            this->fStop = true;
            fRc = psxCond_Broadcast(this->pEmpty);
            fRc = psxCond_Broadcast(this->pFull);
            fRc = psxMutex_Unlock(this->pMutex);
        }
        psxThread_Wait(1000);

        ObjCb_setEmpty(this, OBJ_NIL);
        ObjCb_setFull(this, OBJ_NIL);
        ObjCb_setMutex(this, OBJ_NIL);          // Unlock and free mutex.

        for (i=0; i<this->cEntries; ++i) {
            pObj = this->pEntries[i];
            if (pObj) {
                obj_Release(pObj);
                this->pEntries[i] = OBJ_NIL;
            }
        }

        if (this->pEntries) {
            mem_Free(this->pEntries);
            this->pEntries = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ObjCb      *pDeepCopy = ObjCb_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJCB object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJCB_DATA *     ObjCb_DeepyCopy (
        OBJCB_DATA       *this
    )
    {
        OBJCB_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjCb_New( );
        if (pOther) {
            eRc = ObjCb_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjCb_Disable (
        OBJCB_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjCb_Enable (
        OBJCB_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                            G e t
    //---------------------------------------------------------------

    bool            ObjCb_Get (
        OBJCB_DATA      *this,
        OBJ_ID          *ppData
    )
    {
        bool            fRc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !ObjCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->fStop) {
            return false;
        }

        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            while (((this->numWritten - this->numRead) == 0) && !this->fStop) {
                fRc = psxCond_Wait(this->pFull);
            }
        }

        if ( (ppData == NULL) || (((this->numWritten - this->numRead)) == 0) ) {
            fRc = false;
        }
        else {
            *ppData = this->pEntries[this->start];
            this->pEntries[this->start] = OBJ_NIL;
            // below needed if multi-processor (??)
            //__sync_fetch_and_add( &this->numRead, 1 );
            ++this->numRead;
            ++this->start;
            if (this->start == this->cEntries) {
                this->start = 0;
            }
            fRc = true;
        }

        if (fRc) {
            fRc = psxCond_Signal(this->pEmpty);
        }
        fRc = psxMutex_Unlock(this->pMutex);

        return fRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJCB_DATA *   ObjCb_Init (
        OBJCB_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJCB_DATA);
        //ERESULT         eRc;
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJCB);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjCb_Vtbl);
        
        this->pMutex = psxMutex_New();
        if (OBJ_NIL == this->pMutex) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pEmpty = psxCond_New(this->pMutex);
        if (OBJ_NIL == this->pEmpty) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pFull = psxCond_New(this->pMutex);
        if (OBJ_NIL == this->pFull) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "ObjCb::sizeof(OBJCB_DATA) = %lu\n", 
                sizeof(OBJCB_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJCB_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E m p t y
    //---------------------------------------------------------------

    bool            ObjCb_IsEmpty (
        OBJCB_DATA         *this
    )
    {
        bool            fRc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !ObjCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (((uint16_t)(this->numWritten - this->numRead)) == 0) {
            fRc = true;
        }

        return fRc;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjCb_IsEnabled (
        OBJCB_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s F u l l
    //---------------------------------------------------------------

    bool            ObjCb_IsFull (
        OBJCB_DATA       *this
    )
    {
        bool            fRc = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !ObjCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if ( ((uint16_t)(this->numWritten - this->numRead)) == this->cEntries )
            fRc = true;

        return fRc;
    }



    //---------------------------------------------------------------
    //                       P a u s e
    //---------------------------------------------------------------

    bool            ObjCb_Pause (
        OBJCB_DATA      *this
    )
    {
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !ObjCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
            this->fStop = 1;
            fRc = psxCond_Broadcast(this->pEmpty);
            fRc = psxCond_Broadcast(this->pFull);
            fRc = psxMutex_Unlock(this->pMutex);
        }

        return true;
    }



    //---------------------------------------------------------------
    //                            P u t
    //---------------------------------------------------------------

    bool            ObjCb_Put (
        OBJCB_DATA      *this,
        OBJ_ID          pValue
    )
    {
        bool            fRc = false;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if ( !ObjCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        if (this->fStop) {
            return false;
        }
        fRc = psxMutex_Lock(this->pMutex);
        while (((this->numWritten - this->numRead) == this->cEntries) && !this->fStop) {
            fRc = psxCond_Wait(this->pEmpty);
        }

        if ( ((uint16_t)(this->numWritten - this->numRead)) == this->cEntries ) {
            fRc = false;
        }
        else {
            obj_Retain(pValue);
            this->pEntries[this->end] = pValue;
            ++this->numWritten;
            ++this->end;
            if (this->end == this->cEntries) {
                this->end = 0;
            }
            fRc = true;
        }

        if (fRc) {
            psxCond_Signal(this->pFull);
        }
        psxMutex_Unlock(this->pMutex);

        return fRc;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = ObjCb_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjCb", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjCb_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJCB_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJCB_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjCb_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return ObjCb_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjCb_Enable;
                        }
                        break;

#ifdef  OBJCB_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return ObjCb_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return ObjCb_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjCb_ToDebugString;
                        }
#ifdef  OBJCB_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjCb_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjCb_ToDebugString)
                    return "ToDebugString";
#ifdef  OBJCB_JSON_SUPPORT
                if (pData == ObjCb_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       S e t u p
    //---------------------------------------------------------------

    /*!
     Set up this object for operation.
     @param     this    object pointer
     @param     max     Maximum Number of Objects in Circular Buffer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjCb_Setup (
        OBJCB_DATA      *this,
        uint32_t        max             // Maximum Number of Objects in Buffer
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pEntries)
            ;
        else {
            return ERESULT_GENERAL_FAILURE;
        }
#endif

        this->pEntries = mem_Malloc(max * sizeof(OBJ_ID));
        if (NULL == this->pEntries) {
            return ERESULT_OUT_OF_MEMORY;
        }
        this->cEntries = max;

        // Put code here...

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       R e s u m e
    //---------------------------------------------------------------

    bool            ObjCb_Resume (
        OBJCB_DATA      *this
    )
    {
        bool            fRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if ( !ObjCb_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        fRc = psxMutex_Lock(this->pMutex);
        this->fStop = 0;
        fRc = psxMutex_Unlock(this->pMutex);

        return true;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjCb_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjCb_ToDebugString (
        OBJCB_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjCb_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    ObjCb_getSize(this),
                    obj_getRetainCount(this)
            );

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
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            ObjCb_Validate (
        OBJCB_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJCB))
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


        if (!(obj_getSize(this) >= sizeof(OBJCB_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


