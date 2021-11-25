// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   PropItem_internal.h
 *  Generated 11/22/2021 12:43:21
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




#include        <PropItem.h>
#include        <GenItem_internal.h>
#include        <JsonIn.h>


#ifndef PROPITEM_INTERNAL_H
#define PROPITEM_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct PropItem_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        rsvd16;
    uint8_t         fObj;           // True == Object
    uint8_t         vis;            // See NODEPROP_VIS
    ASTR_DATA       *pExternal;     // Optional External Property Name
    ASTR_DATA       *pInit;         // Optional Initialization
    ASTR_DATA       *pInternal;     // Optional Internal Property Name
    ASTR_DATA       *pLong;         // Optional Long Description
    ASTR_DATA       *pName;         // Property Name
    ASTR_DATA       *pShort;        // Short Description
    ASTR_DATA       *pTypeDef;      // Type Definition

#ifdef   PROPITEM_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif
};
#pragma pack(pop)

    extern
    struct PropItem_class_data_s  PropItem_ClassObj;

    extern
    const
    PROPITEM_VTBL         PropItem_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  PROPITEM_SINGLETON
    PROPITEM_DATA *     PropItem_getSingleton (
        void
    );

    bool            PropItem_setSingleton (
     PROPITEM_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  PropItem_getSuperVtbl (
        PROPITEM_DATA     *this
    );


    ERESULT         PropItem_Assign (
        PROPITEM_DATA    *this,
        PROPITEM_DATA    *pOther
    );


    PROPITEM_DATA *       PropItem_Copy (
        PROPITEM_DATA     *this
    );


    void            PropItem_Dealloc (
        OBJ_ID          objId
    );


    PROPITEM_DATA *     PropItem_DeepCopy (
        PROPITEM_DATA       *this
    );


#ifdef  PROPITEM_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    PROPITEM_DATA *       PropItem_ParseJsonObject (
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
    ERESULT         PropItem_ParseJsonFields (
        JSONIN_DATA     *pParser,
        PROPITEM_DATA     *pObject
    );
#endif


    void *          PropItem_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  PROPITEM_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = PropItem_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     PropItem_ToJson (
        PROPITEM_DATA      *this
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
    ERESULT         PropItem_ToJsonFields (
        PROPITEM_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            PropItem_Validate (
        PROPITEM_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* PROPITEM_INTERNAL_H */

