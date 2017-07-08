/*
 *	Generated 09/07/2015 10:54:22
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


#include    <lex_internal.h>
#include    <srcFile.h>


static
const
char        *pTestInput01 =
    "+ ++ +=\n"
    "\t* *=\n"
    "abc2\n";



@interface lexTests : XCTestCase

@end

@implementation lexTests


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
    LEX_DATA        *pObj = OBJ_NIL;
   
    pObj = lex_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lex_Init( pObj, 3 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



// Revisit this since lex is a virtual object.
#ifdef XYZZY
- (void)testInput01
{
    SRCFILE_DATA	*pSrc = OBJ_NIL;
    ASTR_DATA       *pBuf = OBJ_NIL;
    LEX_DATA        *pLex = OBJ_NIL;
    TOKEN_DATA      *pToken;
    bool            fRc;
    PATH_DATA       *pPath = path_NewA("abc");
    
    pBuf = AStr_NewA(pTestInput01);
    XCTAssertFalse( (OBJ_NIL == pBuf) );
    if (pBuf) {

        pSrc = srcFile_Alloc();
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        pSrc = srcFile_InitAStr( pSrc, pBuf, pPath, 4, true, true );
        XCTAssertFalse( (OBJ_NIL == pSrc) );
        if (pSrc) {
            
            pLex = (LEX_DATA *)pplex2_New(5);
            XCTAssertFalse( (OBJ_NIL == pLex) );
            if (pLex) {

                obj_TraceSet(pLex, true);
                pplex2_setReturnNL((PPLEX2_DATA *)pLex, true);
                pplex2_setReturnWS((PPLEX2_DATA *)pLex, true);
                
                fRc = lex_setParserFunction(pLex, (void *)pplex2_ParseToken, pLex);
                XCTAssertTrue( (fRc) );
                
                fRc =   lex_setSourceFunction(
                                pLex,
                                (void *)srcFile_InputAdvance,
                                (void *)srcFile_InputLookAhead,
                                pSrc
                        );
                XCTAssertTrue( (fRc) );

                // 1st Line - "+ ++ +=\n"
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ADD == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_INC == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_ADD == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 2nd Line - "\t* *=\n"
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_MUL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_WHITESPACE == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_OP_ASSIGN_MUL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                // 3rd Line = "abc2\n"
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_IDENTIFIER == token_getClass(pToken)) );
                //FIXME: XCTAssertTrue( (0 == strcmp("abc2",token_getText(pToken))) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (PPLEX_SEP_NL == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
                pToken = lex_InputLookAhead(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                XCTAssertTrue( (LEX_CLASS_EOF == token_getClass(pToken)) );
                pToken = lex_InputAdvance(pLex, 1);
                XCTAssertFalse( (OBJ_NIL == pToken) );
                
               obj_Release(pLex);
                pLex = OBJ_NIL;
            }
            
            obj_Release(pSrc);
            pSrc = OBJ_NIL;
        }
        
        obj_Release(pBuf);
        pBuf = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    szTbl_SharedReset();
}
#endif



- (void)testStrings
{
    LEX_DATA        *pObj = OBJ_NIL;
    ERESULT         eRc;
    TOKEN_DATA      *pToken;
    WSTR_DATA       *pStrW;
    int32_t         cls;
    TOKEN_DATA      *pWork = OBJ_NIL;
    
    pObj = lex_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = lex_Init( pObj, 3 );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pWork = token_NewCharW("abc", 1, 1, 'd', 'd');
        eRc = lex_ParseAddTokenToString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        pWork = token_NewCharW("abc", 1, 1, 'e', 'e');
        eRc = lex_ParseAddTokenToString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        pWork = token_NewCharW("abc", 1, 1, 'f', 'f');
        eRc = lex_ParseAddTokenToString(pObj, pWork);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pWork);
        pWork = OBJ_NIL;
        
        eRc = lex_ParseFinish(pObj,'a',true);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pToken = lex_getToken(pObj);
        pStrW = token_getStringW(pToken);
        eRc = WStr_CompareW(pStrW, L"def");
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == eRc) );
        cls = token_getClass(pToken);
        XCTAssertTrue( ('a' == cls) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    szTbl_SharedReset();
}




@end



