// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   Compiler.c
 *	Generated 01/04/2020 23:19:02
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
#include        <Compiler_internal.h>
#include        <NodeArray.h>
#include        <NodeHash.h>
#include        <SrcErrors.h>
#include        <trace.h>
#include        <stdarg.h>






#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

#ifdef XYZZY
    static
    void            Compiler_task_body (
        void            *pData
    )
    {
        //COMPILER_DATA  *this = pData;
        
    }
#endif



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    COMPILER_DATA *     Compiler_Alloc (
        void
    )
    {
        COMPILER_DATA       *this;
        uint32_t        cbSize = sizeof(COMPILER_DATA);
        
        // Do initialization.
        
         this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    COMPILER_DATA *     Compiler_New (
        void
    )
    {
        COMPILER_DATA       *this;
        
        this = Compiler_Alloc( );
        if (this) {
            this = Compiler_Init(this);
        } 
        return this;
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                      E r r o r s
    //---------------------------------------------------------------

    SRCERRORS_DATA * compiler_getErrors (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        return this->pErrors;
    }


    bool            Compiler_setErrors (
        COMPILER_DATA   *this,
        SRCERRORS_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pErrors) {
            obj_Release(this->pErrors);
        }
        this->pErrors = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                     F i l e  T a b l e
    //---------------------------------------------------------------

    OBJ_ID          Compiler_getFileTable (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pFileTable;
    }


    bool            Compiler_setFileTable (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pFileTable) {
            obj_Release(this->pFileTable);
        }
        this->pFileTable = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                 I n p u t  P a t h
    //---------------------------------------------------------------

    PATH_DATA *     Compiler_getInputPath (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pInputPath;
    }


    bool            Compiler_setInputPath (
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pInputPath) {
            obj_Release(this->pInputPath);
        }
        this->pInputPath = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              L e x e r
    //---------------------------------------------------------------

    OBJ_ID          Compiler_getLexer (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        return this->pLexer;
    }


    bool            Compiler_setLexer (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pLexer) {
            obj_Release(this->pLexer);
        }
        this->pLexer = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                        L i s t i n g
    //---------------------------------------------------------------

    OBJ_ID          Compiler_getListing (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pListing;
    }

    bool            Compiler_setListing (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pListing) {
            obj_Release(this->pListing);
        }
        this->pListing = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                 O u t p u t  D i r e c t o r y
    //---------------------------------------------------------------

    PATH_DATA *     Compiler_getOutputDir (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pOutputDir;
    }

    bool            Compiler_setOutputDir (
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pOutputDir) {
            obj_Release(this->pOutputDir);
        }
        this->pOutputDir = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                     P a r s e  T r e e
    //---------------------------------------------------------------
    
    OBJ_ID          Compiler_getParseTree (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        return this->pParseTree;
    }


    bool            Compiler_setParseTree (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pParseTree) {
            obj_Release(this->pParseTree);
        }
        this->pParseTree = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------

    ASTR_DATA *     Compiler_getProgramName (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pProgramName;
    }

    bool            Compiler_setProgramName (
        COMPILER_DATA   *this,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pProgramName) {
            obj_Release(this->pProgramName);
        }
        this->pProgramName = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                        Q u e u e 0
    //---------------------------------------------------------------

    NODEARRAY_DATA * Compiler_getQueue0 (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pQueue0;
    }


    bool            Compiler_setQueue0(
        COMPILER_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pQueue0) {
            obj_Release(this->pQueue0);
        }
        this->pQueue0 = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                         Q u e u e 1
    //---------------------------------------------------------------

    NODEARRAY_DATA * Compiler_getQueue1 (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pQueue1;
    }


    bool            Compiler_setQueue1 (
        COMPILER_DATA   *this,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pQueue1) {
            obj_Release(this->pQueue1);
        }
        this->pQueue1 = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                          Q u e u e 2
    //---------------------------------------------------------------

    OBJARRAY_DATA * Compiler_getQueue2 (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pQueue2;
    }


    bool            Compiler_setQueue2 (
        COMPILER_DATA   *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pQueue2) {
            obj_Release(this->pQueue2);
        }
        this->pQueue2 = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                       Q u e u e 3
    //---------------------------------------------------------------

    OBJARRAY_DATA * Compiler_getQueue3 (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pQueue3;
    }


    bool            Compiler_setQueue3 (
        COMPILER_DATA   *this,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pQueue3) {
            obj_Release(this->pQueue3);
        }
        this->pQueue3 = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                              S i z e
    //---------------------------------------------------------------
    
    uint32_t        Compiler_getSize (
        COMPILER_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        return 0;
    }



    //---------------------------------------------------------------
    //                  S y m b o l  T a b l e
    //---------------------------------------------------------------

    OBJ_ID          Compiler_getSymbolTable (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
        }
#endif

        return this->pSymbolTable;
    }

    bool            Compiler_setSymbolTable (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pSymbolTable) {
            obj_Release(this->pSymbolTable);
        }
        this->pSymbolTable = pValue;

        return true;
    }



    //---------------------------------------------------------------
    //                   S o u r c e  F i l e s
    //---------------------------------------------------------------

    SRCFILES_DATA * Compiler_getSourceFiles (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pSourceFiles;
    }


    bool            Compiler_setSourceFiles (
        COMPILER_DATA   *this,
        SRCFILES_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pSourceFiles) {
            obj_Release(this->pSourceFiles);
        }
        this->pSourceFiles = pValue;

        return true;
    }



    SZTBL_DATA *    Compiler_getStringTable (
        COMPILER_DATA       *this
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif
        return this->pStringTable;
    }



    //---------------------------------------------------------------
    //                          S u p e r
    //---------------------------------------------------------------
    
    OBJ_IUNKNOWN *  Compiler_getSuperVtbl (
        COMPILER_DATA     *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        
        return this->pSuperVtbl;
    }
    
  

    //---------------------------------------------------------------
    //                  T e m p  D i r e c t o r y
    //---------------------------------------------------------------

    PATH_DATA *     Compiler_getTempDir (
        COMPILER_DATA   *this
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
        }
