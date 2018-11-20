// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeLnkP_internal.h
 *	Generated 11/19/2018 07:52:23
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




#include        <nodeLnkP.h>
#include        <jsonIn.h>
#include        <node_internal.h>


#ifndef NODELNKP_INTERNAL_H
#define	NODELNKP_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct nodeLnkP_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    NODE_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define NODELINK_LEFT_LINK   OBJ_FLAG_USER5
#define NODELINK_RIGHT_LINK  OBJ_FLAG_USER6
#define NODELINK_RIGHT_CHILD OBJ_FLAG_USER7
    // OBJ_FLAG_USER1 and obj's misc2 are used by node.
    // obj's cbMisc1 is used for balance.

    // Common Data
    NODELNKP_DATA   *pLeft;
    NODELNKP_DATA   *pMiddle;
    NODELNKP_DATA   *pParent;
    NODELNKP_DATA   *pRight;
    uint32_t        index;

};
#pragma pack(pop)

    extern
    struct nodeLnkP_class_data_s  nodeLnkP_ClassObj;

    extern
    const
    NODELNKP_VTBL         nodeLnkP_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODELNKP_SINGLETON
    NODELNKP_DATA *     nodeLnkP_getSingleton(
        void
    );

    bool            nodeLnkP_setSingleton(
     NODELNKP_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  nodeLnkP_getSuperVtbl(
        NODELNKP_DATA     *this
    );


    void            nodeLnkP_Dealloc(
        OBJ_ID          objId
    );


    NODELNKP_DATA *       nodeLnkP_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          nodeLnkP_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     nodeLnkP_ToJSON(
        NODELNKP_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			nodeLnkP_Validate(
        NODELNKP_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODELNKP_INTERNAL_H */

