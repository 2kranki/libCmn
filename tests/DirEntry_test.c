// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/28/2020 23:56:00
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
#include    <DirEntry_internal.h>
#ifdef  DIRENTRY_JSON_SUPPORT
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

#ifdef  DIRENTRY_JSON_SUPPORT
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






int             test_DirEntry_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DIRENTRY_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = DirEntry_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = DirEntry_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_DIRENTRY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_DirEntry_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    DIRENTRY_DATA	*pObj1 = OBJ_NIL;
    DIRENTRY_DATA	*pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(DIRENTRY_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

#if defined(__MACOSX_ENV__) || defined(__MACOS64_ENV__)
    pObj1 = DirEntry_NewA("/Applications", DIRENTRY_TYPE_DIR);
#endif
#if     defined(__WIN32_ENV__) || defined(__WIN64_ENV__)
    pObj1 = DirEntry_NewA("c:/Applications", DIRENTRY_TYPE_DIR);
#endif
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_DIRENTRY);
        TINYTEST_TRUE( (fRc) );
        eRc = DirEntry_Complete(pObj1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        // Test assign.
        pObj2 = DirEntry_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = DirEntry_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DIRENTRY);
        TINYTEST_TRUE( (fRc) );
        eRc = DirEntry_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = DirEntry_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DIRENTRY);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(DIRENTRY_JSON_SUPPORT)
        pStr = DirEntry_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = DirEntry_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_DIRENTRY);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = DirEntry_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_DirEntry_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    DIRENTRY_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pPathA1 = "abc:/def/ghi.txt";
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = DirEntry_NewA("abc:/def/ghi.txt", DIRENTRY_TYPE_REG);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_DIRENTRY);
        TINYTEST_TRUE( (fRc) );

        pPath = DirEntry_getFullPath(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pPath) );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == Path_CompareA(pPath, pPathA1)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_DirEntry);
    TINYTEST_ADD_TEST(test_DirEntry_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_DirEntry_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_DirEntry_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_DirEntry);





