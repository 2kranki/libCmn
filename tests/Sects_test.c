// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 12/27/2020 14:57:52
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
#include    <Sects_internal.h>
#include    <JsonIn.h>
#ifdef  SECTS_JSON_SUPPORT
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

#ifdef  SECTS_JSON_SUPPORT
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






int             test_Sects_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SECTS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Sects_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Sects_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SECTS);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Sects_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SECTS_DATA       *pObj1 = OBJ_NIL;
    SECTS_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SECTS_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Sects_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SECTS);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Sects_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Sects_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SECTS);
        TINYTEST_TRUE( (fRc) );
        //eRc = Sects_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Sects_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SECTS);
        TINYTEST_TRUE( (fRc) );
        //eRc = Sects_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SECTS_JSON_SUPPORT) && defined(XYZZY)
        pStr = Sects_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Sects_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SECTS);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Sects_Compare(pObj1, pObj2);
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



int             test_Sects_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SECTS_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Sects_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SECTS);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = Sects_ToDebugString(pObj, 0);
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



int             test_Sects_AddFind01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SECTS_DATA      *pObj = OBJ_NIL;
    bool            fRc;
    SECT_DATA       *pEntry;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Sects_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SECTS);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        eRc = Sects_AddA(pObj, 'a', 'c', 0x0001, 0x001, 1, "1");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Sects_AddA(pObj, 'b', 'c', 0x0002, 0x002, 2, "2");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Sects_AddA(pObj, 'c', 'c', 0x0003, 0x003, 3, "3");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Sects_AddA(pObj, 'd', 'c', 0x0004, 0x004, 4, "4");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = Sects_AddA(pObj, 'e', 'c', 0x0005, 0x005, 5, "5");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = Sects_AddA(pObj, 'b', 'c', 0x0002, 0x002, 2, "2");
        TINYTEST_TRUE( (ERESULT_FAILED(eRc)) );

        pEntry = Sects_FindA(pObj, "b");
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        {
            ASTR_DATA       *pStr = Sect_ToDebugString(pEntry, 0);
            if (pStr) {
                fprintf(stderr, "Sect(b): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        pEntry = Sects_FindA(pObj, "a");
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        {
            ASTR_DATA       *pStr = Sect_ToDebugString(pEntry, 0);
            if (pStr) {
                fprintf(stderr, "Sect(a): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        pEntry = Sects_FindA(pObj, "e");
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        {
            ASTR_DATA       *pStr = Sect_ToDebugString(pEntry, 0);
            if (pStr) {
                fprintf(stderr, "Sect(e): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        {
            ASTR_DATA       *pStr = Sects_ToDebugString(pObj, 0);
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




TINYTEST_START_SUITE(test_Sects);
    TINYTEST_ADD_TEST(test_Sects_AddFind01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Sects_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Sects_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Sects_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Sects);





