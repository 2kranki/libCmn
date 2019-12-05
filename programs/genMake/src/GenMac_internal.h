// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   GenMac_internal.h
 *	Generated 11/23/2019 12:07:26
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




#include        <GenMac.h>
#include        <GenBase_internal.h>
#include        <jsonIn.h>


#ifndef GENMAC_INTERNAL_H
#define	GENMAC_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct GenMac_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    GENBASE_DATA    super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    // The following are required fields that must be filled in prior
    // to executing any generation.
    ASTRC_DATA      *pObjDir;       // Makefile Variable Name for
    //                              // object file output
    ASTRC_DATA      *pObjVar;       // Makefile Variable Name for
    //                              // accumulating object file names
    ASTRC_DATA      *pSrcDir;       // Makefile Variable Name used to
    //                              // prefix all source file names
    ASTRC_DATA      *pTstBin;       // Makefile Variable Name used to
    //                              // prefix all test compiled programs
    ASTRC_DATA      *pTstDir;       // Makefile Variable Name used to
    //                              // prefix all test source file names
    ASTRC_DATA      *pTstVar;       // Makefile Variable Name for
    //                              // accumulating test program names

};
#pragma pack(pop)

    extern
    struct GenMac_class_data_s  GenMac_ClassObj;

    extern
    const
    GENMAC_VTBL         GenMac_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  GENMAC_SINGLETON
    GENMAC_DATA *   GenMac_getSingleton (
        void
    );

    bool            GenMac_setSingleton (
     GENMAC_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  GenMac_getSuperVtbl (
        GENMAC_DATA     *this
    );


    void            GenMac_Dealloc (
        OBJ_ID          objId
    );


    GENMAC_DATA *   GenMac_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          GenMac_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     GenMac_ToJSON (
        GENMAC_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			GenMac_Validate (
        GENMAC_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GENMAC_INTERNAL_H */

