// vi:nu:et:sts=4 ts=4 sw=4
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


    typedef enum Item_Type_e {
        ITEM_TYPE_UNKNOWN=0,
        ITEM_TYPE_COMMENT=1,
        ITEM_TYPE_GENERAL=2,
        ITEM_TYPE_HEADING=3,
        ITEM_TYPE_LINK=4,
        ITEM_TYPE_TITLE=5,
        ITEM_TYPE_WEBSITES=6,
    } ITEM_TYPES;


    typedef struct {
        const
        char            *pEnum;
        char            *pDesc;
        char            *pName;
        uint32_t        value;
    } Item_Type_entry;

    // This table is in alphanumeric order to be searched
    // with a sequential or binary search by description.

    static
    const
    Item_Type_entry    Item_Type_entries[] = {
        {"ITEM_TYPE_COMMENT", "", "COMMENT", 1},
        {"ITEM_TYPE_GENERAL", "", "GENERAL", 2},
        {"ITEM_TYPE_HEADING", "", "HEADING", 3},
        {"ITEM_TYPE_LINK", "", "LINK", 4},
        {"ITEM_TYPE_TITLE", "", "TITLE", 5},
        {"ITEM_TYPE_UNKNOWN", "", "UNKNOWN", 0},
        {"ITEM_TYPE_WEBSITES", "", "WEBSITES", 6},
    };

    static
    uint32_t    cItem_Type_entries = 7;




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






int         test_misc_OpenClose(
    const
    char        *pTestName
)
{
    MISC_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = misc_Alloc( );
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



int         test_misc_Abbrev01(
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



int         test_misc_BitReversal01(
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



int         test_misc_Parity01(
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



int         test_misc_Match01(
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
    fRc = misc_PatternMatchA("x*.txt","xyzzy.txt",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("x*.t*","xyzzy.txt",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("x*.??t","xyzzy.txt",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("x*.*t","xyzzy.txt",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("x?zz?.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("x?zy?.dmg","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (!fRc) );
    fRc = misc_PatternMatchA("x?zz?.*","xyzzy.dmg",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("*y.??t","xyzzy.txt",NULL,NULL);
    XCTAssertTrue( (fRc) );
    fRc = misc_PatternMatchA("/usr/bin/grep", "/usr/bin/grep",NULL,NULL);
    TINYTEST_TRUE( (fRc) );
    fRc = misc_PatternMatchA("/usr/bin/*", "/usr/bin/grep",NULL,NULL);
    TINYTEST_TRUE( (fRc) );
    fRc = misc_PatternMatchA("/usr/*/grep", "/usr/bin/grep",NULL,NULL);
    TINYTEST_TRUE( (fRc) );
    fRc = misc_PatternMatchA("/*/bin/grep", "/usr/bin/grep",NULL,NULL);
    TINYTEST_TRUE( (fRc) );

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_misc_Prime01(
    const
    char        *pTestName
)
{
    bool        fRc;
    uint64_t    amt;
    uint64_t    amt2;

    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    fRc = misc_IsPrime(2049);
    XCTAssertTrue( (!fRc) );
    fRc = misc_IsPrime(2051);
    XCTAssertTrue( (!fRc) );
    fRc = misc_IsPrime(2053);
    XCTAssertTrue( (fRc) );
    fRc = misc_IsPrime(2057);
    XCTAssertTrue( (!fRc) );

    fRc = misc_IsPrime(4097);
    XCTAssertTrue( (!fRc) );
    fRc = misc_IsPrime(4099);
    XCTAssertTrue( (fRc) );
    fRc = misc_IsPrime(4101);
    XCTAssertTrue( (!fRc) );
    fRc = misc_IsPrime(4103);
    XCTAssertTrue( (!fRc) );

    fRc = misc_IsPrime(8209);
    XCTAssertTrue( (fRc) );

    fRc = misc_IsPrime(16411);
    XCTAssertTrue( (fRc) );
    
    amt = 2147483648;
    amt2 = amt - 1;
    fRc = false;
    while (!fRc) {
        amt2 += 2;
        fRc = misc_IsPrime(amt2);
    }
    fprintf(stderr, "\tPrime for %lld is %lld\n", amt, amt2);
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_misc_SearchBinary01 (
    const
    char        *pTestName
)
{
    MISC_DATA	*pObj = OBJ_NIL;
    Item_Type_entry *pEntry = NULL;
    uint32_t        value = 0;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = misc_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = misc_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

            pEntry = misc_SearchBinary(
                        "ITEM_TYPE_COMMENT",
                        (void *)Item_Type_entries,
                        cItem_Type_entries,
                        sizeof(Item_Type_entry),
                        offsetof(Item_Type_entry, pEnum),
                        (void *)strcmp
                );
            TINYTEST_FALSE( (NULL == pEntry) );
            if (pEntry) {
                value = pEntry->value + 1;
            }
    	    TINYTEST_TRUE( (ITEM_TYPE_COMMENT == value) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_misc);
    TINYTEST_ADD_TEST(test_misc_SearchBinary01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_misc_Prime01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_misc_Match01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_misc_Parity01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_misc_BitReversal01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_misc_Abbrev01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_misc_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_misc);





