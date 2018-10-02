/*
 *	Generated 09/04/2018 13:50:27
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
#include    <genOSX.h>
#include    <genWIN.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <dbprs_internal.h>





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

    
    szTbl_SharedReset( );
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






int             test_dbprs_OpenClose(
    const
    char            *pTestName
)
{
    DBPRS_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_dbprs_Object01(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENOSX_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    int             iRc;
    int             offset = 0;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    const
    char            *pGoodJsonObject1 = "{\n"
        "\"AStr\":{"
            "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
            "\"json\":true,"
            "\"test\":true"
        "}\n"
    "}\n";
    const
    char            *pOutputA =
        "OBJS += $(OBJDIR)/AStr_object.o\n\n"
        "$(OBJDIR)/AStr_object.o: $(SRCDIR)/AStr_object.c \n"
        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
        "OBJS += $(OBJDIR)/AStr.o\n\n"
        "$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c $(SRCDIR)/cmn_defs.h $(SRCDIR)/array.h \n"
        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
        "OBJS += $(OBJDIR)/AStr_JSON.o\n\n"
        "$(OBJDIR)/AStr_JSON.o: $(SRCDIR)/AStr_JSON.c \n"
        "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
        "TESTS += test_AStr\n\n"
        "test_AStr: $(TEST_SRC)/test_AStr.c \n"
        "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $< \n"
        "\t$(TEST_OBJ)/$(@F)\n\n"
    ;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genOSX_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        
        //obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "AStr");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseObject(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_dbprs_Object02(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENOSX_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    const
    char            *pGoodJsonObject1 = "{\n"
    "\"appl\":{"
    "\"deps\":[\"cmn_defs.h\",\"cmdutl.h\"],"
    "\"test\":{\"srcs\":[objTest.c, objTest_object.c]}"
    "}\n"
    "}\n";
    const
    char            *pOutputA =
    "OBJS += $(OBJDIR)/appl_object.o\n\n"
    "$(OBJDIR)/appl_object.o: $(SRCDIR)/appl_object.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "OBJS += $(OBJDIR)/appl.o\n\n"
    "$(OBJDIR)/appl.o: $(SRCDIR)/appl.c $(SRCDIR)/cmn_defs.h $(SRCDIR)/cmdutl.h \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "TESTS += test_appl\n\n"
    "test_appl: $(TEST_SRC)/test_appl.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $< "
            "$(TEST_SRC)/objTest.c $(TEST_SRC)/objTest_object.c \n"
    "\t$(TEST_OBJ)/$(@F)\n\n"
    ;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genOSX_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        
        obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "appl");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseObject(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_dbprs_Object03(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENWIN_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    const
    char            *pGoodJsonObject1 = "{\n"
    "\"AStr\":{"
    "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
    "\"json\":true,"
    "\"test\":true"
    "}\n"
    "}\n";
    const
    char            *pOutputA =
    "OBJS = $(OBJS) $(OBJDIR)\\AStr_object.obj\n\n"
    "$(OBJDIR)\\AStr_object.obj: $(SRCDIR)\\AStr_object.c \n"
    "\t$(CC) $(CFLAGS) /c /out:$(OBJDIR)\\$(@F) $< \n\n"
    "OBJS = $(OBJS) $(OBJDIR)\\AStr.obj\n\n"
    "$(OBJDIR)\\AStr.obj: $(SRCDIR)\\AStr.c $(SRCDIR)\\cmn_defs.h $(SRCDIR)\\array.h \n"
    "\t$(CC) $(CFLAGS) /c /out:$(OBJDIR)\\$(@F) $< \n\n"
    "OBJS = $(OBJS) $(OBJDIR)\\AStr_JSON.obj\n\n"
    "$(OBJDIR)\\AStr_JSON.obj: $(SRCDIR)\\AStr_JSON.c \n"
    "\t$(CC) $(CFLAGS) /c /out:$(OBJDIR)\\$(@F) $< \n\n"
    "TESTS = $(TESTS) test_AStr\n\n"
    "test_AStr: $(TEST_SRC)\\test_AStr.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) /out:$(TEST_OBJ)\\$(@F) $< \n"
    "\t$(TEST_OBJ)\\$(@F)\n\n"
    ;
    int             iRc;
    int             offset = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genWIN_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        
        obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "AStr");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseObject(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_dbprs_Object04(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENOSX_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    const
    char            *pGoodJsonObject1 = "{\n"
    "\"appl\":{"
    "\"deps\":[\"cmn_defs.h\",\"cmdutl.h\"],"
    "\"test\":{\"srcs\":[objTest.c, objTest_object.c]}"
    "}\n"
    "}\n";
    const
    char            *pOutputA =
    "OBJS += $(OBJDIR)/appl_object.o\n\n"
    "$(OBJDIR)/appl_object.o: $(SRCDIR)/appl_object.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "OBJS += $(OBJDIR)/appl.o\n\n"
    "$(OBJDIR)/appl.o: $(SRCDIR)/appl.c $(SRCDIR)/cmn_defs.h $(SRCDIR)/cmdutl.h \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "TESTS += test_appl\n\n"
    "test_appl: $(TEST_SRC)/test_appl.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $< "
    "$(TEST_SRC)/objTest.c $(TEST_SRC)/objTest_object.c \n"
    "\t$(TEST_OBJ)/$(@F)\n\n"
    ;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genOSX_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        
        obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "appl");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseObject(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_dbprs_Object05(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENOSX_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    int             iRc;
    int             offset = 0;
    const
    char            *pGoodJsonObject1 = "[\n"
    "\"appl\""
    "]\n";
    const
    char            *pOutputA =
    "OBJS += $(OBJDIR)/appl_object.o\n\n"
    "$(OBJDIR)/appl_object.o: $(SRCDIR)/appl_object.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "OBJS += $(OBJDIR)/appl.o\n\n"
    "$(OBJDIR)/appl.o: $(SRCDIR)/appl.c \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "TESTS += test_appl\n\n"
    "test_appl: $(TEST_SRC)/test_appl.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $< \n"
    "\t$(TEST_OBJ)/$(@F)\n\n"
    ;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genOSX_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        
        obj_TraceSet(pObj, true);
        pStr = AStr_NewA("appl");
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        pNode = node_NewWithUTF8AndClass("string", 0, pStr);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        obj_Release(pStr);
        pStr = OBJ_NIL;

        eRc = dbprs_ParseObject(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pNode);
        pNode = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_dbprs_Routine01(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENOSX_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    const
    char            *pGoodJsonObject1 = "{\n"
        "\"listdl.c\":{"
            "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
            "\"test\":true"
        "}\n"
    "}\n";
    const
    char            *pOutputA =
    "OBJS += $(OBJDIR)/listdl.o\n\n"
    "$(OBJDIR)/listdl.o: $(SRCDIR)/listdl.c $(SRCDIR)/cmn_defs.h $(SRCDIR)/array.h \n"
    "\t$(CC) $(CFLAGS) -c -o $(OBJDIR)/$(@F) $< \n\n"
    "TESTS += test_listdl\n\n"
    "test_listdl: $(TEST_SRC)/test_listdl.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) -o $(TEST_OBJ)/$(@F) $< \n"
    "\t$(TEST_OBJ)/$(@F)\n\n"
    ;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genOSX_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        
        obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "listdl.c");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseRoutine(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        TINYTEST_TRUE( (0 == strcmp(pOutputA, AStr_getData(pStr))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_dbprs_Routine02(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENWIN_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    const
    char            *pGoodJsonObject1 =
    "{\n"
        "\"listdl.c\":{"
            "\"deps\":[\"cmn_defs.h\",\"array.h\"],"
            "\"test\":true"
        "}\n"
    "}\n";
    const
    char            *pOutputA =
    "OBJS = $(OBJS) $(OBJDIR)\\listdl.obj\n\n"
    "$(OBJDIR)\\listdl.obj: $(SRCDIR)\\listdl.c $(SRCDIR)\\cmn_defs.h $(SRCDIR)\\array.h \n"
    "\t$(CC) $(CFLAGS) /c /out:$(OBJDIR)\\$(@F) $< \n\n"
    "TESTS = $(TESTS) test_listdl\n\n"
    "test_listdl: $(TEST_SRC)\\test_listdl.c \n"
    "\t$(CC) $(CFLAGS) $(TEST_FLGS) /out:$(TEST_OBJ)\\$(@F) $< \n"
    "\t$(TEST_OBJ)\\$(@F)\n\n"
    ;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen = genWIN_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    
    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        
        //obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "listdl.c");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseRoutine(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        TINYTEST_TRUE( (0 == strcmp(pOutputA, AStr_getData(pStr))) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}



int             test_dbprs_Library01(
    const
    char            *pTestName
)
{
    DBPRS_DATA      *pObj = OBJ_NIL;
    GENOSX_DATA     *pGen = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr = OBJ_NIL;
    NODE_DATA       *pNode = OBJ_NIL;
    NODEHASH_DATA   *pDict = OBJ_NIL;
    NODEHASH_DATA   *pHash = OBJ_NIL;
    int             offset = 0;
    int             iRc;
    const
    char            *pGoodJsonObject =
    "{\n"
        "\"library\":{"
            "\"name\":\"Test\","
            "\"deps\":null,"
            "\"libdir\":\"path_libdir\","
            "\"objdir\":\"path_objdir\""
        "}\n"
    "}\n";
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
    "INSTALL_BASE = $(HOME)/Support/lib/$(SYS)\n"
    "INSTALLDIR = $(INSTALL_BASE)/$(LIBNAM)\n"
    "LIBDIR = $(BASEDIR)/$(SYS)\n"
    "SRCDIR = ./src\n"
    "SRCSYSDIR = ./src/$(SYS)\n"
    "ifdef  NDEBUG\n"
    "CFLAGS += -DNDEBUG\n"
    "LIB_FILENAME=$(LIBNAM)R.a\n"
    "OBJDIR = $(LIBDIR)/o/r\n"
    "else   #DEBUG\n"
    "CFLAGS += -D_DEBUG \n"
    "LIB_FILENAME=$(LIBNAM)D.a\n"
    "OBJDIR = $(LIBDIR)/o/d\n"
    "endif  #NDEBUG\n"
    "LIBPATH = $(LIBDIR)/$(LIB_FILENAME)\n\n"
    ".SUFFIXES:\n"
    ".SUFFIXES: .asm .c .o\n\n"
    "OBJS = \n\n"
    "TESTS = \n\n"
    "\n\n\n\n"
    ;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pGen  = genOSX_New(OBJ_NIL);
    TINYTEST_FALSE( (OBJ_NIL == pGen) );
    pDict = nodeHash_New(NODEHASH_TABLE_SIZE_XXXSMALL);
    TINYTEST_FALSE( (OBJ_NIL == pDict) );
    genBase_setDict((GENBASE_DATA *)pGen, pDict);

    pObj = dbprs_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = dbprs_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        dbprs_setGen(pObj, (GENBASE_DATA *)pGen);
        dbprs_setDict(pObj, pDict);
        
        obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "library");
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pHash = jsonIn_CheckNodeDataForHash(pNode);
        
        eRc = dbprs_ParseLibrary(pObj, pHash);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        iRc = str_CompareSpcl(pOutputA, AStr_getData(pStr), &offset);
        fprintf(stderr, "\tiRc=%d  offset=%04X\n", iRc, offset);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pDict);
    pDict = OBJ_NIL;
    obj_Release(pGen);
    pGen = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_dbprs);
    TINYTEST_ADD_TEST(test_dbprs_Library01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_Routine02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_Routine01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_Object05,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_Object04,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_Object03,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_Object02,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_dbprs);





