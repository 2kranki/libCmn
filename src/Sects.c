// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Sects.c
 *  Generated 12/27/2020 14:57:52
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
#include        <Sects_internal.h>
#include        <JsonIn.h>
#include        <ObjEnum_internal.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //                  D e l e t e  E x i t
    //---------------------------------------------------------------

    ERESULT         Sects_DeleteExit (
        SECTS_DATA      *this,
        void            *pKey,
        void            *pData
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
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

    ERESULT         Sects_ScanExit (
        SECTS_DATA      *this,
        const
        char            *pKey,
        SECT_DATA       *pData,
        OBJENUM_DATA    *pEnum
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // We can ignore the key since it is part of the data object.
        if (pData) {
            eRc = ObjEnum_AppendObj(pEnum, pData);
        }

        // Return to caller.
        return eRc;
    }






    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SECTS_DATA *     Sects_Alloc (
        void
    )
    {
        SECTS_DATA       *this;
        uint32_t        cbSize = sizeof(SECTS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SECTS_DATA *     Sects_New (
        void
    )
    {
        SECTS_DATA       *this;
        
        this = Sects_Alloc( );
        if (this) {
            this = Sects_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Sects_getPriority (
        SECTS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Sects_setPriority (
        SECTS_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
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
    
    uint32_t        Sects_getSize (
        SECTS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Sects_getSuperVtbl (
        SECTS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                        T r e e
    //---------------------------------------------------------------

    SZBT_DATA *     Sects_getTree (
        SECTS_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pTree;
    }


    bool            Sects_setTree (
        SECTS_DATA      *this,
        SZBT_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pTree) {
            obj_Release(this->pTree);
        }
        this->pTree = pValue;

        return true;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         Sects_Add (
        SECTS_DATA      *this,
        SECT_DATA       *pEntry
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pEntry) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (obj_IsKindOf(pEntry, OBJ_IDENT_SECT))
            ;
        else {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        obj_Retain(pEntry);
        eRc = szBT_AddA(this->pTree, &pEntry->ident, pEntry);
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pEntry);
        }

        // Return to caller.
        return eRc;
    }


    // Note: This should be kept synch'd with Sect_NewFromDataA!
    ERESULT         Sects_AddA (
        SECTS_DATA      *this,
        char            ident,
        char            type,
        uint32_t        addr,
        uint32_t        offset,
        uint32_t        len,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        SECT_DATA       *pEntry;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pEntry = Sect_NewFromDataA(ident, type, addr, offset, len, pNameA);
        if (pEntry) {
            eRc = szBT_AddA(this->pTree, &pEntry->ident, pEntry);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(pEntry);
            }
        } else {
            eRc = ERESULT_OUT_OF_MEMORY;
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
        ERESULT eRc = Sects_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SECTS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Sects_Assign (
        SECTS_DATA       *this,
        SECTS_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Sects_Validate(pOther)) {
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
    int             Sects_Compare (
        SECTS_DATA     *this,
        SECTS_DATA     *pOther
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
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Sects_Validate(pOther)) {
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
        Sects      *pCopy = Sects_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SECTS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SECTS_DATA *     Sects_Copy (
        SECTS_DATA       *this
    )
    {
        SECTS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SECTS_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Sects_New( );
        if (pOther) {
            eRc = Sects_Assign(this, pOther);
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

    void            Sects_Dealloc (
        OBJ_ID          objId
    )
    {
        SECTS_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SECTS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Sects_setTree(this, OBJ_NIL);

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
        Sects      *pDeepCopy = Sects_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SECTS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SECTS_DATA *     Sects_DeepyCopy (
        SECTS_DATA       *this
    )
    {
        SECTS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Sects_New( );
        if (pOther) {
            eRc = Sects_Assign(this, pOther);
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

    ERESULT         Sects_DeleteA (
        SECTS_DATA      *this,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = szBT_DeleteA(this->pTree, pNameA);

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
    ERESULT         Sects_Disable (
        SECTS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
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
    ERESULT         Sects_Enable (
        SECTS_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
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
    //                        E n u m
    //---------------------------------------------------------------

    OBJENUM_DATA *  Sects_Enum (
        SECTS_DATA      *this
    )
    {
        ERESULT         eRc;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pEnum = ObjEnum_New();
        if (pEnum) {
            eRc = szBT_ForEach(this->pTree, (void *)Sects_ScanExit, this, pEnum);
            if (pEnum->pArray) {
                eRc = ObjArray_SortAscending(pEnum->pArray, (void *)Sect_Compare);
            }
        }

        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------

    SECT_DATA *     Sects_FindA (
        SECTS_DATA      *this,
        const
        char            *pNameA
    )
    {
        //ERESULT         eRc;
        SECT_DATA       *pEntry = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pEntry = (SECT_DATA *)szBT_FindA(this->pTree, pNameA);

        // Return to caller.
        return pEntry;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SECTS_DATA *   Sects_Init (
        SECTS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SECTS_DATA);
        ERESULT         eRc;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SECTS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Sects_Vtbl);
#ifdef  SECTS_JSON_SUPPORT
        JsonIn_RegisterClass(Sects_Class());
#endif
        
        this->pTree = szBT_New( );
        if (OBJ_NIL == this->pTree) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        eRc = szBT_setDeleteExit(this->pTree, (void *)Sects_DeleteExit, this);

#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Sects::sizeof(SECTS_DATA) = %lu\n", 
                sizeof(SECTS_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SECTS_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Sects_IsEnabled (
        SECTS_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
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
        void        *pMethod = Sects_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Sects", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Sects_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SECTS_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SECTS_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Sects_Class();
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
                            return Sects_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Sects_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SECTS_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Sects_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Sects_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Sects_ToDebugString;
                        }
#ifdef  SECTS_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Sects_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Sects_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Sects_ToDebugString)
                    return "ToDebugString";
#ifdef  SECTS_JSON_SUPPORT
                if (pData == Sects_ToJson)
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
        ASTR_DATA      *pDesc = Sects_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sects_ToDebugString (
        SECTS_DATA      *this,
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
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sects_Validate(this)) {
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
                    Sects_getSize(this),
                    obj_getRetainCount(this)
            );

        pEnum = Sects_Enum(this);
        if (pEnum) {
            for (;;) {
                SECT_DATA       *pEntry = OBJ_NIL;
                ASTR_DATA       *pWrk = OBJ_NIL;
                eRc = ObjEnum_Next(pEnum, 1, (OBJ_ID *)&pEntry, NULL);
                if (ERESULT_FAILED(eRc)) {
                    break;
                }
                if (pEntry) {
                    pWrk = Sect_ToDebugString(pEntry, indent+4);
                    if (pWrk) {
                        AStr_Append(pStr, pWrk);
                        obj_Release(pWrk);
                    }
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
    bool            Sects_Validate (
        SECTS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SECTS))
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


        if (!(obj_getSize(this) >= sizeof(SECTS_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


