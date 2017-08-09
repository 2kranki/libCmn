/*
 *	Generated 07/25/2017 10:42:33
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


#include    <crc_internal.h>
#include    <trace.h>




@interface crcTests : XCTestCase

@end

@implementation crcTests


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

    trace_SharedReset();
    mem_Dump( );
    mem_Release( );

    [super tearDown];
}




- (void)testCrc1601
{
    CRC_DATA	*pObj = OBJ_NIL;
    uint32_t    crc;
   
    pObj = crc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_16);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        crc = crc_AccumBlock(pObj, 9, (uint8_t *)"123456789");
        fprintf(stderr, "CRC_TYPE_16 crc=%08X check=%08X\n", crc, crc_getCheck(pObj));
        XCTAssertTrue((crc == crc_getCheck(pObj)));
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testCrc1602
{
    CRC_DATA	*pObj = OBJ_NIL;
    uint32_t    crc;
    
    pObj = crc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_CCITT_16);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        crc = crc_AccumBlock(pObj, 9, (uint8_t *)"123456789");
        fprintf(stderr, "CRC_TYPE_16 crc=%08X check=%08X\n", crc, crc_getCheck(pObj));
        XCTAssertTrue((crc == crc_getCheck(pObj)));
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCrc3201
{
    CRC_DATA	*pObj = OBJ_NIL;
    uint32_t    crc;
    
    pObj = crc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_32);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        crc = crc_AccumBlock(pObj, 9, (uint8_t *)"123456789");
        fprintf(stderr, "CRC_TYPE_32 crc=%08X check=%08X\n", crc, crc_getCheck(pObj));
        XCTAssertTrue((crc == crc_getCheck(pObj)));
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCrc3202
{
    CRC_DATA	*pObj = OBJ_NIL;
    uint32_t    crc;
    
    pObj = crc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_IEEE_32);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        crc = crc_AccumBlock(pObj, 9, (uint8_t *)"123456789");
        fprintf(stderr, "CRC_TYPE_IEEE_32 crc=%08X check=%08X\n", crc, crc_getCheck(pObj));
        XCTAssertTrue((crc == crc_getCheck(pObj)));
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCrc3203
{
    CRC_DATA	*pObj = OBJ_NIL;
    uint32_t    crc;
    
    pObj = crc_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = crc_Init(pObj, CRC_TYPE_MPEG2_32);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        crc = crc_AccumBlock(pObj, 9, (uint8_t *)"123456789");
        fprintf(stderr, "CRC_TYPE_MPEG2_32 crc=%08X check=%08X\n", crc, crc_getCheck(pObj));
        XCTAssertTrue((crc == crc_getCheck(pObj)));
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



