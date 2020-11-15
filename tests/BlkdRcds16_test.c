// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/22/2019 10:06:17
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
#include    <JsonIn.h>
#include    <trace.h>
#include    <BlkdRcds16_internal.h>


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




int             setUp(
    const
    char            *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int             tearDown(
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    
    JsonIn_RegisterReset();
    trace_SharedReset( ); 
    if (mem_Dump( ) ) {
        fprintf(
                stderr,
                "\x1b[1m"
                "\x1b[31m"
                "ERROR: "
                "\x1b[0m"
                "Leaked memory areas were found!\n"
        );
        exitCode = 4;
        return 0;
    }
    mem_Release( );
    
    return 1; 
}






int             test_BlkdRcds16_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BLKDRCDS16_DATA	*pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BlkdRcds16_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = BlkdRcds16_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BLKDRCDS16);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_BlkdRcds16_Test01(
    const
    char        *pTestName
)
{
    BLKDRCDS16_DATA *pObj = OBJ_NIL;
    uint16_t        size = 0;
    uint16_t        index = 0;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    char            data[16];
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = BlkdRcds16_NewWithBlockSize(40, 0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        size = BlkdRcds16_getNumRecords(pObj);
        XCTAssertTrue( (0 == size) );
        
        fprintf(stderr, "*** Just after Initialization ***\n");
        pStr = BlkdRcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = BlkdRcds16_RecordAppend(pObj, 6, (void *)pWord6, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (1 == index) );
        fprintf(stderr, "*** Just after Add Record 1 ***\n");
        pStr = BlkdRcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        size = BlkdRcds16_getNumRecords(pObj);
        XCTAssertTrue( (1 == size) );
        eRc = BlkdRcds16_RecordGetSize(pObj, 1, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );
        eRc = BlkdRcds16_RecordGet(pObj, 1, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == size) );
        eRc = BlkdRcds16_RecordGet(pObj, 1, 16, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (6 == size) );

        eRc = BlkdRcds16_RecordAppend(pObj, 4, (void *)pWord4, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == index) );
        fprintf(stderr, "*** Just after Add Record 2 ***\n");
        pStr = BlkdRcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        size = BlkdRcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        eRc = BlkdRcds16_RecordGetSize(pObj, index, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        eRc = BlkdRcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == size) );
        size = BlkdRcds16_getUnused(pObj);
        XCTAssertTrue( (6 == size) );
        eRc = BlkdRcds16_RecordGet(pObj, index, 16, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        XCTAssertTrue( (0 == strncmp(data, pWord4, size)) );

        eRc = BlkdRcds16_RecordAppend(pObj, 2, (void *)pWord2, &index);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (3 == index) );
        fprintf(stderr, "*** Just after Add Record 3 ***\n");
        pStr = BlkdRcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        size = BlkdRcds16_getNumRecords(pObj);
        XCTAssertTrue( (3 == size) );
        eRc = BlkdRcds16_RecordGetSize(pObj, 3, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        eRc = BlkdRcds16_RecordGet(pObj, index, 0, NULL, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == size) );
        size = BlkdRcds16_getUnused(pObj);
        XCTAssertTrue( (0 == size) );
        eRc = BlkdRcds16_RecordGet(pObj, index, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (2 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strncmp(data, pWord2, size)) );
        
        eRc = BlkdRcds16_RecordGet(pObj, 2, 12, data, &size);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (4 == size) );
        data[size] = 0;
        XCTAssertTrue( (0 == strcmp(data, pWord4)) );
        
        eRc = BlkdRcds16_RecordDelete(pObj, 3);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        size = BlkdRcds16_getUnused(pObj);
        XCTAssertTrue( (6 == size) );
        size = BlkdRcds16_getNumRecords(pObj);
        XCTAssertTrue( (2 == size) );
        
        fprintf(stderr, "*** Just after Delete Record 3 ***\n");
        pStr = BlkdRcds16_ToDebugString(pObj, 4);
        fprintf(stderr, "%s\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_BlkdRcds16_Calc(
    const
    char        *pTestName
)
{
    uint16_t        size = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    size = BlkdRcds16_CalcFromRecordSize(10, 8, 64);
    fprintf(stderr, "\tSize = %d\n", size);
    XCTAssertTrue( (570 == size) );

    size = BlkdRcds16_CalcFromBlockSize(1024, 0);
    fprintf(stderr, "\tSize = %d\n", size);
    XCTAssertTrue( (1008 == size) );

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_BlkdRcds16);
    TINYTEST_ADD_TEST(test_BlkdRcds16_Calc,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BlkdRcds16_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BlkdRcds16_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_BlkdRcds16);





