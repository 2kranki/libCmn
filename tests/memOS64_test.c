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
#ifdef  __MACOS64_ENV__
#include    <memOS64_internal.h>
#endif



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






int         test_memOS64_OpenClose(
    const
    char        *pTestName
)
{
#ifdef  __MACOS64_ENV__
    MEMOSX_DATA	*pObj = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
#ifdef  __MACOS64_ENV__
    pObj = memOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = memOSX_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
#endif

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_memOS64_Tests01(
    const
    char        *pTestName
)
{
#ifdef  __MACOS64_ENV__
    MEMOSX_DATA	*pObj = OBJ_NIL;
    void        *pData1;
    void        *pData2;
    bool        fRc;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
#ifdef  __MACOS64_ENV__
    pObj = memOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = memOSX_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pData1 = memOSX_DebugMalloc(pObj,256, __FILE__, __LINE__);
        XCTAssertFalse( (NULL == pData1) );
        fRc = memOSX_DebugFree(pObj, pData1, __FILE__, __LINE__);
        XCTAssertTrue(fRc);
        
        pData2 = memOSX_DebugMalloc(pObj,256, __FILE__, __LINE__);
        XCTAssertFalse( (NULL == pData2) );
        fRc = memOSX_DebugFree(pObj, pData2, __FILE__, __LINE__);
        XCTAssertTrue(fRc);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
#endif

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_memOS64_Tests02(
    const
    char        *pTestName
)
{
#ifdef  __MACOS64_ENV__
    MEMOSX_DATA	*pObj = OBJ_NIL;
    void        *pData1;
    void        *pData2;
    void        *pData3;
    bool        fRc;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
#ifdef  __MACOS64_ENV__
    pObj = memOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = memOSX_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pData1 = memOSX_DebugMalloc(pObj,1, __FILE__, __LINE__);
        XCTAssertFalse( (NULL == pData1) );
        
        pData2 = memOSX_DebugMalloc(pObj,2, __FILE__, __LINE__);
        XCTAssertFalse( (NULL == pData2) );

        pData3 = memOSX_DebugMalloc(pObj,3, __FILE__, __LINE__);
        XCTAssertFalse( (NULL == pData2) );
        
        fRc = memOSX_DebugFree(pObj, pData2, __FILE__, __LINE__);
        XCTAssertTrue(fRc);
        
        fRc = memOSX_DebugFree(pObj, pData3, __FILE__, __LINE__);
        XCTAssertTrue(fRc);
        
        fRc = memOSX_DebugFree(pObj, pData1, __FILE__, __LINE__);
        XCTAssertTrue(fRc);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
#endif

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_memOS64);
  TINYTEST_ADD_TEST(test_memOS64_Tests02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_memOS64_Tests01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_memOS64_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_memOS64);





