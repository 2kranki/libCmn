// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   MsgData.c
 *	Generated 12/31/2019 10:05:08
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
#include        <MsgData_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            MsgData_task_body (
        void            *pData
    )
    {
        //MSGDATA_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MSGDATA_DATA *     MsgData_Alloc (
        void
    )
    {
        MSGDATA_DATA       *this;
        uint32_t        cbSize = sizeof(MSGDATA_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    MSGDATA_DATA *     MsgData_New (
        void
    )
    {
        MSGDATA_DATA       *this;
        
        this = MsgData_Alloc( );
        if (this) {
            this = MsgData_Init(this);
        } 
        return this;
    }


    MSGDATA_DATA *  MsgData_NewWithData (
        uint32_t        origin,
        uint32_t        dest,
        uint32_t        size,
        void            *pData
    )
    {
        MSGDATA_DATA       *this;

        this = MsgData_New();
        if (this) {
            this->origin = origin;
            this->dest = dest;
            Value_setDataFree((VALUE_DATA *)this, size, pData);
        }
        return this;
    }




    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                   D a t a
    //---------------------------------------------------------------

    void *          MsgData_getData (
        MSGDATA_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !MsgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (void *)Value_getData((VALUE_DATA *)this);
    }

    

    //---------------------------------------------------------------
    //                   D e s t i n a t i o n
    //---------------------------------------------------------------

    uint32_t        MsgData_getDestination (
        MSGDATA_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !MsgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->dest;
    }


    bool            MsgData_setDestination (
        MSGDATA_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !MsgData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->dest = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        N u m 3 2
    //---------------------------------------------------------------

    uint32_t        MsgData_getNum32 (
        MSGDATA_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !MsgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->num32;
    }


    bool            MsgData_setNum32 (
        MSGDATA_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !MsgData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->num32 = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        O r i g i n
    //---------------------------------------------------------------

    uint32_t        MsgData_getOrigin (
        MSGDATA_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !MsgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->origin;
    }


    bool            MsgData_setOrigin (
        MSGDATA_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !MsgData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->origin = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        MsgData_getSize (
        MSGDATA_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Value_getDataLen((VALUE_DATA *)this);
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  MsgData_getSuperVtbl (
        MSGDATA_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
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
        ERESULT eRc = MsgData_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another MSGDATA object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         MsgData_Assign (
        MSGDATA_DATA    *this,
        MSGDATA_DATA    *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!MsgData_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release objects and areas in other object.

        // Create a copy of objects and areas in this object placing
        // them in other.
        eRc = Value_Assign((VALUE_DATA *)this, (VALUE_DATA *)pOther);
        if (ERESULT_FAILED(eRc)) {
            goto eom;
        }

        // Copy other data from this object to other.
        pOther->dest   = this->dest;
        pOther->num32  = this->num32;
        pOther->origin = this->origin;

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
    int             MsgData_Compare (
        MSGDATA_DATA    *this,
        MSGDATA_DATA    *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!MsgData_Validate(pOther)) {
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
        MsgData      *pCopy = MsgData_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a MSGDATA object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    MSGDATA_DATA *     MsgData_Copy (
        MSGDATA_DATA       *this
    )
    {
        MSGDATA_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = MsgData_New( );
        if (pOther) {
            eRc = MsgData_Assign(this, pOther);
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

    void            MsgData_Dealloc (
        OBJ_ID          objId
    )
    {
        MSGDATA_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MSGDATA_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

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
    ERESULT         MsgData_Disable (
        MSGDATA_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!MsgData_Validate(this)) {
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
    ERESULT         MsgData_Enable (
        MSGDATA_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!MsgData_Validate(this)) {
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

    MSGDATA_DATA *   MsgData_Init (
        MSGDATA_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(MSGDATA_DATA);
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

        this = (OBJ_ID)Value_Init((VALUE_DATA *)this);          // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MSGDATA);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                              // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&MsgData_Vtbl);
        
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
        if (!MsgData_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "MsgData::sizeof(MSGDATA_DATA) = %lu\n", sizeof(MSGDATA_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MSGDATA_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         MsgData_IsEnabled (
        MSGDATA_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
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
        void        *pMethod = MsgData_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "MsgData", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          MsgData_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MSGDATA_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!MsgData_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(MSGDATA_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)MsgData_Class();
                break;
                
#ifdef XYZZY  
            // Query for an address to specific data within the object.  
            // This should be used very sparingly since it breaks the 
            // object's encapsulation.                 
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return obj_getInfo(this)->pClassSuperObject;
                        }
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
                            return MsgData_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return MsgData_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return MsgData_ToDebugString;
                        }
#ifdef  MSGDATA_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return MsgData_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == MsgData_ToDebugString)
                    return "ToDebugString";
#ifdef  MSGDATA_JSON_SUPPORT
                if (pData == MsgData_ToJson)
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
        ASTR_DATA      *pDesc = MsgData_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     MsgData_ToDebugString (
        MSGDATA_DATA      *this,
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
        if (!MsgData_Validate(this)) {
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
                    MsgData_getSize(this),
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
    bool            MsgData_Validate (
        MSGDATA_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_MSGDATA))
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


        if (!(obj_getSize(this) >= sizeof(MSGDATA_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


