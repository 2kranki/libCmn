/*
 *	Generated 09/19/2015 00:10:38
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
#import "ternary_internal.h"



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




@interface ternaryTests : XCTestCase

@end

@implementation ternaryTests


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
    TERNARY_DATA	*pObj = OBJ_NIL;
   
    pObj = ternary_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = ternary_Init( pObj, 16 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testAddFind
{
    TERNARY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    void            *pResult;
    
    pObj = ternary_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = ternary_Init( pObj, 16 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_TraceSet(pObj, true);
    if (pObj) {
        
        fprintf(stderr, "\n\n** add sea\n");
        eRc = ternary_Add(pObj, L"sea", "sea");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add sells\n");
        eRc = ternary_Add(pObj, L"sells", "sells");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add she\n");
        eRc = ternary_Add(pObj, L"she", "she");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add shells\n");
        eRc = ternary_Add(pObj, L"shells", "shells");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add shore\n");
        eRc = ternary_Add(pObj, L"shore", "shore");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shore");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add by\n");
        eRc = ternary_Add(pObj, L"by", "by");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shore");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"by");
        XCTAssertFalse( (NULL == pResult) );
        
        fprintf(stderr, "\n\n** add the\n");
        eRc = ternary_Add(pObj, L"the", "the");
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = ternaryTree_VisitPreorder(pObj, NULL, NULL);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        pResult = ternary_Find(pObj, L"sea");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"sells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"she");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shells");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"shore");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"by");
        XCTAssertFalse( (NULL == pResult) );
        pResult = ternary_Find(pObj, L"the");
        XCTAssertFalse( (NULL == pResult) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



