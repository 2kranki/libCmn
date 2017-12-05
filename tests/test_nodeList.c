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
#include    <nodeList_internal.h>


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






int         test_nodeList_OpenClose(
    const
    char        *pTestName
)
{
    NODELIST_DATA *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = nodeList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_nodeList_AddFindDelete01(
    const
    char        *pTestName
)
{
    NODELIST_DATA   *pList;
    NODE_DATA       *pNode;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pList = nodeList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = nodeList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {
        
        for (i=0; i<10; ++i) {
            pNode = node_NewWithUTF8(strings[i], OBJ_NIL);
            eRc = nodeList_Add2Head(pList, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            eRc = nodeList_Find(pList, strings[i], NULL);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
 
        eRc = nodeList_Delete(pList, strings[5]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = nodeList_getSize(pList);
        XCTAssertTrue( (cnt == 9) );
        eRc = nodeList_Find(pList, strings[11], NULL);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pList);
        pList = OBJ_NIL;
        //szTbl_SharedReset();
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeList);
  TINYTEST_ADD_TEST(test_nodeList_AddFindDelete01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_nodeList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeList);





