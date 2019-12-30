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
#include    <number_internal.h>
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






int         test_number_OpenClose(
    const
    char        *pTestName
)
{
    NUMBER_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = number_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = number_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_number_01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    NUMBER_DATA *pObj = OBJ_NIL;
    NUMBER_DATA *pObj2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    static
    const
    char        *pJSON01 =  "{\"objectType\":\"number\", "
                                "\"type\":2 /*NUMBER_TYPE_INT16*/, "
                                "\"data\":{ "
                                    "\"objectType\":\"dec\", "
                                    "\"len\":8, "
                                    "\"crc\":1696784233, "
                                    "\"data\":0 "
                                "}\n"
                            "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = number_NewInt16(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (NUMBER_TYPE_INT16 == pObj->type) );
        TINYTEST_TRUE( (0 == pObj->i16) );
        
        pJSON = number_ToJSON(pObj);
        fprintf(stderr, "\tJSON=\"%s\"\n", AStr_getData(pJSON));
        TINYTEST_FALSE( (OBJ_NIL == pJSON) );
        eRc = AStr_CompareA(pJSON, pJSON01);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );

        pObj2 = number_NewFromJSONString(pJSON);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = number_CompareA(pObj2, "0");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pJSON);
        pJSON = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_number_02(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    NUMBER_DATA *pObj = OBJ_NIL;
    NUMBER_DATA *pObj2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    static
    const
    char        *pJSON01 =  "{\"objectType\":\"number\", "
                                "\"type\":2 /*NUMBER_TYPE_INT16*/, "
                                "\"data\":{ "
                                    "\"objectType\":\"dec\", "
                                    "\"len\":8, "
                                    "\"crc\":532450701, "
                                    "\"data\":18446744073709550382 "
                                "}\n"
                            "}\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = number_NewInt16(-1234);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (NUMBER_TYPE_INT16 == pObj->type) );
        TINYTEST_TRUE( (-1234 == pObj->i16) );
        
        pJSON = number_ToJSON(pObj);
        fprintf(stderr, "\tJSON=\"%s\"\n", AStr_getData(pJSON));
        TINYTEST_FALSE( (OBJ_NIL == pJSON) );
        eRc = AStr_CompareA(pJSON, pJSON01);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pObj2 = number_NewFromJSONString(pJSON);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = number_CompareA(pObj2, "-1234");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        obj_Release(pJSON);
        pJSON = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_number_03(
                           const
                           char        *pTestName
                           )
{
    ERESULT     eRc;
    NUMBER_DATA *pObj = OBJ_NIL;
    NUMBER_DATA *pObj2 = OBJ_NIL;
    ASTR_DATA   *pJSON = OBJ_NIL;
    static
    const
    char        *pJSON01 =  "{\"objectType\":\"number\", "
                                "\"type\":2 /*NUMBER_TYPE_INT16*/, "
                                "\"data\":{ "
                                    "\"objectType\":\"dec\", "
                                    "\"len\":8, "
                                    "\"crc\":3579152923, "
                                    "\"data\":1234 "
                                    "}\n"
                                "}\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = number_NewInt16(1234);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        TINYTEST_TRUE( (NUMBER_TYPE_INT16 == pObj->type) );
        TINYTEST_TRUE( (1234 == pObj->i16) );
        
        pJSON = number_ToJSON(pObj);
        fprintf(stderr, "\tJSON=\"%s\"\n", AStr_getData(pJSON));
        TINYTEST_FALSE( (OBJ_NIL == pJSON) );
        eRc = AStr_CompareA(pJSON, pJSON01);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pObj2 = number_NewFromJSONString(pJSON);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = number_CompareA(pObj2, "1234");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        obj_Release(pJSON);
        pJSON = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_number);
    TINYTEST_ADD_TEST(test_number_03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_number_02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_number_01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_number_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_number);





