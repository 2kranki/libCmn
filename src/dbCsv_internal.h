// vi:nu:et:sts=4 ts=4 sw=4
/* 
 * File:   dbCsv_internal.h
 *	Generated 09/25/2015 21:26:41
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




#ifndef DBCSV_INTERNAL_H
#define	DBCSV_INTERNAL_H


#include    <dbCsv.h>
#include    <path.h>
#include    <srcFile.h>
#include    <stdio.h>

#ifdef	__cplusplus
extern "C" {
#endif


    
    
    
    
//#pragma pack(push, 1)
struct dbCsv_data_s	{
    /* Warning - OBJ_DATA must be first in this object!
     */
    OBJ_DATA        super;

    // Common Data
    SRCFILE_DATA    *pSrc;
    int32_t         fieldSeparator;
    bool            fHasHeader;

    // Field being built
    uint16_t        sizeFld;            // Size of pFld including NUL
    uint16_t        lenFld;             // Used Length in pFld excluding NUL
    int32_t         *pFld;              // Work String

};
//#pragma pack(pop)

    extern
    const
    OBJ_IUNKNOWN    dbCsv_Vtbl;



    // Internal Functions
    ERESULT         dbCsv_AppendCharToString(
        DBCSV_DATA      *cbp,
        int32_t         chr
    );
    
    void            dbCsv_Dealloc(
        OBJ_ID          objId
    );

    DBCSV_DATA *    dbCsv_Init(
        DBCSV_DATA      *cbp
    );
    
    bool            dbCsv_ParseCRLF(
        DBCSV_DATA      *cbp
    );
    
    bool            dbCsv_ParseEOF(
        DBCSV_DATA      *cbp
    );
    
    ASTR_DATA *     dbCsv_ParseField(
        DBCSV_DATA      *cbp
    );
    
    OBJARRAY_DATA * dbCsv_ParseRecord(
        DBCSV_DATA      *cbp
    );
    
    OBJARRAY_DATA * dbCsv_ParseRecords(
        DBCSV_DATA      *cbp
    );
    
    bool            dbCsv_ParseSEP(
        DBCSV_DATA      *cbp
    );
    
    ASTR_DATA *     dbCsv_ParseStringEscaped(
        DBCSV_DATA      *cbp
    );
    
    ASTR_DATA *     dbCsv_ParseStringNonEscaped(
        DBCSV_DATA      *cbp
    );
    
    bool            dbCsv_ParseTEXTDATA(
        DBCSV_DATA      *cbp
    );
    
#ifdef NDEBUG
#else
    bool			dbCsv_Validate(
        DBCSV_DATA      *cbp
    );
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DBCSV_INTERNAL_H */

