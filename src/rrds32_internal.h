// vi:nu:et:sts=4 ts=4 sw=4

/*
 * File:   rrds_internal.h
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




#include    <rrds32.h>
#include    <AStr.h>
#include    <hash32_internal.h>
#include    <lru_internal.h>
#include    <listdl.h>


#ifndef RRDS32_INTERNAL_H
#define	RRDS32_INTERNAL_H  1




#ifdef	__cplusplus
extern "C" {
#endif
    

    //                      LRU Buffer Header
    /* This control block resides at the beginning of each buffer element
     * to provide the overhead fields needed.  Each element is maintained
     * on two lists.  The first is the Hash Chain list which offers quick
     * access to each active element based on their index number.  The
     * second is an LRU list which maintains all active elements ordered
     * by last access.  That is, the most recent accessed will be at the
     * top of the list.
     */
    typedef struct lru_entry_s {
        LISTDL_NODE     lru;                /* LRU chain */
        //LISTDL_NODE     hash;               /* HASH chain */
        uint32_t        key;                // Buffer Number
        uint16_t        flags;              /* Flags */
#define     LRU_DIRTY   0x8000                  // Buffer has been altered
#define     LRU_FIX     0x4000                  // Buffer is fixed in memory
                                                // and not on the LRU Chain
        uint16_t        rsvd;
        uint8_t         *pBuffer;
    } LRU_ENTRY;
    
    
    
#define RRDS32_HEADER_SIZE 1024
    
    
    /*                      File Header
     */
    /* This control block resides at the beginning of the file  and is
     * used to provide the information necessary to access the file as
     * well as .
     * Never put pointers or data that should not be saved to a file
     * in this struct.
     */
    typedef struct rrds32_header_s RRDS32_HEADER;
    
#pragma pack(push, 1)
    struct rrds32_header_s {
        union {
            struct {
                uint16_t        cbSize;
                uint16_t        cbFlags;
                uint32_t        cbIdent;        /* Identifier - rrdsh */
#define RRDS32_HEADER_IDENTIFIER (('f' << 24)+('b' << 16)+('r'<<8)+'h')
                
                /* General Variables
                 */
                uint32_t        recordNum;      /* Number of Records in the file */
                uint16_t        recordSize;
                char            fillChar;       /* New Block Fill Character */
                char            rsvd;
                uint8_t         userData[0];
            } data;
            struct {
                uint8_t         bytes[RRDS32_HEADER_SIZE];
            };
        };
    };
#pragma pack(pop)
    
    
    
    
    
#pragma pack(push, 1)
struct rrds32_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    int             fileHandle;
    char            *pFilePath;
    uint32_t         size;           // Maximum Number of Entries
    LISTDL_DATA     lruFree;        // LRU Free Chain (contains unused buffers)
    LISTDL_DATA     lru;            // LRU Chain (contains active buffers)
    HASH32_DATA     *pHash;         // HASH32 Chain (contains All buffers)
    uint16_t        cLru;           // Number of entries used in the LRU Table
    uint16_t        cBuffers;
    uint8_t         *pBuffers;
	uint32_t        recordNum;      // Number of Records in the Dataset
	uint16_t        recordSize;     // Block Size
	uint16_t        hearderSize;    // Header Length
    RRDS32_HEADER   header;
    LRU_ENTRY       *pLruTable;     // cBuffer number of Entries
    ERESULT         eRc;

};
#pragma pack(pop)




    extern
    const
    RRDS32_VTBL     rrds32_Vtbl;
    
    
    
    // Internal Functions
#ifdef RMW_DEBUG
    bool			rrds32_Validate(
        RRDS32_DATA     *this
    );
#endif

    void            rrds_Dealloc(
        OBJ_ID          objId
    );


#ifdef	__cplusplus
}
#endif

#endif	/* RRDS_INTERNAL_H */

