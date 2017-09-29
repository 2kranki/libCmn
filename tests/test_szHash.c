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
#include    <szHash_internal.h>
#include    <str.h>
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






int         test_szHash_OpenClose(
    const
    char        *pTestName
)
{
    SZHASH_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = szHash_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = szHash_Init( pObj, 5 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_szHash_AddFindDelete1(
    const
    char        *pTestName
)
{
    SZHASH_DATA     *pHash;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    void            *pVoid;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pHash = szHash_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    pHash = szHash_Init( pHash, 5 );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    if (pHash) {
        
        szHash_setComputeHash( pHash, str_HashA, str_HashW );
        szHash_setCompare( pHash, utf8_StrCmp, utf8_StrCmpAW );

        for (i=0; i<10; ++i) {
            eRc = szHash_Add(pHash, strings[i], strings[i]);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = szHash_getSize(pHash);
            XCTAssertTrue( (cnt == (i+1)) );
        }
        
        for (i=0; i<10; ++i) {
            pVoid = szHash_Find(pHash, strings[i]);
            XCTAssertTrue( (pVoid == strings[i]) );
        }
        
        pVoid = szHash_Find(pHash, strings[3]);
        XCTAssertTrue( (pVoid == strings[3]) );
        pVoid = szHash_Find(pHash, strings[9]);
        XCTAssertTrue( (pVoid == strings[9]) );
        pVoid = szHash_Find(pHash, strings[6]);
        XCTAssertTrue( (pVoid == strings[6]) );
        
        eRc = szHash_Delete(pHash, strings[5]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = szHash_getSize(pHash);
        XCTAssertTrue( (cnt == 9) );
        pVoid = szHash_Find(pHash, strings[5]);
        XCTAssertTrue( (pVoid == NULL) );
        
        eRc = szHash_Delete(pHash, strings[8]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = szHash_getSize(pHash);
        XCTAssertTrue( (cnt == 8) );
        pVoid = szHash_Find(pHash, strings[8]);
        XCTAssertTrue( (pVoid == NULL) );
        
        obj_Release(pHash);
        pHash = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_szHash);
  TINYTEST_ADD_TEST(test_szHash_AddFindDelete1,setUp,tearDown);
  TINYTEST_ADD_TEST(test_szHash_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_szHash);





