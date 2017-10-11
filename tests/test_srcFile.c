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
#include    <srcFile_internal.h>



static
const
char        *pFilePath = "/Users/bob/Support/vogel/template.h.txt"; // Currently 248 bytes


static
char        *pTest01 =  "class abc {\n"
                        "\tint a;\n"
                        "\tchar\t\txyzzy(void);\n"
                        "}\n";


static
char        *pTest02 =  "\xC2\xA0" "class" "\xE2\x81\xA0" "abc;\n";





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

    szTbl_SharedReset();    
    trace_SharedReset( ); 
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_srcFile_OpenClose(
    const
    char        *pTestName
)
{
    SRCFILE_DATA	*pObj = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    PATH_DATA       *pPath = path_NewA("abc");
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pBuf = AStr_NewA(pTest01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    
    if (pBuf) {
        pObj = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pObj) );
        pObj = srcFile_InitAStr( pObj, pBuf, pPath, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pObj) );
        if (pObj) {
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    obj_Release(pPath);
    pPath = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_srcFile_Buffer01(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSource = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    TOKEN_DATA      *pToken;
    int32_t         cls = 1;
    char            chr;
    PATH_DATA       *pPath = path_NewA("abc");
    uint16_t        colNo;
    uint32_t        lineNo;
    uint32_t        i;
    const
    char            *pFileName;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pBuf = AStr_NewA("/*/*/* abc */*/*/");
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    i = AStr_getLength(pBuf);
    XCTAssertTrue( (17 == i) );
    TRC( "\tpBuf = %p\n", pBuf );
    
    pSource = srcFile_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pSource) );
    pSource = srcFile_InitAStr( pSource, pBuf, pPath, 4, true, false );
    XCTAssertFalse( (OBJ_NIL == pSource) );
    fprintf( stderr, "\tpSource = %p\n", pSource );
    
    if (pSource) {
        
        obj_TraceSet(pSource,true);
        
        while (!(cls == -1)) {
            pToken = srcFile_InputLookAhead(pSource, 1);
            chr = token_getChrW(pToken);
            cls = token_getClass(pToken);
            colNo = token_getColNo(pToken);
            lineNo = token_getLineNo(pToken);
            pFileName = token_getFileName(pToken);
            fprintf(
                    stderr,
                    "\tfile: %s, line: %d col: %d cls: %04X chr: %02X\n",
                    pFileName,
                    lineNo,
                    colNo,
                    cls,
                    chr
            );
            srcFile_InputAdvance(pSource, 1);
        }
        
        obj_Release(pSource);
        pSource = OBJ_NIL;
    }
    
    obj_Release(pBuf);
    pBuf = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_srcFile_File(
    const
    char        *pTestName
)
{
    SRCFILE_DATA	*pObj  = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    uint32_t        count  = 0;
    TOKEN_DATA      *pToken;
    int32_t         chr;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = path_NewA(pFilePath);
    XCTAssertFalse( (OBJ_NIL == pPath) );
    
    pObj = srcFile_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = srcFile_InitPath( pObj, pPath, 4, true, false );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {

        for ( ;; ) {
            pToken = srcFile_InputLookAhead(pObj, 1);
            if (OBJ_NIL == pToken) {
                break;
            }
            chr = token_getChrW(pToken);
            if (-1 == chr) {
                break;
            }
            ++count;
            srcFile_InputAdvance(pObj, 1);
        }
        fprintf(stderr,"Number of bytes read: %d\n", count);
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_srcFile_Test02(
    const
    char        *pTestName
)
{
    SRCFILE_DATA    *pSource = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    TOKEN_DATA      *pToken;
    int32_t         cls = 1;
    int32_t         chr;
    const
    char            *pFileName;
    uint16_t        colNo;
    uint32_t        lineNo;
    uint32_t        i;
    PATH_DATA       *pPath = path_NewA("abc");
    
    pBuf = AStr_NewA(pTest02);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    i = AStr_getLength(pBuf);
    XCTAssertTrue( (12 == i) );
    //TRC( "\tpBuf = %p\n", pBuffer );
    
    pSource = srcFile_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pSource) );
    pSource = srcFile_InitAStr( pSource, pBuf, pPath, 4, true, false );
    XCTAssertFalse( (OBJ_NIL == pSource) );
    fprintf( stderr, "\tpSource = %p\n", pSource );
    obj_TraceSet(pSource,true);
    
    if (pSource) {
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (0xA0 == chr) );
        cls = token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == cls) );
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('c' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('l' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('a' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('s' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('s' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (0x2060 == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('a' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('b' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('c' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (';' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('\n' == chr) );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken) );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (-1 == chr) );
        cls = token_getClass(pToken);
        XCTAssertTrue( (-1 == cls) );
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        obj_Release(pSource);
        pSource = OBJ_NIL;
    }
    
    obj_Release(pBuf);
    pBuf = OBJ_NIL;
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_srcFile);
  TINYTEST_ADD_TEST(test_srcFile_Test02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_srcFile_File,setUp,tearDown);
  TINYTEST_ADD_TEST(test_srcFile_Buffer01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_srcFile_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_srcFile);





