// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   BitSet.c
 *	Generated 12/18/2019 08:00:17
 *
 *  --  This object uses an Array object to store its data. However,
 *      it does not use the Array's methods to manipulate the data.
 *      Instead, it directly accesses the data.

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
#include        <BitSet_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    uint32_t        BitSet_GetInternal (
        uint32_t        *pData,
        uint32_t        index
    )
    {
        uint32_t        i;
        uint32_t        j;
        
        --index;
        //i = index / 32;                    /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);        /* horizontal - bit */
        j = index & (32 - 1);

        i = (pData[i] & (1 << j)) >> j;
        
        // Return to caller.
        return i;
    }
    
    
    ERESULT         BitSet_SetInternal (
        uint32_t        *pData,
        uint32_t        index,
        bool            value
    )
    {
        uint32_t        i;
        uint32_t        j;
        
        --index;
        //i = index / 32;                    /* horizontal - word */
        i = index >> 5;
        //j = (32-1) - (index % 32);        /* horizontal - bit */
        j = index & (32 - 1);
        
        if (value )
            pData[i] |= (1 << j);
        else
            pData[i] &= ~(1 << j);
        
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BITSET_DATA *     BitSet_Alloc (
        void
    )
    {
        BITSET_DATA       *this;
        uint32_t        cbSize = sizeof(BITSET_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BITSET_DATA *     BitSet_New (
        void
    )
    {
        BITSET_DATA       *this;
        
        this = BitSet_Alloc( );
        if (this) {
            this = BitSet_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         D a t a
    //---------------------------------------------------------------
    
    ARRAY_DATA * BitSet_getData (
        BITSET_DATA *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pData;
    }
    
    
    bool        BitSet_setData (
        BITSET_DATA *this,
        ARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_DATA_OWNED
        obj_Retain(pValue);
        if (this->pData) {
            obj_Release(this->pData);
        }
#endif
        this->pData = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        BitSet_getSize (
        BITSET_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cBits;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  BitSet_getSuperVtbl (
        BITSET_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
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
        ERESULT eRc = BitSet_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another BITSET object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         BitSet_Assign (
        BITSET_DATA		*this,
        BITSET_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BitSet_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.
        if (pOther->pData) {
            obj_Release(pOther->pData);
            pOther->pData = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pData) {
            eRc = array_Assign(this->pData, pOther->pData);
            if (ERESULT_HAS_FAILED(eRc)) {
                return eRc;
            }
        }

        // Copy other data from this object to other.
        pOther->cBits = this->cBits;
        
        // Return to caller.
        return ERESULT_SUCCESS;
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
    ERESULT         BitSet_Compare (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
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
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BitSet_Validate(pOther)) {
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
    //                       C o n t a i n s
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Contains (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        BITSET_DATA     *pWork;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!BitSet_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->cBits == pOther->cBits)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pWork = BitSet_Copy(this);
        if (OBJ_NIL == pWork) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        eRc = BitSet_Intersect(pWork, pOther);
        if (ERESULT_IS_SUCCESSFUL(eRc)) {
            eRc = BitSet_IsEqual(pWork,pOther);
        }
        
        // Return to caller.
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        BitSet      *pCopy = BitSet_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a BITSET object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    BITSET_DATA *     BitSet_Copy (
        BITSET_DATA       *this
    )
    {
        BITSET_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = BitSet_New( );
        if (pOther) {
            eRc = BitSet_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            BitSet_Dealloc (
        OBJ_ID          objId
    )
    {
        BITSET_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((BITSET_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        BitSet_setData(this, OBJ_NIL);
        this->cBits = 0;

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         E x p a n d
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Expand (
        BITSET_DATA     *this,
        uint32_t        size
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        i;
        uint32_t        iMax;
        bool            fRc = false;
        uint32_t        cBits;
        uint32_t        *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if(!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        cBits = this->cBits;
        
        if (size > this->cBits) {
            // Convert to bytes.
            i = ROUNDUP32(size);
            eRc = array_Expand(this->pData, (i >> 5));
            this->cBits = size;
            // Clear the high bits in the current highest word.
            if (cBits) {
                pData = (uint32_t *)array_getData(this->pData);
                iMax = size - cBits;
                for (i=0; i<iMax; i++) {
                    eRc = BitSet_SetInternal(pData, cBits+i+1, false);
                }
            }
        }
        
        // Return to caller.
        return eRc;
    }
            
            
            
    //---------------------------------------------------------------
    //                              G e t
    //---------------------------------------------------------------
    
    bool            BitSet_Get (
        BITSET_DATA     *this,
        uint32_t        index
    )
    {
        bool            fRc = false;
        uint32_t        *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return fRc;
        }
        if (index && ((index-1) < this->cBits))
            ;
        else {
            DEBUG_BREAK();
            return fRc;
        }
#endif
        
        pData = (uint32_t *)array_getData(this->pData);
        if (BitSet_GetInternal(pData, index)) {
            fRc = true;
        }
        
        // Return to caller.
        return fRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BITSET_DATA *   BitSet_Init (
        BITSET_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(BITSET_DATA);
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BITSET);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&BitSet_Vtbl);
        
        this->pData = array_NewWithSize(4); // Allocate in 4 byte groups.
        if (OBJ_NIL == this->pData) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "BitSet::sizeof(BITSET_DATA) = %lu\n", sizeof(BITSET_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(BITSET_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I n t e r s e c t
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Intersect (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        *pData1;
        uint32_t        *pData2;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !BitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( this->cBits == pOther->cBits )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData1 = (uint32_t *)array_getData(this->pData);
        pData2 = (uint32_t *)array_getData(pOther->pData);
        iMax = (ROUNDUP32(this->cBits) >> 5);
        for (i=0; i<iMax; ++i) {
            j = pData1[i];
            pData1[i] &= pData2[i];
            if (j != pData1[i]) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
        }

        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                         I n v e r t
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Invert (
        BITSET_DATA     *this
    )
    {
        uint32_t        *pData;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pData = (uint32_t *)array_getData(this->pData);
        iMax = (ROUNDUP32(this->cBits) >> 5);
        for (i=0; i<iMax; ++i) {
            pData[i] = ~pData[i];
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }
        
        
        
    //---------------------------------------------------------------
    //                         I s E m p t y
    //---------------------------------------------------------------
    
    ERESULT         BitSet_IsEmpty (
        BITSET_DATA     *this
    )
    {
        uint32_t        *pData;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pData = (uint32_t *)array_getData(this->pData);
        iMax = (ROUNDUP32(this->cBits) >> 5);
        for (i=0; i<iMax; ++i) {
            if (pData[i]) {
                return ERESULT_SUCCESS_FALSE;
            }
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_TRUE;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         BitSet_IsEnabled (
        BITSET_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
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
    //                       I s  E q u a l
    //---------------------------------------------------------------
    
    ERESULT         BitSet_IsEqual (
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS_TRUE;
        uint32_t        *pData1;
        uint32_t        *pData2;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !BitSet_Validate( pOther ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( this->cBits == pOther->cBits )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pData1 = (uint32_t *)array_getData(this->pData);
        pData2 = (uint32_t *)array_getData(pOther->pData);
        iMax = (ROUNDUP32(this->cBits) >> 5);
        for (i=0; i<iMax; ++i) {
            if (pData1[i] == pData2[i])
                ;
            else {
                eRc = ERESULT_SUCCESS_FALSE;
                break;
            }
        }
        
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
        void        *pMethod = BitSet_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "BitSet", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          BitSet_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        BITSET_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(BITSET_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)BitSet_Class();
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
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return BitSet_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return BitSet_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == BitSet_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == BitSet_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Set (
        BITSET_DATA     *this,
        uint32_t        index,
        bool            value
    )
    {
        ERESULT         eRc;
        uint32_t        *pData;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (index > this->cBits) {
            eRc = BitSet_Expand(this, index);
        }
        pData = (uint32_t *)array_getData(this->pData);

        BitSet_SetInternal(pData, index, value);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                         S e t  A l l
    //---------------------------------------------------------------
    
    ERESULT         BitSet_SetAll(
        BITSET_DATA     *this
    )
    {
        uint32_t        *pData;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pData = (uint32_t *)array_getData(this->pData);
        iMax = (ROUNDUP32(this->cBits) >> 5);
        for (i=0; i<iMax; ++i) {
            pData[i] = -1;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
        
        
        
    //---------------------------------------------------------------
    //                       S u b t r a c t
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Subtract(
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        *pData1;
        uint32_t        *pData2;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !BitSet_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( this->cBits == pOther->cBits )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData1 = (uint32_t *)array_getData(this->pData);
        pData2 = (uint32_t *)array_getData(pOther->pData);
        iMax = array_getSizeInBytes(this->pData) >> 2;
        for (i=0; i<iMax; ++i) {
            j = pData1[i];
            pData1[i] &= ~pData2[i];
            if (j != pData1[i]) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
        }
        
        // Return to caller.
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                       T o  A r r a y
    //---------------------------------------------------------------
    
    U32ARRAY_DATA * BitSet_ToArrayU32 (
        BITSET_DATA     *this
    )
    {
        ERESULT         eRc;
        U32ARRAY_DATA   *pArray;
        uint32_t        i;
        
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pArray = u32Array_New();
        if (pArray) {
            for (i=0; i<this->cBits; i++) {
                if (BitSet_Get(this, i+1)) {
                    eRc = u32Array_AppendData(pArray, i+1);
                }
            }
            
        }
        
        return pArray;
    }
    
        
        
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  BITSET_JSON_SUPPORT
     ASTR_DATA *     BitSet_ToJson (
        BITSET_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BitSet_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     BitSet_ToDebugString (
        BITSET_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        *pData;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
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
                    "{%p(%s) size=%d arraySize=%d,%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    BitSet_getSize(this),
                    array_getSize(this->pData),
                    array_getSizeInBytes(this->pData),
                    obj_getRetainCount(this)
            );

        pData = (uint32_t *)array_getData(this->pData);
        eRc =   AStr_AppendHexData(
                                 pStr,
                                 pData,
                                 (ROUNDUP32(this->cBits) >> 3),
                                 indent+3
                );

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
    
    
    ASTR_DATA *     bitSet_ToString(
        BITSET_DATA        *this
    )
    {
        ERESULT         eRc;
        uint32_t        *pData;
        uint32_t        i;
        uint32_t        iMax;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!BitSet_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
                      
        pStr = AStr_New();
        if (0 == this->cBits) {
            return pStr;
        }
        
        pData = (uint32_t *)array_getData(this->pData);
        iMax = array_getSizeInBytes(this->pData) >> 2;
        for (i=0; i<iMax-1; i++) {
            eRc = AStr_AppendPrint(pStr, "0x08X, ", pData[i]);
        }
        eRc = AStr_AppendPrint(pStr, "0x08X", pData[i]);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U n i o n
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Union(
        BITSET_DATA     *this,
        BITSET_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        *pData1;
        uint32_t        *pData2;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        j;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !BitSet_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( this->cBits == pOther->cBits )
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pData1 = (uint32_t *)array_getData(this->pData);
        pData2 = (uint32_t *)array_getData(pOther->pData);
        iMax = array_getSizeInBytes(this->pData) >> 2;
        for (i=0; i<iMax; ++i) {
            j = pData1[i];
            pData1[i] |= pData2[i];
            if (j != pData1[i]) {
                eRc = ERESULT_SUCCESS_DATA_CHANGED;
            }
        }

        // Return to caller.
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            BitSet_Validate (
        BITSET_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_BITSET))
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


        if (!(obj_getSize(this) >= sizeof(BITSET_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                         Z e r o
    //---------------------------------------------------------------
    
    ERESULT         BitSet_Zero(
        BITSET_DATA     *this
    )
    {
        uint32_t        *pData;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !BitSet_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pData = (uint32_t *)array_getData(this->pData);
        iMax = (ROUNDUP32(this->cBits) >> 5);
        for (i=0; i<iMax; ++i) {
            pData[i] = 0;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
        
        
        

    
#ifdef	__cplusplus
}
#endif


