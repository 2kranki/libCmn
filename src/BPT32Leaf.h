// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  B-Plus Tree Leaf (BPT32Leaf) Header
//****************************************************************
/*
 * Program
 *          B-Plus Tree Leaf (BPT32Leaf)
 * Purpose
 *			This object provides support for a 32-bit B+ Tree Leaf
 *          block.  A Leaf block consists of an array of nodes where
 *          each node consists of a fixed length key and variable
 *          length data. The block is maintained in ascending key
 *          order. The key must be embedded within the record.
 *
 *          The block is normally part of a doubly-linked
 *          list of leaf blocks for fast sequential access. It is
 *          used by the BPT32 object.
 *
 *          Note that the data size can vary according to require-
 *          ments, but is the same for all node entries once the
 *          block is created.  Whereas, an index block has fixed
 *          sized nodes.
 *
 *          Leaf blocks do not support spanning data records between
 *          blocks.  The data must be able to fit within the block.
 *
 * Remarks
 *  1.      The Key Length and Offset properties must be set before
 *          calling any methods that affect the records in the block.
 *  2.      When a key pointer is provided to a method, it is assumed
 *          that memory can be accessed at that address for property
 *          KeyLen long.
 *
 * History
 *	01/12/2019 Generated
 *  09/23/2021 Regenerated and keys changed from uint32_t to variable
 *              length embedded in the record.
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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <BlkdRcds16.h>


#ifndef         BPT32LEAF_H
#define         BPT32LEAF_H


//#define   BPT32LEAF_IS_IMMUTABLE     1
//#define   BPT32LEAF_JSON_SUPPORT     1
//#define   BPT32LEAF_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT32Leaf_data_s  BPT32LEAF_DATA;            // Inherits from OBJ
    typedef struct BPT32Leaf_class_data_s BPT32LEAF_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT32Leaf_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Leaf_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetLBN) (OBJ_ID);            // Get Logical Block Number
        // Methods:
        //bool        (*pIsEnabled)(BPT32LEAF_DATA *);
    } BPT32LEAF_VTBL;

    typedef struct BPT32Leaf_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Leaf_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32LEAF_DATA *);
    } BPT32LEAF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32LEAF_SINGLETON
    BPT32LEAF_DATA * BPT32Leaf_Shared (
        void
    );

    void            BPT32Leaf_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPT32Leaf object if successful, otherwise OBJ_NIL.
     */
    BPT32LEAF_DATA * BPT32Leaf_Alloc (
        void
    );
    
    
    OBJ_ID          BPT32Leaf_Class (
        void
    );
    
    
    BPT32LEAF_DATA * BPT32Leaf_New (
        void
    );
    
    
    BPT32LEAF_DATA * BPT32Leaf_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff,             // relative to zero
        OBJ_ID          pMgr
    );


