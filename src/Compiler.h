// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Compiler Base Object (Compiler) Header
//****************************************************************
/*
 * Program
 *			Compiler Base Object (Compiler)
 * Purpose
 *          This object provides the fundamental objects or pointers
 *          needed by a compiler.
 *
 * Remarks
 *	1.      None
 *
 * History
 *  06/18/2015 Generated
 *	01/04/2020 Regenerated
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
#include        <Token.h>
#include        <stdarg.h>


#ifndef         COMPILER_H
#define         COMPILER_H


//#define   COMPILER_JSON_SUPPORT 1
#define   COMPILER_SINGLETON    1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Compiler_data_s	COMPILER_DATA;            // Inherits from OBJ
    typedef struct Compiler_class_data_s COMPILER_CLASS_DATA;   // Inherits from OBJ

    typedef struct Compiler_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Compiler_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(COMPILER_DATA *);
    } COMPILER_VTBL;

    typedef struct Compiler_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Compiler_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(COMPILER_DATA *);
    } COMPILER_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  COMPILER_SINGLETON
    COMPILER_DATA * Compiler_Shared (
        void
    );

    void            Compiler_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Compiler object if successful, otherwise OBJ_NIL.
     */
    COMPILER_DATA * Compiler_Alloc (
        void
    );
    
    
    OBJ_ID          Compiler_Class (
        void
    );
    
    
    COMPILER_DATA * Compiler_New (
        void
    );
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    SRCERRORS_DATA * Compiler_getErrors (
        COMPILER_DATA   *this
    );

    bool            Compiler_setErrors (
        COMPILER_DATA   *this,
        SRCERRORS_DATA  *pValue
    );


    // Primary Input Source Path
    PATH_DATA *     Compiler_getInputPath (
        COMPILER_DATA   *this
    );

    bool            Compiler_setInputPath (
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    );


    OBJ_ID          Compiler_getLexer (
        COMPILER_DATA   *this
    );

    bool            Compiler_setLexer (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );


    OBJ_ID          Compiler_getListing (
        COMPILER_DATA   *this
    );

    bool            Compiler_setListing (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );


    // Output Directory Path
    PATH_DATA *     Compiler_getOutputDir (
        COMPILER_DATA   *this
    );

    bool            Compiler_setOutputDir (
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    );


    OBJ_ID          Compiler_getParseTree (
        COMPILER_DATA   *this
    );

    bool            Compiler_setParseTree (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );


    // Program Name used in reports and various
    // file names possibly
    ASTR_DATA *     Compiler_getProgramName (
        COMPILER_DATA   *this
    );

    bool            Compiler_setProgramName (
        COMPILER_DATA   *this,
        ASTR_DATA       *pValue
    );


    NODEARRAY_DATA * Compiler_getQueue0 (
        COMPILER_DATA   *this
    );

    bool            Compiler_setQueue0 (
        COMPILER_DATA   *this,
        NODEARRAY_DATA  *pValue
    );


    NODEARRAY_DATA * Compiler_getQueue1 (
        COMPILER_DATA   *this
    );

    bool            Compiler_setQueue1 (
        COMPILER_DATA   *this,
        NODEARRAY_DATA  *pValue
    );


    OBJARRAY_DATA * Compiler_getQueue2 (
        COMPILER_DATA   *this
    );

    bool            Compiler_setQueue2 (
        COMPILER_DATA   *this,
        OBJARRAY_DATA   *pValue
    );


    OBJARRAY_DATA * Compiler_getQueue3 (
        COMPILER_DATA   *this
    );

    bool            Compiler_setQueue3 (
        COMPILER_DATA   *this,
        OBJARRAY_DATA   *pValue
    );


    SRCFILES_DATA * Compiler_getSourceFiles (
        COMPILER_DATA   *this
    );

    bool            Compiler_setSourceFiles (
        COMPILER_DATA   *this,
        SRCFILES_DATA   *pValue
    );


    OBJ_ID          Compiler_getSymbolTable (
        COMPILER_DATA   *this
    );

    bool            Compiler_setSymbolTable (
        COMPILER_DATA   *this,
        OBJ_ID          pValue
    );


    SZTBL_DATA *    Compiler_getStringTable (
        COMPILER_DATA   *this
    );


    // Temporary File Directory Path
    PATH_DATA *     Compiler_getTempDir (
        COMPILER_DATA   *this
    );

    bool            Compiler_setTempDir (
        COMPILER_DATA   *this,
        PATH_DATA       *pValue
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Compiler_AddProperty (
        COMPILER_DATA   *this,
        NODE_DATA       *pData
    );


    /*!
     Create and set up the srcErrors object if it doesn't already exist.
     @param     this    object pointer
     @return    If successful, a srcErrors object; otherwise,
                OBJ_NIL.
     */
    SRCERRORS_DATA * Compiler_Errors (
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
    uint32_t        Compiler_FilePathToIndex (
        COMPILER_DATA   *this,
        const
        char            *pszPath
    );


    const
    char *          Compiler_IndexToFilePath (
        COMPILER_DATA   *this,
        uint32_t        num
    );


    COMPILER_DATA * Compiler_Init (
        COMPILER_DATA   *this
    );


     uint16_t        Compiler_NumberOfProperties (
         COMPILER_DATA   *this
     );


     const
     char *          Compiler_NumberToString (
         COMPILER_DATA    *this,
         uint32_t        num
     );


     NODE_DATA *     Compiler_Property (
         COMPILER_DATA   *this,
         const
         char            *pName
     );


     NODEARRAY_DATA * Compiler_Properties (
         COMPILER_DATA   *this
     );


     uint32_t        Compiler_StringToNumber (
         COMPILER_DATA    *this,
         const
         char            *pszString
     );


     /* StringToString() adds the given string to the static
      * string table and returns a pointer to it there.
      */
     const
     char *          Compiler_StringToString (
         COMPILER_DATA    *this,
         const
         char            *pszString
     );


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Compiler_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Compiler_ToDebugString (
        COMPILER_DATA   *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* COMPILER_H */

