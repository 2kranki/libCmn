// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   fileio_internal.h
 *	Generated 07/30/2016 20:56:36
 *
 * Notes:
 *  --	N/A
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



#include    <fileio.h>
#include    <lru.h>




#ifndef FILEIO_INTERNAL_H
#define	FILEIO_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif


#define FILEIO_HNDL_STDIN       0           // Standard Input
#define FILEIO_HNDL_STDOUT      1           // Standard Output
#define FILEIO_HNDL_STDERR      2           // Standard Error Output

typedef enum fileio_Close_e {
    FILEIO_CLOSE_NO=0,                      // Do not issue close.
    FILEIO_CLOSE_REQ,                       // Close is required.
} FILEIO_CLOSE;

typedef enum fileio_Open_e {
    FILEIO_OPEN_NO=0,                       // Do not issue open.
    FILEIO_OPEN_REQ,                        // Open is required.
} FILEIO_OPEN;

typedef enum fileio_Status_e {
    FILEIO_STATUS_NOTAVAIL=0,               // No status yet
    FILEIO_STATUS_CLOSED,                   // File is closed.
    FILEIO_STATUS_READ,                     // File is open for reading only.
    FILEIO_STATUS_WRITE,                    // File is open for writing only.
    FILEIO_STATUS_READWRITE,                // File is open for reading or writing.
    FILEIO_STATUS_EOF                       // EOF or write error has occurred.
} FILEIO_STATUS;


#pragma pack(push, 1)
struct fileio_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;      // Needed for Inheritance
    IO_INTERFACE    IO;
#define FILEIO_FILE_OPEN    OBJ_FLAG_USER1

    // Common Data
    PATH_DATA       *pPath;
    int             fileHandle;
    LRU_DATA        *pLRU;
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

};
#pragma pack(pop)

    extern
    const
    struct fileio_class_data_s  fileio_ClassObj;

    extern
    const
    FILEIO_VTBL         fileio_Vtbl;


    IO_VTBL * fileio_IO_getVtbl (
        void
    );


    // Internal Functions
    void            fileio_Dealloc(
        OBJ_ID          objId
    );

    
    void *          fileio_QueryInfo(
         OBJ_ID          objId,
         uint32_t        type,
         void            *pData
    );
    

#ifdef NDEBUG
#else
    bool			fileio_Validate(
        FILEIO_DATA       *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* FILEIO_INTERNAL_H */

