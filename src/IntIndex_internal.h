// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   IntIndex_internal.h
 *  Generated 01/03/2021 13:14:35
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




#include        <IntIndex.h>
#include        <array.h>
#include        <JsonIn.h>


#ifndef INTINDEX_INTERNAL_H
#define INTINDEX_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif


    typedef struct IntIdex_Node_s {
        int             index;
        void            *ptr;
    } INTINDEX_NODE;



    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct IntIndex_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ARRAY_DATA      *pArray;
    uint8_t         fSigned;
    uint8_t         rsvd8[3];

};
#pragma pack(pop)

    extern
    struct IntIndex_class_data_s  IntIndex_ClassObj;

    extern
    const
    INTINDEX_VTBL         IntIndex_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  INTINDEX_SINGLETON
    INTINDEX_DATA * IntIndex_getSingleton (
        void
    );

    bool            IntIndex_setSingleton (
     INTINDEX_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  IntIndex_getSuperVtbl (
        INTINDEX_DATA   *this
    );


    ERESULT         IntIndex_Assign (
        INTINDEX_DATA   *this,
        INTINDEX_DATA   *pOther
    );


    INTINDEX_DATA * IntIndex_Copy (
        INTINDEX_DATA   *this
    );


    void            IntIndex_Dealloc (
        OBJ_ID          objId
    );


#ifdef  INTINDEX_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    INTINDEX_DATA * IntIndex_ParseJsonObject (
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
    ERESULT         IntIndex_ParseJsonFields (
        JSONIN_DATA     *pParser,
        INTINDEX_DATA   *pObject
    );
#endif


    void *          IntIndex_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  INTINDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = IntIndex_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     IntIndex_ToJson (
        INTINDEX_DATA   *this
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
    ERESULT         IntIndex_ToJsonFields (
        INTINDEX_DATA   *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            IntIndex_Validate (
        INTINDEX_DATA   *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* INTINDEX_INTERNAL_H */

