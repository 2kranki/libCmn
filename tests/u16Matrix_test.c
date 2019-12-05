/*
 *	Generated 06/05/2017 21:57:10
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
#include    <u16Matrix_internal.h>



uint16_t        valueCheckGet(
    MATRIX_BUILD    *pBuild,
    uint32_t        i,
    uint32_t        j
)
{
    uint32_t        base;
    uint32_t        index;
    uint32_t        highest = pBuild->highest;
    uint16_t        value = 0;

    base = pBuild->pBase[i-1];
    index = base + j - 1;
    if (index >= highest)
        ;
    else {
        if (pBuild->pCheck[index] == i) {
            value = pBuild->pValue[index];
        }
    }
    
    return value;
}



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






int         test_u16Matrix_OpenClose(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u16Matrix_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = u16Matrix_Init( pObj, 4, 4 );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    pObj = u16Matrix_NewSquare(4);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u16Matrix_SetGet01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    uint16_t        max = 4;
    uint16_t        value = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u16Matrix_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u16Matrix_Init(pObj, max, max);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (0 == value) );
        
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        eRc = u16Matrix_Set(pObj, 1, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (0 == value) );

        eRc = u16Matrix_Set(pObj, 2, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 2, 3);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 2, 4);
        XCTAssertTrue( (0 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 3);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (0 == value) );
        
        eRc = u16Matrix_Set(pObj, 4, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 4, 4);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 4, 3);
        XCTAssertTrue( (0 == value) );
        
        pStr = u16Matrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u16Matrix_SetGet02(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    ASTR_DATA       *pStr;
    uint16_t        max = 4;
    uint16_t        value = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u16Matrix_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u16Matrix_Init( pObj, (2 * max), max );
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        eRc = u16Matrix_Set(pObj, 1, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 2, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 3);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 4, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 4, 4);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 5, 1, 100);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 5, 1);
        XCTAssertTrue( (100 == value) );
        
        pStr = u16Matrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u16Matrix_Identity01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA	*pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    uint16_t        value = 0;
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u16Matrix_NewIdentity(2);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (1 == value) );
        
        pStr = u16Matrix_ToDebugString(pObj, 0);
        fprintf(stderr, "%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;

#ifdef XYZZY
        pStr = u16Matrix_CompressedTable(pObj, "test");
        fprintf(stderr, "%s\n\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
#endif
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u16Matrix_Multiply01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA	*pObj = OBJ_NIL;
    U16MATRIX_DATA	*pObj2 = OBJ_NIL;
    U16MATRIX_DATA	*pResult = OBJ_NIL;
    ERESULT         eRc;
    uint16_t        value = 0;
    
    /*
     1   2    0  1    4  7
            X       =
     3   4    2  3    8  15
     */
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u16Matrix_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u16Matrix_Init(pObj, 2, 2);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        eRc = u16Matrix_Set(pObj, 1, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 1, 2, 2);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (2 == value) );
        
        eRc = u16Matrix_Set(pObj, 2, 1, 3);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (3 == value) );
        
        eRc = u16Matrix_Set(pObj, 2, 2, 4);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (4 == value) );
        
        pObj2 = u16Matrix_Alloc();
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        pObj2 = u16Matrix_Init(pObj2, 2, 2);
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        if (pObj2) {
            
            value = u16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (0 == value) );
            eRc = u16Matrix_Set(pObj2, 1, 1, 0);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (0 == value) );
            
            eRc = u16Matrix_Set(pObj2, 1, 2, 1);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 1, 2);
            XCTAssertTrue( (1 == value) );
            
            eRc = u16Matrix_Set(pObj2, 2, 1, 2);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 2, 1);
            XCTAssertTrue( (2 == value) );
            
            eRc = u16Matrix_Set(pObj2, 2, 2, 3);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 2, 2);
            XCTAssertTrue( (3 == value) );
            
            pResult = u16Matrix_Multiply(pObj, pObj2);
            XCTAssertFalse( (OBJ_NIL == pResult) );
            XCTAssertTrue( (2 == u16Matrix_getM(pResult)) );
            XCTAssertTrue( (2 == u16Matrix_getN(pResult)) );
            
            if (pResult) {

                value = u16Matrix_getN(pResult);
                fprintf(stderr, "n = %d\n", value);
                XCTAssertTrue( (2 == value) );
                value = u16Matrix_getN(pResult);
                fprintf(stderr, "m = %d\n", value);
                XCTAssertTrue( (2 == value) );
                
                value = u16Matrix_Get(pResult, 1, 1);
                fprintf(stderr, "(1,1) = %d need 4\n", value);
                XCTAssertTrue( (4 == value) );
                
                value = u16Matrix_Get(pResult, 1, 2);
                fprintf(stderr, "(1,2) = %d need 7\n", value);
                XCTAssertTrue( (7 == value) );
                
                value = u16Matrix_Get(pResult, 2, 1);
                fprintf(stderr, "(2,1) = %d need 8\n", value);
                XCTAssertTrue( (8 == value) );
                
                value = u16Matrix_Get(pResult, 2, 2);
                fprintf(stderr, "(2,2) = %d need 15\n", value);
                XCTAssertTrue( (15 == value) );
                
                obj_Release(pResult);
                pResult = OBJ_NIL;
            }
            
            obj_Release(pObj2);
            pObj2 = OBJ_NIL;
        }
            
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u16Matrix_Multiply02(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA	*pObj = OBJ_NIL;
    U16MATRIX_DATA	*pObj2 = OBJ_NIL;
    U16MATRIX_DATA	*pResult = OBJ_NIL;
    ERESULT         eRc;
    uint16_t        value = 0;
    
    /*
     0 0 1 1     12     15
     1 0 0 0  X   4  =  12
     1 1 0 1      9     22
     1 1 0 0      6     16
     */
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u16Matrix_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u16Matrix_Init(pObj, 4, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        value = u16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        eRc = u16Matrix_Set(pObj, 1, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 1, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 2, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 4, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 4, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (1 == value) );
        
        pObj2 = u16Matrix_Alloc();
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        pObj2 = u16Matrix_Init(pObj2, 4, 1);
        XCTAssertFalse( (OBJ_NIL == pObj2) );
        if (pObj2) {
            
            value = u16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (0 == value) );
            eRc = u16Matrix_Set(pObj2, 1, 1, 12);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 1, 1);
            XCTAssertTrue( (12 == value) );
            
            eRc = u16Matrix_Set(pObj2, 2, 1, 4);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 2, 1);
            XCTAssertTrue( (4 == value) );
            
            eRc = u16Matrix_Set(pObj2, 3, 1, 9);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 3, 1);
            XCTAssertTrue( (9 == value) );
            
            eRc = u16Matrix_Set(pObj2, 4, 1, 6);
            XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
            value = u16Matrix_Get(pObj2, 4, 1);
            XCTAssertTrue( (6 == value) );
            
            pResult = u16Matrix_Multiply(pObj, pObj2);
            XCTAssertFalse( (OBJ_NIL == pResult) );
            
            if (pResult) {
                
                value = u16Matrix_getM(pResult);
                fprintf(stderr, "m = %d need 4\n", value);
                XCTAssertTrue( (4 == value) );
                value = u16Matrix_getN(pResult);
                fprintf(stderr, "n = %d need 1\n", value);
                XCTAssertTrue( (1 == value) );
                
                value = u16Matrix_Get(pResult, 1, 1);
                fprintf(stderr, "(1,1) = %d need 15\n", value);
                XCTAssertTrue( (15 == value) );
                value = u16Matrix_Get(pResult, 2, 1);
                fprintf(stderr, "(2,1) = %d need 12\n", value);
                XCTAssertTrue( (12 == value) );
                value = u16Matrix_Get(pResult, 3, 1);
                fprintf(stderr, "(3,1) = %d need 22\n", value);
                XCTAssertTrue( (22 == value) );
                value = u16Matrix_Get(pResult, 4, 1);
                fprintf(stderr, "(4,1) = %d need 16\n", value);
                XCTAssertTrue( (16 == value) );
                
                obj_Release(pResult);
                pResult = OBJ_NIL;
            }
            
            obj_Release(pObj2);
            pObj2 = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}



