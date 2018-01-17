// vi:nu:et:sts=4 ts=4 sw=4

/****************************************************************
 *        Table Manager (table) Support Subroutines Header      *
 ****************************************************************/
/*
 * Program
 *              Table Manager (table) Subroutines
 * Purpose
 *              See table.H for a description of these routines.
 * Todo List
 *              None
 * Remarks
 *  1.          The data array is referenced relative to one, but
 *              each reference is adjusted to be relative to zero.
 * History
 *              See table.H for the history.
 * References
 *              See table.H for the references.
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




/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include    "table_internal.h"


#ifdef	__cplusplus
extern	"C" {
#endif
    
#define			Entry2Ptr( Entry )	(void *)\
                                        ((uint8_t *)Entry + offsetof(TABLE_ENTRY,data))
#define			Ptr2Entry( Ptr )	((TABLE_ENTRY *)\
                                        ((uint8_t *)Ptr - offsetof(TABLE_ENTRY,data)))
    
    
    /* Internal Subroutine Definitions
     */
    static
    TABLE_BLOCK *   table_AllocBlock(
        TABLE_DATA      *this,
        TABLE_BLOCK     *pBlock
    );

#ifdef NDEBUG
#else
    bool			table_Validate(
        TABLE_DATA      *this
    );
#endif





    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
    ****************************************************************/

    /*
     * Get a new Block of Entries and set them up appropriately.
     */
    static
    TABLE_BLOCK *   table_AllocBlock(
        TABLE_DATA      *this,
        TABLE_BLOCK     *pBlock     // Block to be added or NULL
    )
    {
        
        uint32_t        i;
        uint32_t        index;
        TABLE_ENTRY     *ep;

        // Do initialization.
        if( NULL == this )
            return( NULL );

        // Allocate a block if not provided.
        if (NULL == pBlock) {
            if (obj_FlagOn(this, TABLE_FLAG_FIXED) && listdl_Count(&this->blockList)) {
                return NULL;
            }
            pBlock = (TABLE_BLOCK *)mem_Malloc( this->blockSize );
            if( NULL == pBlock )
                return( NULL );        
        }
        memset(pBlock, 0, this->blockSize);
        listdl_Add2Head(&this->blockList, pBlock);

        // Chain each entry in the block to the top of the free list
        // in reverse order since the free list is a push down list.
        for( i=0; i<this->entriesPerBlock; ++i ) {
            index = ((this->entriesPerBlock - 1) - i) * this->entrySize;
            ep = (TABLE_ENTRY *)(uint8_t *)&pBlock->data[index];
            listdl_Add2Head(&this->freeList, ep);
        }

        // Return to caller.
        return( pBlock );
    }




    /*
     * Get a new Entry.
     */
    static
    TABLE_ENTRY *   table_NewEntry(
        TABLE_DATA      *this
    )
    {
        TABLE_ENTRY     *ep = NULL;

        // Get a new block of entries if necessary.
        if( (0 == listdl_Count(&this->blockList)) ) {
            if( table_AllocBlock(this, NULL) )
                ;
            else
                return NULL;
        }
        if( (NULL == listdl_Head(&this->freeList)) ) {
            if (obj_IsFlag(this, TABLE_FLAG_FIXED)) {
                return NULL;
            }
            if( table_AllocBlock(this, NULL) )
                ;
            else
                return NULL;
        }

        // Get a free entry and chain it to the top of the active list.
        ep = listdl_DeleteHead( &this->freeList );
        listdl_Add2Tail( &this->activeList, ep );

        // Return to caller.
        return( ep );
    }





    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    TABLE_DATA *    table_Alloc(
    )
    {
        TABLE_DATA      *this;
        uint32_t        cbSize = sizeof(TABLE_DATA);

        this = obj_Alloc(cbSize);
        
        // Return to caller.
        return this;
    }



    uint32_t        table_FindNumEntries(
        uint32_t        approxBlockSizeInK,
        uint32_t        entryDataSize
    )
    {
        uint16_t        cEntries = 1;
        uint16_t        entrySize;
        uint16_t        blockSize = 0;
        int16_t         diff = 0;
        
        // Figure out how many entries per block.
        entrySize = ROUNDUP4(entryDataSize + sizeof(TABLE_ENTRY));        
        for ( ;; ) {
            blockSize = (cEntries * entrySize) + sizeof(TABLE_BLOCK);
            diff = (approxBlockSizeInK * 1024) - blockSize;
            if (diff < 0) {
                --cEntries;
                break;
            }
            ++cEntries;
        }
        
        // Return to caller.
        return( cEntries );
    }
    
    
    
    uint32_t        table_FindBlockSize(
        uint32_t        approxBlockSizeInK,
        uint32_t        entryDataSize
    )
    {
        uint16_t        cEntries = 1;
        uint16_t        entrySize;
        uint16_t        blockSize = 0;
        int16_t         diff = 0;
        
        // Figure out how many entries per block.
        entrySize = ROUNDUP4(entryDataSize + sizeof(TABLE_ENTRY));
        for ( ;; ) {
            blockSize = (cEntries * entrySize) + sizeof(TABLE_BLOCK);
            diff = (approxBlockSizeInK * 1024) - blockSize;
            if (diff < 0) {
                --cEntries;
                break;
            }
            ++cEntries;
        }
        blockSize = (cEntries * entrySize) + sizeof(TABLE_BLOCK);
        
        // Return to caller.
        return( blockSize );
    }
    
    
    TABLE_DATA *    table_New(
        uint16_t        entriesPerBlock,
        uint16_t        entryDataSize,
        bool            fFixed
    )
    {
        TABLE_DATA      *this = OBJ_NIL;

        this = table_Alloc( );
        if (this) {
            this = table_Init(this, entriesPerBlock, entryDataSize, fFixed);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    

    //===============================================================
    //                      *** Propertiess ***
    //===============================================================

    uint32_t        table_getCount(
        TABLE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return listdl_Count(&this->activeList);
    }
    
    
    
    uint16_t        table_getEntriesPerBlock(
        TABLE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->entriesPerBlock;
    }
    
    
    
    uint16_t        table_getEntryDataSize(
        TABLE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->entriesPerBlock;
    }
    
    
    
    ERESULT         table_getLastError(
        TABLE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        return this->eRc;
    }
    
    
    
    
    
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------
    
    void *          table_Add(
        TABLE_DATA      *this
    )
    {
        TABLE_ENTRY     *pWork;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        pWork = table_NewEntry(this);
        
        // Return to caller.
        return( pWork ? Entry2Ptr(pWork) : pWork );
    }
    
    
    
    
    //---------------------------------------------------------------
    //					  D e a l l o c
    //---------------------------------------------------------------

    void			table_Dealloc(
        OBJ_ID          objId
    )
    {
        TABLE_DATA      *this = objId;
        TABLE_BLOCK     *bp;
#ifdef __APPLE__
#else
        enum TN_RCode   tRc;
#endif

        /* Do initialization.
         */
        if (OBJ_NIL == this) {
            return;
        }
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        // Free all external blocks. The list is a pushdown
        // list in order by newest to oldest.
        while( listdl_Count(&this->blockList) ) {
            bp = listdl_Head(&this->blockList);
            listdl_DeleteHead(&this->blockList);
            mem_Free( bp );
        }

        if (this->pMutex) {
            obj_Release(this->pMutex);
            this->pMutex = OBJ_NIL;
        }

        // Free the main control block.
        obj_setVtbl(this, (OBJ_IUNKNOWN *)this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      C o u n t
    //---------------------------------------------------------------

    /* table_Count() returns current number of used entries.
     */

    TABLE_INDEX     table_Count(
        TABLE_DATA      *this
    )
    {
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        

        return( listdl_Count(&this->activeList) );
    }




    //---------------------------------------------------------------
    //                      D e l e t e
    //---------------------------------------------------------------

    bool            table_Delete(
        TABLE_DATA      *this,
        void            *pData
    )
    {
        TABLE_ENTRY     *pEntry = Ptr2Entry(pData);

        /* Do initialization.
         */
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pData) {
            return false;
        }
        if (0 == listdl_Count(&this->activeList)) {
            return false;
        }
#endif

        if (listdl_Contains( &this->activeList, pEntry )) {
            listdl_Delete(   &this->activeList, pEntry );
            listdl_Add2Head( &this->freeList,   pEntry );
        }
        else {
            return false;
        }

        return true;
    }




    //---------------------------------------------------------------
    //                          H e a d
    //---------------------------------------------------------------
    
    void *          table_Head(
        TABLE_DATA      *this
    )
    {
        TABLE_ENTRY     *pWork;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        pWork = listdl_Head(&this->activeList);
        
        // Return to caller.
        return( pWork ? Entry2Ptr(pWork) : pWork );
    }
    
    
        
    /**********************************************************
                              I n i t
     **********************************************************/

    TABLE_DATA *    table_Init(
        TABLE_DATA		*this,
        uint16_t        entriesPerBlock,
        uint16_t        entryDataSize,
        bool            fFixed			// true if Fixed Size Table
    )
    {	
        uint32_t        cbSize = sizeof(TABLE_DATA);
        uint32_t        blockSize = 0;
        uint32_t        entrySize = sizeof(TABLE_ENTRY);
#ifdef __APPLE__
#else
        enum TN_RCode   tRc;
#endif

        // Do initialization.
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }

        if (0 == entryDataSize) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        if (0 == entriesPerBlock) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this = obj_Init( this, cbSize, OBJ_IDENT_TABLE );
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&table_Vtbl);
        
        this->pMutex = psxMutex_New();
        if (this->pMutex) {
        }
        else {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        
        entrySize += entryDataSize;
        entrySize = ROUNDUP4(entrySize);
        if (entrySize > (64 * 1024)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        blockSize =  sizeof(TABLE_BLOCK) + (entrySize * entriesPerBlock);
        if (blockSize > (64 * 1024)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        this->entriesPerBlock = entriesPerBlock;
        this->entryDataSize = entryDataSize;
        this->entrySize = entrySize;
        this->blockSize = blockSize;
        
        // Initialize the fields.
        obj_FlagSet(this, TABLE_FLAG_FIXED, fFixed);
        
        listdl_Init( &this->blockList,  offsetof(TABLE_BLOCK, node) );
        listdl_Init( &this->activeList, offsetof(TABLE_ENTRY, node) );
        listdl_Init( &this->freeList,   offsetof(TABLE_ENTRY, node) );

        // Return to caller.
        return this;
    }



    //---------------------------------------------------------------
    //                          L o c k
    //---------------------------------------------------------------
    
    void            table_Lock(
        TABLE_DATA      *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        fRc = psxMutex_Lock(this->pMutex);
        if (fRc) {
        }
        else {
            // Why?
            DEBUG_BREAK();
        }
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                    M o v e  B e f o r e
    //---------------------------------------------------------------
    
    bool            table_MoveBefore(
        TABLE_DATA      *this,
        void            *pData1,
        void            *pData2
    )
    {
        TABLE_ENTRY     *pWork;
        TABLE_ENTRY     *pNode1 = Ptr2Entry(pData1);
        TABLE_ENTRY     *pNode2 = Ptr2Entry(pData2);
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
        if (NULL == pData1) {
            return false;
        }
        if (!listdl_Contains(&this->activeList, pNode1)) {
            return false;
        }
        if (NULL == pData2) {
            return false;
        }
        if (!listdl_Contains(&this->activeList, pNode2)) {
            return false;
        }
#endif
        
        fRc = listdl_Delete(&this->activeList,pNode2);
        if (!fRc) {
            return false;
        }
        pWork = listdl_AddBefore(&this->activeList, pNode1, pNode2);
        
        // Return to caller.
        return( pWork ? true : false );
    }
    
    
    
    
    //---------------------------------------------------------------
    //                          N e x t
    //---------------------------------------------------------------
    
    void *          table_Next(
        TABLE_DATA      *this,
        void            *pData
    )
    {
        TABLE_ENTRY     *pWork;
        TABLE_ENTRY     *pNode = Ptr2Entry(pData);
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
        if (NULL == pData) {
            return NULL;
        }
        if (!listdl_Contains(&this->activeList, pNode)) {
            return NULL;
        }
#endif
        
        pWork = listdl_Next(&this->activeList,pNode);
        
        // Return to caller.
        return( pWork ? Entry2Ptr(pWork) : pWork );
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    ASTR_DATA *     table_ToDebugString(
        TABLE_DATA      *this,
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
                     "{%p(table) ",
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
        
        j = snprintf( str, sizeof(str), " %p}\n", this );
        AStr_AppendA(pStr, str);
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                          U n l o c k
    //---------------------------------------------------------------
    
    void            table_Unlock(
        TABLE_DATA      *this
    )
    {
        bool            fRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !table_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        fRc = psxMutex_Unlock(this->pMutex);
        if (fRc) {
        }
        else {
            // Why?
            DEBUG_BREAK();
        }
        
        // Return to caller.
    }
    
    
    
    //---------------------------------------------------------------
    //                    V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool			table_Validate(
        TABLE_DATA      *this
    )
    {
        
        // Do initialization.
        if(this) {
            this->eRc = ERESULT_INVALID_OBJECT;
            if ( obj_IsKindOf(this,OBJ_IDENT_TABLE) )
                ;
            else
                return false;
        }
        else
            return false;
        if( (obj_getSize(this) < sizeof(TABLE_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }
        
        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
#endif



    ERESULT         table_VisitAscending(
        TABLE_DATA      *this,
        void            (pVisitor)(
                                OBJ_ID,              // Object supplied below
                                void *               // Current Entry
                        ),
        OBJ_ID          pObject
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        TABLE_ENTRY     *pNode;
        
        pNode=listdl_Head(&this->activeList);
        while (pNode) {
            pVisitor(pObject, Entry2Ptr(pNode));
            pNode = listdl_Next(&this->activeList, pNode);
        }
        
        this->eRc = eRc;
        return eRc;
    }
    
    


