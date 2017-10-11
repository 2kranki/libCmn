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
#include    <WStrC_internal.h>



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






int         test_WStrC_OpenClose(
    const
    char        *pTestName
)
{
    WSTRC_DATA	*pObj = OBJ_NIL;
    WSTRC_DATA	*pCopy = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = WStrC_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = WStrC_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pCopy = WStrC_Copy(pObj);
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



int         test_WStrC_NewA(
    const
    char        *pTestName
)
{
    WSTRC_DATA	*pObj = OBJ_NIL;
    WSTRC_DATA	*pCopy = OBJ_NIL;
    const
    int32_t     *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = WStrC_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = WStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = WStrC_getData(pObj);
        XCTAssertTrue( (0 == utf8_StrCmpAW("abc",pStr)) );
        pCopy = WStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = WStrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = WStrC_getData(pCopy);
        XCTAssertTrue( (0 == utf8_StrCmpAW("abc", pStr)) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_WStrC_NewW(
    const
    char        *pTestName
)
{
    WSTRC_DATA	*pObj = OBJ_NIL;
    WSTRC_DATA	*pCopy = OBJ_NIL;
    const
    int32_t     *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = WStrC_NewW(L"abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = WStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = WStrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pObj,L"abc")) );
        pCopy = WStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = WStrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = WStrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pObj,L"abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_WStrC_NewConW(
    const
    char        *pTestName
)
{
    WSTRC_DATA	*pObj = OBJ_NIL;
    WSTRC_DATA	*pCopy = OBJ_NIL;
    const
    int32_t     *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = WStrC_NewConW(L"abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = WStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = WStrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pObj,L"abc")) );
        pCopy = WStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = WStrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = WStrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pObj,L"abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_WStrC_Mid(
    const
    char        *pTestName
)
{
    WSTRC_DATA	*pObj = OBJ_NIL;
    WSTRC_DATA	*pCopy = OBJ_NIL;
    const
    int32_t     *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = WStrC_NewConW(L"abcdef");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = WStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (6 == len) );
        pStr = WStrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pObj,L"abcdef")) );

        pCopy = WStrC_Mid(pObj, 1, 6);
        XCTAssertTrue( (pCopy != pObj) );
        len = WStrC_getLength(pCopy);
        XCTAssertTrue( (6 == len) );
        pStr = WStrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pCopy,L"abcdef")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        
        pCopy = WStrC_Mid(pObj, 3, 4);
        XCTAssertTrue( (pCopy != pObj) );
        len = WStrC_getLength(pCopy);
        XCTAssertTrue( (4 == len) );
        pStr = WStrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pCopy,L"cdef")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        
        pCopy = WStrC_Mid(pObj, 6, 1);
        XCTAssertTrue( (pCopy != pObj) );
        len = WStrC_getLength(pCopy);
        XCTAssertTrue( (1 == len) );
        pStr = WStrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStrC_CompareW(pCopy,L"f")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        
        //pCopy = WStrC_Mid(pObj, 1, 7);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );
        
        //pCopy = WStrC_Mid(pObj, 3, 0);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );
        
        //pCopy = WStrC_Mid(pObj, 6, 7);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_WStrC);
  TINYTEST_ADD_TEST(test_WStrC_Mid,setUp,tearDown);
  TINYTEST_ADD_TEST(test_WStrC_NewConW,setUp,tearDown);
  TINYTEST_ADD_TEST(test_WStrC_NewW,setUp,tearDown);
  TINYTEST_ADD_TEST(test_WStrC_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_WStrC);





