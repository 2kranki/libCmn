// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Array Object Interface (iObjArray) Header
//****************************************************************
/*
 * Program
 *			 Array Object Interface (iObjArray)
 * Purpose
 *          This Interface providing a common methods for working
 *          with an array of objects.
 *
 *
 * Remarks
 *	1.      Not all methods of this interface must be supported.
 *	        If they are not supported, a fake method must be
 *	        supplied that simply returns ERESULT_NOT_IMPLEMENTED.
 *
 * History
 *	08/10/2019 Created
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





#include        <cmn_defs.h>
#include        <Token.h>



#ifndef         IOBJARRAY_H
#define         IOBJARRAY_H

    
typedef struct iObjArray_vtbl_s    {
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.

    // Add an object to the end of the array (ie append).
    uint32_t         (*pGetSize) (
        OBJ_ID                          // Object Pointer
    );

    // Add an object to the end of the array (ie append).
    ERESULT         (*pAppendObj) (
        OBJ_ID          ,               // Object Pointer
        OBJ_ID          ,               // Object to be added 
        uint32_t        *               // Optional returned index 
        //                              // of the added object
    );

    // Delete an object from the array. 
    ERESULT         (*pDeleteObj) (
        OBJ_ID          ,               // Object Pointer
        uint32_t        index           // index (relative to 1)
    );

    // Get an array item's address using it's index. OBJ_NIL 
    // is returned if the item does not exist.
    OBJ_ID          (*pGetObj)(
            OBJ_ID      ,               // Object Pointer             
            uint32_t    index           // index (relative to 1)
    );

} IOBJARRAY_VTBL;

typedef struct iObjArray_interface_s    {
    IOBJARRAY_VTBL  *pVtbl;
} IOBJARRAY;
    
#define iArray_getSize(pIA)\
        ((IOBJARRAY *)(pIA))->pVtbl->pGetSize(pIA)
#define iArray_AppendObj(pIA,pObj,pIndex)\
        ((IOBJARRAY *)(pIA))->pVtbl->pAppendObj(pIA, pObj, pIndex)
#define iA_DeleteObj(pIA,index)\
        ((IOBJARRAY *)(pIA))->pVtbl->pDeleteObj(pIA, index)
#define iA_GetObj(pIA,index)\
        ((IOBJARRAY *)(pIA))->pVtbl->pGetObj(pIA, index)

#endif  // IOBJARRAY_H







