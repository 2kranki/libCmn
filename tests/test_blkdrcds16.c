/*
 *	Generated 06/05/2017 21:57:10
 */





// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      TINYTEST_ASSERT(condition)
//      TINYTEST_ASSERT_MSG(condition,msg)
//      TINYTEST_EQUAL(expected, actual)
//      TINYTEST_EQUAL_MSG(expected, actual, msg)
//      TINYTEST_FALSE_MSG(condition,msg)
//      TINYTEST_FALSE(condition)
//      TINYTEST_TRUE_MSG(pointer,msg)
//      TINYTEST_TRUE(condition)





#include    <tinytest.h>
#include    <cmn_defs.h>
#include    <trace.h>
#include    <blkdrcds16_internal.h>



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




int         setUp(
    const
    char        *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int         tearDown(
    const
    char        *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_blkdrcds16_OpenClose(
    const
    char        *pTestName
)
{
    BLKDRCDS16_DATA	*pObj = OBJ_NIL;
    uint16_t        size = 0;
    uint16_t        index = 0;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    char            data[16];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = blkdrcds16_Alloc( );
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

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_blkdrcds16_Calc(
    const
    char        *pTestName
)
{
    uint16_t        size = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    size = blkdrcds16_CalcBlockSize(10, 8, 64);
    XCTAssertTrue( (562 == size) );
    

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_blkdrcds16);
  TINYTEST_ADD_TEST(test_blkdrcds16_Calc,setUp,tearDown);
  TINYTEST_ADD_TEST(test_blkdrcds16_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_blkdrcds16);





