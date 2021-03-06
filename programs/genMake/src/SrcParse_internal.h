// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SrcParse_internal.h
 *	Generated 08/19/2019 01:17:17
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




#include        <SrcParse.h>
#include        <JsonIn.h>


#ifndef SRCPARSE_INTERNAL_H
#define	SRCPARSE_INTERNAL_H



#define     PROPERTY_LIB_OWNED 1
#define     PROPERTY_NODES_OWNED 1
#define     PROPERTY_OBJS_OWNED 1
#define     PROPERTY_PGM_OWNED 1
#define     PROPERTY_RTNS_OWNED 1
#define     PROPERTY_TESTS_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SrcParse_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    NODELIB_DATA    *pLib;
    NODEARRAY_DATA  *pObjs;
    NODEPGM_DATA    *pPgm;
    NODEARRAY_DATA  *pRtns;
    NODEARRAY_DATA  *pTests;
    NODE_DATA       *pNodes;

};
#pragma pack(pop)

    extern
    struct SrcParse_class_data_s  SrcParse_ClassObj;

    extern
    const
    SRCPARSE_VTBL         SrcParse_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SRCPARSE_SINGLETON
    SRCPARSE_DATA *     SrcParse_getSingleton (
        void
    );

    bool            SrcParse_setSingleton (
     SRCPARSE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SrcParse_getSuperVtbl (
        SRCPARSE_DATA     *this
    );


    void            SrcParse_Dealloc (
        OBJ_ID          objId
    );


    void *          SrcParse_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     SrcParse_ToJSON (
        SRCPARSE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			SrcParse_Validate (
        SRCPARSE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SRCPARSE_INTERNAL_H */

