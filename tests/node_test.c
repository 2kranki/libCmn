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
#include    <trace.h>
#include    <appl_internal.h>
#include    <AStrArray.h>
#include    <szTbl.h>



int         setUp(
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


int         tearDown(
    const
    char            *pTestName
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






int         test_node_Utf8(
    const
    char            *pTestName
)
{
    NODE_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = node_NewWithUTF8AndClass(0, "abc", NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_node_Utf8Con(
    const
    char            *pTestName
)
{
    NODE_DATA	    *pObj = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = node_NewWithUTF8ConAndClass(0, "abc", OBJ_NIL);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_node_Property01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    NODE_DATA       *pObj = OBJ_NIL;
    ASTR_DATA       *pAStr = OBJ_NIL;
    const
    char            *pStrA = NULL;
    ASTR_DATA       *pAWrk = OBJ_NIL;
    NODEARRAY_DATA  *pKeys = OBJ_NIL;
    uint32_t        i;
    NODE_DATA       *pNode = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = node_NewWithUTF8ConAndClass(0, "abc", OBJ_NIL);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStrA = "c";
        pAStr = AStr_NewA(pStrA);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        eRc = node_PropertyAddA(pObj, pStrA, pAStr);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pAWrk = node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        
        pStrA = "a";
        pAStr = AStr_NewA(pStrA);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        eRc = node_PropertyAddA(pObj, pStrA, pAStr);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pAWrk = node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        
        pStrA = "b";
        pAStr = AStr_NewA(pStrA);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        eRc = node_PropertyAddA(pObj, pStrA, pAStr);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pAWrk = node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;
        
        pStrA = "a";
        pAWrk = node_PropertyA(pObj, pStrA);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pAWrk, pStrA)) );

        pKeys = node_Properties(pObj);
        XCTAssertFalse( (OBJ_NIL == pKeys) );
        i = NodeArray_getSize(pKeys);
        XCTAssertTrue( (3 == i) );
        pNode = NodeArray_Get(pKeys, 1);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(node_getData(pNode), "a")) );
        pNode = NodeArray_Get(pKeys, 2);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(node_getData(pNode), "b")) );
        pNode = NodeArray_Get(pKeys, 3);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(node_getData(pNode), "c")) );
        obj_Release(pKeys);
        pKeys = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_node);
    TINYTEST_ADD_TEST(test_node_Property01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_node_Utf8Con,setUp,tearDown);
    TINYTEST_ADD_TEST(test_node_Utf8,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_node);





