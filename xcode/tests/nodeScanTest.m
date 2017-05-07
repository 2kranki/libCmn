/*
 *	Generated 10/16/2015 09:19:12
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


#include    "nodeScan_internal.h"

// Node classes for the nodes in the AST built when reading in
// the grammar.  See also NODE_CLASSES in ll1.h.
typedef enum ll1_nodeClass_e {
    LL1_NODECLASS_UNKNOWN=0,
    LL1_NODECLASS_OPEN,
    LL1_NODECLASS_CLOSE,
    LL1_NODECLASS_0OR1=8,
    LL1_NODECLASS_0ORMORE,
    LL1_NODECLASS_1ORMORE,
    LL1_NODECLASS_ACTION,
    LL1_NODECLASS_CALL,                     // Action Call
    LL1_NODECLASS_CHAR,
    LL1_NODECLASS_GOAL,
    LL1_NODECLASS_GRAMMAR,
    LL1_NODECLASS_IDENT,
    LL1_NODECLASS_LHS,
    LL1_NODECLASS_OPTD,
    LL1_NODECLASS_OPTE,
    LL1_NODECLASS_OPTI,
    LL1_NODECLASS_OPTIONS,
    LL1_NODECLASS_OPTL,
    LL1_NODECLASS_PAREN,
    LL1_NODECLASS_RHS,
    LL1_NODECLASS_RHSALT,
    LL1_NODECLASS_SEP,
    LL1_NODECLASS_TERM,
    LL1_NODECLASS_TEXT,
    LL1_NODECLASS_TEXTB,
    LL1_NODECLASS_TEXTC,
} LL1_NODECLASS;



typedef struct test_node_def_s {
    const
    char        *pName;
    const
    char        *pData;
    const
    char        *pFile;
    int32_t     lineNo;
    uint16_t    colNo;
    uint16_t    class;
}   TEST_NODE_DEF;


/***
 ( grammar (
            goal=expr 
            term=INTEGER ( options )
            lhs=expr (
                rhs ( ident=term ident=sum ) 
            )
            lhs=sum (
                rhs ( char='+' action_call ident=term ident=sum )
                rhs
            )
            lhs=term (
                rhs ( ident=factor ident=product )
            )
            lhs=product (
                rhs ( char='*' action_call ident=factor ident=product )
                rhs 
            )
            lhs=factor (
                rhs ( char='(' ident=expr char=')' )
                rhs ( ident=INTEGER action_call ) 
            ) 
 ) )
  ***/

static
TEST_NODE_DEF       test_defs01[] = {
    {"(", "", "test03_gmr", 1, 1, LL1_NODECLASS_OPEN},
    {"grammar", "", "test03_gmr", 1, 1, LL1_NODECLASS_GRAMMAR},
    {"(", "", "test03_gmr", 1, 1, LL1_NODECLASS_OPEN},
    {"goal", "expr", "test03_gmr", 7, 7, LL1_NODECLASS_GOAL},
    {"term", "INTEGER", "test03_gmr", 8, 7, LL1_NODECLASS_TERM},
    {"(", "", "test03_gmr", 8, 7, LL1_NODECLASS_OPEN},
    {"options", "", "test03_gmr", 8, 7, LL1_NODECLASS_TERM},
    {")", "", "test03_gmr", 8, 7, LL1_NODECLASS_CLOSE},
    {"lhs", "expr", "test03_gmr", 19, 9, LL1_NODECLASS_LHS},
    {"(", "", "test03_gmr", 19, 9, LL1_NODECLASS_OPEN},
    {"rhs", "expr", "test03_gmr", 19, 9, LL1_NODECLASS_RHS},
    {"(", "", "test03_gmr", 19, 9, LL1_NODECLASS_OPEN},
    {"ident", "term", "test03_gmr", 19, 16, LL1_NODECLASS_IDENT},
    {"ident", "sum", "test03_gmr", 19, 21, LL1_NODECLASS_IDENT},
    {")", "", "test03_gmr", 19, 9, LL1_NODECLASS_CLOSE},
    {")", "", "test03_gmr", 19, 9, LL1_NODECLASS_CLOSE},
    {")", "", "test03_gmr", 1, 1, LL1_NODECLASS_CLOSE},
    {")", "", "test03_gmr", 1, 1, LL1_NODECLASS_CLOSE},
    {(char *)NULL, 0}
};


NODEARRAY_DATA *    build_test_array01(
)
{
    NODEARRAY_DATA  *pArray;
    NODE_DATA       *pNode;
    ERESULT         eRc;
    uint32_t        idx;
    TEST_NODE_DEF   *pDef = test_defs01;
    
    pArray = nodeArray_Alloc( );
    pArray = nodeArray_Init(pArray);
    if (pArray) {
        while (pDef->pName) {
            pNode = node_NewWithUTF8(pDef->pName, OBJ_NIL);
            node_setClass(pNode, pDef->class);
            eRc = nodeArray_AppendNode(pArray, pNode, &idx);
            obj_Release(pNode);
            pNode = OBJ_NIL;
        }
    }
    
    return pArray;
}



@interface nodeScanTests : XCTestCase

@end

@implementation nodeScanTests


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
    NODESCAN_DATA	*pObj = OBJ_NIL;
   
    pObj = nodeScan_Alloc(0);
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    pObj = nodeScan_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj), @"" );
    if (pObj) {
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

}



@end



