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
#include    <misc_internal.h>



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






int         test_misc_OpenClose(
    const
    char        *pTestName
)
{
    MISC_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = misc_Alloc(0);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = misc_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_misc_Abbrev(
    const
    char        *pTestName
)
{
    uint32_t        u32;
    uint64_t        u64;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    u32 = misc_BitReversal32(0x00000001);
    XCTAssertTrue( (u32 == 0x80000000) );
    u32 = misc_BitReversal32(0x80000000);
    XCTAssertTrue( (u32 == 0x00000001) );
    u32 = misc_BitReversal32(0x80000001);
    XCTAssertTrue( (u32 == 0x80000001) );
    
    u64 = misc_BitReversal64(0x0000000000000001);
    XCTAssertTrue( (u64 == 0x8000000000000000) );
    u64 = misc_BitReversal64(0x8000000000000000);
    XCTAssertTrue( (u64 == 0x0000000000000001) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_misc_BitReversal(
    const
    char        *pTestName
)
{
    bool        fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    fRc = misc_AbbrevA("EXACT", "EXACT");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("EXACT", "exact");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("EXACT", "e");
    XCTAssertTrue( (!fRc) );
    fRc = misc_AbbrevA("Exact", "e");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("eXact", "x");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("eXact", "ext");
    XCTAssertTrue( (fRc) );
    fRc = misc_AbbrevA("eXact", "xray");
    XCTAssertTrue( (!fRc) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_misc_Parity(
    const
    char        *pTestName
)
{
    bool        fRc;
    //char        *pEquiv;
    //char        test[64];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    fRc = misc_ComputeEvenParity8(0x01);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x02);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x04);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x08);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x10);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x20);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x40);
    XCTAssertTrue( (!fRc) );
    fRc = misc_ComputeEvenParity8(0x80);
    XCTAssertTrue( (!fRc) );
    
    fRc = misc_ComputeEvenParity8(0x00);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x11);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x22);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x44);
    XCTAssertTrue( (fRc) );
    fRc = misc_ComputeEvenParity8(0x88);
    XCTAssertTrue( (fRc) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_misc_Match(
    const
    char        *pTestName
)
{
    bool        fRc;
    //char        *pEquiv;
    //char        test[64];
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    fRc = misc_PatternMatchA("*.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("*.dmg","xyzzy.txt",NULL,NULL);
    XCTAssertTrue( (!fRc) );
    fRc = misc_PatternMatchA("x?zz?.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("x?zy?.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (!fRc) );
    fRc = misc_PatternMatchA("x?zz?.*","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc) );
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_misc);
  TINYTEST_ADD_TEST(test_misc_Match,setUp,tearDown);
  TINYTEST_ADD_TEST(test_misc_Parity,setUp,tearDown);
  TINYTEST_ADD_TEST(test_misc_BitReversal,setUp,tearDown);
  TINYTEST_ADD_TEST(test_misc_Abbrev,setUp,tearDown);
  TINYTEST_ADD_TEST(test_misc_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_misc);





