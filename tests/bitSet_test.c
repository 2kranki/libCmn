// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/18/2019 08:00:17
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
#include    <BitSet_internal.h>



int             setUp(
    const
    char            *pTestName
)
{
    mem_Init( );
    trace_Shared( ); 
    // Put setup code here. This method is called before the invocation of each
    // test method in the class.
    
    return 1; 
}


int             tearDown(
    const
    char            *pTestName
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






int             test_BitSet_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BITSET_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BitSet_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = BitSet_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int         test_BitSet_GetPut01(
    const
    char        *pTestName
)
{
    BITSET_DATA     *pObj = OBJ_NIL;
    BITSET_DATA     *pObj2 = OBJ_NIL;
    uint32_t        i;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    bool            fRc;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = BitSet_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = BitSet_Init( pObj );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = BitSet_ToDebugString(pObj, 0);
        fprintf(stderr, "Initial:\n%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        for (i=0; i<33; ++i) {
            eRc = BitSet_Set(pObj, i+1, true);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            fRc = BitSet_Get(pObj, i+1);
            XCTAssertTrue( (fRc) );
            pStr = BitSet_ToDebugString(pObj, 3);
            fprintf(stderr, "After setting bit %d:\n%s\n\n\n", i+1, AStr_getData(pStr));
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }
        pStr = BitSet_ToDebugString(pObj, 0);
        fprintf(stderr, "After setting 33 bits:\n%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pObj2 = BitSet_New();
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        eRc = BitSet_Expand(pObj2, 33);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        eRc = BitSet_SetAll(pObj2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pStr = BitSet_ToDebugString(pObj2, 0);
        fprintf(stderr, "After SetAll(pObj2):\n%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = BitSet_Zero(pObj2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pStr = BitSet_ToDebugString(pObj2, 0);
        fprintf(stderr, "After SetEmpty(pObj2):\n%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = BitSet_Invert(pObj2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pStr = BitSet_ToDebugString(pObj2, 0);
        fprintf(stderr, "After Invert(pObj2):\n%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        eRc = BitSet_Invert(pObj2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        pStr = BitSet_ToDebugString(pObj2, 0);
        fprintf(stderr, "After Invert2(pObj2):\n%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_BitSet);
    TINYTEST_ADD_TEST(test_BitSet_GetPut01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_BitSet_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_BitSet);





