/* 
 * File:   cmn.h
 *
 * Notes:
 *   1	Before including define the following to customize the config bits for
 *		the development environment needed:
 *		_EXPLORER_16		Microchip Explorer 16 board
 *		_MAX32              Diligent MAX 32 board
 *		_NETWORK_SHIELD     Diligent Network Shield
 *   2  CONFIG properties are generated in cmn.c depending upon how the above
 *      options are set.
 *   3  We assume that you have allocated some space for a heap
 *      (Properties -> ld -> heapsize).
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


//#define         _EXPLORER_16      1
//#define         _MAX32            1
//#define         _NETWORK_SHIELD   1

//#define         _USE_TNEO         1


#ifndef CMN_PIC32_H
#define	CMN_PIC32_H

/****************************************************************
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/

#include    <xc.h>
#include    <cp0defs.h>
#include    <sys/attribs.h>
#include    <umm_malloc_cfg.h>
#include    <umm_malloc.h>

#ifdef __32MX795F512L__
#include	"32MX795F512L_defs.h"
#endif
#ifdef __32MZ2048ECH100__
#include	"32MZ2048ECH1024_defs.h"
#endif

#ifdef      _USE_TNEO
		// You might want to undef if you do not want the
		// additional error checking.
#		define      TN_CHECK_PARAM  1
#		include     <tn.h>
#   define YIELD()    tn_task_sleep(1)
#   define WAIT_MS(n) tn_task_sleep(n)

typedef enum tneo_priorities_e {
    TNEO_PRIORITY_VERY_HIGH=3,
        TNEO_PRIORITY_HIGH=5,
        TNEO_PRIORITY_NORMAL=7,
        TNEO_PRIORITY_LOW=9,
        TNEO_PRIORITY_VERY_LOW=11
} TNEO_PRIORITIES;

typedef enum TN_RCode TN_RC;

#else
#   define YIELD()      ct_DelayUS(100)
#   define WAIT_MS(n)   ct_DelayUS(n*1000)
#endif



#ifdef	__cplusplus
extern "C" {
#endif


#ifndef DEBUG_BREAK
#   ifdef NDEBUG
#       define DEBUG_BREAK( )  /**/
#   else
#       define DEBUG_BREAK( )  __asm__ volatile ("sdbbp 0")
#   endif
#endif


#ifndef CHECK_FOR_VALID_DCR
#   ifdef NDEBUG
#       define CHECK_FOR_VALID_DCR(dcr) /**/
#   else
#       define CHECK_FOR_VALID_DCR(dcr) \
            if( !( ((uint32_t)dcr >= 0xBFC02FF0) && ((uint32_t)dcr <= 0xBFC02FFF) ) ) \
                DEBUG_BREAK()
#   endif
#endif

#ifndef CHECK_FOR_VALID_SFR
#   ifdef NDEBUG
#       define CHECK_FOR_VALID_SFR(sfr) /**/
#   else
#       define CHECK_FOR_VALID_SFR(sfr) \
            if( !( ((uint32_t)sfr >= 0xBF800000) && ((uint32_t)sfr <= 0xBF8FFFFF) ) ) \
                DEBUG_BREAK()
#   endif
#endif
    
#ifndef BREAK_NOT_BOUNDARY2
#   ifdef NDEBUG
#       define BREAK_NOT_BOUNDARY2(n) /**/
#   else
#       define BREAK_NOT_BOUNDARY2(n) \
            if( !(0 == (((uint32_t)n) & 0x1)) ) \
                DEBUG_BREAK();
#   endif
#endif
    
#ifndef BREAK_NOT_BOUNDARY4
#   ifdef NDEBUG
#       define BREAK_NOT_BOUNDARY4(n) /**/
#   else
#       define BREAK_NOT_BOUNDARY4(n) \
if( !(0 == (((uint32_t)n) & 0x3)) ) \
DEBUG_BREAK();
#   endif
#endif
    
#ifndef BREAK_NOT_BOUNDARY8
#   ifdef NDEBUG
#       define BREAK_NOT_BOUNDARY8(n) /**/
#   else
#       define BREAK_NOT_BOUNDARY8(n) \
            if( !(0 == (((uint32_t)n) & 0x7)) ) \
                DEBUG_BREAK();
#   endif
#endif
    
#ifndef BREAK_NULL
#   ifdef NDEBUG
#       define BREAK_NULL(n) /**/
#   else
#       define BREAK_NULL(n) \
            if( NULL == n ) \
                DEBUG_BREAK();
#   endif
#endif


#ifndef BREAK_ZERO
#   ifdef NDEBUG
#       define BREAK_ZERO(n) /**/
#   else
#       define BREAK_ZERO(n) \
            if( 0 == n ) \
                DEBUG_BREAK();
#   endif
#endif


