// vi:nu:et:sts=4 ts=4 sw=4 
/*
 * File:   tokenList.c
 *	Generated 07/22/2015 10:03:31
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
#include    <tokenList_internal.h>
#include    <enum_internal.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            tokenList_AddBlock(
        TOKENLIST_DATA   *cbp
    )
    {
        TOKENLIST_BLOCK *pBlock;
        TOKENLIST_TOKEN *pEntry;
        uint32_t        i;
        
        // Do initialization.
        if ( 0 == listdl_Count(&cbp->freeList) )
            ;
        else {
            return true;
        }
        
        // Get a new block.
        i = sizeof(TOKENLIST_BLOCK) + (cbp->cBlock * sizeof(TOKENLIST_TOKEN));
        pBlock = (TOKENLIST_BLOCK *)mem_Calloc( i, 1 );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&cbp->blocks, pBlock);
        
        // Now chain the entries to the Free chain.
        for (i=0; i<cbp->cBlock; ++i) {
            pEntry = &pBlock->tokens[i];
            listdl_Add2Tail(&cbp->freeList, pEntry);
        }
        
        // Return to caller.
        return true;
    }
    
    
    
    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TOKENLIST_DATA * tokenList_Alloc(
    )
    {
        TOKENLIST_DATA   *cbp;
        uint32_t        cbSize = sizeof(TOKENLIST_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    TOKENLIST_DATA * tokenList_New(
    )
    {
        TOKENLIST_DATA   *cbp;
        
        cbp = tokenList_Alloc( );
        if (cbp) {
            cbp = tokenList_Init(cbp);
        }
        
        return( cbp );
    }
    
    
    
    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         tokenList_getLastError(
        TOKENLIST_DATA  *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !tokenList_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    bool            tokenList_setLastError(
        TOKENLIST_DATA  *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !tokenList_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    uint16_t        tokenList_getPriority(
        TOKENLIST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !tokenList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        //return this->priority;
        return 0;
    }

    bool            tokenList_setPriority(
        TOKENLIST_DATA   *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !tokenList_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        //this->priority = value;
        return true;
    }



    uint32_t        tokenList_getSize(
        TOKENLIST_DATA   *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !tokenList_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return listdl_Count(&cbp->list);
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         tokenList_Add2Head(
        TOKENLIST_DATA   *this,
        TOKEN_DATA       *pToken
    )
    {
        TOKENLIST_TOKEN   *pEntry;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pToken) || !obj_IsKindOf(pToken,OBJ_IDENT_TOKEN) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
    #endif

        if (0 == listdl_Count(&this->freeList)) {
            if ( tokenList_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        memset(&pEntry->token, 0, sizeof(TOKEN_DATA));
        token_Init(&pEntry->token);
        token_Assign(pToken, &pEntry->token);
        listdl_Add2Head(&this->list, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }


    ERESULT         tokenList_Add2Tail(
        TOKENLIST_DATA   *this,
        TOKEN_DATA       *pToken
    )
    {
        TOKENLIST_TOKEN   *pEntry;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( (OBJ_NIL == pToken) || !obj_IsKindOf(pToken,OBJ_IDENT_TOKEN) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (0 == listdl_Count(&this->freeList)) {
            if ( tokenList_AddBlock(this) )
                ;
            else {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        pEntry = listdl_DeleteHead(&this->freeList);
        if (NULL == pEntry) {
            return ERESULT_INSUFFICIENT_MEMORY;
        }
        memset(&pEntry->token, 0, sizeof(TOKEN_DATA));
        token_Init(&pEntry->token);
        token_Assign(pToken, &pEntry->token);
        listdl_Add2Tail(&this->list, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESSFUL_COMPLETION;
    }
    
    

    //----------------------------------------------------------
    //                      A p p e n d
    //----------------------------------------------------------
    
    ERESULT         tokenList_Append(
        TOKENLIST_DATA	*this,
        TOKENLIST_DATA	*other
    )
    {
        TOKENLIST_TOKEN *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !tokenList_Validate(other) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Head(&other->list);
        while ( pEntry ) {
            tokenList_Add2Tail(this, &pEntry->token);
            pEntry = listdl_Next(&other->list, pEntry);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------
    
    void            tokenList_Dealloc(
        OBJ_ID          objId
    )
    {
        TOKENLIST_DATA   *this = objId;
        TOKENLIST_BLOCK  *pBlock;
        TOKENLIST_TOKEN   *pEntry;
        
        // Do initialization.
        if (NULL == this) {
            return;
        }
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        // Release all the tokens.
        while ( (pEntry = listdl_Head(&this->list)) ) {
            listdl_DeleteHead(&this->list);
        }
        
        while ( listdl_Count(&this->blocks) ) {
            pBlock = listdl_DeleteHead(&this->blocks);
            mem_Free( pBlock );
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                          D e l e t e
    //---------------------------------------------------------------
    
    ERESULT         tokenList_DeleteAll(
        TOKENLIST_DATA	*this
    )
    {
        TOKENLIST_TOKEN   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        for (;;) {
            pEntry = listdl_Head(&this->list);
            if (NULL == pEntry) {
                break;
            }
            
            listdl_Delete(&this->list, pEntry);
            listdl_Add2Tail(&this->freeList, pEntry);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         tokenList_DeleteHead(
        TOKENLIST_DATA	*this
    )
    {
        TOKENLIST_TOKEN   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    ERESULT         tokenList_DeleteTail(
        TOKENLIST_DATA	*this
    )
    {
        TOKENLIST_TOKEN   *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Tail(&this->list);
        if (NULL == pEntry) {
            return ERESULT_DATA_NOT_FOUND;
        }
        
        listdl_Delete(&this->list, pEntry);
        listdl_Add2Tail(&this->freeList, pEntry);
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //----------------------------------------------------------
    //                        E n u m
    //----------------------------------------------------------
    
    ERESULT         tokenList_Enum(
        TOKENLIST_DATA	*this,
        ENUM_DATA       **ppEnum
    )
    {
        ENUM_DATA       *pEnum = OBJ_NIL;
        //uint32_t        i;
        //LISTDL_DATA     *pNodeList;
        TOKENLIST_TOKEN *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate(this) ) {
            DEBUG_BREAK();
            if (ppEnum) {
                *ppEnum = pEnum;
            }
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEnum = enum_New( );
        if (pEnum) {
        }
        else {
            if (ppEnum) {
                *ppEnum = pEnum;
            }
            return ERESULT_OUT_OF_MEMORY;
        }
        
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            enum_Append(pEnum, (void *)&pEntry->token, NULL);
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        // Return to caller.
        if (ppEnum) {
            *ppEnum = pEnum;
        }
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          F o r  E a c h
    //---------------------------------------------------------------
    
    ERESULT         tokenList_ForEach(
        TOKENLIST_DATA	*this,
        P_VOIDEXIT2_BE  pScan,
        OBJ_ID          pObj            // Used as first parameter of scan method
    )
    {
        TOKENLIST_TOKEN *pEntry = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
       
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            eRc = pScan(pObj,&pEntry->token);
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          H e a d
    //---------------------------------------------------------------
    
    TOKEN_DATA *    tokenList_Head(
        TOKENLIST_DATA	*this
                                         )
    {
        TOKENLIST_TOKEN *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEntry = listdl_Head(&this->list);
        if (NULL == pEntry) {
            return OBJ_NIL;
        }
        
        // Return to caller.
        return &pEntry->token;
    }
    

    
    //---------------------------------------------------------------
    //                          I n d e x
    //---------------------------------------------------------------
    
    TOKEN_DATA *    tokenList_Index(
        TOKENLIST_DATA	*this,
        int32_t			index					// (relative to 1)
    )
    {
        TOKENLIST_TOKEN *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEntry = listdl_Index(&this->list, index);
        if (NULL == pEntry) {
            return OBJ_NIL;
        }
        
        // Return to caller.
        return &pEntry->token;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TOKENLIST_DATA * tokenList_Init(
        TOKENLIST_DATA   *this
    )
    {
        uint32_t        cbSize;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_TOKENLIST );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&tokenList_Vtbl);
        
        cbSize = HASH_BLOCK_SIZE - sizeof(TOKENLIST_BLOCK);
        cbSize /= sizeof(TOKENLIST_TOKEN);
        this->cBlock = cbSize;
        
        // Initialize the lists.
        listdl_Init(&this->freeList, offsetof(TOKENLIST_TOKEN, list));
        listdl_Init(&this->blocks, offsetof(TOKENLIST_TOKEN, list));
        listdl_Init(&this->list, offsetof(TOKENLIST_TOKEN, list));
        
    #ifdef NDEBUG
    #else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->list);
    #endif

        return this;
    }

     

    //----------------------------------------------------------
    //                  P r e p e n d
    //----------------------------------------------------------
    
    ERESULT         tokenList_Prepend(
        TOKENLIST_DATA	*this,
        TOKENLIST_DATA	*other
    )
    {
        TOKENLIST_TOKEN *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !tokenList_Validate(other) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pEntry = listdl_Tail(&other->list);
        while ( pEntry ) {
            tokenList_Add2Head(this, &pEntry->token);
            pEntry = listdl_Prev(&other->list, pEntry);
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          T a i l
    //---------------------------------------------------------------
    
    TOKEN_DATA *    tokenList_Tail(
        TOKENLIST_DATA	*this
    )
    {
        TOKENLIST_TOKEN *pEntry = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !tokenList_Validate( this ) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pEntry = listdl_Tail(&this->list);
        if (NULL == pEntry) {
            return OBJ_NIL;
        }
        
        // Return to caller.
        return &pEntry->token;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     tokenList_ToDebugString(
        TOKENLIST_DATA   *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr;
        TOKEN_DATA       *pNode;
        TOKENLIST_TOKEN   *pEntry = OBJ_NIL;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(tokenList) Size=%d\n",
                     this,
                     this->size
                     );
        AStr_AppendA(pStr, str);
        
        pEntry = listdl_Head(&this->list);
        while ( pEntry ) {
            pNode = &pEntry->token;
            if (((OBJ_DATA *)(pNode))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(pNode))->pVtbl->pToDebugString(
                                    pNode,
                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
            }
            pEntry = listdl_Next(&this->list, pEntry);
        }
        
        AStr_AppendCharA(pStr, '\n');
        AStr_AppendCharRepeatA(pStr, indent, ' ');
        j = snprintf( str, sizeof(str), "%p(tokenList)}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            tokenList_Validate(
        TOKENLIST_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_TOKENLIST) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(TOKENLIST_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


