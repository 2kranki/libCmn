/* 
 * File:   cmn_defs.h
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


//#define         _USE_TNEO         1
//  Define the Compiler Environment
//      __AZTECC__      - Aztec C (Being Removed)
//      __BCDOS__       - Borland C++ for MS/DOS (16-Bit)
//      __BC32__        - Borland C++ for MS/DOS (32-Bit)
//      __BCOS2__       - Borland C++ for OS/2 v2.x (32-Bit)
//      __IBMCS2__      - IBM C++ Set/2
//      __MSVC16__      - Microsoft C++ for MS/DOS (16-Bit)
//      __MSVC32__      - Microsoft C++ for Windows 95/NT (32-Bit)
//      __MSVC64__      - Visual Studio (64-Bit)
//      __WATCOM_C386__ - Watcom C++ (32-Bit)
#if     !defined(__APPLE__) && !defined(__AZTEC_C__) &&\
        !defined(__BC_DOS__) && !defined(__BC_32__) &&\
        !defined(__MSVC16__) && !defined(__MSVC32__) && !defined(__MSVC64__) &&\
        !defined(__WATCOM_C386__)
#   error  No compiler environment specified!!!
#endif


//  Define the Operating Environment of the Programs/Routines
//      DPMI32_ENV  - MS/DOS Extender with Windows NT subset support
//      MACOSX_ENV  - Mac OS X Standard Environment
//      MSDOS_ENV   - MS/DOS Standard Environment
//      OS2_ENV     - OS/2 v1.x Support (Being Removed)
//      OS2V2_ENV   - OS/2 v2.x Support
//      PIC32MX_ENV - Microchip PIC32MX Support
//      PIC32MX_TNEO_ENV - Microchip PIC32MX Support w/ TNEO O/S
//      PIC32MZ_ENV - Microchip PIC32MZ Support
//      WIN16_ENV   - Windows v3.1 with MS/DOS
//      WIN32_ENV   - Win32 Support
//      WIN64_ENV   - Win64 Support
#if     !defined(__DPMI32_ENV__) && !defined(__MSDOS_ENV__) &&\
        !defined(__PIC32MX_ENV__) && !defined(__PIC32MX_TNEO_ENV__) &&\
        !defined(__PIC32MZ_ENV__) &&\
        !defined(__WIN16_ENV__) && !defined(__WIN32_ENV__) && !defined(__WIN64_ENV__) &&\
        !defined(__MACOSX_ENV__)
#   error  No execution environment specified!!!
#endif



#if             defined(__MACOSX_ENV__)
#   include        <dirent.h>
#   include        <errno.h>
#   include        <pthread.h>
#   include        <unistd.h>
#   include        <sys/dirent.h>
#   include        <sys/time.h>
#endif
#if             defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
#   define         STRICT
#   include        <windows.h>
#   include        <windowsx.h>
#   include        <signal.h>
#endif
#include        <ctype.h>
#include        <fcntl.h>
#include        <stdarg.h>
#include        <stdbool.h>
#include        <stddef.h>
#include        <stdint.h>
#include        <stdio.h>
#include        <stdlib.h>
#include        <string.h>
#include        <time.h>
#include        <wchar.h>
#include        <sys/stat.h>
#include        <sys/types.h>


#include        <str.h>


#ifndef     CMN_DEFS_H
#define     CMN_DEFS_H   1


#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    //****************************************************************
    //* * * * * * * * * * *  Data Definitions  * * * * * * * * * * * *
    //****************************************************************

    typedef struct cmn_data_s   CMN_DATA;



    //****************************************************************
    //* * * * * * * * * * *  Function Definitions  * * * * * * * * * *
    //****************************************************************




    //****************************************************************
    //* * * * * * *  Architecture Dependent Definitions  * * * * * * *
    //****************************************************************

#include    "obj.h"


    typedef uint32_t    (*GET_SFR)( );
    typedef void        (*PUT_SFR)(uint32_t);
    typedef void        (*PUTCLR_SFR)( );
    typedef void        (*PUTCLRSET_SFR)(uint32_t);

    // Comparison Routine: returns 0 if *p0 == *p1,
    // -n if *p0 < *p1 or +n if *p0 > *p1.
    typedef int         (*P_COMPARE)(void *p0, void *p1);

    typedef void        (*P_VOIDEXIT0)(void);
    typedef void        (*P_VOIDEXIT1)(void *);
    typedef void        (*P_VOIDEXIT2)(void *,void *);
    typedef void        (*P_VOIDEXIT3)(void *,void *,void *);
    typedef void        (*P_VOIDEXIT12)(void *,bool);
    typedef bool        (*P_VOIDEXIT1_B)(void *);
    typedef bool        (*P_VOIDEXIT2_B)(void *,void *);
    typedef bool        (*P_VOIDEXIT3_B)(void *,void *,void *);
    typedef ERESULT     (*P_VOIDEXIT1_BE)(void *);
    typedef ERESULT     (*P_VOIDEXIT2_BE)(void *,void *);
    typedef ERESULT     (*P_VOIDEXIT3_BE)(void *,void *,void *);
    typedef uint32_t    (*P_VOIDEXIT1_U32)(void *);
    typedef void *      (*P_VOIDEXIT1_PTR)(void *);
    typedef uint32_t    (*P_VOIDEXIT2_U32_U32)(void *,uint32_t);



    // All of the scan routines advance the ppCmdStr pointer as they
    // scan the string.

    /* CmdStr is scanned one character at a time into the Output
     * buffer supplied. The scan will go until it hits end of line
     * the end of the string. It will copy at most maxLen characters
     * to the output.
     */
    bool            scanString(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t        maxLen,
        uint32_t		*pScannedLen,       // (returned) Scanned Length
                                            // (not including leading whitespace)
        char			*pOutput            // Output Buffer Pointer
    );

    bool            scanDec32(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t		*pScannedLen,       // (returned,optional) Scanned Length
                                            // (includes leading whitespace)
        uint32_t		*pValue             // (returned,optional) Scanned Number
    );

    bool            scanHex32(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t		*pScannedLen,       // (returned,optional) Scanned Length
        uint32_t		*pValue             // (returned,optional) Scanned Number
    );

    bool            scanWhite(
        char			**ppCmdStr,         // NUL terminated string pointer
        uint32_t		*pScannedLen        // (returned,optional) Scanned Length
    );


    
