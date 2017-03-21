/*
 *	Generated 02/23/2016 11:32:06
 */


/*
 * COPYRIGHT  - (C) Copyright 2015  BY Robert White Services, LLC
 *             This computer software is the proprietary information
 *             of Robert White Services, LLC and is subject to a
 *             License Agreement between the user hereof and Robert
 *             White Services, LLC. All concepts, programs, tech-
 *             niques,  object code  and  source code are the Trade
 *             Secrets of Robert White Services, LLC.
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


#include    <devBase_internal.h>



@interface devBaseTests : XCTestCase

@end

@implementation devBaseTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
    
    mem_Dump( );
}



- (void)testOpenClose
{
    DEVBASE_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            buffer[128];
    uint32_t        retAmt;
   
    pObj = devBase_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = devBase_Init( pObj, NULL );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        eRc = devBase_Start(pObj,0);
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        eRc = devBase_Getc(pObj);
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        eRc = devBase_Ioctl(pObj, 0, 0, 0);
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        eRc = devBase_Putc(pObj,'a');
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        retAmt = 100;
        eRc = devBase_Read(pObj, 20, &buffer, &retAmt);
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        XCTAssertTrue( (0 == retAmt) );
        retAmt = 100;
        eRc = devBase_Write(pObj, 20, &buffer, &retAmt);
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        XCTAssertTrue( (0 == retAmt) );
        devBase_Stop(pObj,0);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



