// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   genBase.c
 *	Generated 04/10/2018 10:49:33
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
#include <genBase_internal.h>
#include <path.h>
#include <trace.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            genBase_task_body(
        void            *pData
    )
    {
        //GENBASE_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    GENBASE_DATA *     genBase_Alloc(
    )
    {
        GENBASE_DATA    *this;
        uint32_t        cbSize = sizeof(GENBASE_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    GENBASE_DATA *     genBase_New(
    )
    {
        GENBASE_DATA       *this;
        
        this = genBase_Alloc( );
        if (this) {
            this = genBase_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                  D a t e  T i m e
    //---------------------------------------------------------------
    
    DATETIME_DATA * genBase_getDateTime(
        GENBASE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return this->pDateTime;
    }
    
    
    bool            genBase_setDateTime(
        GENBASE_DATA    *this,
        DATETIME_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDateTime) {
            obj_Release(this->pDateTime);
        }
        this->pDateTime = pValue;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D i c t i o n a r y
    //---------------------------------------------------------------
    
    SZHASH_DATA *   genBase_getDict(
        GENBASE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return this->pDict;
    }
    
    
    bool            genBase_setDict(
        GENBASE_DATA    *this,
        SZHASH_DATA     *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pDict) {
            obj_Release(this->pDict);
        }
        this->pDict = pValue;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      G e n e r a t o r s
    //---------------------------------------------------------------
    
    ERESULT         genBase_setGenerators(
        GENBASE_DATA    *this,
        ERESULT         (*pFinal)(GENBASE_DATA *),
        ERESULT         (*pInitial)(GENBASE_DATA *, ASTR_DATA *, NODEARRAY_DATA  *),
        ERESULT         (*pLibrary)(GENBASE_DATA *),
        ERESULT         (*pObjects)(GENBASE_DATA *, NODEHASH_DATA *, NODEARRAY_DATA  *),
        ERESULT         (*pOsSpecific)(GENBASE_DATA *, NODEHASH_DATA  *),
        ERESULT         (*pPrograms)(GENBASE_DATA *, NODEHASH_DATA  *),
        ERESULT         (*pTests)(GENBASE_DATA *, NODEHASH_DATA *)
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pFinal = pFinal;
        this->pInitial = pInitial;
        this->pLibrary = pLibrary;
        this->pObjects = pObjects;
        this->pOsSpecific = pOsSpecific;
        this->pPrograms = pPrograms;
        this->pTests = pTests;

        genBase_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         genBase_getLastError(
        GENBASE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

        //this->eRc = ERESULT_SUCCESS;
        return this->eRc;
    }


    bool            genBase_setLastError(
        GENBASE_DATA     *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //          L i b r a r y  I n c l u d e  P a t h
    //---------------------------------------------------------------
    
    ERESULT         genBase_setLibIncludePath(
        GENBASE_DATA    *this,
        PATH_DATA *     (*pLibIncludePath)(
                            GENBASE_DATA *,
                            const char *,
                            const char *,
                            const char *
                        )
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibIncludePath = pLibIncludePath;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          L i b r a r y  I n s t a l l e d  P a t h
    //---------------------------------------------------------------
    
    ERESULT         genBase_setLibInstalledPath(
        GENBASE_DATA    *this,
        PATH_DATA *     (*pLibInstalledPath)(
                             GENBASE_DATA *,
                             const char *,
                             const char *,
                             const char *
                        )
        )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibInstalledPath = pLibInstalledPath;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //          L i b r a r y  N a m e
    //---------------------------------------------------------------
    
    ERESULT         genBase_setLibName(
        GENBASE_DATA    *this,
        ASTR_DATA *     (*pLibName)(
                            GENBASE_DATA *,
                            const char *,
                            const char *
                        )
        )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        this->pLibName = pLibName;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }
    
    
    
    //---------------------------------------------------------------
    //                       M a k e  T y p e
    //---------------------------------------------------------------
    
    uint16_t        genBase_getMakeType(
        GENBASE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return this->makeType;
    }
    
    
    bool            genBase_setMakeType(
        GENBASE_DATA    *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->makeType = value;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //         S c a n n e d  D a t a b a s e  N o d e s
    //---------------------------------------------------------------
    
    NODE_DATA *     genBase_getNodes(
        GENBASE_DATA    *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return this->pNodes;
    }
    
    
    bool            genBase_setNodes(
        GENBASE_DATA    *this,
        NODE_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        obj_Retain(pValue);
        if (this->pNodes) {
            obj_Release(this->pNodes);
        }
        this->pNodes = pValue;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          P r i o r i t y
    //---------------------------------------------------------------
    
    uint16_t        genBase_getPriority(
        GENBASE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genBase_setLastError(this, ERESULT_SUCCESS);
        //return this->priority;
        return 0;
    }


    bool            genBase_setPriority(
        GENBASE_DATA     *this,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        //this->priority = value;

        genBase_setLastError(this, ERESULT_SUCCESS);
        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        genBase_getSize(
        GENBASE_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        genBase_setLastError(this, ERESULT_SUCCESS);
        return 0;
    }



    //---------------------------------------------------------------
    //                              S t r
    //---------------------------------------------------------------
    
    ASTR_DATA * genBase_getStr(
        GENBASE_DATA     *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return this->pStr;
    }
    
    
    bool        genBase_setStr(
        GENBASE_DATA     *this,
        ASTR_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif

        obj_Retain(pValue);
        if (this->pStr) {
            obj_Release(this->pStr);
        }
        this->pStr = pValue;
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  genBase_getSuperVtbl(
        GENBASE_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        genBase_setLastError(this, ERESULT_SUCCESS);
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
        ERESULT eRc = genBase__Assign(this,pOther);
     @endcode 
     @param     this    GENMAKE object pointer
     @param     pOther  a pointer to another GENMAKE object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         genBase_Assign(
        GENBASE_DATA		*this,
        GENBASE_DATA      *pOther
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !genBase_Validate(pOther) ) {
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
        genBase_setLastError(this, ERESULT_SUCCESS);
    eom:
        //FIXME: Implement the assignment.        
        genBase_setLastError(this, ERESULT_NOT_IMPLEMENTED);
        return genBase_getLastError(this);
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
    ERESULT         genBase_Compare(
        GENBASE_DATA     *this,
        GENBASE_DATA     *pOther
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
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if( !genBase_Validate(pOther) ) {
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
        
        this->eRc = eRc;
        return eRc;
    }
    
    
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        genBase      *pCopy = genBase_Copy(this);
     @endcode 
     @param     this    GENMAKE object pointer
     @return    If successful, a GENMAKE object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the GENMAKE object.
     */
    GENBASE_DATA *     genBase_Copy(
        GENBASE_DATA       *this
    )
    {
        GENBASE_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = genBase_New( );
        if (pOther) {
            eRc = genBase_Assign(this, pOther);
            if (ERESULT_HAS_FAILED(eRc)) {
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
        }
        
        // Return to caller.
        //obj_Release(pOther);
        this->eRc = ERESULT_SUCCESS;
        return pOther;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            genBase_Dealloc(
        OBJ_ID          objId
    )
    {
        GENBASE_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((GENMAKE_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        genBase_setDict(this, OBJ_NIL);
        genBase_setNodes(this, OBJ_NIL);
        genBase_setStr(this, OBJ_NIL);

        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super
        // object which we inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //             D i c t i o n a r y  M e t h o d s
    //---------------------------------------------------------------
    
    ERESULT         genBase_DictAdd(
        GENBASE_DATA    *this,
        const
        char            *pName,
        const
        char            *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (OBJ_NIL == this->pDict) {
            this->pDict = szHash_New(SZHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (szHash_FindA(this->pDict, pName)) {
            eRc = szHash_DeleteA(this->pDict, pName);
        }
        eRc = szHash_AddA(this->pDict, pName, (void *)pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                      D i s a b l e
    //---------------------------------------------------------------

    ERESULT         genBase_Disable(
        GENBASE_DATA    *this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        // Put code here...

        obj_Disable(this);
        
        // Return to caller.
        genBase_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //                          E n a b l e
    //---------------------------------------------------------------

    ERESULT         genBase_Enable(
        GENBASE_DATA    *this
    )
    {

        // Do initialization.
    #ifdef NDEBUG
    #else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        obj_Enable(this);

        // Put code here...
        
        // Return to caller.
        genBase_setLastError(this, ERESULT_SUCCESS);
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n c l u d e  P a t h
    //---------------------------------------------------------------
    
    /*!
     Library Include paths can be used for different purposes and
     can refer to different types of subdirectories. This requires
     dictionay entries for "LibIncludePath" and "LibIncludePrefix".
     */
    
    ASTR_DATA *     genBase_CFlagsLibIncludePath(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibIncludePath,
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        PATH_DATA       *pLib = OBJ_NIL;
        ASTR_DATA       *pFullName =  OBJ_NIL;

        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_CFlagsLibIncludePath(\"%s\", %s",
                pName
        );
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if (pLib) {
            return OBJ_NIL;
        }
        pLib = this->pLibIncludePath(this, pName, pLibIncludePath, pLibNamePrefix);
        if (pLib) {
            return OBJ_NIL;
        }
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }

        switch (this->makeType) {
                
            case GENMAKE_TYPE_MACOSX:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "CFLAGS += -I%s/src -I%s/src/$(SYS)\n",
                                         path_getData(pLib),
                                         path_getData(pLib)
                        );
                break;
                
            case GENMAKE_TYPE_MSC32:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "CFLAGS = $(CFLAGS) /I%s\\src /I%s\\src\\$(SYS)\n",
                                         path_getData(pLib),
                                         path_getData(pLib)
                        );
                break;
                
            default:
                break;
        }
        
        // Return to caller.
        genBase_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  O b j e c t  P a t h
    //---------------------------------------------------------------
    
    /*!
     Library Include paths can be used for different purposes and
     can refer to different types of subdirectories.
     */
    
    ASTR_DATA *     genBase_CFlagsLibObjectPath(
        GENBASE_DATA    *this,
        const
        char            *pName              // Library Name
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        char            *pLibObjectPath = NULL;
        char            *pLibObjectPrefix = NULL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_CFlagsLibObjectPath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        pLibObjectPath   = szHash_FindA(this->pDict, "LibObjectPath");
        if (NULL == pLibObjectPath) {
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibObjectPath=\"%s\"", pLibObjectPath);
        pLibObjectPrefix = szHash_FindA(this->pDict, "LibObjectPrefix");
        TRC_OBJ(this, "\tLibObjectPrefix=\"%s\"", (pLibObjectPrefix ? pLibObjectPrefix : ""));
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        switch (this->makeType) {
                
            case GENMAKE_TYPE_MACOSX:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "CFLAGS_LIBS += -l%s%s -L%s/%s%s\n",
                                         pLibObjectPrefix,
                                         pName,
                                         pLibObjectPath,
                                         (pLibObjectPrefix ? pLibObjectPrefix : ""),
                                         pName
                                         );
                break;
                
            case GENMAKE_TYPE_MSC32:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "LIBS = $(LIBS) "
                                         "$(INSTALL_BASE)\\%s%s\\%s%s.lib\n",
                                         (pLibObjectPrefix ? pLibObjectPrefix : ""),
                                         pName,
                                         (pLibObjectPrefix ? pLibObjectPrefix : ""),
                                         pName
                                         );
                break;
                
            default:
                break;
        }
        
        // Return to caller.
        genBase_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  O b j e c t  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     genBase_CompileObject(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Object Class Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_CompileObject(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return OBJ_NIL;
        }
#endif
        if (NULL == pSrcDir) {
            pSrcDir = "SRCDIR";
        }
        if (NULL == pObjDir) {
            pObjDir = "OBJDIR";
        }
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            return OBJ_NIL;
        }
        
        switch (this->makeType) {
                
            case GENMAKE_TYPE_MACOSX:
                if (0 == strcmp(pObjDir, "OBJDIR")) {
                    eRc =   AStr_AppendPrint(
                                             pStr,
                                             "OBJS += $(OBJDIR)/%s.o $(OBJDIR)/%s_object.o\n\n",
                                             pName,
                                             pName
                            );
                }
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "$(%s)/%s.o: $(%s)/%s.c\n\n",
                                         pObjDir,
                                         pName,
                                         pSrcDir,
                                         pName
                                         );
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                         pObjDir
                                         );
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "$(%s)/%s_object.o: $(%s)/%s_object.c\n",
                                         pObjDir,
                                         pName,
                                         pSrcDir,
                                         pName
                                         );
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n\n",
                                         pObjDir
                                         );
                break;
                
            case GENMAKE_TYPE_MSC32:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "OBJS = $(OBJS) $(%s)\\%s.obj $(%s)\\%s_object.obj\n",
                                         pObjDir,
                                         pName,
                                         pObjDir,
                                         pName
                                         );
                break;
                
            default:
                break;
        }
        
        // Return to caller.
        genBase_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  R o u t i n e  C o m p i l a t i o n
    //---------------------------------------------------------------
    
    ASTR_DATA *     genBase_CompileRoutine(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Object Class Name
        const
        char            *pSrcDir,
        const
        char            *pObjDir
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr =  OBJ_NIL;
        PATH_DATA       *pPath = OBJ_NIL;
        ASTR_DATA       *pFileName = OBJ_NIL;
        ASTR_DATA       *pFileExt = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_CompileRoutine(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            genBase_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        if (NULL == pSrcDir) {
            pSrcDir = "SRCDIR";
        }
        if (NULL == pObjDir) {
            pObjDir = "OBJDIR";
        }
        pPath = path_NewA(pName);
        if (OBJ_NIL == pStr) {
            genBase_setLastError(this, ERESULT_INVALID_PARAMETER);
            return OBJ_NIL;
        }
        eRc = path_SplitFile(pPath, &pFileName, &pFileExt);
        BREAK_NULL(pFileName);
        BREAK_NULL(pFileExt);
        pStr = AStr_New();
        if (OBJ_NIL == pStr) {
            obj_Release(pFileExt);
            pFileExt = OBJ_NIL;
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
            obj_Release(pPath);
            pPath = OBJ_NIL;
            genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        
        switch (this->makeType) {
                
            case GENMAKE_TYPE_MACOSX:
                if (AStr_CompareA(pFileExt, "c") == ERESULT_SUCCESS_EQUAL) {
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "$(%s)/%s.o: $(%s)/%s\n",
                                pObjDir,
                                AStr_getData(pFileName),
                                pSrcDir,
                                pName
                            );
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                pObjDir
                            );
                }
                else if (AStr_CompareA(pFileExt, "asm") == ERESULT_SUCCESS_EQUAL) {
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "$(%s)/%s.o: $(%s)/%s\n",
                                pObjDir,
                                AStr_getData(pFileName),
                                pSrcDir,
                                pName
                            );
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "\t$(AS) $(AFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                pObjDir
                            );
                }
                else if (AStr_CompareA(pFileExt, "s") == ERESULT_SUCCESS_EQUAL) {
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "$(%s)/%s.o: $(%s)/%s\n",
                                pObjDir,
                                AStr_getData(pFileName),
                                pSrcDir,
                                pName
                            );
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "\t$(AS) $(AFLAGS) -o $(%s)/$(@F) $<\n\n",
                                pObjDir
                            );
                }
                else if (AStr_CompareA(pFileExt, "cpp") == ERESULT_SUCCESS_EQUAL) {
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "$(%s)/%s.o: $(SRCDIR)/%s\n",
                                pObjDir,
                                AStr_getData(pFileName),
                                pSrcDir,
                                pName
                            );
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "\t$(CC) $(CFLAGS) -c -o $(%s)/$(@F) $<\n\n",
                                pObjDir
                            );
                }
                else {
                    obj_Release(pFileExt);
                    pFileExt = OBJ_NIL;
                    obj_Release(pFileName);
                    pFileName = OBJ_NIL;
                    obj_Release(pPath);
                    pPath = OBJ_NIL;
                    obj_Release(pStr);
                    pStr = OBJ_NIL;
                    genBase_setLastError(this, ERESULT_INVALID_PARAMETER);
                    return OBJ_NIL;
                }
                if (0 == strcmp(pObjDir, "OBJDIR")) {
                    eRc =   AStr_AppendPrint(
                                pStr,
                                "OBJS += $(%s)/%s.o\n\n",
                                pObjDir,
                                pFileName
                            );
                }
                break;
                
            case GENMAKE_TYPE_MSC32:
#ifdef XYZZY
                iMax = nodeArray_getSize(pRoutines);
                for (i=0; i<iMax; ++i) {
                    pNode = nodeArray_Get(pRoutines, i+1);
                    if (pNode) {
                        ASTR_DATA       *pWrk;
                        pStr = node_getData(pNode);
                        pWrk = AStr_Copy(pStr);
                        if (AStr_CompareRightA(pWrk, ".c") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        else if (AStr_CompareRightA(pWrk, ".asm") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                        }
                        else if (AStr_CompareRightA(pWrk, ".s") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 2));
                        }
                        else if (AStr_CompareRightA(pWrk, ".cpp") == ERESULT_SUCCESS_EQUAL) {
                            AStr_Truncate(pWrk, (AStr_getLength(pWrk) - 4));
                        }
                        fprintf(
                                pResults->pOutput,
                                "OBJS = $(OBJS) $(OBJDIR)\\%s.obj\n",
                                AStr_getData(pWrk)
                                );
                        
                        obj_Release(pWrk);
                    }
                }
        }
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "{src}.asm{$(OBJDIR)}.obj:\n");
        fprintf(pResults->pOutput, "\t$(AS) $(AFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "{src}.c{$(OBJDIR)}.obj:\n");
        fprintf(pResults->pOutput, "\t$(CC) $(CFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "{src\\$(SYS)}.asm{$(OBJDIR)}.obj:\n");
        fprintf(pResults->pOutput, "\t$(AS) $(AFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "{src\\$(SYS)}.c{$(OBJDIR)}.obj:\n");
        fprintf(pResults->pOutput, "\t$(CC) $(CFLAGS) /c /Fo$(OBJDIR)\\$(@F) $<\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
        fprintf(pResults->pOutput, "\n");
#endif
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "OBJS = $(OBJS) $(%s)\\%s.obj $(%s)\\%s_object.obj\n",
                                         pObjDir,
                                         pName,
                                         pObjDir,
                                         pName
                                         );
                break;
        
            default:
                break;
        }
    
        // Return to caller.
        obj_Release(pFileExt);
        pFileExt = OBJ_NIL;
        obj_Release(pFileName);
        pFileName = OBJ_NIL;
        obj_Release(pPath);
        pPath = OBJ_NIL;
        genBase_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }



//---------------------------------------------------------------
//  G e n e r a t e  C o m p i l a t i o n  R u l e s
//---------------------------------------------------------------

ASTR_DATA *     genBase_CompileRules(
    GENBASE_DATA    *this,
    const
    char            *pSrcDir,
    const
    char            *pObjDir
)
{
    ERESULT         eRc;
    ASTR_DATA       *pStr =  OBJ_NIL;
    
    // Do initialization.
    TRC_OBJ(this, "genBase_CompileRules( )");
#ifdef NDEBUG
#else
    if( !genBase_Validate(this) ) {
        DEBUG_BREAK();
        //return ERESULT_INVALID_OBJECT;
        genBase_setLastError(this, ERESULT_INVALID_OBJECT);
        return OBJ_NIL;
    }
#endif
    if (NULL == pSrcDir) {
        pSrcDir = "SRCDIR";
    }
    if (NULL == pObjDir) {
        pObjDir = "OBJDIR";
    }
    pStr = AStr_New();
    if (OBJ_NIL == pStr) {
        genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
        return OBJ_NIL;
    }
    
    switch (this->makeType) {
            
        case GENMAKE_TYPE_MACOSX:
            break;
            
        case GENMAKE_TYPE_MSC32:
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{src}.asm{$(%s)}.obj:\n",
                        pObjDir
                    );
            eRc =   AStr_AppendPrint(
                        pStr,
                        "\t$(AS) $(AFLAGS) /c /Fo$(%s)\\$(@F) $<\n\n\n",
                        pObjDir
                    );
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{src}.c{$(%s)}.obj:\n",
                        pObjDir
                    );
            eRc =   AStr_AppendPrint(
                        pStr,
                        "\t$(CC) $(CFLAGS) /c /Fo$(%s)\\$(@F) $<\n\n\n",
                        pObjDir
                    );
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{src\\$(SYS)}.asm{$(%s)}.obj:\n",
                        pObjDir
                    );
            eRc =   AStr_AppendPrint(
                        pStr,
                        "\t$(AS) $(AFLAGS) /c /Fo$(%s)\\$(@F) $<\n\n\n",
                        pObjDir
                    );
            eRc =   AStr_AppendPrint(
                        pStr,
                        "{src\\$(SYS)}.c{$(%s)}.obj:\n",
                        pObjDir
                    );
            eRc =   AStr_AppendPrint(
                        pStr,
                        "\t$(CC) $(CFLAGS) /c /Fo$(%s)\\$(@F) $<\n\n\n",
                        pObjDir
                    );
            break;
    
        default:
            break;
    }

    // Return to caller.
    genBase_setLastError(this, ERESULT_SUCCESS);
    return pStr;
}



//---------------------------------------------------------------
//              G e n e r a t e  M a k e f i l e
//---------------------------------------------------------------

ERESULT         genBase_GenMakefile(
    GENBASE_DATA        *this
)
{
    ERESULT             eRc;
    NODE_DATA           *pNode;
    NODEARRAY_DATA      *pLibDeps = OBJ_NIL;
    NODEHASH_DATA       *pPrimaryHash = OBJ_NIL;
    NODEHASH_DATA       *pObjects = OBJ_NIL;
    NODEHASH_DATA       *pPrograms = OBJ_NIL;
    NODEARRAY_DATA      *pRoutines = OBJ_NIL;
    NODEHASH_DATA       *pTests = OBJ_NIL;
    NODEHASH_DATA       *pMacosx = OBJ_NIL;
    NODEHASH_DATA       *pWin32 = OBJ_NIL;
    ASTR_DATA           *pName = OBJ_NIL;

    // Do initialization.
#ifdef NDEBUG
#else
    if( !genBase_Validate(this) ) {
        DEBUG_BREAK();
        return ERESULT_INVALID_OBJECT;
    }
#endif
    
    pPrimaryHash = node_getData(this->pNodes);
    BREAK_FALSE((obj_IsKindOf(pPrimaryHash, OBJ_IDENT_NODEHASH)));
    if (pPrimaryHash) {
        pNode = nodeHash_FindA(pPrimaryHash, "name");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pName = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pName, OBJ_IDENT_ASTR)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "lib_deps");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pLibDeps = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pLibDeps, OBJ_IDENT_NODEARRAY)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "objects");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pObjects = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pObjects, OBJ_IDENT_NODEHASH)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "routines");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pRoutines = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pRoutines, OBJ_IDENT_NODEARRAY)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "programs");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pPrograms = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pPrograms, OBJ_IDENT_NODEHASH)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "tests");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pTests = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pTests, OBJ_IDENT_NODEHASH)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "macosx");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pMacosx = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pMacosx, OBJ_IDENT_NODEHASH)));
        }
        pNode = nodeHash_FindA(pPrimaryHash, "win32");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            pWin32 = node_getData(pNode);
            BREAK_FALSE((obj_IsKindOf(pWin32, OBJ_IDENT_NODEHASH)));
        }
    }
    
    if (this->pInitial) {
        eRc = this->pInitial(this, pName, pLibDeps);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            exit(99);
        }
    }

    if (this->pObjects) {
        eRc = this->pObjects(this, pObjects, pRoutines);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            exit(99);
        }
    }

