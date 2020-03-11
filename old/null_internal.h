// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   null_internal.h
 *	Generated 11/12/2015 10:20:43
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




#ifndef NULL_INTERNAL_H
#define	NULL_INTERNAL_H


#include    <null.h>
#include    <JsonIn.h>
#include    <NodeHash.h>



#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct null_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

};
#pragma pack(pop)

    extern
    const
    NULL_VTBL       null_Vtbl;



    // Internal Functions
    OBJ_ID          null_Class(
        void
    );
    
    
    NULL_DATA *     null_NewFromHash(
        NODEHASH_DATA   *pHash
    );
    
    
    void            null_Dealloc(
        OBJ_ID          objId
    );

    
    NULL_DATA *     null_ParseObject(
        JSONIN_DATA     *pParser
    );
    
    
    void *          null_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			null_Validate(
        NULL_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NULL_INTERNAL_H */

