// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          B-Plus 32-Bit Tree (bpt32) Header
//****************************************************************
/*
 * Program
 *			B-Plus 32-Bit Tree (bpt32)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate bpt32 to run things without complications
 *          of interfering with the main bpt32. A bpt32 may be 
 *          called a bpt32 on other O/S's.
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
#include        <lru.h>
#include        <rrds.h>


#ifndef         BPT32_H
#define         BPT32_H


//#define   BPT32_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct bpt32_data_s	BPT32_DATA;            // Inherits from OBJ
    typedef struct bpt32_class_data_s BPT32_CLASS_DATA;   // Inherits from OBJ

    typedef struct bpt32_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(BPT32_DATA *);
    } BPT32_VTBL;

    typedef struct bpt32_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in bpt32_object.c.
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
    BPT32_DATA *    bpt32_Shared (
        void
    );

    bool            bpt32_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to bpt32 object if successful, otherwise OBJ_NIL.
     */
    BPT32_DATA *    bpt32_Alloc (
        void
    );
    
    
    OBJ_ID          bpt32_Class (
        void
    );
    
    
    BPT32_DATA *    bpt32_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    LRU_DATA *  bpt32_getLRU (
        BPT32_DATA  *this
    );
    
    
    bool            bpt32_setReadWrite (
        BPT32_DATA     *this,
        ERESULT         (*pBlockRead) (
            OBJ_ID          pObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        ERESULT         (*pBlockWrite) (
            OBJ_ID          pObject,
            uint32_t        lsn,                // Logical Sector Number
            uint8_t         *pBuffer            // Buffer of sectorSize bytes
        ),
        OBJ_ID          pBlockObject
    );
    
    
    RRDS_DATA * bpt32_getRRDS (
        BPT32_DATA  *this
    );
    


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         bpt32_Add (
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
    ERESULT         bpt32_Close (
        BPT32_DATA      *this,
        bool            fDelete
    );
    
    
    /*!
     Create a new file for reading/writing.
     @param     this    object pointer
     @param     pPath   path object pointer for dataset/file
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         bpt32_Create (
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
    ERESULT         bpt32_Find (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    
    BPT32_DATA *    bpt32_Init (
        BPT32_DATA      *this
    );


    /*!
     Open an existing file for reading/writing.
     @param     this    object pointer
     @param     pPath   path object pointer for dataset/file
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         bpt32_Open (
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
    ERESULT         bpt32_SetupSizes(
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
        ASTR_DATA      *pDesc = bpt32_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     bpt32_ToDebugString (
        BPT32_DATA      *this,
        int             indent
    );
    
    
    ERESULT         bpt32_Update (
        BPT32_DATA      *this,
        uint32_t        key,
        void            *pData
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* BPT32_H */

