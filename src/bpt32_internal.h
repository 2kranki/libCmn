// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   bpt32_internal.h
 *	Generated 01/12/2019 14:04:44
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




#include        <bpt32.h>
#include        <bpt32idx_internal.h>
#include        <bpt32lf_internal.h>
#include        <jsonIn.h>


#ifndef BPT32_INTERNAL_H
#define	BPT32_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif



#pragma pack(push, 1)
    typedef struct  bpt32idx_header_s {
        uint16_t        dataSize;       // Size of Data in node
        uint32_t        blockSize;
        uint32_t        numRcds;        // Number of Records in File
        uint32_t        root;           // Root Record Index
        uint32_t        dataHead;
        uint32_t        dataTail;
    } BPT32_HEADER;
#pragma pack(pop)
    
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct bpt32_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    uint16_t        dataSize;       // Size of Data in node
    uint32_t        blockSize;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct bpt32_class_data_s  bpt32_ClassObj;

    extern
    const
    BPT32_VTBL         bpt32_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BPT32_SINGLETON
    BPT32_DATA *     bpt32_getSingleton (
        void
    );

    bool            bpt32_setSingleton (
     BPT32_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  bpt32_getSuperVtbl (
        BPT32_DATA     *this
    );


    void            bpt32_Dealloc (
        OBJ_ID          objId
    );


    BPT32_DATA *       bpt32_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          bpt32_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     bpt32_ToJSON (
        BPT32_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			bpt32_Validate (
        BPT32_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BPT32_INTERNAL_H */

