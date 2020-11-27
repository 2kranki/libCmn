// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   DirEntry_internal.h
 *	Generated 01/28/2020 23:56:00
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




#include        <DirEntry.h>
#include        <JsonIn.h>


#ifndef DIRENTRY_INTERNAL_H
#define	DIRENTRY_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct DirEntry_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    DIRENTRY_DATA   *pNext;         // Dir/File Links
    PATH_DATA       *pFullPath;
    ASTR_DATA       *pShortName;
    DATETIME_DATA   *pCreationTime;
    DATETIME_DATA   *pModifiedTime;
    DATETIME_DATA   *pStatusChangeTime;
    uint16_t        type;           // See DIRENTRY_TYPES
    uint8_t         fCompleted;
    uint8_t         rsvd8;
    uint32_t        attr;           // File Attributes (ie Read-Only, Hidden, ...)
#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
    int64_t         fileSize;
#endif
#if     defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    int64_t         fileSize;
#endif
    uint32_t        userID;
    uint32_t        groupID;
    uint32_t        genNum;
    uint32_t        eaSize;         // File Attributes Size in bytes

};
#pragma pack(pop)

    extern
    struct DirEntry_class_data_s  DirEntry_ClassObj;

    extern
    const
    DIRENTRY_VTBL         DirEntry_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  DIRENTRY_SINGLETON
    DIRENTRY_DATA *     DirEntry_getSingleton (
        void
    );

    bool            DirEntry_setSingleton (
     DIRENTRY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  DirEntry_getSuperVtbl (
        DIRENTRY_DATA     *this
    );


    ERESULT         DirEntry_Assign (
        DIRENTRY_DATA    *this,
        DIRENTRY_DATA    *pOther
    );


    DIRENTRY_DATA *       DirEntry_Copy (
        DIRENTRY_DATA     *this
    );


    void            DirEntry_Dealloc (
        OBJ_ID          objId
    );


#ifdef  DIRENTRY_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    DIRENTRY_DATA *       DirEntry_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         DirEntry_ParseJsonFields(
        JSONIN_DATA     *pParser,
        DIRENTRY_DATA     *pObject
    );
#endif


    void *          DirEntry_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  DIRENTRY_JSON_SUPPORT
    ASTR_DATA *     DirEntry_ToJson (
        DIRENTRY_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			DirEntry_Validate (
        DIRENTRY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DIRENTRY_INTERNAL_H */

