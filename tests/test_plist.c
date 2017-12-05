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
#include    <node.h>
#include    <nodeArray.h>
#include    <nodeHash.h>
#include    <path.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <plist_internal.h>



static
const
char        *pTestInput01 =
"{ \n"
    "\"one\": 123,\n"
    "\"two\":\"xyz\",\n"
    "\"three\":[\"a\",\"b\",\"c\"],\n"
    "\"four\":null\n"
"}\n";


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
"\t},\n"
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






int         test_plist_OpenClose(
    const
    char        *pTestName
)
{
    PLIST_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = plist_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = plist_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_plist_Input01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    PLIST_DATA      *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray;
    const
    char            *pStrA;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
   
#ifdef XYZZY 
    pStr = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pStr), @"" );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath), @"" );
    
    //FIXME: pObj = plist_NewAStr( pStr, pPath, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    obj_Release(pStr);
    obj_Release(pPath);
    obj_setFlags(pObj, (obj_getFlags(pObj) | OBJ_FLAG_TRACE));
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        //FIXME: pFileNode = plist_ParseFile(pObj);
        //XCTAssertFalse( (OBJ_NIL == pFileNode), @"" );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)), @"" );
            mem_Free((void *)pStrA);
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash), @"" );
            XCTAssertTrue( (4 == nodeHash_getSize(pHash)), @"" );
            
            eRc = nodeHash_FindA(pHash, "one", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("number", pStrA)), @"" );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))), @"" );
            
            eRc = nodeHash_FindA(pHash, "two", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("string", pStrA)), @"" );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))), @"" );
            
            eRc = nodeHash_FindA(pHash, "three", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("array", pStrA)), @"" );
            mem_Free((void *)pStrA);
            pArray = node_getData(pNode);
            XCTAssertTrue( (3 == nodeArray_getSize(pArray)), @"" );
            pNode = nodeArray_Get(pArray, 1);
            XCTAssertFalse( (OBJ_NIL == pNode), @"" );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("a", AStr_getData(pStr))), @"" );
            pNode = nodeArray_Get(pArray, 2);
            XCTAssertFalse( (OBJ_NIL == pNode), @"" );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("b", AStr_getData(pStr))), @"" );
            pNode = nodeArray_Get(pArray, 3);
            XCTAssertFalse( (OBJ_NIL == pNode), @"" );
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("c", AStr_getData(pStr))), @"" );
            
            eRc = nodeHash_FindA(pHash, "four", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("null", pStrA)), @"" );
            mem_Free((void *)pStrA);
            
        }
        
        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
#endif
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_plist);
  TINYTEST_ADD_TEST(test_plist_Input01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_plist_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_plist);





