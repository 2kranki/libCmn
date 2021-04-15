// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SqlCol_internal.h
 *	Generated 04/25/2020 18:28:59
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




#include        <SqlCol.h>
#include        <JsonIn.h>


#ifndef SQLCOL_INTERNAL_H
#define	SQLCOL_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SqlCol_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint8_t         type;
    uint8_t         decimalPlaces;
    uint16_t        rsvd16;
    uint16_t        keySeq;
    uint16_t        colSeq;
    uint32_t        flags;
    int32_t         length;
    int32_t         lengthMin;
    ASTR_DATA       *pName;
    ASTR_DATA       *pCheckExpr;
    ASTR_DATA       *pDesc;
    ASTR_DATA       *pDefVal;

};
#pragma pack(pop)

    extern
    struct SqlCol_class_data_s  SqlCol_ClassObj;

    extern
    const
    SQLCOL_VTBL         SqlCol_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SQLCOL_SINGLETON
    SQLCOL_DATA *     SqlCol_getSingleton (
        void
    );

    bool            SqlCol_setSingleton (
     SQLCOL_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SqlCol_getSuperVtbl (
        SQLCOL_DATA     *this
    );


    ERESULT         SqlCol_Assign (
        SQLCOL_DATA    *this,
        SQLCOL_DATA    *pOther
    );


    SQLCOL_DATA *   SqlCol_Copy (
        SQLCOL_DATA     *this
    );


    void            SqlCol_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SQLCOL_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SQLCOL_DATA *       SqlCol_ParseJsonObject (
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
    ERESULT         SqlCol_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SQLCOL_DATA     *pObject
    );
#endif


    void *          SqlCol_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SQLCOL_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlCol_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_ToJson (
        SQLCOL_DATA      *this
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
    ERESULT         SqlCol_ToJsonFields (
        SQLCOL_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			SqlCol_Validate (
        SQLCOL_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SQLCOL_INTERNAL_H */

