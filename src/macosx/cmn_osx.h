/* 
 * File:   cmn_osx.h
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

#ifndef CMN_OSX_H
#define	CMN_OSX_H

/****************************************************************
* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
****************************************************************/

#ifdef	__cplusplus
extern "C" {
#endif



#ifndef DEBUG_BREAK
#   ifdef NDEBUG
#       define DEBUG_BREAK( )  /**/
#   else
#       define DEBUG_BREAK( )\
                if( cmn_AmIBeingDebugged() ){ __asm__("int $3\n" : : );}
#   endif
#endif

#define BREAK_TRUE(n)  if( (n) )  { DEBUG_BREAK(); }
#define BREAK_FALSE(n) if( !(n) ) { DEBUG_BREAK(); }
#define BREAK_NULL(n)  if(NULL == (n))  { DEBUG_BREAK(); }
#define BREAK_NOT_NULL(n)  if(!(NULL == (n)))  { DEBUG_BREAK(); }
#define BREAK_ZERO(n)  if(0 == (n))  { DEBUG_BREAK(); }
#define BREAK_NOT_ZERO(n)  if(!(0 == (n)))  { DEBUG_BREAK(); }
#define BREAK_NOT_WORD_BOUNDARY(n)  if(!(0 == ((uint32_t)n)&0x3))  { DEBUG_BREAK(); }
#define BREAK_NOT_BOUNDARY2(n)  if(!(0 == (((uint32_t)n)&0x1)))  { DEBUG_BREAK(); }
#define BREAK_NOT_BOUNDARY4(n)  if(!(0 == (((uint32_t)n)&0x3)))  { DEBUG_BREAK(); }
#define BREAK_NOT_BOUNDARY8(n)  if(!(0 == (((uint32_t)n)&0x7)))  { DEBUG_BREAK(); }
    


    

//****************************************************************
//* * * * * * * * * * *  Function Definitions  * * * * * * * * * *
//****************************************************************

#ifdef NDEBUG
#else
    bool            cmn_AmIBeingDebugged(
        void
    );
#endif

    
#ifdef USE_PIC32

#define INTERRUPT_STATUS        /**/
#define DISABLE_INTERRUPTS()    /**/
#define ENABLE_INTERRUPTS       /**/
#define RESTORE_INTERRUPTS      /**/
    
    bool            ct_DelayUS(
        uint32_t        us
    );
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
#endif



#ifdef	__cplusplus
}
#endif


#endif	/* CMN_OSX_H */

