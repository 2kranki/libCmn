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
#include    <trace.h>
#include    <nodeHash_internal.h>


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






int         test_nodeHash_OpenClose(
    const
    char        *pTestName
)
{
    NODEHASH_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeHash_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeHash_Init( pObj, 13 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_nodeHash_AddFindDelete01(
    const
    char        *pTestName
)
{
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pNode;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHash = nodeHash_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    pHash = nodeHash_Init( pHash, 5 );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    if (pHash) {
        
        for (i=0; i<10; ++i) {
            pNode = node_NewWithUTF8(strings[i], OBJ_NIL);
            eRc = nodeHash_Add(pHash, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeHash_getSize(pHash);
            XCTAssertTrue( (cnt == (i+1)) );
            eRc = nodeHash_FindA(pHash, strings[i], NULL);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
 
        eRc = nodeHash_Delete(pHash, strings[5]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = nodeHash_getSize(pHash);
        XCTAssertTrue( (cnt == 9) );
        eRc = nodeHash_FindA(pHash, strings[11], NULL);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pHash);
        pHash = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeHash);
  TINYTEST_ADD_TEST(test_nodeHash_AddFindDelete01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_nodeHash_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeHash);





