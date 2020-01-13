// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   crc_internal.h
 *	Generated 07/25/2017 10:42:33
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




#include    <crc.h>


#ifndef CRC_INTERNAL_H
#define	CRC_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct crc_def_s {
        char        *pDesc;
        uint32_t    width;              // Number of bits (generally 16 or 32)
        uint32_t    poly;               // The algorithm's polynomial
        uint32_t    init;               // Initial CRC register value
        uint16_t    fRefIn;             // Reflect input bytes
        uint16_t    fRefOut;            // Reflect output CRC
        uint32_t    xorout;             // XOR this to output CRC
        uint32_t    check;              // checksum of "123456789"
    } CRC_DEF;



#pragma pack(push, 1)
struct crc_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint32_t		type;				// Type of CRC (See rmwCrcType)
    uint32_t		crc;                // CRC Value
    uint32_t        topbit;             // Highest bit
    uint32_t        crcMask;            // CRC Mask
    uint32_t		*pCrc32Table;		// 32-Bit CRC Table
    CRC_DEF         *pDef;

};
#pragma pack(pop)

    extern
    const
    struct crc_class_data_s  crc_ClassObj;

    extern
    const
    CRC_VTBL         crc_Vtbl;


    // Internal Functions
    void            crc_Dealloc(
        OBJ_ID          objId
    );

    void *          crc_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    uint32_t        crc_Reflect(
        uint32_t        v,
        int             cBits
    );
    
    
    bool            crc_setLastError(
        CRC_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			crc_Validate(
        CRC_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CRC_INTERNAL_H */

