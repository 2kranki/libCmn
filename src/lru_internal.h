// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   lru_internal.h
 *	Generated 10/21/2016 23:23:20
 *
 * Notes:
 *  --	N/A
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



#include    <lru.h>
#include    <listdl.h>


#ifndef LRU_INTERNAL_H
#define	LRU_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif

    
#define NUM_HASH_LIST   23          /* Should be a xx number */


#pragma pack(push, 1)
    typedef struct lru_sector_s	{
        LISTDL_NODE     lruList;
        LISTDL_NODE     hashList;
        uint32_t        lsn;                // Logical Sector Number
        uint8_t         data[0];
    } LRU_SECTOR;
#pragma pack(pop)
    
    
    

#pragma pack(push, 1)
struct lru_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint32_t        sectorSize;
    uint32_t        cacheSize;
    
    ERESULT         (*pLogicalRead)(
        OBJ_ID          pObj,
        uint32_t        lsn,                // Logical Sector Number
        uint8_t         *pBuffer            // Buffer of sectorSize bytes
    );
    OBJ_ID          pReadObject;
    
    ERESULT         (*pLogicalWrite)(
        OBJ_ID          pWriteObject,
        uint32_t        lsn,                // Logical Sector Number
        uint8_t         *pBuffer            // Buffer of sectorSize bytes
    );
    OBJ_ID          pWriteObject;

    volatile
    int32_t         numReads;
    volatile
    int32_t         numWrites;

    LISTDL_DATA     freeList;
    LISTDL_DATA     lruList;
    LISTDL_DATA     hashLists[NUM_HASH_LIST];
};
#pragma pack(pop)

    extern
    const
    struct lru_class_data_s  lru_ClassObj;

    extern
    const
    LRU_VTBL         lru_Vtbl;


    // Internal Functions
    void            lru_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			lru_Validate(
        LRU_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* LRU_INTERNAL_H */

