// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 07/15/2021 16:05:13
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
#include    <test_defs.h>
#include    <trace.h>
#include    <W32Str_internal.h>
#include    <W32Array_internal.h>
#include    <JsonIn.h>
#ifdef  W32STR_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif
#include    <utf8.h>



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



int             setUp (
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


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

#ifdef  W32STR_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
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






int             test_W32Str_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    W32STR_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_W32STR);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_W32Str_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    W32STR_DATA     *pObj1 = OBJ_NIL;
    W32STR_DATA     *pObj2 = OBJ_NIL;
    bool            fRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    int             iRc;
    char            *pStrA = NULL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = W32Str_NewA("AbcDef");
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_W32STR);
        TINYTEST_TRUE( (fRc) );
        iRc = W32Str_CompareA(pObj1, "AbcDef");
        TINYTEST_TRUE( (0 == iRc) );
        TINYTEST_TRUE( (6 == W32Str_getLength(pObj1)) );

        // Test assign.
        pObj2 = W32Str_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = W32Str_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStrA = W32Str_CStringA(pObj2, NULL);
        TINYTEST_FALSE( (NULL == pStrA) );
        fprintf(stderr, "\tCStringA: \"%s\"\n", pStrA);
        mem_Free(pStrA);
        pStrA = NULL;
        TINYTEST_TRUE( (6 == W32Str_getLength(pObj2)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32STR);
        TINYTEST_TRUE( (fRc) );
        iRc = W32Str_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == iRc) );
        TINYTEST_TRUE( (W32Str_getLength(pObj1) == W32Str_getLength(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = W32Str_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32STR);
        TINYTEST_TRUE( (fRc) );
        iRc = W32Str_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == iRc) );
        TINYTEST_TRUE( (W32Str_getLength(pObj1) == W32Str_getLength(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
        pStr = W32Str_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = W32Str_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_W32STR);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        iRc = W32Str_Compare(pObj1, pObj2);
        TINYTEST_TRUE( (0 == iRc) );
        TINYTEST_TRUE( (W32Str_getLength(pObj1) == W32Str_getLength(pObj2)) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_W32Str_Test01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    W32STR_DATA     *pObj = OBJ_NIL;
    bool            fRc;
    const
    W32CHR_T        *pDataW;
    W32CHR_T        chr;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_W32STR);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        pDataW = W32Str_getData(pObj);
        XCTAssertTrue( (pDataW) );
        XCTAssertTrue( (pDataW[0] == 0) );

        eRc = W32Str_AppendA( pObj, "abc" );
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );

        chr = W32Str_CharGetW32(pObj, 2);
        XCTAssertTrue( ('b' == chr) );

        eRc = W32Str_CharPutW32(pObj, 2, 'x');
        XCTAssertTrue( (ERESULT_OK(eRc)) );

        eRc = W32Str_CompareA( pObj, "axc" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );

        eRc = W32Str_CharPutW32(pObj, 2, 0xFEFF);
        XCTAssertTrue( (ERESULT_OK(eRc)) );

        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertFalse( (ERESULT_OK(eRc)) );

        {
            ASTR_DATA       *pStr = W32Str_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_Span01 (
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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
        XCTAssertTrue( (0 == eRc) );

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



int         test_W32Str_Compare(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_CompareA(pObj, "xABCxDEFxA");
        XCTAssertTrue( (eRc > 0) );

        eRc = W32Str_CompareA(pObj, "xABCxDEFxZ");
        XCTAssertTrue( (eRc < 0) );

        eRc = W32Str_CompareA(pObj, "xABCxDEF");
        XCTAssertTrue( (eRc > 0) );

        eRc = W32Str_CompareA(pObj, "xABCxDEFxGx");
        XCTAssertTrue( (eRc < 0) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_CompareA(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_CompareA( pObj, "000" );
        XCTAssertTrue( (eRc > 0) );

        eRc = W32Str_CompareA( pObj, "def" );
        XCTAssertTrue( (eRc < 0) );

        eRc = W32Str_CompareA( pObj, "\xC0\x82" );
        XCTAssertTrue( (eRc > 0) );

        eRc = W32Str_AppendW32( pObj, 0, string2 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "abcxyz" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_Truncate(pObj, 0);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == W32Str_getLength(pObj)) );

        eRc = W32Str_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_CompareW(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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

        eRc = W32Str_CompareW32(pObj, whiteSpace, false, false);
        XCTAssertTrue( (0 == eRc) );

        pStr = W32Str_CStringA(pObj, &len);
        XCTAssertTrue( (0 == eRc) );
        XCTAssertTrue( (19 == len) );
        lenStr = utf8_StrLenA(pStr);
        XCTAssertTrue( (10 == lenStr) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;

        pObj = W32Str_NewA(pStr);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareW32(pObj, whiteSpace, false, false);
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;

        mem_Free(pStr);
        pStr = NULL;

        pObj = W32Str_NewW32(0, whiteSpace);
        XCTAssertFalse( (OBJ_NIL == pObj) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareW32(pObj, whiteSpace, false, false);
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_Compare( pObj, pObj );
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;

    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_AppendChr(
    const
    char            *pTestName
)
{
    W32STR_DATA        *pObj = OBJ_NIL;
    W32STR_DATA        *pOther = OBJ_NIL;
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
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_Upper( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "AAA" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_Lower( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "aaa" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_InsertA( pObj, 2, "bb" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "abbaa" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_InsertA( pObj, 1, "c" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "cabbaa" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_InsertA( pObj, 7, "d" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (7 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "cabbaad" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_AppendA( pObj, "eee" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (10 == W32Str_getLength(pObj)) );

        eRc = W32Str_CompareA( pObj, "cabbaadeee" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_IsOnlyASCII(pObj);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );

        pOther = W32Str_Mid(pObj, 1, 2);
        XCTAssertTrue( (2 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "ca" );
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;

        pOther = W32Str_Mid(pObj, 8, 3);
        XCTAssertTrue( (3 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "eee" );
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;

        pOther = W32Str_Left(pObj, 2);
        XCTAssertTrue( (2 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "ca" );
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;

        pOther = W32Str_Right(pObj, 3);
        XCTAssertTrue( (3 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "eee" );
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;

        eRc = W32Str_Remove(pObj, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "abbaadeee" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_Remove(pObj, 7, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "abbaad" );
        XCTAssertTrue( (0 == eRc) );

        eRc = W32Str_Remove(pObj, 4, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (4 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "abbd" );
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_Append(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
    W32STR_DATA    *pObj2 = OBJ_NIL;
    W32STR_DATA    *pObj3 = OBJ_NIL;
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
        XCTAssertTrue( (0 == W32Str_CompareA(pObj, "abc")) );

        eRc = W32Str_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (6 == W32Str_getLength(pObj)) );
        XCTAssertTrue( (0 == W32Str_CompareA(pObj, "abcdef")) );

        eRc = W32Str_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (9 == W32Str_getLength(pObj)) );
        XCTAssertTrue( (0 == W32Str_CompareA(pObj, "abcdefdef")) );

        eRc = W32Str_Truncate(pObj, 0);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (0 == W32Str_getLength(pObj)) );

        eRc = W32Str_Append( pObj, pObj3 );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (3 == W32Str_getLength(pObj)) );
        XCTAssertTrue( (0 == W32Str_CompareA(pObj, "def")) );

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



int         test_W32Str_CharFindNext(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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



int         test_W32Str_CharFindPrev(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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



int         test_W32Str_LeftRightMid(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    W32STR_DATA    *pOther = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = W32Str_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = W32Str_AppendA( pObj, "xABCxDEFxG" );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );

        pOther = W32Str_Left(pObj, 4);
        XCTAssertFalse( (OBJ_NIL == pOther) );
        XCTAssertTrue( (4 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "xABC" );
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;

        pOther = W32Str_Right(pObj, 2);
        XCTAssertFalse( (OBJ_NIL == pOther) );
        XCTAssertTrue( (2 == W32Str_getLength(pOther)) );
        eRc = W32Str_CompareA( pOther, "xG" );
        XCTAssertTrue( (0 == eRc) );
        obj_Release(pOther);
        pOther = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_NewFromEnv(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = W32Str_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (0 == eRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_File(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
    ERESULT     eRc;
    PATH_DATA   *pPath = OBJ_NIL;
    W32STR_DATA    *pOther = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewFromEnv("HOME");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = W32Str_CompareA(pObj, "/Users/bob");
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = W32Str_AppendA(pObj, "/test.txt");

        pPath = Path_NewFromW32STR(pObj);
        XCTAssertFalse( (OBJ_NIL == pPath) );
        if (pPath) {
            eRc = W32Str_ToUtf8File(pObj, pPath);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            pOther = W32Str_NewFromUtf8File(pPath);
            XCTAssertFalse( (OBJ_NIL == pOther) );
            if (pOther) {
                eRc = W32Str_Compare(pObj, pOther);
                XCTAssertTrue( (0 == eRc) );
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



int         test_W32Str_Find(
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



int         test_W32Str_Trim(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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
        XCTAssertTrue( (0 == eRc) );

        // Trailing spaces
        eRc = W32Str_AppendA( pObj, "   " );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (5 == W32Str_getLength(pObj)) );

        eRc = W32Str_Trim( pObj );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        XCTAssertTrue( (2 == W32Str_getLength(pObj)) );
        eRc = W32Str_CompareA( pObj, "bb" );
        XCTAssertTrue( (0 == eRc) );

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
        XCTAssertTrue( (0 == eRc) );

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



int         test_W32Str_EscapeForC(
    const
    char        *pTestName
)
{
    W32STR_DATA    *pObj = OBJ_NIL;
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
        XCTAssertTrue( (eRc == 0) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = W32Str_NewA("\"a\"");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = W32Str_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 5) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,W32Str_getData(pObj));
        eRc = W32Str_CompareA(pObj, "\\\"a\\\"");
        XCTAssertTrue( (eRc == 0) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = W32Str_NewA("\t\t\n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 3) );
        eRc = W32Str_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 6) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,W32Str_getData(pObj));
        eRc = W32Str_CompareA(pObj, "\\t\\t\\n");
        XCTAssertTrue( (eRc == 0) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = W32Str_NewA("\n  \n");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 4) );
        eRc = W32Str_EscapeForC(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        i = W32Str_getLength( pObj );
        XCTAssertTrue( (i == 6) );
        fprintf(stderr, "string=(%d)\"%ls\"\n",i,W32Str_getData(pObj));
        eRc = W32Str_CompareA(pObj, "\\n  \\n");
        XCTAssertTrue( (eRc == 0) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_CRC01(
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
    XCTAssertTrue( (0 == W32Str_CompareA(pObj, "abc")) );
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
    XCTAssertTrue( (0 == W32Str_CompareA(pObj, "")) );
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



int         test_W32Str_SplitOn01(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_New();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = W32Str_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == W32Array_getSize(pArray)) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitOn02(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewA("123");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = W32Str_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (1 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "123")) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitOn03(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;
    const
    char            *pTestString = "1/2/3/4/5";

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestString);
    pObj = W32Str_NewA(pTestString);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = W32Str_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", W32Array_getSize(pArray));
        XCTAssertTrue( (5 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "1")) );
        pStr = W32Array_Get(pArray, 2);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "2")) );
        pStr = W32Array_Get(pArray, 3);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "3")) );
        pStr = W32Array_Get(pArray, 4);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "4")) );
        pStr = W32Array_Get(pArray, 5);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "5")) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitOn04(
    const
    char            *pTestName
                                )
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    int             iRc;
    const
    char            *pTestString = "1/";

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestString);
    pObj = W32Str_NewA(pTestString);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = W32Str_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", W32Array_getSize(pArray));
        XCTAssertTrue( (1 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tString Length = %d\n", W32Str_getLength(pStr));
        XCTAssertTrue( (1 == W32Str_getLength(pStr)) );
        {
            W32CHR_T        chrw = W32Str_CharGetW32(pStr, 1);
            fprintf(stderr, "\tstr: %lc\n", chrw);
        }
        iRc = W32Str_CompareA(pStr, "1");
        XCTAssertTrue( (0 == iRc) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitOn05(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;
    const
    char            *pTestString = "/";

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestString);
    pObj = W32Str_NewA(pTestString);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = W32Str_SplitOnCharW32(pObj, '/');
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", W32Array_getSize(pArray));
        XCTAssertTrue( (1 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_getLength(pStr)) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_FindChars(
    const
    char        *pTestName
)
{
    W32STR_DATA *pObj = OBJ_NIL;
    ERESULT     eRc;
    const
    char        *pStr1 = "abc\tcbs\tnbc\tfox\n";
    W32CHR_T    chrs[3] = {0};
    uint32_t    offset = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewA(pStr1);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        chrs[0] = '\t';
        chrs[1] = '\n';
        offset = 0;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (4 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (8 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (12 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (16 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        chrs[0] = '\n';
        chrs[1] = '\t';
        offset = 0;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (4 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (8 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_SUCCESS == eRc) );
        XCTAssertTrue( (12 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (16 == offset) );
        offset += 1;

        eRc = W32Str_CharsFindNextW32(pObj, &offset, chrs);
        XCTAssertTrue( (ERESULT_FAILED(eRc)) );
        XCTAssertTrue( (0 == offset) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitsOn01(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;
    const
    W32CHR_T        wchrs[3] = {'/', '\n', 0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_New();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = W32Str_SplitOnCharsW32(pObj, wchrs);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (0 == W32Array_getSize(pArray)) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitsOn02(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;
    W32CHR_T        chrs[3] = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = W32Str_NewA("123");
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        chrs[0] = '/';
        pArray = W32Str_SplitOnCharsW32(pObj, chrs);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        XCTAssertTrue( (1 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "123")) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitsOn03(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;
    const
    char            *pTestString = "1/2/3/4/5";
    W32CHR_T        chrs[3] = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestString);
    pObj = W32Str_NewA(pTestString);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        chrs[0] = '/';
        pArray = W32Str_SplitOnCharsW32(pObj, chrs);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", W32Array_getSize(pArray));
        XCTAssertTrue( (5 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "1")) );
        pStr = W32Array_Get(pArray, 2);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "2")) );
        pStr = W32Array_Get(pArray, 3);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "3")) );
        pStr = W32Array_Get(pArray, 4);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "4")) );
        pStr = W32Array_Get(pArray, 5);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_CompareA(pStr, "5")) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitsOn04(
    const
    char            *pTestName
                                )
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    int             iRc;
    const
    char            *pTestString = "1/";
    W32CHR_T        chrs[3] = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestString);
    pObj = W32Str_NewA(pTestString);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        chrs[0] = '/';
        pArray = W32Str_SplitOnCharsW32(pObj, chrs);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", W32Array_getSize(pArray));
        XCTAssertTrue( (1 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        fprintf(stderr, "\tString Length = %d\n", W32Str_getLength(pStr));
        XCTAssertTrue( (1 == W32Str_getLength(pStr)) );
        {
            W32CHR_T        chrw = W32Str_CharGetW32(pStr, 1);
            fprintf(stderr, "\tstr: %lc\n", chrw);
        }
        iRc = W32Str_CompareA(pStr, "1");
        XCTAssertTrue( (0 == iRc) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_SplitsOn05(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    //ERESULT         eRc;
    W32STR_DATA     *pStr = OBJ_NIL;
    W32ARRAY_DATA   *pArray = OBJ_NIL;
    //int             len = 0;
    const
    char            *pTestString = "/";
    W32CHR_T        chrs[3] = {0};

    fprintf(stderr, "Performing: %s\n", pTestName);

    fprintf(stderr, "\tTest String: %s\n", pTestString);
    pObj = W32Str_NewA(pTestString);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        chrs[0] = '/';
        pArray = W32Str_SplitOnCharsW32(pObj, chrs);
        XCTAssertFalse( (OBJ_NIL == pArray) );
        //eRc = obj_getLastError(pObj);
        //XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        //XCTAssertTrue( (AStr_getLength(pStr) == AStr_getLength((ASTR_DATA *)pObj)) );
        fprintf(stderr, "\tArray Size = %d\n", W32Array_getSize(pArray));
        XCTAssertTrue( (1 == W32Array_getSize(pArray)) );
        pStr = W32Array_Get(pArray, 1);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        XCTAssertTrue( (0 == W32Str_getLength(pStr)) );

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pStr);
    pStr = NULL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_W32Str_RemoveNL01(
    const
    char            *pTestName
)
{
    W32STR_DATA     *pObj = OBJ_NIL;
    ERESULT         eRc;
    int             iRc = 0;
    const
    char            *pTestString = "abc\ndef\r\r\r\n\r\n";

    fprintf(stderr, "Performing: %s\n", pTestName);

    //fprintf(stderr, "\tTest String: %s\n", pTestString);
    pObj = W32Str_NewA(pTestString);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = W32Str_RemoveNL(pObj);
        XCTAssertTrue( (ERESULT_OK(eRc)) );
        XCTAssertTrue( (7 == W32Str_getLength(pObj)) );
        iRc = W32Str_CompareA(pObj, "abc\ndef");
        XCTAssertTrue( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_W32Str);
    TINYTEST_ADD_TEST(test_W32Str_RemoveNL01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitsOn05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitsOn04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitsOn03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitsOn02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitsOn01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_FindChars,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitOn05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitOn04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitOn03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitOn02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_SplitOn01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_CRC01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_EscapeForC,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_Trim,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_Find,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_File,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_NewFromEnv,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_LeftRightMid,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_CharFindPrev,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_CharFindNext,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_Append,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_AppendChr,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_CompareW,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_CompareA,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_Compare,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_Span01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_W32Str_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_W32Str);





