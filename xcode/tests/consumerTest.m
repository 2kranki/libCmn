/*
 *	Generated 06/29/2016 10:31:45
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




#include    "consumer_internal.h"



#define NUM_STR     10

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



static
void        printMsg(
    void        *pObj,
    void        *pMsg
)
{
    fprintf(stderr, "  Recieved - %s  %s\n", pObj, pMsg);
}




@interface consumerTests : XCTestCase

@end

@implementation consumerTests


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
    CONSUMER_DATA	*pObj = OBJ_NIL;
    int             i;
   
    pObj = consumer_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = consumer_Init( pObj, 10, 4, (void *)printMsg, pObj);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        printf("Sending Messages...\n");
        for (i=0; i<NUM_STR; ++i) {
            printf("  Sending %s...\n", StrArray[i]);
            consumer_SendMessage(pObj, StrArray[i]);
        }
        
        psxThread_Wait(2000);
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