#endif

        return this->pTempDir;
    }


    bool            Compiler_setTempDir (
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (this->pTempDir) {
            obj_Release(this->pTempDir);
        }
        this->pTempDir = pValue;

        return true;
    }





    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                     A d d  P r o p e r t y
    //---------------------------------------------------------------

    ERESULT         Compiler_AddProperty (
        COMPILER_DATA   *this,
        NODE_DATA       *pData
    )
    {
        ERESULT         eRc;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif

        if (OBJ_NIL == this->pProperties) {
            this->pProperties = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }

        eRc = NodeHash_Add(this->pProperties, pData);

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
        ERESULT eRc = Compiler_Assign(this,pOther);
     @endcode 
     @param     this    object pointer
     @param     pOther  a pointer to another COMPILER object
     @return    If successful, ERESULT_SUCCESS otherwise an 
                ERESULT_* error 
     */
    ERESULT         Compiler_Assign (
        COMPILER_DATA		*this,
        COMPILER_DATA     *pOther
    )
    {
        ERESULT     eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (!Compiler_Validate(pOther)) {
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
     @return    0  if this == other
                <0 if this < other
                >0 if this > other
     */
    int             Compiler_Compare (
        COMPILER_DATA   *this,
        COMPILER_DATA   *pOther
    )
    {
        int             iRc = 0;

#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            //return ERESULT_INVALID_OBJECT;
            return -2;
        }
        if (!Compiler_Validate(pOther)) {
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

   
 
    //---------------------------------------------------------------
    //                          C o p y
    //---------------------------------------------------------------
    
    /*!
     Copy the current object creating a new object.
     Example:
     @code 
        Compiler      *pCopy = Compiler_Copy(this);
     @endcode 
     @param     this    object pointer
     @return    If successful, a COMPILER object which must be 
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    COMPILER_DATA *     Compiler_Copy (
        COMPILER_DATA       *this
    )
    {
        COMPILER_DATA       *pOther = OBJ_NIL;
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        pOther = Compiler_New( );
        if (pOther) {
            eRc = Compiler_Assign(this, pOther);
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

    void            Compiler_Dealloc (
        OBJ_ID          objId
    )
    {
        COMPILER_DATA   *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return;
        }
#endif

#ifdef XYZZY
        if (obj_IsEnabled(this)) {
            ((COMPILER_VTBL *)obj_getVtbl(this))->devVtbl.pStop((OBJ_DATA *)this,NULL);
        }
#endif

        (void)Compiler_setErrors(this, OBJ_NIL);
        (void)Compiler_setInputPath(this, OBJ_NIL);
        (void)Compiler_setLexer(this, OBJ_NIL);
        (void)Compiler_setListing(this, OBJ_NIL);
        (void)Compiler_setOutputDir(this, OBJ_NIL);
        (void)Compiler_setProgramName(this, OBJ_NIL);
        (void)Compiler_setQueue0(this, OBJ_NIL);
        (void)Compiler_setQueue1(this, OBJ_NIL);
        (void)Compiler_setQueue2(this, OBJ_NIL);
        (void)Compiler_setQueue3(this, OBJ_NIL);
        (void)Compiler_setSourceFiles(this, OBJ_NIL);
        (void)Compiler_setSymbolTable(this, OBJ_NIL);
        (void)Compiler_setTempDir(this, OBJ_NIL);

        if (this->pStringTable) {
            obj_Release(this->pStringTable);
            this->pStringTable = OBJ_NIL;
        }

        if (this->pProperties) {
            obj_Release(this->pProperties);
            this->pProperties = OBJ_NIL;
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

    /*!
     Disable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Compiler_Disable (
        COMPILER_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Compiler_Validate(this)) {
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

    /*!
     Enable operation of this object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Compiler_Enable (
        COMPILER_DATA		*this
    )
    {
        //ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!Compiler_Validate(this)) {
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
    //                         E r r o r (s)
    //---------------------------------------------------------------

    SRCERRORS_DATA * Compiler_Errors (
        COMPILER_DATA   *this
    )
    {

#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (OBJ_NIL == this->pErrors) {
            this->pErrors = SrcErrors_New( );
            if (OBJ_NIL == this->pErrors) {
                return OBJ_NIL;
            }
            SrcErrors_setFatalExit(this->pErrors, OBJ_NIL);
        }

        // Return to caller.
        return this->pErrors;
    }



    //---------------------------------------------------------------
    //                F i l e  P a t h  T o  N u m b e r
    //---------------------------------------------------------------

    uint32_t        Compiler_FilePathToNumber (
        COMPILER_DATA   *this,
        const
        char            *pszFilePath
    )
    {
        uint32_t        num;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (NULL == pszFilePath) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        num = szTbl_StringToToken(this->pStringTable, pszFilePath);

        return num;
    }



    //---------------------------------------------------------------
    //                I n d e x  T o  F i l e  P a t h
    //---------------------------------------------------------------

    const
    char *              Compiler_IndexToFilePath (
        COMPILER_DATA       *this,
        uint32_t            num
    )
    {
        const
        char                *pszStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        if (0 == num) {
            return "";
        }

        pszStr = szTbl_TokenToString(this->pStringTable, num);
        if (NULL == pszStr) {
            return NULL;
        }

        return pszStr;
    }



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    COMPILER_DATA *   Compiler_Init (
        COMPILER_DATA       *this
    )
    {
        uint32_t        cbSize = sizeof(COMPILER_DATA);
        //ERESULT         eRc;
        char            *pStrA;
        PATH_DATA       *pDir;

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
        this = (OBJ_ID)obj_Init(this, cbSize, OBJ_IDENT_COMPILER);
        if (OBJ_NIL == this) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
        //obj_setSize(this, cbSize);                        // Needed for Inheritance
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&Compiler_Vtbl);
        
        this->pErrors = SrcErrors_New();
        BREAK_NULL(this->pErrors);
        this->pQueue0 = NodeArray_New();
        BREAK_NULL(this->pQueue0);
        this->pQueue1 = NodeArray_New();
        BREAK_NULL(this->pQueue1);
        this->pQueue2 = ObjArray_New();
        BREAK_NULL(this->pQueue2);
        this->pQueue3 = ObjArray_New();
        BREAK_NULL(this->pQueue3);

        pStrA = getenv("TMP");
        if (NULL == pStrA) {
            pStrA = getenv("TMPDIR");
        }
        if (pStrA) {
            pDir = Path_NewA(pStrA);
            if (pDir) {
                Compiler_setTempDir(this, pDir);
                obj_Release(pDir);
                pDir = OBJ_NIL;
            }
        }

        this->pStringTable = szTbl_Shared();
        if (OBJ_NIL == this->pStringTable) {
            obj_Release(this);
            return OBJ_NIL;
        }

    #ifdef NDEBUG
    #else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            obj_Release(this);
            return OBJ_NIL;
        }
#ifdef XYZZY
        fprintf(stderr, "Compiler::sizeof(COMPILER_DATA) = %lu\n",
                sizeof(COMPILER_DATA));
        fprintf(stderr, "Compiler::sizeof(COMPILER_DATA) % 4 = %lu\n",
                sizeof(COMPILER_DATA) % 4);
#endif
        BREAK_NOT_BOUNDARY4(sizeof(COMPILER_DATA));
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    ERESULT         Compiler_IsEnabled (
        COMPILER_DATA		*this
    )
    {
        //ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
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
    //              N u m b e r  O f  P r o p e r t i e s
    //---------------------------------------------------------------

    uint16_t        Compiler_NumberOfProperties (
        COMPILER_DATA    *this
    )
    {
        uint16_t        num = 0;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = NodeHash_getSize(this->pProperties);
        }

        // Return to caller.
        return num;
    }



    //---------------------------------------------------------------
    //                N u m b e r  T o  S t r i n g
    //---------------------------------------------------------------

    const
    char *              Compiler_NumberToString (
        COMPILER_DATA       *this,
        uint32_t            num
    )
    {
        const
        char                *pszStr;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        pszStr = szTbl_TokenToString(this->pStringTable, num);

        return pszStr;
    }



    //---------------------------------------------------------------
    //                      P r o p e r t y
    //---------------------------------------------------------------

    NODE_DATA *     Compiler_Property (
        COMPILER_DATA   *this,
        const
        char            *pName
    )
    {
        NODE_DATA       *pProperty = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pProperties) {
            pProperty = NodeHash_FindA(this->pProperties, 0, pName);
        }

        // Return to caller.
        return pProperty;
    }



    //---------------------------------------------------------------
    //                    P r o p e r t i e s
    //---------------------------------------------------------------

    NODEARRAY_DATA * Compiler_Properties (
        COMPILER_DATA       *this
    )
    {
        //ERESULT         eRc;
        NODEARRAY_DATA  *pProperties = OBJ_NIL;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif

        if (this->pProperties) {
            pProperties = NodeHash_Nodes(this->pProperties);
        }

        // Return to caller.
        return pProperties;
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
        void        *pMethod = Compiler_QueryInfo(this, OBJ_QUERYINFO_TYPE_METHOD, "xyz");
     @endcode 
     @param     objId   object pointer
     @param     type    one of OBJ_QUERYINFO_TYPE members (see obj.h)
     @param     pData   for OBJ_QUERYINFO_TYPE_INFO, this field is not used,
                        for OBJ_QUERYINFO_TYPE_METHOD, this field points to a 
                        character string which represents the method name without
                        the object name, "Compiler", prefix,
                        for OBJ_QUERYINFO_TYPE_PTR, this field contains the
                        address of the method to be found.
     @return    If unsuccessful, NULL. Otherwise, for:
                OBJ_QUERYINFO_TYPE_INFO: info pointer,
                OBJ_QUERYINFO_TYPE_METHOD: method pointer,
                OBJ_QUERYINFO_TYPE_PTR: constant UTF-8 method name pointer
     */
    void *          Compiler_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        COMPILER_DATA     *this = objId;
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
            DEBUG_BREAK();
            return NULL;
        }
#endif
        
        switch (type) {
                
        case OBJ_QUERYINFO_TYPE_OBJECT_SIZE:
            return (void *)sizeof(COMPILER_DATA);
            break;
            
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return (void *)Compiler_Class();
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
                            return Compiler_Disable;
                        }
                        break;

                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return Compiler_Enable;
                        }
                        break;

                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return Compiler_ToDebugString;
                        }
#ifdef  SRCREF_JSON_SUPPORT
                        if (str_Compare("ToJson", (char *)pStr) == 0) {
                            return Compiler_ToJson;
                        }
#endif
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_PTR:
                if (pData == Compiler_ToDebugString)
                    return "ToDebugString";
#ifdef  SRCREF_JSON_SUPPORT
                if (pData == Compiler_ToJson)
                    return "ToJson";
#endif
                break;
                
            default:
                break;
        }
        
        return this->pSuperVtbl->pQueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  S t r i n g  T o  N u m b e r
    //---------------------------------------------------------------

    uint32_t        Compiler_StringToNumber (
        COMPILER_DATA       *this,
        const
        char                *pszStr
    )
    {
        uint32_t            num;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return 0;
        }
        if (NULL == pszStr) {
            DEBUG_BREAK();
            return 0;
        }
