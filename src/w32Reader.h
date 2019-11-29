// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          UTF-32 Reader Interface (W32_READER) Header
//****************************************************************
/*
 * Program
 *			UTF-32 Reader Interface (W32_READER) Header
 * Purpose
 *          The UTF-32 Reader Interface (W32_READER) provides a 
 *          common interface for reading a UTF-8 string one UTF-32
 *          character at a time.  It supports Look-ahead as well.
 *
 * Remarks
 *	1.      None at this time
 *
 * History
 *	08/11/2019 Created
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
#include        <SrcLoc.h>



#ifndef         W32_READER_H
#define         W32_READER_H

    
typedef struct w32_reader_vtbl_s    {
    OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
    // Properties:
    // Methods:
    // Next() reads the next UTF-32 character from the scan string.
    // It will return -1 if an error or end-of-string (EOS) is encountered.
    W32CHR_T    (*pNext)(OBJ_ID);
    // Peek() returns the n'th character after the current one or -1 if
    // beyond the end-of-string (EOS).
    W32CHR_T    (*pPeek)(
            OBJ_ID,
            uint32_t                    // Number of chars to look ahead
    );
    // Rescan() restarts the scan to the beginning of the data.
    ERESULT     (*pRescan)(OBJ_ID);
} W32_READER_VTBL;
    
typedef struct w32_reader_s    {
    W32_READER_VTBL *pVtbl;
} W32_READER;
    
#define W32_READER_DATA(data,obj_id,interface) (data *)(((uint8_t *)objId)-offsetof(data,interface))

    
#endif  // W32_READER_H







