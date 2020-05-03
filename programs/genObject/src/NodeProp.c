// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   NodeProp.c
 *	Generated 04/26/2020 17:31:56
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
#include        <NodeProp_internal.h>
#include        <trace.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    typedef struct Type_Def_s {
        uint16_t        num;
        const
        char            *pEnum;
        const
        char            *pExternal;
    } TYPE_DEF;

#ifdef XYZZY
    static
    TYPE_DEF        typeDefs[] = {
        {NODEPROP_TYPE_ASTR,    "NODEPROP_TYPE_ASTR",   "ASTR"},
        {NODEPROP_TYPE_FLAG8,   "NODEPROP_TYPE_FLAG8",  "FLAG8"},
        {NODEPROP_TYPE_FLAG16,  "NODEPROP_TYPE_FLAG16", "FLAG16"},
        {NODEPROP_TYPE_FLAG32,  "NODEPROP_TYPE_FLAG8",  "FLAG32"},
        {NODEPROP_TYPE_INT8,    "NODEPROP_TYPE_INT8",   "INT8"},
        {NODEPROP_TYPE_INT16,   "NODEPROP_TYPE_INT16",  "INT16"},
        {NODEPROP_TYPE_INT32,   "NODEPROP_TYPE_INT32",  "INT32"},
        {NODEPROP_TYPE_INT64,   "NODEPROP_TYPE_INT64",  "INT64"},
        {NODEPROP_TYPE_OBJECT,  "NODEPROP_TYPE_OBJECT", "OBJECT"},
        {NODEPROP_TYPE_UINT8,   "NODEPROP_TYPE_UINT8",  "UINT8"},
        {NODEPROP_TYPE_UINT16,  "NODEPROP_TYPE_UINT16", "UINT16"},
        {NODEPROP_TYPE_UINT32,  "NODEPROP_TYPE_UINT32", "UINT32"},
        {NODEPROP_TYPE_UINT64,  "NODEPROP_TYPE_UINT64", "UINT64"},
    };
    static
    const
    uint32_t        cTypeDefs = sizeof(typeDefs) / sizeof(TYPE_DEF);
#endif



 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    uint16_t        NodeProp_TypeDefFromExternal (
        const
        char            *pStrA
    )
    {
        uint32_t            i;

        if (pStrA) {
            for (i=0; i<cTypeDefs; i++) {
                if (0 == strcmp(pStrA, typeDefs[i].pExternal)) {
                    return typeDefs[i].num;
                }
            }
        }
        return 0;
    }


    const
    char *          NodeProp_TypeDefToExternal (
        uint16_t        num
    )
    {
        uint32_t        i;

        if (num) {
            for (i=0; i<cTypeDefs; i++) {
                if (num == typeDefs[i].num) {
                    return typeDefs[i].pExternal;
                }
            }
        }
        return 0;
    }
