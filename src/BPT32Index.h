// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus 32-Bit Tree Index Block (BPT32Index) Header
//****************************************************************
/*
 * Program
 *			B-Plus 32-Bit Tree Index Block (BPT32Index)
 * Purpose
 *			This object provides support for a 32-bit B+ Tree index
 *          block.  This block contains an array of nodes where the
 *          node consists of a uint32_t key and a uint32_t index to
 *          a child block.  So, an index block does not contain any
 *          key's data just indices to child blocks.
 *
 *          There is also a special index, P0, which points to the
 *          child block of keys less than the key in the first node
 *          entry.
 *
 *          The rest of the fields in the block are for management
 *          of the nodes and block identification purposes.  It is
 *          used by BPT32 objects.
 *
 *          Each key in this block represents the left-most key of
 *          of a child block which can be another index block or a
 *          leaf block.
 *
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
#include        <BPT32.h>
#include        <BPT32_Request.h>


#ifndef         BPT32INDEX_H
#define         BPT32INDEX_H


//#define   BPT32INDEX_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT32Index_data_s	BPT32INDEX_DATA;            // Inherits from OBJ
    typedef struct BPT32Index_class_data_s BPT32INDEX_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT32Index_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Index_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetIndex) (OBJ_ID);
        bool            (*pSetManager) (OBJ_ID, OBJ_ID);
        // Methods:
        ERESULT         (*pGet) (OBJ_ID, uint32_t, uint32_t *, void *);
        ERESULT         (*pInsert) (OBJ_ID, uint32_t, void *);
        ERESULT         (*pSetup) (OBJ_ID, uint32_t, uint32_t, uint32_t, bool);
    } BPT32INDEX_VTBL;

    typedef struct BPT32Index_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Index_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32INDEX_DATA *);
    } BPT32INDEX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32INDEX_SINGLETON
    BPT32INDEX_DATA * BPT32Index_Shared (
        void
    );

    bool            BPT32Index_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPT32Index object if successful, otherwise OBJ_NIL.
     */
    BPT32INDEX_DATA * BPT32Index_Alloc (
        void
    );
    
    
    OBJ_ID          BPT32Index_Class (
        void
    );
    
    
    BPT32INDEX_DATA * BPT32Index_New (
        void
    );
    
    
    BPT32INDEX_DATA * BPT32Index_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        dataSize,
        LBN32_T         lbn,                    // Logical Block Number
        bool            fAllocate,              // true == allocate a buffer
        OBJ_ID          pMgr
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------


    uint8_t *       BPT32Index_getBlock (
        BPT32INDEX_DATA   *this
    );
    
    
    LBN32_T         BPT32Index_getLBN (
        BPT32INDEX_DATA *this
    );
    
    bool            BPT32Index_setLBN (
        BPT32INDEX_DATA *this,
        LBN32_T         value
    );
    
    
    bool            BPT32Index_setManager(
        BPT32INDEX_DATA  *this,
        OBJ_ID           *pMgr          // Block Manager
    );
    
    
    uint32_t        BPT32Index_getP0 (
        BPT32INDEX_DATA *this
    );
    
    bool            BPT32Index_setP0 (
        BPT32INDEX_DATA *this,
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
    ERESULT         BPT32Index_CopyFrom (
        BPT32INDEX_DATA *this,
        void            *pData
    );
    
    
    /*!
     Delete the entry if found.
     @param     this    object pointer
     @param     key     key of entry to be deleted
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         BPT32Index_Delete (
        BPT32INDEX_DATA *this,
        uint32_t        key
    );
    
   
    ERESULT         BPT32Index_FindIndex (
        BPT32INDEX_DATA *this,
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
    ERESULT         BPT32Index_FindKey (
        BPT32INDEX_DATA *this,
        uint32_t        key,
        uint32_t        *pIndex
    );
    
    
    /*!
     Flush the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
     error code.
     */
    ERESULT         BPT32Index_Flush (
        BPT32INDEX_DATA *this
    );
    
    
    ERESULT         BPT32Index_Get (
        BPT32INDEX_DATA *this,
        uint32_t        index,          // Relative to 1
        uint32_t        *pKey,
        LBN32_T         *pData
    );
    
    
    BPT32INDEX_DATA * BPT32Index_Init (
        BPT32INDEX_DATA   *this
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
    ERESULT         BPT32Index_Insert (
        BPT32INDEX_DATA *this,
        uint32_t        key,
        LBN32_T         *pData,
        BPT32INDEX_DATA **ppNew
    );

 
    /*!
     Read the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32Index_Read (
        BPT32INDEX_DATA *this
    );
    
    
    ERESULT         BPT32Index_Setup(
        BPT32INDEX_DATA *this,
        uint32_t        blockSize,
        uint32_t        dataSize,
        LBN32_T         lbn,                    // Logical Block Number
        bool            fAllocate               // true == allocate a buffer
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT32Index_ToDebugString(this,4);
     @endcode 
     @param     this    BPT32INDEX object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Index_ToDebugString (
        BPT32INDEX_DATA *this,
        int             indent
    );
    
    
    /*!
     Find an entry in the node and update its data.
     @param     this    object pointer
     @param     key     [input] numeric key
     @param     lbn     [input] Logical Sector Number
     @return    If successful, return ERESULT_SUCCESS and optionally copy the data to
                the area given. Otherwise, return an ERESULT_* error code.
     @warning   The data area provided must be at least dataSize bytes as given in
                the SetupSizes() method.
     */
    ERESULT         BPT32Index_Update (
        BPT32INDEX_DATA *this,
        uint32_t        key,
        LBN32_T         lbn
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32INDEX_H */

