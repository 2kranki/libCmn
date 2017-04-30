// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeEntry.c
 *	Generated 08/29/2016 11:26:27
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
#include "nodeEntry_internal.h"
#include "nodeArray.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/




    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEENTRY_DATA * nodeEntry_Alloc(
    )
    {
        NODEENTRY_DATA  *this;
        uint32_t        cbSize = sizeof(NODEENTRY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEENTRY_DATA * nodeEntry_New(
        NODE_DATA       *pNode
    )
    {
        NODEENTRY_DATA  *this;
        
        this = nodeEntry_Alloc( );
        if (this) {
            this = nodeEntry_Init(this, pNode);
        } 
        return this;
    }



    NODEENTRY_DATA * nodeEntry_NewWithUTF8AndClass(
        const
        char            *pName,
        int32_t         cls,
        OBJ_ID          pData
    )
    {
        NODEENTRY_DATA  *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = nodeEntry_Alloc( );
        if (this) {
            this = nodeEntry_InitWithUTF8(this,pName,pData);
            if (this) {
                node_setClass(nodeEntry_getNode(this), cls);
            }
        }
        
        return this;
    }
    
    
    
    NODEENTRY_DATA * nodeEntry_NewWithUTF8Con(
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        NODEENTRY_DATA  *this;
        
        if (OBJ_NIL == pName) {
            return OBJ_NIL;
        }
        
        this = nodeEntry_Alloc( );
        if (this) {
            this = nodeEntry_InitWithUTF8Con(this,pName,pData);
        }
        
        return this;
    }
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        nodeEntry_getChild(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->rightIndex;
    }
    
    
    bool            nodeEntry_setChild(
        NODEENTRY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
        return true;
    }
    
    
    
    uint32_t        nodeEntry_getIndex(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->index;
    }
    
    
    bool            nodeEntry_setIndex(
        NODEENTRY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->index = value;
        
        return true;
    }
    
    
    
    uint32_t        nodeEntry_getLeft(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->leftIndex;
    }
    
    
    bool            nodeEntry_setLeft(
        NODEENTRY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    
    uint32_t        nodeEntry_getMiddle(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->middleIndex;
    }
    
    
    bool            nodeEntry_setMiddle(
        NODEENTRY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->middleIndex = value;
        
        return true;
    }
    
    
    
    uint16_t        nodeEntry_getMisc(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return node_getMisc((NODE_DATA *)this);
    }
    
    
    
    NODE_DATA *     nodeEntry_getNode(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pNode;
    }
    
    
    bool            nodeEntry_setNode(
        NODEENTRY_DATA  *this,
        NODE_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
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
    
    
    
    uint32_t        nodeEntry_getParent(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->parentIndex;
    }
    
    
    bool            nodeEntry_setParent(
        NODEENTRY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->parentIndex = value;
        
        return true;
    }
    
    
    
    NODEARRAY_DATA * nodeEntry_getProperties(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return node_getProperties((NODE_DATA *)this);
    }
    
    
    
    uint16_t        nodeEntry_getPriority(
        NODEENTRY_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            nodeEntry_setPriority(
        NODEENTRY_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    uint32_t        nodeEntry_getRight(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->rightIndex;
    }
    
    
    bool            nodeEntry_setRight(
        NODEENTRY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->rightIndex = value;
        
        return true;
    }
    
    
    
    uint32_t        nodeEntry_getSibling(
        NODEENTRY_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        
        return this->leftIndex;
    }
    
    
    bool            nodeEntry_setSibling(
        NODEENTRY_DATA  *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->leftIndex = value;
        
        return true;
    }
    
    
    

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    ERESULT         nodeEntry_Assign(
        NODEENTRY_DATA		*this,
        NODEENTRY_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !nodeEntry_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

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
        pOther->index = this->index;
        pOther->leftIndex = this->leftIndex;
        pOther->parentIndex = this->parentIndex;
        pOther->rightIndex = this->rightIndex;
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    NODEENTRY_DATA * nodeEntry_Copy(
        NODEENTRY_DATA  *this
    )
    {
        NODEENTRY_DATA  *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = nodeEntry_New(OBJ_NIL);
        if (pOther) {
            eRc = nodeEntry_Assign(this, pOther);
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

    void            nodeEntry_Dealloc(
        OBJ_ID          objId
    )
    {
        NODEENTRY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        nodeEntry_setNode(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEENTRY_DATA * nodeEntry_Init(
        NODEENTRY_DATA  *this,
        NODE_DATA       *pNode
    )
    {
        uint32_t        cbSize = sizeof(NODEENTRY_DATA);
        
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

        this = obj_Init( this, cbSize, OBJ_IDENT_NODEENTRY );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODEENTRY); // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);           // Needed for Inheritance
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeEntry_Vtbl);
        
        nodeEntry_setNode(this, pNode);
        
    #ifdef NDEBUG
    #else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->rightIndex);
    #endif

        return this;
    }

     
    NODEENTRY_DATA * nodeEntry_InitWithUTF8(
        NODEENTRY_DATA  *this,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *pNode;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pNode = node_NewWithUTF8(pName, pData);
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = nodeEntry_Init( this, pNode );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_Release(pNode);
        
        return this;
    }
    
    
    NODEENTRY_DATA * nodeEntry_InitWithUTF8Con(
        NODEENTRY_DATA  *this,
        const
        char            *pName,
        OBJ_ID          pData
    )
    {
        NODE_DATA       *pNode;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pNode = node_NewWithUTF8Con(pName, pData);
        if (OBJ_NIL == pNode) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = nodeEntry_Init(this, pNode);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_Release(pNode);
        
        return this;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeEntry_ToDebugString(
        NODEENTRY_DATA  *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(nodeEntry) index=%3d left=%3d middle=%3d right=%3d parent=%3d\n",
                     this,
                     nodeEntry_getIndex(this),
                     nodeEntry_getLeft(this),
                     nodeEntry_getMiddle(this),
                     nodeEntry_getRight(this),
                     nodeEntry_getParent(this)
            );
        AStr_AppendA(pStr, str);

        if (this->pNode && ((OBJ_DATA *)(this->pNode))->pVtbl->pToDebugString) {
            pWrkStr =   ((OBJ_DATA *)(this->pNode))->pVtbl->pToDebugString(
                                                this->pNode,
                                                indent+3
                        );
            AStr_Append(pStr, pWrkStr);
            obj_Release(pWrkStr);
        }
        
        if (indent) {
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(nodeEntry)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeEntry_Validate(
        NODEENTRY_DATA      *this
    )
    {
        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_NODEENTRY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(NODEENTRY_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                    V i s i t e d  F l a g
    //---------------------------------------------------------------
    
    bool        nodeEntry_Visited(
        NODEENTRY_DATA	*this
    )
    {
        bool            fValue;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        fValue = obj_IsFlag(this, NODEENTRY_FLAG_VISITED);
        
        // Return to caller.
        return fValue;
    }
    
    
    bool        nodeEntry_VisitedSet(
        NODEENTRY_DATA	*this,
        bool            fValue
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeEntry_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_FlagSet(this, NODEENTRY_FLAG_VISITED, fValue);
        
        // Return to caller.
        return true;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


