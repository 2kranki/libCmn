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
#include    <JsonIn.h>
#include    <trace.h>
#include    <u32Array_internal.h>



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

    
    JsonIn_RegisterReset();
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






int         test_u32Array_OpenClose(
    const
    char            *pTestName
)
{
    U32ARRAY_DATA   *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u32Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = u32Array_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u32Array_AddGet01(
    const
    char            *pTestName
)
{
    U32ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint32_t        data;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u32Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u32Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=1; i<=64; ++i) {
            eRc = u32Array_AppendData(pObj, i);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }
        
        for (i=1; i<=64; ++i) {
            data = u32Array_Get(pObj, i);
            XCTAssertTrue( (data == i) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u32Array_Sort01(
    const
    char            *pTestName
)
{
    U32ARRAY_DATA   *pObj = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint32_t        data;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u32Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u32Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=8; i>0; --i) {
            eRc = u32Array_AppendData(pObj, i);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }
        
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pObj, 8);
            fprintf(stderr, "\tBefore:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        eRc = u32Array_SortAscending(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pObj, 8);
            fprintf(stderr, "\tAfter:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u32Array_Merge01(
    const
    char            *pTestName
)
{
    U32ARRAY_DATA   *pObj = OBJ_NIL;
    U32ARRAY_DATA   *pObj2 = OBJ_NIL;
    U32ARRAY_DATA   *pObj3 = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    uint32_t        data;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u32Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u32Array_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = u32Array_AppendData(pObj, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj, 4);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj, 5);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj, 7);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj, 9);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj, 10);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pObj, 8);
            fprintf(stderr, "\tArray1:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif

        pObj2 = u32Array_New( );
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        eRc = u32Array_AppendData(pObj2, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj2, 4);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj2, 6);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj2, 8);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = u32Array_AppendData(pObj2, 10);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pObj2, 8);
            fprintf(stderr, "\tArray2:\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif

        pObj3 = u32Array_Merge(pObj, pObj2);
        XCTAssertFalse( (OBJ_NIL == pObj3) );
        XCTAssertTrue( (10 == u32Array_getSize(pObj3)) );
#ifdef NDEBUG
#else
        {
            ASTR_DATA       *pStr = OBJ_NIL;
            pStr = u32Array_ToDebugString(pObj3, 8);
            fprintf(stderr, "\tMerged (Should be 1-10):\n%s\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
#endif
        for (i=0; i<10; ++i) {
            XCTAssertTrue( ((i+1) == u32Array_Get(pObj3, i+1)) );
        }
        obj_Release(pObj3);
        pObj3 = OBJ_NIL;
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_u32Array);
    TINYTEST_ADD_TEST(test_u32Array_Merge01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_u32Array_Sort01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_u32Array_AddGet01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_u32Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_u32Array);





