// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SrcRef_internal.h
 *	Generated 12/05/2019 14:04:10
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




#include        <SrcRef.h>
#include        <jsonIn.h>


#ifndef SRCREF_INTERNAL_H
#define	SRCREF_INTERNAL_H



#define     PROPERTY_DIR_OWNED 1
#define     PROPERTY_NAME_OWNED 1
#define     PROPERTY_SUFFIX_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SrcRef_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTRC_DATA      *pDir;
    ASTRC_DATA      *pName;
    ASTRC_DATA      *pSuffix;

};
#pragma pack(pop)

    extern
    struct SrcRef_class_data_s  SrcRef_ClassObj;

    extern
    const
    SRCREF_VTBL         SrcRef_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SRCREF_SINGLETON
    SRCREF_DATA *     SrcRef_getSingleton (
        void
    );

    bool            SrcRef_setSingleton (
     SRCREF_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SrcRef_getSuperVtbl (
        SRCREF_DATA     *this
    );


    void            SrcRef_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SRCREF_JSON_SUPPORT
    SRCREF_DATA *       SrcRef_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          SrcRef_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     SrcRef_ToJson (
        SRCREF_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			SrcRef_Validate (
        SRCREF_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRCREF_INTERNAL_H */

