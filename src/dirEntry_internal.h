// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   dirEntry_internal.h
 *	Generated 06/23/2015 20:03:11
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




#ifndef DIRENTRY_INTERNAL_H
#define	DIRENTRY_INTERNAL_H


#include        <dirEntry.h>
#include        <path.h>

#ifdef	__cplusplus
extern "C" {
#endif


#pragma pack(push, 1)
struct dirEntry_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    PATH_DATA       *pFullPath;
    PATH_DATA       *pDir;
    ASTR_DATA       *pName;
    ASTR_DATA       *pShortName;
    DATETIME_DATA   *pCreationTime;
    DATETIME_DATA   *pModifiedTime;
    DATETIME_DATA   *pStatusChangeTime;
    uint8_t         type;           // See DIRENTRY_TYPES
    uint8_t         reserved8;
    uint16_t        reserved16;
    uint32_t        attr;           // File Attributes (ie Read-Only, Hidden, ...)
#if     defined(__MACOSX_ENV__) || defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    uint64_t        fileSize;
#endif
    uint32_t        userID;
    uint32_t        groupID;
    uint32_t        genNum;
    uint32_t        eaSize;         // File Attributes Size in bytes

};
#pragma pack(pop)

    extern
    const
    struct dirEntry_class_data_s  dirEntry_ClassObj;
    
    extern
    const
    DIRENTRY_VTBL   dirEntry_Vtbl;



    // Internal Functions
    void            dirEntry_Dealloc(
        OBJ_ID          objId
    );


    void *          dirEntry_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );
    
    
#ifdef NDEBUG
#else
    bool			dirEntry_Validate(
        DIRENTRY_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DIRENTRY_INTERNAL_H */

