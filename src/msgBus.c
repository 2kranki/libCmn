// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   msgBus.c
 *	Generated 05/31/2017 20:00:00
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
#include    <msgBus_internal.h>
#include    <ObjMethod.h>
#include    <Value.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /*
     This routine is passed messages, msgData objects, and consults
     the array of nodes to know where to send those messages. The
     data element of each node contains an object method that is to
     be executed upon receipt of an appropriate message.
     */
    static
    void *          msgBus_task_body(
        void            *pData
    )
    {
        MSGBUS_DATA     *this = pData;
        MSGDATA_DATA    *pEntry = OBJ_NIL;
        MSGDATA_DATA    *pCopy = OBJ_NIL;
        bool            fRc = false;
        uint32_t        i;
        uint32_t        iMax;
        NODE_DATA       *pNode = OBJ_NIL;
        OBJMETHOD_DATA  *pMethod = OBJ_NIL;
        void            (*pMsgOutBody)(void *, OBJ_ID) = NULL;
        void            *pMsgOutData;
        uint32_t        origin;
        uint32_t        dest;
        uint32_t        nodeID;

        // WARNING: We had to make this pausible.
        fRc = objCb_Get(this->pBuffer, (void **)&pEntry);
        if (fRc && pEntry) {
            origin = MsgData_getOrigin(pEntry);
            dest = MsgData_getDestination(pEntry);
            iMax = NodeArray_getSize(this->pRegistry);
            if (dest) {     /*** Specific Node ***/
                for (i=0; i<iMax; ++i) {
                    pNode = NodeArray_Get(this->pRegistry, i+1);
                    if (pNode) {
                        nodeID = (uint32_t)node_getNameInt(pNode);
                        if (nodeID == dest) {
                            pMethod = node_getData(pNode);
                            pMsgOutBody = ObjMethod_getMethod(pMethod);
                            pMsgOutData = ObjMethod_getObject(pMethod);
                            pCopy = MsgData_Copy(pEntry);
                            pMsgOutBody(pMsgOutData, pCopy);
                            obj_Release(pCopy);
                            pCopy = OBJ_NIL;
                            break;
                        }
                    }
                }
                pNode = OBJ_NIL;
            }
            else {          /*** General Broadcast ***/
                for (i=0; i<iMax; ++i) {
                    pNode = NodeArray_Get(this->pRegistry, i+1);
                    if (pNode) {
                        nodeID = (uint32_t)node_getNameInt(pNode);
                        if (nodeID == MsgData_getOrigin(pEntry))
                            ;
                        else {
                            pMethod = node_getData(pNode);
                            pMsgOutBody = ObjMethod_getMethod(pMethod);
                            pMsgOutData = ObjMethod_getObject(pMethod);
                            pCopy = MsgData_Copy(pEntry);
                            MsgData_setNum32(pCopy, nodeID);
                            pMsgOutBody(pMsgOutData, pCopy);
                            obj_Release(pCopy);
                            pCopy = OBJ_NIL;
                        }
                    }
                }
                pNode = OBJ_NIL;
            }
            obj_Release(pEntry);
            pEntry = OBJ_NIL;
        }
        
        return NULL;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    MSGBUS_DATA *   msgBus_Alloc(
    )
    {
        MSGBUS_DATA     *this;
        uint32_t        cbSize = sizeof(MSGBUS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc(cbSize);
        
        // Return to caller.
        return this;
    }



    MSGBUS_DATA *     msgBus_New(
        uint16_t        messageCount        // Max Message Queue size
    )
    {
        MSGBUS_DATA       *this;
        
        this = msgBus_Alloc( );
        if (this) {
            this = msgBus_Init(this, messageCount);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    NODEARRAY_DATA * msgBus_getRegistry(
        MSGBUS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pRegistry;
    }
    
    
    bool        msgBus_setRegistry(
        MSGBUS_DATA     *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pRegistry) {
            obj_Release(this->pRegistry);
        }
        this->pRegistry = pValue;
        
        return true;
    }
    
    
    
    uint32_t        msgBus_getRegistrySize(
        MSGBUS_DATA     *this
    )
    {
        uint32_t        size = 0;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        size = NodeArray_getSize(this->pRegistry);
        
        return size;
    }
    
    

    uint32_t        msgBus_getWait(
        MSGBUS_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->msWait;
    }
    
    
    bool            msgBus_setWait(
        MSGBUS_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->msWait = value;
        
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
        ERESULT eRc = msgBus__Assign(this,pOther);
     @endcode
     @param     this    MSGBUS object pointer
     @param     pOther  a pointer to another MSGBUS object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         msgBus_Assign(
        MSGBUS_DATA		*this,
        MSGBUS_DATA      *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !msgBus_Validate(pOther) ) {
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
    //                       B r o a d c a s t
    //---------------------------------------------------------------
    
    ERESULT     msgBus_Broadcast(
        MSGBUS_DATA		*this,
        int32_t         msgOrigin,
        int32_t         msgDest,
        uint16_t        msgLen,
        uint8_t         *pMsgData
    )
    {
        MSGDATA_DATA    *pEntry = OBJ_NIL;
        bool            fRc = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pEntry = MsgData_NewWithData(msgOrigin, msgDest, msgLen, pMsgData);
        if (OBJ_NIL == pEntry) {
            return ERESULT_INVALID_DATA;
        }
        fRc = objCb_Put(this->pBuffer, pEntry);
        obj_Release(pEntry);
        pEntry = OBJ_NIL;
        if (!fRc) {
            return ERESULT_GENERAL_FAILURE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }

    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        msgBus      *pCopy = msgBus_Copy(this);
     @endcode
     @param     this    MSGBUS object pointer
     @return    If successful, a MSGBUS object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the MSGBUS object.
     */
    MSGBUS_DATA *     msgBus_Copy(
        MSGBUS_DATA     *this
    )
    {
        MSGBUS_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        //FIXME: pOther = msgBus_New(obj_getSize(this));
        if (pOther) {
            eRc = msgBus_Assign(this, pOther);
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

    void            msgBus_Dealloc(
        OBJ_ID          objId
    )
    {
        MSGBUS_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        // WARNING: Order is important here!

        objCb_Pause(this->pBuffer);
        psxThread_Wait(500);
        psxThread_Terminate(this->pThread);
        
        if (this->pThread) {
            obj_Release(this->pThread);
            this->pThread = OBJ_NIL;
        }

        if (this->pBuffer) {
            obj_Release(this->pBuffer);
            this->pBuffer = OBJ_NIL;
        }

        if (this->pRegistry) {
            obj_Release(this->pRegistry);
            this->pRegistry = OBJ_NIL;
        }
        
        if (this->pLock) {
            obj_Release(this->pLock);
            this->pLock = OBJ_NIL;
        }

        msgBus_setRegistry(this, OBJ_NIL);

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

    ERESULT         msgBus_Disable(
        MSGBUS_DATA		*this
    )
    {

        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
    #ifdef NDEBUG
    #else
        if( !msgBus_Validate(this) ) {
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

    ERESULT         msgBus_Enable(
        MSGBUS_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !msgBus_Validate(this) ) {
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

    MSGBUS_DATA *   msgBus_Init(
        MSGBUS_DATA     *this,
        uint16_t        messageCount        // Max Message Queue size
    )
    {
        uint32_t        cbSize = sizeof(MSGBUS_DATA);
        
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_MSGBUS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                          // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_MSGBUS);       // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&msgBus_Vtbl);
        
        this->msWait = 10;

        // WARNING: Order is important here!
        
        this->pLock = psxLock_New( );
        if (OBJ_NIL == this->pLock) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pRegistry = NodeArray_New();
        if (OBJ_NIL == this->pRegistry) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pBuffer = objCb_New(messageCount);
        if (OBJ_NIL == this->pBuffer) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->pThread = psxThread_New(msgBus_task_body, this, 0);
        if (OBJ_NIL == this->pThread) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "msgBus::sizeof(OBJMETHOD_DATA) = %lu\n", sizeof(MSGBUS_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(MSGBUS_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         msgBus_IsEnabled(
        MSGBUS_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
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
    
    void *          msgBus_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MSGBUS_DATA     *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
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
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return msgBus_ToDebugString;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if ((void *)pStr == msgBus_ToDebugString)
                    return "ToDebugString";
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      R e g i s t e r
    //---------------------------------------------------------------
    
    ERESULT         msgBus_RegisterObjectMethod(
        MSGBUS_DATA     *this,
        OBJMETHOD_DATA  *pRcvObj,
        int32_t         *pToken
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pRegistry == OBJ_NIL) {
            this->pRegistry = NodeArray_New();
            if (this->pRegistry == OBJ_NIL) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        ++this->unique;
        pNode = node_NewWithInt(this->unique, pRcvObj);
        if (pNode == OBJ_NIL) {
            return ERESULT_OUT_OF_MEMORY;
        }
        
        NodeArray_AppendNode(this->pRegistry, pNode, NULL);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         msgBus_RegisterObjectVtbl(
        MSGBUS_DATA		*this,
        OBJ_ID          *pRcvObj,
        uint16_t        vtblOffset,
        int32_t         *pToken
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (this->pRegistry == OBJ_NIL) {
            this->pRegistry = NodeArray_New();
            if (this->pRegistry == OBJ_NIL) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        ++this->unique;
        pNode = node_NewWithInt(this->unique, pRcvObj);
        if (pNode == OBJ_NIL) {
            return ERESULT_OUT_OF_MEMORY;
        }
        node_setMisc1(pNode, vtblOffset);
        
        NodeArray_AppendNode(this->pRegistry, pNode, NULL);
        obj_Release(pNode);
        pNode = OBJ_NIL;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = msgBus_ToDebugString(this,4);
     @endcode
     @param     this    MSGBUS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     msgBus_ToDebugString(
        MSGBUS_DATA      *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(msgBus)\n",
                     this
            );
        AStr_AppendA(pStr, str);

        if (this->pRegistry) {
            if (((OBJ_DATA *)(this->pRegistry))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pRegistry))->pVtbl->pToDebugString(
                                                    this->pRegistry,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(msgBus)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      U n r e g i s t e r
    //---------------------------------------------------------------
    
    ERESULT         msgBus_UnregisterObject(
        MSGBUS_DATA		*this,
        int32_t         token
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        uint32_t        i;
        uint32_t        iMax;
        uint32_t        nodeID;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !msgBus_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (token == 0) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (this->pRegistry == OBJ_NIL) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        iMax = NodeArray_getSize(this->pRegistry);
        for (i=0; i<iMax; ++i) {
            pNode = NodeArray_Get(this->pRegistry, i+1);
            if (pNode) {
                nodeID = (uint32_t)node_getNameInt(pNode);
                if (token == nodeID) {
                    pNode = NodeArray_Delete(this->pRegistry, i+1);
                    obj_Release(pNode);
                    pNode = OBJ_NIL;
                    return ERESULT_SUCCESS;
                    break;
                }
            }
        }
        
        // Return to caller.
        return ERESULT_DATA_NOT_FOUND;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            msgBus_Validate(
        MSGBUS_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_MSGBUS) )
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


        if( !(obj_getSize(this) >= sizeof(MSGBUS_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


