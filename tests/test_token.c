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

    szTbl_SharedReset();
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






int         test_token_OpenClose(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,3,4};
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_NewInteger(&loc, 11, 64);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( ( 1 == token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        XCTAssertTrue( (64 == token_getInteger(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_token_JSON01(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"srcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":2 /*TOKEN_TYPE_INTEGER*/, "
                                    "\"data\":{ "
                                        "\"objectType\":\"dec\", "
                                        "\"len\":8, "
                                        "\"crc\":1287593348, "
                                        "\"data\":64 "
                                    "}\n"
                                "}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_NewInteger(&loc, 11, 64);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( ( 1 == token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        XCTAssertTrue( (64 == token_getInteger(pObj)) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        if (pToken) {
            XCTAssertTrue( ( 1 == token_getFileIndex(pToken)) );
            XCTAssertTrue( ( 4 == token_getOffset(pToken)) );
            XCTAssertTrue( ( 3 == token_getLineNo(pToken)) );
            XCTAssertTrue( ( 2 == token_getColNo(pToken)) );
            XCTAssertTrue( (11 == token_getClass(pToken)) );
            XCTAssertTrue( (64 == token_getInteger(pToken)) );

            obj_Release(pStr);
            pStr = OBJ_NIL;
            
            pStr = token_ToJSON(pToken);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                //fprintf(stderr, "\tJSON = \"%s\"\n", AStr_getData(pStr));
                eRc = AStr_CompareA(pStr, pJSON_Con);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            
            obj_Release(pToken);
            pToken = OBJ_NIL;
        }
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_token_JSON02(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"srcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":4 /*TOKEN_TYPE_W32CHAR*/, "
                                    "\"data\":{ "
                                        "\"objectType\":\"dec\", "
                                        "\"len\":8, "
                                        "\"crc\":2713989223, "
                                        "\"data\":90 "
                                    "}\n"
                                "}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = token_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = token_InitCharW32(pObj, &loc, 11, 'Z');
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( ( 1 == token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        XCTAssertTrue( ('Z' == token_getChrW32(pObj)) );
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ( 1 == token_getFileIndex(pToken)) );
        XCTAssertTrue( ( 4 == token_getOffset(pToken)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pToken)) );
        XCTAssertTrue( ( 2 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        XCTAssertTrue( ('Z' == token_getChrW32(pToken)) );
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
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_token_JSON03(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"srcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":3 /*TOKEN_TYPE_STRTOKEN*/, "
                                    "\"data\":{ "
                                        "\"objectType\":\"utf8\", "
                                        "\"len\":5, "
                                        "\"crc\":3421846044, "
                                        "\"data\":\"12345\" "
                                    "}\n"
                                "}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    ASTR_DATA   *pAStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = token_NewStrA(&loc, 11, "12345");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( ( 1 == token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        
        pAStr = token_getTextA(pObj);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        XCTAssertTrue( ( 1 == token_getFileIndex(pToken)) );
        XCTAssertTrue( ( 4 == token_getOffset(pToken)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pToken)) );
        XCTAssertTrue( ( 2 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        
        pAStr = token_getTextA(pToken);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
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
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_token_JSON04(
    const
    char        *pTestName
)
{
    TOKEN_DATA	*pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"srcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":3 /*TOKEN_TYPE_STRTOKEN*/, "
                                    "\"data\":{ "
                                        "\"objectType\":\"utf8\", "
                                        "\"len\":4, "
                                        "\"crc\":65385508, "
                                        "\"data\":\"\\n  \\n\" "
                                    "}\n"
                                "}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    ASTR_DATA   *pAStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = token_NewStrA(&loc, 11, "\n  \n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( ( 1 == token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == token_getColNo(pObj)) );
        XCTAssertTrue( (11 == token_getClass(pObj)) );
        
        pAStr = token_getTextA(pObj);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "\n  \n");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        
        pStr = token_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pToken = token_NewFromJSONString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        
        XCTAssertTrue( ( 1 == token_getFileIndex(pToken)) );
        XCTAssertTrue( ( 4 == token_getOffset(pToken)) );
        XCTAssertTrue( ( 3 == token_getLineNo(pToken)) );
        XCTAssertTrue( ( 2 == token_getColNo(pToken)) );
        XCTAssertTrue( (11 == token_getClass(pToken)) );
        
        pAStr = token_getTextA(pToken);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "\n  \n");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
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
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
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