#ifdef  BPT32LEAF_JSON_SUPPORT
    BPT32LEAF_DATA * BPT32Leaf_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPT32LEAF_DATA * BPT32Leaf_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       BPT32Leaf_getBlock (
        BPT32LEAF_DATA  *this
    );


    uint16_t        BPT32Leaf_getKeyLen (
        BPT32LEAF_DATA  *this
    );


    uint16_t        BPT32Leaf_getKeyOff (
        BPT32LEAF_DATA  *this
    );


    uint32_t        BPT32Leaf_getLBN (
        BPT32LEAF_DATA  *this
    );

    bool            BPT32Leaf_setLBN (
        BPT32LEAF_DATA  *this,
        uint32_t        value
    );


    uint32_t        BPT32Leaf_getNextLBN (
        BPT32LEAF_DATA  *this
    );

    bool            BPT32Leaf_setNextLBN (
        BPT32LEAF_DATA  *this,
        uint32_t        value
    );


    uint16_t        BPT32Leaf_getNumRecords (
        BPT32LEAF_DATA  *this
    );


    uint32_t        BPT32Leaf_getPrevLBN (
        BPT32LEAF_DATA  *this
    );

    bool            BPT32Leaf_setPrevLBN (
        BPT32LEAF_DATA  *this,
        uint32_t        value
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add a record to the block in ascending sequence by key.  If the key
     already exists in the block, return an error.
     @param     this    object pointer
     @param     rcdLen  [input] record length (must not be less than the key length)
     @param     pRecord [input] record pointer of record to be added
     @return    If successful, return ERESULT_SUCCESS. Otherwise, return an
                ERESULT_* error code.
     */
    ERESULT         BPT32Leaf_Add (
        BPT32LEAF_DATA  *this,
        uint16_t        rcdLen,
        void            *pRecord
    );


    /*!
     Delete a record from the block that matches tth given key.
     @param     this    object pointer
     @param     pKey    [input] key of record to delete
     @return    If successful, return ERESULT_SUCCESS. Otherwise, return an
                ERESULT_* error code.
     */
    ERESULT         BPT32Leaf_Delete (
        BPT32LEAF_DATA  *this,
        void            *pKey
    );


    /*!
     Flush the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32Leaf_Flush (
        BPT32LEAF_DATA  *this
    );


    /*!
     Scan all the records in order by ascending record number.
     @return    ERESULT_SUCCESS if successful completion.  Otherwise,
                an ERESULT_* error code is returned.
     */
    ERESULT         BPT32Leaf_ForEach (
        BPT32LEAF_DATA  *this,
        P_BOOL_EXIT4A   pScan,              // Return false to stop scan
        OBJ_ID          pObj,               // Used as first parameter of scan method
        //                                  // second parameter is record length
        //                                  // third parameter is recard address
        void            *pArg4              // Used as fourth parameter of scan method
    );


    /*!
     Find a record in the block using the provided key.  If found, optionally return
     the data to the area given and optionally return the record's length in the block.
     @param     this    object pointer
     @param     pKey    [input] key (length is assumed to be same as defined at
                        open/create)
     @param     cData   [input] size of provided data area
     @param     pData   [output] optional pointer to returned data record
     @param     pUsed   [output] optional pointer to returned amount of pData used
                        if pData is NULL and cData is a large number, then this will
                        be the data record size.
     @return    If successful, return ERESULT_SUCCESS and optionally copy the record to
     the area given and optionally, return the length used. Otherwise, return an
     ERESULT_* error code.
     */
    ERESULT         BPT32Leaf_Get (
        BPT32LEAF_DATA  *this,
        void            *pKey,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    );


    /*!
     Get the index'th record from the block.
     @param     this    object pointer
     @param     index   reecord number within block relative to 1
     @param     pLen    optional returned record size
     @return    if successful, record which must be freed using mem_Free().  Otherwise,
                NULL.
     @warning   Remember to release the returned record.
     */
    uint8_t *       BPT32Leaf_GetNum (
        BPT32LEAF_DATA  *this,
        uint32_t        index,          // Relative to 1
        uint16_t        *pLen           // Optional record length
    );


    BPT32LEAF_DATA * BPT32Leaf_Init (
        BPT32LEAF_DATA  *this
    );


    /*!
     Set up an empty block.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_* error.
     */
    ERESULT         BPT32Leaf_Setup(
        BPT32LEAF_DATA  *this,
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff
    );


    /*!
     Split the current block into two equal sized blocks.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32Leaf_Split (
        BPT32LEAF_DATA  *this,
        BPT32LEAF_DATA  *pUpper
    );


#ifdef  BPT32LEAF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT32Leaf_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Leaf_ToJson (
        BPT32LEAF_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT32Leaf_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Leaf_ToDebugString (
        BPT32LEAF_DATA  *this,
        int             indent
    );
    
    
    /*!
     Update a record in the block that matches the given key.
     @param     this    object pointer
     @param     rcdLen  [input] record length (must not be less than the key length)
     @param     pRecord [input] record pointer of record to be updated
     @return    If successful, return ERESULT_SUCCESS. Otherwise, return an
                ERESULT_* error code.
     */
    ERESULT         BPT32Leaf_Update (
        BPT32LEAF_DATA  *this,
        uint16_t        rcdLen,
        void            *pRecord
    );


    /*!
     Verify as much of this object as we can.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32Leaf_Verify (
        BPT32LEAF_DATA  *this
    );


    
#ifdef  __cplusplus
}
#endif

#endif  /* BPT32LEAF_H */

