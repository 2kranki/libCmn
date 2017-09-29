/*
 *	Generated 10/21/2016 23:23:20
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


#include    "lru_internal.h"

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




@interface lruTests : XCTestCase

@end

@implementation lruTests


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
    LRU_DATA        *pObj = OBJ_NIL;
    uint8_t         buffer1[4];
    uint8_t         buffer2[4];
    uint32_t        i;
    ERESULT         eRc;
    bool            fRc;
    LRU_SECTOR      *pSector;
   
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

}



@end



