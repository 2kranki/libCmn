// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   PathArray_internal.h
 *  Generated 12/23/2021 16:41:21
 *
 * Notes:
 *  --  N/A
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




#include        <PathArray.h>
#include        <ObjArray_internal.h>
#include        <JsonIn.h>


#ifndef PATHARRAY_INTERNAL_H
#define PATHARRAY_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct PathArray_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    OBJARRAY_DATA   *pArray;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

#ifdef   PATHARRAY_LOG
    // Informational and Warning Log Messages
    OBJ_ID          *pLog;
#endif
};
#pragma pack(pop)

    extern
    struct PathArray_class_data_s  PathArray_ClassObj;

    extern
    const
    PATHARRAY_VTBL         PathArray_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PATHARRAY_SINGLETON
    PATHARRAY_DATA *     PathArray_getSingleton (
        void
    );

    bool            PathArray_setSingleton (
     PATHARRAY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            PathArray_setArray (
        PATHARRAY_DATA  *this,
        OBJARRAY_DATA   *pValue
    );


    OBJ_DATA *      PathArray_getSuper (
        PATHARRAY_DATA  *this
    );


    OBJ_IUNKNOWN *  PathArray_getSuperVtbl (
        PATHARRAY_DATA  *this
    );


    ERESULT         PathArray_Assign (
        PATHARRAY_DATA  *this,
        PATHARRAY_DATA  *pOther
    );


    PATHARRAY_DATA * PathArray_Copy (
        PATHARRAY_DATA  *this
    );


    void            PathArray_Dealloc (
        OBJ_ID          objId
    );


    PATHARRAY_DATA * PathArray_DeepCopy (
        PATHARRAY_DATA  *this
    );


#ifdef  PATHARRAY_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    PATHARRAY_DATA * PathArray_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PathArray_ParseJsonFields (
        JSONIN_DATA     *pParser,
        PATHARRAY_DATA  *pObject
    );
#endif


    void *          PathArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  PATHARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PathArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PathArray_ToJson (
        PATHARRAY_DATA  *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         PathArray_ToJsonFields (
        PATHARRAY_DATA  *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            PathArray_Validate (
        PATHARRAY_DATA  *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* PATHARRAY_INTERNAL_H */

