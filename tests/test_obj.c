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






int         test_obj_OpenClose(
    const
    char        *pTestName
)
{
	OBJ_DATA    *pObj;
    uint16_t    size = 200;
    bool        fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = obj_Alloc(size);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
    XCTAssertTrue( (OBJ_IDENT_OBJ == obj_getIdent(pObj)) );
    XCTAssertTrue( (size == obj_getSize(pObj)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
    pObj = obj_Init(pObj, size, OBJ_IDENT_CON);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (1 == obj_getRetainCount(pObj)) );
    XCTAssertTrue( (OBJ_IDENT_CON == obj_getIdent(pObj)) );
    XCTAssertTrue( (size == obj_getSize(pObj)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
    XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_INIT)) );
    if (pObj) {

        fRc = obj_FlagOn(pObj, 5);
        XCTAssertTrue( (fRc) );
        fRc = obj_IsFlag(pObj, 5);
        XCTAssertTrue( (fRc) );
        fRc = obj_FlagOff(pObj, 5);
        XCTAssertTrue( (fRc) );
        fRc = obj_IsFlag(pObj, 5);
        XCTAssertTrue( (!fRc) );
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_INIT)) );
        
        fRc = obj_FlagOn(pObj, 15);
        XCTAssertTrue( (fRc) );
        fRc = obj_IsFlag(pObj, 15);
        XCTAssertTrue( (fRc) );
        fRc = obj_FlagOff(pObj, 15);
        XCTAssertTrue( (fRc) );
        fRc = obj_IsFlag(pObj, 15);
        XCTAssertTrue( (!fRc) );
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_INIT)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_obj);
  TINYTEST_ADD_TEST(test_obj_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_obj);





