// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   property_internal.h
 *	Generated 12/02/2018 23:32:21
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




#include        <property.h>
#include        <jsonIn.h>


#ifndef PROPERTY_INTERNAL_H
#define	PROPERTY_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct property_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pName;
    ASTR_DATA       *pDataName;
    ASTR_DATA       *pDesc;
    ASTR_DATA       *pDescShort;
    ASTR_DATA       *pType;
    ASTR_DATA       *pTypeInternal;
    uint32_t        cls;
    uint32_t        len;
    uint32_t        shift;
    uint32_t        mask;
    uint32_t        ptrlvl;
    uint8_t         fGenGet;
    uint8_t         fGenSet;
    uint8_t         fGenInternal;
    uint8_t         fOwned;

};
#pragma pack(pop)

    extern
    struct property_class_data_s  property_ClassObj;

    extern
    const
    PROPERTY_VTBL         property_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PROPERTY_SINGLETON
    PROPERTY_DATA *     property_getSingleton (
        void
    );

    bool            property_setSingleton (
     PROPERTY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  property_getSuperVtbl (
        PROPERTY_DATA     *this
    );


    void            property_Dealloc (
        OBJ_ID          objId
    );


    PROPERTY_DATA *       property_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          property_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     property_ToJSON (
        PROPERTY_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			property_Validate (
        PROPERTY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PROPERTY_INTERNAL_H */