int         test_u16Matrix_ValueCheck01(
    const
    char        *pTestName
)
{
    U16MATRIX_DATA	*pObj = OBJ_NIL;
    ERESULT         eRc;
    uint16_t        value = 0;
    MATRIX_BUILD    *pBuild;
    uint32_t        i = 0;
    uint32_t        iMax = 0;
    
    /*
     0 0 1 1
     1 0 0 0
     1 1 0 1
     1 1 0 0
     */
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = u16Matrix_Alloc();
    XCTAssertFalse( (OBJ_NIL == pObj) );
    pObj = u16Matrix_Init(pObj, 4, 4);
    XCTAssertFalse( (OBJ_NIL == pObj) );
    if (pObj) {
        
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        
        value = u16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (0 == value) );
        eRc = u16Matrix_Set(pObj, 1, 3, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 1, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 2, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 3, 4, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 4, 1, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (1 == value) );
        
        eRc = u16Matrix_Set(pObj, 4, 2, 1);
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(eRc)) );
        value = u16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (1 == value) );
        
        value = u16Matrix_Get(pObj, 1, 1);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 2);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 1, 3);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 1, 4);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 2, 1);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 2, 2);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 2, 3);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 2, 4);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 3, 1);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 3, 2);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 3, 3);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 3, 4);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 4, 1);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 4, 2);
        XCTAssertTrue( (1 == value) );
        value = u16Matrix_Get(pObj, 4, 3);
        XCTAssertTrue( (0 == value) );
        value = u16Matrix_Get(pObj, 4, 4);
        XCTAssertTrue( (0 == value) );

        pBuild = u16Matrix_BuildValueCheck(pObj);
        XCTAssertFalse( (NULL == pBuild) );
        XCTAssertTrue( (ERESULT_IS_SUCCESSFUL(u16Matrix_getLastError(pObj))) );
        
        if (pBuild) {
            
            if (pBuild->m > pBuild->highest) {
                iMax = pBuild->m;
            }
            else {
                iMax = pBuild->highest;
            }
            fprintf(stderr, "\n\n     Base Check Value\n");
            for (i=0; i<iMax; ++i) {
                fprintf(stderr, "%3d  ", i);
                if (i+1 <= pBuild->m) {
                    fprintf(stderr, "%3d  ", pBuild->pBase[i]);
                }
                else {
                    fprintf(stderr, "     ");
                }
                if (i < pBuild->highest) {
                    fprintf(stderr, "%3d  %3d\n", pBuild->pCheck[i], pBuild->pValue[i]);
                }
                else {
                    fprintf(stderr, "\n");
                }
            }
            fprintf(stderr, "\n\n\n");

            value = valueCheckGet(pBuild, 1, 1);
            fprintf(stderr, "(1,1) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 1, 2);
            fprintf(stderr, "(1,2) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 1, 3);
            fprintf(stderr, "(1,3) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 1, 4);
            fprintf(stderr, "(1,4) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            
            value = valueCheckGet(pBuild, 2, 1);
            fprintf(stderr, "(2,1) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 2, 2);
            fprintf(stderr, "(2,2) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 2, 3);
            fprintf(stderr, "(2,3) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 2, 4);
            fprintf(stderr, "(2,4) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            
            value = valueCheckGet(pBuild, 3, 1);
            fprintf(stderr, "(3,1) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 3, 2);
            fprintf(stderr, "(3,2) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 3, 3);
            fprintf(stderr, "(3,3) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 3, 4);
            fprintf(stderr, "(3,4) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            
            value = valueCheckGet(pBuild, 4, 1);
            fprintf(stderr, "(4,1) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 4, 2);
            fprintf(stderr, "(4,2) = %d need 1\n", value);
            XCTAssertTrue( (1 == value) );
            value = valueCheckGet(pBuild, 4, 3);
            fprintf(stderr, "(4,3) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            value = valueCheckGet(pBuild, 4, 4);
            fprintf(stderr, "(4,4) = %d need 0\n", value);
            XCTAssertTrue( (0 == value) );
            
            u16Matrix_FreeValueCheck(pObj, pBuild);
            pBuild = OBJ_NIL;
        }
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_u16Matrix);
  TINYTEST_ADD_TEST(test_u16Matrix_ValueCheck01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u16Matrix_Multiply02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u16Matrix_Multiply01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u16Matrix_Identity01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u16Matrix_SetGet02,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u16Matrix_SetGet01,setUp,tearDown);
  TINYTEST_ADD_TEST(test_u16Matrix_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_u16Matrix);





