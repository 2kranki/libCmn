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
#include    <audioWAV_internal.h>



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






int         test_audioWAV_OpenClose(
    const
    char        *pTestName
)
{
    AUDIOWAV_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioWAV_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = audioWAV_Init( pObj, 2, 22050, 8 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_audioWAV_Silence(
    const
    char        *pTestName
)
{
    AUDIOWAV_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioWAV_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioWAV_Init(pObj, 2, 44100, 16);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioWAV_AppendSilence(pObj, 10000);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pPath = path_NewA("~/audioTest01.wav");
        eRc = audioWAV_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_audioWAV_SineWave(
    const
    char        *pTestName
)
{
    AUDIOWAV_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = audioWAV_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = audioWAV_Init(pObj, 1, 11025, 16);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = audioWAV_AppendSineWave(pObj, 740, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pPath = path_NewA("~/audioTest02.wav");
        eRc = audioWAV_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_audioWAV);
  TINYTEST_ADD_TEST(test_audioWAV_SineWave,setUp,tearDown);
  TINYTEST_ADD_TEST(test_audioWAV_Silence,setUp,tearDown);
  TINYTEST_ADD_TEST(test_audioWAV_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_audioWAV);





