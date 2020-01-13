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
#include    <JsonIn.h>
#include    <hjson_internal.h>
#include    <NodeArray.h>
#include    <NodeHash.h>
#include    <SrcErrors.h>



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
    SrcErrors_SharedReset( );
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
            pStrA = Node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = Node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", NodeHash_getSize(pHash));
            XCTAssertTrue( (6 == NodeHash_getSize(pHash)) );
            
            pNode = NodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("integer", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = Node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))) );
            
            pNode = NodeHash_FindA(pHash, 0, "two");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("string", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = Node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))) );
            
            pNode = NodeHash_FindA(pHash, 0, "three");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("array", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pArray = Node_getData(pNode);
            fprintf(stderr, "array size = %d\n", NodeArray_getSize(pArray));
            XCTAssertTrue( (3 == NodeArray_getSize(pArray)) );
            pNode = NodeArray_Get(pArray, 1);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = Node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("a", AStr_getData(pStr))) );
            pNode = NodeArray_Get(pArray, 2);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = Node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("b", AStr_getData(pStr))) );
            pNode = NodeArray_Get(pArray, 3);
            XCTAssertFalse( (OBJ_NIL == pNode) );
            pStr = Node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("c", AStr_getData(pStr))) );
            
            pNode = NodeHash_FindA(pHash, 0, "four");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("null", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            
            pNode = NodeHash_FindA(pHash, 0, "five");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("true", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            
            pNode = NodeHash_FindA(pHash, 0, "six");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
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
            pStrA = Node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = Node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", NodeHash_getSize(pHash));
            XCTAssertTrue( (1 == NodeHash_getSize(pHash)) );
            
            pNode = NodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("integer", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = Node_getData(pNode);
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
            pStrA = Node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = Node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", NodeHash_getSize(pHash));
            XCTAssertTrue( (1 == NodeHash_getSize(pHash)) );
            
            pNode = NodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("integer", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pStr = Node_getData(pNode);
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
            pStrA = Node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = Node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", NodeHash_getSize(pHash));
            XCTAssertTrue( (1 == NodeHash_getSize(pHash)) );
            
            pNode = NodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = Node_getData(pNode);
            XCTAssertTrue( (0 == NodeHash_getSize(pHash)) );
            
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
            pStrA = Node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pHash = Node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            fprintf(stderr, "hash size = %d\n", NodeHash_getSize(pHash));
            XCTAssertTrue( (1 == NodeHash_getSize(pHash)) );
            
            pNode = NodeHash_FindA(pHash, 0, "one");
            XCTAssertTrue( (pNode) );
            pNode = Node_getData(pNode);
            pStrA = Node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("array", pStrA)) );
            mem_Free((void *)pStrA);
            pStrA = NULL;
            pArray = Node_getData(pNode);
            XCTAssertTrue( (0 == NodeArray_getSize(pArray)) );
            
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
    
    pPath = path_NewA("~/git/libCmn/tests/files/test_hjson_01.txt");
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
            pStr = Node_ToDebugString(pFileNode, 0);
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
    
    pPath = path_NewA("~/git/libCmn/tests/files/test_hjson_02.txt");
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
            pStr = Node_ToDebugString(pFileNode, 0);
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



int         test_hjson_Float01(
    const
    char        *pTestName
)
{
    //ERESULT         eRc;
    HJSON_DATA      *pObj = OBJ_NIL;
    NODE_DATA       *pFileNode;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParseA = "{\"one\": 3.1416}";
    //NODEHASH_DATA   *pHash;
    //int64_t         num = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = hjson_NewA(pStringToParseA, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        pFileNode = hjson_ParseFileHash(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStr = Node_ToDebugString(pFileNode, 3);
            if (pStr) {
                fprintf(stderr, "%s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            obj_Release(pFileNode);
            pFileNode = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_hjson_Float02(
    const
    char        *pTestName
)
{
    //ERESULT         eRc;
    HJSON_DATA      *pObj = OBJ_NIL;
    NODE_DATA       *pFileNode;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParseA = "{\"one\": 3.141600E+00}";
    //NODEHASH_DATA   *pHash;
    //int64_t         num = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = hjson_NewA(pStringToParseA, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        obj_TraceSet(pObj, true);
        pFileNode = hjson_ParseFileHash(pObj);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStr = Node_ToDebugString(pFileNode, 3);
            if (pStr) {
                fprintf(stderr, "%s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            obj_Release(pFileNode);
            pFileNode = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_hjson_Simple01(
    const
    char        *pTestName
)
{
    ERESULT         eRc;
    HJSON_DATA      *pObj = OBJ_NIL;
    NODE_DATA       *pFileNode;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParseA = "{\"one\" : +123}";
    NODEHASH_DATA   *pHash;
    int64_t         num = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = hjson_NewA(pStringToParseA, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = hjson_ParseFileHash(pObj);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStr = Node_ToDebugString(pFileNode, 0);
            fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
            
        }
        
        pHash = JsonIn_CheckNodeForHash(pFileNode);
        XCTAssertFalse( (OBJ_NIL == pHash) );
        eRc = NodeHash_FindIntegerNodeInHashA(pHash, "one", &num);
        XCTAssertTrue( (ERESULT_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (123 == num) );
        XCTAssertFalse( (SrcErrors_getFatal(OBJ_NIL)) );
        XCTAssertTrue( (0 == SrcErrors_getNumErrors(OBJ_NIL)) );

        obj_Release(pFileNode);
        pFileNode = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_hjson_Simple02(
    const
    char        *pTestName
)
{
    //ERESULT         eRc;
    HJSON_DATA      *pObj = OBJ_NIL;
    NODE_DATA       *pFileNode;
    //ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pStringToParseA = "{\"one\" : +123'}";
    //NODEHASH_DATA   *pHash;
    //int64_t         num = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = hjson_NewA(pStringToParseA, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = hjson_ParseFileHash(pObj);
        XCTAssertTrue( (OBJ_NIL == pFileNode) );
        XCTAssertTrue( (SrcErrors_getFatal(OBJ_NIL)) );
        XCTAssertTrue( (1 == SrcErrors_getNumErrors(OBJ_NIL)) );
        SrcErrors_Print(OBJ_NIL, stderr);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_hjson_Object01(
    const
    char            *pTestName
)
{
    HJSON_DATA      *pObj = OBJ_NIL;
    NODE_DATA       *pFileNode = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    const
    char            *pGoodJsonObject1 =
    "{\n"
        "\"AStr\":{"
            "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
            "\"srcs\":[\"str.c\",\"ascii.c\"],"
            "\"json\":true,"
            "\"test\":{\"reqArch\":\"X86\",\"reqOS\":\"macos\",srcs:[\"abc.c\"]}"
        "}\n"
    "}\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = hjson_NewA(pGoodJsonObject1, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = hjson_ParseFileHash(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pFileNode) );
        TINYTEST_FALSE( (SrcErrors_getFatal(OBJ_NIL)) );

        if (pFileNode) {
            ASTR_DATA       *pWrk = OBJ_NIL;
            pWrk = Node_ToDebugString(pFileNode, 0);
            fprintf(stderr, "===> GoodJsonObject1:\n%s\n\n\n", AStr_getData(pWrk));
            obj_Release(pWrk);
            pWrk = OBJ_NIL;
            
            pHash = Node_getData(pFileNode);
            TINYTEST_FALSE( (OBJ_NIL == pHash) );
            TINYTEST_TRUE( (obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH)) );

            obj_Release(pFileNode);
            pFileNode = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
        
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_hjson);
    TINYTEST_ADD_TEST(test_hjson_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson_Simple02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson_Simple01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson_Float02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_hjson_Float01,setUp,tearDown);
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





