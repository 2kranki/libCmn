// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 06/28/2020 10:02:20
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
#include    <JsonIn.h>
#include    <trace.h>
#include    <AudioWAV_internal.h>
#ifdef  AUDIOWAV_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



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

#ifdef  AUDIOWAV_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
    JsonIn_RegisterReset();
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






int             test_AudioWAV_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AUDIOWAV_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AudioWAV_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = AudioWAV_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_AUDIOWAV);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_AudioWAV_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    AUDIOWAV_DATA       *pObj1 = OBJ_NIL;
    AUDIOWAV_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(AUDIOWAV_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = AudioWAV_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_AUDIOWAV);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = AudioWAV_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = AudioWAV_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_AUDIOWAV);
        TINYTEST_TRUE( (fRc) );
        //eRc = AudioWAV_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = AudioWAV_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_AUDIOWAV);
        TINYTEST_TRUE( (fRc) );
        //eRc = AudioWAV_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(AUDIOWAV_JSON_SUPPORT) && defined(XYZZY)
        pStr = AudioWAV_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = AudioWAV_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_AUDIOWAV);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = AudioWAV_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_AudioWAV_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    AUDIOWAV_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AudioWAV_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_AUDIOWAV);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = AudioWAV_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_AudioWAV_Silence(
    const
    char        *pTestName
)
{
    AUDIOWAV_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AudioWAV_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    eRc = AudioWAV_Setup(pObj, 1, 11025, 16);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    if (pObj) {

        eRc = AudioWAV_AppendSilence(pObj, 10000);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pPath = Path_NewA("~/AudioTest01.wav");
        eRc = AudioWAV_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AudioWAV_SineWave(
    const
    char        *pTestName
)
{
    AUDIOWAV_DATA    *pObj = OBJ_NIL;
    ERESULT         eRc;
    PATH_DATA       *pPath = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AudioWAV_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    eRc = AudioWAV_Setup(pObj, 1, 11025, 16);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    if (pObj) {

        eRc = AudioWAV_AppendSineWave(pObj, 740, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pPath = Path_NewA("~/AudioTest02.wav");
        eRc = AudioWAV_WriteToFile(pObj, pPath);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        obj_Release(pPath);
        pPath = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_AudioWAV);
    TINYTEST_ADD_TEST(test_AudioWAV_SineWave,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AudioWAV_Silence,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AudioWAV_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_AudioWAV_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AudioWAV_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AudioWAV);





