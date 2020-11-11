// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/12/2020 09:43:59
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
#include    <TextIns_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



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

    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
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






int             test_TextIns_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TEXTINS_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TextIns_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = TextIns_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TEXTINS);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_TextIns_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TEXTINS_DATA	    *pObj1 = OBJ_NIL;
    TEXTINS_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(TEXTINS_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = TextIns_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_TEXTINS);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = TextIns_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = TextIns_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TEXTINS);
        TINYTEST_TRUE( (fRc) );
        //eRc = TextIns_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (0 == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = TextIns_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TEXTINS);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(TEXTINS_JSON_SUPPORT) && defined(XYZZY)
        pStr = TextIns_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = TextIns_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_TEXTINS);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = TextIns_Compare(pObj1, pObj2);
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



int             test_TextIns_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TEXTINS_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    SRCLOC          loc = {0};
    const
    char            *pFilePath1A = "~/git/libCmn/tests/files/e360_ex1_bal.txt";
    PATH_DATA       *pFilePath1 = OBJ_NIL;
    const
    char            *pFilePath2A = "~/git/libCmn/tests/files/e360_ex2_bal.txt";
    PATH_DATA       *pFilePath2 = OBJ_NIL;
    char            line[256];

    fprintf(stderr, "Performing: %s\n", pTestName);

    pFilePath1 = Path_NewA(pFilePath1A);
    TINYTEST_FALSE( (OBJ_NIL == pFilePath1) );
    Path_Clean(pFilePath1);
    eRc = Path_IsFile(pFilePath1);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pFilePath2 = Path_NewA(pFilePath2A);
    TINYTEST_FALSE( (OBJ_NIL == pFilePath2) );
    Path_Clean(pFilePath2);
    eRc = Path_IsFile(pFilePath2);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

    pObj = TextIns_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TEXTINS);
        TINYTEST_TRUE( (fRc) );
        
        eRc = TextIns_NewSrcFromPath(pObj, pFilePath1, 4);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = TextIns_GetLineA(pObj, sizeof(line), line, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tfile1: %s\n", line);

        eRc = TextIns_NewSrcFromPath(pObj, pFilePath2, 4);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = TextIns_GetLineA(pObj, sizeof(line), line, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tfile2: %s\n", line);

        eRc = TextIns_StackPop(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = TextIns_GetLineA(pObj, sizeof(line), line, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tfile1: %s\n", line);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pFilePath2);
    pFilePath2 = OBJ_NIL;
    obj_Release(pFilePath1);
    pFilePath1 = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_TextIns);
    TINYTEST_ADD_TEST(test_TextIns_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_TextIns_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TextIns_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_TextIns);





