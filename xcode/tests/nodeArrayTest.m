/*
 *	Generated 08/08/2015 09:07:21
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


#include    "nodeArray_internal.h"


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





@interface nodeArrayTests : XCTestCase

@end

@implementation nodeArrayTests


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
    NODEARRAY_DATA	*pObj = OBJ_NIL;
   
    pObj = nodeArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = nodeArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testAdd01
{
    NODEARRAY_DATA  *pArray;
    NODE_DATA       *pNode;
    NODE_DATA       *pNode2;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    uint32_t        idx;
    
    pArray = nodeArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pArray) );
    pArray = nodeArray_Init(pArray);
    XCTAssertFalse( (OBJ_NIL == pArray) );
    if (pArray) {
        
        for (i=0; i<10; ++i) {
            pNode = node_NewWithUTF8Con(strings[i], OBJ_NIL);
            eRc = nodeArray_AppendNode(pArray, pNode, &idx);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeArray_getSize(pArray);
            XCTAssertTrue( (idx == (i+1)) );
            XCTAssertTrue( (cnt == (i+1)) );
            pNode2 = nodeArray_Get(pArray, i+1);
            XCTAssertTrue( (pNode == pNode2) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
        for (i=0; i<10; ++i) {
            pNode = OBJ_NIL;
            eRc = nodeArray_FindA(pArray, strings[i], &pNode);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertFalse( (pNode == OBJ_NIL) );
        }
        
        pNode = OBJ_NIL;
        eRc = nodeArray_FindA(pArray, "xyzzy", &pNode);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (pNode == OBJ_NIL) );
        
        obj_Release(pArray);
        pArray = OBJ_NIL;
    }
    
}



- (void)testAdd02
{
    NODEARRAY_DATA  *pArray;
    NODE_DATA       *pNode;
    NODE_DATA       *pNode2;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    uint32_t        idx;
    
    pArray = nodeArray_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pArray) );
    pArray = nodeArray_Init(pArray);
    XCTAssertFalse( (OBJ_NIL == pArray) );
    if (pArray) {
        
        for (i=0; i<10; ++i) {
            pNode = node_NewWithUTF8Con(strings[i], OBJ_NIL);
            eRc = nodeArray_AppendNode(pArray, pNode, &idx);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            cnt = nodeArray_getSize(pArray);
            XCTAssertTrue( (idx == (i+1)) );
            XCTAssertTrue( (cnt == (i+1)) );
            pNode2 = nodeArray_Get(pArray, i+1);
            XCTAssertTrue( (pNode == pNode2) );
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
        
        obj_Release(pArray);
        pArray = OBJ_NIL;
    }
    
}



@end



