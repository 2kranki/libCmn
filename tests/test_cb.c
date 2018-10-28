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
#include    <test_defs.h>
#include    <trace.h>
#include    <cb_internal.h>
#include    <psxMutex.h>
#include    <psxThread.h>



#define ELEM_SIZE   12          /* includes NUL */
#define NUM_STR     20

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
    "String   10",
    "String   11",
    "String   12",
    "String   13",
    "String   14",
    "String   15",
    "String   16",
    "String   17",
    "String   18",
    "String   19",
    "String   20"
};



typedef struct buffer_entry_s {
    const
    char            *pStr;
} BUFFER_ENTRY;


// Output Queue is written by the separate task.
static
BUFFER_ENTRY    outputQueue[NUM_STR * 2] = {0};
static
volatile
int             outputQueueEnd = -1;
static
PSXMUTEX_DATA   *pMutex = OBJ_NIL;



static
void            addOutput (const char *pStr)
{
    
    psxMutex_Lock(pMutex);
    ++outputQueueEnd;
    outputQueue[outputQueueEnd].pStr = pStr;
    printf("addOutput()  %3d - %s\n", outputQueueEnd, outputQueue[outputQueueEnd].pStr);
    psxMutex_Unlock(pMutex);

}



static
CB_DATA     *pCB = OBJ_NIL;







static
void *          getRoutine(
    void            *pVoid
)
{
    const
    char            *pStr = NULL;
    
    cb_Get(pCB, &pStr);
    if (pStr) {
        addOutput(pStr);
    }

    return NULL;
}




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
    fprintf(stderr, "\ttrace_SharedReset()\n");
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
    fprintf(stderr, "\tmem_Release()\n");
    pCB = OBJ_NIL;
    
    return 1; 
}






int         test_cb_OpenClose(
    const
    char        *pTestName
)
{
    CB_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = cb_Alloc(ELEM_SIZE, 8);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = cb_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cb_CounterOverflow(
    const
    char        *pTestName
)
{
	CB_DATA			*pCB;
    uint16_t        i;
    uint16_t        j;
    bool            fRc;
    char            msg[ELEM_SIZE];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
	pCB = cb_Alloc(ELEM_SIZE, 10);
    fprintf(stderr, "\tAlloc(12,10) = %p\n", pCB);
    XCTAssertFalse( (NULL == pCB) );
	pCB = cb_Init( pCB );
    fprintf(stderr, "\tInit(12,10) = %p\n", pCB);
    XCTAssertFalse( (NULL == pCB) );
    
    // Empty Queue - positive to negative overflow
    pCB->numRead = 32766;
    pCB->numWritten = 32766;
    
    fRc = cb_isEmpty(pCB);
    XCTAssertTrue( (fRc) );

    for (i=0; i<8; ++i) {
        fRc = cb_Put(pCB, StrArray[i]);
        fprintf(stderr, "\tPut(%d)(%c) = %s\n", i, (fRc ? 't' : 'f'), StrArray[i]);
        XCTAssertTrue( (fRc) );
        fRc = cb_isEmpty(pCB);
        XCTAssertFalse( (fRc) );
        j = cb_Count(pCB);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = cb_Get(pCB, &msg);
        fprintf(stderr, "\tGet(%d)(%c) = %s\n", i, (fRc ? 't' : 'f'), msg);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (0 == strcmp(msg,StrArray[i])) );
        
    }
    
    fRc = cb_isEmpty(pCB);
    XCTAssertTrue( (fRc) );
    
    // Empty Queue - negative to positive overflow
    pCB->numRead = -32766;
    pCB->numWritten = -32766;
    
    fRc = cb_isEmpty(pCB);
    XCTAssertTrue( (fRc) );
    
    for (i=0; i<8; ++i) {
        fRc = cb_Put(pCB, StrArray[i]);
        fprintf(stderr, "\tPut(%d)(%c) = %s\n", i, (fRc ? 't' : 'f'), StrArray[i]);
        XCTAssertTrue( (fRc) );
        fRc = cb_isEmpty(pCB);
        XCTAssertFalse( (fRc) );
        j = cb_Count(pCB);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = cb_Get(pCB, &msg);
        fprintf(stderr, "\tGet(%d)(%c) = %s\n", i, (fRc ? 't' : 'f'), msg);
        XCTAssertTrue( (fRc) );
        //STAssertTrue( (aVal == i), @"cb8_Get value failed" );
        
    }
    
    fRc = cb_isEmpty(pCB);
    fprintf(stderr, "\tisEmpty(%c)\n", (fRc ? 't' : 'f'));
    XCTAssertTrue( (fRc) );
    
	obj_Release( pCB );
    fprintf(stderr, "\tobj_Release()\n");
    pCB = NULL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cb_Operation(
    const
    char        *pTestName
)
{
    int             i;
    PSXTHREAD_DATA  *pThread = OBJ_NIL;
    bool            fRc;
    
    pMutex = psxMutex_New();
    XCTAssertFalse( (OBJ_NIL == pMutex) );
    fprintf(stderr, "Performing: %s\n", pTestName);
    printf("Creating Buffer...\n");
    pCB = cb_Alloc(sizeof(BUFFER_ENTRY), 4);
    XCTAssertFalse( (OBJ_NIL == pCB) );
    pCB = cb_Init( pCB );
    XCTAssertFalse( (OBJ_NIL == pCB) );
    if (pCB) {
        obj_TraceSet(pCB, true);
 
        printf("Starting Reader Thread...\n");
        pThread = psxThread_Alloc( );
        XCTAssertFalse( (OBJ_NIL == pThread) );
        pThread = psxThread_Init(pThread, getRoutine, NULL, 0);
        if (OBJ_NIL == pThread) {
            printf("ERROR:  pthread_create errno=%d\n", errno);
            exit(1);
        }
        fRc = psxThread_Pause(pThread);
        XCTAssertTrue( (fRc) );
        while (!psxThread_IsPaused(pThread)) {
            psxThread_Wait(1000);       // Wait 1 sec.
        }
        psxThread_setWait(pThread, 500);
        fRc = psxThread_Resume(pThread);
        while (!psxThread_IsRunning(pThread)) {
            psxThread_Wait(1000);       // Wait 1 sec.
        }
        
        printf("Loading Buffer...\n");
        for (i=0; i<NUM_STR; ++i) {
            printf("  Put(%d) - %s\n", i, StrArray[i]);
            cb_Put(pCB, &StrArray[i]);
        }
        psxThread_Wait(10000);          // Wait 10 secs.
        
        printf("\n\n");
        printf("Output Queue(%d):\n", outputQueueEnd+1);
        for (i=0; i<outputQueueEnd+1; ++i) {
            if (outputQueue[i].pStr) {
                printf("  %3d - %s\n", i, outputQueue[i].pStr);
            }
        }
        
        cb_Pause(pCB);
        psxThread_Terminate(pThread);
        while (!psxThread_IsEnded(pThread)) {
            psxThread_Wait(100);
        }
        obj_Release(pThread);
        pThread = NULL;
        obj_Release(pCB);
        pCB = NULL;
    }
    obj_Release(pMutex);
    pMutex = NULL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}





TINYTEST_START_SUITE(test_cb);
  TINYTEST_ADD_TEST(test_cb_Operation,setUp,tearDown);
  TINYTEST_ADD_TEST(test_cb_CounterOverflow,setUp,tearDown);
  TINYTEST_ADD_TEST(test_cb_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cb);





