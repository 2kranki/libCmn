/*
 *	Generated 06/22/2015 17:14:45
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


#include    "dir_internal.h"
#include    "sys/stat.h"
#include    "sys/types.h"




static
char            *pDir = NULL;
static
bool            scanner( void *pData, DIRENTRY_DATA *pEntry)
{
    PATH_DATA       *pPath;
    char            *pStr;
    struct stat     statbuf;
    
    pPath = path_Copy(dirEntry_getDir(pEntry));
    path_AppendFileName(pPath, dirEntry_getName(pEntry));
    pStr = AStr_CStringA((ASTR_DATA *)pPath,NULL);
    
    fprintf(    stderr,
                "name: %s  type: %d\n",
                pStr,
                dirEntry_getType(pEntry)
    );
    
    if (-1 == stat(pStr,&statbuf))
        fprintf(stderr, "\tCould not stat: %s\n", pStr);
    else {
        //fprintf(stderr, "\tname: (%d)%s\n", statbuf->d_namlen, pDirent->d_name);
    }
    
    mem_Free(pStr);
    pStr = NULL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    return true;
}




@interface dirTests : XCTestCase

@end

@implementation dirTests


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
    DIR_DATA	*pObj = OBJ_NIL;
   
    pObj = dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc  DIR_DATA" );
    pObj = dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not init  DIR_DATA" );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testScan
{
    DIR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath;
    
    pDir = getenv("HOME");
    pObj = dir_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = dir_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pPath = path_NewA(pDir);
        eRc = dir_ScanDir(pObj, pPath, &scanner, NULL);
        obj_Release(pPath);
        pPath = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



