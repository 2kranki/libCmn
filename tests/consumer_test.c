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
#include    <consumer_internal.h>



#define NUM_STR     10

static
char        *StrArray[NUM_STR] = {
//   123456789012
    "String    1",
    "String    2",
    "String    3",
    "String    4",
    "String    5",
    "String    6",
    "String    7",
    "String    8",
    "String    9",
    "String   10"
};



static
void        printMsg(
    void        *pObj,
    void        *pMsg
)
{
    fprintf(stderr, "  Recieved - %s\n", pMsg);
}






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






int             test_consumer_OpenClose(
    const
    char            *pTestName
)
{
    CONSUMER_DATA	*pObj = OBJ_NIL;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = consumer_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = consumer_Init( pObj, 12, 4, (void *)printMsg, pObj);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        printf("Sending Messages...\n");
        for (i=0; i<NUM_STR; ++i) {
            printf("  Sending %s...\n", StrArray[i]);
            consumer_SendMessage(pObj, StrArray[i]);
        }
       
        psxThread_Wait(2000); 
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_consumer);
  TINYTEST_ADD_TEST(test_consumer_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_consumer);





