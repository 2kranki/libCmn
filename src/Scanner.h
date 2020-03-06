// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          String Scanner (Scanner) Header
//****************************************************************
/*
 * Program
 *			String Scanner (Scanner)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate Scanner to run things without complications
 *          of interfering with the main Scanner. A Scanner may be 
 *          called a Scanner on other O/S's.
 *
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

    /*! Property: Separator is an optional seperator which if present
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
     Return the character pointed at by the obj's Misc plus offset.
     @param     this    object pointer
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
    bool            Scanner_MatchChr(
        SCANNER_DATA    *this,
        W32CHR_T        chr
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
     Scan a UTF-8 identifier defined by:
            [a-zA-Z_][0-9a-zA-Z_]*
     The value scanned is returned if scan is successful.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @return    If successful, an AStr object is returned.
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
     The value scanned is returned if scan is successful.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
                otherwise false.
     */
    bool            Scanner_ScanInteger32 (
        SCANNER_DATA    *this,
        int32_t         *pValue
    );


    /*!
     Scan a string from the input which is terminated by white-space, comma or NUL.
     The string may be qouted with ' or ".  A quoted string may contain \b, \f, \n,
     or \r which will be properly scanned and translated.
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
     excluding the program name.
     @return    If successful, an AStrArray object which must be
                released containing the Argument Array, otherwise
                OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStrArray object.
     */
    ASTRARRAY_DATA * Scanner_ScanStringToAstrArray (
        SCANNER_DATA    *this
    );

        /*!
     Scan White-space.
     @param     this    object pointer
     @return    If successful, true, otherwise false.
     */
    bool            Scanner_ScanWS (
        SCANNER_DATA    *this
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

