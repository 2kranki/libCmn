/*
 *	Generated 06/09/2015 13:02:46
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


#include    "path_internal.h"


@interface pathTests : XCTestCase

@end

@implementation pathTests


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
    PATH_DATA	*pObj = OBJ_NIL;
   
    pObj = path_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = path_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testCharFindNext
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    pObj = path_NewA("file://Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        index = 0;      // Start at the beginning.
        eRc = AStr_CharFindNextW((ASTR_DATA *)pObj, &index, '/');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == index), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testNewFromEnv
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = path_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc  AStr_DATA" );
    if (pObj) {
        
        eRc = path_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath01
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA   *pFileN = OBJ_NIL;
    ASTR_DATA   *pFileE = OBJ_NIL;
    
    pObj = path_NewA("file://Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );

        XCTAssertTrue( (pDrive), @"" );
        XCTAssertTrue( (4 == AStr_getLength(pDrive)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pDrive), "file")), @"" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        XCTAssertTrue( (pPath), @"" );
        XCTAssertTrue( (12 == AStr_getLength((ASTR_DATA *)pPath)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/Users/bob/x")), @"" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }

        XCTAssertTrue( (pFileName), @"" );
        XCTAssertTrue( (7 == AStr_getLength((ASTR_DATA *)pFileName)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pFileName), "tmp.txt")), @"" );
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), @"" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
       
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath02
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    pObj = path_NewA("/Users/bob/x/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive), @"" );
        
        XCTAssertTrue( (pPath), @"" );
        XCTAssertTrue( (12 == AStr_getLength((ASTR_DATA *)pPath)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/Users/bob/x")), @"" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), @"" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath03
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    pObj = path_NewA("tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive), @"" );
        
        XCTAssertTrue( (NULL == pPath), @"" );
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), @"" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath04
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    pObj = path_NewA("/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive), @"" );
        
        XCTAssertTrue( (pPath), @"" );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")), @"" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), @"" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath05
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    pObj = path_NewA("file:tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (pDrive), @"" );
        XCTAssertTrue( (4 == AStr_getLength(pDrive)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pDrive), "file")), @"" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        XCTAssertTrue( (NULL == pPath), @"" );
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), @"" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath06
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    pObj = path_NewA("file:/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (pDrive), @"" );
        XCTAssertTrue( (4 == AStr_getLength(pDrive)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pDrive), "file")), @"" );
        if (pDrive) {
            obj_Release(pDrive);
            pDrive = OBJ_NIL;
        }
        
        XCTAssertTrue( (pPath), @"" );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")), @"" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), @"" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath07
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    pObj = path_NewA(":/tmp.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive), @"" );
        
        XCTAssertTrue( (pPath), @"" );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pPath)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pPath), "/")), @"" );
        if (pPath) {
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileE), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileE)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileE), "txt")), @"" );
        if (pFileE) {
            obj_Release(pFileE);
            pFileE = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testSplitPath08
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA  *pDrive = OBJ_NIL;
    PATH_DATA   *pPath = OBJ_NIL;
    PATH_DATA   *pFileName = OBJ_NIL;
    ASTR_DATA  *pFileN = OBJ_NIL;
    ASTR_DATA  *pFileE = OBJ_NIL;
    
    pObj = path_NewA("tmp");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_SplitPath(pObj, &pDrive, &pPath, &pFileName);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        XCTAssertTrue( (NULL == pDrive), @"" );
        
        XCTAssertTrue( (NULL == pPath), @"" );
        
        eRc = path_SplitFile(pFileName, &pFileN, &pFileE);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        if (pFileName) {
            obj_Release(pFileName);
            pFileName = OBJ_NIL;
        }
        
        XCTAssertTrue( (pFileN), @"" );
        XCTAssertTrue( (3 == AStr_getLength(pFileN)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData(pFileN), "tmp")), @"" );
        if (pFileN) {
            obj_Release(pFileN);
            pFileN = OBJ_NIL;
        }
        
        XCTAssertTrue( (NULL == pFileE), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCleanDir01
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = path_NewA("//tmp/");
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == AStr_getLength((ASTR_DATA *)pObj)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/tmp")), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCleanDir02
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = path_NewA("/");
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCleanDir03
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = path_NewA("/./");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength((ASTR_DATA *)pObj)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "/")), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCleanDir04
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = path_NewA("x/./y");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCleanDir05
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    pObj = path_NewA("x//y");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength((ASTR_DATA *)pObj)), @"" );
        XCTAssertTrue( (0 == strcmp(AStr_getData((ASTR_DATA *)pObj), "x/y")), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testCleanDir06
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    char        *pszStr;
    uint32_t    i;
    
    pObj = path_NewA("~/y.tmp");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_Clean(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = AStr_getLength((ASTR_DATA *)pObj);
        XCTAssertTrue( (16 == i), @"" );
        pszStr = AStr_getData((ASTR_DATA *)pObj);
        XCTAssertTrue( (0 == strcmp(pszStr, "/Users/bob/y.tmp")), @"" );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testToBash
{
    PATH_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    ASTR_DATA   *pStr;
    
    pObj = path_NewA("xy z.txt");
    XCTAssertFalse( (OBJ_NIL == pObj), @"Could not alloc PATH_DATA" );
    if (pObj) {
        
        eRc = path_ToBash(pObj,&pStr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == AStr_getLength(pStr)) );
        XCTAssertTrue( (0 == AStr_CompareA(pStr, "xy\\ z.txt")) );
        mem_Free(pStr);
        pStr = NULL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



