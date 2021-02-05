// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeLink.c
 *  Generated 02/03/2021 18:58:16
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
#include        <NodeLink_internal.h>
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
    void            NodeLink_task_body (
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

    NODELINK_DATA *     NodeLink_Alloc (
        void
    )
    {
        NODELINK_DATA       *this;
        uint32_t        cbSize = sizeof(NODELINK_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODELINK_DATA *     NodeLink_New (
        void
    )
    {
        NODELINK_DATA       *this;
        
        this = NodeLink_Alloc( );
        if (this) {
            this = NodeLink_Init(this);
        } 
        return this;
    }



    NODELINK_DATA *     NodeLink_NewWithNode (
        NODE_DATA           *pNode
    )
    {
        NODELINK_DATA       *this;

        this = NodeLink_New( );
        if (this) {
            NodeLink_setNode(this, pNode);
        }
        return this;
    }



    NODELINK_DATA * NodeLink_NewWithUTF8AndClass(
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        NODELINK_DATA   *this;

        this = NodeLink_Alloc( );
        if (this) {
            this = NodeLink_Init(this);
            if (this) {
                this->pNode = Node_NewWithUTF8AndClass(cls, pNameA, pData);
                if (OBJ_NIL == this->pNode) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }


    NODELINK_DATA * NodeLink_NewWithUTF8ConAndClass (
        int32_t         cls,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        NODELINK_DATA   *this;

        this = NodeLink_Alloc( );
        if (this) {
            this = NodeLink_Init(this);
            if (this) {
                this->pNode = Node_NewWithUTF8ConAndClass(cls, pNameA, pData);
                if (OBJ_NIL == this->pNode) {
                    obj_Release(this);
                    this = OBJ_NIL;
                }
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

    int16_t         NodeLink_getBalance(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return (int16_t)obj_getMisc1(this);
    }


    bool            NodeLink_setBalance(
        NODELINK_DATA   *this,
        int16_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_setMisc1(this, value);

        return true;
    }



    //---------------------------------------------------------------
    //                      C h i l d  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getChild(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->leftIndex;
    }


    bool            NodeLink_setChild(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
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

    int32_t         NodeLink_getClass(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Node_getClass(this->pNode);
    }



    //---------------------------------------------------------------
    //                          D a t a
    //---------------------------------------------------------------

    OBJ_ID          NodeLink_getData(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Node_getData(this->pNode);
    }


    bool            NodeLink_setData(
        NODELINK_DATA   *this,
        OBJ_ID          pValue
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Node_setData(this->pNode, pValue);
    }



    //---------------------------------------------------------------
    //                          E x t r a
    //---------------------------------------------------------------

    OBJ_ID          NodeLink_getExtra(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return Node_getExtra(this->pNode);
    }


    bool            NodeLink_setExtra(
        NODELINK_DATA   *this,
        OBJ_ID          pValue
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Node_setExtra(this->pNode, pValue);
    }



    //---------------------------------------------------------------
    //                      F r o m  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getFrom(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->leftIndex;
    }


    bool            NodeLink_setFrom(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->leftIndex = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          H a s h
    //---------------------------------------------------------------

    uint32_t        NodeLink_getHash(
        NODELINK_DATA   *this
    )
    {
        uint32_t        hash = 0;
        NAME_DATA       *pName = OBJ_NIL;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return hash;
        }
#endif
        pName = Node_getName(this->pNode);

        if (pName) {
            hash = Name_getHash(pName);
        }

        return hash;
    }



    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getIndex(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->index;
    }


    bool            NodeLink_setIndex(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
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

    uint32_t        NodeLink_getLeft(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->leftIndex;
    }


    bool            NodeLink_setLeft(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->leftIndex = value;

        return true;
    }


    uint32_t        NodeLink_getLeftLink(
        NODELINK_DATA   *this
    )
    {
        bool            fRc;
        uint32_t        nodeIndex = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        fRc = obj_Flag(this, NODELINK_LEFT_LINK);
        if (fRc)
            nodeIndex = this->leftIndex;

        return nodeIndex;
    }


    bool            NodeLink_setLeftLink(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->leftIndex = value;
        obj_FlagSet(this, NODELINK_LEFT_LINK, (value ? true : false));

        return true;
    }


    uint32_t        NodeLink_getLeftThread(
        NODELINK_DATA   *this
    )
    {
        bool            fRc;
        uint32_t        nodeIndex = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        fRc = obj_Flag(this, NODELINK_LEFT_LINK);
        if (!fRc)
            nodeIndex = this->leftIndex;

        return nodeIndex;
    }


    bool            NodeLink_setLeftThread(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->leftIndex = value;
        obj_FlagSet(this, NODELINK_LEFT_LINK, false);

        return true;
    }



    //---------------------------------------------------------------
    //                   M i d d l e  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getMiddle(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->middleIndex;
    }


    bool            NodeLink_setMiddle(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->middleIndex = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          M i s c
    //---------------------------------------------------------------

    uint32_t        NodeLink_getMisc (
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return obj_getMisc(this);
    }


    bool            NodeLink_setMisc(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_setMisc(this, value);

        return true;
    }


    uint16_t        NodeLink_getMisc1(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return obj_getMisc1(this);
    }


    bool            NodeLink_setMisc1(
        NODELINK_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_setMisc1(this, value);

        return true;
    }


    uint16_t        NodeLink_getMisc2(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return obj_getMisc2(this);
    }


    bool            NodeLink_setMisc2 (
        NODELINK_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_setMisc2(this, value);

        return true;
    }



    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------

    NAME_DATA *     NodeLink_getName(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return Node_getName(this->pNode);
    }


    char *          NodeLink_getNameUTF8(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return Node_getNameUTF8(this->pNode);
    }



    //---------------------------------------------------------------
    //                        N o d e
    //---------------------------------------------------------------

    NODE_DATA *     NodeLink_getNode (
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pNode;
    }


    bool            NodeLink_setNode (
        NODELINK_DATA   *this,
        NODE_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pNode) {
            obj_Release(this->pNode);
        }
        this->pNode = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          O t h e r
    //---------------------------------------------------------------

    OBJ_ID          NodeLink_getOther(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return Node_getOther(this->pNode);
    }


    bool            NodeLink_setOther(
        NODELINK_DATA   *this,
        OBJ_ID          pValue
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Node_setOther(this->pNode, pValue);
    }



    //---------------------------------------------------------------
    //                   P a r e n t  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getParent(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->parentIndex;
    }


    bool            NodeLink_setParent(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
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

    uint16_t        NodeLink_getPriority (
        NODELINK_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeLink_setPriority (
        NODELINK_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                    P r o p e r t i e s
    //---------------------------------------------------------------

    NODEBT_DATA *   NodeLink_getProperties (
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return Node_getProperties(this->pNode);
    }



    //---------------------------------------------------------------
    //                      R i g h t  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getRight(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->rightIndex;
    }


    bool            NodeLink_setRight(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->rightIndex = value;

        return true;
    }


    bool            NodeLink_getRightChild(
        NODELINK_DATA   *this
    )
    {
        bool            fRc;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        fRc = obj_Flag(this, NODELINK_RIGHT_CHILD);

        return fRc;
    }


    bool            NodeLink_setRightChild(
        NODELINK_DATA   *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_FlagSet(this, NODELINK_RIGHT_CHILD, fValue);

        return true;
    }



    uint32_t        NodeLink_getRightLink(
        NODELINK_DATA   *this
    )
    {
        bool            fRc;
        uint32_t        nodeIndex = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        fRc = obj_Flag(this, NODELINK_RIGHT_LINK);
        if (fRc)
            nodeIndex = this->rightIndex;

        return nodeIndex;
    }


    bool            NodeLink_setRightLink(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->rightIndex = value;
        obj_FlagSet(this, NODELINK_RIGHT_LINK, (value ? true : false));

        return true;
    }



    uint32_t        NodeLink_getRightThread(
        NODELINK_DATA   *this
    )
    {
        bool            fRc;
        uint32_t        nodeIndex = 0;

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        fRc = obj_Flag(this, NODELINK_RIGHT_LINK);
        if (!fRc)
            nodeIndex = this->rightIndex;

        return nodeIndex;
    }


    bool            NodeLink_setRightThread(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->rightIndex = value;
        obj_FlagSet(this, NODELINK_RIGHT_LINK, false);

        return true;
    }



    //---------------------------------------------------------------
    //                    S i b l i n g  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getSibling(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->rightIndex;
    }


    bool            NodeLink_setSibling(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->rightIndex = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        NodeLink_getSize (
        NODELINK_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeLink_getSuperVtbl (
        NODELINK_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                    T o  I n d e x
    //---------------------------------------------------------------

    uint32_t        NodeLink_getTo(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->rightIndex;
    }


    bool            NodeLink_setTo(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->rightIndex = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    int32_t         NodeLink_getType(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Node_getType(this->pNode);
    }


    bool            NodeLink_setType(
        NODELINK_DATA   *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return Node_setType(this->pNode, value);
    }



    //---------------------------------------------------------------
    //                          U n i q u e
    //---------------------------------------------------------------

    uint32_t        NodeLink_getUnique(
        NODELINK_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return Node_getUnique(this->pNode);
    }


    bool            NodeLink_setUnique(
        NODELINK_DATA   *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        return Node_setUnique(this->pNode, value);
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
        ERESULT eRc = NodeLink_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODELINK object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeLink_Assign (
        NODELINK_DATA       *this,
        NODELINK_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeLink_Validate(pOther)) {
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
        if (pOther->pNode) {
            obj_Release(pOther->pNode);
            pOther->pNode = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pNode) {
            if (obj_getVtbl(this->pNode)->pCopy) {
                pOther->pNode = obj_getVtbl(this->pNode)->pCopy(this->pNode);
            }
            else {
                obj_Retain(this->pNode);
                pOther->pNode = this->pNode;
            }
        }

        // Copy other data from this object to other.
        if (obj_Flag(this, NODELINK_LEFT_LINK)) {
            obj_FlagOn(pOther, NODELINK_LEFT_LINK);
        } else {
            obj_FlagOn(pOther, NODELINK_LEFT_LINK);
        }
        if (obj_Flag(this, NODELINK_RIGHT_LINK)) {
            obj_FlagOn(pOther, NODELINK_RIGHT_LINK);
        } else {
            obj_FlagOn(pOther, NODELINK_RIGHT_LINK);
        }
        if (obj_Flag(this, NODELINK_RIGHT_CHILD)) {
            obj_FlagOn(pOther, NODELINK_RIGHT_CHILD);
        } else {
            obj_FlagOn(pOther, NODELINK_RIGHT_CHILD);
        }
        pOther->index       = this->index;
        pOther->leftIndex   = this->leftIndex;
        pOther->middleIndex = this->middleIndex;
        pOther->parentIndex = this->parentIndex;
        pOther->rightIndex  = this->rightIndex;

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
    int             NodeLink_Compare (
        NODELINK_DATA     *this,
        NODELINK_DATA     *pOther
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
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!NodeLink_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc = Node_Compare(this->pNode, pOther->pNode);
     
        return iRc;
    }
    
   
    int             NodeLink_CompareA(
         NODELINK_DATA   *this,
         int32_t         cls,
         const
         char            *pNameA
     )
     {
         int             iRc = 0;

         // Validate the input parameters.
 #ifdef NDEBUG
 #else
         if( !NodeLink_Validate(this) ) {
             DEBUG_BREAK();
             return ERESULT_INVALID_OBJECT;
         }
 #endif

         iRc = Node_CompareA(this->pNode, cls, pNameA);

         return iRc;
     }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeLink      *pCopy = NodeLink_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODELINK object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODELINK_DATA *     NodeLink_Copy (
        NODELINK_DATA       *this
    )
    {
        NODELINK_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NODELINK_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NodeLink_New( );
        if (pOther) {
            eRc = NodeLink_Assign(this, pOther);
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

    void            NodeLink_Dealloc (
        OBJ_ID          objId
    )
    {
        NODELINK_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODELINK_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeLink_setNode(this, OBJ_NIL);

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
        NodeLink      *pDeepCopy = NodeLink_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODELINK object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODELINK_DATA *     NodeLink_DeepyCopy (
        NODELINK_DATA       *this
    )
    {
        NODELINK_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeLink_New( );
        if (pOther) {
            eRc = NodeLink_Assign(this, pOther);
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
    ERESULT         NodeLink_Disable (
        NODELINK_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
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
    ERESULT         NodeLink_Enable (
        NODELINK_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
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
    //                          H a s h
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    uint32_t            NodeLink_Hash (
        NODELINK_DATA       *this
    )
    {
        //ERESULT           eRc;
        uint32_t            hash = 0;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
    #endif

        hash = Node_getHash(NodeLink_getNode(this));

        // Return to caller.
        return hash;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODELINK_DATA *   NodeLink_Init (
        NODELINK_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODELINK_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODELINK);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeLink_Vtbl);
#ifdef  NODELINK_JSON_SUPPORT
        JsonIn_RegisterClass(NodeLink_Class());
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
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NodeLink::sizeof(NODELINK_DATA) = %lu\n", 
                sizeof(NODELINK_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODELINK_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeLink_IsEnabled (
        NODELINK_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
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
    //                     P r o p e r t y  A d d
    //---------------------------------------------------------------

    ERESULT         NodeLink_PropertyAddA(
        NODELINK_DATA   *this,
        const
        char            *pNameA,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        //NODE_DATA       *pNode = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        eRc = Node_PropertyAddA(this->pNode, pNameA, pData);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //              P r o p e r t y  C o u n t
    //---------------------------------------------------------------

    uint32_t        NodeLink_PropertyCount(
        NODELINK_DATA   *this
    )
    {
        uint32_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        num = Node_PropertyCount(this->pNode);

        // Return to caller.
        return num;
    }



    //---------------------------------------------------------------
    //                    P r o p e r t y  K e y s
    //---------------------------------------------------------------

    NODEARRAY_DATA * NodeLink_Properties(
        NODELINK_DATA   *this
    )
    {
        NODEARRAY_DATA  *pArray = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !NodeLink_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pArray = Node_Properties(this->pNode);

        // Return to caller.
        return pArray;
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
        void        *pMethod = NodeLink_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeLink", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeLink_QueryInfo (
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
        if (!NodeLink_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NODELINK_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeLink_Class();
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
                            return NodeLink_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeLink_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NODELINK_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return NodeLink_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return NodeLink_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeLink_ToDebugString;
                        }
#ifdef  NODELINK_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return NodeLink_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NodeLink_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeLink_ToDebugString)
                    return "ToDebugString";
#ifdef  NODELINK_JSON_SUPPORT
                if (pData == NodeLink_ToJson)
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
        ASTR_DATA      *pDesc = NodeLink_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeLink_ToDebugString (
        NODELINK_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeLink_Validate(this)) {
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
                    NodeLink_getSize(this),
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendPrint(
                         pStr,
                         "\"index\":\"%4d\", "
                         "%s "
                         "\"leftIndex\":\"%4d\", "
                         "%s "
                         "\"middleIndex\":\"%4d\", "
                         "\"parentIndex\":\"%4d\", "
                         "\"rightIndex\":%4d "
                         "%s "
                         "\"balance\":%4d "
                         "\n",
                         this->index,
                         (NodeLink_getRightChild(this) ? "Right_Child" : ""),
                         this->leftIndex,
                         (NodeLink_getLeftLink(this) ? "Left_Link" : ""),
                         this->middleIndex,
                         this->parentIndex,
                         this->rightIndex,
                         (NodeLink_getRightLink(this) ? "Right_Link" : ""),
                         NodeLink_getBalance(this)
        );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        AStr_AppendA(pStr, "Node");
        if (this->pNode) {
            if (((OBJ_DATA *)(this->pNode))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pNode))->pVtbl->pToDebugString(
                                                    this->pNode,
                                                    indent+4
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
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
    bool            NodeLink_Validate (
        NODELINK_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODELINK))
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


        if (!(obj_getSize(this) >= sizeof(NODELINK_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


