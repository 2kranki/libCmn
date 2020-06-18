// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 06/06/2020 10:44:03
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
#include    <SrcFile_internal.h>
#include    <SrcErrors.h>
#include    <szTbl.h>



static
const
char        *pFilePath = "${HOME}/git/libCmn/tests/files/test_objects.json.txt";
// Currently 853 bytes


static
char        *pTest01 =  "class abc {\n"
                            "\tint a;\n"
                            "\tchar\t\txyzzy(void);\n"
                        "}\n";


static
char        *pTest02 =  "\xC2\xA0" "class" "\xE2\x81\xA0" "abc;\n";



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

    SrcErrors_SharedReset( );
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






int             test_SrcFile_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SRCFILE_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcFile_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SrcFile_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SrcFile_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    SRCFILE_DATA       *pObj1 = OBJ_NIL;
    SRCFILE_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(SRCFILE_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = SrcFile_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_SRCFILE);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = SrcFile_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = SrcFile_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILE);
        TINYTEST_TRUE( (fRc) );
        //eRc = SrcFile_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = SrcFile_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILE);
        TINYTEST_TRUE( (fRc) );
        //eRc = SrcFile_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(SRCFILE_JSON_SUPPORT) && defined(XYZZY)
        pStr = SrcFile_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = SrcFile_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_SRCFILE);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = SrcFile_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_SrcFile_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    SRCFILE_DATA    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcFile_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_SRCFILE);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );
        
        {
            ASTR_DATA       *pStr = SrcFile_ToDebugString(pObj, 4);
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



int                 test_SrcFile_General01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    SRCFILE_DATA    *pObj = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    PATH_DATA       *pPath = Path_NewA("abc");
    TOKEN_DATA      *pToken;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pBuf = AStr_NewA(pTest01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pObj = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
        XCTAssertFalse( (OBJ_NIL == pObj) );

        pToken = SrcFile_InputLookAhead(pObj, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ('c' == Token_getChrW32(pToken)) );
        pToken = SrcFile_InputLookAhead(pObj, 2);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ('l' == Token_getChrW32(pToken)) );
        pToken = SrcFile_InputLookAhead(pObj, 3);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ('a' == Token_getChrW32(pToken)) );

        eRc = SrcFile_CheckPoint(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pToken = SrcFile_InputAdvance(pObj, 3);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ('s' == Token_getChrW32(pToken)) );

        eRc = SrcFile_Restart(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pToken = SrcFile_InputLookAhead(pObj, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ('c' == Token_getChrW32(pToken)) );
        pToken = SrcFile_InputLookAhead(pObj, 2);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ('l' == Token_getChrW32(pToken)) );
        pToken = SrcFile_InputLookAhead(pObj, 3);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( ('a' == Token_getChrW32(pToken)) );

        if (pObj) {
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_SrcFile_Buffer01(
    const
    char            *pTestName
)
{
    SRCFILE_DATA    *pSource = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    TOKEN_DATA      *pToken;
    int32_t         cls = 1;
    char            chr;
    PATH_DATA       *pPath = Path_NewA("abc");
    uint16_t        colNo;
    uint32_t        lineNo;
    uint32_t        i;
    uint16_t        fileIndex;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pBuf = AStr_NewA("/*/*/* abc */*/*/");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    i = AStr_getLength(pBuf);
    XCTAssertTrue( (17 == i) );
    TRC( "\tpBuf = %p\n", pBuf );

    pSource = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pSource) );
    fprintf( stderr, "\tpSource = %p\n", pSource );

    if (pSource) {

        obj_TraceSet(pSource,true);

        while (!(cls == -1)) {
            pToken = SrcFile_InputLookAhead(pSource, 1);
            XCTAssertTrue( (Token_Validate(pToken)) );
            chr = Token_getChrW32(pToken);
            cls = Token_getClass(pToken);
            colNo = Token_getColNo(pToken);
            lineNo = Token_getLineNo(pToken);
            fileIndex = Token_getFileIndex(pToken);
            fprintf(
                    stderr,
                    "\tfile: %d, line: %2d col: %2d cls: %08X chr: %02X\n",
                    fileIndex,
                    lineNo,
                    colNo,
                    cls,
                    chr
                    );
            SrcFile_InputAdvance(pSource, 1);
        }

        obj_Release(pSource);
        pSource = OBJ_NIL;
    }

    obj_Release(pBuf);
    pBuf = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_SrcFile_File(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pObj  = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    uint32_t        count  = 0;
    TOKEN_DATA      *pToken;
    int32_t         chr;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pPath = Path_NewA(pFilePath);
    XCTAssertFalse( (OBJ_NIL == pPath) );

    pObj = SrcFile_NewFromPath(pPath, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        for ( ;; ) {
            pToken = SrcFile_InputLookAhead(pObj, 1);
            if (OBJ_NIL == pToken) {
                break;
            }
            XCTAssertTrue( (Token_Validate(pToken)) );
            chr = Token_getChrW32(pToken);
            if (-1 == chr) {
                break;
            }
            ++count;
            SrcFile_InputAdvance(pObj, 1);
        }
        fprintf(stderr,"Number of bytes read: %d\n", count);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_SrcFile_Test02(
                                const
                                char        *pTestName
                                )
{
    SRCFILE_DATA    *pSource = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    TOKEN_DATA      *pToken;
    int32_t         cls = 1;
    int32_t         chr;
    uint16_t        colNo;
    uint32_t        lineNo;
    uint32_t        i;
    PATH_DATA       *pPath = Path_NewA("abc");
    uint16_t        fileIndex;

    pBuf = AStr_NewA(pTest02);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    i = AStr_getLength(pBuf);
    XCTAssertTrue( (12 == i) );
    //TRC( "\tpBuf = %p\n", pBuffer );

    pSource = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pSource) );
    fprintf( stderr, "\tpSource = %p\n", pSource );
    obj_TraceSet(pSource,true);

    if (pSource) {

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( (0xA0 == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == cls) );
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('c' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('l' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('a' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('s' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('s' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( (0x2060 == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('a' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('b' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('c' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( (';' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('\n' == chr) );
        cls = Token_getClass(pToken);
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( (-1 == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (-1 == cls) );
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        obj_Release(pSource);
        pSource = OBJ_NIL;
    }

    obj_Release(pBuf);
    pBuf = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_SrcFile_Test03(
    const
    char            *pTestName
)
{
    SRCFILE_DATA    *pSource = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    TOKEN_DATA      *pToken;
    int32_t         cls = 1;
    int32_t         chr;
    uint16_t        colNo;
    uint32_t        lineNo;
    uint32_t        i;
    PATH_DATA       *pPath = Path_NewA("abc");
    uint16_t        fileIndex;

    pBuf = AStr_NewA("{oNe: +123}\n");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    i = AStr_getLength(pBuf);
    XCTAssertTrue( (12 == i) );
    //TRC( "\tpBuf = %p\n", pBuffer );

    pSource = SrcFile_NewFromAStr(pPath, pBuf, 1, 4);
    XCTAssertFalse( (OBJ_NIL == pSource) );
    fprintf( stderr, "\tpSource = %p\n", pSource );
    obj_TraceSet(pSource,true);

    if (pSource) {

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('{' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( ('{' == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (1 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('o' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (2 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('N' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_ALPHA_UPPER == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (3 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('e' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_ALPHA_LOWER == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (4 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( (':' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (':' == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (5 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( (' ' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (6 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('+' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( ('+' == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (7 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('1' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_NUMBER == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (8 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('2' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_NUMBER == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (9 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('3' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_NUMBER == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (10 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('}' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( ('}' == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (11 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (1 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( ('\n' == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_EOL == cls) );
        colNo = Token_getColNo(pToken);
        XCTAssertTrue( (0 == colNo) );
        lineNo = Token_getLineNo(pToken);
        XCTAssertTrue( (2 == lineNo) );
        fileIndex = Token_getFileIndex(pToken);
        XCTAssertTrue( (1 == fileIndex) );
        SrcFile_InputAdvance(pSource, 1);

        pToken = SrcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        XCTAssertTrue( (Token_Validate(pToken)) );
        chr = Token_getChrW32(pToken);
        XCTAssertTrue( (-1 == chr) );
        cls = Token_getClass(pToken);
        XCTAssertTrue( (-1 == cls) );
        colNo = Token_getColNo(pToken);
        lineNo = Token_getLineNo(pToken);
        fileIndex = Token_getFileIndex(pToken);
        SrcFile_InputAdvance(pSource, 1);

        obj_Release(pSource);
        pSource = OBJ_NIL;
    }

    obj_Release(pBuf);
    pBuf = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_SrcFile);
    TINYTEST_ADD_TEST(test_SrcFile_Test03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFile_Test02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFile_File,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFile_Buffer01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFile_General01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFile_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_SrcFile_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcFile_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_SrcFile);





