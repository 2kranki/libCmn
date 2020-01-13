// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus 32-Bit Tree Index Block (bpt32idx) Header
//****************************************************************
/*
 * Program
 *			B-Plus 32-Bit Tree Index Block (bpt32idx)
 * Purpose
 *			This object provides support for a 32-bit B+ Tree index
 *          block.  This block contains an array of nodes where the
 *          node consists of a uint32_t key and a uint32_t index to
 *          a child block.  So, an index block does not contain any
 *          key's data just indices to child blocks.  There is also
 *          a special index, P0, which points to the child block of
 *          keys less than the key in the first node entry.  The
 *          rest of the fields in the block are for management of
 *          the nodes and block identification purposes.
 *
 *          Note that the nodes in this block are of fixed size
 *          whereas the nodes in a leaf block vary in size according
 *          to the data size.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/12/2019 Generated
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
#include        <bpt32.h>


#ifndef         BPT32IDX_H
#define         BPT32IDX_H


//#define   BPT32IDX_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bpt32idx_data_s	BPT32IDX_DATA;            // Inherits from OBJ
    typedef struct bpt32idx_class_data_s BPT32IDX_CLASS_DATA;   // Inherits from OBJ

    typedef struct bpt32idx_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32idx_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetIndex) (OBJ_ID);
        bool            (*pSetManager) (OBJ_ID, OBJ_ID);
        // Methods:
        ERESULT         (*pGet) (OBJ_ID, uint32_t, uint32_t *, void *);
        ERESULT         (*pInsert) (OBJ_ID, uint32_t, void *);
        ERESULT         (*pSetup) (OBJ_ID, uint32_t, uint32_t, uint32_t, bool);
    } BPT32IDX_VTBL;

    typedef struct bpt32idx_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32idx_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32IDX_DATA *);
    } BPT32IDX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32IDX_SINGLETON
    BPT32IDX_DATA * bpt32idx_Shared (
        void
    );

    bool            bpt32idx_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to bpt32idx object if successful, otherwise OBJ_NIL.
     */
    BPT32IDX_DATA * bpt32idx_Alloc (
        void
    );
    
    
    OBJ_ID          bpt32idx_Class (
        void
    );
    
    
    BPT32IDX_DATA * bpt32idx_New (
        void
    );
    
    
    BPT32IDX_DATA * bpt32idx_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        dataSize,
        uint32_t        index,                  // Block Index Number
        bool            fAllocate,              // true == allocate a buffer
        OBJ_ID          pMgr
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    uint8_t *       bpt32idx_getBlock (
        BPT32IDX_DATA   *this
    );
    
    
    uint32_t        bpt32idx_getIndex (
        BPT32IDX_DATA    *this
    );
    
    bool            bpt32idx_setIndex (
        BPT32IDX_DATA    *this,
        uint32_t        value
    );
    
    
    bool            bpt32idx_setManager(
        BPT32IDX_DATA    *this,
        OBJ_ID           *pMgr          // Block Manager
    );
    
    
    uint32_t        bpt32idx_getP0 (
        BPT32IDX_DATA   *this
    );
    
    bool            bpt32idx_setP0 (
        BPT32IDX_DATA   *this,
        uint32_t        value
    );

    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Overlay the block data with the given data.
     @param     this    object pointer
     @param     pData   pointer to new data
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         bpt32idx_CopyFrom (
        BPT32IDX_DATA   *this,
        void            *pData
    );
    
    
    /*!
     Delete the entry if found.
     @param     this    object pointer
     @param     key     key of entry to be deleted
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         bpt32idx_Delete (
        BPT32IDX_DATA    *this,
        uint32_t        key
    );
    
   
    ERESULT         bpt32idx_FindIndex (
        BPT32IDX_DATA   *this,
        uint32_t        index,
        uint32_t        *pKey
    );
    
    
    /*!
     Find an index in the block given a key.  If key < node key of first entry, return
     P0.  If node key(i) < key >= node key(i+1), return node index(i).  Otherwise,
     return node index (last entry).
     @param     this    object pointer
     @param     key     [input] numeric key
     @param     pIndex  [output] pointer to returned index if found
     @return    If successful, return ERESULT_SUCCESS and optionally copy the data to
                the area given. Otherwise, return an ERESULT_* error code.
     @warning   The data area provided must be at least dataSize bytes as given in
                the SetupSizes() method.
     */
    ERESULT         bpt32idx_FindKey (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        *pIndex
    );
    
    
    /*!
     Flush the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         bpt32idx_Flush (
        BPT32IDX_DATA   *this
    );
    
    
    ERESULT         bpt32idx_Get (
        BPT32IDX_DATA    *this,
        uint32_t        index,          // Relative to 1
        uint32_t        *pKey,
        uint32_t        *pData
    );
    
    
    BPT32IDX_DATA * bpt32idx_Init (
        BPT32IDX_DATA   *this
    );


    /*!
     Insert the given key and data into the current block.  If the current
     block is full, split this block and add the given key and data into
     the appropriate block.
     @param     this    object pointer
     @param     key     key to be inserted
     @param     pData   pointer to data to be associated with the key
     @param     ppNew   object pointer to new block if split occurs
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         bpt32idx_Insert (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        *pData,
        BPT32IDX_DATA   **ppNew
    );

 
    /*!
     Read the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bpt32idx_Read (
        BPT32IDX_DATA   *this
    );
    
    
    ERESULT         bpt32idx_Setup(
        BPT32IDX_DATA   *this,
        uint32_t        blockSize,
        uint32_t        dataSize,
        uint32_t        index,                  // Block Index Number
        bool            fAllocate               // true == allocate a buffer
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = bpt32idx_ToDebugString(this,4);
     @endcode 
     @param     this    BPT32IDX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    bpt32idx_ToDebugString (
        BPT32IDX_DATA     *this,
        int             indent
    );
    
    
    /*!
     Find an entry in the node and update its data.
     @param     this    object pointer
     @param     key     [input] numeric key
     @param     index   [input] index
     @return    If successful, return ERESULT_SUCCESS and optionally copy the data to
                the area given. Otherwise, return an ERESULT_* error code.
     @warning   The data area provided must be at least dataSize bytes as given in
                the SetupSizes() method.
     */
    ERESULT         bpt32idx_Update (
        BPT32IDX_DATA   *this,
        uint32_t        key,
        uint32_t        index
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32IDX_H */