#define     IS_POWER_OF_2(x)    ((x != 0) && !(x & (x - 1)))
#define     ROUNDUP2(n)         (((n+2-1) >> 1) << 1)
#define     ROUNDUP4(n)         (((n+4-1) >> 2) << 2)
#define     ROUNDUP8(n)         (((n+8-1) >> 3) << 3)
#define     ROUNDUP16(n)        (((n+16-1) >> 4) << 4)
#define     ROUNDUP32(n)        (((n+32-1) >> 5) << 5)


// In C, "long" is defined to be the word size of the computer
// where "int" might be shorter.
#define WORDSIZE sizeof(long)   /* word size in bytes */
#define ROUNDUP_WORD(x) (((x + WORDSIZE - 1) / WORDSIZE) * WORDSIZE)
    

#define     MAKEUINT16(h,l) ((uint16_t)((uint8_t)(l))|((uint8_t)((uint8_t)(h))<<8))
#define     MAKEUINT32(h,l) ((uint32_t)((uint16_t)(l))|((uint32_t)((uint16_t)(h))<<16))
#define     MAKEUINT64(h,l) ((uint64_t)((uint32_t)(l))|((uint64_t)((uint32_t)(h))<<32))
    




    //****************************************************************
    //* * * * * * * * * * *  Function Definitions  * * * * * * * * * *
    //****************************************************************

    //          ** General Exception Handler Functions **
    // cmn_ActivateGeneralExceptionHandler needs to be called at the
    // beginning of the program to activate the handler.
    void            cmn_ActivateGeneralExceptionHandler(void);
    const
    char *          cmn_getLastExceptionReason(void);
    uint32_t        cmn_getLastExceptionAddress(void);



#define WAIT_INFINITE   (-1)

#ifdef	__cplusplus
}
#endif



//****************************************************************
//* * * * * * * * *  Dependent Object Definitions  * * * * * * * *
//****************************************************************

// Some objects are co-dependent which can cause recursive header
// includes. So, we define the objects and their vtbls here.

typedef struct AStr_data_s          ASTR_DATA;
typedef struct AStr_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in AStrC_object.c.
    // Properties:
    // Methods:
    const
    char *      (*pGetData)(ASTR_DATA *);
    uint32_t    (*pGetLength)(ASTR_DATA *);
} ASTR_VTBL;


typedef struct AStrC_data_s         ASTRC_DATA;
typedef struct AStrC_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in AStrC_object.c.
    // Properties:
    // Methods:
    const
    char *      (*pGetData)(ASTRC_DATA *);
    uint32_t    (*pGetLength)(ASTRC_DATA *);
} ASTRC_VTBL;


typedef struct AStrArray_data_s     ASTRARRAY_DATA;
typedef struct AStrArray_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrArray_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(WSTRARRAY_DATA *);
} ASTRARRAY_VTBL;


typedef struct file_data_s	FILE_DATA;
typedef struct file_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in fat16_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(FBSI_DATA *);
} FILE_VTBL;


typedef struct path_data_s          PATH_DATA;
typedef struct path_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrArray_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(WSTRARRAY_DATA *);
} PATH_VTBL;


typedef struct u8Array_data_s	U8ARRAY_DATA;
typedef struct u8Array_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in fileio_object.c.
    // Properties:
    // Methods:
    //bool        (*pIsEnabled)(FILEIO_DATA *);
} U8ARRAY_VTBL;


typedef struct WStr_data_s          WSTR_DATA;
typedef struct WStr_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrC_object.c.
    // Properties:
    // Methods:
    const
    int32_t *   (*pGetData)(WSTR_DATA *);
    uint32_t    (*pGetLength)(WSTR_DATA *);
} WSTR_VTBL;


typedef struct WStrArray_data_s     WSTRARRAY_DATA;
typedef struct WStrArray_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrArray_object.c.
    // Properties:
    // Methods:
    bool        (*pIsEnabled)(WSTRARRAY_DATA *);
} WSTRARRAY_VTBL;


typedef struct WStrC_data_s         WSTRC_DATA;
typedef struct WStrC_vtbl_s	{
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Put other methods below this as pointers and add their
    // method names to the vtbl definition in WStrC_object.c.
    // Properties:
    // Methods:
    const
    int32_t *   (*pGetData)(WSTRC_DATA *);
    uint32_t    (*pGetLength)(WSTRC_DATA *);
} WSTRC_VTBL;



#include    <eResult.h>


#if defined(__MACOSX_ENV__)
#	include     <cmn_osx.h>
#   include     <memOSX.h>
#endif
#if defined(__WIN32_ENV__)
#	include     <cmn_msc.h>
#   include     <memMSC.h>
#endif
#if defined(__WIN64_ENV__)
#	include     <cmn_msc.h>
#   include     <memMSC.h>
#endif
#if defined(__PIC32MX_ENV__)
#	include    <cmn_pic32mx.h>
#endif
#if defined( __PIC32MZ_ENV__ )
#	include    <cmn_pic32mz.h>
#endif





#endif	/* CMN_DEFS_H */

