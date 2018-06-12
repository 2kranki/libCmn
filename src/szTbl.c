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
#include        <szTbl_internal.h>
#include        <str.h>
#include        <utf8.h>



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
        SZTBL_DATA      *this;
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

    ERESULT         szTbl_getLastError(
        SZTBL_DATA      *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            szTbl_setLastError(
        SZTBL_DATA      *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
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
        return ptrArray_getSize(this->pPtrArray);
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
        szHash_setComputeHash( pht, str_HashA, str_HashW32 );
        szHash_setCompare( pht, utf8_StrCmp, utf8_StrCmpAW32 );
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
    
    const
    char *          szTbl_StringToString(
        SZTBL_DATA      *this,
        const
        char            *pStr           // [in]
    )
    {
        SZTBL_HEAP      *pHb;
        SZTBL_NODE      *pNode;
        uint32_t        hash;
        size_t          strLen;
        uint32_t        nodeSize;
        ERESULT         eRc;
        uint32_t        index;
        const
        char            *pStrRet = NULL;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = szTbl_Shared();
        }
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pStr) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return NULL;
        }
#endif
        
        pNode = (SZTBL_NODE *)szHash_FindA(this->pHashTable, pStr);
        if (pNode) {
            this->eRc = ERESULT_SUCCESS;
            return (const char *)pNode->data;
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
                this->eRc = ERESULT_INSUFFICIENT_MEMORY;
                return NULL;
            }
        }
        
        if( (pHb->size - pHb->used) >= nodeSize )
            ;
        else {
            this->eRc = ERESULT_INSUFFICIENT_MEMORY;
            return NULL;
        }
        pNode = (SZTBL_NODE *)(((char *)pHb->node) + pHb->used);
        BREAK_NOT_BOUNDARY4(pNode);
        
        pNode->hash = hash;
        pNode->max = nodeSize - sizeof(SZTBL_NODE);
        pNode->len = strLen;
        str_Copy((char *)pNode->data, pNode->len+1, pStr);
        eRc = ptrArray_AppendData(this->pPtrArray, pNode, &index);
        if (ERESULT_HAS_FAILED(eRc)) {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return NULL;
        }
        pNode->ident = index;
        pStrRet = (const char *)pNode->data;
        
        pHb->used += nodeSize;
        eRc = szHash_AddA(this->pHashTable, (const char *)pNode->data, pNode);

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pStrRet;
    }
    

    
    //---------------------------------------------------------------
    //                 S t r i n g  T o  T o k e n
    //---------------------------------------------------------------
    
    uint32_t        szTbl_StringToToken(
        SZTBL_DATA      *this,
        const
        char            *pStr           // [in]
    )
    {
        SZTBL_HEAP      *pHb;
        SZTBL_NODE      *pNode;
        uint32_t        hash;
        size_t          strLen;
        uint32_t        nodeSize;
        ERESULT         eRc;
        uint32_t        index;
        uint32_t        token;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = szTbl_Shared();
        }
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (NULL == pStr) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif
        
        pNode = (SZTBL_NODE *)szHash_FindA(this->pHashTable, pStr);
        if (pNode) {
            this->eRc = ERESULT_SUCCESS_DATA_EXISTS;
            return pNode->ident;
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
                this->eRc = ERESULT_INSUFFICIENT_MEMORY;
                return 0;
            }
        }
        
        if( (pHb->size - pHb->used) >= nodeSize )
            ;
        else {
            this->eRc = ERESULT_INSUFFICIENT_MEMORY;
            return 0;
        }
        pNode = (SZTBL_NODE *)(((char *)pHb->node) + pHb->used);
        BREAK_NOT_BOUNDARY4(pNode);
        
        pNode->hash = hash;
        pNode->max = nodeSize - sizeof(SZTBL_NODE);
        pNode->len = strLen;
        str_Copy((char *)pNode->data, pNode->len+1, pStr);
        eRc = ptrArray_AppendData(this->pPtrArray, pNode, &index);
        if (ERESULT_HAS_FAILED(eRc)) {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return 0;
        }
        pNode->ident = index;
        token = pNode->ident;
        
        pHb->used += nodeSize;
        eRc = szHash_AddA(this->pHashTable, (char *)pNode->data, pNode);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return token;
    }
    
    
    uint32_t         szTbl_StringW32ToToken(
        SZTBL_DATA      *this,
        const
        W32CHR_T        *pStr           // [in]
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
        uint32_t        token;

        // Do initialization.
        if (OBJ_NIL == this) {
            this = szTbl_Shared();
        }
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pStr) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            return 0;
        }
#endif

        pNode = (SZTBL_NODE *)szHash_FindW32(this->pHashTable, pStr);
        if (pNode) {
            this->eRc = ERESULT_SUCCESS_DATA_EXISTS;
            return pNode->ident;
        }
        
        hash = str_HashW32(pStr, &strLen);
        utf8StrLen = utf8_W32ToUtf8Str( (uint32_t)strLen, pStr, 0, NULL);
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
                this->eRc = ERESULT_INSUFFICIENT_MEMORY;
                return 0;
            }
        }
        
        if( (pHb->size - pHb->used) >= nodeSize )
            ;
        else {
            this->eRc = ERESULT_INSUFFICIENT_MEMORY;
            return 0;
        }
        pNode = (SZTBL_NODE *)(((char *)pHb->node) + pHb->used);
        BREAK_NOT_BOUNDARY4(pNode);
        
        pNode->hash = hash;
        pNode->max = nodeSize - sizeof(SZTBL_NODE);
        pNode->len = utf8StrLen;
        i = utf8_W32ToUtf8Str( (uint32_t)strLen, pStr, utf8StrLen, (char *)(pNode->data));
        eRc = ptrArray_AppendData(this->pPtrArray, pNode, &index);
        if (ERESULT_HAS_FAILED(eRc)) {
            this->eRc = ERESULT_GENERAL_FAILURE;
            return 0;
        }
        pNode->ident = index;
        token = pNode->ident;
        
        pHb->used += nodeSize;
        eRc = szHash_AddA(this->pHashTable, (char *)pNode->data, pNode);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return token;
    }
    
    
    
    //---------------------------------------------------------------
    //                      T o k e n  T o
    //---------------------------------------------------------------
    
    uint32_t        szTbl_TokenToHash(
        SZTBL_DATA      *this,
        uint32_t        token           // [in]
    )
    {
        SZTBL_NODE      *pNode;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = szTbl_Shared();
        }
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pNode = (SZTBL_NODE *)ptrArray_GetData(this->pPtrArray, token);
        if (NULL == pNode) {
            this->eRc = ERESULT_DATA_NOT_FOUND;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return pNode->hash;
    }
    
    
    const
    char *           szTbl_TokenToString(
        SZTBL_DATA      *this,
        uint32_t        token           // [in]
    )
    {
        SZTBL_NODE      *pNode = NULL;
        
        // Do initialization.
        if (OBJ_NIL == this) {
            this = szTbl_Shared();
        }
#ifdef NDEBUG
#else
        if( !szTbl_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        if (this->pPtrArray) {
            pNode = (SZTBL_NODE *)ptrArray_GetData(this->pPtrArray, token);
        }
        if (NULL == pNode) {
            this->eRc = ERESULT_DATA_NOT_FOUND;
            return NULL;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return (const char *)pNode->data;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
 
    ASTR_DATA *     szTbl_ToDebugString(
        SZTBL_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;

        if (OBJ_NIL == this) {
            this = szTbl_Shared();
        }

        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                               pStr,
                               "{%p(%s) size=%d\n",
                               this,
                               pInfo->pClassName,
                               this->size
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


