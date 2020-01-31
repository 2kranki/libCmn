// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Comma Delimited File (CsvFile) Header
//****************************************************************
/*
 * Program
 *			Comma Delimited File (CsvFile)
 * Purpose
 *            This object provides support for the comma separated
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
 *
 * Remarks
 *	1.      None
 *
 * History
 *  09/25/2015 Generated
 *	12/30/2019 Regenerated
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
#include        <ObjArray.h>
#include        <Path.h>


#ifndef         CSVFILE_H
#define         CSVFILE_H


//#define   CSVFILE_JSON_SUPPORT 1
//#define   CSVFILE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    #ifndef         CSVFILE_FIELD_MAX
    #define         CSVFILE_FIELD_MAX 512
    #endif


    typedef struct CsvFile_data_s	CSVFILE_DATA;            // Inherits from OBJ
    typedef struct CsvFile_class_data_s CSVFILE_CLASS_DATA;   // Inherits from OBJ

    typedef struct CsvFile_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in CsvFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CSVFILE_DATA *);
    } CSVFILE_VTBL;

    typedef struct CsvFile_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in CsvFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CSVFILE_DATA *);
    } CSVFILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CSVFILE_SINGLETON
    CSVFILE_DATA *  CsvFile_Shared (
        void
    );

    void            CsvFile_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to CsvFile object if successful, otherwise OBJ_NIL.
     */
    CSVFILE_DATA *  CsvFile_Alloc (
        void
    );
    
    
    OBJ_ID          CsvFile_Class (
        void
    );
    
    
    CSVFILE_DATA *  CsvFile_New (
        void
    );
    
    
    CSVFILE_DATA *  CsvFile_NewFromAStr(
        ASTR_DATA       *pAStr,         // Buffer of file data
        PATH_DATA       *pPath,
        uint16_t        tabSize         // Tab Spacing if any
    );

    CSVFILE_DATA *  CsvFile_NewFromPath(
        PATH_DATA       *pPath,
        uint16_t        tabSize         // Tab Spacing if any
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            CsvFile_getHasHeader (
        CSVFILE_DATA    *this
    );

    bool            CsvFile_setHasHeader (
        CSVFILE_DATA    *this,
        bool            fValue
    );


    W32CHR_T        CsvFile_getFieldSeparator (
        CSVFILE_DATA    *this
    );

    bool            CsvFile_setFieldSeparator (
        CSVFILE_DATA    *this,
        W32CHR_T        value
    );


    bool            CsvFile_setRecordProcess (
        CSVFILE_DATA    *this,
        bool            (*pRecordProcess)(void *pRecordData, OBJARRAY_DATA *pRecord),
        void            *pRecordData
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    CSVFILE_DATA *  CsvFile_Init (
        CSVFILE_DATA    *this
    );


    /*!
     Parse the string/file given and return an object array of records where
     each record is an object array of fields. The fields are always strings.
     @return:   If successful, an ObjArray object which must be released,
                otherwise OBJ_NIL.
     */
    OBJARRAY_DATA * CsvFile_ParseFile (
        CSVFILE_DATA	*this
    );
    
 
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = CsvFile_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     CsvFile_ToDebugString (
        CSVFILE_DATA    *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* CSVFILE_H */

