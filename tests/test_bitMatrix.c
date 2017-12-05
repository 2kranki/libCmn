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
#include    <trace.h>
#include    <bitMatrix_internal.h>



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






int         test_bitMatrix_OpenClose(
    const
    char        *pTestName
)
{
    BITMATRIX_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitMatrix_Alloc(8, 8);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = bitMatrix_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_bitMatrix_SetGet(
    const
    char        *pTestName
)
{
    BITMATRIX_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = bitMatrix_Alloc(11, 11);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = bitMatrix_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = bitMatrix_Set(pObj, 1, 2, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 1, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Set(pObj, 1, 3, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 1, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Set(pObj, 1, 10, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 1, 10);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = bitMatrix_Set(pObj, 2, 7, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 2, 7);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = bitMatrix_Set(pObj, 3, 4, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 3, 4);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Set(pObj, 3, 6, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 3, 6);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Set(pObj, 3, 8, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 3, 8);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = bitMatrix_Set(pObj, 4, 9, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 4, 9);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = bitMatrix_Set(pObj, 5, 8, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 5, 8);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Set(pObj, 5, 10, true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = bitMatrix_Get(pObj, 5, 10);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        pStr = bitMatrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = bitMatrix_ReflectiveTransitiveClosure(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        pStr = bitMatrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_bitMatrix);
  TINYTEST_ADD_TEST(test_bitMatrix_SetGet,setUp,tearDown);
  TINYTEST_ADD_TEST(test_bitMatrix_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_bitMatrix);





