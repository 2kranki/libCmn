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
#include    <szHash.h>


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
    ERESULT         eRc;
    uint16_t        size;		    // maximum number of elements
    uint16_t        makeType;       // Program, Library, etc
    uint16_t        osType;         // OSX, Win32, Win64, etc
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;
    SZHASH_DATA     *pDict;
    NODE_DATA       *pNodes;
    DATETIME_DATA   *pDateTime;
    FBSO_DATA       *pOut;

    PATH_DATA *     (*pLibIncludePath)(GENBASE_DATA *, const char *, const char *, const char *);
    PATH_DATA *     (*pLibInstalledPath)(GENBASE_DATA *, const char *, const char *, const char *);
    ASTR_DATA *     (*pLibName)(GENBASE_DATA *, const char *, const char *);
    PATH_DATA *     (*pLibObjectPath)(GENBASE_DATA *, const char *, const char *, const char *);

    // Routines supplied by inheritors
    ERESULT         (*pFinal)(GENBASE_DATA *);
    ERESULT         (*pInitial)(GENBASE_DATA *, ASTR_DATA *, NODEARRAY_DATA  *);
    ERESULT         (*pLibrary)(GENBASE_DATA *);
    ERESULT         (*pObjects)(GENBASE_DATA *, NODEHASH_DATA *, NODEARRAY_DATA  *);
    ERESULT         (*pOsSpecific)(GENBASE_DATA *, NODEHASH_DATA  *);
    ERESULT         (*pPrograms)(GENBASE_DATA *, NODEHASH_DATA  *);
    ERESULT         (*pTests)(GENBASE_DATA *, NODEHASH_DATA *);

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

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

   bool            genBase_setLastError(
        GENBASE_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  genBase_getSuperVtbl(
        GENBASE_DATA     *this
    );


    void            genBase_Dealloc(
        OBJ_ID          objId
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

