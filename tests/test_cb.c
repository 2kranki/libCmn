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
#include    <cb_internal.h>
#include    <psxThread.h>



#define NUM_STR     20

static
char        *StrArray[NUM_STR] = {
//   123456789
	"String  1",
	"String  2",
	"String  3",
	"String  4",
	"String  5",
	"String  6",
	"String  7",
	"String  8",
	"String  9",
    "String 10",
    "String 11",
    "String 12",
    "String 13",
    "String 14",
    "String 15",
    "String 16",
    "String 17",
    "String 18",
    "String 19",
    "String 20"
};



typedef struct buffer_entry_s {
    const
    char            *pStr;
} BUFFER_ENTRY;


// Output Queue is written by the separate task.
static
BUFFER_ENTRY    outputQueue[NUM_STR * 2] = {0};
static
int             outputQueueEnd = -1;



static
void            addOutput (const char *pStr)
{
    
    ++outputQueueEnd;
    outputQueue[outputQueueEnd].pStr = pStr;
    printf("addOutput()  %3d - %s\n", outputQueueEnd, outputQueue[outputQueueEnd].pStr);
    
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
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_cb_OpenClose(
    const
    char        *pTestName
)
{
    CB_DATA	*pObj = OBJ_NIL;
   
    pObj = cb_Alloc(10, 8);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = cb_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_cb_CounterOverflow(
    const
    char        *pTestName
)
{
	CB_DATA			*cbp;
    uint16_t        i;
    uint16_t        j;
    bool            fRc;
    char            msg[10];
    
	cbp = cb_Alloc(10, 10);
    XCTAssertFalse( (NULL == cbp) );
	cbp = cb_Init( cbp );
    XCTAssertFalse( (NULL == cbp) );
    
    // Empty Queue - positive to negative overflow
    cbp->numRead = 32766;
    cbp->numWritten = 32766;
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );

    for (i=0; i<8; ++i) {
        fRc = cb_Put(cbp, StrArray[i]);
        XCTAssertTrue( (fRc) );
        fRc = cb_isEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = cb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = cb_Get(cbp, &msg);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (0 == strcmp(msg,StrArray[i])) );
        
    }
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
    // Empty Queue - negative to positive overflow
    cbp->numRead = -32766;
    cbp->numWritten = -32766;
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
    for (i=0; i<8; ++i) {
        fRc = cb_Put(cbp, StrArray[i]);
        XCTAssertTrue( (fRc) );
        fRc = cb_isEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = cb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = cb_Get(cbp, &msg);
        XCTAssertTrue( (fRc) );
        //STAssertTrue( (aVal == i), @"cb8_Get value failed" );
        
    }
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
	obj_Release( cbp );
    cbp = NULL;
    
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
            psxThread_Wait(1000);
        }
        psxThread_setWait(pThread, 500);
        fRc = psxThread_Resume(pThread);
        while (!psxThread_IsRunning(pThread)) {
            psxThread_Wait(1000);
        }
        
        printf("Loading Buffer...\n");
        for (i=0; i<NUM_STR; ++i) {
            printf("  Put(%d) - %s\n", i, StrArray[i]);
            cb_Put(pCB, &StrArray[i]);
        }
        psxThread_Wait(10000);
        
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
    
    return 1;
}





TINYTEST_START_SUITE(test_cb);
  TINYTEST_ADD_TEST(test_cb_Operation,setUp,tearDown);
  //TINYTEST_ADD_TEST(test_cb_CounterOverflow,setUp,tearDown);
  TINYTEST_ADD_TEST(test_cb_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cb);





