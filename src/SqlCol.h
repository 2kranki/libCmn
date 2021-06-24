// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  SQL Column Support (SqlCol) Header
//****************************************************************
/*
 * Program
 *          SQL Column Support (SqlCol)
 * Purpose
 *			This object provides support for dealing with an SQL
 *          column (of a table) and its data.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	04/25/2020 Generated
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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <Money64.h>
#include        <Value.h>


#ifndef         SQLCOL_H
#define         SQLCOL_H


//#define   SQLCOL_IS_IMMUTABLE     1
#define   SQLCOL_JSON_SUPPORT     1
//#define   SQLCOL_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SqlCol_data_s	SQLCOL_DATA;            // Inherits from OBJ
    typedef struct SqlCol_class_data_s SQLCOL_CLASS_DATA;   // Inherits from OBJ

    typedef struct SqlCol_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlCol_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCOL_DATA *);
    } SQLCOL_VTBL;

    typedef struct SqlCol_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SqlCol_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SQLCOL_DATA *);
    } SQLCOL_CLASS_VTBL;


    typedef enum SqlCol_types_e  {
        SQLCOL_TYPE_UNKNOWN=0,
        SQLCOL_TYPE_BIGINT,             // int64_t
        SQLCOL_TYPE_BLOB,
        SQLCOL_TYPE_BOOL,
        SQLCOL_TYPE_CHAR,
        SQLCOL_TYPE_DATE,
        SQLCOL_TYPE_DECIMAL,
        SQLCOL_TYPE_FILLER,
        SQLCOL_TYPE_INTEGER,            // int32_t
        SQLCOL_TYPE_MONEY64,
        SQLCOL_TYPE_NCHAR,
        SQLCOL_TYPE_NUMBER,
        SQLCOL_TYPE_NVARCHAR,
        SQLCOL_TYPE_REAL,
        SQLCOL_TYPE_SMALLINT,           // int16_t
        SQLCOL_TYPE_TEXT,
        SQLCOL_TYPE_TINYINT,            // int8_t
        SQLCOL_TYPE_VARCHAR             // Same as TEXT
    } SQLCOL_TYPES;


    typedef enum SqlCol_flags_e  {
        SQLCOL_FLAG_UNIQUE=0x0001,
        SQLCOL_FLAG_NOT_NULL=0x0002,
        SQLCOL_FLAG_AUTO_INC=0x0004,
        SQLCOL_FLAG_PRIM_KEY=0x0008,
    } SQLCOL_FLAGS;


    // This structure is designed so that this object can be initialized
    // from it using the FromStruct() method.
    typedef struct SqlCol_Struct_s {
        const
        char                *pName;             // (Required)
        const
        char                *pDescription;      // (Required)
        const
        char                *pTableName;        // (Optional)
        const
        char                *pDatabaseName;     // (Optional)
        uint8_t             type;               // see SQLCOL_TYPES
        uint16_t            keySequence;
        //                          0 == not a key column
        //                          1+ == column is part of the key in order
        //                                specified by this number
        int8_t              decimalPlaces;      // for SQLCOL_TYPE_REAL
        uint8_t             colSeq;             // Column Sequence number for CSV
        //                                      // or other formats (1+).
        int32_t             length;
        //                          For DBFIELD_TYPE_TEXT and DBFIELD_TYPE_VARCHAR,
        //                          a length of 0 just means that it is variable.
        int32_t             minimumLength;      // For use with TEXT, CHAR or VARCHAR
        uint32_t            flags;              // see SQLCOL_FLAGS
        const
        char                *pDefaultValue;     // Value to be placed inside DEFAULT( )
        //                                      // (Optional)
        const
        char                *pCheckExpression;  // Value to be placed inside CHECK( )
        //                                      // (Optional)
    } SQLCOL_STRUCT;





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SQLCOL_SINGLETON
    SQLCOL_DATA *   SqlCol_Shared (
        void
    );

    void            SqlCol_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SqlCol object if successful, otherwise OBJ_NIL.
     */
    SQLCOL_DATA *   SqlCol_Alloc (
        void
    );
    
    
    OBJ_ID          SqlCol_Class (
        void
    );
    
    
    SQLCOL_DATA *   SqlCol_New (
        void
    );
    
    SQLCOL_DATA *     SqlCol_NewFromStruct (
        const
        SQLCOL_STRUCT   *pStruct
    );


