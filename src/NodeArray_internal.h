// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   NodeArray_internal.h
 *	Generated 01/10/2020 13:58:02
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




#include        <NodeArray.h>
#include        <JsonIn.h>
#include        <ObjArray.h>


#ifndef NODEARRAY_INTERNAL_H
#define	NODEARRAY_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct NodeArray_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJARRAY_DATA   *pArray;
    int             (*pCompare)(NODE_DATA *,NODE_DATA *);
    OBJ_ID          pOther;

};
#pragma pack(pop)

    extern
    struct NodeArray_class_data_s  NodeArray_ClassObj;

    extern
    const
    NODEARRAY_VTBL         NodeArray_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  NODEARRAY_SINGLETON
    NODEARRAY_DATA * NodeArray_getSingleton (
        void
    );

    bool            NodeArray_setSingleton (
     NODEARRAY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  NodeArray_getSuperVtbl (
        NODEARRAY_DATA     *this
    );


    void            NodeArray_Dealloc (
        OBJ_ID          objId
    );


#ifdef  NODEARRAY_JSON_SUPPORT
    NODEARRAY_DATA *       NodeArray_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          NodeArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  NODEARRAY_JSON_SUPPORT
    ASTR_DATA *     NodeArray_ToJson (
        NODEARRAY_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			NodeArray_Validate (
        NODEARRAY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEARRAY_INTERNAL_H */

