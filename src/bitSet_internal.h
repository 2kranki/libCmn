// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BitSet_internal.h
 *	Generated 12/18/2019 08:00:17
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




#include        <BitSet.h>
#include        <JsonIn.h>
#include        <array_internal.h>


#ifndef BITSET_INTERNAL_H
#define	BITSET_INTERNAL_H



#define     PROPERTY_DATA_OWNED     1
#define     BITS_PER_UNIT           32          // 4 byte unit



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BitSet_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ARRAY_DATA      *pData;
    uint32_t        cBits;

};
#pragma pack(pop)

    extern
    struct BitSet_class_data_s  BitSet_ClassObj;

    extern
    const
    BITSET_VTBL     BitSet_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BITSET_SINGLETON
    BITSET_DATA *   BitSet_getSingleton (
        void
    );

    bool            BitSet_setSingleton (
     BITSET_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  BitSet_getSuperVtbl (
        BITSET_DATA     *this
    );


    void            BitSet_Dealloc (
        OBJ_ID          objId
    );


#ifdef  BITSET_JSON_SUPPORT
    BITSET_DATA *   BitSet_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          BitSet_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     BitSet_ToJson (
        BITSET_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			BitSet_Validate (
        BITSET_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BITSET_INTERNAL_H */

