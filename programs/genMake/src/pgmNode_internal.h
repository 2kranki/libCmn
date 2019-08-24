// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   pgmNode_internal.h
 *	Generated 08/19/2019 01:14:29
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




#include        <pgmNode.h>
#include        <jsonIn.h>


#ifndef PGMNODE_INTERNAL_H
#define	PGMNODE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct pgmNode_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct pgmNode_class_data_s  pgmNode_ClassObj;

    extern
    const
    PGMNODE_VTBL         pgmNode_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PGMNODE_SINGLETON
    PGMNODE_DATA *     pgmNode_getSingleton (
        void
    );

    bool            pgmNode_setSingleton (
     PGMNODE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  pgmNode_getSuperVtbl (
        PGMNODE_DATA     *this
    );


    void            pgmNode_Dealloc (
        OBJ_ID          objId
    );


    PGMNODE_DATA *       pgmNode_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          pgmNode_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     pgmNode_ToJSON (
        PGMNODE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			pgmNode_Validate (
        PGMNODE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PGMNODE_INTERNAL_H */

