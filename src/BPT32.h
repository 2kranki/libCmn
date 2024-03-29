// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus 32-Bit Tree (BPT32) Header
//****************************************************************
/*
 * Program
 *			B-Plus 32-Bit Tree (BPT32)
 * Purpose
 *			This object provides support for a B-Plus Tree which
 *          has 32-bit integer keys. It uses BPT32idx (index blocks)
 *          and BPT32lf (leaf blocks) as well.
 *
 * Remarks
 *	1.      None
 *
 * References
 *  1.      "Reexamining B-trees", Ted Johnson and Dennis Shasha,
 *          Dr Dobb's Journal, January 1992
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
#include        <RRDS.h>


#ifndef         BPT32_H
#define         BPT32_H


//#define   BPT32_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct BPT32_data_s	BPT32_DATA;            // Inherits from OBJ
    typedef struct BPT32_class_data_s BPT32_CLASS_DATA;   // Inherits from OBJ

    typedef struct BPT32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32_DATA *);
    } BPT32_VTBL;

    typedef struct BPT32_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in BPT32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32_DATA *);
    } BPT32_CLASS_VTBL;



    
    
    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  BPT32_SINGLETON
    BPT32_DATA *    BPT32_Shared (
        void
    );

    bool            BPT32_SharedReset (
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
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    RRDS_DATA * BPT32_getIO (
        BPT32_DATA  *this
    );
    
    bool        BPT32_setIO (
        BPT32_DATA  *this,
        RRDS_DATA   *pValue
    );

    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Add the given key/data pair in the index if it does not already
     exist.
     @param     this    object pointer
     @param     key     key to be added (must be > 0)
     @param     pData   optional pointer to data area of data size.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT32_Add (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    
    /*!
     Close an open file from reading/writing.
     @param     this    object pointer
     @param     fDelete If true, delete the file after closing it.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT32_Close (
        BPT32_DATA      *this,
        bool            fDelete
    );
    
    
    /*!
     Create a new file for reading/writing.
     @param     this    object pointer
     @param     pPath   path object pointer for dataset/file
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT32_Create (
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    );
    
    
    /*!
     Search the index for the specified key.  If found, return the data
     component of the index associated with the key.
     @param     this    object pointer
     @param     key     integer data key
     @param     pData   optional pointer to data area of data size.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT32_Find (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    
    /*!
     Retrieve the first key/data pair in the index.
     @param     this    object pointer
     @param     pKey    optional pointer to key
     @param     pData   optional pointer to data area of data size.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT32_First (
        BPT32_DATA      *this,
        uint32_t        *pKey,
        void            *pData
    );
    
    
    BPT32_DATA *    BPT32_Init (
        BPT32_DATA      *this
    );


    /*!
     Retrieve the next key/data pair in the index from the last one accessed.
     @param     this    object pointer
     @param     pKey    optional pointer to key
     @param     pData   optional pointer to data area of data size.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT32_Next (
        BPT32_DATA      *this,
        uint32_t        *pKey,
        void            *pData
    );
    
    
    /*!
     Open an existing file for reading/writing.
     @param     this    object pointer
     @param     pPath   path object pointer for dataset/file
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         BPT32_Open (
        BPT32_DATA      *this,
        PATH_DATA       *pPath
    );
    
    
    /*!
     Set up the sizes needed to properly build the index dataset/file.  This
     method should be called before a Create() or an Open().  For the Open(),
     the blockSize and dataSize will be gotten from the file path given.  So,
     use 64 and 4 respectively for that call.
     @param     this        object pointer
     @param     blockSize   size of the file block which must be greater than
                            128
     @param     dataSize    size of the data to be associated with an integer key
     @param     cLRU        number of LRU Buffers
     @param     cHash       LRU Hash Size (Use prime number for this if possible.)
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         BPT32_SetupSizes(
        BPT32_DATA      *this,
        uint32_t        blockSize,
        uint16_t        dataSize,
        uint16_t        cLRU,
        uint16_t        cHash
    );
    
    
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
        BPT32_DATA      *this,
        int             indent
    );
    
    
    ERESULT         BPT32_Update (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32_H */

