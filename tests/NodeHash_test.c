// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/10/2020 16:43:06
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
//#include    <szTbl.h>
#include    <trace.h>
#include    <NodeHash_internal.h>



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




ERESULT         scanPrintExit(
    NODEHASH_DATA   *this,
    NODEHASH_RECORD *pRecord,
    void            *pArg3
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    RBT_NODE        *pNode = &pRecord->node;
    NODE_DATA       *pNode2 = pRecord->node.pKey;
    char            *pName;

    pName = Node_getNameUTF8(pNode2);
    fprintf(
        stderr,
        "\t\t%p  L=%p R=%p %s   D=%p U=%d  cls=%4d %s\n",
        pNode,
        pNode->pLink[RBT_LEFT],
        pNode->pLink[RBT_RIGHT],
        pNode->color ? "red" : "black",
        pNode->pKey,
        pRecord->unique,
        Node_getClass(pNode2),
        pName
    );
    mem_Free(pName);

    return eRc;
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






int             test_NodeHash_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEHASH_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEHASH);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_NodeHash_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    NODEHASH_DATA	*pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_NODEHASH);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeHash_AddFindDelete01(
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

    pHash = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    XCTAssertFalse( (OBJ_NIL == pHash) );
    if (pHash) {

        for (i=0; i<10; ++i) {
            pNode = Node_NewWithUTF8ConAndClass(0, strings[i], OBJ_NIL);
            eRc = NodeHash_Add(pHash, pNode);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            cnt = NodeHash_getSize(pHash);
            XCTAssertTrue( (cnt == (i+1)) );
            fprintf(stderr, "\tAdded %p - %s\n", pNode, strings[i]);
            fprintf(stderr, "\tLooking for: %s\n", strings[i]);
            pNodeFnd = NodeHash_FindA(pHash, 0, strings[i]);
            XCTAssertTrue( (pNode) );
            fprintf(stderr, "\t\tFound\n");
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        eRc = NodeHash_DeleteA(pHash, 0, strings[5]);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        cnt = NodeHash_getSize(pHash);
        XCTAssertTrue( (cnt == 9) );
        pNodeFnd = NodeHash_FindA(pHash, 0, strings[11]);
        XCTAssertTrue( (OBJ_NIL == pNodeFnd) );

        obj_Release(pHash);
        pHash = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeHash_AddFindDelete02(
    const
    char        *pTestName
)
{
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pNode;
    NODE_DATA       *pNodeFnd;
    NODEHASH_RECORD *pRecord;
    ERESULT         eRc;
    char            **pStrA;
    uint32_t        numBuckets;     // Number of Hash Buckets
    uint32_t        numEmpty;       // Number of Empty Hash Buckets
    uint32_t        numMax;         // Maximum Number in any one Hash Bucket
    uint32_t        numAvg;         // Average Number in each Hash Bucket
    uint32_t        i;
    uint32_t        iMax;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pHash = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    XCTAssertFalse( (OBJ_NIL == pHash) );
    if (pHash) {

        pStrA = strings;
        while (*pStrA) {
            pNode = Node_NewWithUTF8ConAndClass(0, *pStrA, OBJ_NIL);
            eRc = NodeHash_Add(pHash, pNode);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            fprintf(stderr, "\tAdded %p - %s\n", pNode, *pStrA);
            fprintf(stderr, "\tLooking for: %s\n", *pStrA);
            pNodeFnd = NodeHash_FindA(pHash, 0, *pStrA);
            XCTAssertTrue( (pNode) );
            fprintf(stderr, "\t\tFound\n");
            obj_Release(pNode);
            pNode = OBJ_NIL;
            ++pStrA;
        }

        eRc = NodeHash_CalcHashStats(pHash, &numBuckets, &numEmpty, &numMax, &numAvg);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        fprintf(
                stderr,
                "\tnumBuckets=%d numEmpty=%d numMax=%d numAvg=%d\n",
                numBuckets,
                numEmpty,
                numMax,
                numAvg
        );

        fprintf(stderr, "Hash Chains %d:\n", pHash->cHash);
        iMax = pHash->cHash;
        for (i=0; i<iMax; ++i) {
            RBT_TREE        *pTree;
            //ASTR_DATA       *pStr = OBJ_NIL;

            fprintf(stderr, "\tChain %4d:\n", i);
            pTree = &pHash->pHash[i];
            eRc =   rbt_VisitNodeInRecurse(
                                       pTree,
                                       pTree->pRoot,
                                       (void *)scanPrintExit,
                                       pHash,               // Used as first parameter of scan method
                                       NULL                 // Used as third parameter of scan method
                    );

        }

        obj_Release(pHash);
        pHash = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_NodeHash_Json01(
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
    const
    char        *pJsonStrA = "{ "
    "\"objectType\":\"nodeHash\", "
    "\"count\":2, "
    "\"entries\":[\n"
    "{ \"objectType\":\"node\", \"class\":0, \"type\":0, \"unique\":91,"
    " \"misc\":0, \"misc1\":0, \"misc2\":0, \n"
    "\t\"name\": {\"objectType\":\"name\", \"type\":2 /*NAME_TYPE_UTF8*/, \"data\":{ \"objectType\":\"utf8\", "
    "\"len\":5, \"crc\":1943333782, \"data\":\"bobby\" }\n"
    "}\n\n}\n"
    ",\n"
    "{ \"objectType\":\"node\", \"class\":0, \"type\":0, \"unique\":89,"
    " \"misc\":0, \"misc1\":0, \"misc2\":0, \n"
    "\t\"name\": {\"objectType\":\"name\", \"type\":2 /*NAME_TYPE_UTF8*/, \"data\":{ \"objectType\":\"utf8\", "
    "\"len\":3, \"crc\":4123767104, \"data\":\"bob\" }\n"
    "}\n\n}\n\n"
    "]\n\n\n"
    "}\n";
    uint32_t    iRc;
    int         index = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pHash = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    XCTAssertFalse( (OBJ_NIL == pHash) );
    if (pHash) {

        for (i=0; i<2; ++i) {
            pNode = Node_NewWithUTF8ConAndClass(0, strings[i], OBJ_NIL);
            eRc = NodeHash_Add(pHash, pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = NodeHash_getSize(pHash);
            XCTAssertTrue( (cnt == (i+1)) );
            pNodeFnd = NodeHash_FindA(pHash, 0, strings[i]);
            XCTAssertTrue( (pNode) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }

        pStr = NodeHash_ToJson(pHash);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON=\"%s\"\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(AStr_getData(pStr), pJsonStrA, &index);
        fprintf(stderr, "\tCompareSpcl: %d, index=%d\n", iRc, index);
        XCTAssertTrue( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pHash);
        pHash = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



#ifdef XYZZY
int         test_NodeHash_Merge01(
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

    pHash1 = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    XCTAssertFalse( (OBJ_NIL == pHash1) );
    pHash2 = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    XCTAssertFalse( (OBJ_NIL == pHash2) );

    for (i=0; i<10; ++i) {
        pNode = Node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
        eRc = NodeHash_Add(pHash1, pNode);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
    }

    for (i=10; i<15; ++i) {
        pNode = Node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
        eRc = NodeHash_Add(pHash2, pNode);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
    }
    pStr = AStr_NewA("test");
    pNode = Node_NewWithUTF8ConAndClass(strings[1], 0, pStr);
    eRc = NodeHash_Add(pHash2, pNode);
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    obj_Release(pNode);
    pNode = OBJ_NIL;
    obj_Release(pStr);
    pStr = OBJ_NIL;

    eRc = NodeHash_Merge(pHash1, pHash2, true);
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    i = NodeHash_getSize(pHash1);
    XCTAssertTrue( (15 == i) );
    pNodeFnd = NodeHash_FindA(pHash1, 0, strings[1]);
    XCTAssertTrue( (pNodeFnd) );
    pStr = Node_getData(pNodeFnd);
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
#endif



#ifdef XYZZY
int             test_NodeHash_Expand01(
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

    pObj = NodeHash_NewWithSize(NODEHASH_TABLE_SIZE_XSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = AStr_NewA("lib");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = NodeHash_AddA(pObj, "lib_prefix", 0, pStr);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = AStr_NewA("Test");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = NodeHash_AddA(pObj, "name", 0, pStr);
        TINYTEST_TRUE( (!ERESULT_FAILED(eRc)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        pStr = AStr_NewA("LIBNAM=${lib_prefix}${name}\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = NodeHash_Expand(pObj, pStr);
            fprintf(stderr, "\tResult=\"%s\"\n", AStr_getData(pStr));
            TINYTEST_TRUE( (0 == strcmp(AStr_getData(pStr), pResult)) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        pStr = AStr_NewA("LIBNAM=$lib_prefix$name\n");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        if (pStr) {
            eRc = NodeHash_Expand(pObj, pStr);
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
#endif




TINYTEST_START_SUITE(test_NodeHash);
    //TINYTEST_ADD_TEST(test_NodeHash_Expand01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_NodeHash_Merge01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_NodeHash_Json01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeHash_AddFindDelete02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeHash_AddFindDelete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeHash_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_NodeHash_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_NodeHash);





