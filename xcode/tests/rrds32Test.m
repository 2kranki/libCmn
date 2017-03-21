
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


#include    "cmn_defs.h"           
#include    "rrds32.h"
#include    "dec.h"




@interface rrds32Tests : XCTestCase

@end

@implementation rrds32Tests


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




- (void)testIO_NoBuffers
{
	RRDS32_DATA		*cbp;
    uint32_t        i;
    bool            fRc;
	char			*pPath     = "/tmp/test.rrds";
    char            block[12]  = "            ";
    char            block2[12] = "            ";
    uint32_t        numRcds = 512;
    uint32_t        cBlock;
    char            *pBlock;
    ERESULT         eRc;

    cbp = rrds32_Alloc();
    XCTAssertFalse( (NULL == cbp));
    cbp = rrds32_Init(cbp, 0);
    XCTAssertFalse( (NULL == cbp));

	eRc = rrds32_Create(cbp, pPath, 12, 0);
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (12 == rrds32_getRecordSize(cbp)));
    
    if (!ERESULT_FAILED(eRc)) {
        for (i=0; i<numRcds; ++i) {
            cBlock = 12;
            pBlock = block;
            dec_putInt32A( i, &cBlock, &pBlock );
            eRc = rrds32_BlockWrite(cbp, i+1, (uint8_t *)block);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            eRc = rrds32_BlockRead(cbp, i+1, (uint8_t *)block2);
            XCTAssertFalse( (ERESULT_FAILED(eRc)) );
            if (0 == memcmp(block, block2, 12) )
                ;
            else {
                XCTFail(@"rrds_BlockWrite()/rrds_BlockRead() did not compare well!");
            }
        }
        
        eRc = rrds32_Close( cbp );
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
    }
    
	eRc = rrds32_Open( cbp, pPath );
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );
    XCTAssertTrue( (12 == rrds32_getRecordSize(cbp)) );
    XCTAssertTrue( ('\0' == rrds32_getFillChar(cbp)) );
    
    for (i=0; i<numRcds; ++i) {
        cBlock = 12;
        pBlock = block;
        dec_putInt32A( i, &cBlock, &pBlock );
        //fRc = rrds_BlockWrite(cbp, i+1, block);
        //STAssertTrue( (fRc), @"rrds_BlockWrite failed!" );
        eRc = rrds32_BlockRead(cbp, i+1, (uint8_t *)block2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        if (0 == memcmp(block, block2, 12) )
            ;
        else {
            XCTFail(@"rrds32_BlockWrite()/rrds_BlockRead() did not compare well!");
        }
    }
    
	eRc = rrds32_Destroy( cbp );
    XCTAssertFalse( (ERESULT_FAILED(eRc)) );

    obj_Release(cbp);
    cbp = OBJ_NIL;
}





@end



