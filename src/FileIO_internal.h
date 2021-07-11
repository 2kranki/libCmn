// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   FileIO_internal.h
 *  Generated 07/10/2021 11:26:44
 *
 * Notes:
 *  --  N/A
 *
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




#include        <FileIO.h>
#include        <array.h>
#include        <JsonIn.h>


#ifndef FILEIO_INTERNAL_H
#define FILEIO_INTERNAL_H





#ifdef  __cplusplus
extern "C" {
#endif




#define FILEIO_HNDL_STDIN       0           // Standard Input
#define FILEIO_HNDL_STDOUT      1           // Standard Output
#define FILEIO_HNDL_STDERR      2           // Standard Error Output

typedef enum FileIO_Close_e {
    FILEIO_CLOSE_NO=0,                      // Do not issue close.
    FILEIO_CLOSE_REQ,                       // Close is required.
} FILEIO_CLOSE;

typedef enum FileIO_Open_e {
    FILEIO_OPEN_NO=0,                       // Do not issue open.
    FILEIO_OPEN_REQ,                        // Open is required.
} FILEIO_OPEN;

typedef enum FileIO_Status_e {
    FILEIO_STATUS_NOTAVAIL=0,               // No status yet
    FILEIO_STATUS_CLOSED,                   // File is closed.
    FILEIO_STATUS_READ,                     // File is open for reading only.
    FILEIO_STATUS_WRITE,                    // File is open for writing only.
    FILEIO_STATUS_READWRITE,                // File is open for reading or writing.
    FILEIO_STATUS_EOF                       // EOF or write error has occurred.
} FILEIO_STATUS;


    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct FileIO_data_s  {
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance
#define FILEIO_FILE_OPEN    OBJ_FLAG_USER1
#define FILEIO_MEM_BASED    OBJ_FLAG_USER2

    // Common Data
    PATH_DATA       *pPath;
    int             fileHandle;
    uint8_t         openFlags;
    uint8_t         closeFlags;
    uint8_t         readAccess;
    uint8_t         writeAccess;
    uint8_t         status;
    uint8_t         filler[3];
#define FILEIO_STATUS_UNKNOWN   0
#define FILEIO_STATUS_CLOSED    1
#define FILEIO_STATUS_READ      2
#define FILEIO_STATUS_WRITE     3
#define FILEIO_STATUS_READWRITE 4
#define FILEIO_STATUS_EOF       5

    // Memory-base FileIO
    ARRAY_DATA      *pData;
    off_t           offset;

};
#pragma pack(pop)

    extern
    struct FileIO_class_data_s  FileIO_ClassObj;

    extern
    const
    FILEIO_VTBL         FileIO_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  FILEIO_SINGLETON
    FILEIO_DATA *     FileIO_getSingleton (
        void
    );

    bool            FileIO_setSingleton (
     FILEIO_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  FileIO_getSuperVtbl (
        FILEIO_DATA     *this
    );


    ERESULT         FileIO_Assign (
        FILEIO_DATA    *this,
        FILEIO_DATA    *pOther
    );


    FILEIO_DATA *       FileIO_Copy (
        FILEIO_DATA     *this
    );


    void            FileIO_Dealloc (
        OBJ_ID          objId
    );


#ifdef  FILEIO_JSON_SUPPORT
    /*!
     Parse the new object from an established parser.
     @param pParser an established jsonIn Parser Object
     @return    a new object if successful, otherwise, OBJ_NIL
     @warning   Returned object must be released.
     */
    FILEIO_DATA *       FileIO_ParseJsonObject (
        JSONIN_DATA     *pParser
    );


    /*!
     Parse the object from an established parser. This helps facilitate
     parsing the fields from an inheriting object.
     @param pParser     an established jsonIn Parser Object
     @param pObject     an Object to be filled in with the
                        parsed fields.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         FileIO_ParseJsonFields (
        JSONIN_DATA     *pParser,
        FILEIO_DATA     *pObject
    );
#endif


    void *          FileIO_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    int32_t         FileIO_ReadIO (
        FILEIO_DATA     *this,
        uint8_t         *pBuffer,
        int32_t         size
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
        FILEIO_DATA      *this
    );


    /*!
     Append the json representation of the object's fields to the given
     string. This helps facilitate parsing the fields from an inheriting 
     object.
     @param this        Object Pointer
     @param pStr        String Pointer to be appended to.
     @return    If successful, ERESULT_SUCCESS. Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         FileIO_ToJsonFields (
        FILEIO_DATA     *this,
        ASTR_DATA       *pStr
    );
#endif


#ifdef NDEBUG
#else
    bool            FileIO_Validate (
        FILEIO_DATA       *this
    );
#endif


    int32_t         FileIO_WriteIO (
        FILEIO_DATA     *this,
        const
        uint8_t         *pBuffer,
        int32_t         size
    );



#ifdef  __cplusplus
}
#endif

#endif  /* FILEIO_INTERNAL_H */

