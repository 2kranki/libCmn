// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   nodeArray_internal.h
 *	Generated 08/08/2015 09:07:21
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



#include    <nodeArray.h>
#include    <ObjArray.h>
#include    <JsonIn.h>





#ifndef NODEARRAY_INTERNAL_H
#define	NODEARRAY_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct nodeArray_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;

    // Common Data
    OBJARRAY_DATA   *pArray;
    int             (*pCompare)(NODE_DATA *,NODE_DATA *);
    OBJ_ID          pOther;

};
#pragma pack(pop)

    extern
    NODEARRAY_CLASS_DATA  nodeArray_ClassObj;
    
    extern
    const
    NODEARRAY_VTBL  nodeArray_Vtbl;



    // Internal Functions
    void            nodeArray_Dealloc(
        OBJ_ID          objId
    );


    NODEARRAY_DATA * nodeArray_ParseJsonObject(
        JSONIN_DATA     *pParser
    );
    
    
    void *          nodeArray_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			nodeArray_Validate(
        NODEARRAY_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* NODEARRAY_INTERNAL_H */

