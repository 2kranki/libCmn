// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Compiler Base Object (compiler) Header
//****************************************************************
/*
 * Program
 *				Compiler Base Object (compiler)
 * Purpose
 *				This object provides the fundamental objects or pointers
 *              needed by a compiler.
 *
 * Remarks
 *	1.      None
 *
 * History
 *	06/18/2015 Generated
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
#include        <lex.h>
#include        <node.h>
#include        <ObjArray.h>
#include        <path.h>
#include        <prt.h>
#include        <SrcErrors.h>
#include        <srcFiles.h>
#include        <szTbl.h>
#include        <AStr.h>
#include        <token.h>
#include        <stdarg.h>


#ifndef         COMPILER_H
#define         COMPILER_H  1



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct compiler_data_s	COMPILER_DATA;

    typedef struct compiler_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in table_object.c.
    } COMPILER_VTBL;
    
    


    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    COMPILER_DATA * compiler_Alloc(
        void
    );
    
    
    COMPILER_DATA * compiler_New(
        void
    );
    
    
    COMPILER_DATA * compiler_Shared(
        void
    );
    
    
    bool            compiler_SharedReset(
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    SRCERRORS_DATA * compiler_getErrors(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setErrors(
        COMPILER_DATA   *this,
        SRCERRORS_DATA  *pValue
    );
    
    
    // Primary Input Source Path
    PATH_DATA *     compiler_getInputPath(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setInputPath(
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    );

    
    ERESULT         compiler_getLastError(
        COMPILER_DATA   *this
    );
    
    
    OBJ_ID          compiler_getLexer(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setLexer(
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );
    
    
    OBJ_ID          compiler_getListing(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setListing(
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );
    

    // Output Directory Path
    PATH_DATA *     compiler_getOutputDir(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setOutputDir(
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    );
    
    
    OBJ_ID          compiler_getParseTree(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setParseTree(
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );
    
    
    // Program Name used in reports and various
    // file names possibly
    ASTR_DATA *     compiler_getProgramName(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setProgramName(
        COMPILER_DATA   *this,
        ASTR_DATA       *pValue
    );
    
    
    NODEARRAY_DATA * compiler_getQueue0(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setQueue0(
        COMPILER_DATA   *this,
        NODEARRAY_DATA  *pValue
    );
    
    
    NODEARRAY_DATA * compiler_getQueue1(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setQueue1(
        COMPILER_DATA   *this,
        NODEARRAY_DATA  *pValue
    );
    
    
    OBJARRAY_DATA * compiler_getQueue2(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setQueue2(
        COMPILER_DATA   *this,
        OBJARRAY_DATA   *pValue
    );
    
    
    OBJARRAY_DATA * compiler_getQueue3(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setQueue3(
        COMPILER_DATA   *this,
        OBJARRAY_DATA   *pValue
    );
    
    
    SRCFILES_DATA * compiler_getSourceFiles(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setSourceFiles(
        COMPILER_DATA   *this,
        SRCFILES_DATA   *pValue
    );
    
    
    OBJ_ID          compiler_getSymbolTable(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setSymbolTable(
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );
    
    
    SZTBL_DATA *    compiler_getStringTable(
        COMPILER_DATA   *this
    );

    
    // Temporary File Directory Path
    PATH_DATA *     compiler_getTempDir(
        COMPILER_DATA   *this
    );
    
    bool            compiler_setTempDir(
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    );
    
    
    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         compiler_AddProperty(
        COMPILER_DATA   *this,
        NODE_DATA       *pData
    );
    
    
    /*!
     Create and set up the srcErrors object if it doesn't already exist.
     @param     this    object pointer
     @return    If successful, a srcErrors object; otherwise,
                OBJ_NIL.
     */
    SRCERRORS_DATA * compiler_Errors (
        COMPILER_DATA   *this
    );
    
    
    /*!
     Create a File Index to be used in tokens, error messages and
     other objects that need to reference back to a specific source
     location.
     @param     this    object pointer
     @param     pszPath UTF-8 File Path pointer
     @return    If successful, an integer greater than zero; otherwise,
                zero.
     */
    uint32_t        compiler_FilePathToIndex(
        COMPILER_DATA   *this,
        const
        char            *pszPath
    );
    
    
    const
    char *          compiler_IndexToFilePath(
        COMPILER_DATA   *this,
        uint32_t        num
    );
    
    
    /* Init() sets up the default TaskBody() outlined above
     * and initializes other fields needed. Init() assumes 
     * that the size of the stack is passed to in obj_misc1.
     */
    COMPILER_DATA * compiler_Init(
        COMPILER_DATA   *this
    );


    uint16_t        compiler_NumberOfProperties(
        COMPILER_DATA   *this
    );
    
    
    const
    char *          compiler_NumberToString(
        COMPILER_DATA	*this,
        uint32_t        num
    );
    
    
    NODE_DATA *     compiler_Property(
        COMPILER_DATA   *this,
        const
        char            *pName
    );
    
    
    NODEARRAY_DATA * compiler_Properties(
        COMPILER_DATA   *this
    );
    
    
    uint32_t        compiler_StringToNumber(
        COMPILER_DATA	*this,
        const
        char            *pszString
    );
    
   
    /* StringToString() adds the given string to the static
     * string table and returns a pointer to it there.
     */
    const
    char *          compiler_StringToString(
        COMPILER_DATA	*this,
        const
        char            *pszString
    );
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* COMPILER_H */

