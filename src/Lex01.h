// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          C99 Lexical Scanner (Lex01) Header
//****************************************************************
/*
 * Program
 *          C99 Lexical Scanner (Lex01)
 * Purpose
 *          This object serves as a filter to convert source code
 *          into C99 Lexical Tokens.
 *
 * Remarks
 *  1.      None
 *
 * History
 *  05/30/2020 Generated
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
#include        <Lex.h>


#ifndef         LEX01_H
#define         LEX01_H


//#define   LEX01_IS_IMMUTABLE     1
//#define   LEX01_JSON_SUPPORT     1
//#define   LEX01_SINGLETON        1





#ifdef  __cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Lex01_data_s  LEX01_DATA;            // Inherits from OBJ
    typedef struct Lex01_class_data_s LEX01_CLASS_DATA;   // Inherits from OBJ

    typedef struct Lex01_vtbl_s  {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex01_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX01_DATA *);
    } LEX01_VTBL;

    typedef struct Lex01_class_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Lex01_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(LEX01_DATA *);
    } LEX01_CLASS_VTBL;


    // The first eight flags are reserved for Lex.
    typedef enum Lex01_Flags_e {
        LEX01_FLAG_RETURN_CM=0x00800000,            // Comments
        LEX01_FLAG_RETURN_NL=0x00400000,            // New-Line
        LEX01_FLAG_RETURN_WS=0x00200000,            // White-Space excluding New-Lines
    } LEX01_FLAGS;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions  * * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  LEX01_SINGLETON
    LEX01_DATA *     Lex01_Shared (
        void
    );

    void            Lex01_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Lex01 object if successful, otherwise OBJ_NIL.
     */
    LEX01_DATA *    Lex01_Alloc (
        void
    );
    
    
    OBJ_ID          Lex01_Class (
        void
    );
    
    
    LEX01_DATA *    Lex01_New (
        void
    );
    
    
#ifdef  LEX01_JSON_SUPPORT
    LEX01_DATA *    Lex01_NewFromJsonString (
        ASTR_DATA       *pString
    );

    LEX01_DATA *    Lex01_NewFromJsonStringA (
        const
        char            *pStringA
    );
#endif



    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    // Comments is a flag to indicate if comments should be
    // included in the token stream. The default is false
    // which excludes comments from the token stream.
    bool            Lex01_getComments(
        LEX01_DATA      *this
    );

    bool            Lex01_setComments(
        LEX01_DATA      *this,
        bool            fValue
    );


    LEX_DATA *      Lex01_getLex(
        LEX01_DATA      *this
    );


    bool            Lex01_getNL(
        LEX01_DATA      *this
    );

    bool            Lex01_setNL(
        LEX01_DATA      *this,
        bool            fValue
    );


    bool            Lex01_geWS(
        LEX01_DATA      *this
    );

    bool            Lex01_setWS(
        LEX01_DATA      *this,
        bool            fValue
    );




    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         Lex01_Disable (
        LEX01_DATA      *this
    );


    ERESULT         Lex01_Enable (
        LEX01_DATA      *this
    );

   
    LEX01_DATA *    Lex01_Init (
        LEX01_DATA      *this
    );


    ERESULT         Lex01_IsEnabled (
        LEX01_DATA      *this
    );
    
 
#ifdef  LEX01_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Lex01_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex01_ToJson (
        LEX01_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Lex01_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Lex01_ToDebugString (
        LEX01_DATA     *this,
        int             indent
    );
    
    

    
#ifdef  __cplusplus
}
#endif

#endif  /* LEX01_H */

