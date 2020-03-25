// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Text File Input (TextIn) Header
//****************************************************************
/*
 * Program
 *			Text File Input (TextIn)
 * Purpose
 *			This object provides support to read a text file from
 *			one of several sources and either at the byte level or
 *			the line level.
 *
 * Remarks
 *	1.      This object uses OBJ_FLAG_USER1 internally.
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


    typedef struct textIn_char_s {
        SRCLOC          loc;
        int32_t         cls;        // ASCII Class
        W32CHR_T        chr;
    } TEXTIN_CHAR;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


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
     The remaining data for that line will be skipped.
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


    TEXTIN_DATA *   TextIn_Init (
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
    Return the next character in the file.
    @return    If successful, ERESULT_SUCCESS and *pChar contains the next
               character from the file, otherwise, an ERESULT_* error and
               *pChar contains EOF(-1).
    */
    W32CHR_T        TextIn_NextChar (
       TEXTIN_DATA      *this
    );

    ERESULT         TextIn_NextChrLoc(
       TEXTIN_DATA      *this,
       TEXTIN_CHAR      *pChr               // [out] next char is returned here
    );


    ERESULT         TextIn_SetupAStr(
       TEXTIN_DATA      *this,
       PATH_DATA        *pFilePath,     // Optoinal Path used for Documentation Only
       ASTR_DATA        *pStr,          // Buffer of file data
       uint16_t        fileIndex,      // File Path Index for a separate path table
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

    ERESULT         TextIn_SetupU8Array (
       TEXTIN_DATA     *this,
       U8ARRAY_DATA    *pBuffer,       // Buffer of file data
       PATH_DATA       *pFilePath,
       uint16_t        fileIndex,      // File Path Index for a separate path table
       uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    ERESULT         TextIn_SetupW32Str(
        TEXTIN_DATA     *this,
        PATH_DATA       *pFilePath,
        W32STR_DATA     *pStr,        // Buffer of file data
        uint16_t        fileIndex,    // File Path Index for a separate path table
        uint16_t        tabSize       // Tab Spacing if any (0 will default to 4)
    );


    ERESULT             TextIn_SkipToEOL (
        TEXTIN_DATA         *this
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
        TEXTIN_DATA   *this
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

