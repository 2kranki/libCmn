/*
 *	Generated 10/28/2017 08:51:04
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
#include    <objMethod_internal.h>



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






int         test_objMethod_OpenClose(
    const
    char        *pTestName
)
{
    OBJMETHOD_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = objMethod_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = objMethod_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_objMethod_Create01(
        const
        char        *pTestName
)
{
    OBJMETHOD_DATA  *pObj = OBJ_NIL;
    OBJMETHOD_DATA  *pObj2 = OBJ_NIL;
    void            *pVoid;
    OBJ_ID          pObj3;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = objMethod_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pObj2 = objMethod_NewObjectA((OBJ_ID)pObj, "ToJSON");
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        if (pObj2) {
            
            pObj3 = objMethod_getObject(pObj2);
            TINYTEST_FALSE( (OBJ_NIL == pObj3) );
            TINYTEST_TRUE( (pObj == pObj3) );
            
            pVoid = objMethod_getMethod(pObj2);
            TINYTEST_FALSE( (OBJ_NIL == pVoid) );
            TINYTEST_TRUE( (objMethod_ToJSON == pVoid) );

            obj_Release(pObj2);
            pObj2 = OBJ_NIL;
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_objMethod);
    TINYTEST_ADD_TEST(test_objMethod_Create01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_objMethod_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_objMethod);





