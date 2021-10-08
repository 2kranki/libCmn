// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  B-Plus Tree Index Block (BPT32Index) Header
//****************************************************************
/*
 * Program
 *          B-Plus Tree Index Block (BPT32Index)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate BPT32Index to run things without complications
 *          of interfering with the main BPT32Index. A BPT32Index may be 
 *          called a BPT32Index on other O/S's.
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


#ifndef         BPT32INDEX_H
#define         BPT32INDEX_H


//#define   BPT32INDEX_IS_IMMUTABLE     1
//#define   BPT32INDEX_JSON_SUPPORT     1
//#define   BPT32INDEX_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT32Index_data_s  BPT32INDEX_DATA;            // Inherits from OBJ
    typedef struct BPT32Index_class_data_s BPT32INDEX_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT32Index_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Index_object.c.
        // Properties:
        uint8_t *       (*pGetBlock) (OBJ_ID);
        uint32_t        (*pGetLBN) (OBJ_ID);            // Get Logical Block Number
        // Methods:
        //bool        (*pIsEnabled)(BPT32INDEX_DATA *);
    } BPT32INDEX_VTBL;

    typedef struct BPT32Index_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32Index_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32INDEX_DATA *);
    } BPT32INDEX_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32INDEX_SINGLETON
    BPT32INDEX_DATA * BPT32Index_Shared (
        void
    );

    void            BPT32Index_SharedReset (
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
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff,                 // relative to zero
        OBJ_ID          pMgr
    );


#ifdef  BPT32INDEX_JSON_SUPPORT
    BPT32INDEX_DATA * BPT32Index_NewFromJsonString (
        ASTR_DATA       *pString
    );

    BPT32INDEX_DATA * BPT32Index_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        BPT32Index_getKeyLen (
        BPT32INDEX_DATA *this
    );


    uint16_t        BPT32Index_getKeyOff (
        BPT32INDEX_DATA *this
    );


    uint32_t        BPT32Index_getLBN (
        BPT32INDEX_DATA *this
    );

    bool            BPT32Index_setLBN (
        BPT32INDEX_DATA *this,
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
    ERESULT         BPT32Index_Add (
        BPT32INDEX_DATA *this,
        uint32_t        lbn,
        void            *pKey
    );


    BPT32INDEX_DATA *   BPT32Index_Init (
        BPT32INDEX_DATA     *this
    );


    /*!
     Set up an empty block.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise an ERESULT_* error.
     */
    ERESULT         BPT32Index_Setup(
        BPT32INDEX_DATA *this,
        uint32_t        blockSize,
        uint32_t        lbn,
        uint16_t        keyLen,
        uint16_t        keyOff                  // relative to zero
    );


#ifdef  BPT32INDEX_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = BPT32Index_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Index_ToJson (
        BPT32INDEX_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = BPT32Index_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     BPT32Index_ToDebugString (
        BPT32INDEX_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* BPT32INDEX_H */

