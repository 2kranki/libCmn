// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   LineIndex.c
 *  Generated 06/04/2020 10:44:19
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
#include        <LineIndex_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            LineIndex_task_body (
        void            *pData
    )
    {
        //LINEINDEX_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    LINEINDEX_DATA *     LineIndex_Alloc (
        void
    )
    {
        LINEINDEX_DATA       *this;
        uint32_t        cbSize = sizeof(LINEINDEX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    LINEINDEX_DATA *     LineIndex_New (
        void
    )
    {
        LINEINDEX_DATA       *this;
        
        this = LineIndex_Alloc( );
        if (this) {
            this = LineIndex_Init(this);
        } 
        return this;
    }


    LINEINDEX_DATA *    LineIndex_NewWithMax (
        uint16_t            max
    )
    {
        LINEINDEX_DATA      *this;

        this = LineIndex_New( );
        if (this) {
            LineIndex_setMax(this, max);
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       A r r a y
    //---------------------------------------------------------------

    ARRAY_DATA *    LineIndex_getArray (
        LINEINDEX_DATA  *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pArray;
    }


    bool            LineIndex_setArray (
        LINEINDEX_DATA  *this,
        ARRAY_DATA      *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
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
    //                      I n t e r v a l
    //---------------------------------------------------------------

    uint32_t        LineIndex_getInterval (
        LINEINDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getMisc(this->pArray);
    }


    bool            LineIndex_setInterval (
        LINEINDEX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        array_setMisc(this->pArray, value);

        return true;
    }



    //---------------------------------------------------------------
    //                         M a x
    //---------------------------------------------------------------
    
    uint32_t        LineIndex_getMax (
        LINEINDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->max;
    }


    bool            LineIndex_setMax (
        LINEINDEX_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->max = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      M a x  L i n e
    //---------------------------------------------------------------

    uint32_t        LineIndex_getMaxLine (
        LINEINDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->maxLineNo;
    }



    //---------------------------------------------------------------
    //                           S i z e
    //---------------------------------------------------------------
    
    uint32_t        LineIndex_getSize (
        LINEINDEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize(this->pArray);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  LineIndex_getSuperVtbl (
        LINEINDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
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
    //                              A d d
    //---------------------------------------------------------------

    ERESULT         LineIndex_Add (
        LINEINDEX_DATA  *this,
        SRCLOC          *pLoc
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        //uint32_t        i;
        //uint32_t        iMax;
        //uint32_t        j;
        //SRCLOC          *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LineIndex_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pLoc) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == this->max) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif

        if (0 == LineIndex_getSize(this)) {
            if ( (pLoc->lineNo % LineIndex_getInterval(this)) == 0 ) {
                eRc = array_AppendData(this->pArray, 1, pLoc);
                this->maxLineNo = pLoc->lineNo;
                return eRc;
            }
        }
        else {
            eRc = ERESULT_SUCCESS;
            if ((pLoc->lineNo > this->maxLineNo)
                && ((pLoc->lineNo % LineIndex_getInterval(this)) == 0)) {
                if (LineIndex_getMax(this) == LineIndex_getSize(this)) {
                    eRc = array_DeleteOdd(this->pArray);
                    if (ERESULT_FAILED(eRc)) {
                        return eRc;
                    }
                }
                eRc = array_AppendData(this->pArray, 1, pLoc);
                if (!ERESULT_FAILED(eRc))
                    this->maxLineNo = pLoc->lineNo;
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
        ERESULT eRc = LineIndex_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another LINEINDEX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         LineIndex_Assign (
        LINEINDEX_DATA  *this,
        LINEINDEX_DATA  *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!LineIndex_Validate(pOther)) {
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
        pOther->max       = this->max;
        pOther->maxLineNo = this->maxLineNo;

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
    int             LineIndex_Compare (
        LINEINDEX_DATA  *this,
        LINEINDEX_DATA  *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!LineIndex_Validate(pOther)) {
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
        LineIndex      *pCopy = LineIndex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LINEINDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LINEINDEX_DATA *     LineIndex_Copy (
        LINEINDEX_DATA       *this
    )
    {
        LINEINDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef LINEINDEX_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = LineIndex_New( );
        if (pOther) {
            eRc = LineIndex_Assign(this, pOther);
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

    void            LineIndex_Dealloc (
        OBJ_ID          objId
    )
    {
        LINEINDEX_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((LINEINDEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        LineIndex_setArray(this, OBJ_NIL);

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
        LineIndex      *pDeepCopy = LineIndex_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a LINEINDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    LINEINDEX_DATA *     LineIndex_DeepyCopy (
        LINEINDEX_DATA       *this
    )
    {
        LINEINDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = LineIndex_New( );
        if (pOther) {
            eRc = LineIndex_Assign(this, pOther);
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
    ERESULT         LineIndex_Disable (
        LINEINDEX_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
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
    ERESULT         LineIndex_Enable (
        LINEINDEX_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
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

    ERESULT         LineIndex_Find (
        LINEINDEX_DATA  *this,
        uint32_t        lineNo,
        SRCLOC          *pLoc
    )
    {
        //ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        i;
        uint32_t        iMax;
        //uint32_t        j;
        SRCLOC          *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LineIndex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        iMax = LineIndex_getSize(this);
        if (iMax) {
            for (i=0; i<iMax; ++i) {
                pEntry = array_GetAddrOf(this->pArray, (i + 1));
                if (lineNo < pEntry->lineNo)
                    break;
            }
            if (i) {
                pEntry = array_GetAddrOf(this->pArray, i);
            }
        }
        else
            return ERESULT_DATA_NOT_FOUND;

        // Return to caller.
        if (pEntry) {
            if (pLoc) {
                *pLoc = *pEntry;
            }
        }
        return ERESULT_SUCCESS;
    }


    ERESULT         LineIndex_FindOffset (
        LINEINDEX_DATA  *this,
        int64_t         offset,
        SRCLOC          *pLoc
    )
    {
        //ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        uint32_t        i;
        uint32_t        iMax;
        //uint32_t        j;
        SRCLOC          *pEntry = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !LineIndex_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        iMax = LineIndex_getSize(this);
        if (iMax) {
            for (i=0; i<iMax; ++i) {
                pEntry = array_GetAddrOf(this->pArray, (i + 1));
                if (offset < pEntry->offset)
                    break;
            }
            if (i) {
                pEntry = array_GetAddrOf(this->pArray, i);
            }
        }
        else
            return ERESULT_DATA_NOT_FOUND;

        // Return to caller.
        if (pEntry) {
            if (pLoc) {
                *pLoc = *pEntry;
            }
        }
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    LINEINDEX_DATA *   LineIndex_Init (
        LINEINDEX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(LINEINDEX_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_LINEINDEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&LineIndex_Vtbl);
        
        this->pArray = array_NewWithSize(sizeof(SRCLOC));
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        LineIndex_setInterval(this, 1);

#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "LineIndex::sizeof(LINEINDEX_DATA) = %lu\n", 
                sizeof(LINEINDEX_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(LINEINDEX_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         LineIndex_IsEnabled (
        LINEINDEX_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
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
        void        *pMethod = LineIndex_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "LineIndex", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          LineIndex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        LINEINDEX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(LINEINDEX_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)LineIndex_Class();
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
                            return LineIndex_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return LineIndex_Enable;
                        }
                        break;

                    case 'P':
#ifdef  LINEINDEX_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return LineIndex_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return LineIndex_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return LineIndex_ToDebugString;
                        }
#ifdef  LINEINDEX_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return LineIndex_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return LineIndex_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == LineIndex_ToDebugString)
                    return "ToDebugString";
#ifdef  LINEINDEX_JSON_SUPPORT
                if (pData == LineIndex_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         LineIndex_Reset (
        LINEINDEX_DATA  *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!LineIndex_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        this->maxLineNo = 0;
        eRc = array_Truncate(this->pArray, 0);

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
        ASTR_DATA      *pDesc = LineIndex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     LineIndex_ToDebugString (
        LINEINDEX_DATA      *this,
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
        if (!LineIndex_Validate(this)) {
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
                    "{%p(%s) size=%d max=%d, maxLineNo=%d\n",
                    this,
                    pInfo->pClassName,
                    LineIndex_getSize(this),
                    LineIndex_getMax(this),
                    this->maxLineNo
            );

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
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
        }
        eRc =   AStr_AppendA(pStr, "Location Table:\n");
        iMax = LineIndex_getSize(this);
        for (i=0; i<iMax; ++i) {
            SRCLOC          *pEntry = array_GetAddrOf(this->pArray, (i + 1));
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+6, ' ');
            }
            eRc =   AStr_AppendPrint(
                            pStr,
                        "{%p(SrcLoc) fileIndex=%4d offset=%lld line=%d col=%d (SrcLoc)%p}\n",
                        pEntry,
                        pEntry->fileIndex,
                        pEntry->offset,
                        pEntry->lineNo,
                        pEntry->colNo,
                        pEntry
                    );
        }
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
        }
        eRc =   AStr_AppendA(pStr, "End of Table\n");

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
    bool            LineIndex_Validate (
        LINEINDEX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_LINEINDEX))
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


        if (!(obj_getSize(this) >= sizeof(LINEINDEX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


