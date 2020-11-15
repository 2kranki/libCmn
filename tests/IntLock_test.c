// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 03/13/2020 09:43:27
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
#include    <IntLock.h>
#ifdef  INTLOCK_JSON_SUPPORT
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

#ifdef  INTLOCK_JSON_SUPPORT
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






int             test_IntLock_OpenClose (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    INTLOCK_DATA	*pObj = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = IntLock_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pObj = IntLock_Init(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pObj) );

        pObj = IntLock_Free(pObj);
        TINYTEST_TRUE( (OBJ_NIL == pObj) );
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_IntLock_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    INTLOCK_DATA	obj = {0};
    INTLOCK_DATA    *pObj;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = IntLock_Init(&obj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = IntLock_Lock(pObj);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc = IntLock_Unlock(pObj);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        pObj = IntLock_Free(pObj);
        TINYTEST_TRUE( (OBJ_NIL == pObj) );
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_IntLock_Test02 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    INTLOCK_DATA    obj = {0};
    INTLOCK_DATA    *pObj;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = IntLock_Init(&obj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = IntLock_TryLock(pObj);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc = IntLock_Unlock(pObj);
        TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        pObj = IntLock_Free(pObj);
        TINYTEST_TRUE( (OBJ_NIL == pObj) );
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_IntLock);
    TINYTEST_ADD_TEST(test_IntLock_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_IntLock_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_IntLock_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_IntLock);





