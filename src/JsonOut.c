// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   JsonOut.c
 *	Generated 01/25/2020 21:31:26
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
#include        <JsonOut_internal.h>
#include        <trace.h>
#include        <utf8_internal.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            JsonOut_task_body (
        void            *pData
    )
    {
        //JSONOUT_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    JSONOUT_DATA *     JsonOut_Alloc (
        void
    )
    {
        JSONOUT_DATA       *this;
        uint32_t        cbSize = sizeof(JSONOUT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    void            JsonOut_Append_bool (
        const
        char            *pNameA,
        bool            flag,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %s,\n", pNameA, (flag ? "true" : "false"));
        }
    }


    void            JsonOut_Append_i16 (
        const
        char            *pNameA,
        int16_t         num,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %ld,\n", pNameA, num);
        }
    }


    void            JsonOut_Append_i16_array (
        const
        char            *pNameA,
        uint16_t        num,            // Number of entries
        const
        int16_t         *pNum,          // First Entry Pointer
        ASTR_DATA       *pStr
    )
    {
        uint32_t        i;

        if (num && pStr && pNameA) {
            AStr_AppendPrint(pStr,
                             "\t\"%s\":{\n"
                             "\t\ttype:I16Array,\n"
                             "\t\tsize:%d,\n"
                             "\t\tdata:[\n\t\t\t",
                             pNameA,
                             num
            );
            for (i=0; i<(num - 1); i++,pNum++) {
                AStr_AppendPrint(pStr, "%d,", *pNum);
                if ((i > 0) && (0== (i % 8))) {
                    AStr_AppendPrint(pStr, "\n\t\t\t");
                }
            }
            if ((i > 0) && (0== (i % 8))) {
                AStr_AppendPrint(pStr, "\n\t\t\t");
            }
            AStr_AppendPrint(pStr, "%d\n\t\t]\n", *pNum);
            AStr_AppendPrint(pStr, "\t},\n");
        }
    }



    void            JsonOut_Append_i32 (
        const
        char            *pNameA,
        int32_t         num,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %ld,\n", pNameA, num);
        }
    }

    void            JsonOut_Append_i32_array (
        const
        char            *pNameA,
        uint32_t        num,            // Number of entries
        const
        int32_t         *pNum,          // First Entry Pointer
        ASTR_DATA       *pStr
    )
    {
        uint32_t        i;

        if (num && pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\":[\n\t\t", pNameA);
            for (i=0; i<(num - 1); i++,pNum++) {
                AStr_AppendPrint(pStr, "%d, ", *pNum);
                if ((i > 0) && (0== (i % 8))) {
                    AStr_AppendPrint(pStr, "\n\t\t");
                }
            }
            if ((i > 0) && (0== (i % 8))) {
                AStr_AppendPrint(pStr, "\n\t\t");
            }
            AStr_AppendPrint(pStr, "%d\n", *pNum);
            AStr_AppendPrint(pStr, "\t],\n");
        }
    }



    void            JsonOut_Append_i64 (
        const
        char            *pNameA,
        int64_t         num,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %lld,\n", pNameA, num);
        }
    }


    void            JsonOut_Append_Object (
        const
        char            *pNameA,
        OBJ_ID          pObj,
        ASTR_DATA       *pStr
    )
    {
        void *          (*pQueryInfo)(
            OBJ_ID          objId,
            uint32_t        type,
            void            *pData
        );
        ASTR_DATA *     (*pToJson)(
            OBJ_ID          objId
        );
        ASTR_DATA       *pWrkStr;

        if (pObj && pStr) {
           pQueryInfo = obj_getVtbl(pObj)->pQueryInfo;
           if (pQueryInfo) {
               pToJson =   (*pQueryInfo)(
                                         pObj,
                                         OBJ_QUERYINFO_TYPE_METHOD,
                                         "ToJson"
                                         );
               if (pToJson) {
                   pWrkStr = (*pToJson)(pObj);
                   if (pWrkStr) {
                       if (pNameA) {
                           AStr_AppendPrint(pStr, "\t\"%s\": ", pNameA);
                       }
                       AStr_Append(pStr, pWrkStr);
                       obj_Release(pWrkStr);
                       pWrkStr = OBJ_NIL;
                       AStr_AppendA(pStr, ",\n");
                   }
               }
           }
        }
    }


    void            JsonOut_Append_AStr (
        const
        char            *pNameA,
        ASTR_DATA       *pObj,
        ASTR_DATA       *pStr
    )
    {
        ASTR_DATA       *pWrkStr;

        if (pObj && pStr && pNameA) {
            pWrkStr = AStr_ToJson(pObj);
            if (pWrkStr) {
                       AStr_AppendPrint(pStr, "\t\"%s\": ", pNameA);
                       AStr_Append(pStr, pWrkStr);
                       obj_Release(pWrkStr);
                       pWrkStr = OBJ_NIL;
                       AStr_AppendA(pStr, ",\n");
            }
        }
    }


    void            JsonOut_Append_AStr_array (
        const
        char            *pNameA,
        ASTRARRAY_DATA  *pArray,
        ASTR_DATA       *pStr
    )
    {
        uint32_t        i;
        uint32_t        iMax;

        if (pStr && pArray) {
            AStr_AppendPrint(pStr, "\t\"%s\":[\n\t\t", pNameA);
            iMax = AStrArray_getSize(pArray);
            if (iMax) {
                for (i=0; i<(iMax - 1); i++) {
                    ASTR_DATA       *pWrk = AStrArray_Get(pArray, i+1);
                    ASTR_DATA       *pWrk2;
                    if (pWrk) {
                        pWrk2 = AStr_ToChrCon(pWrk);
                        if (pWrk2) {
                            AStr_AppendPrint(pStr, "\"%s\",\n\t\t", AStr_getData(pWrk2));
                            obj_Release(pWrk2);
                            pWrk2 = OBJ_NIL;
                        }
                    }
                }
                {
                    ASTR_DATA       *pWrk = AStrArray_Get(pArray, i+1);
                    ASTR_DATA       *pWrk2;
                    if (pWrk) {
                        pWrk2 = AStr_ToChrCon(pWrk);
                        if (pWrk2) {
                            AStr_AppendPrint(pStr, "\"%s\"\n", AStr_getData(pWrk2));
                            obj_Release(pWrk2);
                            pWrk2 = OBJ_NIL;
                        }
                    }
                }
            }
            AStr_AppendPrint(pStr, "\t],\n");
        }
    }


    void            JsonOut_Append_StrA (
        const
        char            *pNameA,
        const
        char            *pStrA,
        ASTR_DATA       *pStr
    )
    {
        ASTR_DATA       *pWrk;

        if (pStrA && pStr && pNameA) {
            pWrk = AStr_NewA(pStrA);
            if (pWrk) {
                JsonOut_Append_AStr(pNameA, pWrk, pStr);
                obj_Release(pWrk);
            }
        }
    }


    void            JsonOut_Append_StrW32 (
        const
        char            *pNameA,
        const
        W32CHR_T        *pObjW32,
        ASTR_DATA       *pStr
    )
    {
        ASTR_DATA       *pWrk;

        if (pObjW32 && pStr && pNameA) {
            pWrk = AStr_NewW32(pObjW32);
            if (pWrk) {
                JsonOut_Append_AStr(pNameA, pWrk, pStr);
                obj_Release(pWrk);
            }
        }
    }


    void            JsonOut_Append_u8 (
        const
        char            *pNameA,
        uint8_t         num,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %u,\n", pNameA, num);
        }
    }


    void            JsonOut_Append_u8_array (
        const
        char            *pNameA,
        uint32_t        num,            // Number of entries
        const
        uint8_t         *pNum,          // First Entry Pointer
        ASTR_DATA       *pStr
    )
    {
        uint32_t        i;

        if (num && pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\":[\n\t\t", pNameA);
            for (i=0; i<(num - 1); i++,pNum++) {
                AStr_AppendPrint(pStr, "%u, ", *pNum);
                if ((i > 0) && (0== (i % 8))) {
                    AStr_AppendPrint(pStr, "\n\t\t");
                }
            }
            if ((i > 0) && (0== (i % 8))) {
                AStr_AppendPrint(pStr, "\n\t\t");
            }
            AStr_AppendPrint(pStr, "%u\n", *pNum);
            AStr_AppendPrint(pStr, "\t],\n");
        }
    }


    void            JsonOut_Append_u16 (
        const
        char            *pNameA,
        uint16_t        num,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %u,\n", pNameA, num);
        }
    }


    void            JsonOut_Append_u32 (
        const
        char            *pNameA,
        uint32_t        num,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %lu,\n", pNameA, num);
        }
    }



    void            JsonOut_Append_u64 (
        const
        char            *pNameA,
        uint64_t        num,
        ASTR_DATA       *pStr
    )
    {
        if (pStr && pNameA) {
            AStr_AppendPrint(pStr, "\t\"%s\": %lu,\n", pNameA, num);
        }
    }



    void            JsonOut_Append_utf8 (
        const
        char            *pNameA,
        const
        char            *pStrA,
        ASTR_DATA       *pStr
    )
    {
        ASTR_DATA       *pWrkStr;

        if (pStrA && pStr && pNameA) {
            pWrkStr = utf8_DataToJson(pStrA);
            AStr_AppendPrint(pStr, "\t\"%s\": %s,\n", pNameA, AStr_getData(pWrkStr));
            obj_Release(pWrkStr);
            pWrkStr = 0;
        }
    }


    JSONOUT_DATA *     JsonOut_New (
        void
    )
    {
        JSONOUT_DATA       *this;
        
        this = JsonOut_Alloc( );
        if (this) {
            this = JsonOut_Init(this);
        } 
        return this;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        JsonOut_getPriority (
        JSONOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            JsonOut_setPriority (
        JSONOUT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
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
    
    uint32_t        JsonOut_getSize (
        JSONOUT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * JsonOut_getStr (
        JSONOUT_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        JsonOut_setStr (
        JSONOUT_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
#endif
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  JsonOut_getSuperVtbl (
        JSONOUT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
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
        ERESULT eRc = JsonOut_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another JSONOUT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         JsonOut_Assign (
        JSONOUT_DATA		*this,
        JSONOUT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!JsonOut_Validate(pOther)) {
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
        
        //goto eom;

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
    int             JsonOut_Compare (
        JSONOUT_DATA    *this,
        JSONOUT_DATA    *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!JsonOut_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        JsonOut      *pCopy = JsonOut_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a JSONOUT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    JSONOUT_DATA *     JsonOut_Copy (
        JSONOUT_DATA       *this
    )
    {
        JSONOUT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef JSONOUT_IS_CONSTANT
        obj_Retain(this);
        pOther = this;
#else
        pOther = JsonOut_New( );
        if (pOther) {
            eRc = JsonOut_Assign(this, pOther);
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

    void            JsonOut_Dealloc (
        OBJ_ID          objId
    )
    {
        JSONOUT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((JSONOUT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        JsonOut_setStr(this, OBJ_NIL);

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
        JsonOut      *pDeepCopy = JsonOut_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a JSONOUT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    JSONOUT_DATA *     JsonOut_DeepyCopy (
        JSONOUT_DATA       *this
    )
    {
        JSONOUT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = JsonOut_New( );
        if (pOther) {
            eRc = JsonOut_Assign(this, pOther);
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
    ERESULT         JsonOut_Disable (
        JSONOUT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
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
    ERESULT         JsonOut_Enable (
        JSONOUT_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
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

    JSONOUT_DATA *   JsonOut_Init (
        JSONOUT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(JSONOUT_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_JSONOUT);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&JsonOut_Vtbl);
        
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
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "JsonOut::sizeof(JSONOUT_DATA) = %lu\n", 
                sizeof(JSONOUT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(JSONOUT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         JsonOut_IsEnabled (
        JSONOUT_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
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
        void        *pMethod = JsonOut_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "JsonOut", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          JsonOut_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        JSONOUT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(JSONOUT_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)JsonOut_Class();
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
                            return JsonOut_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return JsonOut_Enable;
                        }
                        break;

#ifdef  JSONOUT_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return JsonOut_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return JsonOut_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return JsonOut_ToDebugString;
                        }
#ifdef  JSONOUT_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return JsonOut_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == JsonOut_ToDebugString)
                    return "ToDebugString";
#ifdef  JSONOUT_JSON_SUPPORT
                if (pData == JsonOut_ToJson)
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
        ASTR_DATA      *pDesc = JsonOut_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     JsonOut_ToDebugString (
        JSONOUT_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonOut_Validate(this)) {
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
                    JsonOut_getSize(this),
                    obj_getRetainCount(this)
            );

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
    bool            JsonOut_Validate (
        JSONOUT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_JSONOUT))
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


        if (!(obj_getSize(this) >= sizeof(JSONOUT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


