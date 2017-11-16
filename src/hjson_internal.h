// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   hjson_internal.h
 *	Generated 07/08/2017 17:18:30
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




#include    <hjson.h>
#include    <lexj.h>


#ifndef HJSON_INTERNAL_H
#define	HJSON_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct hjson_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    //PATH_DATA       *pPath;
    LEXJ_DATA       *pLexJ;
    NODEHASH_DATA   *pFileObject;
    uint16_t        tabSize;
    uint16_t        rsvd16;

};
#pragma pack(pop)

    extern
    const
    struct hjson_class_data_s  hjson_ClassObj;

    extern
    const
    HJSON_VTBL         hjson_Vtbl;


    // Internal Functions
    void            hjson_Dealloc(
        OBJ_ID          objId
    );

    HJSON_DATA *    hjson_Init(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseArray(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseFileObject(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseHash(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseKeyWord(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseName(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseNumber(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParsePair(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseString(
        HJSON_DATA      *this
    );
    
    
    NODE_DATA *     hjson_ParseValue(
        HJSON_DATA      *this
    );
    
    
    void *          hjson_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    bool            hjson_setLastError(
        HJSON_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			hjson_Validate(
        HJSON_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* HJSON_INTERNAL_H */

