/*
 *	Generated 11/22/2017 13:10:45
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
#include    <SRecords_internal.h>



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






int         test_SRecords_OpenClose(
    const
    char        *pTestName
)
{
    SRECORDS_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SRecords_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SRecords_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_SRecords_Input01(
    const
    char        *pTestName
)
{
    SRECORDS_DATA	*pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        memSize = 0;
    uint8_t         *pData = NULL;
    uint8_t         data[52] =  "\x28\x5F\x24\x5F\x22\x12\x22\x6A\x00\x04\x24\x29\x00\x08\x23\x7C"
                                "\x00\x02\x00\x08\x00\x08\x26\x29\x00\x18\x53\x81\x23\x41\x00\x18"
                                "\x41\xE9\x00\x08\x4E\x42\x23\x43\x00\x18\x23\x42\x00\x08\x24\xA9"
                                "\x00\x14\x4E\xD4";

    fprintf(stderr, "Performing: %s\n", pTestName);

    // Example found in MC68000 Family Programmer's Reference Manual
    pStr = AStr_NewA(
            "S00600004844521B\n"
            "S1130000285F245F2212226A000424290008237C2A\n"
            "S11300100002000800082629001853812341001813\n"
            "S113002041E900084E42234300182342000824A952\n"
            "S107003000144ED492\n"
            "S9030000FC\n"
            );
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    pObj = SRecords_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        eRc = SRecords_ReadFromAStr(pObj, pStr, NULL, 0, &memSize);

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    obj_Release(pStr);
    pStr = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_SRecords_Output01(
    const
    char        *pTestName
)
{
    SRECORDS_DATA   *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTR_DATA       *pRecords = OBJ_NIL;
    ERESULT         eRc;
    uint32_t        memSize = 0;
    uint8_t         data[52] =  "\x28\x5F\x24\x5F\x22\x12\x22\x6A\x00\x04\x24\x29\x00\x08\x23\x7C"
                                "\x00\x02\x00\x08\x00\x08\x26\x29\x00\x18\x53\x81\x23\x41\x00\x18"
                                "\x41\xE9\x00\x08\x4E\x42\x23\x43\x00\x18\x23\x42\x00\x08\x24\xA9"
                                "\x00\x14\x4E\xD4";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    // Example found in MC68000 Family Programmer's Reference Manual
    pStr = AStr_NewA(
                     "S00600004844521B\n"
                     "S1130000285F245F2212226A000424290008237C2A\n"
                     "S11300100002000800082629001853812341001813\n"
                     "S113002041E900084E42234300182342000824A952\n"
                     "S107003000144ED492\n"
                     "S9030000FC\n"
                     );
    TINYTEST_FALSE( (OBJ_NIL == pStr) );
    
    pRecords = SRecords_ToStringS1(0, 0, 52, data);
    TINYTEST_FALSE( (OBJ_NIL == pRecords) );
    fprintf(stderr, "records = \n%s\n\n", AStr_getData(pRecords));
    fprintf(stderr, "example = \n%s\n\n", AStr_getData(pStr));
    eRc = AStr_Compare(pStr, pRecords);
    TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

    obj_Release(pRecords);
    pRecords = OBJ_NIL;
    obj_Release(pStr);
    pStr = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_SRecords);
    TINYTEST_ADD_TEST(test_SRecords_Output01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SRecords_Input01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SRecords_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_SRecords);





