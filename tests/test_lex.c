/*
 *	Generated 06/05/2017 23:06:44
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <cmn_defs.h>
#include    <trace.h>
#include    <lex_internal.h>
#include    <srcFile.h>


#ifdef XYZZY
static
const
char        *pTestInput01 =
    "+ ++ +=\n"
    "\t* *=\n"
    "abc2\n";
#endif






int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    szTbl_SharedReset( );
    trace_SharedReset( );
    if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n"
        );
        exitCode = 4;
        return 0;
    }
    mem_Release( );
    
    return 1; 
}






int         test_lex_OpenClose(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = lex_Alloc();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = lex_Init( pObj, 3 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



// Revisit this since lex is a virtual object.
#ifdef XYZZY
int         test_lex_Input01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA	*pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        pSrc = srcFile_InitAStr( pSrc, pBuf, pPath, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)pplex2_New(5);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                pplex2_setReturnNL((PPLEX2_DATA *)pLex, true);
                pplex2_setReturnWS((PPLEX2_DATA *)pLex, true);
                
                fRc = lex_setParserFunction(pLex, (void *)pplex2_ParseToken, pLex);
                XCTAssertTrue( (fRc) );
                
                fRc =   lex_setSourceFunction(
                                pLex,
                                (void *)srcFile_InputAdvance,
                                (void *)srcFile_InputLookAhead,
                                pSrc
                        );
                XCTAssertTrue( (fRc) );

                // 1st Line - "+ ++ +=\n"
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ADD == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_INC == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_ADD == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 2nd Line - "\t* *=\n"
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_MUL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_MUL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 3rd Line = "abc2\n"
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                //FIXME: XCTAssertTrue( (0 == strcmp("abc2",token_getText(pToken))) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (LEX_CLASS_EOF == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
               obj_Release(pLex);
                pLex = OBJ_NIL;
            }
            
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}
#endif



int         test_lex_Number01(
     const
     char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    uint16_t        newClass;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("123");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        pSrc = srcFile_InitAStr( pSrc, pBuf, pPath, 1, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)lex_New(5);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                fRc =   lex_setSourceFunction(
                            pLex,
                            (void *)srcFile_InputAdvance,
                            (void *)srcFile_InputLookAhead,
                            pSrc
                        );
                XCTAssertTrue( (fRc) );
                
                pToken = srcFile_InputLookAhead(pSrc, 1);
                eRc = lex_ParseTokenSetup(pLex, pToken);
                XCTAssertFalse( (ERESULT_FAILED(eRc)) );
                newClass = lex_ParseNumber(pLex);
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == newClass) );
                eRc = W32Str_CompareA(pLex->pStr, "123");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
                
                obj_Release(pLex);
                pLex = OBJ_NIL;
            }
            
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_lex_Number02(
      const
      char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    uint16_t        newClass;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("123.456");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        pSrc = srcFile_InitAStr( pSrc, pBuf, pPath, 1, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)lex_New(5);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                pToken = srcFile_InputLookAhead(pSrc, 1);
                eRc = lex_ParseTokenSetup(pLex, pToken);
                newClass = lex_ParseNumber(pLex);
                XCTAssertTrue( (LEX_CONSTANT_FLOAT == newClass) );
                eRc = W32Str_CompareA(pLex->pStr, "123.456");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
                
                obj_Release(pLex);
                pLex = OBJ_NIL;
            }
            
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_lex_Number03(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    uint16_t        newClass;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("0");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        pSrc = srcFile_InitAStr( pSrc, pBuf, pPath, 1, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)lex_New(5);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                                              );
                XCTAssertTrue( (fRc) );
                
                pToken = srcFile_InputLookAhead(pSrc, 1);
                eRc = lex_ParseTokenSetup(pLex, pToken);
                newClass = lex_ParseNumber(pLex);
                XCTAssertTrue( (LEX_CONSTANT_INTEGER == newClass) );
                eRc = W32Str_CompareA(pLex->pStr, "0");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
                
                obj_Release(pLex);
                pLex = OBJ_NIL;
            }
            
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_lex_Strings01(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    SRCLOC          src = {1,2,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = lex_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lex_Init( pObj, 3 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pWork = token_NewCharW32(&src, 'd', 'd');
        eRc = lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        pWork = token_NewCharW32(&src, 'e', 'e');
        eRc = lex_ParseTokenAppendString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        pWork = token_NewCharW32(&src, 'f', 'f');
        eRc = lex_ParseTokenAppendString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        eRc = lex_ParseTokenFinalize(pObj,'a',true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = lex_getToken(pObj);
        pStr = token_getTextAStr(pToken);
        eRc = AStr_CompareA(pStr, "def");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        cls = token_getClass(pToken);
        XCTAssertTrue( ('a' == cls) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_lex_Strings02(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    SRCLOC          src = {1,2,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = lex_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lex_Init(pObj, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pWork = token_NewStrA(&src, 510, "\n  \n");
        XCTAssertFalse( (OBJ_NIL == pWork) );

        eRc = lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        eRc = lex_ParseTokenFinalize(pObj, 512, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = lex_getToken(pObj);
        pStr = token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        if (pStr) {
            fprintf(stderr, "\toutput = \"%s\"\n", AStr_getData(pStr));
            eRc = AStr_CompareA(pStr, "\n  \n");
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        }
        obj_Release(pStr);
        cls = token_getClass(pToken);
        fprintf(stderr, "\tclass = %d\n", cls);
        XCTAssertTrue( (512 == cls) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_lex_Strings03(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    ASTR_DATA       *pStr;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    SRCLOC          src = {1,2,3,4};
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = lex_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lex_Init( pObj, 3 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pWork = token_NewStrA(&src, 510, "@interface");
        XCTAssertFalse( (OBJ_NIL == pWork) );

        eRc = lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        eRc = lex_ParseTokenFinalize(pObj, 512, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = lex_getToken(pObj);
        pStr = token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        if (pStr) {
            fprintf(stderr, "\toutput = \"%s\"\n", AStr_getData(pStr));
            eRc = AStr_CompareA(pStr, "@interface");
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        }
        obj_Release(pStr);
        cls = token_getClass(pToken);
        fprintf(stderr, "\tclass = %d\n", cls);
        XCTAssertTrue( (512 == cls) );

        
        pWork = token_NewStrA(&src, 510, "@end");
        
        eRc = lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        eRc = lex_ParseTokenFinalize(pObj, 512, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = lex_getToken(pObj);
        pStr = token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        if (pStr) {
            fprintf(stderr, "\toutput = \"%s\"\n", AStr_getData(pStr));
            eRc = AStr_CompareA(pStr, "@end");
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        }
        obj_Release(pStr);
        cls = token_getClass(pToken);
        fprintf(stderr, "\tclass = %d\n", cls);
        XCTAssertTrue( (512 == cls) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_lex_Strings04(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    ERESULT         eRc;
    W32CHR_T        ch;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pBuf = AStr_NewA("\"\\x01\\x02\"");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {
        
        pSrc = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        pSrc = srcFile_InitAStr( pSrc, pBuf, pPath, 1, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)lex_New(5);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {
                
                obj_TraceSet(pLex, true);
                fRc =   lex_setSourceFunction(
                                              pLex,
                                              (void *)srcFile_InputAdvance,
                                              (void *)srcFile_InputLookAhead,
                                              pSrc
                        );
                XCTAssertTrue( (fRc) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                eRc = lex_ParseTokenSetup(pLex, pToken);

                // The following tests lex_ParseChrCon() as found in ppLex2.
                lex_InputAdvance(pLex, 1);
                while (lex_ParseChrCon(pLex, '\"'))
                    ;
                pToken = lex_InputLookAhead(pLex, 1);
                ch = token_getChrW32(pToken);
                XCTAssertTrue( (ch == '"') );
                lex_ParseTokenAppendString(pLex, pToken);
                {
                    ASTR_DATA       *pWrk2 = W32Str_ToChrCon(pLex->pStr);
                    fprintf(stderr, "\tDATA=\"%s\"\n", AStr_getData(pWrk2));
                    obj_Release(pWrk2);
                }
                eRc = W32Str_CompareA(pLex->pStr, "\"\\x01\\x02\"");
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
                
                obj_Release(pLex);
                pLex = OBJ_NIL;
            }
            
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_cloOpt);
    TINYTEST_ADD_TEST(test_lex_Strings04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lex_Strings03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lex_Strings02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lex_Strings01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lex_Number03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lex_Number02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lex_Number01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_lex_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_lex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cloOpt);





