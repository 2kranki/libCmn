// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   prt_internal.h
 *	Generated 06/16/2015 07:51:09
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




#ifndef PRT_INTERNAL_H
#define	PRT_INTERNAL_H


#include    "prt.h"
#include    <stdbool.h>
#include    <stddef.h>
#include    <stdint.h>
#include    <stdio.h>
#include    <stdlib.h>


#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct prt_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    /* * *  Print File Variables  * * */
    FILE        *pList;          /* List Ouput File */
    char        lstnam[256];
    
    /* * *  Page Setup Variables  * * */
    uint16_t    pagsiz;         /* Lines per Page */
    uint16_t    colmax;         /* Number of Columns on a Line */
    uint16_t    hdrsiz;         /* Number of Lines in Page Header */
    uint16_t    tlrsiz;         /* Number of lines in Page Trailer */
    uint16_t    offhdr;         /* Line Offset of 1st Header Line */
    uint16_t    offtlr;         /* Line Offset of 1st Trailer Line */
    uint16_t    offset;         /* Column Offset on Page */
    uint16_t    dfttab;         /* Default Tab Columns (Default 4) */
    bool        offlin;         /* True = Offset done for this line */
    bool        prtdln;         /* True = print detail line number */
    bool        prtint;         /* True = printing was interrupted */
    bool        prthdr;         /* True = print a header before anything else*/
    bool        format;         /* True = display header/trailer */
    uint16_t    prntyp;         /* Printer Type */
    /*  0 - Simple */
    /*  1 - Laserjet */
    /*  2 - Deskjet */
    
    /* * *  Current Variables  * * */
    uint16_t    curpag;         /* Current Page Number */
    uint16_t    curlin;         /* Current Line Number */
    uint16_t    curcol;         /* Current Column Number */
    uint16_t    curdln;         /* Current Detail Line Number */
    char        *curhdr[3];     /* Page Header Lines */
    char        *curtlr[3];     /* Page Trailer Lines */
    char        hdr1[255];      /* Page Header Line 1 */
    char        hdr2[255];      /* Page Header Line 2 */
    char        hdr3[255];      /* Page Header Line 3 */
    char        tlr1[255];      /* Page Trailer Line 1 */
    char        tlr2[255];      /* Page Trailer Line 2 */
    char        tlr3[255];      /* Page Trailer Line 3 */
    
};
#pragma pack(pop)

    extern
    const
    OBJ_IUNKNOWN    prt_Vtbl;



    // Internal Functions
    void            prt_Dealloc(
        OBJ_ID          objId
    );

#ifdef NDEBUG
#else
    bool			prt_Validate(
        PRT_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PRT_INTERNAL_H */

