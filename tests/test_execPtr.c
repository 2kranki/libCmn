/*
 *	Generated 10/07/2017 12:40:01
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
#include    <execPtr_internal.h>



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






int         test_execPtr_OpenClose(
    const
    char        *pTestName
)
{
    EXECPTR_DATA	*pObj = OBJ_NIL;
    void            *fFunc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = execPtr_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = execPtr_Init(pObj, NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fFunc = execPtr_getFunc(pObj);
        TINYTEST_TRUE( (NULL == fFunc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_execPtr_OpenClose2(
    const
    char        *pTestName
)
{
    EXECPTR_DATA	*pObj = OBJ_NIL;
    void            *fFunc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = execPtr_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = execPtr_Init(pObj, (void *)&tearDown);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        fFunc = execPtr_getFunc(pObj);
        TINYTEST_TRUE( (&tearDown == fFunc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_execPtr);
    TINYTEST_ADD_TEST(test_execPtr_OpenClose2,setUp,tearDown);
    TINYTEST_ADD_TEST(test_execPtr_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_execPtr);





