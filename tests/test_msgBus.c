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
#include    <cmn_defs.h>
#include    <msgBus_internal.h>


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




typedef struct buffer_entry_s {
    const
    char            *pObj;
    const
    char            *pMsg;
} BUFFER_ENTRY;




// Output Queue is written by the separate task.
static
BUFFER_ENTRY    outputQueue[NUM_STR * (NUM_OBJ * 2)] = {0};
static
int             outputQueueEnd = -1;



static
void            addOutput(const char *pObj, const char *pMsg)
{
    
    ++outputQueueEnd;
    outputQueue[outputQueueEnd].pObj = pObj;
    outputQueue[outputQueueEnd].pMsg = pMsg;
    
}



void        printMsg(
    void        *pObj,
    void        **ppMsg
)
{
    fprintf(stderr, "    Rcvd for: %s   msg: %s\n", pObj, *ppMsg);
    addOutput(pObj, *ppMsg);
}






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

    
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_msgBus_Broadcast01(
    const
    char        *pTestName
)
{
    MSGBUS_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    int         i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = msgBus_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = msgBus_Init( pObj, sizeof(const char *), 4 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    obj_TraceSet(pObj, true);
    if (pObj) {

        printf("Registering Receivers...\n");
        for (i=0; i<NUM_OBJ; ++i) {
            eRc = msgBus_Register(pObj, (void *)printMsg, StrObj[i]);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }
        TINYTEST_TRUE( (msgBus_getRegistrySize(pObj) == NUM_OBJ) );

        printf("Broadcasting to all Receivers...\n");
        for (i=0; i<NUM_STR; ++i) {
            printf("  Broadcasting %s...\n", StrArray[i]);
            eRc = msgBus_Broadcast(pObj, (void *)0, (void *)&StrArray[i]);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }

        psxThread_Wait(10000);
        printf("\n\n\n");
        printf("Output Queue(%d):\n", outputQueueEnd+1);
        for (i=0; i<outputQueueEnd+1; ++i) {
            BUFFER_ENTRY    *pEntry = &outputQueue[i];
            if (pEntry->pObj) {
                printf("  %2d %s - %s\n", i, pEntry->pObj, pEntry->pMsg);
            }
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;

        psxThread_Wait(10000);
        printf("\n\n\n");
        printf("Output Queue(%d):\n", outputQueueEnd+1);
        for (i=0; i<outputQueueEnd+1; ++i) {
            BUFFER_ENTRY    *pEntry = &outputQueue[i];
            if (pEntry->pObj) {
                printf("  %2d %s - %s\n", i, pEntry->pObj, pEntry->pMsg);
            }
        }
        
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_msgBus);
  TINYTEST_ADD_TEST(test_msgBus_Broadcast01,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_msgBus);





