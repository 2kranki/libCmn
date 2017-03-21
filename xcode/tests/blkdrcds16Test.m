/*
 *	Generated 03/10/2017 19:43:23
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


#include    "blkdrcds16_internal.h"



static
const
char    *pWord2 = "ab";
static
const
char    *pWord3 = "cde";
static
const
char    *pWord4 = "fghi";
static
const
char    *pWord5 = "jklmn";
static
const
char    *pWord6 = "opqrst";
static
const
char    *pWord2h = "AB";
static
const
char    *pWord3h = "CDE";
#ifdef XYZZY
static
const
char    *pWord4h = "FGHI";
#endif
static
const
char    *pWord5h = "JKLMN";
#ifdef XYZZY
static
const
char    *pWord6h = "OPQRST";
#endif





@interface blkdrcds16Tests : XCTestCase

@end

@implementation blkdrcds16Tests


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




- (void)testCalc
{
    uint16_t        size = 0;
    
    size = blkdrcds16_CalcBlockSize(10, 8, 64);
    XCTAssertTrue( (562 == size) );
    
}



- (void)testOpenClose
{
    BLKDRCDS16_DATA	*pObj = OBJ_NIL;
    uint16_t        size = 0;
    uint16_t        index = 0;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    char            data[16];
   
    pObj = blkdrcds16_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = blkdrcds16_InitWithSizes(pObj, 32, 0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (0 == size) );
        
        fprintf(stderr, "*** Just after Initialization ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = blkdrcds16_RecordAdd(pObj, 6, (void *)pWord6, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (1 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 1, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        eRc = blkdrcds16_RecordGet(pObj, 1, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );

        fprintf(stderr, "*** Just after Add Record 1 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 4, (void *)pWord4, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, index, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (6 == size) );
        
        fprintf(stderr, "*** Just after Add Record 2 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 2, (void *)pWord2, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 3, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (0 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord4)) );
        
        fprintf(stderr, "*** Just after Add Record 3 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordDelete(pObj, 3);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (6 == size) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        
        fprintf(stderr, "*** Just after Delete Record 3 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



- (void)testDeleteFirst
{
    BLKDRCDS16_DATA	*pObj = OBJ_NIL;
    uint16_t        size = 0;
    uint16_t        index = 0;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    char            data[16];
    
    pObj = blkdrcds16_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = blkdrcds16_InitWithSizes(pObj, 32, 0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (0 == size) );
        
        fprintf(stderr, "*** Just after Initialization ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 6, (void *)pWord6, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (1 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 1, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        eRc = blkdrcds16_RecordGet(pObj, 1, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        
        fprintf(stderr, "*** Just after Add Record 1 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 4, (void *)pWord4, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, index, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (6 == size) );
        
        fprintf(stderr, "*** Just after Add Record 2 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 2, (void *)pWord2, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 3, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (0 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord4)) );
        
        fprintf(stderr, "*** Just after Add Record 3 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordDelete(pObj, 1);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (10 == size) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord4)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );

        fprintf(stderr, "*** Just after Delete Record 1 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testDeleteMiddle
{
    BLKDRCDS16_DATA	*pObj = OBJ_NIL;
    uint16_t        size = 0;
    uint16_t        index = 0;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    char            data[16];
    
    pObj = blkdrcds16_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = blkdrcds16_InitWithSizes(pObj, 32, 0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (0 == size) );
        
        fprintf(stderr, "*** Just after Initialization ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 6, (void *)pWord6, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (1 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 1, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        eRc = blkdrcds16_RecordGet(pObj, 1, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        
        fprintf(stderr, "*** Just after Add Record 1 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 4, (void *)pWord4, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, index, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (6 == size) );
        
        fprintf(stderr, "*** Just after Add Record 2 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 2, (void *)pWord2, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 3, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (0 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord4)) );
        
        fprintf(stderr, "*** Just after Add Record 3 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordDelete(pObj, 2);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getUnused(pObj);
        XCTAssertTrue( (8 == size) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord6)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        fprintf(stderr, "*** Just after Delete Record 2 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



- (void)testUpdate
{
    BLKDRCDS16_DATA	*pObj = OBJ_NIL;
    uint16_t        size = 0;
    uint16_t        index = 0;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    char            data[16];
    
    pObj = blkdrcds16_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = blkdrcds16_InitWithSizes(pObj, 36, 0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (0 == size) );
        
        fprintf(stderr, "*** Just after Initialization ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 6, (void *)pWord6, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (1 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 1, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        eRc = blkdrcds16_RecordGet(pObj, 1, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        
        fprintf(stderr, "*** Just after Add Record 1 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 4, (void *)pWord4, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, index, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        
        fprintf(stderr, "*** Just after Add Record 2 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        eRc = blkdrcds16_RecordAdd(pObj, 2, (void *)pWord2, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == index) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        eRc = blkdrcds16_RecordGetSize(pObj, 3, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        eRc = blkdrcds16_RecordGet(pObj, index, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord4)) );
        
        fprintf(stderr, "*** Just after Add Record 3 ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Make second record smaller
        eRc = blkdrcds16_RecordUpdate(pObj, 2, 3, (void *)pWord3);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord6)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord3)) );
        eRc = blkdrcds16_RecordGet(pObj, 3, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        fprintf(stderr, "*** Just after Update Record 2 to be smaller ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Make second record smaller
        eRc = blkdrcds16_RecordUpdate(pObj, 2, 5, (void *)pWord5);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord6)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5)) );
        eRc = blkdrcds16_RecordGet(pObj, 3, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        fprintf(stderr, "*** Just after Update Record 2 to be bigger ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        
        // Make first record smaller
        eRc = blkdrcds16_RecordUpdate(pObj, 1, 2, (void *)pWord2h);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2h)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5)) );
        eRc = blkdrcds16_RecordGet(pObj, 3, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        fprintf(stderr, "*** Just after Update Record 1 to be smaller ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Make first record larger
        eRc = blkdrcds16_RecordUpdate(pObj, 1, 5, (void *)pWord5h);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5h)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5)) );
        eRc = blkdrcds16_RecordGet(pObj, 3, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord2)) );
        
        fprintf(stderr, "*** Just after Update Record 1 to be bigger ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Make third record larger
        eRc = blkdrcds16_RecordUpdate(pObj, 3, 3, (void *)pWord3h);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5h)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5)) );
        eRc = blkdrcds16_RecordGet(pObj, 3, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord3h)) );
        
        fprintf(stderr, "*** Just after Update Record 3 to be smaller ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        // Make third record smaller
        eRc = blkdrcds16_RecordUpdate(pObj, 3, 3, (void *)pWord3h);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = blkdrcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        
        eRc = blkdrcds16_RecordGet(pObj, 1, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5h)) );
        eRc = blkdrcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (5 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord5)) );
        eRc = blkdrcds16_RecordGet(pObj, 3, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord3h)) );
        
        fprintf(stderr, "*** Just after Update Record 3 to be bigger ***\n");
        pStr = blkdrcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
}



@end



