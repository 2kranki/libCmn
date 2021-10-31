// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Fixed Length Records within 16-bit sized Block (BlockF16) Header
//****************************************************************
/*
 * Program
 *          Fixed Length Records within 16-bit sized Block (BlockF16)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate BlockF16 to run things without complications
 *          of interfering with the main BlockF16. A BlockF16 may be 
 *          called a BlockF16 on other O/S's.
 *
 * Remarks
 *  1.      This object uses OBJ_FLAG_USER1.
 *
 * History
 *  10/22/2021 Generated
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


#ifndef         BLOCKF16_H
#define         BLOCKF16_H


//#define   BLOCKF16_IS_IMMUTABLE     1
//#define   BLOCKF16_JSON_SUPPORT     1
//#define   BLOCKF16_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BlockF16_data_s  BLOCKF16_DATA;            // Inherits from OBJ
    typedef struct BlockF16_class_data_s BLOCKF16_CLASS_DATA;   // Inherits from OBJ

    typedef struct BlockF16_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BlockF16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLOCKF16_DATA *);
    } BLOCKF16_VTBL;

    typedef struct BlockF16_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BlockF16_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BLOCKF16_DATA *);
    } BLOCKF16_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BLOCKF16_SINGLETON
    BLOCKF16_DATA * BlockF16_Shared (
        void
    );

    void            BlockF16_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BlockF16 object if successful, otherwise OBJ_NIL.
     */
    BLOCKF16_DATA * BlockF16_Alloc (
        void
    );
    
    
    OBJ_ID          BlockF16_Class (
        void
    );
    
    
    BLOCKF16_DATA * BlockF16_New (
        void
    );
    
    BLOCKF16_DATA * BlockF16_NewWithSizes (
        uint16_t        blockSize,
        uint16_t        rsvdSize,
        uint16_t        dataSize
    );


#ifdef  BLOCKF16_JSON_SUPPORT
    BLOCKF16_DATA *   BlockF16_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BLOCKF16_DATA *   BlockF16_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint8_t *       BlockF16_getBlock (
        BLOCKF16_DATA   *this
    );


    uint16_t        BlockF16_getBlockSize (
        BLOCKF16_DATA   *this
    );


    uint16_t        BlockF16_getDataSize (
        BLOCKF16_DATA   *this
    );


    uint16_t        BlockF16_getMaxRecords(
        BLOCKF16_DATA   *this
    );


    uint16_t        BlockF16_getNumRecords(
        BLOCKF16_DATA   *this
    );


    void *          BlockF16_getReserved(
        BLOCKF16_DATA   *this
    );


    uint16_t        BlockF16_getReservedSize (
        BLOCKF16_DATA   *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add a record to the block if there is room. The size of the
     data provided must be at least property dataSize.
    @param     this         object pointer
    @param     pData        pointer to the data area of fixed size
                            defined by property dataSize
    @return    If successful, ERESULT_SUCCESS. An ERESULT_* error code.
    */
    ERESULT         BlockF16_Add (
        BLOCKF16_DATA   *this,
        void            *pData
    );


    /*!
     Copy a record from the block into a supplied area. The size of the
     area must be at least property dataSize.
    @param     this         object pointer
    @param     index        [in] record number (relative to 1)
    @param     pData        [out] pointer to the data area
    @return    If successful, ERESULT_SUCCESS. An ERESULT_* error code.
    */
    ERESULT         BlockF16_Get (
        BLOCKF16_DATA   *this,
        uint32_t        index,
        void            *pData
    );


    BLOCKF16_DATA * BlockF16_Init (
        BLOCKF16_DATA   *this
    );


    /*!
     Insert the provided record into the block after the record index. An index of 0
     is allowed and inserts the record at the front of the block.
    @param     this         object pointer
    @param     index        [in] record number (relative to 0)
    @param     pData        [in] pointer to the data area
    @return    If successful, ERESULT_SUCCESS. An ERESULT_* error code.
    */
    ERESULT         BlockF16_Insert (
        BLOCKF16_DATA   *this,
        uint32_t        index,
        void            *pData
    );
    
 
    /*!
     Establish the block parameters and allocate it.
     @param     this        object pointer
     @param     blockSize   size of the block in bytes
     @param     rsvdSize    size of the optional reserved area in bytes
     @param     dataSize    size of the records within the block in bytes
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         BlockF16_Setup(
        BLOCKF16_DATA   *this,
        uint16_t        blockSize,
        uint16_t        rsvdSize,
        uint16_t        dataSize
    );


    ERESULT         BlockF16_Split (
        BLOCKF16_DATA   *this,
        BLOCKF16_DATA   **ppNewObj,
        BLOCKF16_DATA   *(*pNew)(
            uint16_t        blockSize,
            uint16_t        rsvdSize,
            uint16_t        dataSize
        )
    );


#ifdef  BLOCKF16_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BlockF16_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlockF16_ToJson (
        BLOCKF16_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BlockF16_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BlockF16_ToDebugString (
        BLOCKF16_DATA     *this,
        int             indent
    );
    
    
    /*!
     Update the record at the given index by the provided record.
    @param     this         object pointer
    @param     index        [in] record number (relative to 1)
    @param     pData        [in] pointer to the data area
    @return    If successful, ERESULT_SUCCESS. An ERESULT_* error code.
    */
    ERESULT         BlockF16_Update (
        BLOCKF16_DATA   *this,
        uint32_t        index,
        void            *pData
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* BLOCKF16_H */

