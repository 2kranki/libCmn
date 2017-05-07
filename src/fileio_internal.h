// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   fileio_internal.h
 *	Generated 07/30/2016 20:56:36
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



#include    <fileio.h>


#ifndef FILEIO_INTERNAL_H
#define	FILEIO_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




#pragma pack(push, 1)
struct fileio_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance

    // Common Data
    ERESULT         eRc;
    PATH_DATA       *pPath;
    uint32_t        headerSize;
    uint8_t         *pHeader;

};
#pragma pack(pop)

    extern
    const
    struct fileio_class_data_s  fileio_ClassObj;

    extern
    const
    FILEIO_VTBL         fileio_Vtbl;


    // Internal Functions
    void            fileio_Dealloc(
        OBJ_ID          objId
    );
    bool            fileio_setLastError(
        FILEIO_DATA     *this,
        ERESULT         value
    );



#ifdef NDEBUG
#else
    bool			fileio_Validate(
        FILEIO_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_INTERNAL_H */

