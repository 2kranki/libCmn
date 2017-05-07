/*
 *	Generated 06/11/2015 16:44:27
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


#include    "szHash_internal.h"
#include    "str.h"

static
char        *strings[] = {
    "bob",
    "bobby",
    "iryana",
    "dashsa",
    "dasha",
    "name",
    "way",
    "bigger",
    "Now",
    "is",
    "the",
    "time",
    "for",
    "all",
    "good",
    "men",
    "to",
    "come",
    "aid",
    "of",
    "their",
    "country",
    "We",
    "need",
    "another",
    "item",
    "in",
    "here",
    "Are",
    "you",
    "alright",
    "with",
    "this",
    (char *)NULL
};





@interface szHashTests : XCTestCase

@end

@implementation szHashTests


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
    SZHASH_DATA	*pObj = OBJ_NIL;
   
    pObj = szHash_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc  SZHASH_DATA" );
    pObj = szHash_Init( pObj, 5 );
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not init  SZHASH_DATA" );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testAddFindDelete_1
{
    SZHASH_DATA     *pHash;
    uint32_t        i;
    uint32_t        cnt;
    ERESULT         eRc;
    void            *pVoid;
    
    pHash = szHash_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pHash), @"Could not alloc  SZHASH_DATA" );
    pHash = szHash_Init( pHash, 5 );
    XCTAssertFalse( (OBJ_NIL == pHash), @"Could not init  SZHASH_DATA" );
    if (pHash) {
        
        szHash_setComputeHash( pHash, str_HashA, str_HashW );
        szHash_setCompare( pHash, utf8_StrCmp, utf8_StrCmpAW );

        for (i=0; i<10; ++i) {
            eRc = szHash_Add(pHash, strings[i], strings[i]);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)), @"Could not Add()" );
            cnt = szHash_getSize(pHash);
            XCTAssertTrue( (cnt == (i+1)), @"Could not Count()" );
        }
        
        for (i=0; i<10; ++i) {
            pVoid = szHash_Find(pHash, strings[i]);
            XCTAssertTrue( (pVoid == strings[i]), @"Could not Find()" );
        }
        
        pVoid = szHash_Find(pHash, strings[3]);
        XCTAssertTrue( (pVoid == strings[3]), @"Could not Find()" );
        pVoid = szHash_Find(pHash, strings[9]);
        XCTAssertTrue( (pVoid == strings[9]), @"Could not Find()" );
        pVoid = szHash_Find(pHash, strings[6]);
        XCTAssertTrue( (pVoid == strings[6]), @"Could not Find()" );
        
        eRc = szHash_Delete(pHash, strings[5]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)), @"Could not Delete()" );
        cnt = szHash_getSize(pHash);
        XCTAssertTrue( (cnt == 9), @"Could not Count()" );
        pVoid = szHash_Find(pHash, strings[5]);
        XCTAssertTrue( (pVoid == NULL), @"" );
        
        eRc = szHash_Delete(pHash, strings[8]);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)), @"Could not Delete()" );
        cnt = szHash_getSize(pHash);
        XCTAssertTrue( (cnt == 8), @"Could not Count()" );
        pVoid = szHash_Find(pHash, strings[8]);
        XCTAssertTrue( (pVoid == NULL), @"" );
        
        obj_Release(pHash);
        pHash = OBJ_NIL;
    }
    
}



@end



