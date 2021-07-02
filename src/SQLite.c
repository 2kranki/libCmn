// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SQLite.c
 *  Generated 07/26/2020 08:55:08
 *
 * To get names of all databases currently open:
    PRAGMA database_list;
 * To retrieve all table names:
    SELECT name FROM sqlite_master
        WHERE type IN ('table','view') AND name NOT LIKE 'sqlite_%'
    UNION ALL
    SELECT name FROM sqlite_temp_master
        WHERE type IN ('table','view')
    ORDER BY 1;
 * To get columns of a table:
    PRAGMA table_info(<table_name>);
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <SQLite_internal.h>
#include        <dec.h>
#include        <trace.h>
#include        <Value_internal.h>
#include        <ValueArray_internal.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    typedef struct table_cb_work_st {
        SQLITE_DATA     *this;
        ASTRCARRAY_DATA *pArray;
    } table_cb_work;


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    // int (*pCallback)(void*,int,char**,char**)
    __attribute__((unused))
    static
    int             SQLite_dump_callback (
        void            *pData,
        int             numCols,
        char            **pColText,
        char            **pColName
    )
    {
        //SQLITE_DATA     *this = pData;
        uint32_t        i;

        for (i=0; i<numCols; ++i) {
            fprintf(stderr, "\t%15s: %s\n", pColName[i], pColText[i]);
        }

        return SQLITE_OK;
    }



    // int (*pCallback)(void*,int,char**,char**)
    static
    int             SQLite_table_callback (
        void            *pData,
        int             numCols,
        char            **pColText,
        char            **pColName
    )
    {
        ERESULT         eRc;
        table_cb_work   *pWork = pData;
        int             i;
        bool            fDisplay = false;
        const
        char            *pNameA = NULL;
        bool            fSqliteName = false;

        // The sqlite_master.tbl_name column holds the name of a table or view that the
        // object is associated with. For a table or view, the tbl_name column is a copy
        // of the name column. For an index, the tbl_name is the name of the table that
        // is indexed. For a trigger, the tbl_name column stores the name of the table or
        // view that causes the trigger to fire.

        for (i=0; i<numCols; ++i) {
            if (((strcmp(pColName[i], "type") == 0) && (strcmp(pColText[i], "table") == 0))) {
                fDisplay = true;
            }
            if ((strcmp(pColName[i], "name") == 0) && (strncmp(pColText[i], "sqlite_", 7) == 0))
                fSqliteName = true;
            if (strcmp(pColName[i], "name") == 0) {
                pNameA = pColText[i];
            }
        }
        if (fDisplay) {
            if (pNameA && !fSqliteName) {
                TRC_OBJ(pWork->this, "\tName: %s\n", pNameA);
                if (pWork->pArray) {
                    eRc = AStrCArray_AppendA(pWork->pArray, pNameA, NULL);
                    if (ERESULT_FAILED(eRc)) {
                        return SQLITE_ABORT;
                    }
                }
            }
        }

        return SQLITE_OK;
    }


    // int (*pCallback)(void*,int,char**,char**)
    static
    int             SQLite_tableCount_callback (
        void            *pData,
        int             numCols,
        char            **pColText,
        char            **pColName
    )
    {
        uint32_t        *pCount = pData;

        if (numCols == 1) {
            if (strcmp(pColName[0], "cRcds") == 0) {
                *pCount = dec_getInt32A(pColText[0]);
            }
        }


        return SQLITE_OK;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SQLITE_DATA *     SQLite_Alloc (
        void
    )
    {
        SQLITE_DATA       *this;
        uint32_t        cbSize = sizeof(SQLITE_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SQLITE_DATA *   SQLite_New (
        void
    )
    {
        SQLITE_DATA     *this;
        
        this = SQLite_Alloc( );
        if (this) {
            this = SQLite_Init(this);
        } 
        return this;
    }


    SQLITE_DATA *   SQLite_NewPath (
        PATH_DATA       *pPath
    )
    {
        SQLITE_DATA     *this;
        ERESULT         eRc;

        this = SQLite_New( );
        if (this) {
            eRc = SQLite_Open(this, pPath);
            if (ERESULT_FAILED(eRc)) {
                obj_Release(this);
                this = OBJ_NIL;
            }
        }
        return this;
    }



    /*!
     Create a string that describes this object and the objects within it.
     @param     pCol    Column Definition Entry
     @return    If successful, an AStr object which must be released containing the
                SQL, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLite_SQL_ColCreate (
        SQLCOL_STRUCT   *pCol
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;

        // Do initialization.
#ifdef NDEBUG
#else
        if (NULL == pCol) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        if (pCol->pName) {
            eRc = AStr_AppendA(pStr, pCol->pName);
        } else {
            obj_Release(pStr);
            return OBJ_NIL;
        }
        switch (pCol->type) {
            case SQLCOL_TYPE_BIGINT:
                eRc = AStr_AppendA(pStr, " BIGINT");
                break;
            case SQLCOL_TYPE_BLOB:
                eRc = AStr_AppendA(pStr, " BLOB");
                break;
            case SQLCOL_TYPE_BOOL:
                eRc = AStr_AppendA(pStr, " BOOL");
                break;
            case SQLCOL_TYPE_CHAR:
                eRc = AStr_AppendPrint(pStr, " CHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_DATE:
                eRc = AStr_AppendA(pStr, " DATE");
                break;
            case SQLCOL_TYPE_DECIMAL:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_FILLER:
                eRc = AStr_AppendPrint(pStr, " CHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_INTEGER:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_MONEY64:
                eRc = AStr_AppendA(pStr, " BIGINT");
                break;
            case SQLCOL_TYPE_NCHAR:
                eRc = AStr_AppendPrint(pStr, " NCHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_NUMBER:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_NVARCHAR:
                eRc = AStr_AppendPrint(pStr, " NVARCHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_REAL:
                eRc = AStr_AppendA(pStr, " REAL");
                break;
            case SQLCOL_TYPE_SMALLINT:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_TEXT:
                eRc = AStr_AppendA(pStr, " TEXT");
                break;
            case SQLCOL_TYPE_TINYINT:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_VARCHAR:
                eRc = AStr_AppendPrint(pStr, " VARCHAR(%d)", pCol->length);
                break;
            default:
                obj_Release(pStr);
                return OBJ_NIL;
                break;
        }

        if (pCol->flags & SQLCOL_FLAG_AUTO_INC) {
            eRc = AStr_AppendA(pStr, " AUTOINCREMENT");
        }
        if (pCol->flags & SQLCOL_FLAG_NOT_NULL) {
            eRc = AStr_AppendA(pStr, " NOT NULL");
        }
        if (pCol->flags & SQLCOL_FLAG_UNIQUE) {
            eRc = AStr_AppendA(pStr, " UNIQUE");
        }
        if (pCol->flags & SQLCOL_FLAG_PRIM_KEY) {
            eRc = AStr_AppendA(pStr, " PRIMARY KEY");
        }

        if (pCol->pDefaultValue) {
            eRc = AStr_AppendPrint(pStr, " DEFAULT( %d )", pCol->pDefaultValue);
        }

        return pStr;
    }



    ASTR_DATA *     SQLite_SQL_ColFromData (
        SQLCOL_STRUCT   *pCol,
        OBJ_ID          *pData
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        ASTR_DATA       *pWrkStr = OBJ_NIL;
        //DATA_DATA       *pData = OBJ_NIL;
        MONEY64_DATA    *pMoney = OBJ_NIL;
        VALUE_DATA      *pValue = OBJ_NIL;
        //uint32_t        i;
        //uint32_t        j;

        // Do initialization.
#ifdef NDEBUG
#else
        if (NULL == pCol) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        if (NULL == pData) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        // Figure out what data that we have to work with.
        if (obj_getType(pData) == OBJ_IDENT_VALUE) {
            pValue = (VALUE_DATA *)pData;
            if (Value_getType(pValue) == VALUE_TYPE_ASTR) {
                pWrkStr = Value_getAStr(pValue);
            } else if (Value_getType(pValue) == VALUE_TYPE_DATA) {
                //pData = Value_getData(pValue);
            } else if (Value_getType(pValue) == VALUE_TYPE_OBJECT) {
                 //OBJ_ID          pObj = Value_getObject(pValue);
            }
        } else if (obj_getType(pData) == OBJ_IDENT_ASTR) {
            pWrkStr = (ASTR_DATA *)pData;
        } else if (obj_getType(pData) == OBJ_IDENT_MONEY64) {
            pMoney = (MONEY64_DATA *)pData;
        } else {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }

        if (pCol->pName) {
            eRc = AStr_AppendA(pStr, pCol->pName);
        } else {
            obj_Release(pStr);
            return OBJ_NIL;
        }
        switch (pCol->type) {
            case SQLCOL_TYPE_BIGINT:
                eRc = AStr_AppendA(pStr, " BIGINT");
                break;
            case SQLCOL_TYPE_BLOB:
                eRc = AStr_AppendA(pStr, " BLOB");
                break;
            case SQLCOL_TYPE_BOOL:
                eRc = AStr_AppendA(pStr, " BOOL");
                break;
            case SQLCOL_TYPE_CHAR:
                eRc = AStr_AppendPrint(pStr, " CHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_DATE:
                eRc = AStr_AppendA(pStr, " DATE");
                break;
            case SQLCOL_TYPE_DECIMAL:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_FILLER:
                eRc = AStr_AppendPrint(pStr, " CHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_INTEGER:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_MONEY64:
                eRc = AStr_AppendA(pStr, " BIGINT");
                break;
            case SQLCOL_TYPE_NCHAR:
                eRc = AStr_AppendPrint(pStr, " NCHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_NUMBER:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_NVARCHAR:
                eRc = AStr_AppendPrint(pStr, " NVARCHAR(%d)", pCol->length);
                break;
            case SQLCOL_TYPE_REAL:
                eRc = AStr_AppendA(pStr, " REAL");
                break;
            case SQLCOL_TYPE_SMALLINT:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_TEXT:
                eRc = AStr_AppendA(pStr, " TEXT");
                break;
            case SQLCOL_TYPE_TINYINT:
                eRc = AStr_AppendA(pStr, " INTEGER");
                break;
            case SQLCOL_TYPE_VARCHAR:
                eRc = AStr_AppendPrint(pStr, " VARCHAR(%d)", pCol->length);
                break;
            default:
                obj_Release(pStr);
                return OBJ_NIL;
                break;
        }

        if (pCol->flags & SQLCOL_FLAG_AUTO_INC) {
            eRc = AStr_AppendA(pStr, " AUTOINCREMENT");
        }
        if (pCol->flags & SQLCOL_FLAG_NOT_NULL) {
            eRc = AStr_AppendA(pStr, " NOT NULL");
        }
        if (pCol->flags & SQLCOL_FLAG_UNIQUE) {
            eRc = AStr_AppendA(pStr, " UNIQUE");
        }
        if (pCol->flags & SQLCOL_FLAG_PRIM_KEY) {
            eRc = AStr_AppendA(pStr, " PRIMARY KEY");
        }

        if (pCol->pDefaultValue) {
            eRc = AStr_AppendPrint(pStr, " DEFAULT( %d )", pCol->pDefaultValue);
        }

        return pStr;
    }





    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                   C o n n e c t i o n
    //---------------------------------------------------------------

    sqlite3 *       SQLite_getConn (
        SQLITE_DATA     *this
    )
    {

        // Validate the input parameters.
    #ifdef NDEBUG
    #else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
    #endif


        return this->pConn;
    }



    //---------------------------------------------------------------
    //                         P a t h
    //---------------------------------------------------------------

    PATH_DATA *     SQLite_getPath (
        SQLITE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPath;
    }


    bool            SQLite_setPath (
        SQLITE_DATA     *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pPath) {
            obj_Release(this->pPath);
        }
        this->pPath = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        SQLite_getPriority (
        SQLITE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SQLite_setPriority (
        SQLITE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        SQLite_getSize (
        SQLITE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * SQLite_getStr (
        SQLITE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        SQLite_setStr (
        SQLITE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SQLite_getSuperVtbl (
        SQLITE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = SQLite_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SQLITE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SQLite_Assign (
        SQLITE_DATA       *this,
        SQLITE_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SQLite_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Assign any Super(s).
        if (this->pSuperVtbl && (this->pSuperVtbl->pWhoAmI() != OBJ_IDENT_OBJ)) {
            if (this->pSuperVtbl->pAssign) {
                eRc = this->pSuperVtbl->pAssign(this, pOther);
                if (ERESULT_FAILED(eRc)) {
                    return eRc;
                }
            }
        }

        // Release objects and areas in other object.
#ifdef  XYZZY
        if (pOther->pArray) {
            obj_Release(pOther->pArray);
            pOther->pArray = OBJ_NIL;
        }
#endif

        // Create a copy of objects and areas in this object placing
        // them in other.
#ifdef  XYZZY
        if (this->pArray) {
            if (obj_getVtbl(this->pArray)->pCopy) {
                pOther->pArray = obj_getVtbl(this->pArray)->pCopy(this->pArray);
            }
            else {
                obj_Retain(this->pArray);
                pOther->pArray = this->pArray;
            }
        }
#endif

        // Copy other data from this object to other.
        //pOther->x     = this->x; 

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        //FIXME: Implement the assignment.        
        eRc = ERESULT_NOT_IMPLEMENTED;
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                       B i n d  V a l u e
    //---------------------------------------------------------------

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
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             iRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        MONEY64_DATA    *pMoney = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Value_Validate(pValue)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        switch (Value_getType(pValue)) {
            case VALUE_TYPE_ASTR:           // AStr Object
                pStr = Value_getAStr(pValue);
                if (pStr) {
                    pStr = AStr_ToSQL(pStr);
                    iRc = sqlite3_bind_text(pStmt, idx, AStr_getData(pStr), -1, NULL);
#ifdef XYZZY            // Not certain if this is needed yet!
                    if (pStr) {
                        iRc = sqlite3_bind_text(pStmt, idx, AStr_getData(pStr), -1, NULL);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    } else {
                        return ERESULT_GENERAL_FAILURE;
                    }
#endif
                } else {
                    return ERESULT_GENERAL_FAILURE;
                }
            case VALUE_TYPE_DOUBLE:         // 64-bit Float
                iRc = sqlite3_bind_double(pStmt, idx, Value_getDouble(pValue));
                break;
            case VALUE_TYPE_INT8:           // int8_t
            case VALUE_TYPE_INT16:          // int16_t
            case VALUE_TYPE_INT32:          // int32_t
                iRc = sqlite3_bind_int(pStmt, idx, Value_getU32(pValue));
                break;
            case VALUE_TYPE_INT64:          // int64_t
                iRc = sqlite3_bind_int64(pStmt, idx, Value_getI64(pValue));
                break;
            case VALUE_TYPE_UINT8:          // int8_t
            case VALUE_TYPE_UINT16:         // int16_t
            case VALUE_TYPE_UINT32:         // int32_t
                iRc = sqlite3_bind_int(pStmt, idx, Value_getI32(pValue));
                break;
            case VALUE_TYPE_UINT64:         // int64_t
                iRc = sqlite3_bind_int64(pStmt, idx, Value_getI64(pValue));
                break;
            case VALUE_TYPE_MONEY64:        // Money64 Object
                pMoney = Value_getMoney64(pValue);
            case VALUE_TYPE_OBJECT:         // Any object that supports "ToJson" method
            case VALUE_TYPE_DATA:           // Any data (pointer and length) (pointer and length
                //                          // must be valid for life of object)
            case VALUE_TYPE_DATA_FREE:      // Any data (pointer and length) which will be freed
                //                          // using mem_Free() when no longer needed (pointer
                //                          // and length must be valid for life of object)
            default:
                return ERESULT_INVALID_FORMAT;
        }

        // Put code here...

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          C l o s e
    //---------------------------------------------------------------

    /*!
     Close the open connection.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Close (
        SQLITE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pConn) {
            sqlite3_close(this->pConn);
            this->pConn = NULL;
        }
        else {
            eRc = ERESULT_FILE_CLOSED;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          C o l
    //---------------------------------------------------------------

    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             SQLite_Compare (
        SQLITE_DATA     *this,
        SQLITE_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SQLite_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

#ifdef  xyzzy
        if (this->token == pOther->token) {
            return iRc;
        }
        iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
#endif

        return iRc;
    }

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        SQLite      *pCopy = SQLite_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLITE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLITE_DATA *     SQLite_Copy (
        SQLITE_DATA       *this
    )
    {
        SQLITE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SQLITE_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SQLite_New( );
        if (pOther) {
            eRc = SQLite_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            SQLite_Dealloc (
        OBJ_ID          objId
    )
    {
        SQLITE_DATA   *this = objId;
        //ERESULT         eRc;
        int         sqlError;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SQLITE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SQLite_setPath(this, OBJ_NIL);

        sqlError = sqlite3_shutdown();
        if (sqlError != SQLITE_OK) {
            DEBUG_BREAK();
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         D e e p  C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        SQLite      *pDeepCopy = SQLite_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLITE object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLITE_DATA *     SQLite_DeepyCopy (
        SQLITE_DATA       *this
    )
    {
        SQLITE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SQLite_New( );
        if (pOther) {
            eRc = SQLite_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Disable (
        SQLITE_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Enable (
        SQLITE_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    ERESULT         SQLite_Exec (
        SQLITE_DATA     *this,
        int             (*pCallback)(void*,int,char**,char**),
        void            *pParm1,
        const
        char            *pSqlA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             sqlError;
        char            *pErrmsg = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pCallback) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (NULL == this->pConn) {
            return ERESULT_GENERAL_FAILURE;
        }

        sqlError = sqlite3_exec(
                             this->pConn,
                             pSqlA,         // 1 or more SQL statements terminated
                             //             // with a ';'
                            pCallback,  // int (*pCallback)(void*,int,char**,char**)
                             //             // If the callback function is not NULL, then
                             //             // it is invoked for each result row coming
                             //             // out of the evaluated SQL statements.
                             //             // If non-zero is returned from callback,
                             //             // sqlite3_exec() immediately returns
                             //             // SQLITE_ABORT.
                            pParm1,          // 1st Arg to pCallback
                             //             // 2nd Arg is number of columns in result
                             //             // 3rd Arg is an array of pointers to strings
                             //             // obtained as if from sqlite3_column_text(),
                             //             // one for each column. If a result row is
                             //             // NULL, then the corresponding string pointer
                             //             // for the sqlite3_exec() callback is a NULL
                             //             // pointer.
                             //             // 4th Arg is an array of pointers to strings
                             //             // where each entry represents the name of
                             //             // corresponding result column as obtained
                             //             // from sqlite3_column_name().
                             &pErrmsg       // An error message allocate with
                             //             // sqlite3_malloc() which must be freed
                             //             // with sqlite3_free()
                    );
        if (sqlError) {
            eRc = ERESULT_GENERAL_FAILURE;
        }
        if (pErrmsg) {
            TRC_OBJ(this,"%s\n", pErrmsg);
            fprintf(stderr, "%s\n", pErrmsg);
            sqlite3_free(pErrmsg);
        }

        // Return to caller.
        return eRc;
    }


    ERESULT         SQLite_ExecPrint (
        SQLITE_DATA     *this,
        int             (*pCallback)(void*,int,char**,char**),
        void            *pParm1,
        const
        char            *pFormatA,
        ...
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        char            str[256];
        int             size;
        va_list         arg_ptr;
        char            *pStrA = str;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pCallback) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (NULL == this->pConn) {
            return ERESULT_GENERAL_FAILURE;
        }

        va_start( arg_ptr, pFormatA );
        str[0] = '\0';
        size = vsnprintf(str, sizeof(str), pFormatA, arg_ptr);
        va_end( arg_ptr );
        if (size >= sizeof(str)) {
            ++size;
            pStrA = (char *)mem_Malloc(size);
            if( pStrA == NULL ) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
            va_start( arg_ptr, pFormatA );
            size = vsnprintf( pStrA, size, pFormatA, arg_ptr );
            va_end( arg_ptr );
            eRc = SQLite_Exec(this, pCallback, pParm1, pStrA);
            mem_Free( pStrA );
            pStrA = NULL;
        }
        else {
            eRc = SQLite_Exec(this, pCallback, pParm1, pStrA);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SQLITE_DATA *   SQLite_Init (
        SQLITE_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SQLITE_DATA);
        //ERESULT         eRc;
        int             sqlError;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        /* cbSize can be zero if Alloc() was not called and we are
         * are passed the address of a zero'd area.
         */
        //cbSize = obj_getSize(this);       // cbSize must be set in Alloc().
        if (cbSize == 0) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);        // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SQLITE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SQLite_Vtbl);

        sqlError = sqlite3_initialize();
        if (sqlError != SQLITE_OK) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SQLite::sizeof(SQLITE_DATA) = %lu\n", 
                sizeof(SQLITE_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SQLITE_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SQLite_IsEnabled (
        SQLITE_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //                          O p e n
    //---------------------------------------------------------------

    /*!
     Open/create an SQLite3 database file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Open (
        SQLITE_DATA     *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             sqlError;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_DATA_ALREADY_EXISTS;
        }
#endif
        if (this->pConn) {
            return ERESULT_GENERAL_FAILURE;
        }

        if (pPath == NULL) {
            this->pPath = Path_NewA("");
            //              Default to on-disk temporary database
            //              ":memory:" would be in-memory temporary database
        }
        else {
            SQLite_setPath(this, pPath);
        }
        sqlError = sqlite3_open_v2(
                                Path_getData(this->pPath),
                                &this->pConn,
                                (SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE),
                                NULL         // default sqlite3_vfs object
                    );
        if (sqlError != SQLITE_OK) {
            // Under some circumstances, the open will fail, but conn is
            // left active. So, we have to clean it up.
            eRc = ERESULT_OPEN_ERROR;
            SQLite_Close(this);
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = SQLite_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SQLite", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SQLite_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SQLITE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SQLITE_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SQLite_Class();
                break;
                              
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'S':
                        if (str_Compare("SuperClass", (char *)pStr) == 0) {
                            return (void *)(obj_getInfo(this)->pClassSuperObject);
                        }
                        break;
                        
                    default:
                        break;
                }
                break;

            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return SQLite_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SQLite_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SQLITE_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return SQLite_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return SQLite_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SQLite_ToDebugString;
                        }
#ifdef  SQLITE_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return SQLite_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SQLite_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SQLite_ToDebugString)
                    return "ToDebugString";
#ifdef  SQLITE_JSON_SUPPORT
                if (pData == SQLite_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          S q l  D a t a
    //---------------------------------------------------------------

    /*!
     Convert SQLite column data to SqlCol object.
     SQLite allows any column to contain any type of data regardless
     of the original table definition. We impose a stricter interpre-
     tation and require that data from SQLite conform to the type
     of data that we are expecting from the column definition.
     @param     this    object pointer
     @param     pStmt   SQLite Statement pointer
     @param     idx     column index (relative to zero)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    SQLCOL_DATA *   SQLite_SqlDataToCol (
        SQLITE_DATA     *this,
        sqlite3_stmt    *pStmt,
        int             idx
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        int             type;           // Sqlite native type
        const
        void            *pBlob;
        double          dbl;
        int64_t         i64;
        const
        uint8_t         *pText;
        int             len;
        SQLCOL_DATA     *pCol = OBJ_NIL;
        const
        char            *pDatabaseName = NULL;
        const
        char            *pTableName = NULL;
        const
        char            *pName = NULL;
        VALUE_DATA      *pValue = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pCol = SqlCol_New();
        if (pCol) {
            pDatabaseName = sqlite3_column_database_name(pStmt, idx);
            if (pDatabaseName) {
                pStr = AStr_NewA(pDatabaseName);
                if (pStr) {
                    SqlCol_setDatabaseName(pCol, pStr);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            pTableName = sqlite3_column_table_name(pStmt, idx);
            if (pTableName) {
                pStr = AStr_NewA(pTableName);
                if (pStr) {
                    SqlCol_setTableName(pCol, pStr);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            pName = sqlite3_column_origin_name(pStmt, idx);
            if (pName) {
                pStr = AStr_NewA(pName);
                if (pStr) {
                    SqlCol_setName(pCol, pStr);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            type = sqlite3_column_type(pStmt, idx);
            switch (type) {

                case SQLITE_BLOB:
                    pBlob = sqlite3_column_blob(pStmt, idx);
                    len = sqlite3_column_bytes(pStmt, idx);
                    if (len && pBlob) {
                        pValue = Value_NewDataCopy(len, (void *)pBlob);
                        if (pValue) {
                            SqlCol_setValue(pCol, pValue);
                            obj_Release(pValue);
                            pValue = OBJ_NIL;
                        } else {
                            obj_Release(pCol);
                            pCol = OBJ_NIL;
                        }
                    } else {
                        obj_Release(pCol);
                        pCol = OBJ_NIL;
                    }
                    break;

                case SQLITE_FLOAT:
                    dbl = sqlite3_column_double(pStmt, idx);
                    pValue = Value_NewDouble(dbl);
                    break;
                case SQLITE_INTEGER:
                    i64 = sqlite3_column_int64(pStmt, idx);
                    pValue = Value_NewI64(i64);
                    break;
                case SQLITE_NULL:
                    // No further data is needed.
                    obj_Release(pValue);
                    pValue = OBJ_NIL;
                    break;
                case SQLITE_TEXT:
                    pText = sqlite3_column_text(pStmt, idx);
                    //len = sqlite3_column_bytes(pStmt, idx);
                    // pText is UTF-8 and NUL terminated.
                    pStr = AStr_NewA((void *)pText);
                    if (pStr) {
                        pValue = Value_NewAStr(pStr);
                        obj_Release(pStr);
                        pStr = OBJ_NIL;
                    } else {
                        obj_Release(pValue);
                        pValue = OBJ_NIL;
                    }
                    break;
                default:
                    DEBUG_BREAK();
                    break;
            }
            if (pValue) {
                SqlCol_setValue(pCol, pValue);
                obj_Release(pValue);
                pValue = OBJ_NIL;
            } else {
                obj_Release(pCol);
                pCol = OBJ_NIL;
            }
        }

        // Return to caller.
        return pCol;
    }



    /*!
     Convert one row of the SQLite data from a step execution to a SqlRow object.
     @param     this    object pointer
     @param     pStmt   SQLite Statement pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    SQLROW_DATA *   SQLite_SqlDataToRow (
        SQLITE_DATA     *this,
        sqlite3_stmt    *pStmt
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        int             cCols = 0;
        int             i;
        SQLCOL_DATA     *pCol = OBJ_NIL;
        SQLROW_DATA     *pRow = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
        if (NULL == pStmt) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pRow = SqlRow_New();
        if (pRow) {
            cCols = sqlite3_column_count(pStmt);
            for (i=0; i<cCols; i++) {
                pCol = SQLite_SqlDataToCol(this, pStmt, i);
                SqlRow_AppendCol(pRow, pCol);
                obj_Release(pCol);
                pCol = OBJ_NIL;
            }
        }

        // Return to caller.
        return pRow;
    }



    //---------------------------------------------------------------
    //                          S t e p
    //---------------------------------------------------------------

    ERESULT         SQLite_Step (
        SQLITE_DATA     *this,
        int             (*pCallback)(void *, SQLROW_DATA *),
        void            *pParm1,
        const
        char            *pSqlA,
        OBJLIST_DATA    *pBindQueue
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             sqlError;
        sqlite3_stmt    *pStmt;
        bool            fDone = false;
        SQLROW_DATA     *pRowSql = OBJ_NIL;
        VALUEARRAY_DATA *pRow = OBJ_NIL;
        int             colNo;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (NULL == pSqlA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        if (NULL == this->pConn) {
            return ERESULT_GENERAL_FAILURE;
        }

        sqlError = sqlite3_prepare_v2(this->pConn, pSqlA, -1, &pStmt, NULL);
        if (SQLITE_OK != sqlError ) {
            return ERESULT_INVALID_PARAMETER;
        }

        do {

            if (pBindQueue && (0 < ObjList_getSize(pBindQueue))) {
                VALUE_DATA          *pValue = OBJ_NIL;

                // Bind each column of the row.
                pRow = ObjList_Head(pBindQueue);
                if (!ValueArray_Validate(pRow)) {
                    DEBUG_BREAK();
                    return ERESULT_INVALID_OBJECT;
                }
                for (colNo=0; colNo < ValueArray_getSize(pRow); colNo++) {
                    pValue = ValueArray_Get(pRow, colNo+1);
                    if (pValue) {
                        eRc = SQLite_BindValue(this, pStmt, colNo, pValue);
                        if (ERESULT_FAILED(eRc)) {
                            sqlError = -2;
                            sqlite3_reset(pStmt);       // Release bound parameters.
                            break;
                        }
                    } else {
                        sqlError = -2;
                        sqlite3_reset(pStmt);           // Release bound parameters.
                        break;
                    }
                }
            }

            fDone = false;
            while (!fDone) {
                sqlError = sqlite3_step(pStmt);
                switch (sqlError) {
                    case SQLITE_DONE:
                        fDone = true;
                        break;
                    case    SQLITE_ROW:
                        if (pCallback) {
                            pRowSql = SQLite_SqlDataToRow(this, pStmt);
                            if (pRowSql) {
                                sqlError = pCallback(pParm1, pRowSql);
                                obj_Release(pRowSql);
                                pRowSql = OBJ_NIL;
                                if (sqlError) {
                                    eRc = ERESULT_FAILURE;
                                    fDone = true;
                                    break;
                                }
                            }
                        }
                        break;
                    default:
                        eRc = ERESULT_FAILURE;
                        fDone = true;
                        break;
                }
            }
            sqlite3_reset(pStmt);           // Release bound parameters.
            if (pBindQueue && (0 < ObjList_getSize(pBindQueue))) {
                ObjList_DeleteHead(pBindQueue);
            }

        } while (ERESULT_OK(eRc) && pBindQueue && (0 < ObjList_getSize(pBindQueue)));

        sqlite3_finalize(pStmt);

        // Return to caller.
        return eRc;
    }


    //---------------------------------------------------------------
    //                      T a b l e
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * SQLite_TableNames (
        SQLITE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTRCARRAY_DATA *pArray = OBJ_NIL;
        table_cb_work   *pWork = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pArray = AStrCArray_New();
        if (OBJ_NIL == pArray) {
            return OBJ_NIL;
        }
        pWork = mem_Malloc(sizeof(table_cb_work));
        if (OBJ_NIL == pWork) {
            obj_Release(pArray);
            return OBJ_NIL;
        }
        pWork->pArray = pArray;
        pWork->this = this;

        eRc =   SQLite_Exec(
                            this,
                            SQLite_table_callback,
                            pWork,
                            "SELECT * FROM sqlite_master;"
                );

        mem_Free(pWork);
        pWork = NULL;
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pArray);
            pArray = OBJ_NIL;
        }

        // Return to caller.
        return pArray;
    }


    uint32_t        SQLite_TableRowCount (
        SQLITE_DATA     *this,
        const
        char            *pTableNameA
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        cRcds = 0;
        ASTR_DATA       *pStr = OBJ_NIL;
        const
        char            *pSql1 = "SELECT COUNT(*) AS cRcds FROM %s ;";

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
        if (NULL == pTableNameA) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return 0;
        }
#endif

        pStr = AStr_NewFromPrint(pSql1, pTableNameA);
        if (pStr) {
            eRc =   SQLite_Exec(
                              this,
                              SQLite_tableCount_callback,
                              &cRcds,
                              AStr_getData(pStr)
                    );
            if (ERESULT_FAILED(eRc)) {
                cRcds = 0;
            }
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }


        // Return to caller.
        return cRcds;
    }




    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SQLite_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLite_ToDebugString (
        SQLITE_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = obj_getInfo(this);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d retain=%d\n",
                    this,
                    pInfo->pClassName,
                    SQLite_getSize(this),
                    obj_getRetainCount(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            ASTR_DATA       *pWrkStr = OBJ_NIL;
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                if (pWrkStr) {
                    AStr_Append(pStr, pWrkStr);
                    obj_Release(pWrkStr);
                }
            }
        }
#endif
        
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

#ifdef NDEBUG
#else
    bool            SQLite_Validate (
        SQLITE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SQLITE))
                ;
            else {
                // 'this' is not our kind of data. We really don't
                // know what that it is at this point. 
                return false;
            }
        }
        else {
            // 'this' is NULL.
            return false;
        }
        // Now, we have validated that we have a valid pointer in
        // 'this'.


        if (!(obj_getSize(this) >= sizeof(SQLITE_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                  X l a t e  E r r o r
    //---------------------------------------------------------------

    ERESULT         SQLite_XlateError (
        SQLITE_DATA     *this,
        int             error
    )
    {
        ERESULT         eRc = ERESULT_FAILURE;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        switch (error) {
            case SQLITE_ABORT:
                eRc = ERESULT_FAILURE;
            case SQLITE_BUSY:
                eRc = ERESULT_BUSY;
            case SQLITE_IOERR:
                eRc = ERESULT_IO_ERROR;
            case SQLITE_OK:
                eRc = ERESULT_SUCCESS;
            case SQLITE_ROW:
                eRc = ERESULT_SUCCESS_PARTIAL_DATA;
            default:
                eRc = ERESULT_UNKNOWN;
        }

        // Return to caller.
        return ERESULT_SUCCESS_FALSE;
    }




    
#ifdef  __cplusplus
}
#endif


