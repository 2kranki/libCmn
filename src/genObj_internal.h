// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   genObj_internal.h
 *	Generated 12/09/2017 07:54:00
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




#include    <genObj.h>
#include    <objHash.h>
#include    <szData.h>




#ifndef GENOBJ_INTERNAL_H
#define	GENOBJ_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct genObj_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    OBJHASH_DATA    *pHash;             // Hash of szData
    ASTR_DATA       *pDateTime;
    
};
#pragma pack(pop)

    extern
    const
    struct genObj_class_data_s  genObj_ClassObj;

    extern
    const
    GENOBJ_VTBL         genObj_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

   bool            genObj_setLastError(
        GENOBJ_DATA     *this,
        ERESULT         value
    );


    OBJ_IUNKNOWN *  genObj_getSuperVtbl(
        GENOBJ_DATA     *this
    );


    ASTR_DATA *     genObj_CreateSpacedComment(
        GENOBJ_DATA     *this,
        const
        char            *pStr
    );
    
    
    void            genObj_Dealloc(
        OBJ_ID          objId
    );


    ERESULT         genObj_GenDataEnd(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr             // (in/out)
    );
    
    
    ERESULT         genObj_GenDataStart(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        const
        char            *pIncludes
    );
    
    
    ERESULT         genObj_GenGetSet(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        uint32_t        offset,
        const
        char            *pDataType,
        const
        char            *pName,
        const
        char            *pPrefix
    );
    
    
    ERESULT         genObj_GenHeading(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr             // (in/out)
    );
    
    
    ERESULT         genObj_GenLicense(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr             // (in/out)
    );
    
    
    ERESULT         genObj_GenMethod(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        uint32_t        offset,
        const
        char            *pName,
        const
        char            *pReturns,
        const
        char            *pDataDefs,
        const
        char            *pBody,
        bool            fStatic
    );
    
    
    ERESULT         genObj_GenPgmEnd(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr             // (in/out)
    );
    
    
    ERESULT         genObj_GenPgmStart(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        const
        char            *pIncludes
    );
    
    
    ERESULT         genObj_GenSection(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        const
        char            *pDescription,
        bool            fSection
    );
    
    
    void *          genObj_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     genObj_ToJSON(
        GENOBJ_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			genObj_Validate(
        GENOBJ_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GENOBJ_INTERNAL_H */

