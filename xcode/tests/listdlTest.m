/*
 *	Generated 06/17/2015 20:19:14
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


#include    "listdl.h"


static
char	*stringTable[] = {
	"now",
    "before",
    "after",
    "tomorrow",
    "today",
    "someday",
#ifdef XYZZY
#endif
};
static
int             num = 6;

typedef struct list_entry_s {
	LISTDL_NODE		node;
	char			*pString;
} LIST_ENTRY;


int             compare(
    void            *p1,
    void            *p2
)
{
    LIST_ENTRY  *pNode1 = p1;
    LIST_ENTRY  *pNode2 = p2;
    int         rc;
    
    rc = strcmp(pNode1->pString, pNode2->pString);
    return rc;
}


static
LIST_ENTRY  *pListTable[6] = {0};
static
int         cLT = 0;




@interface listdlTests : XCTestCase

@end

@implementation listdlTests


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




- (void)testSort
{
    LISTDL_DATA		list = {0};
	bool			fRc;
    uint16_t        i;
    LIST_ENTRY      *pEntry;
   
    fRc = listdl_Init(&list,0);
    XCTAssertTrue( (fRc), @"" );
    if (fRc) {
        for (i=0; i<num; ++i) {
            pEntry = mem_Malloc(sizeof(LIST_ENTRY));
            pListTable[cLT++] = pEntry;
            XCTAssertFalse( (NULL == pEntry), @"" );
            if (pEntry) {
                pEntry->pString = stringTable[i];
                listdl_Add2Head(&list, pEntry);
            }
        }
        
        fprintf(stderr, "Original List:\n");
        pEntry = listdl_Head(&list);
        while (pEntry) {
            fprintf(stderr, "\t%p - %s\n", pEntry, pEntry->pString);
            pEntry = listdl_Next(&list, pEntry);
        }
        
        fRc = listdl_Sort(&list, compare);
        XCTAssertTrue( (fRc), @"" );
        
        fprintf(stderr, "Sorted List:\n");
        pEntry = listdl_Head(&list);
        while (pEntry) {
            fprintf(stderr, "\t%p - %s\n", pEntry, pEntry->pString);
            pEntry = listdl_Next(&list, pEntry);
        }

        while (listdl_Count(&list)) {
            pEntry = listdl_DeleteHead(&list);
            if (pEntry) {
                mem_Free(pEntry);
            }
        }
    }

}



@end



