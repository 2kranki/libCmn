// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   W32Array.c
 *  Generated 07/15/2021 10:35:28
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
#include        <W32Array_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            W32Array_task_body (
        void            *pData
    )
    {
        //W32ARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    W32ARRAY_DATA *     W32Array_Alloc (
        void
    )
    {
        W32ARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(W32ARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    W32ARRAY_DATA * W32Array_New (
        void
    )
    {
        W32ARRAY_DATA   *this;
        
        this = W32Array_Alloc( );
        if (this) {
            this = W32Array_Init(this);
        } 
        return this;
    }



    W32ARRAY_DATA * W32Array_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgV[]
    )
    {
        ERESULT         eRc;
        W32ARRAY_DATA   *pArray = OBJ_NIL;
        W32STR_DATA     *pStr = OBJ_NIL;
        int             i;

        if ((cArgs < 1) || (NULL == ppArgV)) {
            return OBJ_NIL;
        }
        pArray = W32Array_New( );
        if (pArray) {
            for (i=0; i<cArgs; ++i) {
                if (ppArgV[i]) {
                    pStr = W32Str_NewA(ppArgV[i]);
                    if (pStr) {
                        eRc = W32Array_AppendStr(pArray, pStr, NULL);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                        if (ERESULT_FAILED(eRc)) {
                            DEBUG_BREAK();
                            obj_Release(pArray);
                            pArray = OBJ_NIL;
                            break;
                        }
                    }
                    else {
                        obj_Release(pArray);
                        pArray = OBJ_NIL;
                        break;
                    }
                }
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

    OBJARRAY_DATA * W32Array_getArray (
        W32ARRAY_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            W32Array_setArray (
        W32ARRAY_DATA   *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
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
    
    uint16_t        W32Array_getPriority (
        W32ARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            W32Array_setPriority (
        W32ARRAY_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
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
    
    uint32_t        W32Array_getSize (
        W32ARRAY_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        if (this->pArray)
            return ObjArray_getSize(this->pArray);
        else
            return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  W32Array_getSuperVtbl (
        W32ARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
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

    ERESULT         W32Array_AppendStr(
        W32ARRAY_DATA   *this,
        W32STR_DATA     *pObject,
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
        if( !W32Array_Validate(this) ) {
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

        eRc = ObjArray_AppendObj(this->pArray, pObject, pIndex);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                    A p p e n d  F i l e
    //---------------------------------------------------------------

    ERESULT         W32Array_AppendUtf8File(
        W32ARRAY_DATA   *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        FILE            *pFile = NULL;
        W32CHR_T        *pRcd = NULL;
        W32CHR_T        *pRcdRead;
        W32STR_DATA     *pWrk = OBJ_NIL;
        int             maxLineLength = 1024;

        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !W32Array_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( OBJ_NIL == pPath ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (maxLineLength <= 0) {
            return ERESULT_INVALID_PARAMETER;
        }
        pRcd = mem_Malloc(maxLineLength);
        if (pRcd == NULL) {
            return ERESULT_OUT_OF_MEMORY;
        }

        pFile = fopen(Path_getData(pPath), "r");
        if (NULL == pFile) {
            mem_Free(pRcd);
            pRcd = NULL;
            return ERESULT_FILE_NOT_FOUND;
        }
        while ( (pRcdRead = fgetws(pRcd, maxLineLength, pFile)) != NULL ) {
            pWrk = W32Str_NewW32(0, pRcdRead);
            if (pWrk) {
                eRc = W32Array_AppendStr(this, pWrk, NULL);
                obj_Release(pWrk);
                pWrk = OBJ_NIL;
            }
        }
        fclose(pFile);
        pFile = NULL;

        mem_Free(pRcd);
        pRcd = NULL;
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
        ERESULT eRc = W32Array_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another W32ARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         W32Array_Assign (
        W32ARRAY_DATA   *this,
        W32ARRAY_DATA   *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this,"%s:\n", __func__);
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!W32Array_Validate(pOther)) {
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
        TRC_OBJ(this,"\tother_array: %p:\n", pOther->pArray);
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        TRC_OBJ(this,"\tthis_array: %p:\n", this->pArray);
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
        TRC_OBJ(this,"\tother_array after copy: %p:\n", pOther->pArray);

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
    int             W32Array_Compare (
        W32ARRAY_DATA     *this,
        W32ARRAY_DATA     *pOther
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
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!W32Array_Validate(pOther)) {
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
        W32Array      *pCopy = W32Array_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a W32ARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32ARRAY_DATA *     W32Array_Copy (
        W32ARRAY_DATA       *this
    )
    {
        W32ARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef W32ARRAY_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = W32Array_New( );
        if (pOther) {
            eRc = W32Array_Assign(this, pOther);
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

    void            W32Array_Dealloc (
        OBJ_ID          objId
    )
    {
        W32ARRAY_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((W32ARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        W32Array_setArray(this, OBJ_NIL);

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
        W32Array      *pDeepCopy = W32Array_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a W32ARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    W32ARRAY_DATA *  W32Array_DeepyCopy (
        W32ARRAY_DATA    *this
    )
    {
        W32ARRAY_DATA   *pOther = OBJ_NIL;
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        OBJ_IUNKNOWN    *pVtbl;
        W32STR_DATA     *pData = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = W32Array_New( );
        if (OBJ_NIL == pOther) {
            return OBJ_NIL;
        }
        
        iMax = ObjArray_getSize(this->pArray);
        for (i=0; i<iMax; ++i) {
            pData = ObjArray_Get(this->pArray, (i + 1));
            if (pData) {
                pVtbl = obj_getVtbl(pData);
                if (pVtbl->pDeepCopy) {
                    pData = pVtbl->pDeepCopy(pData);
                }
                else if (pVtbl->pCopy) {
                    pData = pVtbl->pCopy(pData);
                }
                else {
                    obj_Retain(pData);
                }
                eRc = ObjArray_AppendObj(pOther->pArray, pData, NULL);
                if (ERESULT_FAILED(eRc)) {
                    obj_Release(pOther);
                    pOther = OBJ_NIL;
                    break;
                }
            }
        }

        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e l e t e
    //---------------------------------------------------------------

    W32STR_DATA *   W32Array_DeleteFirst(
        W32ARRAY_DATA   *this
    )
    {
        W32STR_DATA     *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !W32Array_Validate(this) ) {
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


    W32STR_DATA *   W32Array_DeleteLast(
        W32ARRAY_DATA   *this
    )
    {
        W32STR_DATA     *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !W32Array_Validate(this) ) {
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
    ERESULT         W32Array_Disable (
        W32ARRAY_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
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
    ERESULT         W32Array_Enable (
        W32ARRAY_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
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
    //                        G e t
    //---------------------------------------------------------------

    W32STR_DATA *   W32Array_Get(
        W32ARRAY_DATA   *this,
        uint32_t        index       // Relative to 1
    )
    {
        W32STR_DATA     *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !W32Array_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pArray) {
            pNode = ObjArray_Get(this->pArray,index);
        }

        // Return to caller.
        return pNode;
    }


    W32STR_DATA *   W32Array_GetFirst(
        W32ARRAY_DATA   *this
    )
    {
        W32STR_DATA     *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !W32Array_Validate(this) ) {
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


    W32STR_DATA *   W32Array_GetLast(
        W32ARRAY_DATA   *this
    )
    {
        W32STR_DATA     *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !W32Array_Validate(this) ) {
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

    W32ARRAY_DATA *   W32Array_Init (
        W32ARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(W32ARRAY_DATA);
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
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of W32Array_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_W32ARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&W32Array_Vtbl);
#ifdef  W32ARRAY_JSON_SUPPORT
        JsonIn_RegisterClass(W32Array_Class());
#endif
        
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "W32Array::sizeof(W32ARRAY_DATA) = %lu\n", 
                sizeof(W32ARRAY_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(W32ARRAY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------

    ERESULT         W32Array_InsertStr(
        W32ARRAY_DATA   *this,
        uint32_t        index,
        W32STR_DATA     *pObject
    )
    {
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !W32Array_Validate(this) ) {
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
    
    ERESULT         W32Array_IsEnabled (
        W32ARRAY_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
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
        void        *pMethod = W32Array_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "W32Array", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          W32Array_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        W32ARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(W32ARRAY_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)W32Array_Class();
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
                            return W32Array_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return W32Array_Enable;
                        }
                        break;

                    case 'P':
#ifdef  W32ARRAY_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return W32Array_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return W32Array_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return W32Array_ToDebugString;
                        }
#ifdef  W32ARRAY_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return W32Array_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return W32Array_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == W32Array_ToDebugString)
                    return "ToDebugString";
#ifdef  W32ARRAY_JSON_SUPPORT
                if (pData == W32Array_ToJson)
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

    ERESULT         W32Array_SortAscending(
        W32ARRAY_DATA   *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !W32Array_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            eRc = ObjArray_SortAscending(this->pArray, (OBJ_COMPARE)&W32Str_Compare);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = W32Array_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     W32Array_ToDebugString (
        W32ARRAY_DATA      *this,
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
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!W32Array_Validate(this)) {
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
                    W32Array_getSize(this),
                    obj_getRetainCount(this)
            );

        iMax = W32Array_getSize(this);
        for (i=0; i<iMax; i++) {
            W32STR_DATA         *pStrW = W32Array_Get(this, i+1);
            if (pStrW) {
                ASTR_DATA           *pWrkStr;
                pWrkStr = W32Str_ToAStr(pStrW);
                if (indent) {
                    AStr_AppendCharRepeatA(pStr, indent+4, ' ');
                }
                AStr_AppendPrint(pStr, "%2d - \"", i+1);
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
                AStr_AppendA(pStr, "\"\n");
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
    bool            W32Array_Validate (
        W32ARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_W32ARRAY))
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


        if (!(obj_getSize(this) >= sizeof(W32ARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


