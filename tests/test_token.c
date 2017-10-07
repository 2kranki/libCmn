/*
 *	Generated 06/05/2017 21:57:10
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
#include    <szTbl.h>
#include    <trace.h>
#include    <token_internal.h>



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






int         test_token_OpenClose(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = token_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_token_JSON01(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\","
                                "\"FileName\":\"abc\","
                                "\"LineNo\":52,"
                                "\"ColNo\":22,"
                                "\"Class\":11,"
                                "\"Type\":\"NUMBER\","
                                "\"Data\":64}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitInteger(pObj, "abc", 52, 22, 11, 64);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pObj))) );
        XCTAssertTrue( (52 == token_getLineNo(pObj)) );
        XCTAssertTrue( (22 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        XCTAssertTrue( (64 == token_getInteger(pObj)) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pToken))) );
        XCTAssertTrue( (52 == token_getLineNo(pToken)) );
        XCTAssertTrue( (22 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        XCTAssertTrue( (64 == token_getInteger(pToken)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "\tJSON = \"%s\"\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_token_JSON02(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\","
                                "\"FileName\":\"abc\","
                                "\"LineNo\":52,"
                                "\"ColNo\":22,"
                                "\"Class\":11,"
                                "\"Type\":\"CHAR\","
                                "\"Data\":90}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitCharW(pObj, "abc", 52, 22, 11, 'Z');
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pObj))) );
        XCTAssertTrue( (52 == token_getLineNo(pObj)) );
        XCTAssertTrue( (22 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        XCTAssertTrue( ('Z' == token_getChrW(pObj)) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pToken))) );
        XCTAssertTrue( (52 == token_getLineNo(pToken)) );
        XCTAssertTrue( (22 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        XCTAssertTrue( ('Z' == token_getChrW(pObj)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "\tJSON = \"%s\"\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_token_JSON03(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\","
                                "\"FileName\":\"abc\","
                                "\"LineNo\":52,"
                                "\"ColNo\":22,"
                                "\"Class\":11,"
                                "\"Type\":\"STRING\","
                                "\"Data\":\"12345\"}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    WSTR_DATA   *pStrW;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitStrW(pObj, "abc", 52, 22, 11, L"12345");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pObj))) );
        XCTAssertTrue( (52 == token_getLineNo(pObj)) );
        XCTAssertTrue( (22 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        pStrW = token_getStringW(pObj);
        XCTAssertFalse( (OBJ_NIL == pStrW) );
        XCTAssertTrue( (OBJ_IDENT_WSTR == obj_getType(pStrW)) );
        eRc = WStr_CompareW(pStrW,L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (0 == strcmp("abc", token_getFileName(pToken))) );
        XCTAssertTrue( (52 == token_getLineNo(pToken)) );
        XCTAssertTrue( (22 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        eRc = WStr_CompareW(token_getStringW(pObj),L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "\tJSON = \"%s\"\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_token_JSON04(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\","
                                "\"FileName\":\"\","
                                "\"LineNo\":52,"
                                "\"ColNo\":22,"
                                "\"Class\":11,"
                                "\"Type\":\"STRING\","
                                "\"Data\":\"12345\"}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    WSTR_DATA   *pStrW;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitStrA(pObj, "", 52, 22, 11, "12345");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //fprintf(stderr, "\tFileName = %s\n", token_getFileName(pObj));
        XCTAssertTrue( (0 == strcmp("", token_getFileName(pObj))) );
        XCTAssertTrue( (52 == token_getLineNo(pObj)) );
        XCTAssertTrue( (22 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        pStrW = token_getStringW(pObj);
        XCTAssertFalse( (OBJ_NIL == pStrW) );
        XCTAssertTrue( (OBJ_IDENT_WSTR == obj_getType(pStrW)) );
        eRc = WStr_CompareW(pStrW,L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (0 == strcmp("", token_getFileName(pToken))) );
        XCTAssertTrue( (52 == token_getLineNo(pToken)) );
        XCTAssertTrue( (22 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        eRc = WStr_CompareW(token_getStringW(pObj),L"12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = token_ToJSON(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "\tJSON = \"%s\"\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pToken);
        pToken = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_token);
  TINYTEST_ADD_TEST(test_token_JSON04,setUp,tearDown);
  TINYTEST_ADD_TEST(test_token_JSON03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_token_JSON02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_token_JSON01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_token_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_token);





