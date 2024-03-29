// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//              Text File Input (TextIn) Header
//****************************************************************
/*
 * Program
 *			Text File Input (TextIn)
 * Purpose
 *			This object provides support to read an ASCII text file
 *			from one of several sources and either at the byte level
 *			or the line level.  It also provides support for skipping
 *          certain portions of the file if needed.
 *
 *          This object also provides for input of 80 column records
 *          as used in the IBM environment where the input has already
 *          been translated from EBCDIC to ASCII. In this case, the
 *          input file consists of 81 byte records with the last byte
 *          being a NL (0x0A) as a record terminator. Normally, the
 *          last eight bytes are a sequence number which may consist
 *          of letters or blanks only, letters combined with numbers
 *          or last just numbers.
 * Remarks
 *	1.      This object uses OBJ_FLAG_USER1 internally.
 *  2.      This object discards all '\r' and uses '\n' to detect end
 *          of line. If the input uses '\r' as a line terminator,
 *          then it will not be properly handled.
 *
 * History
 *	01/21/2020 Regenerated
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
#include        <SrcLoc.h>
#include        <Token.h>



#ifndef         TEXTIN_H
#define         TEXTIN_H


//#define   TEXTIN_JSON_SUPPORT 1
//#define   TEXTIN_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TextIn_data_s	TEXTIN_DATA;            // Inherits from OBJ
    typedef struct TextIn_class_data_s TEXTIN_CLASS_DATA;   // Inherits from OBJ

    typedef struct TextIn_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TextIn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEXTIN_DATA *);
    } TEXTIN_VTBL;

    typedef struct TextIn_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TextIn_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEXTIN_DATA *);
    } TEXTIN_CLASS_VTBL;




    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TEXTIN_SINGLETON
    TEXTIN_DATA *   TextIn_Shared (
        void
    );

    void            TextIn_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TextIn object if successful, otherwise OBJ_NIL.
     */
    TEXTIN_DATA *   TextIn_Alloc (
        void
    );
    
    
    OBJ_ID          TextIn_Class (
        void
    );
    
    
    TEXTIN_DATA *   TextIn_New (
        void
    );
    
    
    TEXTIN_DATA *   TextIn_NewFromAStr (
        PATH_DATA       *pFilePath,     // Optoinal Path used for Documentation Only
        ASTR_DATA       *pStr,          // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    TEXTIN_DATA *  TextIn_NewFromFile (
        PATH_DATA       *pFilePath,
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    TEXTIN_DATA *   TextIn_NewFromPath (
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    TEXTIN_DATA *   TextIn_NewFromStrA (
        PATH_DATA       *pFilePath,
        const
        char            *pStrA,         // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    TEXTIN_DATA *   TextIn_NewFromW32Str (
        PATH_DATA       *pFilePath,
        W32STR_DATA     *pStr,          // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


#ifdef  TEXTIN_JSON_SUPPORT
    TEXTIN_DATA *   TextIn_NewFromJsonString(
        ASTR_DATA       *pString
    );

    TEXTIN_DATA *   TextIn_NewFromJsonStringA(
        const
        char            *pStringA
    );
#endif


    TEXTIN_DATA *  TextIn_NewFromPath (
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    uint16_t        TextIn_getFileIndex (
        TEXTIN_DATA     *this
    );

    bool            TextIn_setFileIndex (
        TEXTIN_DATA     *this,
        uint16_t        value
    );


    PATH_DATA *     TextIn_getPath (
        TEXTIN_DATA     *this
    );


    /*!
     The Remove NL property allows for NLs to be skipped as
     input but still reflected in the statistics.
     */
    bool            TextIn_getRemoveNLs (
        TEXTIN_DATA     *this
    );

    bool            TextIn_setRemoveNLs (
        TEXTIN_DATA     *this,
        bool            fValue
    );


    /*!
     The Tab Size property if non-zero causes horizontal tabs
     to be expanded to spaces to multiples of the tabl size.
     The default is zero (ie no tab expansion).
     */
    uint16_t        TextIn_getTabSize (
        TEXTIN_DATA     *this
    );

    bool            TextIn_setTabSize (
        TEXTIN_DATA     *this,
        uint16_t        value
    );


    /*!
     The Upper Limit property if non-zero causes GetLine() to
     stop gathering data for that line when the limit is reached.
     The remaining data for that line will be skipped. For
     instance, setting this to 80, only returns the first 80
     bytes of a line and the rest of the line is ignored.
     */
    uint16_t        TextIn_getUpperLimit (
        TEXTIN_DATA     *this
    );

    bool            TextIn_setUpperLimit (
        TEXTIN_DATA     *this,
        uint16_t        value
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Read a line of text into the given buffer if it will fit. '\n'
     is considered the line terminator. Ignore '\r' in the file.
     @param     this    object pointer
     @param     pBuffer UTF-8 Buffer for data
     @param     size    size of buffer
     @param     pLoc    Address of SRCLOC used to indicate the first
                        character of the line
     @return    If successful, ERESULT_SUCCESS and pBuffer contains the
                line of UTF-8 text.  ERESULT_EOF_ERROR if end of file
                is reached for first character.  Otherwise, an ERESULT_*
                error.
     */
    ERESULT         TextIn_GetLineA (
        TEXTIN_DATA     *this,
        int             size,
        char            *pBuffer,
        SRCLOC          *pLoc
    );

    ERESULT         TextIn_GetLineW32 (
        TEXTIN_DATA     *this,
        int             size,
        W32CHR_T        *pBuffer,
        SRCLOC          *pLoc
    );


    /*!
     Read a line of text into the given string or obtain a new
     string. '\n' is considered the line terminator. '\r' is ignored.
     @param     this    object pointer
     @param     ppStr   return area for new string object pointer or
                        if not OBJ_NIL on entry to method, truncate
                        given string and use it.
     @param     pLoc    Address of SRCLOC used to indicate the first
                        character of the line
     @return    If successful, ERESULT_SUCCESS and pBuffer contains the
                line of UTF-8 text.  ERESULT_EOF_ERROR if end of file
                is reached for first character.  Otherwise, an ERESULT_*
                error.
     */
    ERESULT         TextIn_GetLineAStr (
        TEXTIN_DATA     *this,
        ASTR_DATA       **ppStr,
        SRCLOC          *pLoc
    );

    ERESULT         TextIn_GetLineW32Str (
        TEXTIN_DATA     *this,
        W32STR_DATA     **ppStr,
        SRCLOC          *pLoc
    );


    TEXTIN_DATA *   TextIn_Init (
        TEXTIN_DATA     *this
    );


    /*!
    Indicate if End-of-File has been reached.
    @return    true if EOF has been reached. Otherwise, false.
    */
    bool            TextIn_IsAtEOF (
        TEXTIN_DATA     *this
    );


    /*! Get the location for the last character received.
    */
    ERESULT         TextIn_Location (
       TEXTIN_DATA     *this,
       uint16_t        *pFilenameIndex,
       size_t          *pOffset,
       uint32_t        *pLineNo,
       uint16_t        *pColNo
    );


    /*!
    Get the next character in the file as a W32CHR_T token only.
    @return    If successful, pointer to a TOKEN_FIELD that contains the next
               character from the file and its associated data. Otherwise, NULL.
    */
    TOKEN_FIELDS *  TextIn_NextToken (
       TEXTIN_DATA      *this
    );


    /*!
     Seek (ie reposition) in the file to the following offset insuring
     that the line and column number are proper.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIn_SeekOffset (
        TEXTIN_DATA     *this,
        int64_t         offset
    );


    ERESULT         TextIn_SetupAStr(
       TEXTIN_DATA      *this,
       PATH_DATA        *pFilePath,     // Optoinal Path used for Documentation Only
       ASTR_DATA        *pStr,          // Buffer of file data
       uint16_t         fileIndex,      // File Path Index for a separate path table
       uint16_t         tabSize         // Tab Spacing if any (0 will default to 4)
    );

    ERESULT         TextIn_SetupFile (
       TEXTIN_DATA     *this,
       PATH_DATA       *pFilePath,
       FILE            *pFile,
       uint16_t        fileIndex,      // File Path Index for a separate path table
       uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    ERESULT         TextIn_SetupPath (
       TEXTIN_DATA     *this,
       PATH_DATA       *pFilePath,
       uint16_t        fileIndex,      // File Path Index for a separate path table
       uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    ERESULT         TextIn_SetupStrA(
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        const
        char            *pStrA,       // Buffer of file data
        uint16_t        fileIndex,    // File Path Index for a separate path table
        uint16_t        tabSize       // Tab Spacing if any (0 will default to 4)
    );

    ERESULT         TextIn_SetupW32Str(
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        W32STR_DATA     *pStr,        // Buffer of file data
        uint16_t        fileIndex,    // File Path Index for a separate path table
        uint16_t        tabSize       // Tab Spacing if any (0 will default to 4)
    );


    ERESULT         TextIn_SkipToEOL (
        TEXTIN_DATA     *this
    );


#ifdef  TEXTIN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TextIn_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextIn_ToJson(
        TEXTIN_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TextIn_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    TextIn_ToDebugString (
        TEXTIN_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TEXTIN_H */

