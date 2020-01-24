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
#include    <W32StrC_internal.h>



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






int         test_W32StrC_OpenClose(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = W32StrC_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = W32StrC_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pCopy = W32StrC_Copy(pObj);
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



int         test_W32StrC_NewA(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = W32StrC_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (0 == utf8_StrCmpAW32("abc",pStr)) );
        pCopy = W32StrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (0 == utf8_StrCmpAW32("abc", pStr)) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_W32StrC_NewW(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = W32StrC_NewW32(L"abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj, L"abc")) );
        pCopy = W32StrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj, L"abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_W32StrC_NewConW(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = W32StrC_NewConW32(L"abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj,L"abc")) );
        pCopy = W32StrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj,L"abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_W32StrC_Mid(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = W32StrC_NewConW32(L"abcdef");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (6 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj,L"abcdef")) );

        pCopy = W32StrC_Mid(pObj, 1, 6);
        XCTAssertTrue( (pCopy != pObj) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (6 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pCopy,L"abcdef")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        
        pCopy = W32StrC_Mid(pObj, 3, 4);
        XCTAssertTrue( (pCopy != pObj) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (4 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pCopy,L"cdef")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        
        pCopy = W32StrC_Mid(pObj, 6, 1);
        XCTAssertTrue( (pCopy != pObj) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (1 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pCopy,L"f")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        
        //pCopy = W32StrC_Mid(pObj, 1, 7);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );
        
        //pCopy = W32StrC_Mid(pObj, 3, 0);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );
        
        //pCopy = W32StrC_Mid(pObj, 6, 7);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_W32StrC);
  TINYTEST_ADD_TEST(test_W32StrC_Mid,setUp,tearDown);
  TINYTEST_ADD_TEST(test_W32StrC_NewConW,setUp,tearDown);
  TINYTEST_ADD_TEST(test_W32StrC_NewW,setUp,tearDown);
  TINYTEST_ADD_TEST(test_W32StrC_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_W32StrC);





