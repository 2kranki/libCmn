// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   blocks32.c
 *	Generated 09/04/2016 13:13:56
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
#include <blocks_internal.h>
#include <enum_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    bool            blocks_AddBlock(
        BLOCKS_DATA     *this
    )
    {
        BLOCKS_BLOCK    *pBlock;
        BLOCKS_NODE     *pNode;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!blocks_Validate(this)) {
            DEBUG_BREAK();
        }
        if (0 == this->blockSize) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (0 == listdl_Count(&this->freeList))
            ;
        else {
            return true;
        }
        
        // Get a new block.
        pBlock = (BLOCKS_BLOCK *)mem_Malloc( this->blockSize );
        if( NULL == pBlock ) {
            return false;
        }
        listdl_Add2Tail(&this->blocks, pBlock);
        ++this->cBlocks;
        
        // Now chain the entries to the Free chain.
        for (i=0; i<this->cRecordsPerBlock; ++i) {
            pNode = (BLOCKS_NODE *)((uint8_t *)&pBlock->data + (this->recordSize * i));
            listdl_Add2Tail(&this->freeList, pNode);
        }
        
        // Return to caller.
        return true;
    }



    ERESULT         blocks_RecordFreeExit(
        BLOCKS_DATA     *this,
        void            *pRecord,
        void            *pArg3
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        //BLOCKS_NODE     *pNode = (BLOCKS_NODE *)((uint8_t *)pRecord - sizeof(BLOCKS_NODE));

        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        eRc = blocks_RecordFree(this, pRecord);
        
        // Return to caller.
        return eRc;
    }
    
    

    
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    BLOCKS_DATA *   blocks_Alloc(
    )
    {
        BLOCKS_DATA     *this;
        uint32_t        cbSize = sizeof(BLOCKS_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    BLOCKS_DATA *   blocks_New(
        void
    )
    {
        BLOCKS_DATA   *this;
        
        this = blocks_Alloc( );
        if (this) {
            this = blocks_Init(this);
        } 
        return this;
    }


    BLOCKS_DATA *   blocks_NewWithSizes(
        uint32_t        blockSize,
        uint32_t        recordSize
    )
    {
        BLOCKS_DATA     *this;
        ERESULT         eRc;
        
        this = blocks_Alloc( );
        if (this) {
            this = blocks_Init(this);
            if (this) {
                eRc = blocks_SetupSizes(this, blockSize, recordSize);
                if (ERESULT_FAILED(eRc)) {
                    DEBUG_BREAK();
                    obj_Release(this);
                    this = OBJ_NIL;
                }
            }
        }
        return this;
    }
    
    

    int32_t         blocks_Available(
        uint32_t        blockSize       // If 0, use default size.
    )
    {
        int32_t         avail = 0;
        
        if (blockSize == 0) {
            blockSize = BLKS_BLOCK_SIZE;
        }
        avail = blockSize - sizeof(BLOCKS_BLOCK);
        
        return avail;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint32_t        blocks_getBlockAvail(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->blockAvail;
    }
    
    
    
    uint32_t        blocks_getBlockSize(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->blockSize;
    }
    
    
    
    /*!
     * The delete exit is called whenever an active record is to be
     * freed allowing any clean up to be performed.
     */
    bool            blocks_setDeleteExit(
        BLOCKS_DATA     *this,
        P_ERESULT_EXIT3 pDelete,
        OBJ_ID          pObj,           // Used as first parameter of scan method
        void            *pArg3          // Used as third parameter of scan method
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->pDelete   = pDelete;
        this->pObj      = pObj;
        this->pArg3     = pArg3;
        
        return true;
    }

    
    LISTDL_DATA *   blocks_getList(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return &this->activeList;
    }
    
    
    
    uint32_t        blocks_getNumActive(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return listdl_Count(&this->activeList);
    }
    
    
    
    uint32_t        blocks_getRecordsPerBlock(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->cRecordsPerBlock;
    }
    
    
    
    uint32_t        blocks_getRecordSize(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->recordSize;
    }
    
    
    
    uint32_t        blocks_getSize(
        BLOCKS_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->cBlocks;
    }



    uint32_t        blocks_getUnique(
        BLOCKS_DATA     *this
    )
    {
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        return this->recordSize;
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
        ERESULT eRc = blocks__Assign(this,pOther);
     @endcode
     @param     this    BLOCKS object pointer
     @param     pOther  a pointer to another BLOCKS object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error 
     */
    ERESULT         blocks_Assign(
        BLOCKS_DATA		*this,
        BLOCKS_DATA      *pOther
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !blocks_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
        eRc = ERESULT_NOT_IMPLEMENTED; // <-- Remove this!
    //eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code
        blocks      *pCopy = blocks_Copy(this);
     @endcode
     @param     this    BLOCKS object pointer
     @return    If successful, a BLOCKS object which must be released,
                otherwise OBJ_NIL.
     @warning   Remember to release the returned the BLOCKS object.
     */
    BLOCKS_DATA *   blocks_Copy(
        BLOCKS_DATA     *this
    )
    {
        BLOCKS_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = blocks_NewWithSizes(this->blockSize, this->recordSize);
        if (pOther) {
            eRc = blocks_Assign(this, pOther);
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

    void            blocks_Dealloc(
        OBJ_ID          objId
    )
    {
        BLOCKS_DATA     *this = objId;
        BLOCKS_BLOCK    *pBlock;
        BLOCKS_NODE     *pNode;
        ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        // Delete all the active records.
        for (;;) {
            pNode = listdl_Tail(&this->activeList);
            if (pNode) {
                eRc = blocks_RecordFree(this, pNode->data);
            }
            else
                break;
        }
        
        // Delete all the blocks.
        while (listdl_Count(&this->blocks)) {
            pBlock = listdl_DeleteTail(&this->blocks);
            mem_Free(pBlock);
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        //other_Dealloc(this);          // Needed for inheritance
        obj_Dealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //----------------------------------------------------------
    //                        E n u m
    //----------------------------------------------------------
    
    ERESULT         blocks_Enum(
        BLOCKS_DATA     *this,
        ENUM_DATA       **ppEnum
    )
    {
        ENUM_DATA       *pEnum = OBJ_NIL;
        //uint32_t        i;
        BLOCKS_BLOCK    *pBlock;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
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
        
        pBlock = listdl_Head(&this->blocks);
        for (; pBlock; ) {
            enum_Append(pEnum, (void *)pBlock->data, NULL);
            pBlock = listdl_Next(&this->blocks, pBlock);
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
    
    ERESULT         blocks_ForEach(
        BLOCKS_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,            // Used as first parameter of scan method
        void            *pArg3
    )
    {
        BLOCKS_NODE     *pEntry = OBJ_NIL;
        ERESULT         eRc = ERESULT_SUCCESSFUL_COMPLETION;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( NULL == pScan ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        pEntry = listdl_Head(&this->activeList);
        while ( pEntry ) {
            eRc = pScan(pObj, pEntry->data, pArg3);
            if (ERESULT_HAS_FAILED(eRc)) {
                break;
            }
            pEntry = listdl_Next(&this->activeList, pEntry);
        }
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    BLOCKS_DATA *   blocks_Init(
        BLOCKS_DATA     *this
    )
    {
        uint32_t        cbSize = sizeof(BLOCKS_DATA);
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_BLOCKS);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_BLOCKS);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&blocks_Vtbl);
        
        listdl_Init(&this->blocks,  offsetof(BLOCKS_BLOCK, list));
        listdl_Init(&this->activeList, 0);
        listdl_Init(&this->freeList, 0);

    #ifdef NDEBUG
    #else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //----------------------------------------------------------
    //                  R e c o r d
    //----------------------------------------------------------
    
    ERESULT         blocks_RecordFree(
        BLOCKS_DATA     *this,
        void            *pRecord
    )
    {
        BLOCKS_NODE     *pNode = (BLOCKS_NODE *)((uint8_t *)pRecord - sizeof(BLOCKS_NODE));
        bool            fRc;
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        fRc = listdl_Delete(&this->activeList, pNode);
        if (fRc) {
            if (this->pDelete) {
                eRc = this->pDelete(this->pObj, pRecord, this->pArg3);
            }
            listdl_Add2Head(&this->freeList, pNode);
        }
        else
            eRc = ERESULT_DATA_NOT_FOUND;
        
        // Return to caller.
        return eRc;
    }
    
    
    void *          blocks_RecordGet(
        BLOCKS_DATA    *this,
        int32_t        index                    // (relative to 1)
    )
    {
        BLOCKS_NODE     *pNode;
        void            *pData = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pNode = listdl_Index(&this->activeList, index);
        if (pNode) {
            pData = pNode->data;
        }
        
        // Return to caller.
        return pData;
    }
    
    
    
    void *          blocks_RecordNew(
        BLOCKS_DATA     *this
    )
    {
        bool            fRc;
        //uint32_t        i;
        BLOCKS_NODE     *pNode;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !blocks_Validate(this) ) {
            DEBUG_BREAK();
            //this->eRc = ERESULT_INVALID_OBJECT;
            return NULL;
        }
#endif
        
        if (0 == listdl_Count(&this->freeList)) {
            fRc = blocks_AddBlock(this);
            if (!fRc)
                return NULL;
        }
        
        pNode = listdl_DeleteHead(&this->freeList);
        if (pNode) {
            memset(pNode->data, 0, (this->recordSize - sizeof(BLOCKS_NODE)));
            listdl_Add2Head(&this->activeList, pNode);
        }
        ++this->unique;
        
        // Return to caller.
        return &pNode->data;
    }
    
    
    
    //----------------------------------------------------------
    //                      S e t u p
    //----------------------------------------------------------
    
    ERESULT         blocks_SetupSizes(
        BLOCKS_DATA     *this,
        uint32_t        blockSize,
        uint32_t        recordSize
    )
    {
        
        // Do initialization.
        if (blockSize == 0)
            blockSize = BLKS_BLOCK_SIZE;
#ifdef NDEBUG
#else
        if (!blocks_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (this->cBlocks) {
            DEBUG_BREAK();
            return ERESULT_DATA_ALREADY_EXISTS;
        }
        if (recordSize > 0)
            ;
        else {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
        if (recordSize > (blockSize - sizeof(BLOCKS_BLOCK))) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        this->blockSize = blockSize;
        this->blockAvail = blockSize - sizeof(BLOCKS_BLOCK);
        this->dataSize = recordSize;
        recordSize = recordSize + sizeof(BLOCKS_NODE);
        this->recordSize = ((recordSize + 4 - 1) >> 2) << 2;
        if (recordSize) {
            this->cRecordsPerBlock = this->blockAvail / recordSize;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = blocks_ToDebugString(this,4);
     @endcode
     @param     this    BLOCKS object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     blocks_ToDebugString(
        BLOCKS_DATA     *this,
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
                     "{%p(blocks)  Records per Block=%d\n",
                     this,
                     this->cRecordsPerBlock
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
        
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        j = snprintf(str, sizeof(str), " %p(blocks)}\n", this);
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            blocks_Validate(
        BLOCKS_DATA      *this
    )
    {

        if( this ) {
            if ( obj_IsKindOf(this,OBJ_IDENT_BLOCKS) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(BLOCKS_DATA)) )
            return false;

#ifdef XYZZY
        if (this->blockSize) {
            i = this->blockSize - sizeof(BLOCKS_BLOCK);
            i /= sizeof(NODELIST_NODE);
            if (i == this->cBlock)
                ;
            else
                return false;
        }
        else {
            if (this->cBlock)
                return false;
        }
#endif
        
        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


