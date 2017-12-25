// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   srcLoc_internal.h
 *	Generated 01/01/2016 08:01:11
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




#ifndef SRCLOC_INTERNAL_H
#define	SRCLOC_INTERNAL_H


#include    <srcLoc.h>
#include    <jsonIn.h>



#ifdef	__cplusplus
extern "C" {
#endif


    
#pragma pack(push, 1)
struct srcLoc_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
#define SRCLOC_FLAG_ALLOC       OBJ_FLAG_USER1  // We allocated token data

    // Common Data
    SRCLOC          *pData;
    // NOTE -- Do NOT declare any variables here, put them above "data".
};
#pragma pack(pop)

    extern
    const
    OBJ_IUNKNOWN    srcLoc_Vtbl;



    // Internal Functions
    bool            srcLoc_setSrc(
        SRCLOC_DATA     *this,
        SRCLOC          *pValue
    );
    
    
    void            srcLoc_Dealloc(
        OBJ_ID          objId
    );


    SRCLOC_DATA *   srcLoc_ParseObject(
        JSONIN_DATA     *pParser
    );
    
    
    void *          srcLoc_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			srcLoc_Validate(
        SRCLOC_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRCLOC_INTERNAL_H */

