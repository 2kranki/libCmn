// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Tokenize a TextIn Stream (SrcFile) Header
//****************************************************************
/*
 * Program
 *          Tokenize a TextIn Stream with Look-ahead and Backup
 *          Recovery (SrcFile)
 * Purpose
 *          This object tokenizes an input stream of text using
 *          a TextIn object and provides look-ahead conforming
 *          to Lex input.  It also provides for backup/recovery
 *          of those tokens for lexical scanner that must backup
 *          such as re2c.
 *
 *          This object requires look-ahead which defaults to 4.
 *          This means that you can always see the next 4 tokens
 *          of input.  However, this may be insufficient on oc-
 *          casion.
 *
 *          When look-ahead is insufficient, you can use the
 *          backup and recovery (checkpoint/restart) system which
 *          allows you to look further ahead in the text file
 *          with optional restart if needed (ie parse failure).
 *
 * Remarks
 *  1.      None
 *
 * History
 *  12/18/2018 Generated
 *  06/06/2020 Regenerated and updated with backup/recovery.
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
#include        <laInterface.h>
#include        <Path.h>
#include        <TextIn.h>
#include        <Token.h>


#ifndef         SRCFILE_H
#define         SRCFILE_H


//#define   SRCFILE_IS_IMMUTABLE     1
//#define   SRCFILE_JSON_SUPPORT     1
//#define   SRCFILE_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcFile_data_s  SRCFILE_DATA;            // Inherits from OBJ
    typedef struct SrcFile_class_data_s SRCFILE_CLASS_DATA;   // Inherits from OBJ

    // NOTE: This VTBL must be kept in compliance with the laInterface.
    typedef struct SrcFile_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcFile_object.c.
        // Properties:
        // Methods:
        // Advance() advances the current input source num elements.
        TOKEN_DATA *     (*pAdvance)(
                OBJ_ID,
                uint16_t        num
        );

        // Advance() advances the current input source num elements.
        TOKEN_DATA *     (*pLookAhead)(
                OBJ_ID,
                uint16_t        num
        );

    } SRCFILE_VTBL;

    typedef struct SrcFile_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCFILE_DATA *);
    } SRCFILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCFILE_SINGLETON
    SRCFILE_DATA *  SrcFile_Shared (
        void
    );

    void            SrcFile_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SrcFile object if successful, otherwise OBJ_NIL.
     */
    SRCFILE_DATA *  SrcFile_Alloc (
        void
    );
    
    
    OBJ_ID          SrcFile_Class (
        void
    );
    
    
    SRCFILE_DATA *  SrcFile_New (
        void
    );
    
    SRCFILE_DATA *  SrcFile_NewFromAStr(
        PATH_DATA       *pFilePath,     // Optoinal File Path used for Documentation Purposes
        ASTR_DATA       *pStr,          // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    SRCFILE_DATA *  SrcFile_NewFromFile(
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    SRCFILE_DATA *  SrcFile_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    SRCFILE_DATA *  SrcFile_NewFromStrA(
        PATH_DATA       *pFilePath,     // Optoinal File Path used for Documentation Purposes
        const
        char            *pStrA,         // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    SRCFILE_DATA *  SrcFile_NewFromW32Str(
        PATH_DATA       *pFilePath,     // Optoinal File Path used for Documentation Purposes
        W32STR_DATA     *pStr,          // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


#ifdef  SRCFILE_JSON_SUPPORT
    SRCFILE_DATA *  SrcFile_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SRCFILE_DATA *  SrcFile_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    /*!
     The file index property is meant to index some table for the
     file path information.
     */
    uint16_t        SrcFile_getFileIndex (
        SRCFILE_DATA     *this
    );

    bool            SrcFile_setFileIndex (
        SRCFILE_DATA    *this,
        uint16_t        value
    );


    /*!
     The Remove NL property allows for NLs to be skipped as
     input but still reflected in the statistics.
     */
    bool            SrcFile_getRemoveNLs (
        SRCFILE_DATA    *this
    );

    bool            SrcFile_setRemoveNLs (
        SRCFILE_DATA    *this,
        bool            fValue
    );


    /*!
     The Tab Size property if non-zero causes horizontal tabs
     to be expanded to spaces to multiples of the tabl size.
     The default is zero (ie no tab expansion).
     */
    uint16_t        SrcFile_getTabSize (
        SRCFILE_DATA    *this
    );

    bool            SrcFile_setTabSize (
        SRCFILE_DATA    *this,
        uint16_t        value
    );


    /*! SrcFile inherits from TextIn. So, get direct access
        to TextIn.
     */
    TEXTIN_DATA *   SrcFile_getTextIn (
        SRCFILE_DATA    *this
    );



    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    /*!
     Save the current token for a checkpoint which will allow a restart
     to begin again at this point.  You may issue as many checkpoints as
     you want. However, Restart() will only recognize the last one, because
     they overwrite the previous one (ie not stacked).
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   Mulitple checkpoints can be called, but only the last
                one will be recognized by Restart().
     */
    ERESULT         SrcFile_CheckPoint (
        SRCFILE_DATA    *this
    );


    SRCFILE_DATA *  SrcFile_Init (
        SRCFILE_DATA    *this
    );


    /*!
     Advance the input the number of characters specified.
     @param     this    object pointer
     @param     numChrs number of characters to advance (must be > 0)
     @return    The current token character or OBJ_NIL if an error occurred.
     */
    TOKEN_DATA *    SrcFile_InputAdvance (
        SRCFILE_DATA    *this,
        uint16_t        numChrs
    );


    /*!
     Look ahead the number of characters specified.
     @param     this    object pointer
     @param     num     number of characters to look ahead (must be > 0)
     @return    The token character or OBJ_NIL if an error occurred.
     */
    TOKEN_DATA *    SrcFile_InputLookAhead (
        SRCFILE_DATA    *this,
        uint16_t        num
    );


    /*!
     Restart the token stream at the previous checkpoint.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     @warning   This should never be called unless SrcFile_Checkpoint()
                has already been called first at the point that you
                want restarted at.
     */
    ERESULT         SrcFile_Restart (
        SRCFILE_DATA    *this
    );


#ifdef  SRCFILE_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = SrcFile_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcFile_ToJson (
        SRCFILE_DATA    *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcFile_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcFile_ToDebugString (
        SRCFILE_DATA    *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SRCFILE_H */

