// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeLnkP.c
 *	Generated 11/19/2018 07:52:23
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
#include        <nodeLnkP_internal.h>
#include        <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            nodeLnkP_task_body(
        void            *pData
    )
    {
        //NODELNKP_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODELNKP_DATA *     nodeLnkP_Alloc(
        void
    )
    {
        NODELNKP_DATA       *this;
        uint32_t        cbSize = sizeof(NODELNKP_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODELNKP_DATA *     nodeLnkP_New(
        void
    )
    {
        NODELNKP_DATA       *this;
        
        this = nodeLnkP_Alloc( );
        if (this) {
            this = nodeLnkP_Init(this);
        } 
        return this;
    }


    NODELNKP_DATA * nodeLnkP_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        NODELNKP_DATA   *this;
        NAME_DATA       *pName = OBJ_NIL;
        
        this = nodeLnkP_Alloc( );
        if (this) {
            this = nodeLnkP_Init(this);
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
    
    
    NODELNKP_DATA * nodeLnkP_NewWithUTF8ConAndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        NODELNKP_DATA   *this;
        NAME_DATA       *pName = OBJ_NIL;
        
        this = nodeLnkP_Alloc( );
        if (this) {
            this = nodeLnkP_Init(this);
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
    //                         B a l a n c e
    //---------------------------------------------------------------
    
    int16_t         nodeLnkP_getBalance(
        NODELNKP_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return (int16_t)obj_getMisc1(this);
    }
    
    
    bool            nodeLnkP_setBalance(
        NODELNKP_DATA   *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_setMisc1(this, value);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    uint32_t        nodeLnkP_getIndex(
        NODELNKP_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->index;
    }
    
    
    bool            nodeLnkP_setIndex(
        NODELNKP_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
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
    
    NODELNKP_DATA * nodeLnkP_getLeftLink(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc;
        NODELNKP_DATA   *pNode = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_LEFT_LINK);
        if (fRc)
            pNode = this->pLeft;
        
        return pNode;
    }
    
    
    bool            nodeLnkP_setLeftLink(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

#ifdef OWNED_POINTERS
        obj_Retain(pValue);
        if (this->pLeft) {
            obj_Release(this->pLeft);
        }
#endif
        this->pLeft = pValue;
        
        obj_FlagSet(this, NODELINK_LEFT_LINK, (pValue ? true : false));
        
        return true;
    }
    
    
    
    NODELNKP_DATA * nodeLnkP_getLeftThread(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc;
        NODELNKP_DATA   *pNode = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_LEFT_LINK);
        if (!fRc)
            pNode = this->pLeft;
        
        return pNode;
    }
    
    
    bool            nodeLnkP_setLeftThread(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef OWNED_POINTERS
        obj_Retain(pValue);
        if (this->pLeft) {
            obj_Release(this->pLeft);
        }
#endif
        this->pLeft = pValue;
        
        obj_FlagSet(this, NODELINK_LEFT_LINK, false);
        
        return true;
    }
    
    
    

    //---------------------------------------------------------------
    //                         M i d d l e
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeLnkP_getMiddle(
        NODELNKP_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pMiddle;
    }
    
    
    bool            nodeLnkP_setMiddle(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef OWNED_POINTERS
        obj_Retain(pValue);
        if (this->pMiddle) {
            obj_Release(this->pMiddle);
        }
#endif
        this->pMiddle = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------
    
    NAME_DATA *     nodeLnkP_getName(
        NODELNKP_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return node_getName((NODE_DATA *)this);
    }
    
    
    char *          nodeLnkP_getNameUTF8(
        NODELNKP_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return node_getNameUTF8((NODE_DATA *)this);
    }
    
    

    //---------------------------------------------------------------
    //                         P a r e n t
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeLnkP_getParent(
        NODELNKP_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pParent;
    }
    
    
    bool            nodeLnkP_setParent(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef OWNED_POINTERS
        obj_Retain(pValue);
        if (this->pParent) {
            obj_Release(this->pParent);
        }
#endif
        this->pParent = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        nodeLnkP_getPriority(
        NODELNKP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            nodeLnkP_setPriority(
        NODELNKP_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                         R e d
    //---------------------------------------------------------------
    
    bool            nodeLnkP_getRed(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_RED);
        
        return fRc;
    }
    
    
    bool            nodeLnkP_setRed(
        NODELNKP_DATA   *this,
        bool            fValue
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_FlagSet(this, NODELINK_RED, fValue);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                         R i g h t
    //---------------------------------------------------------------
    
    NODELNKP_DATA * nodeLnkP_getRight(
        NODELNKP_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pRight;
    }
    
    
    bool            nodeLnkP_setRight(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef OWNED_POINTERS
        obj_Retain(pValue);
        if (this->pRight) {
            obj_Release(this->pRight);
        }
#endif
        this->pRight = pValue;
        
        return true;
    }
    
    
    bool            nodeLnkP_getRightChild(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_RIGHT_CHILD);
        
        return fRc;
    }
    
    
    bool            nodeLnkP_setRightChild(
        NODELNKP_DATA   *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_FlagSet(this, NODELINK_RIGHT_CHILD, fValue);
        
        return true;
    }
    
    
    NODELNKP_DATA * nodeLnkP_getRightLink(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc;
        NODELNKP_DATA   *pNode = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_RIGHT_LINK);
        if (fRc)
            pNode = this->pRight;
        
        return pNode;
    }
    
    
    bool            nodeLnkP_setRightLink(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
#ifdef OWNED_POINTERS
        obj_Retain(pValue);
        if (this->pRight) {
            obj_Release(this->pRight);
        }
#endif
        this->pRight = pValue;
        
        obj_FlagSet(this, NODELINK_RIGHT_LINK, (pValue ? true : false));
        
        return true;
    }
    
    
    
    NODELNKP_DATA * nodeLnkP_getRightThread(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc;
        NODELNKP_DATA   *pNode = OBJ_NIL;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_RIGHT_LINK);
        if (!fRc)
            pNode = this->pRight;
        
        return pNode;
    }
    
    
    bool            nodeLnkP_setRightThread(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pValue
    )
    {
        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pRight) {
            obj_Release(this->pRight);
        }
        this->pRight = pValue;
        
        obj_FlagSet(this, NODELINK_RIGHT_LINK, false);
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        nodeLnkP_getSize(
        NODELNKP_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  nodeLnkP_getSuperVtbl(
        NODELNKP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
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
        ERESULT eRc = nodeLnkP_Assign(this,pOther);
     @endcode 
     @param     this    NODELNKP object pointer
     @param     pOther  a pointer to another NODELNKP object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         nodeLnkP_Assign(
        NODELNKP_DATA		*this,
        NODELNKP_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeLnkP_Validate(pOther) ) {
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
    ERESULT         nodeLnkP_Compare(
        NODELNKP_DATA     *this,
        NODELNKP_DATA     *pOther
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeLnkP_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = node_Compare((NODE_DATA *)this, (NODE_DATA *)pOther);

        return eRc;
    }
    

    ERESULT         nodeLnkP_CompareA(
        NODELNKP_DATA   *this,
        int32_t         cls,
        const
        char            *pNameA
    )
    {
        ERESULT         eRc;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = node_CompareA((NODE_DATA *)this, cls, pNameA);
        
        return eRc;
    }
    
    

    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        nodeLnkP      *pCopy = nodeLnkP_Copy(this);
     @endcode 
     @param     this    NODELNKP object pointer
     @return    If successful, a NODELNKP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODELNKP_DATA *     nodeLnkP_Copy(
        NODELNKP_DATA       *this
    )
    {
        NODELNKP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeLnkP_New( );
        if (pOther) {
            eRc = nodeLnkP_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        return pOther;
    }
    
    
    ERESULT         nodeLnkP_CopyProperties(
        NODELNKP_DATA   *this,
        NODELNKP_DATA   *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        obj_FlagSet(pOther, NODELINK_RED, obj_Flag(this, NODELINK_RED));
        obj_setMisc1(pOther, obj_getMisc1(this));   // Balance
        pOther->index = this->index;
        pOther->pLeft = this->pLeft;
        obj_FlagSet(pOther, NODELINK_LEFT_LINK, obj_Flag(this, NODELINK_LEFT_LINK));
        pOther->pMiddle = this->pMiddle;
        pOther->pParent = this->pParent;
        pOther->pRight = this->pRight;
        obj_FlagSet(pOther, NODELINK_RIGHT_LINK, obj_Flag(this, NODELINK_RIGHT_LINK));
        obj_FlagSet(pOther, NODELINK_RIGHT_CHILD, obj_Flag(this, NODELINK_RIGHT_CHILD));

        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    

    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeLnkP_Dealloc(
        OBJ_ID          objId
    )
    {
        NODELNKP_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODELNKP_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        nodeLnkP_setLeftLink(this, OBJ_NIL);
        nodeLnkP_setMiddle(this, OBJ_NIL);
        nodeLnkP_setParent(this, OBJ_NIL);
        nodeLnkP_setRight(this, OBJ_NIL);

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

    ERESULT         nodeLnkP_Disable(
        NODELNKP_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeLnkP_Validate(this) ) {
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

    ERESULT         nodeLnkP_Enable(
        NODELNKP_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !nodeLnkP_Validate(this) ) {
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

    NODELNKP_DATA *   nodeLnkP_Init(
        NODELNKP_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODELNKP_DATA);
        
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
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODELNKP);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                      // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODELNKP); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeLnkP_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "nodeLnkP::sizeof(NODELNKP_DATA) = %lu\n", sizeof(NODELNKP_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODELNKP_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         nodeLnkP_IsEnabled(
        NODELNKP_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
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
    //                  I s  L e f t  L i n k
    //---------------------------------------------------------------
    
    bool            nodeLnkP_IsLeftLink(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_LEFT_LINK);
        
        return fRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                  I s  R i g h t  C h i l d
    //---------------------------------------------------------------
    
    bool            nodeLnkP_IsRightChild(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc = false;
        NODELNKP_DATA   *pParent;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pParent = this->pParent;
        if (pParent) {
            if (pParent->pRight == this)
                fRc = true;
        }
        
        return fRc;
    }
    

    
    //---------------------------------------------------------------
    //                  I s  R i g h t  L i n k
    //---------------------------------------------------------------
    
    bool            nodeLnkP_IsRightLink(
        NODELNKP_DATA   *this
    )
    {
        bool            fRc = false;
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fRc = obj_Flag(this, NODELINK_RIGHT_LINK);

        return fRc;
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
        void        *pMethod = nodeLnkP_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "nodeLnkP", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          nodeLnkP_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODELNKP_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NODELNKP_DATA);
                break;
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)nodeLnkP_Class();
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
                            return nodeLnkP_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return nodeLnkP_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return nodeLnkP_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return nodeLnkP_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == nodeLnkP_ToDebugString)
                    return "ToDebugString";
                if (pData == nodeLnkP_ToJSON)
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
    
     ASTR_DATA *     nodeLnkP_ToJSON(
        NODELNKP_DATA      *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
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
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = nodeLnkP_ToDebugString(this,4);
     @endcode 
     @param     this    NODELNKP object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     nodeLnkP_ToDebugString(
        NODELNKP_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeLnkP_Validate(this) ) {
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
                    "{%p(%s) retain=%d\n",
                    this,
                    pInfo->pClassName,
                    obj_getRetainCount(this)
            );
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        AStr_AppendPrint(
                         pStr,
                         "index:\"%4d\", "
                         "%s "
                         "%s "
                         "left%s:\"%p\", "
                         "middle:\"%p\", "
                         "parent:\"%p\", "
                         "right%s:%p "
                         "balance:%4d "
                         "\n",
                         this->index,
                         (nodeLnkP_getRed(this) ? "red," : "black,"),
                         (nodeLnkP_getRightChild(this) ? "RChild," : ""),
                         (nodeLnkP_getLeftLink(this) ? "_Link" : "_Thread"),
                         this->pLeft,
                         this->pMiddle,
                         this->pParent,
                         (nodeLnkP_getRightLink(this) ? "_Link" : "_Thread"),
                         this->pRight,
                         nodeLnkP_getBalance(this)
        );

        if (this->pSuperVtbl) {
            if (this->pSuperVtbl->pToDebugString) {
                pWrkStr =   this->pSuperVtbl->pToDebugString(
                                                             this,
                                                             indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        

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
    bool            nodeLnkP_Validate(
        NODELNKP_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_NODELNKP) )
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


        if( !(obj_getSize(this) >= sizeof(NODELNKP_DATA)) ) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


