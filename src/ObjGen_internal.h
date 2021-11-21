// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ObjGen_internal.h
 *  Generated 11/19/2021 06:00:58
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




#include        <ObjGen.h>
#include        <JsonIn.h>


#ifndef OBJGEN_INTERNAL_H
#define OBJGEN_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ObjGen_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStr;
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;

};
#pragma pack(pop)

    extern
    struct ObjGen_class_data_s  ObjGen_ClassObj;

    extern
    const
    OBJGEN_VTBL         ObjGen_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  OBJGEN_SINGLETON
    OBJGEN_DATA *     ObjGen_getSingleton (
        void
    );

    bool            ObjGen_setSingleton (
     OBJGEN_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ObjGen_getSuperVtbl (
        OBJGEN_DATA     *this
    );


    ERESULT         ObjGen_Assign (
        OBJGEN_DATA    *this,
        OBJGEN_DATA    *pOther
    );


    OBJGEN_DATA *       ObjGen_Copy (
        OBJGEN_DATA     *this
    );


    void            ObjGen_Dealloc (
        OBJ_ID          objId
    );


    OBJGEN_DATA *     ObjGen_DeepCopy (
        OBJGEN_DATA       *this
    );


#ifdef  OBJGEN_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    OBJGEN_DATA *       ObjGen_ParseJsonObject (
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
    ERESULT         ObjGen_ParseJsonFields (
        JSONIN_DATA     *pParser,
        OBJGEN_DATA     *pObject
    );
#endif


    void *          ObjGen_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  OBJGEN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjGen_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjGen_ToJson (
        OBJGEN_DATA      *this
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
    ERESULT         ObjGen_ToJsonFields (
        OBJGEN_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            ObjGen_Validate (
        OBJGEN_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* OBJGEN_INTERNAL_H */

