// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   BitMatrix_internal.h
 *	Generated 12/18/2019 08:00:28
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




#include        <BitMatrix.h>
#include        <JsonIn.h>


#ifndef BITMATRIX_INTERNAL_H
#define	BITMATRIX_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct BitMatrix_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        xSize;
    uint32_t        ySize;
    uint32_t        xWords;         // x-axis in words
    uint32_t        cElems;         // Size in 32-bit words
    uint32_t        rsvd32;
    uint32_t        *pElems;        // the array in x-axis

};
#pragma pack(pop)

    extern
    struct BitMatrix_class_data_s  BitMatrix_ClassObj;

    extern
    const
    BITMATRIX_VTBL         BitMatrix_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BITMATRIX_SINGLETON
    BITMATRIX_DATA * BitMatrix_getSingleton (
        void
    );

    bool            BitMatrix_setSingleton (
     BITMATRIX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  BitMatrix_getSuperVtbl (
        BITMATRIX_DATA     *this
    );


    void            BitMatrix_Dealloc (
        OBJ_ID          objId
    );


#ifdef  BITMATRIX_JSON_SUPPORT
    BITMATRIX_DATA * BitMatrix_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          BitMatrix_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         BitMatrix_SetSize(
        BITMATRIX_DATA  *this,
        uint32_t        ySize,
        uint32_t        xSize
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     BitMatrix_ToJson (
        BITMATRIX_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			BitMatrix_Validate (
        BITMATRIX_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BITMATRIX_INTERNAL_H */

