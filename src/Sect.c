// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Sect.c
 *  Generated 12/27/2020 14:58:15
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
#include        <Sect_internal.h>
#include        <ascii.h>
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
    void            Sect_task_body (
        void            *pData
    )
    {
        //SECT_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SECT_DATA *     Sect_Alloc (
        void
    )
    {
        SECT_DATA       *this;
        uint32_t        cbSize = sizeof(SECT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SECT_DATA *     Sect_New (
        void
    )
    {
        SECT_DATA       *this;
        
        this = Sect_Alloc( );
        if (this) {
            this = Sect_Init(this);
        } 
        return this;
    }



    SECT_DATA *     Sect_NewFromDataA (
        char            ident,
        char            type,
        uint32_t        addr,
        uint32_t        offset,
        uint32_t        len,
        const
        char            *pNameA
    )
    {
        SECT_DATA       *this;

        this = Sect_New( );
        if (this) {
            this->ident  = ident;
            this->type   = type;
            this->addr   = addr;
            this->offset = offset;
            this->len    = len;
            this->pName  = AStr_NewA(pNameA);
            if (OBJ_NIL == this->pName) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }

        return this;
    }




    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                       A d d r e s s
    //---------------------------------------------------------------

    uint32_t        Sect_getAddr (
        SECT_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->addr;
    }


    bool            Sect_setAddr (
        SECT_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->addr = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        D a t a
    //---------------------------------------------------------------

    U8ARRAY_DATA *  Sect_getData (
        SECT_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pData;
    }


    bool            Sect_setData (
        SECT_DATA       *this,
        U8ARRAY_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pData) {
            obj_Release(this->pData);
        }
        this->pData = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                      I d e n t i f i e r
    //---------------------------------------------------------------

    char            Sect_getIdent (
        SECT_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->ident;
    }


    bool            Sect_setIdent (
        SECT_DATA       *this,
        char            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->ident = value;

        return true;
    }



    //---------------------------------------------------------------
    //                       O f f s e t
    //---------------------------------------------------------------

    uint32_t        Sect_getOffset (
        SECT_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->offset;
    }


    bool            Sect_setOffset (
        SECT_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->offset = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     Sect_getName (
        SECT_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool            Sect_setName (
        SECT_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Sect_getPriority (
        SECT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Sect_setPriority (
        SECT_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
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
    
    uint32_t        Sect_getSize (
        SECT_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Sect_getSuperVtbl (
        SECT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    char            Sect_getType (
        SECT_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            Sect_setType (
        SECT_DATA       *this,
        char            value
    )
    {
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->type = value;

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
        ERESULT eRc = Sect_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SECT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Sect_Assign (
        SECT_DATA       *this,
        SECT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Sect_Validate(pOther)) {
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
        if (pOther->pName) {
            obj_Release(pOther->pName);
            pOther->pName = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pCopy) {
                pOther->pName = obj_getVtbl(this->pName)->pCopy(this->pName);
            }
            else {
                obj_Retain(this->pName);
                pOther->pName = this->pName;
            }
        }

        // Copy other data from this object to other.
        pOther->ident    = this->ident;
        pOther->type     = this->type;
        pOther->addr     = this->addr;
        pOther->len      = this->len;
        pOther->offset   = this->offset;

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
    int             Sect_Compare (
        SECT_DATA     *this,
        SECT_DATA     *pOther
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
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Sect_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc = utf8_StrCmp(&this->ident, &pOther->ident);
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Sect      *pCopy = Sect_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SECT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SECT_DATA *     Sect_Copy (
        SECT_DATA       *this
    )
    {
        SECT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SECT_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Sect_New( );
        if (pOther) {
            eRc = Sect_Assign(this, pOther);
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

    void            Sect_Dealloc (
        OBJ_ID          objId
    )
    {
        SECT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SECT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Sect_setData(this, OBJ_NIL);
        Sect_setName(this, OBJ_NIL);

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
        Sect      *pDeepCopy = Sect_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SECT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SECT_DATA *     Sect_DeepyCopy (
        SECT_DATA       *this
    )
    {
        SECT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Sect_New( );
        if (pOther) {
            eRc = Sect_Assign(this, pOther);
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
    ERESULT         Sect_Disable (
        SECT_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
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
    ERESULT         Sect_Enable (
        SECT_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
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
    //                          I n i t
    //---------------------------------------------------------------

    SECT_DATA *   Sect_Init (
        SECT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SECT_DATA);
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

        //this = (OBJ_ID)Node_Init((NODE_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SECT);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Sect_Vtbl);
#ifdef  SECT_JSON_SUPPORT
        JsonIn_RegisterClass(Sect_Class());
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
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Sect::sizeof(SECT_DATA) = %lu\n", 
                sizeof(SECT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SECT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Sect_IsEnabled (
        SECT_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
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
    //                          K e y
    //---------------------------------------------------------------

    ASTR_DATA *     Sect_Key (
        SECT_DATA       *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        eRc = AStr_AppendPrint(
                    pStr,
                    "%c",
                    this->ident
            );

        return pStr;
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
        void        *pMethod = Sect_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Sect", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Sect_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SECT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SECT_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Sect_Class();
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
                            return Sect_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Sect_Enable;
                        }
                        break;

                    case 'K':
                        if (str_Compare("Key", (char *)pStr) == 0) {
                            return Sect_Key;
                        }
                        break;

                    case 'P':
#ifdef  SECT_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Sect_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Sect_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Sect_ToDebugString;
                        }
#ifdef  SECT_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Sect_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Sect_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Sect_Key)
                    return "Key";
                if (pData == Sect_ToDebugString)
                    return "ToDebugString";
#ifdef  SECT_JSON_SUPPORT
                if (pData == Sect_ToJson)
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
        ASTR_DATA      *pDesc = Sect_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Sect_ToDebugString (
        SECT_DATA      *this,
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
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Sect_Validate(this)) {
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
                    Sect_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "\tident=%c type=%c addr=%08X offset=%08X len=%08X name=%s\n",
                    this->ident,
                    this->type,
                    this->addr,
                    this->offset,
                    this->len,
                    this->pName ? AStr_getData(this->pName) : ""
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
    bool            Sect_Validate (
        SECT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SECT))
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


        if (!(obj_getSize(this) >= sizeof(SECT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


