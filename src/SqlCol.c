// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   SqlCol.c
 *	Generated 04/25/2020 18:28:59
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
#include        <SqlCol_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    
    // TypeExpr: type_name ['(' integer [',' decimal_integer] ')']
    //         ;
    SQLCOL_TYPE_EXPR    typeExprs[] = {
        {"BLOB", "TEXT", SQLCOL_TYPE_BLOB, 0},
        {"BOOL", "INTEGER", SQLCOL_TYPE_BOOL, 0},
        {"CHAR", "TEXT", SQLCOL_TYPE_CHAR, 0},
        {"DECIMAL", "REAL", SQLCOL_TYPE_DECIMAL, 1},
        {"INT", "INTEGER", SQLCOL_TYPE_INTEGER, 0},
        {"INTEGER", "INTEGER", SQLCOL_TYPE_INTEGER, 0},
        {"NCHAR", "TEXT", SQLCOL_TYPE_NCHAR, 0},
        {"NVARCHAR", "TEXT", SQLCOL_TYPE_NVARCHAR, 0},
        {"REAL", "REAL", SQLCOL_TYPE_REAL, 1},
        {"TEXT", "TEXT", SQLCOL_TYPE_TEXT, 0},
        {"VARCHAR", "TEXT", SQLCOL_TYPE_VARCHAR, 0},
    };
    int                 cTypeExprs = sizeof(typeExprs)/sizeof(SQLCOL_TYPE_EXPR);

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    SQLCOL_TYPE_EXPR * SqlCol_FindByName (
        const
        char        *pName
    )
    {
        int         i;
        int         iRc;
        SQLCOL_TYPE_EXPR
                    *pEntry;

        for (i=0; i<cTypeExprs; i++) {
            pEntry = &typeExprs[i];
            iRc = strcmp(pName, pEntry->pNameA);
            if (0 == iRc)
                return pEntry;

        }

        return NULL;
    }


    SQLCOL_TYPE_EXPR * SqlCol_FindByType (
        uint8_t     type                    // see SQLCOL_TYPES
    )
    {
        int         i;
        SQLCOL_TYPE_EXPR
                    *pEntry;

        for (i=0; i<cTypeExprs; i++) {
            pEntry = &typeExprs[i];
            if (pEntry->type == type)
                return pEntry;

        }

        return NULL;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    SQLCOL_DATA *     SqlCol_Alloc (
        void
    )
    {
        SQLCOL_DATA       *this;
        uint32_t        cbSize = sizeof(SQLCOL_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    SQLCOL_DATA *     SqlCol_New (
        void
    )
    {
        SQLCOL_DATA       *this;
        
        this = SqlCol_Alloc( );
        if (this) {
            this = SqlCol_Init(this);
        } 
        return this;
    }


    SQLCOL_DATA *     SqlCol_NewFromStruct (
        SQLCOL_STRUCT   *pStruct
    )
    {
        SQLCOL_DATA     *this;
        ERESULT         eRc;

        this = SqlCol_New( );
        if (this) {
            eRc = SqlCol_FromStruct(this, pStruct);
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
    //              C h e c k  E x p r e s s i o n
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getCheckExpr (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pCheckExpr;
    }


    bool        SqlCol_setCheckExpr (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pCheckExpr) {
            obj_Release(this->pCheckExpr);
        }
        this->pCheckExpr = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          C o l  S e q
    //---------------------------------------------------------------

    uint16_t        SqlCol_getColSeq (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->colSeq;
    }


    bool            SqlCol_setColSeq (
        SQLCOL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->colSeq = value;

        return true;
    }



    //---------------------------------------------------------------
    //                   D a t a b a s e  N a m e
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getDatabaseName (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDBName;
    }


    bool        SqlCol_setDatabaseName (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDBName) {
            obj_Release(this->pDBName);
        }
        this->pDBName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  D e c i m a l  P l a c e s
    //---------------------------------------------------------------

    uint8_t         SqlCol_getDecimalPlaces (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->decimalPlaces;
    }


    bool            SqlCol_setDecimalPlaces (
        SQLCOL_DATA     *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->decimalPlaces = value;

        return true;
    }



    //---------------------------------------------------------------
    //                  D e f a u l t  V a l u e
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getDefVal (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDefVal;
    }


    bool        SqlCol_setDefVal (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDefVal) {
            obj_Release(this->pDefVal);
        }
        this->pDefVal = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                  D e s c r i p t i o n
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getDesc (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDesc;
    }


    bool        SqlCol_setDesc (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDesc) {
            obj_Release(this->pDesc);
        }
        this->pDesc = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         F l a g s
    //---------------------------------------------------------------

    uint32_t        SqlCol_getFlags (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->flags;
    }


    bool            SqlCol_setFlags (
        SQLCOL_DATA     *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->flags = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          K e y  S e q
    //---------------------------------------------------------------

    uint16_t        SqlCol_getKeySeq (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->keySeq;
    }


    bool            SqlCol_setKeySeq (
        SQLCOL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->keySeq = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          L e n g t h
    //---------------------------------------------------------------

    int32_t         SqlCol_getLength (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->length;
    }


    bool            SqlCol_setLength (
        SQLCOL_DATA     *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->length = value;

        return true;
    }


    int32_t         SqlCol_getLengthMin (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->lengthMin;
    }


    bool            SqlCol_setLengthMin (
        SQLCOL_DATA     *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->lengthMin = value;

        return true;
    }



    //---------------------------------------------------------------
    //                        N a m e
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getName (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool        SqlCol_setName (
        SQLCOL_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        SqlCol_getPriority (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            SqlCol_setPriority (
        SQLCOL_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
    
    uint32_t        SqlCol_getSize (
        SQLCOL_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  SqlCol_getSuperVtbl (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      T a b l e  N a m e
    //---------------------------------------------------------------

    ASTR_DATA * SqlCol_getTableName (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pTableName;
    }


    bool        SqlCol_setTableName (
        SQLCOL_DATA *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pTableName) {
            obj_Release(this->pTableName);
        }
        this->pTableName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         T y p e
    //---------------------------------------------------------------

    uint8_t         SqlCol_getType (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            SqlCol_setType (
        SQLCOL_DATA     *this,
        uint8_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->type = value;

        return true;
    }



    //---------------------------------------------------------------
    //                          V a l u e
    //---------------------------------------------------------------

    VALUE_DATA *    SqlCol_getValue (
        SQLCOL_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pValue;
    }


    bool        SqlCol_setValue (
        SQLCOL_DATA *this,
        VALUE_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pValue) {
            obj_Release(this->pValue);
        }
        this->pValue = pValue;

        return true;
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
        ERESULT eRc = SqlCol_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another SQLCOL object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         SqlCol_Assign (
        SQLCOL_DATA		*this,
        SQLCOL_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!SqlCol_Validate(pOther)) {
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
        SqlCol_setCheckExpr(pOther, OBJ_NIL);
        SqlCol_setDatabaseName(pOther, OBJ_NIL);
        SqlCol_setDefVal(pOther, OBJ_NIL);
        SqlCol_setDesc(pOther, OBJ_NIL);
        SqlCol_setName(pOther, OBJ_NIL);
        SqlCol_setTableName(pOther, OBJ_NIL);
        SqlCol_setValue(pOther, OBJ_NIL);

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pName) {
            pOther->pName = AStr_Copy(this->pName);
        }
        if (this->pDBName) {
            pOther->pDBName = AStr_Copy(this->pDBName);
        }
        if (this->pDesc) {
            pOther->pDesc = AStr_Copy(this->pDesc);
        }
        if (this->pDefVal) {
            pOther->pDefVal = AStr_Copy(this->pDefVal);
        }
        if (this->pCheckExpr) {
            pOther->pCheckExpr = AStr_Copy(this->pCheckExpr);
        }
        if (this->pTableName) {
            pOther->pTableName = AStr_Copy(this->pTableName);
        }
        if (this->pValue) {
            pOther->pValue = Value_Copy(this->pValue);
        }

        // Copy other data from this object to other.
        pOther->type            = this->type;
        pOther->decimalPlaces   = this->decimalPlaces;
        pOther->colSeq          = this->colSeq;
        pOther->keySeq          = this->keySeq;
        pOther->flags           = this->flags;
        pOther->length          = this->length;
        pOther->lengthMin       = this->lengthMin;

        //goto eom;

        // Return to caller.
        eRc = ERESULT_SUCCESS;
    eom:
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      C o m p a r e
    //---------------------------------------------------------------
    
    /*!
     Compare the two provided objects.
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             SqlCol_Compare (
        SQLCOL_DATA     *this,
        SQLCOL_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SqlCol_Validate(pOther)) {
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

   
    int             SqlCol_CompareKeySeq (
        SQLCOL_DATA     *this,
        SQLCOL_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SqlCol_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        if (this->keySeq == pOther->keySeq) {
            return iRc;
        }
        if (this->keySeq < pOther->keySeq) {
            iRc = -1;
        } else {
            iRc = 1;
        }

        return iRc;
    }


    int             SqlCol_CompareName (
        SQLCOL_DATA     *this,
        SQLCOL_DATA     *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!SqlCol_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        iRc = AStr_Compare(this->pName, pOther->pName);

        return iRc;
    }



    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        SqlCol      *pCopy = SqlCol_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLCOL object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLCOL_DATA *     SqlCol_Copy (
        SQLCOL_DATA       *this
    )
    {
        SQLCOL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef SQLCOL_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = SqlCol_New( );
        if (pOther) {
            eRc = SqlCol_Assign(this, pOther);
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

    void            SqlCol_Dealloc (
        OBJ_ID          objId
    )
    {
        SQLCOL_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((SQLCOL_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        SqlCol_setCheckExpr(this, OBJ_NIL);
        SqlCol_setDatabaseName(this, OBJ_NIL);
        SqlCol_setDefVal(this, OBJ_NIL);
        SqlCol_setDesc(this, OBJ_NIL);
        SqlCol_setName(this, OBJ_NIL);
        SqlCol_setTableName(this, OBJ_NIL);
        SqlCol_setValue(this, OBJ_NIL);

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
        SqlCol      *pDeepCopy = SqlCol_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a SQLCOL object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SQLCOL_DATA *     SqlCol_DeepyCopy (
        SQLCOL_DATA       *this
    )
    {
        SQLCOL_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = SqlCol_New( );
        if (pOther) {
            eRc = SqlCol_Assign(this, pOther);
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
    ERESULT         SqlCol_Disable (
        SQLCOL_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
    ERESULT         SqlCol_Enable (
        SQLCOL_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
    //                      F r o m  S t r u c t
    //---------------------------------------------------------------

    ERESULT         SqlCol_FromStruct (
        SQLCOL_DATA     *this,
        SQLCOL_STRUCT   *pStruct
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Release any prior data.
        SqlCol_setCheckExpr(this, OBJ_NIL);
        SqlCol_setDatabaseName(this, OBJ_NIL);
        SqlCol_setDefVal(this, OBJ_NIL);
        SqlCol_setDesc(this, OBJ_NIL);
        SqlCol_setName(this, OBJ_NIL);
        SqlCol_setTableName(this, OBJ_NIL);

        if (pStruct->pCheckExpression) {
            this->pCheckExpr = AStr_NewA(pStruct->pCheckExpression);
            if (OBJ_NIL == this->pCheckExpr) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        this->pName = AStr_NewA(pStruct->pName);
        if (OBJ_NIL == this->pName) {
            SqlCol_setCheckExpr(this, OBJ_NIL);
            return ERESULT_OUT_OF_MEMORY;
        }
        if (pStruct->pDefaultValue) {
            this->pDefVal = AStr_NewA(pStruct->pDefaultValue);
            if (OBJ_NIL == this->pDefVal) {
                SqlCol_setCheckExpr(this, OBJ_NIL);
                SqlCol_setName(this, OBJ_NIL);
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        if (pStruct->pDatabaseName) {
            this->pDBName = AStr_NewA(pStruct->pDatabaseName);
            if (OBJ_NIL == this->pDBName) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        if (pStruct->pTableName) {
            this->pTableName = AStr_NewA(pStruct->pTableName);
            if (OBJ_NIL == this->pTableName) {
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        this->pDesc = AStr_NewA(pStruct->pDescription);
        if (OBJ_NIL == this->pDesc) {
            SqlCol_setCheckExpr(this, OBJ_NIL);
            SqlCol_setName(this, OBJ_NIL);
            SqlCol_setDefVal(this, OBJ_NIL);
            return ERESULT_OUT_OF_MEMORY;
        }
        this->decimalPlaces = pStruct->decimalPlaces;
        this->flags         = pStruct->flags;
        this->keySeq        = pStruct->keySequence;
        this->length        = pStruct->length;
        this->lengthMin     = pStruct->minimumLength;
        this->colSeq        = pStruct->colSeq;
        this->type          = pStruct->type;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      F u l l  N a m e
    //---------------------------------------------------------------

    /*!
     Construct the full name from the database, table and column names.
     @param     this    object pointer
     @return    if successful, AStr object which must be released.
                Otherwise, OBJ_NIL if an error occurred.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_FullName (
        SQLCOL_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (pStr) {
            if (this->pDBName) {
                eRc = AStr_Append(pStr, this->pDBName);
                eRc = AStr_AppendA(pStr, ".");
            }
            if (this->pTableName) {
                eRc = AStr_Append(pStr, this->pTableName);
                eRc = AStr_AppendA(pStr, ".");
            }
            eRc = AStr_Append(pStr, this->pName);
        }

        // Return to caller.
        return pStr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    SQLCOL_DATA *   SqlCol_Init (
        SQLCOL_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(SQLCOL_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_SQLCOL);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&SqlCol_Vtbl);
        
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
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "SqlCol::sizeof(SQLCOL_DATA) = %lu\n", 
                sizeof(SQLCOL_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(SQLCOL_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         SqlCol_IsEnabled (
        SQLCOL_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
        void        *pMethod = SqlCol_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "SqlCol", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          SqlCol_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        SQLCOL_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(SQLCOL_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)SqlCol_Class();
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
                            return SqlCol_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return SqlCol_Enable;
                        }
                        break;

                    case 'P':
#ifdef  SQLCOL_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return SqlCol_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return SqlCol_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return SqlCol_ToDebugString;
                        }
#ifdef  SQLCOL_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return SqlCol_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return SqlCol_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == SqlCol_ToDebugString)
                    return "ToDebugString";
#ifdef  SQLCOL_JSON_SUPPORT
                if (pData == SqlCol_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------

    /*!
     Convert the internal column definition to SQL.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                SQL, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_ToSQL (
        SQLCOL_DATA     *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        //uint32_t        i;
        //uint32_t        j;
        const
        char            *pWrkStrA;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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

        if (this->pName) {
            eRc = AStr_Append(pStr, this->pName);
            eRc = AStr_AppendA(pStr, " ");
        }

        switch (this->type) {
            case SQLCOL_TYPE_BLOB:
                eRc = AStr_AppendA(pStr, "BLOB ");
                break;

            case SQLCOL_TYPE_BOOL:
                eRc = AStr_AppendA(pStr, "BOOL ");
                break;

            case SQLCOL_TYPE_CHAR:
                if (this->length) {
                    eRc = AStr_AppendPrint(pStr, "CHAR(%d) ", this->length);
                } else {
                    eRc = AStr_AppendA(pStr, "CHAR ");
                }
                break;

            case SQLCOL_TYPE_DATE:
                pWrkStrA = "DATE";
                break;

            case SQLCOL_TYPE_DECIMAL:
                if (this->length) {
                    eRc =   AStr_AppendPrint(
                                             pStr,
                                             "DECIMAL(%d,%d) ",
                                             this->length,
                                             this->decimalPlaces
                            );
                } else {
                    eRc = AStr_AppendA(pStr, "DECIMAL ");
                }
                break;

            case SQLCOL_TYPE_FILLER:
                pWrkStrA = "FILLER";
                break;

            case SQLCOL_TYPE_INTEGER:
                pWrkStrA = "INTEGER";
                break;

            case SQLCOL_TYPE_NCHAR:
                if (this->length) {
                    eRc = AStr_AppendPrint(pStr, "NCHAR(%d) ", this->length);
                } else {
                    eRc = AStr_AppendA(pStr, "NCHAR ");
                }
                break;

            case SQLCOL_TYPE_NUMBER:
                pWrkStrA = "NUMBER";
                break;

            case SQLCOL_TYPE_NVARCHAR:
                if (this->length) {
                    eRc = AStr_AppendPrint(pStr, "NVARCHAR(%d) ", this->length);
                } else {
                    eRc = AStr_AppendA(pStr, "NVARCHAR ");
                }
                break;

            case SQLCOL_TYPE_REAL:
                if (this->length) {
                    eRc =   AStr_AppendPrint(
                                             pStr,
                                             "REAL(%d,%d) ",
                                             this->length,
                                             this->decimalPlaces
                            );
                } else {
                    eRc = AStr_AppendA(pStr, "REAL ");
                }
                break;

            case SQLCOL_TYPE_TEXT:
                if (this->length) {
                    eRc = AStr_AppendPrint(pStr, "TEXT(%d) ", this->length);
                } else {
                    eRc = AStr_AppendA(pStr, "TEXT ");
                }
                break;

            case SQLCOL_TYPE_VARCHAR:
                if (this->length) {
                    eRc = AStr_AppendPrint(pStr, "VARCHAR(%d) ", this->length);
                } else {
                    eRc = AStr_AppendA(pStr, "VARCHAR ");
                }
                break;

            default:
                pWrkStrA = "==>UNKNOWN<==";
                break;
        }

        // Primary key is always id INTEGER PRIMARY KEY. So, we will skip this
        // but use it for indices.
        //    if (this->flags & SQLCOL_FLAG_PRIM_KEY) {
        //        eRc = AStr_AppendA(pStr, "PRIMARY KEY ");
        //    }
        if (this->flags & SQLCOL_FLAG_UNIQUE) {
            eRc = AStr_AppendA(pStr, "UNIQUE ");
        }
        if (this->flags & SQLCOL_FLAG_NOT_NULL) {
            eRc = AStr_AppendA(pStr, "NOT NULL ");
        }
        if (this->flags & SQLCOL_FLAG_AUTO_INC) {
            eRc = AStr_AppendA(pStr, "AUTOINCREMENT ");
        }

        if (this->pDefVal) {
            eRc = AStr_AppendPrint(pStr, "DEFAULT(%s) ", AStr_getData(this->pDefVal));
        }
        if (this->pCheckExpr) {
            eRc = AStr_AppendPrint(pStr, "%s", AStr_getData(this->pDefVal));
        }

        return pStr;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
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
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     SqlCol_ToDebugString (
        SQLCOL_DATA      *this,
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
        const
        char            *pWrkStrA;
        SQLCOL_TYPE_EXPR
                        *pTypeExpr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!SqlCol_Validate(this)) {
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
                    "{%p(%s) retain=%d\n",
                    this,
                    pInfo->pClassName,
                    obj_getRetainCount(this)
            );

        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "\tname: %s\n"
                    "\tdesc: %s\n"
                    "\tlength: %d\n"
                    "\tlengthMin: %d\n"
                    "\tdecimal_places: %d\n"
                    "\tkeySeq: %d\n"
                    "\tcolSeq: %d\n"
                    "\tflags: %s%s%s%s\n"
                    "\tcheck: %s\n"
                    "\tdefault: %s\n",
                    this->pName ? AStr_getData(this->pName) : "<NULL>",
                    this->pDesc ? AStr_getData(this->pDesc) : "<NULL>",
                    this->length,
                    this->lengthMin,
                    this->decimalPlaces,
                    this->keySeq,
                    this->colSeq,
                    this->flags & SQLCOL_FLAG_UNIQUE ? "Unique " : "",
                    this->flags & SQLCOL_FLAG_NOT_NULL ? "Not_NULL " : "",
                    this->flags & SQLCOL_FLAG_AUTO_INC ? "Auto_Inc " : "",
                    this->flags & SQLCOL_FLAG_PRIM_KEY ? "Primary_Key " : "",
                    this->pCheckExpr ? AStr_getData(this->pCheckExpr) : "<NULL>",
                    this->pDefVal ? AStr_getData(this->pDefVal) : "<NULL>"
            );
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        pTypeExpr = SqlCol_FindByType(this->type);
        if (pTypeExpr) {
            pWrkStrA = pTypeExpr->pNameA;
        } else {
            pWrkStrA = "==> UNKNOWN <==";
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "\ttype: 0x%02x - %s\n",
                    this->type,
                    pWrkStrA
            );

#ifdef  XYZZY        
        if (this->pData) {
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
    bool            SqlCol_Validate (
        SQLCOL_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_SQLCOL))
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


        if (!(obj_getSize(this) >= sizeof(SQLCOL_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


