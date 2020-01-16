// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 01/14/2020 16:31:30
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
#include    <SrcErrors.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <ObjVLink_internal.h>



int             setUp (
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


int             tearDown (
    const
    char            *pTestName
)
{
    // Put teardown code here. This method is called after the invocation of each
    // test method in the class.

    SrcErrors_SharedReset( );
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






int             test_ObjVLink_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJVLINK_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjVLink_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ObjVLink_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJVLINK);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ObjVLink_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    OBJVLINK_DATA	*pObj1 = OBJ_NIL;
    OBJVLINK_DATA	*pObj2 = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = ObjVLink_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_OBJVLINK);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = ObjVLink_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = ObjVLink_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJVLINK);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = ObjVLink_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_OBJVLINK);
        TINYTEST_TRUE( (fRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_ObjVLink_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    OBJVLINK_DATA	*pObj = OBJ_NIL;
    bool            fRc;
    int32_t         i;
    int32_t         num;
    int32_t         amt;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = ObjVLink_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = ObjVLink_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_OBJVLINK);
        TINYTEST_TRUE( (fRc) );

        for (i=0; i<32; i++) {
            num = i + 1;
            amt = ObjVLink_Set(pObj, num, num);
            amt = ObjVLink_Get(pObj, num);
            if (amt != num) {
                fprintf(stderr, "num=%d amt=%d\n", num, amt);
            }
            TINYTEST_TRUE( (amt == num) );
        }

        amt = ObjVLink_Get(pObj, OBJVLINK_INDEX_INDEX);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_INDEX) );
        amt = ObjVLink_getIndex(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_INDEX) );
        ObjVLink_setIndex(pObj, OBJVLINK_INDEX_INDEX+1);
        amt = ObjVLink_getIndex(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_INDEX+1) );

        amt = ObjVLink_Get(pObj, OBJVLINK_INDEX_LEFT);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_LEFT) );
        amt = ObjVLink_getLeft(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_LEFT) );
        ObjVLink_setLeft(pObj, OBJVLINK_INDEX_LEFT+1);
        amt = ObjVLink_getLeft(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_LEFT+1) );

        amt = ObjVLink_Get(pObj, OBJVLINK_INDEX_MIDDLE);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_MIDDLE) );
        amt = ObjVLink_getMiddle(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_MIDDLE) );
        ObjVLink_setMiddle(pObj, OBJVLINK_INDEX_MIDDLE+1);
        amt = ObjVLink_getMiddle(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_MIDDLE+1) );

        amt = ObjVLink_Get(pObj, OBJVLINK_INDEX_MISC);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_MISC) );
        amt = ObjVLink_getMisc(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_MISC) );
        ObjVLink_setMisc(pObj, OBJVLINK_INDEX_MISC+1);
        amt = ObjVLink_getMisc(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_MISC+1) );

        amt = ObjVLink_Get(pObj, OBJVLINK_INDEX_PARENT);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_PARENT) );
        amt = ObjVLink_getParent(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_PARENT) );
        ObjVLink_setParent(pObj, OBJVLINK_INDEX_PARENT+1);
        amt = ObjVLink_getParent(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_PARENT+1) );

        amt = ObjVLink_Get(pObj, OBJVLINK_INDEX_RIGHT);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_RIGHT) );
        amt = ObjVLink_getRight(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_RIGHT) );
        ObjVLink_setRight(pObj, OBJVLINK_INDEX_RIGHT+1);
        amt = ObjVLink_getRight(pObj);
        TINYTEST_TRUE( (amt == OBJVLINK_INDEX_RIGHT+1) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_ObjVLink);
    TINYTEST_ADD_TEST(test_ObjVLink_Test01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjVLink_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_ObjVLink_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_ObjVLink);





