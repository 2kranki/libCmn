// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   nodeScan.c
 *	Generated 10/16/2015 09:19:12
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
#include "nodeScan_internal.h"
#include "nodeTree.h"
#include <stdio.h>



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

    NODESCAN_DATA *     nodeScan_Alloc(
    )
    {
        NODESCAN_DATA       *cbp;
        uint32_t        cbSize = sizeof(NODESCAN_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    NODESCAN_DATA *     nodeScan_NewFromArray(
        NODEARRAY_DATA  *pArray     // Tree converted to array with up/down members.
    )
    {
        NODESCAN_DATA       *this;
        
        this = nodeScan_Alloc( );
        if (this) {
            this = nodeScan_InitArray(this, pArray);
        } 
        return this;
    }



    NODESCAN_DATA *     nodeScan_NewFromTree(
        NODETREE_DATA       *pTree
    )
    {
        NODESCAN_DATA       *this;
        NODEARRAY_DATA      *pArray;
        
        pArray = nodeTree_ToLinearizationPre(pTree);
        if (pArray) {
        }
        else {
            return OBJ_NIL;
        }
        
        this = nodeScan_Alloc( );
        if (this) {
            this = nodeScan_InitArray(this, pArray);
        }
        
        return this;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    NODEARRAY_DATA * nodeScan_getArray(
        NODESCAN_DATA    *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return cbp->pArray;
    }
    
    
    bool            nodeScan_setArray(
        NODESCAN_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        nodeScan_setIndex(this, 0);
        
        return true;
    }
    
    
    
    uint32_t        nodeScan_getIndex(
        NODESCAN_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        return cbp->index;
    }

    bool            nodeScan_setIndex(
        NODESCAN_DATA   *cbp,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        cbp->index = value;
        
        return true;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            nodeScan_Dealloc(
        OBJ_ID          objId
    )
    {
        NODESCAN_DATA   *cbp = objId;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        nodeScan_setArray(cbp, OBJ_NIL);

        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODESCAN_DATA * nodeScan_Init(
        NODESCAN_DATA   *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(this);
        this = (NODESCAN_DATA *)obj_Init( this, cbSize, OBJ_IDENT_NODESCAN );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_NODESCAN);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&nodeScan_Vtbl);
        
        //this->stackSize = obj_getMisc1(this);
        //this->pArray = objArray_New( );

    #ifdef NDEBUG
    #else
        if( !nodeScan_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     
    NODESCAN_DATA *   nodeScan_InitArray(
        NODESCAN_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
        
        this = nodeScan_Init(this);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        if (pValue) {
            nodeScan_setArray(this, pValue);
            nodeScan_setIndex(this, 0);
        }
        
        return this;
    }
    
    

    //--------------------------------------------------------------
    //                  I n p u t  A d v a n c e
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_InputAdvance(
        NODESCAN_DATA	*cbp,
        uint16_t        numChrs
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        // Shift inputs.
        ++cbp->index;
        if (cbp->index >= nodeArray_getSize(cbp->pArray)) {
            cbp->index = 0;
        }
        pNode = nodeArray_Get(cbp->pArray, cbp->index+1);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    //--------------------------------------------------------------
    //               I n p u t  L o o k  A h e a d
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_InputLookAhead(
        NODESCAN_DATA   *cbp,
        uint16_t        num
    )
    {
        uint16_t        idx;
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        idx = (cbp->index + num - 1) % nodeArray_getSize(cbp->pArray);
        pNode = nodeArray_Get(cbp->pArray, idx+1);
        
        // Return to caller.
        return pNode;
    }
    
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  N a m e
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_MatchName(
        NODESCAN_DATA	*cbp,
        char            *pStr
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pName;
        int             cmp;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pNode = nodeArray_Get(cbp->pArray, cbp->index+1);
        if (pNode) {
            pName = node_getNameUTF8(pNode);
            cmp = strcmp(pName, pStr);
            mem_Free((void *)pName);
            if( 0 == cmp ) {
                (void)nodeScan_InputAdvance(cbp,1);
                return pNode;
            }
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //--------------------------------------------------------------
    //                 M a t c h  I n p u t  C l a s s
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_MatchClass(
        NODESCAN_DATA	*cbp,
        int32_t         cls
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pNode = nodeArray_Get(cbp->pArray, cbp->index+1);
        if( pNode && (cls == node_getClass(pNode)) ) {
            (void)nodeScan_InputAdvance(cbp,1);
            return pNode;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    

    //--------------------------------------------------------------
    //              M a t c h  I n p u t  C l a s s e s
    //--------------------------------------------------------------
    
    NODE_DATA *     nodeScan_MatchClasses(
        NODESCAN_DATA   *cbp,
        int32_t         *pSet
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !nodeScan_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pSet) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        while (*pSet) {
            pNode = nodeScan_MatchClass(cbp,*pSet);
            if(pNode) {
                return pNode;
            }
            ++pSet;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     nodeScan_ToDebugString(
        NODESCAN_DATA   *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        
        if (OBJ_NIL == cbp) {
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
                     "{%p(nodeScan) index=%d ",
                     cbp,
                     nodeScan_getIndex(cbp)
            );
        AStr_AppendA(pStr, str);

        if (cbp->pArray) {
            if (((OBJ_DATA *)(cbp->pArray))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pArray))->pVtbl->pToDebugString(
                                                    cbp->pArray,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            nodeScan_Validate(
        NODESCAN_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_NODESCAN) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(NODESCAN_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


