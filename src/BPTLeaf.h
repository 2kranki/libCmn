// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  B-Plus Tree Leaf (BPTLeaf) Header
//****************************************************************
/*
 * Program
 *          B-Plus Tree Leaf (BPTLeaf)
 * Purpose
 *			This object provides support for a 32-bit B+ Tree Leaf
 *          block.  A Leaf block consists of an array of nodes where
 *          each node consists of a fixed length key and variable
 *          length data. The block is maintained in ascending key
 *          order. The key must be embedded within the record.
 *
 *          The block is normally part of a doubly-linked
 *          list of leaf blocks for fast sequential access. It is
 *          used by the BPT object.
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


#ifndef         BPTLEAF_H
#define         BPTLEAF_H


//#define   BPTLEAF_IS_IMMUTABLE     1
//#define   BPTLEAF_JSON_SUPPORT     1
//#define   BPTLEAF_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPTLeaf_data_s  BPTLEAF_DATA;            // Inherits from OBJ
    typedef struct BPTLeaf_class_data_s BPTLEAF_CLASS_DATA;   // Inherits from OBJ

    // WARNING: This must conform to BPT_BLK_VTBL found in BPT_Request.h.
    typedef struct BPTLeaf_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPTLeaf_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetLBN) (OBJ_ID);            // Get Logical Block Number
        // Methods:
        ERESULT         (*pGetNum) (OBJ_ID, uint32_t, uint32_t *, void *);
    } BPTLEAF_VTBL;

    typedef struct BPTLeaf_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPTLeaf_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPTLEAF_DATA *);
    } BPTLEAF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPTLEAF_SINGLETON
    BPTLEAF_DATA * BPTLeaf_Shared (
        void
    );

    void            BPTLeaf_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPTLeaf object if successful, otherwise OBJ_NIL.
     */
    BPTLEAF_DATA * BPTLeaf_Alloc (
        void
    );
    
    
    OBJ_ID          BPTLeaf_Class (
        void
    );
    
    
    BPTLEAF_DATA * BPTLeaf_New (
        void
    );
    
    
    BPTLEAF_DATA * BPTLeaf_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff,             // relative to zero
        OBJ_ID          pMgr
    );


#ifdef  BPTLEAF_JSON_SUPPORT
    BPTLEAF_DATA * BPTLeaf_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPTLEAF_DATA * BPTLeaf_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       BPTLeaf_getBlock (
        BPTLEAF_DATA  *this
    );


    uint16_t        BPTLeaf_getKeyLen (
        BPTLEAF_DATA  *this
    );


    uint16_t        BPTLeaf_getKeyOff (
        BPTLEAF_DATA  *this
    );


    uint32_t        BPTLeaf_getLBN (
        BPTLEAF_DATA  *this
    );

    bool            BPTLeaf_setLBN (
        BPTLEAF_DATA  *this,
        uint32_t        value
    );


    uint32_t        BPTLeaf_getNextLBN (
        BPTLEAF_DATA  *this
    );

    bool            BPTLeaf_setNextLBN (
        BPTLEAF_DATA  *this,
        uint32_t        value
    );


    uint16_t        BPTLeaf_getNumRecords (
        BPTLEAF_DATA  *this
    );


    uint32_t        BPTLeaf_getPrevLBN (
        BPTLEAF_DATA  *this
    );

    bool            BPTLeaf_setPrevLBN (
        BPTLEAF_DATA  *this,
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
    ERESULT         BPTLeaf_Add (
        BPTLEAF_DATA  *this,
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
    ERESULT         BPTLeaf_Delete (
        BPTLEAF_DATA  *this,
        void            *pKey
    );


    /*!
     Flush the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPTLeaf_Flush (
        BPTLEAF_DATA  *this
    );


    /*!
     Scan all the records in order by ascending record number.
     @return    ERESULT_SUCCESS if successful completion.  Otherwise,
                an ERESULT_* error code is returned.
     */
    ERESULT         BPTLeaf_ForEach (
        BPTLEAF_DATA  *this,
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
     @param     pData   [output] optional pointer to returned data record of size cData
     @param     pUsed   [output] optional pointer to returned amount of pData used
                        if pData is NULL and cData is a large number, then this will
                        be the data record size.
     @return    If successful, return ERESULT_SUCCESS and optionally copy the record to
     the area given and optionally, return the length used. Otherwise, return an
     ERESULT_* error code.
     */
    ERESULT         BPTLeaf_Get (
        BPTLEAF_DATA  *this,
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
    uint8_t *       BPTLeaf_GetNum (
        BPTLEAF_DATA  *this,
        uint32_t        index,          // Relative to 1
        uint16_t        *pLen           // Optional record length
    );


    BPTLEAF_DATA * BPTLeaf_Init (
        BPTLEAF_DATA  *this
    );


    /*!
     Set up an empty block.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_* error.
     */
    ERESULT         BPTLeaf_Setup(
        BPTLEAF_DATA  *this,
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
    ERESULT         BPTLeaf_Split (
        BPTLEAF_DATA  *this,
        BPTLEAF_DATA  *pUpper
    );


#ifdef  BPTLEAF_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPTLeaf_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTLeaf_ToJson (
        BPTLEAF_DATA  *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPTLeaf_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTLeaf_ToDebugString (
        BPTLEAF_DATA  *this,
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
    ERESULT         BPTLeaf_Update (
        BPTLEAF_DATA  *this,
        uint16_t        rcdLen,
        void            *pRecord
    );


    /*!
     Verify as much of this object as we can.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPTLeaf_Verify (
        BPTLEAF_DATA  *this
    );


    
#ifdef  __cplusplus
}
#endif

#endif  /* BPTLEAF_H */

