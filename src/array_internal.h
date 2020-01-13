// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   array_internal.h
 *	Generated 11/08/2017 09:27:01
 *
 * Notes:
 *  --
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




#include    <array.h>


#ifndef ARRAY_INTERNAL_H
#define	ARRAY_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

 #pragma pack(push, 1)
struct array_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        fZeroNew;       // Zero new space added
    uint16_t        elemSize;       // Element Size
    uint32_t        size;           // Controlled by User
    uint32_t        max;            // Number of Array Elements
    uint32_t        misc;           // Controlled by User
    uint8_t         *pArray;

};
#pragma pack(pop)

    extern
    const
    struct array_class_data_s  array_ClassObj;

    extern
    const
    ARRAY_VTBL         array_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            array_setElemSize(
        ARRAY_DATA      *this,
        uint16_t        value
    );
    
    
    uint32_t        array_getMax(
        ARRAY_DATA     *this
    );
    
    
    bool            array_setSize(
        ARRAY_DATA      *this,
        uint32_t        value
    );
    
    
    bool            array_setZeroNew(
        ARRAY_DATA      *this,
        uint16_t        value
    );
    
    
    ARRAY_DATA *    array_Copy(
        ARRAY_DATA      *this
    );
    
    
    void            array_Dealloc(
        OBJ_ID          objId
    );


    ARRAY_DATA *    array_DeepCopy(
        ARRAY_DATA      *this
    );
    
    
    ERESULT         array_Expand(
        ARRAY_DATA      *this,
        uint32_t        min
    );
    
    
    void            array_FreeArray(
        ARRAY_DATA      *this
    );
    
    
    uint32_t        array_OffsetOf(
        ARRAY_DATA      *this,
        uint32_t        index
    );
    
    
    void *          array_Ptr(
        ARRAY_DATA      *this,
        uint32_t        elem        // Element Number (relative to 1)
    );
    
    
    void *          array_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     array_ToJSON(
        ARRAY_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			array_Validate(
        ARRAY_DATA      *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* ARRAY_INTERNAL_H */

