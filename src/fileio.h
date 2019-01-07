// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Generic Disk File Input/Output (fileio) Header
//****************************************************************
/*
 * Program
 *			Generic Disk File Input/Output (fileio)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate fileio to run things without complications
 *          of interfering with the main fileio. A fileio may be 
 *          called a fileio on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal fileio. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	07/30/2016 Generated
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


#ifndef         FILEIO_H
#define         FILEIO_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct fileio_data_s	FILEIO_DATA;    // Inherits from OBJ.

    typedef struct fileio_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fileio_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FILEIO_DATA *);
    } FILEIO_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return:   pointer to fileio object if successful, otherwise OBJ_NIL.
     */
    FILEIO_DATA *   fileio_Alloc(
        void
    );
    
    
    FILEIO_DATA *   fileio_New(
        void
    );
    
    
    /*!
     Create a new file of zero bytes in length and return the fileio object
     ready to read/write data in it.
     @param     pPath   Path file name to be created
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    FILEIO_DATA *   fileio_NewCreate(
        PATH_DATA       *pPath
    );
    
    
    /*!
     Open an existing file.
     @param     pPath   File's Path
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    FILEIO_DATA *   fileio_NewOpen(
        PATH_DATA       *pPath
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     The Append Atrribute defaults to false and data is always
     written to point of the last seek. By setting the Append
     Attribute to true, you force all further writes while it
     is in effect to be at the end of the file.
     */
    bool            fileio_getAppend(
        FILEIO_DATA     *this
    );
    
    bool            fileio_setAppend(
        FILEIO_DATA     *this,
        bool            fValue
    );
    

    ERESULT         fileio_getLastError(
        FILEIO_DATA     *this
    );
    
    
    PATH_DATA *     fileio_getPath(
        FILEIO_DATA     *this
    );
    
    bool            fileio_setPath(
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
    ERESULT         fileio_Close(
        FILEIO_DATA     *this,
        bool            fDelete
    );


    /*!
     Create a new file for reading/writing.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         fileio_Create(
        FILEIO_DATA     *this,
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
    ERESULT         fileio_Gets (
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        uint8_t         *pBuffer
    );
    
    
    FILEIO_DATA *   fileio_Init(
        FILEIO_DATA     *this
    );


    bool            fileio_IsOpen(
        FILEIO_DATA     *this
    );
    
    
    /*!
     Open an existing file for reading/writing.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS; otherwise ERESULT_* error.
     */
    ERESULT         fileio_Open(
        FILEIO_DATA		*this,
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
    ERESULT         fileio_Read(
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        void            *pBuffer,
        uint32_t        *pReadCount
    );
    
    
    /*!
     Read a block of data from a specific location in a file.
     @param     this    object pointer
     @param     offset  File Offset where the next data read/write is to occur
     @return    If successful, offset within file; otherwise -1 and an ERESULT_*
                error is set in Last Error.
     */
    off_t           fileio_Seek(
        FILEIO_DATA     *this,
        off_t           offset
    );
    
    
    off_t           fileio_SeekCur(
        FILEIO_DATA     *this,
        off_t           offset
    );
    
    
    off_t           fileio_SeekEnd(
        FILEIO_DATA     *this,
        off_t           offset
    );
    
    
    /*!
     Get the size of the file in bytes.
     @param     this    object pointer
     @return    If successful, size of the file; otherwise -1.
     */
    size_t          fileio_Size(
        FILEIO_DATA     *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code
        ASTR_DATA      *pDesc = fileio_ToDebugString(pObj,4);
     @endcode
     @param     this    fileio object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     fileio_ToDebugString(
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
    ERESULT         fileio_Write(
        FILEIO_DATA     *this,
        uint32_t        cBuffer,
        const
        void            *pBuffer
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_H */

