/*
 *	Generated 11/08/2017 09:27:01
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
#include    <array_internal.h>



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






int         test_array_OpenClose(
    const
    char        *pTestName
)
{
    ARRAY_DATA	*pObj = OBJ_NIL;
    uint32_t    i;
    ERESULT     eRc;
    char        *pStr;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = array_NewWithSize(1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = array_InsertData(pObj, 1, 4, "abc");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (4 == i) );
        XCTAssertTrue( (4 == pObj->max) );

        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Insert01(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ARRAY_DATA      *pObj2 = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = array_InsertData(pObj, 1, 4, "abc");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        eRc = array_InsertData(pObj, 1, 3, "def");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == memcmp("defabc\x00", pStr, array_getSize(pObj))) );
 
        pObj2 = array_Copy(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        pStr = array_Ptr(pObj2, 1);
        XCTAssertTrue( (0 == memcmp("defabc\x00", pStr, array_getSize(pObj))) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        pObj2 = array_DeepCopy(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        pStr = array_Ptr(pObj2, 1);
        XCTAssertTrue( (0 == memcmp("defabc\x00", pStr, array_getSize(pObj))) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Insert02(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = array_InsertData(pObj, 1, 4, "abc");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (4 == i) );
        
        pStr = array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)) );
        
        eRc = array_InsertData(pObj, 3, 3, "def");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        
        pStr = array_Ptr(pObj,1);
        XCTAssertTrue( (0 == memcmp("abdefc\x00", pStr, array_getSize(pObj))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Insert03(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = array_InsertData(pObj, 1, 4, "abc");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (4 == i) );
        
        pStr = array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)) );
        
        eRc = array_InsertData(pObj, 4, 3, "def");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == memcmp("abcdef\x00", pStr, array_getSize(pObj))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_CopyAssign01(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ARRAY_DATA      *pOther = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = array_InsertData(pObj, 1, 7, "abcdef");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        
        pStr = array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 6)) );
        
        pOther = array_Copy(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 7)) );
        
        eRc = array_InsertData(pOther, 7, 3, "ghi");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pOther);
        XCTAssertTrue( (10 == i) );
        
        pStr = array_Ptr(pOther, 1);
        XCTAssertTrue( (0 == strncmp("abcdefghi", pStr, 10)) );
        
        eRc = array_Assign(pOther, pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (10 == i) );
        
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strncmp("abcdefghi", pStr, 10)) );
        
        obj_Release(pOther);
        pOther = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Get01(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    char            chr;
    char            chrs[7];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = array_InsertData(pObj, 1, 7, "abcdef");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("abcdef", pStr)) );
        
        eRc = array_Get(pObj, 1, 1, &chr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (chr == 'a') );
        
        eRc = array_Get(pObj, 3, 1, &chr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (chr == 'c') );
        
        eRc = array_Get(pObj, 6, 1, &chr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (chr == 'f') );
        
        eRc = array_Get(pObj, 8, 1, &chr);
        XCTAssertFalse( (ERESULT_OK(eRc)) );
        
        for (i=0; i<7; ++i) {
            chrs[i] = '\0';
        }
        
        eRc = array_Get(pObj, 5, 2, &chrs);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (0 == strcmp("ef", chrs)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Delete01(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    uint32_t        len;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        array_setZeroNew(pObj, true);
        
        pStr = "abcdef";
        len = (uint32_t)(strlen(pStr) + 1);
        eRc = array_InsertData(pObj, 1, len, pStr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (len == i) );
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("abcdef", pStr)) );
        fprintf(stderr, "\tmax = %d\n", array_getMax(pObj));
        XCTAssertTrue( (0 == memcmp("abcdef\x00\x00", pStr, array_getMax(pObj))) );

        eRc = array_Delete(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == memcmp("bcdef\x00", pStr, array_getSize(pObj))) );
        XCTAssertTrue( (0 == memcmp("bcdef\x00\x00\x00", pStr, array_getMax(pObj))) );

        eRc = array_Delete(pObj, 4, 2);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (4 == i) );
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == memcmp("bcd\x00", pStr, array_getSize(pObj))) );
        
        eRc = array_Delete(pObj, 2, 2);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (2 == i) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Delete02(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    uint32_t        len;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        array_setZeroNew(pObj, true);

        pStr = "cabbaadeee";
        len = (uint16_t)(strlen(pStr) + 1);
        eRc = array_InsertData(pObj, 1, len, pStr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (len == i) );
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("cabbaadeee", pStr)) );
        
        eRc = array_Delete(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (10 == i) );
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("abbaadeee", pStr)) );
        
        eRc = array_Delete(pObj, 7, 3);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("abbaad", pStr)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Ptr01(
    const
    char            *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    uint8_t         *pData;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = (uint8_t *)array_Ptr(pObj, 2);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertTrue( (pData == (pObj->pArray + 2-1)) );
        
        pData = (uint8_t *)array_Ptr(pObj, 4);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertTrue( (pData == (pObj->pArray + 4-1)) );
        
        pData = (uint8_t *)array_Ptr(pObj, 2);
        XCTAssertFalse( (pData == NULL) );
        XCTAssertTrue( (pData == (pObj->pArray + 2-1)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Xchg01(
    const
    char        *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    char            chr;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = array_InsertData(pObj, 1, 7, "abcdef");
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        
        i = array_getSize(pObj);
        XCTAssertTrue( (7 == i) );
        
        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("abcdef", pStr)) );
        
        eRc = array_Get(pObj, 1, 1, &chr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (chr == 'a') );
        
        eRc = array_Get(pObj, 3, 1, &chr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (chr == 'c') );
        
        eRc = array_Get(pObj, 6, 1, &chr);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (chr == 'f') );
        
        eRc = array_Get(pObj, 8, 1, &chr);
        XCTAssertFalse( (ERESULT_OK(eRc)) );
        
        eRc = array_Xchg(pObj, 1, 6);
        XCTAssertTrue( (ERESULT_OK(eRc)) );

        pStr = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strcmp("fbcdea", pStr)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_DeleteOdd01(
    const
    char            *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStrA;
    uint32_t        i;
    uint32_t        len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        array_setZeroNew(pObj, true);
        array_setMisc(pObj, 1);
        i = array_getMisc(pObj);
        XCTAssertTrue( (1 == i) );

        pStrA = "abcdef";
        len = (uint16_t)(strlen(pStrA));
        XCTAssertTrue( (len == 6) );
        eRc = array_InsertData(pObj, 1, len, pStrA);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (len == i) );
        pStrA = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStrA, len)) );
        
        eRc = array_DeleteOdd(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( ((len >> 1) == i) );
        pStrA = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strncmp("ace", pStrA, (len >> 1))) );
        i = array_getMisc(pObj);
        XCTAssertTrue( (2 == i) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_DeleteOdd02(
    const
    char            *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStrA;
    uint32_t        i;
    uint32_t        len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        array_setZeroNew(pObj, true);
        array_setMisc(pObj, 1);
        i = array_getMisc(pObj);
        XCTAssertTrue( (1 == i) );
        
        pStrA = "abcde";
        len = (uint16_t)(strlen(pStrA));
        XCTAssertTrue( (len == 5) );
        eRc = array_InsertData(pObj, 1, len, pStrA);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (len == i) );
        pStrA = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strncmp("abcde", pStrA, len)) );
        
        eRc = array_DeleteOdd(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( ((len >> 1) == i) );
        pStrA = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strncmp("ace", pStrA, (len >> 1))) );
        i = array_getMisc(pObj);
        XCTAssertTrue( (2 == i) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_array_Zero01(
    const
    char            *pTestName
)
{
    ARRAY_DATA      *pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStrA;
    uint32_t        i;
    uint32_t        len;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = array_NewWithSize(1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        i = array_getElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        array_setZeroNew(pObj, true);
        array_setMisc(pObj, 1);
        i = array_getMisc(pObj);
        XCTAssertTrue( (1 == i) );

        pStrA = "abcde";
        len = (uint16_t)(strlen(pStrA));
        XCTAssertTrue( (len == 5) );
        eRc = array_InsertData(pObj, 1, len, pStrA);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = array_getSize(pObj);
        XCTAssertTrue( (len == i) );
        pStrA = array_Ptr(pObj, 1);
        XCTAssertTrue( (0 == strncmp("abcdefg", pStrA, len)) );

        eRc = array_ZeroAll(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        for (i=0; i<len; i++) {
            XCTAssertTrue( (pStrA[i] == 0) );
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_array);
    TINYTEST_ADD_TEST(test_array_Zero01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_DeleteOdd02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_DeleteOdd01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Xchg01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Ptr01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Delete02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Delete01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Get01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_CopyAssign01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Insert03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Insert02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_Insert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_array);





