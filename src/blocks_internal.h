// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   blocks_internal.h
 *	Generated 09/04/2016 13:13:56
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



#include    <blocks.h>
#include    <listdl.h>


#ifndef BLOCKS_INTERNAL_H
#define	BLOCKS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


    //                  Block
    // A block is consists of multiple entries.
    typedef struct blocks_block_s BLOCKS_BLOCK;
    struct blocks_block_s {
        LISTDL_NODE         node;           // Chain for block list
        uint8_t             data[0];
    };
    
    


//#pragma pack(push, 1)
struct blocks_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    LISTDL_DATA     blockList;
    uint32_t        blockSize;

};
//#pragma pack(pop)

    extern
    const
    struct blocks_class_data_s  blocks_ClassObj;

    extern
    const
    BLOCKS_VTBL         blocks_Vtbl;


    // Internal Functions
    void            blocks_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			blocks_Validate(
        BLOCKS_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLOCKS_INTERNAL_H */

