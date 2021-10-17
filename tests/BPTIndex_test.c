// vi:nu:et:sts=4 ts=4 sw=4
//****************************************************************
//                      Test Object Program
//****************************************************************
/*
 * Program
 *          Test Object Program
 * Purpose
 *          This program tests a particular object given certain
 *          parameters.
 *
 * Remarks
 *  1.      This relies on the fact that we can add to the Test
 *          Object by simply coding methods that use the Test
 *          Object.
 *
 * History
 *  08/29/2021 Generated
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */




/*
 TestForFail(error_sttring)         <= Tests eRc for failure
 TestForFalse(test, error_sttring)
 TestForNotNull(test, error)
 TestForNull(test, error)
 TestForSuccess(error)              <= Tests eRc for success
 TestForTrue(test, error)
 */





#include    <test_defs.h>
#include    <Test_internal.h>
#include    <trace.h>
#include    <BPTIndex_internal.h>
#include    <BPTLeaf_internal.h>
#include    <BPT_internal.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>





uint32_t        masterLBN = 0;
uint32_t        masterBlockSize = 128;
uint32_t        masterKeyLen = 4;
uint32_t        masterKeyOff = 0;
BPT_HEADER    hdr = {
    0
};


void *          Misc_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
);


// This VTbl supports Retain() and Release() which is
// used by objects other than the Shared object. These
// objects can still be shared among other objects. It
// just that they are deleted when their usage count
// goes to zero.
static
const
BPT_VTBL     Misc_Vtbl = {
    {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        (P_OBJ_QUERYINFO)Misc_QueryInfo,
        NULL,
        NULL,           // BPTIndex_Enable,
        NULL,           // BPTIndex_Disable,
        NULL,           // (P_OBJ_ASSIGN)BPTIndex_Assign,
        NULL,           // (P_OBJ_COMPARE)BPTIndex_Compare,
        NULL,           // (P_OBJ_PTR)BPTIndex_Copy,
        NULL,           // (P_OBJ_PTR)BPTIndex_DeepCopy,
        NULL            // (P_OBJ_HASH)BPTIndex_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //BPTIndex_IsEnabled,

};



void        *FakeObj = (void *)&Misc_Vtbl;



//---------------------------------------------------------------
//                  B l o c k  R e q u e s t
//---------------------------------------------------------------

/*!
 @warning   This method must always conform to P_ERESULT_EXIT5.
 */
ERESULT         BlockRequest(
    OBJ_ID          this,
    uint32_t        request,
    OBJ_ID          pObj,
    void            *pParm1,
    void            *pParm2,
    void            *pParm3
)
{
    ERESULT         eRc = ERESULT_GENERAL_FAILURE;
    BPTINDEX_DATA *pIndex = OBJ_NIL;
    BPTLEAF_DATA  *pLeaf = OBJ_NIL;
    uint32_t        lbn = 0;            // Logical Block Number
    void            *pBlock = NULL;
    BPT_BLK_VTBL  *pVtbl = NULL;


    switch (request) {

        case BPT_REQUEST_NEW_LBN:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++masterLBN;
            if (pParm3)
                *((uint32_t *)pParm3) = lbn;
            break;

        case BPT_REQUEST_NEW_INDEX:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++masterLBN;
            pIndex =    BPTIndex_NewWithSizes(
                                        masterBlockSize,
                                        lbn,
                                        masterKeyLen,
                                        masterKeyOff,
                                        OBJ_NIL
                        );
            if (OBJ_NIL == pIndex) {
                DEBUG_BREAK();
                --masterLBN;
                return ERESULT_OUT_OF_MEMORY;
            }
            if (pParm3)
                *((void **)pParm3) = pIndex;
            else
                obj_Release(pIndex);
            pIndex = NULL;
            break;

        case BPT_REQUEST_NEW_LEAF:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++masterLBN;
            pLeaf = BPTLeaf_NewWithSizes(
                                           masterBlockSize,
                                           lbn,
                                           masterKeyLen,
                                           masterKeyOff,
                                           OBJ_NIL
                    );
            if (OBJ_NIL == pLeaf) {
                DEBUG_BREAK();
                --masterLBN;
                return ERESULT_OUT_OF_MEMORY;
            }
            pLeaf->pReq = BlockRequest;
            if (pParm3)
                *((void **)pParm3) = pLeaf;
            else
                obj_Release(pLeaf);
            pLeaf = NULL;
            break;

        case BPT_REQUEST_PARENT:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
            lbn = pVtbl->pGetLBN(pObj);
            //FIXME: eRc = BPT_BlockFindParent(this, lbn, pParm3);
            break;

        case BPT_REQUEST_READ:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
            lbn = pVtbl->pGetLBN(pObj);
            pBlock = pVtbl->pGetBlock(pObj);
            if (NULL == pBlock) {
                eRc = ERESULT_DATA_MISSING;
            } else {
                if (lbn && pBlock) {
                    eRc = ERESULT_SUCCESS;
                }
                else
                    eRc = ERESULT_GENERAL_FAILURE;
            }
            break;

        case BPT_REQUEST_SPLIT:
            TRC_OBJ(this, "\tSplit Block...\n");
            //FIXME: eRc = BPT_BlockSplit(this, (OBJ_ID)pObj, pRet);
            break;

        case BPT_REQUEST_SET_TAIL:
            TRC_OBJ(this, "\tSet new data tail...\n");
            if (OBJ_IDENT_BPTLEAF == obj_getType(pObj)) {
                hdr.dataTail = BPTLeaf_getLBN((BPTLEAF_DATA *)pObj);
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_GENERAL_FAILURE;
            break;

        case BPT_REQUEST_WRITE:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            pVtbl = (BPT_BLK_VTBL *)obj_getVtbl(pObj);
            lbn = pVtbl->pGetLBN(pObj);
            TRC_OBJ(this, "\tWrite data for block %d...\n", lbn);
            pBlock = pVtbl->pGetBlock(pObj);
            if (lbn && pBlock) {
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_GENERAL_FAILURE;
            break;

        default:
            DEBUG_BREAK();
            return ERESULT_INVALID_REQUEST;
            break;
    }

    return eRc;
}



//---------------------------------------------------------------
//                     Q u e r y  I n f o
//---------------------------------------------------------------

void *          Misc_QueryInfo (
    OBJ_ID          objId,
    uint32_t        type,
    void            *pData
)
{
    BPT_CLASS_DATA *this = objId;
    const
    char            *pStr = pData;

    if (OBJ_NIL == this) {
        return NULL;
    }

    switch (type) {

        case OBJ_QUERYINFO_TYPE_METHOD:
            switch (*pStr) {

                case 'B':
                    if (str_Compare("BlockRequest", (char *)pStr) == 0) {
                        return BlockRequest;
                    }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

    return NULL;
}






ERESULT         Test_BPTIndex_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPTINDEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPTIndex_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = BPTIndex_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_BPTIndex_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPTINDEX_DATA       *pObj1 = OBJ_NIL;
    BPTINDEX_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BPTINDEX_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = BPTIndex_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = BPTIndex_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = BPTIndex_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BPTIndex_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = BPTIndex_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BPTIndex_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BPTINDEX_JSON_SUPPORT) && defined(XYZZY)
        pStr = BPTIndex_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = BPTIndex_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = BPTIndex_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;
#endif

        obj_Release(pObj1);
        pObj1 = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_BPTIndex_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    int             iRc;
    BPTINDEX_DATA *pObj = OBJ_NIL;
    bool            fRc;
    uint16_t        cData;
    const
    int             blockSize = 64;
    BPTINDEX_RSVD *pRsvd;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPTIndex_NewWithSizes(blockSize, 22, 4, 0, &FakeObj);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");
        pRsvd = (BPTINDEX_RSVD *)BlkdRcds16_getReserved((BLKDRCDS16_DATA *)pObj);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");
        TestForTrue((pObj->lbn == 22), "Failed Test");
        TestForTrue((BPTIndex_getKeyLen(pObj) == 4), "Failed Test");
        TestForTrue((BPTIndex_getKeyOff(pObj) == 0), "Failed Test");
        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "Before Adds");
        fRc = BPTIndex_Verify(pObj);
        TestForTrue(fRc, "Failed Test");

        eRc = BPTIndex_Add(pObj, 1, "001");
        TestForSuccess("Failed Add - 001");
        fRc = BPTIndex_Verify(pObj);
        TestForTrue(fRc, "Failed Test");
        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "After Add 001");

        eRc = BPTIndex_Add(pObj, 3, "003");
        TestForSuccess("Failed Add - 003");
        fRc = BPTIndex_Verify(pObj);
        TestForTrue(fRc, "Failed Test");
        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "After Add 003");

        eRc = BPTIndex_Add(pObj, 5, "005");
        TestForSuccess("Failed Add - 005");
        fRc = BPTIndex_Verify(pObj);
        TestForTrue(fRc, "Failed Test");
        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "After Add 005");

        eRc = BPTIndex_Add(pObj, 7, "007");
        TestForSuccess("Failed Add - 007");
        fRc = BPTIndex_Verify(pObj);
        TestForTrue(fRc, "Failed Test");
        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "After Add 007");

        eRc = BPTIndex_Add(pObj, 9, "009");
        TestForSuccess("Failed Add - 009");
        fRc = BPTIndex_Verify(pObj);
        TestForTrue(fRc, "Failed Test");
        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "After Add 009");


        iRc = BPTIndex_FindByKey(pObj, "001", &cData);
        TestForTrue((1 == iRc), "Failed Test");
        TestForTrue((0 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "002", &cData);
        TestForTrue((0 == iRc), "Failed Test");
        TestForTrue((1 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "003", &cData);
        TestForTrue((2 == iRc), "Failed Test");
        TestForTrue((0 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "004", &cData);
        TestForTrue((0 == iRc), "Failed Test");
        TestForTrue((2 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "005", &cData);
        TestForTrue((3 == iRc), "Failed Test");
        TestForTrue((0 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "006", &cData);
        TestForTrue((0 == iRc), "Failed Test");
        TestForTrue((3 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "007", &cData);
        TestForTrue((4 == iRc), "Failed Test");
        TestForTrue((0 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "000", &cData);
        TestForTrue((0 == iRc), "Failed Test");
        TestForTrue((0 == cData), "Failed Test");

        iRc = BPTIndex_FindByKey(pObj, "010", &cData);
        TestForTrue((0 == iRc), "Failed Test");
        TestForTrue((5 == cData), "Failed Test");


        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "Last");
        {
            ASTR_DATA       *pStr = BPTIndex_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_BPTIndex_Test02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPTINDEX_DATA *pObj = OBJ_NIL;
    bool            fRc;
    const
    int             blockSize = 64;

    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPTIndex_NewWithSizes(blockSize, 22, 4, 0, &FakeObj);
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPTINDEX);
        TestForTrue(fRc, "Failed Ident Test");

        Test_Dump(blockSize, BlkdRcds16_getData((BLKDRCDS16_DATA *)pObj), "Last");
        {
            ASTR_DATA       *pStr = BPTIndex_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug: %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}




int     main (
    int         cArgs,
    const
    char        *ppArgs[],
    const
    char        *ppEnv[]
)
{
    ERESULT     eRc;
    TEST_DATA   test = {0};
    TEST_DATA   *pTest = OBJ_NIL;
    int         i;
    const
    char        *pTestNameA = NULL;

    pTest = Test_Init(&test);
    if (OBJ_NIL == pTest) {
        fprintf(
                stderr,
                "\x1b[1m\x1b[31mFATAL\x1b[0m: Could not create Test object!\n\n\n"
        );
        exit(201);
    }

    // Scan args.
    for (i=0; i<cArgs; i++) {
        if (0 == strcmp("--no_int3", ppArgs[i])) {
            Test_setAllowInt3(pTest, false);
        }
    }

    // Execute tests.
    TestExec("OpenClose", Test_BPTIndex_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_BPTIndex_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_BPTIndex_Test01, NULL, NULL);
    TestExec("Test02", Test_BPTIndex_Test02, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



