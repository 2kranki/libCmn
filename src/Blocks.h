// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          A List of Memory Blocks/Buffers (Blocks) Header
//****************************************************************
/*
 * Program
 *			A List of Memory Blocks/Buffers (Blocks)
 * Purpose
 *          This object provides a updatable list of data blocks.
 *          Many collections allocate smaller areas. This object
 *          provides an easy way to allocate those smaller areas
 *          in blocks to facilitate memory management. It only
 *          supports fixed-lenth records!
 *
 * Remarks
 *  1.      Internally, blocks are made up of nodes which have
 *          have a fixed size.
 *  2.      The unique number returned on a RecordNew will be
 *          unique for the entire lifetime of this object and
 *          will not be re-used even if the record is deleted
 *          and then re-used.
 *  3.      This object only support fixed length records.
 *
 * History
 *  09/04/2016 Generated
 *	01/10/2020 Regenerated
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
#include        <Enum.h>
#include        <listdl.h>


#ifndef         BLOCKS_H
#define         BLOCKS_H


//#define   BLOCKS_JSON_SUPPORT 1
//#define   BLOCKS_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Blocks_data_s	BLOCKS_DATA;            // Inherits from OBJ
    typedef struct Blocks_class_data_s BLOCKS_CLASS_DATA;   // Inherits from OBJ

    typedef struct Blocks_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Blocks_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLOCKS_DATA *);
    } BLOCKS_VTBL;

    typedef struct Blocks_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Blocks_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLOCKS_DATA *);
    } BLOCKS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BLOCKS_SINGLETON
    BLOCKS_DATA *   Blocks_Shared (
        void
    );

    void            Blocks_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Blocks object if successful, otherwise OBJ_NIL.
     */
    BLOCKS_DATA *   Blocks_Alloc (
        void
    );
    
    
    OBJ_ID          Blocks_Class (
        void
    );
    
    
    BLOCKS_DATA *   Blocks_New (
        void
    );
    
    
    BLOCKS_DATA *   Blocks_NewWithSizes (
        uint32_t        blockSize,      // If 0, use default size.
        uint32_t        recordSize
    );


    /*!
     Calculate the amount of space available in a block once this object's
     overhead is removed.
     @return:   the number of bytes available (-1 == blockSize is too small)
     */
    int32_t         Blocks_AvailableSize (
        uint32_t        blockSize       // If 0, use default size.
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        Blocks_getBlockAvail (
         BLOCKS_DATA     *this
    );


    uint32_t        Blocks_getBlockSize (
         BLOCKS_DATA     *this
    );

    /*!
    * The delete exit is called whenever an active record is to be
    * freed allowing any clean up to be performed.
    */
    bool            Blocks_setDeleteExit (
        BLOCKS_DATA     *this,
        P_ERESULT_EXIT3 pDelete,
        OBJ_ID          pObj,           // Used as first parameter of scan method
        void            *pArg3          // Used as third parameter of scan method
    );


    /*!
    * Active Records List
    */
    LISTDL_DATA *   Blocks_getList (
        BLOCKS_DATA     *this
    );


    /*! @property MaxRecords
        returns the current maximum number of
        records that this object can have. This
        number will change as more blocks are
        added.
     */
    uint32_t        Blocks_getMaxRecords (
        BLOCKS_DATA     *this
    );


    /*!
    * Number of Active Records
    */
    uint32_t        Blocks_getNumActive (
        BLOCKS_DATA     *this
    );


    uint32_t        Blocks_getRecordsPerBlock (
        BLOCKS_DATA     *this
    );


    uint32_t        Blocks_getRecordSize (
        BLOCKS_DATA     *this
    );


    /*!
    Return the number of blocks in the list.
    Example:
    @code
     uint32_t cBlocks = blocks_getSize(this);
    @endcode
    @param     this    BLOCKS object pointer
    @return    The amount the number of blocks in the list.
    */
    uint32_t        Blocks_getSize (
        BLOCKS_DATA     *this
    );


    uint32_t        Blocks_getUnique (
        BLOCKS_DATA     *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Create an Enumerator that will enumerate through all the blocks.
     @return    If successful, valid enumerator. Otherwise, OBJ_NIL.
                error code.
     @warning   Remember to release the returned Enumeration object.
     */
    ERESULT         Blocks_Enum (
        BLOCKS_DATA     *this,
        ENUM_DATA       **ppEnum
    );


    /*!
     Scan the active record list applying the given routine to each member
     of the list.  Halt the scan if an error return code is returned by
     the scan routine.
     @param     this    Object Pointer
     @param     pScan   Scan Routine Address
     @param     pObj    First Parameter for the Scan Routine (optional)
     @param     pArg3   Third Parameter for the Scan Routine (optional)
     @return:   If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
     error.
     */
    ERESULT         Blocks_ForEach (
        BLOCKS_DATA     *this,
        P_ERESULT_EXIT3 pScan,
        OBJ_ID          pObj,           // Used as first parameter of scan method
        void            *pArg3          // Used as third parameter of scan method
    );


    BLOCKS_DATA *   Blocks_Init (
        BLOCKS_DATA     *this
    );


    ERESULT         Blocks_RecordFree (
        BLOCKS_DATA     *this,
        void            *pRecord
    );


    /*!
     Return the address of the index'th record. This is relatively slow
     since it searches a doubly-linked list for the index'th entry.
     @param     this    Object Pointer
     @param     index   number of item on the active list (relative to 1)
     @return:   If successful, address of the record. Otherwise, NULL.
     */
    void *          Blocks_RecordGet (
        BLOCKS_DATA    *this,
        int32_t        index                    // (relative to 1)
    );


    /*!
     Return the address of the record given its unique number. This tries
     to be much faster than RecordGet() since it accesses an index to
     find the record.
     @param     this    Object Pointer
     @param     unique  record's unique number
     @return:   If successful, address of the record. Otherwise, NULL.
     */
    void *          Blocks_RecordGetUnique (
        BLOCKS_DATA    *this,
        uint32_t       unique
    );


    void *          Blocks_RecordNew (
        BLOCKS_DATA     *this,
        uint32_t        *pUnique            // Optional Unique Number.
    );


    /*! Return the unique number for the given record index.
     @param     this    Object Pointer
     @param     index   number of item on the active list (relative to 1)
     @return:   If successful, record unique number (> 0). Otherwise, 0.
     */
    uint32_t        Blocks_RecordUnique(
        BLOCKS_DATA    *this,
        int32_t        index                    // (relative to 1)
    );


    /*!
     Reset this object to its beginning state.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Blocks_Reset (
        BLOCKS_DATA     *this
    );


    /*!
     If there is an active index, then remove it.  Add a new index for
     the unique identifiers in the record and add all current records to
     it which greatly speeds up access by index number.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Blocks_SetupIndex (
        BLOCKS_DATA     *this
    );


    /*!
     Create a string that describes this object and the objects within it.
     @param     this        object pointer
     @param     blockSize   number of characters to indent every line of output, can be 0
     @param     recordSize  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     */
    ERESULT         Blocks_SetupSizes (
        BLOCKS_DATA     *this,
        uint32_t        blockSize,
        uint32_t        recordSize
    );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Blocks_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Blocks_ToDebugString (
        BLOCKS_DATA     *this,
        int             indent
    );
    
    
    uint32_t        Blocks_UniqueFromData(
        BLOCKS_DATA     *this,
        void            *pData
    );



    
#ifdef	__cplusplus
}
#endif

#endif	/* BLOCKS_H */

