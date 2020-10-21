// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   SqlStmt_internal.h
 *  Generated 10/20/2020 13:49:42
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




#include        <SqlStmt.h>
#include        <JsonIn.h>
#import         <sqlite3.h>


#ifndef SQLSTMT_INTERNAL_H
#define SQLSTMT_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct SqlStmt_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    sqlite3_stmt    *pSqlStmt;
    ASTR_DATA       *pStmt;
    SQLITE_DATA     *pDB;

};
#pragma pack(pop)

    extern
    struct SqlStmt_class_data_s  SqlStmt_ClassObj;

    extern
    const
    SQLSTMT_VTBL         SqlStmt_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  SQLSTMT_SINGLETON
    SQLSTMT_DATA *     SqlStmt_getSingleton (
        void
    );

    bool            SqlStmt_setSingleton (
     SQLSTMT_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  SqlStmt_getSuperVtbl (
        SQLSTMT_DATA     *this
    );


    ERESULT         SqlStmt_Assign (
        SQLSTMT_DATA    *this,
        SQLSTMT_DATA    *pOther
    );


    SQLSTMT_DATA *       SqlStmt_Copy (
        SQLSTMT_DATA     *this
    );


    void            SqlStmt_Dealloc (
        OBJ_ID          objId
    );


#ifdef  SQLSTMT_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    SQLSTMT_DATA *       SqlStmt_ParseJsonObject (
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
    ERESULT         SqlStmt_ParseJsonFields (
        JSONIN_DATA     *pParser,
        SQLSTMT_DATA     *pObject
    );
#endif


    void *          SqlStmt_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SQLSTMT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SqlStmt_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlStmt_ToJson (
        SQLSTMT_DATA      *this
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
    ERESULT         SqlStmt_ToJsonFields (
        SQLSTMT_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif




#ifdef NDEBUG
#else
    bool            SqlStmt_Validate (
        SQLSTMT_DATA       *this
    );
#endif



#ifdef  __cplusplus
}
#endif

#endif  /* SQLSTMT_INTERNAL_H */

