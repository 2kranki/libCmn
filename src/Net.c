// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Net.c
 *  Generated 07/03/2021 07:04:16
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
#include        <Net_internal.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    //---------------------------------------------------------------
    //          A c q u i r e  L i s t e n  S o c k e t
    //---------------------------------------------------------------

    /*!
     Acquire a TCP/IP socket to listen on. If successful, the socket
     will
     @param     this    object pointer
     @param     pPort   port pointer
     @param     cQueue  pending connections queue size
     @return    if successful, ERESULT_SUCCESS, NET_FLAG_OPEN is on and
                this->socket is valid.  Otherwise, an ERESULT_* error
                code.
     */
    ERESULT         Net_AcquireListenSocket (
        NET_DATA        *this,
        const
        char            *pPort,
        int             cQueue      // pending connections queue size
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        struct addrinfo hints;
        struct addrinfo *servinfo;
        struct addrinfo *p;
        int             yes = 1;
        int             rv;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        TRC_OBJ(this,"%s:\n", __func__);

        if (obj_Flag(this, NET_FLAG_OPEN)) {
            return ERESULT_OPEN_ERROR;
        }
        
        // This block of code looks at the local network interfaces and
        // tries to find some that match our requirements (namely either
        // IPv4 or IPv6 (PF_UNSPEC) and TCP (SOCK_STREAM) and use any IP on
        // this machine (AI_PASSIVE).
        // "man 3 getaddrinfo" tells how to fill this out.
        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;                // Use IPv4 or IPv6
        hints.ai_socktype = SOCK_STREAM;            // TCP stream sockets
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;                // Use my IP

        // The getaddrinfo() function is used to get a list of IP addresses
        // and port numbers for host hostname and service servname.
        rv =    getaddrinfo(
                    NULL,           // e.g. "www.example.com" or IP
                    pPort,          // e.g. "http" or port number
                    &hints,         // ???
                    &servinfo       // (output)
                );
        if (rv != 0) {
            TRC_OBJ(this, "\tgetaddrinfo: %s\n", gai_strerror(rv));
            return ERESULT_DATA_NOT_FOUND;
        }

        // Once we have a list of potential interfaces, loop through them
        // and try to set up a socket on each. Quit looping the first time
        // we have success. ???
        for (p = servinfo; p != NULL; p = p->ai_next) {

            // Try to make a socket based on this candidate interface
            // "man 2 socket" tells how to fill this out.
            this->socket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
            if (this->socket == -1) {
                continue;
            }

            // SO_REUSEADDR prevents the "address already in use" errors
            // that commonly come up when testing servers.
            // "man 2 setsockopt"
            rv = setsockopt(this->socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
            if ( rv == -1) {
                TRC_OBJ(this, "\tsetsockopt: errno: %d\n", errno);
                close(this->socket);
                this->socket = -1;
                freeaddrinfo(servinfo);
                return ERESULT_IO_ERROR;
            }

            // See if we can bind this socket to this local IP address. This
            // associates the file descriptor (the socket descriptor) that
            // we will read and write on with a specific IP address.
            // "man 2 bind"
            rv = bind(this->socket, p->ai_addr, p->ai_addrlen);
            if (rv == 0) {
                break;
            }

            // We could not bind this socket. So, let's try the next one.
            close(this->socket);
            this->socket = -1;
        }

        // "man 3 freeaddrinfo" tells about this.
        freeaddrinfo(servinfo); // all done with this structure

        // If p is NULL, it means we didn't break out of the loop, above,
        // and we don't have a good socket.
        if (p == NULL)  {
            TRC_OBJ(this, "\tFailed to find a local address!\n");
            return ERESULT_DATA_NOT_FOUND;
        }

        // Creation of socket-based connections requires several operations.
        // First, a socket is created with socket(2). Next, a willingness to
        // accept incoming connections and a queue limit for incoming con-
        // nections are specified with listen().  Finally, the connections
        // are accepted with accept(2).  The listen() call applies only to
        // sockets of type SOCK_STREAM.
        // "man 2 listen" tells about this.
        rv = listen(this->socket, cQueue);
        if (rv == -1) {
            close(this->socket);
            this->socket = -1;
            return ERESULT_IO_ERROR;
        }

        obj_FlagOn(this, NET_FLAG_OPEN);

        // Return to caller.
        return eRc;
    }




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NET_DATA *     Net_Alloc (
        void
    )
    {
        NET_DATA       *this;
        uint32_t        cbSize = sizeof(NET_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NET_DATA *     Net_New (
        void
    )
    {
        NET_DATA       *this;
        
        this = Net_Alloc( );
        if (this) {
            this = Net_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        Net_getPriority (
        NET_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Net_setPriority (
        NET_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
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
    
    uint32_t        Net_getSize (
        NET_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * Net_getStr (
        NET_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        Net_setStr (
        NET_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Net_getSuperVtbl (
        NET_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
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
        ERESULT eRc = Net_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NET object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Net_Assign (
        NET_DATA       *this,
        NET_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Net_Validate(pOther)) {
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
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                     C l o s e
    //---------------------------------------------------------------

    ERESULT         Net_Close (
        NET_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        if (!obj_Flag(this, NET_FLAG_OPEN)) {
            return ERESULT_CLOSE_ERROR;
        }

        close(this->socket);
        this->socket = -1;

        obj_FlagOff(this, NET_FLAG_OPEN);

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
    int             Net_Compare (
        NET_DATA     *this,
        NET_DATA     *pOther
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
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Net_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Net      *pCopy = Net_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NET object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NET_DATA *     Net_Copy (
        NET_DATA       *this
    )
    {
        NET_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NET_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Net_New( );
        if (pOther) {
            eRc = Net_Assign(this, pOther);
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

    void            Net_Dealloc (
        OBJ_ID          objId
    )
    {
        NET_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NET_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Net_setStr(this, OBJ_NIL);

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
        Net      *pDeepCopy = Net_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NET object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NET_DATA *     Net_DeepyCopy (
        NET_DATA       *this
    )
    {
        NET_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Net_New( );
        if (pOther) {
            eRc = Net_Assign(this, pOther);
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
    ERESULT         Net_Disable (
        NET_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
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
    ERESULT         Net_Enable (
        NET_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
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

    NET_DATA *   Net_Init (
        NET_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NET_DATA);
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
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Net_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NET);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Net_Vtbl);
#ifdef  NET_JSON_SUPPORT
        JsonIn_RegisterClass(Net_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Net::sizeof(NET_DATA) = %lu\n", 
                sizeof(NET_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NET_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Net_IsEnabled (
        NET_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
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
        void        *pMethod = Net_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Net", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Net_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NET_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NET_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Net_Class();
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
                            return Net_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Net_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NET_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Net_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Net_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Net_ToDebugString;
                        }
#ifdef  NET_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Net_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Net_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Net_ToDebugString)
                    return "ToDebugString";
#ifdef  NET_JSON_SUPPORT
                if (pData == Net_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e r v e r
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Net_ServerStart (
        NET_DATA        *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!Net_Validate(this)) {
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
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Net_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Net_ToDebugString (
        NET_DATA      *this,
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
        if (!Net_Validate(this)) {
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
                    Net_getSize(this),
                    obj_getRetainCount(this)
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
    bool            Net_Validate (
        NET_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NET))
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


        if (!(obj_getSize(this) >= sizeof(NET_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


