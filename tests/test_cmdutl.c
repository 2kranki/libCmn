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
#include    <cmdutl_internal.h>



//fixme: need to adjust for:
static
const
char        *pTestInput01 =
    " "
    "one=123 "
    "--two=\"xyz\" "
    "three=[\"a\", \"b\", \"c\"] "
    "4"
"\n";


#ifdef XYZZY
static
const
char        *pTestInput02 =
"{\n"
    "\"one\": {\n"
            "\t\"header\": \"SVG Viewer\",\n"
            "\t\"items\": [\n"
                            "\t\t{\"id\": \"Open\"},\n"
                            "\t\t[\"abc\", 1.234, 0.3e-1, 3.141516,],\n"
                            "\t\tnull,\n"
                            "\t\tfalse,\n"
                            "\t\ttrue\n"
                            "]\n"
            "\t}\n"
    "\"two\":null\n"
"}\n";
#endif



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

    
    szTbl_SharedReset();
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






int         test_cmdutl_OpenClose(
    const
    char        *pTestName
)
{
    CMDUTL_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = cmdutl_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = cmdutl_Init(pObj, 0, NULL);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_CommandString01(
    const
    char        *pTestName
)
{
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    uint32_t        cArray;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pArray = cmdutl_CommandStringToArray(" a b --c d");
    XCTAssertFalse( (OBJ_NIL == pArray) );
    cArray = AStrArray_getSize(pArray);
    XCTAssertTrue( (5 == cArray) );

    if (pArray) {

        pStr = AStrArray_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "")) );
        
        pStr = AStrArray_Get(pArray, 2);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "a")) );
        
        pStr = AStrArray_Get(pArray, 3);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "b")) );
        
        pStr = AStrArray_Get(pArray, 4);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "--c")) );
        
        pStr = AStrArray_Get(pArray, 5);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "d")) );
        
        obj_Release(pArray);
        pArray = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_cmdutl_Input01(
    const
    char        *pTestName
)
{
    CMDUTL_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    NODE_DATA       *pFileNode = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    const
    char            *pStrA = NULL;
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pStr) );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    
    //pObj = cmdutl_NewAStr(pStr, pPath, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_Release(pStr);
    obj_Release(pPath);
    obj_setFlags(pObj, (obj_getFlags(pObj) | OBJ_FLAG_TRACE));
    if (pObj) {
        
        //pFileNode = cmdutl_ParseFile(pObj);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            XCTAssertTrue( (4 == nodeHash_getSize(pHash)) );
            
            pNode = nodeHash_FindA(pHash, "one");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("number", pStrA)) );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))) );
            
            pNode = nodeHash_FindA(pHash, "two");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("string", pStrA)) );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))) );
            
            pNode = nodeHash_FindA(pHash, "three");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("array", pStrA)) );
            mem_Free((void *)pStrA);
            pArray = node_getData(pNode);
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
            
            pNode = nodeHash_FindA(pHash, "four");
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("null", pStrA)) );
            mem_Free((void *)pStrA);
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_cmdutl);
    //TINYTEST_ADD_TEST(test_cmdutl_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_CommandString01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_cmdutl_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_cmdutl);





