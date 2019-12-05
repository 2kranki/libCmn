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
#include    <sidx_internal.h>



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






int         test_sidx_OpenClose(
    const
    char        *pTestName
)
{
    SIDX_DATA       *pObj = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    bool            fRc;
    ASTR_DATA       *pStr;
    uint32_t        index;
    size_t          offset;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = sidx_Alloc(4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = sidx_Init( pObj, 2 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (4 == sidx_getSize(pObj)) );
        
        iMax = 8;
        for (i=0; i<iMax; ++i) {
            fRc = sidx_AddIndex(pObj, i, (i*2));
            XCTAssertTrue( (fRc) );
            XCTAssertTrue( (2 == sidx_getInterval(pObj)) );
        }
        XCTAssertTrue( (4 == pObj->used) );
        XCTAssertTrue( (6 == pObj->max) );
        
        pStr = sidx_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        iMax = 16;
        for (i=8; i<iMax; ++i) {
            fRc = sidx_AddIndex(pObj, i, (i*2));
            XCTAssertTrue( (fRc) );
            XCTAssertTrue( (4 == sidx_getInterval(pObj)) );
        }
        XCTAssertTrue( (4 == pObj->used) );
        
        pStr = sidx_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fRc = sidx_FindIndex(pObj, 3, &index, &offset);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (0 == index) );
        XCTAssertTrue( (0 == offset) );
        
        fRc = sidx_FindIndex(pObj, 5, &index, &offset);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (4 == index) );
        XCTAssertTrue( (8 == offset) );
        
        fRc = sidx_FindIndex(pObj, 15, &index, &offset);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (12 == index) );
        XCTAssertTrue( (24 == offset) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_sidx);
  TINYTEST_ADD_TEST(test_sidx_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_sidx);