#endif

        num = szTbl_StringToToken( this->pStringTable, pszStr);

        return num;
    }



    //---------------------------------------------------------------
    //                S t r i n g  T o  S t r i n g
    //---------------------------------------------------------------

    const
    char *              Compiler_StringToString (
        COMPILER_DATA       *this,
        const
        char                *pszStr
    )
    {
        const
        char                *pszStrRet;

        // Do initialization.
#ifdef NDEBUG
#else
        if( !Compiler_Validate(this) ) {
            DEBUG_BREAK();
            return NULL;
        }
#endif

        pszStrRet = szTbl_StringToString( this->pStringTable, pszStr);
        if (NULL == pszStrRet) {
            return NULL;
        }

        return pszStrRet;
    }



    //---------------------------------------------------------------
    //                       T o  S t r i n g
    //---------------------------------------------------------------
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Compiler_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning  Remember to release the returned AStr object.
     */
    ASTR_DATA *     Compiler_ToDebugString (
        COMPILER_DATA   *this,
        int             indent
    )
    {
        ERESULT         eRc;
        //int             j;
        ASTR_DATA       *pStr;
        //ASTR_DATA       *pWrkStr;
        const
        OBJ_INFO        *pInfo;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if (!Compiler_Validate(this)) {
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
                    Compiler_getSize(this),
                    obj_getRetainCount(this)
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
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            Compiler_Validate (
        COMPILER_DATA      *this
    )
    {
 
        // WARNING: We have established that we have a valid pointer
        //          in 'this' yet.
       if (this) {
            if (obj_IsKindOf(this, OBJ_IDENT_COMPILER))
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


        if (!(obj_getSize(this) >= sizeof(COMPILER_DATA))) {
            return false;
        }

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


