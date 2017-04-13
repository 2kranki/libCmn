/* 
 * File:   cmn_msc.c
 * Author: bob
 *
 * Created on September 26, 2014, 3:40 PM
 */

#include        "cmn_defs.h"
#include        <assert.h>
#include        <stdbool.h>
#include        <sys/types.h>
#include        <unistd.h>
#include        <sys/sysctl.h>

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


//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

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





/****************************************************************
* * * * * * * * * * *  Function Definitions   * * * * * * * * * *
****************************************************************/

//===============================================================
//                    P r o p e r t i e s
//===============================================================

//===============================================================
//                    M e t h o d s
//===============================================================









