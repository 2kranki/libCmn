// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Stacked Text Input Files (TextIns) Header
//****************************************************************
/*
 * Program
 *			Stacked Text Input Files (TextIns)
 * Purpose
 *			This object provides two primary functions. First, it
 *
 *
 * Remarks
 *	1.      None
 *
 * History
 *	02/12/2020 Generated
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
#include        <TextIn.h>


#ifndef         TEXTINS_H
#define         TEXTINS_H


//#define   TEXTINS_IS_IMMUTABLE     1
//#define   TEXTINS_JSON_SUPPORT     1
//#define   TEXTINS_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct TextIns_data_s	TEXTINS_DATA;            // Inherits from OBJ
    typedef struct TextIns_class_data_s TEXTINS_CLASS_DATA;   // Inherits from OBJ

    typedef struct TextIns_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TextIns_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEXTINS_DATA *);
    } TEXTINS_VTBL;

    typedef struct TextIns_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in TextIns_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(TEXTINS_DATA *);
    } TEXTINS_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  TEXTINS_SINGLETON
    TEXTINS_DATA *  TextIns_Shared (
        void
    );

    void            TextIns_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to TextIns object if successful, otherwise OBJ_NIL.
     */
    TEXTINS_DATA *  TextIns_Alloc (
        void
    );
    
    
    OBJ_ID          TextIns_Class (
        void
    );
    
    
    TEXTINS_DATA *  TextIns_New (
        void
    );
    
    
#ifdef  TEXTINS_JSON_SUPPORT
    TEXTINS_DATA *   TextIns_NewFromJsonString (
        ASTR_DATA       *pString
    );

    TEXTINS_DATA *   TextIns_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            TextIns_getReuse(
        TEXTINS_DATA    *this
    );

    bool            TextIns_setReuse(
        TEXTINS_DATA    *this,
        bool            fValue
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
    ERESULT         TextIns_GetLineA (
        TEXTINS_DATA    *this,
        int             size,
        char            *pBuffer,
        SRCLOC          *pLoc
    );

    ERESULT         TextIns_GetLineW32 (
        TEXTINS_DATA    *this,
        int             size,
        W32CHR_T        *pBuffer,
        SRCLOC          *pLoc
    );


    TEXTINS_DATA *  TextIns_Init (
        TEXTINS_DATA    *this
    );


    /*!
     Create a new srcFile object from the given parameters and push it to the
     top of the stack.
     */
    ERESULT         TextIns_NewSrcFromAStr (
        TEXTINS_DATA    *this,
        PATH_DATA       *pFilePath,
        ASTR_DATA       *pAStr,         // Buffer of file data
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );

    ERESULT         TextIns_NewSrcFromPath (
        TEXTINS_DATA    *this,
        PATH_DATA       *pFilePath,
        uint16_t        tabSize         // Tab Spacing if any (0 will default to 4)
    );


    /*!
     Get a path given its index.
     @param     this    object pointer
     @param     index   path name index (relative to 1)
     @return    if successful, path object pointer.  Otherwise, OBJ_NIL.
     */
    PATH_DATA *     TextIns_Path (
        TEXTINS_DATA    *this,
        uint16_t        index
    );


    /*!
     Add a path to the paths if it is not already there and return its index.
     @param     this    object pointer
     @param     pPath   path name object
     @return    if successful, the path name index relative to 1.
                Otherwise, 0.
     */
    uint16_t        TextIns_PathAdd (
        TEXTINS_DATA    *this,
        PATH_DATA       *pPath
    );


    /*!
     Clear/delete all input objects from the stack.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIns_StackClear (
        TEXTINS_DATA    *this
    );


    /*!
     Get an input object given its index.
     @param     this    object pointer
     @param     index   path name index (relative to 1)
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    TEXTIN_DATA *   TextIns_StackGet (
        TEXTINS_DATA    *this,
        uint16_t        index
    );


    /*!
     Pop an input object from the stack so that the next input is from
     the pushed object.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIns_StackPop (
        TEXTINS_DATA    *this
    );


    /*!
     Get an top input object given its index.
     @param     this    object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    TEXTIN_DATA *   TextIns_StackTop (
        TEXTINS_DATA    *this
    );


    /*!
     Push the given input object to the stack making it the top of the
     stack and so that the next input is from this object.
     @param     this    object pointer
     @param     pItem   input TextIn object pointer
     @return    if successful, ERESULT_SUCCESS.  Otherwise, an ERESULT_*
                error code.
     */
    ERESULT         TextIns_StackPush (
        TEXTINS_DATA    *this,
        TEXTIN_DATA     *pItem
    );


#ifdef  TEXTINS_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = TextIns_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     TextIns_ToJson (
        TEXTINS_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = TextIns_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    TextIns_ToDebugString (
        TEXTINS_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* TEXTINS_H */

