// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Sym.c
 *	Generated 02/22/2020 20:18:12
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
#include        <Sym_internal.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Sym_task_body (
        void            *pData
    )
    {
        //SYM_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SYM_DATA *     Sym_Alloc (
        void
    )
    {
        SYM_DATA       *this;
        uint32_t        cbSize = sizeof(SYM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SYM_DATA *     Sym_New (
        void
    )
    {
        SYM_DATA       *this;
        
        this = Sym_Alloc( );
        if (this) {
            this = Sym_Init(this);
        } 
        return this;
    }



    SYM_DATA *     Sym_NewA(
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        SYM_DATA        *this;

        if (OBJ_NIL == pNameA) {
            return OBJ_NIL;
        }

        this = Sym_New( );
        if (this) {
            Sym_setNameA(this, pNameA);
            Sym_getEntry(this)->Cls = cls;
        }

        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A b s o l u t e
    //---------------------------------------------------------------

    bool            Sym_getAbs (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (Sym_getEntry(this)->Flags & SYM_ABS) ? true : false;
    }


    bool            Sym_setAbs (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->Flags |= SYM_ABS;
        } else {
            Sym_getEntry(this)->Flags &= ~SYM_ABS;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                        A l i g n
    //---------------------------------------------------------------

    uint16_t        Sym_getAlign (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->Align;
    }


    bool            Sym_setAlign (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->Align = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------

    int32_t         Sym_getClass (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->Cls;
    }


    bool            Sym_setClass (
        SYM_DATA        *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->Cls = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          D u p
    //---------------------------------------------------------------

    uint16_t        Sym_getDup (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->Dup;
    }


    bool            Sym_setDup (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->Dup = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        E n t r y
    //---------------------------------------------------------------

    SYM_ENTRY *     Sym_getEntry (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->entry;
    }


    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------

    const
    char *          Sym_getNameA (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->Name;
    }


    bool            Sym_setNameA (
        SYM_DATA        *this,
        const
        char            *pValue
    )
    {
        uint32_t        len;

#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pValue) {
            DEBUG_BREAK();
            return false;
        }
#endif

        str_Copy((char *)Sym_getEntry(this)->Name, SYM_ENTRY_NAME_MAX, pValue);
        len = utf8_StrLenA(pValue);
        //FIXME: Sym_getEntry(this)->cName = len;

        return true;
    }



    //---------------------------------------------------------------
    //                     R e l o c a t a b l e
    //---------------------------------------------------------------

    bool            Sym_getRel (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return (Sym_getEntry(this)->Flags & SYM_REL) ? true : false;
    }


    bool            Sym_setRel (
        SYM_DATA        *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value) {
            Sym_getEntry(this)->Flags |= SYM_REL;
        } else {
            Sym_getEntry(this)->Flags &= ~SYM_REL;
        }

        return true;
    }



    //---------------------------------------------------------------
    //                        S c a l e
    //---------------------------------------------------------------

    uint16_t        Sym_getScale (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->Scale;
    }


    bool            Sym_setScale (
        SYM_DATA        *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->Scale = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Sym_getSize (
        SYM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Sym_getSuperVtbl (
        SYM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    int32_t         Sym_getType (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->Type;
    }


    bool            Sym_setType (
        SYM_DATA        *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->Type = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          V a l u e
    //---------------------------------------------------------------

    int32_t         Sym_getValue (
        SYM_DATA        *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Sym_getEntry(this)->Value;
    }


    bool            Sym_setValue (
        SYM_DATA        *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Sym_getEntry(this)->Value = value;

        return true;
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
        ERESULT eRc = Sym_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SYM object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Sym_Assign (
        SYM_DATA		*this,
        SYM_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Sym_Validate(pOther)) {
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
        memcpy(&pOther->entry, &this->entry, sizeof(SYM_ENTRY));

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
    ERESULT         Sym_Compare (
        SYM_DATA     *this,
        SYM_DATA     *pOther
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
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Sym_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        i = this->entry.Cls - pOther->entry.Cls;
        if (0 == i) {
            i = strcmp(this->entry.Name, pOther->entry.Name);
            if (0 == i) {
                return ERESULT_SUCCESS_EQUAL;
            }
        }
        
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
        Sym      *pCopy = Sym_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SYM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SYM_DATA *     Sym_Copy (
        SYM_DATA       *this
    )
    {
        SYM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SYM_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Sym_New( );
        if (pOther) {
            eRc = Sym_Assign(this, pOther);
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

    void            Sym_Dealloc (
        OBJ_ID          objId
    )
    {
        SYM_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SYM_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
        Sym      *pDeepCopy = Sym_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SYM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SYM_DATA *     Sym_DeepyCopy (
        SYM_DATA       *this
    )
    {
        SYM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Sym_New( );
        if (pOther) {
            eRc = Sym_Assign(this, pOther);
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
    ERESULT         Sym_Disable (
        SYM_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
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
    ERESULT         Sym_Enable (
        SYM_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
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

    SYM_DATA *   Sym_Init (
        SYM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SYM_DATA);
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

        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SYM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Sym_Vtbl);
        
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
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Sym::sizeof(SYM_DATA) = %lu\n", 
                sizeof(SYM_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SYM_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Sym_IsEnabled (
        SYM_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
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
        void        *pMethod = Sym_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Sym", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Sym_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SYM_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SYM_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Sym_Class();
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
                            return Sym_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Sym_Enable;
                        }
                        break;

#ifdef  SYM_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Sym_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Sym_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Sym_ToDebugString;
                        }
#ifdef  SYM_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Sym_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Sym_ToDebugString)
                    return "ToDebugString";
#ifdef  SYM_JSON_SUPPORT
                if (pData == Sym_ToJson)
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
        ASTR_DATA      *pDesc = Sym_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sym_ToDebugString (
        SYM_DATA      *this,
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
        char            NameA[256];
        uint32_t        len;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sym_Validate(this)) {
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
                    Sym_getSize(this),
                    obj_getRetainCount(this)
            );

        len = utf8_Utf8ToChrConStr(0, this->entry.Name, sizeof(NameA), NameA);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Name:\"%s\",\n", NameA);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Class:%d,\n", this->entry.Cls);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Type:%d,\n", this->entry.Type);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Prim:%d,\n", this->entry.Prim);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Len:%d,\n", this->entry.Len);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Dup:%d,\n", this->entry.Dup);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Align:%d,\n", this->entry.Align);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Scale:%d,\n", this->entry.Scale);
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(pStr, "Value:%d,\n", this->entry.Value);

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
    bool            Sym_Validate (
        SYM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SYM))
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


        if (!(obj_getSize(this) >= sizeof(SYM_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


