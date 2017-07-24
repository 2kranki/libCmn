// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   szTbl.c
 *	Generated 06/12/2015 10:58:21
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
#include    "szTbl_internal.h"
#include    "str.h"
#include    "utf8.h"



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    SZTBL_DATA      *pShared = OBJ_NIL;
    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    uint16_t		node_SizeNeeded(
        uint16_t		cLen
    );
    
    
    static
    SZTBL_HEAP *    szTbl_BlockAdd(
        SZTBL_DATA      *cbp
    )
    {
        SZTBL_HEAP      *pHeap;
        
        pHeap = (SZTBL_HEAP *)mem_Malloc( SZTBL_BLOCK_SIZE );
        if (pHeap) {
            pHeap->cbSize = SZTBL_BLOCK_SIZE;
            pHeap->size = SZTBL_BLOCK_SIZE - sizeof(SZTBL_HEAP);
            pHeap->used = 0;
            pHeap->rsvd = 0;
            pHeap->pNext = cbp->pHeap;
            cbp->pHeap = pHeap;
        }
        return pHeap;
    }
    
    

#ifdef XYZZY
    static
    bool            node_Construct(
        SZTBL_NODE      *pNode,
        uint16_t		cLen,
        uint32_t        hash,
        uint32_t        ident,
        char 			*pszString
    )
    {
        uint16_t        cbSize = node_SizeNeeded(cLen);
        bool            fRc = false;
        
        if (pNode) {
            pNode->hash = hash;
            pNode->ident = ident;
            pNode->max = cbSize - sizeof(SZTBL_NODE);
            pNode->len = cLen;
            fRc = str_Copy( pNode->data, pNode->max, pszString);
        }
        return fRc;
    }
