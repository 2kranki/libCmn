// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   AStrCReader_internal.h
 *	Generated 08/11/2019 13:04:20
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




#include        <AStrCReader.h>
#include        <AStrC_internal.h>
#include        <jsonIn.h>


#ifndef ASTRCREADER_INTERNAL_H
#define	ASTRCREADER_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct AStrCReader_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTRC_DATA      *pStr;
    const
    char            *pData;

};
#pragma pack(pop)

    extern
    struct AStrCReader_class_data_s  AStrCReader_ClassObj;

    extern
    const
    ASTRCREADER_VTBL         AStrCReader_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  ASTRCREADER_SINGLETON
    ASTRCREADER_DATA *     AStrCReader_getSingleton (
        void
    );

    bool            AStrCReader_setSingleton (
     ASTRCREADER_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  AStrCReader_getSuperVtbl (
        ASTRCREADER_DATA     *this
    );


    void            AStrCReader_Dealloc (
        OBJ_ID          objId
    );


    ASTRCREADER_DATA *       AStrCReader_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          AStrCReader_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     AStrCReader_ToJSON (
        ASTRCREADER_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			AStrCReader_Validate (
        ASTRCREADER_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* ASTRCREADER_INTERNAL_H */

