// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Generic String Scanner (Scanner) Header
//****************************************************************
/*
 * Program
 *			Generic String Scanner (Scanner)
 * Purpose
 *			This object provides a generic scanner which is based
 *          on a builtin static W32StrC.  Originally, it was a set
 *          of disjoint routines that scanned various types of
 *          items which were used mostly to scan program command
 *          lines. They have been updated to be more cohesive and
 *          more general in nature.
 *
 *          Most of the methods will first scan off white-space
 *          before beginning their specific scan.
 * Remarks
 *  1.      OBJ_FLAG_USER1 is used by this object.
 *  2.      obj's Misc fields are used by this object.
 *
 * History
 *  07/26/2018 Generated
 *	03/04/2020 Regenerated
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
#include        <AStrArray.h>


#ifndef         SCANNER_H
#define         SCANNER_H


//#define   SCANNER_IS_IMMUTABLE     1
#define   SCANNER_JSON_SUPPORT     1
//#define   SCANNER_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Scanner_data_s	SCANNER_DATA;            // Inherits from OBJ
    typedef struct Scanner_class_data_s SCANNER_CLASS_DATA;   // Inherits from OBJ

    typedef struct Scanner_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Scanner_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SCANNER_DATA *);
    } SCANNER_VTBL;

    typedef struct Scanner_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Scanner_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SCANNER_DATA *);
    } SCANNER_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SCANNER_SINGLETON
    SCANNER_DATA *  Scanner_Shared (
        void
    );

    void            Scanner_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Scanner object if successful, otherwise OBJ_NIL.
     */
    SCANNER_DATA *  Scanner_Alloc (
        void
    );


    OBJ_ID          Scanner_Class (
        void
    );
    
    
    SCANNER_DATA *  Scanner_New (
        void
    );
    

    SCANNER_DATA *  Scanner_NewA (
        const
        char            *pStrA
    );


    SCANNER_DATA *  Scanner_NewW32(
        const
        W32CHR_T        *pStr
    );


