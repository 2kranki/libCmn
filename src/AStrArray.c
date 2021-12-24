// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   AStrArray.c
 *  Generated 04/11/2021 10:41:38
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
#include        <AStrArray_internal.h>
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
    void            AStrArray_task_body (
        void            *pData
    )
    {
        //ASTRARRAY_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ASTRARRAY_DATA *     AStrArray_Alloc (
        void
    )
    {
        ASTRARRAY_DATA       *this;
        uint32_t        cbSize = sizeof(ASTRARRAY_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ASTRARRAY_DATA *     AStrArray_New (
        void
    )
    {
        ASTRARRAY_DATA       *this;
        
        this = AStrArray_Alloc( );
        if (this) {
            this = AStrArray_Init(this);
        } 
        return this;
    }


    ASTRARRAY_DATA *    AStrArray_NewFromArgV(
        int             cArgs,
        const
        char            *ppArgV[]
    )
    {
        ASTRARRAY_DATA  *pArray = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        int             i;

        if ((cArgs < 1) || (NULL == ppArgV)) {
            return OBJ_NIL;
        }
        pArray = AStrArray_New( );
        if (pArray) {
            for (i=0; i<cArgs; ++i) {
                if (ppArgV[i]) {
                    pStr = AStr_NewA(ppArgV[i]);
                    if (pStr) {
                        AStrArray_AppendStr(pArray, pStr, NULL);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
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


    ASTRARRAY_DATA *    AStrArray_NewFromArrayA(
        const
        char            *ppArgV[]
    )
    {
        ASTRARRAY_DATA  *pArray = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;

        if (NULL == ppArgV) {
            return OBJ_NIL;
        }
        pArray = AStrArray_New( );
        if (pArray) {
            while (*ppArgV) {
                pStr = AStr_NewA(*ppArgV);
                if (pStr) {
                    AStrArray_AppendStr(pArray, pStr, NULL);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
                else {
                    obj_Release(pArray);
                    pArray = OBJ_NIL;
                    break;
                }
                ++ppArgV;
            }
        }

        return pArray;
    }



    ASTRARRAY_DATA * AStrArray_NewFromListA (
        const
        char            *pStrA,
        ...
    )
    {
        ASTRARRAY_DATA  *pArray = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        va_list         pList;

        if (NULL == pStrA) {
            return OBJ_NIL;
        }
        pArray = AStrArray_New( );
        if (pArray) {
            pStr = AStr_NewA(pStrA);
            if (pStr) {
                AStrArray_AppendStr(pArray, pStr, NULL);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            va_start(pList, pStrA);
            for (;;) {
                char        *pStrA = va_arg(pList, char *);
                if (pStrA) {
                    pStr = AStr_NewA(pStrA);
                    if (pStr) {
                        AStrArray_AppendStr(pArray, pStr, NULL);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
                else
                    break;
            }
            va_end(pList);
        }

        return pArray;
    }


    ASTRARRAY_DATA * AStrArray_NewFromList (
        va_list         pList
    )
    {
        ASTRARRAY_DATA  *pArray = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;

        pArray = AStrArray_New( );
        if (pArray) {
            for (;;) {
                char        *pStrA = va_arg(pList, char *);
                if (pStrA) {
                    pStr = AStr_NewA(pStrA);
                    if (pStr) {
                        AStrArray_AppendStr(pArray, pStr, NULL);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    }
                }
                else
                    break;
            }
        }

        return pArray;
    }



    ASTRARRAY_DATA * AStrArray_NewFromUtf8File(
        PATH_DATA       *pPath,
        int             maxLineLength
    )
    {
        ASTRARRAY_DATA  *this =  OBJ_NIL;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == pPath) {
            return this;
        }

        this = AStrArray_New( );
        if (this) {
            eRc = AStrArray_AppendUtf8File(this, pPath, maxLineLength);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        // Return to caller.
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                           A r r a y
    //---------------------------------------------------------------

    OBJARRAY_DATA * AStrArray_getArray (
        ASTRARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            AStrArray_setArray (
        ASTRARRAY_DATA  *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
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
    
    uint32_t        AStrArray_getSize (
        ASTRARRAY_DATA       *this
    )
    {
        uint32_t            i = 0;

#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
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
    
    OBJARRAY_DATA * AStrArray_getSuper (
        ASTRARRAY_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    OBJ_IUNKNOWN *  AStrArray_getSuperVtbl (
        ASTRARRAY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
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

    ERESULT         AStrArray_AppendStr(
        ASTRARRAY_DATA  *this,
        ASTR_DATA       *pObject,
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
        if( !AStrArray_Validate(this) ) {
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

    ERESULT         AStrArray_AppendUtf8File(
        ASTRARRAY_DATA  *this,
        PATH_DATA       *pPath,
        int             maxLineLength
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        FILE            *pFile = NULL;
        char            *pRcd = NULL;
        char            *pRcdRead;
        ASTR_DATA       *pWrk = OBJ_NIL;

        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !AStrArray_Validate( this ) ) {
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
        while ( (pRcdRead = fgets(pRcd, maxLineLength, pFile)) != NULL ) {
            pWrk = AStr_NewA(pRcdRead);
            if (pWrk) {
                eRc = AStrArray_AppendStr(this, pWrk, NULL);
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
        ERESULT eRc = AStrArray_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another ASTRARRAY object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         AStrArray_Assign (
        ASTRARRAY_DATA       *this,
        ASTRARRAY_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!AStrArray_Validate(pOther)) {
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
    int             AStrArray_Compare (
        ASTRARRAY_DATA     *this,
        ASTRARRAY_DATA     *pOther
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
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!AStrArray_Validate(pOther)) {
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
        AStrArray      *pCopy = AStrArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ASTRARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ASTRARRAY_DATA *     AStrArray_Copy (
        ASTRARRAY_DATA       *this
    )
    {
        ASTRARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef ASTRARRAY_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = AStrArray_New( );
        if (pOther) {
            eRc = AStrArray_Assign(this, pOther);
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

    void            AStrArray_Dealloc (
        OBJ_ID          objId
    )
    {
        ASTRARRAY_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ASTRARRAY_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        AStrArray_setArray(this, OBJ_NIL);

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
        AStrArray      *pDeepCopy = AStrArray_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ASTRARRAY object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ASTRARRAY_DATA *     AStrArray_DeepyCopy (
        ASTRARRAY_DATA       *this
    )
    {
        ASTRARRAY_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = AStrArray_New( );
        if (pOther) {
            eRc = AStrArray_Assign(this, pOther);
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

    ASTR_DATA *     AStrArray_DeleteFirst(
        ASTRARRAY_DATA    *this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
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


    ASTR_DATA *     AStrArray_DeleteLast(
        ASTRARRAY_DATA    *this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
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
    ERESULT         AStrArray_Disable (
        ASTRARRAY_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
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
    ERESULT         AStrArray_Enable (
        ASTRARRAY_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
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
    //                          E n u m
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    OBJENUM_DATA *  AStrArray_Enum (
        ASTRARRAY_DATA  *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        OBJENUM_DATA    *pEnum = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
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

    ASTR_DATA *     AStrArray_Get (
        ASTRARRAY_DATA  *this,
        uint32_t        index       // Relative to 1
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
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


    ASTR_DATA *     AStrArray_GetFirst (
        ASTRARRAY_DATA  *this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
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


    ASTR_DATA *     AStrArray_GetLast(
        ASTRARRAY_DATA    *this
    )
    {
        ASTR_DATA       *pNode = OBJ_NIL;

        // Do initialization.
        if (NULL == this) {
            return OBJ_NIL;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
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

    ASTRARRAY_DATA *   AStrArray_Init (
        ASTRARRAY_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ASTRARRAY_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ASTRARRAY);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&AStrArray_Vtbl);
#ifdef  ASTRARRAY_JSON_SUPPORT
        JsonIn_RegisterClass(AStrArray_Class());
#endif
        
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
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "AStrArray::sizeof(ASTRARRAY_DATA) = %lu\n", 
                sizeof(ASTRARRAY_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(ASTRARRAY_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                          I n s e r t
    //---------------------------------------------------------------

    ERESULT         AStrArray_InsertStr(
        ASTRARRAY_DATA    *this,
        uint32_t        index,
        ASTR_DATA       *pObject
    )
    {
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
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
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         AStrArray_IsEnabled (
        ASTRARRAY_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
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
        void        *pMethod = AStrArray_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "AStrArray", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          AStrArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ASTRARRAY_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!AStrArray_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(ASTRARRAY_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)AStrArray_Class();
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
                            return AStrArray_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return AStrArray_Enable;
                        }
                        break;

                    case 'P':
#ifdef  ASTRARRAY_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return AStrArray_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return AStrArray_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return AStrArray_ToDebugString;
                        }
#ifdef  ASTRARRAY_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return AStrArray_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return AStrArray_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == AStrArray_ToDebugString)
                    return "ToDebugString";
#ifdef  ASTRARRAY_JSON_SUPPORT
                if (pData == AStrArray_ToJson)
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

    ERESULT         AStrArray_SortAscending(
        ASTRARRAY_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        if (NULL == this) {
            return false;
        }
#ifdef NDEBUG
#else
        if( !AStrArray_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pArray) {
            eRc = ObjArray_SortAscending(this->pArray, (OBJ_COMPARE)&AStr_Compare);
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
        ASTR_DATA      *pDesc = AStrArray_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     AStrArray_ToDebugString (
        ASTRARRAY_DATA      *this,
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
        if (!AStrArray_Validate(this)) {
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
                    AStrArray_getSize(this),
                    obj_getRetainCount(this)
            );

        if (this->pArray) {
            for (i=0; i<ObjArray_getSize(this->pArray); i++) {
                ASTR_DATA       *pWrk = ObjArray_Get(this->pArray, i+1);
                if (pWrk) {
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent+4, ' ');
                    }
                    AStr_AppendPrint(pStr, "%3d %s\n", i+1, AStr_getData(pWrk));
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
    bool            AStrArray_Validate (
        ASTRARRAY_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_ASTRARRAY))
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


        if (!(obj_getSize(this) >= sizeof(ASTRARRAY_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


