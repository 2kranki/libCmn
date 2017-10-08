/*
 *	Generated 06/30/2017 09:01:13
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
#include    <enum_internal.h>


static
char	*stringTable[] = {
    "now",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday"
};
static
int             cStringTable = 6;




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






int         test_enum_OpenClose(
    const
    char        *pTestName
)
{
    ENUM_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = enum_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = enum_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( (0 == pObj->max) );
        XCTAssertTrue( (0 == pObj->size) );
        XCTAssertTrue( (0 == pObj->current) );
        XCTAssertTrue( (NULL == pObj->ppArray) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_enum_Test01(
    const
    char        *pTestName
)
{
    ENUM_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    int         i;
    uint32_t    idx = 0;
    const
    char        *pStr = NULL;
    const
    char        *pStrLA = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = enum_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = enum_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( (0 == pObj->max) );
        XCTAssertTrue( (0 == pObj->size) );
        XCTAssertTrue( (0 == pObj->current) );
        XCTAssertTrue( (NULL == pObj->ppArray) );
        
        eRc = enum_Append(pObj, stringTable[0], &idx);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == pObj->max) );
        XCTAssertTrue( (1 == pObj->size) );
        XCTAssertTrue( (0 == pObj->current) );
        XCTAssertFalse( (NULL == pObj->ppArray) );
        
        for (i=1; i<cStringTable; ++i) {
            eRc = enum_Append(pObj, stringTable[i], &idx);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            //XCTAssertTrue( (2 == pObj->max) );
            XCTAssertTrue( (idx == pObj->size) );
            XCTAssertTrue( (0 == pObj->current) );
            XCTAssertFalse( (NULL == pObj->ppArray) );
        }
        XCTAssertTrue( (cStringTable == pObj->size) );
        XCTAssertTrue( (cStringTable == enum_Remaining(pObj)) );
        
        eRc = enum_Next(pObj, 1, (void **)&pStr, &idx);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (idx == 1) );
        XCTAssertTrue( (0 == strcmp(pStr, stringTable[0])) );
        XCTAssertTrue( (1 == pObj->current) );
        
        for (i=1; i<cStringTable; ++i) {
            eRc = enum_LookAhead(pObj, 0, (void **)&pStrLA);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = enum_Next(pObj, 1, (void **)&pStr, &idx);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            XCTAssertTrue( (pStr == pStrLA) );
            XCTAssertTrue( (idx == 1) );
            XCTAssertTrue( (0 == strcmp(pStr, stringTable[i])) );
            XCTAssertTrue( (i+1 == pObj->current) );
            XCTAssertFalse( (NULL == pObj->ppArray) );
        }
        XCTAssertTrue( (0 == enum_Remaining(pObj)) );
        
        eRc = enum_Next(pObj, 1, (void **)&pStr, &idx);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (idx == 0) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_enum);
  TINYTEST_ADD_TEST(test_enum_Test01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_enum_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_enum);





