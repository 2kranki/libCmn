/*
 *	Generated 12/17/2017 07:12:31
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
#include    <SrcError_internal.h>



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

    
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
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






int         test_SrcError_OpenClose(
    const
    char        *pTestName
)
{
    SRCERROR_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcError_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SrcError_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE(obj_IsKindOf(pObj, OBJ_IDENT_SRCERROR));

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_SrcError_Json01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    SRCERROR_DATA   *pObj = OBJ_NIL;
    SRCERROR_DATA   *pObj2 = OBJ_NIL;
    SRCLOC          loc = {1,2,0,3,0,4};
    //SRCLOC          loc2 = {0};
    ASTR_DATA       *pJson = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;


    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcError_NewFromData(16, &loc, "Error - Mistake!");
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE(obj_IsKindOf(pObj, OBJ_IDENT_SRCERROR));
        
        pJson = SrcError_ToJson(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pJson) );
        fprintf(stderr, "%s\n", AStr_getData(pJson));
        pObj2 = SrcError_NewFromJsonString(pJson);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        TINYTEST_TRUE( (16 == SrcError_getSeverity(pObj2)) );
        TINYTEST_TRUE( (1 == SrcError_getLocation(pObj2)->fileIndex) );
        TINYTEST_TRUE( (2 == SrcError_getLocation(pObj2)->colNo) );
        TINYTEST_TRUE( (3 == SrcError_getLocation(pObj2)->lineNo) );
        TINYTEST_TRUE( (4 == SrcError_getLocation(pObj2)->offset) );
        eRc = AStr_CompareA(SrcError_getErrorStr(pObj2), "Error - Mistake!");
        TINYTEST_TRUE( (0 == eRc) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pJson);
        pJson = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_srcError);
    TINYTEST_ADD_TEST(test_SrcError_Json01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcError_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_srcError);





