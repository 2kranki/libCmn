

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


#include    "cb_internal.h"           // We cheat!


#define NUM_STR     20

/* String Variables */
// Length == 10 (includes ending NUL)
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
    "String 10",
    "String 11",
    "String 12",
    "String 13",
    "String 14",
    "String 15",
    "String 16",
    "String 17",
    "String 18",
    "String 19",
    "String 20"
};


typedef struct buffer_entry_s {
    const
    char            *pStr;
} BUFFER_ENTRY;


// Output Queue is written by the separate task.
static
BUFFER_ENTRY    outputQueue[NUM_STR * 2] = {0};
static
int             outputQueueEnd = -1;



static
void            addOutput (const char *pStr)
{
    
    ++outputQueueEnd;
    outputQueue[outputQueueEnd].pStr = pStr;
    printf("addOutput()  %3d - %s\n", outputQueueEnd, outputQueue[outputQueueEnd].pStr);
    
}



static
CB_DATA     *pCB = OBJ_NIL;







static
void *          getRoutine(
    void            *pVoid
)
{
    const
    char            *pStr = NULL;
    
    while (1) {
        pStr = NULL;
        cb_Get(pCB, &pStr, -1);
        if (pStr) {
            addOutput(pStr);
        }
        usleep(500000);
    }
    
    return NULL;
}



@interface cbTests : XCTestCase

@end

@implementation cbTests


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
	CB_DATA			*cbp;

	cbp = cb_Alloc(10, 8);
    XCTAssertFalse( (NULL == cbp) );
	cbp = cb_Init( cbp );
    XCTAssertFalse( (NULL == cbp) );
    if (cbp) {
        obj_Release(cbp);
        cbp = NULL;
    }

}


- (void)testCounterOverflow
{
	CB_DATA			*cbp;
    uint16_t        i;
    uint16_t        j;
    bool            fRc;
    char            msg[10];
    
	cbp = cb_Alloc(10, 10);
    XCTAssertFalse( (NULL == cbp) );
	cbp = cb_Init( cbp );
    XCTAssertFalse( (NULL == cbp) );
    
    // Empty Queue - positive to negative overflow
    cbp->numRead = 32766;
    cbp->numWritten = 32766;
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );

    for (i=0; i<8; ++i) {
        fRc = cb_Put(cbp, StrArray[i]);
        XCTAssertTrue( (fRc) );
        fRc = cb_isEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = cb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = cb_Get(cbp, &msg, -1);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (0 == strcmp(msg,StrArray[i])) );
        
    }
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
    // Empty Queue - negative to positive overflow
    cbp->numRead = -32766;
    cbp->numWritten = -32766;
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
    for (i=0; i<8; ++i) {
        fRc = cb_Put(cbp, StrArray[i]);
        XCTAssertTrue( (fRc) );
        fRc = cb_isEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = cb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = cb_Get(cbp, &msg, -1);
        XCTAssertTrue( (fRc) );
        //STAssertTrue( (aVal == i), @"cb8_Get value failed" );
        
    }
    
    fRc = cb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
	obj_Release( cbp );
    cbp = NULL;
    
}


@end



