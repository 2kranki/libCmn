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
#include    <trace.h>
#include    <listdl.h>



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
    mem_Dump( );
    mem_Release( );
    
    return 1; 
}






int         test_listdl_Sort(
    const
    char        *pTestName
)
{
    LISTDL_DATA		list = {0};
	bool			fRc;
    uint16_t        i;
    LIST_ENTRY      *pEntry;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    fRc = listdl_Init(&list,0);
    XCTAssertTrue( (fRc) );
    if (fRc) {
        for (i=0; i<num; ++i) {
            pEntry = mem_Malloc(sizeof(LIST_ENTRY));
            pListTable[cLT++] = pEntry;
            XCTAssertFalse( (NULL == pEntry) );
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
        XCTAssertTrue( (fRc) );
        
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

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_listdl);
  TINYTEST_ADD_TEST(test_listdl_Sort,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_listdl);





