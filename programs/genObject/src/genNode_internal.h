// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   genNode_internal.h
 *	Generated 11/04/2018 19:07:17
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




#include        <genNode.h>
#include        <jsonIn.h>


#ifndef GENNODE_INTERNAL_H
#define	GENNODE_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct genNode_data_s	{
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
    struct genNode_class_data_s  genNode_ClassObj;

    extern
    const
    GENNODE_VTBL         genNode_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  GENNODE_SINGLETON
    GENNODE_DATA *     genNode_getSingleton(
        void
    );

    bool            genNode_setSingleton(
     GENNODE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  genNode_getSuperVtbl(
        GENNODE_DATA     *this
    );


    void            genNode_Dealloc(
        OBJ_ID          objId
    );


    GENNODE_DATA *       genNode_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          genNode_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     genNode_ToJSON(
        GENNODE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			genNode_Validate(
        GENNODE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* GENNODE_INTERNAL_H */
