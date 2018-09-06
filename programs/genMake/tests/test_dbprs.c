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
        "$(OBJDIR)/AStr.o: $(SRCDIR)/AStr.c \n"
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
        
        obj_TraceSet(pObj, true);
        eRc = dbprs_ParseInputStr(pObj, pGoodJsonObject1);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pNode = dbprs_getNodes(pObj);
        TINYTEST_FALSE( (OBJ_NIL == pNode) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        pNode = nodeHash_FindA((NODEHASH_DATA *)node_getData(pNode), "AStr");
        TINYTEST_FALSE( (OBJ_NIL == pObj) );
        TINYTEST_TRUE( (obj_IsKindOf(pNode, OBJ_IDENT_NODE)) );
        eRc = dbprs_ParseObject(pObj, pNode);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        pStr = dbprs_getStr(pObj);
        fprintf(stderr, "\t\"%s\"", AStr_getData(pStr));
        TINYTEST_TRUE( (0 == strcmp(pOutputA, AStr_getData(pStr))) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    obj_Release(pGen);
    pGen = OBJ_NIL;

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_dbprs);
    TINYTEST_ADD_TEST(test_dbprs_Object01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_dbprs_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_dbprs);





