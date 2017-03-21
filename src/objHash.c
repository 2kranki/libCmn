// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objHash.c
 *	Generated 10/24/2015 13:59:04
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
#include "objHash_internal.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            objHash_AddBlock(
        OBJHASH_DATA    *cbp
    );
    
    static
    uint16_t        objHash_IndexFromHash(
        OBJHASH_DATA    *cbp,
        uint32_t        hash
    );
    
    static
    LISTDL_DATA *   objHash_NodeListFromHash(
        OBJHASH_DATA    *cbp,
        uint32_t        hash
    );
    
    
    
    /* Expand the current Pointer Array by Inc entries.
     */
    static
    bool            objHash_AddBlock(
        OBJHASH_DATA    *cbp
    )
    {
        OBJHASH_BLOCK   *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&cbp->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(OBJHASH_BLOCK) + (cbp->cBlock * sizeof(OBJHASH_NODE));
        pBlock = (OBJHASH_BLOCK *)mem_Malloc( i );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&cbp->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<cbp->cBlock; ++i) {
            listdl_Add2Tail(&cbp->freeList, &pBlock->node[i]);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    static
    OBJHASH_NODE *  objHash_FindNode(
        OBJHASH_DATA    *cbp,
        uint32_t        hash,
        OBJ_ID          pObject
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        int             iRc;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
        pNodeList = objHash_NodeListFromHash( cbp, hash );
        pVtbl = obj_getVtbl(pObject);
        
        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (pNode->hash == hash) {
                iRc = pVtbl->pCompare(pObject,pNode->pObject);
                if (0 == iRc) {
                    return pNode;
                }
                if (iRc < 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    static
    uint16_t        objHash_IndexFromHash(
        OBJHASH_DATA    *cbp,
        uint32_t        hash
    )
    {
        uint16_t        index;
        
        index = hash % cbp->cHash;
        return index;
    }
    
    
    
    static
    LISTDL_DATA *   objHash_NodeListFromHash(
        OBJHASH_DATA    *cbp,
        uint32_t        hash
    )
    {
        LISTDL_DATA     *pNodeList;
        
        pNodeList = &cbp->pHash[objHash_IndexFromHash(cbp,hash)];
        return( pNodeList );
    }
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJHASH_DATA *     objHash_Alloc(
    )
    {
        OBJHASH_DATA    *cbp;
        uint32_t        cbSize = sizeof(OBJHASH_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    OBJHASH_DATA *     objHash_New(
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        OBJHASH_DATA       *cbp;
        
        cbp = objHash_Alloc( );
        if (cbp) {
            cbp = objHash_Init( cbp, cHash );
        } 
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        objHash_getSize(
        OBJHASH_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !objHash_Validate( this ) ) {
            DEBUG_BREAK();
        }
#endif
        return this->num;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //----------------------------------------------------------
    //                          A d d
    //----------------------------------------------------------
    
    ERESULT         objHash_Add(
        OBJHASH_DATA    *this,
        OBJ_ID			pObject
    )
    {
        LISTDL_DATA     *pNodeList;
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        OBJ_IUNKNOWN    *pVtbl;
        
#ifdef NDEBUG
#else
        if( !objHash_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pObject) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pVtbl = obj_getVtbl(pObject);
        
        hash = pVtbl->pHash(pObject);
        pNode = objHash_Find(this, pObject);
        if (pNode) {
            //fprintf( stderr, "Node Key = %s\n", pNode->pszKey);
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        
        // Determine the entry number.
        if (0 == listdl_Count(&this->freeList)) {
            if ( objHash_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        pNode = listdl_DeleteHead(&this->freeList);
        if (NULL == pNode) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Add it to the table.
        obj_Retain(pObject);
        pNode->pObject = pObject;
        pNode->hash    = hash;
        pNode->unique  = this->unique++;
        
        pNodeList = objHash_NodeListFromHash( this, hash );
        listdl_Add2Tail(pNodeList, pNode);
        
        ++this->num;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objHash_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJHASH_DATA    *cbp = objId;
        OBJHASH_BLOCK   *pBlock;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !objHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        //TODO: Release all active objects.

        while ( listdl_Count(&cbp->blocks) ) {
            pBlock = listdl_DeleteHead(&cbp->blocks);
            mem_Free( pBlock );
        }
        
        if( cbp->pHash ) {
            mem_Free( cbp->pHash );
            cbp->pHash = NULL;
        }
        
        obj_Dealloc( cbp );
        cbp = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    bool            objHash_Disable(
        OBJHASH_DATA		*cbp
    )
    {

        // Do initialization.
        if (NULL == cbp) {
            return false;
        }
    #ifdef NDEBUG
    #else
        if( !objHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif

        // Put code here...

        obj_Disable(cbp);
        
        // Return to caller.
        return true;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    bool            objHash_Enable(
        OBJHASH_DATA		*cbp
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !objHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
    #endif
        
        obj_Enable(cbp);

        // Put code here...
        
        // Return to caller.
        return true;
    }



    //----------------------------------------------------------
    //                        F i n d
    //----------------------------------------------------------
    
    OBJ_ID          objHash_Find(
        OBJHASH_DATA    *cbp,
        OBJ_ID          *pObject
    )
    {
        OBJHASH_NODE    *pNode;
        uint32_t        hash;
        const
        OBJ_IUNKNOWN    *pVtbl;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pVtbl = obj_getVtbl(pObject);
        
        hash = pVtbl->pHash(pObject);
        
        pNode = objHash_FindNode( cbp, hash, pObject );
        if (pNode) {
            return pNode->pObject;
        }
        
        // Return to caller.
        return OBJ_NIL;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJHASH_DATA *   objHash_Init(
        OBJHASH_DATA    *cbp,
        uint16_t        cHash       // [in] Hash Table Size
    )
    {
        uint32_t        cbSize;
        uint32_t        i;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        
        cbSize = obj_getSize(cbp);
        cbp = (OBJHASH_DATA *)obj_Init( cbp, cbSize, OBJ_IDENT_OBJHASH );
        if (OBJ_NIL == cbp) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //obj_setSize(cbp, cbSize);         // Needed for Inheritance
        //obj_setIdent((OBJ_ID)cbp, OBJ_IDENT_OBJHASH);
        obj_setVtbl(cbp, &objHash_Vtbl);
        
        cbp->cHash = cHash;
        cbSize = 4096 - sizeof(OBJHASH_BLOCK);
        cbSize /= sizeof(OBJHASH_NODE);
        cbp->cBlock = cbSize;
        
        // Allocate the Hash Table.
        cbSize = cHash * sizeof(LISTDL_DATA);
        cbp->pHash = (LISTDL_DATA *)mem_Malloc( cbSize );
        if (NULL == cbp->pHash) {
            DEBUG_BREAK();
            mem_Free(cbp);
            cbp = NULL;
            return cbp;
        }
        for (i=0; i<cHash; ++i) {
            listdl_Init(&cbp->pHash[i], offsetof(OBJHASH_NODE, list));
        }
        listdl_Init(&cbp->freeList, offsetof(OBJHASH_NODE, list));
        
    #ifdef NDEBUG
    #else
        if( !objHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            obj_Release(cbp);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&cbp->thread);
    #endif

        return cbp;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            objHash_IsEnabled(
        OBJHASH_DATA		*cbp
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(cbp))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     objHash_ToDebugString(
        OBJHASH_DATA    *cbp,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        
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
                     "{%p(objHash) side=%d ",
                     cbp,
                     objHash_getSize(cbp)
            );
        AStr_AppendA(pStr, str);

#ifdef  XYZZY        
        if (cbp->pData) {
            if (((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(cbp->pData))->pVtbl->toDebugString(
                                                    cbp->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf( str, sizeof(str), " %p}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objHash_Validate(
        OBJHASH_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_OBJHASH) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(OBJHASH_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


