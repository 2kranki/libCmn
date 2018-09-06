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



static
char        *strings[] = {
    "x1.c",
    "x2.c",
    (char *)NULL
};





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
            "OBJS += $(OBJDIR)/xyzzy_object.o\n\n"
            "$(OBJDIR)/xyzzy_object.o: $(SRCDIR)/xyzzy_object.c \n"
            "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
            "OBJS += $(OBJDIR)/xyzzy.o\n\n"
            "$(OBJDIR)/xyzzy.o: $(SRCDIR)/xyzzy.c \n"
            "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n";

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_GenCompileObject(
                                pObj,
                                "xyzzy",        // Object class name
                                NULL,           // Source Directory Env Name
                                NULL,           // Object Directory Env Name
                                NULL,           // Object Make Variable
                                OBJ_NIL,
                                OBJ_NIL
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



int             test_genOSX_Routine01(
    const
    char            *pTestName
)
{
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
    "OBJS += $(OBJDIR)/xyzzy.o\n\n"
    "$(OBJDIR)/xyzzy.o: $(SRCDIR)/xyzzy.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_GenCompileRoutine(
                         pObj,
                         "xyzzy.c",     // Object class name
                         NULL,          // Source Directory Env Name
                         NULL,          // Object Directory Env Name
                         NULL,          // Object Make Variable
                         NULL,
                         OBJ_NIL,       // Source Dependencies
                         OBJ_NIL,       // Object Dependencies
                         true,
                         false
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




int             test_genOSX_Routine02(
    const
    char            *pTestName
)
{
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
    "OBJV += $(DIROBJ)/xyzzy.o\n\n"
    "$(DIROBJ)/xyzzy.o: $(DIRSRC)/xyzzy.c \n"
    "\t$(CC) $(CFLAGS)  -o $(DIROBJ)/$(@F) $< \n\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_GenCompileRoutine(
                                         pObj,
                                         "xyzzy.c",     // Object class name
                                         "DIRSRC",      // Source Directory Env Name
                                         "DIROBJ",      // Object Directory Env Name
                                         "OBJV",        // Object Make Variable
                                         NULL,
                                         OBJ_NIL,       // Source Dependencies
                                         OBJ_NIL,       // Object Dependencies
                                         false,
                                         false
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



int             test_genOSX_Routine03(
    const
    char            *pTestName
)
{
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
    "OBJV += $(DIROBJ)/xyzzy.o\n\n"
    "$(DIROBJ)/xyzzy.o: $(DIRSRC)/xyzzy.c \n"
    "\t$(CC) $(CFLAGS)  -o $(DIROBJ)/$(@F) $< \n"
    "\t$(DIROBJ)/$(@F)\n\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_GenCompileRoutine(
                                         pObj,
                                         "xyzzy.c",     // Object class name
                                         "DIRSRC",      // Source Directory Env Name
                                         "DIROBJ",      // Object Directory Env Name
                                         "OBJV",        // Object Make Variable
                                         NULL,
                                         OBJ_NIL,       // Source Dependencies
                                         OBJ_NIL,       // Object Dependencies
                                         false,
                                         true
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



int             test_genOSX_Routine04(
    const
    char            *pTestName
)
{
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODEARRAY_DATA  *pObjDeps = OBJ_NIL;
    uint32_t        i;
    uint32_t        idx;
    ERESULT         eRc;
    const
    char            *pOutputA =
    "OBJV += $(DIROBJ)/xyzzy.o\n\n"
    "$(DIROBJ)/xyzzy.o: $(DIRSRC)/xyzzy.c \n"
    "\t$(CC) $(CFLAGS)  -o $(DIROBJ)/$(@F) $< $(DIRSRC)/x1.c $(DIRSRC)/x2.c \n"
    "\t$(DIROBJ)/$(@F)\n\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObjDeps = nodeArray_New();
    XCTAssertFalse( (OBJ_NIL == pObjDeps) );
    for (i=0; (i<10 && strings[i]); ++i) {
        NODE_DATA       *pNode;
        pNode = node_NewWithUTF8ConAndClass(strings[i], 0, OBJ_NIL);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        node_setClass(pNode, i+1);
        eRc = nodeArray_AppendNode(pObjDeps, pNode, &idx);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
    }
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_GenCompileRoutine(
                                         pObj,
                                         "xyzzy.c",     // Object class name
                                         "DIRSRC",      // Source Directory Env Name
                                         "DIROBJ",      // Object Directory Env Name
                                         "OBJV",        // Object Make Variable
                                         NULL,
                                         OBJ_NIL,       // Source Dependencies
                                         pObjDeps,      // Object Dependencies
                                         false,
                                         true
                                         );
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStr, pOutputA)) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    obj_Release(pObjDeps);
    pObjDeps = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genOSX_Test01(
    const
    char            *pTestName
)
{
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
    "TESTS += test_xyzzy\n\n"
    "test_xyzzy: $(TEST_SRC)/test_xyzzy.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $< \n"
    "\t$(TEST_OBJ)/$(@F)\n\n";
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr =  genOSX_GenCompileTest(
                    pObj,
                    "xyzzy",        // Object class name
                    NULL,           // Source Directory Env Name
                    NULL,           // Object Directory Env Name
                    NULL,           // Object Make Variable
                    OBJ_NIL,
                    OBJ_NIL
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
    TINYTEST_ADD_TEST(test_genOSX_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_genOSX);





