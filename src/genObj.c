// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   genObj.c
 *	Generated 12/09/2017 07:54:00
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
#include    <genObj_internal.h>
#include    <ascii.h>
#include    <str.h>
#include    <utf8.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    typedef struct getter_s {
        const
        char            *pType;
        const
        char            *pName;
    } GETTER;
    
    GETTER          getters[] = {
        {"int", "iRet"},
        {"int8_t", "iRet"},
        {"int16_t", "iRet"},
        {"int32_t", "iRet"},
        {"int64_t", "iRet"},
        {"uint8_t", "iRet"},
        {"uint16_t", "iRet"},
        {"uint32_t", "iRet"},
        {"uint64_t", "iRet"},
        {"uint64_t", "iRet"},
    };

 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    ASTR_DATA *     genObj_CreateSpacedComment(
        GENOBJ_DATA     *this,
        const
        char            *pStr
    )
    {
        ASTR_DATA       *pNew = OBJ_NIL;
        uint32_t        i;
        uint32_t        len;
        uint32_t        off;
        W32CHR_T        chr;

        if (OBJ_NIL == pStr) {
            return pNew;
        }
        len = utf8_StrLenA(pStr);
        if (0 == len) {
            return pNew;
        }
        pNew = AStr_New( );
        
        utf8_Utf8ToW32(pStr, &chr);
        AStr_AppendCharW32(pNew, chr);
        for(i=1; i<len; ++i) {
            off = utf8_StrOffset(pStr, i);
            utf8_Utf8ToW32((pStr + off), &chr);
            AStr_AppendCharW32(pNew, ' ');
            if (('A' <= chr) && (chr <= 'Z')) {
                AStr_AppendCharW32(pNew, ' ');
            }
            AStr_AppendCharW32(pNew, chr);
        }
        return pNew;
    }



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GENOBJ_DATA *     genObj_Alloc(
    )
    {
        GENOBJ_DATA     *this;
        uint32_t        cbSize = sizeof(GENOBJ_DATA);
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GENOBJ_DATA *     genObj_New(
    )
    {
        GENOBJ_DATA       *this;
        
        this = genObj_Alloc( );
        if (this) {
            this = genObj_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         genObj_getLastError(
        GENOBJ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            genObj_setLastError(
        GENOBJ_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        genObj_getPriority(
        GENOBJ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genObj_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            genObj_setPriority(
        GENOBJ_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        genObj_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        genObj_getSize(
        GENOBJ_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genObj_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  genObj_getSuperVtbl(
        GENOBJ_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        genObj_setLastError(this, ERESULT_SUCCESS);
        return this->pSuperVtbl;
    }
    
  

    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                      A d d  V a r i a b l e
    //---------------------------------------------------------------
    
    ERESULT         genObj_AddVarA(
        GENOBJ_DATA     *this,
        const
        char            *pName,
        const
        char            *pValue
    )
    {
        ASTR_DATA       *pAValue = OBJ_NIL;
        ASTR_DATA       *pAValueUC = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        NODE_DATA       *pNodeUC = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        pAValue = AStr_NewA(pValue);
        if (OBJ_NIL == pAValue) {
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return this->eRc;
        }
        pNode = node_NewWithUTF8(pName, pAValue);
        if (OBJ_NIL == pAValue) {
            obj_Release(pAValue);
            this->eRc = ERESULT_OUT_OF_MEMORY;
            return this->eRc;
        }

        this->eRc = nodeHash_Add(this->pHash, pNode);
        if (!ERESULT_FAILED(this->eRc) && (0 == strcmp("ClassName", pName))) {
            pAValueUC = AStr_ToUpper(pAValue);
            if (OBJ_NIL == pAValueUC) {
                obj_Release(pNode);
                obj_Release(pAValue);
                this->eRc = ERESULT_OUT_OF_MEMORY;
                return this->eRc;
            }
            pNodeUC = node_NewWithUTF8("ClassNameUC", pAValueUC);
            if (OBJ_NIL == pNodeUC) {
                obj_Release(pNode);
                obj_Release(pAValueUC);
                obj_Release(pAValue);
                this->eRc = ERESULT_OUT_OF_MEMORY;
                return this->eRc;
            }
            this->eRc = nodeHash_Add(this->pHash, pNodeUC);
        }
        else if (!ERESULT_FAILED(this->eRc) && (0 == strcmp("SuperClassName", pName))) {
            pAValueUC = AStr_ToUpper(pAValue);
            if (OBJ_NIL == pAValueUC) {
                obj_Release(pNode);
                obj_Release(pAValue);
                this->eRc = ERESULT_OUT_OF_MEMORY;
                return this->eRc;
            }
            pNodeUC = node_NewWithUTF8("SuperClassNameUC", pAValueUC);
            if (OBJ_NIL == pNodeUC) {
                obj_Release(pNode);
                obj_Release(pAValueUC);
                obj_Release(pAValue);
                this->eRc = ERESULT_OUT_OF_MEMORY;
                return this->eRc;
            }
            this->eRc = nodeHash_Add(this->pHash, pNodeUC);
        }

        obj_Release(pNodeUC);
        pNodeUC = OBJ_NIL;
        obj_Release(pAValueUC);
        pAValueUC = OBJ_NIL;
        obj_Release(pNode);
        pNode = OBJ_NIL;
        obj_Release(pAValue);
        pAValue = OBJ_NIL;

        // Return to caller.
        return this->eRc;
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
        ERESULT eRc = genObj__Assign(this,pOther);
     @endcode 
     @param     this    GENOBJ object pointer
     @param     pOther  a pointer to another GENOBJ object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         genObj_Assign(
        GENOBJ_DATA		*this,
        GENOBJ_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !genObj_Validate(pOther) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

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
        
        //goto eom;

        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        genObj_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return genObj_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        genObj      *pCopy = genObj_Copy(this);
     @endcode 
     @param     this    GENOBJ object pointer
     @return    If successful, a GENOBJ object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the GENOBJ object.
     */
    GENOBJ_DATA *   genObj_Copy(
        GENOBJ_DATA     *this
    )
    {
        GENOBJ_DATA     *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
       
        //FIXME: Remove ifdef/endif
#ifdef XYZZY
        pOther = genObj_New( );
        if (pOther) {
            eRc = genObj_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
#endif
        
        // Return to caller.
        //obj_Release(pOther);
        genObj_setLastError(this, ERESULT_SUCCESS);
        genObj_setLastError(this, ERESULT_NOT_IMPLEMENTED); //FIXME: Remove this.
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            genObj_Dealloc(
        OBJ_ID          objId
    )
    {
        GENOBJ_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GENOBJ_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        if (this->pHash) {
            obj_Release(this->pHash);
            this->pHash = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         genObj_Disable(
        GENOBJ_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         genObj_Enable(
        GENOBJ_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //               G e n e r a t e  D a t a  E n d
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenDataEnd(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr             // (in/out)
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pClassName;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pNode = nodeHash_FindA(this->pHash, "ClassName");
        if (OBJ_NIL == pNode) {
            return this->eRc;
        }
        pClassName = AStr_getData(node_getData(pNode));

        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendA(*ppStr, "\n\n");
        AStr_AppendA(*ppStr, "#ifdef    __cplusplus\n");
        AStr_AppendA(*ppStr, "}\n");
        AStr_AppendA(*ppStr, "#endif\n");
        AStr_AppendA(*ppStr, "\n\n\n");
        AStr_AppendA(*ppStr, "\n\n\n");

        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //               G e n e r a t e  D a t a  S t a r t
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenDataStart(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        const
        char            *pIncludes
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pClassName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pNode = nodeHash_FindA(this->pHash, "ClassName");
        if (OBJ_NIL == pNode) {
            return this->eRc;
        }
        pClassName = AStr_getData(node_getData(pNode));
        
        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendA(
                     *ppStr,
                     "//*****************************************************************\n"
                     );
        AStr_AppendA(
                     *ppStr,
                     "//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *\n"
                     );
        AStr_AppendA(
                     *ppStr,
                     "//*****************************************************************\n"
                     );
        AStr_AppendA(*ppStr, "\n\n");
        AStr_AppendA(*ppStr, "/* Header File Inclusion */\n");
        AStr_AppendPrint(*ppStr, "#include <%s_internal.h>\n", pClassName);
        AStr_AppendPrint(*ppStr, "#include <ascii.h>\n");
        AStr_AppendPrint(*ppStr, "#include <utf8.h>\n");
        if (pIncludes) {
            AStr_AppendA(*ppStr, pIncludes);
        }
        AStr_AppendA(*ppStr, "\n\n\n");
        AStr_AppendA(*ppStr, "#ifdef    __cplusplus\n");
        AStr_AppendA(*ppStr, "extern \"C\" {\n");
        AStr_AppendA(*ppStr, "#endif\n");
        AStr_AppendA(*ppStr, "\n\n\n");
        AStr_AppendA(*ppStr, "\n\n\n");
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          G e n e r a t e  G e t t e r  S e t t e r
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenGetSet(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        uint32_t        offset,
        const
        char            *pDataType,
        const
        char            *pName,
        const
        char            *pPrefix
    )
    {
        ASTR_DATA       *pOffset = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        int32_t         i;
        const
        char            *pClassName;
        const
        char            *pClassNameUC;
        ASTR_DATA       *pMethodName = OBJ_NIL;
        ASTR_DATA       *pMethodDesc = OBJ_NIL;
        bool            fObject = false;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pOffset = AStr_New();
        BREAK_NULL(pOffset);
        AStr_AppendCharRepeatA(pOffset, offset, ' ');
        pNode = nodeHash_FindA(this->pHash, "ClassName");
        if (OBJ_NIL == pNode) {
            obj_Release(pOffset);
            return this->eRc;
        }
        pClassName = AStr_getData(node_getData(pNode));
        pNode = nodeHash_FindA(this->pHash, "ClassNameUC");
        if (OBJ_NIL == pNode) {
            obj_Release(pOffset);
            return this->eRc;
        }
        pClassNameUC = AStr_getData(node_getData(pNode));
        if (0 == strcmp("eRc", pName)) {
            pMethodName = AStr_NewA("LastError");
            BREAK_NULL(pMethodName);
            pMethodDesc = genObj_CreateSpacedComment(this, "LastError");
            if (OBJ_NIL == pMethodDesc) {
                obj_Release(pOffset);
                return this->eRc;
            }
        }
        else {
            if ((*pName == 'p') && (ascii_isUpperA(*(pName + 1)))) {
                pMethodName = AStr_NewA(pName + 1);
                BREAK_NULL(pMethodName);
            }
            else {
                pMethodName = AStr_NewA(pName);
                BREAK_NULL(pMethodName);
            }
            pMethodDesc = genObj_CreateSpacedComment(this, AStr_getData(pMethodName));
            if (OBJ_NIL == pMethodDesc) {
                obj_Release(pOffset);
                return this->eRc;
            }
            AStr_CharPutW32(pMethodName, 1, ascii_toUpperA(AStr_CharGetW32(pMethodName,1)));
        }
        i = 40 - AStr_getLength(pMethodDesc);
        if (i > 1) {
            AStr_CharInsertW32Repeat(pMethodDesc, 1, (i >> 1), ' ');
        }
        {
            ASTR_DATA           *pWrk = AStr_NewA(pDataType);
            if (pWrk) {
                if (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pWrk, "OBJ_ID")) {
                    fObject = true;
                }
                else if (AStr_CompareRightA(pWrk, "_DATA *") == ERESULT_SUCCESS_EQUAL) {
                    fObject = true;
                }
            }
            obj_Release(pWrk);
        }
        
        
        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendPrint(
                         *ppStr,
                         "%s//---------------------------------------------------------------\n",
                         AStr_getData(pOffset)
                         );
        AStr_AppendPrint(
                         *ppStr,
                         "%s//\t\t\t%s\n",
                         AStr_getData(pOffset),
                         AStr_getData(pMethodDesc)
                         );
        AStr_AppendPrint(
                         *ppStr,
                         "%s//---------------------------------------------------------------\n",
                         AStr_getData(pOffset)
                         );
        AStr_AppendPrint(*ppStr, "\n");
        AStr_AppendPrint(
                         *ppStr,
                         "%s%s\t\t\t%s_get%s(\n",
                         AStr_getData(pOffset),
                         pDataType,
                         pClassName,
                         AStr_getData(pMethodName)
                         );
        AStr_AppendPrint(
                         *ppStr,
                         "%s\t%s_DATA\t*this\n",
                         AStr_getData(pOffset),
                         pClassNameUC
                         );
        AStr_AppendPrint(*ppStr, "%s)\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s{\n", AStr_getData(pOffset));
        if (0 == strcmp("int", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint8_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint16_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint32_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint64_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint8_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint16_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint32_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint64_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (fObject) {
            AStr_AppendPrint(*ppStr, "%s\tOBJ_ID\t\t\tpObj = OBJ_NIL;\n", AStr_getData(pOffset));
        }
        else {
            AStr_AppendPrint(
                             *ppStr,
                             "%s\t%s\t\t\t%s = 0;\n",
                             AStr_getData(pOffset),
                             pDataType,
                             pName
            );
        }
        AStr_AppendPrint(*ppStr, "\n");
        AStr_AppendPrint(*ppStr, "%s\t// Do initialization.\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#ifdef NDEBUG\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#else\n", AStr_getData(pOffset));
        AStr_AppendPrint(
                         *ppStr,
                         "%s\tif (!%s_Validate(this)) {\n",
                         AStr_getData(pOffset),
                         pClassName
                         );
        AStr_AppendPrint(*ppStr, "%s\t\tDEBUG_BREAK();\n", AStr_getData(pOffset));
        if (fObject) {
            AStr_AppendPrint(*ppStr, "%s\t\treturn pObj;\n", AStr_getData(pOffset));
        }
        else {
            AStr_AppendPrint(*ppStr, "%s\t\treturn iRet;\n", AStr_getData(pOffset));
        }
        AStr_AppendPrint(*ppStr, "\t%s}\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#endif\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "\n");
        if (fObject) {
            AStr_AppendPrint(
                             *ppStr,
                             "%s\tpObj = this->%s;\n",
                             AStr_getData(pOffset),
                             pName
            );
        }
        else {
            AStr_AppendPrint(
                             *ppStr,
                             "%s\tiRet = this->%s;\n",
                             AStr_getData(pOffset),
                             pName
                             );
        }
        AStr_AppendPrint(*ppStr, "\n");
        AStr_AppendPrint(*ppStr, "%s\t// Return to caller.\n", AStr_getData(pOffset));
        if (0 == strcmp("void", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("ERESULT", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\treturn this->eRc;\n", AStr_getData(pOffset));
        }
        else if (fObject) {
            AStr_AppendPrint(*ppStr, "%s\treturn pObj;\n", AStr_getData(pOffset));
        }
        AStr_AppendPrint(*ppStr, "%s}\n\n\n", AStr_getData(pOffset));
        
        AStr_AppendPrint(
                         *ppStr,
                         "%sbool\t\t\t%s_set%s(\n",
                         AStr_getData(pOffset),
                         pClassName,
                         AStr_getData(pMethodName)
        );
        AStr_AppendPrint(
                         *ppStr,
                         "%s\t%s_DATA\t*this,\n",
                         AStr_getData(pOffset),
                         pClassNameUC
        );
        if (0 == strcmp("int", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint8_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint16_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint32_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tint64_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint8_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint16_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint32_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pDataType)) {
            AStr_AppendPrint(*ppStr, "%s\tuint64_t\t\t\tvalue\n", AStr_getData(pOffset));
        }
        else if (fObject) {
            AStr_AppendPrint(
                             *ppStr,
                             "%s\t%s\t\t\tpValue\n",
                             AStr_getData(pOffset),
                             pDataType
            );
        }
        else {
            AStr_AppendPrint(
                             *ppStr,
                             "%s\t%s\t\t\tvalue\n",
                             AStr_getData(pOffset),
                             pDataType
                             );
        }
        AStr_AppendPrint(*ppStr, "%s)\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s{\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "\n");
        AStr_AppendPrint(*ppStr, "%s\t// Do initialization.\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#ifdef NDEBUG\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#else\n", AStr_getData(pOffset));
        AStr_AppendPrint(
                         *ppStr,
                         "%s\tif (!%s_Validate(this)) {\n",
                         AStr_getData(pOffset),
                         pClassName
                         );
        AStr_AppendPrint(*ppStr, "%s\t\tDEBUG_BREAK();\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s\t\treturn false;\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "\t%s}\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#endif\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "\n");
        if (fObject) {
            AStr_AppendPrint(*ppStr,
                             "%s\tobj_Retain(pValue);\n",
                             AStr_getData(pOffset)
            );
            AStr_AppendPrint(*ppStr,
                             "%s\tif (this->%s) {\n",
                             AStr_getData(pOffset),
                             pName
                             );
            AStr_AppendPrint(*ppStr,
                             "%s\t\tobj_Release(this->%s);\n",
                             AStr_getData(pOffset),
                             pName
                             );
            AStr_AppendPrint(*ppStr,
                             "%s\t\t//this->%s = OBJ_NIL;\n",
                             AStr_getData(pOffset),
                             pName
                             );
            AStr_AppendPrint(*ppStr, "\t%s}\n", AStr_getData(pOffset));
            AStr_AppendPrint(*ppStr,
                             "%s\tthis->%s = pValue;\n",
                             AStr_getData(pOffset),
                             pName
                             );
        }
        else {
            AStr_AppendPrint(*ppStr,
                             "%s\tthis->%s = value;\n",
                             AStr_getData(pOffset),
                             pName
            );
        }
        AStr_AppendPrint(*ppStr, "\n");
        AStr_AppendPrint(*ppStr, "%s\t// Return to caller.\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s\treturn true;\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s}\n\n\n\n", AStr_getData(pOffset));

        obj_Release(pOffset);
        pOffset = OBJ_NIL;
        obj_Release(pMethodDesc);
        pMethodDesc = OBJ_NIL;
        obj_Release(pMethodName);
        pMethodName = OBJ_NIL;

        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //               G e n e r a t e  L i c e n s e
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenLicense(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr             // (in/out)
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendA(*ppStr, "/*\n");
        AStr_AppendA(*ppStr, " This is free and unencumbered software released into the public domain.\n");
        AStr_AppendA(*ppStr, " \n");
        AStr_AppendA(*ppStr, " Anyone is free to copy, modify, publish, use, compile, sell, or\n");
        AStr_AppendA(*ppStr, " distribute this software, either in source code form or as a compiled\n");
        AStr_AppendA(*ppStr, " binary, for any purpose, commercial or non-commercial, and by any\n");
        AStr_AppendA(*ppStr, " means.\n");
        AStr_AppendA(*ppStr, " \n");
        AStr_AppendA(*ppStr, " In jurisdictions that recognize copyright laws, the author or authors\n");
        AStr_AppendA(*ppStr, " of this software dedicate any and all copyright interest in the\n");
        AStr_AppendA(*ppStr, " software to the public domain. We make this dedication for the benefit\n");
        AStr_AppendA(*ppStr, " of the public at large and to the detriment of our heirs and\n");
        AStr_AppendA(*ppStr, " successors. We intend this dedication to be an overt act of\n");
        AStr_AppendA(*ppStr, " relinquishment in perpetuity of all present and future rights to this\n");
        AStr_AppendA(*ppStr, " software under copyright law.\n");
        AStr_AppendA(*ppStr, " \n");
        AStr_AppendA(*ppStr, " THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n");
        AStr_AppendA(*ppStr, " EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF\n");
        AStr_AppendA(*ppStr, " MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.\n");
        AStr_AppendA(*ppStr, " IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR\n");
        AStr_AppendA(*ppStr, " OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,\n");
        AStr_AppendA(*ppStr, " ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n");
        AStr_AppendA(*ppStr, " OTHER DEALINGS IN THE SOFTWARE.\n");
        AStr_AppendA(*ppStr, " \n");
        AStr_AppendA(*ppStr, " For more information, please refer to <http://unlicense.org/>\n");
        AStr_AppendA(*ppStr, " \n");
        AStr_AppendA(*ppStr, " */\n\n\n\n");

        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //               G e n e r a t e  M e t h o d
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenMethod(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        uint32_t        offset,
        const
        char            *pName,
        const
        char            *pReturns,
        const
        char            *pDataDefs,
        const
        char            *pBody,
        bool            fStatic
    )
    {
        ASTR_DATA       *pOffset = OBJ_NIL;
        NODE_DATA       *pNode = OBJ_NIL;
        int32_t         i;
        const
        char            *pClassName;
        const
        char            *pClassNameUC;
        ASTR_DATA       *pMethodDesc = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pOffset = AStr_New();
        AStr_AppendCharRepeatA(pOffset, offset, ' ');
        pNode = nodeHash_FindA(this->pHash, "ClassName");
        if (OBJ_NIL == pNode) {
            obj_Release(pOffset);
            return this->eRc;
        }
        pClassName = AStr_getData(node_getData(pNode));
        pNode = nodeHash_FindA(this->pHash, "ClassNameUC");
        if (OBJ_NIL == pNode) {
            obj_Release(pOffset);
            return this->eRc;
        }
        pClassNameUC = AStr_getData(node_getData(pNode));
        pMethodDesc = genObj_CreateSpacedComment(this, pName);
        if (OBJ_NIL == pMethodDesc) {
            obj_Release(pOffset);
            return this->eRc;
        }
        i = 40 - AStr_getLength(pMethodDesc);
        if (i > 1) {
            AStr_CharInsertW32Repeat(pMethodDesc, 1, (i >> 1), ' ');
        }
        

        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendPrint(
            *ppStr,
            "%s//---------------------------------------------------------------\n",
            AStr_getData(pOffset)
        );
        AStr_AppendPrint(
                         *ppStr,
                         "%s//\t\t\t%s\n",
                         AStr_getData(pOffset),
                         AStr_getData(pMethodDesc)
        );
        obj_Release(pMethodDesc);
        pMethodDesc = OBJ_NIL;
        AStr_AppendPrint(
            *ppStr,
            "%s//---------------------------------------------------------------\n",
            AStr_getData(pOffset)
        );
        AStr_AppendPrint(*ppStr, "\n");
        if (fStatic) {
            AStr_AppendPrint(
                             *ppStr,
                             "%sstatic\n",
                             AStr_getData(pOffset)
                             );
        }
        AStr_AppendPrint(
                         *ppStr,
                         "%s%s\t\t\t%s_%s(\n",
                         AStr_getData(pOffset),
                         pReturns,
                         pClassName,
                         pName
                         );
        if (pDataDefs) {
            AStr_AppendPrint(
                             *ppStr,
                             "%s\t%s_DATA\t*this,\n",
                             AStr_getData(pOffset),
                             pClassNameUC
            );
            AStr_AppendPrint(
                             *ppStr,
                             "%s",
                             pDataDefs
            );
        }
        else {
            AStr_AppendPrint(
                             *ppStr,
                             "%s\t%s_DATA\t*this\n",
                             AStr_getData(pOffset),
                             pClassNameUC
            );
        }
        AStr_AppendPrint(*ppStr, "%s)\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s{\n", AStr_getData(pOffset));
        if (0 == strcmp("int", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tint\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tint8_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tint16_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tint32_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tint64_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tuint8_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tuint16_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tuint32_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\tuint64_t\t\t\tiRet = 0;\n", AStr_getData(pOffset));
        }
        if (pDataDefs) {
            AStr_AppendPrint(*ppStr, "%s", pDataDefs);
        }
        AStr_AppendPrint(*ppStr, "\n");
        AStr_AppendPrint(*ppStr, "%s\t// Do initialization.\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#ifdef NDEBUG\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#else\n", AStr_getData(pOffset));
        AStr_AppendPrint(
                         *ppStr,
                         "%s\tif (!%s_Validate(this)) {\n",
                         AStr_getData(pOffset),
                         pClassName
        );
        AStr_AppendPrint(*ppStr, "%s\t\tDEBUG_BREAK();\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s\t\treturn ERESULT_INVALID_OBJECT;\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "\t%s}\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "%s#endif\n", AStr_getData(pOffset));
        AStr_AppendPrint(*ppStr, "\n");
        if (pBody) {
            AStr_AppendPrint(*ppStr, "%s", pBody);
        }
        AStr_AppendPrint(*ppStr, "\n");
        AStr_AppendPrint(*ppStr, "%s\t// Return to caller.\n", AStr_getData(pOffset));
        if (0 == strcmp("void", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int8_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int16_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int32_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("int64_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint8_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint16_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint32_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
        else if (0 == strcmp("uint64_t", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn iRet;\n", AStr_getData(pOffset));
        }
       else if (0 == strcmp("ERESULT", pReturns)) {
            AStr_AppendPrint(*ppStr, "%s\treturn this->eRc;\n", AStr_getData(pOffset));
        }
        else {
            AStr_AppendPrint(*ppStr, "%s\treturn this->eRc;\n", AStr_getData(pOffset));
        }
        AStr_AppendPrint(*ppStr, "%s}\n\n\n\n", AStr_getData(pOffset));
        
        obj_Release(pOffset);
        pOffset = OBJ_NIL;
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //               G e n e r a t e  P g m  E n d
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenPgmEnd(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr             // (in/out)
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pClassName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pNode = nodeHash_FindA(this->pHash, "ClassName");
        if (OBJ_NIL == pNode) {
            return this->eRc;
        }
        pClassName = AStr_getData(node_getData(pNode));
        
        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendA(*ppStr, "\n\n");
        AStr_AppendA(*ppStr, "#ifdef    __cplusplus\n");
        AStr_AppendA(*ppStr, "}\n");
        AStr_AppendA(*ppStr, "#endif\n");
        AStr_AppendA(*ppStr, "\n\n\n");
        AStr_AppendA(*ppStr, "\n\n\n");
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //               G e n e r a t e  P g m  S t a r t
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenPgmStart(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        const
        char            *pIncludes
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pClassName;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pNode = nodeHash_FindA(this->pHash, "ClassName");
        if (OBJ_NIL == pNode) {
            return this->eRc;
        }
        pClassName = AStr_getData(node_getData(pNode));
        
        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendA(
                     *ppStr,
                     "//*****************************************************************\n"
                     );
        AStr_AppendA(
                     *ppStr,
                     "//* * * * * * * * * * * *  Program Routines   * * * * * * * * * * *\n"
                     );
        AStr_AppendA(
                     *ppStr,
                     "//*****************************************************************\n"
                     );
        AStr_AppendA(*ppStr, "\n\n");
        AStr_AppendA(*ppStr, "/* Header File Inclusion */\n");
        AStr_AppendPrint(*ppStr, "#include <%s_internal.h>\n", pClassName);
        AStr_AppendPrint(*ppStr, "#include <ascii.h>\n");
        AStr_AppendPrint(*ppStr, "#include <utf8.h>\n");
        if (pIncludes) {
            AStr_AppendA(*ppStr, pIncludes);
        }
        AStr_AppendA(*ppStr, "\n\n\n");
        AStr_AppendA(*ppStr, "#ifdef    __cplusplus\n");
        AStr_AppendA(*ppStr, "extern \"C\" {\n");
        AStr_AppendA(*ppStr, "#endif\n");
        AStr_AppendA(*ppStr, "\n\n\n");
        AStr_AppendA(*ppStr, "\n\n\n");
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //              G e n e r a t e  S e c t i o n
    //---------------------------------------------------------------
    
    ERESULT         genObj_GenSection(
        GENOBJ_DATA     *this,
        ASTR_DATA       **ppStr,            // (in/out)
        const
        char            *pSection
    )
    {
        NODE_DATA       *pNode = OBJ_NIL;
        const
        char            *pClassName;
        ASTR_DATA       *pWrk;
        uint32_t        i;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == ppStr) {
            genObj_setLastError(this, ERESULT_INVALID_PARAMETER);
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        pNode = nodeHash_FindA(this->pHash, "ClassName");
        if (OBJ_NIL == pNode) {
            return ERESULT_DATA_NOT_FOUND;
        }

        if (OBJ_NIL == *ppStr) {
            *ppStr = AStr_New();
        }
        AStr_AppendA(
                     *ppStr,
                     "//===============================================================\n"
                     );
        pWrk = AStr_NewA(pSection);
        BREAK_NULL(pWrk);
        i = 40 - AStr_getLength(pWrk);
        if (i > 1) {
            AStr_CharInsertW32Repeat(pWrk, 1, (i >> 1), ' ');
        }
        AStr_AppendPrint(
                     *ppStr,
                     "// %s\n",
                    AStr_getData(pWrk)
        );
        obj_Release(pWrk);
        AStr_AppendA(
                     *ppStr,
                     "//===============================================================\n"
        );
        AStr_AppendA(*ppStr, "\n\n");
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GENOBJ_DATA *   genObj_Init(
        GENOBJ_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(GENOBJ_DATA);
        
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

        //this = (OBJ_ID)other_Init((OTHER_DATA *)this);    // Needed for Inheritance
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_GENOBJ);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_GENOBJ);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&genObj_Vtbl);
        
        genObj_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pHash = nodeHash_New(NODEHASH_TABLE_SIZE_XXXSMALL);

    #ifdef NDEBUG
    #else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "genObj::offsetof(eRc) = %lu\n", offsetof(GENOBJ_DATA,eRc));
        //fprintf(stderr, "genObj::sizeof(GENOBJ_DATA) = %lu\n", sizeof(GENOBJ_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(GENOBJ_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         genObj_IsEnabled(
        GENOBJ_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            genObj_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        genObj_setLastError(this, ERESULT_SUCCESS_FALSE);
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
        void        *pMethod = genObj_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "genObj", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          genObj_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GENOBJ_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return genObj_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return genObj_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return genObj_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return genObj_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == genObj_ToDebugString)
                    return "ToDebugString";
                if (pData == genObj_ToJSON)
                    return "ToJSON";
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
        ASTR_DATA      *pDesc = genObj_ToDebugString(this,4);
     @endcode 
     @param     this    GENOBJ object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     genObj_ToDebugString(
        GENOBJ_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = genObj_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    genObj_getSize(this)
            );

#ifdef  XYZZY        
        if (this->pData) {
            if (((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString) {
                pWrkStr =   ((OBJ_DATA *)(this->pData))->pVtbl->pToDebugString(
                                                    this->pData,
                                                    indent+3
                            );
                AStr_Append(pStr, pWrkStr);
                obj_Release(pWrkStr);
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
        
        genObj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     genObj_ToJSON(
        GENOBJ_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        pInfo = obj_getInfo(this);
        
        pStr = AStr_New();
        eRc =   AStr_AppendPrint(
                    pStr,
                    "{\"objectType\":\"%s\"",
                    pInfo->pClassName
                );
        
        AStr_AppendA(pStr, "}\n");
        
        genObj_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      U p d a t e  V a r i a b l e
    //---------------------------------------------------------------
    
    ERESULT         genObj_UpdateVar(
        GENOBJ_DATA     *this,
        const
        char            *pName,
        const
        char            *pValue
    )
    {
        char            *pValueNew;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genObj_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        // FIXME: Correct to use nodeHash instead of szHash.
#ifdef XYZZY
        this->eRc = szHash_UpdateA(this->pHash, pName, (void *)pValue);
        if (!ERESULT_FAILED(this->eRc) && (0 == strcmp("ClassName", pName))) {
            pValueNew = str_DupA(pValue);
            pValueNew = str_ToUpperA((char *)pValueNew);
            this->eRc = szHash_UpdateA(this->pHash, "ClassNameUC", (void *)pValueNew);
            mem_Free(pValueNew);
        }
        else if (!ERESULT_FAILED(this->eRc) && (0 == strcmp("SuperClassName", pName))) {
            pValueNew = str_DupA(pValue);
            pValueNew = str_ToUpperA((char *)pValueNew);
            this->eRc = szHash_UpdateA(this->pHash, "SuperClassNameUC", (void *)pValueNew);
            mem_Free(pValueNew);
        }
#endif

        // Return to caller.
        return this->eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            genObj_Validate(
        GENOBJ_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_GENOBJ) )
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


        if( !(obj_getSize(this) >= sizeof(GENOBJ_DATA)) ) {
            this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