#ifdef  SQLCOL_JSON_SUPPORT
    SQLCOL_DATA *   SqlCol_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SQLCOL_DATA *   SqlCol_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTR_DATA *     SqlCol_getCheckExpr (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setCheckExpr (
        SQLCOL_DATA     *this,
        ASTR_DATA       *pValue
    );


    uint16_t        SqlCol_getColSeq (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setColSeq (
        SQLCOL_DATA     *this,
        uint16_t        value
    );


    ASTR_DATA *     SqlCol_getDatabaseName (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setDatabaseName (
        SQLCOL_DATA     *this,
        ASTR_DATA       *pValue
    );


    uint8_t         SqlCol_getDecimalPlaces (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setDecimalPlaces (
        SQLCOL_DATA     *this,
        uint8_t         value
    );


    ASTR_DATA *     SqlCol_getDefVal (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setDefVal (
        SQLCOL_DATA     *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     SqlCol_getDesc (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setDesc (
        SQLCOL_DATA     *this,
        ASTR_DATA       *pValue
    );


    uint32_t        SqlCol_getFlags (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setFlags (
        SQLCOL_DATA     *this,
        uint32_t        value
    );


    uint16_t        SqlCol_getKeySeq (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setKeySeq (
        SQLCOL_DATA     *this,
        uint16_t        value
    );


    int32_t         SqlCol_getLength (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setLength (
        SQLCOL_DATA     *this,
        int32_t         value
    );


    int32_t         SqlCol_getLengthMin (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setLengthMin (
        SQLCOL_DATA     *this,
        int32_t         value
    );


    ASTR_DATA *     SqlCol_getName (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setName (
        SQLCOL_DATA     *this,
        ASTR_DATA       *pValue
    );


    ASTR_DATA *     SqlCol_getTableName (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setTableName (
        SQLCOL_DATA     *this,
        ASTR_DATA       *pValue
    );


    uint8_t         SqlCol_getType (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setType (
        SQLCOL_DATA     *this,
        uint8_t         value
    );


    VALUE_DATA *    SqlCol_getValue (
        SQLCOL_DATA     *this
    );

    bool            SqlCol_setValue (
        SQLCOL_DATA     *this,
        VALUE_DATA      *pValue
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Compare the two provided object's Key Sequence.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             SqlCol_CompareKeySeq (
        SQLCOL_DATA     *this,
        SQLCOL_DATA     *pOther
    );


    /*!
     Compare the two provided object's Name.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             SqlCol_CompareName (
        SQLCOL_DATA     *this,
        SQLCOL_DATA     *pOther
    );


    int             SqlCol_CompareNameA (
        SQLCOL_DATA     *this,
        const
        char            *pNameA
    );


    /*!
     Construct the full name from the database, table and column names.
     @param     this    object pointer
     @return    if successful, AStr object which must be released.
                Otherwise, OBJ_NIL if an error occurred.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_FullName (
        SQLCOL_DATA     *this
    );


    /*!
     Initialize this object from the supplied struct.
     @param     this    object pointer
     @param     pStruct Struct pointer containing data
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code.
     */
    ERESULT         SqlCol_FromStruct (
        SQLCOL_DATA		*this,
        const
        SQLCOL_STRUCT   *pStruct
    );

   
    SQLCOL_DATA *   SqlCol_Init (
        SQLCOL_DATA     *this
    );


    ERESULT         SqlCol_IsEnabled (
        SQLCOL_DATA		*this
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
        SQLCOL_DATA   *this
    );
#endif


    /*!
     Convert the internal column definition to SQL.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                SQL, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_ToSQL (
        SQLCOL_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SqlCol_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_ToDebugString (
        SQLCOL_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SQLCOL_H */

