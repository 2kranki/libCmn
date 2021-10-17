// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//             B-Plus Tree (BPT32) Request Header
//****************************************************************
/*
 * Program
 *          B-Plus Tree Requests (BPT32)
 * Purpose
 *          This object provides support for a B-Plus Tree which
 *          has fixed size keys embedded at a fixed location within
 *          each record of the dataset. The records may be variable
 *          length, but the key must always fit within the record
 *          at the same location in each. All blocks within the
 *          dataset are a fixed size and allocated as needed.
 *
 *          If a number is embedded in the key, it should either
 *          be put in right-adjusted character format or Big Endian
 *          format for the keys to collate properly.
 *
 *          The size of a record may be changed by updating it.
 *          However, records and their associated overhead must
 *          fit within the block size of the dataset.
 *
 *          The reason for the 32 suffix is that we use a 32-bit
 *          Logical Block Number (lbn) to access the blocks in
 *          the dataset.  This still allows for a sizeable dataset
 *          since the blocks can be up to 64k.
 *
 * Remarks
 *  1.      None
 *
 * References
 *  1.      "Reexamining B-trees", Ted Johnson and Dennis Shasha,
 *          Dr Dobb's Journal, January 1992
 *
 * History
 *  01/12/2019 Generated
 *  09/25/2021 Regenerated
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





#ifndef         BPT32_REQUEST_H
#define         BPT32_REQUEST_H





#ifdef  __cplusplus
extern "C" {
#endif


    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef uint32_t        LBN32_T;        // Logical Block Number Type

    typedef struct BPT32_blk_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        LBN32_T         (*pGetLBN) (OBJ_ID);
        bool            (*pSetManager) (OBJ_ID, OBJ_ID);
        // Methods:
        //                               nodeIndex [out]key  [out]data
        ERESULT         (*pGet) (OBJ_ID, uint32_t, uint32_t *, void *);
        //              //                    key      data
        ERESULT         (*pInsert) (OBJ_ID, uint32_t, void *);
        //              //                 blocksize datasize   lbn
        ERESULT         (*pSetup) (OBJ_ID, uint32_t, uint32_t, LBN32_T,  bool);
    } BPT32_BLK_VTBL;


    // Used internally for communication between this object and
    typedef enum BPT32_request_e {
        BPT32_REQUEST_UNKNOWN=0,
        BPT32_REQUEST_NEW_LBN,              // Return a new Logical Block Number not
        //                                  // currently allocated.
        //                                  //  obj   - ignored
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - lbn return pointer (uint32_t *)
        BPT32_REQUEST_NEW_INDEX,            // Return a new empty index block.
        BPT32_REQUEST_NEW_LEAF,             // Return a new empty leaf block.
        BPT32_REQUEST_PARENT,               // Get Parent after a search
        BPT32_REQUEST_READ,                 // Read a buffer from disk
        //                                  //  obj   - object requesting write
        //                                  //        (lbn and block are gotten from vtbl)
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - ignored
        BPT32_REQUEST_SPLIT,                // A Block Split occurred so
        //                                  // handle the index block update(s)
        BPT32_REQUEST_SET_TAIL,             // Change Data Tail to given block.
        //                                  //  obj   - object requesting tail
        //                                  //        (lbn is gotten from vtbl)
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - ignored
        BPT32_REQUEST_WRITE,                // Write a buffer to disk.
        //                                  //  obj   - object requesting write
        //                                  //        (lbn and block are gotten from vtbl)
        //                                  //  parm1 - ignored
        //                                  //  parm2 - ignored
        //                                  //  parm3 - ignored
    } BPT32_REQUEST;




#ifdef  __cplusplus
}
#endif

#endif  /* BPT32_REQUEST_H */

