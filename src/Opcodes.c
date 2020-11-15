// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Opcodes.c
 *	Generated 02/27/2020 16:46:25
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
#include        <Opcodes_internal.h>
#include        <ObjEnum_internal.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         Opcodes_DeleteExit (
        OPCODES_DATA    *this,
        void            *pKey,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // We can ignore the key since it is part of the data object.

        // Release the Opcode object.
        obj_Release(pData);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                  S c a n  E x i t
    //---------------------------------------------------------------

    ERESULT         Opcodes_ScanExit (
        OPCODES_DATA    *this,
        const
        char            *pKey,
        OPCODE_DATA     *pData,
        OBJENUM_DATA    *pEnum
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // We can ignore the key since it is part of the data object.

        eRc = ObjEnum_AppendObj(pEnum, pData);

        // Return to caller.
        return eRc;
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OPCODES_DATA *     Opcodes_Alloc (
        void
    )
    {
        OPCODES_DATA    *this;
        uint32_t        cbSize = sizeof(OPCODES_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OPCODES_DATA *     Opcodes_New (
        void
    )
    {
        OPCODES_DATA       *this;
        
        this = Opcodes_Alloc( );
        if (this) {
            this = Opcodes_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                        A r r a y
    //---------------------------------------------------------------

    OBJARRAY_DATA * Opcodes_getArray (
        OPCODES_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            Opcodes_setArray (
        OPCODES_DATA    *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
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
    
    uint16_t        Opcodes_getPriority (
        OPCODES_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Opcodes_setPriority (
        OPCODES_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
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
    
    uint32_t        Opcodes_getSize (
        OPCODES_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return ObjArray_getSize(this->pArray);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Opcodes_getSuperVtbl (
        OPCODES_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
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

    ERESULT         Opcodes_Add (
        OPCODES_DATA    *this,
        OPCODE_DATA     *pOpc
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        OPCODE_ENTRY    *pEntry;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pOpc) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (obj_IsKindOf(pOpc, OBJ_IDENT_OPCODE))
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pEntry = Opcode_getEntry(pOpc);
        pEntry->unique = ObjArray_getSize(this->pArray);

        eRc = ObjArray_AppendObj(this->pArray, pOpc, NULL);

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
        ERESULT eRc = Opcodes_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OPCODES object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Opcodes_Assign (
        OPCODES_DATA	*this,
        OPCODES_DATA    *pOther
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Opcodes_Validate(pOther)) {
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
            ObjArray_DeleteAll(pOther->pArray);
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        pEnum = Opcodes_Enum(this);
        for (;;) {
            OPCODE_DATA         *pOpc = OBJ_NIL;
            uint32_t            num = 0;

            eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pOpc, &num);
            if (ERESULT_OK(eRc) && pOpc && (1 == num)) {
                eRc = Opcodes_Add(pOther, pOpc);
            } else {
                break;
            }
        }
        obj_Release(pEnum);
        pEnum = OBJ_NIL;

        // Copy other data from this object to other.
        
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
    int             Opcodes_Compare (
        OPCODES_DATA    *this,
        OPCODES_DATA    *pOther
    )
    {
        int             i = 0;

#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Opcodes_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //i = utf8_StrCmp(Opcode_getNameA(this), Opcode_getNameA(pOther));

        return i;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Opcodes      *pCopy = Opcodes_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPCODES object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPCODES_DATA *     Opcodes_Copy (
        OPCODES_DATA       *this
    )
    {
        OPCODES_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OPCODES_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Opcodes_New( );
        if (pOther) {
            eRc = Opcodes_Assign(this, pOther);
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

    void            Opcodes_Dealloc (
        OBJ_ID          objId
    )
    {
        OPCODES_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OPCODES_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Opcodes_setArray(this, OBJ_NIL);

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
        Opcodes      *pDeepCopy = Opcodes_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OPCODES object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OPCODES_DATA *     Opcodes_DeepyCopy (
        OPCODES_DATA       *this
    )
    {
        OPCODES_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Opcodes_New( );
        if (pOther) {
            eRc = Opcodes_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------

    ERESULT         Opcodes_DeleteA (
        OPCODES_DATA    *this,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_FAILURE;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //FIXME: eRc = szBT_DeleteA(this->pTree, pNameA);

        // Return to caller.
        return eRc;
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
    ERESULT         Opcodes_Disable (
        OPCODES_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
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
    ERESULT         Opcodes_Enable (
        OPCODES_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
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
    //                        E n u m
    //---------------------------------------------------------------

    OBJENUM_DATA *  Opcodes_Enum (
        OPCODES_DATA    *this
    )
    {
        //ERESULT         eRc;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pEnum = ObjArray_Enum(this->pArray);

        return pEnum;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    OPCODE_DATA *   Opcodes_FindA (
        OPCODES_DATA    *this,
        const
        char            *pNameA
    )
    {
        //ERESULT         eRc;
        OPCODE_DATA     *pOpc = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        //FIXME: pOpc = (OPCODE_DATA *)szBT_FindA(this->pTree, pNameA);

        // Return to caller.
        return pOpc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OPCODES_DATA *  Opcodes_Init (
        OPCODES_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(OPCODES_DATA);
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
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Opcodes_Vtbl);
#ifdef  OPCODES_JSON_SUPPORT
        JsonIn_RegisterClass(Opcode_Class());
        JsonIn_RegisterClass(ObjArray_Class());
        JsonIn_RegisterClass(this);
#endif

        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //eRc = szBT_setDeleteExit(this->pTree, (void *)Opcodes_DeleteExit, this);

#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Opcodes::sizeof(OPCODES_DATA) = %lu\n", 
                sizeof(OPCODES_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OPCODES_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Opcodes_IsEnabled (
        OPCODES_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
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
        void        *pMethod = Opcodes_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Opcodes", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Opcodes_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OPCODES_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OPCODES_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Opcodes_Class();
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
                            return Opcodes_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Opcodes_Enable;
                        }
                        break;

#ifdef  OPCODES_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Opcodes_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Opcodes_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Opcodes_ToDebugString;
                        }
#ifdef  OPCODES_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Opcodes_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Opcodes_ToDebugString)
                    return "ToDebugString";
#ifdef  OPCODES_JSON_SUPPORT
                if (pData == Opcodes_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                 S o r t  A s c e n d i n g
    //---------------------------------------------------------------

    /*!
     Sort the codes by opcode name and renumber the unique value of
     each opcode entry. The opcode entries
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Opcodes_SortAscending (
        OPCODES_DATA    *this
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        OPCODE_DATA     *pOpc;
        OPCODE_ENTRY    *pEntry;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc =   ObjArray_SortAscending(
                                     Opcodes_getArray(this),
                                     (P_OBJ_COMPARE)Opcode_Compare
                );

        iMax = ObjArray_getSize(Opcodes_getArray(this));
        for (i=0; i<iMax; ++i) {
            pOpc = ObjArray_Get(Opcodes_getArray(this), i+1);
            pEntry = Opcode_getEntry(pOpc);
            pEntry->unique = i+1;
        }

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
        ASTR_DATA      *pDesc = Opcodes_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Opcodes_ToDebugString (
        OPCODES_DATA    *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr = OBJ_NIL;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
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
                    Opcodes_getSize(this),
                    obj_getRetainCount(this)
            );

        pEnum = Opcodes_Enum(this);
        if (pEnum) {
            for (;;) {
                OPCODE_DATA     *pOpc = OBJ_NIL;
                ASTR_DATA       *pWrk = OBJ_NIL;
                eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pOpc, NULL);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
                pWrk = Opcode_ToDebugString(pOpc, indent+4);
                if (pWrk) {
                    AStr_Append(pStr, pWrk);
                    obj_Release(pWrk);
                }
            }
            obj_Release(pEnum);
            pEnum = OBJ_NIL;
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
    bool            Opcodes_Validate (
        OPCODES_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OPCODES))
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


        if (!(obj_getSize(this) >= sizeof(OPCODES_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                  V e r i f y  T r e e
    //---------------------------------------------------------------

    /*!
     Verify the binary tree used by this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Opcodes_VerifyTree (
        OPCODES_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_FAILURE;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Opcodes_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //FIXME: eRc = szBT_VerifyTree(this->pTree);

        // Return to caller.
        return eRc;
    }




    
#ifdef	__cplusplus
}
#endif


