// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   block16_internal.h
 *	Generated 01/05/2016 07:38:50
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


#include    <block16.h>



#ifndef BLOCK16_INTERNAL_H
#define	BLOCK16_INTERNAL_H 1


#ifdef	__cplusplus
extern "C" {
#endif


    // In C, "long" is defined to be the word size of the computer
    // where "int" might be shorter.
//#define WORDSIZE sizeof(long)   /* word size in bytes */
//#define WORDSIZE 4              /* word size in bytes */
//#define ROUNDUP_WORD(x) (((x + WORDSIZE - 1) / WORDSIZE) * WORDSIZE)
    
    
    /* Main Control block */
    /* This control block resides only in memory and is used to provide
     * the information necessary to access the block data.
     */
    
#pragma pack(push, 1)
typedef struct blocked16_data_s {
        // With pack(1), we must be careful that the user and data are
        // on a word boundary.
        uint16_t			cbSize;         // Total Block Size
        uint16_t            headerSize;     // Header Data Size
        uint16_t            dataSize;       // Data Size
        uint16_t            dataUsed;       // Amount of Data Size Used
        uint8_t             header[0];
        // This block consists of an optional header data area to be used
        // as needed followed by the actual block data. The header data
        // size and data size are always rounded up to the nearest word.
        // Both the areas are simply considered an array of bytes and
        // treated as such. The header is a fixed amount and the data can
        // can be a variable amount.
} BLOCKED16_DATA;
#pragma pack(pop)
    
    
    
    
#pragma pack(push, 1)
struct block16_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    ERESULT         eRc;
    BLOCKED16_DATA  *pBlock;

};
#pragma pack(pop)

    extern
    const
    struct block16_class_data_s  block16_ClassObj;
    
    extern
    const
    BLOCK16_VTBL    block16_Vtbl;



    // Internal Functions
    bool            block16_setBlock(
        BLOCK16_DATA    *this,
        void            *pValue
    );
    
    
    void            block16_Dealloc(
        OBJ_ID          objId
    );

    
#ifdef NDEBUG
#else
    bool			block16_Validate(
        BLOCK16_DATA    *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLOCK16_INTERNAL_H */

