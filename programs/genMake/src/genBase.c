// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   GenBase.c
 *	Generated 11/23/2019 12:07:15
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
#include        <GenBase_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /*! If no output object is present, default to using one that
     accumulates everything into an AStr object.
     */
    static
    void            GenBase_CheckOutput (
        GENBASE_DATA    *this
    )
    {
        if (OBJ_NIL == this->pOut) {
            this->pOut = TextOut_NewAStr();
        }
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GENBASE_DATA *     GenBase_Alloc (
        void
    )
    {
        GENBASE_DATA       *this;
        uint32_t        cbSize = sizeof(GENBASE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GENBASE_DATA *     GenBase_New (
        TEXTOUT_DATA    *pOutput
    )
    {
        GENBASE_DATA       *this;
        
        this = GenBase_Alloc( );
        if (this) {
            this = GenBase_Init(this);
            if (pOutput) {
                GenBase_setOutput(this, pOutput);
            } else {
                this->pOut = TextOut_NewAStr();
                if (OBJ_NIL == this->pOut) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    return OBJ_NIL;
                }
            }
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       O u t p u t
    //---------------------------------------------------------------
    
    TEXTOUT_DATA *  GenBase_getOutput (
        GENBASE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOut;
    }
    
    
    bool            GenBase_setOutput (
        GENBASE_DATA    *this,
        TEXTOUT_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_STR_OWNED
        obj_Retain(pValue);
        if (this->pOut) {
            obj_Release(this->pOut);
        }
#endif
        this->pOut = pValue;
        
        return true;
    }
            
            
            
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        GenBase_getPriority (
        GENBASE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            GenBase_setPriority (
        GENBASE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
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
    
    uint32_t        GenBase_getSize (
        GENBASE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * GenBase_getStr (
        GENBASE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        GenBase_setStr (
        GENBASE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  GenBase_getSuperVtbl (
        GENBASE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * GenBase_getTime (
        GENBASE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pTime;
    }
    
    
    bool        GenBase_setTime (
        GENBASE_DATA     *this,
        DATETIME_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef  PROPERTY_TIME_OWNED
        obj_Retain(pValue);
        if (this->pTime) {
            obj_Release(this->pTime);
        }
#endif
        this->pTime = pValue;
        
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
        ERESULT eRc = GenBase_Assign(this,pOther);
     @endcode 
     @param     this    GENBASE object pointer
     @param     pOther  a pointer to another GENBASE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         GenBase_Assign (
        GENBASE_DATA		*this,
        GENBASE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!GenBase_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         GenBase_Compare (
        GENBASE_DATA     *this,
        GENBASE_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!GenBase_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        GenBase      *pCopy = GenBase_Copy(this);
     @endcode 
     @param     this    GENBASE object pointer
     @return    If successful, a GENBASE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GENBASE_DATA *     GenBase_Copy (
        GENBASE_DATA       *this
    )
    {
        GENBASE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = GenBase_New(OBJ_NIL);
        if (pOther) {
            eRc = GenBase_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            GenBase_Dealloc (
        OBJ_ID          objId
    )
    {
        GENBASE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GENBASE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        GenBase_setOutput(this, OBJ_NIL);
        GenBase_setStr(this, OBJ_NIL);
        GenBase_setTime(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
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
    ERESULT         GenBase_Disable (
        GENBASE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!GenBase_Validate(this)) {
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
    ERESULT         GenBase_Enable (
        GENBASE_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }



    ERESULT_DATA *  GenBase_GenHeader (
        GENBASE_DATA    *this
    )
    {
        ASTR_DATA       *pStr =  OBJ_NIL;
        ASTR_DATA       *pWrk =  OBJ_NIL;

            // Do initialization.
        #ifdef NDEBUG
        #else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return eResult_NewStrA(ERESULT_INVALID_OBJECT, NULL);
        }
    #endif
        
        // Set up to generate Makefile entry.
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return eResult_NewStrA(ERESULT_OUT_OF_MEMORY, NULL);
        }

        AStr_AppendA(pStr,
                     "# Generated file - Edits will be discarded by next generation!\n");
        if (GenBase_getTime(this)) {
            pWrk = dateTime_ToString(GenBase_getTime(this));
            AStr_AppendPrint(pStr, "# (%s)\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
        }
        AStr_AppendA(pStr, "\n");
        
        GenBase_Output(this, pStr);
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Return to caller.
        return OBJ_NIL;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GENBASE_DATA *   GenBase_Init (
        GENBASE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GENBASE_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_GENBASE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&GenBase_Vtbl);
        
        this->pTime = dateTime_NewCurrent();
        if (OBJ_NIL == this->pTime) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "GenBase::sizeof(GENBASE_DATA) = %lu\n", sizeof(GENBASE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(GENBASE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         GenBase_IsEnabled (
        GENBASE_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
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
    //                          O u t p u t
    //---------------------------------------------------------------

    ERESULT         GenBase_Output (
        GENBASE_DATA    *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        GenBase_CheckOutput(this);
        
        eRc = TextOut_PutA(this->pOut, AStr_getData(pStr));

        // Return to caller.
        return eRc;
    }


    ERESULT         GenBase_OutputA (
        GENBASE_DATA    *this,
        const
        char            *pStrA
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        GenBase_CheckOutput(this);
        
        eRc = TextOut_PutA(this->pOut, pStrA);

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
        void        *pMethod = GenBase_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "GenBase", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          GenBase_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GENBASE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(GENBASE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)GenBase_Class();
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
                            return GenBase_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return GenBase_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return GenBase_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return GenBase_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == GenBase_ToDebugString)
                    return "ToDebugString";
                if (pData == GenBase_ToJSON)
                    return "ToJSON";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     GenBase_ToJSON (
        GENBASE_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!GenBase_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        if (pStr) {
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{\"objectType\":\"%s\"",
                        pInfo->pClassName
                    );
            
            AStr_AppendA(pStr, "}\n");
        }
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = GenBase_ToDebugString(this,4);
     @endcode 
     @param     this    GENBASE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     GenBase_ToDebugString (
        GENBASE_DATA      *this,
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
        if (!GenBase_Validate(this)) {
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
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    GenBase_getSize(this)
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
    bool            GenBase_Validate (
        GENBASE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_GENBASE))
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


        if (!(obj_getSize(this) >= sizeof(GENBASE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


