/*
 *	Generated 10/18/2015 19:44:45
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */


#import <XCTest/XCTest.h>
#import <libCmn/libCmn.h>



// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      XCTAssert(expression, failure_description, ...)
//      XCTFail(failure_description, ...)
//      XCTAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      XCTAssertEquals(value_1, value_2, failure_description, ...)
//      XCTAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      XCTAssertNil(expression, failure_description, ...)
//      XCTAssertNotNil(expression, failure_description, ...)
//      XCTAssertTrue(expression, failure_description, ...)
//      XCTAssertFalse(expression, failure_description, ...)
//      XCTAssertThrows(expression, failure_description, ...)
//      XCTAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    "json_internal.h"



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



@interface jsonTests : XCTestCase

@end

@implementation jsonTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    mem_Dump( );
    mem_Release( );
    
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
}




- (void)testOpenClose
{
    JSON_DATA	*pObj = OBJ_NIL;
   
    pObj = json_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = json_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    szTbl_SharedReset();
}



- (void)testInput01
{
    ERESULT         eRc;
    JSON_DATA       *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray;
    const
    char            *pStrA;
    
    
    pStr = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pStr) );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    
    pObj = json_NewAStr( pStr, pPath, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_Release(pStr);
    obj_Release(pPath);
    obj_setFlags(pObj, (obj_getFlags(pObj) | OBJ_FLAG_TRACE));
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = json_ParseFile(pObj);
        XCTAssertFalse( (OBJ_NIL == pFileNode) );
        if (pFileNode) {
            pStrA = node_getNameUTF8(pFileNode);
            XCTAssertTrue( (0 == strcmp("hash", pStrA)) );
            mem_Free((void *)pStrA);
            pHash = node_getData(pFileNode);
            XCTAssertFalse( (OBJ_NIL == pHash) );
            XCTAssertTrue( (4 == nodeHash_getSize(pHash)) );
            
            eRc = nodeHash_FindA(pHash, "one", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("number", pStrA)) );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("123", AStr_getData(pStr))) );
            
            eRc = nodeHash_FindA(pHash, "two", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pNode = node_getData(pNode);
            pStrA = node_getNameUTF8(pNode);
            XCTAssertTrue( (0 == strcmp("string", pStrA)) );
            mem_Free((void *)pStrA);
            pStr = node_getData(pNode);
            XCTAssertTrue( (0 == strcmp("xyz", AStr_getData(pStr))) );
            
            eRc = nodeHash_FindA(pHash, "three", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
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
            
            eRc = nodeHash_FindA(pHash, "four", &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
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
    
    szTbl_SharedReset();
}



- (void)testInput02
{
    //ERESULT         eRc;
    JSON_DATA       *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    //NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    
    
    pPath = path_NewA("/Users/bob/git/libCan/other/pic32mx/can.json.txt");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    
    pObj = json_NewFromPath( pPath, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_Release(pPath);
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = json_ParseFile(pObj);
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
    
    szTbl_SharedReset();
}



- (void)testInput03
{
    //ERESULT         eRc;
    JSON_DATA       *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    //NODEHASH_DATA   *pHash;
    NODE_DATA       *pFileNode;
    //NODE_DATA       *pNode;
    //NODEARRAY_DATA  *pArray;
    FILE            *pInput = NULL;
    
    
    pInput = fopen("/Users/bob/git/libCan/other/pic32mx/can.json.txt", "r");
    XCTAssertFalse( (OBJ_NIL == pInput) );
    
    pObj = json_NewFromFile( pInput, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_Release(pPath);
    if (pObj) {
        
        obj_TraceSet(pObj, true);
        pFileNode = json_ParseFile(pObj);
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
    
    szTbl_SharedReset();
}



@end



