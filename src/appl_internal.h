// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   appl_internal.h
 *	Generated 06/05/2017 10:38:38
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




#include    <appl.h>
#include    <nodeHash.h>


#ifndef APPL_INTERNAL_H
#define	APPL_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif



#pragma pack(push, 1)
struct appl_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    DATETIME_DATA   *pDateTime;
    NODEHASH_DATA   *pProperties;
    
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
    APPL_CLO        *pProgramArgs;
    APPL_CLO        *pGroupArgs;

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

    OBJ_ID          pObjProcess;
    ERESULT         (*pProcessInit)(OBJ_ID);
    ERESULT         (*pProcessArg)(OBJ_ID, ASTR_DATA *);

    OBJ_ID          pObjUsage;
    ERESULT         (*pUsageProgLine)(OBJ_ID, FILE *, PATH_DATA *, const char *);
    ERESULT         (*pUsageDesc)(OBJ_ID, FILE *, PATH_DATA *);
    ERESULT         (*pUsageOptions)(OBJ_ID, FILE *);
    
};
#pragma pack(pop)

    extern
    const
    struct appl_class_data_s  appl_ClassObj;

    extern
    const
    APPL_VTBL         appl_Vtbl;


    // Internal Functions
    bool            appl_setDebug(
        APPL_DATA       *this,
        bool            fValue
    );
    
    
    bool            appl_setLastError(
        APPL_DATA     *this,
        ERESULT         value
    );
    
    
    bool            appl_setParseArgsDefaults(
        APPL_DATA       *this,
        ERESULT         (*pValue)(OBJ_ID)
    );
    
    
    bool            appl_setParseArgsKeywords(
        APPL_DATA       *this,
        void            (*pValue)(OBJ_ID, const char *)
    );
    
    
    APPL_CLO *      appl_ArgFindLong(
        APPL_DATA       *this,
        const
        char            *pLong
    );
    
    
    APPL_CLO *      appl_ArgFindShort(
        APPL_DATA       *this,
        char            chr
    );
    
    
    void            appl_Dealloc(
        OBJ_ID          objId
    );


    ASTR_DATA *     appl_ConstructProgramLine(
        int             cArgs,
        const
        char            **ppArgs
    );
    
    
    ERESULT         appl_Help(
        APPL_DATA       *this,
        ASTR_DATA       *pStr
    );
    
    
    ERESULT         appl_ParseArgsLong(
        APPL_DATA       *this,
        bool            fTrue,
        ASTR_DATA       *pArg
    );
    
    
    ERESULT         appl_ParseArgsShort(
        APPL_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    );
    
    
    void *          appl_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    void            appl_UsageArg(
        APPL_DATA       *this,
        ASTR_DATA       *pStr,              // in-out
        APPL_CLO        *pClo
    );
    
    
    void            appl_UsageNoMsg(
        APPL_DATA       *this
    );


#ifdef NDEBUG
#else
    bool			appl_Validate(
        APPL_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* APPL_INTERNAL_H */

