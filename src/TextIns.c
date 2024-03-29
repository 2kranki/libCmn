// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   TextIns.c
 *	Generated 02/12/2020 09:43:59
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
#include        <TextIns_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            TextIns_task_body (
        void            *pData
    )
    {
        //TEXTINS_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TEXTINS_DATA *     TextIns_Alloc (
        void
    )
    {
        TEXTINS_DATA       *this;
        uint32_t        cbSize = sizeof(TEXTINS_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TEXTINS_DATA *     TextIns_New (
        void
    )
    {
        TEXTINS_DATA       *this;
        
        this = TextIns_Alloc( );
        if (this) {
            this = TextIns_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P a t h s
    //---------------------------------------------------------------

    OBJARRAY_DATA * TextIns_getPaths (
        TEXTINS_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPaths;
    }


    bool            TextIns_setPaths (
        TEXTINS_DATA    *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pPaths) {
            obj_Release(this->pPaths);
        }
        this->pPaths = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          R e u s e
    //---------------------------------------------------------------
    
    bool            TextIns_getReuse (
        TEXTINS_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fReuse;
    }


    bool            TextIns_setReuse (
        TEXTINS_DATA    *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (value)
            this->fReuse = 1;
        else
            this->fReuse = 0;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        TextIns_getSize (
        TEXTINS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S t a c k
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * TextIns_getStack (
        TEXTINS_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStack;
    }
    
    
    bool            TextIns_setStack (
        TEXTINS_DATA    *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStack) {
            obj_Release(this->pStack);
        }
        this->pStack = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  TextIns_getSuperVtbl (
        TEXTINS_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
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
        ERESULT eRc = TextIns_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another TEXTINS object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         TextIns_Assign (
        TEXTINS_DATA		*this,
        TEXTINS_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!TextIns_Validate(pOther)) {
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
    //                      C l o s e
    //---------------------------------------------------------------

    /*!
     Close the current file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIns_Close (
        TEXTINS_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //eRc = TextIn_Close(TextIns_StackTop(this));

        //obj_Disable(this);
        
        // Return to caller.
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
    int             TextIns_Compare (
        TEXTINS_DATA    *this,
        TEXTINS_DATA    *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!TextIns_Validate(pOther)) {
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
        TextIns      *pCopy = TextIns_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEXTINS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEXTINS_DATA *     TextIns_Copy (
        TEXTINS_DATA       *this
    )
    {
        TEXTINS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef TEXTINS_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = TextIns_New( );
        if (pOther) {
            eRc = TextIns_Assign(this, pOther);
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

    void            TextIns_Dealloc (
        OBJ_ID          objId
    )
    {
        TEXTINS_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((TEXTINS_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        TextIns_setPaths(this, OBJ_NIL);
        TextIns_setStack(this, OBJ_NIL);

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
        TextIns      *pDeepCopy = TextIns_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a TEXTINS object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    TEXTINS_DATA *     TextIns_DeepyCopy (
        TEXTINS_DATA       *this
    )
    {
        TEXTINS_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = TextIns_New( );
        if (pOther) {
            eRc = TextIns_Assign(this, pOther);
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
    ERESULT         TextIns_Disable (
        TEXTINS_DATA    *this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
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
    ERESULT         TextIns_Enable (
        TEXTINS_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
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
    //                          G e t  L i n e
    //---------------------------------------------------------------

    ERESULT         TextIns_GetLineA (
        TEXTINS_DATA    *this,
        int             size,
        char            *pBuffer,
        SRCLOC          *pLoc
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = TextIn_GetLineA(TextIns_StackTop(this), size, pBuffer, pLoc);

        // Return to caller.
        return eRc;
    }


    ERESULT         TextIns_GetLineW32 (
        TEXTINS_DATA    *this,
        int             size,
        W32CHR_T        *pBuffer,
        SRCLOC          *pLoc
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = TextIn_GetLineW32(TextIns_StackTop(this), size, pBuffer, pLoc);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TEXTINS_DATA *   TextIns_Init (
        TEXTINS_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(TEXTINS_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_TEXTINS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&TextIns_Vtbl);
        
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "TextIns::sizeof(TEXTINS_DATA) = %lu\n", 
                sizeof(TEXTINS_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(TEXTINS_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         TextIns_IsEnabled (
        TEXTINS_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
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
    //                          N e w  S r c
    //---------------------------------------------------------------

    ERESULT         TextIns_NewSrcFromAStr (
        TEXTINS_DATA    *this,
        PATH_DATA       *pFilePath,     // [in] doc only
        ASTR_DATA       *pAStr,         // Buffer of file data
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        TEXTIN_DATA     *pSrc;
        uint16_t        index;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        index = TextIns_PathAdd(this, pFilePath);
        if (0 == index) {
            return ERESULT_GENERAL_FAILURE;
        }

        pSrc = TextIn_NewFromAStr(pFilePath, pAStr, index, tabSize);
        if (OBJ_NIL == pSrc) {
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }
        TextIns_StackPush(this, pSrc);
        obj_Release(pSrc);
        pSrc = OBJ_NIL;

        return ERESULT_SUCCESS;
    }


    ERESULT         TextIns_NewSrcFromPath (
        TEXTINS_DATA    *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    )
    {
        TEXTIN_DATA     *pSrc;
        uint16_t        index;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        index = TextIns_PathAdd(this, pFilePath);
        if (0 == index) {
            return ERESULT_GENERAL_FAILURE;
        }

        pSrc = TextIn_NewFromPath(pFilePath, index, tabSize);
        if (OBJ_NIL == pSrc) {
            obj_Release(this);
            return ERESULT_OUT_OF_MEMORY;
        }

        TextIns_StackPush(this, pSrc);
        obj_Release(pSrc);
        pSrc = OBJ_NIL;

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                         P a t h
    //---------------------------------------------------------------

    /*!
     Get a path given its index.
     @param     this    object pointer
     @param     index   path name index (relative to 1)
     @return    if successful, path object pointer.  Otherwise, OBJ_NIL.
     */
    PATH_DATA *     TextIns_Path (
        TEXTINS_DATA    *this,
        uint16_t        index
    )
    {
        //ERESULT         eRc;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        if (this->pPaths) {
            pPath = ObjArray_Get(this->pPaths, index);
        }

        // Return to caller.
        return pPath;
    }


    /*!
     Add a path to the paths if it is not already there and return its index.
     @param     this    object pointer
     @param     pPath   path name object
     @return    if successful, the path name index relative to 1.
                Otherwise, 0.
     */
    uint16_t        TextIns_PathAdd (
        TEXTINS_DATA    *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        PATH_DATA       *pPathF = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif
        if (OBJ_NIL == this->pPaths) {
            this->pPaths = ObjArray_New( );
            if (OBJ_NIL == this->pPaths) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        iMax = ObjArray_getSize(this->pPaths);
        for (i=0; i < iMax; i++) {
            pPathF = (PATH_DATA *)ObjArray_Get(this->pPaths, i+1);
            if (pPathF && (0 == Path_Compare(pPath, pPathF))) {
                return i+1;
            }
        }

        i = 0;
        eRc = ObjArray_AppendObj(this->pPaths, pPath, &i);
        if (ERESULT_FAILED(eRc)) {
            return 0;
        }

        // Return to caller.
        return i;
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
        void        *pMethod = TextIns_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "TextIns", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          TextIns_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        TEXTINS_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!TextIns_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(TEXTINS_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)TextIns_Class();
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
                            return TextIns_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return TextIns_Enable;
                        }
                        break;

#ifdef  TEXTINS_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return TextIns_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return TextIns_ParseJsonObject;
                        }
                        break;
#endif

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return TextIns_ToDebugString;
                        }
#ifdef  TEXTINS_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return TextIns_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == TextIns_ToDebugString)
                    return "ToDebugString";
#ifdef  TEXTINS_JSON_SUPPORT
                if (pData == TextIns_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S t a c k  P o p
    //---------------------------------------------------------------

    ERESULT         TextIns_StackClear(
        TEXTINS_DATA    *this
    )
    {
        TEXTIN_DATA     *pItem = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIns_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (OBJ_NIL == this->pStack) {
            return ERESULT_DATA_NOT_FOUND;
        }

        // Pop all elements from the top of the parse stack.
        while( ObjArray_getSize(this->pStack) ) {
            pItem = ObjArray_DeleteLast(this->pStack);
            obj_Release(pItem);
            pItem = OBJ_NIL;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      S t a c k  G e t
    //---------------------------------------------------------------

    /*!
     Get an input object given its index.
     @param     this    object pointer
     @param     index   path name index (relative to 1)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    TEXTIN_DATA *   TextIns_StackGet(
        TEXTINS_DATA    *this,
        uint16_t        index
    )
    {
        TEXTIN_DATA     *pItem = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIns_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (OBJ_NIL == this->pStack) {
            return OBJ_NIL;
        }

        pItem = ObjArray_Get(this->pStack, index);

        // Return to caller.
        return pItem;
    }



    //---------------------------------------------------------------
    //                      S t a c k  P o p
    //---------------------------------------------------------------

    /*!
     Pop an input object from the stack so that the next input is from
     the pushed object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIns_StackPop(
        TEXTINS_DATA    *this
    )
    {
        TEXTIN_DATA     *pItem = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIns_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (OBJ_NIL == this->pStack) {
            return ERESULT_DATA_NOT_FOUND;
        }

        /* Pop 1 element from the top of the parse stack.
         */
        if( ObjArray_getSize(this->pStack) ) {
            pItem = ObjArray_DeleteLast(this->pStack);
            obj_Release(pItem);
            pItem = OBJ_NIL;
        }
        else {
            return ERESULT_DATA_NOT_FOUND;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      S t a c k  P u s h
    //---------------------------------------------------------------

    /*!
     Push the given input object to the stack making it the top of the
     stack and so that the next input is from this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIns_StackPush(
        TEXTINS_DATA    *this,
        TEXTIN_DATA     *pItem
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIns_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if  ((NULL == pItem) || !(obj_IsKindOf(pItem, OBJ_IDENT_TEXTIN))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (OBJ_NIL == this->pStack) {
            this->pStack = ObjArray_New( );
            if (OBJ_NIL == this->pStack) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        eRc = ObjArray_AppendObj(this->pStack, pItem, NULL);
        if (ERESULT_HAS_FAILED(eRc)) {
            DEBUG_BREAK();
            return eRc;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                      S t a c k  T o p
    //---------------------------------------------------------------

    TEXTIN_DATA *   TextIns_StackTop(
        TEXTINS_DATA    *this
    )
    {
        TEXTIN_DATA     *pItem = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !TextIns_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        if (this->pStack) {
            pItem = ObjArray_GetLast(this->pStack);
        }

        // Return to caller.
        return pItem;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TextIns_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextIns_ToDebugString (
        TEXTINS_DATA    *this,
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
        if (!TextIns_Validate(this)) {
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
                    TextIns_getSize(this),
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
    bool            TextIns_Validate (
        TEXTINS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_TEXTINS))
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


        if (!(obj_getSize(this) >= sizeof(TEXTINS_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


