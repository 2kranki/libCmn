// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 06/04/2020 10:44:19
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
#include    <LineIndex_internal.h>
#ifdef  LINEINDEX_JSON_SUPPORT
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

#ifdef  LINEINDEX_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_LineIndex_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LINEINDEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = LineIndex_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = LineIndex_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LINEINDEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_LineIndex_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    LINEINDEX_DATA       *pObj1 = OBJ_NIL;
    LINEINDEX_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(LINEINDEX_JSON_SUPPORT)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    uint32_t        i;
    uint32_t        iMax;
    SRCLOC          loc = {0};
    SRCLOC          fnd = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = LineIndex_NewWithMax(4);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_LINEINDEX);
        TINYTEST_TRUE( (fRc) );
        iMax = 7;
        for (i=0; i<iMax; ++i) {
            loc.lineNo = i;
            loc.offset = i << 1;
            eRc = LineIndex_Add(pObj1, &loc);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = LineIndex_Find(pObj1, i, &fnd);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        XCTAssertTrue( (4 == LineIndex_getSize(pObj1)) );
        XCTAssertTrue( (4 == LineIndex_getMax(pObj1)) );
        XCTAssertTrue( (2 == LineIndex_getInterval(pObj1)) );

        // Test assign.
        pObj2 = LineIndex_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = LineIndex_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LINEINDEX);
        TINYTEST_TRUE( (fRc) );
        eRc = LineIndex_Find(pObj2, 3, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == fnd.lineNo) );
        XCTAssertTrue( (4 == fnd.offset) );
        eRc = LineIndex_Find(pObj2, 7, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == fnd.lineNo) );
        XCTAssertTrue( (12 == fnd.offset) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = LineIndex_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LINEINDEX);
        TINYTEST_TRUE( (fRc) );
        eRc = LineIndex_Find(pObj2, 3, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == fnd.lineNo) );
        XCTAssertTrue( (4 == fnd.offset) );
        eRc = LineIndex_Find(pObj2, 7, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == fnd.lineNo) );
        XCTAssertTrue( (12 == fnd.offset) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(LINEINDEX_JSON_SUPPORT)
        pStr = LineIndex_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = LineIndex_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_LINEINDEX);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = LineIndex_Find(pObj2, 3, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == fnd.lineNo) );
        XCTAssertTrue( (4 == fnd.offset) );
        eRc = LineIndex_Find(pObj2, 7, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == fnd.lineNo) );
        XCTAssertTrue( (12 == fnd.offset) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_LineIndex_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    LINEINDEX_DATA  *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = LineIndex_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_LINEINDEX);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = LineIndex_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_LineIndex_General01 (
    const
    char        *pTestName
)
{
    LINEINDEX_DATA  *pObj = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    SRCLOC          loc;
    SRCLOC          fnd;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = LineIndex_NewWithMax(4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( (4 == LineIndex_getMax(pObj)) );

        iMax = 4;
        for (i=0; i<iMax; ++i) {
            loc.lineNo = i;
            loc.offset = i << 1;
            eRc = LineIndex_Add(pObj, &loc);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = LineIndex_Find(pObj, i, &fnd);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        XCTAssertTrue( (4 == LineIndex_getSize(pObj)) );
        XCTAssertTrue( (4 == LineIndex_getMax(pObj)) );
        XCTAssertTrue( (1 == LineIndex_getInterval(pObj)) );

        pStr = LineIndex_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        iMax = 7;
        for (i=4; i<iMax; ++i) {
            loc.lineNo = i;
            loc.offset = i << 1;
            eRc = LineIndex_Add(pObj, &loc);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = LineIndex_Find(pObj, i, &fnd);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        XCTAssertTrue( (4 == LineIndex_getSize(pObj)) );
        XCTAssertTrue( (4 == LineIndex_getMax(pObj)) );
        XCTAssertTrue( (2 == LineIndex_getInterval(pObj)) );

        pStr = LineIndex_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = LineIndex_Find(pObj, 0, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == fnd.lineNo) );
        XCTAssertTrue( (0 == fnd.offset) );

        eRc = LineIndex_Find(pObj, 1, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == fnd.lineNo) );
        XCTAssertTrue( (0 == fnd.offset) );

        eRc = LineIndex_Find(pObj, 2, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == fnd.lineNo) );
        XCTAssertTrue( (4 == fnd.offset) );

        eRc = LineIndex_Find(pObj, 3, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == fnd.lineNo) );
        XCTAssertTrue( (4 == fnd.offset) );

        eRc = LineIndex_Find(pObj, 7, &fnd);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == fnd.lineNo) );
        XCTAssertTrue( (12 == fnd.offset) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_LineIndex);
    TINYTEST_ADD_TEST(test_LineIndex_General01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LineIndex_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LineIndex_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_LineIndex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_LineIndex);





