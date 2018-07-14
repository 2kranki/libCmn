// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeLink.c
 *	Generated 06/30/2018 19:10:48
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
#include        <nodeLink_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            nodeLink_task_body(
        void            *pData
    )
    {
        //NODELINK_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODELINK_DATA *     nodeLink_Alloc(
    )
    {
        NODELINK_DATA   *this;
        uint32_t        cbSize = sizeof(NODELINK_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODELINK_DATA *     nodeLink_New(
    )
    {
        NODELINK_DATA       *this;
        
        this = nodeLink_Alloc( );
        if (this) {
            this = nodeLink_Init(this);
        } 
        return this;
    }


    NODELINK_DATA * nodeLink_NewWithUTF8AndClass(
        const
        char            *pNameA,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        NODELINK_DATA   *this;
        NAME_DATA       *pName = OBJ_NIL;
        
        this = nodeLink_Alloc( );
        if (this) {
            this = nodeLink_Init(this);
            if (this) {
                if (pNameA) {
                    pName = name_NewUTF8(pNameA);
                    node_setName((NODE_DATA *)this, pName);
                    obj_Release(pName);
                    pName = OBJ_NIL;
                }
                node_setClass((NODE_DATA *)this, cls);
                node_setData((NODE_DATA *)this, pData);
            }
        }
        return this;
    }

    
    NODELINK_DATA * nodeLink_NewWithUTF8ConAndClass(
        const
        char            *pNameA,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        NODELINK_DATA   *this;
        NAME_DATA       *pName = OBJ_NIL;
        
        this = nodeLink_Alloc( );
        if (this) {
            this = nodeLink_Init(this);
            if (this) {
                if (pNameA) {
                    pName = name_NewUTF8Con(pNameA);
                    node_setName((NODE_DATA *)this, pName);
                    obj_Release(pName);
                    pName = OBJ_NIL;
                }
                node_setClass((NODE_DATA *)this, cls);
                node_setData((NODE_DATA *)this, pData);
            }
        }
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      C h i l d  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getChild(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->leftIndex;
    }
    
    
    bool            nodeLink_setChild(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C l a s s
    //---------------------------------------------------------------
    
    int32_t         nodeLink_getClass(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return node_getClass((NODE_DATA *)this);
    }
    

    
    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------
    
    OBJ_ID          nodeLink_getData(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return node_getData((NODE_DATA *)this);
    }

    
    
    //---------------------------------------------------------------
    //                          E x t r a
    //---------------------------------------------------------------
    
    OBJ_ID          nodeLink_getExtra(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return node_getExtra((NODE_DATA *)this);
    }

    
    
    //---------------------------------------------------------------
    //                      F r o m  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getFrom(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->leftIndex;
    }
    
    
    bool            nodeLink_setFrom(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getIndex(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->index;
    }
    
    
    bool            nodeLink_setIndex(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->index = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L e f t  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getLeft(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->leftIndex;
    }
    
    
    bool            nodeLink_setLeft(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                   M i d d l e  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getMiddle(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->middleIndex;
    }
    
    
    bool            nodeLink_setMiddle(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->middleIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------
    
    NAME_DATA *     nodeLink_getName(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return node_getName((NODE_DATA *)this);
    }

    
    
    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------
    
    OBJ_ID          nodeLink_getOther(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return node_getOther((NODE_DATA *)this);
    }
    
    
    //---------------------------------------------------------------
    //                   P a r e n t  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getParent(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->parentIndex;
    }
    
    
    bool            nodeLink_setParent(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->parentIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        nodeLink_getPriority(
        NODELINK_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        obj_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            nodeLink_setPriority(
        NODELINK_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                      R i g h t  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getRight(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->rightIndex;
    }
    
    
    bool            nodeLink_setRight(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                    S i b l i n g  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getSibling(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->rightIndex;
    }
    
    
    bool            nodeLink_setSibling(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  nodeLink_getSuperVtbl(
        NODELINK_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        
        obj_setLastError(this, ERESULT_SUCCESS);
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                    T o  I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLink_getTo(
        NODELINK_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->rightIndex;
    }
    
    
    bool            nodeLink_setTo(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
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
        ERESULT eRc = nodeLink__Assign(this,pOther);
     @endcode 
     @param     this    NODELINK object pointer
     @param     pOther  a pointer to another NODELINK object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         nodeLink_Assign(
        NODELINK_DATA		*this,
        NODELINK_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeLink_Validate(pOther) ) {
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
        obj_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        obj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return obj_getLastError(this);
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
    ERESULT         nodeLink_Compare(
        NODELINK_DATA     *this,
        NODELINK_DATA     *pOther
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
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeLink_Validate(pOther) ) {
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
        
        obj_setLastError(this, eRc);
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        nodeLink      *pCopy = nodeLink_Copy(this);
     @endcode 
     @param     this    NODELINK object pointer
     @return    If successful, a NODELINK object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the NODELINK object.
     */
    NODELINK_DATA * nodeLink_Copy(
        NODELINK_DATA   *this
    )
    {
        NODELINK_DATA   *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeLink_New( );
        if (pOther) {
            eRc = nodeLink_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        obj_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeLink_Dealloc(
        OBJ_ID          objId
    )
    {
        NODELINK_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return;
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

    ERESULT         nodeLink_Disable(
        NODELINK_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         nodeLink_Enable(
        NODELINK_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODELINK_DATA * nodeLink_Init(
        NODELINK_DATA   *this
    )
    {
        uint32_t        cbSize = sizeof(NODELINK_DATA);
        
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

        this = (OBJ_ID)node_Init((NODE_DATA *)this);    // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODELINK);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODELINK); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeLink_Vtbl);
        
        obj_setLastError(this, ERESULT_GENERAL_FAILURE);
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "nodeLink::sizeof(NODELINK_DATA) = %lu\n", sizeof(NODELINK_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODELINK_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         nodeLink_IsEnabled(
        NODELINK_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            obj_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = nodeLink_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "nodeLink", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeLink_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODELINK_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)nodeLink_Class();
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
                            return nodeLink_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return nodeLink_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeLink_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return nodeLink_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == nodeLink_ToDebugString)
                    return "ToDebugString";
                if (pData == nodeLink_ToJSON)
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
        ASTR_DATA      *pDesc = nodeLink_ToDebugString(this,4);
     @endcode 
     @param     this    NODELINK object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeLink_ToDebugString(
        NODELINK_DATA      *this,
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
        if( !nodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s)\n",
                    this,
                    pInfo->pClassName
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(
                         pStr,
                         "\"index\":\"%s\", "
                         "\"leftIndex\":\"%s\", "
                         "\"middleIndex\":\"%d\", "
                         "\"parentIndex\":\"%d\", "
                         "\"rightIndex\":%d\n",
                         this->index,
                         this->leftIndex,
                         this->middleIndex,
                         this->parentIndex,
                         this->rightIndex
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
        
        obj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeLink_Validate(
        NODELINK_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODELINK) )
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


        if( !(obj_getSize(this) >= sizeof(NODELINK_DATA)) ) {
            obj_setLastError(this, ERESULT_INVALID_OBJECT);
            return false;
        }

        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


