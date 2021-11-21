// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   ObjGen.c
 *  Generated 11/19/2021 06:00:58
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
#include        <ObjGen_internal.h>
#include        <ascii.h>
#include        <JsonIn.h>
#include        <trace.h>
#include        <utf8.h>






#ifdef  __cplusplus
extern "C" {
#endif

    /*
     This table relies on the fact that we deal with numbers
     directly not indirectly (ie through pointers).  Therefore,
     we can generate numbers to be passed through methods w/o
     worrying about pointers.
     */
    typedef struct Prop_s {
        const
        char        *pTypeA;
        const
        char        *pValueA;
        const
        char        *pRetA;
    } PROP;

    // Table is sorted by Type.
    PROP        Props[] = {
        { "bool", "fValue", "bRet"},
        { "int", "value", "iRet"},
        { "int128_t", "value", "iRet"},
        { "int16_t", "value", "iRet"},
        { "int32_t", "value", "iRet"},
        { "int64_t", "value", "iRet"},
        { "int8_t", "value", "iRet"},
        { "uint128_t", "value", "iRet"},
        { "uint16_t", "value", "iRet"},
        { "uint32_t", "value", "iRet"},
        { "uint64_t", "value", "iRet"},
        { "uint8_t", "value", "iRet"},
    };
    const
    int         cProps = sizeof(Props)/sizeof(PROP);

    
    //****************************************************************
    // * * * * * * * * * * *    Internal Data    * * * * * * * * * * *
    //****************************************************************

    // Place constant internal data here. Generally, it should be
    // 'static' so that it does not interfere with other objects.


 
    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/

    // Given an enum description, return its value + 1 or
    // 0 for not found.
    const
    PROP *          ObjGen_TypeToProp(
        char            *pTypeA
    )
    {
        int            iRc;
        uint32_t        iMax = cProps;
        uint32_t        i    = 0;
        uint32_t        high = 0;
        uint32_t        low  = 0;
        uint32_t        mid  = 0;

        if (iMax > 10) {
            for (i=0; i<iMax; i++) {
                iRc = strcmp(pTypeA, Props[i].pTypeA);
                if (0 == iRc) {
                    return &Props[i];
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
                iRc = strcmp(pTypeA, Props[i].pTypeA);
                if (iRc < 0) {
                    high = mid;
                } else if (iRc == 0) {
                    return &Props[i];
                } else {
                    low = mid + 1;
                }
            }
            if( high == low ) {
                i = low;
                iRc = strcmp(pTypeA, Props[i].pTypeA);
                if (0 == iRc) {
                    return &Props[i];
                }
            }
        }
        return NULL;
    }





    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            ObjGen_task_body (
        void            *pData
    )
    {
        //OBJGEN_DATA  *this = pData;
        
    }
#endif



    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJGEN_DATA *     ObjGen_Alloc (
        void
    )
    {
        OBJGEN_DATA       *this;
        uint32_t        cbSize = sizeof(OBJGEN_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJGEN_DATA *     ObjGen_New (
        void
    )
    {
        OBJGEN_DATA       *this;
        
        this = ObjGen_Alloc( );
        if (this) {
            this = ObjGen_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        ObjGen_getPriority (
        OBJGEN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        //return this->priority;
        return 0;
    }


    bool            ObjGen_setPriority (
        OBJGEN_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
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
    
    uint32_t        ObjGen_getSize (
        OBJGEN_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * ObjGen_getStr (
        OBJGEN_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pStr;
    }
    
    
    bool        ObjGen_setStr (
        OBJGEN_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
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
    
    OBJ_IUNKNOWN *  ObjGen_getSuperVtbl (
        OBJGEN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  
    OBJGEN_DATA *  ObjGen_getSuper (
        OBJGEN_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return (OBJGEN_DATA *)this;
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
        ERESULT eRc = ObjGen_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another OBJGEN object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         ObjGen_Assign (
        OBJGEN_DATA       *this,
        OBJGEN_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!ObjGen_Validate(pOther)) {
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
    int             ObjGen_Compare (
        OBJGEN_DATA     *this,
        OBJGEN_DATA     *pOther
    )
    {
        int             iRc = -1;
#ifdef  xyzzy        
        const
        char            *pStr1;
        const
        char            *pStr2;
#endif
        
#ifdef  OBJGEN_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjGen_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!ObjGen_Validate(pOther)) {
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
        ObjGen      *pCopy = ObjGen_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJGEN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJGEN_DATA *     ObjGen_Copy (
        OBJGEN_DATA       *this
    )
    {
        OBJGEN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
#ifdef OBJGEN_IS_IMMUTABLE
        obj_Retain(this);
        pOther = this;
#else
        pOther = ObjGen_New( );
        if (pOther) {
            eRc = ObjGen_Assign(this, pOther);
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

    void            ObjGen_Dealloc (
        OBJ_ID          objId
    )
    {
        OBJGEN_DATA   *this = objId;
        //ERESULT         eRc;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJGEN_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        ObjGen_setStr(this, OBJ_NIL);

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
        ObjGen      *pDeepCopy = ObjGen_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a OBJGEN object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    OBJGEN_DATA *     ObjGen_DeepCopy (
        OBJGEN_DATA       *this
    )
    {
        OBJGEN_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = ObjGen_New( );
        if (pOther) {
            eRc = ObjGen_Assign(this, pOther);
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
    ERESULT         ObjGen_Disable (
        OBJGEN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OBJGEN_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjGen_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
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
    ERESULT         ObjGen_Enable (
        OBJGEN_DATA     *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OBJGEN_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjGen_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
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
    //                      H e a d e r  L i n e
    //---------------------------------------------------------------

    ASTR_DATA *     ObjGen_HeaderLine(
        OBJGEN_DATA     *this,
        bool            fAddOffset,
        W32CHR_T        chr
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        int32_t         iRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        pStr = AStr_NewFromPrint("%s//", fAddOffset ? "\t" : "");
        if (pStr) {
            iRc = OBJGEN_LINE_LENGTH - AStr_getLength(pStr);
            if (fAddOffset)
                iRc -= 4;
            if (iRc > 0) {
                AStr_AppendCharRepeatW32(pStr, iRc, chr);
            }
            AStr_AppendA(pStr, "\n");
        }

        return pStr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJGEN_DATA *   ObjGen_Init (
        OBJGEN_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJGEN_DATA);
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

        //this = (OBJ_ID)ObjGen_Init((OBJGEN_DATA *)this);   // Needed for Inheritance
        // If you use inheritance, remember to change the obj_ClassObj reference 
        // in the OBJ_INFO at the end of ObjGen_object.c
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJGEN);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&ObjGen_Vtbl);
#ifdef  OBJGEN_JSON_SUPPORT
        JsonIn_RegisterClass(ObjGen_Class());
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
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#if defined(__APPLE__) && defined(XYZZY)
//#if defined(__APPLE__)
        fprintf(
                stderr, 
                "ObjGen::sizeof(OBJGEN_DATA) = %lu\n", 
                sizeof(OBJGEN_DATA)
        );
#endif
        BREAK_NOT_BOUNDARY4(sizeof(OBJGEN_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                      I s  E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         ObjGen_IsEnabled (
        OBJGEN_DATA       *this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OBJGEN_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjGen_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
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
    //                      P r o p e r t y
    //---------------------------------------------------------------

    ASTR_DATA *     ObjGen_Property(
        OBJGEN_DATA     *this,
        uint32_t        offset,
        const
        char            *pTypeA,
        const
        char            *pNameA,
        const
        char            *pPrefixA,
        uint8_t         fOwned
    )
    {
        ASTR_DATA       *pStr = OBJ_NIL;
        ASTR_DATA       *pOffset = OBJ_NIL;
        int32_t         i;
        ASTR_DATA       *pClassName = OBJ_NIL;
        ASTR_DATA       *pClassNameUC = OBJ_NIL;
        ASTR_DATA       *pMethodName = OBJ_NIL;
        ASTR_DATA       *pMethodDesc = OBJ_NIL;
        bool            fObject = false;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !ObjGen_Validate(this) ) {
            DEBUG_BREAK();
            // return ERESULT_INVALID_OBJECT;
            return pStr;
        }
#endif
        pOffset = AStr_New();
        BREAK_NULL(pOffset);
        AStr_AppendCharRepeatA(pOffset, offset, ' ');

#ifdef XYZAZY
        pClassName = genObj_DictFindA(this, GENOBJ_CLASSNAME);
        if (OBJ_NIL == pClassName) {
            obj_Release(pOffset);
            // return ERESULT_KEY_NOT_FOUND;
            return pStr;
        }
        pClassNameUC = genObj_DictFindA(this, GENOBJ_CLASSNAME_UC);
        if (OBJ_NIL == pClassNameUC) {
            obj_Release(pOffset);
            // return ERESULT_KEY_NOT_FOUND;
            return pStr;
        }
#endif

        if (0 == strcmp("eRc", pNameA)) {
            pMethodName = AStr_NewA("LastError");
            BREAK_NULL(pMethodName);
            pMethodDesc = ObjGen_SpacedComment(this, "LastError");
            if (OBJ_NIL == pMethodDesc) {
                obj_Release(pOffset);
                // return ERESULT_KEY_NOT_FOUND;
                return pStr;
            }
        }
        else {
            if ((*pNameA == 'p') && (ascii_isUpperA(*(pNameA + 1)))) {
                pMethodName = AStr_NewA(pNameA + 1);
                BREAK_NULL(pMethodName);
            }
            else {
                pMethodName = AStr_NewA(pNameA);
                BREAK_NULL(pMethodName);
            }
            pMethodDesc = ObjGen_SpacedComment(this, AStr_getData(pMethodName));
            if (OBJ_NIL == pMethodDesc) {
                obj_Release(pOffset);
                return ERESULT_KEY_NOT_FOUND;
            }
            AStr_CharPutW32(pMethodName, 1, ascii_toUpperA(AStr_CharGetW32(pMethodName,1)));
        }
        i = 40 - AStr_getLength(pMethodDesc);
        if (i > 1) {
            AStr_CharInsertW32Repeat(pMethodDesc, 1, (i >> 1), ' ');
        }
        {
            ASTR_DATA           *pWrk = AStr_NewA(pTypeA);
            if (pWrk) {
                if (0 == AStr_CompareA(pWrk, "OBJ_ID")) {
                    fObject = true;
                }
                else if (AStr_CompareRightA(pWrk, "_DATA *") == 0) {
                    fObject = true;
                }
            }
            obj_Release(pWrk);
        }


        if (OBJ_NIL == pStr) {
            pStr = AStr_New();
        }
        AStr_AppendPrint(
                         pStr,
                         "%s//---------------------------------------------------------------\n",
                         AStr_getData(pOffset)
                         );
        AStr_AppendPrint(
                         pStr,
                         "%s//\t\t\t%s\n",
                         AStr_getData(pOffset),
                         AStr_getData(pMethodDesc)
                         );
        AStr_AppendPrint(
                         pStr,
                         "%s//---------------------------------------------------------------\n",
                         AStr_getData(pOffset)
                         );
        AStr_AppendPrint(pStr, "\n");
        AStr_AppendPrint(
                         pStr,
                         "%s%s\t\t\t%s_get%s(\n",
                         AStr_getData(pOffset),
                         pTypeA,
                         AStr_getData(pClassName),
                         AStr_getData(pMethodName)
                         );
        AStr_AppendPrint(
                         pStr,
                         "%s\t%s_DATA\t*this\n",
                         AStr_getData(pOffset),
                         AStr_getData(pClassNameUC)
                         );
        AStr_AppendPrint(pStr, "%s)\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s{\n", AStr_getData(pOffset));
        if (0 == strcmp("int", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint8_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint16_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint32_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint64_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint8_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint16_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint32_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint64_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (fObject) {
            AStr_AppendPrint(pStr, "%s\tOBJ_ID\t\t\tpObj = OBJ_NIL;\n", AStr_getData(pOffset));
        }
        else {
            AStr_AppendPrint(
                             pStr,
                             "%s\t%s\t\t\t%s = 0;\n",
                             AStr_getData(pOffset),
                             pDataType,
                             pName
            );
        }
        AStr_AppendPrint(pStr, "\n");
        AStr_AppendPrint(pStr, "%s\t// Do initialization.\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s#ifdef NDEBUG\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s#else\n", AStr_getData(pOffset));
        AStr_AppendPrint(
                         pStr,
                         "%s\tif (!%s_Validate(this)) {\n",
                         AStr_getData(pOffset),
                         AStr_getData(pClassName)
                         );
        AStr_AppendPrint(pStr, "%s\t\tDEBUG_BREAK();\n", AStr_getData(pOffset));
        if (fObject) {
            AStr_AppendPrint(pStr, "%s\t\treturn pObj;\n", AStr_getData(pOffset));
        }
        else {
            AStr_AppendPrint(pStr, "%s\t\treturn iRet;\n", AStr_getData(pOffset));
        }
        AStr_AppendPrint(pStr, "\t%s}\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s#endif\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "\n");
        if (fObject) {
            AStr_AppendPrint(
                             pStr,
                             "%s\tpObj = this->%s;\n",
                             AStr_getData(pOffset),
                             pNameA
            );
        }
        else {
            AStr_AppendPrint(
                             pStr,
                             "%s\tiRet = this->%s;\n",
                             AStr_getData(pOffset),
                             pNameA
                             );
        }
        AStr_AppendPrint(pStr, "\n");
        AStr_AppendPrint(pStr, "%s\t// Return to caller.\n", AStr_getData(pOffset));
        if (0 == strcmp("void", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("ERESULT", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\treturn this->eRc;\n", AStr_getData(pOffset));
        }
        else if (fObject) {
            AStr_AppendPrint(pStr, "%s\treturn pObj;\n", AStr_getData(pOffset));
        }
        AStr_AppendPrint(pStr, "%s}\n\n\n", AStr_getData(pOffset));

        AStr_AppendPrint(
                         pStr,
                         "%sbool\t\t\t%s_set%s(\n",
                         AStr_getData(pOffset),
                         AStr_getData(pClassName),
                         AStr_getData(pMethodName)
        );
        AStr_AppendPrint(
                         pStr,
                         "%s\t%s_DATA\t*this,\n",
                         AStr_getData(pOffset),
                         AStr_getData(pClassNameUC)
        );
        if (0 == strcmp("int", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint8_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint16_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint32_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tint64_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint8_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint16_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint32_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pTypeA)) {
            AStr_AppendPrint(pStr, "%s\tuint64_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (fObject) {
            AStr_AppendPrint(
                             pStr,
                             "%s\t%s\t\t\tpValue\n",
                             AStr_getData(pOffset),
                             pTypeA
            );
        }
        else {
            AStr_AppendPrint(
                             pStr,
                             "%s\t%s\t\t\tvalue\n",
                             AStr_getData(pOffset),
                             pTypeA
                             );
        }
        AStr_AppendPrint(pStr, "%s)\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s{\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "\n");
        AStr_AppendPrint(pStr, "%s\t// Do initialization.\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s#ifdef NDEBUG\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s#else\n", AStr_getData(pOffset));
        AStr_AppendPrint(
                         pStr,
                         "%s\tif (!%s_Validate(this)) {\n",
                         AStr_getData(pOffset),
                         AStr_getData(pClassName)
                         );
        AStr_AppendPrint(pStr, "%s\t\tDEBUG_BREAK();\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s\t\treturn false;\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "\t%s}\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s#endif\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "\n");
        if (fObject) {
            if (fOwned)
                ;
            else {
                AStr_AppendPrint(pStr, "%s#ifdef XYZZY_NOT_OWNED\n", AStr_getData(pOffset));
            }
            AStr_AppendPrint(pStr,
                             "%s\tobj_Retain(pValue);\n",
                             AStr_getData(pOffset)
            );
            AStr_AppendPrint(pStr,
                             "%s\tif (this->%s) {\n",
                             AStr_getData(pOffset),
                             pNameA
                             );
            AStr_AppendPrint(pStr,
                             "%s\t\tobj_Release(this->%s);\n",
                             AStr_getData(pOffset),
                             pNameA
                             );
            if (fOwned)
                ;
            else {
                AStr_AppendPrint(pStr, "%s#endif\n", AStr_getData(pOffset));
            }
            AStr_AppendPrint(pStr,
                             "%s\t\t//this->%s = OBJ_NIL;\n",
                             AStr_getData(pOffset),
                             pNameA
                             );
            AStr_AppendPrint(pStr, "\t%s}\n", AStr_getData(pOffset));
            AStr_AppendPrint(pStr,
                             "%s\tthis->%s = pValue;\n",
                             AStr_getData(pOffset),
                             pNameA
                             );
        }
        else {
            AStr_AppendPrint(pStr,
                             "%s\tthis->%s = value;\n",
                             AStr_getData(pOffset),
                             pNameA
            );
        }
        AStr_AppendPrint(pStr, "\n");
        AStr_AppendPrint(pStr, "%s\t// Return to caller.\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s\treturn true;\n", AStr_getData(pOffset));
        AStr_AppendPrint(pStr, "%s}\n\n\n\n", AStr_getData(pOffset));

        obj_Release(pOffset);
        pOffset = OBJ_NIL;
        obj_Release(pMethodDesc);
        pMethodDesc = OBJ_NIL;
        obj_Release(pMethodName);
        pMethodName = OBJ_NIL;

        // Return to caller.
        return pStr;
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
        void        *pMethod = ObjGen_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "ObjGen", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          ObjGen_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJGEN_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
                return (void *)sizeof(OBJGEN_DATA);
                break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)ObjGen_Class();
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
                            return ObjGen_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return ObjGen_Enable;
                        }
                        break;

                    case 'P':
#ifdef  OBJGEN_JSON_SUPPORT
                        if (str_Compare("ParseJsonFields", (char *)pStr) == 0) {
                            return ObjGen_ParseJsonFields;
                        }
                        if (str_Compare("ParseJsonObject", (char *)pStr) == 0) {
                            return ObjGen_ParseJsonObject;
                        }
#endif
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return ObjGen_ToDebugString;
                        }
#ifdef  OBJGEN_JSON_SUPPORT
                        if (str_Compare("ToJsonFields", (char *)pStr) == 0) {
                            return ObjGen_ToJsonFields;
                        }
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return ObjGen_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == ObjGen_ToDebugString)
                    return "ToDebugString";
#ifdef  OBJGEN_JSON_SUPPORT
                if (pData == ObjGen_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  S p a c e d  C o m m e n t
    //---------------------------------------------------------------

    ASTR_DATA *     ObjGen_SpacedComment(
        OBJGEN_DATA     *this,
        const
        char            *pStrA
    )
    {
        ASTR_DATA       *pNew = OBJ_NIL;
        ASTR_DATA       *pStr = OBJ_NIL;
        int32_t         iRc;
        uint32_t        i;
        uint32_t        len;
        uint32_t        off = 0;
        W32CHR_T        chr;

        // Do initialization.
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        if (NULL == pStrA) {
            return pNew;
        }
        len = utf8_StrLenA(pStrA);
        if (0 == len) {
            return pStr;
        }
        pNew = AStr_New( );

        for(i=0; i<(len-1); ++i) {
            off = utf8_StrOffset(pStrA, i);
            utf8_Utf8ToW32((pStrA + off), &chr);
            AStr_AppendCharW32(pNew, ' ');
            if (('A' <= chr) && (chr <= 'Z')) {
                AStr_AppendCharW32(pNew, ' ');
            }
            AStr_AppendCharW32(pNew, chr);
        }
        utf8_Utf8ToW32((pStrA + off), &chr);
        AStr_AppendCharW32(pNew, chr);

        // Now center.
        pStr = AStr_NewA("// ");
        if (pStr) {
            iRc = OBJGEN_LINE_LENGTH - AStr_getLength(pNew) - AStr_getLength(pStr);
            iRc /= 2;
            if (iRc > 0) {
                AStr_AppendCharRepeatA(pStr, iRc, ' ');
            }
            AStr_Append(pStr, pNew);
            AStr_AppendA(pStr, "\n");
        }

        obj_Release(pNew);
        return pStr;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjGen_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjGen_ToDebugString (
        OBJGEN_DATA      *this,
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
        if (!ObjGen_Validate(this)) {
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
                    ObjGen_getSize(this),
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
    bool            ObjGen_Validate (
        OBJGEN_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_OBJGEN))
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


        if (!(obj_getSize(this) >= sizeof(OBJGEN_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
#endif


    
    //---------------------------------------------------------------
    //                          V I
    //---------------------------------------------------------------

    /*!
     Return the VI header line.
     @param     this    object pointer
     @return    if successful, an AStr object containing the header line.
                Otherwise, OBJ_NIL.
     */
    ASTR_DATA *     ObjGen_VI (
        OBJGEN_DATA     *this
    )
    {
        //ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(this, "%s:\n", __func__);
#ifdef  OBJGEN_SINGLETON
        if (OBJ_NIL == this) {
            this = ObjGen_Shared();
        }
#endif
#ifdef NDEBUG
#else
        if (!ObjGen_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return pStr;
        }
#endif

        pStr = AStr_NewA("// vi:nu:et:sts=4 ts=4 sw=4\n");

        // Return to caller.
        return pStr;
    }




    
#ifdef  __cplusplus
}
#endif


