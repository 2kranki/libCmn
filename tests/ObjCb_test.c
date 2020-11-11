// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/21/2020 14:01:14
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
#include    <ObjCb_internal.h>
#ifdef  OBJCB_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif
#include    <psxThread.h>


#define NUM_STR     10

/* Other variables */
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
    "String 10"
};



typedef struct buffer_entry_s {
    OBJ_ID          *pObj;
} BUFFER_ENTRY;


// Output Queue is written by the separate task.
static
BUFFER_ENTRY    outputQueue[NUM_STR * 2] = {0};
static
int             outputQueueEnd = -1;



static
void            addOutput (OBJ_ID  *pObj)
{

    ++outputQueueEnd;
    outputQueue[outputQueueEnd].pObj = pObj;
    printf("addOutput()  %3d - %s\n",
           outputQueueEnd,
           AStr_getData((ASTR_DATA *)outputQueue[outputQueueEnd].pObj)
    );

}



static
OBJCB_DATA      *pCB = OBJ_NIL;




static
void *          getRoutine(
    void            *pVoid
)
{
    OBJ_ID          pObj;

    ObjCb_Get(pCB, &pObj);
    if (pObj) {
        addOutput(pObj);
    }

    return NULL;
}




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

#ifdef  OBJCB_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_ObjCb_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJCB_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjCb_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ObjCb_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJCB);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ObjCb_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJCB_DATA	    *pObj1 = OBJ_NIL;
    OBJCB_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(OBJCB_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = ObjCb_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OBJCB);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = ObjCb_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = ObjCb_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJCB);
        TINYTEST_TRUE( (fRc) );
        //eRc = ObjCb_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = ObjCb_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJCB);
        TINYTEST_TRUE( (fRc) );
        //eRc = ObjCb_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(OBJCB_JSON_SUPPORT) && defined(XYZZY)
        pStr = ObjCb_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = ObjCb_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJCB);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = ObjCb_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ObjCb_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    OBJCB_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjCb_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJCB);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_ObjCb_CounterOverflow(
    const
    char                *pTestName
)
{
    OBJCB_DATA          *cbp;
    uint16_t            i;
    uint16_t            j;
    bool                fRc;
    //char                msg[10];
    NAME_DATA           *pName;

    fprintf(stderr, "Performing: %s\n", pTestName);

    cbp = ObjCb_NewWithSize(8);
    XCTAssertFalse( (NULL == cbp) );

    // Empty Queue - positive to negative overflow
    cbp->numRead = 32766;
    cbp->numWritten = 32766;

    fRc = ObjCb_IsEmpty(cbp);
    XCTAssertTrue( (fRc) );

    for (i=0; i<8; ++i) {
        pName =  Name_NewUTF8(StrArray[i]);
        fRc = ObjCb_Put(cbp,pName);
        obj_Release(pName);
        XCTAssertTrue( (fRc) );
        fRc = ObjCb_IsEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = ObjCb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }

    for (i=0; i<8; ++i) {
        fRc = ObjCb_Get(cbp, (void *)&pName);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (0 == Name_CompareA(pName,StrArray[i])) );
        obj_Release(pName);
    }

    fRc = ObjCb_IsEmpty(cbp);
    XCTAssertTrue( (fRc) );

    // Empty Queue - negative to positive overflow
    cbp->numRead = -32766;
    cbp->numWritten = -32766;

    fRc = ObjCb_IsEmpty(cbp);
    XCTAssertTrue( (fRc) );

    for (i=0; i<8; ++i) {
        pName =  Name_NewUTF8(StrArray[i]);
        fRc = ObjCb_Put(cbp, pName);
        obj_Release(pName);
        XCTAssertTrue( (fRc) );
        fRc = ObjCb_IsEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = ObjCb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }

    for (i=0; i<8; ++i) {
        fRc = ObjCb_Get(cbp, (void *)&pName);
        XCTAssertTrue( (fRc) );
        //STAssertTrue( (aVal == i) );
        obj_Release(pName);
    }

    fRc = ObjCb_IsEmpty(cbp);
    XCTAssertTrue( (fRc) );

    obj_Release( cbp );
    cbp = NULL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_ObjCb_Operation(
    const
    char        *pTestName
)
{
    int             i;
    PSXTHREAD_DATA  *pThread = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStrA = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    printf("Creating Buffer...\n");
    pCB = ObjCb_NewWithSize(4);
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
            pStrA = AStr_NewA(StrArray[i]);
            ObjCb_Put(pCB, pStrA);
            obj_Release(pStrA);
        }
        psxThread_Wait(2000);

        printf("\n\n");
        printf("Output Queue(%d):\n", outputQueueEnd+1);
        for (i=0; i<outputQueueEnd+1; ++i) {
            if (outputQueue[i].pObj) {
                printf("  %3d - %s\n", i,
                       AStr_getData((ASTR_DATA *)outputQueue[i].pObj)
                );
                obj_Release(outputQueue[i].pObj);
                outputQueue[i].pObj = OBJ_NIL;
            }
        }

        ObjCb_Pause(pCB);
        psxThread_Terminate(pThread);
        while (!psxThread_IsEnded(pThread)) {
            psxThread_Wait(100);
        }
        obj_Release(pThread);
        pThread = NULL;
        obj_Release(pCB);
        pCB = NULL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ObjCb);
    TINYTEST_ADD_TEST(test_ObjCb_Operation,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjCb_CounterOverflow,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjCb_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_ObjCb_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjCb_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ObjCb);





