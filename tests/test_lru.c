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
#include    <lru_internal.h>



static
const
//                            0  1  2  3  4  5  6  7  8  9  0  1  2  3  4
char        *pReadOnlyDisk ="aaabbbcccdddeeefffggghhhiiijjjkkklllmmmnnn"
//                            5  6  7  8  9  0  1  2  3  4  5
                            "ooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz";
static
const
uint32_t    sectorSize = 3;
static
uint32_t    numSectors = 26;


ERESULT         logicalRead(
    OBJ_ID          pObj,
    uint32_t        lsn,                // Logical Sector Number
    uint8_t         *pBuffer            // Buffer of sectorSize bytes
)
{
    const
    char            *pData = NULL;
    
    if (lsn >= numSectors) {
        return ERESULT_INVALID_PARAMETER;
    }
    if (pBuffer == NULL) {
        return ERESULT_INVALID_PARAMETER;
    }
    
    pData = &pReadOnlyDisk[lsn * sectorSize];
    memmove(pBuffer, pData, sectorSize);
 
    return ERESULT_SUCCESS;
}




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






int         test_lru_OpenClose(
    const
    char        *pTestName
)
{
    LRU_DATA        *pObj = OBJ_NIL;
    uint8_t         buffer1[4];
    uint8_t         buffer2[4];
    uint32_t        i;
    ERESULT         eRc;
    bool            fRc;
    LRU_SECTOR      *pSector;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    for (i=0; i<4; ++i) {
        buffer1[i] = '\0';
        buffer2[i] = '\0';
    }
    pObj = lru_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lru_Init(pObj, sectorSize, 2);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    fRc = lru_setLogicalSectorRead(pObj, logicalRead, NULL);
    XCTAssertTrue( (fRc) );
    if (pObj) {
        eRc = lru_Read(pObj, 0, buffer1);
        XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == strcmp((char *)buffer1, "aaa")) );

        eRc = lru_Read(pObj, 1, buffer1);
        XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == strcmp((char *)buffer1, "bbb")) );
        XCTAssertTrue( (2 == listdl_Count(&pObj->lruList)) );
        pSector = listdl_Index(&pObj->lruList, 1);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "bbb", 3)) );
        pSector = listdl_Index(&pObj->lruList, 2);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "aaa", 3)) );
        
        eRc = lru_Read(pObj, 2, buffer1);
        XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == strcmp((char *)buffer1, "ccc")) );
        pSector = listdl_Index(&pObj->lruList, 1);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "ccc", 3)) );
        pSector = listdl_Index(&pObj->lruList, 2);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "bbb", 3)) );
        
        eRc = lru_Read(pObj, 0, buffer1);
        XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == strcmp((char *)buffer1, "aaa")) );
        pSector = listdl_Index(&pObj->lruList, 1);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "aaa", 3)) );
        pSector = listdl_Index(&pObj->lruList, 2);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "ccc", 3)) );
        
        eRc = lru_Read(pObj, 3, buffer1);
        XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == strcmp((char *)buffer1, "ddd")) );
        
        eRc = lru_Read(pObj, 4, buffer1);
        XCTAssertTrue( (!ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == strcmp((char *)buffer1, "eee")) );
        pSector = listdl_Index(&pObj->lruList, 1);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "eee", 3)) );
        pSector = listdl_Index(&pObj->lruList, 2);
        XCTAssertTrue( (0 == strncmp((char *)pSector->data, "ddd", 3)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_lru);
  TINYTEST_ADD_TEST(test_lru_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_lru);





