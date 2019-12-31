// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   scanner_internal.h
 *	Generated 07/26/2018 19:55:39
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




#include    <scanner.h>
#include    <JsonIn.h>
#include    <scanReader.h>


#ifndef SCANNER_INTERNAL_H
#define	SCANNER_INTERNAL_H



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct scanner_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    uint16_t        size;		    // maximum number of elements
    uint16_t        reserved;
    ASTR_DATA       *pStr;
    W32_READER      *pRdr;

};
#pragma pack(pop)

    extern
    const
    struct scanner_class_data_s  scanner_ClassObj;

    extern
    const
    SCANNER_VTBL         scanner_Vtbl;



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    bool            scanner_setRdr(
        SCANNER_DATA    *this,
        W32_READER      *pValue
    );
    
    
    OBJ_IUNKNOWN *  scanner_getSuperVtbl(
        SCANNER_DATA     *this
    );


    void            scanner_Dealloc(
        OBJ_ID          objId
    );


    SCANNER_DATA *  scanner_ParseObject(
        JSONIN_DATA     *pParser
    );


    void *          scanner_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


    bool            scanner_ScanHex(
        SCANNER_DATA    *this,
        uint32_t        *pValue             // (returned) Scanned Number
    );
    
    
    /*!
     Scan a UTF-8 hexadecimal value such as ([1-9a-fA-F][0-9a-fA-F]*).
     (('-' | ) [1-9][0-9]+). The converted value scanned is returned if scan
     is successful. Nothing is changed if the scan is unsuccessful.
     @param     ppCmdStr    [in/out] pointer to a UTF-8 string pointer. On output
     the pointer will be updated just past the last acceptable
     character scanned.
     @param     pScannedLen Optional pointer to number of characters which created
     the returned string
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
     otherwise false.
     */
    bool            scanner_ScanHex32(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen,       // (returned) Scanned Length
        uint32_t        *pValue             // (returned) Scanned Number
    );
    
    
    bool            scanner_ScanOct(
        SCANNER_DATA    *this,
        uint32_t        *pValue             // (returned) Scanned Number
    );
    
    
    /*!
     Scan a UTF-8 octal value such as ([1-7][0-7]*). The converted value scanned
     is returned if scan is successful. Nothing is changed if the scan is unsuc-
     cessful.
     @param     ppCmdStr    [in/out] pointer to a UTF-8 string pointer. On output
     the pointer will be updated just past the last acceptable
     character scanned.
     @param     pScannedLen Optional pointer to number of characters which created
     the returned string
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
     otherwise false.
     */
    bool            scanner_ScanOct32(
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen,       // (returned) Scanned Length
        uint32_t        *pValue             // (returned) Scanned Number
    );
    
    
    ASTR_DATA *     scanner_ToJSON(
        SCANNER_DATA      *this
    );




#ifdef NDEBUG
#else
    bool			scanner_Validate(
        SCANNER_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SCANNER_INTERNAL_H */

