/*
 *	Generated 08/11/2019 13:04:20
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
#include    <AStrCReader_internal.h>



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






int             test_AStrCReader_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRCREADER_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrCReader_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = AStrCReader_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_AStrCReader_Test01(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTRCREADER_DATA *pObj = OBJ_NIL;
    ASTRC_DATA      *pStr = OBJ_NIL;
    W32CHR_T        chr;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr = AStrC_NewFromConstant("abc");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    
    pObj = AStrCReader_NewAStrC( pStr );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        //obj_TraceSet(pObj, true);
        
        chr = AStrCReader_Next(pObj);
        TINYTEST_TRUE( (chr == 'a') );
        chr = AStrCReader_Next(pObj);
        TINYTEST_TRUE( (chr == 'b') );
        chr = AStrCReader_Next(pObj);
        TINYTEST_TRUE( (chr == 'c') );
        chr = AStrCReader_Next(pObj);
        fprintf(stderr, "-1 == %d\n", chr);
        TINYTEST_TRUE( (chr == -1) );
        
        eRc = AStrCReader_Rescan(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        chr = AStrCReader_Next(pObj);
        TINYTEST_TRUE( (chr == 'a') );
        chr = AStrCReader_Next(pObj);
        TINYTEST_TRUE( (chr == 'b') );
        chr = AStrCReader_Next(pObj);
        TINYTEST_TRUE( (chr == 'c') );
        chr = AStrCReader_Next(pObj);
        fprintf(stderr, "-1 == %d\n", chr);
        TINYTEST_TRUE( (chr == -1) );
        
        eRc = AStrCReader_Rescan(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        chr = AStrCReader_Peek(pObj, 1);
        TINYTEST_TRUE( (chr == 'a') );
        chr = AStrCReader_Peek(pObj, 2);
        TINYTEST_TRUE( (chr == 'b') );
        chr = AStrCReader_Peek(pObj, 3);
        TINYTEST_TRUE( (chr == 'c') );
        chr = AStrCReader_Peek(pObj, 4);
        fprintf(stderr, "-1 == %d\n", chr);
        TINYTEST_TRUE( (chr == -1) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_AStrCReader);
    TINYTEST_ADD_TEST(test_AStrCReader_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrCReader_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AStrCReader);





