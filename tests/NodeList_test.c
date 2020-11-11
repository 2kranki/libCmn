// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/10/2020 13:58:08
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
//#include    <szTbl.h>
#include    <trace.h>
#include    <NodeList_internal.h>



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

    pNameA = Node_getNameUTF8(pNode);
    fprintf(stderr, "\t\t%s\n", pNameA);
    mem_Free(pNameA);
    return ERESULT_SUCCESS;
}



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

    //szTbl_SharedReset( );
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






int             test_NodeList_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODELIST_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODELIST);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeList_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODELIST_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeList_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeList_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODELIST);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeList_AddFindDelete01(
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

    pList = NodeList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = NodeList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {

        for (i=0; i<10; ++i) {
            pNode = Node_NewWithUTF8ConAndClass(0, strings[i], OBJ_NIL);
            eRc = NodeList_Add2Head(pList, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = NodeList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pNode = NodeList_FindA(pList, 0, strings[i]);
            XCTAssertTrue( (pNode) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

#ifdef XYZZY
        eRc = NodeList_DeleteA(pList, 0, strings[5]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = NodeList_getSize(pList);
        XCTAssertTrue( (cnt == 9) );
        pNode = NodeList_FindA(pList, 0, strings[11]);
        XCTAssertTrue( (OBJ_NIL == pNode) );
#endif

        obj_Release(pList);
        pList = OBJ_NIL;
        //szTbl_SharedReset();
    }

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int         test_NodeList_AddFindDelete02(
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

    pList = NodeList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pList) );
    pList = NodeList_Init( pList );
    XCTAssertFalse( (OBJ_NIL == pList) );
    if (pList) {

        NodeList_setOrdered(pList, true);

        for (i=0; i<10; ++i) {
            fprintf(stderr, "\tAdding %s\n", strings[i]);
            pNode = Node_NewWithUTF8ConAndClass(0, strings[i], OBJ_NIL);
            eRc = NodeList_Add2Head(pList, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = NodeList_getSize(pList);
            XCTAssertTrue( (cnt == (i+1)) );
            pNode2 = NodeList_FindA(pList, 0, strings[i]);
            XCTAssertTrue( (pNode2) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        cnt = NodeList_getSize(pList);
        fprintf(stderr, "\n\tCount = %d\n", cnt);
        for (i=0; i<cnt; ++i) {
            char        *pNameA = NULL;
            pNode = NodeList_Index(pList, i+1);
            pNameA = Node_getNameUTF8(pNode);
            fprintf(stderr, "\t\t%s\n", pNameA);
            mem_Free(pNameA);
            pNameA = NULL;
        }

        fprintf(stderr, "\nForEach:\n");
        NodeList_ForEach(pList, (void *)listEntryPrintRtn, pList, NULL);

        pArray = NodeList_Nodes(pList);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        XCTAssertTrue( (NodeList_getSize(pList) == NodeArray_getSize(pArray)) );
        for (i=0; i<cnt; ++i) {
            pNode = NodeList_Index(pList, i+1);
            pNode2 = NodeArray_Get(pArray, i+1);
            eRc = Node_Compare(pNode, pNode2);
            XCTAssertTrue( (0 == eRc) );
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




TINYTEST_START_SUITE(test_NodeList);
    TINYTEST_ADD_TEST(test_NodeList_AddFindDelete02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeList_AddFindDelete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeList_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeList_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeList);





