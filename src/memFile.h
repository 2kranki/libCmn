// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Memory Based File (memFile) Header
//****************************************************************
/*
 * Program
 *			Memory Based File (memFile)
 * Purpose
 *			This object provides a memory based standard I/O
 *          file.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	01/13/2019 Generated
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
#include        <path.h>


#ifndef         MEMFILE_H
#define         MEMFILE_H


//#define   MEMFILE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct memFile_data_s	MEMFILE_DATA;            // Inherits from OBJ
    typedef struct memFile_class_data_s MEMFILE_CLASS_DATA;   // Inherits from OBJ

    typedef struct memFile_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memFile_object.c.
        // Properties:
        // Methods:
        ERESULT         (*pClose) (
            OBJ_ID          this,
            bool            fDelete
        );
        ERESULT         (*pCreate) (
            OBJ_ID          this,
            PATH_DATA       *pPath
        );
        ERESULT         (*pGets) (
            OBJ_ID          this,
            uint32_t        cBuffer,
            uint8_t         *pBuffer
        );
        ERESULT         (*pOpen) (
            OBJ_ID          this,
            PATH_DATA       *pPath
        );
        ERESULT         (*pRead) (
            OBJ_ID          this,
            uint32_t        cBuffer,
            void            *pBuffer,
            uint32_t        *pReadCount
        );
        off_t           (*pSeekBegin) (
            OBJ_ID          this,
            off_t           offset
        );
        off_t           (*pSeekCur) (
            OBJ_ID          this,
            off_t           offset
        );
        off_t           (*pSeekEnd) (
            OBJ_ID          this,
            off_t           offset
        );
        size_t          (*pSize) (
            OBJ_ID          this
        );
        off_t           (*pTell) (
            OBJ_ID          this
        );
        ERESULT         (*pWrite) (
            OBJ_ID          this,
            uint32_t        cBuffer,
            const
            void            *pBuffer
        );
    } MEMFILE_VTBL;

    typedef struct memFile_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in memFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(MEMFILE_DATA *);
    } MEMFILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  MEMFILE_SINGLETON
    MEMFILE_DATA *  memFile_Shared (
        void
    );

    bool            memFile_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to memFile object if successful, otherwise OBJ_NIL.
     */
    MEMFILE_DATA *  memFile_Alloc (
        void
    );
    
    
    OBJ_ID          memFile_Class (
        void
    );
    
    
    MEMFILE_DATA *  memFile_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint32_t        memFile_getBlockSize (
        MEMFILE_DATA    *this
    );


    uint32_t        memFile_getSize (
        MEMFILE_DATA       *this
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Close an open file from reading/writing.
     @param     this    object pointer
     @param     fDelete If true, delete the file after closing it.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         memFile_Close (
        MEMFILE_DATA    *this,
        bool            fDelete
    );
    
    
    /*!
     Create a new file for reading/writing.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         memFile_Create (
        MEMFILE_DATA    *this,
        PATH_DATA       *pPath
    );
    
    
    /*!
     Read a line from the file and store it into the buffer. Stop when either
     (cBuffer - 1) characters are read, the newline character is read, or the
     end-of-file is reached, whichever comes first.
     @param     this    object pointer
     @param     cBuffer size of the buffer which must be greater than 1
     @param     pBuffer buffer pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         memFile_Gets (
        MEMFILE_DATA     *this,
        uint32_t        cBuffer,
        uint8_t         *pBuffer
    );
    
    
    MEMFILE_DATA *  memFile_Init (
        MEMFILE_DATA    *this
    );


    /*!
     Open an existing file for reading/writing.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         memFile_Open (
        MEMFILE_DATA    *this,
        PATH_DATA       *pPath
    );
    
    
    /*!
     Read a block of data from a specific location in a file. If a partial
     amount of data is read, pReadCount will contain the amount if present
     and the returned code will be ERESULT_SUCCESS_PARTIAL_DATA.
     @param     this        object pointer
     @param     cBuffer     Data block size
     @param     pBuffer     Data block pointer
     @param     pReadCount  Optional Amount actually read pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         memFile_Read(
        MEMFILE_DATA    *this,
        uint32_t        cBuffer,
        void            *pBuffer,
        uint32_t        *pReadCount
    );
    
 
    /*!
     Seek to a specific location in the file.
     @param     this    object pointer
     @param     offset  File Offset where the next data read/write is to occur
     @return    If successful, offset within file; otherwise -1 and an ERESULT_*
     error is set in Last Error.
     */
    off_t           memFile_SeekBegin (
        MEMFILE_DATA     *this,
        off_t           offset
    );
    
    
    off_t           memFile_SeekCur (
        MEMFILE_DATA    *this,
        off_t           offset
    );
    
    
    off_t           memFile_SeekEnd (
        MEMFILE_DATA     *this,
        off_t           offset
    );
    
    
    ERESULT         memFile_SetupSizes(
        MEMFILE_DATA    *this,
        uint32_t        blockSize
    );
    
    
    /*!
     Get the size of the file in bytes.
     @param     this    object pointer
     @return    If successful, size of the file; otherwise -1.
     */
    size_t          memFile_Size (
        MEMFILE_DATA    *this
    );
    
    
    /*!
     Get the current File Offset where the next data read/write is to occur.
     @param     this    object pointer
     @return    If successful, offset within file; otherwise -1.
     */
    off_t           memFile_Tell (
        MEMFILE_DATA    *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = memFile_ToDebugString(this,4);
     @endcode 
     @param     this    MEMFILE object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    memFile_ToDebugString (
        MEMFILE_DATA    *this,
        int             indent
    );
    
    
    /*!
     Write data to the file at the internal offset.
     @param     this    object pointer
     @param     cBuffer Data block size
     @param     pBuffer Data block pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         memFile_Write(
        MEMFILE_DATA    *this,
        uint32_t        cBuffer,
        const
        void            *pBuffer
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* MEMFILE_H */

