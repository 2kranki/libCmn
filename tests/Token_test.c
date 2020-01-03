// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/02/2020 15:58:09
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
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <Token_internal.h>



int             setUp(
    const
    char            *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int             tearDown(
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    SrcErrors_SharedReset();
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






int             test_Token_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TOKEN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Token_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Token_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKEN);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Token_Test01(
    const
    char        *pTestName
)
{
    TOKEN_DATA    *pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,0,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Token_NewInteger(&loc, 11, 64);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj)) );
        XCTAssertTrue( (11 == Token_getClass(pObj)) );
        XCTAssertTrue( (64 == Token_getInteger(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Token_JSON01(
    const
    char        *pTestName
)
{
    TOKEN_DATA  *pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,0,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"Token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"SrcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":3 /*TOKEN_TYPE_INTEGER*/, "
                                    "\"data\":{ "
                                        "\"objectType\":\"dec\", "
                                        "\"len\":8, "
                                        "\"crc\":1287593348, "
                                        "\"data\":64 "
                                    "}\n"
                                "}\n";
    ERESULT     eRc;
    TOKEN_DATA  *pToken;
    int         iRc;
    int         offset = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Token_NewInteger(&loc, 11, 64);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj)) );
        XCTAssertTrue( (11 == Token_getClass(pObj)) );
        XCTAssertTrue( (64 == Token_getInteger(pObj)) );

        pStr = Token_ToJson(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tJSON1: %s\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pJSON_Con, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        pToken = Token_NewFromJsonString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        if (pToken) {
            XCTAssertTrue( ( 1 == Token_getFileIndex(pToken)) );
            XCTAssertTrue( ( 4 == Token_getOffset(pToken)) );
            XCTAssertTrue( ( 3 == Token_getLineNo(pToken)) );
            XCTAssertTrue( ( 2 == Token_getColNo(pToken)) );
            XCTAssertTrue( (11 == Token_getClass(pToken)) );
            XCTAssertTrue( (64 == Token_getInteger(pToken)) );

            obj_Release(pStr);
            pStr = OBJ_NIL;

            pStr = Token_ToJson(pToken);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                fprintf(stderr, "\tJSON2 = \"%s\"\n", AStr_getData(pStr));
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



int         test_Token_JSON02(
    const
    char        *pTestName
)
{
    TOKEN_DATA  *pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,0,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"Token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"SrcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":7 /*TOKEN_TYPE_W32CHAR*/, "
                                    "\"data\":{ "
                                        "\"objectType\":\"dec\", "
                                        "\"len\":8, "
                                        "\"crc\":2713989223, "
                                        "\"data\":90 "
                                    "}\n"
                                "}\n";
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    int             iRc;
    int             offset = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Token_New();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    eRc = Token_SetupCharW32(pObj, &loc, 11, 'Z');
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    if (pObj) {

        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj)) );
        XCTAssertTrue( (11 == Token_getClass(pObj)) );
        XCTAssertTrue( ('Z' == Token_getChrW32(pObj)) );

        pStr = Token_ToJson(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pJSON_Con, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        pToken = Token_NewFromJsonString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ( 1 == Token_getFileIndex(pToken)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pToken)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pToken)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pToken)) );
        XCTAssertTrue( (11 == Token_getClass(pToken)) );
        XCTAssertTrue( ('Z' == Token_getChrW32(pToken)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = Token_ToJson(pToken);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        //fprintf(stderr, "\tJSON = \"%s\"\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pJSON_Con, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

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



int         test_Token_JSON03(
    const
    char        *pTestName
)
{
    TOKEN_DATA    *pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,0,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"Token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"SrcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":6 /*TOKEN_TYPE_STRTOKEN*/, "
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
    int             iRc;
    int             offset = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Token_NewStrA(&loc, 11, "12345");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj)) );
        XCTAssertTrue( (11 == Token_getClass(pObj)) );

        pAStr = Token_getTextAStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        pStr = Token_ToJson(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pJSON_Con, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        pToken = Token_NewFromJsonString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        XCTAssertTrue( ( 1 == Token_getFileIndex(pToken)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pToken)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pToken)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pToken)) );
        XCTAssertTrue( (11 == Token_getClass(pToken)) );

        pAStr = Token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "12345");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = Token_ToJson(pToken);
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



int         test_Token_JSON04(
    const
    char        *pTestName
)
{
    TOKEN_DATA    *pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,0,3,4};
    ASTR_DATA   *pStr;
    const
    char        *pJSON_Con =    "{\"objectType\":\"Token\", "
                                    "\"class\":11, "
                                    "\"loc\":{ "
                                        "\"objectType\":\"SrcLoc\", "
                                        "\"fileIndex\":1, "
                                        "\"offset\":4, "
                                        "\"lineNo\":3, "
                                        "\"colNo\":2 "
                                    "}\n, "
                                    "\"misc\":0, "
                                    "\"type\":6 /*TOKEN_TYPE_STRTOKEN*/, "
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

    pObj = Token_NewStrA(&loc, 11, "\n  \n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj)) );
        XCTAssertTrue( (11 == Token_getClass(pObj)) );

        pAStr = Token_getTextAStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "\n  \n");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        pStr = Token_ToJson(pObj);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        eRc = AStr_CompareA(pStr, pJSON_Con);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        pToken = Token_NewFromJsonString(pStr);
        XCTAssertFalse( (OBJ_NIL == pToken) );

        XCTAssertTrue( ( 1 == Token_getFileIndex(pToken)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pToken)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pToken)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pToken)) );
        XCTAssertTrue( (11 == Token_getClass(pToken)) );

        pAStr = Token_getTextAStr(pToken);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        XCTAssertTrue( (OBJ_IDENT_ASTR == obj_getType(pAStr)) );
        eRc = AStr_CompareA(pAStr, "\n  \n");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = Token_ToJson(pToken);
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




TINYTEST_START_SUITE(test_Token);
    TINYTEST_ADD_TEST(test_Token_JSON04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Token_JSON03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Token_JSON02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Token_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Token_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Token_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Token);





