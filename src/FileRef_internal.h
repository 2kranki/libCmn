// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   FileRef_internal.h
 *	Generated 12/06/2019 21:02:56
 *
 * Notes:
 *  --	N/A
 *
 */


/*
/Volumes/apple06_data/bob/git/libCmn/programs/genMake/src/SrcParse.h This is free and unencumbered software released into the public domain.
 
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




#include        <FileRef.h>
#include        <JsonIn.h>


#ifndef FILEREF_INTERNAL_H
#define	FILEREF_INTERNAL_H



#define     PROPERTY_DRV_OWNED 1
#define     PROPERTY_DIR_OWNED 1
#define     PROPERTY_EXT_OWNED 1
#define     PROPERTY_NAME_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct FileRef_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTRC_DATA      *pDrv;          // Drive
    ASTRC_DATA      *pDir;          // Directory
    ASTRC_DATA      *pName;         // File Name
    ASTRC_DATA      *pExt;          // File Extension

};
#pragma pack(pop)

    extern
    struct FileRef_class_data_s  FileRef_ClassObj;

    extern
    const
    FILEREF_VTBL         FileRef_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  FILEREF_SINGLETON
    FILEREF_DATA *     FileRef_getSingleton (
        void
    );

    bool            FileRef_setSingleton (
     FILEREF_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  FileRef_getSuperVtbl (
        FILEREF_DATA     *this
    );


    void            FileRef_Dealloc (
        OBJ_ID          objId
    );


#ifdef  FILEREF_JSON_SUPPORT
    FILEREF_DATA *       FileRef_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          FileRef_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     FileRef_ToJson (
        FILEREF_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			FileRef_Validate (
        FILEREF_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* FILEREF_INTERNAL_H */

