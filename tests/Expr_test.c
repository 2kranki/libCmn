// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 03/03/2020 17:03:28
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
#include    <Expr_internal.h>
#ifdef  EXPR_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif
#include    <trace.h>
#include    <W32StrC.h>



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

#ifdef  EXPR_JSON_SUPPORT
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






int             test_Expr_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Expr_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Expr_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_EXPR);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Expr_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    EXPR_DATA	    *pObj1 = OBJ_NIL;
    EXPR_DATA	    *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(EXPR_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Expr_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_EXPR);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Expr_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Expr_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_EXPR);
        TINYTEST_TRUE( (fRc) );
        //eRc = Expr_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Expr_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_EXPR);
        TINYTEST_TRUE( (fRc) );
        //eRc = Expr_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(EXPR_JSON_SUPPORT) && defined(XYZZY)
        pStr = Expr_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Expr_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_EXPR);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Expr_Compare(pObj1, pObj2);
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



int             test_Expr_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    EXPR_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
    int32_t         iRc;
    const
    char            *pExpr1A = "1+1";
    const
    char            *pExpr2A = "2*5+1";
    const
    char            *pExpr3A = "1+2*5";
    W32STRC_DATA     *pW32 = OBJ_NIL;
    W32CHR_T        chr;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pW32 = W32StrC_NewA(pExpr1A);
    TINYTEST_FALSE( (OBJ_NIL == pW32) );
    chr = W32StrC_LookAhead(pW32, 1);
    TINYTEST_TRUE( ('1' == chr) );
    chr = W32StrC_LookAhead(pW32, 2);
    TINYTEST_TRUE( ('+' == chr) );
    chr = W32StrC_LookAhead(pW32, 3);
    TINYTEST_TRUE( ('1' == chr) );
    chr = W32StrC_LookAhead(pW32, 4);
    TINYTEST_TRUE( (0 == chr) );
    chr = W32StrC_LookAhead(pW32, 10);
    TINYTEST_TRUE( (0 == chr) );
    W32StrC_Advance(pW32, 1);
    chr = W32StrC_LookAhead(pW32, 1);
    TINYTEST_TRUE( ('+' == chr) );
    W32StrC_Advance(pW32, 1);
    chr = W32StrC_LookAhead(pW32, 1);
    TINYTEST_TRUE( ('1' == chr) );
    W32StrC_Advance(pW32, 1);
    chr = W32StrC_LookAhead(pW32, 1);
    TINYTEST_TRUE( (0 == chr) );

    pObj = Expr_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_EXPR);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pW32);
    pW32 = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Expr);
    TINYTEST_ADD_TEST(test_Expr_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Expr_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Expr_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Expr);





