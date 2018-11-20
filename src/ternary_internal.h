// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ternary_internal.h
 *	Generated 09/19/2015 00:10:38
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




#ifndef TERNARY_INTERNAL_H
#define	TERNARY_INTERNAL_H


#include    "ternary.h"
#include    "blocks_internal.h"

#ifdef	__cplusplus
extern "C" {
#endif


    typedef struct  ternary_node_s TERNARY_NODE;
    struct          ternary_node_s {
        TERNARY_NODE    *pLow;
        union {
            TERNARY_NODE    *pEqual;
            void            *pData;
        };
        TERNARY_NODE    *pHigh;
        uint32_t        chr;
    };
    
    
    
    
#pragma pack(push, 1)
struct ternary_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;
#define TERNARY_FLAG_OBJECT    OBJ_FLAG_USER1        /* Data is an object */

    // Common Data
    ERESULT         eRc;
    
    // Tree Variables
    TERNARY_NODE    *pRoot;             // Root of Ternary Node Tree
    uint32_t		cTreeNum;           // Current Number of Entries
    uint32_t        maxKeyLen;
    
};
#pragma pack(pop)

    extern
    const
    TERNARY_VTBL    ternary_Vtbl;



    // Internal Functions
    void            ternary_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			ternary_Validate(
        TERNARY_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* TERNARY_INTERNAL_H */

