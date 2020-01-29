// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   Path_internal.h
 *	Generated 01/29/2020 13:19:38
 *
 * Notes:
 *  --	N/A
 *
 */


//TODO: Normalize a pathname by collapsing redundant separators
//      and up-level references so that A//B, A/B/, A/./B and
//      A/foo/../B all become A/B
//TODO: Return the canonical path of the specified filename,
//      eliminating any symbolic links encountered in the path


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




#include        <Path.h>
#include        <AStr_internal.h>
#include        <file.h>
#include        <JsonIn.h>
#include        <utf8.h>


#ifndef PATH_INTERNAL_H
#define	PATH_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct Path_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    ASTR_DATA       super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct Path_class_data_s  Path_ClassObj;

    extern
    const
    PATH_VTBL         Path_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PATH_SINGLETON
    PATH_DATA *     Path_getSingleton (
        void
    );

    bool            Path_setSingleton (
     PATH_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  Path_getSuperVtbl (
        PATH_DATA     *this
    );


    ERESULT         Path_Assign (
        PATH_DATA    *this,
        PATH_DATA    *pOther
    );


    PATH_DATA *       Path_Copy (
        PATH_DATA     *this
    );


    void            Path_Dealloc (
        OBJ_ID          objId
    );


#ifdef  PATH_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    PATH_DATA *       Path_ParseJsonObject (
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
    ERESULT         Path_ParseJsonFields(
        JSONIN_DATA     *pParser,
        PATH_DATA     *pObject
    );
#endif


    void *          Path_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  PATH_JSON_SUPPORT
    ASTR_DATA *     Path_ToJson (
        PATH_DATA      *this
    );
#endif




#ifdef NDEBUG
#else
    bool			Path_Validate (
        PATH_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* PATH_INTERNAL_H */

