// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeEnum_internal.h
 *	Generated 11/23/2018 21:35:43
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




#include        <nodeEnum.h>
#include        <jsonIn.h>
#include        <objEnum_internal.h>


#ifndef NODEENUM_INTERNAL_H
#define	NODEENUM_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct nodeEnum_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJENUM_DATA    super;
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
    struct nodeEnum_class_data_s  nodeEnum_ClassObj;

    extern
    const
    NODEENUM_VTBL         nodeEnum_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEENUM_SINGLETON
    NODEENUM_DATA * nodeEnum_getSingleton (
        void
    );

    bool            nodeEnum_setSingleton (
     NODEENUM_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  nodeEnum_getSuperVtbl (
        NODEENUM_DATA     *this
    );


    ERESULT         nodeEnum_Append (
        NODEENUM_DATA   *this,
        NODE_DATA       *pNode
    );
    
    
    void            nodeEnum_Dealloc (
        OBJ_ID          objId
    );


    NODEENUM_DATA * nodeEnum_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          nodeEnum_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     nodeEnum_ToJSON (
        NODEENUM_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			nodeEnum_Validate (
        NODEENUM_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEENUM_INTERNAL_H */

