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
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                  D i c t i o n a r y
    //---------------------------------------------------------------
    
    NODEHASH_DATA * genBase_getDict(
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
        
        return this->pDict;
    }
    
    
    bool            genBase_setDict(
        GENBASE_DATA    *this,
        NODEHASH_DATA   *pValue
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
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      L i b D e p s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * genBase_getLibDeps(
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
        
        return this->pLibDeps;
    }
    
    
    bool            genBase_setLibDeps(
        GENBASE_DATA    *this,
        NODEARRAY_DATA  *pValue
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
        if (this->pLibDeps) {
            obj_Release(this->pLibDeps);
        }
        this->pLibDeps = pValue;
        
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
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                          N a m e
    //---------------------------------------------------------------
    
    ASTR_DATA *     genBase_getName(
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
        
        return this->pName;
    }
    
    
    bool            genBase_setName(
        GENBASE_DATA    *this,
        ASTR_DATA       *pValue
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
        if (this->pName) {
            obj_Release(this->pName);
        }
        this->pName = pValue;
        
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
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O b j  D i r s
    //---------------------------------------------------------------
    
    NODEHASH_DATA * genBase_getObjDirs(
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
        
        return this->pObjDirs;
    }
    
    
    bool            genBase_setObjDirs(
        GENBASE_DATA    *this,
        NODEHASH_DATA   *pValue
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
        if (this->pObjDirs) {
            obj_Release(this->pObjDirs);
        }
        this->pObjDirs = pValue;
        
        return true;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O b j e c t s
    //---------------------------------------------------------------
    
    NODEHASH_DATA * genBase_getObjects(
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
        
        return this->pObjects;
    }
    
    
    
    //---------------------------------------------------------------
    //                      O u t p u t
    //---------------------------------------------------------------
    
    TEXTOUT_DATA *  genBase_getOutput(
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
        
        return this->pOutput;
    }
    

    bool            genBase_setOutput(
        GENBASE_DATA    *this,
        TEXTOUT_DATA    *pValue
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
        if (this->pOutput) {
            obj_Release(this->pOutput);
        }
        this->pOutput = pValue;
        
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

        return true;
    }



    //---------------------------------------------------------------
    //                      P r o g r a m s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * genBase_getPrograms(
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
        
        return this->pPrograms;
    }

    
    
    //---------------------------------------------------------------
    //                      R o u t i n e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * genBase_getRoutines(
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
        
        return this->pRoutines;
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

        return 0;
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

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                      T e s t s
    //---------------------------------------------------------------
    
    NODEHASH_DATA * genBase_getTests(
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
        
        return this->pTests;
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
        GENBASE_DATA	*this,
        GENBASE_DATA    *pOther
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
        genBase      *pCopy = genBase_Copy(this);
     @endcode 
     @param     this    GENMAKE object pointer
     @return    If successful, a GENMAKE object which must be released,
                otherwise OBJ_NIL.
     @warning  Remember to release the returned the GENMAKE object.
     */
    GENBASE_DATA *  genBase_Copy(
        GENBASE_DATA    *this
    )
    {
        GENBASE_DATA    *pOther = OBJ_NIL;
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

        genBase_setDateTime(this, OBJ_NIL);
        genBase_setDict(this, OBJ_NIL);
        genBase_setNodes(this, OBJ_NIL);
        genBase_setObjDirs(this, OBJ_NIL);
        genBase_setOutput(this, OBJ_NIL);

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
    
    ERESULT         genBase_DictAddUpdate(
        GENBASE_DATA    *this,
        const
        char            *pName,
        OBJ_ID          pData
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
            this->pDict = nodeHash_New(NODEHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (nodeHash_FindA(this->pDict, pName)) {
            eRc = nodeHash_DeleteA(this->pDict, pName);
        }
        eRc = nodeHash_AddA(this->pDict, pName, 0, (void *)pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    ERESULT         genBase_DictAddUpdateA(
        GENBASE_DATA    *this,
        const
        char            *pName,
        const
        char            *pData
    )
    {
        ERESULT         eRc;
        ASTR_DATA       *pStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        pStr = AStr_NewA(pData);
        if (OBJ_NIL == pStr) {
            return ERESULT_OUT_OF_MEMORY;
        }

        if (OBJ_NIL == this->pDict) {
            this->pDict = nodeHash_New(NODEHASH_TABLE_SIZE_SMALL);
            if (OBJ_NIL == this->pDict) {
                DEBUG_BREAK();
                return ERESULT_OUT_OF_MEMORY;
            }
        }
        
        if (nodeHash_FindA(this->pDict, pName)) {
            eRc = nodeHash_DeleteA(this->pDict, pName);
        }
        eRc = nodeHash_AddA(this->pDict, pName, 0, (void *)pData);
        
        // Return to caller.
        obj_Release(pStr);
        pStr = OBJ_NIL;
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
        return ERESULT_SUCCESS;
    }



    //---------------------------------------------------------------
    //     E x p a n d  E n v i r o n m e n t  V a r i a b l e s
    //---------------------------------------------------------------
    
    /*!
     Substitute environment variables into the current string using a BASH-like
     syntax.  Variable names should have the syntax of:
     '$' '{'[a-zA-Z_][a-zA-Z0-9_]* '}'.
     Substitutions are not rescanned after insertion.
     @param     this    object pointer
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_* error code
     is returned.
     */
    ERESULT         genBase_ExpandDict(
        GENBASE_DATA    *this,
        ASTR_DATA       *pStr
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
        NODE_DATA       *pVar = OBJ_NIL;
        const
        char            *pEnvVar = NULL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if(!genBase_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if(OBJ_NIL == pStr) {
            DEBUG_BREAK();
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (0 == AStr_getLength(pStr)) {
            return ERESULT_SUCCESS;
        }
        
        // Expand Environment variables.
        while (fMore) {
            fMore = false;
            eRc = AStr_CharFindNextW32(pStr, &i, '$');
            if (ERESULT_FAILED(eRc)) {
                break;
            }
            else {
                chr = AStr_CharGetW32(pStr, i+1);
                if (chr == '{') {
                    i += 2;
                    j = i;
                    eRc = AStr_CharFindNextW32(pStr, &j, '}');
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_PARSE_ERROR;
                    }
                    len = j - i;
                    eRc = AStr_Mid(pStr, i, len, &pName);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    
                    // Find the name from the Dictionary.
                    pVar = nodeHash_FindA(this->pDict, AStr_getData(pName));
                    if (OBJ_NIL == pVar) {
                        obj_Release(pName);
                        return ERESULT_DATA_NOT_FOUND;
                    }
                    obj_Release(pName);
                    pName = OBJ_NIL;
                    //FIXME: Get pEnvVar from node data
                    
                    // Substitute the name from the Dictionary.
                    eRc = AStr_Remove(pStr, i-2, len+3);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    eRc = AStr_InsertA(pStr, i-2, pEnvVar);
                    if (ERESULT_FAILED(eRc)) {
                        return ERESULT_OUT_OF_MEMORY;
                    }
                    pEnvVar = NULL;
                    fMore = true;
                }
                else if (chr == '$') {
                    eRc = AStr_Remove(pStr, i, 1);
                    ++i;
                    fMore = true;
                    continue;
                }
                else {
                    return ERESULT_PARSE_ERROR;
                }
            }
        }
        
        // Return to caller.
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
                
            case GENMAKE_OS_MACOSX:
                eRc =   AStr_AppendPrint(
                                         pStr,
                                         "CFLAGS += -I%s/src -I%s/src/$(SYS)\n",
                                         path_getData(pLib),
                                         path_getData(pLib)
                        );
                break;
                
            case GENMAKE_OS_MSC32:
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
        
        //FIXME: get data To_String ??? or To_PATH ????
#ifdef XYZZY
        pLibObjectPath   = nodeHash_FindA(this->pDict, "LibObjectPath");
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
                
            case GENMAKE_OS_MACOSX:
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
                
            case GENMAKE_OS_MSC32:
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
#endif
        
        // Return to caller.
        return pStr;
    }
    
    
    
//---------------------------------------------------------------
//         G e n e r a t e  F i n a l
//---------------------------------------------------------------

ERESULT         genBase_GenFinal(
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
    
    //obj_Enable(this);
    
    // Put code here...
    
    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//         G e n e r a t e  I n i t i a l  D a t a
//---------------------------------------------------------------

ASTR_DATA *     genBase_GenInitial(
    GENBASE_DATA    *this
)
{
    ASTR_DATA       *pStr = OBJ_NIL;
    
    // Do initialization.
#ifdef NDEBUG
#else
    if( !genBase_Validate(this) ) {
        DEBUG_BREAK();
        return pStr;
    }
#endif
    
    //obj_Enable(this);
    
    // Put code here...
    
    // Return to caller.
    return pStr;
}



//---------------------------------------------------------------
//         G e n e r a t e  L i b r a r y
//---------------------------------------------------------------

ERESULT         genBase_GenLibrary(
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
    
    //obj_Enable(this);
    
    // Put code here...
    
    // Return to caller.
    return ERESULT_SUCCESS;
}



ERESULT         genBase_GenObjects(
    GENBASE_DATA    *this
)
{
    ERESULT         eRc;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray =  OBJ_NIL;
    int             i;
    int             iMax;

    // Do initialization.
#ifdef NDEBUG
#else
    if( !genBase_Validate(this) ) {
        DEBUG_BREAK();
        return ERESULT_INVALID_OBJECT;
    }
#endif
    
    if (this->pObjects) {
        pArray = nodeHash_Nodes(this->pObjects);
        if (OBJ_NIL == pArray) {
        }
        else {
            BREAK_FALSE((obj_IsKindOf(pArray, OBJ_IDENT_NODEARRAY)));
            iMax = nodeArray_getSize(pArray);
            for (i=0; i<iMax; ++i) {
                pNode = nodeArray_Get(pArray, i+1);
                if (pNode) {
                    eRc = ((GENBASE_VTBL *)obj_getVtbl(this))->pGenObject(this, pNode);
                    if (ERESULT_FAILED(eRc)) {
                        DEBUG_BREAK();
                        exit(102);
                    }
                    
                }
            }
        }
    }
    
    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//         G e n e r a t e  O / S  S p e c i f i c
//---------------------------------------------------------------

ERESULT         genBase_GenOSSpecific(
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
    
    //obj_Enable(this);
    
    // Put code here...
    
    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//         G e n e r a t e   P r o g r a m s
//---------------------------------------------------------------

ERESULT         genBase_GenPrograms(
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
    
    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//         G e n e r a t e   R o u t i n e s
//---------------------------------------------------------------

ERESULT         genBase_GenRoutines(
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
    
    //obj_Enable(this);
    
    // Put code here...
    
    // Return to caller.
    return ERESULT_SUCCESS;
}



//---------------------------------------------------------------
//         G e n e r a t e  T e s t s
//---------------------------------------------------------------

ERESULT         genBase_GenTests(
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
    
    //obj_Enable(this);
    
    // Put code here...
    
    // Return to caller.
    return ERESULT_SUCCESS;
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
        //obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
        return OBJ_NIL;
    }
    
    switch (this->makeType) {
            
        case GENMAKE_OS_MACOSX:
            break;
            
        case GENMAKE_OS_MSC32:
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
    return pStr;
}



//---------------------------------------------------------------
//              G e n e r a t e  M a k e f i l e
//---------------------------------------------------------------

ERESULT         genBase_GenMakefile(
    GENBASE_DATA        *this,
    NODE_DATA           *pNodes,
    NODEHASH_DATA       *pDict,
    DATETIME_DATA       *pDateTime,
    TEXTOUT_DATA        *pOutput
)
{
    ERESULT             eRc;
    NODE_DATA           *pNode;
    NODEHASH_DATA       *pPrimaryHash = OBJ_NIL;

    // Do initialization.
#ifdef NDEBUG
#else
    if( !genBase_Validate(this) ) {
        DEBUG_BREAK();
        return ERESULT_INVALID_OBJECT;
    }
#endif
    genBase_setDateTime(this, pDateTime);
    genBase_setDict(this, pDict);
    genBase_setNodes(this, pNodes);
    genBase_setOutput(this, pOutput);

    pPrimaryHash = node_getData(pNodes);
    BREAK_FALSE((obj_IsKindOf(pPrimaryHash, OBJ_IDENT_NODEHASH)));
    if (pPrimaryHash) {
        pNode = nodeHash_FindA(pPrimaryHash, "name");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            this->pName = node_getData(pNode);
            if (obj_IsKindOf(this->pName, OBJ_IDENT_NULL)) {
                this->pName = OBJ_NIL;
            }
            else if (obj_IsKindOf(this->pName, OBJ_IDENT_ASTR)) {
            }
            else {
                DEBUG_BREAK();
            }
        }
        pNode = nodeHash_FindA(pPrimaryHash, "deps");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            this->pLibDeps = node_getData(pNode);
            if (obj_IsKindOf(this->pLibDeps, OBJ_IDENT_NULL)) {
                this->pLibDeps = OBJ_NIL;
            }
            else if (obj_IsKindOf(this->pLibDeps, OBJ_IDENT_NODEARRAY)) {
            }
            else {
                DEBUG_BREAK();
            }
        }
        pNode = nodeHash_FindA(pPrimaryHash, "objects");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            this->pObjects = node_getData(pNode);
            if (obj_IsKindOf(this->pObjects, OBJ_IDENT_NULL)) {
                this->pObjects = OBJ_NIL;
            }
            else if (obj_IsKindOf(this->pObjects, OBJ_IDENT_NODEHASH)) {
            }
            else {
                DEBUG_BREAK();
            }
        }
        pNode = nodeHash_FindA(pPrimaryHash, "routines");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            this->pRoutines = node_getData(pNode);
            if (obj_IsKindOf(this->pRoutines, OBJ_IDENT_NULL)) {
                this->pRoutines = OBJ_NIL;
            }
            else if (obj_IsKindOf(this->pRoutines, OBJ_IDENT_NODEARRAY)) {
            }
            else {
                DEBUG_BREAK();
            }
        }
        pNode = nodeHash_FindA(pPrimaryHash, "programs");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            this->pPrograms = node_getData(pNode);
            if (obj_IsKindOf(this->pPrograms, OBJ_IDENT_NULL)) {
                this->pPrograms = OBJ_NIL;
            }
            else if (obj_IsKindOf(this->pPrograms, OBJ_IDENT_NODEHASH)) {
            }
            else {
                DEBUG_BREAK();
            }
        }
        pNode = nodeHash_FindA(pPrimaryHash, "tests");
        if (NULL == pNode) {
        }
        else {
            pNode = node_getData(pNode);
            this->pTests = node_getData(pNode);
            if (obj_IsKindOf(this->pTests, OBJ_IDENT_NULL)) {
                this->pTests = OBJ_NIL;
            }
            else if (obj_IsKindOf(this->pTests, OBJ_IDENT_NODEHASH)) {
            }
            else {
                DEBUG_BREAK();
            }
        }
        //TODO: Find O/S Specific data.
    }
    
    eRc = ((GENBASE_VTBL *)obj_getVtbl(this))->pGenInitial(this);
    if (ERESULT_FAILED(eRc)) {
        DEBUG_BREAK();
        exit(100);
    }

    eRc = ((GENBASE_VTBL *)obj_getVtbl(this))->pGenObjects(this);
    if (ERESULT_FAILED(eRc)) {
        DEBUG_BREAK();
        exit(101);
    }
    
    eRc = ((GENBASE_VTBL *)obj_getVtbl(this))->pGenRoutines(this);
    if (ERESULT_FAILED(eRc)) {
        DEBUG_BREAK();
        exit(102);
    }
    
    eRc = ((GENBASE_VTBL *)obj_getVtbl(this))->pGenTests(this);
    if (ERESULT_FAILED(eRc)) {
        DEBUG_BREAK();
        exit(102);
    }
    
    eRc = ((GENBASE_VTBL *)obj_getVtbl(this))->pGenPrograms(this);
    if (ERESULT_FAILED(eRc)) {
        DEBUG_BREAK();
        exit(102);
    }

    eRc = ((GENBASE_VTBL *)obj_getVtbl(this))->pGenFinal(this);
    if (ERESULT_FAILED(eRc)) {
        DEBUG_BREAK();
        exit(102);
    }
    
    // Return to caller.
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
            return ERESULT_SUCCESS_TRUE;
        }
        
        // Return to caller.
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
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibIncludePath) && this->pDict) {
            //FIXME: pLibIncludePath = szHash_FindA(this->pDict, "LibIncludePath");
        }
        TRC_OBJ(this, "\tLibIncludePath=\"%s\"", (pLibIncludePath ? pLibIncludePath : ""));

        if (pLibIncludePath) {
            pPath = path_NewA(pLibIncludePath);
            if (OBJ_NIL == pPath) {
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }

        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
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
        NODE_DATA       *pNode = OBJ_NIL;
        
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
            return OBJ_NIL;
        }
#endif
        pFullName = this->pLibName(this, pName, pLibNamePrefix);
        if ( OBJ_NIL == pFullName) {
            obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
            return OBJ_NIL;
        }
        TRC_OBJ(this, "\tLibName=\"%s\"", AStr_getData(pFullName));
        if ((OBJ_NIL == pLibInstalledPath) && this->pDict) {
            pNode = nodeHash_FindA(this->pDict, "LibInstalledPath");
            pLibInstalledPath = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibInstalledPath=\"%s\"", (pLibInstalledPath ? pLibInstalledPath : ""));
        
        if (pLibInstalledPath) {
            pPath = path_NewA(pLibInstalledPath);
            if (OBJ_NIL == pPath) {
                obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = path_AppendDirA(pPath, AStr_getData(pFullName));
        }
        else {
            pPath = path_NewA(AStr_getData(pFullName));
            if (OBJ_NIL == pPath) {
                obj_setLastError(this, ERESULT_OUT_OF_MEMORY);
                return OBJ_NIL;
            }
            eRc = ERESULT_SUCCESS;
        }
        
        // Return to caller.
        obj_Release(pFullName);
        pFullName = OBJ_NIL;
        obj_setLastError(this, eRc);
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
        NODE_DATA       *pNode = OBJ_NIL;

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
            return OBJ_NIL;
        }
#endif
        if ((OBJ_NIL == pLibNamePrefix) && this->pDict) {
            pNode = nodeHash_FindA(genBase_getDict((GENBASE_DATA *)this), "LibNamePrefix");
            pLibNamePrefix = AStr_getData(node_getData(pNode));
        }
        TRC_OBJ(this, "\tLibNamePrefix=\"%s\"", (pLibNamePrefix ? pLibNamePrefix : ""));
        
        if (pLibNamePrefix) {
            pFullName = AStr_NewA(pLibNamePrefix);
            if (OBJ_NIL == pFullName) {
                obj_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
            eRc = AStr_AppendA(pFullName, pName);
        }
        else {
            pFullName = AStr_NewA(pName);
            if (OBJ_NIL == pFullName) {
                obj_setLastError(this, ERESULT_GENERAL_FAILURE);
                return OBJ_NIL;
            }
        }
        
        // Return to caller.
        obj_setLastError(this, ERESULT_SUCCESS);
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
    //  G e n e r a t e  t h e  f u l l  L i b r a r y  N a m e
    //---------------------------------------------------------------
    
    /*!
     Take the dictionary entries from the defaults and over-rides to
     create base directories and file paths needed to build the
     library or program.
     @return    ERESULT_SUCCESS if successful.  Otherwise, an ERESULT_*
                error code is returned.
     */
    ERESULT         genBase_SetupDictionary(
        GENBASE_DATA    *this
    )
    {
        ERESULT         eRc = ERESULT_SUCCESS;
        ASTR_DATA       *pStr = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !genBase_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif

#ifdef xyzzz
        if ((OBJ_NIL == pLibNamePrefix) && this->pDict) {
            pLibNamePrefix = szHash_FindA(this->pDict, "LibNamePrefix");
        }
        TRC_OBJ(this, "\tLibNamePrefix=\"%s\"", (pLibNamePrefix ? pLibNamePrefix : ""));
        
        if (pLibNamePrefix) {
            pFullName = AStr_NewA(pLibNamePrefix);
            if (OBJ_NIL == pFullName) {
                return ERESULT_GENERAL_FAILURE;
            }
            eRc = AStr_AppendA(pFullName, pName);
        }
        else {
            pFullName = AStr_NewA(pName);
            if (OBJ_NIL == pFullName) {
                return ERESULT_GENERAL_FAILURE;
            }
        }
#endif
        
        
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
              
        pInfo = obj_getInfo(this);
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
        
        return pStr;
    }
    
    
    
    ASTR_DATA *     genBase_ToJSON(
        GENBASE_DATA      *this
    )
    {
        ERESULT         eRc;
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
            //this->eRc = ERESULT_INVALID_OBJECT;
            return false;
        }

        // Return to caller.
        //this->eRc = ERESULT_SUCCESS;
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


