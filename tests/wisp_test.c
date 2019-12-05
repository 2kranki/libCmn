/*
 *	Generated 08/04/2018 08:13:16
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
#include    <wisp_internal.h>


static
const
char        *pWords[8] ={
    "APE",
    "BATHER",
    "BOY",
    "JUNK",
    "BATH",
    "APEX",
    "APPLE",
    "BY"
};





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






int             test_wisp_OpenClose(
    const
    char            *pTestName
)
{
    WISP_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = wisp_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = wisp_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_wisp_Basics01(
    const
    char            *pTestName
)
{
    WISP_DATA       *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        index = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = wisp_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = wisp_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        index = 0;
        eRc = wisp_Cons(pObj, 1, 1, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (1 == index) );
        TINYTEST_TRUE( (1 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (1 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );

        index = 0;
        eRc = wisp_Cons(pObj, 2, 2, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (2 == index) );
        TINYTEST_TRUE( (2 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (2 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 0;
        eRc = wisp_Cons(pObj, 3, 3, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (3 == index) );
        TINYTEST_TRUE( (3 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (3 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 0;
        eRc = wisp_Cons(pObj, 4, 4, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (4 == index) );
        TINYTEST_TRUE( (4 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (4 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        TINYTEST_TRUE( (4 == wisp_getSize(pObj)) );
        
        index = 2;
        eRc = wisp_SetAtom(pObj, index, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );

        index = 2;
        eRc = wisp_SetAtom(pObj, index, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 2;
        eRc = wisp_SetBP(pObj, index, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_TRUE( (wisp_GetBP(pObj, index)) );
        
        index = 2;
        eRc = wisp_SetBP(pObj, index, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_wisp_Dict01(
    const
    char            *pTestName
)
{
    WISP_DATA       *pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        index = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = wisp_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = wisp_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        index = 0;
        eRc = wisp_Cons(pObj, 1, 1, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (1 == index) );
        TINYTEST_TRUE( (1 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (1 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 0;
        eRc = wisp_Cons(pObj, 2, 2, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (2 == index) );
        TINYTEST_TRUE( (2 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (2 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 0;
        eRc = wisp_Cons(pObj, 3, 3, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (3 == index) );
        TINYTEST_TRUE( (3 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (3 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 0;
        eRc = wisp_Cons(pObj, 4, 4, &index);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (4 == index) );
        TINYTEST_TRUE( (4 == wisp_GetCAR(pObj, index)) );
        TINYTEST_TRUE( (4 == wisp_GetCDR(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        TINYTEST_TRUE( (4 == wisp_getSize(pObj)) );
        
        index = 2;
        eRc = wisp_SetAtom(pObj, index, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 2;
        eRc = wisp_SetAtom(pObj, index, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        index = 2;
        eRc = wisp_SetBP(pObj, index, true);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_TRUE( (wisp_GetBP(pObj, index)) );
        
        index = 2;
        eRc = wisp_SetBP(pObj, index, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (wisp_GetAtom(pObj, index)) );
        TINYTEST_FALSE( (wisp_GetBP(pObj, index)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_wisp);
    TINYTEST_ADD_TEST(test_wisp_Basics01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wisp_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_wisp);





