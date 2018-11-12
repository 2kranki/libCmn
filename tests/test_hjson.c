/*
 *	Generated 07/08/2017 17:18:30
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
#include    <hjson_internal.h>
#include    <nodeArray.h>
#include    <nodeHash.h>



static
const
char        *pTestInput01 =
"// Test01 Input\n"
"{ /* test comment */\n\n\n"
    "\t\"one\" : 123,\n"
    "\ttwo : \"xyz\"\n"
    "\t#two_a : \"xyz\"\n"
    "\tthree : [a, b, c],\n"
    "\t//three_b : [a, b, c],\n"
    "\tfour : null\n"       // Note <=== missing comma
    "\t#four_c : null,\n"
    "\t\"five\" : true,\n"
    "\t\"six\" : false\n"
"}\n";





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

    
    szTbl_SharedReset( );
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






int         test_hjson_OpenClose(
    const
    char        *pTestName
)
{
    HJSON_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = hjson_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = hjson_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_hjson01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pHJSON = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray;
    const
    char            *pStrA;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pStr = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pStr) );
    
    pHJSON = hjson_NewAStr(pStr, 4);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    XCTAssertFalse( (OBJ_NIL == pHJSON) );
    if (pHJSON) {
        
        //obj_TraceSet(pHJSON, true);
        pFileNode = hjson_ParseFileHash(pHJSON);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", nodeHash_getSize(pHash));
            XCTAssertTrue( (6 == nodeHash_getSize(pHash)) );
            
            pNode = nodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("integer", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))) );
            
            pNode = nodeHash_FindA(pHash, 0, "two");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("string", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))) );
            
            pNode = nodeHash_FindA(pHash, 0, "three");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("array", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pArray = node_getData(pNode);
            fprintf(stderr, "array size = %d\n", nodeArray_getSize(pArray));
            XCTAssertTrue( (3 == nodeArray_getSize(pArray)) );
            pNode = nodeArray_Get(pArray, 1);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("a", AStr_getData(pStr))) );
            pNode = nodeArray_Get(pArray, 2);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("b", AStr_getData(pStr))) );
            pNode = nodeArray_Get(pArray, 3);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("c", AStr_getData(pStr))) );
            
            pNode = nodeHash_FindA(pHash, 0, "four");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("null", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            
            pNode = nodeHash_FindA(pHash, 0, "five");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("true", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            
            pNode = nodeHash_FindA(pHash, 0, "six");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("false", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pHJSON);
        pHJSON = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_hjson02(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pHJSON = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    const
    char            *pStrA;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHJSON = hjson_NewA("{\"one\" : +123}\n", 4);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    XCTAssertFalse( (OBJ_NIL == pHJSON) );
    if (pHJSON) {
        
        obj_TraceSet(pHJSON, true);
        pFileNode = hjson_ParseFileHash(pHJSON);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", nodeHash_getSize(pHash));
            XCTAssertTrue( (1 == nodeHash_getSize(pHash)) );
            
            pNode = nodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("integer", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("+123", AStr_getData(pStr))) );
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pHJSON);
        pHJSON = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_hjson03(
    const
    char        *pTestName
)
{
    HJSON_DATA      *pHJSON = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    const
    char            *pStrA;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHJSON = hjson_NewA("{\"one\":-123}", 4);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    XCTAssertFalse( (OBJ_NIL == pHJSON) );
    if (pHJSON) {
        
        obj_TraceSet(pHJSON, true);
        pFileNode = hjson_ParseFileHash(pHJSON);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", nodeHash_getSize(pHash));
            XCTAssertTrue( (1 == nodeHash_getSize(pHash)) );
            
            pNode = nodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("integer", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("-123", AStr_getData(pStr))) );
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pHJSON);
        pHJSON = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_hjson04(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pHJSON = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    const
    char            *pStrA;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHJSON = hjson_NewA("{\"one\" : {}}\n", 4);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    XCTAssertFalse( (OBJ_NIL == pHJSON) );
    if (pHJSON) {
        
        obj_TraceSet(pHJSON, true);
        pFileNode = hjson_ParseFileHash(pHJSON);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", nodeHash_getSize(pHash));
            XCTAssertTrue( (1 == nodeHash_getSize(pHash)) );
            
            pNode = nodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = node_getData(pNode);
            XCTAssertTrue( (0 == nodeHash_getSize(pHash)) );
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pHJSON);
        pHJSON = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_hjson05(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pHJSON = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray;
    const
    char            *pStrA;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pHJSON = hjson_NewA("{\"one\" : [] }\n", 4);
    obj_Release(pStr);
    pStr = OBJ_NIL;
    XCTAssertFalse( (OBJ_NIL == pHJSON) );
    if (pHJSON) {
        
        obj_TraceSet(pHJSON, true);
        pFileNode = hjson_ParseFileHash(pHJSON);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", nodeHash_getSize(pHash));
            XCTAssertTrue( (1 == nodeHash_getSize(pHash)) );
            
            pNode = nodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("array", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pArray = node_getData(pNode);
            XCTAssertTrue( (0 == nodeArray_getSize(pArray)) );
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pHJSON);
        pHJSON = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int             test_hjson_File01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    //NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = path_NewA("~/git/libCmn/tests/test_hjson_01.txt");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    eRc = path_Clean(pPath);
    XCTAssertTrue( (ERESULT_SUCCESSFUL(eRc)) );
    
    pObj = hjson_NewFromPath(pPath, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_Release(pPath);
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = hjson_ParseFileHash(pObj);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStr = node_ToDebugString(pFileNode, 0);
            fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int             test_hjson_File02(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    //NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    FILE            *pInput = NULL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = path_NewA("~/git/libCmn/tests/test_hjson_02.txt");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    eRc = path_Clean(pPath);
    XCTAssertTrue( (ERESULT_SUCCESSFUL(eRc)) );

    pInput = fopen(path_getData(pPath), "r");
    XCTAssertFalse( (OBJ_NIL == pInput) );
    
    pObj = hjson_NewFromFile(pInput, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_Release(pPath);
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = hjson_ParseFileHash(pObj);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStr = node_ToDebugString(pFileNode, 0);
            fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fclose(pInput);
    pInput = NULL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_hjson);
    TINYTEST_ADD_TEST(test_hjson_File02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson_File01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_hjson);





