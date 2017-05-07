// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 02/07/2016 15:50:27
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


#include    "name_internal.h"
#include    "mem.h"


extern
void        memTesterC(
);


void        memTesterM(
)
{
    NAME_DATA	*pName1 = OBJ_NIL;
    const
    char        *pStrA;

#ifndef         MEMOSX_H
    mem_DebugSet(true);
    mem_DebugSet(true);
#endif
    pStrA = mem_Malloc(256);
    mem_Free((void *)pStrA);
    pStrA = mem_MallocObject(256);
    mem_Free((void *)pStrA);
   fprintf(stderr, "name_NewUTF8()\n");
    pName1 = name_NewUTF8( "abc" );
    obj_Release(pName1);
    pName1 = OBJ_NIL;
    mem_StrDup("abc");
#ifndef         MEMOSX_H
    mem_DebugCheck( "abc", 1);
    mem_DebugSet(true);
#endif
    mem_Calloc(1, 256);
    mem_MallocObject(256);
    fprintf(stderr, "name_NewUTF8()\n");
    pName1 = name_NewUTF8( "abc" );
    mem_Free(pName1);
}


@interface nameTests : XCTestCase

@end

@implementation nameTests


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
    NAME_DATA	*pObj = OBJ_NIL;
   
    pObj = name_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = name_InitInt( pObj, 0 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testUTF8
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;


#ifndef         MEMOSX_H
    //memTesterC();
    memTesterM();
    mem_DebugSet(true);
    mem_DebugSet(true);
    mem_Malloc(256);
    mem_MallocObject(256);
    fprintf(stderr, "name_NewUTF8()\n");
    pName1 = name_NewUTF8( "abc" );
    mem_StrDup("abc");
    mem_DebugCheck( "abc", 1);
    mem_DebugSet(true);
    mem_Calloc(1, 256);
    mem_MallocObject(256);
    fprintf(stderr, "name_NewUTF8()\n");
    pName1 = name_NewUTF8( "abc" );
    mem_Free(pName1);
#endif

    
    pName1 = name_NewUTF8( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {

        pAStr1 = name_getStrA(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;

        pWStr1 = name_getStrW(pName1);
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "abc")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;

        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
}



- (void)testUTF8Con
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    const
    char        *pChrs = NULL;
    
    
#ifndef         MEMOSX_H
    //memTesterC();
    memTesterM();
    mem_DebugSet(true);
    mem_DebugSet(true);
    mem_Malloc(256);
    mem_MallocObject(256);
    fprintf(stderr, "name_NewUTF8()\n");
    pName1 = name_NewUTF8( "abc" );
    mem_StrDup("abc");
    mem_DebugCheck( "abc", 1);
    mem_DebugSet(true);
    mem_Calloc(1, 256);
    mem_MallocObject(256);
    fprintf(stderr, "name_NewUTF8()\n");
    pName1 = name_NewUTF8( "abc" );
    mem_Free(pName1);
#endif
    
    
    pName1 = name_NewUTF8Con( "abc" );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStrA(pName1);
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "abc")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        pWStr1 = name_getStrW(pName1);
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "abc")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        pChrs = name_getUTF8(pName1);
        XCTAssertTrue( (0 == str_Compare("abc", pChrs)) );
        mem_Free((void *)pChrs);
        pChrs = NULL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
}



- (void)testInt
{
    NAME_DATA	*pName1 = OBJ_NIL;
    WSTR_DATA   *pWStr1 = OBJ_NIL;
    ASTR_DATA   *pAStr1 = OBJ_NIL;
    
    
    pName1 = name_NewInt( 123456 );
    XCTAssertFalse( (OBJ_NIL == pName1) );
    if (pName1) {
        
        pAStr1 = name_getStrA(pName1);
        fprintf(stderr, "strA = %s\n", AStr_getData(pAStr1));
        XCTAssertTrue( (0 == AStr_CompareA(pAStr1, "00000000000000123456")) );
        obj_Release(pAStr1);
        pAStr1 = OBJ_NIL;
        
        pWStr1 = name_getStrW(pName1);
        fprintf(stderr, "strW = %ls\n", WStr_getData(pWStr1));
        XCTAssertTrue( (0 == WStr_CompareA(pWStr1, "00000000000000123456")) );
        obj_Release(pWStr1);
        pWStr1 = OBJ_NIL;
        
        obj_Release(pName1);
        pName1 = OBJ_NIL;
    }
    
}



@end



