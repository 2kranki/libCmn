/*
 *	Generated 05/31/2017 20:00:00
 */


#import <XCTest/XCTest.h>



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


#include    <msgBus_internal.h>



@interface msgBusTests : XCTestCase

@end

@implementation msgBusTests


- (void)setUp
{
    [super setUp];
    
    mem_Init( );
    
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    mem_Dump( );
    mem_Release( );

    [super tearDown];
}




- (void)testOpenClose
{
    MSGBUS_DATA	*pObj = OBJ_NIL;
   
    pObj = msgBus_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = msgBus_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end


