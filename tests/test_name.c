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
#include    <name_internal.h>



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

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_UTF8(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewUTF8( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pAStr1 = name_getStrA(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pWStr1 = name_getStrW(pName1);
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "abc")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_UTF8Con(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewUTF8Con( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStrA(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        pWStr1 = name_getStrW(pName1);
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "abc")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_Int(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewInt( 123456 );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStrA(pName1);
        fprintf(stderr, "strA = \"%s\"\n", AStr_getData(pAStr1));
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "0000000000000123456")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        pWStr1 = name_getStrW(pName1);
        fprintf(stderr, "strW = %ls\n", WStr_getData(pWStr1));
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "0000000000000123456")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_Ptr(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    const
    char        *pStr = NULL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewPtr( test_name_Ptr );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pStr = name_ToUTF8(pName1);
        XCTAssertTrue( (pStr) );
        fprintf(stderr, "ptr = %s\n", pStr);
        mem_Free((void *)pStr);
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_ToJSON_UTF8(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewUTF8( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pAStr1 = name_getStrA(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pWStr1 = name_getStrW(pName1);
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "abc")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_ToJSON_UTF8Con(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewUTF8Con( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStrA(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        pWStr1 = name_getStrW(pName1);
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "abc")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_ToJSON_Int(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewInt( 123456 );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStrA(pName1);
        fprintf(stderr, "strA = %s\n", AStr_getData(pAStr1));
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "00000000000000123456")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        pWStr1 = name_getStrW(pName1);
        fprintf(stderr, "strW = %ls\n", WStr_getData(pWStr1));
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "00000000000000123456")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_name_ToJSON_Ptr(
    const
    char        *pTestName
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    const
    char        *pStr = NULL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pName1 = name_NewPtr( test_name_Ptr );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pStr = name_ToUTF8(pName1);
        XCTAssertTrue( (pStr) );
        fprintf(stderr, "ptr = %s\n", pStr);
        mem_Free((void *)pStr);
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_name);
  //TINYTEST_ADD_TEST(test_name_ToJSON_Ptr,setUp,tearDown);
  //TINYTEST_ADD_TEST(test_name_ToJSON_Int,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_ToJSON_UTF8Con,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_ToJSON_UTF8,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_Ptr,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_Int,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_UTF8Con,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_UTF8,setUp,tearDown);
  TINYTEST_ADD_TEST(test_name_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_name);





