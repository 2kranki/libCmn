// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   CsvRcd_internal.h
 *  Generated 07/16/2021 23:40:28
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




#include        <CsvRcd.h>
#include        <AStrArray.h>
#include        <JsonIn.h>


#ifndef CSVRCD_INTERNAL_H
#define CSVRCD_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct CsvRcd_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    W32STR_DATA     *pStr;
    ASTRARRAY_DATA  *pErrors;
    W32CHR_T        *pChr;
    W32CHR_T        *pEnd;
    uint32_t        col;
    W32CHR_T        fieldSeparator;
    W32CHR_T        lineEnd1;
    W32CHR_T        lineEnd2;

};
#pragma pack(pop)

    extern
    struct CsvRcd_class_data_s  CsvRcd_ClassObj;

    extern
    const
    CSVRCD_VTBL         CsvRcd_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CSVRCD_SINGLETON
    CSVRCD_DATA *     CsvRcd_getSingleton (
        void
    );

    bool            CsvRcd_setSingleton (
     CSVRCD_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  CsvRcd_getSuperVtbl (
        CSVRCD_DATA     *this
    );


    ERESULT         CsvRcd_Assign (
        CSVRCD_DATA    *this,
        CSVRCD_DATA    *pOther
    );


    CSVRCD_DATA *       CsvRcd_Copy (
        CSVRCD_DATA     *this
    );


    void            CsvRcd_Dealloc (
        OBJ_ID          objId
    );


#ifdef  CSVRCD_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    CSVRCD_DATA *       CsvRcd_ParseJsonObject (
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
    ERESULT         CsvRcd_ParseJsonFields (
        JSONIN_DATA     *pParser,
        CSVRCD_DATA     *pObject
    );
#endif


    void *          CsvRcd_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  CSVRCD_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = CsvRcd_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     CsvRcd_ToJson (
        CSVRCD_DATA      *this
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
    ERESULT         CsvRcd_ToJsonFields (
        CSVRCD_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            CsvRcd_Validate (
        CSVRCD_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* CSVRCD_INTERNAL_H */

