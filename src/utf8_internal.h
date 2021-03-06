// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   utf8_internal.h
 *	Generated 08/06/2015 20:23:35
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




#include    <utf8.h>
#include    <AStr.h>
#include    <JsonIn.h>



#ifndef UTF8_INTERNAL_H
#define	UTF8_INTERNAL_H


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct utf8_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    uint16_t        size;		/* maximum number of elements           */
    uint16_t        reserved;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    UTF8_VTBL       utf8_Vtbl;



    // Internal Functions
    void            utf8_Dealloc(
        OBJ_ID          objId
    );

    
    void            utf8_Int64ToChrClean(
        int64_t         num,
        char            *pBuffer
    );
    
    
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new UTF-8 String if successful, otherwise, NULL
     @warning   Returned UTF-8 string must be freed using mem_Free().
     */
    uint8_t *       utf8_ParseJsonObject(
        JSONIN_DATA     *pParser,
        uint32_t        *pLength
    );
    
    
#ifdef NDEBUG
#else
    bool			utf8_Validate(
        UTF8_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* UTF8_INTERNAL_H */

