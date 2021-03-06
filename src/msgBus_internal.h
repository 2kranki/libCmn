// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   msgBus_internal.h
 *	Generated 05/31/2017 20:00:00
 *
 * Notes:
 *  --	We use the node data property to hold the receiver object and
 *      the misc field to hold the offset of the method in the vtbl.
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




#include    <msgBus.h>
#include    <MsgData.h>
#include    <ObjCb.h>
#include    <Node.h>
#include    <NodeArray.h>
#include    <psxLock.h>
#include    <psxMutex.h>
#include    <psxSem.h>
#include    <psxThread.h>



#ifndef MSGBUS_INTERNAL_H
#define	MSGBUS_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct msgBus_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    PSXLOCK_DATA    *pLock;
    NODEARRAY_DATA  *pRegistry;
    PSXTHREAD_DATA  *pThread;
    OBJCB_DATA      *pBuffer;
    volatile
    uint32_t        msWait;
    volatile
    uint16_t        actualSize;
    uint16_t        rsvd16;
    volatile
    int32_t         unique;
    uint32_t        rsvd32;

};
#pragma pack(pop)

    extern
    const
    struct msgBus_class_data_s  msgBus_ClassObj;

    extern
    const
    MSGBUS_VTBL         msgBus_Vtbl;


    // Internal Functions
    void            msgBus_Dealloc(
        OBJ_ID          objId
    );

    void *          msgBus_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );





#ifdef NDEBUG
#else
    bool			msgBus_Validate(
        MSGBUS_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MSGBUS_INTERNAL_H */

