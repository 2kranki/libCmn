// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   cmdutl_internal.h
 *	Generated 10/18/2015 19:44:45
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




#ifndef CMDUTL_INTERNAL_H
#define	CMDUTL_INTERNAL_H


#include    <cmdutl.h>
#include    <node_internal.h>
#include    <nodeArray.h>
#include    <nodeHash.h>
#include    <nodeTree.h>
#include    <path.h>
#include    <srcFile.h>
#include    <stdio.h>
#include    <wchar.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    


#pragma pack(push, 1)
struct cmdutl_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;
    CMDUTL_OPTION   *pOptions;

    // Common Data
    PATH_DATA       *pPath;             // Program Path
    char            **ppArgV;
    bool            fPermute;
    int             optIndex;
    W32CHR_T        optopt;
    char            *pOptArg;
    char            errmsg[64];
    int             subopt;

    // ArgC/ArgV Stuff
    ASTRARRAY_DATA  *pSavedArgs;
    OBJ_ID          pObj;
    void            (*pFatalError)(
        const
        char            *fmt,
        ...
    );

    // Program Arguments and Options
    uint16_t        cOptions;
    uint16_t        rsvd16_2;
    uint32_t        nextArg;
    CMDUTL_OPTION   *pOptDefns;
        
};
#pragma pack(pop)

    extern
    const
    CMDUTL_VTBL     cmdutl_Vtbl;



    // Internal Functions
    bool            cmdutl_setArgV(
        CMDUTL_DATA     *this,
        ASTRARRAY_DATA  *pValue
    );


    ERESULT         cmdutl_AppendCharToField(
        CMDUTL_DATA     *cbp,
        W32CHR_T        chr
    );

    
    int             cmdutl_Argtype(
        const
        char            *optstring,
        char            c
    );
    
    
    int             cmdutl_CreateErrorMsg(
        CMDUTL_DATA     *this,
        const
        char            *pMsg,
        const
        char            *pData
    );
    
    
    void            cmdutl_Dealloc(
        OBJ_ID          objId
    );

    
    int             cmdutl_IsDashDash(
        const
        char            *arg
    );
    
    
    int             cmdutl_IsLongOpt(
        const
        char            *arg
    );
    
    
    int             cmdutl_IsShortOpt(
        const
        char            *arg
    );
    
    
    char *          cmdutl_LongOptsArg(
        char            *option
    );
    
    
    bool            cmdutl_LongOptsEnd(
        const
        CMDUTL_OPTION   *pOptions,
        int             i
    );
    
    
    int             cmdutl_LongOptsFallback(
        CMDUTL_DATA     *this,
        const
        CMDUTL_OPTION   *pOptions,
        int             *pLongIndex
    );
    
    
    int             cmdutl_LongOptsMatch(
        const
        char            *pLongName,
        const
        char            *option
    );
    
    
    bool            cmdutl_OptstringFromLongOptions(
        const
        CMDUTL_OPTION   *pOptions,
        int             len,
        char            *pOptstring
    );
    
    
    int             cmdutl_Parse(
        CMDUTL_DATA     *this,
        const
        char            *optstring
    );
    
    
    int             cmdutl_ParseLong(
        CMDUTL_DATA     *this,
        CMDUTL_OPTION   *pOptions,
        int             *longindex
    );
    
    
    void            cmdutl_Permute(
        CMDUTL_DATA     *this,
        int             index
    );
    
    
#ifdef NDEBUG
#else
    bool			cmdutl_Validate(
        CMDUTL_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CMDUTL_INTERNAL_H */