#ifndef BREAK_NOT_ZERO
#   ifdef NDEBUG
#       define BREAK_NOT_ZERO(n) /**/
#   else
#       define BREAK_NOT_ZERO(n) \
            if( !(0 == n) ) \
                DEBUG_BREAK();
#   endif
#endif


#ifndef INTERRUPT_STATUS
#define INTERRUPT_STATUS    uint32_t    cp0_12_status;
#endif

#ifndef DISABLE_INTERRUPTS
#define DISABLE_INTERRUPTS()                                    \
    do {														\
		asm volatile( "di %0" : "=r"(cp0_12_status) );			\
        asm volatile( "ehb" );                                  \
    } while(0)
#endif

#ifndef ENABLE_INTERRUPTS
// ENABLE_INTERRUPTS enables interrupts unconditionally.
#define ENABLE_INTERRUPTS                                           \
    do {                                                            \
        cp0_12_status |= 1;                                         \
        asm volatile("mtc0  %0, $12, 0" : : "r" (cp0_12_status));   \
    } while(0)
#endif

#ifndef RESTORE_INTERRUPTS
// RESTORE_INTERRUPTS re-enables interrupts only if they were enabled
// at the time that DISABLE_INTERRUPTS was performed. Otherwise, it is
// effectively a nop.
#define RESTORE_INTERRUPTS                                          \
    do {                                                            \
        asm volatile("mtc0  %0, $12, 0" : : "r" (cp0_12_status));	\
    } while(0)
#endif



//##############################################################################
//                              PIC32MX795F512L
//##############################################################################

#if defined (__32MX795F512L__)

#if defined(_EXPLORER_16) || defined(_NETWORK_SHIELD)
#define FRC_FREQ	(8000000UL)         /* 125 ns */
// SYSCLK = 80 MHz (12.5 ns)
#define SYS_FREQ	(80000000UL)
// PB_FREQ = SYS_FREQ / FPBDIV
#define PB_FREQ		(SYS_FREQ / 2)
#define SOSC_FREQ   (32768UL)   /* 30.5 us */
#endif
#define MAX_FLASH_SPEED_HZ  (30000000UL)
#define MAX_PB_BUS_FREQ_HZ  (80000000UL)

// 8 MHz Oscillator failed on Explorer 16 Board and PIC32MX795F512L reverted
// to its FRC Clock divided by FRCDIV of 2. PBDIV became 8 which gave an F_PB
// of 500,000 Hz or 2us. SYS_CLK became 4 MHz or 250ns.



//##############################################################################
//                              PIC32MZ2048ECH100
//##############################################################################

#elif defined (__32MZ2048ECH100__)

#define PA_TO_KVA( x ) ( (void *)((uint32_t)x | 0x80000000) )
#define KVA_TO_PA( x ) ( (void *)((uint32_t)x & 0x7FFFFFFF) )

#define FRC_FREQ	(8000000UL)         /* 125 ns */

#define PB1_FREQ     (SYS_FREQ/2)
#define PB2_FREQ     (SYS_FREQ/2)
#define PB3_FREQ     (SYS_FREQ/2)
#define PB4_FREQ     (SYS_FREQ/2)
#define PB5_FREQ     (SYS_FREQ/2)
#define PB6_FREQ     (SYS_FREQ/2)
#define PB7_FREQ     (SYS_FREQ)
#if defined(EXPLORER_16) || defined(CFG_NETWORK_SHIELD)
#define SOSC_FREQ       32768
#endif
#define MAX_FLASH_SPEED_HZ  (30000000L)     /*???*/
#define MAX_PB_BUS_FREQ_HZ  (80000000L)     /*???*/

#else
    #error Unsupported CPU type
#endif

    

/**
 * Macro for checking value returned from system service.
 *
 * If you ignore the value returned by any system service, it is almost always
 * a BAD idea: if something goes wrong, the sooner you know it, the better.
 * But, checking error for every system service is a kind of annoying, so,
 * simple macro was invented for that.
 *
 * In most situations, any values other than `#TN_RC_OK` or `#TN_RC_TIMEOUT`
 * are not allowed (i.e. should never happen in normal device operation).
 *
 * So, if error value is neither `#TN_RC_OK` nor `#TN_RC_TIMEOUT`, this macro
 * issues a software break.
 *
 * If you need to allow `#TN_RC_OK` only, use `SYSRETVAL_CHECK()` instead (see
 * below)
 *
 * Usage is as follows:
 *
 * \code{.c}
 *    enum TN_RCode rc
 *       = SYSRETVAL_CHECK_TO(tn_queue_send(&my_queue, p_data, MY_TIMEOUT));
 *
 *    switch (rc){
 *       case TN_RC_OK:
 *          //-- handle successfull operation
 *          break;
 *       case TN_RC_TIMEOUT:
 *          //-- handle timeout
 *          break;
 *       default:
 *          //-- should never be here
 *          break;
 *    }
 * \endcode
 *
 */
