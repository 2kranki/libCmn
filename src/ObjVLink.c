// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjVLink.c
 *	Generated 01/14/2020 16:31:29
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
#include        <ObjVLink_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ObjVLink_task_body (
        void            *pData
    )
    {
        //OBJVLINK_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJVLINK_DATA *     ObjVLink_Alloc (
        void
    )
    {
        OBJVLINK_DATA       *this;
        uint32_t        cbSize = sizeof(OBJVLINK_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJVLINK_DATA *     ObjVLink_New (
        void
    )
    {
        OBJVLINK_DATA       *this;
        
        this = ObjVLink_Alloc( );
        if (this) {
            this = ObjVLink_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    int32_t         ObjVLink_getIndex (
        OBJVLINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->index;
    }


    bool            ObjVLink_setIndex (
        OBJVLINK_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->index = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          L e f t
    //---------------------------------------------------------------
    
    int32_t         ObjVLink_getLeft (
        OBJVLINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->left;
    }


    bool            ObjVLink_setLeft (
        OBJVLINK_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->left = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          M i d d l e
    //---------------------------------------------------------------
    
    int32_t         ObjVLink_getMiddle (
        OBJVLINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->middle;
    }


    bool            ObjVLink_setMiddle (
        OBJVLINK_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->middle = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          M i s c
    //---------------------------------------------------------------
    
    int32_t         ObjVLink_getMisc (
        OBJVLINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->misc;
    }


    bool            ObjVLink_setMisc (
        OBJVLINK_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->misc = value;

        return true;
    }



    //---------------------------------------------------------------
    //                      O b j e c t
    //---------------------------------------------------------------
    
    OBJ_DATA *      ObjVLink_getObj (
        OBJVLINK_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pObj;
    }
    
    
    bool            ObjVLink_setObj (
        OBJVLINK_DATA    *this,
        OBJ_DATA        *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pObj) {
            obj_Release(this->pObj);
        }
        this->pObj = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P a r e n t
    //---------------------------------------------------------------
    
    int32_t         ObjVLink_getParent (
        OBJVLINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->parent;
    }


    bool            ObjVLink_setParent (
        OBJVLINK_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->parent = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          R i g h t
    //---------------------------------------------------------------
    
    int32_t         ObjVLink_getRight (
        OBJVLINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->right;
    }


    bool            ObjVLink_setRight (
        OBJVLINK_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->right = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        ObjVLink_getSize (
        OBJVLINK_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  ObjVLink_getSuperVtbl (
        OBJVLINK_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
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
        ERESULT eRc = ObjVLink_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJVLINK object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjVLink_Assign (
        OBJVLINK_DATA	*this,
        OBJVLINK_DATA   *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjVLink_Validate(pOther)) {
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
        ObjVLink_setObj(pOther, OBJ_NIL);

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
        if (this->pObj) {
            if (obj_getVtbl(this->pObj)->pCopy) {
                pOther->pObj = obj_getVtbl(this->pObj)->pCopy(this->pObj);
            }
            else {
                obj_Retain(this->pObj);
                pOther->pObj = this->pObj;
            }
        }


        // Copy other data from this object to other.
        pOther->index   = this->index;
        pOther->left    = this->left;
        pOther->middle  = this->middle;
        pOther->misc    = this->misc;
        pOther->parent  = this->parent;
        pOther->right   = this->right;

        //goto eom;

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
    int             ObjVLink_Compare (
        OBJVLINK_DATA   *this,
        OBJVLINK_DATA   *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!ObjVLink_Validate(pOther)) {
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
        ObjVLink      *pCopy = ObjVLink_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJVLINK object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJVLINK_DATA *     ObjVLink_Copy (
        OBJVLINK_DATA       *this
    )
    {
        OBJVLINK_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjVLink_New( );
        if (pOther) {
            eRc = ObjVLink_Assign(this, pOther);
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

    void            ObjVLink_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJVLINK_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJVLINK_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ObjVLink_setObj(this, OBJ_NIL);
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
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        ObjVLink      *pDeepCopy = ObjVLink_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJVLINK object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJVLINK_DATA *     ObjVLink_DeepyCopy (
        OBJVLINK_DATA       *this
    )
    {
        OBJVLINK_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjVLink_New( );
        if (pOther) {
            eRc = ObjVLink_Assign(this, pOther);
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
    ERESULT         ObjVLink_Disable (
        OBJVLINK_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
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
    ERESULT         ObjVLink_Enable (
        OBJVLINK_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
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
    //                          G e t
    //---------------------------------------------------------------

    int32_t         ObjVLink_Get (
        OBJVLINK_DATA   *this,
        uint32_t        index
    )
    {
        int32_t         amt = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (0 == index) {
            return 0;
        }

        switch (index) {
            case OBJVLINK_INDEX_INDEX:
                amt = this->index;
                break;

            case OBJVLINK_INDEX_LEFT:
                amt = this->left;
                break;

            case OBJVLINK_INDEX_MIDDLE:
                amt = this->middle;
                break;

            case OBJVLINK_INDEX_MISC:
                amt = this->misc;
                break;

            case OBJVLINK_INDEX_PARENT:
                amt = this->parent;
                break;

            case OBJVLINK_INDEX_RIGHT:
                amt = this->right;
                break;

            default:
                if (this->pArray) {
                    amt =   I32Array_Get(
                                       this->pArray,
                                       (index - OBJVLINK_INDEX_HIGH + 1)
                            );
                }
                break;
        }

        // Return to caller.
        return amt;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJVLINK_DATA *   ObjVLink_Init (
        OBJVLINK_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJVLINK_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJVLINK);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjVLink_Vtbl);
        
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
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
        //fprintf(stderr, "ObjVLink::sizeof(OBJVLINK_DATA) = %lu\n", sizeof(OBJVLINK_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJVLINK_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjVLink_IsEnabled (
        OBJVLINK_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
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
    //                      N u m  V L i n k s
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    uint32_t        ObjVLink_NumVLinks (
        OBJVLINK_DATA	*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (OBJ_NIL == this->pArray) {
            return 0;
        }

        
        // Return to caller.
        return I32Array_getSize(this->pArray);
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
        void        *pMethod = ObjVLink_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjVLink", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjVLink_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJVLINK_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(OBJVLINK_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjVLink_Class();
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
                            return ObjVLink_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjVLink_Enable;
                        }
                        break;

#ifdef  OBJVLINK_JSON_SUPPORT
                    case 'P':
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return ObjVLink_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return ObjVLink_ParseJsonObject;
                        }
                        break;
#endif
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjVLink_ToDebugString;
                        }
#ifdef  OBJVLINK_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjVLink_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjVLink_ToDebugString)
                    return "ToDebugString";
#ifdef  OBJVLINK_JSON_SUPPORT
                if (pData == ObjVLink_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S e t
    //---------------------------------------------------------------

    int32_t         ObjVLink_Set (
        OBJVLINK_DATA   *this,
        uint32_t        index,
        int32_t         amt
    )
    {
        ERESULT         eRc;
        int32_t         amtRet = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjVLink_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        if (0 == index) {
            return 0;
        }

        switch (index) {
            case OBJVLINK_INDEX_INDEX:
                amtRet = this->index;
                this->index = amt;
                break;

            case OBJVLINK_INDEX_LEFT:
                amtRet = this->left;
                this->left = amt;
                break;

            case OBJVLINK_INDEX_MIDDLE:
                amtRet = this->middle;
                this->middle = amt;
                break;

            case OBJVLINK_INDEX_MISC:
                amtRet = this->misc;
                this->misc = amt;
                break;

            case OBJVLINK_INDEX_PARENT:
                amtRet = this->parent;
                this->parent = amt;
                break;

            case OBJVLINK_INDEX_RIGHT:
                amtRet = this->right;
                this->right = amt;
                break;

            default:
                if (OBJ_NIL == this->pArray) {
                    this->pArray = I32Array_New();
                }
                if (this->pArray) {
                    amtRet = I32Array_Get(
                                       this->pArray,
                                       (index - OBJVLINK_INDEX_HIGH + 1)
                            );
                    eRc =   I32Array_SetData(
                                 this->pArray,
                                 (index - OBJVLINK_INDEX_HIGH + 1),
                                 amt
                            );
                }
                break;
        }

        // Return to caller.
        return amtRet;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjVLink_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjVLink_ToDebugString (
        OBJVLINK_DATA      *this,
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
        if (!ObjVLink_Validate(this)) {
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
                    ObjVLink_getSize(this),
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
    bool            ObjVLink_Validate (
        OBJVLINK_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJVLINK))
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


        if (!(obj_getSize(this) >= sizeof(OBJVLINK_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


