/*
 *	Generated 05/31/2017 20:00:00
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
#include    <test_defs.h>
#include    <msgBus_internal.h>
#include    <msgData_internal.h>
#include    <objTest_internal.h>


#define NUM_OBJ      4
#define NUM_STR     10

/* Other variables */
static
char        *StrObj[NUM_OBJ] = {
//   1234567890
	"Obj1",
	"Obj2",
	"Obj3",
	"Obj4"
};

static
char        *StrArray[NUM_STR] = {
//   1234567890
	"String  1",
	"String  2",
	"String  3",
	"String  4",
	"String  5",
	"String  6",
	"String  7",
	"String  8",
	"String  9",
	"String 10"
};




int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    
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






int             test_msgBus_Broadcast01(
    const
    char            *pTestName
)
{
    MSGBUS_DATA	    *pObj = OBJ_NIL;
    ERESULT         eRc;
    int             i;
    int             iMax;
    OBJMETHOD_DATA  *pMethod = OBJ_NIL;
    OBJTEST_DATA    *pTest = OBJ_NIL;
    int32_t         token = 0;
    MSGDATA_DATA    *pData = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pTest = objTest_New();
    TINYTEST_FALSE( (OBJ_NIL == pTest) );
    pObj = msgBus_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = msgBus_Init(pObj, 20);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    obj_TraceSet(pObj, true);
    if (pObj) {

        printf("Registering %d Receivers...\n", NUM_OBJ);
        // The test receivers just accumulate the messages in the order
        // that they are received into one large array.
        for (i=0; i<NUM_OBJ; ++i) {
            pMethod = objMethod_NewObjectA(pTest, "TestMethod01");
            TINYTEST_FALSE( (OBJ_NIL == pMethod) );
            eRc = msgBus_RegisterObjectMethod(pObj, pMethod, &token);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            printf("  Registered %2d...\n", token);
            obj_Release(pMethod);
            pMethod = OBJ_NIL;
        }
        TINYTEST_TRUE( (msgBus_getRegistrySize(pObj) == NUM_OBJ) );

        printf("Broadcasting %d messages to all Receivers...\n", NUM_STR);
        for (i=0; i<NUM_STR; ++i) {
            printf("  Broadcasting %2d - %s...\n", i+1, StrArray[i]);
            eRc = msgBus_Broadcast(pObj, 1, 0, (strlen(StrArray[i]) + 1), (void *)StrArray[i]);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }

        printf("\n\nWaiting a little to give broadcast a little time.\n");
        psxThread_Wait(2000);
        printf("\n\n\n");

        // Display the array as mentioned above.
        iMax = objArray_getSize(pTest->pArray);
        printf("Output Queue(%d):\n", iMax);
        printf("   i num origin dest len text\n");
        for (i=0; i<iMax; ++i) {
            pData = objArray_Get(pTest->pArray, i+1);
            if (pData) {
                printf("  %2d %2d    %2d    %2d   %2d %s\n",
                       i,
                       msgData_getNum32(pData),
                       msgData_getOrigin(pData),
                       msgData_getDestination(pData),
                       msgData_getSize(pData),
                       msgData_getData(pData)
                );
            }
        }
        printf("Done\n");

        obj_Release(pObj);
        pObj = OBJ_NIL;

    }
    obj_Release(pTest);
    pTest = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_msgBus);
  TINYTEST_ADD_TEST(test_msgBus_Broadcast01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_msgBus);





