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




ERESULT     listEntryPrintRtn(
    NODELIST_DATA   *this,
    NODE_DATA       *pNode,
    void            *pVoid
)
{
    char            *pNameA;
    
    pNameA = node_getNameUTF8(pNode);
    fprintf(stderr, "\t\t%s\n", pNameA);
    mem_Free(pNameA);
    return ERESULT_SUCCESS;
}



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

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
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
            pNode = node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
            eRc = nodeList_Add2Head(pList, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pNode = nodeList_FindA(pList, 0, strings[i]);
            XCTAssertTrue( (pNode) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
 
        eRc = nodeList_Delete(pList, 0, strings[5]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = nodeList_getSize(pList);
        XCTAssertTrue( (cnt == 9) );
        pNode = nodeList_FindA(pList, 0, strings[11]);
        XCTAssertTrue( (OBJ_NIL == pNode) );

        obj_Release(pList);
        pList = OBJ_NIL;
        //szTbl_SharedReset();
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_nodeList_AddFindDelete02(
    const
    char        *pTestName
)
{
    NODELIST_DATA   *pList;
    NODE_DATA       *pNode;
    NODE_DATA       *pNode2;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    NODEARRAY_DATA  *pArray;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pList = nodeList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = nodeList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {
        
        nodeList_setOrdered(pList, true);
        
        for (i=0; i<10; ++i) {
            fprintf(stderr, "\tAdding %s\n", strings[i]);
            pNode = node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
            eRc = nodeList_Add2Head(pList, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pNode2 = nodeList_FindA(pList, 0, strings[i]);
            XCTAssertTrue( (pNode2) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
        cnt = nodeList_getSize(pList);
        fprintf(stderr, "\n\tCount = %d\n", cnt);
        for (i=0; i<cnt; ++i) {
            char        *pNameA = NULL;
            pNode = nodeList_Get(pList, i+1);
            pNameA = node_getNameUTF8(pNode);
            fprintf(stderr, "\t\t%s\n", pNameA);
            mem_Free(pNameA);
            pNameA = NULL;
        }

        fprintf(stderr, "\nForEach:\n");
        nodeList_ForEach(pList, (void *)listEntryPrintRtn, pList, NULL);
        
        pArray = nodeList_Nodes(pList);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        XCTAssertTrue( (nodeList_getSize(pList) == nodeArray_getSize(pArray)) );
        for (i=0; i<cnt; ++i) {
            pNode = nodeList_Get(pList, i+1);
            pNode2 = nodeArray_Get(pArray, i+1);
            eRc = node_Compare(pNode, pNode2);
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        }
        obj_Release(pArray);
        pArray = OBJ_NIL;

        obj_Release(pList);
        pList = OBJ_NIL;
        //szTbl_SharedReset();
    }
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeList);
    TINYTEST_ADD_TEST(test_nodeList_AddFindDelete02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeList_AddFindDelete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeList);





