// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 01/04/2021 10:35:59
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
#include    <U32Index_internal.h>
#include    <JsonIn.h>
#ifdef  U32INDEX_JSON_SUPPORT
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

#ifdef  U32INDEX_JSON_SUPPORT
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






int             test_U32Index_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U32INDEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U32Index_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = U32Index_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_U32INDEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_U32Index_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U32INDEX_DATA       *pObj1 = OBJ_NIL;
    U32INDEX_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(U32INDEX_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = U32Index_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_U32INDEX);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = U32Index_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = U32Index_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U32INDEX);
        TINYTEST_TRUE( (fRc) );
        //eRc = U32Index_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = U32Index_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U32INDEX);
        TINYTEST_TRUE( (fRc) );
        //eRc = U32Index_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(U32INDEX_JSON_SUPPORT) && defined(XYZZY)
        pStr = U32Index_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = U32Index_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_U32INDEX);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = U32Index_Compare(pObj1, pObj2);
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



int             test_U32Index_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    U32INDEX_DATA   *pObj = OBJ_NIL;
    bool            fRc;
    void            *ptr;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = U32Index_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_U32INDEX);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        eRc = U32Index_Add(pObj, 3, (void *)3, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = U32Index_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 3: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = U32Index_Add(pObj, 2, (void *)2, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = U32Index_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 2: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = U32Index_Add(pObj, 5, (void *)5, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = U32Index_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 5: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        eRc = U32Index_Add(pObj, 4, (void *)4, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = U32Index_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 4: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        eRc = U32Index_Add(pObj, 1, (void *)1, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        {
            ASTR_DATA       *pStr = U32Index_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Added 1: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        ptr = U32Index_Find(pObj, 1);
        TINYTEST_TRUE( ((void *)1 == ptr) );
        ptr = U32Index_Find(pObj, 5);
        TINYTEST_TRUE( ((void *)5 == ptr) );
        ptr = U32Index_Find(pObj, 2);
        TINYTEST_TRUE( ((void *)2 == ptr) );
        ptr = U32Index_Find(pObj, 3);
        TINYTEST_TRUE( ((void *)3 == ptr) );
        ptr = U32Index_Find(pObj, 4);
        TINYTEST_TRUE( ((void *)4 == ptr) );
        ptr = U32Index_Find(pObj, 6);
        TINYTEST_TRUE( ((void *)0 == ptr) );

        {
            ASTR_DATA       *pStr = U32Index_ToDebugString(pObj, 0);
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




TINYTEST_START_SUITE(test_U32Index);
    TINYTEST_ADD_TEST(test_U32Index_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_U32Index_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_U32Index_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_U32Index);





