// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SQLite_internal.h
 *  Generated 07/26/2020 08:55:08
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




#include        <SQLite.h>
#include        <JsonIn.h>
#include        <ObjList.h>
#include        <sqlite3.h>


#ifndef SQLITE_INTERNAL_H
#define SQLITE_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SQLite_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    sqlite3         *pConn;
    PATH_DATA       *pPath;         // Database Path
    uint16_t        size;           // maximum number of elements
    uint16_t        rsvd16;
    ASTR_DATA       *pStr;

};
#pragma pack(pop)

    extern
    struct SQLite_class_data_s  SQLite_ClassObj;

    extern
    const
    SQLITE_VTBL         SQLite_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SQLITE_SINGLETON
    SQLITE_DATA *   SQLite_getSingleton (
        void
    );

    bool            SQLite_setSingleton (
     SQLITE_DATA        *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SQLite_getSuperVtbl (
        SQLITE_DATA     *this
    );


    ERESULT         SQLite_Assign (
        SQLITE_DATA     *this,
        SQLITE_DATA     *pOther
    );


    /*!
     Bind the given Value object to the given SQLite statement.
     @param     this    object pointer
     @param     pStmt   SQLite Statement pointer
     @param     idx     index into the statement for the value to be
                        assigned to
     @param     pValue  Value object pointer containing data to be
                        bound to the statement
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_BindValue (
        SQLITE_DATA     *this,
        sqlite3_stmt    *pStmt,
        int             idx,
        VALUE_DATA      *pValue
    );


    /*!
     Convert SQLite column data to SqlCol object.
     SQLite allows any column to contain any type of data regardless
     of the original table definition. We impose a stricter interpre-
     tation and require that data from SQLite conform to the type
     of data that we are expecting from the column definition.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    SQLCOL_DATA *   SQLite_ColDataToCol (
        SQLITE_DATA     *this,
        sqlite3_stmt    *pStmt,
        int             idx
    );


    SQLITE_DATA *   SQLite_Copy (
        SQLITE_DATA     *this
    );


    void            SQLite_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SQLITE_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SQLITE_DATA *   SQLite_ParseJsonObject (
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
    ERESULT         SQLite_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SQLITE_DATA     *pObject
    );
#endif


    void *          SQLite_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SQLITE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SQLite_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLite_ToJson (
        SQLITE_DATA     *this
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
    ERESULT         SQLite_ToJsonFields (
        SQLITE_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            SQLite_Validate (
        SQLITE_DATA     *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SQLITE_INTERNAL_H */

