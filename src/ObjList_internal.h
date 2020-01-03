// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjList_internal.h
 *	Generated 12/15/2019 12:58:04
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




#include    <ObjList.h>
#include    <JsonIn.h>
#include    <listdl.h>
#include    <blocks_internal.h>


#ifndef OBJLIST_INTERNAL_H
#define	OBJLIST_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif


    //      Hash Node Descriptor
#pragma pack(push, 1)
    typedef struct  objList_record_s {
        LISTDL_NODE     list;
        OBJ_ID          pObject;
        uint32_t        unique;
        uint32_t        user;
    } OBJLIST_RECORD;
#pragma pack(pop)
    
    


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjList_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    BLOCKS_DATA     super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    #define LIST_FLAG_ORDERED OBJ_FLAG_USER1

    // Common Data
    LISTDL_DATA     list;           // Main List
    OBJLIST_RECORD  *pCur;
    uint32_t        unique;

};
#pragma pack(pop)

    extern
    struct ObjList_class_data_s  ObjList_ClassObj;

    extern
    const
    OBJLIST_VTBL         ObjList_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJLIST_SINGLETON
    OBJLIST_DATA *  ObjList_getSingleton (
        void
    );

    bool            ObjList_setSingleton (
     OBJLIST_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    LISTDL_DATA *   ObjList_getList (
        OBJLIST_DATA    *this
    );


    OBJ_IUNKNOWN *  ObjList_getSuperVtbl (
        OBJLIST_DATA     *this
    );


    void            ObjList_Dealloc (
        OBJ_ID          objId
    );


    OBJLIST_RECORD * ObjList_FindObj(
        OBJLIST_DATA    *this,
        OBJ_ID          pObj
    );


#ifdef  OBJLIST_JSON_SUPPORT
    OBJLIST_DATA *   ObjList_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    void *          ObjList_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     ObjList_ToJson (
        OBJLIST_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			ObjList_Validate (
        OBJLIST_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* OBJLIST_INTERNAL_H */

