// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          TEXTOUT Console Transmit Task (textOut) Header
//****************************************************************
/*
 * Program
 *			Separate textOut (textOut)
 * Purpose
 *			This object provides a standardized way of handling
 *          a separate textOut to run things without complications
 *          of interfering with the main textOut. A textOut may be 
 *          called a textOut on other O/S's.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/08/2017 Generated
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


#ifndef         TEXTOUT_H
#define         TEXTOUT_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct textOut_data_s	TEXTOUT_DATA;    // Inherits from OBJ.

    typedef struct textOut_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in textOut_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEXTOUT_DATA *);
    } TEXTOUT_VTBL;



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
     @return    pointer to textOut object if successful, otherwise OBJ_NIL.
     */
    TEXTOUT_DATA *  textOut_Alloc (
        void
    );
    
    
    TEXTOUT_DATA *  textOut_New (
        void
    );
    
    
    TEXTOUT_DATA *  textOut_NewAStr (
        void
    );
    
    
    TEXTOUT_DATA *  textOut_NewFromPath (
        PATH_DATA       *pPath
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    FILE *          textOut_getFile (
        TEXTOUT_DATA    *this
    );

    bool            textOut_setFile (
        TEXTOUT_DATA    *this,
        FILE            *pValue
    );
    
    
    uint16_t        textOut_getOffset (
        TEXTOUT_DATA    *this
    );
    
    bool            textOut_setOffset (
        TEXTOUT_DATA    *this,
        uint16_t        value
    );
    

    char            textOut_getOffsetChr (
        TEXTOUT_DATA    *this
    );
    
    bool            textOut_setOffsetChr (
        TEXTOUT_DATA    *this,
        char            value
    );
    
    
    ASTR_DATA *     textOut_getStr (
        TEXTOUT_DATA    *this
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    TEXTOUT_DATA *  textOut_Init (
        TEXTOUT_DATA     *this
    );


    ERESULT         textOut_Print (
        TEXTOUT_DATA    *this,
        const
        char            *pFormat,
        ...
    );
    
    
    /*!
     Output the given utf-8 string.
     @param     this    Object Pointer
     @param     pStrA   Pointer to UTF-8 character string
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
                an ERESULT_* error code
     */
    ERESULT         textOut_PutA (
        TEXTOUT_DATA    *this,
        const
        char            *pStrA
    );
    
    
    /*!
     Output the given utf-8 string.
     @param     this    Object Pointer
     @param     pStr    Pointer to string
     @return    If successful, ERESULT_SUCCESS.  Otherwise,
     an ERESULT_* error code
     */
    ERESULT         textOut_PutAStr (
        TEXTOUT_DATA    *this,
        ASTR_DATA       *pStr
    );
    
    
    ERESULT         textOut_Putc (
        TEXTOUT_DATA    *this,
        const
        char            chr
    );
    
    
    ERESULT         textOut_Putwc (
        TEXTOUT_DATA    *this,
        const
        W32CHR_T        chr
    );
    
    
    /*!
     Set up this object to write to a file.
     @param     this    object pointer
     @param     pFile   open file to write to
     @param     fClose  true == close the file when done with it.
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an
     ERESULT_* error code.
     */
    ERESULT             textOut_SetupFile (
        TEXTOUT_DATA        *this,
        FILE                *pFile,
        bool                fClose
    );
    
    
    /*!
     Set up this object to write to a file path deleting a prior
     file if it exists.
     @param     this    object pointer
     @param     pPath   file path to write to
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an
                ERESULT_* error code.
     */
    ERESULT             textOut_SetupPath (
        TEXTOUT_DATA        *this,
        PATH_DATA           *pPath
    );
    
    
    /*!
     Set up this object to write to a file path appending to any
     prior data in the file if it exists.
     @param     this    object pointer
     @param     pPath   file path to write to
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an
     ERESULT_* error code.
     */
    ERESULT             textOut_SetupPathAppend (
        TEXTOUT_DATA        *this,
        PATH_DATA           *pPath
    );
    

    /*!
     Set up stdout as the file to write to.
     @param     this    object pointer
     @return    If successful, ERESULT_SUCCESS.  Otherwise, an
                ERESULT_* error code.
     */
    ERESULT             textOut_SetupStdout (
        TEXTOUT_DATA        *this
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = textOut_ToDebugString(this,4);
     @endcode 
     @param     this    TEXTOUT object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    textOut_ToDebugString (
        TEXTOUT_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TEXTOUT_H */

