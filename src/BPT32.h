// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  B-Plus Tree (BPT32) Header
//****************************************************************
/*
 * Program
 *          B-Plus Tree (BPT32)
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


#ifndef         BPT32_H
#define         BPT32_H


//#define   BPT32_IS_IMMUTABLE     1
//#define   BPT32_JSON_SUPPORT     1
//#define   BPT32_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT32_data_s  BPT32_DATA;            // Inherits from OBJ
    typedef struct BPT32_class_data_s BPT32_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT32_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32_DATA *);
    } BPT32_VTBL;

    typedef struct BPT32_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32_DATA *);
    } BPT32_CLASS_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32_SINGLETON
    BPT32_DATA *    BPT32_Shared (
        void
    );

    void            BPT32_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to BPT32 object if successful, otherwise OBJ_NIL.
     */
    BPT32_DATA *    BPT32_Alloc (
        void
    );
    
    
    OBJ_ID          BPT32_Class (
        void
    );
    
    
    BPT32_DATA *    BPT32_New (
        void
    );
    
    
    BPT32_DATA *    BPT32_NewWithSizes (
        uint16_t        blockSize,
        uint16_t        keyLen,
        uint16_t        keyOff
    );


#ifdef  BPT32_JSON_SUPPORT
    BPT32_DATA *   BPT32_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPT32_DATA *   BPT32_NewFromJsonStringA (
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

    ERESULT         BPT32_Add (
        BPT32_DATA      *this,
        uint16_t        size,
        void            *pRecord
    );


    void *          BPT32_Delete (
        BPT32_DATA      *this,
        void            *pKey
    );

   
    void *          BPT32_Find (
        BPT32_DATA      *this,
        void            *pKey,
        uint16_t        *pLen
    );


    BPT32_DATA *    BPT32_Init (
        BPT32_DATA      *this
    );


    ERESULT         BPT32_IsEnabled (
        BPT32_DATA      *this
    );
    
 
#ifdef  BPT32_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT32_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32_ToJson (
        BPT32_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32_ToDebugString (
        BPT32_DATA     *this,
        int             indent
    );
    
    
    ERESULT         BPT32_Update (
        BPT32_DATA      *this,
        uint16_t        size,
        void            *pRecord
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* BPT32_H */

