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
#include    <srcLoc_internal.h>
#include    <szTbl.h>





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






int         test_srcLoc_OpenClose(
    const
    char            *pTestName
)
{
    SRCLOC_DATA	    *pObj = OBJ_NIL;
    ASTR_DATA       *pAStr = OBJ_NIL;
    SRCLOC_DATA	    *pObj2 = OBJ_NIL;
    static
    const
    char            *pJsonA =   "{ "
                                    "\"objectType\":\"srcLoc\", "
                                    "\"fileIndex\":1, "
                                    "\"offset\":20, "
                                    "\"lineNo\":3, "
                                    "\"colNo\":4 "
                                "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = srcLoc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = srcLoc_InitFLC( pObj, 1, 20, 3, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE( (1 == srcLoc_getFileIndex(pObj)) );
        TINYTEST_TRUE( (20 == srcLoc_getOffset(pObj)) );
        TINYTEST_TRUE( (3 == srcLoc_getLineNo(pObj)) );
        TINYTEST_TRUE( (4 == srcLoc_getColNo(pObj)) );

        pAStr = srcLoc_ToJSON(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pAStr) );
        fprintf(stderr, "JSON='%s'\n", AStr_getData(pAStr));
        TINYTEST_TRUE( (0 == strcmp(pJsonA, AStr_getData(pAStr))) );
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        pObj2 = srcLoc_NewFromJSONStringA(pJsonA);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        TINYTEST_TRUE( (1 == srcLoc_getFileIndex(pObj2)) );
        TINYTEST_TRUE( (20 == srcLoc_getOffset(pObj2)) );
        TINYTEST_TRUE( (3 == srcLoc_getLineNo(pObj2)) );
        TINYTEST_TRUE( (4 == srcLoc_getColNo(pObj2)) );
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_srcLoc);
  TINYTEST_ADD_TEST(test_srcLoc_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_srcLoc);





