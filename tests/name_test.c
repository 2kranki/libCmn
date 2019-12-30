/*
 *	Generated 06/05/2017 10:38:38
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
#include    <name_internal.h>
#include    <SrcErrors.h>



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

    SrcErrors_SharedReset( );
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






int         test_name_OpenClose(
    const
    char        *pTestName
)
{
    NAME_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = name_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = name_InitInt(pObj, 0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_name_UTF8(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewUTF8( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pAStr1 = name_getStr(pName1);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_name_UTF8Con(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewUTF8Con( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStr(pName1);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_name_Int(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewInt( 123456 );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStr(pName1);
        fprintf(stderr, "strA = \"%s\"\n", AStr_getData(pAStr1));
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAStr1, "0000000000000123456")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_name_Json01_UTF8(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    NAME_DATA	*pName1 = OBJ_NIL;
    NAME_DATA   *pName2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    static
    const
    char        *pJSON01 =  "{\"objectType\":\"name\", "
                                "\"type\":2 /*NAME_TYPE_UTF8*/, "
                                "\"data\":{ "
                                    "\"objectType\":\"utf8\", "
                                    "\"len\":3, "
                                    "\"crc\":891568578, "
                                    "\"data\":\"abc\" "
                                "}\n"
                            "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pName1 = name_NewUTF8( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pJSON = name_ToJson(pName1);
        XCTAssertFalse( (OBJ_NIL == pJSON) );
        fprintf(stderr, "\tjSON=\"%s\"\n", AStr_getData(pJSON));
        eRc = AStr_CompareA(pJSON, pJSON01);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        pName2 = name_NewFromJsonString(pJSON);
        eRc = name_CompareA(pName2, "abc");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pName2);
        pName2 = OBJ_NIL;
        
        obj_Release(pJSON);
        pJSON = OBJ_NIL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_name_Json01_UTF8Con(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    NAME_DATA	*pName1 = OBJ_NIL;
    NAME_DATA   *pName2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    static
    const
    char        *pJSON01 =  "{\"objectType\":\"name\", "
                                "\"type\":2 /*NAME_TYPE_UTF8*/, "
                                "\"data\":{ "
                                    "\"objectType\":\"utf8\", "
                                    "\"len\":3, "
                                    "\"crc\":891568578, "
                                    "\"data\":\"abc\" "
                                "}\n"
                            "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewUTF8Con( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pJSON = name_ToJson(pName1);
        XCTAssertFalse( (OBJ_NIL == pJSON) );
        fprintf(stderr, "\tjSON=\"%s\"\n", AStr_getData(pJSON));
        eRc = AStr_CompareA(pJSON, pJSON01);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pName2 = name_NewFromJsonString(pJSON);
        eRc = name_CompareA(pName2, "abc");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pName2);
        pName2 = OBJ_NIL;
        
        obj_Release(pJSON);
        pJSON = OBJ_NIL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_name_Json01_Int(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    NAME_DATA	*pName1 = OBJ_NIL;
    NAME_DATA   *pName2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    ASTR_DATA   *pAStr = OBJ_NIL;
    static
    const
    char        *pJSON01 =  "{\"objectType\":\"name\", "
                                "\"type\":1 /*NAME_TYPE_INTEGER*/, "
                                "\"data\":{ "
                                    "\"objectType\":\"dec\", "
                                    "\"len\":8, "
                                    "\"crc\":333216031, "
                                    "\"data\":123456 "
                                "}\n"
                            "}\n";

    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pName1 = name_NewInt( 123456 );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr = name_getStr(pName1);
        fprintf(stderr, "Need = \"0000000000000123456\"\n");
        fprintf(stderr, "Got  = \"%s\"\n", AStr_getData(pAStr));
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAStr, "0000000000000123456")) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        
        pJSON = name_ToJson(pName1);
        XCTAssertFalse( (OBJ_NIL == pJSON) );
        fprintf(stderr, "\tjSON=\"%s\"\n", AStr_getData(pJSON));
        eRc = AStr_CompareA(pJSON, pJSON01);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pName2 = name_NewFromJsonString(pJSON);
        eRc = name_CompareA(pName2, "123456");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pName2);
        pName2 = OBJ_NIL;
        
        obj_Release(pJSON);
        pJSON = OBJ_NIL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_name);
  TINYTEST_ADD_TEST(test_name_Json01_Int,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_Json01_UTF8Con,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_Json01_UTF8,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_Int,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_UTF8Con,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_UTF8,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_name);





