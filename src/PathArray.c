// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   PathArray.c
 *  Generated 12/23/2021 16:41:21
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
#include        <PathArray_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            PathArray_task_body (
        void            *pData
    )
    {
        //PATHARRAY_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PATHARRAY_DATA *     PathArray_Alloc (
        void
    )
    {
        PATHARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(PATHARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    PATHARRAY_DATA *     PathArray_New (
        void
    )
    {
        PATHARRAY_DATA       *this;
        
        this = PathArray_Alloc( );
        if (this) {
            this = PathArray_Init(this);
        } 
        return this;
    }



    PATHARRAY_DATA * PathArray_NewFromListA (
        const
        char            *pPathA,
        ...
    )
    {
        PATHARRAY_DATA  *pArray = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        va_list         pList;

        if (NULL == pPathA) {
            return OBJ_NIL;
        }
        pArray = PathArray_New( );
        if (pArray) {
            pPath = Path_NewA(pPathA);
            if (pPath) {
                PathArray_AppendPath(pArray, pPath, NULL);
                obj_Release(pPath);
                pPath = OBJ_NIL;
            }
            va_start(pList, pPathA);
            for (;;) {
                char        *pStrA = va_arg(pList, char *);
                if (pStrA) {
                    pPath = Path_NewA(pStrA);
                    if (pPath) {
                        PathArray_AppendPath(pArray, pPath, NULL);
                        obj_Release(pPath);
                        pPath = OBJ_NIL;
                    }
                }
                else
                    break;
            }
            va_end(pList);
        }

        return pArray;
    }


    PATHARRAY_DATA * PathArray_NewFromList (
        va_list         pList
    )
    {
        PATHARRAY_DATA  *pArray = OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;

        pArray = PathArray_New( );
        if (pArray) {
            for (;;) {
                char        *pPathA = va_arg(pList, char *);
                if (pPathA) {
                    pPath = Path_NewA(pPathA);
                    if (pPath) {
                        PathArray_AppendPath(pArray, pPath, NULL);
                        obj_Release(pPath);
                        pPath = OBJ_NIL;
                    }
                }
                else
                    break;
            }
        }

        return pArray;
    }


    PATHARRAY_DATA * PathArray_NewFromPath (
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        PATHARRAY_DATA  *pArray = OBJ_NIL;

        pArray = PathArray_New( );
        if (pArray) {
            eRc = PathArray_SplitDir(pArray, pPath);
            if (ERESULT_FAILED(eRc)) {
                DEBUG_BREAK();
                obj_Release(pArray);
                pArray = OBJ_NIL;
            }
        }

        return pArray;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          A r r a y
    //---------------------------------------------------------------

    OBJARRAY_DATA * PathArray_getArray (
        PATHARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            PathArray_setArray (
        PATHARRAY_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
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
    //                          L o g
    //---------------------------------------------------------------

#ifdef   PATHARRAY_LOG
    bool            PathArray_setLog (
        PATHARRAY_DATA   *this,
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pLog = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        PathArray_getPriority (
        PATHARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            PathArray_setPriority (
        PATHARRAY_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
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
    
    uint32_t        PathArray_getSize (
        PATHARRAY_DATA       *this
    )
    {
        uint32_t            i = 0;

#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->pArray) {
            i = ObjArray_getSize(this->pArray);
        }

        return i;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_DATA *      PathArray_getSuper (
        PATHARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }

    OBJ_IUNKNOWN *  PathArray_getSuperVtbl (
        PATHARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
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

    ERESULT         PathArray_AppendPath(
        PATHARRAY_DATA  *this,
        PATH_DATA       *pPath,
        uint32_t        *pIndex
    )
    {
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (pPath && obj_IsKindOf(pPath, OBJ_IDENT_PATH)) {
        } else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        eRc = ObjArray_AppendObj(this->pArray, pPath, pIndex);

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
        ERESULT eRc = PathArray_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another PATHARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         PathArray_Assign (
        PATHARRAY_DATA       *this,
        PATHARRAY_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!PathArray_Validate(pOther)) {
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
        //pOther->x     = this->x; 

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
    int             PathArray_Compare (
        PATHARRAY_DATA     *this,
        PATHARRAY_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  PATHARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = PathArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!PathArray_Validate(pOther)) {
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
        PathArray      *pCopy = PathArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PATHARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PATHARRAY_DATA *     PathArray_Copy (
        PATHARRAY_DATA       *this
    )
    {
        PATHARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef PATHARRAY_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = PathArray_New( );
        if (pOther) {
            eRc = PathArray_Assign(this, pOther);
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

    void            PathArray_Dealloc (
        OBJ_ID          objId
    )
    {
        PATHARRAY_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((PATHARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        PathArray_setArray(this, OBJ_NIL);

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
        PathArray      *pDeepCopy = PathArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a PATHARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    PATHARRAY_DATA *     PathArray_DeepCopy (
        PATHARRAY_DATA       *this
    )
    {
        PATHARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = PathArray_New( );
        if (pOther) {
            eRc = PathArray_Assign(this, pOther);
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

    PATH_DATA *     PathArray_DeleteFirst(
        PATHARRAY_DATA  *this
    )
    {
        PATH_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_DeleteFirst(this->pArray);
        }

        // Return to caller.
        return pNode;
    }


    PATH_DATA *     PathArray_DeleteLast(
        PATHARRAY_DATA  *this
    )
    {
        PATH_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_DeleteLast(this->pArray);
        }

        // Return to caller.
        return pNode;
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
    ERESULT         PathArray_Disable (
        PATHARRAY_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PATHARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = PathArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
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
    ERESULT         PathArray_Enable (
        PATHARRAY_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PATHARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = PathArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   PATHARRAY_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n u m
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    OBJENUM_DATA *  PathArray_Enum (
        PATHARRAY_DATA  *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pEnum;
        }
#endif

        pEnum = ObjArray_Enum(this->pArray);

        // Return to caller.
        return pEnum;
    }



    //---------------------------------------------------------------
    //                        G e t
    //---------------------------------------------------------------

    PATH_DATA *     PathArray_Get (
        PATHARRAY_DATA  *this,
        uint32_t        index       // Relative to 1
    )
    {
        PATH_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_Get(this->pArray, index);
        }

        // Return to caller.
        return pNode;
    }


    PATH_DATA *     PathArray_GetFirst (
        PATHARRAY_DATA  *this
    )
    {
        PATH_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_GetFirst(this->pArray);
        }

        // Return to caller.
        return pNode;
    }


    PATH_DATA *     PathArray_GetLast(
        PATHARRAY_DATA  *this
    )
    {
        PATH_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_GetLast(this->pArray);
        }

        // Return to caller.
        return pNode;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PATHARRAY_DATA *   PathArray_Init (
        PATHARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(PATHARRAY_DATA);
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

        //this = (OBJ_ID)ObjArray_Init((OBJARRAY_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of PathArray_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_PATHARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&PathArray_Vtbl);
#ifdef  PATHARRAY_JSON_SUPPORT
        JsonIn_RegisterClass(PathArray_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "PathArray::sizeof(PATHARRAY_DATA) = %lu\n", 
                sizeof(PATHARRAY_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(PATHARRAY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------

    ERESULT         PathArray_InsertStr(
        PATHARRAY_DATA  *this,
        uint32_t        index,
        PATH_DATA       *pObject
    )
    {
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            this->pArray = ObjArray_New();
            if (OBJ_NIL == this->pArray) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        eRc = ObjArray_InsertObj(this->pArray, index, pObject);

        // Return to caller.
        return eRc;
    }


    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         PathArray_IsEnabled (
        PATHARRAY_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  PATHARRAY_SINGLETON
        if (OBJ_NIL == this) {
            this = PathArray_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
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
        void        *pMethod = PathArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "PathArray", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          PathArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        PATHARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(PATHARRAY_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)PathArray_Class();
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
                            return PathArray_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return PathArray_Enable;
                        }
                        break;

                    case 'P':
#ifdef  PATHARRAY_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return PathArray_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return PathArray_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return PathArray_ToDebugString;
                        }
#ifdef  PATHARRAY_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return PathArray_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return PathArray_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == PathArray_ToDebugString)
                    return "ToDebugString";
#ifdef  PATHARRAY_JSON_SUPPORT
                if (pData == PathArray_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                         S o r t
    //---------------------------------------------------------------

    ERESULT         PathArray_SortAscending(
        PATHARRAY_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            eRc = ObjArray_SortAscending(this->pArray, (OBJ_COMPARE)&Path_Compare);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     S p l i t  D i r
    //---------------------------------------------------------------

    ERESULT         PathArray_SplitDir(
        PATHARRAY_DATA  *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        uint32_t        index;
        uint32_t        begin;
        uint32_t        end;
        uint32_t        begDir = 1;
        W32CHR_T        chr;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !PathArray_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pPath && obj_IsKindOf(pPath, OBJ_IDENT_PATH)) {
        } else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Scan off the directory entries except for maybe the right-most
        // directory entry.
        chr = AStr_CharGetW32((ASTR_DATA *)pPath, begDir);
        if ('/' == chr) {
            begDir++;
        }
        for (;;) {
            index = begDir;
            begin = begDir;
            eRc = AStr_CharFindNextW32((ASTR_DATA *)pPath, &index, '/');
            if (ERESULT_OK(eRc)) {      // *** Directory is present ***
                end = index - 1;
                if (begin <= end) {
                    eRc =   AStr_Mid(
                                    (ASTR_DATA *)pPath,
                                    begin,
                                    (end -  begin + 1),
                                    &pStr
                            );
                    if (ERESULT_OK(eRc)) {
                        PATH_DATA       *pWrk = Path_NewFromAStr(pStr);
                        Path_Clean(pWrk);
                        eRc = PathArray_AppendPath(this, pWrk, NULL);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                        obj_Release(pWrk);
                    }
                } else if (begin == index) {
                    PATH_DATA       *pWrk = Path_NewA("/");
                    eRc = PathArray_AppendPath(this, pWrk, NULL);
                    obj_Release(pWrk);
                }
                begDir = index + 1;
            } else {
                break;
            }
        }

        // We assume that the remaining is the last directory entry if any.
        begin = begDir;
        end = AStr_getLength((ASTR_DATA *)pPath);
        if (begin <= end) {
            eRc =   AStr_Mid(
                            (ASTR_DATA *)pPath,
                            begin,
                            (end -  begin + 1),
                            &pStr
                    );
            if (ERESULT_OK(eRc)) {
                PATH_DATA       *pWrk = Path_NewFromAStr(pStr);
                Path_Clean(pWrk);
                eRc = PathArray_AppendPath(this, pWrk, NULL);
                obj_Release(pStr);
                pStr = OBJ_NIL;
                obj_Release(pWrk);
            }
        } else if (begin == index) {
            PATH_DATA       *pWrk = Path_NewA("/");
            eRc = PathArray_AppendPath(this, pWrk, NULL);
            obj_Release(pWrk);
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  D i r
    //---------------------------------------------------------------

    /*!
     Create a directory string from the contents of this object.
     @param     this    object pointer
     @return    If successful, a Path object which must be released containing the
                directory, otherwise OBJ_NIL.
     @warning  Remember to release the returned Path object.
     */
    PATH_DATA *     PathArray_ToDir (
        PATHARRAY_DATA  *this
    )
    {
        //ERESULT         eRc;
        PATH_DATA       *pPath;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pPath = Path_NewA("/");
        if (OBJ_NIL == pPath) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        if (this->pArray) {
            iMax = ObjArray_getSize(this->pArray);
            for (i=0; i<iMax; i++) {
                PATH_DATA       *pWrk = ObjArray_Get(this->pArray, i+1);
                if (pWrk) {
                    AStr_AppendA((ASTR_DATA *)pPath, Path_getData(pWrk));
                }
                AStr_AppendA((ASTR_DATA *)pPath, "/");
            }
        }

        Path_Clean(pPath);
        return pPath;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = PathArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     PathArray_ToDebugString (
        PATHARRAY_DATA  *this,
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
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!PathArray_Validate(this)) {
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
                    PathArray_getSize(this),
                    obj_getRetainCount(this)
            );

        if (this->pArray) {
            for (i=0; i<ObjArray_getSize(this->pArray); i++) {
                PATH_DATA       *pWrk = ObjArray_Get(this->pArray, i+1);
                if (pWrk) {
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent+4, ' ');
                    }
                    AStr_AppendPrint(pStr, "%3d \"%s\"\n", i+1, Path_getData(pWrk));
                }
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
    bool            PathArray_Validate (
        PATHARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_PATHARRAY))
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


        if (!(obj_getSize(this) >= sizeof(PATHARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


