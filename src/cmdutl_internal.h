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
    PATH_DATA       *pPath;
    char            **argv;
    int             permute;
    int             optIndex;
    W32CHR_T        optopt;
    char            *optarg;
    char            errmsg[64];
    int             subopt;

    // ArgC/ArgV Stuff
    int             cArgs;              // Copy of Original Arguments
    char            **ppArgs;

    // Program Options
    uint8_t         fDebug;
    uint8_t         fForce;
    uint8_t         fQuiet;
    uint8_t         rsvd8;
    uint16_t        iVerbose;
    uint16_t        rsvd16_1;
    
    // Program Arguments and Options
    uint16_t        cOptions;
    uint16_t        rsvd16_2;
    ASTRARRAY_DATA  *pArgs;
    ASTRARRAY_DATA  *pEnv;
    uint16_t        cProgramArgs;
    uint16_t        cGroupArgs;
    uint32_t        nextArg;
    PATH_DATA       *pProgramPath;
    CMDUTL_OPTION   *pProgramArgs;
    CMDUTL_OPTION   *pGroupArgs;
    
    OBJ_ID          pObjPrs;
    ERESULT         (*pParseArgsDefaults)(OBJ_ID);
    /*!
     @return    If successful, ERESULT_SUCCESS_0, ERESULT_SUCCESS_1,
     ERESULT_SUCCESS_2 or ERESULT_SUCCESS_3 to denote how
     many parameters were used beyond the normal 1.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         (*pParseArgsLong)(
                                      OBJ_ID          this,
                                      bool            fTrue,
                                      ASTR_DATA       *pName,
                                      ASTR_DATA       *pWrk,
                                      uint32_t        index,
                                      ASTRARRAY_DATA  *pArgs
                                      );
    ERESULT         (*pParseArgsShort)(OBJ_ID, int *, const char ***);
    ERESULT         (*pParseArgsError)(OBJ_ID, int *, const char ***);
    
};
#pragma pack(pop)

    extern
    const
    CMDUTL_VTBL     cmdutl_Vtbl;



    // Internal Functions
    ERESULT         cmdutl_AppendCharToField(
        CMDUTL_DATA     *cbp,
        W32CHR_T        chr
    );

    
    void            cmdutl_Dealloc(
        OBJ_ID          objId
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

