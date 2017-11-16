/*
 *	Generated 11/04/2017 09:37:49
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
#include    <msgData_internal.h>



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






int         test_msgData_OpenClose(
    const
    char        *pTestName
)
{
    MSGDATA_DATA	*pObj = OBJ_NIL;
    const
    char            *pData = "01234567";
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = msgData_New(1, 0, (strlen(pData) + 1), (void *)pData);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE( (1 == msgData_getOrigin(pObj)) );
        TINYTEST_TRUE( (0 == msgData_getDestination(pObj)) );
        TINYTEST_TRUE( ((strlen(pData)+1) == msgData_getSize(pObj)) );
        TINYTEST_TRUE( (0 == strcmp(pData, msgData_getData(pObj))) );
        printf("   num origin dest len text\n");
        fprintf(stderr, "   %2d    %2d    %2d   %2d \"%s\"\n",
               msgData_getNum32(pObj),
               msgData_getOrigin(pObj),
               msgData_getDestination(pObj),
               msgData_getSize(pObj),
               msgData_getData(pObj)
               );
        printf("   len includes trailing NUL.\n");


        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_msgData);
    TINYTEST_ADD_TEST(test_msgData_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_msgData);





