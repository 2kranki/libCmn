// vi:nu:et:sts=4 ts=4 sw=4
/*
 *  Generated 05/04/2021 09:30:56
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
#include    <test_defs.h>
#include    <trace.h>
#include    <Consumer_internal.h>
#include    <AStrArray.h>
#include    <JsonIn.h>
#ifdef  CONSUMER_JSON_SUPPORT
#   include    <SrcErrors.h>
#   include    <szTbl.h>
#endif



#define NUM_STR     10

static
char        *szStrArray[NUM_STR] = {
//   123456789012
    "String    1",
    "String    2",
    "String    3",
    "String    4",
    "String    5",
    "String    6",
    "String    7",
    "String    8",
    "String    9",
    "String   10"
};


int         cStrs = 0;
ASTR_DATA   *pStrs[NUM_STR+1];


static
void        printMsg(
    void        *pObj,
    char        *pMsg
)
{
    fprintf(stderr, "  Recieved - %s\n", pMsg);
}


static
void        HandleObject(
    void            *pThis,
    OBJ_ID          *pObj
)
{
    CONSUMER_DATA   *this = (CONSUMER_DATA *)pThis;
    ASTR_DATA       *pStr = (ASTR_DATA *)pObj;
    ASTRARRAY_DATA  *pArray;

    pArray = Consumer_getOther(this);
    if (pArray && pStr) {
        AStrArray_AppendStr(pArray, pStr, NULL);
    }
    fprintf(stderr, "  Recieved - %s\n", AStr_getData(pStr));
    obj_Release(pStr);
    pStr = OBJ_NIL;
}






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

#ifdef  CONSUMER_JSON_SUPPORT
    SrcErrors_SharedReset( );
    szTbl_SharedReset( );
#endif
    JsonIn_RegisterReset();
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






int             test_Consumer_OpenClose (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CONSUMER_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Consumer_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = Consumer_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CONSUMER);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Consumer_Copy01 (
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    CONSUMER_DATA       *pObj1 = OBJ_NIL;
    CONSUMER_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(CONSUMER_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = Consumer_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj1) );
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_CONSUMER);
        TINYTEST_TRUE( (fRc) );
        
        // Test assign.
        pObj2 = Consumer_New();
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        eRc = Consumer_Assign(pObj1, pObj2);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CONSUMER);
        TINYTEST_TRUE( (fRc) );
        //eRc = Consumer_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = Consumer_Copy(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CONSUMER);
        TINYTEST_TRUE( (fRc) );
        //eRc = Consumer_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(CONSUMER_JSON_SUPPORT) && defined(XYZZY)
        pStr = Consumer_ToJson(pObj1);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = Consumer_NewFromJsonString(pStr);
        TINYTEST_FALSE( (OBJ_NIL == pObj2) );
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_CONSUMER);
        TINYTEST_TRUE( (fRc) );
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //eRc = Consumer_Compare(pObj1, pObj2);
        //TINYTEST_TRUE( (ERESULT_SUCCESS_EQUAL == eRc) );

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_Consumer_Test01 (
    const
    char            *pTestName
)
{
    //ERESULT         eRc = ERESULT_SUCCESS;
    CONSUMER_DATA   *pObj = OBJ_NIL;
    ASTR_DATA       *pStr = OBJ_NIL;
    ASTRARRAY_DATA  *pArray = OBJ_NIL;
    bool            fRc;
    int             i;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = Consumer_New( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pArray = AStrArray_New();
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        Consumer_setOther(pObj, pArray);        // for HandleObject()
        Consumer_setService(pObj, (void *)HandleObject, (OBJ_ID)pObj);

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_CONSUMER);
        TINYTEST_TRUE( (fRc) );
        //TINYTEST_TRUE( (ERESULT_OK(eRc)) );

        for (i=0; i<NUM_STR; i++) {
            pStr = AStr_NewA(szStrArray[i]);
            TINYTEST_FALSE( (OBJ_NIL == pStr) );
            fRc = Consumer_Send(pObj, pStr, true);
            TINYTEST_TRUE( (fRc) );
            obj_Release(pStr);
            pStr = OBJ_NIL;
        }

        {
            ASTR_DATA       *pStr = Consumer_ToDebugString(pObj, 0);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pArray);
        pArray = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_Consumer);
    TINYTEST_ADD_TEST(test_Consumer_Test01,setUp,tearDown);
    //TINYTEST_ADD_TEST(test_Consumer_Copy01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_Consumer_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_Consumer);





