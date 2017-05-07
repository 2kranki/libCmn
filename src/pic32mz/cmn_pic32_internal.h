// vi:nu:et:sts=4 ts=4 sw=4 tw=90
/* 
 * File:   cmn_internal.h
 * Author: bob
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
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




#ifndef CMN_PIC32_INTERNAL_H
#define	CMN_PIC32_INTERNAL_H


#include    "cmn.h"


#ifdef	__cplusplus
extern "C" {
#endif


#define _IFS0_CTIF_POSITION                      0x00000000
#define _IFS0_CTIF_MASK                          0x00000001
#define _IFS0_CTIF_LENGTH                        0x00000001
    
#define _IEC0_CTIE_POSITION                      0x00000000
#define _IEC0_CTIE_MASK                          0x00000001
#define _IEC0_CTIE_LENGTH                        0x00000001
    
#define _IPC0_CTIS_POSITION                      0x00000000
#define _IPC0_CTIS_MASK                          0x00000003
#define _IPC0_CTIS_LENGTH                        0x00000002
    
#define _IPC0_CTIP_POSITION                      0x00000002
#define _IPC0_CTIP_MASK                          0x0000001C
#define _IPC0_CTIP_LENGTH                        0x00000003
    



typedef struct cmn_entry_s {

    //TODO: Needs updating

    // Interrupt Priorities
    uint32_t        priority;
    uint32_t        subpriority;
    uint32_t        *ipc;
    uint32_t        *ipcClr;
    uint32_t        *ipcSet;
    uint32_t        priorityPosition;
    uint32_t        priorityMask;
    uint32_t        subpriorityPosition;
    uint32_t        subpriorityMask;

    // Interrupt Flag
    uint32_t        *ifs;
    uint32_t        *ifsClr;
    uint32_t        *ifsSet;
    uint32_t        irqflg;

    // Interrupt Enable
    uint32_t        *iec;
    uint32_t        *iecClr;
    uint32_t        *iecSet;
    uint32_t        intflg;

} CMN_ENTRY;



struct cmn_data_s	{
    uint32_t        cbSize;
    uint32_t        identifier;
#define CMN_IDENTIFIER (('c' << 24)+('m' << 16)+('n'<<8)+' ')

    // Common Data
    const
    CMN_ENTRY       *utp;
    
    CFG_DATA        *pCfg;
    CON_DATA        *pCon;
    CT_DATA         *pCt;
    DMA_DATA        *pDma;
    MON_DATA        *pMon;
    OSC_DATA        *pOsc;
    TIMER_DATA      *pTimer1;
    UART_DATA       *pUart2;
    void            *pUser1;
    void            *pUser2;

};




// Internal Functions

    


#ifdef	__cplusplus
}
#endif

#endif	/* CMN_PIC32_INTERNAL_H */

