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
#include    <dbCsv_internal.h>
#include    <szTbl.h>



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






int         test_dbCsv_OpenClose(
    const
    char        *pTestName
)
{
    DBCSV_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    pObj = dbCsv_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbCsv_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dbCsv_Input01(
    const
    char        *pTestName
)
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

    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pStr = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pStr) );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    
    pObj = dbCsv_NewFromAStr( pStr, pPath, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pRecords = dbCsv_ParseFile(pObj);
        XCTAssertFalse( (OBJ_NIL == pRecords) );
        if (pRecords) {
            iMax = objArray_getSize(pRecords);
            for (i=1; i<=iMax; ++i) {
                pRecord = objArray_Get(pRecords,i);
                XCTAssertFalse( (OBJ_NIL == pRecord) );
                if (pRecord) {
                    jMax = objArray_getSize(pRecord);
                    for (j=1; j<=jMax; ++j) {
                        pField = objArray_Get(pRecord,j);
                        XCTAssertFalse( (OBJ_NIL == pField) );
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
                                        XCTAssertTrue( (0 == strcmp("a",AStr_getData(pField))) );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("10",AStr_getData(pField))) );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("def",AStr_getData(pField))) );
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

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_dbCsv_Input02(
    const
    char        *pTestName
)
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
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    pStr = AStr_NewA(pTestInput02);
    XCTAssertFalse( (OBJ_NIL == pStr) );
    pPath = path_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pPath) );
    
    pObj = dbCsv_NewFromAStr( pStr, pPath, 4 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pRecords = dbCsv_ParseFile(pObj);
        XCTAssertFalse( (OBJ_NIL == pRecords) );
        if (pRecords) {
            iMax = objArray_getSize(pRecords);
            for (i=1; i<=iMax; ++i) {
                pRecord = objArray_Get(pRecords,i);
                XCTAssertFalse( (OBJ_NIL == pRecord) );
                if (pRecord) {
                    jMax = objArray_getSize(pRecord);
                    for (j=1; j<=jMax; ++j) {
                        pField = objArray_Get(pRecord,j);
                        XCTAssertFalse( (OBJ_NIL == pField) );
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
                                        XCTAssertTrue( (0 == strcmp("a",AStr_getData(pField))) );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("b",AStr_getData(pField))) );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("c",AStr_getData(pField))) );
                                        break;
                                        
                                    case 4:
                                        XCTAssertTrue( (0 == strcmp("def",AStr_getData(pField))) );
                                        break;
                                        
                                    default:
                                        break;
                                }
                                break;
                                
                            case 2:
                                switch (j) {
                                    case 1:
                                        XCTAssertTrue( (0 == strcmp("d",AStr_getData(pField))) );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("e",AStr_getData(pField))) );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("f",AStr_getData(pField))) );
                                        break;
                                        
                                    case 4:
                                        XCTAssertTrue( (0 == strcmp("55",AStr_getData(pField))) );
                                        break;
                                        
                                    default:
                                        break;
                                }
                                break;
                                
                            case 3:
                                switch (j) {
                                    case 1:
                                        XCTAssertTrue( (0 == strcmp("h",AStr_getData(pField))) );
                                        break;
                                        
                                    case 2:
                                        XCTAssertTrue( (0 == strcmp("i",AStr_getData(pField))) );
                                        break;
                                        
                                    case 3:
                                        XCTAssertTrue( (0 == strcmp("j",AStr_getData(pField))) );
                                        break;
                                        
                                    case 4:
                                        XCTAssertTrue( (0 == strcmp("77",AStr_getData(pField))) );
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

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}






TINYTEST_START_SUITE(test_dbCsv);
  TINYTEST_ADD_TEST(test_dbCsv_OpenClose,setUp,tearDown);
  TINYTEST_ADD_TEST(test_dbCsv_Input01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_dbCsv_Input02,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_dbCsv);





