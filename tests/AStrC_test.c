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
#include    <JsonIn.h>
#include    <trace.h>
#include    <AStrC_internal.h>



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






int         test_AStrC_OpenClose(
    const
    char        *pTestName
)
{
    ASTRC_DATA	*pObj = OBJ_NIL;
    ASTRC_DATA	*pCopy = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrC_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = AStrC_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pCopy = AStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrC_NewA(
    const
    char        *pTestName
)
{
    ASTRC_DATA	*pObj = OBJ_NIL;
    ASTRC_DATA	*pCopy = OBJ_NIL;
    const
    char        *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
  
    pObj = AStrC_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = AStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pObj);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        pCopy = AStrC_Copy(pObj);
        XCTAssertTrue( (pCopy == pObj) );
        XCTAssertTrue( (2 == obj_getRetainCount(pObj)) );
        len = AStrC_getLength(pCopy);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pCopy);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        obj_Release(pCopy);
        pCopy = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrC_Append01(
    const
    char        *pTestName
)
{
    ASTRC_DATA  *pObj = OBJ_NIL;
    ASTRC_DATA  *pObj2 = OBJ_NIL;
    const
    char        *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrC_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = AStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pObj);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        pObj2 = AStrC_AppendA(pObj, "def");
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        len = AStrC_getLength(pObj2);
        XCTAssertTrue( (6 == len) );
        pStr = AStrC_getData(pObj2);
        XCTAssertTrue( (0 == strcmp(pStr, "abcdef")) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrC_Append02(
    const
    char        *pTestName
)
{
    ASTRC_DATA  *pObj = OBJ_NIL;
    ASTRC_DATA  *pObj2 = OBJ_NIL;
    ASTRC_DATA  *pObj3 = OBJ_NIL;
    const
    char        *pStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrC_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        len = AStrC_getLength(pObj);
        //fprintf(stderr, "len=%d\n",len);
        XCTAssertTrue( (3 == len) );
        pStr = AStrC_getData(pObj);
        XCTAssertTrue( (0 == strcmp(pStr, "abc")) );
        pObj2 = AStrC_NewA("def");
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        if (pObj2) {
            len = AStrC_getLength(pObj2);
            XCTAssertTrue( (3 == len) );
            pStr = AStrC_getData(pObj2);
            XCTAssertTrue( (0 == strcmp(pStr, "def")) );
            
            pObj3 = AStrC_Append(pObj, pObj2);
            XCTAssertFalse( (OBJ_NIL == pObj3) );
            len = AStrC_getLength(pObj3);
            XCTAssertTrue( (6 == len) );
            pStr = AStrC_getData(pObj3);
            XCTAssertTrue( (0 == strcmp(pStr, "abcdef")) );
            obj_Release(pObj3);
            pObj3 = OBJ_NIL;
        }
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrC_LeftMidRight(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTRC_DATA  *pObj = OBJ_NIL;
    ASTRC_DATA  *pOtr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStrC_NewA("abcdef");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (6 == AStrC_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abcdef", AStrC_getData(pObj))) );
    if (pObj) {

#ifdef XYZZY
        eRc = AStrC_Left( pObj, 3, &pOtr );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStrC_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("abc", AStrC_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
#endif
        
        fprintf(stderr, "\tThis will cause a breakpoint, just continue on.\n");
        pOtr = AStrC_Mid(OBJ_NIL, 4, 2);
        XCTAssertTrue( (OBJ_NIL == pOtr) );
        
        pOtr = AStrC_Mid(pObj, 4, 2);
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (2 == AStrC_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("de", AStrC_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
#ifdef XYZZY
        eRc = AStr_Right(pObj, 3, &pOtr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("def", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
#endif

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStrC_Find(
    const
    char        *pTestName
)
{
    ASTRC_DATA  *pObj = OBJ_NIL;
    ERESULT     eRc;
    //                             1111111111222222222
    //                    1234567890123456789012345678
    const
    char        *pStr1 = "isa isa isa";
    const
    W32CHR_T    szSrchW32[] = {'i','s','a',0};
    const
    char        *pSrchA = "isa";
    uint32_t    offset = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_NewA(pStr1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = AStrC_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStrC_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStrC_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = AStrC_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        eRc = AStrC_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStrC_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStrC_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = AStrC_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_AStrC_Prepend(
    const
    char        *pTestName
)
{
    ASTRC_DATA  *pObj   = OBJ_NIL;
    ASTRC_DATA  *pObj2  = OBJ_NIL;
    ERESULT     eRc;
    W32CHR_T    chrW32;
    //                             1111111111222222222
    //                    1234567890123456789012345678
    const
    char        *pStr1 = "isa";
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = AStrC_NewA(pStr1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj2 = AStrC_PrependA(pObj, "xyz");
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        fprintf(stderr, "obj2 -> %s\n", AStrC_getData(pObj2));
        eRc = AStrC_CompareA(pObj2, "xyzisa");
        XCTAssertTrue( (0 == eRc) );
        chrW32 = AStrC_CharGetFirstW32(pObj2);
        XCTAssertTrue( ('x' == chrW32) );
        chrW32 = AStrC_CharGetLastW32(pObj2);
        XCTAssertTrue( ('a' == chrW32) );
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_AStrC);
    TINYTEST_ADD_TEST(test_AStrC_Prepend,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrC_Find,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrC_LeftMidRight,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrC_Append02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrC_Append01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrC_NewA,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStrC_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AStrC);





