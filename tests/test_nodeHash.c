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
    pObj = nodeHash_Init(pObj, 13);
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
    NODE_DATA       *pNodeFnd;
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
            pNode = node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
            eRc = nodeHash_Add(pHash, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeHash_getSize(pHash);
            XCTAssertTrue( (cnt == (i+1)) );
            pNodeFnd = nodeHash_FindA(pHash, 0, strings[i]);
            XCTAssertTrue( (pNode) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
 
        eRc = nodeHash_DeleteA(pHash, 0, strings[5]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        cnt = nodeHash_getSize(pHash);
        XCTAssertTrue( (cnt == 9) );
        pNodeFnd = nodeHash_FindA(pHash, 0, strings[11]);
        XCTAssertTrue( (OBJ_NIL == pNodeFnd) );
        
        obj_Release(pHash);
        pHash = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_nodeHash_AddFindDelete02(
    const
    char        *pTestName
)
{
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pNode;
    NODE_DATA       *pNodeFnd;
    NODEHASH_NODE   *pIntNode;
    ERESULT         eRc;
    char            **pStrA;
    uint32_t        numBuckets;     // Number of Hash Buckets
    uint32_t        numEmpty;       // Number of Empty Hash Buckets
    uint32_t        numMax;         // Maximum Number in any one Hash Bucket
    uint32_t        numAvg;         // Average Number in each Hash Bucket
    uint32_t        i;
    uint32_t        iMax;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHash = nodeHash_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    pHash = nodeHash_Init( pHash, 5 );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    if (pHash) {
        
        pStrA = strings;
        while (*pStrA) {
            pNode = node_NewWithUTF8ConAndClass(*pStrA, 0, OBJ_NIL);
            eRc = nodeHash_Add(pHash, pNode);
            XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
            pNodeFnd = nodeHash_FindA(pHash, 0, *pStrA);
            XCTAssertTrue( (pNode) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
            ++pStrA;
        }
        
        eRc = nodeHash_CalcHashStats(pHash, &numBuckets, &numEmpty, &numMax, &numAvg);
        XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tnumBuckets=%d numEmpty=%d numMax=%d numAvg=%d\n",
                numBuckets,
                numEmpty,
                numMax,
                numAvg
        );
        
        iMax = pHash->cHash;
        for (i=0; i<iMax; ++i) {
            LISTDL_DATA     *pNodeList;
            ASTR_DATA       *pStr = OBJ_NIL;
            
            pNodeList = &pHash->pHash[i];
            pIntNode = listdl_Head(pNodeList);
            fprintf(stderr, "\tHash Chain %d:\n", (i+1));
            while ( pIntNode ) {
                pStr = node_ToDebugString(pIntNode->pNode, 4);
                fprintf(stderr, "\t%s", AStr_getData(pStr));
                obj_Release(pStr);
                pIntNode = listdl_Next(pNodeList, pIntNode);
            }
                
        }
        
        obj_Release(pHash);
        pHash = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_nodeHash_JSON01(
    const
    char        *pTestName
)
{
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pNode;
    NODE_DATA       *pNodeFnd;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHash = nodeHash_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    pHash = nodeHash_Init( pHash, 5 );
    XCTAssertFalse( (OBJ_NIL == pHash) );
    if (pHash) {
        
        for (i=0; i<10; ++i) {
            pNode = node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
            eRc = nodeHash_Add(pHash, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeHash_getSize(pHash);
            XCTAssertTrue( (cnt == (i+1)) );
            pNodeFnd = nodeHash_FindA(pHash, 0, strings[i]);
            XCTAssertTrue( (pNode) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
        pStr = nodeHash_ToJSON(pHash);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON=\"%s\"\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pHash);
        pHash = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_nodeHash_Merge01(
    const
    char        *pTestName
)
{
    NODEHASH_DATA   *pHash1;
    NODEHASH_DATA   *pHash2;
    NODE_DATA       *pNode;
    NODE_DATA       *pNodeFnd;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHash1 = nodeHash_New(NODEHASH_TABLE_SIZE_XXXXSMALL);
    XCTAssertFalse( (OBJ_NIL == pHash1) );
    pHash2 = nodeHash_New(NODEHASH_TABLE_SIZE_XXXXXSMALL);
    XCTAssertFalse( (OBJ_NIL == pHash2) );
    
    for (i=0; i<10; ++i) {
        pNode = node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
        eRc = nodeHash_Add(pHash1, pNode);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
    }
    
    for (i=10; i<15; ++i) {
        pNode = node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
        eRc = nodeHash_Add(pHash2, pNode);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
    }
    pStr = AStr_NewA("test");
    pNode = node_NewWithUTF8ConAndClass(strings[1], 0, pStr);
    eRc = nodeHash_Add(pHash2, pNode);
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    obj_Release(pNode);
    pNode = OBJ_NIL;
    obj_Release(pStr);
    pStr = OBJ_NIL;
    
    eRc = nodeHash_Merge(pHash1, pHash2, true);
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    i = nodeHash_getSize(pHash1);
    XCTAssertTrue( (15 == i) );
    pNodeFnd = nodeHash_FindA(pHash1, 0, strings[1]);
    XCTAssertTrue( (pNodeFnd) );
    pStr = node_getData(pNodeFnd);
    XCTAssertTrue( (pStr) );
    XCTAssertTrue( (obj_IsKindOf(pStr, OBJ_IDENT_ASTR)) );
    XCTAssertTrue( (0 == strcmp(AStr_getData(pStr), "test")) );

    obj_Release(pHash1);
    pHash1 = OBJ_NIL;
    obj_Release(pHash2);
    pHash2 = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_nodeHash_Expand01(
    const
    char            *pTestName
                                    )
{
    NODEHASH_DATA   *pObj = OBJ_NIL;
    ERESULT         eRc = ERESULT_SUCCESS;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pResult = "LIBNAM=libTest\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = nodeHash_New(NODEHASH_TABLE_SIZE_XXXXXSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = AStr_NewA("lib");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = nodeHash_AddA(pObj, "lib_prefix", 0, pStr);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = AStr_NewA("Test");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = nodeHash_AddA(pObj, "name", 0, pStr);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = AStr_NewA("LIBNAM=${lib_prefix}${name}\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = nodeHash_Expand(pObj, pStr);
            fprintf(stderr, "\tResult=\"%s\"\n", AStr_getData(pStr));
            TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), pResult)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        pStr = AStr_NewA("LIBNAM=$lib_prefix$name\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = nodeHash_Expand(pObj, pStr);
            fprintf(stderr, "\tResult=\"%s\"\n", AStr_getData(pStr));
            TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), pResult)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_nodeHash);
    TINYTEST_ADD_TEST(test_nodeHash_Expand01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeHash_Merge01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeHash_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeHash_AddFindDelete02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeHash_AddFindDelete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_nodeHash_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_nodeHash);





