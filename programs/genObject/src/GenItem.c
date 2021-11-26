// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   GenItem.c
 *  Generated 11/21/2021 11:15:18
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
#include        <GenItem_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
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
     * "genitem_types.txt"
     * If you want to change this enum, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // This table is in enum order and provides
    // the index + 1 into the GenItem_type_entries
    // table. 0 means no enum entry.
    const
    uint16_t    GenItem_type_index[3] = {
        2, 1, 3,
    };


    const
    uint32_t    cGenItem_type_index = 3;




    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } GenItem_type_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    const
    GenItem_type_entry    GenItem_type_entries[] = {
        {"GENITEM_TYPE_ENUM", "", "ENUM", 1},
        {"GENITEM_TYPE_OBJECT", "", "OBJECT", 0},
        {"GENITEM_TYPE_PROPERTY", "", "PROPERTY", 2},
    };
    uint32_t    cGenItem_type_entries = 3;




 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/

    /* The following routine was generated from:
     * "genitem_types.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum value, return its character format.
    const
    char *            GenItem_typeToEnum (
        uint32_t        value
    )
    {
        if (value >= cGenItem_type_index) {
            return "<<<Unknown Enum Value>>>";
        }
        if (GenItem_type_index[value]) {
            return GenItem_type_entries[GenItem_type_index[value] - 1].pEnum;
        } else {
            return "<<<Unknown Enum Value>>>";
        }
    }

    // Given an enum value, return its name.
    const
    char *            GenItem_typeToName (
        uint32_t        value
    )
    {
        if (value >= cGenItem_type_index) {
            return NULL;
        }
        if (GenItem_type_index[value]) {
            return GenItem_type_entries[GenItem_type_index[value] - 1].pName;
        } else {
            return NULL;
        }
    }



    /* The following routine was generated from:
     * "genitem_types.txt"
     * If you want to change it, you
     * should alter the above file and
     * regenerate using genEnum!
     */

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    uint32_t        GenItem_EnumTotype (
        char            *pDesc
    )
    {
        int            iRc;
        uint32_t        iMax = cGenItem_type_entries;
        uint32_t        i    = 0;
        uint32_t        high = 0;
        uint32_t        low  = 0;
        uint32_t        mid  = 0;

        if (iMax > 10) {
            for (i=0; i<iMax; i++) {
                iRc = strcmp(pDesc, GenItem_type_entries[i].pEnum);
                if (0 == iRc) {
                    return GenItem_type_entries[i].value + 1;
                }
                if (iRc < 0) {
                    break;
                }
            }
        } else {
            high = iMax - 1;
            while (low < high) {
                mid = (high + low) / 2;
                i = mid + 1;
                iRc = strcmp(pDesc, GenItem_type_entries[i].pEnum);
                if (iRc < 0) {
                    high = mid;
                } else if (iRc == 0) {
                    return GenItem_type_entries[i].value + 1;
                } else {
                    low = mid + 1;
                }
            }
            if( high == low ) {
                i = low;
                iRc = strcmp(pDesc, GenItem_type_entries[i].pEnum);
                if (0 == iRc) {
                    return GenItem_type_entries[i].value + 1;
                }
            }
        }
        return 0;
    }



    
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    const
    char *          GenItem_DictLookup (
        GENITEM_DATA    *this,
        const
        char            *pNameA
    )
    {
        ASTR_DATA       *pData = OBJ_NIL;
        const
        char            *pDataA = NULL;

        if (this->pDict) {
            pData = Dict_FindA(this->pDict, pNameA);
            if (pData)
                pDataA = AStr_getData(pData);
        }

        return pDataA;
    }



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GENITEM_DATA *     GenItem_Alloc (
        void
    )
    {
        GENITEM_DATA       *this;
        uint32_t        cbSize = sizeof(GENITEM_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GENITEM_DATA *     GenItem_New (
        void
    )
    {
        GENITEM_DATA       *this;
        
        this = GenItem_Alloc( );
        if (this) {
            this = GenItem_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      D i c t i o n a r y
    //---------------------------------------------------------------

    DICT_DATA *     GenItem_getDict (
        GENITEM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pDict;
    }


    bool            GenItem_setDict (
        GENITEM_DATA    *this,
        DICT_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pDict) {
            obj_Release(this->pDict);
        }
        this->pDict = pValue;
        this->pDictObj = pValue;
        this->pDictLookupA = (void *)Dict_GetA;


        return true;
    }



    //---------------------------------------------------------------
    //                          M o d e l
    //---------------------------------------------------------------

    ASTR_DATA *     GenItem_getFile (
        GENITEM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pFile;
    }


    bool            GenItem_setFile (
        GENITEM_DATA    *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pFile) {
            obj_Release(this->pFile);
        }
        this->pFile = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          L o g
    //---------------------------------------------------------------

    bool            GenItem_setLog (
        GENITEM_DATA    *this,
        OBJ_ID          pObj
    )
    {
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->pLog = pObj;

        return true;
    }



    //---------------------------------------------------------------
    //                          M o d e l
    //---------------------------------------------------------------

    PATH_DATA *     GenItem_getModel (
        GENITEM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pModel;
    }


    bool            GenItem_setModel (
        GENITEM_DATA    *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pModel) {
            obj_Release(this->pModel);
        }
        this->pModel = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                        O u t p u t
    //---------------------------------------------------------------

    PATH_DATA *     GenItem_getOutput (
        GENITEM_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        return this->pOutput;
    }


    bool            GenItem_setOutput (
        GENITEM_DATA    *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pOutput) {
            obj_Release(this->pOutput);
        }
        this->pOutput = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        GenItem_getPriority (
        GENITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            GenItem_setPriority (
        GENITEM_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
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
    
    uint32_t        GenItem_getSize (
        GENITEM_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  GenItem_getSuperVtbl (
        GENITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  
    GENITEM_DATA *  GenItem_getSuper (
        GENITEM_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (GENITEM_DATA *)this;
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
        ERESULT eRc = GenItem_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another GENITEM object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         GenItem_Assign (
        GENITEM_DATA       *this,
        GENITEM_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!GenItem_Validate(pOther)) {
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
    int             GenItem_Compare (
        GENITEM_DATA     *this,
        GENITEM_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  GENITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = GenItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!GenItem_Validate(pOther)) {
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
        GenItem      *pCopy = GenItem_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a GENITEM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GENITEM_DATA *     GenItem_Copy (
        GENITEM_DATA       *this
    )
    {
        GENITEM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef GENITEM_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = GenItem_New( );
        if (pOther) {
            eRc = GenItem_Assign(this, pOther);
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

    void            GenItem_Dealloc (
        OBJ_ID          objId
    )
    {
        GENITEM_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GENITEM_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        GenItem_setDict(this, OBJ_NIL);
        GenItem_setFile(this, OBJ_NIL);
        GenItem_setModel(this, OBJ_NIL);
        GenItem_setOutput(this, OBJ_NIL);

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
        GenItem      *pDeepCopy = GenItem_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a GENITEM object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    GENITEM_DATA *     GenItem_DeepCopy (
        GENITEM_DATA       *this
    )
    {
        GENITEM_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = GenItem_New( );
        if (pOther) {
            eRc = GenItem_Assign(this, pOther);
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
    ERESULT         GenItem_Disable (
        GENITEM_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  GENITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = GenItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
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
    ERESULT         GenItem_Enable (
        GENITEM_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  GENITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = GenItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
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
    //                 E x p a n d  V a r i a b l e s
    //---------------------------------------------------------------

    /*! Expand the ${} variables in a string until there are no more. When
        a variable is found, look it up in the dictionary and then the
        program environment.  If it exists in one of those, replace the
        ${} variable with the text found. If it is not found, simply
        remove the ${} variable and note it to the log.
     */
    ERESULT         GenItem_ExpandVars(
        GENITEM_DATA    *this,
        ASTR_DATA       *pInOut
    )
    {
        ERESULT         eRc;
        uint32_t        i = 0;
        uint32_t        j;
        uint32_t        len;
        int32_t         chr;
        bool            fMore = true;
        //PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pName = OBJ_NIL;
        const
        char            *pEnvVar = NULL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !GenItem_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (0 == AStr_getLength(pInOut)) {
            return ERESULT_SUCCESS;
        }

        // Expand Environment variables.
        while (fMore) {
            fMore = false;
            eRc = AStr_CharFindNextW32(pInOut, &i, '$');
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            else {
                chr = AStr_CharGetW32(pInOut, i+1);
                if (chr == '{') {
                    j = i + 2;
                    eRc = AStr_CharFindNextW32(pInOut, &j, '}');
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_PARSE_ERROR;
                    }
                    len = j - (i + 2);
                    eRc = AStr_Mid(pInOut, i+2, len, &pName);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }

                    // See if we can find the variable in the dictionary
                    // or program environment.
                    pEnvVar = NULL;
                    if (this->pDictLookupA) {
                        pEnvVar = this->pDictLookupA(this->pDictObj, AStr_getData(pName));
                    }
                    if (NULL == pEnvVar) {
                        if (this->pLog) {
                            ((LOG_INTERFACE *)(this->pLog))->pVtbl->pLogWarn(
                                    this->pLog,
                                    0,
                                    "Could not find variable, %s, skipped!",
                                    AStr_getData(pName)
                            );
                        }
                    }
                    obj_Release(pName);
                    pName = OBJ_NIL;

                    // Remove the ${} variable.
                    eRc = AStr_Remove(pInOut, i, len+3);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }

                    // Insert the variable's text if it exists.
                    if (pEnvVar) {
                        eRc = AStr_InsertA(pInOut, i, pEnvVar);
                        if (ERESULT_FAILED(eRc)) {
                            return ERESULT_OUT_OF_MEMORY;
                        }
                    }
                    pEnvVar = NULL;
                    fMore = true;
                }
                else {
                    ++i;
                    fMore = true;
                    continue;
                }
            }
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       G e n e r a t e
    //---------------------------------------------------------------

    /*!
     Generate various phases for this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         GenItem_Generate (
        GENITEM_DATA       *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  GENITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = GenItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        if (this->pGen) {
            eRc = this->pGen(this->pGen, "a");
            if (ERESULT_FAILED(eRc)) {
                goto exit00;
            }
            eRc = this->pGen(this->pGen, "b");
            if (ERESULT_FAILED(eRc)) {
                goto exit00;
            }
            eRc = this->pGen(this->pGen, "c");
            if (ERESULT_FAILED(eRc)) {
                goto exit00;
            }
            eRc = this->pGen(this->pGen, "d");
            if (ERESULT_FAILED(eRc)) {
                goto exit00;
            }
            eRc = this->pGen(this->pGen, "c_props");
            if (ERESULT_FAILED(eRc)) {
                goto exit00;
            }
        }

        // Return to caller.
    exit00:
        return eRc;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GENITEM_DATA *   GenItem_Init (
        GENITEM_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GENITEM_DATA);
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

        //this = (OBJ_ID)GenItem_Init((GENITEM_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of GenItem_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_GENITEM);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&GenItem_Vtbl);
#ifdef  GENITEM_JSON_SUPPORT
        JsonIn_RegisterClass(GenItem_Class());
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
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "GenItem::sizeof(GENITEM_DATA) = %lu\n", 
                sizeof(GENITEM_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(GENITEM_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         GenItem_IsEnabled (
        GENITEM_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  GENITEM_SINGLETON
        if (OBJ_NIL == this) {
            this = GenItem_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
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
    //                     T e x t  P r e p r o c
    //---------------------------------------------------------------

    /*!
     The text in the input is part of the argument to an %ifdef or %ifndef.
     Evaluate the text as a boolean expression.  Return true or false.
     @param     this    object pointer
     @return    exprssion evaluates to a true (1+) or false (0).
     */
    int             GenItem_PreProcBoolEval (
        GENITEM_DATA    *this,
        char            *z,
        int             lineno
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        int             neg = 0;
        int             res = 0;
        int             okTerm = 1;
        int             i;
        const
        char            *pStrDef = NULL;
        char            nameA[DICT_NAME_MAXLEN+1];

        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -1;
        }
#endif

        for (i=0; z[i]!=0; i++) {
            if (ascii_isWhiteSpaceA(z[i]))
                continue;
            // !term
            if (z[i] == '!') {
                if (!okTerm)
                    goto syntax_error;
                neg = !neg;
                continue;
            }
            // term || term
            if ((z[i] == '|') && (z[i+1] == '|')) {
                if (okTerm)
                    goto syntax_error;
                if (res)
                    return 1;
                i++;
                okTerm = 1;
                continue;
            }
            // term && term
            if ((z[i] == '&') && (z[i+1] == '&')) {
                if (okTerm)
                    goto syntax_error;
                if (!res)
                    return 0;
                i++;
                okTerm = 1;
                continue;
            }
            // ( terms )
            if( z[i]=='(' ) {
                int         k;
                int         n = 1;

                if (!okTerm) {
                    goto syntax_error;
                }

                for (k=i+1; z[k]; k++) {
                    if (z[k] == ')') {
                        n--;
                        if (n == 0) {
                            z[k] = 0;
                            res = GenItem_PreProcBoolEval(this, &z[i+1], -1);
                            z[k] = ')';
                            if (res < 0) {
                                i = i-res;
                                goto syntax_error;
                            }
                            i = k;
                            break;
                        }
                    } else if (z[k] == '(') {
                        n++;
                    } else if (z[k] == 0) {
                        i = k;
                        goto syntax_error;
                    }
                }
                if (neg) {
                    res = !res;
                    neg = 0;
                }
                okTerm = 0;
                continue;
            }

            // term := (bool)found define_name
            if (ascii_isAlphaA(z[i])) {
                int         k;
                int         n;

                if (!okTerm)
                    goto syntax_error;
                for (k=i+1; ascii_isAlphanumericA(z[k]) || z[k]=='_'; k++) {
                }
                n = k - i;
                if (n > DICT_NAME_MAXLEN)
                    n = DICT_NAME_MAXLEN;
                strncpy(nameA, &z[i], n);
                nameA[n] = '\0';

                // Search the defines to see if the one that we scanned exists.
                // Set res=1 if found
                res = 0;
                if (this->pDictLookupA) {
                    pStrDef = this->pDictLookupA(this->pDictObj, nameA);
                } else {
                    fprintf(stderr,
                            "FATAL - Missing Dictionary Lookup for %s!\n",
                            nameA
                    );
                    exit(1);
                }
                if (pStrDef) {
                    res = 1;
                    pStrDef = NULL;
                }
                i = k-1;
                if (neg) {
                    res = !res;
                    neg = 0;
                }
                okTerm = 0;
                continue;
            }
            goto syntax_error;
        }

        // Return to caller.
        return res;
    syntax_error:
        if (lineno > 0) {
            fprintf(stderr, "%%if syntax error on line %d.\n", lineno);
            fprintf(stderr, "  %.*s <-- syntax error here\n", i+1, z);
            exit(1);
        } else {
            return -(i+1);
        }

    }


    /*!
     Run the preprocessor over the input file text.  The global variables
     azDefine[0] through azDefine[nDefine-1] contains the names of all defined
     macros.  This routine looks for "%ifdef" and "%ifndef" and "%endif" and
     comments them out.  Text in between is also commented out as appropriate.
     The initial version of this preprocessor was taken from "lemon" by
     by Richard Hipp which is part of SQLite, a great SQL tool. SQLite and
     this code was placed in the Public Domain by its author.
     @param     this    object pointer
     @param     prefixA preprocess statement identifier
     @param     z       a NUL-terminated character string containing all lines
                        of text that need to be scanned. On output, the lines
                        that need to be removed will be replaced with blank
                        lines including the %ifdef, %if, %ifndef, %else and
                        %endif lines.
     @return    If succesful, an AStr object which has the lines not needed
                removed.
    */
    ASTR_DATA *     GenItem_Preproc (
        GENITEM_DATA    *this,
        const
        char            prefixA,
        char            *z
    )
    {
        int             i, j, k;
        int             exclude = 0;        // Exclude source until %else or %endif
        int             start = 0;
        int             lineno = 1;
        int             start_lineno = 1;
        ASTR_DATA       *pStr = OBJ_NIL;
        struct remove_list_s {
            int         start;
            int         len;
        }               removeList[100];
        const
        int             maxRemoveList = 100;
        int             cRemoveList = 0;

        pStr = AStr_NewA(z);
        if (OBJ_NIL == pStr) {
            fprintf(stderr,
                    "FATAL - could not allocate AStr object,"
                    " out of memory!\n"
            );
            exit(1);
        }
        // Scan line 1 char at a time until NUL-terminator.
        start = 0;
        for (i=0; z[i]; i++) {
            if (z[i] == '\n')
                lineno++;
            if ((z[i] != '%') || ((i > 0) && (z[i-1] != '\n'))) {
                continue;
            }
            if (prefixA == z[i]) {
                i++;
                if ((strncmp(&z[i],"endif",5) == 0) && ascii_isWhiteSpaceA(z[i+5])) {
                    if (exclude) {
                        exclude--;
                        if (exclude == 0) {
                            // Push (start, i-1)
                            if (cRemoveList < maxRemoveList) {
                                removeList[cRemoveList].start = start;
                                removeList[cRemoveList].len = i-start;
                                cRemoveList++;
                            } else {
                                fprintf(stderr,
                                        "FATAL - Too many code deletions!\n"
                                );
                                exit(1);
                            }
                        }
                    }
                    // Remove remainder of line.
                    for (j=i; (z[j] && (z[j] != '\n')); j++)
                        ;
                    // Push (i, j-1)
                    if (cRemoveList < maxRemoveList) {
                        removeList[cRemoveList].start = i;
                        removeList[cRemoveList].len = j - i + 1;
                        cRemoveList++;
                    } else {
                        fprintf(stderr,
                                "FATAL - Too many code deletions!\n"
                        );
                        exit(1);
                    }
                } else if ((strncmp(&z[i],"else",4) == 0)
                            && ascii_isWhiteSpaceA(z[i+4])
                           ) {
                    if (exclude == 1) {
                        exclude = 0;
                        // Push (start, i-1)
                        if (cRemoveList < maxRemoveList) {
                            removeList[cRemoveList].start = start;
                            removeList[cRemoveList].len = i-start;
                            cRemoveList++;
                        } else {
                            fprintf(stderr,
                                    "FATAL - Too many code deletions!\n"
                            );
                            exit(1);
                        }
                    } else if (exclude == 0) {
                        exclude = 1;
                        start = i;
                        start_lineno = lineno;
                    }
                    // Remove remainder of line.
                    for (j=i; z[j] && (z[j] != '\n'); j++)
                        ;
                    // Push (i, j-1)
                    if (cRemoveList < maxRemoveList) {
                        removeList[cRemoveList].start = i;
                        removeList[cRemoveList].len = j - i + 1;
                        cRemoveList++;
                    } else {
                        fprintf(stderr,
                                "FATAL - Too many code deletions!\n"
                        );
                        exit(1);
                    }
                } else if ((strncmp(&z[i],"ifdef ",6) == 0)
                           || (strncmp(&z[i],"if ",3) == 0)
                           || (strncmp(&z[i],"ifndef ",7) == 0)) {
                    if (exclude) {
                        exclude++;
                    } else {
                        int         isNot;
                        int         iBool;
                        // Skip leading white-space.
                        for (j=i; z[j] && !ascii_isSpaceA(z[j]); j++) {
                        }
                        iBool = j;
                        isNot = (j == (i + 7));
                        // Skip to EOL.
                        while (z[j] && (z[j] != '\n')) {
                            j++;
                        }
                        k = z[j];
                        z[j] = '\0';
                        exclude = GenItem_PreProcBoolEval(this, &z[iBool], lineno);
                        z[j] = k;
                        if (!isNot)
                            exclude = !exclude;
                        if (exclude) {
                            start = i;
                            start_lineno = lineno;
                        }
                    }
                    // Remove remainder of line.
                    for (j=i; z[j] && z[j]!='\n'; j++)
                        ;
                    // Push (i, j-1)
                    if (cRemoveList < maxRemoveList) {
                        removeList[cRemoveList].start = i;
                        removeList[cRemoveList].len = j - i + 1;
                        cRemoveList++;
                    } else {
                        fprintf(stderr,
                                "FATAL - Too many code deletions!\n"
                        );
                        exit(1);
                    }
                }
            }
        }
        if (exclude) {
            fprintf(stderr,"FATAL - unterminated %%ifdef starting on line %d\n", start_lineno);
            exit(1);
        }

        // Remove skipped text.
        for (i=cRemoveList; i; i--) {
            AStr_Remove(pStr, removeList[i-1].start, removeList[i-1].len);
        }

        return pStr;
    }



    //---------------------------------------------------------------
    //                P r o c e s s  F i l e
    //---------------------------------------------------------------

    ERESULT         GenItem_ProcessFile (
        GENITEM_DATA    *this,
        bool            fVerbose
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        cnt = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif


        // Read in the file.
        if (OBJ_NIL == this->pModel) {
            fprintf(stderr, "FATAL - Missing Model Path!");
            exit(4);
        }
        this->pFile = AStr_NewFromUtf8File(this->pModel);
        if (OBJ_NIL == this->pFile) {
            fprintf(
                    stderr,
                    "FATAL - Could not read file, %s!",
                    Path_getData(this->pModel)
            );
            exit(4);
        }

        iLog_Info(
                this->pLog,
                "Processing %s...",
                Path_getData(this->pModel)
        );
        cnt = 0;
        //FIXME: eRc = Gen_ExpandData(this, pInput, pOutput, &cnt);
        iLog_Info(this->pLog, "%d lines", cnt);
        iLog_Info(
                this->pLog,
                "Completed %s Processing.",
                Path_getData(this->pModel)
        );

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
        void        *pMethod = GenItem_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "GenItem", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          GenItem_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GENITEM_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!GenItem_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(GENITEM_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)GenItem_Class();
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
                            return GenItem_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return GenItem_Enable;
                        }
                        break;

                    case 'P':
#ifdef  GENITEM_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return GenItem_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return GenItem_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return GenItem_ToDebugString;
                        }
#ifdef  GENITEM_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return GenItem_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return GenItem_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == GenItem_ToDebugString)
                    return "ToDebugString";
#ifdef  GENITEM_JSON_SUPPORT
                if (pData == GenItem_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      S e t  D e f a u l t s
    //---------------------------------------------------------------

    /*! Set default values needed to process the model.
     @return    If successful, then ERESULT_SUCESS. Otherwise, an ERESULT_*
                error. Note: this is ignored in Appl.
     */
    ERESULT         GenItem_SetDefaults (
        GENITEM_DATA    *this
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr = OBJ_NIL;
        long            clock;
        struct tm       *now;
        char            str[32];

        // Do initialization.
#ifdef NDEBUG
#else
        if( !GenItem_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // Set up DATE and TIME.
        (void) time (&clock);
        now = localtime (&clock);
        snprintf(
                       str,
                       sizeof(str),
                       "%2.2d/%2.2d/%2.2d",
                       now->tm_mon+1,
                       now->tm_mday,
                       now->tm_year+1900
        );
        pStr = AStr_NewA(str);
        if (pStr) {
            eRc = Dict_AddAStr(this->pDict, GEN_DATE, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        snprintf(
                 str,
                 sizeof(str),
                 "%2.2d:%2.2d:%2.2d",
                 now->tm_hour,
                 now->tm_min,
                 now->tm_sec
        );
        pStr = AStr_NewA(str);
        if (pStr) {
            eRc = Dict_AddAStr(this->pDict, GEN_TIME, pStr);
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        // Return to caller.
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = GenItem_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     GenItem_ToDebugString (
        GENITEM_DATA      *this,
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
        if (!GenItem_Validate(this)) {
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
                    GenItem_getSize(this),
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
    bool            GenItem_Validate (
        GENITEM_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_GENITEM))
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


        if (!(obj_getSize(this) >= sizeof(GENITEM_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    
    
#ifdef  __cplusplus
}
#endif


