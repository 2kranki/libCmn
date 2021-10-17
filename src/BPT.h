// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  B-Plus Tree (BPT) Header
//****************************************************************
/*
 * Program
 *          B-Plus Tree (BPT)
 * Purpose
 *          This object provides support for a B-Plus Tree which
 *          has fixed size keys embedded at a fixed location within
 *          each record of the dataset. The records may be variable
 *          length, but the key must always fit within the record
 *          at the same location in each. The maximum key length
 *          is 255. All blocks within the dataset are a fixed size
 *          and allocated as needed.
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





#include        <cmn_defs.h>
#include        <AStr.h>
#include        <lru.h>
#include        <RRDS.h>


#ifndef         BPT_H
#define         BPT_H


//#define   BPT_IS_IMMUTABLE     1
//#define   BPT_JSON_SUPPORT     1
//#define   BPT_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT_data_s  BPT_DATA;            // Inherits from OBJ
    typedef struct BPT_class_data_s BPT_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT_DATA *);
    } BPT_VTBL;

    typedef struct BPT_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT_DATA *);
    } BPT_CLASS_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT_SINGLETON
    BPT_DATA *    BPT_Shared (
        void
    );

    void            BPT_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPT object if successful, otherwise OBJ_NIL.
     */
    BPT_DATA *    BPT_Alloc (
        void
    );
    
    
    OBJ_ID          BPT_Class (
        void
    );
    
    
    BPT_DATA *    BPT_New (
        void
    );
    
    
    BPT_DATA *    BPT_NewWithSizes (
        uint16_t        blockSize,
        uint16_t        keyLen,
        uint16_t        keyOff,
        uint16_t        cLRU,
        uint16_t        cHash
    );


#ifdef  BPT_JSON_SUPPORT
    BPT_DATA *   BPT_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPT_DATA *   BPT_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given record to the dataset if it does not already
     exist.
     @param     this    object pointer
     @param     size    record size in bytes (must be >= keyLen property)
     @param     pRecord record pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT_Add (
        BPT_DATA        *this,
        uint16_t        size,
        void            *pRecord
    );


    /*!
     Close an open file from reading/writing.
     @param     this    object pointer
     @param     fDelete If true, delete the file after closing it.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT_Close (
        BPT_DATA        *this,
        bool            fDelete
    );


    /*!
     Create a new file for reading/writing.
     @param     this    object pointer
     @param     pPath   path object pointer for dataset/file
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT_Create (
        BPT_DATA        *this,
        PATH_DATA       *pPath
    );


    void *          BPT_Delete (
        BPT_DATA        *this,
        void            *pKey
    );

   
    /*!
     Search the index for the specified key.  If found, return the data
     component of the index associated with the key.
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
    ERESULT         BPT_Find (
        BPT_DATA        *this,
        uint8_t         *pKey,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    );


    /*!
     Retrieve the first key/data pair in the index.
     @param     this    object pointer
     @param     pData   optional pointer to data area of cData size.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT_First (
        BPT_DATA        *this,
        uint16_t        cData,
        void            *pData,
        uint16_t        *pUsed
    );


    BPT_DATA *      BPT_Init (
        BPT_DATA        *this
    );


    /*!
     Set up the sizes needed to properly build the index dataset/file.  This
     method should be called before a Create() or an Open().  For the Open(),
     the blockSize and dataSize will be gotten from the file path given.  So,
     use 64 and 4 respectively for that call.
     @param     this        object pointer
     @param     blockSize   size of the file block which must be greater than
                            128
     @param     keyLen      key length in bytes
     @param     keyOff      key offset within the record relative to 0
     @param     cLRU        number of LRU Buffers
     @param     cHash       LRU Hash Size (Use prime number for this if possible.)
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT_SetupSizes(
        BPT_DATA        *this,
        uint32_t        blockSize,
        uint16_t        keyLen,
        uint16_t        keyOff,
        uint16_t        cLRU,
        uint16_t        cHash
    );


#ifdef  BPT_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT_ToJson (
        BPT_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT_ToDebugString (
        BPT_DATA     *this,
        int             indent
    );
    
    
    ERESULT         BPT_Update (
        BPT_DATA      *this,
        uint16_t        size,
        void            *pRecord
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* BPT_H */

