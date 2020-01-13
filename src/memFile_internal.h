// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   memFile_internal.h
 *	Generated 01/13/2019 15:55:16
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




#include        <memFile.h>
#include        <array.h>
#include        <JsonIn.h>


#ifndef MEMFILE_INTERNAL_H
#define	MEMFILE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct memFile_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define MEMFILE_FILE_OPEN    OBJ_FLAG_USER1

    // Common Data
    PATH_DATA       *pPath;
    ARRAY_DATA      *pData;
    off_t           offset;

};
#pragma pack(pop)

    extern
    struct memFile_class_data_s  memFile_ClassObj;

    extern
    const
    MEMFILE_VTBL         memFile_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  MEMFILE_SINGLETON
    MEMFILE_DATA *     memFile_getSingleton (
        void
    );

    bool            memFile_setSingleton (
     MEMFILE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  memFile_getSuperVtbl (
        MEMFILE_DATA     *this
    );


    void            memFile_Dealloc (
        OBJ_ID          objId
    );


    MEMFILE_DATA *       memFile_ParseObject (
        JSONIN_DATA     *pParser
    );


    void *          memFile_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ASTR_DATA *     memFile_ToJSON (
        MEMFILE_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			memFile_Validate (
        MEMFILE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* MEMFILE_INTERNAL_H */

