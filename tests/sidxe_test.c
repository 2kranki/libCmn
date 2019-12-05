/*
 *	Generated 12/18/2018 10:26:03
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
#include    <sidxe_internal.h>



int             setUp(
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


int             tearDown(
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






int             test_sidxe_OpenClose(
    const
    char            *pTestName
)
{
    SIDXE_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = sidxe_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = sidxe_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_sidx_General01 (
    const
    char        *pTestName
)
{
    SIDXE_DATA      *pObj = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    bool            fRc;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    SRCLOC          loc;
    SRCLOC          fnd;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = sidxe_NewWithMax(4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (4 == sidxe_getMax(pObj)) );
        
        iMax = 4;
        for (i=0; i<iMax; ++i) {
            loc.lineNo = i;
            loc.offset = i << 1;
            eRc = sidxe_Add(pObj, &loc);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = sidxe_FindLineNo(pObj, i, &fnd);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        XCTAssertTrue( (4 == sidxe_getSize(pObj)) );
        XCTAssertTrue( (4 == sidxe_getMax(pObj)) );
        XCTAssertTrue( (1 == sidxe_getInterval(pObj)) );

        pStr = sidxe_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        iMax = 7;
        for (i=4; i<iMax; ++i) {
            loc.lineNo = i;
            loc.offset = i << 1;
            eRc = sidxe_Add(pObj, &loc);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = sidxe_FindLineNo(pObj, i, &fnd);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        XCTAssertTrue( (4 == sidxe_getSize(pObj)) );
        XCTAssertTrue( (4 == sidxe_getMax(pObj)) );
        XCTAssertTrue( (2 == sidxe_getInterval(pObj)) );
        
        pStr = sidxe_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = sidxe_FindLineNo(pObj, 0, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == fnd.lineNo) );
        XCTAssertTrue( (0 == fnd.offset) );
        
        eRc = sidxe_FindLineNo(pObj, 1, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == fnd.lineNo) );
        XCTAssertTrue( (0 == fnd.offset) );
        
        eRc = sidxe_FindLineNo(pObj, 2, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == fnd.lineNo) );
        XCTAssertTrue( (4 == fnd.offset) );
        
        eRc = sidxe_FindLineNo(pObj, 3, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == fnd.lineNo) );
        XCTAssertTrue( (4 == fnd.offset) );
        
        eRc = sidxe_FindLineNo(pObj, 7, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == fnd.lineNo) );
        XCTAssertTrue( (12 == fnd.offset) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_sidxe);
    TINYTEST_ADD_TEST(test_sidx_General01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_sidxe_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_sidxe);





