// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Item.c
 *  Generated 11/12/2021 13:39:34
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
#include        <Item_internal.h>
#include        <JsonIn.h>
#include        <misc.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif
    

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.

    /* The following tables were generated from:
     * "item_types.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the Item_Type_entries
    // table. 0 means no enum entry.
    static
    const
    uint16_t    Item_Type_index[7] = {
        6, 1, 2, 3, 4, 5, 7,
    };

    static
    const
    uint32_t    cItem_Type_index = 7;




    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } Item_Type_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    static
    const
    Item_Type_entry    Item_Type_entries[] = {
        {"ITEM_TYPE_COMMENT", "", "COMMENT", 1},
        {"ITEM_TYPE_GENERAL", "", "GENERAL", 2},
        {"ITEM_TYPE_HEADING", "", "HEADING", 3},
        {"ITEM_TYPE_LINK", "", "LINK", 4},
        {"ITEM_TYPE_TITLE", "", "TITLE", 5},
        {"ITEM_TYPE_UNKNOWN", "", "UNKNOWN", 0},
        {"ITEM_TYPE_WEBSITES", "", "WEBSITES", 6},
    };

    static
    uint32_t    cItem_Type_entries = 7;




 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* The following routine was generated from:
     * "item_types.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum value, return its character format.
    const
    char *            Item_TypeToEnum (
        uint32_t        value
    )
    {
        if (value >= cItem_Type_index) {
            return "<<<Unknown Enum Value>>>";
        }
        if (Item_Type_index[value]) {
            return Item_Type_entries[Item_Type_index[value] - 1].pEnum;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }

    // Given an enum value, return its name.
    const
    char *            Item_TypeToName (
        uint32_t        value
    )
    {
        if (value >= cItem_Type_index) {
            return NULL;
        }
        if (Item_Type_index[value]) {
            return Item_Type_entries[Item_Type_index[value] - 1].pName;
        } else {
            return NULL;
        }
    }



    /* The following routine was generated from:
     * "item_types.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        Item_EnumToType (
        char            *pDescA
    )
    {
        Item_Type_entry *pEntry = NULL;
        uint32_t        value = 0;

        if (pDescA) {
            pEntry = misc_SearchBinary(
                        pDescA,
                        (void *)Item_Type_entries,
                        cItem_Type_entries,
                        sizeof(Item_Type_entry),
                        offsetof(Item_Type_entry, pEnum),
                        (void *)strcmp
                );
            if (pEntry) {
                value = pEntry->value + 1;
            }
        }
        return value;
    }




    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    ITEM_DATA *     Item_Alloc (
        void
    )
    {
        ITEM_DATA       *this;
        uint32_t        cbSize = sizeof(ITEM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    ITEM_DATA *     Item_New (
        void
    )
    {
        ITEM_DATA       *this;
        
        this = Item_Alloc( );
        if (this) {
            this = Item_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         D e s c
    //---------------------------------------------------------------

    ASTR_DATA *     Item_getDesc (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDesc;
    }


    bool            Item_setDesc (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
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
    //                       D i r e c t o r y
    //---------------------------------------------------------------

    ASTR_DATA *     Item_getDir (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDir;
    }


    bool            Item_setDir (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDir) {
            obj_Release(this->pDir);
        }
        this->pDir = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                      F i l e  N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     Item_getFileName (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pFileName;
    }


    bool            Item_setFileName (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pFileName) {
            obj_Release(this->pFileName);
        }
        this->pFileName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         H e a d i n g s
    //---------------------------------------------------------------

    ASTRARRAY_DATA * Item_getHeadings (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pHeadings;
    }


    bool            Item_setHeadings (
        ITEM_DATA       *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pHeadings) {
            obj_Release(this->pHeadings);
        }
        this->pHeadings = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                       I d e n t i f i e r
    //---------------------------------------------------------------

    ASTR_DATA *     Item_getIdent (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pIdent;
    }


    bool            Item_setIdent (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pIdent) {
            obj_Release(this->pIdent);
        }
        this->pIdent = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                       K e y  W o r d s
    //---------------------------------------------------------------

    ASTRARRAY_DATA * Item_getKeyWords (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pKeyWords;
    }


    bool            Item_setKeyWords (
        ITEM_DATA       *this,
        ASTRARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pKeyWords) {
            obj_Release(this->pKeyWords);
        }
        this->pKeyWords = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     Item_getName (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pName;
    }


    bool            Item_setName (
        ITEM_DATA       *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
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
    
    int32_t         Item_getPriority (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->priority;
    }


    bool            Item_setPriority (
        ITEM_DATA       *this,
        int32_t         value
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->priority = value;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Item_getSize (
        ITEM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Item_getSuperVtbl (
        ITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  
    OBJ_DATA *      Item_getSuper (
        ITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJ_DATA *)this;
    }

    

    //---------------------------------------------------------------
    //                          T y p e
    //---------------------------------------------------------------

    uint32_t        Item_getType (
        ITEM_DATA       *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->type;
    }


    bool            Item_setType (
        ITEM_DATA       *this,
        uint32_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->type = value;

        return true;
    }




    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          A d d
    //---------------------------------------------------------------

    ERESULT         Item_AddHeadingsA (
        ITEM_DATA       *this,
        ...
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        va_list         pList;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        va_start(pList, this);
        for (;;) {
            char        *pStrA = va_arg(pList, char *);
            if (pStrA) {
                pStr = AStr_NewA(pStrA);
                if (pStr) {
                    AStrArray_AppendStr(this->pHeadings, pStr, NULL);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            else
                break;
        }
        va_end(pList);

        // Return to caller.
        return eRc;
    }


    ERESULT         Item_AddKeyWordsA (
        ITEM_DATA       *this,
        ...
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        va_list         pList;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        va_start(pList, this);
        for (;;) {
            char        *pStrA = va_arg(pList, char *);
            if (pStrA) {
                pStr = AStr_NewA(pStrA);
                if (pStr) {
                    AStrArray_AppendStr(this->pKeyWords, pStr, NULL);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            else
                break;
        }
        va_end(pList);

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                       A s s i g n
    //---------------------------------------------------------------
    
    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before 
     a copy of the object is performed.
     Example:
     @code 
        ERESULT eRc = Item_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another ITEM object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Item_Assign (
        ITEM_DATA       *this,
        ITEM_DATA       *pOther
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Item_Validate(pOther)) {
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
        if (pOther->pDesc) {
            obj_Release(pOther->pDesc);
            pOther->pDesc = OBJ_NIL;
        }
        if (pOther->pDir) {
            obj_Release(pOther->pDir);
            pOther->pDir = OBJ_NIL;
        }
        if (pOther->pFileName) {
            obj_Release(pOther->pFileName);
            pOther->pFileName = OBJ_NIL;
        }
        if (pOther->pHeadings) {
            obj_Release(pOther->pHeadings);
            pOther->pHeadings = OBJ_NIL;
        }
        if (pOther->pIdent) {
            obj_Release(pOther->pIdent);
            pOther->pIdent = OBJ_NIL;
        }
        if (pOther->pKeyWords) {
            obj_Release(pOther->pKeyWords);
            pOther->pKeyWords = OBJ_NIL;
        }
        if (pOther->pName) {
            obj_Release(pOther->pName);
            pOther->pName = OBJ_NIL;
        }

        // Create a copy of objects and areas in this object placing
        // them in other.
        if (this->pDesc) {
            pOther->pDesc = AStr_Copy(this->pDesc);
        }
        if (this->pDir) {
            pOther->pDir = AStr_Copy(this->pDir);
        }
        if (this->pFileName) {
            pOther->pFileName = AStr_Copy(this->pFileName);
        }
        if (this->pHeadings) {
            pOther->pHeadings = AStrArray_Copy(this->pHeadings);
        } else {
            pOther->pHeadings = AStrArray_New();
        }
        if (this->pIdent) {
            pOther->pIdent = AStr_Copy(this->pIdent);
        }
        if (this->pKeyWords) {
            pOther->pKeyWords = AStrArray_Copy(this->pKeyWords);
        } else {
            pOther->pKeyWords = AStrArray_New();
        }
        if (this->pName) {
            pOther->pName = AStr_Copy(this->pName);
        }

        // Copy other data from this object to other.
        pOther->type = this->type;

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
    int             Item_Compare (
        ITEM_DATA     *this,
        ITEM_DATA     *pOther
    )
    {
        int             iRc = -1;
        
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Item_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        if (this->pDir) {
            iRc = AStr_Compare(Item_getDir(this), Item_getDir(pOther));
        } else if (this->pFileName) {
            iRc = AStr_Compare(Item_getFileName(this), Item_getFileName(pOther));
        } else {
            iRc = -2;
        }


        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Item      *pCopy = Item_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ITEM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ITEM_DATA *     Item_Copy (
        ITEM_DATA       *this
    )
    {
        ITEM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef ITEM_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Item_New( );
        if (pOther) {
            eRc = Item_Assign(this, pOther);
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

    void            Item_Dealloc (
        OBJ_ID          objId
    )
    {
        ITEM_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((ITEM_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Item_setDesc(this, OBJ_NIL);
        Item_setDir(this, OBJ_NIL);
        Item_setFileName(this, OBJ_NIL);
        Item_setHeadings(this, OBJ_NIL);
        Item_setIdent(this, OBJ_NIL);
        Item_setKeyWords(this, OBJ_NIL);
        Item_setName(this, OBJ_NIL);

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
        Item      *pDeepCopy = Item_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a ITEM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    ITEM_DATA *     Item_DeepCopy (
        ITEM_DATA       *this
    )
    {
        ITEM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Item_New( );
        if (pOther) {
            eRc = Item_Assign(this, pOther);
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
    ERESULT         Item_Disable (
        ITEM_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Put code here...

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
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
    ERESULT         Item_Enable (
        ITEM_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                    G e n e r a t e
    //---------------------------------------------------------------

    /*!
     Generate the HTML link for this item if it has a file name and
     a deescription.
     @param     this    object pointer
     @param     pStr    AStr object pointer that the link string will
                        be appended to
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Item_Generate (
        ITEM_DATA       *this,
        ASTR_DATA       *pStr
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pName = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (pStr && this->pFileName && this->pDesc) {
            if (this->pName) {
                pName = AStr_NewFromPrint(
                                          " id=\"%s\"",
                                          AStr_getData(this->pName)
                        );
            }
            eRc =   AStr_AppendPrint(
                            pStr,
                            "<li%s><a href=\"./%s\" target=\"_blank\">%s</a></li>",
                            pName ? AStr_getData(pName) : "",
                            AStr_getData(this->pFileName),
                            AStr_getData(this->pDesc)
                    );
            obj_Release(pName);
            pName = OBJ_NIL;
        } else {
            eRc = ERESULT_DATA_MISSING;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    ITEM_DATA *   Item_Init (
        ITEM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(ITEM_DATA);
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

        //this = (OBJ_ID)Node_Init((NODE_DATA *)this);    // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Item_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_ITEM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Item_Vtbl);
#ifdef  ITEM_JSON_SUPPORT
        JsonIn_RegisterClass(Item_Class());
#endif
        
        this->pHeadings = AStrArray_New( );
        if (OBJ_NIL == this->pHeadings) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

        this->pKeyWords = AStrArray_New( );
        if (OBJ_NIL == this->pKeyWords) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Item::sizeof(ITEM_DATA) = %lu\n", 
                sizeof(ITEM_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(ITEM_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Item_IsEnabled (
        ITEM_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
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
        void        *pMethod = Item_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Item", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Item_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        ITEM_DATA       *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(ITEM_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Item_Class();
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
                            return Item_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Item_Enable;
                        }
                        break;

                    case 'P':
#ifdef  ITEM_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Item_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Item_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Item_ToDebugString;
                        }
#ifdef  ITEM_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Item_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Item_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Item_ToDebugString)
                    return "ToDebugString";
#ifdef  ITEM_JSON_SUPPORT
                if (pData == Item_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e t u p
    //---------------------------------------------------------------

    /*!
     Establish an item from a set of strings. The item must have a
     directory name or a file name, but not both. If a file name is
     present, it will be linked with the description to become an
     HTML link (ie <li></li>).
     @param     this        object pointer
     @param     pDirA       optional directory name (which should match current
                            directory)
     @param     pFileNameA  optional file name (which must match a file name in
                            the current directory)
     @param     pDescA      description (which will become the visible portion
                            of the generated link <li></li>)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Item_SetupA (
        ITEM_DATA       *this,
        const
        char            *pDirA,
        const
        char            *pFileNameA,
        const
        char            *pDescA,
        ...
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        va_list         pList;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  ITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = Item_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (pDirA && pFileNameA) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (pDirA) {
            pStr = AStr_NewA(pDirA);
            if (pStr) {
                Item_setDir(this, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        if (pFileNameA) {
            pStr = AStr_NewA(pFileNameA);
            if (pStr) {
                Item_setFileName(this, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        if (pDescA) {
            pStr = AStr_NewA(pDescA);
            if (pStr) {
                Item_setDesc(this, pStr);
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        va_start(pList, pDescA);
        for (;;) {
            char        *pStrA = va_arg(pList, char *);
            if (pStrA) {
                pStr = AStr_NewA(pStrA);
                if (pStr) {
                    AStrArray_AppendStr(this->pHeadings, pStr, NULL);
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                }
            }
            else
                break;
        }
        va_end(pList);

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
        ASTR_DATA      *pDesc = Item_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Item_ToDebugString (
        ITEM_DATA       *this,
        int             indent
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        uint32_t        i;
        uint32_t        iMax;
        //uint32_t        j;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Item_Validate(this)) {
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
                    Item_getSize(this),
                    obj_getRetainCount(this)
            );
        if (this->pDir) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "dir=\"%s\"\n",
                        AStr_getData(this->pDir)
                );
        }
        if (this->pFileName) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "filename=\"%s\"\n",
                        AStr_getData(this->pFileName)
                );
        }
        if (this->pDesc) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "desc=\"%s\"\n",
                        AStr_getData(this->pDesc)
                );
        }
        if (this->pIdent) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "dir=\"%s\"\n",
                        AStr_getData(this->pIdent)
                );
        }
        if (this->pHeadings) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(pStr, "headings=[\n");
            iMax = AStrArray_getSize(this->pHeadings);
            for (i=0; i<iMax; i++) {
                ASTR_DATA       *pWrk = AStrArray_Get(this->pHeadings, i+1);
                if (pWrk) {
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent+8, ' ');
                    }
                    eRc = AStr_AppendPrint(
                                pStr,
                                "%s\n",
                                AStr_getData(pWrk)
                        );
                }
            }
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(pStr, "]\n");
        }
        if (this->pKeyWords) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(pStr, "keywords=[\n");
            iMax = AStrArray_getSize(this->pKeyWords);
            for (i=0; i<iMax; i++) {
                ASTR_DATA       *pWrk = AStrArray_Get(this->pKeyWords, i+1);
                if (pWrk) {
                    if (indent) {
                        AStr_AppendCharRepeatA(pStr, indent+8, ' ');
                    }
                    eRc = AStr_AppendPrint(
                                pStr,
                                "%s\n",
                                AStr_getData(pWrk)
                        );
                }
            }
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(pStr, "]\n");
        }
        if (this->pName) {
            if (indent) {
                AStr_AppendCharRepeatA(pStr, indent+4, ' ');
            }
            eRc = AStr_AppendPrint(
                        pStr,
                        "name=\"%s\"\n",
                        AStr_getData(this->pName)
                );
        }
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent+4, ' ');
        }
        eRc = AStr_AppendPrint(pStr, "type=%d\n", this->type);

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
    bool            Item_Validate (
        ITEM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_ITEM))
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


        if (!(obj_getSize(this) >= sizeof(ITEM_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


