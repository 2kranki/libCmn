// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ternary.c
 *	Generated 09/19/2015 00:10:38
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
#include "ternary_internal.h"
#include "trace.h"
#include "WStr.h"
#include <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    TERNARY_NODE *  ternary_NodeAlloc(
        TERNARY_DATA    *this
    )
    {
        
        uint32_t        i;
        uint32_t        index;
        TERNARY_NODE    *pNode;
        
        // Do initialization.
        
        // Allocate a block if no free nodes.
        if (NULL == this->pFreeNodes) {
            TERNARY_BUFFER          *pBuffer = blocks_Add((BLOCKS_DATA *)this);
            if (pBuffer == NULL) {
                this->eRc = ERESULT_OUT_OF_MEMORY;
                return NULL;
            }
            for( i=0; i<this->nodesPerBLock; ++i ) {
                index = (this->nodesPerBLock - 1) - i;
                pNode = &pBuffer->array[index];
                pNode->pData = this->pFreeNodes;
                this->pFreeNodes = pNode;
            }
        }
        
        pNode = this->pFreeNodes;
        this->pFreeNodes = pNode->pEqual;
        ++this->cTreeNum;
        
        // Return to caller.
        return pNode;
    }
    
    
    
    TERNARY_NODE *  ternary_NodeInsert(
        TERNARY_DATA    *this,
        TERNARY_NODE    *pNode,
        W32CHR_T        *pChr,
        void            *pData
    )
    {
        
        // Allocate a block if no free nodes.
        if (NULL == pNode) {
            pNode = ternary_NodeAlloc(this);
            if (pNode == NULL) {
                return NULL;
            }
            pNode->chr = *pChr;
            pNode->pLow = NULL;
            pNode->pEqual = NULL;
            pNode->pHigh = NULL;
            if (pNode->chr) {
                TRC_OBJ(this, "ternary_InsertNode: %p chr=%lc\n", pNode, pNode->chr);
            }
            else {
                TRC_OBJ(this, "ternary_InsertNode: %p chr='\\0'\n", pNode);
            }
        }
        if (*pChr < pNode->chr) {
            pNode->pLow = ternary_NodeInsert(this,pNode->pLow,pChr,pData);
            TRC_OBJ(this, "ternary_InsertNode: %p low=%p\n", pNode, pNode->pLow);
        }
        else if (*pChr == pNode->chr) {
            if (*pChr) {
                pNode->pEqual = ternary_NodeInsert(this, pNode->pEqual, ++pChr,pData);
                TRC_OBJ(this, "ternary_InsertNode: %p equal=%p\n", pNode, pNode->pEqual);
            }
            else {
                pNode->pData = pData;
                TRC_OBJ(this, "ternary_InsertNode: %p set pData\n", pNode);
            }
        }
        else {
            pNode->pHigh = ternary_NodeInsert(this,pNode->pHigh,pChr,pData);
            TRC_OBJ(this, "ternary_InsertNode: %p high=%p\n", pNode, pNode->pHigh);
        }
        
        // Return to caller.
        return pNode;
    }
    
    
    
    ERESULT         ternary_NodePreorder(
        TERNARY_DATA    *this,
        void            (pVisitor)(
            OBJ_ID          ,       // Object supplied below
            void            *       // Current Data
        ),
        OBJ_ID          pObject,
        TERNARY_NODE    *pNode
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
        if (NULL == pNode) {
            return eRc;
        }
        if (pNode->chr) {
            TRC_OBJ(this, "ternary_NodePreorder: %p L=%p E=%p H=%p chr=%lc\n",
                    pNode, pNode->pLow, pNode->pEqual, pNode->pHigh, pNode->chr);
        }
        else {
            TRC_OBJ(this, "ternary_NodePreorder: %p  EOS\n", pNode);
        }
        
        if (pNode->pLow) {
            eRc =   ternary_NodePreorder(
                                         this,
                                         pVisitor,
                                         pObject,
                                         pNode->pLow
                    );
        }
        
        
        if (pNode->chr) {
            eRc =   ternary_NodePreorder(
                                this,
                                pVisitor,
                                pObject,
                                pNode->pEqual
                    );
        }
        else {
            if (pVisitor) {
                pVisitor(pObject,pNode->pData);
            }
        }
        
        if (pNode->pHigh) {
            eRc =   ternary_NodePreorder(
                                this,
                                pVisitor,
                                pObject,
                                pNode->pHigh
                    );
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }
    
    
    
    

    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TERNARY_DATA *  ternary_Alloc(
    )
    {
        TERNARY_DATA    *this;
        uint32_t        cbSize = sizeof(TERNARY_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    TERNARY_DATA *  ternary_New(
        uint32_t        bufferSize
    )
    {
        TERNARY_DATA       *this;
        
        this = ternary_Alloc( );
        if (this) {
            this = ternary_Init( this, bufferSize );
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT         ternary_getLastError(
        TERNARY_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !ternary_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->eRc;
    }
    
    
    
    uint32_t        ternary_getSize(
        TERNARY_DATA    *this
    )
    {
#ifdef NDEBUG
#else
        if( !ternary_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return  0;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                              A d d
    //---------------------------------------------------------------
    
    bool            ternary_AddW32(
        TERNARY_DATA	*this,
        W32CHR_T		*pName,
        void            *pData
    )
    {
        uint32_t        keyLen;
        
#ifdef NDEBUG
#else
        if( !ternary_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (pName == NULL) {
            DEBUG_BREAK();
            this->eRc = ERESULT_INVALID_PARAMETER;
            return false;
        }
#endif
        keyLen = WStr_StrLen(pName);
        if (keyLen > this->maxKeyLen) {
            this->maxKeyLen = keyLen;
        }
        
        this->pRoot = ternary_NodeInsert(this, this->pRoot, pName, pData);
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            ternary_Dealloc(
        OBJ_ID          objId
    )
    {
        TERNARY_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !ternary_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        obj_setVtbl(this, (OBJ_IUNKNOWN *)this->pSuperVtbl);
        blocks_Dealloc(this);
        //obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                          F i n d
    //---------------------------------------------------------------
    
    void *          ternary_FindW32(
        TERNARY_DATA	*this,
        W32CHR_T		*pszKey
    )
    {
        int32_t			diff;
        TERNARY_NODE    *pNode = NULL;
        void            *pData = NULL;
        W32CHR_T        *pKey = pszKey;
        
        // Validate the input parameters.
        if( NULL == pszKey ) {
            this->eRc = ERESULT_INVALID_PARAMETER;
            goto Exit00;
        }
        
        // Search the current table.
        pNode = this->pRoot;
        for( ;; ) {
            if( NULL == pNode )
                break;
            diff = *pKey - pNode->chr;
            if( diff == 0 ) {
                if( *pKey == 0 ) {
                    pData = pNode->pData;
                    this->eRc = ERESULT_SUCCESS;
                    goto Exit00;
                }
                ++pKey;
                pNode = pNode->pEqual;
            }
            else if ( diff < 0 )
                pNode = pNode->pLow;
            else
                pNode = pNode->pHigh;
        }
        
        // Return to caller.
    Exit00:
        return pData;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    TERNARY_DATA *  ternary_Init(
        TERNARY_DATA    *this,
        uint32_t        bufferSize
    )
    {
        uint32_t        cbSize = sizeof(TERNARY_DATA);
        uint32_t        blockSize = 4096;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        //cbSize = obj_getSize(this);
        //this = (TERNARY_DATA *)obj_Init( this, cbSize, OBJ_IDENT_TERNARY );
        this = (TERNARY_DATA *)blocks_Init((BLOCKS_DATA *)this, blockSize );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);         // Needed for Inheritance
        obj_setIdent((OBJ_ID)this, OBJ_IDENT_TERNARY);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ternary_Vtbl);

        this->nodesPerBLock = blockSize / sizeof(TERNARY_NODE);
        
    #ifdef NDEBUG
    #else
        if( !ternary_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        BREAK_NOT_BOUNDARY4(&this->nodesPerBLock);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     ternary_ToDebugString(
        TERNARY_DATA    *this,
        int             indent
    )
    {
        char            str[256];
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        SZSTR_DATA      *pWrkStr;
#endif
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{%p(ternary) side=%d ",
                     this,
                     ternary_getSize(this)
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
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            ternary_Validate(
        TERNARY_DATA      *this
    )
    {
        this->eRc = ERESULT_INVALID_OBJECT;
        if(this) {
            if ( obj_IsKindOf(this,OBJ_IDENT_TERNARY) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(TERNARY_DATA)) )
            return false;

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    //---------------------------------------------------------------
    //                    V i s i t  P r e o r d e r
    //---------------------------------------------------------------
    
    ERESULT         ternaryTree_VisitPreorder(
        TERNARY_DATA	*this,
        void            (pVisitor)(
            OBJ_ID          ,       // Object supplied below
            void            *       // Word associated Data
        ),
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !ternary_Validate(this) ) {
            DEBUG_BREAK();
            return this->eRc;
        }
#endif
        
        eRc = ternary_NodePreorder(this, pVisitor, pObject, this->pRoot);
        
        // Return to caller.
        return this->eRc;
    }
    
    
    
    
    
#ifdef	__cplusplus
}
#endif


