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


static
const
char        *pTestInput01 =
    "+ ++ +=\n"
    "\t* *=\n"
    "abc2\n";






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

    
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_lex_OpenClose(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
   
    pObj = lex_Alloc();
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = lex_Init( pObj, 3 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

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
    szTbl_SharedReset();

    return 1;
}
#endif



int         test_lex_Strings(
    const
    char        *pTestName
)
{
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    WSTR_DATA       *pStrW;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    
    pObj = lex_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lex_Init( pObj, 3 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pWork = token_NewCharW("abc", 1, 1, 'd', 'd');
        eRc = lex_ParseTokenSetup(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        pWork = token_NewCharW("abc", 1, 1, 'e', 'e');
        eRc = lex_ParseTokenAppendString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        pWork = token_NewCharW("abc", 1, 1, 'f', 'f');
        eRc = lex_ParseTokenAppendString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        eRc = lex_ParseTokenFinalize(pObj,'a',true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = lex_getToken(pObj);
        pStrW = token_getStringW(pToken);
        eRc = WStr_CompareW(pStrW, L"def");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        cls = token_getClass(pToken);
        XCTAssertTrue( ('a' == cls) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();

    return 1;
}




TINYTEST_START_SUITE(test_cloOpt);
  TINYTEST_ADD_TEST(test_lex_Strings,setUp,tearDown);
  //TINYTEST_ADD_TEST(test_lex_Input01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_lex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cloOpt);





