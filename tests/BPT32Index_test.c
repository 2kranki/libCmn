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
#include    <BPT32Index_internal.h>
#include    <BPT32_internal.h>
#include    <BPT32_Request.h>
#include    <JsonIn.h>
#include    <SrcErrors.h>
#include    <szTbl.h>






uint32_t        masterLBN = 0;
uint32_t        masterBlockSize = 128;
uint32_t        masterKeyLen = 4;
uint32_t        masterKeyOff = 0;
BPT32_HEADER    hdr = {
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
BPT32_VTBL     Misc_Vtbl = {
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
    BPT32INDEX_DATA *pIndex = OBJ_NIL;
    BPT32LEAF_DATA  *pLeaf = OBJ_NIL;
    uint32_t        lbn = 0;            // Logical Block Number
    void            *pBlock = NULL;
    BPT32_BLK_VTBL  *pVtbl = NULL;


    switch (request) {

        case BPT32_REQUEST_NEW_LBN:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++masterLBN;
            if (pParm3)
                *((uint32_t *)pParm3) = lbn;
            break;

        case BPT32_REQUEST_NEW_INDEX:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++masterLBN;
            pIndex =    BPT32Index_NewWithSizes(
                                        masterBlockSize,
                                        lbn,
                                        sizeof(uint32_t),
                                        true,
                                        this
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
            eRc = ERESULT_SUCCESS;
            break;

        case BPT32_REQUEST_NEW_LEAF:
            if (NULL == pParm3) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            lbn = ++masterLBN;
            pLeaf = BPT32Leaf_NewWithSizes(
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
            eRc = ERESULT_SUCCESS;
            break;

        case BPT32_REQUEST_PARENT:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
            lbn = pVtbl->pGetLBN(pObj);
            //FIXME: eRc = BPT_BlockFindParent(this, lbn, pParm3);
            break;

        case BPT32_REQUEST_READ:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
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

        case BPT32_REQUEST_SPLIT:
            TRC_OBJ(this, "\tSplit Block...\n");
            //FIXME: eRc = BPT_BlockSplit(this, (OBJ_ID)pObj, pRet);
            eRc = ERESULT_SUCCESS;
            break;

        case BPT32_REQUEST_SET_TAIL:
            TRC_OBJ(this, "\tSet new data tail...\n");
            if (OBJ_IDENT_BPTLEAF == obj_getType(pObj)) {
                hdr.dataTail = BPT32Leaf_getLBN((BPT32LEAF_DATA *)pObj);
                eRc = ERESULT_SUCCESS;
            }
            else
                eRc = ERESULT_GENERAL_FAILURE;
            break;

        case BPT32_REQUEST_WRITE:
            if (NULL == pObj) {
                DEBUG_BREAK();
                return ERESULT_INVALID_PARAMETER;
            }
            pVtbl = (BPT32_BLK_VTBL *)obj_getVtbl(pObj);
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
    BPT32_CLASS_DATA *this = objId;
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



ERESULT         Test_BPT32Index_OpenClose (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32INDEX_DATA       *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPT32Index_Alloc( );
    TestForNotNull(pObj, "Missing Test Alloc() object");
    pObj = BPT32Index_Init( pObj );
    TestForNotNull(pObj, "Missing Test Init() object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test something.
        TestForSuccess("test failed");

        obj_Release(pObj);
        pObj = OBJ_NIL;
    }

    fprintf(stderr, "...%s completed.\n\n\n", pTestName);
    return eRc;
}



ERESULT         Test_BPT32Index_Copy01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32INDEX_DATA       *pObj1 = OBJ_NIL;
    BPT32INDEX_DATA       *pObj2 = OBJ_NIL;
    bool            fRc;
#if defined(BPT32INDEX_JSON_SUPPORT) && defined(XYZZY)
    ASTR_DATA       *pStr = OBJ_NIL;
#endif
    //int             iRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj1 = BPT32Index_New( );
    TestForNotNull(pObj1, "Missing Test object");
    if (pObj1) {

        //obj_TraceSet(pObj1, true);       
        fRc = obj_IsKindOf(pObj1, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        // Test assign.
        pObj2 = BPT32Index_New();
        TestForNotNull(pObj2, "Missing copied object");
        eRc = BPT32Index_Assign(pObj1, pObj2);
        TestForFalse((ERESULT_FAILED(eRc)), "Assignment failed");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BPT32Index_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test copy.
        pObj2 = BPT32Index_Copy(pObj1);
        TestForNotNull(pObj2, "Missing copied object");

        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        //iRc = BPT32Index_Compare(pObj1, pObj2);
        //TestForTrue((0 == iRc), "Failed Compare");
        //TODO: Add More tests here!

        obj_Release(pObj2);
        pObj2 = OBJ_NIL;

        // Test json support.
#if defined(BPT32INDEX_JSON_SUPPORT) && defined(XYZZY)
        pStr = BPT32Index_ToJson(pObj1);
        TestForNotNull(pStr, "Missing JSON output");
        fprintf(stderr, "JSON: %s\n", AStr_getData(pStr));
        pObj2 = BPT32Index_NewFromJsonString(pStr);
        TestForNotNull(pObj2, "Missing JSON created object");
        fRc = obj_IsKindOf(pObj2, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        obj_Release(pStr);
        pStr = OBJ_NIL;
        //iRc = BPT32Index_Compare(pObj1, pObj2);
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



ERESULT         Test_BPT32Index_Test01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32INDEX_DATA *pObj = OBJ_NIL;
    bool            fRc;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPT32Index_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        {
            ASTR_DATA       *pStr = BPT32Index_ToDebugString(pObj, 4);
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



ERESULT         Test_BPT32Index_Insert01 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32INDEX_DATA *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32INDEX_NODE *pNode;
    BPT32INDEX_DATA *pNew = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPT32Index_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        eRc = BPT32Index_Setup(pObj, 48, 0, sizeof(uint32_t), true);
        TestForSuccess("Failed Setup");
        TestForTrue((pObj->pBlock), "");
        max = pObj->pBlock->max;
        BPT32Index_setManager(pObj, &FakeObj);

        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        TestForTrue((pObj->pBlock->max == 4), "");
        for (i=0; i<pObj->pBlock->max; ++i) {
            k = i + 1;
            d = i;
            fprintf(stderr, "\tInserting: %d\n", k);
            eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
            TestForSuccess("Failed Setup");
            {
                pStr = BPT32Index_ToDebugString(pObj, 3);
                fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
            TestForTrue((OBJ_NIL == pNew), "");
        }
        
        TestForTrue((4 == pObj->pBlock->used), "");
        for (i=0; i<pObj->pBlock->used; ++i) {
            k = i + 1;
            d = i;
            pNode = &pObj->pBlock->nodes[i];
            TestForTrue((k == pNode->key), "");
            TestForTrue((d == pNode->index), "");
        }

        {
            ASTR_DATA       *pStr = BPT32Index_ToDebugString(pObj, 4);
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



ERESULT         Test_BPT32Index_Insert02 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32INDEX_DATA *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32INDEX_NODE *pNode;
    BPT32INDEX_DATA *pNew = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPT32Index_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        eRc = BPT32Index_Setup(pObj, 48, 0, sizeof(uint32_t), true);
        TestForSuccess("Failed Setup");
        TestForTrue((pObj->pBlock), "");
        TestForTrue((pObj->pBlock->max == 4), "");
        max = pObj->pBlock->max;
        BPT32Index_setManager(pObj, &FakeObj);

        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 3;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("Failed Setup");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        k = 1;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("Failed Setup");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        k = 4;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        k = 2;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        TestForTrue((4 == pObj->pBlock->used), "");
        for (i=0; i<pObj->pBlock->used; ++i) {
            k = i + 1;
            d = i;
            pNode = &pObj->pBlock->nodes[i];
            TestForTrue((k == pNode->key), "");
            TestForTrue((k == pNode->index), "");
        }

        fprintf(stderr, "\tDeleting: 3\n");
        eRc = BPT32Index_Delete(pObj, 3);
        TestForSuccess("");
        TestForTrue((3 == pObj->pBlock->used), "");

        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        pNode = BPT32Index_FindNode(pObj, 3, &i);
        TestForTrue((pNode), "");
        TestForTrue((pNode->key == 4), "");
        TestForTrue((i == 2), "");
        
        fprintf(stderr, "\tDeleting: %d\n", max);
        eRc = BPT32Index_Delete(pObj, max);
        TestForSuccess("");
        TestForTrue((2 == pObj->pBlock->used), "");

        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        fprintf(stderr, "\tDeleting: 1\n");
        eRc = BPT32Index_Delete(pObj, 1);
        TestForSuccess("");
        TestForTrue((1 == pObj->pBlock->used), "");


        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        {
            ASTR_DATA       *pStr = BPT32Index_ToDebugString(pObj, 4);
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



ERESULT         Test_BPT32Index_Insert03 (
    TEST_DATA       *this,
    const
    char            *pTestName
)
{
    ERESULT         eRc = ERESULT_SUCCESS;
    BPT32INDEX_DATA *pObj = OBJ_NIL;
    bool            fRc;
    uint32_t        d;
    uint32_t        k;
    uint32_t        i;
    uint32_t        max;
    ASTR_DATA       *pStr;
    BPT32INDEX_NODE *pNode;
    BPT32INDEX_DATA *pNew = OBJ_NIL;
   
    fprintf(stderr, "Performing: %s\n", pTestName);

    pObj = BPT32Index_New( );
    TestForNotNull(pObj, "Missing Test object");
    if (pObj) {

        //obj_TraceSet(pObj, true);       
        fRc = obj_IsKindOf(pObj, OBJ_IDENT_BPT32INDEX);
        TestForTrue(fRc, "Failed Ident Test");
        
        eRc = BPT32Index_Setup(pObj, 48, 0, sizeof(uint32_t), true);
        TestForSuccess("");
        TestForTrue((pObj->pBlock), "");
        TestForTrue((pObj->pBlock->max == 4), "");
        max = pObj->pBlock->max;
        BPT32Index_setManager(pObj, &FakeObj);

        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        
        k = 3;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        k = 1;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        k = 4;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        k = 5;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("");
        pStr = BPT32Index_ToDebugString(pObj, 3);
        fprintf(stderr, "\n%s\n\n", AStr_getData(pStr));
        obj_Release(pStr);
        pStr = OBJ_NIL;
        TestForTrue((OBJ_NIL == pNew), "");

        TestForTrue((4 == pObj->pBlock->used), "");
        k = 1;
        pNode = &pObj->pBlock->nodes[0];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");
        k = 3;
        pNode = &pObj->pBlock->nodes[1];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");
        k = 4;
        pNode = &pObj->pBlock->nodes[2];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");
        k = 5;
        pNode = &pObj->pBlock->nodes[3];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");

        // Cause a split with new record in lower half
        k = 2;
        d = k;
        fprintf(stderr, "\tInserting: %d\n", k);
        eRc = BPT32Index_Insert(pObj, k, &d, &pNew);
        TestForSuccess("");
        TestForTrue((pNew), "");

        {
            ASTR_DATA       *pStr = BPT32Index_ToDebugString(pObj, 4);
            if (pStr) {
                fprintf(stderr, "Debug (Left): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }
        {
            ASTR_DATA       *pStr = BPT32Index_ToDebugString(pNew, 4);
            if (pStr) {
                fprintf(stderr, "Debug (Right): %s\n", AStr_getData(pStr));
                obj_Release(pStr);
                pStr = OBJ_NIL;
            }
        }

        TestForTrue((3 == pObj->pBlock->used), "");
        TestForTrue((2 == pNew->pBlock->used), "");
        k = 1;
        pNode = &pObj->pBlock->nodes[0];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");
        k = 2;
        pNode = &pObj->pBlock->nodes[1];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");
        k = 3;
        pNode = &pObj->pBlock->nodes[2];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");
        k = 4;
        pNode = &pNew->pBlock->nodes[0];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");
        k = 5;
        pNode = &pNew->pBlock->nodes[1];
        TestForTrue((k == pNode->key), "");
        TestForTrue((k == pNode->index), "");

        obj_Release(pNew);
        pNew = OBJ_NIL;

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
    TestExec("OpenClose", Test_BPT32Index_OpenClose, NULL, NULL);
    //TestExec("Copy01", Test_BPT32Index_Copy01, pTest, NULL, NULL);
    TestExec("Test01", Test_BPT32Index_Test01, NULL, NULL);
    TestExec("Insert01", Test_BPT32Index_Insert01, NULL, NULL);
    TestExec("Insert02", Test_BPT32Index_Insert02, NULL, NULL);
    TestExec("Insert03", Test_BPT32Index_Insert03, NULL, NULL);

    obj_Release(pTest);
    pTest = OBJ_NIL;

    // Return to Operating System.
    return 0;
}