#define TN_SYSRETVAL_CHECK_TO(x)                                  \
   ({                                                             \
      int __rv = (x);                                             \
      if (__rv != TN_RC_OK && __rv != TN_RC_TIMEOUT){             \
         DEBUG_BREAK();                                        \
      }                                                           \
      /* like, return __rv */                                     \
      __rv;                                                       \
    })


/**
 * The same as `SYSRETVAL_CHECK_TO()`, but it allows `#TN_RC_OK` only.
 *
 * Since there is only one return code allowed, usage is simple:
 *
 * \code{.c}
 *    SYSRETVAL_CHECK(tn_queue_send(&my_queue, p_data, MY_TIMEOUT));
 * \endcode
 */
#define TN_SYSRETVAL_CHECK(x)                                     \
   ({                                                             \
      int __rv = (x);                                             \
      if (__rv != TN_RC_OK){                                      \
         DEBUG_BREAK();                                        \
      }                                                           \
      /* like, return __rv */                                     \
      __rv;                                                       \
    })



#include    "cfg.h"
#include    "con.h"
#include    "ct.h"
#include    "dma.h"
#include    "mon.h"
#include    "osc.h"
#include    "timer.h"
#include    "uart.h"



//****************************************************************
//* * * * * * * * * * *   Method Definitions   * * * * * * * * * *
//****************************************************************

CFG_DATA *      cmn_getCfg(
    CMN_DATA        *cbp
);

bool            cmn_setCfg(
    CMN_DATA        *cbp,
    CFG_DATA        *pCfg
);


CON_DATA *      cmn_getCon(
    CMN_DATA        *cbp
);

bool            cmn_setCon(
    CMN_DATA        *cbp,
    CON_DATA        *pCon
);


CT_DATA *       cmn_getCt(
    CMN_DATA        *cbp
);

bool            cmn_setCt(
    CMN_DATA        *cbp,
    CT_DATA         *pCT
);
    
    
DMA_DATA *      cmn_getDma(
    CMN_DATA        *cbp
);

bool            cmn_setDma(
    CMN_DATA        *cbp,
    DMA_DATA        *pDma
);
    
    
MON_DATA *      cmn_getMon(
    CMN_DATA        *cbp
);

bool            cmn_setMon(
    CMN_DATA        *cbp,
    MON_DATA        *pMon
);


OSC_DATA *      cmn_getOsc(
    CMN_DATA        *cbp
);

bool            cmn_setOsc(
    CMN_DATA        *cbp,
    OSC_DATA        *pOsc
);


TIMER_DATA *    cmn_getTimer1(
    CMN_DATA        *cbp
);

bool            cmn_setTimer1(
    CMN_DATA        *cbp,
    TIMER_DATA      *pTimer
);


UART_DATA *	cmn_getUart2(
    CMN_DATA        *cbp
);

bool            cmn_setUart2(
    CMN_DATA        *cbp,
    UART_DATA		*pUart
);


void *          cmn_getUser1(
    CMN_DATA        *cbp
);

bool            cmn_setUser1(
    CMN_DATA        *cbp,
    void            *pData
);


void *          cmn_getUser2(
    CMN_DATA        *cbp
);

bool            cmn_setUser2(
    CMN_DATA        *cbp,
    void            *pData
);





//****************************************************************
//* * * * * * * * * * *  Function Definitions  * * * * * * * * * *
//****************************************************************

CMN_DATA *      cmn_Close(
    CMN_DATA        *cbp
);


/* cmn_Open creates the CMN_DATA area and returns it. 
 * If any of the CFG, OSC or CT objects is null, a default object is
 * created. The CT object is initialized with 1ms freq, but it is not
 * enabled.
 * We need CT for our WAIT_MS() and WAIT_US() support.
 */
CMN_DATA *      cmn_Open(
    CFG_DATA        *pCfg,			// CFG Object or NULL
    CT_DATA         *pCt,			// CT Object or NULL
    DMA_DATA        *pDma,			// DMA Object or NULL
    OSC_DATA        *pOsc,			// OSC Object or NULL
    TIMER_DATA      *pTimer1        // TIMER Object or NULL
);


//          ** General Exception Handler Functions **
// cmn_ActivateGeneralExceptionHandler needs to be called at the
// beginning of the program to activate the handler.
void            cmn_ActivateGeneralExceptionHandler(
    void
);
const
char *          cmn_getLastExceptionReason(
    void
);
uint32_t        cmn_getLastExceptionAddress(
    void
);




#ifdef	__cplusplus
}
#endif

#endif	/* CMN_PIC32_H */

