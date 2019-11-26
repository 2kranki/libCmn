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
#include        <genBase_internal.h>


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
    GENBASE_DATA    super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pName;
 
    PATH_DATA *     (*pLibIncludePath)(GENOSX_DATA *, const char *, const char *, const char *);
    PATH_DATA *     (*pLibInstalledPath)(GENOSX_DATA *, const char *, const char *, const char *);
    ASTR_DATA *     (*pLibName)(GENOSX_DATA *, const char *, const char *);
    PATH_DATA *     (*pLibObjectPath)(GENOSX_DATA *, const char *, const char *, const char *);
    
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

    OBJ_IUNKNOWN *  genOSX_getSuperVtbl(
        GENOSX_DATA     *this
    );


    ASTR_DATA *     genOSX_CompileObjectStr(
        GENOSX_DATA     *this,
        const
        char            *pName,             // Object Class Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir,
        const
        char            *pObjVar
    );
    
    
    ASTR_DATA *     genOSX_CompileRoutineStr(
        GENOSX_DATA     *this,
        const
        char            *pName,             // Object Class Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir,
        const
        char            *pObjVar
    );
    
    
    void            genOSX_Dealloc(
        OBJ_ID          objId
    );


    ASTR_DATA *     genOSX_GenFinal(
        GENOSX_DATA     *this
    );
    
    
    ASTR_DATA *     genOSX_GenInitial(
        GENOSX_DATA     *this
    );
    
    
    ERESULT         genOSX_GenLibrary(
        GENOSX_DATA     *this
    );
    
    
    ERESULT         genOSX_GenObjects(
        GENOSX_DATA     *this
    );
    
    
    ERESULT         genOSX_GenOSSpecific(
        GENOSX_DATA     *this
    );
    
    
    ERESULT         genOSX_GenRoutines(
        GENOSX_DATA     *this
    );
    
    
    ERESULT         genOSX_GenTests(
        GENOSX_DATA     *this
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

