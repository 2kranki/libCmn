// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Object Generation Helper Methods (ObjGen) Header
//****************************************************************
/*
 * Program
 *          Object Generation Helper Methods (ObjGen)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate ObjGen to run things without complications
 *          of interfering with the main ObjGen. A ObjGen may be 
 *          called a ObjGen on other O/S's.
 *
 * Remarks
 *    1.    Left boundary for methods is 5 with method name at 21.
 *          Method parameters and variables are +4 or 9 (type) and
 *          25 (name).  Comments are generally started in column 37.
 *          We set up a VI settings at the beginning of each source
 *          file which sets tabs to 4. This aligns with the column
 *          numbers mentioned.
 *
 * History
 *  11/19/2021 Generated
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


#ifndef         OBJGEN_H
#define         OBJGEN_H


//#define   OBJGEN_IS_IMMUTABLE     1
//#define   OBJGEN_JSON_SUPPORT     1
//#define   OBJGEN_SINGLETON        1

#define OBJGEN_LINE_LENGTH 71



#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct ObjGen_data_s  OBJGEN_DATA;          // Inherits from OBJGEN
    typedef struct ObjGen_class_data_s OBJGEN_CLASS_DATA;  // Inherits from OBJ

    typedef struct ObjGen_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        //ObjGen_VTBL    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjGen_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJGEN_DATA *);
    } OBJGEN_VTBL;

    typedef struct ObjGen_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in ObjGen_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(OBJGEN_DATA *);
    } OBJGEN_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  OBJGEN_SINGLETON
    OBJGEN_DATA *   ObjGen_Shared (
        void
    );

    void            ObjGen_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to ObjGen object if successful, otherwise OBJ_NIL.
     */
    OBJGEN_DATA *   ObjGen_Alloc (
        void
    );
    
    
    OBJ_ID          ObjGen_Class (
        void
    );
    
    
    OBJGEN_DATA *   ObjGen_New (
        void
    );
    
    
#ifdef  OBJGEN_JSON_SUPPORT
    OBJGEN_DATA *   ObjGen_NewFromJsonString (
        ASTR_DATA       *pString
    );

    OBJGEN_DATA *   ObjGen_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         ObjGen_Disable (
        OBJGEN_DATA     *this
    );


    ERESULT         ObjGen_Enable (
        OBJGEN_DATA     *this
    );

   
    /*!
     Return a header comment line as used in headings where the
     line is a single line comment followed by a fixed number of
     chr's.
     @param     this        object pointer
     @param     fAddOffset  true == prefix line with "\t"
     @param     chrW32      the character to appeend after the
                            single-line comment. Normally, this
                            is '*', '-' or '='.
     @return    if successful, an AStr object containing the header line.
                Otherwise, OBJ_NIL.
     */
    ASTR_DATA *     ObjGen_HeaderLine(
        OBJGEN_DATA     *this,
        bool            fAddOffset,
        W32CHR_T        chrW32
    );


    OBJGEN_DATA *   ObjGen_Init (
        OBJGEN_DATA     *this
    );


    ERESULT         ObjGen_IsEnabled (
        OBJGEN_DATA     *this
    );
    
 
    /*!
     Return a spaced comment line as used in headings where each
     comment character is followed by a space and the comment is
     centered.
     @param     this    object pointer
     @param     pStrA   UTF-8 Comment to be spaced
     @return    if successful, an AStr object containing the header line.
                Otherwise, OBJ_NIL.
     */
    ASTR_DATA *     ObjGen_SpacedComment(
        OBJGEN_DATA     *this,
        const
        char            *pStrA
    );


#ifdef  OBJGEN_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = ObjGen_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjGen_ToJson (
        OBJGEN_DATA     *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = ObjGen_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     ObjGen_ToDebugString (
        OBJGEN_DATA     *this,
        int             indent
    );
    
    
    /*!
     Return the VI header line.
     @param     this    object pointer
     @return    if successful, an AStr object containing the header line.
                Otherwise, OBJ_NIL.
     */
    ASTR_DATA *     ObjGen_VI (
        OBJGEN_DATA     *this
    );


    
#ifdef  __cplusplus
}
#endif

#endif  /* OBJGEN_H */

