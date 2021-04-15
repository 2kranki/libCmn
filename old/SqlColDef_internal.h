// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SqlColDef_internal.h
 *	Generated 04/26/2020 11:52:28
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




#include        <SqlColDef.h>
#include        <JsonIn.h>


#ifndef SQLCOLDEF_INTERNAL_H
#define	SQLCOLDEF_INTERNAL_H





#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SqlColDef_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint8_t         type;
    uint8_t         decimalPlaces;
    uint8_t         seq;
    uint8_t         rsvd8;
    uint16_t        keySeq;
    uint16_t        rsvd16;
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
    struct SqlColDef_class_data_s  SqlColDef_ClassObj;

    extern
    const
    SQLCOLDEF_VTBL         SqlColDef_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SQLCOLDEF_SINGLETON
    SQLCOLDEF_DATA *     SqlColDef_getSingleton (
        void
    );

    bool            SqlColDef_setSingleton (
     SQLCOLDEF_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SqlColDef_getSuperVtbl (
        SQLCOLDEF_DATA     *this
    );


    ERESULT         SqlColDef_Assign (
        SQLCOLDEF_DATA    *this,
        SQLCOLDEF_DATA    *pOther
    );


    SQLCOLDEF_DATA *       SqlColDef_Copy (
        SQLCOLDEF_DATA     *this
    );


    void            SqlColDef_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SQLCOLDEF_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SQLCOLDEF_DATA *       SqlColDef_ParseJsonObject (
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
    ERESULT         SqlColDef_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SQLCOLDEF_DATA     *pObject
    );
#endif


    void *          SqlColDef_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SQLCOLDEF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlColDef_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlColDef_ToJson (
        SQLCOLDEF_DATA      *this
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
    ERESULT         SqlColDef_ToJsonFields (
        SQLCOLDEF_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool			SqlColDef_Validate (
        SQLCOLDEF_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SQLCOLDEF_INTERNAL_H */

