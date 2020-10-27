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
#include        <trace.h>






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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         SQLite_Compare (
        SQLITE_DATA     *this,
        SQLITE_DATA     *pOther
    )
    {
        int             i = 0;
        ERESULT         eRc = ERESULT_SUCCESS_EQUAL;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef NDEBUG
#else
        if (!SQLite_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SQLite_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

#ifdef  xyzzy        
        if (this->token == pOther->token) {
            this->eRc = eRc;
            return eRc;
        }
        
        pStr1 = szTbl_TokenToString(OBJ_NIL, this->token);
        pStr2 = szTbl_TokenToString(OBJ_NIL, pOther->token);
        i = strcmp(pStr1, pStr2);
#endif

        
        if (i < 0) {
            eRc = ERESULT_SUCCESS_LESS_THAN;
        }
        if (i > 0) {
            eRc = ERESULT_SUCCESS_GREATER_THAN;
        }
        
        return eRc;
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
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          E x e c
    //---------------------------------------------------------------

    /*!
     Execute an SQL Statement.
     @param     this        object pointer
     @param     pSql        sql statement
     @param     pCallback   optional callback address
     @param     pParm1      optional 1st parameter pass to callback
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLite_Exec (
        SQLITE_DATA     *this,
        ASTR_DATA       *pSql,
        int             (*pCallback)(void*,int,char**,char**),
        void            *pParm1
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
            return ERESULT_DATA_ALREADY_EXISTS;
        }
#endif
        if (NULL == this->pConn) {
            return ERESULT_GENERAL_FAILURE;
        }

        sqlError = sqlite3_exec(
                             this->pConn,
                             AStr_getData(pSql), // 1 or more SQL statements terminated
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
    //                  T a b l e  N a m e s
    //---------------------------------------------------------------

    ASTRCARRAY_DATA * SQLite_TableNames (
        SQLITE_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pSql = OBJ_NIL;
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
        pSql = AStr_NewA("SELECT * FROM sqlite_master;");
        if (OBJ_NIL == pSql) {
            return OBJ_NIL;
        }
        pArray = AStrCArray_New();
        if (OBJ_NIL == pArray) {
            obj_Release(pSql);
            return OBJ_NIL;
        }
        pWork = mem_Malloc(sizeof(table_cb_work));
        if (OBJ_NIL == pWork) {
            obj_Release(pSql);
            obj_Release(pArray);
            return OBJ_NIL;
        }
        pWork->pArray = pArray;
        pWork->this = this;

        eRc = SQLite_Exec(this, pSql, SQLite_table_callback, pWork);

        mem_Free(pWork);
        pWork = NULL;
        obj_Release(pSql);
        pSql = OBJ_NIL;
        if (ERESULT_FAILED(eRc)) {
            obj_Release(pArray);
            pArray = OBJ_NIL;
        }

        // Return to caller.
        return pArray;
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


