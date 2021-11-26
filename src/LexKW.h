// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Keyword Lexical Scanner (LexKW) Header
//****************************************************************
/*
 * Program
 *          Keyword Lexical Scanner (LexKW)
 * Purpose
 *          This object provides a standardized way of handling
 *          a separate LexKW to run things without complications
 *          of interfering with the main LexKW. A LexKW may be 
 *          called a LexKW on other O/S's.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  03/30/2021 Generated
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


#ifndef         LEXKW_H
#define         LEXKW_H


//#define   LEXKW_IS_IMMUTABLE     1
//#define   LEXKW_JSON_SUPPORT     1
//#define   LEXKW_SINGLETON        1







#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct LexKW_data_s  LEXKW_DATA;            // Inherits from OBJ
    typedef struct LexKW_class_data_s LEXKW_CLASS_DATA;   // Inherits from OBJ

    typedef struct LexKW_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexKW_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXKW_DATA *);
    } LEXKW_VTBL;

    typedef struct LexKW_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexKW_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXKW_DATA *);
    } LEXKW_CLASS_VTBL;


    // Use uint32_t for these options.
    typedef enum lex_lang_e {
        LEX_LANG_UNKNOWN=0,
        LEX_LANG_ASM        = 0x80000000,       // Base Assembler
        LEX_LANG_ASM86      = 0x40000000,       // -- Intel 8x86 Assembler Extension
        LEX_LANG_ASM360     = 0x20000000,       // -- IBM 360 Assembler Keywords Extension
        LEX_LANG_C          = 0x00800000,       // Base C Language
        LEX_LANG_MSC        = 0x00400000,       // -- Microsoft C Extensions of C
        LEX_LANG_CPP        = 0x00200000,       // -- C++ Keywords Extension of C
        LEX_LANG_OBJC       = 0x00100000,       // -- Obj-C Keywords Extension
        LEX_LANG_OOBJ       = 0x00080000,       // -- Our Object Keywords Extension
        LEX_LANG_LL1        = 0x00010000,       // -- LL1 Extension
    } LEX_LANG;


    typedef struct lex_kwdtbl_entry_s {
        char        *pKwd;                    /* Key Word */
        int32_t     value;                    /* Lexical Scan Value */
        uint32_t    flags;                    /* Flags */
    } LEX_KWDTBL_ENTRY;





    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEXKW_SINGLETON
    LEXKW_DATA *    LexKW_Shared (
        void
    );

    void            LexKW_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to LexKW object if successful, otherwise OBJ_NIL.
     */
    LEXKW_DATA *    LexKW_Alloc (
        void
    );
    
    
    OBJ_ID          LexKW_Class (
        void
    );
    
    
    LEXKW_DATA *    LexKW_New (
        void
    );
    
    
#ifdef  LEXKW_JSON_SUPPORT
    LEXKW_DATA *   LexKW_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEXKW_DATA *   LexKW_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif


    LEX_KWDTBL_ENTRY *
                    LexKW_Search(
        const
        char            *pNameA
    );


    bool            LexKW_ValidateKeywords (
        void
    );


    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT     LexKW_Disable (
        LEXKW_DATA       *this
    );


    ERESULT     LexKW_Enable (
        LEXKW_DATA       *this
    );

   
    LEXKW_DATA *   LexKW_Init (
        LEXKW_DATA     *this
    );


    ERESULT     LexKW_IsEnabled (
        LEXKW_DATA       *this
    );
    
 
#ifdef  LEXKW_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LexKW_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexKW_ToJson (
        LEXKW_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LexKW_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexKW_ToDebugString (
        LEXKW_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEXKW_H */

