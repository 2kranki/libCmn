// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  C Lexical Scanner (LexC) Header
//****************************************************************
/*
 * Program
 *          C Lexical Scanner (LexC)
 * Purpose
 *          This object provides a basic C/C++ style lexical
 *          scanner.
 *
 * Remarks
 *  1.      This lexical scanner differs from the ANSI standard in
 *          that embedded multi-line comments are allowed.
 *
 * History
 *  05/30/2020 Generated
 *  09/02/2021 Regenerated from Lex02 and upgraded to new Lex
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
#include        <SrcErrors.h>
#include        <SrcFile.h>


#ifndef         LEXC_H
#define         LEXC_H


//#define   LEXC_IS_IMMUTABLE     1
//#define   LEXC_JSON_SUPPORT     1
//#define   LEXC_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct LexC_data_s  LEXC_DATA;            // Inherits from OBJ
    typedef struct LexC_class_data_s LEXC_CLASS_DATA;   // Inherits from OBJ

    typedef struct LexC_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexC_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXC_DATA *);
    } LEXC_VTBL;

    typedef struct LexC_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in LexC_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEXC_DATA *);
    } LEXC_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEXC_SINGLETON
    LEXC_DATA *     LexC_Shared (
        void
    );

    void            LexC_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to LexC object if successful, otherwise OBJ_NIL.
     */
    LEXC_DATA *     LexC_Alloc (
        void
    );
    
    
    OBJ_ID          LexC_Class (
        void
    );
    
    
    /*!
        Given a lexical value class translate that to a printable string,
        mostly to be used for debugging purposes.
        @return     pointer to string if successful, otherwise
                    "LEX_CLASS_UNKNOWN".
      */
    const
    char *          LexC_ClassToString(
        int32_t         value
    );


    LEXC_DATA *     LexC_New (
        void
    );
    
    
    LEXC_DATA *     LexC_NewFromStrA (
        PATH_DATA       *pPath,
        const
        char            *pStringA
    );


#ifdef  LEXC_JSON_SUPPORT
    LEXC_DATA *     LexC_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEXC_DATA *     LexC_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    LEX_DATA *      LexC_getLex (
        LEXC_DATA       *this
    );



    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    LEXC_DATA *     LexC_Init (
        LEXC_DATA       *this
    );


    /*!
     Advance in the output token stream num tokens, refilling the
     empty positions in the parsed output queue.
     @param     this    object pointer
     @param     num     number of tokens to advance
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    LexC_TokenAdvance(
        LEXC_DATA       *this,
        uint16_t        num
    );


    /*!
     Look Ahead in the output token stream to the num'th token in the
     parsed output queue.
     @param     this    object pointer
     @param     num     number of tokens to lookahead to
     @return:   If successful, a token which must NOT be released,
                otherwise OBJ_NIL.
     */
    TOKEN_DATA *    LexC_TokenLookAhead(
        LEXC_DATA       *this,
        uint16_t        num
    );


#ifdef  LEXC_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = LexC_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexC_ToJson (
        LEXC_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = LexC_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     LexC_ToDebugString (
        LEXC_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEXC_H */

