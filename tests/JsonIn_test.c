// vi:nu:et:sts=4 ts=4 sw=4
/*
 *	Generated 12/30/2019 21:36:00
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
#include    <NodeArray.h>
#include    <szTbl.h>
#include    <trace.h>
#include    <JsonIn_internal.h>
#include    <SrcErrors.h>
#include    <utf8_internal.h>



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






int             test_JsonIn_OpenClose(
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    JSONIN_DATA	    *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = JsonIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = JsonIn_Init( pObj );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_JSONIN);
        TINYTEST_TRUE( (fRc) );
        
        // Test something.
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return 1;
}



int             test_JsonIn_01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    JSONIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    const
    char            *JsonInput = "{\n"
        "\"objectType\":\"szTbl\","
        "\"Count\":5, "
        "\"Entries\":["
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
    int64_t         count = 0;
    int64_t         hash = 0;
    int64_t         len = 0;
    uint32_t        len2 = 0;
    int64_t         ident = 0;
    NODE_DATA       *pNode;
    NAME_DATA       *pName;
    NODEARRAY_DATA  *pArray;
    NODEHASH_DATA   *pHash;
    uint32_t        i = 0;
    uint8_t         *pData = NULL;
    uint8_t         *pData2 = NULL;
    uint32_t        dataLen = 0;
    ASTR_DATA       *pStrWrk;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = JsonIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = JsonIn_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = AStr_NewA(JsonInput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        //obj_TraceSet(pObj, true);
        eRc = JsonIn_ParseAStr(pObj, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = JsonIn_ConfirmObjectType(pObj, "szTbl");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = JsonIn_FindIntegerNodeInHashA(pObj, "Count", &count);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tCount = %lld\n", count);
        pNode = NodeHash_FindA(pObj->pHash, 0, "Count");
        TINYTEST_FALSE( (NULL == pNode) );
        pStrWrk = JsonIn_CheckNodeDataForInteger(pNode);
        count = AStr_ToInt64(pStrWrk);
        fprintf(stderr, "\tCount from check = %lld\n", count);

        eRc = JsonIn_FindArrayNodeInHashA(pObj, "Entries", &pArray);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE((count == NodeArray_getSize(pArray)));

        for(i=0; i<count; ++i) {
            pNode = NodeArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            pName = Node_getName(pNode);
            TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == Name_CompareA(pName, "hash")));
            pHash = Node_getData(pNode);
            TINYTEST_FALSE( (OBJ_NIL == pHash) );
            TINYTEST_TRUE(( obj_IsKindOf(pHash, OBJ_IDENT_NODEHASH) ));
            eRc = JsonIn_SubObjectFromHash(pObj, pHash);
                eRc = JsonIn_FindIntegerNodeInHashA(pObj, "Hash", &hash);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\t\tHash(%d) = %lld\n", i+1, hash);
                eRc = JsonIn_FindIntegerNodeInHashA(pObj, "Ident", &ident);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\t\tIdent(%d) = %lld\n", i+1, ident);
                eRc = JsonIn_FindIntegerNodeInHashA(pObj, "Length", &len);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\t\tlen(%d) = %lld\n", i+1, len);
                eRc = JsonIn_SubObjectInHash(pObj, "Data");
                    TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                    pData = utf8_ParseJsonObject(pObj, &len2);
                    TINYTEST_FALSE( (NULL == pData) );
                    TINYTEST_TRUE((len == len2));
                    fprintf(stderr, "\t\tdata(%d) = %s\n", i+1, pData);
                    if (pData) {
                        mem_Free(pData);
                        pData = NULL;
                    }
                    pNode = NodeHash_FindA(pObj->pHash, 0, "data");
                    TINYTEST_FALSE( (NULL == pNode) );
                    pStrWrk = JsonIn_CheckNodeDataForString(pNode);
                    if (pStrWrk) {
                        fprintf(stderr, "\t\tdata from check = %s\n", AStr_getData(pStrWrk));
                    }
                    else {
                        fprintf(stderr, "\t\tdata from check = NULL\n");
                    }
                eRc = JsonIn_SubObjectEnd(pObj);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                pData2 = NULL;
                len = 0;
                eRc = JsonIn_FindUtf8NodeInHashA(pObj, "Data", &pData2, &dataLen);
                TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
                fprintf(stderr, "\t\tdata2(%d) = %s\n", dataLen, pData2);
                TINYTEST_TRUE((0 == strcmp(AStr_getData(pStrWrk), (char *)pData2)));
                mem_Free(pData2);
                pData2 = NULL;
            eRc = JsonIn_SubObjectEnd(pObj);
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



int             test_JsonIn_Float01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    JSONIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    const
    char            *JsonInput = "{ "
        "\"objectType\":\"Value\", "
        "\"type\":1 /*VALUE_TYPE_FLOAT*/, "
        "\"data\":3.141600E+00"
    "}\n";
    int64_t         type = 0;
    NODE_DATA       *pNode;
    ASTR_DATA       *pStrWrk = OBJ_NIL;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = JsonIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = JsonIn_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = AStr_NewA(JsonInput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        //obj_TraceSet(pObj, true);
        eRc = JsonIn_ParseAStr(pObj, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = JsonIn_ConfirmObjectType(pObj, "Value");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = JsonIn_FindIntegerNodeInHashA(pObj, "type", &type);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        fprintf(stderr, "\tType = %lld\n", type);
        pNode = NodeHash_FindA(pObj->pHash, 0, "data");
        TINYTEST_FALSE( (NULL == pNode) );
        pStrWrk = JsonIn_CheckNodeDataForFloat(pNode);
        TINYTEST_FALSE( (OBJ_NIL == pStrWrk) );
        fprintf(stderr, "\tData = %s\n", AStr_getData(pStrWrk));
        TINYTEST_TRUE((ERESULT_SUCCESS_EQUAL == AStr_CompareA(pStrWrk, "3.141600E+00")));

        obj_Release(pStr);
        pStr = OBJ_NIL;

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_JsonIn_Integers01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    JSONIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    const
    char            *JsonInput = "{ "
        "\"objectType\":\"IntegerArray\", "
        "\"data\":[1,2,3],"
    "}\n";
    int64_t         type = 0;
    NODE_DATA       *pNode;
    NODEARRAY_DATA  *pArray = OBJ_NIL;
    ASTR_DATA       *pStrWrk = OBJ_NIL;
    uint32_t        i;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = JsonIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = JsonIn_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = AStr_NewA(JsonInput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        //obj_TraceSet(pObj, true);
        eRc = JsonIn_ParseAStr(pObj, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        eRc = JsonIn_ConfirmObjectType(pObj, "IntegerArray");
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        // This illustrates one way of parsing an Integer Array.
        eRc = JsonIn_FindArrayNodeInHashA(pObj, "data", &pArray);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_FALSE( (OBJ_NIL == pArray) );
        TINYTEST_TRUE((3 == NodeArray_getSize(pArray)));
        for (i=0; i<NodeArray_getSize(pArray); i++) {
            int64_t         num = 0;
            pNode = NodeArray_Get(pArray, i+1);
            TINYTEST_FALSE( (OBJ_NIL == pNode) );
            {
                ASTR_DATA       *pWrk;
                pWrk = Node_ToDebugString(pNode, 0);
                if (pWrk) {
                    fprintf(stderr, "Node(%d): %s\n", i+1, AStr_getData(pWrk));
                    obj_Release(pWrk);
                }
            }
            pStrWrk = JsonIn_CheckNodeForInteger(pNode);
            TINYTEST_FALSE( (OBJ_NIL == pStrWrk) );
            fprintf(stderr, "\tData(%d) = %s\n", i+1, AStr_getData(pStrWrk));
            num = AStr_ToInt64(pStrWrk);
            TINYTEST_TRUE((num == i+1));
        }

        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}



int             test_JsonIn_I16Array01(
    const
    char            *pTestName
)
{
    ERESULT         eRc;
    JSONIN_DATA     *pObj = OBJ_NIL;
    ASTR_DATA       *pStr;
    const
    char            *JsonInput = "{\n"
        "\t\"x\":{\n"
            "\t\ttype:I16Array,\n"
            "\t\tsize:9,\n"
            "\t\tdata:[\n"
            "\t\t\t0,1,2,3,4,5,6,7,\n"
            "\t\t\t8\n"
            "\t\t]\n"
        "\t},\n"
    "}\n";
    uint32_t        i;
    uint16_t        size = 0;
    int16_t         array[9];

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = JsonIn_Alloc( );
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    pObj = JsonIn_Init(pObj);
    TINYTEST_FALSE( (OBJ_NIL == pObj) );
    if (pObj) {

        pStr = AStr_NewA(JsonInput);
        TINYTEST_FALSE( (OBJ_NIL == pStr) );
        //obj_TraceSet(pObj, true);
        eRc = JsonIn_ParseAStr(pObj, pStr);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );

        // This illustrates one way of parsing an Integer Array.
        eRc = JsonIn_FindI16ArrayNodeInHashA(pObj, "x", 9, array, &size);
        TINYTEST_FALSE( (ERESULT_FAILED(eRc)) );
        TINYTEST_TRUE((9 == size));
        for (i=0; i<size; i++) {
            TINYTEST_TRUE( (i == array[i]) );
        }

        obj_Release(pStr);
        pStr = OBJ_NIL;
        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n", pTestName);
    return 1;
}




TINYTEST_START_SUITE(test_JsonIn);
    TINYTEST_ADD_TEST(test_JsonIn_I16Array01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_JsonIn_Integers01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_JsonIn_Float01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_JsonIn_01,setUp,tearDown);
    TINYTEST_ADD_TEST(test_JsonIn_OpenClose,setUp,tearDown);
TINYTEST_END_SUITE();

TINYTEST_MAIN_SINGLE_SUITE(test_JsonIn);





