// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/23/2020 22:22:04
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
#include    <W32StrC_internal.h>
#ifdef  W32STRC_JSON_SUPPORT
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

#ifdef  W32STRC_JSON_SUPPORT
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






int             test_W32StrC_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    W32STRC_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32StrC_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = W32StrC_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_W32STRC);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_W32StrC_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    W32STRC_DATA	*pObj1 = OBJ_NIL;
    W32STRC_DATA	*pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(W32STRC_JSON_SUPPORT)
    ASTR_DATA	    *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = W32StrC_NewA("abcdef");
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_W32STRC);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = W32StrC_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = W32StrC_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32STRC);
        TINYTEST_TRUE( (fRc) );
        eRc = W32StrC_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = W32StrC_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32STRC);
        TINYTEST_TRUE( (fRc) );
        eRc = W32StrC_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(W32STRC_JSON_SUPPORT)
        pStr = W32StrC_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = W32StrC_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32STRC);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TINYTEST_FALSE( (NULL == pObj2->pArray) );
        TINYTEST_TRUE( (pObj1->len == pObj2->len) );
        eRc = W32StrC_Compare(pObj1, pObj2);
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



int             test_W32StrC_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    W32STRC_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32StrC_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_W32STRC);
        TINYTEST_TRUE( (fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32StrC_NewA(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32StrC_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (0 == utf8_StrCmpAW32("abc",pStr)) );
        pCopy = W32StrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (0 == utf8_StrCmpAW32("abc", pStr)) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_W32StrC_NewW(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32StrC_NewW32(L"abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj, L"abc")) );
        pCopy = W32StrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj, L"abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_W32StrC_NewConW(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32StrC_NewConW32(L"abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj,L"abc")) );
        pCopy = W32StrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj,L"abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_W32StrC_Mid(
    const
    char        *pTestName
)
{
    W32STRC_DATA *pObj = OBJ_NIL;
    W32STRC_DATA *pCopy = OBJ_NIL;
    const
    W32CHR_T    *pStr;
    uint32_t    len;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32StrC_NewConW32(L"abcdef");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = W32StrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (6 == len) );
        pStr = W32StrC_getData(pObj);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pObj,L"abcdef")) );

        pCopy = W32StrC_Mid(pObj, 1, 6);
        XCTAssertTrue( (pCopy != pObj) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (6 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pCopy,L"abcdef")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        pCopy = W32StrC_Mid(pObj, 3, 4);
        XCTAssertTrue( (pCopy != pObj) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (4 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pCopy,L"cdef")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        pCopy = W32StrC_Mid(pObj, 6, 1);
        XCTAssertTrue( (pCopy != pObj) );
        len = W32StrC_getLength(pCopy);
        XCTAssertTrue( (1 == len) );
        pStr = W32StrC_getData(pCopy);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareW32(pCopy,L"f")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        pCopy = W32StrC_Left(pObj, 3);
        XCTAssertFalse( (pCopy == OBJ_NIL) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareA(pCopy,"abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        pCopy = W32StrC_Right(pObj, 3);
        XCTAssertFalse( (pCopy == OBJ_NIL) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32StrC_CompareA(pCopy,"def")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        //pCopy = W32StrC_Mid(pObj, 3, 0);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );

        //pCopy = W32StrC_Mid(pObj, 6, 7);
        //XCTAssertTrue( (pCopy == OBJ_NIL) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int             test_Expr_LookAhead01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    const
    char            *pExpr1A = "1+1";
    const
    char            *pExpr2A = "2*5+1";
    const
    char            *pExpr3A = "1+2*5";
    W32STRC_DATA     *pW32 = OBJ_NIL;
    W32CHR_T        chr;
    bool            fRc;

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

    W32StrC_Reset(pW32);
    TINYTEST_TRUE( (0 == obj_getMisc(pW32)) );
    fRc = W32StrC_MatchStrA(pW32, "1+");
    TINYTEST_TRUE( (fRc) );
    fprintf(stderr, "\tMisc = %d\n", obj_getMisc(pW32));
    TINYTEST_TRUE( (2 == obj_getMisc(pW32)) );
    fRc = W32StrC_MatchStrA(pW32, "1+");
    TINYTEST_TRUE( (!fRc) );
    fprintf(stderr, "\tMisc = %d\n", obj_getMisc(pW32));
    TINYTEST_TRUE( (2 == obj_getMisc(pW32)) );
    fRc = W32StrC_MatchStrA(pW32, "1");
    TINYTEST_TRUE( (fRc) );
    fprintf(stderr, "\tMisc = %d\n", obj_getMisc(pW32));
    TINYTEST_TRUE( (3 == obj_getMisc(pW32)) );
    fRc = W32StrC_MatchStrA(pW32, "1");
    TINYTEST_TRUE( (!fRc) );
    fprintf(stderr, "\tMisc = %d\n", obj_getMisc(pW32));
    TINYTEST_TRUE( (3 == obj_getMisc(pW32)) );

    obj_Release(pW32);
    pW32 = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_W32StrC);
    TINYTEST_ADD_TEST(test_Expr_LookAhead01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32StrC_Mid,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32StrC_NewConW,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32StrC_NewW,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32StrC_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32StrC_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32StrC_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_W32StrC);





