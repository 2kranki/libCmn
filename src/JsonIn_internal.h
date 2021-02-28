// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   JsonIn_internal.h
 *	Generated 12/30/2019 21:36:00
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




#include        <JsonIn.h>
#include        <ObjList.h>


#ifndef JSONIN_INTERNAL_H
#define	JSONIN_INTERNAL_H



#define     PROPERTY_HASH_OWNED 1
#define     PROPERTY_LIST_OWNED 1
#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct JsonIn_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJARRAY_DATA   *pClasses;
    ASTR_DATA       *pStr;
    NODEHASH_DATA   *pHash;
    OBJLIST_DATA    *pList;
    uint32_t        index;          // Current index into array.

};
#pragma pack(pop)

    extern
    struct JsonIn_class_data_s  JsonIn_ClassObj;

    extern
    const
    JSONIN_VTBL         JsonIn_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  JSONIN_SINGLETON
    JSONIN_DATA *   JsonIn_getSingleton (
        void
    );

    bool            JsonIn_setSingleton (
     JSONIN_DATA       *pValue
);
#endif


    OBJLIST_DATA *  JsonIn_RegisterList (
        void
    );



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  JsonIn_getSuperVtbl (
        JSONIN_DATA     *this
    );


    void            JsonIn_Dealloc (
        OBJ_ID          objId
    );


#ifdef  JSONIN_JSON_SUPPORT
    JSONIN_DATA *   JsonIn_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          JsonIn_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    ERESULT         JsonIn_ToDebugStringElement (
        JSONIN_DATA     *this,
        ASTR_DATA       *pStr,
        NODE_DATA       *pNode,
        bool            fInArray,
        int             indent
    );


#ifdef  JSONIN_JSON_SUPPORT
    ASTR_DATA *     JsonIn_ToJson (
        JSONIN_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			JsonIn_Validate (
        JSONIN_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* JSONIN_INTERNAL_H */

