// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/02/2020 15:56:31
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
#include    <ascii.h>
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <TokenList_internal.h>


#ifdef XYZZY
static
char        *strings[] = {
    "bob",
    "bobby",
    "iryana",
    "dashsa",
    "dasha",
    "name",
    "way",
    "bigger",
    "Now",
    "is",
    "the",
    "time",
    "for",
    "all",
    "good",
    "men",
    "to",
    "come",
    "aid",
    "of",
    "their",
    "country",
    "We",
    "need",
    "another",
    "item",
    "in",
    "here",
    "Are",
    "you",
    "alright",
    "with",
    "this",
    (char *)NULL
};
#endif




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

    SrcErrors_SharedReset();
    szTbl_SharedReset();
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






int             test_TokenList_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    TOKENLIST_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TokenList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = TokenList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_TOKENLIST);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_TokenList_AddHead01(
    const
    char        *pTestName
)
{
    TOKENLIST_DATA   *pList;
    TOKEN_DATA       *pToken;
    TOKEN_DATA       *pToken2;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    int32_t         chr = '0';
    SRCLOC          src = {1,2,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pList = TokenList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = TokenList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {

        for (i=0; i<10; ++i) {
            pToken = Token_NewCharW32(&src, ascii_toLexicalClassW32(chr+i), (chr+i));
            eRc = TokenList_Add2Head(pList, pToken);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = TokenList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pToken2 = TokenList_Head(pList);
            eRc = Token_Compare(pToken, pToken2);
            XCTAssertTrue( (eRc == 0) );
            obj_Release(pToken);
            pToken = OBJ_NIL;
        }

        obj_Release(pList);
        pList = OBJ_NIL;
        szTbl_SharedReset();
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_TokenList_AddTail01(
    const
    char        *pTestName
)
{
    TOKENLIST_DATA   *pList;
    TOKEN_DATA       *pToken;
    TOKEN_DATA       *pToken2;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    int32_t         chr = '0';
    SRCLOC          src = {1,2,3,4};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pList = TokenList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = TokenList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {

        for (i=0; i<10; ++i) {
            pToken = Token_NewCharW32(&src, ascii_toLexicalClassW32(chr+i), (chr+i));
            eRc = TokenList_Add2Tail(pList, pToken);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = TokenList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pToken2 = TokenList_Tail(pList);
            eRc = Token_Compare(pToken, pToken2);
            XCTAssertTrue( (eRc == 0) );
            obj_Release(pToken);
            pToken = OBJ_NIL;
        }

        obj_Release(pList);
        pList = OBJ_NIL;
        szTbl_SharedReset();
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_TokenList_Json01(
    const
    char        *pTestName
)
{
    TOKENLIST_DATA  *pObj = OBJ_NIL;
    TOKENLIST_DATA  *pObj2 = OBJ_NIL;
    TOKEN_DATA      *pNameA = OBJ_NIL;
    TOKEN_DATA      *pNameB = OBJ_NIL;
    TOKEN_DATA      *pNameC = OBJ_NIL;
    TOKEN_DATA      *pNameD = OBJ_NIL;
    TOKEN_DATA      *pNameE = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    TOKEN_DATA      *pEntry;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = TokenList_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pNameA = Token_NewCharW32(NULL, 'A', 'A');
        XCTAssertFalse( (OBJ_NIL == pNameA) );
        pNameB = Token_NewCharW32(NULL, 'B', 'B');
        XCTAssertFalse( (OBJ_NIL == pNameB) );
        pNameC = Token_NewCharW32(NULL, 'C', 'C');
        XCTAssertFalse( (OBJ_NIL == pNameC) );
        pNameD = Token_NewCharW32(NULL, 'D', 'D');
        XCTAssertFalse( (OBJ_NIL == pNameD) );
        pNameE = Token_NewCharW32(NULL, 'E', 'E');
        XCTAssertFalse( (OBJ_NIL == pNameE) );

        eRc = TokenList_Add2Tail(pObj, pNameA);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = TokenList_Add2Tail(pObj, pNameB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = TokenList_Add2Tail(pObj, pNameC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = TokenList_Add2Tail(pObj, pNameD);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = TokenList_Add2Tail(pObj, pNameE);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );

        pStr = TokenList_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug1 = %s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = TokenList_ToJson(pObj);
        TINYTEST_FALSE( (pStr == OBJ_NIL) );
        if (pStr) {
            fprintf(stderr, "Json = %s\n\n\n", AStr_getData(pStr));
        }

        pObj2 = TokenList_NewFromJsonString(pStr);
        TINYTEST_FALSE( (pObj2 == OBJ_NIL) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        XCTAssertTrue( (!(pObj == pObj2)) );
        XCTAssertTrue( (TokenList_getSize(pObj) == TokenList_getSize(pObj2)) );

        pStr = TokenList_ToDebugString(pObj2, 0);
        fprintf(stderr, "Debug2 = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pNameE);
        pNameE = OBJ_NIL;
        obj_Release(pNameD);
        pNameD = OBJ_NIL;
        obj_Release(pNameC);
        pNameC = OBJ_NIL;
        obj_Release(pNameB);
        pNameB = OBJ_NIL;
        obj_Release(pNameA);
        pNameA = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_TokenList);
    TINYTEST_ADD_TEST(test_TokenList_Json01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TokenList_AddTail01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TokenList_AddHead01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_TokenList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_TokenList);