#ifdef  SCANNER_JSON_SUPPORT
    SCANNER_DATA *  Scanner_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SCANNER_DATA *  Scanner_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*! @property   scan index
        The scan index is where within this string the LookAhead()
        and Advancee() methods start their search.
     */
    uint32_t        Scanner_getIndex(
        SCANNER_DATA    *this
    );

    bool            Scanner_setIndex(
        SCANNER_DATA    *this,
        uint32_t        value
    );


    bool            Scanner_setLabelChars(
        SCANNER_DATA    *this,
        bool            (*pIsLabelCharW32)(W32CHR_T chr),
        bool            (*pIsLabel1stCharW32)(W32CHR_T chr)
    );


    /*! @property Separator is an optional seperator which if present
        will influence how strings are separated. For command line
        scanning, this should be set to '='.
     */
    W32CHR_T        Scanner_getSeperator (
        SCANNER_DATA    *this
    );

    bool            Scanner_setSeperator (
        SCANNER_DATA    *this,
        W32CHR_T        value
    );


    W32STRC_DATA *  Scanner_getW32StrC (
        SCANNER_DATA    *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Advance the index into the string by the offset amount.
     @param     this    object pointer
     @param     offset  amount to advance scan by
     @warning   This method uses obj's misc field.
     */
    void            Scanner_Advance(
        SCANNER_DATA    *this,
        int32_t         offset
    );


    /*!
     Assign the contents of this object to the other object (ie
     this -> other).  Any objects in other will be released before
     a copy of the object is performed.
     Example:
     @code
        ERESULT eRc = Scanner_Assign(this,pOther);
     @endcode
     @param     this    object pointer
     @param     pOther  a pointer to another SCANNER object
     @return    If successful, ERESULT_SUCCESS otherwise an
                ERESULT_* error
     */
    ERESULT         Scanner_Assign (
        SCANNER_DATA    *this,
        SCANNER_DATA    *pOther
    );


    /*!
     Compare the two provided objects.
     @return    ERESULT_SUCCESS_EQUAL if this == other
                ERESULT_SUCCESS_LESS_THAN if this < other
                ERESULT_SUCCESS_GREATER_THAN if this > other
     */
    ERESULT         Scanner_Compare (
        SCANNER_DATA     *this,
        SCANNER_DATA     *pOther
    );


    /*!
     Copy the current object creating a new object.
     Example:
     @code
        Scanner      *pCopy = Scanner_Copy(this);
     @endcode
     @param     this    object pointer
     @return    If successful, a SCANNER object which must be
                released, otherwise OBJ_NIL.
     @warning   Remember to release the returned object.
     */
    SCANNER_DATA *  Scanner_Copy (
        SCANNER_DATA    *this
    );


    uint32_t        Scanner_Hash(
        SCANNER_DATA    *this
    );


    SCANNER_DATA *  Scanner_Init (
        SCANNER_DATA    *this
    );


    /*!
     Check to see if there is more data to scan.
     @param     this    object pointer
     @return    If there is more to scan, true, otherwise false.
     */
    bool            Scanner_IsMore (
        SCANNER_DATA    *this
    );


    /*!
     Return the character pointed at by the obj's Misc plus offset
     (ie one of the next character(s) to be scanned).
     @param     this    object pointer
     @param     offset  offset of lookahead (relative to 1)
     @return    If successful, the indexed character, otherwise 0.
     @warning   This method uses obj's misc field.
     */
    W32CHR_T        Scanner_LookAhead(
        SCANNER_DATA    *this,
        uint32_t        offset              // Relative to 1
    );


    /*!
     Match the given character against the current obj's Misc
     index into the string.  If they match, advance the scan.
     @param     this    object pointer
     @param     chr     character to be matched
     @return    If they match, return true otherwise false.
     @warning   This method uses obj's misc field.
     */
    bool            Scanner_MatchChrW32(
        SCANNER_DATA    *this,
        W32CHR_T        chr
    );


    /*!
     Match each of the given character(s) against the current obj's
     Misc index into the string.  If they match, advance the scan
     and return true. Otherwise, try the next charactere in the list
     terminating when NUL is found.
     @param     this    object pointer
     @param     pChrs   pointer to a NUL-terminaed list of characters
                        to be matched
     @return    If they match, return true; otherwise false.
     @warning   This method uses obj's misc field.
     */
    bool            Scanner_MatchChrsW32(
        SCANNER_DATA    *this,
        W32CHR_T        *pChrs
    );


    /*!
     Match the given UTF-8 String against the current obj's Misc
     index into the string.  If they match, it advances the scan.
     @param     this    object pointer
     @param     pStrA   string to be matched
     @return    If they match, return true otherwise false.
     @warning   This method uses obj's misc field.
     */
    bool            Scanner_MatchStrA(
        SCANNER_DATA    *this,
        const
        char            *pStrA
    );


    /*!
     Reset the scan index.
     @param     this    object pointer
     @warning   This method uses obj's misc field.
     */
    void            Scanner_Reset(
        SCANNER_DATA    *this
    );


    /*!
     Assume that the scanner string is an expression, parse it and
     calculate its answer.
     @param     this    object pointer
     @param     pAnswer pointer where answer is returned
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         Scanner_ScanExpr (
        SCANNER_DATA    *this,
        int32_t         *pAnswer
    );


    /*!
     Scan a UTF-8 identifier defined by:
            [a-zA-Z_][0-9a-zA-Z_]*
     Leading white-space is skipped and the scan terminates
     when a charracter which does not match the above is found.
     @param     this    object pointer
     @return    If successful, an AStr object is returned. Otherwise, OBJ_NIL.
     @warning   The AStr object must be released!
     */
    ASTR_DATA *     Scanner_ScanIdentifierToAStr(
        SCANNER_DATA    *this
    );


    /*!
     Scan a UTF-8 decimal value such as:
                ('0' ('x' | 'X') [0-9a-fA-F]*)      ** Hexadecimal **
            |   ('0' [0-7]*)                        ** Octal **
            |   (('-' | '+' | ) [1-9][0-9]+)        ** Decimal **
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     pValue  Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
                otherwise false.
     */
    bool            Scanner_ScanInteger32 (
        SCANNER_DATA    *this,
        int32_t         *pValue
    );


    /*!
     Scan a string from the input which is terminated by comma or NUL. This
     is equivalent to a comma delimited file type scan. The string may be
     quoted or not.  Whitespace will be absorbed into the string if not
     quoted. Leading whitespace will not be absorbed into the string.
     If strings need to contain spaces, they must be surrounded
     by quotes, either single or double.  Quoted strings may also
     contain the special sequences which will be translated into
     specific characters such as:
            \\      '\'
            \b      0x07
            \f      0x0C
            \n      0x0A
            \r      0x0D
            \t      0x09
     Quoted strings are terminated by a quote which is the duplicate
     of the leading quote, either single or double. For a non-quoted
     string, the scan is terminated by a comma (',') or line ter-
     minator (NUL). Note that this is a slightly different scan
     than the one used for ScanStringToAstrArray(). In either case,
     the scan is left pointing after the string terminator.
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                scanned string, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Scanner_ScanStringToAStr (
        SCANNER_DATA    *this
    );


    /*!
     Set up an ArgC/ArgV type array given a command line string
     excluding the program name. The string is parsed using ',',
     whitespace or line terminator (NUL) to separate each item.
     If strings need to contain spaces, they must be surrounded
     by quotes, either single or double.  Quoted strings may also
     contain the special sequences which will be translated into
     specific characters such as:
            \\      '\'
            \b      0x07
            \f      0x0C
            \n      0x0A
            \r      0x0D
            \t      0x09
     Quoted strings are tereminated by a quote which is the duplicate
     of the leading quote.  Non-quoted strings are terminated by
     ',', whitespace or line terminator (NUL). The scan is stopped
     at the line terminator (NUL).
     @return    If successful, an AStrArray object which must be
                released containing the Argument Array, otherwise
                OBJ_NIL if an error occurred. The first of element
                of the returned array will be a "" string to take
                the place of the program name.
     @warning   Remember to release the returned AStrArray object.
     */
    ASTRARRAY_DATA * Scanner_ScanStringToAstrArray (
        SCANNER_DATA    *this
    );


    /*!
     Scan a UTF-8 decimal value such as:
                ('0' ('x' | 'X') [0-9a-fA-F]*)      ** Hexadecimal **
            |   ('0' [0-7]*)                        ** Octal **
            |   [1-9][0-9]+)                        ** Decimal **
     The value scanned is returned if scan is successful and the next
     scan will start immediately after this one. No terminator is con-
     sidered since the scan is well defined.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
                otherwise false.
     */
    bool            Scanner_ScanUnsigned32 (
        SCANNER_DATA    *this,
        uint32_t        *pValue
    );


    /*!
     Scan White-space moving the scan point past the white-space.
     @param     this    object pointer
     @return    If successful, true, otherwise false.
     */
    bool            Scanner_ScanWS (
        SCANNER_DATA    *this
    );


    /*!
     Set up the given string as the string to be scanned, resetting
     the internal scan state and releasing any prior scan data.
     @return    If successful, true; otherewise, false.
     */
    ERESULT         Scanner_SetupA(
        SCANNER_DATA    *this,
        const
        char            *pStrA
    );


#ifdef  SCANNER_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Scanner_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Scanner_ToJson (
        SCANNER_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Scanner_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Scanner_ToDebugString (
        SCANNER_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SCANNER_H */

