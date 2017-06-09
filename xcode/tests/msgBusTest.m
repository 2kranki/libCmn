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



#define NUM_OBJ      4
#define NUM_STR     10

/* Other variables */
static
char        *StrObj[NUM_OBJ] = {
    //   1234567890
    "Obj1",
    "Obj2",
    "Obj3",
    "Obj4"
};

static
char        *StrArray[NUM_STR] = {
    //   1234567890
    "String  1",
    "String  2",
    "String  3",
    "String  4",
    "String  5",
    "String  6",
    "String  7",
    "String  8",
    "String  9",
    "String 10"
};




void        printMsg(
    void        *pObj,
    void        *pMsg
)
{
    fprintf(stderr, "%s  %s\n", pObj, pMsg);
}




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
    ERESULT     eRc;
    int         i;
    
    pObj = msgBus_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = msgBus_Init( pObj, 10, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    obj_TraceSet(pObj, true);
    if (pObj) {
        
        for (i=0; i<NUM_OBJ; ++i) {
            eRc = msgBus_Register(pObj, printMsg, StrObj[i]);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        for (i=0; i<NUM_STR; ++i) {
            eRc = msgBus_Broadcast(pObj, (void *)0, (uint8_t *)StrArray[0]);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



