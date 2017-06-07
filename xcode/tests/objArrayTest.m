/*
 *	Generated 07/02/2015 11:03:00
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


#include    <objArray_internal.h>
#include    <AStr_internal.h>

static
char	*stringTable[] = {
    "now",
    "xray",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday",
};
static
int             num = 7;



@interface objArrayTests : XCTestCase

@end

@implementation objArrayTests


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
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    ASTR_DATA       *pStr;
   
    pObj = objArray_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = objArray_AppendObj(pObj, pStr, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        eRc = objArray_SortAscending(pObj, (OBJ_COMPARE)&AStr_Compare);
        
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testDeleteFirst
{
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    ASTR_DATA       *pStr;
    
    pObj = objArray_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = objArray_AppendObj(pObj, pStr, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (num == objArray_getSize(pObj)) );
        fprintf( stderr, "size = %d\n", objArray_getSize(pObj) );
        
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        pStr = objArray_DeleteFirst(pObj);
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[0])) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        for (i=0; i<num-1; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i+1])) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testDelete01
{
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    ASTR_DATA       *pStr;
    
    pObj = objArray_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = objArray_AppendObj(pObj, pStr, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (num == objArray_getSize(pObj)) );
        fprintf( stderr, "size = %d\n", objArray_getSize(pObj) );
        
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        pStr = objArray_Delete(pObj, 1);
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[0])) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        for (i=0; i<num-1; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i+1])) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testDelete02
{
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    ASTR_DATA       *pStr;
    
    pObj = objArray_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = objArray_AppendObj(pObj, pStr, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (num == objArray_getSize(pObj)) );
        fprintf( stderr, "size = %d\n", objArray_getSize(pObj) );
        
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        pStr = objArray_Delete(pObj, num);
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[6])) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        for (i=0; i<num-1; ++i) {
            pStr = objArray_Get(pObj, i+1);
            fprintf( stderr, "%d - %s\n", i, AStr_getData(pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testDelete03
{
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        i;
    ASTR_DATA       *pStr;
    
    pObj = objArray_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        for (i=0; i<num; ++i) {
            pStr = AStr_NewA(stringTable[i]);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            if (pStr) {
                eRc = objArray_AppendObj(pObj, pStr, NULL);
                XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        XCTAssertTrue( (num == objArray_getSize(pObj)) );
        fprintf( stderr, "size = %d\n", objArray_getSize(pObj) );
        
        for (i=0; i<num; ++i) {
            pStr = objArray_Get(pObj, i+1);
            XCTAssertFalse( (OBJ_NIL == pStr) );
            XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[i])) );
        }
        
        pStr = objArray_Delete(pObj, 4);
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[4-1])) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pStr = objArray_Get(pObj, 1);
        fprintf( stderr, "%d - %s\n", 1, AStr_getData(pStr) );
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[1-1])) );
        pStr = objArray_Get(pObj, 2);
        fprintf( stderr, "%d - %s\n", 2, AStr_getData(pStr) );
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[2-1])) );
        pStr = objArray_Get(pObj, 3);
        fprintf( stderr, "%d - %s\n", 3, AStr_getData(pStr) );
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[3-1])) );
        pStr = objArray_Get(pObj, 4);
        fprintf( stderr, "%d - %s\n", 4, AStr_getData(pStr) );
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[4])) );
        pStr = objArray_Get(pObj, 5);
        fprintf( stderr, "%d - %s\n", 5, AStr_getData(pStr) );
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[5])) );
        pStr = objArray_Get(pObj, 6);
        fprintf( stderr, "%d - %s\n", 6, AStr_getData(pStr) );
        XCTAssertTrue( (0 == strcmp((char *)AStr_getData(pStr), stringTable[6])) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testInsertObj
{
    OBJARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    //uint32_t        i;
    ASTR_DATA       *pStr1;
    ASTR_DATA       *pStr2;
    
    pObj = objArray_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = objArray_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr1 = AStr_NewA(stringTable[0]);
        XCTAssertFalse( (OBJ_NIL == pStr1) );
        if (pStr1) {
            eRc = objArray_InsertObj(pObj, 0, pStr1);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue((objArray_getSize(pObj) == 1));
            pStr2 = objArray_Get(pObj, 1);
            XCTAssertTrue( (pStr1 == pStr2) );
            obj_Release(pStr1);
            pStr1 = OBJ_NIL;
        }
        
        pStr1 = AStr_NewA(stringTable[1]);
        XCTAssertFalse( (OBJ_NIL == pStr1) );
        if (pStr1) {
            eRc = objArray_InsertObj(pObj, 0, pStr1);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue((objArray_getSize(pObj) == 2));
            pStr2 = objArray_Get(pObj, 1);
            XCTAssertTrue( (pStr1 == pStr2) );
            pStr2 = objArray_Get(pObj, 2);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[0])) );
            obj_Release(pStr1);
            pStr1 = OBJ_NIL;
        }
        
        pStr1 = AStr_NewA(stringTable[2]);
        XCTAssertFalse( (OBJ_NIL == pStr1) );
        if (pStr1) {
            eRc = objArray_InsertObj(pObj, 1, pStr1);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue((objArray_getSize(pObj) == 3));
            pStr2 = objArray_Get(pObj, 1);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[1])) );
            pStr2 = objArray_Get(pObj, 2);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[2])) );
            pStr2 = objArray_Get(pObj, 3);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[0])) );
            obj_Release(pStr1);
            pStr1 = OBJ_NIL;
        }
        
        pStr1 = AStr_NewA(stringTable[3]);
        XCTAssertFalse( (OBJ_NIL == pStr1) );
        if (pStr1) {
            eRc = objArray_InsertObj(pObj, 3, pStr1);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue((objArray_getSize(pObj) == 4));
            pStr2 = objArray_Get(pObj, 1);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[1])) );
            pStr2 = objArray_Get(pObj, 2);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[2])) );
            pStr2 = objArray_Get(pObj, 3);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[0])) );
            pStr2 = objArray_Get(pObj, 4);
            XCTAssertTrue( (ERESULT_SUCCESS == AStr_CompareA(pStr2, stringTable[3])) );
            obj_Release(pStr1);
            pStr1 = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



