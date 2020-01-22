/*
 *	Generated 11/23/2017 23:46:18
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
#include    <textIn_internal.h>



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






int         test_textIn_OpenClose(
    const
    char        *pTestName
)
{
    TEXTIN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = textIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = textIn_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_textIn_Input01(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    W32CHR_T        chr = 0;
    //ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr = AStr_NewA("abc\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = textIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'a') );

        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'b') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'c') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == '\n') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == EOF) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pStr);
    pStr = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_textIn_Input02(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    W32CHR_T        chr = 0;
    //ERESULT         eRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr = AStr_NewA("abc\tdef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = textIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'a') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'b') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'c') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == ' ') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'd') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'e') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == 'f') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == '\n') );
        
        chr = textIn_NextChar(pObj);
        TINYTEST_TRUE( (chr == EOF) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pStr);
    pStr = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_textIn_GetLine01(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    char            buffer[128];
    SRCLOC          loc = {0};
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pStr = AStr_NewA("abc\n\ndef\n");
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = textIn_NewFromAStr(OBJ_NIL, pStr, 1, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = textIn_GetLine(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "abc")) );

        eRc = textIn_GetLine(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (buffer[0] == '\0') );
        
        eRc = textIn_GetLine(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "def")) );
        
        eRc = textIn_GetLine(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (eRc == ERESULT_EOF_ERROR) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pStr);
    pStr = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_textIn_GetLine02(
    const
    char            *pTestName
)
{
    TEXTIN_DATA     *pObj = OBJ_NIL;
    //ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    char            buffer[128];
    SRCLOC          loc = {0};
    const
    char            *pFilePathA = "~/git/libCmn/tests/files/test_hjson_01.txt";
    PATH_DATA       *pFilePath = OBJ_NIL;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pFilePath = path_NewA(pFilePathA);
    TINYTEST_FALSE( (OBJ_NIL == pFilePath) );
    path_Clean(pFilePath);
    eRc = path_IsFile(pFilePath);
    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
    pObj = textIn_NewFromPath(pFilePath, 0, 4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        eRc = textIn_GetLine(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "{")) );
        
        eRc = textIn_GetLine(pObj, buffer, 128, &loc);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE( (0 == strcmp(buffer, "    \"one\": {")) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pFilePath);
    pFilePath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_textIn);
    TINYTEST_ADD_TEST(test_textIn_GetLine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_textIn_Input02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_textIn_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_textIn_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_textIn);





