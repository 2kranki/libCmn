// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus 32-Bit Tree Leaf Block (BPT32Leaf) Header
//****************************************************************
/*
 * Program
 *			B-Plus 32-Bit Tree Leaf Block
 * Purpose
 *			This object provides support for a 32-bit B+ Tree Leaf
 *          block.  A Leaf block consists of an array of nodes where
 *          each node consists of a uint32_t key and fixed sized
 *          data. The size of the data is specified at block creation
 *          time.  The block is normally part of a doubly-linked
 *          list of leaf blocks for fast sequential access. It is
 *          used by the bpt32 object.
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


#ifndef         BPT32LEAF_H
#define         BPT32LEAF_H


//#define   BPT32LEAF_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT32Leaf_data_s	BPT32LEAF_DATA;            // Inherits from OBJ
    typedef struct BPT32Leaf_class_data_s BPT32LEAF_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT32Leaf_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Leaf_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetIndex) (OBJ_ID);
        bool            (*pSetManager) (OBJ_ID, OBJ_ID);
        // Methods:
        ERESULT         (*pGet) (OBJ_ID, uint32_t, uint32_t *, void *);
        ERESULT         (*pInsert) (OBJ_ID, uint32_t, void *);
        ERESULT         (*pSetup) (OBJ_ID, uint32_t, uint32_t, uint32_t, bool);
    } BPT32LEAF_VTBL;

    typedef struct BPT32Leaf_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Leaf_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32LEAF_DATA *);
    } BPT32LEAF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32LEAF_SINGLETON
    BPT32LEAF_DATA *  BPT32Leaf_Shared (
        void
    );

    bool            BPT32Leaf_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPT32Leaf object if successful, otherwise OBJ_NIL.
     */
    BPT32LEAF_DATA *  BPT32Leaf_Alloc (
        void
    );
    
    
    OBJ_ID          BPT32Leaf_Class (
        void
    );
    
    
    BPT32LEAF_DATA *  BPT32Leaf_New (
        void
    );
    
    BPT32LEAF_DATA *  BPT32Leaf_NewWithSizes (
        uint32_t        blockSize,
        uint16_t        dataSize,
        LBN32_T         lbn,                    // Logical Block Number
        bool            fAllocate,
        OBJ_ID          pMgr
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       BPT32Leaf_getBlock (
        BPT32LEAF_DATA  *this
    );
    
    
    LBN32_T         BPT32Leaf_getLBN (
        BPT32LEAF_DATA  *this
    );
    
    bool            BPT32Leaf_setLBN (
        BPT32LEAF_DATA  *this,
        LBN32_T         value
    );
    
    
    /*!
     The last index property provides access to the last node
     index within this leaf when a key was inserted or accessed.
     Generally, this is used with Get() for accessing all the
     keys in the Leaf block.
     */
    uint32_t        BPT32Leaf_getLastIndex (
        BPT32LEAF_DATA    *this
    );
    
    
    bool            BPT32Leaf_setManager(
        BPT32LEAF_DATA    *this,
        OBJ_ID          *pMgr          // Block Manager
    );
    
    
    uint32_t        BPT32Leaf_getNext (
        BPT32LEAF_DATA    *this
    );
    
    bool            BPT32Leaf_setNext (
        BPT32LEAF_DATA    *this,
        uint32_t        value
    );
    
    
    uint32_t        BPT32Leaf_getParent (
        BPT32LEAF_DATA    *this
    );
    
    bool            BPT32Leaf_setParent (
        BPT32LEAF_DATA    *this,
        uint32_t        value
    );

    
    uint32_t        BPT32Leaf_getPrev (
        BPT32LEAF_DATA    *this
    );
    
    bool            BPT32Leaf_setPrev (
        BPT32LEAF_DATA    *this,
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
    ERESULT         BPT32Leaf_CopyFrom (
        BPT32LEAF_DATA   *this,
        void           *pData
    );
    
    
    /*!
     Delete the entry if found.
     @param     this    object pointer
     @param     key     key of entry to be deleted
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32Leaf_Delete (
        BPT32LEAF_DATA    *this,
        uint32_t        key
    );
    
    
    /*!
     Find an entry in the node.  If found, optionally return the data to the are given.
     @param     this    object pointer
     @param     key     [input] numeric key
     @param     pData   [output] pointer to data
     @return    If successful, return ERESULT_SUCCESS and optionally copy the data to
     the area given. Otherwise, return an ERESULT_* error code.
     @warning   The data area provided must be at least dataSize bytes as given in
     the SetupSizes() method.
     */
    ERESULT         BPT32Leaf_FindKey (
        BPT32LEAF_DATA    *this,
        uint32_t        key,
        void            *pData
    );
    
    
    /*!
     Flush the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32Leaf_Flush (
        BPT32LEAF_DATA    *this
    );
    
    
    ERESULT         BPT32Leaf_Get (
        BPT32LEAF_DATA    *this,
        uint32_t        index,          // Relative to 1
        uint32_t        *pKey,
        void            *pData
    );
    
    
    BPT32LEAF_DATA *  BPT32Leaf_Init (
        BPT32LEAF_DATA    *this
    );


    ERESULT         BPT32Leaf_Insert (
        BPT32LEAF_DATA	*this,
        uint32_t        key,
        void            *pData
    );
    
 
    /*!
     Every method which accesses keys within leaf retains the memory
     of successful access.  This utilizes that saved value to provide
     back the next key/data pair from the leaf until EOF occurs.
     @param this    Object Pointer
     @param pKey    Optional pointer to a key field to be returned
     @param pData   Optional pointer to a data field to be returned.
     */
    ERESULT         BPT32Leaf_NextKey (
        BPT32LEAF_DATA    *this,
        uint32_t        *pKey,
        void            *pData
    );
    
    
    ERESULT         BPT32Leaf_Setup(
        BPT32LEAF_DATA    *this,
        uint32_t        blockSize,
        uint16_t        dataSize,
        uint32_t        index,
        bool            fAllocate
    );
    
    
    ERESULT         BPT32Leaf_Split (
        BPT32LEAF_DATA    *this,
        uint32_t        key,
        void            *pData,
        uint32_t        nodeIndex
    );
    
    
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
    ASTR_DATA *    BPT32Leaf_ToDebugString (
        BPT32LEAF_DATA    *this,
        int             indent
    );
    
    
    /*!
     Find an entry in the node and update its data.
     @param     this    object pointer
     @param     key     [input] numeric key
     @param     pData   [input] pointer to data
     @return    If successful, return ERESULT_SUCCESS and optionally copy the data to
     the area given. Otherwise, return an ERESULT_* error code.
     @warning   The data area provided must be at least dataSize bytes as given in
     the SetupSizes() method.
     */
    ERESULT         BPT32Leaf_Update (
        BPT32LEAF_DATA    *this,
        uint32_t        key,
        void            *pData
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32LEAF_H */

