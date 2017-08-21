/*
 *	Generated 07/02/2015 10:57:54
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


#include    "ptrArray_internal.h"

static
char	*stringTable[] = {
    "now",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday",
};
static
int             num = 6;


@interface ptrArrayTests : XCTestCase

@end

@implementation ptrArrayTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    mem_Init();
    
    
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
    PTRARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    char            *pStr;
   
    pObj = ptrArray_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = ptrArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            eRc = ptrArray_AppendData(pObj, stringTable[i], NULL);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        }
        
        for (i=0; i<num; ++i) {
            pStr = ptrArray_GetData(pObj, i+1);
            XCTAssertFalse( (NULL == pStr) );
            XCTAssertTrue( (0 == strcmp(pStr, stringTable[i])) );
        }
        
        eRc = ptrArray_Sort(pObj, (PTR_COMPARE)&strcmp);
        
        for (i=0; i<num; ++i) {
            pStr = ptrArray_GetData(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, pStr );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



