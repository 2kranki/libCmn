// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   msgData_internal.h
 *	Generated 11/04/2017 09:37:49
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




#include    <msgData.h>


#ifndef MSGDATA_INTERNAL_H
#define	MSGDATA_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct msgData_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint32_t        origin;         // Origin Number
    uint32_t        dest;           // Destination Number (0 == general broadcast)
    uint32_t        num32;          // 
    uint16_t        size;		    // Message Size
    uint16_t        reserved;
    uint8_t         data[0];

};
#pragma pack(pop)

    extern
    const
    struct msgData_class_data_s  msgData_ClassObj;

    extern
    const
    MSGDATA_VTBL         msgData_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            msgData_setLastError(
        MSGDATA_DATA     *this,
        ERESULT         value
    );


    void            msgData_Dealloc(
        OBJ_ID          objId
    );


    void *          msgData_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     msgData_ToJSON(
        MSGDATA_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			msgData_Validate(
        MSGDATA_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MSGDATA_INTERNAL_H */

