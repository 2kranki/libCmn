// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   CsvFile_internal.h
 *	Generated 12/30/2019 11:06:40
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




#include        <CsvFile.h>
#include        <JsonIn.h>
#include        <SrcFile.h>


#ifndef CSVFILE_INTERNAL_H
#define	CSVFILE_INTERNAL_H



#define     PROPERTY_STR_OWNED 1



#ifdef	__cplusplus
extern "C" {
#endif




    //---------------------------------------------------------------
    //                  Object Data Description
    //---------------------------------------------------------------

#pragma pack(push, 1)
struct CsvFile_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;
    OBJ_IUNKNOWN    *pSuperVtbl;    // Needed for Inheritance

    // Common Data
    SRCFILE_DATA    *pSrc;
    W32CHR_T        fieldSeparator;
    uint8_t         fHasHeader;
    uint8_t         filler8[3];

    // Field being built
    uint16_t        sizeFld;            // Size of pFld including NUL
    uint16_t        lenFld;             // Used Length in pFld excluding NUL
    W32CHR_T        *pFld;              // Work String
    
    bool            (*pRecordProcess)(void *pRecordData, OBJARRAY_DATA *pRecord);
    //                                  // Returns: true == Add Record to Records
    //                                  //          false == Don't add Record
    void            *pRecordData;

};
#pragma pack(pop)

    extern
    struct CsvFile_class_data_s  CsvFile_ClassObj;

    extern
    const
    CSVFILE_VTBL         CsvFile_Vtbl;



    //---------------------------------------------------------------
    //              Class Object Method Forward Definitions
    //---------------------------------------------------------------

#ifdef  CSVFILE_SINGLETON
    CSVFILE_DATA *  CsvFile_getSingleton (
        void
    );

    bool            CsvFile_setSingleton (
     CSVFILE_DATA       *pValue
);
#endif



    //---------------------------------------------------------------
    //              Internal Method Forward Definitions
    //---------------------------------------------------------------

    OBJ_IUNKNOWN *  CsvFile_getSuperVtbl (
        CSVFILE_DATA     *this
    );


    ERESULT         CsvFile_AppendCharW32ToString (
        CSVFILE_DATA    *this,
        W32CHR_T        chr
    );
 

    void            CsvFile_Dealloc (
        OBJ_ID          objId
    );


    bool            CsvFile_ParseCRLF (
        CSVFILE_DATA    *this
    );


    bool            CsvFile_ParseEOF (
        CSVFILE_DATA    *this
    );


    ASTR_DATA *     CsvFile_ParseField (
        CSVFILE_DATA    *this
    );


#ifdef  CSVFILE_JSON_SUPPORT
    CSVFILE_DATA *  CsvFile_ParseJsonObject (
        JSONIN_DATA     *pParser
    );
#endif


    OBJARRAY_DATA * CsvFile_ParseRecord(
        CSVFILE_DATA    *this
    );
    

    OBJARRAY_DATA * CsvFile_ParseRecords(
        CSVFILE_DATA    *this
    );
    

    bool            CsvFile_ParseSEP(
        CSVFILE_DATA    *this
    );
    

    ASTR_DATA *     CsvFile_ParseStringEscaped(
        CSVFILE_DATA    *this
    );
    

    ASTR_DATA *     CsvFile_ParseStringNonEscaped(
        CSVFILE_DATA    *this
    );
    

    bool            CsvFile_ParseTEXTDATA(
        CSVFILE_DATA    *this
    );
    

    bool            CsvFile_ParseWS(
        CSVFILE_DATA    *this
    );
    
    
    void *          CsvFile_QueryInfo (
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    );


#ifdef  SRCREF_JSON_SUPPORT
    ASTR_DATA *     CsvFile_ToJson (
        CSVFILE_DATA    *this
    );
#endif




#ifdef NDEBUG
#else
    bool			CsvFile_Validate (
        CSVFILE_DATA       *this
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* CSVFILE_INTERNAL_H */

