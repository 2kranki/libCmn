/*
 *	Generated 04/01/2018 21:11:43
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
#include    <md5ChkSum_internal.h>
#include    <file.h>
#include    <fileio.h>



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






int             test_md5ChkSum_OpenClose(
    const
    char            *pTestName
)
{
    MD5CHKSUM_DATA	    *pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = md5ChkSum_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = md5ChkSum_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int         test_md5ChkSum_Read01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    MD5CHKSUM_DATA	*pChkSum = OBJ_NIL;
    FILEIO_DATA     *pObj = OBJ_NIL;
    PATH_DATA       *pPath = OBJ_NIL;
    const
    char            *pPathA = "/Users/bob/Support/testFiles/test_ebcdic.txt";
    int64_t         fileSize = 0;
    uint8_t         *pBuffer = NULL;
    const
    uint8_t         *pDigest = NULL;
    int             iRc;
    const
    uint8_t         answer[16] = {0xeb,0x25,0xa3,0x26,0xf0,0x21,0xac,0xcd,0x3e,0xb7,0xb6,0x1f,0xe2,0xd5,0x7d,0xc3};
    
    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pPath = path_NewA(pPathA);
    TINYTEST_FALSE( (OBJ_NIL == pPath) );

    pObj = fileio_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = fileio_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pChkSum = md5ChkSum_New( );
        TINYTEST_FALSE( (OBJ_NIL == pChkSum) );
        
        eRc = fileio_Open(pObj, pPath);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        fileSize = file_SizeA(pPathA);
        TINYTEST_FALSE( (-1 == fileSize) );

        if (fileSize) {
            pBuffer = mem_Malloc(fileSize);
            TINYTEST_FALSE( (NULL == pBuffer) );

            eRc = fileio_Read(pObj, fileSize, pBuffer);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

            eRc = md5ChkSum_Update(pChkSum, pBuffer, fileSize);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

            mem_Free(pBuffer);
            pBuffer = NULL;
        }

        eRc = fileio_Close(pObj, false);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        obj_Release(pObj);
        pObj = OBJ_NIL;
        
        eRc = md5ChkSum_Finalize(pChkSum);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        pDigest = md5ChkSum_getDigest(pChkSum);
        TINYTEST_FALSE( (NULL == pDigest) );
        fprintf(stderr, "md5 digest = eb25a326f021accd3eb7b61fe2d57dc3\n");
        fprintf(stderr, "our digest = ");
        for(iRc=0; iRc<16; ++iRc) {
            fprintf(stderr, "%02x", pDigest[iRc]);
        }
        fprintf(stderr, "\n");

        iRc = memcmp(pDigest, answer, 16);
        fprintf(stderr, "iRc = %d\n", iRc);
        TINYTEST_TRUE( (0 == iRc) );

        obj_Release(pChkSum);
        pChkSum = OBJ_NIL;
    }
    
    obj_Release(pPath);
    pPath = OBJ_NIL;
    
    fprintf(stderr, "...%s completed.\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_md5ChkSum);
    TINYTEST_ADD_TEST(test_md5ChkSum_Read01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_md5ChkSum_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_md5ChkSum);





