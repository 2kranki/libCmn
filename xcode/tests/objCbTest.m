

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
#include "objCb_internal.h"


// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      STAssert(expression, failure_description, ...)
//      STFail(failure_description, ...)
//      STAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      STAssertEquals(value_1, value_2, failure_description, ...)
//      STAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      STAssertNil(expression, failure_description, ...)
//      STAssertNotNil(expression, failure_description, ...)
//      STAssertTrue(expression, failure_description, ...)
//      STAssertFalse(expression, failure_description, ...)
//      STAssertThrows(expression, failure_description, ...)
//      STAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      STAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      STAssertNoThrow(expression, failure_description, ...)
//      STAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      STAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)




#define NUM_STR     10

/* Other variables */
static
char        *StrArray[NUM_STR] = {
//   123456789
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





@interface objCbTests : XCTestCase

@end



@implementation objCbTests


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
	OBJCB_DATA			*cbp;

	cbp = objCb_Alloc(8);
    XCTAssertFalse( (NULL == cbp), @"Could not alloc" );
	cbp = objCb_Init( cbp );
    XCTAssertFalse( (NULL == cbp), @"Could not init" );
    if (cbp) {
        obj_Release(cbp);
        cbp = NULL;
    }

}


- (void)testCounterOverflow
{
	OBJCB_DATA			*cbp;
    uint16_t            i;
    uint16_t            j;
    bool                fRc;
    //char                msg[10];
    NAME_DATA           *pName;
    
	cbp = objCb_Alloc(8);
    XCTAssertFalse( (NULL == cbp), @"Could not alloc" );
	cbp = objCb_Init( cbp );
    XCTAssertFalse( (NULL == cbp), @"Could not init" );

    // Empty Queue - positive to negative overflow
    cbp->numRead = 32766;
    cbp->numWritten = 32766;
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc), @"cb8_IsEmpty failed" );

    for (i=0; i<8; ++i) {
        pName =  name_NewUTF8(StrArray[i]);
        fRc = objCb_Put(cbp,pName);
        obj_Release(pName);
        XCTAssertTrue( (fRc), @"objCb_Put failed" );
        fRc = objCb_isEmpty(cbp);
        XCTAssertFalse( (fRc), @"objCb_IsEmpty failed" );
        j = objCb_Count(cbp);
        XCTAssertTrue( (j == (i+1)), @"objCb_Count failed j=%d, i=%d", j, i );
    }
    
    for (i=0; i<8; ++i) {
        fRc = objCb_Get(cbp, (void *)&pName);
        XCTAssertTrue( (fRc), @"objCb_Get failed" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == name_CompareA(pName,StrArray[i])) );
        obj_Release(pName);
    }
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc), @"objCb_IsEmpty failed" );
    
    // Empty Queue - negative to positive overflow
    cbp->numRead = -32766;
    cbp->numWritten = -32766;
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc), @"objCb_IsEmpty failed" );
    
    for (i=0; i<8; ++i) {
        pName =  name_NewUTF8(StrArray[i]);
        fRc = objCb_Put(cbp, pName);
        obj_Release(pName);
        XCTAssertTrue( (fRc), @"objCb_Put failed" );
        fRc = objCb_isEmpty(cbp);
        XCTAssertFalse( (fRc), @"objCb_IsEmpty failed" );
        j = objCb_Count(cbp);
        XCTAssertTrue( (j == (i+1)), @"objCb_Count failed j=%d, i=%d", j, i );
    }
    
    for (i=0; i<8; ++i) {
        fRc = objCb_Get(cbp, (void *)&pName);
        XCTAssertTrue( (fRc), @"objCb_Get failed" );
        //STAssertTrue( (aVal == i), @"cb8_Get value failed" );
        obj_Release(pName);
    }
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc), @"objCb_IsEmpty failed" );
    
	obj_Release( cbp );
    cbp = NULL;
    
}


@end



