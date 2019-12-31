// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeLink_internal.h
 *	Generated 06/30/2018 19:10:48
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




#include    <nodeLink.h>
#include    <JsonIn.h>
#include    <node_internal.h>


#ifndef NODELINK_INTERNAL_H
#define	NODELINK_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct nodeLink_data_s	{
    /* Warning - NODE_DATA must be first in this object!
     */
    NODE_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NODELINK_LEFT_LINK   OBJ_FLAG_USER5
#define NODELINK_RIGHT_LINK  OBJ_FLAG_USER6
#define NODELINK_RIGHT_CHILD OBJ_FLAG_USER7
    // OBJ_FLAG_USER1 and obj's misc2 are used by node.
    // obj's cbMisc1 is used for balance.

    // Common Data

    // Indices
    uint32_t        index;
    uint32_t        leftIndex;
    uint32_t        middleIndex;
    uint32_t        parentIndex;
    uint32_t        rightIndex;

};
#pragma pack(pop)

    extern
    struct nodeLink_class_data_s  nodeLink_ClassObj;

    extern
    const
    NODELINK_VTBL         nodeLink_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  nodeLink_getSuperVtbl(
        NODELINK_DATA     *this
    );


    void            nodeLink_Dealloc(
        OBJ_ID          objId
    );


    NODELINK_DATA * nodeLink_ParseObject(
        JSONIN_DATA     *pParser
    );


    ERESULT         nodeLink_ParseObjectFields(
        JSONIN_DATA     *pParser,
        NODELINK_DATA   *pObject
    );
    
    
    void *          nodeLink_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     nodeLink_ToJSON(
        NODELINK_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			nodeLink_Validate(
        NODELINK_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODELINK_INTERNAL_H */

