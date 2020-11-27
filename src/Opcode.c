// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Opcode.c
 *	Generated 02/27/2020 14:36:27
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
#include        <Opcode_internal.h>
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
    void            Opcode_task_body (
        void            *pData
    )
    {
        //OPCODE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OPCODE_DATA *   Opcode_Alloc (
        void
    )
    {
        OPCODE_DATA     *this;
        uint32_t        cbSize = sizeof(OPCODE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OPCODE_DATA *   Opcode_New (
        void
    )
    {
        OPCODE_DATA     *this;
        
        this = Opcode_Alloc( );
        if (this) {
            this = Opcode_Init(this);
        } 
        return this;
    }



    OPCODE_DATA *   Opcode_NewA (
        const
        char            *pNameA
    )
    {
        OPCODE_DATA     *this;

        this = Opcode_New( );
        if (this) {
            Opcode_setNameA(this, pNameA);
        }
        return this;
    }



    OPCODE_DATA *   Opcode_NewEntry (
        OPCODE_ENTRY    *pEntry
    )
    {
        OPCODE_DATA     *this;

        this = Opcode_New( );
        if (this) {
            Opcode_setEntry(this, pEntry);
        }
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //           D i s a s s e m b l y  S t r i n g
    //---------------------------------------------------------------

    const
    char *          Opcode_getDisA (
        OPCODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Opcode_getEntry(this)->DisA;
    }


    bool            Opcode_setDisA (
        OPCODE_DATA     *this,
        const
        char            *pValue
    )
    {

#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        str_Copy((char *)Opcode_getEntry(this)->DisA, OPCODE_ENTRY_DIS_MAX, pValue);

        return true;
    }



    //---------------------------------------------------------------
    //                        E n t r y
    //---------------------------------------------------------------

    OPCODE_ENTRY *  Opcode_getEntry (
        OPCODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return &this->entry;
    }

    bool            Opcode_setEntry (
        OPCODE_DATA     *this,
        const
        OPCODE_ENTRY    *pEntry
    )
    {
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        memmove(&this->entry, pEntry, sizeof(OPCODE_ENTRY));

        return true;
    }



    //---------------------------------------------------------------
    //                        E x e c
    //---------------------------------------------------------------

    bool            Opcode_setExec (
        OPCODE_DATA     *this,
        ERESULT         (*pExec)(OBJ_ID, OBJ_ID),
        OBJ_ID          pObjExec
    )
    {
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pExec = pExec;
        this->pObjExec = pObjExec;

        return true;
    }



    //---------------------------------------------------------------
    //                        L e n g t h
    //---------------------------------------------------------------

    uint8_t         Opcode_getLen (
        OPCODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Opcode_getEntry(this)->iLen;
    }


    bool            Opcode_setLen (
        OPCODE_DATA     *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Opcode_getEntry(this)->iLen = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------

    const
    char *          Opcode_getNameA (
        OPCODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Opcode_getEntry(this)->NameA;
    }


    bool            Opcode_setNameA (
        OPCODE_DATA     *this,
        const
        char            *pValue
    )
    {

#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        str_Copy((char *)Opcode_getEntry(this)->NameA, OPCODE_ENTRY_NAME_MAX, pValue);

        return true;
    }



    //---------------------------------------------------------------
    //                        N o d e
    //---------------------------------------------------------------

    NODE_DATA *     Opcode_getNode (
        OPCODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (NODE_DATA *)this;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Opcode_getSize (
        OPCODE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Opcode_getSuperVtbl (
        OPCODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                        T y p e
    //---------------------------------------------------------------

    int16_t         Opcode_getType (
        OPCODE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Opcode_getEntry(this)->iLen;
    }


    bool            Opcode_setType (
        OPCODE_DATA     *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        Opcode_getEntry(this)->iLen = value;

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
        ERESULT eRc = Opcode_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OPCODE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Opcode_Assign (
        OPCODE_DATA		*this,
        OPCODE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Opcode_Validate(pOther)) {
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
        memcpy(&pOther->entry, &this->entry, sizeof(OPCODE_ENTRY));
        
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Opcode_Compare (
        OPCODE_DATA     *this,
        OPCODE_DATA     *pOther
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
        int             i = 0;

#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Opcode_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        i = utf8_StrCmp(this->entry.NameA, pOther->entry.NameA);
        
        return i;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Opcode      *pCopy = Opcode_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPCODE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPCODE_DATA *     Opcode_Copy (
        OPCODE_DATA       *this
    )
    {
        OPCODE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OPCODE_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Opcode_New( );
        if (pOther) {
            eRc = Opcode_Assign(this, pOther);
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

    void            Opcode_Dealloc (
        OBJ_ID          objId
    )
    {
        OPCODE_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OPCODE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
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
        Opcode      *pDeepCopy = Opcode_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPCODE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPCODE_DATA *     Opcode_DeepyCopy (
        OPCODE_DATA       *this
    )
    {
        OPCODE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Opcode_New( );
        if (pOther) {
            eRc = Opcode_Assign(this, pOther);
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
    ERESULT         Opcode_Disable (
        OPCODE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
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
    ERESULT         Opcode_Enable (
        OPCODE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
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
    //                      E x e c u t e
    //---------------------------------------------------------------

    /*!
     Execute the method attached to this opcode.
     @param     this        object pointer
     @param     pOperand    Operand object pointer (optional)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Opcode_Exec (
        OPCODE_DATA     *this,
        OBJ_ID          pOperand
    )
    {
        ERESULT         eRc = ERESULT_INVALID_FUNCTION;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pExec) {
            eRc = this->pExec(this->pObjExec, pOperand);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OPCODE_DATA *   Opcode_Init (
        OPCODE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OPCODE_DATA);
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

        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OPCODE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Opcode_Vtbl);
        
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
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Opcode::sizeof(OPCODE_DATA) = %lu\n", 
                sizeof(OPCODE_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OPCODE_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Opcode_IsEnabled (
        OPCODE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
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
    //                      P a r s e
    //---------------------------------------------------------------

    ERESULT         Opcode_Parse (
        OPCODE_DATA     *this,
        OBJ_ID          pOperand
    )
    {
        ERESULT         eRc = ERESULT_INVALID_FUNCTION;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pPrs) {
            eRc = this->pPrs(this->pObjPrs, pOperand);
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
        void        *pMethod = Opcode_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Opcode", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Opcode_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OPCODE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OPCODE_DATA);
                break;

            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Opcode_Class();
                break;
                
            // Query for an address to specific data within the object.
            // This should be used very sparingly since it breaks the
            // object's encapsulation.
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {

                    case 'O':
                        if (str_Compare("Opcode", (char *)pStr) == 0) {
                            return this;
                        }
                        break;

                    case 'S':
                        if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                            return &this->pSuperVtbl;
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
                            return Opcode_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Opcode_Enable;
                        }
                        break;

#ifdef  OPCODE_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Opcode_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Opcode_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Opcode_ToDebugString;
                        }
#ifdef  OPCODE_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Opcode_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Opcode_ToDebugString)
                    return "ToDebugString";
#ifdef  OPCODE_JSON_SUPPORT
                if (pData == Opcode_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  I n i t S t r i n g
    //---------------------------------------------------------------

    /*!
     Create a string that when compiled will initialize for this opcode.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                initialization, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcode_ToInitString (
        OPCODE_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        uint32_t        i;
        //uint32_t        j;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        eRc = AStr_AppendA(pStr, "\t{\n");
        eRc = AStr_AppendPrint(pStr, "\t\t\"%s\",\n", this->entry.NameA);
        eRc = AStr_AppendPrint(pStr, "\t\t\"%s\",\n", this->entry.DisA);
        eRc = AStr_AppendPrint(pStr, "\t\t%d,\t// iLen\n", this->entry.iLen);
        eRc = AStr_AppendPrint(pStr, "\t\t%d,\n", this->entry.cCode);
        eRc = AStr_AppendA(pStr, "\t\t{");
        for (i=0; i<this->entry.cCode-1; i++) {
            eRc = AStr_AppendPrint(pStr, "0x%02X,", this->entry.iCode[i]);
        }
        eRc = AStr_AppendPrint(pStr, "0x%02X},\n", this->entry.iCode[i]);
        eRc = AStr_AppendA(pStr, "\t\t{");
        for (i=0; i<this->entry.cCode-1; i++) {
            eRc = AStr_AppendPrint(pStr, "0x%02X,", this->entry.iMask[i]);
        }
        eRc = AStr_AppendPrint(pStr, "0x%02X},\n", this->entry.iMask[i]);
        eRc = AStr_AppendPrint(pStr, "\t\t%u,\t// iType\n", this->entry.iType);
        eRc = AStr_AppendPrint(pStr, "\t\t%d,\t// iClass\n", this->entry.iClass);
        eRc = AStr_AppendPrint(pStr, "\t\t%d,\n", this->entry.cCondCodes);
        if (this->entry.cCondCodes) {
            AStr_AppendA(pStr, "\t\t{");
            for (i=0; i<this->entry.cCondCodes-1; i++) {
                AStr_AppendPrint(pStr, "\"%s\", ", this->entry.szCondCodes[i]);
            }
            AStr_AppendPrint(pStr, "\"%s\"},\n", this->entry.szCondCodes[i]);
        } else {
            AStr_AppendA(pStr, "\t\t{\"\"},\n");
        }
        eRc = AStr_AppendPrint(pStr, "\t\t%d,\t// iCondCodes\n", this->entry.iCondCodes);
        eRc = AStr_AppendPrint(pStr, "\t\t%u,\t// iFeatures\n", this->entry.iFeatures);
        eRc = AStr_AppendPrint(pStr, "\t\t%u,\t// iInterrupts\n", this->entry.iInterrupts);
        eRc = AStr_AppendPrint(pStr, "\t\t%u\t// unique\n", this->entry.unique);

        eRc =   AStr_AppendA(pStr, " \t},\n");

        return pStr;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Opcode_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcode_ToDebugString (
        OPCODE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        //uint32_t        j;
        const
        char            *pDesc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcode_Validate(this)) {
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
                    Opcode_getSize(this),
                    obj_getRetainCount(this)
            );

        eRc = AStr_AppendPrint(pStr, "\tname=%s\n", this->entry.NameA);
        eRc = AStr_AppendPrint(pStr, "\tdis=%s\n", this->entry.DisA);
        eRc = AStr_AppendPrint(pStr, "\tcCode=%d\n", this->entry.cCode);
        eRc = AStr_AppendA(pStr, "\tiCode=[");
        for (i=0; i<this->entry.cCode; i++) {
            eRc = AStr_AppendPrint(pStr, " 0x%2X,", this->entry.iCode[i]);
        }
        eRc = AStr_AppendA(pStr, "]\n");
        eRc = AStr_AppendA(pStr, "\tiMask=[");
        for (i=0; i<this->entry.cCode; i++) {
            eRc = AStr_AppendPrint(pStr, " 0x%2X,", this->entry.iMask[i]);
        }
        eRc = AStr_AppendA(pStr, "]\n");
        if (this->pTypeDesc) {
            pDesc = this->pTypeDesc(this->entry.iType);
            if (pDesc) {
                eRc = AStr_AppendPrint(pStr, "\tType=%s\n", pDesc);
            }
        } else {
            eRc = AStr_AppendPrint(pStr, "\tType=%u\n", this->entry.iType);
        }
        eRc = AStr_AppendPrint(pStr, "\tiLen=%d,", this->entry.iLen);
        if (this->entry.cCondCodes) {
            eRc = AStr_AppendPrint(pStr, "\tcCondCodes=%d,", this->entry.cCondCodes);
            AStr_AppendA(pStr, "\tszCondCodes:[\n");
            for (i=0; i<this->entry.cCondCodes-1; i++) {
                AStr_AppendPrint(pStr, "\t\t%s,\n", this->entry.szCondCodes[i]);
            }
            AStr_AppendPrint(pStr, "\t\t%s\n", this->entry.szCondCodes[i]);
            AStr_AppendA(pStr, "\t],\n");
        }
        if (this->entry.iFeatures) {
            if (this->pFeatureDesc) {
                AStr_AppendA(pStr, "\tiFeatures:[\n");
                for (i=0; i<OPCODE_ENTRY_IFEATURES_MAX; i++) {
                    uint16_t    mask = 1 << i;
                    if (this->entry.iFeatures & mask) {
                        pDesc = this->pFeatureDesc(this->entry.iFeatures & mask);
                        if (pDesc) {
                            AStr_AppendPrint(pStr, "\t\t%s,\n", pDesc);
                        }
                    }
                }
                AStr_AppendA(pStr, "\t],\n");
            } else {
                eRc = AStr_AppendPrint(pStr, "\tiFeatures:=%u\n", this->entry.iFeatures);
            }
        }
        if (this->entry.iInterrupts) {
            if (this->pInterruptDesc) {
                AStr_AppendA(pStr, "\tiInterrupts:[\n");
                for (i=0; i<OPCODE_ENTRY_IINTERRUPTS_MAX; i++) {
                    uint32_t    mask = 1 << i;
                    if (this->entry.iInterrupts & mask) {
                        pDesc = this->pInterruptDesc(i+1);
                        if (pDesc) {
                            AStr_AppendPrint(pStr, "\t\t%s,\n", pDesc);
                        }
                    }
                }
                AStr_AppendA(pStr, "\t],\n");
            } else {
                eRc = AStr_AppendPrint(pStr, "\tiInterrupts: %u\n", this->entry.iInterrupts);
            }
        }
        
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
    bool            Opcode_Validate (
        OPCODE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OPCODE))
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


        if (!(obj_getSize(this) >= sizeof(OPCODE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


