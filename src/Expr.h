// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Universal Expression Parser (Expr) Header
//****************************************************************
/*
 * Program
 *			Universal Expression Parser (Expr)
 * Purpose
 *			This object provides Universal Expression Parser.
 *
 * Expr: Logical_Or

 * Remarks
 *	1.      None
 *
 * History
 *	03/03/2020 Generated
 */

/*                 * * *  Expression Grammar  * * *
                                                Associativity
expr        :   Logical_Or
            ;

Logical_Or  :   Logical_Or "||" Logical_And     # Left to Right
            |   Logical_And
            ;

Logical_And :   Logical_And "&&" Bitwise_Or     # Left to Right
            |   Bitwise_Or
            ;

Bitwise_Or  :   Bitwise_Or '|' Bitwise_Xor      # Left to Right
            |   Bitwise_Xor
            ;

Bitwise_Xor :   Bitwise_Xor '^' Bitwise_And     # Left to Right
            |   Bitwise_And
            ;

Bitwise_And :   Bitwise_And '&' Equal           # Left to Right
            |   Equal
            ;

Equal       :   Equql "==" Rel                  # Left to Right
            |   Equal "!=" Rel
            |   Rel
            ;

Rel         :   Rel '<' Shift                   # Left to Right
            |   Rel "<=" Shift
            |   Rel '>' Shift
            |   Rel ">=" Shift
            |   Shift
            ;

Shift       :   Shift "<<" Add                  # Left to Right
            |   Shift ">>" Add
            |   Add
            ;

 Add        :   Add '+' Mult                    # Left to Right
            |   Add '-' Mult
            |   Mult
            ;

 Mult       :   Mult '*' Unary                  # Left to Right
            |   Mult '/' Unary
            |   Mult '%' Unary
            |   Unary
            ;

 Unary      :   '!' Prim                        # Right to Left
            |   '+' Prim
            |   '-' Prim
            |   "++" Prim
            |   "--" Prim
            |   Prim
            ;

 Prim       :   integer                         # Left to Right
            |   symbol
            |   '(' Expr ')'
            ;

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
#include        <Scanner.h>


#ifndef         EXPR_H
#define         EXPR_H


//#define   EXPR_IS_IMMUTABLE     1
//#define   EXPR_JSON_SUPPORT     1
//#define   EXPR_SINGLETON        1





#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct Expr_data_s	EXPR_DATA;            // Inherits from OBJ
    typedef struct Expr_class_data_s EXPR_CLASS_DATA;   // Inherits from OBJ

    typedef struct Expr_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Expr_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXPR_DATA *);
    } EXPR_VTBL;

    typedef struct Expr_class_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in Expr_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(EXPR_DATA *);
    } EXPR_CLASS_VTBL;




    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

#ifdef  EXPR_SINGLETON
    EXPR_DATA *     Expr_Shared (
        void
    );

    void            Expr_SharedReset (
        void
    );
#endif


   /*!
     Allocate a new Object and partially initialize. Also, this sets an
     indicator that the object was alloc'd which is tested when the object is
     released.
     @return    pointer to Expr object if successful, otherwise OBJ_NIL.
     */
    EXPR_DATA *     Expr_Alloc (
        void
    );
    
    
    OBJ_ID          Expr_Class (
        void
    );
    
    
    EXPR_DATA *     Expr_New (
        void
    );
    
    
#ifdef  EXPR_JSON_SUPPORT
    EXPR_DATA *   Expr_NewFromJsonString (
        ASTR_DATA       *pString
    );

    EXPR_DATA *   Expr_NewFromJsonStringA (
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

    ERESULT     Expr_Calc (
        EXPR_DATA	*this,
        int32_t     *pAnswer
    );


    EXPR_DATA *   Expr_Init (
        EXPR_DATA     *this
    );


    /*!
     Set up a Scanner object as the primary source of data and parsing
     support.
     @param     this    object pointer
     @param     pScan   Scanner object pointer
     @return    If successful, ERESULT_SUCCESS, otherwise an ERESULT_* error.
     */
    ERESULT     Expr_SetupScanner (
        EXPR_DATA		*this,
        SCANNER_DATA    *pScan
    );
    
 
#ifdef  EXPR_JSON_SUPPORT
    /*!
     Create a string that describes this object and the objects within it in
     HJSON formt. (See hjson object for details.)
     Example:
     @code
     ASTR_DATA      *pDesc = Expr_ToJson(this);
     @endcode
     @param     this    object pointer
     @return    If successful, an AStr object which must be released containing the
                JSON text, otherwise OBJ_NIL and LastError set to an appropriate
                ERESULT_* error code.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *     Expr_ToJson (
        EXPR_DATA   *this
    );
#endif


    /*!
     Create a string that describes this object and the objects within it.
     Example:
     @code 
        ASTR_DATA      *pDesc = Expr_ToDebugString(this,4);
     @endcode 
     @param     this    object pointer
     @param     indent  number of characters to indent every line of output, can be 0
     @return    If successful, an AStr object which must be released containing the
                description, otherwise OBJ_NIL.
     @warning   Remember to release the returned AStr object.
     */
    ASTR_DATA *    Expr_ToDebugString (
        EXPR_DATA     *this,
        int             indent
    );
    
    

    
#ifdef	__cplusplus
}
#endif

#endif	/* EXPR_H */

