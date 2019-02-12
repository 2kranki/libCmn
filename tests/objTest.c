// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   objTest.c
 *	Generated 11/01/2017 08:45:27
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
#include <objTest_internal.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    
CMDUTL_OPTION       pPgmOpts[] = {
    {
        "archive",
        'a',
        CMDUTL_ARG_OPTION_NONE,
        CMDUTL_TYPE_BOOL,
        offsetof(OBJTEST_DATA, fArchive),
        NULL,
        "Set Archive Mode"
    },
    {
        "arglength",
        'l',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_NUMBER,
        offsetof(OBJTEST_DATA, pArgLen),
        NULL,
        "Set Argument Length"
    },
    {
        "input",
        'i',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_PATH,
        offsetof(OBJTEST_DATA, pInFilePath),
        NULL,
        "Set Input File Path"
    },
    {
        "output",
        'o',
        CMDUTL_ARG_OPTION_REQUIRED,
        CMDUTL_TYPE_PATH,
        offsetof(OBJTEST_DATA, pOutFilePath),
        NULL,
        "Set Output File Path"
    },
    {NULL,0,0,0,0,NULL,NULL}                    // End of Table
};





 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            objTest_task_body(
        void            *pData
    )
    {
        //OBJTEST_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    OBJTEST_DATA *     objTest_Alloc(
    )
    {
        OBJTEST_DATA    *this;
        uint32_t        cbSize = sizeof(OBJTEST_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    OBJTEST_DATA *     objTest_New(
    )
    {
        OBJTEST_DATA       *this;
        
        this = objTest_Alloc( );
        if (this) {
            this = objTest_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                         A r c h i v e 
    //---------------------------------------------------------------
    
    bool            objTest_getArchive(
        OBJTEST_DATA    *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return this->fArchive;
    }


    bool            objTest_setArchive(
        OBJTEST_DATA    *this,
        bool            value
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        this->fArchive = value;

        return true;
    }



    //---------------------------------------------------------------
    //                       A r g  L e n g t h
    //---------------------------------------------------------------
    
    NUMBER_DATA *   objTest_getArgLength(
        OBJTEST_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArgLen;
    }
    
    
    bool            objTest_setArgLength(
        OBJTEST_DATA    *this,
        NUMBER_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArgLen) {
            obj_Release(this->pArgLen);
        }
        this->pArgLen = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       A r r a y
    //---------------------------------------------------------------
    
    OBJARRAY_DATA * objTest_getArray(
        OBJTEST_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pArray;
    }
    
    
    bool            objTest_setArray(
        OBJTEST_DATA    *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pArray) {
            obj_Release(this->pArray);
        }
        this->pArray = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                       I n  P a t h 
    //---------------------------------------------------------------
    
    PATH_DATA *     objTest_getInPath(
        OBJTEST_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pInFilePath;
    }
    
    
    bool            objTest_setInPath(
        OBJTEST_DATA    *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pInFilePath) {
            obj_Release(this->pInFilePath);
        }
        this->pInFilePath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         objTest_getLastError(
        OBJTEST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            objTest_setLastError(
        OBJTEST_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                       O u t  P a t h 
    //---------------------------------------------------------------
    
    PATH_DATA *     objTest_getOutPath(
        OBJTEST_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        return this->pOutFilePath;
    }
    
    
    bool            objTest_setOutPath(
        OBJTEST_DATA    *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pOutFilePath) {
            obj_Release(this->pOutFilePath);
        }
        this->pOutFilePath = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        objTest_getPriority(
        OBJTEST_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        objTest_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            objTest_setPriority(
        OBJTEST_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        objTest_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        objTest_getSize(
        OBJTEST_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        objTest_setLastError(this, ERESULT_SUCCESS);
        return 0;
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
        ERESULT eRc = objTest__Assign(this,pOther);
     @endcode 
     @param     this    OBJTEST object pointer
     @param     pOther  a pointer to another OBJTEST object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         objTest_Assign(
        OBJTEST_DATA		*this,
        OBJTEST_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !objTest_Validate(pOther) ) {
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
        objTest_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        objTest_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return objTest_getLastError(this);
    }
    
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        objTest      *pCopy = objTest_Copy(this);
     @endcode 
     @param     this    OBJTEST object pointer
     @return    If successful, a OBJTEST object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the OBJTEST object.
     */
    OBJTEST_DATA *     objTest_Copy(
        OBJTEST_DATA       *this
    )
    {
        OBJTEST_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = objTest_New( );
        if (pOther) {
            eRc = objTest_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        objTest_setLastError(this, ERESULT_SUCCESS);
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            objTest_Dealloc(
        OBJ_ID          objId
    )
    {
        OBJTEST_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((OBJTEST_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        objTest_setArgLength(this, OBJ_NIL);
        objTest_setArray(this, OBJ_NIL);
        objTest_setInPath(this, OBJ_NIL);
        objTest_setOutPath(this, OBJ_NIL);
        if (this->pLock) {
            obj_Release(this->pLock);
            this->pLock = OBJ_NIL;
        }

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         objTest_Disable(
        OBJTEST_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        objTest_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         objTest_Enable(
        OBJTEST_DATA		*this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        objTest_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    OBJTEST_DATA *   objTest_Init(
        OBJTEST_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(OBJTEST_DATA);
        
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

        this = (OBJ_ID)appl_Init((APPL_DATA *)this);        // Needed for Inheritance
        //this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_OBJTEST);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        obj_setSize(this, cbSize);                          // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&objTest_Vtbl);
        
        objTest_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pArray = objArray_New();
        if (OBJ_NIL == this->pArray) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
       this->pLock = psxLock_New();
        if (OBJ_NIL == this->pLock) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "objTest::offsetof(eRc) = %lu\n", offsetof(OBJTEST_DATA,eRc));
        //fprintf(stderr, "objTest::sizeof(OBJTEST_DATA) = %lu\n", sizeof(OBJTEST_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(OBJTEST_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         objTest_IsEnabled(
        OBJTEST_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            objTest_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        objTest_setLastError(this, ERESULT_SUCCESS_FALSE);
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
     void        *pMethod = objTest_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                         for OBJ_QUERYINFO_TYPE_METHOD, this field points to a
                         character string which represents the method name without
                         the object name, "objTest", prefix,
                         for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                         address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                 OBJ_QUERYINFO_TYPE_INFO: info pointer,
                 OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                 OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          objTest_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        OBJTEST_DATA    *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
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
                            return objTest_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return objTest_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("TestMethod01", (char *)pStr) == 0) {
                            return objTest_TestMethod01;
                        }
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return objTest_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return objTest_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == objTest_TestMethod01)
                    return "TestMethod01";
                else if (pData == objTest_ToDebugString)
                    return "ToDebugString";
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                      T e s t  M e t h o d s
    //---------------------------------------------------------------
    
    ERESULT         objTest_TestMethod01(
        OBJTEST_DATA    *this,
        OBJ_ID          pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
        if (NULL == this) {
            return ERESULT_INVALID_OBJECT;
        }
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        psxLock_Lock(this->pLock);
        eRc = objArray_AppendObj(this->pArray, pData, NULL);
        BREAK_FAILED(eRc);
        psxLock_Unlock(this->pLock);

        // Return to caller.
        objTest_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = objTest_ToDebugString(this,4);
     @endcode 
     @param     this    OBJTEST object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     objTest_ToDebugString(
        OBJTEST_DATA      *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
#ifdef  XYZZY        
        ASTR_DATA       *pWrkStr;
#endif
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = objTest_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    objTest_getSize(this)
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
            AStr_AppendCharRepeatW32(pStr, indent, ' ');
        }
        eRc =   AStr_AppendPrint(
                    pStr,
                    " %p(%s)}\n", 
                    this, 
                    pInfo->pClassName
                );
        
        objTest_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     objTest_ToJSON(
        OBJTEST_DATA      *this
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !objTest_Validate(this) ) {
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
        
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            objTest_Validate(
        OBJTEST_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, OBJ_IDENT_OBJTEST) )
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


        if( !(obj_getSize(this) >= sizeof(OBJTEST_DATA)) ) {
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


