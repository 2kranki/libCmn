// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          SCANNER Console Transmit Task (scanner) Header
//****************************************************************
/*
 * Program
 *			Separate scanner (scanner)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate scanner to run things without complications
 *          of interfering with the main scanner. A scanner may be 
 *          called a scanner on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	07/26/2018 Generated
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
#include        <w32Reader.h>


#ifndef         SCANNER_H
#define         SCANNER_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct scanner_data_s	SCANNER_DATA;    // Inherits from OBJ.

    typedef struct scanner_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in scanner_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SCANNER_DATA *);
    } SCANNER_VTBL;



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to scanner object if successful, otherwise OBJ_NIL.
     */
    SCANNER_DATA *  scanner_Alloc (
        void
    );
    
    
    OBJ_ID          scanner_Class (
        void
    );
    
    
    SCANNER_DATA *  scanner_New (
        void
    );
    
    
    SCANNER_DATA *  scanner_NewReader(
        W32_READER      *pRdr
    );
    
    
    /*!
     Scan a UTF-8 decimal value such as:
                ('0' ('x' | 'X') [0-9a-fA-F]*)      ** Hexadecimal **
            |   ('0' [0-7]*)                        ** Octal **
            |   (('-' | '+' | ) [1-9][0-9]+)        ** Decimal **
     The value scanned is returned if scan is successful.
     Nothing is changed if the scan is unsuccessful.
     @param     ppCmdStr    [in/out] pointer to a UTF-8 string pointer. On output
                            the pointer will be updated just past the last acceptable
                            character scanned.
     @param     pScannedLen Optional pointer to number of characters which created
                            the returned string
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
                otherwise false.
     */
    bool            scanner_ScanDec32 (
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen,       // (returned) Scanned Length
        uint32_t        *pValue             // (returned) Scanned Number
    );
    

    /*!
     Scan a string from the input which is terminated by white-space, comma or NUL.
     The string may be qouted with ' or ".  A quoted string may contain \b, \f, \n,
     or \r which will be properly scanned and translated.
     @param     ppCmdStr    [in/out] pointer to a UTF-8 string pointer. On output
                            the pointer will be updated just past the last acceptable
                            character scanned.
     @param     pScannedLen Optional pointer to number of characters which created
                            the returned string
     @return    If successful, an AStr object which must be released containing the
                scanned string, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     scanner_ScanStringToAStr (
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen        // [out] Scanned Length
        //                                  // (not including leading whitespace)
    );
    
    
    /*!
     Set up an ArgC/ArgV type array given a command line string
     excluding the program name.
     @param     pCmdStrA    Pointer to a UTF-8 Argument character string
     @return    If successful, an AStrArray object which must be
                released containing the Argument Array, otherwise
                OBJ_NIL if an error occurred.
     @warning   Remember to release the returned AStrArray object.
     */
    ASTRARRAY_DATA * scanner_ScanStringToAstrArray (
        const
        char            *pCmdStrA
    );
    
    
    /*!
     Scan UTF-8 white-space from the input string discarding it.
     @param     ppCmdStr    [in/out] pointer to a UTF-8 string pointer. On output
                            the pointer will be updated just past the last acceptable
                            character scanned.
     @param     pScannedLen Optional pointer to number of characters which created
                            the returned string
     @return    If successful, true, otherwise false.
     */
    bool            scanner_ScanWhite (
        char            **ppCmdStr,         // NUL terminated string pointer
        uint32_t        *pScannedLen        // (returned) Scanned Length
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    W32_READER *    scanner_getRdr(
        SCANNER_DATA    *this
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SCANNER_DATA *   scanner_Init (
        SCANNER_DATA     *this
    );


    /*!
     Scan a UTF-8 decimal value such as:
     ('0' ('x' | 'X') [0-9a-fA-F]*)      ** Hexadecimal **
     |   ('0' [0-7]*)                        ** Octal **
     |   (('-' | '+' | ) [1-9][0-9]+)        ** Decimal **
     The scan is successful if the number has a valid format and
     it is properly terminated.
     The value scanned is returned if scan is successful.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
                otherwise false.
     */
    bool            scanner_ScanDec (
        SCANNER_DATA    *this,
        uint32_t        *pValue             // (returned) Scanned Number
    );
    
    
    /*!
     Scan a UTF-8 number such as:
     ('0' ('x' | 'X') [0-9a-fA-F]*)      ** Hexadecimal **
     |   ('0' [0-7]*)                        ** Octal **
     |   (('-' | '+' | ) [1-9][0-9]+)        ** Decimal **
     The scan is successful if the number has a valid format.
     The value scanned is returned if scan is successful.
     Nothing is changed if the scan is unsuccessful.
     @param     this    object pointer
     @param     pValue      Optional pointer to where value will be returned
     @return    If successful, true and *pValue contains the amount converted,
     otherwise false.
     */
    bool            scanner_ScanNumber (
        SCANNER_DATA    *this,
        uint32_t        *pValue             // (returned) Scanned Number
    );
    
    
    /*!
     Scan UTF-8 white-space from the input string discarding it.
     @param     this    object pointer
     @return    If successful, true, otherwise false.
     */
    bool            scanner_ScanWS (
        SCANNER_DATA    *this
    );
    
    
    ERESULT         scanner_Setup (
        SCANNER_DATA    *this,
        const
        char            *pStrA
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = scanner_ToDebugString(this,4);
     @endcode 
     @param     this    SCANNER object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    scanner_ToDebugString (
        SCANNER_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SCANNER_H */

