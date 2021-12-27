// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Index.c
 *  Generated 12/22/2021 13:33:31
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
#include        <Index_internal.h>
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
     * "node_classes.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the IndexNode_Class_entries
    // table. 0 means no enum entry.
    const
    uint16_t    IndexNode_Class_index[7] = {
        6, 1, 2, 3, 4, 5, 7,
    };

    const
    uint32_t    cIndexNode_Class_index = 7;




    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } IndexNode_Class_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    const
    IndexNode_Class_entry    IndexNode_Class_entries[] = {
        {"INDEXNODE_CLASS_COMMENT", "", "COMMENT", 1},
        {"INDEXNODE_CLASS_GENERAL", "", "GENERAL", 2},
        {"INDEXNODE_CLASS_HEADING", "", "HEADING", 3},
        {"INDEXNODE_CLASS_LINK", "", "LINK", 4},
        {"INDEXNODE_CLASS_TITLE", "", "TITLE", 5},
        {"INDEXNODE_CLASS_UNKNOWN", "", "UNKNOWN", 0},
        {"INDEXNODE_CLASS_WEBSITES", "", "WEBSITES", 6},
    };

    uint32_t    cIndexNode_Class_entries = 7;





 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/



    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* The following routine was generated from:
     * "node_classes.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum value, return its character format.
    const
    char *            IndexNode_ClassToEnum (
        uint32_t        value
    )
    {
        if (value >= cIndexNode_Class_index) {
            return "<<<Unknown Enum Value>>>";
        }
        if (IndexNode_Class_index[value]) {
            return IndexNode_Class_entries[IndexNode_Class_index[value] - 1].pEnum;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }

    // Given an enum value, return its name.
    const
    char *            IndexNode_ClassToName (
        uint32_t        value
    )
    {
        if (value >= cIndexNode_Class_index) {
            return NULL;
        }
        if (IndexNode_Class_index[value]) {
            return IndexNode_Class_entries[IndexNode_Class_index[value] - 1].pName;
        } else {
            return NULL;
        }
    }



    /* The following routine was generated from:
     * "node_classes.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        IndexNode_EnumToClass (
        char            *pDescA
    )
    {
        IndexNode_Class_entry    *pEntry = NULL;
        uint32_t        value = 0;

        if (pDescA) {
            pEntry = misc_SearchBinary(
                        pDescA,
                        (void *)IndexNode_Class_entries,
                        cIndexNode_Class_entries,
                        sizeof(IndexNode_Class_entry),
                        offsetof(IndexNode_Class_entry, pEnum),
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

    INDEX_DATA *     Index_Alloc (
        void
    )
    {
        INDEX_DATA       *this;
        uint32_t        cbSize = sizeof(INDEX_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    INDEX_DATA *     Index_New (
        void
    )
    {
        INDEX_DATA       *this;
        
        this = Index_Alloc( );
        if (this) {
            this = Index_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                           D i r
    //---------------------------------------------------------------

    PATH_DATA *     Index_getDir (
        INDEX_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDir;
    }


    bool            Index_setDir (
        INDEX_DATA      *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
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
    //                           D r i v e
    //---------------------------------------------------------------

    ASTR_DATA *     Index_getDrive (
        INDEX_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDrv;
    }


    bool            Index_setDrive (
        INDEX_DATA      *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDrv) {
            obj_Release(this->pDrv);
        }
        this->pDrv = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                        E x c l u d e s
    //---------------------------------------------------------------

    PATHARRAY_DATA * Index_getExcludes (
        INDEX_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pExcludes;
    }


    bool            Index_setExcludes (
        INDEX_DATA      *this,
        PATHARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pExcludes) {
            obj_Release(this->pExcludes);
        }
        this->pExcludes = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                        I t e m s
    //---------------------------------------------------------------

    OBJARRAY_DATA * Index_getItems (
        INDEX_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pItems;
    }


    bool            Index_setItems (
        INDEX_DATA      *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pItems) {
            obj_Release(this->pItems);
        }
        this->pItems = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          L o g
    //---------------------------------------------------------------

#ifdef   INDEX_LOG
    bool            Index_setLog (
        INDEX_DATA   *this,
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pLog = pObj;

        return true;
    }
#endif



    //---------------------------------------------------------------
    //                           P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Index_getPath (
        INDEX_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pPath;
    }


    bool            Index_setPath (
        INDEX_DATA      *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
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
    
    uint16_t        Index_getPriority (
        INDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            Index_setPriority (
        INDEX_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
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
    
    uint32_t        Index_getSize (
        INDEX_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    INDEX_DATA *  Index_getSuper (
        INDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (INDEX_DATA *)this;
    }

    OBJ_IUNKNOWN *  Index_getSuperVtbl (
        INDEX_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                        T o p
    //---------------------------------------------------------------

    PATHARRAY_DATA * Index_getTop (
        INDEX_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pTop;
    }


    bool            Index_setTop (
        INDEX_DATA      *this,
        PATHARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pTop) {
            obj_Release(this->pTop);
        }
        this->pTop = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                           T r e e
    //---------------------------------------------------------------

    NODETREE_DATA * Index_getTree (
        INDEX_DATA      *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pTree;
    }


    bool            Index_setTree (
        INDEX_DATA      *this,
        NODETREE_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pTree) {
            obj_Release(this->pTree);
        }
        this->pTree = pValue;

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
        ERESULT eRc = Index_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another INDEX object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Index_Assign (
        INDEX_DATA       *this,
        INDEX_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Index_Validate(pOther)) {
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Index_Compare (
        INDEX_DATA     *this,
        INDEX_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Index_Validate(pOther)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_PARAMETER;
            return -2;
        }
#endif

        //TODO: iRc = utf8_StrCmp(AStr_getData(this->pStr), AStr_getData(pOther->pStr));
     
        return iRc;
    }
    
   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Index      *pCopy = Index_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a INDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    INDEX_DATA *     Index_Copy (
        INDEX_DATA       *this
    )
    {
        INDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef INDEX_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = Index_New( );
        if (pOther) {
            eRc = Index_Assign(this, pOther);
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
    //            C r e a t e  D i r e c t o r y  P a t h
    //---------------------------------------------------------------

    /*!
     Create the path to directory to be indexed.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    PATH_DATA *     Index_CreateDirPath (
        INDEX_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif

        pPath = Path_NewFromDriveDirFilename(this->pDrv, OBJ_NIL, OBJ_NIL);
        if (pPath) {
            if (this->pExcludes) {
                eRc = Path_AppendDirs(pPath, this->pExcludes);
            }
            if (this->pTop) {
                eRc = Path_AppendDirs(pPath, this->pTop);
            }
            eRc = Path_AppendDir(pPath, (ASTR_DATA *)this->pDir);
        }

        // Return to caller.
        return pPath;
    }



    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            Index_Dealloc (
        OBJ_ID          objId
    )
    {
        INDEX_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((INDEX_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        Index_setDir(this, OBJ_NIL);
        Index_setDrive(this, OBJ_NIL);
        Index_setExcludes(this, OBJ_NIL);
        Index_setItems(this, OBJ_NIL);
        Index_setPath(this, OBJ_NIL);
        Index_setTop(this, OBJ_NIL);
        Index_setTree(this, OBJ_NIL);

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
        Index      *pDeepCopy = Index_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a INDEX object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    INDEX_DATA *     Index_DeepCopy (
        INDEX_DATA       *this
    )
    {
        INDEX_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Index_New( );
        if (pOther) {
            eRc = Index_Assign(this, pOther);
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
    ERESULT         Index_Disable (
        INDEX_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
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
    ERESULT         Index_Enable (
        INDEX_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   INDEX_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                  G a t h e r  I t e m s
    //---------------------------------------------------------------

    /*!
     Gather up the items that will make up the main and site link indices.
     @param     this    object pointer
     @param     pPath   Path object pointer to subdirectory with items in it.
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Index_GatherItems (
        INDEX_DATA      *this,
        PATH_DATA       *pPath
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        DIR_DATA        *pDir = OBJ_NIL;
        OBJENUM_DATA    *pEnum;
        DIRENTRY_DATA   *pEntry;
        uint32_t        count;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (
            (OBJ_NIL == pPath)
            || !obj_IsKindOf(pPath, OBJ_IDENT_PATH)
            || !Path_IsDir(pPath)
        ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        TRC_OBJ(this,"\tEnabled?: %s:\n", obj_Enable(this) ? "true" : "false");
#ifdef   INDEX_MSGS
        if (this->pMsgInfo) {
            this->pMsgInfo(this->pMsgObj, "Enabling object!\n");
        }
#endif
        pDir = Dir_New();
        if (OBJ_NIL == pDir) {
            return ERESULT_OUT_OF_MEMORY;
        }
        pEnum = Dir_EnumDir(pDir, pPath, false);
        if (OBJ_NIL == pEnum) {
            obj_Release(pDir);
            return ERESULT_OUT_OF_MEMORY;
        }
        if (OBJ_NIL == this->pItems) {
            this->pItems = ObjArray_New();
            if (OBJ_NIL == this->pItems) {
                obj_Release(pDir);
                return ERESULT_OUT_OF_MEMORY;
            }
        }

        for (;;) {
            eRc = ObjEnum_Next(pEnum, 1, (void **)&pEntry, &count);
            if (ERESULT_FAILED(eRc) || (OBJ_NIL == pEntry)) {
                break;
            }
            DirEntry_Complete(pEntry);
#ifdef NDEBUG
#else
            if (obj_Trace(this)) {
                fprintf(
                        stderr,
                        "\tname: %-25s  type: %2d  gen: %d\n",
                        Path_getData(DirEntry_getFullPath(pEntry)),
                        DirEntry_getType(pEntry),
                        DirEntry_getGenerationNumber(pEntry)
                );
            }
#endif
            eRc = DirEntry_MatchA(pEntry, "*.json.txt");
            if (ERESULT_OK(eRc)) {
                ITEM_DATA       *pItem;
                ASTR_DATA       *pStr;
                TRC_OBJ(this,"\t\tIs Index Link!\n");
                // Read Item and add it to the table.
                pStr = AStr_NewFromUtf8File(DirEntry_getFullPath(pEntry));
                pItem = Item_NewFromJsonString(pStr);
                if (pItem) {
                    ObjArray_Append(this->pItems, (OBJ_ID)pItem);
                    obj_Release(pItem);
                }
                obj_Release(pStr);
            }
        }
        obj_Release(pEnum);
        obj_Release(pDir);
        eRc = ERESULT_SUCCESS;

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      G e n e r a t e
    //---------------------------------------------------------------

    ERESULT         Index_Generate (
        INDEX_DATA      *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        PATH_DATA       *pPath;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        pPath = Index_CreateDirPath(this);
        if (pPath) {
            return ERESULT_DATA_MISSING;
        }
        if (!Path_IsDir(pPath)) {
            return ERESULT_DATA_MISSING;
        }

        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    INDEX_DATA *   Index_Init (
        INDEX_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(INDEX_DATA);
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

        //this = (OBJ_ID)Index_Init((INDEX_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of Index_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_INDEX);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Index_Vtbl);
#ifdef  INDEX_JSON_SUPPORT
        JsonIn_RegisterClass(Index_Class());
#endif
        
        /*
        this->pArray = ObjArray_New( );
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        */

#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "Index::sizeof(INDEX_DATA) = %lu\n", 
                sizeof(INDEX_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(INDEX_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Index_IsEnabled (
        INDEX_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
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
        void        *pMethod = Index_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Index", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Index_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        INDEX_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(INDEX_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Index_Class();
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
                            return Index_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Index_Enable;
                        }
                        break;

                    case 'P':
#ifdef  INDEX_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return Index_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return Index_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Index_ToDebugString;
                        }
#ifdef  INDEX_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return Index_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Index_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Index_ToDebugString)
                    return "ToDebugString";
#ifdef  INDEX_JSON_SUPPORT
                if (pData == Index_ToJson)
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

    ERESULT         Index_Setup (
        INDEX_DATA      *this,
        ASTR_DATA       *pDrv,
        PATHARRAY_DATA  *pExcludes,
        PATHARRAY_DATA  *pTop,
        PATH_DATA       *pDir
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        NODETREE_DATA   *pTree = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  INDEX_SINGLETON
        if (OBJ_NIL == this) {
            this = Index_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!Index_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        Index_setDrive(this, pDrv);
        Index_setExcludes(this, pExcludes);
        Index_setTop(this, pTop);
        Index_setDir(this, pDir);
        Index_setPath(this, OBJ_NIL);
        if (this->pTree) {
            pTree = NodeTree_New();
            Index_setTree(this, pTree);
            obj_Release(pTree);
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
        ASTR_DATA      *pDesc = Index_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Index_ToDebugString (
        INDEX_DATA      *this,
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
        if (!Index_Validate(this)) {
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
                    Index_getSize(this),
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
    bool            Index_Validate (
        INDEX_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_INDEX))
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


        if (!(obj_getSize(this) >= sizeof(INDEX_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


