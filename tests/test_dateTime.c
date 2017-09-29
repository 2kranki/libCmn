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
#include    <dateTime_internal.h>



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






int         test_dateTime_OpenClose(
    const
    char            *pTestName
)
{
    DATETIME_DATA   *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = dateTime_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dateTime_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dateTime_Current(
    const
    char        *pTestName
)
{
    DATETIME_DATA       *pObj = OBJ_NIL;
    time_t              current;
    struct tm           *pTime;
    int16_t             work;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    current = time(NULL);
    pTime = gmtime(&current);
    ++pTime->tm_mon;
    pTime->tm_year += 1900;
    
    pObj = dateTime_NewCurrent();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        work = dateTime_getMonth(pObj);
        XCTAssertTrue((work == pTime->tm_mon));
        work = dateTime_getDay(pObj);
        XCTAssertTrue((work == pTime->tm_mday));
        work = dateTime_getYear(pObj);
        XCTAssertTrue((work == pTime->tm_year));
        work = dateTime_getHours(pObj);
        XCTAssertTrue((work == pTime->tm_hour));
        work = dateTime_getMins(pObj);
        XCTAssertTrue((work == pTime->tm_min));
        work = dateTime_getSecs(pObj);
        XCTAssertTrue((work == pTime->tm_sec));
        work = dateTime_getMilli(pObj);
        XCTAssertTrue((work == 0));
        
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_dateTime);
  TINYTEST_ADD_TEST(test_dateTime_Current,setUp,tearDown);
  TINYTEST_ADD_TEST(test_dateTime_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_dateTime);





