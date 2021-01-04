// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 01/03/2021 13:14:35
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
#include    <IntIndex_internal.h>
#include    <JsonIn.h>
#ifdef  INTINDEX_JSON_SUPPORT
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

#ifdef  INTINDEX_JSON_SUPPORT
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






int             test_IntIndex_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    INTINDEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = IntIndex_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = IntIndex_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_INTINDEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_IntIndex_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    INTINDEX_DATA       *pObj1 = OBJ_NIL;
    INTINDEX_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(INTINDEX_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = IntIndex_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_INTINDEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = IntIndex_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = IntIndex_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_INTINDEX);
        TINYTEST_TRUE( (fRc) );
        //eRc = IntIndex_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = IntIndex_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_INTINDEX);
        TINYTEST_TRUE( (fRc) );
        //eRc = IntIndex_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(INTINDEX_JSON_SUPPORT) && defined(XYZZY)
        pStr = IntIndex_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = IntIndex_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_INTINDEX);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = IntIndex_Compare(pObj1, pObj2);
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



int             test_IntIndex_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    INTINDEX_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    void            *ptr;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = IntIndex_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_INTINDEX);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        eRc = IntIndex_Add(pObj, 3, (void *)3, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = IntIndex_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 3: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = IntIndex_Add(pObj, 2, (void *)2, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = IntIndex_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 2: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = IntIndex_Add(pObj, 5, (void *)5, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = IntIndex_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 5: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        eRc = IntIndex_Add(pObj, 4, (void *)4, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = IntIndex_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 4: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = IntIndex_Add(pObj, 1, (void *)1, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = IntIndex_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 1: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        ptr = IntIndex_Find(pObj, 1);
        TINYTEST_TRUE( ((void *)1 == ptr) );
        ptr = IntIndex_Find(pObj, 5);
        TINYTEST_TRUE( ((void *)5 == ptr) );
        ptr = IntIndex_Find(pObj, 2);
        TINYTEST_TRUE( ((void *)2 == ptr) );
        ptr = IntIndex_Find(pObj, 3);
        TINYTEST_TRUE( ((void *)3 == ptr) );
        ptr = IntIndex_Find(pObj, 4);
        TINYTEST_TRUE( ((void *)4 == ptr) );
        ptr = IntIndex_Find(pObj, 6);
        TINYTEST_TRUE( ((void *)0 == ptr) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_IntIndex);
    TINYTEST_ADD_TEST(test_IntIndex_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_IntIndex_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_IntIndex_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_IntIndex);





