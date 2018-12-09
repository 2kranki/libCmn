/*
 *	Generated 07/26/2018 19:55:39
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
#include    <scanner_internal.h>



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






int             test_scanner_OpenClose(
    const
    char            *pTestName
)
{
    SCANNER_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = scanner_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = scanner_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_scanner_ScanAstr01(
    const
    char            *pTestName
)
{
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *testString;
    char            *pCurChr;
    uint32_t        cScanned = 0;
    ASTR_DATA       *pStr = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = scanner_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = scanner_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        testString = " abc";
        pCurChr = testString;
        cScanned = 0;
        pStr = scanner_ScanStringToAStr(&pCurChr, &cScanned);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (3 == cScanned) );
        TINYTEST_TRUE( (*pCurChr == '\0') );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        testString = " abc ";
        pCurChr = testString;
        cScanned = 0;
        pStr = scanner_ScanStringToAStr(&pCurChr, &cScanned);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (3 == cScanned) );
        TINYTEST_TRUE( (*pCurChr == ' ') );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        testString = " abc, ";
        pCurChr = testString;
        cScanned = 0;
        pStr = scanner_ScanStringToAStr(&pCurChr, &cScanned);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (3 == cScanned) );
        TINYTEST_TRUE( (*pCurChr == ',') );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        testString = " abc= ";
        pCurChr = testString;
        cScanned = 0;
        pStr = scanner_ScanStringToAStr(&pCurChr, &cScanned);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (3 == cScanned) );
        TINYTEST_TRUE( (*pCurChr == '=') );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        testString = " 'abc' ";
        pCurChr = testString;
        cScanned = 0;
        pStr = scanner_ScanStringToAStr(&pCurChr, &cScanned);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (pCurChr == (testString + 6)) );
        TINYTEST_TRUE( (3 == cScanned) );
        TINYTEST_TRUE( (*pCurChr == ' ') );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        testString = " 'abc\\n\\r' ";
        pCurChr = testString;
        cScanned = 0;
        pStr = scanner_ScanStringToAStr(&pCurChr, &cScanned);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (pCurChr == (testString + 10)) );
        TINYTEST_TRUE( (5 == cScanned) );
        TINYTEST_TRUE( (*pCurChr == ' ') );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc\n\r")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        testString = " 'abc\\x11' ";
        pCurChr = testString;
        cScanned = 0;
        pStr = scanner_ScanStringToAStr(&pCurChr, &cScanned);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        TINYTEST_TRUE( (pCurChr == (testString + 10)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (*pCurChr == ' ') );
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, "abc\x11")) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_scanner_ScanDec01(
    const
    char            *pTestName
)
{
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *testString;
    char            *pCurChr;
    uint32_t        cScanned = 0;
    uint32_t        value = 0;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = scanner_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = scanner_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        testString = " 100";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanDec32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (100 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == '\0') );
        
        testString = " 100 ";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanDec32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (100 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ' ') );
        
        testString = " 100,";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanDec32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (100 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ',') );
        
        testString = " -10,";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanDec32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (-10 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ',') );
        
        testString = " +10,";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanDec32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (10 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ',') );
        
        testString = " x,";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanDec32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == testString) );
        TINYTEST_TRUE( (0 == cScanned) );
        TINYTEST_TRUE( (0 == value) );
        TINYTEST_TRUE( (!fRc) );
        
        testString = " 1x,";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanDec32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == testString) );
        TINYTEST_TRUE( (0 == cScanned) );
        TINYTEST_TRUE( (0 == value) );
        TINYTEST_TRUE( (!fRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_scanner_ScanHex01(
    const
    char            *pTestName
)
{
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *testString;
    char            *pCurChr;
    uint32_t        cScanned = 0;
    uint32_t        value = 0;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = scanner_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = scanner_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        testString = " 10F";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanHex32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (271 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == '\0') );
        
        testString = " 10F ";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanHex32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (271 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ' ') );
        
        testString = " 10F,";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanHex32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (271 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ',') );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_scanner_ScanOct01(
    const
    char            *pTestName
)
{
    SCANNER_DATA    *pObj = OBJ_NIL;
    char            *testString;
    char            *pCurChr;
    uint32_t        cScanned = 0;
    uint32_t        value = 0;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = scanner_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = scanner_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        testString = " 100";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanOct32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (64 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == '\0') );
        
        testString = " 277 ";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanOct32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (191 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ' ') );
        
        testString = " 123,";
        pCurChr = testString;
        cScanned = 0;
        value = 0;
        fRc = scanner_ScanOct32(&pCurChr, &cScanned, &value);
        TINYTEST_TRUE( (pCurChr == (testString + 4)) );
        TINYTEST_TRUE( (4 == cScanned) );
        TINYTEST_TRUE( (83 == value) );
        TINYTEST_TRUE( (fRc) );
        TINYTEST_TRUE( (*pCurChr == ',') );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_scanner_AStrArray01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    SCANNER_DATA    *pObj = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    char            *testString;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = scanner_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = scanner_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        testString = "a";
        fprintf(stderr, "Scanning: %s\n", testString);
        pArray = scanner_ScanStringToAstrArray(testString);
        {
            ASTR_DATA           *pStr;
            pStr = AStrArray_ToDebugString(pArray, 4);
            if (pStr) {
                fprintf(stderr, "\tAStrArray =\n%s\n", AStr_getData(pStr));
                obj_Release(pStr);
            }
        }
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (2 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "a");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        
        testString = "a,b";
        fprintf(stderr, "Scanning: %s\n", testString);
        pArray = scanner_ScanStringToAstrArray(testString);
        {
            ASTR_DATA           *pStr;
            pStr = AStrArray_ToDebugString(pArray, 4);
            if (pStr) {
                fprintf(stderr, "\tAStrArray =\n%s\n", AStr_getData(pStr));
                obj_Release(pStr);
            }
        }
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (3 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "a");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 3), "b");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        
        testString = "a b";
        fprintf(stderr, "Scanning: %s\n", testString);
        pArray = scanner_ScanStringToAstrArray(testString);
        {
            ASTR_DATA           *pStr;
            pStr = AStrArray_ToDebugString(pArray, 4);
            if (pStr) {
                fprintf(stderr, "\tAStrArray =\n%s\n", AStr_getData(pStr));
                obj_Release(pStr);
            }
        }
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE( (3 == AStrArray_getSize(pArray)) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 2), "a");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        eRc = AStr_CompareA(AStrArray_Get(pArray, 3), "b");
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pArray);
        pArray = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_scanner);
    TINYTEST_ADD_TEST(test_scanner_AStrArray01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_scanner_ScanOct01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_scanner_ScanHex01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_scanner_ScanDec01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_scanner_ScanAstr01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_scanner_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_scanner);





