// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/29/2020 13:34:28
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
#include    <DateTime_internal.h>
#ifdef  DATETIME_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



int             setUp (
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


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

#ifdef  DATETIME_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_DateTime_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DATETIME_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = DateTime_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = DateTime_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_DATETIME);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_DateTime_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DATETIME_DATA	    *pObj1 = OBJ_NIL;
    DATETIME_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(DATETIME_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = DateTime_NewCurrent( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_DATETIME);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = DateTime_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = DateTime_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DATETIME);
        TINYTEST_TRUE( (fRc) );
        eRc = DateTime_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = DateTime_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DATETIME);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(DATETIME_JSON_SUPPORT)
        pStr = DateTime_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = DateTime_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DATETIME);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = DateTime_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_DateTime_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    DATETIME_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = DateTime_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_DATETIME);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_DateTime_Current(
    const
    char        *pTestName
)
{
    DATETIME_DATA       *pObj = OBJ_NIL;
    DATETIME_DATA       *pObj2 = OBJ_NIL;
    time_t              current;
    struct tm           *pTime;
    int16_t             work;
    ASTR_DATA           *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    current = time(NULL);
    pTime = gmtime(&current);
    ++pTime->tm_mon;
    pTime->tm_year += 1900;

    pObj = DateTime_NewCurrent();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = DateTime_ToString(pObj);
        fprintf(stderr, "\t%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        work = DateTime_getMonth(pObj);
        XCTAssertTrue((work == pTime->tm_mon));
        work = DateTime_getDay(pObj);
        XCTAssertTrue((work == pTime->tm_mday));
        work = DateTime_getYear(pObj);
        XCTAssertTrue((work == pTime->tm_year));
        work = DateTime_getHours(pObj);
        XCTAssertTrue((work == pTime->tm_hour));
        work = DateTime_getMins(pObj);
        XCTAssertTrue((work == pTime->tm_min));
        work = DateTime_getSecs(pObj);
        XCTAssertTrue((work == pTime->tm_sec));
        work = DateTime_getMilli(pObj);
        XCTAssertTrue((work == 0));

        //obj_Release(pObj);
        //pObj = OBJ_NIL;
    }

    pObj2 = DateTime_NewFromTimeT(current);
    XCTAssertFalse( (OBJ_NIL == pObj2) );
    if (pObj2) {

        pStr = DateTime_ToString(pObj2);
        fprintf(stderr, "\t%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        work = DateTime_getMonth(pObj);
        //fprintf(stderr, "\tMonth: %d %d\n", work, DateTime_getMonth(pObj2));
        XCTAssertTrue((work == DateTime_getMonth(pObj2)));
        work = DateTime_getDay(pObj);
        XCTAssertTrue((work == DateTime_getDay(pObj2)));
        work = DateTime_getYear(pObj);
        XCTAssertTrue((work == DateTime_getYear(pObj2)));
        work = DateTime_getHours(pObj);
        XCTAssertTrue((work == DateTime_getHours(pObj2)));
        work = DateTime_getMins(pObj);
        XCTAssertTrue((work == DateTime_getMins(pObj2)));
        work = DateTime_getSecs(pObj);
        XCTAssertTrue((work == DateTime_getSecs(pObj2)));
        work = DateTime_getMilli(pObj2);
        XCTAssertTrue((work == 0));

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
    }

    obj_Release(pObj);
    pObj = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_DateTime);
    TINYTEST_ADD_TEST(test_DateTime_Current,setUp,tearDown);
    TINYTEST_ADD_TEST(test_DateTime_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_DateTime_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_DateTime_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_DateTime);





