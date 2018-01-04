// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   msgData.c
 *	Generated 11/04/2017 09:37:49
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
#include <msgData_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            msgData_task_body(
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

    MSGDATA_DATA *  msgData_Alloc(
        uint16_t        size
    )
    {
        MSGDATA_DATA    *this;
        uint32_t        cbSize = sizeof(MSGDATA_DATA);
        
        // Do initialization.
        
        if (0 == size) {
            size = 256;
        }
        if (size > (65536 - sizeof(MSGDATA_DATA)) ) {
            return OBJ_NIL;
        }
        cbSize += size;
        this = obj_Alloc( cbSize );
        obj_setMisc1(this, size);
        
        // Return to caller.
        return this;
    }



    MSGDATA_DATA *  msgData_New(
        uint32_t        origin,
        uint32_t        dest,
        uint16_t        size,
        void            *pData
    )
    {
        MSGDATA_DATA       *this;
        
        this = msgData_Alloc(size);
        if (this) {
            this = msgData_Init(this, origin, dest, size, pData);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         D a t a
    //---------------------------------------------------------------
    
    void *          msgData_getData(
        MSGDATA_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return this->data;
    }
    
    
    
    //---------------------------------------------------------------
    //                   D e s t i n a t i o n
    //---------------------------------------------------------------
    
    uint32_t        msgData_getDestination(
        MSGDATA_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return this->dest;
    }
    
    
    bool            msgData_setDestination(
        MSGDATA_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->dest = value;
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         msgData_getLastError(
        MSGDATA_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            msgData_setLastError(
        MSGDATA_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                        N u m 3 2
    //---------------------------------------------------------------
    
    uint32_t        msgData_getNum32(
        MSGDATA_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return this->num32;
    }
    
    
    bool            msgData_setNum32(
        MSGDATA_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->num32 = value;
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        O r i g i n
    //---------------------------------------------------------------
    
    uint32_t        msgData_getOrigin(
        MSGDATA_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return this->origin;
    }
    
    
    bool            msgData_setOrigin(
        MSGDATA_DATA    *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->origin = value;
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint16_t        msgData_getSize(
        MSGDATA_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        msgData_setLastError(this, ERESULT_SUCCESS);
        return this->size;
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
        ERESULT eRc = msgData__Assign(this,pOther);
     @endcode 
     @param     this    MSGDATA object pointer
     @param     pOther  a pointer to another MSGDATA object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         msgData_Assign(
        MSGDATA_DATA		*this,
        MSGDATA_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !msgData_Validate(pOther) ) {
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
        msgData_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        msgData_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return msgData_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        msgData      *pCopy = msgData_Copy(this);
     @endcode 
     @param     this    MSGDATA object pointer
     @return    If successful, a MSGDATA object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the MSGDATA object.
     */
    MSGDATA_DATA *  msgData_Copy(
        MSGDATA_DATA    *this
    )
    {
        MSGDATA_DATA    *pOther = OBJ_NIL;
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = msgData_New(this->origin, this->dest, this->size, this->data);
        if (OBJ_NIL == pOther) {
            msgData_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        pOther->num32 = this->num32;
        
        // Return to caller.
        msgData_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            msgData_Dealloc(
        OBJ_ID          objId
    )
    {
        MSGDATA_DATA    *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((MSGDATA_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        //msgData_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         msgData_Disable(
        MSGDATA_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        msgData_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         msgData_Enable(
        MSGDATA_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        msgData_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    MSGDATA_DATA *  msgData_Init(
        MSGDATA_DATA    *this,
        uint32_t        origin,
        uint32_t        dest,
        uint16_t        size,
        void            *pData
    )
    {
        uint32_t        cbSize = sizeof(MSGDATA_DATA);
        uint32_t        dataSize = 0;

        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        dataSize = obj_getMisc1(this);
        if ((dataSize == 0) || !(dataSize == size)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MSGDATA);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_MSGDATA);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&msgData_Vtbl);
        
        msgData_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->origin = origin;
        this->dest = dest;
        this->size = size;
        memmove(this->data, pData, this->size);

    #ifdef NDEBUG
    #else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "msgData::offsetof(eRc) = %lu\n", offsetof(MSGDATA_DATA,eRc));
        //fprintf(stderr, "msgData::sizeof(MSGDATA_DATA) = %lu\n", sizeof(MSGDATA_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(MSGDATA_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         msgData_IsEnabled(
        MSGDATA_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            msgData_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        msgData_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = msgData_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   OBJTEST object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "msgData", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          msgData_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MSGDATA_DATA   *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return msgData_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return msgData_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return msgData_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return msgData_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == msgData_ToDebugString)
                    return "ToDebugString";
                if (pData == msgData_ToJSON)
                    return "ToJSON";
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
        ASTR_DATA      *pDesc = msgData_ToDebugString(this,4);
     @endcode 
     @param     this    MSGDATA object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     msgData_ToDebugString(
        MSGDATA_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = msgData_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    msgData_getSize(this)
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     msgData_ToJSON(
        MSGDATA_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !msgData_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        msgData_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            msgData_Validate(
        MSGDATA_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_MSGDATA) )
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


        if( !(obj_getSize(this) >= sizeof(MSGDATA_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


