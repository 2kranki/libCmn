// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   cmnMac64.c
 * Author: bob
 *
 * Created on September 26, 2014, 3:40 PM
 */

#include        <cmn_defs.h>
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

#ifdef NDEBUG
#else
// https://developer.apple.com/library/mac/qa/qa1361/_index.html
// Q:  How do I determine if I'm being run under the debugger?
// A: How do I determine if I'm being run under the debugger?
// The code in Listing 1 shows the best way to do this.

bool            cmn_AmIBeingDebugged(
    void
)
{
    int                 junk;
    int                 mib[4];
    struct kinfo_proc   info;
    size_t              size;
    
    // Initialize the flags so that, if sysctl fails for some bizarre
    // reason, we get a predictable result.
    
    info.kp_proc.p_flag = 0;
    
    // Initialize mib, which tells sysctl the info we want, in this case
    // we're looking for information about a specific process ID.
    
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_PID;
    mib[3] = getpid();
    
    // Call sysctl.
    
    size = sizeof(info);
    junk = sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, NULL, 0);
    assert(junk == 0);
    
    // We're being debugged if the P_TRACED flag is set.
    
    return ( (info.kp_proc.p_flag & P_TRACED) != 0 );
}
#endif



//===============================================================
//                    P r o p e r t i e s
//===============================================================

//===============================================================
//                    M e t h o d s
//===============================================================









