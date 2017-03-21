/*
 *	Generated 06/17/2015 11:21:15
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */


#import <XCTest/XCTest.h>
#import <libCmn/libCmn.h>



// All code under test must be linked into the Unit Test bundle
// Test Macros:
//      XCTAssert(expression, failure_description, ...)
//      XCTFail(failure_description, ...)
//      XCTAssertEqualObjects(object_1, object_2, failure_description, ...) uses isEqualTo:
//      XCTAssertEquals(value_1, value_2, failure_description, ...)
//      XCTAssertEqualsWithAccuracy(value_1, value_2, accuracy, failure_description, ...)
//      XCTAssertNil(expression, failure_description, ...)
//      XCTAssertNotNil(expression, failure_description, ...)
//      XCTAssertTrue(expression, failure_description, ...)
//      XCTAssertFalse(expression, failure_description, ...)
//      XCTAssertThrows(expression, failure_description, ...)
//      XCTAssertThrowsSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertThrowsSpecificNamed(expression, exception_class, exception_name, failure_description, ...)
//      XCTAssertNoThrow(expression, failure_description, ...)
//      XCTAssertNoThrowSpecific(expression, exception_class, failure_description, ...)
//      XCTAssertNoThrowSpecificNamed(expression, exception_class, exception_name, failure_description, ...)


#include    "srcFile_internal.h"
#include    "szTbl.h"
#include    "trace.h"


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


@interface srcFileTests : XCTestCase

@end

@implementation srcFileTests


- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    mem_Init( );
    
}


- (void)tearDown
{
    mem_Dump( );
    mem_Release( );
    
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.
    [super tearDown];
}




- (void)testOpenClose
{
    SRCFILE_DATA	*pObj = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    PATH_DATA       *pPath = path_NewA("abc");
   
    pBuf = AStr_NewA(pTest01);
    XCTAssertFalse( (OBJ_NIL == pBuf), @"" );
    
    if (pBuf) {
        pObj = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pObj), @"" );
        pObj = srcFile_InitAStr( pObj, pBuf, pPath, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pObj), @"" );
        if (pObj) {
            obj_Release(pObj);
            pObj = OBJ_NIL;
        }
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    obj_Release(pPath);
    pPath = OBJ_NIL;

    szTbl_SharedReset();
}



- (void)testBuffer01
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
    
    pBuf = AStr_NewA("/*/*/* abc */*/*/");
    XCTAssertFalse( (OBJ_NIL == pBuf), @"" );
    i = AStr_getLength(pBuf);
    XCTAssertTrue( (17 == i), @"" );
    TRC( "\tpBuf = %p\n", pBuf );
    
    pSource = srcFile_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pSource), @"" );
    pSource = srcFile_InitAStr( pSource, pBuf, pPath, 4, true, false );
    XCTAssertFalse( (OBJ_NIL == pSource), @"" );
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
    
    szTbl_SharedReset();
}



- (void)testFile
{
    SRCFILE_DATA	*pObj  = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    uint32_t        count  = 0;
    TOKEN_DATA      *pToken;
    int32_t         chr;
    
    pPath = path_NewA(pFilePath);
    XCTAssertFalse( (OBJ_NIL == pPath), @"" );
    
    pObj = srcFile_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = srcFile_InitFile( pObj, pPath, 4, true, false );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
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
    
    szTbl_SharedReset();
}



- (void)testTest02
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
    XCTAssertFalse( (OBJ_NIL == pBuf), @"" );
    i = AStr_getLength(pBuf);
    XCTAssertTrue( (12 == i), @"" );
    //TRC( "\tpBuf = %p\n", pBuffer );
    
    pSource = srcFile_Alloc( );
    XCTAssertFalse( (OBJ_NIL == pSource), @"" );
    pSource = srcFile_InitAStr( pSource, pBuf, pPath, 4, true, false );
    XCTAssertFalse( (OBJ_NIL == pSource), @"" );
    fprintf( stderr, "\tpSource = %p\n", pSource );
    obj_TraceSet(pSource,true);
    
    if (pSource) {
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (0xA0 == chr), @"" );
        cls = token_getClass(pToken);
        XCTAssertTrue( (ASCII_LEXICAL_WHITESPACE == cls), @"" );
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('c' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('l' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('a' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('s' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('s' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (0x2060 == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('a' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('b' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('c' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (';' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( ('\n' == chr), @"" );
        cls = token_getClass(pToken);
        colNo = token_getColNo(pToken);
        lineNo = token_getLineNo(pToken);
        pFileName = token_getFileName(pToken);
        srcFile_InputAdvance(pSource, 1);
        
        pToken = srcFile_InputLookAhead(pSource, 1);
        XCTAssertFalse( (OBJ_NIL == pToken), @"" );
        chr = token_getChrW(pToken);
        XCTAssertTrue( (-1 == chr), @"" );
        cls = token_getClass(pToken);
        XCTAssertTrue( (-1 == cls), @"" );
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
    
    szTbl_SharedReset();
}



@end



