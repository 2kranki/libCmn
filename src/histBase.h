// vi:nu:et:sts=4 ts=4 sw=4 tw=90

//****************************************************************
//          History Table (histBase) Header
//****************************************************************
/*
 * Program
 *			History Table (histBase)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate histBase to run things without complications
 *          of interfering with the main histBase. A histBase may be 
 *          called a histBase on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal histBase. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	02/26/2016 Generated
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





#include        <cmn_defs.h>
#include        <devBase.h>


#if         defined(HISTBASE_GENERATE)
#undef  HIST_IOCTL_ADD
#define HIST_IOCTL_ADD(obj,subsys,ident,data0,data1)    \
    histBase_Ioctl(                                     \
        obj,                                            \
        ((subsys << 24) | (ident << 8) | HIST_IOCTL_OP_ADD), \
        (void *)data0,                                  \
        (void *)data1                                   \
    )

/*!
 HIST_IOCTL_ENUMERATE() returns the the Table one entry at
 a time to the routine provided. Order is oldest to newest.
 We lock/unlock the table for this if it is not already locked.
 @param data0
 is a function, void (*pFunc)(data1,HIST_ENTRY *)
 @param data1
 is the first parameter to the function
 */
#undef  HIST_IOCTL_ENUMERATE
#define HIST_IOCTL_ENUMERATE(obj,subsys,ident,data0,data1) \
    histBase_Ioctl(obj,HIST_IOCTL_OP_ENUMERATE,data0,data1)

#undef  HIST_IOCTL_LOCK
#define HIST_IOCTL_LOCK(obj,subsys,ident,data0,data1)      \
    histBase_Ioctl(obj,HIST_IOCTL_OP_LOCK,NULL,NULL)

/*!
 HIST_IOCTL_SIZE() returns the the Table size in bytes
 @param data0
 returned size ptr (uint32_t *)
 */
#undef  HIST_IOCTL_SIZE
#define HIST_IOCTL_SIZE(pObj,data0)                         \
    histBase_Ioctl(pObj,HIST_IOCTL_OP_SIZE,data0,NULL)

#undef  HIST_IOCTL_UNLOCK
#define HIST_IOCTL_UNLOCK(obj,subsys,ident,data0,data1)     \
    histBase_Ioctl(obj,HIST_IOCTL_OP_UNLOCK,NULL,NULL)
#else       // not defined(USE_HISTBASE)
#undef  HIST_IOCTL_ADD
#define HIST_IOCTL_ADD(obj,subsys,ident,data0,data1)        ERESULT_NOT_SUPPORTED
#undef  HIST_IOCTL_ENUMERATE
#define HIST_IOCTL_ENUMERATE(obj,subsys,ident,data0,data1)  ERESULT_NOT_SUPPORTED
#undef  HIST_IOCTL_LOCK
#define HIST_IOCTL_LOCK(obj,subsys,ident,data0,data1)       ERESULT_NOT_SUPPORTED
#undef  HIST_IOCTL_SIZE
#define HIST_IOCTL_SIZE(pObj,data0)                         ERESULT_NOT_SUPPORTED
#undef  HIST_IOCTL_UNLOCK
#define HIST_IOCTL_UNLOCK(obj,subsys,ident,data0,data1)     ERESULT_NOT_SUPPORTED
#endif      // USE_HISTBASE



#ifndef         HISTBASE_H
#define         HISTBASE_H      1
#pragma once



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct histBase_data_s	HISTBASE_DATA;    // Inherits from devBase.

    typedef struct histBase_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in histBase_object.c.
        // Properties:
        // Methods:
        DEVBASE_VTBL    devVtbl;             // Inherited VTBL from devBase
    } HISTBASE_VTBL;


    
    typedef enum hist_subsys_e {
        HIST_SUBSYS_UNKNOWN=0,
        HIST_SUBSYS_CANBASE,
        HIST_SUBSYS_CP0BASE,
        HIST_SUBSYS_CP0DEV,
        HIST_SUBSYS_OSCBASE,
        HIST_SUBSYS_RTCCBASE,
        HIST_SUBSYS_SYSBASE,
        HIST_SUBSYS_TMR1BASE,
        HIST_SUBSYS_TMRNBASE,
        HIST_SUBSYS_UARTBASE,
        HIST_SUBSYS_UARTDEV,
    } HIST_SUBSYS;
    
    
    // This structure must be capable of being sent via ioctl in its
    // paramenters except for the timeStamp.
    // 4096 buffer == 256 16-byte entries
#pragma pack(push,1)
    typedef struct hist_entry_s {
        union {
            struct {
                uint32_t        timeStamp;
                uint8_t         reserved;
                uint8_t         subsys;
                uint16_t        ident;
                uint32_t        data0;
                uint32_t        data1;
            };
            struct {
                uint32_t        data32_0;
                uint32_t        data32_1;
                uint32_t        data32_2;
                uint32_t        data32_3;
            };
        };
    } HIST_ENTRY;
#pragma pack()

    
    typedef enum hist_ioctl_op_e {
        HIST_IOCTL_OP_UNKNOWN=0,
        HIST_IOCTL_OP_ADD,
        HIST_IOCTL_OP_ENUMERATE,
        HIST_IOCTL_OP_LOCK,
        HIST_IOCTL_OP_SIZE,
        HIST_IOCTL_OP_UNLOCK,
    } HIST_IOCTL_OP;
    
    
    
    
    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    HISTBASE_DATA *     histBase_Alloc(
        uint16_t        tableSize           // Number of elements
                                            // (Power of 2 only)
    );
    
    
    HISTBASE_DATA *     histBase_New(
        DEVMGR_DATA     *pMgr,
        uint16_t        tableSize           // Number of elements
                                            // (Power of 2 only)
    );
    
    
    const
    char *          histBase_SubsysDesc(
        HIST_SUBSYS     code
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            histBase_setCount(
        HISTBASE_DATA   *this,
        uint32_t        (*pCountFunc)(void *),
        void            *pCountData
    );
    
    
    
    
    bool            histBase_setWrap(
        HISTBASE_DATA   *this,
        void            (*pWrapFunc)(void *,HISTBASE_DATA *),
        void            *pWrapData
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    HISTBASE_DATA * histBase_Init(
        HISTBASE_DATA   *this,
        DEVMGR_DATA     *pMgr
    );


    ERESULT         histBase_Ioctl(
        HISTBASE_DATA	*this,
        uint32_t        request,
        void            *pParm1,
        void            *pParm2
    );
    
 
    ERESULT         histBase_Read(
        HISTBASE_DATA	*this,
        uint32_t        amt,
        void            *pData,
        uint32_t        *pAmtRead
    );
    
    
    ERESULT         histBase_Start(
        HISTBASE_DATA	*this,
        void            *pParm
    );
    
    
    ERESULT         histBase_Stop(
        HISTBASE_DATA	*this,
        void            *pParm
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *    histBase_ToDebugString(
        HISTBASE_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* HISTBASE_H */

