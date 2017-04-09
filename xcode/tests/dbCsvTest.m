/*
 *	Generated 09/25/2015 21:26:41
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


#include    "dbCsv_internal.h"
#include    "szTbl.h"


static
const
char        *pTestInput01 = "a,10,\"def\"\n";


static
const
char        *pTestInput02 =
"#x,y,a\n"
"a,b,c,\"def\"\n"
"d,e,f,55\n"
"h,i,j,77\n";






@interface dbCsvTests : XCTestCase

@end

@implementation dbCsvTests


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




- (void)testInput01
{
    DBCSV_DATA      *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    uint32_t        j;
    uint32_t        jMax;
    OBJARRAY_DATA   *pRecord;
    OBJARRAY_DATA   *pRecords;
    ASTR_DATA       *pField;

    
    pStr = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pStr), @"" );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath), @"" );
    
    pObj = dbCsv_NewAStr( pStr, pPath, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        pRecords = dbCsv_ParseFile(pObj);
        XCTAssertFalse( (OBJ_NIL == pRecords), @"" );
        if (pRecords) {
            iMax = objArray_getSize(pRecords);
            for (i=1; i<=iMax; ++i) {
                pRecord = objArray_Get(pRecords,i);
                XCTAssertFalse( (OBJ_NIL == pRecord), @"" );
                if (pRecord) {
                    jMax = objArray_getSize(pRecord);
                    for (j=1; j<=jMax; ++j) {
                        pField = objArray_Get(pRecord,j);
                        XCTAssertFalse( (OBJ_NIL == pField), @"" );
                        if (pField) {
                            fprintf(
                                    stderr,
                                    "line %d, field %d, %s\n",
                                    i,
                                    j,
                                    AStr_getData(pField)
                            );
                        }
                        switch (i) {
                            case 1:
                                switch (j) {
                                    case 1:
                                        XCTAssertTrue( (0 == strcmp("a",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("10",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("def",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    default:
                                        break;
                                }
                                break;
                                
                            default:
                                break;
                        }
                    }
                    
                }
            }
            
        }
        
        obj_Release(pRecords);
        pRecords = OBJ_NIL;
    }
    obj_Release(pObj);
    pObj = OBJ_NIL;
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    obj_Release(pStr);
    pStr = OBJ_NIL;
    szTbl_SharedReset();
}



- (void)testInput02
{
    DBCSV_DATA      *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    uint32_t        i;
    uint32_t        iMax;
    uint32_t        j;
    uint32_t        jMax;
    OBJARRAY_DATA   *pRecord;
    OBJARRAY_DATA   *pRecords;
    ASTR_DATA       *pField;
    
    
    pStr = AStr_NewA(pTestInput02);
    XCTAssertFalse( (OBJ_NIL == pStr), @"" );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath), @"" );
    
    pObj = dbCsv_NewAStr( pStr, pPath, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        pRecords = dbCsv_ParseFile(pObj);
        XCTAssertFalse( (OBJ_NIL == pRecords), @"" );
        if (pRecords) {
            iMax = objArray_getSize(pRecords);
            for (i=1; i<=iMax; ++i) {
                pRecord = objArray_Get(pRecords,i);
                XCTAssertFalse( (OBJ_NIL == pRecord), @"" );
                if (pRecord) {
                    jMax = objArray_getSize(pRecord);
                    for (j=1; j<=jMax; ++j) {
                        pField = objArray_Get(pRecord,j);
                        XCTAssertFalse( (OBJ_NIL == pField), @"" );
                        if (pField) {
                            fprintf(
                                    stderr,
                                    "line %d, field %d, %s\n",
                                    i,
                                    j,
                                    AStr_getData(pField)
                                    );
                        }
                        switch (i) {
                            case 1:
                                switch (j) {
                                    case 1:
                                        XCTAssertTrue( (0 == strcmp("a",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("b",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("c",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 4:
                                        XCTAssertTrue( (0 == strcmp("def",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    default:
                                        break;
                                }
                                break;
                                
                            case 2:
                                switch (j) {
                                    case 1:
                                        XCTAssertTrue( (0 == strcmp("d",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("e",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("f",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 4:
                                        XCTAssertTrue( (0 == strcmp("55",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    default:
                                        break;
                                }
                                break;
                                
                            case 3:
                                switch (j) {
                                    case 1:
                                        XCTAssertTrue( (0 == strcmp("h",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("i",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("j",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    case 4:
                                        XCTAssertTrue( (0 == strcmp("77",AStr_getData(pField))), @"" );
                                        break;
                                        
                                    default:
                                        break;
                                }
                                break;
                                
                            default:
                                break;
                        }
                    }
                    
                }
            }
            
        }
        
        obj_Release(pRecords);
        pRecords = OBJ_NIL;
    }
    obj_Release(pObj);
    pObj = OBJ_NIL;
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    obj_Release(pStr);
    pStr = OBJ_NIL;
    szTbl_SharedReset();
}



@end



