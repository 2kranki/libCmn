// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   blks_internal.h
 *	Generated 01/13/2019 16:16:32
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




#include        <blks.h>
#include        <JsonIn.h>
#include        <ptrArray.h>


#ifndef BLKS_INTERNAL_H
#define	BLKS_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct blks_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    uint32_t        blockSize;
    PTRARRAY_DATA   *pIndex;

};
#pragma pack(pop)

    extern
    struct blks_class_data_s  blks_ClassObj;

    extern
    const
    BLKS_VTBL         blks_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  BLKS_SINGLETON
    BLKS_DATA *     blks_getSingleton (
        void
    );

    bool            blks_setSingleton (
     BLKS_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  blks_getSuperVtbl (
        BLKS_DATA     *this
    );


    void            blks_Dealloc (
        OBJ_ID          objId
    );


    BLKS_DATA *       blks_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          blks_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     blks_ToJSON (
        BLKS_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			blks_Validate (
        BLKS_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* BLKS_INTERNAL_H */

