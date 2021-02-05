// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   U32Index_internal.h
 *  Generated 01/04/2021 10:35:59
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




#include        <U32Index.h>
#include        <array.h>
#include        <JsonIn.h>


#ifndef U32INDEX_INTERNAL_H
#define U32INDEX_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    typedef struct U32Index_Node_s {
        uint32_t        index;
        void            *ptr;
    } U32INDEX_NODE;




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct U32Index_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint32_t        highest;        // Highest key in index
    ARRAY_DATA      *pArray;

};
#pragma pack(pop)

    extern
    struct U32Index_class_data_s  U32Index_ClassObj;

    extern
    const
    U32INDEX_VTBL         U32Index_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  U32INDEX_SINGLETON
    U32INDEX_DATA *     U32Index_getSingleton (
        void
    );

    bool            U32Index_setSingleton (
     U32INDEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  U32Index_getSuperVtbl (
        U32INDEX_DATA     *this
    );


    ERESULT         U32Index_Assign (
        U32INDEX_DATA    *this,
        U32INDEX_DATA    *pOther
    );


    U32INDEX_DATA *       U32Index_Copy (
        U32INDEX_DATA     *this
    );


    void            U32Index_Dealloc (
        OBJ_ID          objId
    );


#ifdef  U32INDEX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    U32INDEX_DATA *       U32Index_ParseJsonObject (
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
    ERESULT         U32Index_ParseJsonFields (
        JSONIN_DATA     *pParser,
        U32INDEX_DATA     *pObject
    );
#endif


    void *          U32Index_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  U32INDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = U32Index_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     U32Index_ToJson (
        U32INDEX_DATA      *this
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
    ERESULT         U32Index_ToJsonFields (
        U32INDEX_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            U32Index_Validate (
        U32INDEX_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* U32INDEX_INTERNAL_H */