#endif






    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    NODEPROP_DATA *     NodeProp_Alloc (
        void
    )
    {
        NODEPROP_DATA       *this;
        uint32_t        cbSize = sizeof(NODEPROP_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    NODEPROP_DATA *     NodeProp_New (
        void
    )
    {
        NODEPROP_DATA       *this;
        
        this = NodeProp_Alloc( );
        if (this) {
            this = NodeProp_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          E x t e r n a l
    //---------------------------------------------------------------

    ASTR_DATA *     NodeProp_getExternal (
        NODEPROP_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pExternal;
    }


    bool            NodeProp_setExternal (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pExternal) {
            obj_Release(this->pExternal);
        }
        this->pExternal = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ASTR_DATA * NodeProp_getInit (
        NODEPROP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pInit;
    }


    bool        NodeProp_setInit (
        NODEPROP_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pInit) {
            obj_Release(this->pInit);
        }
        this->pInit = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                       I n t e r n a l
    //---------------------------------------------------------------

    ASTR_DATA * NodeProp_getInternal (
        NODEPROP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pInternal;
    }


    bool        NodeProp_setInternal (
        NODEPROP_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pInternal) {
            obj_Release(this->pInternal);
        }
        this->pInternal = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         L o n g
    //---------------------------------------------------------------

    ASTR_DATA *     NodeProp_getLong (
        NODEPROP_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pLong;
    }


    bool            NodeProp_setLong (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pLong) {
            obj_Release(this->pLong);
        }
        this->pLong = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                            N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     NodeProp_getName (
        NODEPROP_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool        NodeProp_setName (
        NODEPROP_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
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
    
    uint16_t        NodeProp_getPriority (
        NODEPROP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            NodeProp_setPriority (
        NODEPROP_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
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
    
    uint32_t        NodeProp_getSize (
        NODEPROP_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                            S h o r t
    //---------------------------------------------------------------
    
    ASTR_DATA * NodeProp_getShort (
        NODEPROP_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pShort;
    }
    
    
    bool        NodeProp_setShort (
        NODEPROP_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pShort) {
            obj_Release(this->pShort);
        }
        this->pShort = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  NodeProp_getSuperVtbl (
        NODEPROP_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                 T y p e  D e f i n i t i o n
    //---------------------------------------------------------------

    ASTR_DATA *     NodeProp_getTypeDef (
        NODEPROP_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pTypeDef;
    }


    bool            NodeProp_setTypeDef (
        NODEPROP_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pTypeDef) {
            obj_Release(this->pTypeDef);
        }
        this->pTypeDef = pValue;

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
        ERESULT eRc = NodeProp_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another NODEPROP object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         NodeProp_Assign (
        NODEPROP_DATA		*this,
        NODEPROP_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeProp_Validate(pOther)) {
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
        NodeProp_setExternal(pOther, OBJ_NIL);
        NodeProp_setInit(pOther, OBJ_NIL);
        NodeProp_setInternal(pOther, OBJ_NIL);
        NodeProp_setLong(pOther, OBJ_NIL);
        NodeProp_setName(pOther, OBJ_NIL);
        NodeProp_setShort(pOther, OBJ_NIL);
        NodeProp_setTypeDef(pOther, OBJ_NIL);

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pExternal) {
            if (obj_getVtbl(this->pExternal)->pCopy) {
                pOther->pExternal = obj_getVtbl(this->pExternal)->pCopy(this->pExternal);
            }
            else {
                obj_Retain(this->pExternal);
                pOther->pExternal = this->pExternal;
            }
        }
        if (this->pInit) {
            if (obj_getVtbl(this->pInit)->pCopy) {
                pOther->pInit = obj_getVtbl(this->pInit)->pCopy(this->pInit);
            }
            else {
                obj_Retain(this->pInit);
                pOther->pInit = this->pInit;
            }
        }
        if (this->pInternal) {
            if (obj_getVtbl(this->pInternal)->pCopy) {
                pOther->pInternal = obj_getVtbl(this->pInternal)->pCopy(this->pInternal);
            }
            else {
                obj_Retain(this->pInternal);
                pOther->pInternal = this->pInternal;
            }
        }
        if (this->pLong) {
            if (obj_getVtbl(this->pLong)->pCopy) {
                pOther->pLong = obj_getVtbl(this->pLong)->pCopy(this->pLong);
            }
            else {
                obj_Retain(this->pLong);
                pOther->pLong = this->pLong;
            }
        }
        if (this->pName) {
            if (obj_getVtbl(this->pName)->pCopy) {
                pOther->pName = obj_getVtbl(this->pName)->pCopy(this->pName);
            }
            else {
                obj_Retain(this->pName);
                pOther->pName = this->pName;
            }
        }
        if (this->pShort) {
            if (obj_getVtbl(this->pShort)->pCopy) {
                pOther->pShort = obj_getVtbl(this->pShort)->pCopy(this->pShort);
            }
            else {
                obj_Retain(this->pShort);
                pOther->pShort = this->pShort;
            }
        }
        if (this->pTypeDef) {
            if (obj_getVtbl(this->pTypeDef)->pCopy) {
                pOther->pTypeDef = obj_getVtbl(this->pTypeDef)->pCopy(this->pTypeDef);
            }
            else {
                obj_Retain(this->pTypeDef);
                pOther->pTypeDef = this->pTypeDef;
            }
        }

        // Copy other data from this object to other.
        pOther->fObj = this->fObj;
        
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
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         NodeProp_Compare (
        NODEPROP_DATA     *this,
        NODEPROP_DATA     *pOther
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
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!NodeProp_Validate(pOther)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        eRc = AStr_Compare(this->pName, pOther->pName);

        return eRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        NodeProp      *pCopy = NodeProp_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODEPROP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEPROP_DATA *     NodeProp_Copy (
        NODEPROP_DATA       *this
    )
    {
        NODEPROP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef NODEPROP_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = NodeProp_New( );
        if (pOther) {
            eRc = NodeProp_Assign(this, pOther);
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

    void            NodeProp_Dealloc (
        OBJ_ID          objId
    )
    {
        NODEPROP_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((NODEPROP_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        NodeProp_setExternal(this, OBJ_NIL);
        NodeProp_setInit(this, OBJ_NIL);
        NodeProp_setInternal(this, OBJ_NIL);
        NodeProp_setLong(this, OBJ_NIL);
        NodeProp_setName(this, OBJ_NIL);
        NodeProp_setShort(this, OBJ_NIL);
        NodeProp_setTypeDef(this, OBJ_NIL);

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
        NodeProp      *pDeepCopy = NodeProp_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a NODEPROP object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    NODEPROP_DATA *     NodeProp_DeepyCopy (
        NODEPROP_DATA       *this
    )
    {
        NODEPROP_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = NodeProp_New( );
        if (pOther) {
            eRc = NodeProp_Assign(this, pOther);
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
    ERESULT         NodeProp_Disable (
        NODEPROP_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
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
    ERESULT         NodeProp_Enable (
        NODEPROP_DATA		*this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
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
    //                    G e n e r a t e
    //---------------------------------------------------------------

    ASTR_DATA *     NodeProp_GenCode (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        // Generate Documentation
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "//");
        AStr_AppendCharRepeatA(pStr, 62, '-');
        AStr_AppendA(pStr, "\n");
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        if (this->pShort) {
            AStr_AppendA(pStr, "//");
            spcs = 62 - (AStr_getLength(pWrk) + AStr_getLength(this->pShort) + 3);
            spcs >>= 1;
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendPrint(pStr,
                             "%s - %s\n",
                             AStr_getData(pWrk),
                             AStr_getData(this->pShort)
            );
        } else {
            AStr_AppendA(pStr, "//");
            spcs = 62 - (AStr_getLength(pWrk) + 3);
            spcs >>= 1;
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(pWrk)
            );
        }
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "//");
        AStr_AppendCharRepeatA(pStr, 62, '-');
        AStr_AppendA(pStr, "\n\n");

        // Generate Get Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(ERESULT_SUCCESS_EQUAL == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr,
                             "%s *",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - (AStr_getLength(this->pTypeDef) + 2);
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
        }
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_get%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this\n");
        AStr_AppendA(pStr, "    )\n");
        AStr_AppendA(pStr, "    {\n\n");
        AStr_AppendA(pStr, "#ifdef NDEBUG\n#else\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "if (%s_Validate(this)) {\n", pClass);
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        AStr_AppendA(pStr, "DEBUG_BREAK();\n");
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        if (this->fObj)
            AStr_AppendA(pStr, "return OBJ_NIL;\n");
        else
            AStr_AppendA(pStr, "return 0;\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendA(pStr, "}\n");
        AStr_AppendA(pStr, "#end\n\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        if (this->pInternal)
            AStr_AppendPrint(pStr, "return this->%s\n", AStr_getData(this->pInternal));
        else
            AStr_AppendPrint(pStr, "return this->%s\n", AStr_getData(this->pName));
        AStr_AppendA(pStr, "    }\n\n");

        // Generate Set Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "bool");
        spcs = 16 - 4;
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_set%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this,\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        spcs = 16 - AStr_getLength(this->pTypeDef);
        if (spcs < 1)
            spcs = 1;
        if (this->fObj
            && !(ERESULT_SUCCESS_EQUAL == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "*pValue,\n");
        } else {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "value\n");
        }
        AStr_AppendA(pStr, "    )\n");
        AStr_AppendA(pStr, "    {\n\n");
        AStr_AppendA(pStr, "#ifdef NDEBUG\n#else\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "if (%s_Validate(this)) {\n", pClass);
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        AStr_AppendA(pStr, "DEBUG_BREAK();\n");
        AStr_AppendCharRepeatA(pStr, 12, ' ');
        AStr_AppendA(pStr, "return false;\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendA(pStr, "}\n");
        AStr_AppendA(pStr, "#end\n\n");
        if (this->fObj) {
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            AStr_AppendA(pStr, "obj_Retain(pValue);\n");
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            if (this->pInternal) {
                AStr_AppendPrint(pStr,
                                 "if (this->%s) {\n",
                                 AStr_getData(this->pInternal)
                );
                AStr_AppendCharRepeatA(pStr, 12, ' ');
                AStr_AppendPrint(pStr,
                                 "obj_Release(this->%s);\n",
                                 AStr_getData(this->pInternal)
                );
            } else {
                AStr_AppendPrint(pStr,
                                 "if (this->%s) {\n",
                                 AStr_getData(this->pName)
                );
                AStr_AppendCharRepeatA(pStr, 12, ' ');
                AStr_AppendPrint(pStr,
                                 "obj_Release(this->%s);\n",
                                 AStr_getData(this->pName)
                );
            }
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            AStr_AppendA(pStr, "}\n");
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            if (this->pInternal) {
                AStr_AppendPrint(pStr,
                                 "this->%s = pValue;\n",
                                 AStr_getData(this->pInternal)
                );
            } else {
                AStr_AppendPrint(pStr,
                                 "this->%s = pValue;\n",
                                 AStr_getData(this->pName)
                );
            }
        } else {
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            if (this->pInternal) {
                AStr_AppendPrint(pStr,
                                 "this->%s = value;\n",
                                 AStr_getData(this->pInternal)
                );
            } else {
                AStr_AppendPrint(pStr,
                                 "this->%s = value;\n",
                                 AStr_getData(this->pName)
                );
            }
        }

        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendA(pStr, "return true;\n");
        AStr_AppendA(pStr, "    }\n\n");

        // Generate WS
        AStr_AppendA(pStr, "\n");

        return pStr;
    }


    ASTR_DATA *     NodeProp_GenHdrDefn (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if ((this->vis == NODEPROP_VIS_PUBLIC) || (this->vis == NODEPROP_VIS_READ_ONLY)) {
            pStr = AStr_New();
        }
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        // Generate Documentation
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        if (this->pShort) {
            AStr_AppendPrint(pStr,
                             "/*! @property %s - %s\n",
                             AStr_getData(pWrk),
                             AStr_getData(this->pShort)
            );
        } else {
            AStr_AppendPrint(pStr,
                             "/*! @property %s\n",
                             AStr_getData(pWrk)
            );
        }
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 5, ' ');
        AStr_AppendA(pStr, "*/\n");

        // Generate Get Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(ERESULT_SUCCESS_EQUAL == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr,
                             "%s *",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - (AStr_getLength(this->pTypeDef) + 2);
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
        }
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_get%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this\n");
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, ");\n\n");

        // Generate Set Method
        if (this->vis == NODEPROP_VIS_PUBLIC) {
            AStr_AppendCharRepeatA(pStr, 4, ' ');
            AStr_AppendA(pStr, "bool");
            spcs = 16 - 4;
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            if (this->pExternal) {
                pWrk = AStr_ToUpperName(this->pExternal);
            } else {
                pWrk = AStr_ToUpperName(this->pName);
            }
            AStr_AppendPrint(pStr,
                             "%s_set%s (\n",
                             pClass,
                             AStr_getData(pWrk)
            );
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            AStr_AppendPrint(pStr, "%s", pClassUC);
            spcs = 16 - (int32_t)strlen(pClassUC);
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "*this,\n");
            AStr_AppendCharRepeatA(pStr, 8, ' ');
            spcs = 16 - AStr_getLength(this->pTypeDef);
            if (spcs < 1)
                spcs = 1;
            if (this->fObj
                && !(ERESULT_SUCCESS_EQUAL == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
                AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
                AStr_AppendCharRepeatA(pStr, spcs, ' ');
                AStr_AppendA(pStr, "*pValue,\n");
            } else {
                AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
                AStr_AppendCharRepeatA(pStr, spcs, ' ');
                AStr_AppendA(pStr, "value\n");
            }
            AStr_AppendCharRepeatA(pStr, 4, ' ');
            AStr_AppendA(pStr, ");\n\n");
        }

        // Generate WS
        AStr_AppendA(pStr, "\n");

        return pStr;
    }


    ASTR_DATA *     NodeProp_GenIntDefn (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        // Generate Documentation
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        if (this->pShort) {
            AStr_AppendPrint(pStr,
                             "/*! @property %s - %s\n",
                             AStr_getData(pWrk),
                             AStr_getData(this->pShort)
            );
        } else {
            AStr_AppendPrint(pStr,
                             "/*! @property %s\n",
                             AStr_getData(pWrk)
            );
        }
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 5, ' ');
        AStr_AppendA(pStr, "*/\n");

        // Generate Get Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(ERESULT_SUCCESS_EQUAL == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr,
                             "%s *",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - (AStr_getLength(this->pTypeDef) + 2);
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
        }
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_get%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this\n");
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, ");\n\n");

        // Generate Set Method
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, "bool");
        spcs = 16 - 4;
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        if (this->pExternal) {
            pWrk = AStr_ToUpperName(this->pExternal);
        } else {
            pWrk = AStr_ToUpperName(this->pName);
        }
        AStr_AppendPrint(pStr,
                         "%s_set%s (\n",
                         pClass,
                         AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        pWrk = OBJ_NIL;
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        AStr_AppendPrint(pStr, "%s", pClassUC);
        spcs = 16 - (int32_t)strlen(pClassUC);
        if (spcs < 1)
            spcs = 1;
        AStr_AppendCharRepeatA(pStr, spcs, ' ');
        AStr_AppendA(pStr, "*this,\n");
        AStr_AppendCharRepeatA(pStr, 8, ' ');
        spcs = 16 - AStr_getLength(this->pTypeDef);
        if (spcs < 1)
            spcs = 1;
        if (this->fObj
            && !(ERESULT_SUCCESS_EQUAL == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "*pValue,\n");
        } else {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            AStr_AppendA(pStr, "value\n");
        }
        AStr_AppendCharRepeatA(pStr, 4, ' ');
        AStr_AppendA(pStr, ");\n\n");

        // Generate WS
        AStr_AppendA(pStr, "\n");

        return pStr;
    }


    ASTR_DATA *     NodeProp_GenIntVar (
        NODEPROP_DATA   *this,
        const
        char            *pClass,
        const
        char            *pClassUC
    )
    {
        //ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pWrk = OBJ_NIL;
        //ASTR_DATA       *pWrkStr;
        //uint32_t        i;
        //uint32_t        j;
        int32_t         spcs = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return pStr;
        }

        AStr_AppendCharRepeatA(pStr, 4, ' ');
        if (this->fObj
            && !(ERESULT_SUCCESS_EQUAL == AStr_CompareA(this->pTypeDef, "OBJ_ID"))) {
            AStr_AppendPrint(pStr, "%s", AStr_getData(this->pTypeDef));
            spcs = 16 - AStr_getLength(this->pTypeDef);
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            if (this->pInternal) {
                pWrk = this->pInternal;
            } else {
                pWrk = this->pName;
            }
            AStr_AppendPrint(pStr, "*%s;\n", AStr_getData(pWrk));
        } else {
            AStr_AppendPrint(pStr,
                             "%s",
                             AStr_getData(this->pTypeDef)
            );
            spcs = 16 - AStr_getLength(this->pTypeDef);
            if (spcs < 1)
                spcs = 1;
            AStr_AppendCharRepeatA(pStr, spcs, ' ');
            if (this->pInternal) {
                pWrk = this->pInternal;
            } else {
                pWrk = this->pName;
            }
            AStr_AppendPrint(pStr, "%s;\n", AStr_getData(pWrk));
        }

        return pStr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    NODEPROP_DATA *   NodeProp_Init (
        NODEPROP_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(NODEPROP_DATA);
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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_NODEPROP);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&NodeProp_Vtbl);
        
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
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "NodeProp::sizeof(NODEPROP_DATA) = %lu\n", 
                sizeof(NODEPROP_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(NODEPROP_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         NodeProp_IsEnabled (
        NODEPROP_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
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
        void        *pMethod = NodeProp_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "NodeProp", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          NodeProp_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        NODEPROP_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!NodeProp_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(NODEPROP_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)NodeProp_Class();
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
                            return NodeProp_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return NodeProp_Enable;
                        }
                        break;

                    case 'P':
#ifdef  NODEPROP_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return NodeProp_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return NodeProp_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return NodeProp_ToDebugString;
                        }
#ifdef  NODEPROP_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return NodeProp_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return NodeProp_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == NodeProp_ToDebugString)
                    return "ToDebugString";
#ifdef  NODEPROP_JSON_SUPPORT
                if (pData == NodeProp_ToJson)
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
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = NodeProp_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     NodeProp_ToDebugString (
        NODEPROP_DATA      *this,
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
        if (!NodeProp_Validate(this)) {
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
                    NodeProp_getSize(this),
                    obj_getRetainCount(this)
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
    bool            NodeProp_Validate (
        NODEPROP_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_NODEPROP))
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


        if (!(obj_getSize(this) >= sizeof(NODEPROP_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef	__cplusplus
}
#endif


