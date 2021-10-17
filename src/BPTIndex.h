// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  B-Plus Tree Index Block (BPTIndex) Header
//****************************************************************
/*
 * Program
 *          B-Plus Tree Index Block (BPTIndex)
 * Purpose
 *          This object provides a B-Plus Tree Index Block and its
 *          manipulation.  The block consists of a base area, record
 *          area and reserved area.  The base area and reserved area
 *          contain controlling information for the entire block.
 *          The record area consists of 0 or more fixed size records
 *          where each record consists of a block number along with
 *          a fixed length key.  Given the block size and the key
 *          length, the maximum number of records can easily be cal-
 *          culated for the block.
 *
 *          Each key in this block represents the left-most key of
 *          of a child block which can be another index block or a
 *          leaf block.
 *
 *          There is also a special index, P0, which points to the
 *          child block of keys less than the key in the first node
 *          entry.
 *
 * Remarks
 *  1.      When a key pointer is provided to a method, it is assumed
 *          that memory can be accessed at that address for property
 *          KeyLen long.
 *
 * History
 *  01/12/2019 Generated
 *  09/25/2021 Regenerated and keys changed from uint32_t to variable
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


#ifndef         BPTINDEX_H
#define         BPTINDEX_H


//#define   BPTINDEX_IS_IMMUTABLE     1
//#define   BPTINDEX_JSON_SUPPORT     1
//#define   BPTINDEX_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPTIndex_data_s  BPTINDEX_DATA;            // Inherits from OBJ
    typedef struct BPTIndex_class_data_s BPTINDEX_CLASS_DATA;   // Inherits from OBJ

    // WARNING: This must conform to BPT_BLK_VTBL found in BPT_Request.h.
    typedef struct BPTIndex_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPTIndex_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetLBN) (OBJ_ID);            // Get Logical Block Number
        // Methods:
        //bool        (*pIsEnabled)(BPTINDEX_DATA *);
    } BPTINDEX_VTBL;

    typedef struct BPTIndex_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPTIndex_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPTINDEX_DATA *);
    } BPTINDEX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPTINDEX_SINGLETON
    BPTINDEX_DATA * BPTIndex_Shared (
        void
    );

    void            BPTIndex_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPTIndex object if successful, otherwise OBJ_NIL.
     */
    BPTINDEX_DATA * BPTIndex_Alloc (
        void
    );
    
    
    OBJ_ID          BPTIndex_Class (
        void
    );
    
    
    BPTINDEX_DATA * BPTIndex_New (
        void
    );
    
    
    BPTINDEX_DATA * BPTIndex_NewWithSizes (
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff,                 // relative to zero
        OBJ_ID          pMgr
    );


#ifdef  BPTINDEX_JSON_SUPPORT
    BPTINDEX_DATA * BPTIndex_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPTINDEX_DATA * BPTIndex_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        BPTIndex_getKeyLen (
        BPTINDEX_DATA *this
    );


    uint16_t        BPTIndex_getKeyOff (
        BPTINDEX_DATA *this
    );


    uint32_t        BPTIndex_getLBN (
        BPTINDEX_DATA *this
    );

    bool            BPTIndex_setLBN (
        BPTINDEX_DATA *this,
        uint32_t        value
    );

    
    uint32_t        BPTIndex_getP0 (
        BPTINDEX_DATA *this
    );

    bool            BPTIndex_setP0 (
        BPTINDEX_DATA *this,
        uint32_t        value
    );



//---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add a record to the block in ascending sequence by key.  If the key
     already exists in the block, return an error.
     @param     this    object pointer
     @param     lbn     [input] logical block number
     @param     pKey    [input] key (length is assumed to be same as defined at
                        open/create)
     @return    If successful, return ERESULT_SUCCESS. Otherwise, return an
                ERESULT_* error code.
     */
    ERESULT         BPTIndex_Add (
        BPTINDEX_DATA *this,
        uint32_t        lbn,
        void            *pKey
    );


    /*!
     Delete a record from the block that matches tth given key.
     @param     this    object pointer
     @param     pKey    [input] key of record to delete
     @return    If successful, return ERESULT_SUCCESS. Otherwise, return an
                ERESULT_* error code.
     */
    ERESULT         BPTIndex_Delete (
        BPTINDEX_DATA *this,
        void            *pKey
    );


    /*!
     Flush the block to its backing dataset/file.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPTIndex_Flush (
        BPTINDEX_DATA *this
    );


    /*!
     Scan all the records in order by ascending record number.
     @return    ERESULT_SUCCESS if successful completion.  Otherwise,
                an ERESULT_* error code is returned.
     */
    ERESULT         BPTIndex_ForEach (
        BPTINDEX_DATA *this,
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
    ERESULT         BPTIndex_Get (
        BPTINDEX_DATA *this,
        void            *pKey,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    );


    BPTINDEX_DATA *   BPTIndex_Init (
        BPTINDEX_DATA     *this
    );


    /*!
     Get the maximum number of records per block.
     @param     this    object pointer
     @return    if successful, the maximum number of records.  Otherwise, 0.
     */
    uint32_t        BPTIndex_MaxRcds (
        BPTINDEX_DATA *this
    );


    /*!
     Set up an empty block.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_* error.
     */
    ERESULT         BPTIndex_Setup(
        BPTINDEX_DATA *this,
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff                  // relative to zero
    );


#ifdef  BPTINDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPTIndex_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTIndex_ToJson (
        BPTINDEX_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPTIndex_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPTIndex_ToDebugString (
        BPTINDEX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* BPTINDEX_H */

