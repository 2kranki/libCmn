// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   sidxe_internal.h
 *	Generated 12/18/2018 10:26:03
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




#include        <sidxe.h>
#include        <array.h>
#include        <JsonIn.h>


#ifndef SIDXE_INTERNAL_H
#define	SIDXE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct sidxe_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        max;		    // maximum number of entries
    uint16_t        reserved;
    uint32_t        maxLineNo;
    ASTR_DATA       *pStr;
    ARRAY_DATA      *pArray;

};
#pragma pack(pop)

    extern
    struct sidxe_class_data_s  sidxe_ClassObj;

    extern
    const
    SIDXE_VTBL         sidxe_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SIDXE_SINGLETON
    SIDXE_DATA *     sidxe_getSingleton (
        void
    );

    bool            sidxe_setSingleton (
     SIDXE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  sidxe_getSuperVtbl (
        SIDXE_DATA     *this
    );


    void            sidxe_Dealloc (
        OBJ_ID          objId
    );


    SIDXE_DATA *       sidxe_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          sidxe_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     sidxe_ToJSON (
        SIDXE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			sidxe_Validate (
        SIDXE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SIDXE_INTERNAL_H */

