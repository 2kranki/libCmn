// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   IntIndex.c
 *  Generated 01/03/2021 13:14:35
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
#include        <IntIndex_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    INTINDEX_NODE * IntIndex_Search (
        INTINDEX_DATA   *this,
        int             index
    )
    {
        INTINDEX_NODE   *pNode;
        uint32_t        max = array_getSize(this->pArray);
        int             cmp;
        uint32_t        high;
        uint32_t        low;
        uint32_t        mid;


        if (0 == max)
            return NULL;

        // Do a binary search on the array.
        high = max - 1;
        low = 0;
        while (low < high) {
            mid = (low + high) / 2;
            pNode  = array_GetAddrOf(this->pArray, mid+1);
            if (this->fSigned) {
                cmp = index - pNode->index;
            } else {
                cmp = (unsigned int)index - (unsigned int)pNode->index;
            }
            if (0 > cmp)
                high = mid;
            if (0 == cmp)
                return pNode;
            if (0 < cmp)
                low = mid + 1;
        }
        if (low == high) {
            pNode  = array_GetAddrOf(this->pArray, low+1);
            if (this->fSigned) {
                cmp = index - pNode->index;
            } else {
                cmp = (unsigned int)index - (unsigned int)pNode->index;
            }
            if (0 == cmp)
                return pNode;

        }

        return NULL;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    INTINDEX_DATA *     IntIndex_Alloc (
        void
    )
    {
        INTINDEX_DATA       *this;
        uint32_t        cbSize = sizeof(INTINDEX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    INTINDEX_DATA *     IntIndex_New (
        void
    )
    {
        INTINDEX_DATA       *this;
        
        this = IntIndex_Alloc( );
        if (this) {
            this = IntIndex_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      A r r a y
    //---------------------------------------------------------------

    ARRAY_DATA *        IntIndex_getArray (
        INTINDEX_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool                IntIndex_setArray (
        INTINDEX_DATA       *this,
        ARRAY_DATA          *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
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
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        IntIndex_getPriority (
        INTINDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            IntIndex_setPriority (
        INTINDEX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        S i g n e d
    //---------------------------------------------------------------

    bool            IntIndex_getSigned (
        INTINDEX_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fSigned ? true : false;
    }


    bool            IntIndex_setSigned (
        INTINDEX_DATA   *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fSigned = fValue ? 1 : 0;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        IntIndex_getSize (
        INTINDEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize(this->pArray);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  IntIndex_getSuperVtbl (
        INTINDEX_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
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
    //                          A d d
    //---------------------------------------------------------------

    ERESULT          IntIndex_Add (
        INTINDEX_DATA   *this,
        int             index,
        void            *ptr,
        bool            fUpdate
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        INTINDEX_NODE   *pNode;
        INTINDEX_NODE   node;
        int             cmp;
        uint32_t        high;
        uint32_t        low;
        uint32_t        mid;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (array_getSize(this->pArray) == 0) {
            node.index = index;
            node.ptr = ptr;
            eRc = array_AppendData(this->pArray, 1, &node);
            return eRc;
        }
        node.index = index;
        node.ptr = ptr;

        // Do a binary search on the array.
        high = array_getSize(this->pArray) - 1;
        low = 0;
        while (low < high) {
            mid = (low + high) / 2;
            pNode  = array_GetAddrOf(this->pArray, mid+1);
            if (this->fSigned) {
                cmp = index - pNode->index;
            } else {
                cmp = (unsigned int)index - (unsigned int)pNode->index;
            }
            if (0 > cmp)
                high = mid;
            if (0 == cmp) {
                if (fUpdate) {
                    pNode->ptr = ptr;
                    return ERESULT_SUCCESS;
                } else {
                    return ERESULT_DATA_ALREADY_EXISTS;
                }
            }
            if (0 < cmp)
                low = mid + 1;
        }
        if (low == high) {
            pNode  = array_GetAddrOf(this->pArray, low+1);
            if (this->fSigned) {
                cmp = index - pNode->index;
            } else {
                cmp = (unsigned int)index - (unsigned int)pNode->index;
            }
            if (0 == cmp) {
                if (fUpdate) {
                    pNode->ptr = ptr;
                    return ERESULT_SUCCESS;
                } else {
                    return ERESULT_DATA_ALREADY_EXISTS;
                }
            }
            if (0 < cmp) {
                eRc = array_AppendData(this->pArray, 1, &node);
            } else {
                eRc = array_InsertData(this->pArray, low+1, 1, &node);
            }
        }

        // Return to caller.
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
        ERESULT eRc = IntIndex_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another INTINDEX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         IntIndex_Assign (
        INTINDEX_DATA       *this,
        INTINDEX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!IntIndex_Validate(pOther)) {
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
        //pOther->x     = this->x; 

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
    int             IntIndex_Compare (
        INTINDEX_DATA     *this,
        INTINDEX_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!IntIndex_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        IntIndex      *pCopy = IntIndex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a INTINDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    INTINDEX_DATA *     IntIndex_Copy (
        INTINDEX_DATA       *this
    )
    {
        INTINDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef INTINDEX_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = IntIndex_New( );
        if (pOther) {
            eRc = IntIndex_Assign(this, pOther);
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

    void            IntIndex_Dealloc (
        OBJ_ID          objId
    )
    {
        INTINDEX_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((INTINDEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        IntIndex_setArray(this, OBJ_NIL);

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
        IntIndex      *pDeepCopy = IntIndex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a INTINDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    INTINDEX_DATA *     IntIndex_DeepyCopy (
        INTINDEX_DATA       *this
    )
    {
        INTINDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = IntIndex_New( );
        if (pOther) {
            eRc = IntIndex_Assign(this, pOther);
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
    ERESULT         IntIndex_Disable (
        INTINDEX_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
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
    ERESULT         IntIndex_Enable (
        INTINDEX_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    /*!
     Search the index by index number and return the associated void
     pointer if found.
     @param     this    object pointer
     @param     index   index number to search by
     @return    if successful, the void pointer associated with the
                index; otherwise, NULL;
     */
    void *          IntIndex_Find (
        INTINDEX_DATA   *this,
        int             index
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        INTINDEX_NODE   *pNode;
        void            *ptr = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif

        pNode = IntIndex_Search(this, index);
        if (pNode)
            ptr = pNode->ptr;

        // Return to caller.
        return ptr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    INTINDEX_DATA *   IntIndex_Init (
        INTINDEX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(INTINDEX_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_INTINDEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&IntIndex_Vtbl);
#ifdef  INTINDEX_JSON_SUPPORT
        JsonIn_RegisterClass(IntIndex_Class());
#endif
        
        this->pArray = array_NewWithSize(sizeof(INTINDEX_NODE));
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "IntIndex::sizeof(INTINDEX_DATA) = %lu\n", 
                sizeof(INTINDEX_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(INTINDEX_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         IntIndex_IsEnabled (
        INTINDEX_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
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
        void        *pMethod = IntIndex_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "IntIndex", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          IntIndex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        INTINDEX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(INTINDEX_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)IntIndex_Class();
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
                            return IntIndex_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return IntIndex_Enable;
                        }
                        break;

                    case 'P':
#ifdef  INTINDEX_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return IntIndex_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return IntIndex_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return IntIndex_ToDebugString;
                        }
#ifdef  INTINDEX_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return IntIndex_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return IntIndex_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == IntIndex_ToDebugString)
                    return "ToDebugString";
#ifdef  INTINDEX_JSON_SUPPORT
                if (pData == IntIndex_ToJson)
                    return "ToJson";
#endif
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
        ASTR_DATA      *pDesc = IntIndex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     IntIndex_ToDebugString (
        INTINDEX_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        uint32_t        iMax;
        //uint32_t        j;
        INTINDEX_NODE   *pNode;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!IntIndex_Validate(this)) {
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
                    IntIndex_getSize(this),
                    obj_getRetainCount(this)
            );

        iMax = array_getSize(this->pArray);
        for (i=0; i<iMax; i++) {
            pNode  = array_GetAddrOf(this->pArray, i+1);
            if (pNode) {
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+4, ' ');
                }
                AStr_AppendPrint(pStr, "%8d  %p\n", pNode->index, pNode->ptr);
            }
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
    bool            IntIndex_Validate (
        INTINDEX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_INTINDEX))
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


        if (!(obj_getSize(this) >= sizeof(INTINDEX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


