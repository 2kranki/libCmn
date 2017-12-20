// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   srcFile_internal.h
 *	Generated 06/17/2015 11:21:15
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




#ifndef SRCFILE_INTERNAL_H
#define	SRCFILE_INTERNAL_H


#include    "srcFile.h"
#include    <stdio.h>
#include    "objArray.h"
#include    "token_internal.h"
#include    "tokenList.h"

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct srcFile_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;
#define SRCFILE_INIT_DONE   OBJ_FLAG_USER1

    // Common Data
    PATH_DATA       *pPath;
    const
    char            *pFileName;
    union {
        FBSI_DATA           *pFbsi;
        ASTR_DATA           *pAStr;
        FILE                *pFile;
        U8ARRAY_DATA        *pU8Array;
        W32STR_DATA         *pW32Str;
    };
    uint16_t        type;               // OBJ_CLASS_FBSI or OBJ_CLASS_SBUF
    uint16_t        flags;              /* Flags */
#define FLG_EOF         0x8000                  /* End-of-File has been reached. */
#define FLG_INS         0x4000                  /* Lines are being inserted. */
#define FLG_NNL         0x2000                  /* Remove all '\n's. */
#define FLG_OPN         0x1000                  /* File is open and useable. */
#define FLG_TAB         0x0800                  /* Expand Horizontal Tabs. */
#define FLG_FILE        0x0400                  /* FILE file was provided */
    uint32_t        lineNo;             /* Current Line Number */
    size_t          fileOffset;
    uint16_t        colNo;              /* Current Column Number */
    uint8_t         fStripCR;
    uint8_t         fBackTrack;
    uint16_t        tabSize;            /* Tab Spacing Size */
    uint16_t        fileIndex;
    TOKEN_DATA      curchr;             /*  Current Character */

    // Input Routines
    TOKENLIST_DATA  *pTokens;
    uint32_t        rsvd32;
    uint16_t        sizeInputs;
    uint16_t        curInputs;
    TOKEN_DATA      *pInputs;
    
};
#pragma pack(pop)

    extern
    const
    SRCFILE_VTBL    srcFile_Vtbl;



    // Internal Functions
    bool            srcFile_setFileIndex(
        SRCFILE_DATA    *this,
        uint16_t        value
    );
    
    
    void            srcFile_Dealloc(
        OBJ_ID          objId
    );
    

    int32_t         srcFile_InputNextChar(
        SRCFILE_DATA	*cbp
    );
    
    
#ifdef NDEBUG
#else
    bool			srcFile_Validate(
        SRCFILE_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRCFILE_INTERNAL_H */

