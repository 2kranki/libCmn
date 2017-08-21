/*
 *	Generated 06/30/2017 09:01:13
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
#include    <str.h>
#include    <szTbl_internal.h>
#include    <utf8.h>


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
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_szTbl_OpenClose(
    const
    char        *pTestName
)
{
    SZTBL_DATA	*pObj = OBJ_NIL;
   
    pObj = szTbl_Shared();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    return 1;
}



int         test_szTbl_Add(
    const
    char        *pTestName
)
{
    SZTBL_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i = 0;
    uint32_t    token;
    uint32_t    tokenW;
    char        **ppStr;
    const
    char        *pStr;
    ASTR_DATA	*pAStr = OBJ_NIL;
    
    pObj = szTbl_Shared();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        ppStr = strings;
        while (*ppStr) {
            ++i;
            eRc = szTbl_StringToToken(pObj, *ppStr, &token);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            if (ERESULT_HAS_FAILED(eRc)) {
                fprintf( stderr, "error word = %s\n", *ppStr );
            }
            XCTAssertTrue( (token == i) );
            eRc = szTbl_TokenToString(pObj, token, &pStr);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertFalse( (NULL == pStr) );
            if (pStr) {
                XCTAssertTrue( (0 == strcmp(*ppStr,pStr)) );
            }
            ++ppStr;
        }
        
        eRc = szTbl_StringToToken(pObj, "item", &token);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = szTbl_StringWToToken(pObj, L"item", &tokenW);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (token == tokenW) );
        
        eRc = szTbl_StringWToToken(pObj, L"item size", &tokenW);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = szTbl_StringToToken(pObj, "item size", &token);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (token == tokenW) );
        
        pAStr = szTbl_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        fprintf(stderr, "JSON='%s'\n", AStr_getData(pAStr));
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    return 1; 
}




TINYTEST_START_SUITE(test_szTbl);
  TINYTEST_ADD_TEST(test_szTbl_Add,setUp,tearDown);
  TINYTEST_ADD_TEST(test_szTbl_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_szTbl);





