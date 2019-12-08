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
#include    <srcErrors.h>
#include    <utf8.h>
#include    <W32Str_internal.h>



// Faked UTF-8 of 0x01..0x04 in 1..4 bytes
#ifdef XYZZY
static
const
char            *pString1 = "\x01\xC0\x82\xE0\x80\x83\xF8\x80\x80\x84\x00";
#endif

// WStr of "xyz"
static
const
W32CHR_T        string2[4] = { 'x', 'y', 'z', 0 };


static
const
W32CHR_T        whiteSpace[11] = {
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

    srcErrors_SharedReset( ); 
    szTbl_SharedReset( );
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






int         test_w32str_OpenClose(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    W32CHR_T    *pData;
    W32CHR_T    chr;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pData = W32Str_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 0) );
        
        eRc = W32Str_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        
        chr = W32Str_CharGetW32(pObj, 2);
        XCTAssertTrue( ('b' == chr) );
        
        eRc = W32Str_CharPutW32(pObj, 2, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = W32Str_CompareA( pObj, "axc" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = W32Str_CharPutW32(pObj, 2, 0xFEFF);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_Span(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index = 0;
    W32CHR_T    scanStr[4] = {'x','y','z',0};
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_AppendA( pObj, "xABCyDEFzGHI" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (12 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "xABCyDEFzGHI" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        ++index;
        eRc = W32Str_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        ++index;
        eRc = W32Str_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        ++index;
        eRc = W32Str_IndexUntil(pObj, scanStr, &index);
        XCTAssertTrue( (ERESULT_OUT_OF_RANGE == eRc) );
        XCTAssertTrue( (0 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_AssignCopy(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    W32STR_DATA	*pOther = OBJ_NIL;
    ERESULT     eRc;
    const
    W32CHR_T    *pData1;
    const
    W32CHR_T    *pData2;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_AppendA( pObj, "abcdefghi" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == W32Str_getLength(pObj)) );
        
        pOther = W32Str_Copy(pObj);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        
        eRc = W32Str_CompareA( pObj, "abcdefghi" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Compare( pOther, pObj );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        pData1 = W32Str_getData(pObj);
        pData2 = W32Str_getData(pOther);
        XCTAssertTrue( (!(pData1 == pData2)) );
        
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_Compare(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = W32Str_CompareA(pObj, "xABCxDEFxG");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_CompareA(pObj, "xABCxDEFxA");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_GREATER_THAN) );

        eRc = W32Str_CompareA(pObj, "xABCxDEFxZ");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_LESS_THAN) );
        
        eRc = W32Str_CompareA(pObj, "xABCxDEF");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_GREATER_THAN) );
        
        eRc = W32Str_CompareA(pObj, "xABCxDEFxGx");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_LESS_THAN) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_CompareA(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    W32CHR_T    *pData;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = W32Str_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 0) );
        
        eRc = W32Str_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        
        pData = W32Str_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 'a') );
        XCTAssertTrue( (pData[1] == 'b') );
        XCTAssertTrue( (pData[2] == 'c') );
        XCTAssertTrue( (pData[3] == 0) );
        
        eRc = W32Str_CompareA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_CompareA( pObj, "000" );
        XCTAssertTrue( (ERESULT_SUCCESS_GREATER_THAN == eRc) );
        
        eRc = W32Str_CompareA( pObj, "def" );
        XCTAssertTrue( (ERESULT_SUCCESS_LESS_THAN == eRc) );
        
        eRc = W32Str_CompareA( pObj, "\xC0\x82" );
        XCTAssertTrue( (ERESULT_SUCCESS_GREATER_THAN == eRc) );
        
        eRc = W32Str_AppendW32( pObj, 0, string2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "abcxyz" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Truncate(pObj, 0);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_CompareW(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    W32CHR_T    *pData;
    char        *pStr = NULL;
    uint32_t    lenStr;
    uint32_t    len;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pData = W32Str_getData(pObj);
        XCTAssertTrue( (pData) );
        XCTAssertTrue( (pData[0] == 0) );
        
        eRc = W32Str_AppendW32( pObj, 10, whiteSpace );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );
        
        pData = W32Str_getData(pObj);
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
        
        eRc = W32Str_CompareW32( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        pStr = W32Str_CStringA(pObj, &len);
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        XCTAssertTrue( (19 == len) );
        lenStr = utf8_StrLenA(pStr);
        XCTAssertTrue( (10 == lenStr) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;

        pObj = W32Str_NewA(pStr);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareW32( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
        mem_Free(pStr);
        pStr = NULL;

        pObj = W32Str_NewW32(0, whiteSpace);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareW32( pObj, whiteSpace );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Compare( pObj, pObj );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_AppendChr(
    const
    char            *pTestName
)
{
    W32STR_DATA	    *pObj = OBJ_NIL;
    W32STR_DATA	    *pOther = OBJ_NIL;
    ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_New( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_AppendCharW32( pObj, 3, 'a' );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = W32Str_CompareA( pObj, "aaa" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Upper( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "AAA" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Lower( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "aaa" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_InsertA( pObj, 2, "bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "abbaa" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_InsertA( pObj, 1, "c" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "cabbaa" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_InsertA( pObj, 7, "d" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (7 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "cabbaad" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_AppendA( pObj, "eee" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_CompareA( pObj, "cabbaadeee" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
       
        eRc = W32Str_Mid(pObj, 1, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "ca" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = W32Str_Mid(pObj, 8, 3, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "eee" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = W32Str_Left(pObj, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "ca" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = W32Str_Right(pObj, 3, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "eee" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = W32Str_Remove(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "abbaadeee" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Remove(pObj, 7, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "abbaad" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Remove(pObj, 4, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "abbd" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_Append(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    W32STR_DATA	*pObj2 = OBJ_NIL;
    W32STR_DATA	*pObj3 = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj2 = W32Str_NewA("abc");
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        pObj3 = W32Str_NewA("def");
        XCTAssertFalse( (OBJ_NIL == pObj3) );
        
        eRc = W32Str_Append( pObj, pObj2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "abc")) );
        
        eRc = W32Str_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "abcdef")) );
        
        eRc = W32Str_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == W32Str_getLength(pObj)) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "abcdefdef")) );
        
        eRc = W32Str_Truncate(pObj, 0);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "def")) );

        obj_Release(pObj3);
        pObj3 = OBJ_NIL;
        
        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_CharFindNext(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = W32Str_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = W32Str_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        ++index;
        eRc = W32Str_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        ++index;
        eRc = W32Str_CharFindNextW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        ++index;
        eRc = W32Str_CharFindNextW32(pObj, &index, 'x');
        XCTAssertFalse( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_CharFindPrev(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    index;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        index = 0;      // Start at the beginning.
        eRc = W32Str_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == index) );
        
        --index;
        eRc = W32Str_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == index) );
        
        --index;
        eRc = W32Str_CharFindPrevW32(pObj, &index, 'x');
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (1 == index) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_LeftRightMid(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    W32STR_DATA	*pOther = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        
        eRc = W32Str_Left(pObj, 4, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "xABC" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        eRc = W32Str_Right(pObj, 2, &pOther);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "xG" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_NewFromEnv(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_File(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath = OBJ_NIL;
    W32STR_DATA	*pOther = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = W32Str_AppendA(pObj, "/test.txt");
        
        pPath = path_NewFromW32STR(pObj);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        if (pPath) {
            eRc = W32Str_ToUtf8File(pObj, pPath);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pOther = W32Str_NewFromUtf8File(pPath);
            XCTAssertFalse( (OBJ_NIL == pOther) );
            if (pOther) {
                eRc = W32Str_Compare(pObj, pOther);
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
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_Find(
    const
    char        *pTestName
)
{
    W32STR_DATA *pObj = OBJ_NIL;
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

    pObj = W32Str_NewA(pStr1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = W32Str_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = W32Str_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = W32Str_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenW32(szSrchW32);

        eRc = W32Str_FindNextW32(pObj, szSrchW32, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        eRc = W32Str_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (1 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = W32Str_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (5 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = W32Str_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (9 == offset) );
        offset += utf8_StrLenA(pSrchA);

        eRc = W32Str_FindNextA(pObj, pSrchA, &offset);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_Trim(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    W32CHR_T    chrW32 = 'x';
    
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        // Leading Spaces
        eRc = W32Str_AppendA( pObj, "   bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        // Trailing spaces
        eRc = W32Str_AppendA( pObj, "   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Truncate( pObj, 0 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == W32Str_getLength(pObj)) );

        // Leading and Trailing spaces
        eRc = W32Str_AppendA( pObj, "   bb   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (8 == W32Str_getLength(pObj)) );
        
        eRc = W32Str_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "bb" );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        
        eRc = W32Str_Truncate(pObj, 0);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        eRc = array_Get((ARRAY_DATA *)pObj, 1, 1, &chrW32);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (0 == chrW32) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_EscapeForC(
    const
    char        *pTestName
)
{
    W32STR_DATA	*pObj = OBJ_NIL;
    ERESULT     eRc;
    uint32_t    i;
    W32CHR_T    chrW32;
    const
    W32CHR_T    *pChrW32 = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewA("\\");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 1) );
        chrW32 = W32Str_CharGetW32(pObj, 1);
        XCTAssertTrue( (chrW32 == '\\') );
        pChrW32 = W32Str_getData(pObj);
        XCTAssertTrue( (*pChrW32 == '\\') );
        XCTAssertTrue( (*(pChrW32+1) == 0) );
        eRc = W32Str_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 2) );
        chrW32 = W32Str_CharGetW32(pObj, 1);
        XCTAssertTrue( (chrW32 == '\\') );
        chrW32 = W32Str_CharGetW32(pObj, 2);
        XCTAssertTrue( (chrW32 == '\\') );
        pChrW32 = W32Str_getData(pObj);
        XCTAssertTrue( (*pChrW32 == '\\') );
        XCTAssertTrue( (*(pChrW32+1) == '\\') );
        XCTAssertTrue( (*(pChrW32+2) == '\0') );
        //fprintf(stderr, "string=(%d)\"%ls\"\n", i, W32Str_getData(pObj) );
        eRc = W32Str_CompareA(pObj, "\\\\");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = W32Str_NewA("\"a\"");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = W32Str_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 5) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,W32Str_getData(pObj));
        eRc = W32Str_CompareA(pObj, "\\\"a\\\"");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = W32Str_NewA("\t\t\n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = W32Str_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 6) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,W32Str_getData(pObj));
        eRc = W32Str_CompareA(pObj, "\\t\\t\\n");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = W32Str_NewA("\n  \n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 4) );
        eRc = W32Str_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 6) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,W32Str_getData(pObj));
        eRc = W32Str_CompareA(pObj, "\\n  \\n");
        XCTAssertTrue( (eRc == ERESULT_SUCCESS_EQUAL) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_CRC01(
    const
    char        *pTestName
)
{
    W32STR_DATA   *pObj = OBJ_NIL;
    uint32_t    crc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = W32Str_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "abc")) );
    if (pObj) {
        
        crc = W32Str_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"abc\") = %u\n", crc);
        XCTAssertTrue( (3785294476 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = W32Str_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == W32Str_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "")) );
    if (pObj) {
        
        crc = W32Str_getCrcIEEE(pObj);
        fprintf(stderr, "\tcrc(\"\") = %u\n", crc);
        //XCTAssertTrue( (2807916624 == crc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_w32str_JSON01(
    const
    char        *pTestName
)
{
    ERESULT     eRc = ERESULT_SUCCESS;
    W32STR_DATA *pObj = OBJ_NIL;
    //uint32_t    crc;
    ASTR_DATA   *pJson = OBJ_NIL;
    W32STR_DATA *pJsonOut = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = W32Str_NewA("abc");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "abc")) );
    if (pObj) {
        
        pJson = W32Str_ToJSON(pObj);
        fprintf(stderr, "\tJSON(\"abc\") = %s\n", AStr_getData(pJson));
        pJsonOut = W32Str_NewFromJSONString(pJson);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        if (pJsonOut) {
            XCTAssertFalse( (OBJ_NIL == pJsonOut) );
            XCTAssertTrue( (3 == W32Str_getLength(pJsonOut)) );
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pJsonOut, "abc")) );
            obj_Release(pJsonOut);
            pJsonOut = OBJ_NIL;
        }
        obj_Release(pJson);
        pJson = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    pObj = W32Str_NewA("");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    XCTAssertTrue( (0 == W32Str_getLength(pObj)) );
    XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pObj, "")) );
    if (pObj) {
        
        pJson = W32Str_ToJSON(pObj);
        fprintf(stderr, "\tJSON(\"\") = %s\n", AStr_getData(pJson));
        pJsonOut = W32Str_NewFromJSONString(pJson);
        XCTAssertFalse( (ERESULT_FAILED(eRc)) );
        XCTAssertFalse( (OBJ_NIL == pJsonOut) );
        if (pJsonOut) {
            XCTAssertTrue( (0 == W32Str_getLength(pJsonOut)) );
            XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == W32Str_CompareA(pJsonOut, "")) );
            obj_Release(pJsonOut);
            pJsonOut = OBJ_NIL;
        }
        obj_Release(pJson);
        pJson = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_w32str);
    TINYTEST_ADD_TEST(test_w32str_JSON01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_CRC01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_EscapeForC,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_Trim,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_Find,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_File,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_NewFromEnv,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_LeftRightMid,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_CharFindPrev,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_CharFindNext,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_Append,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_AppendChr,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_CompareW,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_CompareA,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_Compare,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_AssignCopy,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_Span,setUp,tearDown);
    TINYTEST_ADD_TEST(test_w32str_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_w32str);





