// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   U8VlArray.c
 *	Generated 03/20/2020 11:56:58
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
#include        <U8VlArray_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            U8VlArray_task_body (
        void            *pData
    )
    {
        //U8VLARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    U8VLARRAY_DATA * U8VlArray_Alloc (
        void
    )
    {
        U8VLARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(U8VLARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    U8VLARRAY_DATA * U8VlArray_New (
        void
    )
    {
        U8VLARRAY_DATA       *this;
        
        this = U8VlArray_Alloc( );
        if (this) {
            this = U8VlArray_Init(this);
        } 
        return this;
    }



    U8VLARRAY_DATA * U8VlArray_NewExternal (
        uint8_t         *pData
    )
    {
        U8VLARRAY_DATA       *this;

        this = U8VlArray_New();
        if (this) {
            this->pData = pData;
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        U8VlArray_getPriority (
        U8VLARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            U8VlArray_setPriority (
        U8VLARRAY_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
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
    
    uint32_t        U8VlArray_getSize (
        U8VLARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  U8VlArray_getSuperVtbl (
        U8VLARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
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
    //                         A p p e n d
    //---------------------------------------------------------------

    /*!
     Append a data element to the array. The first byte of the element
     must be its length including the first byte.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         U8VlArray_AppendData (
        U8VLARRAY_DATA  *this,
        uint8_t         *pData
    )
    {
        //ERESULT         eRc;
        uint32_t        unused;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pData) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        unused = this->pData[0] - this->pData[1];
        if (pData[0] > unused) {
            return ERESULT_OUT_OF_MEMORY;
        }

        memmove(this->pData+(this->pData[1]), pData, pData[0]);
        this->pData[1] += pData[0];

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = U8VlArray_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another U8VLARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         U8VlArray_Assign (
        U8VLARRAY_DATA		*this,
        U8VLARRAY_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!U8VlArray_Validate(pOther)) {
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
        if (pOther->pData) {
            mem_Free(pOther->pData);
            pOther->pData = NULL;
            obj_FlagOff(pOther, U8VLARRAY_FLAG_ALLOC);
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pData) {
            pOther->pData = mem_Malloc(this->pData[0]);
            if (pOther->pData) {
                memmove(pOther->pData, this->pData, this->pData[0]);
                obj_FlagOn(pOther, U8VLARRAY_FLAG_ALLOC);
            } else {
                eRc = ERESULT_OUT_OF_MEMORY;
                goto eom;
            }
        }

        // Copy other data from this object to other.
        
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
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
    int             U8VlArray_Compare (
        U8VLARRAY_DATA  *this,
        U8VLARRAY_DATA  *pOther
    )
    {
        int             i = 0;

#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!U8VlArray_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (this->pData == pOther->pData) {
            return i;
        }

        if (this->pData[0] == pOther->pData[0]) {
            i = memcmp(this->pData, pOther->pData, this->pData[0]);
            if (i) {
                i = 1;
            }
        } else {
            i = 1;
        }

        return i;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        U8VlArray      *pCopy = U8VlArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a U8VLARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U8VLARRAY_DATA *     U8VlArray_Copy (
        U8VLARRAY_DATA       *this
    )
    {
        U8VLARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef U8VLARRAY_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = U8VlArray_New( );
        if (pOther) {
            eRc = U8VlArray_Assign(this, pOther);
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
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            U8VlArray_Dealloc (
        OBJ_ID          objId
    )
    {
        U8VLARRAY_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((U8VLARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (obj_Flag(this, U8VLARRAY_FLAG_ALLOC)) {
            mem_Free(this->pData);
            this->pData = NULL;
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
        U8VlArray      *pDeepCopy = U8VlArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a U8VLARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    U8VLARRAY_DATA *     U8VlArray_DeepyCopy (
        U8VLARRAY_DATA       *this
    )
    {
        U8VLARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = U8VlArray_New( );
        if (pOther) {
            eRc = U8VlArray_Assign(this, pOther);
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
    ERESULT         U8VlArray_Disable (
        U8VLARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
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
    ERESULT         U8VlArray_Enable (
        U8VLARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
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
    //                      G e t
    //---------------------------------------------------------------

    uint8_t *       U8VlArray_Get (
        U8VLARRAY_DATA  *this,
        uint32_t        index
    )
    {
        //ERESULT         eRc;
        uint8_t         *pData = NULL;
        uint32_t        cur = 2;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
        if (NULL == this->pData) {
            DEBUG_BREAK();
            //return ERESULT_GENERAL_FAILURE;
            return NULL;
        }
        if (index)
            ;
        else {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return NULL;
        }
#endif

        while (index && (cur < this->pData[1])) {
            if (--index == 0) {
                pData = &this->pData[cur];
                break;
            }
            cur += this->pData[cur];
        }

        // Return to caller.
        return pData;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    U8VLARRAY_DATA *   U8VlArray_Init (
        U8VLARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(U8VLARRAY_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_U8VLARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&U8VlArray_Vtbl);
        JsonIn_RegisterClass(U8VlArray_Class());

        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "U8VlArray::sizeof(U8VLARRAY_DATA) = %lu\n", 
                sizeof(U8VLARRAY_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(U8VLARRAY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I n s e r t
    //---------------------------------------------------------------

    ERESULT         U8VlArray_InsertData (
        U8VLARRAY_DATA  *this,
        uint32_t        index,
        uint8_t         *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint8_t         *pInsert = NULL;
        uint32_t        cur = 2;
        uint32_t        len = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pData) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
        if (pData[0] < 2) {
            return ERESULT_DATA_TOO_SMALL;
        }
#endif
        len = pData[0];
        if (len > (this->pData[0] - this->pData[1])) {
            return ERESULT_DATA_TOO_BIG;
        }

        while (index && (cur < this->pData[1])) {
            if (index-- == 0) {
                pInsert = &this->pData[cur];
                break;
            }
            cur += this->pData[cur];
        }
        if (index < 2)
            ;
        else {
            return ERESULT_DATA_OUT_OF_RANGE;
        }

        if (cur <= this->pData[1]) {
            memmove(
                    &this->pData[cur + len],
                    &this->pData[cur],
                    (this->pData[1] - cur)
            );
        }

        memmove(
                &this->pData[cur],
                pData,
                len
        );
        this->pData[1] += len;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         U8VlArray_IsEnabled (
        U8VLARRAY_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = U8VlArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "U8VlArray", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          U8VlArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        U8VLARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(U8VLARRAY_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)U8VlArray_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return U8VlArray_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return U8VlArray_Enable;
                        }
                        break;

                    case 'P':
#ifdef  U8VLARRAY_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return U8VlArray_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return U8VlArray_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return U8VlArray_ToDebugString;
                        }
#ifdef  U8VLARRAY_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return U8VlArray_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return U8VlArray_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == U8VlArray_ToDebugString)
                    return "ToDebugString";
#ifdef  U8VLARRAY_JSON_SUPPORT
                if (pData == U8VlArray_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t u p
    //---------------------------------------------------------------

    /*!
     Set up a previously existing managed space for this object.
     @param     this    object pointer
     @param     pData   pointer to space to be managed
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         U8VlArray_SetupExternal (
        U8VLARRAY_DATA  *this,
        uint8_t         *pData
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (pData[1] > pData[0]) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (this->pData && obj_Flag(this, U8VLARRAY_FLAG_ALLOC)) {
            mem_Free(this->pData);
            obj_FlagOff(this, U8VLARRAY_FLAG_ALLOC);
        }

        this->pData = pData;

        // Return to caller.
        return ERESULT_SUCCESS;
    }


    /*!
     Set up a new managed space controlled by this object.
     @param     this    object pointer
     @param     size    total size of the managed space, (> 1 and < 256)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         U8VlArray_SetupSize (
        U8VLARRAY_DATA  *this,
        uint32_t        size
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!U8VlArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if ((size > 1) && (size < 256))
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (this->pData && obj_Flag(this, U8VLARRAY_FLAG_ALLOC)) {
            mem_Free(this->pData);
        }

        this->pData = mem_Calloc(1, size);
        this->pData[0] = size;
        this->pData[1] = 2;
        obj_FlagOn(this, U8VLARRAY_FLAG_ALLOC);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = U8VlArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     U8VlArray_ToDebugString (
        U8VLARRAY_DATA      *this,
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
        if (!U8VlArray_Validate(this)) {
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
                    U8VlArray_getSize(this),
                    obj_getRetainCount(this)
            );

        if (this->pData) {
            AStr_AppendA(pStr, "\tData:\n");
            AStr_AppendHexData(pStr, this->pData, this->pData[0], indent+8);
        } else {
            AStr_AppendA(pStr, "\tNo data!\n");
        }

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            U8VlArray_Validate (
        U8VLARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_U8VLARRAY))
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


        if (!(obj_getSize(this) >= sizeof(U8VLARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


