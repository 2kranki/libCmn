// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   main_internal.h
 *	Generated 07/17/2017 14:59:49
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




#include        <main.h>
#include        <appl_internal.h>


#ifndef MAIN_INTERNAL_H
#define	MAIN_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct main_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    APPL_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        makeType;       // See MAKETYPE
    uint16_t        reserved;
    SZHASH_DATA     *pDict;
    OBJ_ID          pGen;
    PATH_DATA       *pFilePath;
    PATH_DATA       *pOutputPath;
    NODE_DATA       *pNodes;
    TEXTOUT_DATA    *pOut;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct main_class_data_s  main_ClassObj;

    extern
    const
    MAIN_VTBL         main_Vtbl;


    // Internal Functions
    void            main_Dealloc(
        OBJ_ID          objId
    );

    ERESULT         main_ParseArgsDefault(
        MAIN_DATA        *this
    );
    
    int             main_ParseArgsLong(
        MAIN_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    );
    
    int             main_ParseArgsShort(
        MAIN_DATA       *this,
        int             *pArgC,
        const
        char            ***pppArgV
    );
    
    ERESULT         main_ParseInputFile(
        MAIN_DATA       *this,
        PATH_DATA       *pPath
    );
    
    ERESULT         main_ParseInputStr(
        MAIN_DATA       *this,
        const
        char            *pStr
    );
    
    ERESULT         main_ProcessInit(
        MAIN_DATA       *this
    );
    
    ERESULT         main_ProcessArg(
        MAIN_DATA       *this,
        ASTR_DATA       *pStr
    );
    
    void *          main_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    bool            main_setLastError(
        MAIN_DATA       *this,
        ERESULT         value
    );


    ERESULT         main_UsageDesc(
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pProgramPath
    );
    

    ERESULT         main_UsageProgLine(
        MAIN_DATA       *this,
        FILE            *pOutput,
        PATH_DATA       *pProgramPath,
        const
        char            *pNameA
    );
    
    
    ERESULT         main_UsageOptions(
        MAIN_DATA       *this,
        FILE            *pOutput
    );
    
    


#ifdef NDEBUG
#else
    bool			main_Validate(
        MAIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_INTERNAL_H */

