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
#include    <Path.h>
#include    <trace.h>
#include    <audioCW_internal.h>



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






int         test_audioCW_OpenClose(
    const
    char        *pTestName
)
{
    AUDIOCW_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioCW_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = audioCW_Init( pObj, 1, 11025, 8, 740 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = audioCW_CalculateTiming(pObj, 15, 15);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        eRc = audioCW_PutTextW32(pObj, 5, L"PARIS");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        pPath = Path_NewA("~/cw_15_15_PARIS.wav");
        eRc = audioCW_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_audioCW_Text01(
    const
    char        *pTestName
)
{
    AUDIOCW_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioCW_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioCW_Init( pObj, 1, 11025, 8, 740 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioCW_CalculateTiming(pObj, 15, 15);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        eRc = audioCW_PutTextW32(pObj, 5, L"PARIS");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        pPath = Path_NewA("~/cw_15_15_PARIS.wav");
        eRc = audioCW_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_audioCW_Text02(
    const
    char        *pTestName
)
{
    AUDIOCW_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioCW_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioCW_Init( pObj, 1, 11025, 8, 740 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioCW_CalculateTiming(pObj, 15, 15);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        eRc = audioCW_PutTextW32(pObj, 5, L"IRYNA");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        pPath = Path_NewA("~/cw_15_15_IRYNA.wav");
        eRc = audioCW_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_audioCW_Text03(
    const
    char        *pTestName
)
{
    AUDIOCW_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioCW_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioCW_Init( pObj, 1, 11025, 8, 740 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioCW_CalculateTiming(pObj, 15, 15);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        eRc = audioCW_PutTextW32(pObj, 5, L"DAVIN");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        pPath = Path_NewA("~/cw_15_15_DAVIN.wav");
        eRc = audioCW_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_audioCW_Text04(
    const
    char        *pTestName
)
{
    AUDIOCW_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioCW_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioCW_Init( pObj, 1, 11025, 8, 740 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioCW_CalculateTiming(pObj, 15, 15);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        eRc = audioCW_PutTextW32(pObj, 5, L"DREW");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        pPath = Path_NewA("~/cw_15_15_DREW.wav");
        eRc = audioCW_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_audioCW_Text05(
                                const
                                char        *pTestName
                                )
{
    AUDIOCW_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioCW_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioCW_Init( pObj, 1, 11025, 8, 740 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioCW_CalculateTiming(pObj, 15, 15);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        eRc = audioCW_PutTextW32(pObj, 5, L"DOMINIC");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        pPath = Path_NewA("~/cw_15_15_DOMINIC.wav");
        eRc = audioCW_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_audioCW);
    TINYTEST_ADD_TEST(test_audioCW_Text05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_audioCW_Text04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_audioCW_Text03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_audioCW_Text02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_audioCW_Text01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_audioCW_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_audioCW);





