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
#include    <pwr2Array_internal.h>



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






int         test_pwr2Array_OpenClose(
    const
    char        *pTestName
)
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = pwr2Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = pwr2Array_Init( pObj, 0 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pwr2Array_Insert01(
    const
    char        *pTestName
)
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = pwr2Array_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = pwr2Array_Init( pObj, 0 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "def");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("defabc", pStr)) );
            obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pwr2Array_Insert02(
    const
    char        *pTestName
)
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = pwr2Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)) );
        
        eRc = pwr2Array_InsertData(pObj, 3, 3, "def");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abdefc", pStr)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pwr2Array_Insert03(
    const
    char        *pTestName
)
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = pwr2Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 3, "abc");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abc", pStr)) );
        
        eRc = pwr2Array_InsertData(pObj, 4, 3, "def");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abcdef", pStr)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pwr2Array_Get01(
    const
    char        *pTestName
)
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    char            chr;
    char            chrs[7];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = pwr2Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 6, "abcdef");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strcmp("abcdef", pStr)) );
        
        eRc = pwr2Array_Get(pObj, 1, 1, &chr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (chr == 'a') );
        
        eRc = pwr2Array_Get(pObj, 3, 1, &chr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (chr == 'c') );
        
        eRc = pwr2Array_Get(pObj, 6, 1, &chr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (chr == 'f') );
        
        eRc = pwr2Array_Get(pObj, 7, 1, &chr);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = pwr2Array_Get(pObj, 6, 2, &chr);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        for (i=0; i<7; ++i) {
            chrs[i] = '\0';
        }
        
        eRc = pwr2Array_Get(pObj, 5, 2, &chrs);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == strcmp("ef", chrs)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pwr2Array_Delete01(
    const
    char        *pTestName
)
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = pwr2Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 6, "abcdef");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 6)) );
        
        eRc = pwr2Array_Delete(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (5 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("bcdef", pStr, 5)) );

        eRc = pwr2Array_Delete(pObj, 4, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (3 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("bcd", pStr, 3)) );
        
        eRc = pwr2Array_Delete(pObj, 3, 2);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_pwr2Array_CopyAssign01(
    const
    char        *pTestName
)
{
    PWR2ARRAY_DATA	*pObj = OBJ_NIL;
    PWR2ARRAY_DATA	*pOther = OBJ_NIL;
    ERESULT         eRc;
    char            *pStr;
    uint32_t        i;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = pwr2Array_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = pwr2Array_Init( pObj, 0 );           // 1 byte per element
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = pwr2Array_ElemSize(pObj);
        XCTAssertTrue( (1 == i) );
        
        eRc = pwr2Array_InsertData(pObj, 1, 6, "abcdef");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 6)) );
        
        pOther = pwr2Array_Copy(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (6 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdef", pStr, 6)) );
        
        eRc = pwr2Array_InsertData(pOther, 7, 3, "ghi");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pOther);
        XCTAssertTrue( (9 == i) );
        
        pStr = pwr2Array_Ptr(pOther,1);
        XCTAssertTrue( (0 == strncmp("abcdefghi", pStr, 9)) );
        
        eRc = pwr2Array_Assign(pOther, pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        i = pwr2Array_getSize(pObj);
        XCTAssertTrue( (9 == i) );
        
        pStr = pwr2Array_Ptr(pObj,1);
        XCTAssertTrue( (0 == strncmp("abcdefghi", pStr, 9)) );
        
        obj_Release(pOther);
        pOther = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_pwr2Array);
  TINYTEST_ADD_TEST(test_pwr2Array_CopyAssign01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pwr2Array_Delete01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pwr2Array_Get01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pwr2Array_Insert03,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pwr2Array_Insert02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pwr2Array_Insert01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_pwr2Array_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_pwr2Array);





