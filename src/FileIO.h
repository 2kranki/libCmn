// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//        Generic Dataset/File Input/Output (FileIO) Header
//****************************************************************
/*
 * Program
 *          Generic Dataset/File Input/Output (FileIO)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate FileIO to run things without complications
 *          of interfering with the main FileIO. A FileIO may be 
 *          called a FileIO on other O/S's.
 *
 * Remarks
 *  1.      This object uses OBJ_FLAG_USER1 and OBJ_FLAG_USER2.
 *
 * History
 *  07/30/2016 Generated
 *  07/10/2021 Regenerated and merged in memFile.
 *  10/29/2021 Changed memory files to use u8Array instead og array.
 *             Added memory file retention so that a memory file can
 *             be closed and then reopened based on path name.
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
#include        <ioInterface.h>
#include        <Path.h>


#ifndef         FILEIO_H
#define         FILEIO_H


//#define   FILEIO_IS_IMMUTABLE     1
//#define   FILEIO_JSON_SUPPORT     1
//#define   FILEIO_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct FileIO_data_s  FILEIO_DATA;            // Inherits from OBJ
    typedef struct FileIO_class_data_s FILEIO_CLASS_DATA;   // Inherits from OBJ

    typedef struct FileIO_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //============= I/O Interface Compatibility ===============
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in FileIO_object.c.
        // Properties:
        // Methods:
        ERESULT         (*pClose) (
            OBJ_ID          this,
            bool            fDelete
        );
        // Flush() writes any pending buffered data to the file output if
        // write() is active.
        ERESULT         (*pFlush)(OBJ_ID);
        // Read() attempts to read the amount of data specified from the
        // data source.  It returns the amount actually read which might
        // be less than the amount requested. It will return -1 if an
        // error or EOF is encountered.
        int32_t         (*pRead)(
                OBJ_ID,
                uint8_t *,                  // Data Buffer Pointer
                int32_t                     // Requested Amount to Read
        );
        // Seek() alters the current file_offset within the data source so that
        // the next read or write will occur at the specified offset.
        off_t           (*pSeek)(
                OBJ_ID,
                off_t,                      // File Offset in Bytes
                uint8_t
#define                     IO_SEEK_SET  1   // Set to given offset
#define                     IO_SEEK_CUR  2   // Use file_offset plus given offset
#define                     IO_SEEK_END  3   // Use eof_offset plus given offset
        );
        off_t           (*pTell)(OBJ_ID);
        // Write() attempts to write the amount of data specified from the
        // data source.  It returns the amount actually written which might
        // be less than the amount requested. It will return -1 if an
        // error or EOF is encountered.
        int32_t         (*pWrite)(
                OBJ_ID,
                uint8_t *,
                int32_t
        );
        //=========== End of I/O Interface Compatibility =============
        ERESULT         (*pGets) (
            OBJ_ID          this,
            uint32_t        cBuffer,
            uint8_t         *pBuffer
        );
        ERESULT         (*pOpen) (
            OBJ_ID          this,
            PATH_DATA       *pPath
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
        ERESULT         (*pCreate) (
            OBJ_ID          this,
            PATH_DATA       *pPath
        );
    } FILEIO_VTBL;

    typedef struct FileIO_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in FileIO_object.c.
        // Properties:
        // Methods:
        bool            (*pMemFileAdd)(OBJ_ID);
        bool            (*pMemFileDelete)(PATH_DATA *);
        OBJ_ID          (*pMemFileFind)(PATH_DATA *);
        void            (*pMemFileReset)(void);
    } FILEIO_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  FILEIO_SINGLETON
    FILEIO_DATA *   FileIO_Shared (
        void
    );

    void            FileIO_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to FileIO object if successful, otherwise OBJ_NIL.
     */
    FILEIO_DATA *   FileIO_Alloc (
        void
    );
    
    
    OBJ_ID          FileIO_Class (
        void
    );
    
    
    FILEIO_DATA *   FileIO_New (
        void
    );
    
    
    /*!
     Create a new file of zero bytes in length and return the FileIO object
     ready to read/write data in it.
     @param     pPath   Path file name to be created
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    FILEIO_DATA *   FileIO_NewCreate (
        PATH_DATA       *pPath,
        bool            fMem
    );


    /*!
     Open an existing file.
     @param     pPath   File's Path
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    FILEIO_DATA *   FileIO_NewOpen (
        PATH_DATA       *pPath,
        bool            fMem
    );


    /*!
     Open a duplicated stdin.
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    FILEIO_DATA *   FileIO_NewStdin (
        void
    );


#ifdef  FILEIO_JSON_SUPPORT
    FILEIO_DATA *   FileIO_NewFromJsonString (
        ASTR_DATA       *pString
    );

    FILEIO_DATA *   FileIO_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     The Append Atrribute defaults to false and data is always
     written to point of the last seek. By setting the Append
     Attribute to true, you force all further writes while it
     is in effect to be at the end of the file.
     */
    bool            FileIO_getAppend (
        FILEIO_DATA     *this
    );

    bool            FileIO_setAppend (
        FILEIO_DATA     *this,
        bool            fValue
    );


    IO_INTERFACE *  FileIO_getIO (
        FILEIO_DATA     *this
    );


    PATH_DATA *     FileIO_getPath (
        FILEIO_DATA     *this
    );

    bool            FileIO_setPath (
        FILEIO_DATA     *this,
        PATH_DATA       *pValue
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
    ERESULT         FileIO_Close (
        FILEIO_DATA     *this,
        bool            fDelete
    );


    /*!
     Create a new file for reading/writing.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         FileIO_Create (
        FILEIO_DATA     *this,
        PATH_DATA       *pPath,
        bool            fMem
    );


    ERESULT         FileIO_Flush (
        FILEIO_DATA     *this
    );


    /*!
     Read a line from the file and store it into the buffer. Stop when either
     (cBuffer - 1) characters are read, the newline character is read, or the
     end-of-file is reached, whichever comes first. '\n' & '\r' are considered
     end-of-line characters and are not included in the buffer.
     @param     this    object pointer
     @param     cBuffer size of the buffer which must be greater than 1
     @param     pBuffer buffer pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         FileIO_Gets (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        uint8_t         *pBuffer
    );


    FILEIO_DATA *   FileIO_Init (
        FILEIO_DATA     *this
    );


    ERESULT         FileIO_IsEnabled (
        FILEIO_DATA     *this
    );
    
 
    bool            FileIO_IsOpen (
        FILEIO_DATA     *this
    );


    /*!
     Open an existing file for reading/writing.
     @param     this    object pointer
     @param     pPath   Path object pointer
     @param     fMem    true == open file as memory based,
                        false == disk based
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         FileIO_Open (
        FILEIO_DATA     *this,
        PATH_DATA       *pPath,
        bool            fMem
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
    ERESULT         FileIO_Read (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        void            *pBuffer,
        uint32_t        *pReadCount
    );


    /*!
     Seek() alters the current file_offset within the data source so that
     the next read or write will occur at the specified offset.
     @param     this    object pointer
     @param     offset  File Offset where the next data read/write is to occur
     @param     type    seek type
     @return    If successful, offset within file; otherwise -1 and an ERESULT_*
                error is set in Last Error.
     */
    off_t           FileIO_Seek(
        FILEIO_DATA     *this,
        off_t           offset,         // File Offset in Bytes
        uint8_t         type
    #define                     IO_SEEK_SET  1   // Set to given offset
    #define                     IO_SEEK_CUR  2   // Use file_offset plus given offset
    #define                     IO_SEEK_END  3   // Use eof_offset plus given offset
    );


    /*!
     Seek to a specific location in the file.
     @param     this    object pointer
     @param     offset  File Offset where the next data read/write is to occur
                        (relative to zero)
     @return    If successful, offset within file; otherwise -1 and an ERESULT_*
                error is set in Last Error.
     */
    off_t           FileIO_SeekBegin (
        FILEIO_DATA     *this,
        off_t           offset
    );


    off_t           FileIO_SeekCur (
        FILEIO_DATA     *this,
        off_t           offset
    );


    off_t           FileIO_SeekEnd (
        FILEIO_DATA     *this,
        off_t           offset
    );


    /*!
     Get the size of the file in bytes.
     @param     this    object pointer
     @return    If successful, size of the file; otherwise -1.
     */
    size_t          FileIO_Size (
        FILEIO_DATA     *this
    );


    /*!
     Get the current File Offset where the next data read/write is to occur.
     File Offset is relative to zero.
     @param     this    object pointer
     @return    If successful, offset within file; otherwise -1.
     */
    off_t           FileIO_Tell (
        FILEIO_DATA     *this
    );


#ifdef  FILEIO_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = FileIO_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     FileIO_ToJson (
        FILEIO_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = FileIO_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     FileIO_ToDebugString (
        FILEIO_DATA     *this,
        int             indent
    );
    
    
    /*!
     Write a block of data to a specific location in a file.
     @param     this    object pointer
     @param     cBuffer Data block size
     @param     pBuffer Data block pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         FileIO_Write (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        const
        void            *pBuffer
    );



    
#ifdef  __cplusplus
}
#endif

#endif  /* FILEIO_H */

