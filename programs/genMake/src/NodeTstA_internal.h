// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeTstA_internal.h
 *	Generated 11/10/2019 17:54:48
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




#include        <NodeTstA.h>
#include        <NodeBase_internal.h>
#include        <JsonIn.h>


#ifndef NODETSTA_INTERNAL_H
#define	NODETSTA_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeTstA_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    NODEBASE_DATA   super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct NodeTstA_class_data_s  NodeTstA_ClassObj;

    extern
    const
    NODETSTA_VTBL         NodeTstA_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODETSTA_SINGLETON
    NODETSTA_DATA *     NodeTstA_getSingleton (
        void
    );

    bool            NodeTstA_setSingleton (
     NODETSTA_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeTstA_getSuperVtbl (
        NODETSTA_DATA     *this
    );


    void            NodeTstA_Dealloc (
        OBJ_ID          objId
    );


    NODETSTA_DATA *       NodeTstA_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          NodeTstA_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     NodeTstA_ToJSON (
        NODETSTA_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			NodeTstA_Validate (
        NODETSTA_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODETSTA_INTERNAL_H */

