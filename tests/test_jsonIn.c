/*
 *	Generated 12/21/2017 05:41:06
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





#include        <tinytest.h>
#include        <cmn_defs.h>
#include        <nodeArray.h>
#include        <szTbl.h>
#include        <trace.h>
#include        <jsonIn_internal.h>
#include        <utf8_internal.h>



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






int         test_jsonIn_OpenClose(
    const
    char        *pTestName
)
{
    JSONIN_DATA	*pObj = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = jsonIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = jsonIn_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        // Test something.

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_jsonIn_01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    JSONIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    const
    char            *jsonInput = "{\n"
        "\"objectType\":\"szTbl\","
        "\"Count\":5, \"Entries\":["
            "{Length:3,\"Hash\":816909077,\"Ident\":1,\n"
             "\"Data\":{ \"objectType\":\"utf8\", \"len\":3, \"crc\":4123767104,\n"
                        "\"data\":\"bob\" }\n"
            " },\n"
            "{Length:5,\"Hash\":1570040108,\"Ident\":2,\n"
            " \"Data\":{ \"objectType\":\"utf8\", \"len\":5, \"crc\":1943333782,\n"
                        "\"data\":\"bobby\" }\n"
            "},\n"
            "{Length:6,\"Hash\":2237716196,\"Ident\":3,\n"
            " \"Data\":{ \"objectType\":\"utf8\", \"len\":6, \"crc\":2210534776,"
                "\"data\":\"iryana\" }\n"
            "},\n"
            "{Length:6,\"Hash\":2149526240,\"Ident\":4,\n"
            " \"Data\":{ \"objectType\":\"utf8\", \"len\":6, \"crc\":2266782723,\n"
                "\"data\":\"dashsa\" }\n"
            "},\n"
            "{Length:5,\"Hash\":1651721647,\"Ident\":5,\n"
            " \"Data\":{ \"objectType\":\"utf8\", \"len\":5, \"crc\":3895251102,\n"
                "\"data\":\"dasha\" }\n"
            "}\n"
        "]\n"
    "}\n";
    uint32_t        count = 0;
    uint32_t        hash = 0;
    uint32_t        len = 0;
    uint32_t        len2 = 0;
    uint32_t        ident = 0;
    NODE_DATA       *pNode;
    NAME_DATA       *pName;
    NODEARRAY_DATA  *pArray;
    NODEHASH_DATA   *pHash;
    uint32_t        i = 0;
    uint8_t         *pData = NULL;

    fprintf(stderr, "Performing: %s\n", pTestName);
    
    pObj = jsonIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = jsonIn_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {
        
        pStr = AStr_NewA(jsonInput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        eRc = jsonIn_ParseAStr(pObj, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = jsonIn_ConfirmObjectType(pObj, "szTbl");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        
        count = (uint32_t)jsonIn_FindIntegerNodeInHash(pObj, "Count");
        eRc = jsonIn_getLastError(pObj);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tCount = %d\n", count);

        pArray = jsonIn_FindArrayNodeInHash(pObj, "Entries");
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE((count == nodeArray_getSize(pArray)));

        for(i=0; i<count; ++i) {
            pNode = nodeArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            pName = node_getName(pNode);
            TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == name_CompareA(pName, "hash")));
            pHash = node_getData(pNode);
            TINYTEST_FALSE( (OBJ_NIL == pHash) );
            TINYTEST_TRUE(( obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH) ));
            eRc = jsonIn_SubobjectFromHash(pObj, pHash);
            hash = (uint32_t)jsonIn_FindIntegerNodeInHash(pObj, "Hash");
            eRc = jsonIn_getLastError(pObj);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            fprintf(stderr, "\t\tHash(%d) = %u\n", i+1, hash);
            ident = (uint32_t)jsonIn_FindIntegerNodeInHash(pObj, "Ident");
            eRc = jsonIn_getLastError(pObj);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            fprintf(stderr, "\t\tIdent(%d) = %u\n", i+1, ident);
            len = (uint32_t)jsonIn_FindIntegerNodeInHash(pObj, "Length");
            eRc = jsonIn_getLastError(pObj);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            fprintf(stderr, "\t\tlen(%d) = %u\n", i+1, len);
            eRc = jsonIn_SubobjectInHash(pObj, "Data");
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            pData = utf8_ParseObject(pObj, &len2);
            TINYTEST_FALSE( (NULL == pData) );
            TINYTEST_TRUE((len == len2));
            fprintf(stderr, "\t\tdata(%d) = %s\n", i+1, pData);
            if (pData) {
                mem_Free(pData);
                pData = NULL;
            }
            eRc = jsonIn_SubobjectEnd(pObj);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
            eRc = jsonIn_SubobjectEnd(pObj);
            TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        }
        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }
    
    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_jsonIn);
    TINYTEST_ADD_TEST(test_jsonIn_01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_jsonIn_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_jsonIn);





