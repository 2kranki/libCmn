// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   compiler.c
 *	Generated by 06/18/2015 11:14:11
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
#include        "compiler_internal.h"
#include        <nodeArray.h>
#include        <nodeHash.h>
#include        <srcErrors.h>
#include        <trace.h>
#include        <stdarg.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    static
    COMPILER_DATA   singleton = {{0}};


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    


    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    COMPILER_DATA * compiler_Alloc(
    )
    {
        COMPILER_DATA   *this;
        uint32_t        cbSize = sizeof(COMPILER_DATA);
        
        // Do initialization.
        
        this = obj_Alloc( cbSize );
        
        // Return to caller.
        return this;
    }



    COMPILER_DATA * compiler_New(
    )
    {
        COMPILER_DATA   *this;
        
        // Do initialization.
        
        this = compiler_Alloc( );
        if (this) {
            this = compiler_Init(this);
        }
        
        // Return to caller.
        return this;
    }
    
    
    
    COMPILER_DATA * compiler_Shared(
    )
    {
        COMPILER_DATA   *this = &singleton;
        uint32_t        cbSize = sizeof(COMPILER_DATA);
        
        if (obj_getRetainCount(this) == 0) {
            obj_setSize(this, cbSize);
            this = compiler_Init( this );
        }
        return this;
    }
    
    
    
    bool            compiler_SharedReset(
    )
    {
        COMPILER_DATA   *this = &singleton;
        
        while (obj_getRetainCount(this)) {
            obj_Release(this);
        }
        memset(&singleton, 0, sizeof(COMPILER_DATA));
        
        return true;
    }
    
    
    


    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    ERESULT_DATA *  compiler_getErrors(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pErrors;
    }
    
    
    bool            compiler_setErrors(
        COMPILER_DATA   *cbp,
        ERESULT_DATA    *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pErrors) {
            obj_Release(cbp->pErrors);
        }
        cbp->pErrors = pValue;
        
        return true;
    }
    
    
    
    OBJ_ID          compiler_getFileTable(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pFileTable;
    }

    
    bool            compiler_setFileTable(
        COMPILER_DATA   *cbp,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pFileTable) {
            obj_Release(cbp->pFileTable);
        }
        cbp->pFileTable = pValue;
        
        return true;
    }
    
    
    
    PATH_DATA *     compiler_getInputPath(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pInputPath;
    }

    
    bool            compiler_setInputPath(
        COMPILER_DATA   *cbp,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pInputPath) {
            obj_Release(cbp->pInputPath);
        }
        cbp->pInputPath = pValue;
        
        return true;
    }
    
    

    //---------------------------------------------------------------
    //                      L a s t  E r r o r
    //---------------------------------------------------------------
    
    ERESULT         compiler_getLastError(
        COMPILER_DATA   *this
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
#endif
        
        return this->eRc;
    }
    
    
    bool            compiler_setLastError(
        COMPILER_DATA   *this,
        ERESULT         value
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        this->eRc = value;
        
        return true;
    }
    
    
    
    OBJ_ID          compiler_getListing(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pListing;
    }
    
    bool            compiler_setListing(
        COMPILER_DATA   *cbp,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pListing) {
            obj_Release(cbp->pListing);
        }
        cbp->pListing = pValue;
        
        return true;
    }
    
    

    PATH_DATA *     compiler_getOutputDir(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pOutputDir;
    }
    
    bool            compiler_setOutputDir(
        COMPILER_DATA   *cbp,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pOutputDir) {
            obj_Release(cbp->pOutputDir);
        }
        cbp->pOutputDir = pValue;
        
        return true;
    }
    
    
    
    NODETREE_DATA * compiler_getParseTree(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pParseTree;
    }
    
    
    bool            compiler_setParseTree(
        COMPILER_DATA   *cbp,
        NODETREE_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pParseTree) {
            obj_Release(cbp->pParseTree);
        }
        cbp->pParseTree = pValue;
        
        return true;
    }
    
    
    
    uint16_t        compiler_getPriority(
        COMPILER_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        //return cbp->priority;
        return 0;
    }

    bool            compiler_setPriority(
        COMPILER_DATA     *cbp,
        uint16_t        value
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        //cbp->priority = value;
        return true;
    }



    ASTR_DATA *     compiler_getProgramName(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pProgramName;
    }
    
    bool            compiler_setProgramName(
        COMPILER_DATA   *cbp,
        ASTR_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pProgramName) {
            obj_Release(cbp->pProgramName);
        }
        cbp->pProgramName = pValue;
        
        return true;
    }
    
    

    NODEARRAY_DATA * compiler_getQueue0(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pQueue0;
    }
    
    
    bool            compiler_setQueue0(
        COMPILER_DATA   *cbp,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pQueue0) {
            obj_Release(cbp->pQueue0);
        }
        cbp->pQueue0 = pValue;
        
        return true;
    }
    
    
    
    NODEARRAY_DATA * compiler_getQueue1(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pQueue1;
    }
    
    
    bool            compiler_setQueue1(
        COMPILER_DATA   *cbp,
        NODEARRAY_DATA  *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pQueue1) {
            obj_Release(cbp->pQueue1);
        }
        cbp->pQueue1 = pValue;
        
        return true;
    }
    
    
    
    OBJARRAY_DATA * compiler_getQueue2(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pQueue2;
    }
    
    
    bool            compiler_setQueue2(
        COMPILER_DATA   *cbp,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pQueue2) {
            obj_Release(cbp->pQueue2);
        }
        cbp->pQueue2 = pValue;
        
        return true;
    }
    
    
    
    OBJARRAY_DATA * compiler_getQueue3(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pQueue3;
    }
    
    
    bool            compiler_setQueue3(
        COMPILER_DATA   *cbp,
        OBJARRAY_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pQueue3) {
            obj_Release(cbp->pQueue3);
        }
        cbp->pQueue3 = pValue;
        
        return true;
    }
    
    
    
    OBJ_ID          compiler_getSymbolTable(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pSymbolTable;
    }
    
    bool            compiler_setSymbolTable(
        COMPILER_DATA   *cbp,
        OBJ_ID          pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pSymbolTable) {
            obj_Release(cbp->pSymbolTable);
        }
        cbp->pSymbolTable = pValue;
        
        return true;
    }
    
    
    
    SRCFILES_DATA * compiler_getSourceFiles(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pSourceFiles;
    }

    
    bool            compiler_setSourceFiles(
        COMPILER_DATA   *cbp,
        SRCFILES_DATA   *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pSourceFiles) {
            obj_Release(cbp->pSourceFiles);
        }
        cbp->pSourceFiles = pValue;
        
        return true;
    }
    
    
    
    SZTBL_DATA *    compiler_getStringTable(
        COMPILER_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return cbp->pStringTable;
    }



    PATH_DATA *     compiler_getTempDir(
        COMPILER_DATA   *cbp
    )
    {
        
        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        
        return cbp->pTempDir;
    }

    
    bool            compiler_setTempDir(
        COMPILER_DATA   *cbp,
        PATH_DATA       *pValue
    )
    {
#ifdef NDEBUG
#else
        if( !compiler_Validate( cbp ) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        obj_Retain(pValue);
        if (cbp->pTempDir) {
            obj_Release(cbp->pTempDir);
        }
        cbp->pTempDir = pValue;
        
        return true;
    }
    
    
    

    
    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                     A d d  P r o p e r t y
    //---------------------------------------------------------------
    
    ERESULT         compiler_AddProperty(
        COMPILER_DATA   *this,
        NODE_DATA       *pData
    )
    {
        ERESULT         eRc;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
        if (OBJ_NIL == pData) {
            return ERESULT_INVALID_PARAMETER;
        }
#endif
        
        if (OBJ_NIL == this->pProperties) {
            this->pProperties = nodeHash_New( );
            if (OBJ_NIL == this->pProperties) {
                return ERESULT_INSUFFICIENT_MEMORY;
            }
        }
        
        eRc = nodeHash_Add(this->pProperties, pData);
        
        // Return to caller.
        return eRc;
    }
    
    
    
    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            compiler_Dealloc(
        OBJ_ID          objId
    )
    {
        COMPILER_DATA   *this = objId;

        // Do initialization.
        if (OBJ_NIL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        (void)compiler_setErrors(this, OBJ_NIL);
        (void)compiler_setInputPath(this, OBJ_NIL);
        (void)compiler_setListing(this, OBJ_NIL);
        (void)compiler_setOutputDir(this, OBJ_NIL);
        (void)compiler_setProgramName(this, OBJ_NIL);
        (void)compiler_setQueue0(this, OBJ_NIL);
        (void)compiler_setQueue1(this, OBJ_NIL);
        (void)compiler_setQueue2(this, OBJ_NIL);
        (void)compiler_setQueue3(this, OBJ_NIL);
        (void)compiler_setSourceFiles(this, OBJ_NIL);
        (void)compiler_setSymbolTable(this, OBJ_NIL);
        (void)compiler_setTempDir(this, OBJ_NIL);
        
        if (this->pStringTable) {
            obj_Release(this->pStringTable);
            this->pStringTable = OBJ_NIL;
        }

        if (this->pProperties) {
            obj_Release(this->pProperties);
            this->pProperties = OBJ_NIL;
        }
        
        obj_setVtbl(this, this->pSuperVtbl);
        // pSuperVtbl is saved immediately after the super object which we
        // inherit from is initialized.
        this->pSuperVtbl->pDealloc(this);
        this = OBJ_NIL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                         E r r o r
    //---------------------------------------------------------------
    
#ifdef XYZZY
    void            compiler_Error(
        COMPILER_DATA   *cbp,
        const
        char            *pFileName,
        uint32_t		linnum,
        uint16_t		colnum,
        const
        char			*fmt,
        ...
    )
    {
        char			line_out[256];
        uint32_t		i;
        va_list 		argsp;
        
        
        va_start( argsp, fmt );
        if( OBJ_NIL == cbp->pListing ) {
            fprintf(
                    stderr,
                    "Error: %s line: %d col: %d  ",
                    pFileName,
                    linnum,
                    colnum
                    );
            vfprintf( stderr, fmt, argsp );
            return;
        }
        
        /* Display the error message.
         */
        prt_Printf(
                   cbp->pListing,
                   "Error: %s line: %d col: %d  ",
                   pFileName,
                   linnum,
                   colnum
                   );
        vsprintf( line_out, fmt, argsp );
        for( i=0; line_out[i]; ++i ) {
            prt_Putc( cbp->pListing, line_out[i] );
        }
        
        
        /* Return to O/S.
         */
        ++cbp->numErrors;
        if (cbp->numErrors > 50) {
            compiler_ErrorFatal(cbp, "Too many errors");
        }
    }
    
    
    
    
    void            compiler_ErrorArg(
        COMPILER_DATA   *cbp,
        const
        char            *pFileName,
        uint32_t		linnum,
        uint16_t		colnum,
        const
        char			*fmt,
        va_list 		argsp
    )
    {
        char			line_out[256];
        uint32_t		i;
        
        
        if( OBJ_NIL == cbp->pListing ) {
            fprintf(
                    stderr,
                    "Error: %s line: %d col: %d  ",
                    pFileName,
                    linnum,
                    colnum
                    );
            vfprintf( stderr, fmt, argsp );
            return;
        }
        
        /* Display the error message.
         */
        prt_Printf(
                   cbp->pListing,
                   "Error: %s line: %d col: %d  ",
                   pFileName,
                   linnum,
                   colnum
                   );
        vsprintf( line_out, fmt, argsp );
        for( i=0; line_out[i]; ++i ) {
            prt_Putc( cbp->pListing, line_out[i] );
        }
        
        
        /* Return to O/S.
         */
        ++cbp->numErrors;
        if (cbp->numErrors > 50) {
            compiler_ErrorFatal(cbp, "Too many errors");
        }
    }
#endif

    
    
    
    //---------------------------------------------------------------
    //                       F a t a l  E r r o r
    //---------------------------------------------------------------
    
#ifdef XYZZY
    void            compiler_ErrorFatal(
        COMPILER_DATA   *cbp,
        const
        char			*fmt,
        ...
    )
    {
        va_list 		argsp;
        
        DEBUG_BREAK();
        
        va_start( argsp, fmt );
        fprintf( stderr, "Fatal Error:  " );
        vfprintf( stderr, fmt, argsp );
        va_end( argsp );
        
        exit( 99 );
    }
    
    
    void            compiler_ErrorFatalArg(
        COMPILER_DATA   *cbp,
        const
        char			*fmt,
        va_list 		argsp
    )
    {
        
        DEBUG_BREAK();
        
        fprintf( stderr, "Fatal Error:  " );
        vfprintf( stderr, fmt, argsp );
        
        exit( 99 );
    }
    
    
    void            compiler_ErrorFatalExpecting(
        COMPILER_DATA   *this,
        const
        char			*pExpecting,
        TOKEN_DATA      *pToken
    )
    {
        const
        char            *pFileName;
        uint32_t		linnum;
        uint16_t		colnum;
        ASTR_DATA       *pAStr;

        if (OBJ_NIL == pToken) {
            DEBUG_BREAK();
            exit(100);
        }
        
        DEBUG_BREAK();
        
        pFileName = token_getFileName(pToken);
        linnum = token_getLineNo(pToken);
        colnum = token_getColNo(pToken);
        
        pAStr = token_ToDataString(pToken);
        fprintf(
                stderr,
                "Fatal Error:  file: %s line: %d col: %d - Expecting %s, but found %s",
                pFileName,
                linnum,
                colnum,
                pExpecting,
                AStr_getData(pAStr)
        );
        obj_Release(pAStr);
        
        exit( 99 );
    }
#endif
    
    
    
    //---------------------------------------------------------------
    //                F i l e  P a t h  T o  N u m b e r
    //---------------------------------------------------------------
    
    uint32_t        compiler_FilePathToNumber(
        COMPILER_DATA   *this,
        const
        char            *pszFilePath
    )
    {
        uint32_t        num;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
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
    //                          I n i t
    //---------------------------------------------------------------

    COMPILER_DATA *   compiler_Init(
        COMPILER_DATA   *this
    )
    {
        char            *pStr;
        PATH_DATA       *pDir;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_COMPILER );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, (OBJ_IUNKNOWN *)&compiler_Vtbl);
        
        this->pErrors = eResult_New();
        BREAK_NULL(this->pErrors);
        this->pQueue0 = nodeArray_New();
        BREAK_NULL(this->pQueue0);
        this->pQueue1 = nodeArray_New();
        BREAK_NULL(this->pQueue1);
        this->pQueue2 = objArray_New();
        BREAK_NULL(this->pQueue2);
        this->pQueue3 = objArray_New();
        BREAK_NULL(this->pQueue3);
        
        pStr = getenv("TMP");
        if (NULL == pStr) {
            pStr = getenv("TMPDIR");
        }
        if (pStr) {
            pDir = path_NewA(pStr);
            if (pDir) {
                compiler_setTempDir(this, pDir);
                obj_Release(pDir);
                pDir = OBJ_NIL;
            }
        }
        
        this->pStringTable = szTbl_Shared();
        if (OBJ_NIL == this->pStringTable) {
            obj_Release(this);
            return OBJ_NIL;
        }
        
        this->fTrace = true;

#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#ifdef __APPLE__
        fprintf(stderr, "compiler::sizeof(COMPILER_DATA) = %lu\n", sizeof(COMPILER_DATA));
#endif
        BREAK_NOT_BOUNDARY4(sizeof(COMPILER_DATA));
#endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    bool            compiler_IsEnabled(
        COMPILER_DATA   *this
    )
    {
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        
        if (obj_IsEnabled(this))
            return true;
        
        // Return to caller.
        return false;
    }
    
    
    
    //---------------------------------------------------------------
    //              N u m b e r  O f  P r o p e r t i e s
    //---------------------------------------------------------------
    
    uint16_t        compiler_NumberOfProperties(
        COMPILER_DATA	*this
    )
    {
        uint16_t        num = 0;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return false;
        }
#endif
        if (this->pProperties) {
            num = nodeHash_getSize(this->pProperties);
        }
        
        // Return to caller.
        return num;
    }
    
    
    
    //---------------------------------------------------------------
    //                I n d e x  T o  F i l e  P a t h
    //---------------------------------------------------------------
    
    const
    char *              compiler_IndexToFilePath(
        COMPILER_DATA		*this,
        uint32_t            num
    )
    {
        const
        char                *pszStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
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
    //                N u m b e r  T o  S t r i n g
    //---------------------------------------------------------------
    
    const
    char *              compiler_NumberToString(
        COMPILER_DATA		*this,
        uint32_t            num
    )
    {
        const
        char                *pszStr;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
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
    
    NODE_DATA *     compiler_Property(
        COMPILER_DATA       *this,
        const
        char            *pName
    )
    {
        NODE_DATA       *pProperty = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperty = nodeHash_FindA(this->pProperties, 0, pName);
        }
        
        // Return to caller.
        return pProperty;
    }
    
    
    
    //---------------------------------------------------------------
    //                    P r o p e r t i e s
    //---------------------------------------------------------------
    
    NODEARRAY_DATA * compiler_Properties(
        COMPILER_DATA       *this
    )
    {
        //ERESULT         eRc;
        NODEARRAY_DATA  *pProperties = OBJ_NIL;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
#endif
        
        if (this->pProperties) {
            pProperties = nodeHash_Nodes(this->pProperties);
        }
        
        // Return to caller.
        return pProperties;
    }
    
    
    
    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------
    
    void *          compiler_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        COMPILER_DATA   *this = objId;
        const
        char            *pStr = pData;

        if (OBJ_NIL == this) {
            return NULL;
        }
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
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

#ifdef XYZZY
                    case 'D':
                        if (str_Compare("Disable", (char *)pStr) == 0) {
                            return hex_Disable;
                        }
                        break;
                        
                    case 'E':
                        if (str_Compare("Enable", (char *)pStr) == 0) {
                            return hex_Enable;
                        }
                        break;
                        
                    case 'T':
                        if (str_Compare("ToDebugString", (char *)pStr) == 0) {
                            return hex_ToDebugString;
                        }
                        if (str_Compare("ToJSON", (char *)pStr) == 0) {
                            return hex_ToJSON;
                        }
                        break;
#endif
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return obj_QueryInfo(objId, type, pData);
    }
    
    
    
    //---------------------------------------------------------------
    //                  S t r i n g  T o  N u m b e r
    //---------------------------------------------------------------
    
    uint32_t        compiler_StringToNumber(
        COMPILER_DATA		*this,
        const
        char                *pszStr
    )
    {
        uint32_t            num;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
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
    char *              compiler_StringToString(
        COMPILER_DATA		*this,
        const
        char                *pszStr
    )
    {
        const
        char                *pszStrRet;
        
        // Do initialization.
#ifdef NDEBUG
#else
        if( !compiler_Validate(this) ) {
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
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            compiler_Validate(
        COMPILER_DATA      *this
    )
    {
        if(this) {
            if ( obj_IsKindOf(this, OBJ_IDENT_COMPILER) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(this) >= sizeof(COMPILER_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


