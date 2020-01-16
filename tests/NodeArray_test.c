// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/10/2020 13:58:02
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
#include    <NodeArray_internal.h>



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






int             test_NodeArray_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEARRAY_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeArray_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEARRAY_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeArray_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = NodeArray_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEARRAY);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeArray_Add01(
    const
    char        *pTestName
)
{
    NODEARRAY_DATA  *pArray;
    NODE_DATA       *pNode;
    NODE_DATA       *pNode2;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    uint32_t        idx;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pArray = NodeArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pArray) );
    pArray = NodeArray_Init(pArray);
    XCTAssertFalse( (OBJ_NIL == pArray) );
    if (pArray) {

        for (i=0; i<10; ++i) {
            pNode = Node_NewWithUTF8ConAndClass(0, strings[i], OBJ_NIL);
            eRc = NodeArray_AppendNode(pArray, pNode, &idx);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = NodeArray_getSize(pArray);
            XCTAssertTrue( (idx == (i+1)) );
            XCTAssertTrue( (cnt == (i+1)) );
            pNode2 = NodeArray_Get(pArray, i+1);
            XCTAssertTrue( (pNode == pNode2) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        for (i=0; i<10; ++i) {
            pNode = OBJ_NIL;
            pNode = NodeArray_FindA(pArray, 0, strings[i]);
            XCTAssertFalse( (pNode == OBJ_NIL) );
        }

        pNode = OBJ_NIL;
        pNode = NodeArray_FindA(pArray, 0, "xyzzy");
        XCTAssertTrue( (pNode == OBJ_NIL) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_NodeArray_Add02(
    const
    char        *pTestName
)
{
    NODEARRAY_DATA  *pArray;
    NODE_DATA       *pNode;
    NODE_DATA       *pNode2;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    uint32_t        idx;
    int32_t         cls;
    I32ARRAY_DATA   *pClasses = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pArray = NodeArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pArray) );
    pArray = NodeArray_Init(pArray);
    XCTAssertFalse( (OBJ_NIL == pArray) );
    if (pArray) {

        for (i=0; i<10; ++i) {
            pNode = Node_NewWithUTF8ConAndClass(0, strings[i], OBJ_NIL);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            Node_setClass(pNode, i+1);
            eRc = NodeArray_AppendNode(pArray, pNode, &idx);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = NodeArray_getSize(pArray);
            XCTAssertTrue( (idx == (i+1)) );
            XCTAssertTrue( (cnt == (i+1)) );
            pNode2 = NodeArray_Get(pArray, i+1);
            XCTAssertTrue( (pNode == pNode2) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        pClasses = NodeArray_ToClassArray(pArray);
        XCTAssertFalse( (OBJ_NIL == pClasses) );
        for (i=0; i<10; ++i) {
            cls = I32Array_Get(pClasses, i+1);
            XCTAssertTrue( (cls == (i+1)) );
        }
        obj_Release(pClasses);
        pClasses = OBJ_NIL;

        obj_Release(pArray);
        pArray = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_NodeArray);
    TINYTEST_ADD_TEST(test_NodeArray_Add02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeArray_Add01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeArray_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeArray_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeArray);





