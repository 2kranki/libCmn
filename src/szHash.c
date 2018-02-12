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
#include    <szHash_internal.h>
#include    <enum_internal.h>
#include    <ascii.h>
#include    <stdio.h>
#include    <str.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            szHash_AddBlock(
        SZHASH_DATA     *this
    );
    
    static
    uint16_t        szHash_IndexFromHash(
        SZHASH_DATA     *this,
        uint32_t        hash
    );
    
    static
    LISTDL_DATA *   szHash_NodeListFromHash(
        SZHASH_DATA     *this,
        uint32_t        hash
    );
    

    
    /* Expand the current Pointer Array by Inc entries.
     */
    static
    bool            szHash_AddBlock(
        SZHASH_DATA     *this
    )
    {
        SZHASH_BLOCK    *pBlock;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&this->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(SZHASH_BLOCK) + (this->cBlock * sizeof(SZHASH_NODE));
        pBlock = (SZHASH_BLOCK *)mem_Malloc( i );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&this->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<this->cBlock; ++i) {
            listdl_Add2Tail(&this->freeList, &pBlock->node[i]);
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
        pNodeList = szHash_NodeListFromHash(this, hash);
        
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
    SZHASH_NODE *   szHash_FindNodeW32(
        SZHASH_DATA     *this,
        uint32_t        hash,
        const
        W32CHR_T        *pszKey
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
                iRc = (*this->pCompareAW32)(pNode->pszKey, pszKey);
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
        SZHASH_DATA     *this,
        uint32_t        hash
    )
    {
        uint16_t        index;
        
        index = hash % this->cHash;
        return index;
    }
    
    
    
    static
    LISTDL_DATA *   szHash_NodeListFromHash(
        SZHASH_DATA     *this,
        uint32_t        hash
    )
    {
        LISTDL_DATA     *pNodeList;
        
        pNodeList = &this->pHash[szHash_IndexFromHash(this,hash)];
        return( pNodeList );
    }
    
    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SZHASH_DATA *   szHash_Alloc(
    )
    {
        SZHASH_DATA     *this;
        uint32_t        cbSize = sizeof(SZHASH_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SZHASH_DATA *   szHash_New(
        uint16_t        cHash
    )
    {
        SZHASH_DATA     *this;
        
        // Do initialization.
        
        this = szHash_Alloc( );
        if (this) {
            this = szHash_Init(this, cHash);
        }
        
        // Return to caller.
        return this;
    }
    
    
    

    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    bool			szHash_setCompare(
        SZHASH_DATA     *this,
        int             (*pCompare)(const char *pKey1, const char *pKey2),
        int             (*pCompareAW32)(const char *pKey1, const W32CHR_T *pKey2)
    )
    {
        
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pCompare) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pCompare = pCompare;
        this->pCompareAW32 = pCompareAW32;
        
        return true;
    }
    
    
    
    bool			szHash_setComputeHash(
        SZHASH_DATA     *this,
        uint32_t        (*pComputeHash)(const char *pszKey1, size_t *pLen),
        uint32_t        (*pComputeHashW32)(const W32CHR_T *pszKey1, size_t *pLen)
    )
    {
        
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pComputeHash) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pComputeHash = pComputeHash;
        this->pComputeHashW32 = pComputeHashW32;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                   D u p l i c a t e s
    //---------------------------------------------------------------
    
    bool            szHash_getDuplicates(
        SZHASH_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->eRc = ERESULT_SUCCESS;
        return this->fDups ? true : false;
    }
    
    
    bool            szHash_setDuplicates(
        SZHASH_DATA     *this,
        bool            fValue
    )
    {
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->fDups = fValue ? 1 : 0;
        
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         szHash_getLastError(
        SZHASH_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            szHash_setLastError(
        SZHASH_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S i z e
    //---------------------------------------------------------------
    
    uint32_t        szHash_getSize(
        SZHASH_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
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
    
    ERESULT         szHash_AddA(
        SZHASH_DATA     *this,
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
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == this->pCompare) {
            return ERESULT_INVALID_FUNCTION;
        }
        if (NULL == this->pComputeHash) {
            return ERESULT_INVALID_FUNCTION;
        }
#endif
        
        hash = (*this->pComputeHash)(pszKey,NULL);
        if (this->fDups)
            ;
        else {
            pNode = szHash_FindNode(this, hash, pszKey);
            if (pNode) {
                fprintf( stderr, "Node Key = %s\n", pNode->pszKey);
                return ERESULT_DATA_ALREADY_EXISTS;
            }
        }
        
        // Determine the entry number.
        if (0 == listdl_Count(&this->freeList)) {
            if ( szHash_AddBlock(this) )
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
        pNode->pszKey = pszKey;
        pNode->pData  = pData;
        pNode->hash   = hash;
        
        pNodeList = szHash_NodeListFromHash(this, hash);
        listdl_Add2Head(pNodeList, pNode);

        ++this->num;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            szHash_Dealloc(
        OBJ_ID          objId
    )
    {
        SZHASH_DATA     *this = objId;
        SZHASH_BLOCK    *pBlock;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        while ( listdl_Count(&this->blocks) ) {
            pBlock = listdl_DeleteHead(&this->blocks);
            mem_Free( pBlock );
        }
        
        if( this->pHash ) {
            mem_Free( this->pHash );
            this->pHash = NULL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //----------------------------------------------------------
    //					  D e l e t e
    //----------------------------------------------------------
    
    ERESULT         szHash_DeleteA(
        SZHASH_DATA     *this,
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
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pszKey ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        hash = (*this->pComputeHash)(pszKey,NULL);
        pNode = szHash_FindNode(this, hash, pszKey);
        if (NULL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }

        pNodeList = szHash_NodeListFromHash(this, hash);
        listdl_Delete(pNodeList, pNode);
        listdl_Add2Tail(&this->freeList, pNode);
        --this->num;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //----------------------------------------------------------
    //                        E n u m
    //----------------------------------------------------------
    
    ENUM_DATA *     szHash_EnumKeys(
        SZHASH_DATA     *this
    )
    {
        ENUM_DATA       *pEnum = OBJ_NIL;
        uint32_t        i;
        LISTDL_DATA     *pNodeList;
        SZHASH_NODE     *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return pEnum;
        }
#endif
        
        pEnum = enum_New( );
        if (pEnum)
            ;
        else {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return pEnum;
        }
        
        for (i=0; i<this->cHash; ++i) {
            pNodeList = &this->pHash[i];
            pNode = listdl_Head(pNodeList);
            while (pNode) {
                enum_Append(pEnum, (void *)pNode->pszKey, NULL);
                pNode = listdl_Next(pNodeList, pNode);
            }
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pEnum;
    }
    
    

    //----------------------------------------------------------
    //                        F i n d
    //----------------------------------------------------------
    
    void *          szHash_FindA(
        SZHASH_DATA     *this,
        const
        char            *pszKey
    )
    {
        SZHASH_NODE     *pNode;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        hash = (*this->pComputeHash)(pszKey,NULL);
        
        pNode = szHash_FindNode(this, hash, pszKey);
        if (pNode) {
            return pNode->pData;
        }
        
        // Return to caller.
        return NULL;
    }
    
    
    void *          szHash_FindW32(
        SZHASH_DATA     *this,
        const
        W32CHR_T        *pszKey
    )
    {
        SZHASH_NODE     *pNode;
        uint32_t        hash;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        hash = (*this->pComputeHashW32)(pszKey, NULL);
        
        pNode = szHash_FindNodeW32(this, hash, pszKey);
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
        SZHASH_DATA         *this,
        uint16_t            cHash
    )
    {
        uint32_t            cbSize;
        uint32_t            i;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        if ( cHash == 0 )
            return( OBJ_NIL );
        
        this = obj_Init(this, obj_getSize(this), OBJ_IDENT_SZHASH);
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&szHash_Vtbl);
        
        this->cHash = cHash;
        cbSize = 4096 - sizeof(SZHASH_BLOCK);
        cbSize /= sizeof(SZHASH_NODE);
        this->cBlock = cbSize;
        
        // Allocate the Hash Table.
        cbSize = cHash * sizeof(LISTDL_DATA);
        this->pHash = (LISTDL_DATA *)mem_Malloc( cbSize );
        if (NULL == this->pHash) {
            DEBUG_BREAK();
            mem_Free(this);
            this = NULL;
            return this;
        }
        for (i=0; i<cHash; ++i) {
            listdl_Init(&this->pHash[i], offsetof(SZHASH_NODE, list));
        }
        listdl_Init(&this->freeList, offsetof(SZHASH_NODE, list));
        
        // Set Default Comparison Routines.
        szHash_setComputeHash(this, str_HashA, str_HashW32);
        szHash_setCompare(this, utf8_StrCmp, utf8_StrCmpAW32);
        
    #ifdef NDEBUG
    #else
        if ( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->pHash);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     szHash_ToDebugString(
        SZHASH_DATA     *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY
        ASTR_DATA       *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(szHash) ",
                     this
                     );
        AStr_AppendA(pStr, str);
        
#ifdef  XYZZY
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->toDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->toDebugString(
                                                                             this->pData,
                                                                             indent+3
                                                                             );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
        }
#endif
        
        j = snprintf(str, sizeof(str), " %p(szHash)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //----------------------------------------------------------
    //					  U p d a t e
    //----------------------------------------------------------
    
    ERESULT         szHash_UpdateA(
        SZHASH_DATA     *this,
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
        if( !szHash_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        hash = (*this->pComputeHash)(pszKey,NULL);
        pNode = szHash_FindNode(this, hash, pszKey);
        if (pNode) {
            pNode->pData = pData;
        }
        else
            return ERESULT_DATA_NOT_FOUND;
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            szHash_Validate(
        SZHASH_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_SZHASH) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(SZHASH_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


