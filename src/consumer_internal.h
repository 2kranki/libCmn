// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   consumer_internal.h
 *	Generated 06/29/2016 10:31:45
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



#include    <consumer.h>
#include    <psxMutex.h>
#include    <psxSem.h>
#include    <psxThread.h>



#ifndef CONSUMER_INTERNAL_H
#define	CONSUMER_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct consumer_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    PSXSEM_DATA     *pSemEmpty;
    PSXSEM_DATA     *pSemFull;
    PSXMUTEX_DATA   *pMutex;
    PSXTHREAD_DATA  *pThread;
    
    uint16_t        szDQueBuf;          // Buffer/Msg Size
    uint16_t        cDQueBufs;          // Number of Buffers/Msgs in Queue
    uint8_t         *pData;             // The buffers and index are here.
    uint32_t        *pDQueBufs;         // Points into data[0] below
    uint32_t        **ppDQueBufs;       // Points into data[0] below

    uint16_t        size;               // maximum number of elements
    uint16_t        reserved;

};
#pragma pack(pop)

    extern
    const
    struct consumer_class_data_s	consumer_ClassObj;

    extern
    const
    CONSUMER_VTBL         consumer_Vtbl;


    // Internal Functions
    void            consumer_Dealloc(
        OBJ_ID          objId
    );



#ifdef NDEBUG
#else
    bool			consumer_Validate(
        CONSUMER_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CONSUMER_INTERNAL_H */

