// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SRecords_internal.h
 *	Generated 11/22/2017 13:10:45
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




#include    <SRecords.h>
#include    <srcFile.h>


#ifndef SRECORDS_INTERNAL_H
#define	SRECORDS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif

    typedef enum fsm_action_e {
        FSM_ACTION_UNKNOWN=0,
        FSM_ACTION_SKIP_LEADING_WS,
        FSM_ACTION_READ_CHAR,
        FSM_ACTION_ADD_CHECKSUM,
        FSM_ACTION_CHECK_CHECKSUM,
        FSM_ACTION_STORE_RECORD_LENGTH,
        FSM_ACTION_ZERO_DATA_INDEX,
        FSM_ACTION_STORE_DATA,
        FSM_ACTION_INCREASE_DATA_INDEX,
        FSM_ACTION_COMPLETION,
    } FSM_ACTION;

    typedef enum fsm_state_e {
        FSM_STATE_UNKNOWN=0,
        FSM_STATE_START=1,
        FSM_STATE_FINISH=1,
        FSM_STATE_SKIP_LEADING_WS,
        FSM_STATE_READ_ADDR_1_1,
        FSM_STATE_READ_ADDR_1_2,
        FSM_STATE_READ_ADDR_2_1,
        FSM_STATE_READ_ADDR_2_2,
        FSM_STATE_READ_ADDR_3_1,
        FSM_STATE_READ_ADDR_3_2,
        FSM_STATE_READ_ADDR_4_1,
        FSM_STATE_READ_ADDR_4_2,
        FSM_STATE_READ_DATA_1,
        FSM_STATE_READ_DATA_2,
        FSM_STATE_READ_CHECKSUM_1,
        FSM_STATE_READ_CHECKSUM_2,
    } FSM_STATE;
    

    
    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct SRecords_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        size;		/* maximum number of elements           */
    uint16_t        reserved;
    ASTR_DATA       *pStr;
    SRCFILE_DATA    *pSrc;
    uint32_t        startAddr;
    uint8_t         *pAddrBase;
    uint8_t         *pAddrCur;

};
#pragma pack(pop)

    extern
    const
    struct SRecords_class_data_s  SRecords_ClassObj;

    extern
    const
    SRECORDS_VTBL       SRecords_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            SRecords_setLastError(
        SRECORDS_DATA   *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  SRecords_getSuperVtbl(
        SRECORDS_DATA   *this
    );


    void            SRecords_Dealloc(
        OBJ_ID          objId
    );


    void *          SRecords_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     SRecords_ToJSON(
        SRECORDS_DATA   *this
    );




#ifdef NDEBUG
#else
    bool			SRecords_Validate(
        SRECORDS_DATA   *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRECORDS_INTERNAL_H */

