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
                                NULL,           // Compile Flag Variable Name
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
                         NULL,          // Compile Flag Variable Name
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
                                         NULL,          // Compile Flag Variable Name
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
                                         NULL,          // Compile Flag Variable Name
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
        ASTR_DATA       *pStr;
        pStr = AStr_NewA(strings[i]);
        XCTAssertFalse( (OBJ_NIL == pStr) );
        pNode = node_NewWithUTF8ConAndClass("string", 0, pStr);
        XCTAssertFalse( (OBJ_NIL == pNode) );
        node_setClass(pNode, i+1);
        eRc = nodeArray_AppendNode(pObjDeps, pNode, &idx);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        obj_Release(pNode);
        pNode = OBJ_NIL;
        obj_Release(pStr);
        pStr = OBJ_NIL;
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
                                         NULL,          // Compile Flag Variable Name
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
    char                *pTestName
)
{
    GENOSX_DATA         *pObj = OBJ_NIL;
    ASTR_DATA           *pStr = OBJ_NIL;
    int                 iRc;
    int                 offset = 0;
    const
    char                *pOutputA =
    "TESTS += test_xyzzy\n\n"
    "test_xyzzy: $(TEST_SRC)/test_xyzzy.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $(OBJS) $< \n"
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
                    NULL,           // Compile Flag Variable Name
                    OBJ_NIL,
                    OBJ_NIL
                );
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=0x%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genOSX_GenInitial01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
        "# Generated file - edits may be discarded!\n\n"
        "LIBNAM=libTest\n"
        "SYS=macosx\n"
        "TEMP=/tmp\n"
        "BASEDIR = $(TEMP)/$(LIBNAM)\n\n"
        "CFLAGS_LIBS = \n"
        "CFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n"
        "CFLAGS += -D__MACOSX_ENV__\n\n"
        "TEST_FLGS = -Itests $(CFLAGS_LIBS)\n\n"
        "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
        "INSTALLDIR = $(INSTALL_BASE)/$(LIBNAM)\n"
        "LIBDIR = $(BASEDIR)/$(SYS)\n"
        "SRCDIR = ./src\n"
        "SRCSYSDIR = ./src/$(SYS)\n"
        "TEST_SRC = ./tests\n"
        "ifdef  NDEBUG\n"
        "CFLAGS += -DNDEBUG\n"
        "LIB_FILENAME=$(LIBNAM)R.a\n"
        "OBJDIR = $(LIBDIR)/o/r\n"
        "else   #DEBUG\n"
        "CFLAGS += -D_DEBUG \n"
        "LIB_FILENAME=$(LIBNAM)D.a\n"
        "OBJDIR = $(LIBDIR)/o/d\n"
        "endif  #NDEBUG\n"
        "TEST_OBJ = $(OBJDIR)/tests\n"
        "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n\n"
        ".SUFFIXES:\n"
        ".SUFFIXES: .asm .c .o\n\n"
        "OBJS = \n\n"
        "TESTS = \n\n"
        "\n\n\n\n"
    ;
    int                 iRc;
    int                 offset = 0;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        genBase_setMakeType((GENBASE_DATA *)pObj, GENMAKE_TYPE_LIB);
        
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, namePrefixID, "lib");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, nameID, "Test");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pStr =  genOSX_GenInitial(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=0x%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genOSX_GenInitial02(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
    "# Generated file - edits may be discarded!\n\n"
    "PGMNAM=Test\n"
    "SYS=macosx\n"
    "TEMP=/tmp\n"
    "BASEDIR = $(TEMP)/$(PGMNAM)\n\n"
    "CFLAGS_LIBS = \n"
    "CFLAGS += -g -Werror -Isrc -Isrc/$(SYS)\n"
    "CFLAGS += -D__MACOSX_ENV__\n\n"
    "TEST_FLGS = -Itests $(CFLAGS_LIBS)\n\n"
    "INSTALL_BASE = $(HOME)/Support/bin\n"
    "INSTALLDIR = $(INSTALL_BASE)\n"
    "LIBDIR = $(BASEDIR)/$(SYS)\n"
    "SRCDIR = ./src\n"
    "SRCSYSDIR = ./src/$(SYS)\n"
    "TEST_SRC = ./tests\n"
    "ifdef  NDEBUG\n"
    "CFLAGS += -DNDEBUG\n"
    "LIB_FILENAME=$(LIBNAM)R.a\n"
    "OBJDIR = $(LIBDIR)/o/r\n"
    "else   #DEBUG\n"
    "CFLAGS += -D_DEBUG \n"
    "LIB_FILENAME=$(LIBNAM)D.a\n"
    "OBJDIR = $(LIBDIR)/o/d\n"
    "endif  #NDEBUG\n"
    "TEST_OBJ = $(OBJDIR)/tests\n"
    "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n\n"
    ".SUFFIXES:\n"
    ".SUFFIXES: .asm .c .o\n\n"
    "OBJS = \n\n"
    "TESTS = \n\n"
    "\n\n\n\n"
    ;
    int                 iRc;
    int                 offset = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        genBase_setMakeType((GENBASE_DATA *)pObj, GENMAKE_TYPE_PGM);
        
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, namePrefixID, "lib");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, nameID, "Test");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr =  genOSX_GenInitial(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=0x%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genOSX_GenFinal01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
    "\n\n\n"
    "$(LIBPATH):  $(OBJS)\n"
    "\t-cd $(LIBDIR) ; [ -d $(LIB_FILENAME) ] && rm $(LIB_FILENAME)\n"
    "\tar rc $(LIBPATH) $(OBJS)\n\n\n\n"
    ".PHONY: test\n"
    "test: $(TESTS)\n\n\n"
    ".PHONY: clean\n"
    "clean:\n"
    "\t-cd $(TEMP) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
    "\n\n.PHONY: install\ninstall:\n"
    "\t-cd $(INSTALL_BASE) ; [ -d $(LIBNAM) ] && rm -fr $(LIBNAM)\n"
    "\t-cd $(INSTALL_BASE) ; "
    "[ ! -d $(LIBNAM)/include ] && "
    "mkdir -p $(LIBNAM)/include/$(SYS)\n"
    "\tcp $(LIBPATH) $(INSTALLDIR)/$(LIBNAM).a\n"
    "\tcp src/*.h $(INSTALLDIR)/include/\n"
    "\tif [ -d src/$(SYS) ]; then \\\n"
    "\t\tcp src/$(SYS)/*.h $(INSTALLDIR)/include/$(SYS)/; \\\n"
    "\tfi\n\n\n"
    ".PHONY: create_dirs\n"
    "create_dirs:\n"
    "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)/tests\n\n\n"
    ".PHONY: all\n"
    "all:  clean create_dirs $(LIBPATH)\n\n\n\n"
    ;
    int                 iRc;
    int                 offset = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        genBase_setMakeType((GENBASE_DATA *)pObj, GENMAKE_TYPE_LIB);
        
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, namePrefixID, "lib");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, nameID, "Test");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr =  genOSX_GenFinal(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=0x%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_genOSX_GenFinal02(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    GENOSX_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    const
    char            *pOutputA =
    "\n\n\n"
    ".PHONY: test\n"
    "test: $(TESTS)\n\n\n"
    ".PHONY: clean\n"
    "clean:\n"
    "\t-cd $(TEMP) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n\n\n"
    ".PHONY: install\ninstall:\n"
    "\t-cd $(INSTALL_BASE) ; [ -d $(PGMNAM) ] && rm -fr $(PGMNAM)\n"
    "\tcp $(OBJDIR)/$(PGMNAM) $(INSTALLDIR)/$(PGMNAM)\n\n\n"
    ".PHONY: link\nlink: $(OBJS) src/main.c\n"
    "\tCC -o $(OBJDIR)/$(PGMNAM) $(CFLAGS) $(CFLAGS_LIBS) $^\n\n\n"
    ".PHONY: create_dirs\n"
    "create_dirs:\n"
    "\t[ ! -d $(OBJDIR) ] && mkdir -p $(OBJDIR)/tests\n\n\n"
    ".PHONY: all\n"
    "all:  clean create_dirs link\n\n\n\n"
    ;
    int                 iRc;
    int                 offset = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = genOSX_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = genOSX_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        genBase_setMakeType((GENBASE_DATA *)pObj, GENMAKE_TYPE_PGM);
        
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, mainID, "main.c");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, namePrefixID, "lib");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        eRc = genBase_DictAddA((GENBASE_DATA *)pObj, nameID, "Test");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pStr =  genOSX_GenFinal(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "\t\"%s\"\n", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=0x%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_genOSX);
    TINYTEST_ADD_TEST(test_genOSX_GenFinal02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_GenFinal01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_GenInitial02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_GenInitial01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_Routine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_genOSX_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_genOSX);





