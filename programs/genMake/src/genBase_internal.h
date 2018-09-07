// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   genBase_internal.h
 *	Generated 04/10/2018 10:49:33
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




#include    <genBase.h>
#include    <fbso.h>
#include    <nodeHash.h>


#ifndef GENBASE_INTERNAL_H
#define	GENBASE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct genBase_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        makeType;       // Program, Library, etc
    uint16_t        osType;         // OSX, Win32, Win64, etc
    uint16_t        rsvd16;
    ASTR_DATA       *pName;         // (Not Owned)
    NODEHASH_DATA   *pDict;
    NODE_DATA       *pNodes;
    DATETIME_DATA   *pDateTime;
    TEXTOUT_DATA    *pOutput;
    NODEHASH_DATA   *pObjDirs;      // Object Directories
    // The following are filled in from sections of the Node Tree.
    NODEHASH_DATA   *pHeaders;      // (Not Owned)
    NODEARRAY_DATA  *pLibDeps;      // (Not Owned)
    NODEHASH_DATA   *pObjects;      // (Not Owned)
    NODEARRAY_DATA  *pPrograms;     // (Not Owned)
    NODEARRAY_DATA  *pRoutines;     // (Not Owned)
    NODEHASH_DATA   *pTests;        // (Not Owned)

    PATH_DATA *     (*pLibIncludePath)(GENBASE_DATA *, const char *, const char *, const char *);
    PATH_DATA *     (*pLibInstalledPath)(GENBASE_DATA *, const char *, const char *, const char *);
    ASTR_DATA *     (*pLibName)(GENBASE_DATA *, const char *, const char *);
    PATH_DATA *     (*pLibObjectPath)(GENBASE_DATA *, const char *, const char *, const char *);
    OBJ_ID          pLibObj;

};
#pragma pack(pop)

    extern
    const
    struct genBase_class_data_s  genBase_ClassObj;

    extern
    const
    GENBASE_VTBL         genBase_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            genBase_setObjDirs(
        GENBASE_DATA    *this,
        NODEHASH_DATA   *pValue
    );
    
    
    OBJ_IUNKNOWN *  genBase_getSuperVtbl(
        GENBASE_DATA     *this
    );


    void            genBase_Dealloc(
        OBJ_ID          objId
    );


    ERESULT         genBase_GenFinal(
        GENBASE_DATA    *this
    );
    
    
    ERESULT         genBase_GenInitial(
        GENBASE_DATA    *this
    );
    
    
    ERESULT         genBase_GenLibrary(
        GENBASE_DATA    *this
    );
    
    
    ERESULT         genBase_GenObject(
        GENBASE_DATA    *this,
        NODE_DATA       *pNode
    );
    
    ERESULT         genBase_GenObjects(
        GENBASE_DATA    *this
    );
    
    
    ERESULT         genBase_GenOSSpecific(
        GENBASE_DATA    *this
    );
    
    
    ERESULT         genBase_GenPrograms(
        GENBASE_DATA    *this
    );
    
    
    ERESULT         genBase_GenRoutines(
        GENBASE_DATA    *this
    );
    
    
    ERESULT         genBase_GenTests(
        GENBASE_DATA    *this
    );
    
    
    void *          genBase_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     genBase_ToJSON(
        GENBASE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			genBase_Validate(
        GENBASE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GENBASE_INTERNAL_H */

