// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   RpgBase_internal.h
 *  Generated 03/22/2021 07:15:24
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




#include        <RpgBase.h>
#include        <JsonIn.h>
#include        <ObjArray.h>


#ifndef RPGBASE_INTERNAL_H
#define RPGBASE_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct RpgBase_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;
    OBJ_ID          *pData;
    OBJ_ID          *pRcdCur;
    OBJ_ID          *pRcdNxt;
    OBJARRAY_DATA   *pLevels;

    uint8_t         lvlbrk1;
    uint8_t         lvlbrk2;
    uint8_t         lvlbrk3;
    uint8_t         lvlbrk4;
    uint8_t         lvlbrk5;
    uint8_t         lvlbrk6;
    uint8_t         lvlbrk7;
    uint8_t         lvlbrk8;
    uint8_t         lvlbrk9;
    uint8_t         rcdMatch;
    uint8_t         pg1;
    uint8_t         pgBrk;

};
#pragma pack(pop)

    extern
    struct RpgBase_class_data_s  RpgBase_ClassObj;

    extern
    const
    RPGBASE_VTBL         RpgBase_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  RPGBASE_SINGLETON
    RPGBASE_DATA *     RpgBase_getSingleton (
        void
    );

    bool            RpgBase_setSingleton (
     RPGBASE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  RpgBase_getSuperVtbl (
        RPGBASE_DATA     *this
    );


    ERESULT         RpgBase_Assign (
        RPGBASE_DATA    *this,
        RPGBASE_DATA    *pOther
    );


    RPGBASE_DATA *       RpgBase_Copy (
        RPGBASE_DATA     *this
    );


    void            RpgBase_Dealloc (
        OBJ_ID          objId
    );


#ifdef  RPGBASE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    RPGBASE_DATA *       RpgBase_ParseJsonObject (
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
    ERESULT         RpgBase_ParseJsonFields (
        JSONIN_DATA     *pParser,
        RPGBASE_DATA     *pObject
    );
#endif


    void *          RpgBase_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  RPGBASE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = RpgBase_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     RpgBase_ToJson (
        RPGBASE_DATA      *this
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
    ERESULT         RpgBase_ToJsonFields (
        RPGBASE_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            RpgBase_Validate (
        RPGBASE_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* RPGBASE_INTERNAL_H */

