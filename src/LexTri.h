// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  C Trigraph Lexical Scanner (LexTri) Header
//****************************************************************
/*
 * Program
 *          C Trigraph Lexical Scanner (LexTri)
 * Purpose
 *          This object serves as a filter to convert all C
 *          trigraphs back into normal C letters. Most source
 *          tokens are just passed through this. When a trigraph
 *          is recognized, it is converted into one token from
 *          three input tokens.
 *
 *          Trigraphs were created because systems such as IBM
 *          EBCDIC terminals did not have the ASCII character set.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/30/2020 Generated as Lex01
 *  09/02/2021 Regenerated
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
#include        <Lex.h>


#ifndef         LEXTRI_H
#define         LEXTRI_H


//#define   LEXTRI_IS_IMMUTABLE     1
//#define   LEXTRI_JSON_SUPPORT     1
//#define   LEXTRI_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct LexTri_data_s  LEXTRI_DATA;            // Inherits from Lex
    typedef struct LexTri_class_data_s LEXTRI_CLASS_DATA;   // Inherits from OBJ

    typedef struct LexTri_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexTri_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXTRI_DATA *);
    } LEXTRI_VTBL;

    typedef struct LexTri_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexTri_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXTRI_DATA *);
    } LEXTRI_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEXTRI_SINGLETON
    LEXTRI_DATA *     LexTri_Shared (
        void
    );

    void            LexTri_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to LexTri object if successful, otherwise OBJ_NIL.
     */
    LEXTRI_DATA *     LexTri_Alloc (
        void
    );
    
    
    OBJ_ID          LexTri_Class (
        void
    );
    
    
    LEXTRI_DATA *     LexTri_New (
        void
    );
    
    
#ifdef  LEXTRI_JSON_SUPPORT
    LEXTRI_DATA *   LexTri_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEXTRI_DATA *   LexTri_NewFromJsonStringA (
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

    ERESULT     LexTri_Disable (
        LEXTRI_DATA       *this
    );


    ERESULT     LexTri_Enable (
        LEXTRI_DATA       *this
    );

   
    LEXTRI_DATA *   LexTri_Init (
        LEXTRI_DATA     *this
    );


    ERESULT     LexTri_IsEnabled (
        LEXTRI_DATA       *this
    );
    
 
#ifdef  LEXTRI_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LexTri_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexTri_ToJson (
        LEXTRI_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LexTri_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexTri_ToDebugString (
        LEXTRI_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEXTRI_H */

