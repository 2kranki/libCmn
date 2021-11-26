// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          I/O Interface (ioInterface) Header
//****************************************************************
/*
 * Program
 *			I/O Interface (ioInterface)
 * Purpose
 *          The I/O Interface providing a common interface for
 *          objects that need to do file-like I/O.
 *
 *          An object would provide this interface after it has
 *          opened the file source.The default size is 80 bytes. It is assumed that data
 *          is only in columns 1 - 71. Column 72 is a continuation
 *          indicator with a default continuation column of 16.
 *          Columns 73 - 80 are assumed to be sequence numbers
 *          which are not checked.
 *
 *          All memory needed is gotten from the operating system
 *          to minimize impact on C's Heap.
 *
 *          An associated LRU buffering mechanism is utilized in
 *          these routines.
 *
 * Remarks
 *	1.      Internally, lines may be 80-82 characters. When a
 *          dataset is opened, it will be scanned at bytes 80
 *          and 81 to determine if there are \r or \n characters
 *          after the 80 bytes of data.
 *
 * History
 *	08/10/2019 Created
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



#ifndef         IOINTERFACE_H
#define         IOINTERFACE_H

    
typedef struct io_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Properties:
        // Methods:
        // Close() closes the current file source.
        ERESULT     (*pClose)(OBJ_ID);
        // Flush() writes any pending buffered data to the file output if
        // write() is active.
        ERESULT     (*pFlush)(
                OBJ_ID
        );
        // Read() attempts to read the amount of data specified from the
        // data source.  It returns the amount actually read which might
        // be less than the amount requested. It will return -1 if an
        // error or EOF is encountered.
        int32_t     (*pRead)(
                OBJ_ID, 
                uint8_t *,                  // Data Buffer Pointer 
                int32_t                     // Requested Amount to Read
        );
        // Seek() alters the current file_offset within the data source so that
        // the next read or write will occur at the specified offset.
        off_t       (*pSeek)(
                OBJ_ID, 
                off_t,                      // File Offset in Bytes 
                uint8_t
#define                     IO_SEEK_SET  1   // Set to given offset
#define                     IO_SEEK_CUR  2   // Use file_offset plus given offset
#define                     IO_SEEK_END  3   // Use eof_offset plus given offset
        );
        off_t       (*pTell)(OBJ_ID);
        // Write() attempts to write the amount of data specified from the
        // data source.  It returns the amount actually written which might
        // be less than the amount requested. It will return -1 if an
        // error or EOF is encountered.
        int32_t     (*pWrite)(OBJ_ID, uint8_t *, int32_t);
    } IO_VTBL;
    
    typedef struct io_interface_s    {
        IO_VTBL     *pVtbl;
    } IO_INTERFACE;
    
#define IO_INTERFACE_DATA(data,obj_id,interface)\
            (data *)(((uint8_t *)objId)-offsetof(data,interface))

#define iIO_Close(pIO)\
        ((IO_INTERFACE *)(pIO))->pVtbl->pClose(pIO)
#define iIO_Flush(pIO)\
        ((IO_INTERFACE *)(pIO))->pVtbl->pFlush(pIO)
#define iIO_Read(pIO,pBuffer,size)\
        ((IO_INTERFACE *)(pIO))->pVtbl->pRead(pIO, pBuffer, size)
#define iIO_Seek(pIO,offset,type)\
        ((IO_INTERFACE *)(pIO))->pVtbl->pSeek(pIO, offset, type)
#define iIO_Tell(pIO)\
        ((IO_INTERFACE *)(pIO))->pVtbl->pTell(pIO)
#define iIO_Write(pIO,pBuffer,size)\
        ((IO_INTERFACE *)(pIO))->pVtbl->pWrite(pIO, pBuffer, size)

#endif  // IOINTERFACE_H







