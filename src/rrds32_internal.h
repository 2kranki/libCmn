// vi:nu:et:sts=4 ts=4 sw=4

/*
 * File:   rrds_internal.h
 *
 * Created on September 26, 2014, 3:39 PM
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




#include    <rrds32.h>
#include    <AStr.h>
#include    <fileio.h>
#include    <lru.h>
#include    <listdl.h>


#ifndef RRDS32_INTERNAL_H
#define	RRDS32_INTERNAL_H  1




#ifdef	__cplusplus
extern "C" {
#endif
    

#define RRDS32_HEADER_SIZE 4096
    
    
    /*                      File Header
     */
    /* This control block resides at the beginning of the file  and is
     * used to provide the information necessary to access the file as
     * well as .
     * Never put pointers or data that should not be saved to a file
     * in this struct.
     */
    typedef struct rrds32_header_s RRDS32_HEADER;
    
#pragma pack(push, 1)
    struct rrds32_header_s {
        uint16_t        cbSize;
        uint16_t        cbFlags;
        uint32_t        cbIdent;        /* Identifier - rrds */
        #define RRDS32_HEADER_IDENTIFIER (('r' << 24)+('r' << 16)+('d'<<8)+'d')

        /* General Variables
        */
        uint32_t        recordNum;      /* Number of Records in the file */
        uint16_t        recordSize;
        char            fillChar;       /* New Block Fill Character */
        char            rsvd;
        uint8_t         userData[0];
    };
#pragma pack(pop)
    
    
    
    
    
#pragma pack(push, 1)
struct rrds32_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    FILEIO_DATA     *pIO;
    LRU_DATA        *pLRU;
    uint32_t        size;           // Maximum Number of Entries
	uint32_t        headerSize;     // Header Length
    RRDS32_HEADER   *pHeader;

};
#pragma pack(pop)




    extern
    const
    RRDS32_VTBL     rrds32_Vtbl;
    
    
    
    // Internal Functions
    void            rrds_Dealloc(
        OBJ_ID          objId
    );


    void *          rrds32_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool            rrds32_Validate(
        RRDS32_DATA     *this
    );
#endif
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* RRDS_INTERNAL_H */

