// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   clo_internal.h
 *	Generated 06/05/2017 21:57:10
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




#include    <clo.h>
#include    <AStrArray.h>
#include    <path.h>


#ifndef CLO_INTERNAL_H
#define	CLO_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif



    typedef enum clo_opt_type_e {
        CLO_OPT_TYPE_UNKNOWN=0,
        CLO_OPT_TYPE_BOOL,
        CLO_OPT_TYPE_CSV,
        CLO_OPT_TYPE_DIR,
        CLO_OPT_TYPE_NODE,
        CLO_OPT_TYPE_NUMBER,
        CLO_OPT_TYPE_PATH,
        CLO_OPT_TYPE_STRING,
        CLO_OPT_TYPE_SWITCH,
        CLO_OPT_TYPE_VALUE,
    } CLO_OPT_TYPE;
    
    
    typedef struct clo_opt_dfn_s {
        char            argChr;
        const
        char            *pArgLong;
        uint16_t        type;
        uint16_t        rsvd16;
        uint32_t        size;           // in bytes
        const
        char            *pName;         // Node Name
    } CLO_OPT_DFN;
    
    
    


#pragma pack(push, 1)
struct clo_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    PATH_DATA       *pProgramPath;
    ASTR_DATA       *pCommandLine;
    ASTRARRAY_DATA  *pArgs;
    NODEHASH_DATA   *pCLO;
    uint8_t         fDebug;
    uint8_t         fForce;
    uint16_t        iVerbose;


    uint16_t        cProgramArgs1;
    uint16_t        cProgramArgs2;
    uint16_t        cGroupArgs;
    uint16_t        rsvd16;
    CLO_ARG         *pProgramArgs1;
    CLO_ARG         *pProgramArgs2;
    CLO_ARG         *pGroupArgs;
    uint8_t         *pProgramResults;           // Program Arguments
    uint8_t         *pGroupResults;             // Group Arguments and Options
    
    OBJ_ID          *pGroupObj;
    void            (*pGroupInit)(OBJ_ID, uint8_t *);
    
};
#pragma pack(pop)

    extern
    const
    struct clo_class_data_s  clo_ClassObj;

    extern
    const
    CLO_VTBL         clo_Vtbl;


    // Internal Functions
    void            clo_Dealloc(
        OBJ_ID          objId
    );

    void *          clo_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    bool            clo_setLastError(
        CLO_DATA     *this,
        ERESULT         value
    );




#ifdef NDEBUG
#else
    bool			clo_Validate(
        CLO_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CLO_INTERNAL_H */

