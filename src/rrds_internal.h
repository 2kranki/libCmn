// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   rrds_internal.h
 *	Generated 01/05/2019 23:32:39
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




#include        <rrds.h>
#include        <fileio.h>
#include        <JsonIn.h>
#include        <lru_internal.h>


#ifndef RRDS_INTERNAL_H
#define	RRDS_INTERNAL_H



#define     PROPERTY_IO_OWNED   1
#define     PROPERTY_STR_OWNED  1



#ifdef	__cplusplus
extern "C" {
#endif


    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct rrds_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    LRU_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    // OBJ_FLAG_USER1 is used in LRU

    // Common Data
    FILEIO_DATA     *pIO;
    uint16_t        recordSize;     // Real Record Size including Record Terminators
    uint16_t        reqSize;        // Requested Record Size without optional
    //                              // terminators included
    uint16_t        cLRU;
    uint16_t        cHash;
    uint8_t         recordTerm;     // Record Terminator (see rcd_trm_e)
    uint8_t         fillChar;
    uint8_t         rsvd8[2];
    uint32_t        cRecords;

};
#pragma pack(pop)

    extern
    struct rrds_class_data_s  rrds_ClassObj;

    extern
    const
    RRDS_VTBL         rrds_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RRDS_SINGLETON
    RRDS_DATA *   rrds_getSingleton (
        void
    );

    bool            rrds_setSingleton (
     RRDS_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            rrds_setIO (
        RRDS_DATA       *this,
        OBJ_ID          pValue
    );
    
    
    OBJ_IUNKNOWN *  rrds_getSuperVtbl (
        RRDS_DATA       *this
    );


    void            rrds_Dealloc (
        OBJ_ID          objId
    );


    RRDS_DATA *     rrds_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          rrds_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         rrds_Setup (
        RRDS_DATA       *this
    );
    
    


#ifdef NDEBUG
#else
    bool			rrds_Validate (
        RRDS_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* RRDS_INTERNAL_H */

