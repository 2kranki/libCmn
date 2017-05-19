// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   table_internal.h
 * Author: bob
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *
 * Created on September 26, 2014, 3:39 PM
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





#ifndef TABLE_INTERNAL_H
#define	TABLE_INTERNAL_H


#include    <table.h>
#include    <AStr.h>
#include    <listdl.h>
#include    <psxMutex.h>



#ifdef	__cplusplus
extern "C" {
#endif


    
    //                  Entry
    // An entry block is simply an occurrence of a block.
    typedef struct table_entry_s TABLE_ENTRY;
    struct table_entry_s {
        LISTDL_NODE         node;           // Chain for active or free list
        uint8_t             data[0];
    };
    
    
    //                  Block
    // A block is consists of multiple entries.
    typedef struct table_block_s TABLE_BLOCK;
    struct table_block_s {
        LISTDL_NODE         node;           // Chain for block list
        uint8_t             data[0];
        //TABLE_ENTRY         data[0];  // MSC gets C2233 if we use this.
    };
    
    
    //              Control Block
    /* This control block resides only in memory and is used to provide
     * the information necessary to access the table data.
     */
    struct table_data_s {
        /* Warning - OBJ_DATA must be first in this object!
         */
        OBJ_DATA            super;
        OBJ_IUNKNOWN        *pSuperVtbl;
#define TABLE_FLAG_FIXED    5

        ERESULT             eRc;

        /* Table General Variables
         */
        uint16_t            entriesPerBlock;    // Number of Entries per Table Block
        uint16_t            entryDataSize;      // Entry Data Size
        uint16_t            entrySize;          // Total Entry Size including Data
        uint16_t            blockSize;
        
        /* Table Entry List/Chain Variables
         */
        LISTDL_DATA         blockList;
        LISTDL_DATA         activeList;         
        LISTDL_DATA         freeList;
        uint16_t            numEntries;         // Total Number of Table Entries
        uint16_t            reserved;
        
        PSXMUTEX_DATA       *pMutex;
        
    };
    
    
    extern
    const
    TABLE_VTBL      table_Vtbl;
    
    extern
    const
    struct table_class_data_s table_ClassObj;

    


    /****************************************************************
     * * * * * * *  Internal Function Definitions * * * * * * * * * *
     ****************************************************************/
    
    void            table_Dealloc(
        OBJ_ID          objId
    );
    
    
    void *			table_UnusedDataPtr(
        TABLE_DATA		*
    );
    
#ifdef NDEBUG
#else
    bool            table_Validate(
        TABLE_DATA      *cbp
    );
#endif
    
    


#ifdef	__cplusplus
}
#endif

#endif	/* TABLE_INTERNAL_H */

