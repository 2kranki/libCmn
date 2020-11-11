// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   JsonPP.c
 *	Generated 01/25/2020 21:40:07
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
#include        <JsonPP_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            JsonPP_task_body (
        void            *pData
    )
    {
        //JSONPP_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    JSONPP_DATA *   JsonPP_Alloc (
        void
    )
    {
        JSONPP_DATA     *this;
        uint32_t        cbSize = sizeof(JSONPP_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    JSONPP_DATA *   JsonPP_New (
        void
    )
    {
        JSONPP_DATA     *this;
        
        this = JsonPP_Alloc( );
        if (this) {
            this = JsonPP_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          I n d e n t
    //---------------------------------------------------------------
    
    uint32_t        JsonPP_getIndent (
        JSONPP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->indent;
    }


    bool            JsonPP_setIndent (
        JSONPP_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->indent = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        JsonPP_getSize (
        JSONPP_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * JsonPP_getStr (
        JSONPP_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        JsonPP_setStr (
        JSONPP_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  JsonPP_getSuperVtbl (
        JSONPP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
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
        ERESULT eRc = JsonPP_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another JSONPP object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         JsonPP_Assign (
        JSONPP_DATA		*this,
        JSONPP_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!JsonPP_Validate(pOther)) {
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
    int             JsonPP_Compare (
        JSONPP_DATA     *this,
        JSONPP_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!JsonPP_Validate(pOther)) {
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
        JsonPP      *pCopy = JsonPP_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a JSONPP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    JSONPP_DATA *     JsonPP_Copy (
        JSONPP_DATA       *this
    )
    {
        JSONPP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef JSONPP_IS_CONSTANT
        obj_Retain(this);
        pOther = this;
#else
        pOther = JsonPP_New( );
        if (pOther) {
            eRc = JsonPP_Assign(this, pOther);
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

    void            JsonPP_Dealloc (
        OBJ_ID          objId
    )
    {
        JSONPP_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((JSONPP_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        JsonPP_setStr(this, OBJ_NIL);

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
        JsonPP      *pDeepCopy = JsonPP_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a JSONPP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    JSONPP_DATA *     JsonPP_DeepyCopy (
        JSONPP_DATA       *this
    )
    {
        JSONPP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = JsonPP_New( );
        if (pOther) {
            eRc = JsonPP_Assign(this, pOther);
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
    ERESULT         JsonPP_Disable (
        JSONPP_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
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
    ERESULT         JsonPP_Enable (
        JSONPP_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
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

    JSONPP_DATA *   JsonPP_Init (
        JSONPP_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(JSONPP_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_JSONPP);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&JsonPP_Vtbl);
        
        this->indent = 4;
        this->pStr = AStr_New( );
        if (OBJ_NIL == this->pStr) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        fprintf(
                stderr, 
                "JsonPP::sizeof(JSONPP_DATA) = %lu\n", 
                sizeof(JSONPP_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(JSONPP_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         JsonPP_IsEnabled (
        JSONPP_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
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
    //                      P r e t t y  P r i n t
    //---------------------------------------------------------------

    ERESULT         JsonPP_PrettyPrint (
        JSONPP_DATA     *this,
        NODE_DATA       *pNodes,
        uint32_t        indent,
        ASTR_DATA       **ppStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODEHASH_DATA   *pHash;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !JsonPP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pNodes) {
            DEBUG_BREAK();
            return ERESULT_DATA_MISSING;
        }
#endif

        pHash = JsonIn_CheckNodeForHash(pNodes);
        if (OBJ_NIL == pHash) {
            return ERESULT_PARSE_ERROR;
        }
        eRc = JsonPP_PrintHash(this, pHash, indent, "");

        // Return to caller.
        if (ppStr) {
            obj_Retain(this->pStr);
            *ppStr = this->pStr;
        }
        return eRc;
    }



    //---------------------------------------------------------------
    //                     P r i n t  A r r a y
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         JsonPP_PrintArray (
        JSONPP_DATA     *this,
        NODEARRAY_DATA  *pArray,
        uint32_t        indent,
        const
        char            *pComma
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (indent) {
            AStr_AppendCharRepeatA(this->pStr, indent, ' ');
        }
        AStr_AppendA(this->pStr, "[\n");
        iMax = NodeArray_getSize(pArray);
        for (i=0; i<iMax; i++) {
            pNode = NodeArray_Get(pArray, i+1);
            JsonPP_PrintValue(
                              this,
                              pNode,
                              (indent + this->indent),
                              i == iMax - 1 ? "" : ","
            );
        }
        if (indent) {
            AStr_AppendCharRepeatA(this->pStr, indent, ' ');
        }
        AStr_AppendPrint(this->pStr, "]%s\n", pComma);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                     P r i n t  H a s h
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         JsonPP_PrintHash (
        JSONPP_DATA     *this,
        NODEHASH_DATA   *pHash,
        uint32_t        indent,
        const
        char            *pComma
    )
    {
        //ERESULT         eRc;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pArray = NodeHash_Nodes(pHash);
        if (OBJ_NIL == pArray) {
            return ERESULT_SUCCESS;
        }

        if (indent) {
            AStr_AppendCharRepeatA(this->pStr, indent, ' ');
        }
        AStr_AppendA(this->pStr, "{\n");
        iMax = NodeArray_getSize(pArray);
        for (i=0; i<iMax; i++) {
            pNode = NodeArray_Get(pArray, i+1);
            JsonPP_PrintPair(
                             this,
                             pNode,
                             (indent + this->indent),
                             i == iMax - 1 ? "" : ","
            );
        }
        if (indent) {
            AStr_AppendCharRepeatA(this->pStr, indent, ' ');
        }
        AStr_AppendPrint(this->pStr, "}%s\n", pComma);

        obj_Release(pArray);
        pArray = OBJ_NIL;

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                     P r i n t  P a i r
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         JsonPP_PrintPair (
        JSONPP_DATA     *this,
        NODE_DATA       *pNode,
        uint32_t        indent,
        const
        char            *pComma
    )
    {
        //ERESULT         eRc;
        NODE_DATA       *pData = OBJ_NIL;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        FALSE_DATA      *pFalse = OBJ_NIL;
        NULL_DATA       *pNull = OBJ_NIL;
        TRUE_DATA       *pTrue = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        char            *pNameA = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pNameA = Node_getNameUTF8(pNode);
        if (NULL == pNameA) {
            DEBUG_BREAK();
            fprintf(stderr, "ERROR - Hash Pair is missing Name!\n\n\n");
            exit(8);
        }
        pData = Node_getData(pNode);
        if (OBJ_NIL == pData) {
            DEBUG_BREAK();
            fprintf(stderr, "ERROR - Hash Pair is missing Data object!\n\n\n");
            exit(8);
        }

        if (indent) {
            AStr_AppendCharRepeatA(this->pStr, indent, ' ');
        }
        AStr_AppendPrint(this->pStr, "\"%s\"", pNameA);
        mem_Free(pNameA);
        pNameA = NULL;
        AStr_AppendA(this->pStr, " : ");

        pFalse = JsonIn_CheckNodeForFalse(pData);
        if (pFalse) {
            AStr_AppendPrint(this->pStr, "false%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pStr = JsonIn_CheckNodeForInteger(pData);
        if (pStr) {
            AStr_AppendPrint(this->pStr, "%s%s\n", AStr_getData(pStr), pComma);
            return ERESULT_SUCCESS;
        }
        pNull = JsonIn_CheckNodeForNull(pData);
        if (pNull) {
            AStr_AppendPrint(this->pStr, "null%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pStr = JsonIn_CheckNodeForString(pData);
        if (pStr) {
            AStr_AppendPrint(this->pStr, "\"%s\"%s\n", AStr_getData(pStr), pComma);
            return ERESULT_SUCCESS;
        }
        pTrue = JsonIn_CheckNodeForTrue(pData);
        if (pTrue) {
            AStr_AppendPrint(this->pStr, "true%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pArray = JsonIn_CheckNodeForArray(pData);
        if (pArray) {
            AStr_AppendA(this->pStr, "[\n");
            iMax = NodeArray_getSize(pArray);
            for (i=0; i<iMax; i++) {
                pNode = NodeArray_Get(pArray, i+1);
                JsonPP_PrintValue(
                                  this,
                                  pNode,
                                  (indent + this->indent),
                                  i == iMax - 1 ? "" : ","
                );
            }
            if (indent) {
                AStr_AppendCharRepeatA(this->pStr, indent, ' ');
            }
            AStr_AppendPrint(this->pStr, "]%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pHash = JsonIn_CheckNodeForHash(pData);
        if (pHash) {
            pArray = NodeHash_Nodes(pHash);
            if (pArray) {
                AStr_AppendA(this->pStr, "{\n");
                iMax = NodeArray_getSize(pArray);
                for (i=0; i<iMax; i++) {
                    pNode = NodeArray_Get(pArray, i+1);
                    JsonPP_PrintPair(
                                     this,
                                     pNode,
                                     (indent + this->indent),
                                     i == iMax - 1 ? "" : ","
                    );
                }
                if (indent) {
                    AStr_AppendCharRepeatA(this->pStr, indent, ' ');
                }
                AStr_AppendPrint(this->pStr, "}%s\n", pComma);
                obj_Release(pArray);
                pArray = OBJ_NIL;
                return ERESULT_SUCCESS;
            }
        }

        DEBUG_BREAK();
        fprintf(stderr, "ERROR - Hash Pair has an invalid Data object!\n\n\n");
        exit(8);

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                     P r i n t  V a l u e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         JsonPP_PrintValue (
        JSONPP_DATA     *this,
        NODE_DATA       *pNode,
        uint32_t        indent,
        const
        char            *pComma
    )
    {
        //ERESULT         eRc;
        NODEARRAY_DATA  *pArray = OBJ_NIL;
        NODEHASH_DATA   *pHash = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        FALSE_DATA      *pFalse = OBJ_NIL;
        NULL_DATA       *pNull = OBJ_NIL;
        TRUE_DATA       *pTrue = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (indent) {
            AStr_AppendCharRepeatA(this->pStr, indent, ' ');
        }

        pFalse = JsonIn_CheckNodeForFalse(pNode);
        if (pFalse) {
            AStr_AppendPrint(this->pStr, "false%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pStr = JsonIn_CheckNodeForInteger(pNode);
        if (pStr) {
            AStr_AppendPrint(this->pStr, "%s%s\n", AStr_getData(pStr), pComma);
            return ERESULT_SUCCESS;
        }
        pNull = JsonIn_CheckNodeForNull(pNode);
        if (pNull) {
            AStr_AppendPrint(this->pStr, "null%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pStr = JsonIn_CheckNodeForString(pNode);
        if (pStr) {
            AStr_AppendPrint(this->pStr, "\"%s\"%s\n", AStr_getData(pStr), pComma);
            return ERESULT_SUCCESS;
        }
        pTrue = JsonIn_CheckNodeForTrue(pNode);
        if (pTrue) {
            AStr_AppendPrint(this->pStr, "true%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pArray = JsonIn_CheckNodeForArray(pNode);
        if (pArray) {
            AStr_AppendA(this->pStr, "[\n");
            iMax = NodeArray_getSize(pArray);
            for (i=0; i<iMax; i++) {
                pNode = NodeArray_Get(pArray, i+1);
                JsonPP_PrintPair(
                                 this,
                                 pNode,
                                 (indent + this->indent),
                                 i == iMax - 1 ? "" : ","
                );
            }
            if (indent) {
                AStr_AppendCharRepeatA(this->pStr, indent, ' ');
            }
            AStr_AppendPrint(this->pStr, "]%s\n", pComma);
            return ERESULT_SUCCESS;
        }
        pHash = JsonIn_CheckNodeForHash(pNode);
        if (pHash) {
            pArray = NodeHash_Nodes(pHash);
            if (pArray) {
                AStr_AppendA(this->pStr, "[\n");
                iMax = NodeArray_getSize(pArray);
                for (i=0; i<iMax; i++) {
                    pNode = NodeArray_Get(pArray, i+1);
                    JsonPP_PrintPair(
                                     this,
                                     pNode,
                                     (indent + this->indent),
                                     i == iMax - 1 ? "" : ","
                    );
                }
                if (indent) {
                    AStr_AppendCharRepeatA(this->pStr, indent, ' ');
                }
                AStr_AppendPrint(this->pStr, "]%s\n", pComma);
                obj_Release(pArray);
                pArray = OBJ_NIL;
                return ERESULT_SUCCESS;
            }
        }

        DEBUG_BREAK();
        fprintf(stderr, "ERROR - Hash Pair has an invalid Data object!\n\n\n");
        exit(8);

        // Return to caller.
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
        void        *pMethod = JsonPP_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "JsonPP", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          JsonPP_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        JSONPP_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!JsonPP_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(JSONPP_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)JsonPP_Class();
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
                            return JsonPP_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return JsonPP_Enable;
                        }
                        break;

#ifdef  JSONPP_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return JsonPP_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return JsonPP_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return JsonPP_ToDebugString;
                        }
#ifdef  JSONPP_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return JsonPP_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == JsonPP_ToDebugString)
                    return "ToDebugString";
#ifdef  JSONPP_JSON_SUPPORT
                if (pData == JsonPP_ToJson)
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
        ASTR_DATA      *pDesc = JsonPP_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     JsonPP_ToDebugString (
        JSONPP_DATA      *this,
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
        if (!JsonPP_Validate(this)) {
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
                    JsonPP_getSize(this),
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
    bool            JsonPP_Validate (
        JSONPP_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_JSONPP))
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


        if (!(obj_getSize(this) >= sizeof(JSONPP_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


