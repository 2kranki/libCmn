/*
 *	Generated 06/05/2017 21:57:10
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
#include    <szTbl.h>
#include    <token.h>
#include    <trace.h>
#include    <tokenList_internal.h>



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




int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
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






int         test_tokenList_OpenClose(
    const
    char        *pTestName
)
{
    TOKENLIST_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = tokenList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = tokenList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

       fprintf(stderr, "===>  tokenList - tokens Per Block = %d\n", pObj->cBlock);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_tokenList_AddHead01(
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
    
    pList = tokenList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = tokenList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {
        
        for (i=0; i<10; ++i) {
            pToken = token_NewCharW32(&src, ascii_toLexicalClassW32(chr+i), (chr+i));
            eRc = tokenList_Add2Head(pList, pToken);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = tokenList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pToken2 = tokenList_Head(pList);
            eRc = token_Compare(pToken, pToken2);
            XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
            obj_Release(pToken);
            pToken = OBJ_NIL;
        }

        obj_Release(pList);
        pList = OBJ_NIL;
        szTbl_SharedReset();
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_tokenList_AddTail01(
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
    
    pList = tokenList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = tokenList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {
        
        for (i=0; i<10; ++i) {
            pToken = token_NewCharW32(&src, ascii_toLexicalClassW32(chr+i), (chr+i));
            eRc = tokenList_Add2Tail(pList, pToken);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = tokenList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pToken2 = tokenList_Tail(pList);
            eRc = token_Compare(pToken, pToken2);
            XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
            obj_Release(pToken);
            pToken = OBJ_NIL;
        }
        
        obj_Release(pList);
        pList = OBJ_NIL;
        szTbl_SharedReset();
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_tokenList);
  TINYTEST_ADD_TEST(test_tokenList_AddTail01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_tokenList_AddHead01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_tokenList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_tokenList);





