/*
 *	Generated 12/17/2017 07:12:35
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
#include    <SrcErrors_internal.h>



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

    
    SrcErrors_SharedReset( );
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






int         test_SrcErrors_OpenClose(
    const
    char        *pTestName
)
{
    SRCERRORS_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = SrcErrors_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SrcErrors_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        TINYTEST_TRUE(obj_IsKindOf(pObj, OBJ_IDENT_SRCERRORS));
        TINYTEST_TRUE(obj_IsKindOf(pObj, OBJ_IDENT_OBJARRAY));

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_SrcErrors_Fatal01(
    const
    char        *pTestName
)
{
    SRCERRORS_DATA  *pObj = OBJ_NIL;
    SRCLOC          location = {1,3,2,200};
    
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = SrcErrors_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = SrcErrors_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        SrcErrors_AddFatalA(
                            pObj,
                            &location,
                            "Expecting '}', but found nothing"
        );
        SrcErrors_Print(pObj, stderr);
        fprintf(stderr, "fatal indicator: %s\n",
                SrcErrors_getFatal(pObj) ? "true" : "false"
        );
        TINYTEST_TRUE( (SrcErrors_getFatal(pObj)) );
        
        fprintf(stderr, "Resetting fatal indicator\n");
        SrcErrors_setFatal(pObj, false);
        TINYTEST_TRUE( (!SrcErrors_getFatal(pObj)) );
        SrcErrors_AddErrorA(
                            pObj,
                            SRCERROR_SEVERITY_WARNING,
                            &location,
                            "Just an error, not fatal!"
        );
        SrcErrors_Print(pObj, stderr);
        fprintf(stderr, "fatal indicator: %s\n",
                SrcErrors_getFatal(pObj) ? "true" : "false"
        );
        TINYTEST_TRUE( (!SrcErrors_getFatal(pObj)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_srcErrors);
    TINYTEST_ADD_TEST(test_SrcErrors_Fatal01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_SrcErrors_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_srcErrors);





