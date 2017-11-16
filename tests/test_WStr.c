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
#include    <utf8.h>
#include    <WStr_internal.h>



// Faked UTF-8 of 0x01..0x04 in 1..4 bytes
#ifdef XYZZY
static
const
char            *pString1 = "\x01\xC0\x82\xE0\x80\x83\xF8\x80\x80\x84\x00";
#endif

// WStr of "xyz"
static
const
int32_t         string2[4] = { 'x', 'y', 'z', 0 };


static
const
int32_t         whiteSpace[11] = {
    ' ',
    '\f',
    '\n',
    '\r',
    '\t',
    0x00A0,     // no-break space
    0x200B,     // zero width space
    0x2060,     // word joiner
    0x3000,     // ideographic space
    0xFEFF,     // zero width no-break space
    0
};



#ifdef XYZZY
static
const
char        whiteSpaceA[20] = {
    ' ','\f','\n','\r','\t',
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
    mem_Release( );
    
    return 1; 
}






int         test_wstr_OpenClose(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData;
    int32_t     chr;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 0) );
        
        eRc = WStr_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)) );
        
        chr = WStr_CharGetW32(pObj, 2);
        XCTAssertTrue( ('b' == chr) );
        
        eRc = WStr_CharPutW32(pObj, 2, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA( pObj, "axc" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CharPutW32(pObj, 2, 0xFEFF);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_Span(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index = 0;
    int32_t     scanStr[4] = {'x','y','z',0};
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCyDEFzGHI" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (12 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "xABCyDEFzGHI" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        ++index;
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        ++index;
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        ++index;
        eRc = WStr_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_OUT_OF_RANGE == eRc) );
        XCTAssertTrue( (0 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_AssignCopy(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    WSTR_DATA	*pOther = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData1;
    const
    int32_t     *pData2;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "abcdefghi" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == WStr_getLength(pObj)) );
        
        pOther = WStr_Copy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        
        eRc = WStr_CompareA( pObj, "abcdefghi" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Compare( pOther, pObj );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        pData1 = WStr_getData(pObj);
        pData2 = WStr_getData(pOther);
        XCTAssertTrue( (!(pData1 == pData2)) );
        
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_Compare(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA(pObj, "xABCxDEFxG");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA(pObj, "xABCxDEFxA");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_GREATER_THAN) );

        eRc = WStr_CompareA(pObj, "xABCxDEFxZ");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_LESS_THAN) );
        
        eRc = WStr_CompareA(pObj, "xABCxDEF");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_GREATER_THAN) );
        
        eRc = WStr_CompareA(pObj, "xABCxDEFxGx");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_LESS_THAN) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_CompareA(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 0) );
        
        eRc = WStr_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)) );
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 'a') );
        XCTAssertTrue( (pData[1] == 'b') );
        XCTAssertTrue( (pData[2] == 'c') );
        XCTAssertTrue( (pData[3] == 0) );
        
        eRc = WStr_CompareA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_CompareA( pObj, "000" );
        XCTAssertTrue( (ERESULT_SUCCESS_GREATER_THAN == eRc) );
        
        eRc = WStr_CompareA( pObj, "def" );
        XCTAssertTrue( (ERESULT_SUCCESS_LESS_THAN == eRc) );
        
        eRc = WStr_CompareA( pObj, "\xC0\x82" );
        XCTAssertTrue( (ERESULT_SUCCESS_GREATER_THAN == eRc) );
        
        eRc = WStr_AppendW32( pObj, 0, string2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "abcxyz" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Truncate(pObj, 0);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == WStr_getLength(pObj)) );
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_CompareW(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    int32_t     *pData;
    char        *pStr = NULL;
    uint32_t    lenStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 0) );
        
        eRc = WStr_AppendW32( pObj, 10, whiteSpace );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );
        
        pData = WStr_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == ' ') );
        XCTAssertTrue( (pData[1] == '\f') );
        XCTAssertTrue( (pData[2] == '\n') );
        XCTAssertTrue( (pData[3] == '\r') );
        XCTAssertTrue( (pData[4] == '\t') );
        XCTAssertTrue( (pData[5] == 0xA0) );
        XCTAssertTrue( (pData[6] == 0x200B) );
        XCTAssertTrue( (pData[7] == 0x2060) );
        XCTAssertTrue( (pData[8] == 0x3000) );
        XCTAssertTrue( (pData[9] == 0xFEFF) );
        XCTAssertTrue( (pData[10] == 0) );
        
        eRc = WStr_CompareW32( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pStr = WStr_CStringA(pObj, &len);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (19 == len) );
        lenStr = utf8_StrLenA(pStr);
        XCTAssertTrue( (10 == lenStr) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;

        pObj = WStr_NewA(pStr);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );

        eRc = WStr_CompareW32( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
        mem_Free(pStr);
        pStr = NULL;

        pObj = WStr_NewW32(0, whiteSpace);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareW32( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Compare( pObj, pObj );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_AppendChr(
    const
    char            *pTestName
)
{
    WSTR_DATA	    *pObj = OBJ_NIL;
    WSTR_DATA	    *pOther = OBJ_NIL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_AppendCharW32( pObj, 3, 'a' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)) );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_CompareA( pObj, "aaa" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Upper( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "AAA" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Lower( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "aaa" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_InsertA( pObj, 2, "bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "abbaa" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_InsertA( pObj, 1, "c" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "cabbaa" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_InsertA( pObj, 7, "d" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (7 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "cabbaad" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_AppendA( pObj, "eee" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == WStr_getLength(pObj)) );
        
        eRc = WStr_CompareA( pObj, "cabbaadeee" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
       
        eRc = WStr_Mid(pObj, 1, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pOther)) );
        eRc = WStr_CompareA( pOther, "ca" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Mid(pObj, 8, 3, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pOther)) );
        eRc = WStr_CompareA( pOther, "eee" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Left(pObj, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pOther)) );
        eRc = WStr_CompareA( pOther, "ca" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Right(pObj, 3, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pOther)) );
        eRc = WStr_CompareA( pOther, "eee" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Remove(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == WStr_getLength(pObj)) );
        eRc = WStr_CompareA( pObj, "abbaadeee" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Remove(pObj, 7, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)) );
        eRc = WStr_CompareA( pObj, "abbaad" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Remove(pObj, 4, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == WStr_getLength(pObj)) );
        eRc = WStr_CompareA( pObj, "abbd" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_Append(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    WSTR_DATA	*pObj2 = OBJ_NIL;
    WSTR_DATA	*pObj3 = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj2 = WStr_NewA("abc");
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        pObj3 = WStr_NewA("def");
        XCTAssertFalse( (OBJ_NIL == pObj3) );
        
        eRc = WStr_Append( pObj, pObj2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == WStr_getLength(pObj)) );
        XCTAssertTrue( (0 == wcscmp(L"abc",WStr_getData(pObj))) );
        
        eRc = WStr_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == WStr_getLength(pObj)) );
        XCTAssertTrue( (0 == wcscmp(L"abcdef",WStr_getData(pObj))) );
        
        obj_Release(pObj3);
        pObj3 = OBJ_NIL;
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_CharFindNext(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = WStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        ++index;
        eRc = WStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        ++index;
        eRc = WStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        ++index;
        eRc = WStr_CharFindNextW32(pObj, &index, 'x');
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_CharFindPrev(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = WStr_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        --index;
        eRc = WStr_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        --index;
        eRc = WStr_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_LeftRightMid(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    WSTR_DATA	*pOther = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = WStr_Left(pObj, 4, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == WStr_getLength(pOther)) );
        eRc = WStr_CompareA( pOther, "xABC" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = WStr_Right(pObj, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pOther)) );
        eRc = WStr_CompareA( pOther, "xG" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_NewFromEnv(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_File(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath = OBJ_NIL;
    WSTR_DATA	*pOther = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = WStr_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = WStr_AppendA(pObj, "/test.txt");
        
        pPath = path_NewFromWStr(pObj);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        if (pPath) {
            eRc = WStr_ToUtf8File(pObj, pPath);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pOther = WStr_NewFromUtf8File(pPath);
            XCTAssertFalse( (OBJ_NIL == pOther) );
            if (pOther) {
                eRc = WStr_Compare(pObj, pOther);
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



int         test_wstr_Trim(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = WStr_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Leading Spaces
        eRc = WStr_AppendA( pObj, "   bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == WStr_getLength(pObj)) );
        
        eRc = WStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pObj)) );
        eRc = WStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        // Trailing spaces
        eRc = WStr_AppendA( pObj, "   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == WStr_getLength(pObj)) );
        
        eRc = WStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pObj)) );
        eRc = WStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        eRc = WStr_Truncate( pObj, 0 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == WStr_getLength(pObj)) );

        // Leading and Trailing spaces
        eRc = WStr_AppendA( pObj, "   bb   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (8 == WStr_getLength(pObj)) );
        
        eRc = WStr_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == WStr_getLength(pObj)) );
        eRc = WStr_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_wstr_EscapeForC(
    const
    char        *pTestName
)
{
    WSTR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i;
    W32CHR_T    chrW32;
    const
    W32CHR_T    *pChrW32 = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = WStr_NewA("\\");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 1) );
        chrW32 = WStr_CharGetW32(pObj, 1);
        XCTAssertTrue( (chrW32 == '\\') );
        pChrW32 = WStr_getData(pObj);
        XCTAssertTrue( (*pChrW32 == '\\') );
        XCTAssertTrue( (*(pChrW32+1) == 0) );
        eRc = WStr_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 2) );
        chrW32 = WStr_CharGetW32(pObj, 1);
        XCTAssertTrue( (chrW32 == '\\') );
        chrW32 = WStr_CharGetW32(pObj, 2);
        XCTAssertTrue( (chrW32 == '\\') );
        pChrW32 = WStr_getData(pObj);
        XCTAssertTrue( (*pChrW32 == '\\') );
        XCTAssertTrue( (*(pChrW32+1) == '\\') );
        XCTAssertTrue( (*(pChrW32+2) == '\0') );
        //fprintf(stderr, "string=(%d)\"%ls\"\n", i, WStr_getData(pObj) );
        eRc = WStr_CompareA(pObj, "\\\\");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = WStr_NewA("\"a\"");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = WStr_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 5) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,WStr_getData(pObj));
        eRc = WStr_CompareA(pObj, "\\\"a\\\"");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = WStr_NewA("\t\t\n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = WStr_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 6) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,WStr_getData(pObj));
        eRc = WStr_CompareA(pObj, "\\t\\t\\n");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = WStr_NewA("\n  \n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 4) );
        eRc = WStr_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = WStr_getLength( pObj );
        XCTAssertTrue( (i == 6) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,WStr_getData(pObj));
        eRc = WStr_CompareA(pObj, "\\n  \\n");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_WStr_CRC01(
    const
    char        *pTestName
)
{
    WSTR_DATA   *pObj = OBJ_NIL;
    uint32_t    crc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = WStr_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == WStr_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStr_CompareA(pObj, "abc")) );
    if (pObj) {
        
        crc = WStr_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"abc\") = %u\n", crc);
        XCTAssertTrue( (3785294476 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = WStr_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == WStr_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStr_CompareA(pObj, "")) );
    if (pObj) {
        
        crc = WStr_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"\") = %u\n", crc);
        //XCTAssertTrue( (2807916624 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_WStr_JSON01(
    const
    char        *pTestName
)
{
    ERESULT     eRc;
    WSTR_DATA   *pObj = OBJ_NIL;
    //uint32_t    crc;
    ASTR_DATA   *pJson = OBJ_NIL;
    WSTR_DATA   *pJsonOut = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = WStr_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == WStr_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStr_CompareA(pObj, "abc")) );
    if (pObj) {
        
        pJson = WStr_ToJSON(pObj);
        fprintf(stderr, "\tJSON(\"abc\") = %s\n", AStr_getData(pJson));
        eRc = WStr_NewFromJSONString(pJson, &pJsonOut);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        if (pJsonOut) {
            XCTAssertFalse( (OBJ_NIL == pJsonOut) );
            XCTAssertTrue( (3 == WStr_getLength(pJsonOut)) );
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStr_CompareA(pJsonOut, "abc")) );
            obj_Release(pJsonOut);
            pJsonOut = OBJ_NIL;
        }
        obj_Release(pJson);
        pJson = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = WStr_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == WStr_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStr_CompareA(pObj, "")) );
    if (pObj) {
        
        pJson = WStr_ToJSON(pObj);
        fprintf(stderr, "\tJSON(\"\") = %s\n", AStr_getData(pJson));
        eRc = WStr_NewFromJSONString(pJson, &pJsonOut);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pJsonOut) );
        if (pJsonOut) {
            XCTAssertTrue( (0 == WStr_getLength(pJsonOut)) );
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == WStr_CompareA(pJsonOut, "")) );
            obj_Release(pJsonOut);
            pJsonOut = OBJ_NIL;
        }
        obj_Release(pJson);
        pJson = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_wstr);
    TINYTEST_ADD_TEST(test_WStr_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_WStr_CRC01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_EscapeForC,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_Trim,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_File,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_NewFromEnv,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_LeftRightMid,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_CharFindPrev,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_CharFindNext,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_Append,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_AppendChr,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_CompareW,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_CompareA,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_Compare,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_AssignCopy,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_Span,setUp,tearDown);
    TINYTEST_ADD_TEST(test_wstr_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_wstr);





