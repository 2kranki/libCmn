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
#include    <AStrC_internal.h>



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






int         test_AStrC_OpenClose(
    const
    char        *pTestName
)
{
    ASTRC_DATA	*pObj = OBJ_NIL;
    ASTRC_DATA	*pCopy = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrC_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = AStrC_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pCopy = AStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrC_NewA(
    const
    char        *pTestName
)
{
    ASTRC_DATA	*pObj = OBJ_NIL;
    ASTRC_DATA	*pCopy = OBJ_NIL;
    const
    char        *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
  
    pObj = AStrC_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = AStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pObj);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        pCopy = AStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = AStrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pCopy);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_AStrC);
  TINYTEST_ADD_TEST(test_AStrC_NewA,setUp,tearDown);
  TINYTEST_ADD_TEST(test_AStrC_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AStrC);





