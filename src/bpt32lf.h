// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus 32-Bit Tree Leaf Block (bpt32lf) Header
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
 *          list of leaf blocks for fast sequential access.
 *
 *          Note that the data size can vary according to require-
 *          ments, but is the same for all node entries once the
 *          block is created.  Whereas, an index block has fixed
 *          sized nodes.
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


#ifndef         BPT32LF_H
#define         BPT32LF_H


//#define   BPT32LF_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bpt32lf_data_s	BPT32LF_DATA;            // Inherits from OBJ
    typedef struct bpt32lf_class_data_s BPT32LF_CLASS_DATA;   // Inherits from OBJ

    typedef struct bpt32lf_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32lf_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetIndex) (OBJ_ID);
        bool            (*pSetManager) (OBJ_ID, OBJ_ID);
        // Methods:
        ERESULT         (*pGet) (OBJ_ID, uint32_t, uint32_t *, void *);
        ERESULT         (*pInsert) (OBJ_ID, uint32_t, void *);
        ERESULT         (*pSetup) (OBJ_ID, uint32_t, uint32_t, uint32_t, bool);
    } BPT32LF_VTBL;

    typedef struct bpt32lf_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32lf_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32LF_DATA *);
    } BPT32LF_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32LF_SINGLETON
    BPT32LF_DATA *  bpt32lf_Shared (
        void
    );

    bool            bpt32lf_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to bpt32lf object if successful, otherwise OBJ_NIL.
     */
    BPT32LF_DATA *  bpt32lf_Alloc (
        void
    );
    
    
    OBJ_ID          bpt32lf_Class (
        void
    );
    
    
    BPT32LF_DATA *  bpt32lf_New (
        void
    );
    
    BPT32LF_DATA *  bpt32lf_NewWithSizes (
        uint32_t        blockSize,
        uint16_t        dataSize,
        uint32_t        index,
        bool            fAllocate,
        OBJ_ID          pMgr
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       bpt32lf_getBlock (
        BPT32LF_DATA     *this
    );
    
    
    uint32_t        bpt32lf_getIndex (
        BPT32LF_DATA    *this
    );
    
    bool            bpt32lf_setIndex (
        BPT32LF_DATA    *this,
        uint32_t        value
    );
    
    
    /*!
     The last index property provides access to the last node
     index within this leaf when a key was inserted or accessed.
     Generally, this is used with Get() for accessing all the
     keys in the Leaf block.
     */
    uint32_t        bpt32lf_getLastIndex (
        BPT32LF_DATA    *this
    );
    
    
    bool            bpt32lf_setManager(
        BPT32LF_DATA    *this,
        OBJ_ID          *pMgr          // Block Manager
    );
    
    
    uint32_t        bpt32lf_getNext (
        BPT32LF_DATA    *this
    );
    
    bool            bpt32lf_setNext (
        BPT32LF_DATA    *this,
        uint32_t        value
    );
    
    
    uint32_t        bpt32lf_getParent (
        BPT32LF_DATA    *this
    );
    
    bool            bpt32lf_setParent (
        BPT32LF_DATA    *this,
        uint32_t        value
    );

    
    uint32_t        bpt32lf_getPrev (
        BPT32LF_DATA    *this
    );
    
    bool            bpt32lf_setPrev (
        BPT32LF_DATA    *this,
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
    ERESULT         bpt32lf_CopyFrom (
        BPT32LF_DATA   *this,
        void           *pData
    );
    
    
    /*!
     Delete the entry if found.
     @param     this    object pointer
     @param     key     key of entry to be deleted
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bpt32lf_Delete (
        BPT32LF_DATA    *this,
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
    ERESULT         bpt32lf_FindKey (
        BPT32LF_DATA    *this,
        uint32_t        key,
        void            *pData
    );
    
    
    /*!
     Flush the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         bpt32lf_Flush (
        BPT32LF_DATA    *this
    );
    
    
    ERESULT         bpt32lf_Get (
        BPT32LF_DATA    *this,
        uint32_t        index,          // Relative to 1
        uint32_t        *pKey,
        void            *pData
    );
    
    
    BPT32LF_DATA *  bpt32lf_Init (
        BPT32LF_DATA    *this
    );


    ERESULT         bpt32lf_Insert (
        BPT32LF_DATA	*this,
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
    ERESULT         bpt32lf_NextKey (
        BPT32LF_DATA    *this,
        uint32_t        *pKey,
        void            *pData
    );
    
    
    ERESULT         bpt32lf_Setup(
        BPT32LF_DATA    *this,
        uint32_t        blockSize,
        uint16_t        dataSize,
        uint32_t        index,
        bool            fAllocate
    );
    
    
    ERESULT         bpt32lf_Split (
        BPT32LF_DATA    *this,
        uint32_t        key,
        void            *pData,
        uint32_t        nodeIndex
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = bpt32lf_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    bpt32lf_ToDebugString (
        BPT32LF_DATA    *this,
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
    ERESULT         bpt32lf_Update (
        BPT32LF_DATA    *this,
        uint32_t        key,
        void            *pData
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32LF_H */

