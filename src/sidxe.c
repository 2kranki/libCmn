// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   sidxe.c
 *	Generated 12/18/2018 10:26:03
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
#include        <sidxe_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            sidxe_task_body (
        void            *pData
    )
    {
        //SIDXE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SIDXE_DATA *     sidxe_Alloc (
        void
    )
    {
        SIDXE_DATA       *this;
        uint32_t        cbSize = sizeof(SIDXE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SIDXE_DATA *     sidxe_New (
        void
    )
    {
        SIDXE_DATA       *this;
        
        this = sidxe_Alloc( );
        if (this) {
            this = sidxe_Init(this);
        } 
        return this;
    }


    SIDXE_DATA *    sidxe_NewWithMax (
        uint16_t        max
    )
    {
        SIDXE_DATA       *this;
        
        this = sidxe_New( );
        if (this) {
            sidxe_setMax(this, max);
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          I n t e r v a l
    //---------------------------------------------------------------
    
    uint32_t        sidxe_getInterval (
        SIDXE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return array_getMisc(this->pArray);
    }
    
    
    
    //---------------------------------------------------------------
    //                          M a x
    //---------------------------------------------------------------
    
    uint16_t        sidxe_getMax (
        SIDXE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->max;
    }
    
    
    bool            sidxe_setMax (
        SIDXE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->max = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        sidxe_getPriority (
        SIDXE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            sidxe_setPriority (
        SIDXE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
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
    
    uint32_t        sidxe_getSize (
        SIDXE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return array_getSize(this->pArray);
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * sidxe_getStr (
        SIDXE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        sidxe_setStr (
        SIDXE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  sidxe_getSuperVtbl (
        SIDXE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
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
    
    ERESULT         sidxe_Add (
        SIDXE_DATA      *this,
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
        if( !sidxe_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pLoc) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (0 == sidxe_getMax(this)) {
            DEBUG_BREAK();
            return ERESULT_GENERAL_FAILURE;
        }
#endif
        
        if (0 == sidxe_getSize(this)) {
            if ( (pLoc->lineNo % sidxe_getInterval(this)) == 0 ) {
                eRc = array_AppendData(this->pArray, 1, pLoc);
                this->maxLineNo = pLoc->lineNo;
                return eRc;
            }
        }
        else {
            eRc = ERESULT_SUCCESS;
            if ((pLoc->lineNo > this->maxLineNo)
                && ((pLoc->lineNo % sidxe_getInterval(this)) == 0)) {
                if (sidxe_getMax(this) == sidxe_getSize(this)) {
                    eRc = array_DeleteOdd(this->pArray);
                    if (ERESULT_FAILED(eRc))
                        return eRc;
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
        ERESULT eRc = sidxe_Assign(this,pOther);
     @endcode 
     @param     this    SIDXE object pointer
     @param     pOther  a pointer to another SIDXE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         sidxe_Assign (
        SIDXE_DATA		*this,
        SIDXE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!sidxe_Validate(pOther)) {
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
    ERESULT         sidxe_Compare (
        SIDXE_DATA     *this,
        SIDXE_DATA     *pOther
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
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!sidxe_Validate(pOther)) {
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
        sidxe      *pCopy = sidxe_Copy(this);
     @endcode 
     @param     this    SIDXE object pointer
     @return    If successful, a SIDXE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SIDXE_DATA *     sidxe_Copy (
        SIDXE_DATA       *this
    )
    {
        SIDXE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = sidxe_New( );
        if (pOther) {
            eRc = sidxe_Assign(this, pOther);
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

    void            sidxe_Dealloc (
        OBJ_ID          objId
    )
    {
        SIDXE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SIDXE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        sidxe_setStr(this, OBJ_NIL);

        if (this->pArray) {
            obj_Release(this->pArray);
            this->pArray = OBJ_NIL;
        }
        
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

    ERESULT         sidxe_Disable (
        SIDXE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!sidxe_Validate(this)) {
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

    ERESULT         sidxe_Enable (
        SIDXE_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!sidxe_Validate(this)) {
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
    //                          F i n d
    //---------------------------------------------------------------
    
    ERESULT         sidxe_FindLineNo (
        SIDXE_DATA      *this,
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
        if( !sidxe_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        iMax = sidxe_getSize(this);
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
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SIDXE_DATA *   sidxe_Init (
        SIDXE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SIDXE_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SIDXE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_SIDXE);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&sidxe_Vtbl);
        
        this->pArray = array_NewWithSize(sizeof(SRCLOC));
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        array_setMisc(this->pArray, 1);
        
    #ifdef NDEBUG
    #else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "sidxe::sizeof(SIDXE_DATA) = %lu\n", sizeof(SIDXE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SIDXE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         sidxe_IsEnabled (
        SIDXE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
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
        void        *pMethod = sidxe_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "sidxe", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          sidxe_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SIDXE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(SIDXE_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)sidxe_Class();
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
                            return sidxe_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return sidxe_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return sidxe_ToDebugString;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return sidxe_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == sidxe_ToDebugString)
                    return "ToDebugString";
                if (pData == sidxe_ToJSON)
                    return "ToJson";
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------
    
    ERESULT         sidxe_Reset (
        SIDXE_DATA      *this
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
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
    //                       T o  J S O N
    //---------------------------------------------------------------
    
     ASTR_DATA *     sidxe_ToJSON (
        SIDXE_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
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
        ASTR_DATA      *pDesc = sidxe_ToDebugString(this,4);
     @endcode 
     @param     this    SIDXE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     sidxe_ToDebugString (
        SIDXE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        uint32_t        i;
        uint32_t        iMax;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        //SRCLOC          *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!sidxe_Validate(this)) {
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
                    sidxe_getSize(this),
                    sidxe_getMax(this),
                    this->maxLineNo
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+3, ' ');
        }
        eRc =   AStr_AppendA(pStr, "Location Table:\n");
        iMax = sidxe_getSize(this);
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
    bool            sidxe_Validate (
        SIDXE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SIDXE))
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


        if (!(obj_getSize(this) >= sizeof(SIDXE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