#ifdef XYZZY
    switch (this->makeType) {
            
        case MAKETYPE_MACOSX:
            if (pMacosx) {
                genMakeFile_macosx(pResults, pMacosx);
            }
            break;
            
        case MAKETYPE_MSC32:
            if (pWin32) {
                genMakeFile_win32(pResults, pWin32);
            }
            break;
            
        default:
            break;
    }
#endif
    
    if (this->pLibrary) {
        eRc = this->pLibrary(this);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            exit(99);
        }
    }
    
    if (this->pPrograms && pPrograms) {
        eRc = this->pPrograms(this, pPrograms);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            exit(99);
        }
    }
    
    if (this->pTests) {
        eRc = this->pTests(this, pTests);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            exit(99);
        }
    }
    
    if (this->pFinal) {
        eRc = this->pFinal(this);
        if (ERESULT_FAILED(eRc)) {
            DEBUG_BREAK();
            exit(99);
        }
    }

    // Return to caller.
    genBase_setLastError(this, ERESULT_SUCCESS_FALSE);
    return ERESULT_SUCCESS_FALSE;
}



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    GENBASE_DATA *   genBase_Init(
        GENBASE_DATA    *this
    )
    {
        uint32_t        cbSize = sizeof(GENBASE_DATA);
        
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
        this = (OBJ_ID)obj_Init(this, cbSize, MAIN_IDENT_GENBASE);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        //obj_setIdent((OBJ_ID)this, OBJ_IDENT_GENMAKE);         // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&genBase_Vtbl);
        
        genBase_setLastError(this, ERESULT_GENERAL_FAILURE);
        this->pLibIncludePath = genBase_LibIncludePath;
        this->pLibName = genBase_LibName;
        
    #ifdef NDEBUG
    #else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef __APPLE__
        //fprintf(stderr, "genBase::offsetof(eRc) = %lu\n", offsetof(GENBASE_DATA,eRc));
        //fprintf(stderr, "genBase::sizeof(GENBASE_DATA) = %lu\n", sizeof(GENBASE_DATA));
#endif
        BREAK_NOT_BOUNDARY4(&this->eRc);
        BREAK_NOT_BOUNDARY4(sizeof(GENBASE_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         genBase_IsEnabled(
        GENBASE_DATA		*this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        if (obj_IsEnabled(this)) {
            genBase_setLastError(this, ERESULT_SUCCESS_TRUE);
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
        genBase_setLastError(this, ERESULT_SUCCESS_FALSE);
        return ERESULT_SUCCESS_FALSE;
    }
    
    
    
    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n c l u d e  P a t h
    //---------------------------------------------------------------

    /*!
     Generate the Library Path given a name, the libraries super
     directory and an optional prefix.  The library super directory
     and optional library prefix name can either be supplied as a
     parameter of the method or they can be provided by the internal
     dictionary.  The dictionary will be accessed for "LibIncludePath"
     or "LibNamePrefix" if their respective method parameter is NULL.
     The diotionary entries for either can be over-ridden by passing
     "" instead of NULL.
     @param     this    object pointer
     @param     pName   library name
     @param     pLibIncludePath Optional directory which contains the
                        library.  If NULL, then "LibIncludePath" must
                        be present in the dictionary.
     @param     pLibNamePrefix  Optional prefix to the library name
                        such as "lib".  If NULL, then "LibNamePrefix"
                        will be used if present in the dictionary.
     */

    PATH_DATA *     genBase_LibIncludePath(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibIncludePath,
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        PATH_DATA       *pPath =  OBJ_NIL;
        ASTR_DATA       *pFullName = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_LibIncludePath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            genBase_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibIncludePath) && this->pDict) {
            pLibIncludePath = szHash_FindA(this->pDict, "LibIncludePath");
        }
        TRC_OBJ(this, "\tLibIncludePath=\"%s\"", (pLibIncludePath ? pLibIncludePath : ""));

        if (pLibIncludePath) {
            pPath = path_NewA(pLibIncludePath);
            if (OBJ_NIL == pPath) {
                genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }

        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        genBase_setLastError(this, eRc);
        return pPath;
    }



    //---------------------------------------------------------------
    //  G e n e r a t e  L i b r a r y  I n s t a l l e d  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     genBase_LibInstalledPath(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibInstalledPath,
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        PATH_DATA       *pPath =  OBJ_NIL;
        ASTR_DATA       *pFullName = OBJ_NIL;
        
        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_LibInstalledPath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            genBase_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibInstalledPath) && this->pDict) {
            pLibInstalledPath = szHash_FindA(this->pDict, "LibInstalledPath");
        }
        TRC_OBJ(this, "\tLibInstalledPath=\"%s\"", (pLibInstalledPath ? pLibInstalledPath : ""));
        
        if (pLibInstalledPath) {
            pPath = path_NewA(pLibInstalledPath);
            if (OBJ_NIL == pPath) {
                genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                genBase_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        genBase_setLastError(this, eRc);
        return pPath;
    }



    //---------------------------------------------------------------
    //  G e n e r a t e  t h e  f u l l  L i b r a r y  N a m e
    //---------------------------------------------------------------

    ASTR_DATA *     genBase_LibName(
        GENBASE_DATA    *this,
        const
        char            *pName,             // Library Name
        const
        char            *pLibNamePrefix
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pFullName = OBJ_NIL;

        // Do initialization.
        TRC_OBJ(
                this,
                "genBase_LibIncludePath(\"%s\", %s",
                pName
                );
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            genBase_setLastError(this, ERESULT_INVALID_OBJECT);
            return OBJ_NIL;
        }
#endif
        if ((OBJ_NIL == pLibNamePrefix) && this->pDict) {
            pLibNamePrefix = szHash_FindA(this->pDict, "LibNamePrefix");
        }
        TRC_OBJ(this, "\tLibNamePrefix=\"%s\"", (pLibNamePrefix ? pLibNamePrefix : ""));
        
        if (pLibNamePrefix) {
            pFullName = AStr_NewA(pLibNamePrefix);
            if (OBJ_NIL == pFullName) {
                genBase_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
            eRc = AStr_AppendA(pFullName, pName);
        }
        else {
            pFullName = AStr_NewA(pName);
            if (OBJ_NIL == pFullName) {
                genBase_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        genBase_setLastError(this, ERESULT_SUCCESS);
        return pFullName;
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
        void        *pMethod = genBase_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "genBase", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          genBase_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        GENBASE_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)genBase_Class();
                break;
                
#ifdef XYZZY  
        // Query for an address to specific data within the object.  
        // This should be used very sparingly since it breaks the 
        // object's encapsulation.                 
        case OBJ_QUERYINFO_TYPE_DATA_PTR:
            switch (*pStr) {
 
                case 'S':
                    if (str_Compare("SuperVtbl", (char *)pStr) == 0) {
                        return &this->pSuperVtbl;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
#endif
             case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)obj_getInfo(this);
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return genBase_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return genBase_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return genBase_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return genBase_ToJSON;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == genBase_ToDebugString)
                    return "ToDebugString";
                if (pData == genBase_ToJSON)
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
        ASTR_DATA      *pDesc = genBase_ToDebugString(this,4);
     @endcode 
     @param     this    GENMAKE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     genBase_ToDebugString(
        GENBASE_DATA      *this,
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
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
              
        pInfo = genBase_Vtbl.iVtbl.pInfo;
        pStr = AStr_New();
        if (indent) {
            AStr_AppendCharRepeatA(pStr, indent, ' ');
        }
        eRc = AStr_AppendPrint(
                    pStr,
                    "{%p(%s) size=%d\n",
                    this,
                    pInfo->pClassName,
                    genBase_getSize(this)
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
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    ASTR_DATA *     genBase_ToJSON(
        GENBASE_DATA      *this
    )
    {
        ERESULT         eRc;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
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
        
        genBase_setLastError(this, ERESULT_SUCCESS);
        return pStr;
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            genBase_Validate(
        GENBASE_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if( this ) {
            if ( obj_IsKindOf(this, MAIN_IDENT_GENBASE) )
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


        if( !(obj_getSize(this) >= sizeof(GENBASE_DATA)) ) {
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


