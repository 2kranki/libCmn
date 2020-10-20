// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Tokenize a TextIn Streams (SrcFiles) Header
//****************************************************************
/*
 * Program
 *          SrcFiles (SrcFiles)
 * Purpose
 *              This object serves two purposes. First, it provides
 *              for file inclusion by using a stack of sources which
 *              when exhausted are popped off the stack. Second, it
 *              provides for translation from a file number used in
 *              the tokens back to a file name.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  10/19/2020 Generated
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
#include        <SrcFile.h>
#include        <ObjArray.h>
#include        <Path.h>
#include        <Token.h>


#ifndef         SRCFILES_H
#define         SRCFILES_H


//#define   SRCFILES_IS_IMMUTABLE     1
//#define   SRCFILES_JSON_SUPPORT     1
//#define   SRCFILES_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct SrcFiles_data_s  SRCFILES_DATA;            // Inherits from OBJ
    typedef struct SrcFiles_class_data_s SRCFILES_CLASS_DATA;   // Inherits from OBJ

    typedef struct SrcFiles_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcFiles_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCFILES_DATA *);
    } SRCFILES_VTBL;

    typedef struct SrcFiles_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in SrcFiles_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(SRCFILES_DATA *);
    } SRCFILES_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  SRCFILES_SINGLETON
    SRCFILES_DATA * SrcFiles_Shared (
        void
    );

    void            SrcFiles_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to SrcFiles object if successful, otherwise OBJ_NIL.
     */
    SRCFILES_DATA * SrcFiles_Alloc (
        void
    );
    
    
    OBJ_ID          SrcFiles_Class (
        void
    );
    
    
    SRCFILES_DATA * SrcFiles_New (
        void
    );
    
    
#ifdef  SRCFILES_JSON_SUPPORT
    SRCFILES_DATA * SrcFiles_NewFromJsonString (
        ASTR_DATA       *pString
    );

    SRCFILES_DATA * SrcFiles_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    OBJARRAY_DATA * SrcFiles_getPaths(
        SRCFILES_DATA   *this
    );


    bool            SrcFiles_getReuse(
        SRCFILES_DATA   *this
    );

    bool            SrcFiles_setReuse(
        SRCFILES_DATA   *this,
        bool            fValue
    );


    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    uint16_t        SrcFiles_AddPath(
        SRCFILES_DATA   *this
    );


    SRCFILES_DATA * SrcFiles_Init(
        SRCFILES_DATA   *this
    );


    TOKEN_DATA *    SrcFiles_InputAdvance(
        SRCFILES_DATA   *this,
        uint16_t        numChrs
    );


    TOKEN_DATA *    SrcFiles_InputLookAhead(
        SRCFILES_DATA   *this,
        uint16_t        num
    );


    /*!
     Create a new srcFile object from the given parameters and push it to the
     top of the stack.
     */
    ERESULT         SrcFiles_NewSrcFromAStr(
        SRCFILES_DATA   *this,
        PATH_DATA       *pFilePath,
        ASTR_DATA       *pAStr,         // Buffer of file data
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    ERESULT         SrcFiles_NewSrcFromFile(
        SRCFILES_DATA   *this,
        FILE            *pFile,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    ERESULT         SrcFiles_NewSrcFromPath(
        SRCFILES_DATA   *this,
        PATH_DATA       *pFilePath,
        uint16_t        fileIndex,      // File Path Index for a separate path table
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    ERESULT         SrcFiles_StackPop(
        SRCFILES_DATA   *this
    );


    ERESULT         SrcFiles_StackPush(
        SRCFILES_DATA   *this,
        SRCFILE_DATA    *pItem
    );


    SRCFILE_DATA *  SrcFiles_StackTop(
        SRCFILES_DATA   *this
    );


    /*
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = SrcFiles_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     SrcFiles_ToDebugString (
        SRCFILES_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* SRCFILES_H */

