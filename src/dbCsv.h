// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Comma Delimited Files (dbCsv) Header
//****************************************************************
/*
 * Program
 *			Separate dbCsv (dbCsv)
 * Purpose
 *			This object provides support for the comma separated 
 *          values format (CSV) file.
 *
 *          BNF for csv files:
 *              file : [header CRLF] record {CRLF record} [CRLF] (CPM_EOF | EOF)
 *                   ;
 *              header : name {SEP name}
 *                     ;
 *              record : field {SEP field}
 *                     ;
 *              name : field
 *                   ;
 *              field : 
                            escaped 
                        |   non-escaped
 *                    ;
 *              escaped :   '"'
                                {
                                    TEXTDATA 
                                |   SEP 
                                |   '\t' 
                                |   '\r' 
                                |   '\n' 
                                |   '"' '"' 
                                |   '\' '"'
                                } 
                            '"'
 *                      ;
 *              non-escaped : {TEXTDATA}
 *                          ;
 *              SEP : ',' | '\t' | ' '      // defined for entire file
 *                    ;
 *              CRLF : '\r' ['\n'] | '\n' ['\r']
 *                   ;
 *              TEXTDATA :  [(' '..'~') - (SEP, '"')]
 *                       |  unicode_char    // (> 128)
 *                       ;
 * Remarks
 *	1.      None
  *
 * History
 *	09/25/2015 Generated
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
#include        <objArray.h>
#include        <path.h>


#ifndef         DBCSV_H
#define         DBCSV_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************

#ifndef         DBCSV_FIELD_MAX
#define         DBCSV_FIELD_MAX 512
#endif


    typedef struct dbCsv_data_s	DBCSV_DATA;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the dbCsv including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    DBCSV_DATA *     dbCsv_Alloc(
    );
    
    
    DBCSV_DATA *     dbCsv_New(
    );
    
    DBCSV_DATA *    dbCsv_NewAStr(
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    
    DBCSV_DATA *    dbCsv_NewFile(
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            dbCsv_getHasHeader(
        DBCSV_DATA      *this
    );

    bool            dbCsv_setHasHeader(
        DBCSV_DATA      *this,
        bool            fValue
    );
    
    
    int32_t         dbCsv_getFieldSeparator(
        DBCSV_DATA      *this
    );
    
    bool            dbCsv_setFieldSeparator(
        DBCSV_DATA      *this,
        int32_t         value
    );
    
    
    bool            dbCsv_setRecordProcess(
        DBCSV_DATA      *this,
        bool            (*pRecordProcess)(void *pRecordData, OBJARRAY_DATA *pRecord),
        void            *pRecordData
    );
    
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    DBCSV_DATA *    dbCsv_InitFile(
        DBCSV_DATA      *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize                 // Tab Spacing if any
    );
    
    DBCSV_DATA *    dbCsv_InitAStr(
        DBCSV_DATA      *this,
        ASTR_DATA       *pSzStr,        // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );

    DBCSV_DATA *    dbCsv_InitWStr(
        DBCSV_DATA      *this,
        WSTR_DATA       *pWStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t		tabSize         // Tab Spacing if any
    );

    
    /*!
     Parse the string/file given and return an object array of records where
     each record is an object array of fields. The fields are always strings.
     @return:   If successful, an ObjArray object which must be released,
                otherwise OBJ_NIL.
     */
    OBJARRAY_DATA * dbCsv_ParseFile(
        DBCSV_DATA		*this
    );
    
    
    /*!
     Create a string that describes this object and the
     objects within it.
     @return:   If successful, an AStr object which must be released,
                otherwise OBJ_NIL.
     */
    ASTR_DATA *     dbCsv_ToDebugString(
        DBCSV_DATA      *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* DBCSV_H */

