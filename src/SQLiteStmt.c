// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SQLiteStmt.c
 *  Generated 10/23/2020 12:24:56
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include        <SQLiteStmt_internal.h>
#include        <trace.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            SQLiteStmt_task_body (
        void            *pData
    )
    {
        //SQLITESTMT_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SQLITESTMT_DATA *     SQLiteStmt_Alloc (
        void
    )
    {
        SQLITESTMT_DATA       *this;
        uint32_t        cbSize = sizeof(SQLITESTMT_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SQLITESTMT_DATA *     SQLiteStmt_New (
        void
    )
    {
        SQLITESTMT_DATA       *this;
        
        this = SQLiteStmt_Alloc( );
        if (this) {
            this = SQLiteStmt_Init(this);
        } 
        return this;
    }


    SQLITESTMT_DATA * SQLiteStmt_NewStmt (
        SQLITE_DATA     *pDB,
        ASTR_DATA       *pStmt
    )
    {
        SQLITESTMT_DATA *this;

        this = SQLiteStmt_New( );
        if (this) {
            SQLiteStmt_Setup(this, pDB, pStmt);
        }
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                              D B
    //---------------------------------------------------------------

    SQLITE_DATA *   SQLiteStmt_getDB (
        SQLITESTMT_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDB;
    }


    bool            SQLiteStmt_setDB (
        SQLITESTMT_DATA *this,
        SQLITE_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(this->pDB);
        if (this->pDB) {
            obj_Release(this->pDB);
        }
        this->pDB = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------

    uint32_t        SQLiteStmt_getSize (
        SQLITESTMT_DATA *this
    )
    {
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                        S t a t e
    //---------------------------------------------------------------
    
    uint32_t        SQLiteStmt_getState (
        SQLITESTMT_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->state;
    }


    bool            SQLiteStmt_setState (
        SQLITESTMT_DATA *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->state = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        S t a t e m e n t
    //---------------------------------------------------------------

    ASTR_DATA *     SQLiteStmt_getStmt (
        SQLITESTMT_DATA *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pStmt;
    }


    bool        SQLiteStmt_setStmt (
        SQLITESTMT_DATA *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStmt) {
            obj_Release(this->pStmt);
        }
        this->pStmt = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SQLiteStmt_getSuperVtbl (
        SQLITESTMT_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
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
        ERESULT eRc = SQLiteStmt_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SQLITESTMT object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SQLiteStmt_Assign (
        SQLITESTMT_DATA       *this,
        SQLITESTMT_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SQLiteStmt_Validate(pOther)) {
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
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         SQLiteStmt_Compare (
        SQLITESTMT_DATA     *this,
        SQLITESTMT_DATA     *pOther
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
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SQLiteStmt_Validate(pOther)) {
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
        SQLiteStmt      *pCopy = SQLiteStmt_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLITESTMT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLITESTMT_DATA *     SQLiteStmt_Copy (
        SQLITESTMT_DATA       *this
    )
    {
        SQLITESTMT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SQLITESTMT_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SQLiteStmt_New( );
        if (pOther) {
            eRc = SQLiteStmt_Assign(this, pOther);
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

    void            SQLiteStmt_Dealloc (
        OBJ_ID          objId
    )
    {
        SQLITESTMT_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SQLITESTMT_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SQLiteStmt_setDB(this, OBJ_NIL);
        SQLiteStmt_setStmt(this, OBJ_NIL);
        if (this->pSqlStmt) {
            sqlite3_reset(this->pSqlStmt);
            sqlite3_finalize(this->pSqlStmt);
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
        SQLiteStmt      *pDeepCopy = SQLiteStmt_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLITESTMT object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLITESTMT_DATA *     SQLiteStmt_DeepyCopy (
        SQLITESTMT_DATA       *this
    )
    {
        SQLITESTMT_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SQLiteStmt_New( );
        if (pOther) {
            eRc = SQLiteStmt_Assign(this, pOther);
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
    ERESULT         SQLiteStmt_Disable (
        SQLITESTMT_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
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
    ERESULT         SQLiteStmt_Enable (
        SQLITESTMT_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
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
    //                       F i n a l i z e
    //---------------------------------------------------------------

    /*!
     Finalize a prepared statement releasing any internal memory resources
     and deallocates any memory. Once finalized, the statement cannot be
     reused, it must go through the preparation stage again.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLiteStmt_Finalize (
        SQLITESTMT_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             error;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pSqlStmt) {
            error = sqlite3_reset(this->pSqlStmt);
            if (error) {
                eRc = ERESULT_FAILURE;
            }
            error = sqlite3_finalize(this->pSqlStmt);
            if (error) {
                eRc = ERESULT_FAILURE;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SQLITESTMT_DATA *   SQLiteStmt_Init (
        SQLITESTMT_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SQLITESTMT_DATA);
        //ERESULT         eRc;
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SQLITESTMT);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SQLiteStmt_Vtbl);
        
        /*
        this->pArray = objArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SQLiteStmt::sizeof(SQLITESTMT_DATA) = %lu\n", 
                sizeof(SQLITESTMT_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SQLITESTMT_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SQLiteStmt_IsEnabled (
        SQLITESTMT_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
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
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    /*!
     Return information about this object. This method can translate
     methods to strings and vice versa, return the address of the
     object information structure.
     Example:
     @code
        // Return a method pointer for a string or NULL if not found. 
        void        *pMethod = SQLiteStmt_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SQLiteStmt", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SQLiteStmt_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SQLITESTMT_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SQLITESTMT_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SQLiteStmt_Class();
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
                            return SQLiteStmt_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SQLiteStmt_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SQLITESTMT_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return SQLiteStmt_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return SQLiteStmt_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SQLiteStmt_ToDebugString;
                        }
#ifdef  SQLITESTMT_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return SQLiteStmt_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SQLiteStmt_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SQLiteStmt_ToDebugString)
                    return "ToDebugString";
#ifdef  SQLITESTMT_JSON_SUPPORT
                if (pData == SQLiteStmt_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                          R e s e t
    //---------------------------------------------------------------

    /*!
     Reset a prepared statement making it available for further
     execution.  This should follow Step().
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLiteStmt_Reset (
        SQLITESTMT_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        int             error;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pSqlStmt) {
            error = sqlite3_reset(this->pSqlStmt);
            if (error) {
                eRc = ERESULT_FAILURE;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     S e t u p  S t m t
    //---------------------------------------------------------------

    ERESULT         SQLiteStmt_Setup (
        SQLITESTMT_DATA *this,
        SQLITE_DATA     *pDB,
        ASTR_DATA       *pStmt
    )
    {
        int             error;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pSqlStmt) {
            error = sqlite3_reset(this->pSqlStmt);
            error = sqlite3_finalize(this->pSqlStmt);
        }
        SQLiteStmt_setDB(this, pDB);
        SQLiteStmt_setStmt(this, pStmt);

        error = sqlite3_prepare_v2(
                        SQLite_getConn(this->pDB),
                        AStr_getData(this->pStmt),
                        -1,
                        &this->pSqlStmt,
                        NULL
                        );

        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          S t e p
    //---------------------------------------------------------------

    /*!
     Execute a prepared statement.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         SQLiteStmt_Step (
        SQLITESTMT_DATA *this
    )
    {
        ERESULT         eRc = ERESULT_GENERAL_FAILURE;
        int             error;
        int             retries = 100;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SQLiteStmt_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pSqlStmt) {
            error = sqlite3_step(this->pSqlStmt);
            if ((error == SQLITE_BUSY) || (error == SQLITE_LOCKED)) {
                while (retries-- && ((error == SQLITE_BUSY) || (error == SQLITE_LOCKED))) {
                    usleep(10000);                  // Sleep for 10ms
                    error = sqlite3_step(this->pSqlStmt);
                }
            }
            switch (error) {
                case SQLITE_DONE:
                case SQLITE_OK:
                    this->state = SQLITESTMT_STATE_DONE;
                    eRc = ERESULT_SUCCESS;
                    break;
                case SQLITE_ROW:
                    this->state = SQLITESTMT_STATE_ROW;
                    eRc = ERESULT_SUCCESS_PARTIAL_DATA;
                    break;
                default:
                    eRc = ERESULT_FAILURE;
            }
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SQLiteStmt_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SQLiteStmt_ToDebugString (
        SQLITESTMT_DATA      *this,
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
        if (!SQLiteStmt_Validate(this)) {
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
                    SQLiteStmt_getSize(this),
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
    bool            SQLiteStmt_Validate (
        SQLITESTMT_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SQLITESTMT))
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


        if (!(obj_getSize(this) >= sizeof(SQLITESTMT_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


