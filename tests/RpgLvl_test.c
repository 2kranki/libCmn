// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 05/23/2021 00:37:45
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
#include    <RpgLvl_internal.h>
#include    <JsonIn.h>
#ifdef  RPGLVL_JSON_SUPPORT
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

#ifdef  RPGLVL_JSON_SUPPORT
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






int             test_RpgLvl_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RPGLVL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = RpgLvl_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = RpgLvl_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_RPGLVL);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_RpgLvl_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RPGLVL_DATA       *pObj1 = OBJ_NIL;
    RPGLVL_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(RPGLVL_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = RpgLvl_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_RPGLVL);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = RpgLvl_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = RpgLvl_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RPGLVL);
        TINYTEST_TRUE( (fRc) );
        //iRc = RpgLvl_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = RpgLvl_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RPGLVL);
        TINYTEST_TRUE( (fRc) );
        //iRc = RpgLvl_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(RPGLVL_JSON_SUPPORT) && defined(XYZZY)
        pStr = RpgLvl_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = RpgLvl_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_RPGLVL);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = RpgLvl_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_RpgLvl_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    RPGLVL_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = RpgLvl_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_RPGLVL);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = RpgLvl_ToDebugString(pObj, 4);
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




TINYTEST_START_SUITE(test_RpgLvl);
    TINYTEST_ADD_TEST(test_RpgLvl_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_RpgLvl_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_RpgLvl_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_RpgLvl);





