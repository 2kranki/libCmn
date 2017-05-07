/*
 *	Generated 02/26/2016 00:57:45
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


#define HISTBASE_GENERATE    1
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

#import <histBase_internal.h>



@interface histBaseTests : XCTestCase

@end

@implementation histBaseTests


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



- (void)testOpenCloseAdd
{
    HISTBASE_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        value = 256;
   
    pObj = histBase_Alloc(2);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = histBase_Init( pObj, OBJ_NIL );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = histBase_Start(pObj, NULL);
        XCTAssertTrue((ERESULT_SUCCESSFUL_COMPLETION == eRc));
        
        eRc = histBase_Ioctl(pObj,HIST_IOCTL_OP_SIZE,&value,NULL);
        XCTAssertTrue((ERESULT_SUCCESSFUL_COMPLETION == eRc));
        XCTAssertTrue(((2 * sizeof(HIST_ENTRY)) == value));
        //eRc = HIST_IOCTL_SIZE(pObj,(&value));
        XCTAssertTrue((ERESULT_SUCCESSFUL_COMPLETION == eRc));
        XCTAssertTrue(((2 * sizeof(HIST_ENTRY)) == value));
        //eRc = HIST_IOCTL_ADD(pObj, 1, 2, 3, 4, 5);
        eRc = histBase_Ioctl(pObj,((1 << 24) | (2 << 8) | HIST_IOCTL_OP_ADD),(void *)3,(void *)4);
        XCTAssertTrue((ERESULT_SUCCESSFUL_COMPLETION == eRc));

        eRc = histBase_Stop(pObj, NULL);
        XCTAssertTrue((ERESULT_SUCCESSFUL_COMPLETION == eRc));
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



