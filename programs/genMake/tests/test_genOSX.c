/*
 *	Generated 04/18/2018 09:07:03
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
#include    <genOSX_internal.h>



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






int             test_genOSX_OpenClose(
    const
    char            *pTestName
)
{
    GENOSX_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genOSX_Object01(
    const
    char            *pTestName
)
{
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
            "OBJS += $(OBJDIR)/xyzzy.o\n\n"
            "$(OBJDIR)/xyzzy.o: $(SRCDIR)/xyzzy.c\n"
            "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $<\n\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_CompileRoutineStr(
                                pObj,
                                "xyzzy.c",      // Object class name
                                NULL,           // Source Directory Env Name
                                NULL,           // Object Directory Env Name
                                NULL            // Object Make Variable
                );
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, pOutputA)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genOSX_Object02(
    const
    char            *pTestName
)
{
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
        "OBJS += $(OBJDIR)/xyzzy.o $(OBJDIR)/xyzzy_object.o\n\n"
        "$(OBJDIR)/xyzzy.o: $(SRCDIR)/xyzzy.c\n\n"
        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $<\n\n"
        "$(OBJDIR)/xyzzy_object.o: $(SRCDIR)/xyzzy_object.c\n"
        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $<\n\n\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_CompileObjectStr(
                                        pObj,
                                        "xyzzy",        // Object class name
                                        NULL,           // Source Directory Env Name
                                        NULL,           // Object Directory Env Name
                                        NULL            // Object Make Variable
                );
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, pOutputA)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_genOSX);
    TINYTEST_ADD_TEST(test_genOSX_Object02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_genOSX);





