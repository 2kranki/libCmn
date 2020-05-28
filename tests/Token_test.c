// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/02/2020 15:58:09
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
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <Token_internal.h>



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

    SrcErrors_SharedReset();
    szTbl_SharedReset();
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






int             test_Token_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TOKEN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Token_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Token_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKEN);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Token_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TOKEN_DATA       *pObj1 = OBJ_NIL;
    TOKEN_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(TOKEN_JSON_SUPPORT)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    SRCLOC          loc = {1,2,0,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Token_NewInteger(&loc, 11, 64);
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_TOKEN);
        TINYTEST_TRUE( (fRc) );
        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj1)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj1)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj1)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj1)) );
        XCTAssertTrue( (11 == Token_getClass(pObj1)) );
        XCTAssertTrue( (TOKEN_TYPE_INTEGER == Token_getType(pObj1)) );
        XCTAssertTrue( (64 == Token_getInteger(pObj1)) );
        {
            ASTR_DATA       *pStr = Token_ToDebugString(pObj1, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }


        // Test assign.
        pObj2 = Token_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Token_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TOKEN);
        TINYTEST_TRUE( (fRc) );
        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj2)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj2)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj2)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj2)) );
        XCTAssertTrue( (11 == Token_getClass(pObj2)) );
        XCTAssertTrue( (TOKEN_TYPE_INTEGER == Token_getType(pObj2)) );
        XCTAssertTrue( (64 == Token_getInteger(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Token_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TOKEN);
        TINYTEST_TRUE( (fRc) );
        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj2)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj2)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj2)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj2)) );
        XCTAssertTrue( (11 == Token_getClass(pObj2)) );
        XCTAssertTrue( (TOKEN_TYPE_INTEGER == Token_getType(pObj2)) );
        XCTAssertTrue( (64 == Token_getInteger(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(TOKEN_JSON_SUPPORT)
        pStr = Token_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Token_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TOKEN);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj2)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj2)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj2)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj2)) );
        XCTAssertTrue( (11 == Token_getClass(pObj2)) );
        XCTAssertTrue( (TOKEN_TYPE_INTEGER == Token_getType(pObj2)) );
        XCTAssertTrue( (64 == Token_getInteger(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_Token_Test01(
    const
    char        *pTestName
)
{
    TOKEN_DATA    *pObj = OBJ_NIL;
    SRCLOC      loc = {1,2,0,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = Token_NewInteger(&loc, 11, 64);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( ( 1 == Token_getFileIndex(pObj)) );
        XCTAssertTrue( ( 4 == Token_getOffset(pObj)) );
        XCTAssertTrue( ( 3 == Token_getLineNo(pObj)) );
        XCTAssertTrue( ( 2 == Token_getColNo(pObj)) );
        XCTAssertTrue( (11 == Token_getClass(pObj)) );
        XCTAssertTrue( (64 == Token_getInteger(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Token);
    TINYTEST_ADD_TEST(test_Token_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Token_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Token_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Token);





