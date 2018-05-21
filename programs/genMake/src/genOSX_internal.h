// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   genOSX_internal.h
 *	Generated 04/18/2018 09:07:03
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




#include        <genOSX.h>


#ifndef GENOSX_INTERNAL_H
#define	GENOSX_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct genOSX_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pStr;
    GENBASE_DATA    *pBase;
    SZHASH_DATA     *pDict;
    FILE            *pOutput;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    const
    struct genOSX_class_data_s  genOSX_ClassObj;

    extern
    const
    GENOSX_VTBL         genOSX_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            genOSX_setLastError(
        GENOSX_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  genOSX_getSuperVtbl(
        GENOSX_DATA     *this
    );


    void            genOSX_Dealloc(
        OBJ_ID          objId
    );


    ERESULT         genOSX_GenFinal(
        GENOSX_DATA     *this,
        FILE            *pOutput
    );
    
    
    ERESULT         genOSX_GenInitial(
        GENOSX_DATA     *this,
        ASTR_DATA       *pName,
        NODEARRAY_DATA  *pLibDeps,
        DATETIME_DATA   *pDateTime,
        FILE            *pOutput
    );
    
    
    ERESULT         genOSX_GenLibrary(
        GENOSX_DATA     *this,
        FILE            *pOutput
    );
    
    
    ERESULT         genOSX_GenObjects(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pObjects,
        NODEARRAY_DATA  *pRoutines,
        FILE            *pOutput
    );
    
    
    ERESULT         genOSX_GenOSSpecific(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pSection,
        FILE            *pOutput
    );
    
    
    ERESULT         genOSX_GenPrograms(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pPrograms,
        FILE            *pOutput
    );
    
    
    ERESULT         genOSX_GenTests(
        GENOSX_DATA     *this,
        NODEHASH_DATA   *pTests,
        FILE            *pOutput
    );
    
    
    void *          genOSX_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     genOSX_ToJSON(
        GENOSX_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			genOSX_Validate(
        GENOSX_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GENOSX_INTERNAL_H */

