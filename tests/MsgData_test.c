// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/31/2019 10:05:08
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
#include    <MsgData_internal.h>



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






int             test_MsgData_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    MSGDATA_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = MsgData_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = MsgData_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_MSGDATA);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_MsgData_Test01(
    const
    char        *pTestName
)
{
    MSGDATA_DATA    *pObj = OBJ_NIL;
    const
    char            *pData = "01234567";

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = MsgData_NewWithData(1, 0, (uint32_t)(strlen(pData) + 1), (void *)pData);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE( (1 == MsgData_getOrigin(pObj)) );
        TINYTEST_TRUE( (0 == MsgData_getDestination(pObj)) );
        TINYTEST_TRUE( ((strlen(pData)+1) == MsgData_getSize(pObj)) );
        TINYTEST_TRUE( (0 == strcmp(pData, MsgData_getData(pObj))) );
        printf("   num origin dest len text\n");
        fprintf(stderr, "   %2d    %2d    %2d   %2d \"%s\"\n",
               MsgData_getNum32(pObj),
               MsgData_getOrigin(pObj),
               MsgData_getDestination(pObj),
               MsgData_getSize(pObj),
               (char *)MsgData_getData(pObj)
               );
        printf("   len includes trailing NUL.\n");


        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_MsgData);
    TINYTEST_ADD_TEST(test_MsgData_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_MsgData_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_MsgData);





