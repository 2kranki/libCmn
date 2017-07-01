/*
 *	Generated 06/30/2017 09:01:13
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


#include    <enum_internal.h>

static
char	*stringTable[] = {
    "now",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday"
};
static
int             cStringTable = 6;



@interface enumTests : XCTestCase

@end

@implementation enumTests


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
    ENUM_DATA	*pObj = OBJ_NIL;
   
    pObj = enum_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = enum_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        XCTAssertTrue( (0 == pObj->max) );
        XCTAssertTrue( (0 == pObj->size) );
        XCTAssertTrue( (0 == pObj->current) );
        XCTAssertTrue( (NULL == pObj->ppArray) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)test01
{
    ENUM_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    int         i;
    uint32_t    idx = 0;
    const
    char        *pStr = NULL;
    
    pObj = enum_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = enum_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        XCTAssertTrue( (0 == pObj->max) );
        XCTAssertTrue( (0 == pObj->size) );
        XCTAssertTrue( (0 == pObj->current) );
        XCTAssertTrue( (NULL == pObj->ppArray) );
        
        eRc = enum_Append(pObj, stringTable[0], &idx);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == pObj->max) );
        XCTAssertTrue( (1 == pObj->size) );
        XCTAssertTrue( (0 == pObj->current) );
        XCTAssertFalse( (NULL == pObj->ppArray) );
        
        for (i=1; i<cStringTable; ++i) {
            eRc = enum_Append(pObj, stringTable[i], &idx);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            //XCTAssertTrue( (2 == pObj->max) );
            XCTAssertTrue( (idx == pObj->size) );
            XCTAssertTrue( (0 == pObj->current) );
            XCTAssertFalse( (NULL == pObj->ppArray) );
        }
        XCTAssertTrue( (cStringTable == pObj->size) );
        
        eRc = enum_Next(pObj, 1, (void **)&pStr, &idx);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (idx == 1) );
        XCTAssertTrue( (0 == strcmp(pStr, stringTable[0])) );
        XCTAssertTrue( (1 == pObj->current) );
        
        for (i=1; i<cStringTable; ++i) {
            eRc = enum_Next(pObj, 1, (void **)&pStr, &idx);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            XCTAssertTrue( (idx == 1) );
            XCTAssertTrue( (0 == strcmp(pStr, stringTable[i])) );
            XCTAssertTrue( (i+1 == pObj->current) );
            XCTAssertFalse( (NULL == pObj->ppArray) );
        }
        
        eRc = enum_Next(pObj, 1, (void **)&pStr, &idx);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (idx == 0) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



