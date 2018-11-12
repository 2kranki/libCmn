// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeBTree_internal.h
 *	Generated 11/12/2018 09:44:16
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




#include        <nodeBTree.h>
#include        <jsonIn.h>


#ifndef NODEBTREE_INTERNAL_H
#define	NODEBTREE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct nodeBTree_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
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
    struct nodeBTree_class_data_s  nodeBTree_ClassObj;

    extern
    const
    NODEBTREE_VTBL         nodeBTree_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEBTREE_SINGLETON
    NODEBTREE_DATA *     nodeBTree_getSingleton(
        void
    );

    bool            nodeBTree_setSingleton(
     NODEBTREE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  nodeBTree_getSuperVtbl(
        NODEBTREE_DATA     *this
    );


    void            nodeBTree_Dealloc(
        OBJ_ID          objId
    );


    NODEBTREE_DATA *       nodeBTree_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          nodeBTree_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     nodeBTree_ToJSON(
        NODEBTREE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			nodeBTree_Validate(
        NODEBTREE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEBTREE_INTERNAL_H */

