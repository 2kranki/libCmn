// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//            Comma Delimited Record (CsvRcd) Header
//****************************************************************
/*
 * Program
 *          Comma Delimited Record (CsvRcd)
 * Purpose
 *            This object provides support for the comma separated
 *          values format (CSV) record.
 *
 *          BNF for csv files:
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
 *  1.  https://stackoverflow.com/questions/14274259/read-csv-with-scanner
 *      talks about valid CSV scanning and notes that rfc4180 denotes the
 *      proper scanning of CSV records. https://datatracker.ietf.org/doc/html/rfc4180
 *
 * History
 *  07/16/2021 Generated
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
#include        <W32Array.h>
#include        <W32Str.h>


#ifndef         CSVRCD_H
#define         CSVRCD_H


//#define   CSVRCD_IS_IMMUTABLE     1
//#define   CSVRCD_JSON_SUPPORT     1
//#define   CSVRCD_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct CsvRcd_data_s  CSVRCD_DATA;            // Inherits from OBJ
    typedef struct CsvRcd_class_data_s CSVRCD_CLASS_DATA;   // Inherits from OBJ

    typedef struct CsvRcd_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in CsvRcd_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CSVRCD_DATA *);
    } CSVRCD_VTBL;

    typedef struct CsvRcd_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in CsvRcd_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(CSVRCD_DATA *);
    } CSVRCD_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  CSVRCD_SINGLETON
    CSVRCD_DATA *   CsvRcd_Shared (
        void
    );

    void            CsvRcd_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to CsvRcd object if successful, otherwise OBJ_NIL.
     */
    CSVRCD_DATA *   CsvRcd_Alloc (
        void
    );
    
    
    OBJ_ID          CsvRcd_Class (
        void
    );
    
    
    CSVRCD_DATA *   CsvRcd_New (
        void
    );
    
    
#ifdef  CSVRCD_JSON_SUPPORT
    CSVRCD_DATA *   CsvRcd_NewFromJsonString (
        ASTR_DATA       *pString
    );

    CSVRCD_DATA *   CsvRcd_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    ASTRARRAY_DATA * CsvRcd_getErrors (
        CSVRCD_DATA     *this
    );

    bool            CsvRcd_setErrors (
        CSVRCD_DATA     *this,
        ASTRARRAY_DATA  *pValue
    );


    W32STR_DATA *   CsvRcd_getStr (
        CSVRCD_DATA     *this
    );

    bool            CsvRcd_setStr (
        CSVRCD_DATA     *this,
        W32STR_DATA     *pValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    CSVRCD_DATA *   CsvRcd_Init (
        CSVRCD_DATA     *this
    );


    /*!
     Parse the given line into an array of wide strings.  If there
     are errors in the parse, they will be found in the Errors
     property.  Otherwise, the errors property will be OBJ_NIL.
     @param     this    object pointer
     @param     pLine   line input object pointer
     @return    If successful, an W32Array object which must be released
                containing W32Str's for each field. Otherwise OBJ_NIL.
     @warning   Remember to release the returned W32Array object.
     */
    W32ARRAY_DATA * CsvRcd_Parse (
        CSVRCD_DATA     *this,
        W32STR_DATA     *pLine
    );


#ifdef  CSVRCD_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = CsvRcd_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     CsvRcd_ToJson (
        CSVRCD_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = CsvRcd_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     CsvRcd_ToDebugString (
        CSVRCD_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* CSVRCD_H */

