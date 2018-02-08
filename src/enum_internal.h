// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   enum_internal.h
 *	Generated 06/30/2017 09:01:13
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




#include    <enum.h>
#include    <array.h>


#ifndef ENUM_INTERNAL_H
#define	ENUM_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //      Node Descriptor
#pragma pack(push, 1)
    typedef struct  enum_node_s {
        const
        char            *pszKey;
        uint32_t        index;
    } ENUM_NODE;
#pragma pack(pop)
    
    
#pragma pack(push, 1)
struct enum_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
    #define ENUM_FREE_ARRAY OBJ_FLAG_USER1         

    // Common Data
    ERESULT         eRc;
    
    uint32_t        max;                // Total size of ppArray
    uint32_t        size;               // Number of elements in use in ppArray
    uint32_t        current;            // Current element index
    uint8_t         **ppArray;

};
#pragma pack(pop)

    extern
    const
    struct enum_class_data_s  enum_ClassObj;

    extern
    const
    ENUM_VTBL         enum_Vtbl;


    // Internal Functions
    ERESULT         enum_Append(
        ENUM_DATA       *this,
        void            *pObject,
        uint32_t        *pIndex
    );
    
    
    void            enum_Dealloc(
        OBJ_ID          objId
    );

    
    void *          enum_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    bool            enum_setLastError(
        ENUM_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			enum_Validate(
        ENUM_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* ENUM_INTERNAL_H */

