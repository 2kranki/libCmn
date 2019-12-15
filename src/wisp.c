// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   wisp.c
 *	Generated 08/04/2018 08:13:16
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
#include        <wisp_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            wisp_task_body(
        void            *pData
    )
    {
        //WISP_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    WISP_DATA *     wisp_Alloc(
        void
    )
    {
        WISP_DATA       *this;
        uint32_t        cbSize = sizeof(WISP_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    WISP_DATA *     wisp_New(
        void
    )
    {
        WISP_DATA       *this;
        
        this = wisp_Alloc( );
        if (this) {
            this = wisp_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        wisp_getPriority(
        WISP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            wisp_setPriority(
        WISP_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        wisp_getSize(
        WISP_DATA       *this
    )
    {
        uint32_t        size;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        size = u32Array_getSize(this->pMem);
        size = size >> 1;
        
        return size;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * wisp_getStr(
        WISP_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        wisp_setStr(
        WISP_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  wisp_getSuperVtbl(
        WISP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
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
        ERESULT eRc = wisp__Assign(this,pOther);
     @endcode 
     @param     this    WISP object pointer
     @param     pOther  a pointer to another WISP object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         wisp_Assign(
        WISP_DATA		*this,
        WISP_DATA       *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !wisp_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         wisp_Compare(
        WISP_DATA     *this,
        WISP_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !wisp_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o n s t r u c t
    //---------------------------------------------------------------
    
    ERESULT         wisp_Cons(
        WISP_DATA       *this,
        uint32_t        e1,
        uint32_t        e2,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;
        uint32_t        index;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = u32Array_AppendData(this->pMem, e1);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        index = u32Array_getSize(this->pMem);
        eRc = u32Array_AppendData(this->pMem, e2);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }
        index = (index >> 1) + 1;

        // Return to caller.
        if (pIndex)
            *pIndex = index;
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        wisp      *pCopy = wisp_Copy(this);
     @endcode 
     @param     this    WISP object pointer
     @return    If successful, a WISP object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the WISP object.
     */
    WISP_DATA *     wisp_Copy(
        WISP_DATA       *this
    )
    {
        WISP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = wisp_New( );
        if (pOther) {
            eRc = wisp_Assign(this, pOther);
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

    void            wisp_Dealloc(
        OBJ_ID          objId
    )
    {
        WISP_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((WISP_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        wisp_setStr(this, OBJ_NIL);
        if (this->pMem) {
            obj_Release(this->pMem);
            this->pMem = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         wisp_Disable(
        WISP_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !wisp_Validate(this) ) {
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

    ERESULT         wisp_Enable(
        WISP_DATA       *this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !wisp_Validate(this) ) {
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
    //                          G e t
    //---------------------------------------------------------------
    
    bool            wisp_GetAtom(
        WISP_DATA       *this,
        uint32_t        index
    )
    {
        uint32_t        idx = 0;
        uint32_t        value = 0;
        bool            fRc = false;
        
        // Do initialization.
        idx = ((index - 1) << 1) + 1;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            //obj_setLastError(this, ERESULT_SUCCESS);
            return fRc;
        }
        if (idx && (idx < u32Array_getSize(this->pMem)))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
            
        value = u32Array_Get(this->pMem, idx) & 0x80000000;
        if (value) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
            
            
    bool            wisp_GetBP(
        WISP_DATA       *this,
        uint32_t        index
    )
    {
        uint32_t        idx = 0;
        uint32_t        value = 0;
        bool            fRc = false;
        
        // Do initialization.
        idx = ((index - 1) << 1) + 2;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            //obj_setLastError(this, ERESULT_SUCCESS);
            return fRc;
        }
        if (idx && (idx <= u32Array_getSize(this->pMem)))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return fRc;
        }
#endif
        
        value = u32Array_Get(this->pMem, idx) & 0x80000000;
        if (value) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
    
    
    uint32_t        wisp_GetCAR(
        WISP_DATA       *this,
        uint32_t        index
    )
    {
        uint32_t        idx = 0;
        uint32_t        car = 0;

        // Do initialization.
        idx = ((index - 1) << 1) + 1;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            //obj_setLastError(this, ERESULT_SUCCESS);
            return car;
        }
        if (idx && (idx < u32Array_getSize(this->pMem)))
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return car;
        }
#endif
        
        car = u32Array_Get(this->pMem, idx) & 0x7FFFFFFF;
        
        // Return to caller.
        return car;
    }
    
    
    uint32_t        wisp_GetCDR(
        WISP_DATA       *this,
        uint32_t        index
    )
    {
        uint32_t        idx = 0;
        uint32_t        cdr = 0;

        // Do initialization.
        idx = ((index - 1) << 1) + 2;
    #ifdef NDEBUG
    #else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            //obj_setLastError(this, ERESULT_SUCCESS);
            return cdr;
        }
        if (idx && (idx <= u32Array_getSize(this->pMem)))
            ;
            else {
                DEBUG_BREAK();
                //return ERESULT_INVALID_PARAMETER;
                return cdr;
            }
    #endif
        
        cdr = u32Array_Get(this->pMem, idx) & 0x7FFFFFFF;

        // Return to caller.
        return cdr;
    }
                    
                    

    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    WISP_DATA *     wisp_Init(
        WISP_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(WISP_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_WISP);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_WISP);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&wisp_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );
        
        this->pMem = u32Array_New( );
        if (OBJ_NIL == this->pMem) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "wisp::sizeof(WISP_DATA) = %lu\n", sizeof(WISP_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(WISP_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         wisp_IsEnabled(
        WISP_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
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
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         wisp_SetAtom(
        WISP_DATA       *this,
        uint32_t        index,
        bool            fValue
    )
    {
        ERESULT         eRc;
        uint32_t        idx = 0;
        uint32_t        car = 0;
        
        // Do initialization.
        idx = ((index - 1) << 1) + 1;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (idx && (idx < u32Array_getSize(this->pMem)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        car = u32Array_Get(this->pMem, idx) & 0x7FFFFFFF;
        if (fValue) {
            car |= 0x80000000;
        }
        eRc = u32Array_SetData(this->pMem, idx, car);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         wisp_SetBP(
        WISP_DATA       *this,
        uint32_t        index,
        bool            fValue
    )
    {
        ERESULT         eRc;
        uint32_t        idx = 0;
        uint32_t        cdr = 0;
        
        // Do initialization.
        idx = ((index - 1) << 1) + 2;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (idx && (idx <= (u32Array_getSize(this->pMem) >> 1)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        cdr = u32Array_Get(this->pMem, idx) & 0x7FFFFFFF;
        if (fValue) {
            cdr |= 0x80000000;
        }
        eRc = u32Array_SetData(this->pMem, idx, cdr);

        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         wisp_SetCAR(
        WISP_DATA       *this,
        uint32_t        index,
        uint32_t        value
    )
    {
        ERESULT         eRc;
        uint32_t        idx = 0;
        uint32_t        car = 0;

        // Do initialization.
        idx = ((index - 1) << 1) + 1;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (idx && (idx < u32Array_getSize(this->pMem)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        car = u32Array_Get(this->pMem, idx) & 0x80000000;
        car |= value & 0x7FFFFFFF;
        eRc = u32Array_SetData(this->pMem, idx, car);

        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         wisp_SetCDR(
        WISP_DATA       *this,
        uint32_t        index,
        uint32_t        value
    )
    {
        ERESULT         eRc;
        uint32_t        idx = 0;
        uint32_t        cdr = 0;

        // Do initialization.
        idx = ((index - 1) << 1) + 2;
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (idx && (idx <= u32Array_getSize(this->pMem)))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        cdr = u32Array_Get(this->pMem, idx) & 0x80000000;
        cdr |= value & 0x7FFFFFFF;
        eRc = u32Array_SetData(this->pMem, idx, cdr);

        // Return to caller.
        return eRc;
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
        void        *pMethod = wisp_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "wisp", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          wisp_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        WISP_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)wisp_Class();
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
                            return wisp_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return wisp_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return wisp_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return wisp_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == wisp_ToDebugString)
                    return "ToDebugString";
                if (pData == wisp_ToJSON)
                    return "ToJson";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = wisp_ToDebugString(this,4);
     @endcode 
     @param     this    WISP object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     wisp_ToDebugString(
        WISP_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    wisp_getSize(this)
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
    
    
    
    ASTR_DATA *     wisp_ToJSON(
        WISP_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !wisp_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            wisp_Validate(
        WISP_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_WISP) )
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


        if( !(obj_getSize(this) >= sizeof(WISP_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