#endif
    
    
    
    static
    uint16_t		node_SizeNeeded(
        uint16_t		cLen
    )
    {
        uint16_t        cbSize = sizeof(SZTBL_NODE);
        
        cbSize += cLen + 1;     // Adjust for NUL char.
        cbSize += 4 - 1;        // Round up to 32 bit boundary.
        cbSize /= 4;
        cbSize *= 4;
        return cbSize;
    }
    
    
    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SZTBL_DATA *     szTbl_Alloc(
    )
    {
        SZTBL_DATA       *this;
        uint32_t        cbSize = sizeof(SZTBL_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SZTBL_DATA *     szTbl_Shared(
    )
    {
        
        if (pShared) {
        }
        else {
            pShared = szTbl_Alloc( );
            if (pShared) {
                pShared = szTbl_Init(pShared);
            }
         }
        
        return pShared;
    }
    
    
    
    SZTBL_DATA *     szTbl_SharedReset(
    )
    {
        
        if (pShared) {
            obj_Release(pShared);
            pShared = OBJ_NIL;
        }
        
        return pShared;
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        szTbl_getPriority(
        SZTBL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            szTbl_setPriority(
        SZTBL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }



    uint32_t        szTbl_getSize(
        SZTBL_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return( 0 );
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            szTbl_Dealloc(
        OBJ_ID          objId
    )
    {
        SZTBL_DATA      *this = objId;
        SZTBL_HEAP      *pBlock;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !szTbl_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        if (this->pHashTable) {
            obj_Release(this->pHashTable);
            this->pHashTable = OBJ_NIL;
        }
        
        if (this->pPtrArray) {
            obj_Release(this->pPtrArray);
            this->pPtrArray = OBJ_NIL;
        }
        
        while (this->pHeap) {
            pBlock = this->pHeap;
            this->pHeap = pBlock->pNext;
            mem_Free(pBlock);
            //pBlock = NULL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc( this );
        if( this == pShared ) {
            pShared = OBJ_NIL;
        }
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SZTBL_DATA *   szTbl_Init(
        SZTBL_DATA       *this
    )
    {
        SZHASH_DATA     *pht;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_SZTBL );
        if (OBJ_NIL == this) {
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&szTbl_Vtbl);
        
        pht = szHash_Alloc();
        pht = szHash_Init(pht, SZHASH_TABLE_SIZE_SMALL);
        if (OBJ_NIL == pht) {
            obj_Release(this);
            return OBJ_NIL;
        }
        szHash_setComputeHash( pht, str_HashA, str_HashW );
        szHash_setCompare( pht, utf8_StrCmp, utf8_StrCmpAW );
        this->pHashTable = pht;
        
        this->pPtrArray = ptrArray_New();
        if (OBJ_NIL == this->pPtrArray) {
            obj_Release(pht);
            obj_Release(this);
            return OBJ_NIL;
        }
        
    #ifdef NDEBUG
    #else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                 S t r i n g  T o  S t r i n g
    //---------------------------------------------------------------
    
    ERESULT          szTbl_StringToString(
        SZTBL_DATA      *this,
        const
        char            *pStr,          // [in]
        const
        char            **ppStr         // [out] Returned String
    )
    {
        SZTBL_HEAP      *pHb;
        SZTBL_NODE      *pNode;
        uint32_t        hash;
        size_t          strLen;
        uint32_t        nodeSize;
        ERESULT         eRc;
        uint32_t        index;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStr) {
            return ERESULT_INVALID_PARAMETER;
        }
        if (NULL == ppStr) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = (SZTBL_NODE *)szHash_Find(this->pHashTable, pStr);
        if (pNode) {
            if (ppStr) {
                *ppStr = (const char *)pNode->data;
            }
            return ERESULT_SUCCESS_DATA_EXISTS;
        }

        hash = str_HashA(pStr, &strLen);
        nodeSize = node_SizeNeeded(strLen);
        
        // Add a Heap block if necessary.
        pHb = this->pHeap;
        while( pHb ) {
            if( (pHb->size - pHb->used) >= nodeSize )
                break;
            pHb = pHb->pNext;
        }
        if( NULL == pHb ) {
            pHb = szTbl_BlockAdd(this);
            if( NULL == pHb ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        if( (pHb->size - pHb->used) >= nodeSize )
            ;
        else {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        pNode = (SZTBL_NODE *)(((char *)pHb->node) + pHb->used);
        BREAK_NOT_BOUNDARY4(pNode);
        
        pNode->hash = hash;
        pNode->max = nodeSize - sizeof(SZTBL_NODE);
        pNode->len = strLen;
        str_Copy((char *)pNode->data, pNode->len+1, pStr);
        eRc = ptrArray_AppendObj(this->pPtrArray, pNode, &index);
        if (ERESULT_HAS_FAILED(eRc)) {
            return ERESULT_GENERAL_FAILURE;
        }
        pNode->ident = index;
        if (ppStr) {
            *ppStr = (const char *)pNode->data;
        }
        
        pHb->used += nodeSize;
        eRc = szHash_Add(this->pHashTable, (const char *)pNode->data, pNode);

        // Return to caller.
        return eRc;
    }
    

    
    //---------------------------------------------------------------
    //                 S t r i n g  T o  T o k e n
    //---------------------------------------------------------------
    
    ERESULT          szTbl_StringToToken(
        SZTBL_DATA      *this,
        const
        char            *pStr,          // [in]
        uint32_t        *pToken         // [out] Returned Token
    )
    {
        SZTBL_HEAP      *pHb;
        SZTBL_NODE      *pNode;
        uint32_t        hash;
        size_t          strLen;
        uint32_t        nodeSize;
        ERESULT         eRc;
        uint32_t        index;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStr) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = (SZTBL_NODE *)szHash_Find(this->pHashTable, pStr);
        if (pNode) {
            if (pToken) {
                *pToken = pNode->ident;
            }
            return ERESULT_SUCCESS_DATA_EXISTS;
        }
        
        hash = str_HashA(pStr, &strLen);
        nodeSize = node_SizeNeeded(strLen);
        
        // Add a Heap block if necessary.
        pHb = this->pHeap;
        while( pHb ) {
            if( (pHb->size - pHb->used) >= nodeSize )
                break;
            pHb = pHb->pNext;
        }
        if( NULL == pHb ) {
            pHb = szTbl_BlockAdd(this);
            if( NULL == pHb ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        if( (pHb->size - pHb->used) >= nodeSize )
            ;
        else {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        pNode = (SZTBL_NODE *)(((char *)pHb->node) + pHb->used);
        BREAK_NOT_BOUNDARY4(pNode);
        
        pNode->hash = hash;
        pNode->max = nodeSize - sizeof(SZTBL_NODE);
        pNode->len = strLen;
        str_Copy((char *)pNode->data, pNode->len+1, pStr);
        eRc = ptrArray_AppendObj(this->pPtrArray, pNode, &index);
        if (ERESULT_HAS_FAILED(eRc)) {
            return ERESULT_GENERAL_FAILURE;
        }
        pNode->ident = index;
        if (pToken) {
            *pToken = pNode->ident;
        }
        
        pHb->used += nodeSize;
        eRc = szHash_Add(this->pHashTable, (char *)pNode->data, pNode);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT          szTbl_StringWToToken(
        SZTBL_DATA      *this,
        const
        int32_t         *pStr,          // [in]
        uint32_t        *pToken         // [out] Returned Token
    )
    {
        SZTBL_HEAP      *pHb;
        SZTBL_NODE      *pNode;
        uint32_t        hash;
        size_t          strLen;
        uint32_t        utf8StrLen;
        uint32_t        nodeSize;
        ERESULT         eRc;
        uint32_t        index;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStr) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        pNode = (SZTBL_NODE *)szHash_FindW(this->pHashTable, pStr);
        if (pNode) {
            if (pToken) {
                *pToken = pNode->ident;
            }
            return ERESULT_SUCCESS_DATA_EXISTS;
        }
        
        hash = str_HashW(pStr, &strLen);
        utf8StrLen = utf8_WCToUtf8Str( (uint32_t)strLen, pStr, 0, NULL);
        nodeSize = node_SizeNeeded(utf8StrLen-1);
        
        // Add a Heap block if necessary.
        pHb = this->pHeap;
        while( pHb ) {
            if( (pHb->size - pHb->used) >= nodeSize )
                break;
            pHb = pHb->pNext;
        }
        if( NULL == pHb ) {
            pHb = szTbl_BlockAdd(this);
            if( NULL == pHb ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        if( (pHb->size - pHb->used) >= nodeSize )
            ;
        else {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        pNode = (SZTBL_NODE *)(((char *)pHb->node) + pHb->used);
        BREAK_NOT_BOUNDARY4(pNode);
        
        pNode->hash = hash;
        pNode->max = nodeSize - sizeof(SZTBL_NODE);
        pNode->len = utf8StrLen;
        i = utf8_WCToUtf8Str( (uint32_t)strLen, pStr, utf8StrLen, (char *)(pNode->data));
        eRc = ptrArray_AppendObj(this->pPtrArray, pNode, &index);
        if (ERESULT_HAS_FAILED(eRc)) {
            return ERESULT_GENERAL_FAILURE;
        }
        pNode->ident = index;
        if (pToken) {
            *pToken = pNode->ident;
        }
        
        pHb->used += nodeSize;
        eRc = szHash_Add(this->pHashTable, (char *)pNode->data, pNode);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                T o k e n  T o  S t r i n g
    //---------------------------------------------------------------
    
    ERESULT          szTbl_TokenToString(
        SZTBL_DATA      *this,
        uint32_t        token,          // [in]
        const
        char            **ppStr         // [out] Returned String
    )
    {
        SZTBL_NODE      *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == ppStr) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pNode = (SZTBL_NODE *)ptrArray_Get(this->pPtrArray, token);
        if (NULL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        // Return to caller.
        if (ppStr) {
            *ppStr = (const char *)pNode->data;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
 
    ASTR_DATA *     szTbl_ToDebugString(
        SZTBL_DATA      *this,
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
            AStr_AppendCharRepeatW(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(szTbl) ",
                     this
            );
        AStr_AppendA(pStr, str);

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
        
        j = snprintf( str, sizeof(str), " %p(szTbl)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            szTbl_Validate(
        SZTBL_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp, OBJ_IDENT_SZTBL) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(SZTBL_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


