// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ExpandNodes_internal.h
 *	Generated 11/10/2019 17:43:09
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




#include        <ExpandNodes.h>
#include        <jsonIn.h>
#include        <NodeHdr.h>
#include        <NodeLib.h>
#include        <NodeObj.h>
#include        <NodePgm.h>
#include        <NodeRtn.h>
#include        <NodeRtnA.h>
#include        <NodeTest.h>
#include        <NodeTstA.h>
#include        <nodeArray_internal.h>


#ifndef EXPANDNODES_INTERNAL_H
#define	EXPANDNODES_INTERNAL_H



#define     PROPERTY_LIB_OWNED 1
#define     PROPERTY_PGM_OWNED 1
#define     PROPERTY_RTNS_OWNED 1
#define     PROPERTY_TESTS_OWNED 1
#define     PROPERTY_STR_OWNED 1
#define     PROPERTY_SUFFIXC_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ExpandNodes_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;
    DICT_DATA       *pDict;
    NODELIB_DATA    *pLib;
    NODEPGM_DATA    *pPgm;
    NODEARRAY_DATA  *pRtns;
    NODEARRAY_DATA  *pTests;
    ASTRC_DATA      *pSuffixC;

};
#pragma pack(pop)

    extern
    struct ExpandNodes_class_data_s  ExpandNodes_ClassObj;

    extern
    const
    EXPANDNODES_VTBL         ExpandNodes_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  EXPANDNODES_SINGLETON
    EXPANDNODES_DATA * ExpandNodes_getSingleton (
        void
    );

    bool            ExpandNodes_setSingleton (
     EXPANDNODES_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ExpandNodes_getSuperVtbl (
        EXPANDNODES_DATA    *this
    );


    void            ExpandNodes_Dealloc (
        OBJ_ID          objId
    );


    EXPANDNODES_DATA *  ExpandNodes_ParseJsonObject (
        JSONIN_DATA         *pParser
    );


    void *          ExpandNodes_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     ExpandNodes_ToJSON (
        EXPANDNODES_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			ExpandNodes_Validate (
        EXPANDNODES_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* EXPANDNODES_INTERNAL_H */

