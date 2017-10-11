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
#include    <szTbl.h>
#include    <trace.h>
#include    <AStr_internal.h>


// Faked UTF-8 of 0x01..0x04 in 1..4 bytes
#ifdef XYZZY
static
const
char        *pString1 = "\x01\xC0\x82\xE0\x80\x83\xF8\x80\x80\x84\x00";
#endif


#ifdef XYZZY
static
const
int32_t         whiteSpace[12] = {
    ' ',
    '\f',
    '\n',
    '\r',
    '\t',
    0x0085,     // Next New Line (Paragraph break)
    0x00A0,     // no-break space
    0x200B,     // zero width space
    0x2060,     // word joiner
    0x3000,     // ideographic space
    0xFEFF,     // zero width no-break space
    0
};
#endif


#ifdef XYZZY
static
const
char        whiteSpaceA[22] = {
    ' ','\f','\n','\r','\t',
    0xC2,0x85,          // Next New Line (Paragraph break)
    0xC2,0xA0,          // no-break space
    0xE2,0x80,0x8B,     // zero width space
    0xE2,0x81,0xA0,     // word joiner
    0xE3,0x80,0x80,     // ideographic space
    0xEF,0xBB,0xBF,     // zero width no-break space
    0
};
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

    
    szTbl_SharedReset( ); 
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_AStr_OpenClose(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    int32_t     chrW;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = AStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = AStr_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
        
        eRc = AStr_AppendA( pObj, "def" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
        
        eRc = AStr_AppendCharRepeatA( pObj, 2, 'z' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (8 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdefzz", AStr_getData(pObj))) );
        
        eRc = AStr_AppendCharRepeatW( pObj, 2, 'y' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdefzzyy", AStr_getData(pObj))) );
        
        eRc = AStr_CharPutW( pObj, 2, 'x' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("axcdefzzyy", AStr_getData(pObj))) );
        
        eRc = AStr_CharPutW( pObj, 2, 'b' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdefzzyy", AStr_getData(pObj))) );
        
        eRc = AStr_Truncate( pObj, 6 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
        
        eRc = AStr_CompareA(pObj, "abcdef");
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        
        eRc = AStr_CompareA(pObj, "aaaaaa");
        XCTAssertTrue( (ERESULT_SUCCESS_GREATER_THAN == eRc) );
        
        eRc = AStr_CompareA(pObj, "zzzzzz");
        XCTAssertTrue( (ERESULT_SUCCESS_LESS_THAN == eRc) );
        
        chrW = AStr_CharGetW( pObj, 0 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (-1 == chrW) );
        
        chrW = AStr_CharGetW( pObj, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( ('a' == chrW) );
        
        chrW = AStr_CharGetW( pObj, 6 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( ('f' == chrW) );
        
        chrW = AStr_CharGetW( pObj, 7 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (-1 == chrW) );
        
        eRc = AStr_Remove( pObj, 4, 2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcf", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 4, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 1, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("bc", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 1, 2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == AStr_getLength(pObj)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_AppendBig(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    uint32_t    i = 0;
    uint32_t    iMax = 5000;
    ASTR_DATA	*pObj = OBJ_NIL;
    char        *pLower = "abcdefghijklmnopqrstuvwxyz";
    char        *pUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char        *pNumbers = "0123456789";
    ASTR_DATA   *pLowerA = OBJ_NIL;
    ASTR_DATA   *pUpperA = OBJ_NIL;
    ASTR_DATA   *pNumbersA = OBJ_NIL;
    ASTR_DATA   *pBaseA = OBJ_NIL;
    const
    char        *pChrs;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pLowerA = AStr_NewA(pLower);
    XCTAssertFalse( (OBJ_NIL == pLowerA) );
    XCTAssertTrue( (26 == AStr_getLength(pLowerA)) );
    XCTAssertTrue( (0 == strcmp(pLower, AStr_getData(pLowerA))) );
    
    pUpperA = AStr_NewA(pUpper);
    XCTAssertFalse( (OBJ_NIL == pUpperA) );
    XCTAssertTrue( (26 == AStr_getLength(pUpperA)) );
    XCTAssertTrue( (0 == strcmp(pUpper, AStr_getData(pUpperA))) );
    
    pNumbersA = AStr_NewA(pNumbers);
    XCTAssertFalse( (OBJ_NIL == pNumbersA) );
    XCTAssertTrue( (10 == AStr_getLength(pNumbersA)) );
    XCTAssertTrue( (0 == strcmp(pNumbers, AStr_getData(pNumbersA))) );
    
    pBaseA = AStr_New();
    XCTAssertFalse( (OBJ_NIL == pBaseA) );
    XCTAssertTrue( (0 == AStr_getLength(pBaseA)) );
    eRc = AStr_Append( pBaseA, pNumbersA );
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    XCTAssertTrue( (10 == AStr_getLength(pBaseA)) );
    pChrs = AStr_getData(pBaseA);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pNumbersA), pChrs, AStr_getLength(pNumbersA))) );
    eRc = AStr_Append( pBaseA, pLowerA );
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    XCTAssertTrue( (36 == AStr_getLength(pBaseA)) );
    pChrs = AStr_getData(pBaseA);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pNumbersA), pChrs, AStr_getLength(pNumbersA))) );
    pChrs = AStr_getData(pBaseA) + AStr_getLength(pNumbersA);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pLowerA), pChrs, AStr_getLength(pLowerA))) );
    eRc = AStr_Append( pBaseA, pUpperA );
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    XCTAssertTrue( (62 == AStr_getLength(pBaseA)) );
    pChrs = AStr_getData(pBaseA);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pNumbersA), pChrs, AStr_getLength(pNumbersA))) );
    pChrs = AStr_getData(pBaseA) + AStr_getLength(pNumbersA);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pLowerA), pChrs, AStr_getLength(pLowerA))) );
    pChrs = AStr_getData(pBaseA) + AStr_getLength(pNumbersA) + AStr_getLength(pLowerA);
    XCTAssertTrue( (0 == strncmp(AStr_getData(pUpperA), pChrs, AStr_getLength(pUpperA))) );

    pObj = AStr_New();
    if (pObj) {

        for (i=0; i<iMax; ++i) {
            eRc = AStr_Append( pObj, pBaseA );
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue( (((i+1) * AStr_getLength(pBaseA)) == AStr_getLength(pObj)) );
        }
        for (i=0; i<iMax; ++i) {
            pChrs = AStr_getData(pObj) + (i * AStr_getLength(pBaseA));
            XCTAssertTrue( (0 == strncmp(AStr_getData(pBaseA), pChrs, AStr_getLength(pBaseA))) );
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pBaseA);
    pBaseA = OBJ_NIL;
    obj_Release(pNumbersA);
    pNumbersA = OBJ_NIL;
    obj_Release(pUpperA);
    pUpperA = OBJ_NIL;
    obj_Release(pLowerA);
    pLowerA = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_AppendPrint01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_New();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == AStr_getLength(pObj)) );
    if (pObj) {
        
        eRc = AStr_AppendPrint(pObj, "%03d,%03d", 54, 113);
        fprintf(stderr, "pObj=%s\n",AStr_getData(pObj));
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (7 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("054,113", AStr_getData(pObj))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_AssignCopy(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    ASTR_DATA	*pOtr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("abcdef");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (6 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
    if (pObj) {
        
        pOtr = AStr_Copy( pObj );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (6 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pOtr))) );
        
        eRc = AStr_Truncate( pObj, 3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
        
        eRc = AStr_Assign(pOtr, pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
        
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_CharFindNext(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = AStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = AStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = AStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        ++index;
        eRc = AStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        ++index;
        eRc = AStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        ++index;
        eRc = AStr_CharFindNextW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_HAS_FAILED(eRc)) );
        XCTAssertTrue( (0 == index) );
        
        eRc = AStr_CharReplaceAllW(pObj, 'x', 'y');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("yABCyDEFyG", AStr_getData(pObj))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_CharFindPrev(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = AStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = AStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = AStr_CharFindPrevW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        --index;
        eRc = AStr_CharFindPrevW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        --index;
        eRc = AStr_CharFindPrevW(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_CompareRight(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("abcdefghijklmnop");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (16 == AStr_getLength(pObj)) );
    if (pObj) {
        
        //eRc = AStr_CompareRightA(pObj, NULL);
        //XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        eRc = AStr_CompareRightA(pObj, "abc");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_GREATER_THAN) );
        eRc = AStr_CompareRightA(pObj, "nop");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        eRc = AStr_CompareRightA(pObj, "xyz");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_LESS_THAN) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_File(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath = OBJ_NIL;
    ASTR_DATA	*pOther = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = AStr_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = AStr_AppendA(pObj, "/test.txt");
        
        pPath = path_NewFromAStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        if (pPath) {
            eRc = AStr_CompareA((ASTR_DATA *)pPath, "/Users/bob/test.txt");
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
            eRc = AStr_ToUtf8File(pObj, pPath);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pOther = AStr_NewFromUtf8File(pPath);
            XCTAssertFalse( (OBJ_NIL == pOther) );
            if (pOther) {
                eRc = AStr_Compare(pObj, pOther);
                XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
                obj_Release(pOther);
                pOther = OBJ_NIL;
            }
            obj_Release(pPath);
            pPath = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_Hex01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    uint16_t    num = 0xF0F0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == AStr_getLength(pObj)) );
    if (pObj) {
        
        eRc = AStr_AppendHex16(pObj, num);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("F0F0", AStr_getData(pObj))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_Hex02(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    uint32_t    num = 0xF0F0F0F0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == AStr_getLength(pObj)) );
    if (pObj) {
        
        eRc = AStr_AppendHex32(pObj, num);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        fprintf(stderr, "hex32 (%d)%s\n", AStr_getLength(pObj), AStr_getData(pObj));
        XCTAssertTrue( (8 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("F0F0F0F0", AStr_getData(pObj))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_Insert01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("def");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("def", AStr_getData(pObj))) );
    if (pObj) {
        
        eRc = AStr_InsertA( pObj, 1, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
        
        eRc = AStr_InsertA(pObj, 6, "ghi");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("abcdeghif", AStr_getData(pObj))) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_LeftMidRight(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    ASTR_DATA	*pOtr = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("abcdef");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (6 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abcdef", AStr_getData(pObj))) );
    if (pObj) {
        
        eRc = AStr_Left( pObj, 3, &pOtr );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
        eRc = AStr_Mid( pObj, 4, 2, &pOtr );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (2 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("de", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
        eRc = AStr_Right(pObj, 3, &pOtr);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pOtr) );
        XCTAssertTrue( (3 == AStr_getLength(pOtr)) );
        XCTAssertTrue( (0 == strcmp("def", AStr_getData(pOtr))) );
        obj_Release(pOtr);
        pOtr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_NewParenthesized(
    const
    char        *pTestName
)
{
    ERESULT     eRc = ERESULT_SUCCESS;
    ASTR_DATA	*pObj = OBJ_NIL;
    ASTR_DATA	*pNew = OBJ_NIL;
    char        *pWrk;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("kind:\"xyzzy\"\n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (13 == AStr_getLength(pObj)) );
    if (pObj) {
        fprintf(stderr, "pObj(%d)=%s\n", AStr_getLength(pObj), AStr_getData(pObj));
        
        pNew = AStr_NewParenthesizedFromAStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pNew) );
        if (pNew) {
            fprintf(stderr, "pNew(%d)=%s\n", AStr_getLength(pNew), AStr_getData(pNew));
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            XCTAssertTrue( (18 == AStr_getLength(pNew)) );
            pWrk = "\"kind:\\\"xyzzy\\\"\\n\"";
            fprintf(stderr, "pWrk(%lu)=%s\n", strlen(pWrk), pWrk);
            XCTAssertTrue( (0 == strcmp(pWrk, AStr_getData(pNew))) );
            obj_Release(pNew);
            pNew = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_Remove01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("def");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("def", AStr_getData(pObj))) );
    if (pObj) {
        
        eRc = AStr_Remove( pObj, 1, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("ef", AStr_getData(pObj))) );
        
        eRc = AStr_Remove( pObj, 2, 1 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == AStr_getLength(pObj)) );
        XCTAssertTrue( (0 == strcmp("e", AStr_getData(pObj))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_Trim(
    const
    char        *pTestName
)
{
    ASTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = AStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Leading Spaces
        eRc = AStr_AppendA( pObj, "   bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == AStr_getLength(pObj)) );
        
        eRc = AStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        eRc = AStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        
        // Trailing spaces
        eRc = AStr_AppendA( pObj, "   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == AStr_getLength(pObj)) );
        
        eRc = AStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        eRc = AStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        
        eRc = AStr_Truncate( pObj, 0 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == AStr_getLength(pObj)) );
        
        // Leading and Trailing spaces
        eRc = AStr_AppendA( pObj, "   bb   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (8 == AStr_getLength(pObj)) );
        
        eRc = AStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == AStr_getLength(pObj)) );
        eRc = AStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESSFUL_COMPLETION == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_ToChrCon01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA	*pObj = OBJ_NIL;
    ASTR_DATA   *pNew;
    const
    char        *pChrCon = "def\u0414\n";
    const
    char        *pChrCon2 = "def\\u0414\\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("def");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    eRc = AStr_AppendCharW(pObj, 0x0414);   // Cyrillic Capital D
    XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
    eRc = AStr_AppendCharA(pObj, '\n');
    fprintf(stderr, "inputLen=%d\n", AStr_getLength(pObj));
    XCTAssertTrue( (5 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == memcmp(pChrCon, AStr_getData(pObj), 5)) );
    if (pObj) {
        
        pNew = AStr_ToChrCon(pObj);
        XCTAssertFalse( (OBJ_NIL == pNew) );
        XCTAssertTrue( (11 == AStr_getLength(pNew)) );
        fprintf(stderr, "outputLen=%d\n", AStr_getLength(pNew));
        fprintf(stderr, "output=%s\n", AStr_getData(pNew));
        XCTAssertTrue( (0 == memcmp(pChrCon2, AStr_getData(pNew), 11)) );
        obj_Release(pNew);
        pNew = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_CRC01(
    const
    char        *pTestName
)
{
    ASTR_DATA   *pObj = OBJ_NIL;
    uint32_t    crc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
    if (pObj) {
        
        crc = AStr_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"abc\") = %u\n", crc);
        XCTAssertTrue( (2807916624 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = AStr_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("", AStr_getData(pObj))) );
    if (pObj) {
        
        crc = AStr_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"\") = %u\n", crc);
        //XCTAssertTrue( (2807916624 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_AStr_JSON01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    ASTR_DATA   *pObj = OBJ_NIL;
    uint32_t    crc;
    ASTR_DATA   *pJson = OBJ_NIL;
    ASTR_DATA   *pJsonOut = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = AStr_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pObj))) );
    if (pObj) {
        
        pJson = AStr_ToJSON(pObj);
        fprintf(stderr, "\tJSON(\"abc\") = %s\n", AStr_getData(pJson));
        eRc = AStr_NewFromJSONString(pJson, &pJsonOut);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pJsonOut) );
        XCTAssertTrue( (3 == AStr_getLength(pJsonOut)) );
        XCTAssertTrue( (0 == strcmp("abc", AStr_getData(pJsonOut))) );
        obj_Release(pJsonOut);
        pJsonOut = OBJ_NIL;
        obj_Release(pJson);
        pJson = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = AStr_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == AStr_getLength(pObj)) );
    XCTAssertTrue( (0 == strcmp("", AStr_getData(pObj))) );
    if (pObj) {
        
        pJson = AStr_ToJSON(pObj);
        fprintf(stderr, "\tJSON(\"\") = %s\n", AStr_getData(pJson));
        eRc = AStr_NewFromJSONString(pJson, &pJsonOut);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pJsonOut) );
        XCTAssertTrue( (0 == AStr_getLength(pJsonOut)) );
        XCTAssertTrue( (0 == strcmp("", AStr_getData(pJsonOut))) );
        obj_Release(pJsonOut);
        pJsonOut = OBJ_NIL;
        obj_Release(pJson);
        pJson = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_AStr);
    TINYTEST_ADD_TEST(test_AStr_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_CRC01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_ToChrCon01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_Trim,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_Remove01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_NewParenthesized,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_LeftMidRight,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_Insert01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_Hex02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_Hex01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_File,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_CompareRight,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_CharFindPrev,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_CharFindNext,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_AssignCopy,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_AppendPrint01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_AppendBig,setUp,tearDown);
    TINYTEST_ADD_TEST(test_AStr_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_AStr);





