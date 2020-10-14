// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SqlCurs_internal.h
 *  Generated 10/11/2020 18:09:06
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




#include        <SqlCurs.h>
#include        <JsonIn.h>


#ifndef SQLCURS_INTERNAL_H
#define SQLCURS_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SqlCurs_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct SqlCurs_class_data_s  SqlCurs_ClassObj;

    extern
    const
    SQLCURS_VTBL         SqlCurs_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SQLCURS_SINGLETON
    SQLCURS_DATA *     SqlCurs_getSingleton (
        void
    );

    bool            SqlCurs_setSingleton (
     SQLCURS_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SqlCurs_getSuperVtbl (
        SQLCURS_DATA     *this
    );


    ERESULT         SqlCurs_Assign (
        SQLCURS_DATA    *this,
        SQLCURS_DATA    *pOther
    );


    SQLCURS_DATA *       SqlCurs_Copy (
        SQLCURS_DATA     *this
    );


    void            SqlCurs_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SQLCURS_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SQLCURS_DATA *       SqlCurs_ParseJsonObject (
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
    ERESULT         SqlCurs_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SQLCURS_DATA     *pObject
    );
#endif


    void *          SqlCurs_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SQLCURS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlCurs_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCurs_ToJson (
        SQLCURS_DATA      *this
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
    ERESULT         SqlCurs_ToJsonFields (
        SQLCURS_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            SqlCurs_Validate (
        SQLCURS_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SQLCURS_INTERNAL_H */

