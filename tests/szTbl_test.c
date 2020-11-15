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
#include    <JsonIn.h>
#include    <trace.h>
#include    <str.h>
#include    <SrcErrors.h>
#include    <szTbl_internal.h>
#include    <utf8.h>
#include    <W32Str.h>


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

    
    SrcErrors_SharedReset( ); 
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






int         test_szTbl_OpenClose(
    const
    char        *pTestName
)
{
    SZTBL_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = szTbl_New();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_szTbl_Add(
    const
    char        *pTestName
)
{
    SZTBL_DATA	    *pObj = OBJ_NIL;
    SZTBL_DATA      *pNew = OBJ_NIL;
    //ERESULT         eRc;
    uint32_t        i = 0;
    uint32_t        token;
    uint32_t        tokenW;
    char            **ppStr;
    const
    char            *pStr;
    ASTR_DATA	    *pAStr = OBJ_NIL;
    W32STR_DATA     *pWStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = szTbl_Shared();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        ppStr = strings;
        while (*ppStr) {
            ++i;
            token = szTbl_StringToToken(pObj, *ppStr);
            XCTAssertTrue( (token == i) );
            pStr = szTbl_TokenToString(pObj, token);
            XCTAssertFalse( (NULL == pStr) );
            if (pStr) {
                XCTAssertTrue( (0 == strcmp(*ppStr, pStr)) );
                fprintf(stderr, "\tAdded and confirmed: %s\n", pStr);
            }
            ++ppStr;
        }
        
        token = szTbl_StringToToken(pObj, "item");
        pWStr = W32Str_NewA("item");
        XCTAssertFalse( (OBJ_NIL == pWStr) );
        tokenW = szTbl_StringW32ToToken(pObj, W32Str_getData(pWStr));
        XCTAssertTrue( (token == tokenW) );
        fprintf(stderr, "\tConfirmed: %s\n", "item");
        obj_Release(pWStr);
        pWStr = OBJ_NIL;
        
        pWStr = W32Str_NewA("item size");
        XCTAssertFalse( (OBJ_NIL == pWStr) );
        tokenW = szTbl_StringW32ToToken(pObj, W32Str_getData(pWStr));
        token = szTbl_StringToToken(pObj, "item size");
        XCTAssertTrue( (token == tokenW) );
        fprintf(stderr, "\tAdded and confirmed: %s\n", "item size");
        obj_Release(pWStr);
        pWStr = OBJ_NIL;

        pAStr = szTbl_ToJSON(pObj);
        XCTAssertFalse( (OBJ_NIL == pAStr) );
        fprintf(stderr, "JSON='%s'\n", AStr_getData(pAStr));
        pNew = szTbl_NewFromJSONString(pAStr);
        obj_Release(pNew);
        pNew = OBJ_NIL;
        obj_Release(pAStr);
        pAStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1; 
}




TINYTEST_START_SUITE(test_szTbl);
  TINYTEST_ADD_TEST(test_szTbl_Add,setUp,tearDown);
  TINYTEST_ADD_TEST(test_szTbl_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_szTbl);





