/*
 *	Generated 09/14/2016 11:48:53
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


#include    <objList_internal.h>
#include    <name.h>
#include    <szTbl.h>



@interface objListTests : XCTestCase

@end

@implementation objListTests


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
    OBJLIST_DATA	*pObj = OBJ_NIL;
   
    pObj = objList_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objList_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testBasicList01
{
    OBJLIST_DATA	*pObj = OBJ_NIL;
    NAME_DATA       *pNameA = OBJ_NIL;
    NAME_DATA       *pNameB = OBJ_NIL;
    NAME_DATA       *pNameC = OBJ_NIL;
    NAME_DATA       *pNameD = OBJ_NIL;
    NAME_DATA       *pNameE = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NAME_DATA       *pEntry;
    
    pObj = objList_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objList_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pNameA = name_NewUTF8("A");
        XCTAssertFalse( (OBJ_NIL == pNameA) );
        pNameB = name_NewUTF8("B");
        XCTAssertFalse( (OBJ_NIL == pNameB) );
        pNameC = name_NewUTF8("C");
        XCTAssertFalse( (OBJ_NIL == pNameC) );
        pNameD = name_NewUTF8("D");
        XCTAssertFalse( (OBJ_NIL == pNameD) );
        pNameE = name_NewUTF8("E");
        XCTAssertFalse( (OBJ_NIL == pNameE) );
        
        eRc = objList_Add2Head(pObj, pNameA);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = objList_Add2Head(pObj, pNameB);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        eRc = objList_Add2Head(pObj, pNameC);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        
        // Verify that the linkage fields are correct.
        pEntry = objList_Head(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        pEntry = objList_Index(pObj, 1);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameC) );
        pEntry = objList_Index(pObj, 2);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameB) );
        pEntry = objList_Index(pObj, 3);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        pEntry = objList_Tail(pObj);
        XCTAssertFalse( (pEntry == OBJ_NIL) );
        XCTAssertTrue( (pEntry == pNameA) );
        
        pStr = objList_ToDebugString(pObj, 0);
        fprintf(stderr, "Debug = %s\n\n\n",AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pNameE);
        pNameE = OBJ_NIL;
        obj_Release(pNameD);
        pNameD = OBJ_NIL;
        obj_Release(pNameC);
        pNameC = OBJ_NIL;
        obj_Release(pNameB);
        pNameB = OBJ_NIL;
        obj_Release(pNameA);
        pNameA = OBJ_NIL;
        
        XCTAssertTrue( (obj_IsFlag(pObj, OBJ_FLAG_ALLOC)) );
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
    
}



@end



