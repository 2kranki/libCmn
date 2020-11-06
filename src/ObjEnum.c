// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjEnum.c
 *	Generated 12/16/2019 11:38:07
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
#include        <ObjEnum_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ObjEnum_task_body (
        void            *pData
    )
    {
        //OBJENUM_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJENUM_DATA *     ObjEnum_Alloc (
        void
    )
    {
        OBJENUM_DATA       *this;
        uint32_t        cbSize = sizeof(OBJENUM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJENUM_DATA *     ObjEnum_New (
        void
    )
    {
        OBJENUM_DATA       *this;
        
        this = ObjEnum_Alloc( );
        if (this) {
            this = ObjEnum_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * ObjEnum_getArray(
        OBJENUM_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            ObjEnum_setArray(
        OBJENUM_DATA    *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
        
        
        
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjEnum_getSize (
        OBJENUM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return ObjArray_getSize(this->pArray);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ObjEnum_getSuperVtbl (
        OBJENUM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
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
    //                          A p p e n d
    //---------------------------------------------------------------
    
    ERESULT         ObjEnum_AppendObj(
        OBJENUM_DATA    *this,
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New( );
            if (OBJ_NIL == this->pArray) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
       }
        
        eRc = ObjArray_AppendObj(this->pArray, pObject, NULL);
        
        return eRc;
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
        ERESULT eRc = ObjEnum_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJENUM object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjEnum_Assign (
        OBJENUM_DATA	*this,
        OBJENUM_DATA    *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjEnum_Validate(pOther)) {
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
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }

        // Copy other data from this object to other.
        pOther->current = this->current;

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
    ERESULT         ObjEnum_Compare (
        OBJENUM_DATA     *this,
        OBJENUM_DATA     *pOther
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
        if (!ObjEnum_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjEnum_Validate(pOther)) {
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
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ObjEnum      *pCopy = ObjEnum_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJENUM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJENUM_DATA *     ObjEnum_Copy (
        OBJENUM_DATA       *this
    )
    {
        OBJENUM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjEnum_New( );
        if (pOther) {
            eRc = ObjEnum_Assign(this, pOther);
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

    void            ObjEnum_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJENUM_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

        ObjEnum_setArray(this, OBJ_NIL);

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

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         ObjEnum_Disable (
        OBJENUM_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjEnum_Validate(this)) {
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
    ERESULT         ObjEnum_Enable (
        OBJENUM_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!ObjEnum_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    OBJENUM_DATA *   ObjEnum_Init (
        OBJENUM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJENUM_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJENUM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjEnum_Vtbl);
        
    #ifdef NDEBUG
    #else
        if (!ObjEnum_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "ObjEnum::sizeof(OBJENUM_DATA) = %lu\n", sizeof(OBJENUM_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJENUM_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjEnum_IsEnabled (
        OBJENUM_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
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
    //                      L o o k  A h e a d
    //---------------------------------------------------------------
    
    ERESULT         ObjEnum_LookAhead(
        OBJENUM_DATA    *this,
        uint32_t        offset,
        void            **ppObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            //objEnum_setLastError(this, ERESULT_INVALID_OBJECT);
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == ppObject) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == this->pArray)
            return ERESULT_SUCCESS;
        
        if (obj_Flag(this, OBJENUM_SORTED))
            ;
        else {
            eRc = ObjArray_SortAscending(this->pArray, NULL);
            obj_FlagOn(this, OBJENUM_SORTED);
        }
        
        if ((this->current + offset) < ObjArray_getSize(this->pArray)) {
        }
        else {
            return ERESULT_OUT_OF_RANGE;
        }
        
        *ppObject = ObjArray_Get(this->pArray, (this->current + offset + 1));
        
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N e x t
    //---------------------------------------------------------------
    
    ERESULT         ObjEnum_Next(
        OBJENUM_DATA    *this,
        uint32_t        cElems,
        OBJ_ID          *ppArray,
        uint32_t        *pReturnAmt
    )
    {
        ERESULT         eRc;
        uint32_t        count = 0;
        OBJ_ID          pObj;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == ppArray) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (OBJ_NIL == this->pArray)
            return ERESULT_OUT_OF_RANGE;

        if (obj_Flag(this, OBJENUM_SORTED))
            ;
        else {
            eRc = ObjArray_SortAscending(this->pArray, NULL);
            obj_FlagOn(this, OBJENUM_SORTED);
        }
        
        if (this->current < ObjArray_getSize(this->pArray)) {
        }
        else {
            if (pReturnAmt) {
                *pReturnAmt = 0;
            }
            return ERESULT_OUT_OF_RANGE;
        }
        
        for( ;; ) {
            if( count < cElems )
                ;
            else
                break;
            if( this->current < ObjArray_getSize(this->pArray) )
                ;
            else
                break;
            pObj = ObjArray_Get(this->pArray, (this->current + 1));
            if( OBJ_NIL == pObj )
                ;
            else {
                ppArray[count] = pObj;
                ++count;
            }
            this->current += 1;
        }
        
        if (pReturnAmt) {
            *pReturnAmt = count;
        }
        return ERESULT_SUCCESS;
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
        void        *pMethod = ObjEnum_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjEnum", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjEnum_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJENUM_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJENUM_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjEnum_Class();
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
                            return ObjEnum_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjEnum_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjEnum_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjEnum_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjEnum_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == ObjEnum_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      R e m a i n i n g
    //---------------------------------------------------------------
    
    uint32_t        ObjEnum_Remaining(
        OBJENUM_DATA    *this
    )
    {
        uint32_t        count = 0;
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (OBJ_NIL == this->pArray)
            return 0;

        count = ObjArray_getSize(this->pArray) - this->current;
        
        // Return to caller.
        return count;
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------
    
    ERESULT         ObjEnum_Reset(
        OBJENUM_DATA    *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->current = 0;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
        
        
        
    //---------------------------------------------------------------
    //                          S k i p
    //---------------------------------------------------------------
    
    ERESULT         ObjEnum_Skip(
        OBJENUM_DATA    *this,
        uint32_t        cElems
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        this->current += cElems;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S o r t
    //---------------------------------------------------------------
    
    ERESULT         ObjEnum_SortAscending(
        OBJENUM_DATA    *this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjEnum_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (NULL == this->pArray) {
            return ERESULT_SUCCESS;
        }

        eRc = ObjArray_SortAscending(this->pArray, NULL);
        obj_FlagOn(this, OBJENUM_SORTED);
        
        return eRc;
    }
        
        
        
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
#ifdef  OBJENUM_JSON_SUPPORT
     ASTR_DATA *     ObjEnum_ToJson (
        OBJENUM_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
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
        ASTR_DATA      *pDesc = ObjEnum_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjEnum_ToDebugString (
        OBJENUM_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjEnum_Validate(this)) {
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
                    ObjEnum_getSize(this),
                    obj_getRetainCount(this)
            );

        if (this->pArray) {
            if (((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pArray))->pVtbl->pToDebugString(
                                                    this->pArray,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
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
    bool            ObjEnum_Validate (
        OBJENUM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJENUM))
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


        if (!(obj_getSize(this) >= sizeof(OBJENUM_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


