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
#include    <name.h>
#include    <trace.h>
#include    <objCb_internal.h>



#define NUM_STR     10

/* Other variables */
static
char        *StrArray[NUM_STR] = {
//   123456789
	"String  1",
	"String  2",
	"String  3",
	"String  4",
	"String  5",
	"String  6",
	"String  7",
	"String  8",
	"String  9",
	"String 10"
};





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






int         test_objCb_OpenClose(
    const
    char        *pTestName
)
{
    OBJCB_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = objCb_Alloc(8);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = objCb_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_objCb_CounterOverflow(
    const
    char        *pTestName
)
{
	OBJCB_DATA			*cbp;
    uint16_t            i;
    uint16_t            j;
    bool                fRc;
    //char                msg[10];
    NAME_DATA           *pName;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
	cbp = objCb_Alloc(8);
    XCTAssertFalse( (NULL == cbp) );
	cbp = objCb_Init( cbp );
    XCTAssertFalse( (NULL == cbp) );

    // Empty Queue - positive to negative overflow
    cbp->numRead = 32766;
    cbp->numWritten = 32766;
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );

    for (i=0; i<8; ++i) {
        pName =  name_NewUTF8(StrArray[i]);
        fRc = objCb_Put(cbp,pName);
        obj_Release(pName);
        XCTAssertTrue( (fRc) );
        fRc = objCb_isEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = objCb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = objCb_Get(cbp, (void *)&pName);
        XCTAssertTrue( (fRc) );
        XCTAssertTrue( (ERESULT_SUCCESS_EQUAL == name_CompareA(pName,StrArray[i])) );
        obj_Release(pName);
    }
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
    // Empty Queue - negative to positive overflow
    cbp->numRead = -32766;
    cbp->numWritten = -32766;
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
    for (i=0; i<8; ++i) {
        pName =  name_NewUTF8(StrArray[i]);
        fRc = objCb_Put(cbp, pName);
        obj_Release(pName);
        XCTAssertTrue( (fRc) );
        fRc = objCb_isEmpty(cbp);
        XCTAssertFalse( (fRc) );
        j = objCb_Count(cbp);
        XCTAssertTrue( (j == (i+1)) );
    }
    
    for (i=0; i<8; ++i) {
        fRc = objCb_Get(cbp, (void *)&pName);
        XCTAssertTrue( (fRc) );
        //STAssertTrue( (aVal == i) );
        obj_Release(pName);
    }
    
    fRc = objCb_isEmpty(cbp);
    XCTAssertTrue( (fRc) );
    
	obj_Release( cbp );
    cbp = NULL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_objCb);
  TINYTEST_ADD_TEST(test_objCb_CounterOverflow,setUp,tearDown);
  TINYTEST_ADD_TEST(test_objCb_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_objCb);





