// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   u32Matrix_internal.h
 *	Generated 08/12/2018 23:54:39
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




#include        <u32Matrix.h>
#include        <jsonIn.h>


#ifndef U32MATRIX_INTERNAL_H
#define	U32MATRIX_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    typedef struct matrix_build_s {
        uint32_t        ySize;          // Height (Number of Rows, i)
        uint32_t        xSize;          // Width (Number of Columns, j)
        uint32_t        baseMax;        // Highest index allowed (m * n)
        uint32_t        maxBase;        // Current Highest Index Used
        uint32_t        highest;        // Highest pCheck entry used
        int32_t         *pBase;         // Row Base Index (j) into VALUE/CHECK
        uint32_t        *pCheck;        // Column Check for Row indexed from pBase
        uint32_t        *pValue;        // Row and Column value given Check
    } MATRIX_BUILD;
    
    

    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct u32Matrix_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        xSize;          // Width (x-axis, Number of Columns, i)
    uint32_t        ySize;          // Height (y-axis, Number of Rows, j)
    uint32_t        cElems;         // Size of Elems (ie m * n)
    uint32_t        *pElems;

};
#pragma pack(pop)

    extern
    const
    struct u32Matrix_class_data_s  u32Matrix_ClassObj;

    extern
    const
    U32MATRIX_VTBL         u32Matrix_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  u32Matrix_getSuperVtbl(
        U32MATRIX_DATA     *this
    );


    void            u32Matrix_Dealloc(
        OBJ_ID          objId
    );


    uint32_t        u32Matrix_index(
        U32MATRIX_DATA  *this,
        uint32_t        x,
        uint32_t        y
    );
    
    
    U32MATRIX_DATA * u32Matrix_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          u32Matrix_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     u32Matrix_ToJSON(
        U32MATRIX_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			u32Matrix_Validate(
        U32MATRIX_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* U32MATRIX_INTERNAL_H */

