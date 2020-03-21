// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   U8VlArray_internal.h
 *	Generated 03/20/2020 11:56:58
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




#include        <U8VlArray.h>
#include        <JsonIn.h>


#ifndef U8VLARRAY_INTERNAL_H
#define	U8VLARRAY_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct U8VlArray_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
    #define U8VLARRAY_FLAG_ALLOC OBJ_FLAG_USER1

    // Common Data
    uint8_t         *pData;

};
#pragma pack(pop)

    extern
    struct U8VlArray_class_data_s  U8VlArray_ClassObj;

    extern
    const
    U8VLARRAY_VTBL         U8VlArray_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  U8VLARRAY_SINGLETON
    U8VLARRAY_DATA *     U8VlArray_getSingleton (
        void
    );

    bool            U8VlArray_setSingleton (
     U8VLARRAY_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  U8VlArray_getSuperVtbl (
        U8VLARRAY_DATA     *this
    );


    ERESULT         U8VlArray_Assign (
        U8VLARRAY_DATA    *this,
        U8VLARRAY_DATA    *pOther
    );


    U8VLARRAY_DATA *       U8VlArray_Copy (
        U8VLARRAY_DATA     *this
    );


    void            U8VlArray_Dealloc (
        OBJ_ID          objId
    );


#ifdef  U8VLARRAY_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    U8VLARRAY_DATA *       U8VlArray_ParseJsonObject (
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
    ERESULT         U8VlArray_ParseJsonFields (
        JSONIN_DATA     *pParser,
        U8VLARRAY_DATA     *pObject
    );
#endif


    void *          U8VlArray_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  U8VLARRAY_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = U8VlArray_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U8VlArray_ToJson (
        U8VLARRAY_DATA      *this
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
    ERESULT         U8VlArray_ToJsonFields (
        U8VLARRAY_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			U8VlArray_Validate (
        U8VLARRAY_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* U8VLARRAY_INTERNAL_H */

