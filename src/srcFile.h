// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Tokenize a Source File (srcFile) Header
//****************************************************************
/*
 * Program
 *			Tokenize a Source File (srcFile)
 * Purpose
 *			This object provides a standardized way of tokenizing
 *          a Source File (ie returning the file one character at
 *          a time with appropriate location information.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	12/18/2018 Generated
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
#include        <path.h>
#include        <Token.h>


#ifndef         SRCFILE_H
#define         SRCFILE_H


//#define   SRCFILE_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct srcFile_data_s	SRCFILE_DATA;            // Inherits from OBJ
    typedef struct srcFile_class_data_s SRCFILE_CLASS_DATA;   // Inherits from OBJ

    typedef struct srcFile_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in srcFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCFILE_DATA *);
    } SRCFILE_VTBL;

    typedef struct srcFile_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in srcFile_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCFILE_DATA *);
    } SRCFILE_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCFILE_SINGLETON
    SRCFILE_DATA *  srcFile_Shared (
        void
    );

    bool            srcFile_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to srcFile object if successful, otherwise OBJ_NIL.
     */
    SRCFILE_DATA *  srcFile_Alloc (
        void
    );
    
    
    OBJ_ID          srcFile_Class (
        void
    );
    
    
    SRCFILE_DATA *  srcFile_New (
        void
    );
    
    SRCFILE_DATA *  srcFile_NewFromAStr(
        PATH_DATA       *pFilePath,     // Optoinal File Path used for Documentation Purposes
        ASTR_DATA       *pStr,          // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    SRCFILE_DATA *  srcFile_NewFromFile(
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    SRCFILE_DATA *  srcFile_NewFromPath(
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );
    
    


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            srcFile_getExpandTabs (
        SRCFILE_DATA    *this
    );
    
    bool            srcFile_setExpandTabs (
        SRCFILE_DATA    *this,
        bool            fValue
    );

    
    /*!
     The file index property is meant to index some table for the
     file path information.
     */
    uint16_t        srcFile_getFileIndex (
        SRCFILE_DATA     *this
    );
    
    bool            srcFile_setFileIndex (
        SRCFILE_DATA    *this,
        uint16_t        value
    );

    
    /*!
     The Remove NL property allows for NLs to be skipped as
     input but still reflected in the statistics.
     */
    bool            srcFile_getRemoveNLs (
        SRCFILE_DATA    *this
    );

    bool            srcFile_setRemoveNLs (
        SRCFILE_DATA    *this,
        bool            fValue
    );
    
    
    /*!
     The Tab Size property if non-zero causes horizontal tabs
     to be expanded to spaces to multiples of the tabl size.
     The default is zero (ie no tab expansion).
     */
    uint16_t        srcFile_getTabSize (
        SRCFILE_DATA    *this
    );
    
    bool            srcFile_setTabSize (
        SRCFILE_DATA    *this,
        uint16_t        value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    SRCFILE_DATA *   srcFile_Init (
        SRCFILE_DATA     *this
    );
    
    
    /*!
     Advance the input the number of characters specified.
     @param     this    object pointer
     @param     numChrs number of characters to advance (must be > 0)
     @return    The current token character or OBJ_NIL if an error occurred.
     */
    TOKEN_DATA *    srcFile_InputAdvance (
        SRCFILE_DATA    *this,
        uint16_t        numChrs
    );
    
    
    /*!
     Look ahead the number of characters specified.
     @param     this    object pointer
     @param     num     number of characters to look ahead (must be > 0)
     @return    The token character or OBJ_NIL if an error occurred.
     */
    TOKEN_DATA *    srcFile_InputLookAhead (
        SRCFILE_DATA    *this,
        uint16_t        num
    );
    
    
    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = srcFile_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    srcFile_ToDebugString (
        SRCFILE_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* SRCFILE_H */

