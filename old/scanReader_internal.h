// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   scanReader_internal.h
 *	Generated 08/11/2019 14:55:03
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




#include        <scanReader.h>
#include        <JsonIn.h>


#ifndef SCANREADER_INTERNAL_H
#define	SCANREADER_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct scanReader_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    const
    char            *pData;         // All of the Data
    const
    char            *pStr;          // Current Scan Pointer within Data
    SRCLOC          loc;

};
#pragma pack(pop)

    extern
    struct scanReader_class_data_s  scanReader_ClassObj;

    extern
    const
    SCANREADER_VTBL         scanReader_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SCANREADER_SINGLETON
    SCANREADER_DATA * scanReader_getSingleton (
        void
    );

    bool            scanReader_setSingleton (
     SCANREADER_DATA    *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  scanReader_getSuperVtbl (
        SCANREADER_DATA *this
    );


    bool            scanReader_setStr (
        SCANREADER_DATA *this,
        const
        char            *pValue
    );
    
    
    void            scanReader_Dealloc (
        OBJ_ID          objId
    );


    SCANREADER_DATA * scanReader_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          scanReader_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     scanReader_ToJSON (
        SCANREADER_DATA *this
    );




#ifdef NDEBUG
#else
    bool			scanReader_Validate (
        SCANREADER_DATA *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SCANREADER_INTERNAL_H */

