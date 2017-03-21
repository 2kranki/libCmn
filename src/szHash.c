// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   szHash.c
 *	Generated 06/11/2015 16:44:27
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
#include    "szHash_internal.h"
#include    <stdio.h>
#include    "str.h"
#include    "utf8.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            szHash_AddBlock(
        SZHASH_DATA     *cbp
    );
    
    static
    uint16_t        szHash_IndexFromHash(
        SZHASH_DATA     *cbp,
        uint32_t        hash
    );
    
    static
    LISTDL_DATA *   szHash_NodeListFromHash(
        SZHASH_DATA     *cbp,
        uint32_t        hash
    );
    

    
    /* Expand the current Pointer Array by Inc entries.
     */
    static
    bool            szHash_AddBlock(
        SZHASH_DATA     *cbp
    )
    {
        SZHASH_BLOCK    *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&cbp->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(SZHASH_BLOCK) + (cbp->cBlock * sizeof(SZHASH_NODE));
        pBlock = (SZHASH_BLOCK *)mem_Malloc( i );
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
    SZHASH_NODE *   szHash_FindNode(
        SZHASH_DATA     *this,
        uint32_t        hash,
        const
        char            *pszKey
    )
    {
        LISTDL_DATA     *pNodeList;
        SZHASH_NODE     *pNode;
        int             iRc;
        
        // Do initialization.
        pNodeList = szHash_NodeListFromHash( this, hash );
        
        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (pNode->hash == hash) {
                iRc = (*this->pCompare)(pNode->pszKey, pszKey);
                if (0 == iRc) {
                    return pNode;
                }
                if (iRc > 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    static
    SZHASH_NODE *   szHash_FindNodeW(
        SZHASH_DATA     *this,
        uint32_t        hash,
        const
        int32_t         *pszKey
    )
    {
        LISTDL_DATA     *pNodeList;
        SZHASH_NODE     *pNode;
        int             iRc;
        
        // Do initialization.
        pNodeList = szHash_NodeListFromHash( this, hash );
        
        pNode = listdl_Head(pNodeList);
        while ( pNode ) {
            if (pNode->hash == hash) {
                iRc = (*this->pCompareAW)(pNode->pszKey, pszKey);
                if (0 == iRc) {
                    return pNode;
                }
                if (iRc > 0) {
                    break;
                }
            }
            pNode = listdl_Next(pNodeList, pNode);
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    static
    uint16_t        szHash_IndexFromHash(
        SZHASH_DATA     *cbp,
        uint32_t        hash
    )
    {
        uint16_t        index;
        
        index = hash % cbp->cHash;
        return index;
    }
    
    
    
    static
    LISTDL_DATA *   szHash_NodeListFromHash(
        SZHASH_DATA     *cbp,
        uint32_t        hash
    )
    {
        LISTDL_DATA     *pNodeList;
        
        pNodeList = &cbp->pHash[szHash_IndexFromHash(cbp,hash)];
        return( pNodeList );
    }
    
    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SZHASH_DATA *     szHash_Alloc(
    )
    {
        SZHASH_DATA       *cbp;
        uint32_t        cbSize = sizeof(SZHASH_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }




    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool			szHash_setCompare(
        SZHASH_DATA     *this,
        int             (*pCompare)(const char *pKey1, const char *pKey2),
        int             (*pCompareAW)(const char *pKey1, const int32_t *pKey2)
    )
    {
        
#ifdef NDEBUG
#else
        if( !szHash_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pCompare) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pCompare = pCompare;
        this->pCompareAW = pCompareAW;
        
        return true;
    }
    
    
    
    bool			szHash_setComputeHash(
        SZHASH_DATA     *this,
        uint32_t        (*pComputeHash)(const char *pszKey1, size_t *pLen),
        uint32_t        (*pComputeHashW)(const int32_t *pszKey1, size_t *pLen)
    )
    {
        
#ifdef NDEBUG
#else
        if( !szHash_Validate( this ) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pComputeHash) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pComputeHash = pComputeHash;
        this->pComputeHashW = pComputeHashW;
        
        return true;
    }
    
    
    
    uint32_t        szHash_getSize(
        SZHASH_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        return cbp->num;
    }


    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //----------------------------------------------------------
    //                          A d d
    //----------------------------------------------------------
    
    ERESULT         szHash_Add(
        SZHASH_DATA     *cbp,
        const
        char            *pszKey,
        void			*pData
    )
    {
        LISTDL_DATA     *pNodeList;
        SZHASH_NODE     *pNode;
        uint32_t        hash;
        
#ifdef NDEBUG
#else
        if( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == cbp->pCompare) {
            return ERESULT_INVALID_FUNCTION;
        }
        if (NULL == cbp->pComputeHash) {
            return ERESULT_INVALID_FUNCTION;
        }
#endif
        
        hash = (*cbp->pComputeHash)(pszKey,NULL);
        pNode = szHash_FindNode(cbp, hash, pszKey);
        if (pNode) {
            fprintf( stderr, "Node Key = %s\n", pNode->pszKey);
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        
        // Determine the entry number.
        if (0 == listdl_Count(&cbp->freeList)) {
            if ( szHash_AddBlock(cbp) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        pNode = listdl_DeleteHead(&cbp->freeList);
        if (NULL == pNode) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        
        // Add it to the table.
        pNode->pszKey = pszKey;
        pNode->pData  = pData;
        pNode->hash   = hash;
        
        pNodeList = szHash_NodeListFromHash( cbp, hash );
        listdl_Add2Tail(pNodeList, pNode);

        ++cbp->num;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            szHash_Dealloc(
        OBJ_ID          objId
    )
    {
        SZHASH_DATA     *cbp = objId;
        SZHASH_BLOCK    *pBlock;

        // Do initialization.
        if (NULL == cbp) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

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



    //----------------------------------------------------------
    //					  D e l e t e
    //----------------------------------------------------------
    
    ERESULT         szHash_Delete(
        SZHASH_DATA     *cbp,
        const
        char            *pszKey
    )
    {
        LISTDL_DATA     *pNodeList;
        SZHASH_NODE     *pNode;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pszKey ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        hash = (*cbp->pComputeHash)(pszKey,NULL);
        pNode = szHash_FindNode(cbp, hash, pszKey);
        if (NULL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }

        pNodeList = szHash_NodeListFromHash( cbp, hash );
        listdl_Delete(pNodeList, pNode);
        listdl_Add2Tail(&cbp->freeList, pNode);
        --cbp->num;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //----------------------------------------------------------
    //                        F i n d
    //----------------------------------------------------------
    
    void *          szHash_Find(
        SZHASH_DATA     *cbp,
        const
        char            *pszKey
    )
    {
        SZHASH_NODE     *pNode;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        hash = (*cbp->pComputeHash)(pszKey,NULL);
        
        pNode = szHash_FindNode( cbp, hash, pszKey );
        if (pNode) {
            return pNode->pData;
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    void *          szHash_FindW(
        SZHASH_DATA     *cbp,
        const
        int32_t         *pszKey
    )
    {
        SZHASH_NODE     *pNode;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        hash = (*cbp->pComputeHashW)(pszKey,NULL);
        
        pNode = szHash_FindNodeW( cbp, hash, pszKey );
        if (pNode) {
            return pNode->pData;
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SZHASH_DATA *       szHash_Init(
        SZHASH_DATA         *cbp,
        uint16_t            cHash
    )
    {
        uint32_t            cbSize;
        uint32_t            i;
        
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        if ( cHash == 0 )
            return( OBJ_NIL );
        
        cbp = obj_Init( cbp, obj_getSize(cbp), OBJ_IDENT_SZHASH );
        if (OBJ_NIL == cbp) {
            return OBJ_NIL;
        }
        obj_setVtbl(cbp, &szHash_Vtbl);
        
        cbp->cHash = cHash;
        cbSize = 4096 - sizeof(SZHASH_BLOCK);
        cbSize /= sizeof(SZHASH_NODE);
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
            listdl_Init(&cbp->pHash[i], offsetof(SZHASH_NODE, list));
        }
        listdl_Init(&cbp->freeList, offsetof(SZHASH_NODE, list));
        
        // Set Default Comparison Routines.
        szHash_setComputeHash( cbp, str_HashA, str_HashW );
        szHash_setCompare( cbp, utf8_StrCmp, utf8_StrCmpAW );
        
    #ifdef NDEBUG
    #else
        if ( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&cbp->pHash);
    #endif

        return cbp;
    }

     

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     szHash_ToDebugString(
        SZHASH_DATA      *cbp,
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
                     "{%p(szHash) ",
                     cbp
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
        
        j = snprintf( str, sizeof(str), " %p(szHash)}\n", cbp );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //----------------------------------------------------------
    //					  U p d a t e
    //----------------------------------------------------------
    
    ERESULT         szHash_Update(
        SZHASH_DATA     *cbp,
        const
        char            *pszKey,
        void            *pData
    )
    {
        SZHASH_NODE     *pNode;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szHash_Validate( cbp ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        hash = (*cbp->pComputeHash)(pszKey,NULL);    
        pNode = szHash_FindNode( cbp, hash, pszKey );
        if (pNode) {
            pNode->pData = pData;
        }
        else
            return ERESULT_DATA_NOT_FOUND;
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            szHash_Validate(
        SZHASH_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_SZHASH) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(SZHASH_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


