// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeList_internal.h
 *	Generated 11/23/2018 17:15:11
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




#include        <nodeList.h>
#include        <jsonIn.h>
#include        <nodeEnum_internal.h>
#include        <ObjList_internal.h>


#ifndef NODELIST_INTERNAL_H
#define	NODELIST_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct nodeList_data_s	{
    /* Warning - OBJLIST_DATA must be first in this object!
     */
    OBJLIST_DATA    super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pStr;

    volatile
    int32_t         numRead;
    // WARNING - 'elems' must be last element of this structure!
    uint32_t        elems[0];

};
#pragma pack(pop)

    extern
    struct nodeList_class_data_s  nodeList_ClassObj;

    extern
    const
    NODELIST_VTBL         nodeList_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODELIST_SINGLETON
    NODELIST_DATA * nodeList_getSingleton(
        void
    );

    bool            nodeList_setSingleton(
        NODELIST_DATA   *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  nodeList_getSuperVtbl(
        NODELIST_DATA   *this
    );


    void            nodeList_Dealloc(
        OBJ_ID          objId
    );


    NODELIST_DATA * nodeList_ParseJsonObject(
        JSONIN_DATA     *pParser
    );


    void *          nodeList_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     nodeList_ToJSON(
        NODELIST_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			nodeList_Validate(
        NODELIST_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODELIST_INTERNAL_H */

