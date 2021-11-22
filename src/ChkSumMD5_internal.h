// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   ChkSumMD5_internal.h
 *  Generated 11/21/2021 14:37:54
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




#include        <ChkSumMD5.h>
#include        <JsonIn.h>
#include        <md5.h>


#ifndef CHKSUMMD5_INTERNAL_H
#define CHKSUMMD5_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct ChkSumMD5_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    ASTR_DATA       *pStrMD5;
    MD5_CTX         ctx;
    uint8_t         digest[16];

#ifdef   CHKSUMMD5_MSGS
    // Informational and Warning Log Messages
    void            (*pMsgInfo)(OBJ_ID, const char *, ...);
    void            (*pMsgWarn)(OBJ_ID, uint16_t, const char *, ...);
    OBJ_ID          pMsgObj;
#endif
};
#pragma pack(pop)

    extern
    struct ChkSumMD5_class_data_s  ChkSumMD5_ClassObj;

    extern
    const
    CHKSUMMD5_VTBL         ChkSumMD5_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CHKSUMMD5_SINGLETON
    CHKSUMMD5_DATA * ChkSumMD5_getSingleton (
        void
    );

    bool            ChkSumMD5_setSingleton (
     CHKSUMMD5_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  ChkSumMD5_getSuperVtbl (
        CHKSUMMD5_DATA  *this
    );


    ERESULT         ChkSumMD5_Assign (
        CHKSUMMD5_DATA  *this,
        CHKSUMMD5_DATA  *pOther
    );


    CHKSUMMD5_DATA * ChkSumMD5_Copy (
        CHKSUMMD5_DATA  *this
    );


    void            ChkSumMD5_Dealloc (
        OBJ_ID          objId
    );


    CHKSUMMD5_DATA * ChkSumMD5_DeepCopy (
        CHKSUMMD5_DATA  *this
    );


#ifdef  CHKSUMMD5_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    CHKSUMMD5_DATA * ChkSumMD5_ParseJsonObject (
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
    ERESULT         ChkSumMD5_ParseJsonFields (
        JSONIN_DATA     *pParser,
        CHKSUMMD5_DATA  *pObject
    );
#endif


    void *          ChkSumMD5_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  CHKSUMMD5_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ChkSumMD5_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ChkSumMD5_ToJson (
        CHKSUMMD5_DATA  *this
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
    ERESULT         ChkSumMD5_ToJsonFields (
        CHKSUMMD5_DATA  *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            ChkSumMD5_Validate (
        CHKSUMMD5_DATA  *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* CHKSUMMD5_INTERNAL_H */

